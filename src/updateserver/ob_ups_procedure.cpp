#include "ob_ups_procedure.h"

using namespace oceanbase::updateserver;
using namespace oceanbase::sql;

int SpUpsInstExecStrategy::execute_inst(SpInst *inst)
{
  int ret = OB_SUCCESS;
  SpInstType type = inst->get_type();
//  TBSYS_LOG(TRACE, "execute inst[%ld]", i);
  switch(type)
  {
  case SP_E_INST:
    ret = execute_expr(static_cast<SpExprInst*>(inst));
    break;
  case SP_EA_INST:
    ret = execute_array_expr(static_cast<SpArrayExprInst*>(inst));
    break;
  case SP_D_INST:
    ret = execute_rw_delta(static_cast<SpRwDeltaInst*>(inst));
    break;
  case SP_DE_INST:
    ret = execute_rw_delta_into_var(static_cast<SpRwDeltaIntoVarInst*>(inst));
    break;
//  case SP_BLOCK_INST:
//    ret = execute_block(static_cast<SpBlockInsts*>(inst));
//    break;
  case SP_C_INST:
    ret = execute_if_ctrl(static_cast<SpIfCtrlInsts*>(inst));
    break;
  default:
    ret = OB_NOT_SUPPORTED;
    TBSYS_LOG(WARN, "Unsupport execute inst[%d] on updateserver", type);
    break;
  }
  return ret;
}


int SpUpsInstExecStrategy::execute_expr(SpExprInst *inst)
{
  int ret = OB_SUCCESS;
  TBSYS_LOG(TRACE, "expr plan: \n%s", to_cstring(inst->get_val()));
  common::ObRow input_row;
  const ObObj *val = NULL;
  if((ret= inst->get_val().calc(input_row, val))!=OB_SUCCESS)
  {
    TBSYS_LOG(WARN, "sp expr compute failed");
  }
  //update the varialbe here
  else if ( OB_SUCCESS != (ret = inst->get_ownner()->write_variable(inst->get_var(), *val)) )
  {}
  return ret;
}

int SpUpsInstExecStrategy::execute_array_expr(SpArrayExprInst *inst)
{
  int ret = OB_SUCCESS;
  TBSYS_LOG(TRACE, "expr plan: \n%s", to_cstring(*(inst->get_val_expr())));
  common::ObRow input_row;
  const ObObj *val = NULL;
  int64_t idx = 0;
  if( OB_SUCCESS != (ret = inst->get_idx_expr()->calc(input_row, val)) )
  {
    TBSYS_LOG(WARN, "sp idx_expr calc failed");
  }
  else if( val->get_type() != ObIntType)
  {
    TBSYS_LOG(WARN, "idx value type is not int, value = %s", to_cstring(*val));
    ret = OB_ERR_ILLEGAL_INDEX;
  }
  else
  {
    ret = val->get_int(idx);
  }

  if( OB_SUCCESS == ret) {}
  else if((ret= inst->get_val_expr()->calc(input_row, val))!=OB_SUCCESS)
  {
    TBSYS_LOG(WARN, "sp expr compute failed");
  }
  //update the varialbe here
  //have some problem here, to store the array value on ups
  else if ( OB_SUCCESS != (ret = inst->get_ownner()->write_variable(inst->get_array_name(), *val)) )
  {}
  return ret;
}

//int SpRwDeltaInst::ups_exec()
int SpUpsInstExecStrategy::execute_rw_delta(SpRwDeltaInst *inst)
{
  int ret = OB_SUCCESS;
  //it should be a ObUpsModify
  TBSYS_LOG(TRACE, "rw delta inst plan: \n%s", to_cstring(*(inst->get_rwdelta_op())));
  if( OB_SUCCESS != (ret = inst->get_rwdelta_op()->open()) )
  {
    TBSYS_LOG(WARN, "execute rw_delta_inst on ups");
  }
  return ret;
}

