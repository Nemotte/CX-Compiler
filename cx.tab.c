/* A Bison parser, made by GNU Bison 2.7.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2012 Free Software Foundation, Inc.
   
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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.7"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
/* Line 371 of yacc.c  */
#line 1 "src/cx.y"

    #include <stdio.h>
    #include <stdlib.h>
    #include <malloc.h>
    #include <memory.h>
    #include <string.h>
    #include <stdbool.h>

    #define txmax 100       // 符号表容量
    #define al 10           // 标识符最大长度
    #define amax 2048       // 地址上界
    #define levmax 3        // 最大允许过程嵌套声明层数
    #define cxmax 200       // 最多的虚拟机代码数
    #define stacksize 500   // 运行时数据栈元素最多为500个

    // 符号表中的类型
    enum object{
        constant,
        variable,
        procedure,
    };

    // 变量类型
    enum vartype {
        inttype,
        booltype,
        chartype
    };

    // 符号表结构
    struct tablestruct{
        char name[al];      // 名字
        enum object kind;   // 类型
        enum vartype type;  // 变量类型
        int val;            // 数值
        int level;          // 所处层
        int adr;            // 地址
        int size;           // 需要分配的数据空间
    };
    struct tablestruct table[txmax];

    // 虚拟机代码指令
    enum fct{
        lit, opr, lod, sto, cal, pint, jmp, jpc, jpe, ext, blo, fre,
    };

    // 虚拟机代码结构
    struct instruction{
        enum fct f;         // 虚拟机代码指令
        int l;              // 引用层与声明层的层次差
        int a;              // 根据f的不同而不同
    };
    struct instruction code[cxmax];

    int tx;
    int cx;
    int px;
    int lev;
    int proctable[3];
    char id[al];
    int leveltable[5];
    int num;
    bool listswitch;
    bool tableswitch;
    bool stackswitch;
    bool interpretswitch;
    int p;
    int b;
    int t;

    FILE* fin;
    FILE* ftable;
    FILE* fcode;
    FILE* foutput;
    FILE* fresult;
    FILE* fstack;
    char fname[al];
    int err;
    int switchaddr;
    extern int line;

    char varType[10];

    void init();
    void enter(enum vartype t, enum object k);
    int position(char* s);
    void setdx(int n);
    void gen(enum fct x, int y, int z);
    void listall();
    void displaytable();
    void interpret();
    int base(int l, int *s, int b);
    
    int yylex();
    int yyerror(const char *s);
    void redirectInput(FILE *fin);

    int hasProc;

    #define YYERROR_VERBOSE 1

/* Line 371 of yacc.c  */
#line 170 "cx.tab.c"

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "cx.tab.h".  */
#ifndef YY_YY_CX_TAB_H_INCLUDED
# define YY_YY_CX_TAB_H_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     INT = 258,
     BOOL = 259,
     IF = 260,
     ELSE = 261,
     WHILE = 262,
     WRITE = 263,
     READ = 264,
     CALL = 265,
     PROC = 266,
     PLUS = 267,
     MINUS = 268,
     TIMES = 269,
     SLASH = 270,
     LES = 271,
     LEQ = 272,
     GTR = 273,
     GEQ = 274,
     EQL = 275,
     NEQ = 276,
     BECOMES = 277,
     COMMA = 278,
     OR = 279,
     AND = 280,
     NOT = 281,
     SEMICOLON = 282,
     LPAREN = 283,
     RPAREN = 284,
     LBRACE = 285,
     RBRACE = 286,
     SYM_TRUE = 287,
     SYM_FALSE = 288,
     REPEAT = 289,
     UNTIL = 290,
     XOR = 291,
     CASE = 292,
     SWITCH = 293,
     DEFAULT = 294,
     BREAK = 295,
     COLON = 296,
     CONST = 297,
     EXIT = 298,
     CONTINUE = 299,
     FOR = 300,
     DO = 301,
     MOD = 302,
     ODD = 303,
     SELFADD = 304,
     SELFMINUS = 305,
     IDENT = 306,
     NUMBER = 307,
     CHARACTER = 308,
     IFX = 309
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 387 of yacc.c  */
#line 104 "src/cx.y"

    char *ident;
    int number;


/* Line 387 of yacc.c  */
#line 273 "cx.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !YY_YY_CX_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

