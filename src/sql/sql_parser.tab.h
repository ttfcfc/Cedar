
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     NAME = 258,
     STRING = 259,
     INTNUM = 260,
     DATE_VALUE = 261,
     HINT_VALUE = 262,
     BOOL = 263,
     APPROXNUM = 264,
     NULLX = 265,
     UNKNOWN = 266,
     QUESTIONMARK = 267,
     SYSTEM_VARIABLE = 268,
     TEMP_VARIABLE = 269,
     EXCEPT = 270,
     UNION = 271,
     INTERSECT = 272,
     OR = 273,
     AND = 274,
     NOT = 275,
     COMP_NE = 276,
     COMP_GE = 277,
     COMP_GT = 278,
     COMP_EQ = 279,
     COMP_LT = 280,
     COMP_LE = 281,
     CNNOP = 282,
     LIKE = 283,
     BETWEEN = 284,
     IN = 285,
     IS = 286,
     MOD = 287,
     UMINUS = 288,
     PROCEDURE = 289,
     DECLARE = 290,
     ELSEIF = 291,
     OUT = 292,
     INOUT = 293,
     WHILE = 294,
     LOOP = 295,
     EXIT = 296,
     CONTINUE = 297,
     DO = 298,
     CALL = 299,
     ARRAY = 300,
     REVERSE = 301,
     CURSOR = 302,
     OPEN = 303,
     FETCH = 304,
     CLOSE = 305,
     NEXT = 306,
     PRIOR = 307,
     FIRST = 308,
     LAST = 309,
     ABSOLUTE = 310,
     RELATIVE = 311,
     ADD = 312,
     ANY = 313,
     ALL = 314,
     ALTER = 315,
     AS = 316,
     ASC = 317,
     BEGI = 318,
     BIGINT = 319,
     BINARY = 320,
     BOOLEAN = 321,
     BOTH = 322,
     BY = 323,
     CASCADE = 324,
     CASE = 325,
     CHARACTER = 326,
     CLUSTER = 327,
     COMMENT = 328,
     COMMIT = 329,
     CONSISTENT = 330,
     COLUMN = 331,
     COLUMNS = 332,
     CREATE = 333,
     CREATETIME = 334,
     CURRENT_USER = 335,
     CHANGE_OBI = 336,
     SWITCH_CLUSTER = 337,
     DATE = 338,
     DATETIME = 339,
     DEALLOCATE = 340,
     DECIMAL = 341,
     DEFAULT = 342,
     DELETE = 343,
     DESC = 344,
     DESCRIBE = 345,
     DISTINCT = 346,
     DOUBLE = 347,
     DROP = 348,
     DUAL = 349,
     ELSE = 350,
     END = 351,
     END_P = 352,
     ERROR = 353,
     EXECUTE = 354,
     EXISTS = 355,
     EXPLAIN = 356,
     FLOAT = 357,
     FOR = 358,
     FROM = 359,
     FULL = 360,
     FROZEN = 361,
     FORCE = 362,
     GLOBAL = 363,
     GLOBAL_ALIAS = 364,
     GRANT = 365,
     GROUP = 366,
     HAVING = 367,
     HINT_BEGIN = 368,
     HINT_END = 369,
     HOTSPOT = 370,
     IDENTIFIED = 371,
     IF = 372,
     INNER = 373,
     INTEGER = 374,
     INSERT = 375,
     INTO = 376,
     JOIN = 377,
     SEMI_JOIN = 378,
     KEY = 379,
     LEADING = 380,
     LEFT = 381,
     LIMIT = 382,
     LOCAL = 383,
     LOCKED = 384,
     LOCKWJH = 385,
     MEDIUMINT = 386,
     MEMORY = 387,
     MODIFYTIME = 388,
     MASTER = 389,
     NUMERIC = 390,
     OFFSET = 391,
     ON = 392,
     ORDER = 393,
     OPTION = 394,
     OUTER = 395,
     PARAMETERS = 396,
     PASSWORD = 397,
     PRECISION = 398,
     PREPARE = 399,
     PRIMARY = 400,
     READ_STATIC = 401,
     REAL = 402,
     RENAME = 403,
     REPLACE = 404,
     RESTRICT = 405,
     PRIVILEGES = 406,
     REVOKE = 407,
     RIGHT = 408,
     ROLLBACK = 409,
     KILL = 410,
     READ_CONSISTENCY = 411,
     NO_GROUP = 412,
     SCHEMA = 413,
     SCOPE = 414,
     SELECT = 415,
     SESSION = 416,
     SESSION_ALIAS = 417,
     SET = 418,
     SHOW = 419,
     SMALLINT = 420,
     SNAPSHOT = 421,
     SPFILE = 422,
     START = 423,
     STATIC = 424,
     SYSTEM = 425,
     STRONG = 426,
     SET_MASTER_CLUSTER = 427,
     SET_SLAVE_CLUSTER = 428,
     SLAVE = 429,
     TABLE = 430,
     TABLES = 431,
     THEN = 432,
     TIME = 433,
     TIMESTAMP = 434,
     TINYINT = 435,
     TRAILING = 436,
     TRANSACTION = 437,
     TO = 438,
     UPDATE = 439,
     USER = 440,
     USING = 441,
     VALUES = 442,
     VARCHAR = 443,
     VARBINARY = 444,
     WHERE = 445,
     WHEN = 446,
     WITH = 447,
     WORK = 448,
     PROCESSLIST = 449,
     QUERY = 450,
     CONNECTION = 451,
     WEAK = 452,
     INDEX = 453,
     STORING = 454,
     BLOOMFILTER_JOIN = 455,
     MERGE_JOIN = 456,
     AUTO_INCREMENT = 457,
     CHUNKSERVER = 458,
     COMPRESS_METHOD = 459,
     CONSISTENT_MODE = 460,
     EXPIRE_INFO = 461,
     GRANTS = 462,
     JOIN_INFO = 463,
     MERGESERVER = 464,
     REPLICA_NUM = 465,
     ROOTSERVER = 466,
     ROW_COUNT = 467,
     SERVER = 468,
     SERVER_IP = 469,
     SERVER_PORT = 470,
     SERVER_TYPE = 471,
     STATUS = 472,
     TABLE_ID = 473,
     TABLET_BLOCK_SIZE = 474,
     TABLET_MAX_SIZE = 475,
     UNLOCKED = 476,
     UPDATESERVER = 477,
     USE_BLOOM_FILTER = 478,
     VARIABLES = 479,
     VERBOSE = 480,
     WARNINGS = 481
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{


  struct _ParseNode *node;
  const struct _NonReservedKeyword *non_reserved_keyword;
  int    ival;



} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif



#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