//int SpRwDeltaIntoVarInst::ups_exec()
int SpUpsInstExecStrategy::execute_rw_delta_into_var(SpRwDeltaIntoVarInst *inst)
{
  int ret = OB_SUCCESS;
  const common::ObRow *row;
  ObPhyOperator *op_ = inst->get_rwdelta_op();
  ObArray<SpVar> &var_list_ = inst->get_var_list();
  SpProcedure *proc = inst->get_ownner();
  TBSYS_LOG(TRACE, "rw_delta_into_var inst plan: \n%s", to_cstring(*op_));
  if(NULL != op_)
  {
    op_->open();
    ret = op_->get_next_row(row);

    if( ret == OB_ITER_END )
    {
      ret = OB_ERROR; //does not get row
    }
    else if( ret == OB_SUCCESS )
    {
      for(int64_t i = 0; i < var_list_.count() && OB_SUCCESS == ret; ++i)
      {
        SpVar &var = var_list_.at(i);
        const ObObj *cell = NULL;
        if(OB_SUCCESS !=(ret=row->raw_get_cell(i, cell)))//取出一列
        {
          TBSYS_LOG(WARN, "raw_get_cell %ld failed", i);
        }
        else if(OB_SUCCESS !=(proc->write_variable(var, *cell)))
        {
          TBSYS_LOG(WARN, "write into variables fail");
        }

      }
    }
  }
  return ret;
}

//int SpBlockInsts::ups_exec()
int SpUpsInstExecStrategy::execute_block(SpBlockInsts* inst)
{
  int ret = OB_SUCCESS;
  ObArray<SpInst*>& inst_list_ = inst->get_inst_list();
//  const SpProcedure *proc_ = inst->get_ownner();
  for(int64_t i = 0; i < inst_list_.count() && OB_SUCCESS == ret; ++i)
  {
    TBSYS_LOG(TRACE, "execute inst[%ld]", i);
    ret = execute_inst(inst);
//    proc_->debug_status(inst);
  }
  return ret;
}

int SpUpsInstExecStrategy::execute_if_ctrl(SpIfCtrlInsts *inst)
{
  int ret = OB_SUCCESS;
  common::ObRow fake_row;
  const ObObj *flag = NULL;
  TBSYS_LOG(TRACE, "if_ctrl inst:\n%s", to_cstring(inst->get_if_expr()));
  if(OB_SUCCESS != (ret = inst->get_if_expr().calc(fake_row, flag)) )
  {
    TBSYS_LOG(WARN, "if expr evalute failed");
  }
  else if( flag->is_true() )
  { //execute the then branch
    if( OB_SUCCESS != (ret = execute_multi_inst(inst->get_then_block())) )
    {
      TBSYS_LOG(WARN, "execute then block fail");
    }
  }
  else
  { //execute the fail branch
    if( OB_SUCCESS != (ret = execute_multi_inst(inst->get_else_block())) )
    {
      TBSYS_LOG(WARN, "execute else block fail");
    }
  }
  return ret;
}

int SpUpsInstExecStrategy::execute_multi_inst(SpMultiInsts *mul_inst)
{
  int ret = OB_SUCCESS;
  int64_t pc = 0;
  for(; pc < mul_inst->inst_count() && OB_SUCCESS == ret; ++pc)
  {
    SpInst *inst = NULL;
    mul_inst->get_inst(pc, inst);
    if( inst != NULL )
    {
      ret = execute_inst(inst);
    }
    else
    {
      ret = OB_ERR_ILLEGAL_INDEX;
      TBSYS_LOG(WARN, "does not fetch inst[%ld]", pc);
    }
  }
  return ret;
}

/*============================================================================
 *                    ObUpsProcedure  Definition
 * ==========================================================================*/
ObUpsProcedure::ObUpsProcedure() :
  is_var_tab_created(false),
  block_allocator_(SMALL_BLOCK_SIZE, common::OB_MALLOC_BLOCK_SIZE),
  var_name_val_map_allocer_(SMALL_BLOCK_SIZE, ObWrapperAllocator(&block_allocator_)),
  name_pool_()
{}

ObUpsProcedure::~ObUpsProcedure()
{
//  TBSYS_LOG(INFO, "release ob_ups_procedure");
}

int ObUpsProcedure::create_variable_table()
{
  return var_name_val_map_.create(hash::cal_next_prime(16), &var_name_val_map_allocer_, &block_allocator_);
}