/* Line 390 of yacc.c  */
#line 301 "cx.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(N) (N)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   477

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  55
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  63
/* YYNRULES -- Number of rules.  */
#define YYNRULES  119
/* YYNRULES -- Number of states.  */
#define YYNSTATES  245

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   309

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     6,     7,    15,    18,    19,    23,
      26,    33,    40,    43,    45,    47,    49,    53,    54,    58,
      60,    63,    64,    67,    68,    77,    78,    79,    80,    81,
      93,    96,    97,   102,   107,   108,   113,   114,   119,   120,
     129,   130,   139,   149,   150,   162,   164,   165,   166,   167,
     183,   187,   190,   192,   194,   195,   199,   203,   204,   205,
     206,   207,   218,   219,   224,   229,   230,   232,   233,   235,
     236,   237,   242,   243,   254,   255,   258,   259,   266,   271,
     275,   277,   281,   283,   285,   287,   290,   294,   299,   301,
     305,   309,   313,   317,   321,   325,   327,   329,   331,   333,
     336,   339,   341,   345,   349,   351,   355,   359,   363,   365,
     369,   371,   375,   377,   380,   383,   385,   386,   387,   388
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      56,     0,    -1,    57,    -1,    -1,    -1,    30,    58,    60,
      59,    66,    74,    31,    -1,    60,    61,    -1,    -1,    62,
      63,    27,    -1,    62,    63,    -1,    42,    62,    51,    22,
      52,    27,    -1,    42,    62,    51,    22,   107,    27,    -1,
       1,    27,    -1,     3,    -1,     4,    -1,    65,    -1,    63,
      23,    65,    -1,    -1,     1,    64,    27,    -1,    51,    -1,
       1,    27,    -1,    -1,    66,    67,    -1,    -1,    11,    51,
      28,    29,   114,    68,    69,   114,    -1,    -1,    -1,    -1,
      -1,    30,   116,    70,   115,    60,    71,    74,    72,    31,
      73,   117,    -1,    74,    75,    -1,    -1,   113,    22,   108,
      27,    -1,   113,    22,   107,    27,    -1,    -1,     9,   113,
      76,    27,    -1,    -1,     8,   108,    77,    27,    -1,    -1,
       5,    28,   102,    29,   114,    78,    75,    94,    -1,    -1,
       7,   114,    28,   102,    29,   114,    79,    75,    -1,    34,
     114,    75,    35,    28,   102,    29,   114,    27,    -1,    -1,
      46,   114,    75,   114,     7,    28,   102,   114,    80,    29,
      27,    -1,    96,    -1,    -1,    -1,    -1,    45,    28,    91,
     114,    93,    81,    27,   114,    82,   114,    92,    29,    83,
     114,    75,    -1,    43,    52,    27,    -1,   112,    27,    -1,
      86,    -1,    85,    -1,    -1,     1,    84,    27,    -1,    10,
     113,    27,    -1,    -1,    -1,    -1,    -1,    30,   116,    87,
      60,    88,    74,    89,    31,    90,   117,    -1,    -1,   113,
      22,   108,    27,    -1,   113,    22,   102,    27,    -1,    -1,
     108,    -1,    -1,   102,    -1,    -1,    -1,     6,   114,    95,
      75,    -1,    -1,    38,   114,    97,    28,   108,    29,    30,
      98,   101,    31,    -1,    -1,    98,    99,    -1,    -1,    37,
     108,   114,   100,    41,    75,    -1,    39,    41,   114,    75,
      -1,   102,    24,   103,    -1,   103,    -1,   103,    25,   104,
      -1,   104,    -1,   113,    -1,   107,    -1,    26,   104,    -1,
      28,   102,    29,    -1,    48,    28,   106,    29,    -1,   105,
      -1,   106,    20,   108,    -1,   106,    21,   108,    -1,   106,
      16,   108,    -1,   106,    17,   108,    -1,   106,    18,   108,
      -1,   106,    19,   108,    -1,   113,    -1,    52,    -1,    32,
      -1,    33,    -1,    12,   109,    -1,    13,   109,    -1,   109,
      -1,   108,    12,   109,    -1,   108,    13,   109,    -1,   110,
      -1,   109,    14,   110,    -1,   109,    15,   110,    -1,   109,
      47,   110,    -1,   111,    -1,   110,    36,   111,    -1,   106,
      -1,    28,   108,    29,    -1,   112,    -1,   113,    49,    -1,
     113,    50,    -1,    51,    -1,    -1,    -1,    -1,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   130,   130,   134,   138,   134,   151,   156,   162,   166,
     171,   194,   217,   221,   225,   232,   236,   240,   240,   244,
     255,   259,   261,   266,   265,   280,   285,   294,   298,   278,
     306,   307,   311,   327,   344,   343,   353,   353,   357,   357,
     362,   362,   368,   371,   371,   374,   375,   378,   381,   375,
     388,   391,   392,   393,   394,   394,   398,   412,   417,   422,
     426,   410,   432,   434,   449,   466,   468,   472,   476,   482,
     486,   486,   496,   496,   504,   506,   510,   510,   522,   531,
     534,   538,   541,   545,   554,   555,   558,   559,   562,   566,
     569,   572,   575,   578,   581,   587,   606,   614,   619,   628,
     631,   635,   638,   642,   650,   653,   657,   661,   669,   672,
     679,   682,   685,   691,   706,   724,   731,   737,   743,   751
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INT", "BOOL", "IF", "ELSE", "WHILE",
  "WRITE", "READ", "CALL", "PROC", "PLUS", "MINUS", "TIMES", "SLASH",
  "LES", "LEQ", "GTR", "GEQ", "EQL", "NEQ", "BECOMES", "COMMA", "OR",
  "AND", "NOT", "SEMICOLON", "LPAREN", "RPAREN", "LBRACE", "RBRACE",
  "SYM_TRUE", "SYM_FALSE", "REPEAT", "UNTIL", "XOR", "CASE", "SWITCH",
  "DEFAULT", "BREAK", "COLON", "CONST", "EXIT", "CONTINUE", "FOR", "DO",
  "MOD", "ODD", "SELFADD", "SELFMINUS", "IDENT", "NUMBER", "CHARACTER",
  "IFX", "$accept", "program", "block", "@1", "$@2", "decls", "decl",
  "type", "varlist", "$@3", "vardef", "procdecls", "procdecl", "$@4",
  "procbody", "$@5", "$@6", "$@7", "$@8", "stmts", "stm", "$@9", "$@10",
  "$@11", "$@12", "$@13", "$@14", "$@15", "$@16", "$@17", "callstm",
  "blockstm", "$@18", "$@19", "$@20", "$@21", "fordecl", "forstm",
  "forbexpr", "elsestm", "$@22", "switchstm", "$@23", "casestms",
  "casestm", "$@24", "defaultstm", "bexpr", "bterm", "bfactor", "rel",
  "idornum", "trueorfalse", "aexpr", "aterm", "afactor", "abasic",
  "aselfaddorminus", "ident", "get_cx", "get_table_addr", "inc_level",
  "dec_level", YY_NULL
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    55,    56,    58,    59,    57,    60,    60,    61,    61,
      61,    61,    61,    62,    62,    63,    63,    64,    63,    65,
      65,    66,    66,    68,    67,    70,    71,    72,    73,    69,
      74,    74,    75,    75,    76,    75,    77,    75,    78,    75,
      79,    75,    75,    80,    75,    75,    81,    82,    83,    75,
      75,    75,    75,    75,    84,    75,    85,    87,    88,    89,
      90,    86,    91,    91,    91,    92,    92,    93,    93,    94,
      95,    94,    97,    96,    98,    98,   100,    99,   101,   102,
     102,   103,   103,   104,   104,   104,   104,   104,   104,   105,
     105,   105,   105,   105,   105,   106,   106,   107,   107,   108,
     108,   108,   108,   108,   109,   109,   109,   109,   110,   110,
     111,   111,   111,   112,   112,   113,   114,   115,   116,   117
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     0,     7,     2,     0,     3,     2,
       6,     6,     2,     1,     1,     1,     3,     0,     3,     1,
       2,     0,     2,     0,     8,     0,     0,     0,     0,    11,
       2,     0,     4,     4,     0,     4,     0,     4,     0,     8,
       0,     8,     9,     0,    11,     1,     0,     0,     0,    15,
       3,     2,     1,     1,     0,     3,     3,     0,     0,     0,
       0,    10,     0,     4,     4,     0,     1,     0,     1,     0,
       0,     4,     0,    10,     0,     2,     0,     6,     4,     3,
       1,     3,     1,     1,     1,     2,     3,     4,     1,     3,
       3,     3,     3,     3,     3,     1,     1,     1,     1,     2,
       2,     1,     3,     3,     1,     3,     3,     3,     1,     3,
       1,     3,     1,     2,     2,     1,     0,     0,     0,     0
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     3,     0,     2,     7,     1,     0,     0,    13,    14,
       0,    21,     6,     0,    12,     0,    31,     0,    19,     9,
      15,     0,     0,    22,     0,    20,     0,     0,     8,     0,
       0,    54,     0,   116,     0,     0,     0,   118,     5,   116,
     116,     0,     0,   116,   115,    30,    53,    52,    45,     0,
       0,    18,     0,    16,    97,    98,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    96,   110,    36,   101,   104,
     108,   112,    95,    34,     0,    57,     0,    72,     0,    62,
       0,    51,     0,   113,   114,    10,    11,   116,    55,     0,
       0,     0,     0,    80,    82,    88,     0,    84,    95,     0,
      99,   100,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    56,     7,     0,     0,    50,   116,     0,   116,     0,
       0,    23,    85,     0,     0,     0,   116,     0,     0,     0,
       0,     0,     0,     0,     0,   111,   102,   103,    37,   105,
     106,   107,   109,    35,     0,     0,     0,    67,     0,     0,
      33,    32,     0,    86,     0,    95,    79,    38,    81,    91,
      92,    93,    94,    89,    90,   116,    31,     0,     0,    46,
      68,     0,     0,   110,     0,    95,     0,   118,   116,    87,
       0,    40,     0,     0,     0,     0,    64,    63,     0,    25,
      24,    69,     0,     0,   116,    74,   116,   116,   117,   116,
      39,    41,    60,     0,     0,    47,    43,     7,    70,   119,
      42,     0,     0,    75,     0,   116,     0,     0,     0,    61,
     116,   116,    73,    65,     0,    31,    71,    76,     0,     0,
      66,    44,     0,     0,    78,    48,     0,     0,   116,    28,
      77,     0,   119,    49,    29
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     4,    11,     6,    12,    13,    19,    26,
      20,    16,    23,   152,   178,   198,   225,   236,   242,    24,
      45,   110,   105,   180,   192,   216,   185,   215,   238,    59,
      46,    47,   112,   166,   193,   209,   116,   229,   169,   200,
     218,    48,   114,   204,   213,   233,   214,   123,    93,    94,
      95,    66,    97,   102,    68,    69,    70,    71,    72,    61,
     207,    75,   219
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -163
static const yytype_int16 yypact[] =
{
       5,  -163,    44,  -163,  -163,  -163,   225,    52,  -163,  -163,
      88,  -163,  -163,     7,  -163,    31,    91,    72,  -163,     4,
    -163,    83,    79,  -163,   331,  -163,    92,    18,  -163,   -11,
     117,  -163,   120,  -163,    34,    98,    98,  -163,  -163,  -163,
    -163,    99,   122,  -163,  -163,  -163,  -163,  -163,  -163,   126,
     -17,  -163,    72,  -163,  -163,  -163,   128,   136,   137,   138,
     159,   139,    26,    26,    34,  -163,  -163,   109,     2,   134,
    -163,  -163,    86,  -163,   145,  -163,   398,  -163,   146,    98,
     398,  -163,   425,  -163,  -163,  -163,  -163,  -163,  -163,   159,
     159,   149,    -9,   153,  -163,  -163,   221,  -163,   104,   159,
       2,     2,    75,    26,    26,   152,    26,    26,    26,    26,
     155,  -163,  -163,   151,   156,  -163,  -163,   161,  -163,   162,
      68,  -163,  -163,    -6,    90,   159,  -163,   159,    34,    34,
      34,    34,    34,    34,     0,  -163,     2,     2,  -163,   134,
     134,   134,  -163,  -163,   274,   160,    34,   159,   148,   190,
    -163,  -163,   168,  -163,   172,  -163,   153,  -163,  -163,   109,
     109,   109,   109,   109,   109,  -163,  -163,   159,    77,  -163,
     179,   148,    10,   221,   105,     1,   184,  -163,  -163,  -163,
     398,  -163,   341,    35,   185,   189,  -163,  -163,   159,  -163,
    -163,   213,   398,   192,  -163,  -163,  -163,   179,  -163,  -163,
    -163,  -163,  -163,   193,    33,  -163,  -163,  -163,  -163,  -163,
    -163,    34,   180,  -163,   200,  -163,   215,   284,   398,  -163,
     109,  -163,  -163,    34,   218,  -163,  -163,  -163,   398,   217,
     109,  -163,   388,   206,  -163,  -163,   219,   398,  -163,  -163,
    -163,   398,  -163,  -163,  -163
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -163,  -163,  -163,  -163,  -163,  -109,  -163,   241,  -163,  -163,
     226,  -163,  -163,  -163,  -163,  -163,  -163,  -163,  -163,  -162,
     -66,  -163,  -163,  -163,  -163,  -163,  -163,  -163,  -163,  -163,
    -163,  -163,  -163,  -163,  -163,  -163,  -163,  -163,  -163,  -163,
    -163,  -163,  -163,  -163,  -163,  -163,  -163,   -54,   127,   -87,
    -163,   -51,   -22,   -21,   -20,    32,   163,   -23,   -24,    28,
    -163,    80,    12
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -84
static const yytype_int16 yytable[] =
{
      50,    49,   122,   144,   182,    82,    92,    57,    17,    96,
     113,    73,    74,    67,   118,   125,   106,   107,   125,    52,
     126,    54,    55,   153,   125,   -83,   -83,    27,   -83,   165,
     -83,    28,    83,    84,   125,     1,    98,   186,    96,    96,
     158,    56,   100,   101,     5,   134,    62,    63,    96,   108,
      83,    84,    50,    49,    64,   117,    50,    49,    18,   125,
     119,   120,    64,   232,   194,    98,    98,    76,    77,    18,
     211,    80,   212,   154,    96,    98,    96,    44,    65,    14,
     103,   104,    21,   136,   137,    44,    65,   103,   104,   103,
     104,     8,     9,   170,   172,   151,    96,   173,   217,    25,
     155,    98,    22,    98,   135,    29,   184,   159,   160,   161,
     162,   163,   164,   183,   191,   121,    96,   103,   104,    51,
     173,   103,   104,    98,   175,   168,   201,   174,   -83,   -83,
      30,   -83,   187,   -83,   197,    83,    84,    96,   139,   140,
     141,    44,    65,    98,   147,    58,   149,   175,    60,    44,
      79,    78,   226,    81,   157,    85,    50,    49,    50,    49,
      62,    63,   234,    86,    98,    88,    87,    99,    50,    49,
     109,   240,   111,   115,    89,   243,   171,   124,   127,   138,
      54,    55,   143,   148,   146,    89,   145,    90,   167,   150,
     220,    54,    55,   181,    50,    49,    91,   176,   177,    44,
      65,   179,   230,   125,    50,    49,   190,    91,    50,    49,
      44,    65,   188,    50,    49,   195,   196,    50,    49,   199,
     210,   221,   203,   202,   205,   206,     7,   208,     8,     9,
      -4,   222,    -4,    -4,    -4,    -4,    -4,   128,   129,   130,
     131,   132,   133,   223,   224,   231,   235,   237,   227,   228,
     239,    15,   156,    53,   244,    -4,    -4,   189,     0,    -4,
       0,     0,     0,    -4,     0,     0,   241,    10,    -4,     0,
      -4,    -4,   142,     0,     0,     7,    -4,     8,     9,   -58,
       0,   -58,   -58,   -58,   -58,     7,     0,     8,     9,   -26,
       0,   -26,   -26,   -26,   -26,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -58,   -58,     0,     0,   -58,     0,
       0,     0,   -58,     0,   -26,   -26,    10,   -58,   -26,   -58,
     -58,     0,   -26,     0,     0,   -58,    10,   -26,     0,   -26,
     -26,     0,    31,     0,     0,   -26,    32,     0,    33,    34,
      35,    36,    31,     0,     0,     0,    32,     0,    33,    34,
      35,    36,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    37,    38,     0,     0,    39,     0,     0,     0,    40,
       0,    37,   -59,     0,    41,    39,    42,    43,     0,    40,
       0,     0,    44,     0,    41,     0,    42,    43,     0,    31,
       0,     0,    44,    32,     0,    33,    34,    35,    36,    31,
       0,     0,     0,    32,     0,    33,    34,    35,    36,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    37,   -27,
       0,     0,    39,     0,     0,     0,    40,     0,    37,     0,
       0,    41,    39,    42,    43,     0,    40,    62,    63,    44,
       0,    41,     0,    42,    43,     0,     0,     0,     0,    44,
       0,     0,     0,    64,     0,     0,     0,    54,    55,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    44,    65
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-163)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
      24,    24,    89,   112,   166,    22,    60,    29,     1,    60,
      76,    35,    36,    34,    80,    24,    14,    15,    24,     1,
      29,    32,    33,    29,    24,    24,    25,    23,    27,    29,
      29,    27,    49,    50,    24,    30,    60,    27,    89,    90,
     127,    52,    62,    63,     0,    99,    12,    13,    99,    47,
      49,    50,    76,    76,    28,    79,    80,    80,    51,    24,
      82,    82,    28,   225,    29,    89,    90,    39,    40,    51,
      37,    43,    39,   124,   125,    99,   127,    51,    52,    27,
      12,    13,    51,   103,   104,    51,    52,    12,    13,    12,
      13,     3,     4,   147,   148,    27,   147,   148,   207,    27,
     124,   125,    11,   127,    29,    22,    29,   128,   129,   130,
     131,   132,   133,   167,   180,    87,   167,    12,    13,    27,
     171,    12,    13,   147,   148,   146,   192,   148,    24,    25,
      51,    27,    27,    29,   188,    49,    50,   188,   106,   107,
     108,    51,    52,   167,   116,    28,   118,   171,    28,    51,
      28,    52,   218,    27,   126,    27,   180,   180,   182,   182,
      12,    13,   228,    27,   188,    27,    29,    28,   192,   192,
      36,   237,    27,    27,    26,   241,    28,    28,    25,    27,
      32,    33,    27,    22,    28,    26,    35,    28,    28,    27,
     211,    32,    33,   165,   218,   218,    48,     7,    30,    51,
      52,    29,   223,    24,   228,   228,   178,    48,   232,   232,
      51,    52,    28,   237,   237,    30,    27,   241,   241,     6,
      27,    41,   194,    31,   196,   197,     1,   199,     3,     4,
       5,    31,     7,     8,     9,    10,    11,    16,    17,    18,
      19,    20,    21,   215,    29,    27,    29,    41,   220,   221,
      31,    10,   125,    27,   242,    30,    31,   177,    -1,    34,
      -1,    -1,    -1,    38,    -1,    -1,   238,    42,    43,    -1,
      45,    46,   109,    -1,    -1,     1,    51,     3,     4,     5,
      -1,     7,     8,     9,    10,     1,    -1,     3,     4,     5,
      -1,     7,     8,     9,    10,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    30,    31,    -1,    -1,    34,    -1,
      -1,    -1,    38,    -1,    30,    31,    42,    43,    34,    45,
      46,    -1,    38,    -1,    -1,    51,    42,    43,    -1,    45,
      46,    -1,     1,    -1,    -1,    51,     5,    -1,     7,     8,
       9,    10,     1,    -1,    -1,    -1,     5,    -1,     7,     8,
       9,    10,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    30,    31,    -1,    -1,    34,    -1,    -1,    -1,    38,
      -1,    30,    31,    -1,    43,    34,    45,    46,    -1,    38,
      -1,    -1,    51,    -1,    43,    -1,    45,    46,    -1,     1,
      -1,    -1,    51,     5,    -1,     7,     8,     9,    10,     1,
      -1,    -1,    -1,     5,    -1,     7,     8,     9,    10,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    30,    31,
      -1,    -1,    34,    -1,    -1,    -1,    38,    -1,    30,    -1,
      -1,    43,    34,    45,    46,    -1,    38,    12,    13,    51,
      -1,    43,    -1,    45,    46,    -1,    -1,    -1,    -1,    51,
      -1,    -1,    -1,    28,    -1,    -1,    -1,    32,    33,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    51,    52
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    30,    56,    57,    58,     0,    60,     1,     3,     4,
      42,    59,    61,    62,    27,    62,    66,     1,    51,    63,
      65,    51,    11,    67,    74,    27,    64,    23,    27,    22,
      51,     1,     5,     7,     8,     9,    10,    30,    31,    34,
      38,    43,    45,    46,    51,    75,    85,    86,    96,   112,
     113,    27,     1,    65,    32,    33,    52,   107,    28,    84,
      28,   114,    12,    13,    28,    52,   106,   108,   109,   110,
     111,   112,   113,   113,   113,   116,   114,   114,    52,    28,
     114,    27,    22,    49,    50,    27,    27,    29,    27,    26,
      28,    48,   102,   103,   104,   105,   106,   107,   113,    28,
     109,   109,   108,    12,    13,    77,    14,    15,    47,    36,
      76,    27,    87,    75,    97,    27,    91,   113,    75,   107,
     108,   114,   104,   102,    28,    24,    29,    25,    16,    17,
      18,    19,    20,    21,   102,    29,   109,   109,    27,   110,
     110,   110,   111,    27,    60,    35,    28,   114,    22,   114,
      27,    27,    68,    29,   106,   113,   103,   114,   104,   108,
     108,   108,   108,   108,   108,    29,    88,    28,   108,    93,
     102,    28,   102,   106,   108,   113,     7,    30,    69,    29,
      78,   114,    74,   102,    29,    81,    27,    27,    28,   116,
     114,    75,    79,    89,    29,    30,    27,   102,    70,     6,
      94,    75,    31,   114,    98,   114,   114,   115,   114,    90,
      27,    37,    39,    99,   101,    82,    80,    60,    95,   117,
     108,    41,    31,   114,    29,    71,    75,   114,   114,    92,
     108,    27,    74,   100,    75,    29,    72,    41,    83,    31,
      75,   114,    73,    75,   117
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))