int ObUpsProcedure::open()
{
  int ret = OB_SUCCESS;
  SpUpsInstExecStrategy strategy;
  TBSYS_LOG(TRACE, "UpsProcedure open, inst list:\n %s", to_cstring(*this));
  pc_ = 0;
  //we need only to execute the block instructions
  SpInst *inst = inst_list_.at(0);
  ret = strategy.execute_block(static_cast<SpBlockInsts*>(inst));

  return ret;
}

int ObUpsProcedure::close()
{
  return OB_SUCCESS;
}

void ObUpsProcedure::reset()
{
  pc_ = 0;

  SpProcedure::reset();
  name_pool_.clear();
  var_name_val_map_.destroy();
}

void ObUpsProcedure::reuse()
{
  pc_ = 0;
}

int ObUpsProcedure::write_variable(const ObString &var_name, const ObObj &val)
{
  int ret = OB_SUCCESS;
  ObString tmp_var;
  ObObj tmp_val;
  if( OB_UNLIKELY(!is_var_tab_created) )
  {
    if( OB_SUCCESS != (ret = create_variable_table()) )
    {
      TBSYS_LOG(WARN, "create variable table fail, ret=%d", ret);
    }
    else
    {
      TBSYS_LOG(TRACE, "create var table successful");
      is_var_tab_created = true;
    }
  }
  if( OB_SUCCESS != ret )
  {}
  else if (var_name.length() <= 0)
  {
    ret = OB_ERROR;
    TBSYS_LOG(ERROR, "Empty variable name");
  }
  else if ((ret = name_pool_.write_string(var_name, &tmp_var)) != OB_SUCCESS
           || (ret = name_pool_.write_obj(val, &tmp_val)) != OB_SUCCESS
           || ((ret = var_name_val_map_.set(tmp_var, tmp_val, 1)) != hash::HASH_INSERT_SUCC
               && ret != hash::HASH_OVERWRITE_SUCC))
  {
    ret = OB_ERROR;
    TBSYS_LOG(ERROR, "Add variable %.*s error", var_name.length(), var_name.ptr());
  }
  else
  {
    TBSYS_LOG(TRACE, "write variable %.*s = %s", var_name.length(), var_name.ptr(), to_cstring(val));
    ret = OB_SUCCESS;
  }
  return ret;
}

int ObUpsProcedure::read_variable(const ObString &var_name, ObObj &val) const
{
  int ret = OB_SUCCESS;
  if( OB_UNLIKELY(!is_var_tab_created) )
	{
		TBSYS_LOG(WARN, "var_table does not create");
    ret = OB_ERR_VARIABLE_UNKNOWN;
	}
  else if (var_name_val_map_.get(var_name, val) != hash::HASH_EXIST)
	{
		TBSYS_LOG(WARN, "var does not exist");
    ret = OB_ERR_VARIABLE_UNKNOWN;
  }
  else
  {
    TBSYS_LOG(TRACE, "read var %.*s = %s", var_name.length(), var_name.ptr(), to_cstring(val));
  }
  return ret;
}

int ObUpsProcedure::read_variable(const ObString &var_name, const ObObj *&val) const
{
	int ret = OB_SUCCESS;
  if( OB_UNLIKELY(!is_var_tab_created) )
	{
		TBSYS_LOG(WARN, "var_table does not create");
    ret = OB_ERR_VARIABLE_UNKNOWN;
	}
  else if ((val=var_name_val_map_.get(var_name)) == NULL)
	{
		TBSYS_LOG(WARN, "var does not exist");
    ret = OB_ERR_VARIABLE_UNKNOWN;
  }
  else
  {
    TBSYS_LOG(TRACE, "read var %.*s = %s", var_name.length(), var_name.ptr(), to_cstring(*val));
  }
	return ret;
}

int64_t ObUpsProcedure::to_string(char *buf, const int64_t buf_len) const
{
  int64_t pos = 0;
  databuff_printf(buf, buf_len, pos, "Procedure instruction list:\n");
  for(int64_t i = 0; i < inst_list_.count(); ++i)
  {
    SpInst *inst = inst_list_.at(i);
    databuff_printf(buf, buf_len, pos, "inst %ld: ", i);
    pos += inst->to_string(buf + pos, buf_len -pos);
  }
  databuff_printf(buf, buf_len, pos, "Procedure variable status:\n");
  return pos;
}