/* Error token number */
#define YYTERROR	1
#define YYERRCODE	256


/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */
#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
        break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
        break;
    }
}




/* The lookahead symbol.  */
int yychar;


#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval YY_INITIAL_VALUE(yyval_default);

/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 3:
/* Line 1792 of yacc.c  */
#line 134 "src/cx.y"
    {
        (yyval.number) = cx;
        gen(jmp, 0, 1);
    }
    break;

  case 4:
/* Line 1792 of yacc.c  */
#line 138 "src/cx.y"
    {
        setdx((yyvsp[(3) - (3)].number));
        code[(yyvsp[(2) - (3)].number)].a = cx;
        gen(pint, 0, (yyvsp[(3) - (3)].number) + 3);
    }
    break;

  case 5:
/* Line 1792 of yacc.c  */
#line 145 "src/cx.y"
    {
        gen(opr, 0, 0);
    }
    break;

  case 6:
/* Line 1792 of yacc.c  */
#line 152 "src/cx.y"
    {
        (yyval.number) = (yyvsp[(1) - (2)].number) + (yyvsp[(2) - (2)].number);
    }
    break;

  case 7:
/* Line 1792 of yacc.c  */
#line 156 "src/cx.y"
    {
        (yyval.number) = 0;
    }
    break;

  case 8:
/* Line 1792 of yacc.c  */
#line 163 "src/cx.y"
    {
        (yyval.number) = (yyvsp[(2) - (3)].number);
    }
    break;

  case 9:
/* Line 1792 of yacc.c  */
#line 167 "src/cx.y"
    {
        (yyval.number) = (yyvsp[(2) - (2)].number);         
        yyerror("Miss SEMICOLON");  //错误处理，变量声明缺少结尾分号
    }
    break;

  case 10:
/* Line 1792 of yacc.c  */
#line 171 "src/cx.y"
    {
        strcpy(id, (yyvsp[(3) - (6)].ident));
        if (!strcmp(varType, "int")) 
            enter(inttype, constant); 
        else if(!strcmp(varType, "bool"))
            enter(booltype, constant);
        else if(!strcmp(varType, "char"))
            enter(chartype, constant);

        int tmp = position((yyvsp[(3) - (6)].ident));
        
        if (table[tmp].type == inttype)
            table[tmp].val = (yyvsp[(5) - (6)].number);
        else{
            char *str1 = "Symbol \"";
            char *str2 = "\" type should be int";
            char *str = (char *) malloc(strlen(str1) + strlen(str2) + strlen(table[tmp].name));
            strcpy(str, str1); 
            strcat(str, table[tmp].name);
            strcat(str, str2);
            yyerror(str);
        }
    }
    break;

  case 11:
/* Line 1792 of yacc.c  */
#line 194 "src/cx.y"
    {
        strcpy(id, (yyvsp[(3) - (6)].ident));
        if (!strcmp(varType, "int")) 
            enter(inttype, constant); 
        else if(!strcmp(varType, "bool"))
            enter(booltype, constant);
        else if(!strcmp(varType, "char"))
            enter(chartype, constant);
        
        int tmp = position((yyvsp[(3) - (6)].ident));

        if (table[tmp].type == booltype)
            table[tmp].val = (yyvsp[(5) - (6)].number);
        else{
            char *str1 = "Symbol \"";
            char *str2 = "\" type should be bool";
            char *str = (char *) malloc(strlen(str1) + strlen(str2) + strlen(table[tmp].name));
            strcpy(str, str1); 
            strcat(str, table[tmp].name);
            strcat(str, str2);
            yyerror(str);
        }
    }
    break;

  case 13:
/* Line 1792 of yacc.c  */
#line 222 "src/cx.y"
    {
        strcpy(varType, "int");
    }
    break;

  case 14:
/* Line 1792 of yacc.c  */
#line 226 "src/cx.y"
    {
        strcpy(varType, "bool");
    }
    break;

  case 15:
/* Line 1792 of yacc.c  */
#line 233 "src/cx.y"
    {
        (yyval.number) = (yyvsp[(1) - (1)].number);
    }
    break;

  case 16:
/* Line 1792 of yacc.c  */
#line 237 "src/cx.y"
    {
        (yyval.number) = (yyvsp[(1) - (3)].number) + (yyvsp[(3) - (3)].number);
    }
    break;

  case 17:
/* Line 1792 of yacc.c  */
#line 240 "src/cx.y"
    {/*错误处理*/}
    break;

  case 19:
/* Line 1792 of yacc.c  */
#line 245 "src/cx.y"
    {
        strcpy(id, (yyvsp[(1) - (1)].ident));
        if (!strcmp(varType, "int")) 
            enter(inttype, variable); 
        else if(!strcmp(varType, "bool"))
            enter(booltype, variable);
        else if(!strcmp(varType, "char"))
            enter(chartype, variable);
        (yyval.number) = 1;
    }
    break;

  case 23:
/* Line 1792 of yacc.c  */
#line 266 "src/cx.y"
    {
        hasProc = 1;
        gen(jmp, 0, 0);
        strcpy(id, (yyvsp[(2) - (5)].ident));
        enter(-1, procedure);
    }
    break;

  case 24:
/* Line 1792 of yacc.c  */
#line 272 "src/cx.y"
    {
        code[(yyvsp[(5) - (8)].number)].a = (yyvsp[(8) - (8)].number);
    }
    break;

  case 25:
/* Line 1792 of yacc.c  */
#line 280 "src/cx.y"
    {
        leveltable[lev] = tx;
    }
    break;

  case 26:
/* Line 1792 of yacc.c  */
#line 285 "src/cx.y"
    {
        setdx((yyvsp[(5) - (5)].number));
        table[(yyvsp[(4) - (5)].number)].adr = cx;
        table[(yyvsp[(4) - (5)].number)].size = (yyvsp[(5) - (5)].number) + 3;
        gen(pint, 0, (yyvsp[(5) - (5)].number) + 3);
        if(hasProc)
            displaytable();
    }
    break;

  case 27:
/* Line 1792 of yacc.c  */
#line 294 "src/cx.y"
    {
        gen(opr, 0, 0);
    }
    break;

  case 28:
/* Line 1792 of yacc.c  */
#line 298 "src/cx.y"
    {
        tx = leveltable[lev];
    }
    break;

  case 32:
/* Line 1792 of yacc.c  */
#line 312 "src/cx.y"
    {
        if ((yyvsp[(1) - (4)].number) == 0)
            yyerror("Symbol does not exist");
        else if (table[(yyvsp[(1) - (4)].number)].kind == variable && table[(yyvsp[(1) - (4)].number)].type == inttype)
            gen(sto, lev - table[(yyvsp[(1) - (4)].number)].level, table[(yyvsp[(1) - (4)].number)].adr);
        else{
            char *str1 = "Symbol \"";
            char *str2 = "\" should be a variable and type should be int";
            char *str = (char *) malloc(strlen(str1) + strlen(str2) + strlen(table[(yyvsp[(1) - (4)].number)].name));
            strcpy(str, str1); 
            strcat(str, table[(yyvsp[(1) - (4)].number)].name);
            strcat(str, str2);
            yyerror(str);
        }
    }
    break;

  case 33:
/* Line 1792 of yacc.c  */
#line 328 "src/cx.y"
    {
        if ((yyvsp[(1) - (4)].number) == 0)
            yyerror("Symbol does not exist");
        else if (table[(yyvsp[(1) - (4)].number)].kind == variable && table[(yyvsp[(1) - (4)].number)].type == booltype) 
            gen(sto, lev - table[(yyvsp[(1) - (4)].number)].level, table[(yyvsp[(1) - (4)].number)].adr);
        else{
            char *str1 = "Symbol \"";
            char *str2 = "\" should be a variable and type should be bool";
            char *str = (char *) malloc(strlen(str1) + strlen(str2) + strlen(table[(yyvsp[(1) - (4)].number)].name));
            strcpy(str, str1); 
            strcat(str, table[(yyvsp[(1) - (4)].number)].name);
            strcat(str, str2);
            yyerror(str);
        }
    }
    break;

  case 34:
/* Line 1792 of yacc.c  */
#line 344 "src/cx.y"
    {
        if (table[(yyvsp[(2) - (2)].number)].kind == variable && table[(yyvsp[(2) - (2)].number)].type == inttype) {
            gen(opr, 0, 16);
            gen(sto, lev - table[(yyvsp[(2) - (2)].number)].level, table[(yyvsp[(2) - (2)].number)].adr);
        }
        else {
            yyerror("Can only read int variable");
        }
    }
    break;

  case 36:
/* Line 1792 of yacc.c  */
#line 353 "src/cx.y"
    {
        gen(opr, 0, 14);
        gen(opr, 0, 15);
    }
    break;

  case 38:
/* Line 1792 of yacc.c  */
#line 357 "src/cx.y"
    {
        gen(jpc, 0, 0);
    }
    break;

  case 39:
/* Line 1792 of yacc.c  */
#line 359 "src/cx.y"
    {
        code[(yyvsp[(5) - (8)].number)].a = (yyvsp[(8) - (8)].number);
    }
    break;

  case 40:
/* Line 1792 of yacc.c  */
#line 362 "src/cx.y"
    {
        gen(jpc, 0, 0);
    }
    break;

  case 41:
/* Line 1792 of yacc.c  */
#line 364 "src/cx.y"
    {
        gen(jmp, 0, (yyvsp[(2) - (8)].number));
        code[(yyvsp[(6) - (8)].number)].a = cx;
    }
    break;

  case 42:
/* Line 1792 of yacc.c  */
#line 368 "src/cx.y"
    {
        gen(jpc, 0, (yyvsp[(2) - (9)].number));
    }
    break;

  case 43:
/* Line 1792 of yacc.c  */
#line 371 "src/cx.y"
    {
        gen(jpe, 0, (yyvsp[(2) - (8)].number));
    }
    break;

  case 46:
/* Line 1792 of yacc.c  */
#line 375 "src/cx.y"
    {
        if ((yyvsp[(5) - (5)].number) == 1)
            gen(lit, 0, 1);
    }
    break;

  case 47:
/* Line 1792 of yacc.c  */
#line 378 "src/cx.y"
    {
        gen(jpe, 0, 0);
        gen(jmp, 0, 0);
    }
    break;

  case 48:
/* Line 1792 of yacc.c  */
#line 381 "src/cx.y"
    {
        gen(jmp, 0, (yyvsp[(4) - (12)].number));
    }
    break;

  case 49:
/* Line 1792 of yacc.c  */
#line 383 "src/cx.y"
    {
        gen(jmp, 0, (yyvsp[(10) - (15)].number));
        code[(yyvsp[(8) - (15)].number)].a = (yyvsp[(14) - (15)].number);
        code[(yyvsp[(8) - (15)].number) + 1].a = cx;
    }
    break;

  case 50:
/* Line 1792 of yacc.c  */
#line 388 "src/cx.y"
    {
        gen(ext, 0, 0);
    }
    break;

  case 54:
/* Line 1792 of yacc.c  */
#line 394 "src/cx.y"
    {/*错误处理*/}
    break;

  case 56:
/* Line 1792 of yacc.c  */
#line 399 "src/cx.y"
    {
        if ((yyvsp[(2) - (3)].number) == 0)
            yyerror("Call symbol does not exist");
        else if (table[(yyvsp[(2) - (3)].number)].kind != procedure)
            yyerror("Call symbol should be a procedure");
        else
            gen(cal, lev - table[(yyvsp[(2) - (3)].number)].level, table[(yyvsp[(2) - (3)].number)].adr);    
    }
    break;

  case 57:
/* Line 1792 of yacc.c  */
#line 412 "src/cx.y"
    {
        proctable[lev] = tx;
        gen(blo, 0, 0);
    }
    break;

  case 58:
/* Line 1792 of yacc.c  */
#line 417 "src/cx.y"
    {
        setdx((yyvsp[(4) - (4)].number));
        gen(pint, 0, (yyvsp[(4) - (4)].number) + 3);
    }
    break;

  case 59:
/* Line 1792 of yacc.c  */
#line 422 "src/cx.y"
    {
        gen(fre, 0, 0);
    }
    break;

  case 60:
/* Line 1792 of yacc.c  */
#line 426 "src/cx.y"
    {
        tx = proctable[lev];
    }
    break;

  case 63:
/* Line 1792 of yacc.c  */
#line 434 "src/cx.y"
    {
        if ((yyvsp[(1) - (4)].number) == 0)
            yyerror("Symbol does not exist");
        else if (table[(yyvsp[(1) - (4)].number)].kind == variable && table[(yyvsp[(1) - (4)].number)].type == inttype)
            gen(sto, lev - table[(yyvsp[(1) - (4)].number)].level, table[(yyvsp[(1) - (4)].number)].adr);
        else{
            char *str1 = "Symbol \"";
            char *str2 = "\" should be a variable and type should be int";
            char *str = (char *) malloc(strlen(str1) + strlen(str2) + strlen(table[(yyvsp[(1) - (4)].number)].name));
            strcpy(str, str1); 
            strcat(str, table[(yyvsp[(1) - (4)].number)].name);
            strcat(str, str2);
            yyerror(str);
        }
    }
    break;

  case 64:
/* Line 1792 of yacc.c  */
#line 449 "src/cx.y"
    {
        if ((yyvsp[(1) - (4)].number) == 0)
            yyerror("Symbol does not exist");
        else if (table[(yyvsp[(1) - (4)].number)].kind == variable && table[(yyvsp[(1) - (4)].number)].type == booltype) 
            gen(sto, lev - table[(yyvsp[(1) - (4)].number)].level, table[(yyvsp[(1) - (4)].number)].adr);
        else{
            char *str1 = "Symbol \"";
            char *str2 = "\" should be a variable and type should be bool";
            char *str = (char *) malloc(strlen(str1) + strlen(str2) + strlen(table[(yyvsp[(1) - (4)].number)].name));
            strcpy(str, str1); 
            strcat(str, table[(yyvsp[(1) - (4)].number)].name);
            strcat(str, str2);
            yyerror(str);
        }
    }
    break;

  case 67:
/* Line 1792 of yacc.c  */
#line 472 "src/cx.y"
    {
        (yyval.number) = 1; 
    }
    break;

  case 68:
/* Line 1792 of yacc.c  */
#line 476 "src/cx.y"
    {
        (yyval.number) = 0; 
    }
    break;

  case 69:
/* Line 1792 of yacc.c  */
#line 483 "src/cx.y"
    {
        (yyval.number) = cx;
    }
    break;

  case 70:
/* Line 1792 of yacc.c  */
#line 486 "src/cx.y"
    {
        gen(jmp, 0, 0); //满足if条件的直接jmp走
    }
    break;

  case 71:
/* Line 1792 of yacc.c  */
#line 489 "src/cx.y"
    {
        (yyval.number) = (yyvsp[(2) - (4)].number) + 1; //jmp的后一条指令位置
        code[(yyvsp[(2) - (4)].number)].a = cx; //回填，满足if条件的跳到哪里
    }
    break;

  case 72:
/* Line 1792 of yacc.c  */
#line 496 "src/cx.y"
    {
        gen(jpc, 0, 0);
        switchaddr = (yyvsp[(2) - (2)].number);
    }
    break;

  case 73:
/* Line 1792 of yacc.c  */
#line 499 "src/cx.y"
    {
        code[(yyvsp[(2) - (10)].number)].a = cx;
    }
    break;

  case 76:
/* Line 1792 of yacc.c  */
#line 510 "src/cx.y"
    {
        gen(jmp, 0, 0);
    }
    break;

  case 77:
/* Line 1792 of yacc.c  */
#line 512 "src/cx.y"
    {
        gen(lit, 0, 0);
        gen(jmp, 0, switchaddr);
        code[(yyvsp[(3) - (6)].number)].a = cx;
        gen(opr, 0, 24);
        gen(jpc, 0, (yyvsp[(3) - (6)].number)+1);
    }
    break;

  case 78:
/* Line 1792 of yacc.c  */
#line 522 "src/cx.y"
    {
        (yyval.number) = (yyvsp[(3) - (4)].number);
        // code[$3].a = cx;
        gen(jpc, 0, (yyvsp[(3) - (4)].number));
    }
    break;

  case 79:
/* Line 1792 of yacc.c  */
#line 531 "src/cx.y"
    {
        gen(opr, 0, 22);
    }
    break;

  case 81:
/* Line 1792 of yacc.c  */
#line 538 "src/cx.y"
    {
        gen(opr, 0, 21);
    }
    break;

  case 83:
/* Line 1792 of yacc.c  */
#line 546 "src/cx.y"
    { 
        if ((yyvsp[(1) - (1)].number) == 0)
            yyerror("Symbol does not exist");
        else if (table[(yyvsp[(1) - (1)].number)].kind == variable)
            gen(lod, lev - table[(yyvsp[(1) - (1)].number)].level, table[(yyvsp[(1) - (1)].number)].adr);
        else if (table[(yyvsp[(1) - (1)].number)].kind == constant)
            gen(lit, 0, table[(yyvsp[(1) - (1)].number)].val);
    }
    break;

  case 85:
/* Line 1792 of yacc.c  */
#line 555 "src/cx.y"
    {
        gen(opr, 0, 20);
    }
    break;

  case 87:
/* Line 1792 of yacc.c  */
#line 559 "src/cx.y"
    {
        gen(opr, 0, 6);
    }
    break;

  case 89:
/* Line 1792 of yacc.c  */
#line 566 "src/cx.y"
    {
        gen(opr, 0, 8);
    }
    break;

  case 90:
/* Line 1792 of yacc.c  */
#line 569 "src/cx.y"
    {
        gen(opr, 0, 9);
    }
    break;

  case 91:
/* Line 1792 of yacc.c  */
#line 572 "src/cx.y"
    {
        gen(opr, 0, 10);
    }
    break;

  case 92:
/* Line 1792 of yacc.c  */
#line 575 "src/cx.y"
    {
        gen(opr, 0, 13);
    }
    break;

  case 93:
/* Line 1792 of yacc.c  */
#line 578 "src/cx.y"
    {
        gen(opr, 0, 12);
    }
    break;

  case 94:
/* Line 1792 of yacc.c  */
#line 581 "src/cx.y"
    {
        gen(opr, 0, 11);
    }
    break;

  case 95:
/* Line 1792 of yacc.c  */
#line 588 "src/cx.y"
    { 
        if ((yyvsp[(1) - (1)].number) == 0)
            yyerror("Symbol does not exist");
        else if (table[(yyvsp[(1) - (1)].number)].kind == procedure)
            yyerror("Symbol should not be a procedure");
        else if (table[(yyvsp[(1) - (1)].number)].kind == constant) {
            (yyval.number) = 0;
            gen(lit, 0, table[(yyvsp[(1) - (1)].number)].val);
        }
        else if (table[(yyvsp[(1) - (1)].number)].kind == variable && table[(yyvsp[(1) - (1)].number)].type == inttype) {
            (yyval.number) = 0; 
            gen(lod, lev - table[(yyvsp[(1) - (1)].number)].level, table[(yyvsp[(1) - (1)].number)].adr);
        }
        else if (table[(yyvsp[(1) - (1)].number)].kind == variable && table[(yyvsp[(1) - (1)].number)].type == booltype) {
            (yyval.number) = 0; 
            gen(lod, lev - table[(yyvsp[(1) - (1)].number)].level, table[(yyvsp[(1) - (1)].number)].adr);
        }
    }
    break;

  case 96:
/* Line 1792 of yacc.c  */
#line 607 "src/cx.y"
    {
        (yyval.number) = 0;
        gen(lit, 0, (yyvsp[(1) - (1)].number));
    }
    break;

  case 97:
/* Line 1792 of yacc.c  */
#line 614 "src/cx.y"
    {
        gen(lit, 0, 1);
        (yyval.number) = 1;
    }
    break;

  case 98:
/* Line 1792 of yacc.c  */
#line 619 "src/cx.y"
    {
        gen(lit, 0, 0);
        (yyval.number) = 0;
    }
    break;

  case 99:
/* Line 1792 of yacc.c  */
#line 628 "src/cx.y"
    {
        (yyval.number) = 0;
    }
    break;

  case 100:
/* Line 1792 of yacc.c  */
#line 631 "src/cx.y"
    {
        (yyval.number) = 0;
        gen(opr, 0, 1);
    }
    break;

  case 101:
/* Line 1792 of yacc.c  */
#line 635 "src/cx.y"
    {
        (yyval.number) = (yyvsp[(1) - (1)].number);
    }
    break;

  case 102:
/* Line 1792 of yacc.c  */
#line 638 "src/cx.y"
    {
        (yyval.number) = 0;
        gen(opr, 0, 2);
    }
    break;

  case 103:
/* Line 1792 of yacc.c  */
#line 642 "src/cx.y"
    {
        (yyval.number) = 0;
        gen(opr, 0, 3);
    }
    break;

  case 104:
/* Line 1792 of yacc.c  */
#line 650 "src/cx.y"
    {
        (yyval.number) = (yyvsp[(1) - (1)].number);
    }
    break;

  case 105:
/* Line 1792 of yacc.c  */
#line 653 "src/cx.y"
    {
        (yyval.number) = 0;
        gen(opr, 0, 4);
    }
    break;

  case 106:
/* Line 1792 of yacc.c  */
#line 657 "src/cx.y"
    {
        (yyval.number) = 0;
        gen(opr, 0, 5);
    }
    break;

  case 107:
/* Line 1792 of yacc.c  */
#line 661 "src/cx.y"
    {
        (yyval.number) = 0;
        gen(opr, 0, 18);
    }
    break;

  case 108:
/* Line 1792 of yacc.c  */
#line 669 "src/cx.y"
    {
        (yyval.number) = (yyvsp[(1) - (1)].number);
    }
    break;

  case 109:
/* Line 1792 of yacc.c  */
#line 672 "src/cx.y"
    {
        (yyval.number) = 0;
        gen(opr, 0, 19);
    }
    break;

  case 110:
/* Line 1792 of yacc.c  */
#line 679 "src/cx.y"
    {
        (yyval.number) = (yyvsp[(1) - (1)].number);
    }
    break;

  case 111:
/* Line 1792 of yacc.c  */
#line 682 "src/cx.y"
    {
        (yyval.number) = 0;
    }
    break;

  case 112:
/* Line 1792 of yacc.c  */
#line 685 "src/cx.y"
    {
        (yyval.number) = (yyvsp[(1) - (1)].number);
    }
    break;

  case 113:
/* Line 1792 of yacc.c  */
#line 691 "src/cx.y"
    { 
        if ((yyvsp[(1) - (2)].number) == 0)
            yyerror("Symbol does not exist");
        else if (table[(yyvsp[(1) - (2)].number)].kind == constant) 
            yyerror("Constant cannot selfadd");
        else if (table[(yyvsp[(1) - (2)].number)].kind == variable && table[(yyvsp[(1) - (2)].number)].type != inttype) 
            yyerror("Only int variable can selfadd");
        else if (table[(yyvsp[(1) - (2)].number)].kind == variable && table[(yyvsp[(1) - (2)].number)].type == inttype) {
            gen(lod, lev - table[(yyvsp[(1) - (2)].number)].level, table[(yyvsp[(1) - (2)].number)].adr);
            gen(lit, 0, 1);
            gen(opr, 0, 2);
            gen(sto, lev - table[(yyvsp[(1) - (2)].number)].level, table[(yyvsp[(1) - (2)].number)].adr);
        }
        (yyval.number) = (yyvsp[(1) - (2)].number);
    }
    break;

  case 114:
/* Line 1792 of yacc.c  */
#line 706 "src/cx.y"
    { 
        if ((yyvsp[(1) - (2)].number) == 0)
            yyerror("Symbol does not exist");
        else if (table[(yyvsp[(1) - (2)].number)].kind == constant) 
            yyerror("Constant cannot selfadd");
        else if (table[(yyvsp[(1) - (2)].number)].kind == variable && table[(yyvsp[(1) - (2)].number)].type != inttype) 
            yyerror("Only int variable can selfadd");
        else if (table[(yyvsp[(1) - (2)].number)].kind == variable && table[(yyvsp[(1) - (2)].number)].type == inttype) {
            gen(lod, lev - table[(yyvsp[(1) - (2)].number)].level, table[(yyvsp[(1) - (2)].number)].adr);
            gen(lit, 0, 1);
            gen(opr, 0, 3);
            gen(sto, lev - table[(yyvsp[(1) - (2)].number)].level, table[(yyvsp[(1) - (2)].number)].adr);
        }
        (yyval.number) = (yyvsp[(1) - (2)].number);
    }
    break;

  case 115:
/* Line 1792 of yacc.c  */
#line 725 "src/cx.y"
    {
        (yyval.number) = position((yyvsp[(1) - (1)].ident)); 
    }
    break;

  case 116:
/* Line 1792 of yacc.c  */
#line 731 "src/cx.y"
    {
        (yyval.number) = cx;
    }
    break;

  case 117:
/* Line 1792 of yacc.c  */
#line 737 "src/cx.y"
    {
        (yyval.number) = tx;
    }
    break;

  case 118:
/* Line 1792 of yacc.c  */
#line 743 "src/cx.y"
    {
        lev++;               
        if (lev > levmax)   /* 嵌套层数过多 */
            yyerror("Lev is too big");    
    }
    break;

  case 119:
/* Line 1792 of yacc.c  */
#line 751 "src/cx.y"
    {
        lev--;
    }
    break;


/* Line 1792 of yacc.c  */
#line 2667 "cx.tab.c"
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


/* Line 2055 of yacc.c  */
#line 756 "src/cx.y"


int yyerror(char const *str){
    err = err + 1;
	extern char *yytext;
	fprintf(stdout, "parser error near line %d \"%s\", %s.\n", line, yytext, str);
    fprintf(foutput, "parser error near line %d \"%s\", %s.\n", line, yytext, str);
	return 0;
}

void init(){
    tx = 0;
    cx = 0;
    lev = 0;   
    proctable[0] = 0;
    num = 0;
    err = 0;
    hasProc = 0;
}

void enter(enum vartype t, enum object k){
    tx = tx + 1;
    strcpy(table[tx].name, id);
    table[tx].kind = k;
    table[tx].type = t;
    table[tx].level = lev;
}

int position(char *s){
    int i;
    strcpy(table[0].name, s);
    i = tx;
    while(strcmp(table[i].name, s) != 0)
        i--;
    return i;
}

/* 为本层变量分配相对地址，从3开始分配 */
void setdx(int n) {
    int i;
    for (i = 1; i <= n; i++) {
        table[tx - i + 1].adr = n - i + 3;
    }
}

/* 生成虚拟机代码 */
void gen(enum fct x, int y, int z) {
    if (cx >= cxmax) {
        printf("Program is too long!\n"); /* 生成的虚拟机代码程序过长 */
        exit(1);
    }
    if (z >= amax) {
        printf("Displacement address is too big!\n"); /* 地址偏移越界 */
        exit(1);
    }
    code[cx].f = x;
    code[cx].l = y;
    code[cx].a = z;
    cx++;
}

/* 输出所有目标代码  */
void listall() {
    int i;
    char name[][5] = {
        {"lit"}, {"opr"}, {"lod"}, {"sto"}, {"cal"}, {"pint"}, 
        {"jmp"}, {"jpc"}, {"jpe"}, {"ext"}, {"blo"}, {"fre"}
    };
    if (listswitch) {
        for (i = 0; i < cx; i++) {
            printf("%d %s %d %d\n", i, name[code[i].f], code[i].l, code[i].a);
            fprintf(fcode,"%d %s %d %d\n", i, name[code[i].f], code[i].l, code[i].a);
        }
        printf("\n");
    }
}

/* 输出符号表 */
void displaytable() {
    int i;
    if (tableswitch) {
        for (i = 1; i <= tx; i++) {
            switch (table[i].kind)
            {
            case constant:
                printf("    %d const %s ", i, table[i].name);
                printf("val=%d type=%d \n", table[i].val, table[i].type);
                fprintf(ftable, "    %d const %s ", i, table[i].name);
                fprintf(ftable, "val=%d type=%d \n", table[i].val, table[i].type);
                break;
            case variable:
                printf("    %d var   %s ", i, table[i].name);
                printf("lev=%d addr=%d type=%d \n", table[i].level, table[i].adr,  table[i].type);
                fprintf(ftable, "    %d var   %s ", i, table[i].name);
                fprintf(ftable, "lev=%d addr=%d type=%d \n", table[i].level, table[i].adr, table[i].type);
                break;
            case procedure:
                printf("    %d proc  %s ", i, table[i].name);
                printf("lev=%d addr=%d size=%d\n", table[i].level, table[i].adr, table[i].size);
                fprintf(ftable,"    %d proc  %s ", i, table[i].name);
                fprintf(ftable,"lev=%d addr=%d size=%d\n", table[i].level, table[i].adr, table[i].size);
                break;
            }
        }
        printf("\n");
        fprintf(ftable, "\n");
    }
}

void printstack(FILE* f, int t, int p, int *s) {
    int i;
    if (stackswitch) {
        fprintf(f, "pcode %2d: |", p);
        for (i = 1; i <= t; i++)
            fprintf(f, " %2d |", s[i]);
        fprintf(f, "%s", "\n");
    }
}

/* 解释程序 */
void interpret() {
	int p = 0; /* 指令指针 */
    int b = 1; /* 指令基址 */
    int t = 0; /* 栈顶指针 */
    struct instruction i; /* 存放当前指令 */
    int s[stacksize]; /* 栈 */

	printf("Start CX interpret\n");
 	fprintf(fresult,"Start CX interpret\n");
	s[0] = 0;
	s[1] = 0;
	s[2] = 0;
	s[3] = 0;
	do {
		i = code[p];  /* 读当前指令 */
        p = p + 1;
        switch (i.f)
        {
        case lit: /* 将常量a的值取到栈顶 */
            t = t + 1;
            s[t] = i.a;
            printstack(fstack, t, p, s);
            break;
        case opr: /* 数学、逻辑运算 */
            switch(i.a) {
            case 0:  /* 函数调用结束后返回 */
                t = b - 1;
                p = s[t + 3];
                b = s[t + 2];
                break;
            case 1: /* 栈顶元素取反 */
                s[t] = -s[t];
                break;
            case 2: /* 次栈顶项加上栈顶项，退两个栈元素，相加值进栈 */
                t = t - 1;
                s[t] = s[t] + s[t + 1];
                break;
            case 3:/* 次栈顶项减去栈顶项 */
                t = t - 1;
                s[t] = s[t] - s[t + 1];
                break;
            case 4:/* 次栈顶项乘以栈顶项 */
                t = t - 1;
                s[t] = s[t] * s[t + 1];
                break;
            case 5:/* 次栈顶项除以栈顶项 */
                t = t - 1;
                s[t] = s[t] / s[t + 1];
                break;
            case 6:/* 栈顶元素的奇偶判断 */
                s[t] = s[t] % 2;
                break;
            case 8:/* 次栈顶项与栈顶项是否相等 */
                t = t - 1;
                s[t] = (s[t] == s[t + 1]);
                break;
            case 9:/* 次栈顶项与栈顶项是否不等 */
                t = t - 1;
                s[t] = (s[t] != s[t + 1]);
                break;
            case 10:/* 次栈顶项是否小于栈顶项 */
                t = t - 1;
                s[t] = (s[t] < s[t + 1]);
                break;
            case 11:/* 次栈顶项是否大于等于栈顶项 */
                t = t - 1;
                s[t] = (s[t] >= s[t + 1]);
                break;
            case 12:/* 次栈顶项是否大于栈顶项 */
                t = t - 1;
                s[t] = (s[t] > s[t + 1]);
                break;
            case 13: /* 次栈顶项是否小于等于栈顶项 */
                t = t - 1;
                s[t] = (s[t] <= s[t + 1]);
                break;
            case 14:/* 栈顶值输出 */
                printf("%d", s[t]);
                fprintf(fresult, "%d", s[t]);
                t = t - 1;
                break;
            case 15:/* 输出换行符 */
                printf("\n");
                fprintf(fresult,"\n");
                break;
            case 16:/* 读入一个数置于栈顶 */
                t = t + 1;
                printf("input a number: ");
                fprintf(fresult, "input a number: ");
                scanf("%d", &(s[t]));
                getchar();
                fprintf(fresult, "%d\n", s[t]);           
                break;
            case 17:/* 读入一个字符置于栈顶 */
            {
                char ch;
                t = t + 1;
                printf("input a character: ");
                fprintf(fresult, "input a character: ");
                scanf("%c", &ch);
                getchar();
                s[t] = ch;
                fprintf(fresult, "%c\n", s[t]);           
                break;
            }
            case 18:/* 次栈顶项求余栈顶项 */ 
                t = t - 1;
                s[t] = s[t] % s[t + 1];
                break;
            case 19:/* 次栈顶项异或栈顶项 */
                t = t - 1;
                s[t] = s[t] ^ s[t + 1];
                break;
            case 20:/* 栈顶的值取not */
                s[t] = !s[t];
                break;
            case 21:/* 次栈顶项and栈顶项 */
                t = t - 1;
                s[t] = s[t] && s[t + 1];
                break;
            case 22:/* 次栈顶项or栈顶项 */
                t = t - 1;
                s[t] = s[t] || s[t + 1];
                break;
            case 23:/* 栈顶字符输出 */
                printf("%c", s[t]);
                fprintf(fresult, "%c", s[t]);
                t = t - 1;
                break;
            case 24:/* switch用 次栈顶项与栈顶项是否不等 */
                s[t] = (s[t] != s[t - 1]);
                break;
            }
            printstack(fstack, t, p, s);
            break;	
        case lod: /* 取相对当前过程的数据基地址为a的内存的值到栈顶 */
            t = t + 1;
            s[t] = s[base(i.l, s, b) + i.a];
            printstack(fstack, t, p, s);            
            break;
        case sto: /* 栈顶的值存到相对当前过程的数据基地址为a的内存 */
            s[base(i.l, s, b) + i.a] = s[t];
            t = t - 1;
            printstack(fstack, t, p, s);
            break;
        case cal: /* 调用子过程 */
            s[t + 1] = base(i.l, s, b); /* 将父过程基地址入栈，即建立静态链 */
            s[t + 2] = b; /* 将本过程基地址入栈，即建立动态链 */
            s[t + 3] = p; /* 将当前指令指针入栈，即保存返回地址 */
            b = t + 1;  /* 改变基地址指针值为新过程的基地址 */
            p = i.a;  /* 跳转 */
            printstack(fstack, t, p, s);
            break;
        case pint: /* 在数据栈中为被调用的过程开辟a个单元的数据区 */
            t = t + i.a;
            printstack(fstack, t, p, s);
            break;
        case jmp: /* 直接跳转 */
            p = i.a;
            printstack(fstack, t, p, s);
            break;
        case jpc: /* 如果栈顶等于0条件跳转 */
            if (s[t] == 0)
                p = i.a;
            t = t - 1;
            printstack(fstack, t, p, s);
            break;
        case jpe: /* 如果栈顶等于1条件跳转 */
            if (s[t]) 
                p = i.a;
            t = t - 1;
            printstack(fstack, t, p, s);
            break;
        case ext:
            p = 0;
            printstack(fstack, t, p, s);
            break;
        case blo: //不改变p
            s[t + 1] = base(i.l, s, b);
            s[t + 2] = b;
            b = t + 1;
            printstack(fstack, t, p, s);
            break;
        case fre: //不改变p
            t = b - 1;
            b = s[t + 2];
            printstack(fstack, t, p, s);
            break;
        }
    } while (p != 0);
    printf("End CX interpret\n");
    fprintf(fresult, "End CX interpret\n");
}

/* 解释程序 */
void interpret_once(int q) {
    struct instruction i; /* 存放当前指令 */
    int s[stacksize]; /* 栈 */

    FILE* fqresult;
    FILE* fqstack;

    FILE* fqcode;

    char tmp[3];
    itoa(q, tmp, 10);
    

    char* qresult1 = "./interpret/fqresult_";
    char* q2 = ".txt";
    
    char *qs = (char *) malloc(strlen(qresult1) + strlen(tmp) + strlen(q2));

    strcpy(qs, qresult1);
    strcat(qs, tmp);
    strcat(qs, q2);

    char* qstack1 = "./interpret/fqstack_";
    char *qstack = (char *) malloc(strlen(qstack1) + strlen(tmp) + strlen(q2));

    strcpy(qstack, qstack1);
    strcat(qstack, tmp);
    strcat(qstack, q2);

    char* qcode1 = "./interpret/fqcode_";
    char *qcode = (char *) malloc(strlen(qcode1) + strlen(tmp) + strlen(q2)+1);

    strcpy(qcode, qcode1);
    strcat(qcode, tmp);
    strcat(qcode, q2);


    if ((fqresult = fopen(qs, "w")) == NULL) {
        printf("Can't open qresult once file!\n");
        exit(1);
    }

    if ((fqstack = fopen(qstack, "w")) == NULL) {
        printf("Can't open qstack once file!\n");
        exit(1);
    }

    if ((fqcode = fopen(qcode, "w")) == NULL) {
        printf("Can't open qcode once file!\n");
        exit(1);
    }

	s[0] = 0;
	s[1] = 0;
	s[2] = 0;
	s[3] = 0;
		i = code[p];  /* 读当前指令 */
        char name[][5] = {
            {"lit"}, {"opr"}, {"lod"}, {"sto"}, {"cal"}, {"pint"}, 
            {"jmp"}, {"jpc"}, {"jpe"}, {"ext"}, {"blo"}, {"fre"}
        };
        fprintf(fqcode,"%d %s %d %d\n", q+1, name[i.f], i.l, i.a);
        fclose(fqcode);
        p = p + 1;
        switch (i.f)
        {
        case lit: /* 将常量a的值取到栈顶 */
            t = t + 1;
            s[t] = i.a;
            printstack(fqstack, t, p, s);
            break;
        case opr: /* 数学、逻辑运算 */
            switch(i.a) {
            case 0:  /* 函数调用结束后返回 */
                t = b - 1;
                p = s[t + 3];
                b = s[t + 2];
                break;
            case 1: /* 栈顶元素取反 */
                s[t] = -s[t];
                break;
            case 2: /* 次栈顶项加上栈顶项，退两个栈元素，相加值进栈 */
                t = t - 1;
                s[t] = s[t] + s[t + 1];
                break;
            case 3:/* 次栈顶项减去栈顶项 */
                t = t - 1;
                s[t] = s[t] - s[t + 1];
                break;
            case 4:/* 次栈顶项乘以栈顶项 */
                t = t - 1;
                s[t] = s[t] * s[t + 1];
                break;
            case 5:/* 次栈顶项除以栈顶项 */
                t = t - 1;
                s[t] = s[t] / s[t + 1];
                break;
            case 6:/* 栈顶元素的奇偶判断 */
                s[t] = s[t] % 2;
                break;
            case 8:/* 次栈顶项与栈顶项是否相等 */
                t = t - 1;
                s[t] = (s[t] == s[t + 1]);
                break;
            case 9:/* 次栈顶项与栈顶项是否不等 */
                t = t - 1;
                s[t] = (s[t] != s[t + 1]);
                break;
            case 10:/* 次栈顶项是否小于栈顶项 */
                t = t - 1;
                s[t] = (s[t] < s[t + 1]);
                break;
            case 11:/* 次栈顶项是否大于等于栈顶项 */
                t = t - 1;
                s[t] = (s[t] >= s[t + 1]);
                break;
            case 12:/* 次栈顶项是否大于栈顶项 */
                t = t - 1;
                s[t] = (s[t] > s[t + 1]);
                break;
            case 13: /* 次栈顶项是否小于等于栈顶项 */
                t = t - 1;
                s[t] = (s[t] <= s[t + 1]);
                break;
            case 14:/* 栈顶值输出 */
                printf("%d", s[t]);
                fprintf(fqresult, "%d", s[t]);
                t = t - 1;
                break;
            case 15:/* 输出换行符 */
                printf("\n");
                fprintf(fqresult,"\n");
                break;
            case 16:/* 读入一个数置于栈顶 */
                t = t + 1;
                printf("input a number: ");
                fprintf(fqresult, "input a number: ");
                scanf("%d", &(s[t]));
                getchar();
                fprintf(fqresult, "%d\n", s[t]);           
                break;
            case 17:/* 读入一个字符置于栈顶 */
            {
                char ch;
                t = t + 1;
                printf("input a character: ");
                fprintf(fqresult, "input a character: ");
                scanf("%c", &ch);
                getchar();
                s[t] = ch;
                fprintf(fqresult, "%c\n", s[t]);           
                break;
            }
            case 18:/* 次栈顶项求余栈顶项 */ 
                t = t - 1;
                s[t] = s[t] % s[t + 1];
                break;
            case 19:/* 次栈顶项异或栈顶项 */
                t = t - 1;
                s[t] = s[t] ^ s[t + 1];
                break;
            case 20:/* 栈顶的值取not */
                s[t] = !s[t];
                break;
            case 21:/* 次栈顶项and栈顶项 */
                t = t - 1;
                s[t] = s[t] && s[t + 1];
                break;
            case 22:/* 次栈顶项or栈顶项 */
                t = t - 1;
                s[t] = s[t] || s[t + 1];
                break;
            case 23:/* 栈顶字符输出 */
                printf("%c", s[t]);
                fprintf(fqresult, "%c", s[t]);
                t = t - 1;
                break;
            case 24:/* switch用 次栈顶项与栈顶项是否不等 */
                s[t] = (s[t] != s[t - 1]);
                break;
            }
            printstack(fqstack, t, p, s);
            break;	
        case lod: /* 取相对当前过程的数据基地址为a的内存的值到栈顶 */
            t = t + 1;
            s[t] = s[base(i.l, s, b) + i.a];
            printstack(fqstack, t, p, s);            
            break;
        case sto: /* 栈顶的值存到相对当前过程的数据基地址为a的内存 */
            s[base(i.l, s, b) + i.a] = s[t];
            t = t - 1;
            printstack(fqstack, t, p, s);
            break;
        case cal: /* 调用子过程 */
            s[t + 1] = base(i.l, s, b); /* 将父过程基地址入栈，即建立静态链 */
            s[t + 2] = b; /* 将本过程基地址入栈，即建立动态链 */
            s[t + 3] = p; /* 将当前指令指针入栈，即保存返回地址 */
            b = t + 1;  /* 改变基地址指针值为新过程的基地址 */
            p = i.a;  /* 跳转 */
            printstack(fqstack, t, p, s);
            break;
        case pint: /* 在数据栈中为被调用的过程开辟a个单元的数据区 */
            t = t + i.a;
            printstack(fqstack, t, p, s);
            break;
        case jmp: /* 直接跳转 */
            p = i.a;
            printstack(fqstack, t, p, s);
            break;
        case jpc: /* 如果栈顶等于0条件跳转 */
            if (s[t] == 0)
                p = i.a;
            t = t - 1;
            printstack(fqstack, t, p, s);
            break;
        case jpe: /* 如果栈顶等于1条件跳转 */
            if (s[t]) 
                p = i.a;
            t = t - 1;
            printstack(fqstack, t, p, s);
            break;
        case ext:
            p = 0;
            printstack(fqstack, t, p, s);
            break;
        case blo: //不改变p
            s[t + 1] = base(i.l, s, b);
            s[t + 2] = b;
            b = t + 1;
            printstack(fqstack, t, p, s);
            break;
        case fre: //不改变p
            t = b - 1;
            b = s[t + 2];
            printstack(fqstack, t, p, s);
            break;
        }
    fclose(fqresult);
    fclose(fqstack);
}


/* 通过过程基址求上ｌ层过程的基址 */
int base(int l, int s[], int b) {
    int b1 = b;
    while (l > 0) {
        b1 = s[b1];
        l = l - 1;
    }
    return b1;
}

int main(int argc, char *argv[])
{
    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            if (strcmp(argv[i], "-c") == 0) {  /* 是否输出虚拟机代码 */
                listswitch = true;
            } else if (strcmp(argv[i], "-t") == 0) {  /* 是否输出符号表 */
                tableswitch = true;
            } else if (strcmp(argv[i], "-s") == 0) {  /* 是否输出栈信息 */
                stackswitch = true;
            } else if (strcmp(argv[i], "-i") == 0) {  /* 是否输出单步调试信息 */
                interpretswitch = true;
            }
        }
    }
    if ((fin = fopen(argv[argc - 1], "r")) == NULL) {
        printf("Cann't open file according to given filename.\n");
		exit(0);
    }
    if ((foutput = fopen("foutput.txt", "w")) == NULL) {
        printf("Can't open the output file!\n");
        exit(0);
    }
    if ((ftable = fopen("ftable.txt", "w")) == NULL) {
        printf("Can't open ftable.txt file!\n");
        exit(0);
    }

	redirectInput(fin);
    init();
	err=0;
	yyparse();

    if ((fcode = fopen("fcode.txt", "w")) == NULL) {
        printf("Can't open fcode.txt file!\n");
        exit(1);
    }
    if ((fresult = fopen("fresult.txt", "w")) == NULL) {
        printf("Can't open fresult.txt file!\n");
        exit(1);
    }
    if ((fstack = fopen("fstack.txt", "w")) == NULL) {
        printf("Can't open fresult.txt file!\n");
        exit(1);
    }

	if(err==0){
        printf("===Parsing success!===\n\n");
        fprintf(foutput, "===Parsing success!===\n");

        listall();  /* 输出所有代码 */
        fclose(fcode);
        if(!hasProc)
            displaytable();
        if(interpretswitch){
            p = 0; /* 指令指针 */
            b = 1; /* 指令基址 */
            t = 0; /* 栈顶指针 */
            int q = 0;
            do{
                interpret_once(q);
                q++;
            }while(p!=0);
        }
        else
            interpret();  /* 调用解释执行程序 */
        fclose(fresult);
        fclose(fstack);
	}
	else{
        if(err == 1)
	 	    printf("%d error in cx program.\n", err);
        else
            printf("%d errors in cx program.\n", err);
	}
	fclose(ftable);
    fclose(foutput);
    fclose(fin);
	return 0;
}