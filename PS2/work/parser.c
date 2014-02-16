/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.5"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 268 of yacc.c  */
#line 1 "src/parser.y"

#include "nodetypes.h"
#include "tree.h"
#include <stdlib.h>

// This defines the type for every $$ value in the productions.
#define YYSTYPE node_t *

#define YYDEBUG 1

// This variable is located in vslc.c
extern int outputStage;

/*
 * Variables connecting the parser to the state of the scanner - defs. will be
 * generated as part of the scanner (lexical analyzer).
 */
extern char yytext[];
extern int yylineno;

/*
 * Wrapper functions for node_init. The main purpose of calling these functions
 * instead of node_init directly is to enable the debug output, as well as a reduction
 * of typing. These functions are named CN for "create
 * node", and L, T, or E if they take an additional label, type or expression_type argument
 * in addition. When the label, type or expression_type is not supplied, node_init is called
 * default values.
 */
 
node_t* CN(nodetype_t type, int n_children, ...){
	if( outputStage == 2 ) fprintf ( stderr, "Hit rule \"%s\" on text '%s' at line %d\n", type.text , yytext, yylineno );
	va_list child_list;
	va_start(child_list, n_children);
	node_t* to_return = node_init(type, NULL, NO_TYPE, default_e, n_children, child_list);
	va_end(child_list);
	return to_return;
}

node_t* CNL(nodetype_t type, char* label, int n_children, ...){
	if( outputStage == 2 ) fprintf ( stderr, "Hit rule \"%s\" on text '%s' at line %d\n", type.text , yytext, yylineno );
	va_list child_list;
	va_start(child_list, n_children);
	node_t* to_return = node_init(type, label, NO_TYPE, default_e, n_children, child_list);
	va_end(child_list);
	return to_return;
}

node_t* CNT(nodetype_t type, base_data_type_t base_type, int n_children, ...){
	if( outputStage == 2 ) fprintf ( stderr, "Hit rule \"%s\" on text '%s' at line %d\n", type.text , yytext, yylineno );
	va_list child_list;
	va_start(child_list, n_children);
	node_t* to_return = node_init(type, NULL, base_type, default_e, n_children, child_list);
	va_end(child_list);
	return to_return;
}

node_t* CNE(nodetype_t type, expression_type_t expression_type, int n_children, ...){
	if( outputStage == 2 ) fprintf ( stderr, "Hit rule \"%s\" on text '%s' at line %d\n", type.text , yytext, yylineno );
	va_list child_list;
	va_start(child_list, n_children);
	node_t* to_return = node_init(type, NULL, NO_TYPE, expression_type, n_children, child_list);
	va_end(child_list);
	return to_return;
}


// Helper for setting the value of an Integer node
static void SetInteger(node_t* node, char *string)
{
	node->int_const = atol ( string );
	node->data_type.base_type= INT_TYPE;
}

// Helper for setting the value of an float node
static void SetFloat(node_t* node, char *string)
{
	node->float_const = atof ( string );
	node->data_type.base_type= FLOAT_TYPE;
}


// Helper for setting the value of an string node
static void SetString(node_t* node, char *string)
{
	node->string_const = STRDUP( string );
	node->data_type.base_type= STRING_TYPE;
}

/*
 * Since the return value of yyparse is an integer (as defined by yacc/bison),
 * we need the top level production to finalize parsing by setting the root
 * node of the entire syntax tree inside its semantic rule instead. This global
 * variable will let us get a hold of the tree root after it has been
 * generated.
 */
node_t *root;


/*
 * These functions are referenced by the generated parser before their
 * definition. Prototyping them saves us a couple of warnings during build.
 */
int yyerror ( const char *error );  /* Defined below */
int yylex ( void );                 /* Defined in the generated scanner */


/* Line 268 of yacc.c  */
#line 178 "y.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     INT_CONST = 258,
     FLOAT_CONST = 259,
     TRUE_CONST = 260,
     FALSE_CONST = 261,
     STRING_CONST = 262,
     INT = 263,
     FLOAT = 264,
     BOOL = 265,
     VOID = 266,
     IDENTIFIER = 267,
     ASSIGN = 268,
     FUNC = 269,
     START = 270,
     PRINT = 271,
     RETURN = 272,
     IF = 273,
     THEN = 274,
     ELSE = 275,
     END = 276,
     WHILE = 277,
     DO = 278,
     EQUAL = 279,
     GEQUAL = 280,
     LEQUAL = 281,
     NEQUAL = 282,
     AND = 283,
     OR = 284,
     _CLASS_ = 285,
     THIS = 286,
     HAS = 287,
     WITH = 288,
     NEW = 289,
     UMINUS = 290
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 255 "y.tab.c"

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
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
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
/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  8
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   401

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  50
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  25
/* YYNRULES -- Number of rules.  */
#define YYNRULES  70
/* YYNRULES -- Number of states.  */
#define YYNSTATES  131

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   290

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    49,     2,     2,     2,     2,    47,     2,
      43,    44,    39,    37,    45,    38,    42,    40,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    46,
      35,     2,    36,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    48,     2,     2,     2,     2,     2,
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
      41
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,     8,    18,    21,    22,    24,    27,
      29,    33,    35,    39,    41,    42,    44,    45,    47,    50,
      58,    62,    63,    66,    69,    72,    75,    78,    81,    84,
      87,    91,    99,   105,   111,   114,   117,   119,   123,   127,
     131,   135,   139,   143,   147,   151,   155,   159,   163,   167,
     170,   173,   177,   179,   181,   183,   186,   191,   198,   200,
     204,   206,   208,   210,   212,   214,   216,   218,   220,   222,
     224
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      51,     0,    -1,    53,    -1,    59,    53,    -1,    73,    14,
      74,    43,    57,    44,    15,    54,    21,    -1,    53,    52,
      -1,    -1,    62,    -1,    54,    62,    -1,    63,    -1,    55,
      45,    63,    -1,    69,    -1,    56,    45,    69,    -1,    55,
      -1,    -1,    56,    -1,    -1,    60,    -1,    59,    60,    -1,
      30,    74,    32,    61,    33,    53,    21,    -1,    61,    63,
      45,    -1,    -1,    63,    45,    -1,    64,    45,    -1,    65,
      45,    -1,    66,    45,    -1,    68,    45,    -1,    67,    45,
      -1,    70,    46,    -1,    73,    74,    -1,    74,    13,    69,
      -1,    18,    69,    19,    54,    20,    62,    21,    -1,    18,
      69,    19,    54,    21,    -1,    22,    69,    23,    54,    21,
      -1,    17,    69,    -1,    16,    56,    -1,    72,    -1,    69,
      37,    69,    -1,    69,    38,    69,    -1,    69,    39,    69,
      -1,    69,    40,    69,    -1,    69,    36,    69,    -1,    69,
      35,    69,    -1,    69,    24,    69,    -1,    69,    27,    69,
      -1,    69,    25,    69,    -1,    69,    26,    69,    -1,    69,
      47,    69,    -1,    69,    48,    69,    -1,    38,    69,    -1,
      49,    69,    -1,    43,    69,    44,    -1,    70,    -1,    31,
      -1,    71,    -1,    34,    73,    -1,    74,    43,    58,    44,
      -1,    69,    42,    74,    43,    58,    44,    -1,    74,    -1,
      69,    42,    74,    -1,     5,    -1,     6,    -1,     3,    -1,
       4,    -1,     7,    -1,     8,    -1,     9,    -1,    10,    -1,
      11,    -1,    74,    -1,    12,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,   138,   138,   139,   140,   141,   142,   143,   144,   145,
     146,   147,   148,   149,   150,   151,   152,   153,   154,   155,
     156,   157,   158,   159,   160,   161,   162,   163,   164,   165,
     166,   167,   168,   169,   170,   171,   172,   173,   174,   175,
     176,   177,   178,   179,   180,   181,   182,   183,   184,   185,
     186,   187,   188,   189,   190,   191,   192,   193,   194,   195,
     196,   197,   198,   199,   200,   201,   202,   203,   204,   205,
     206
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INT_CONST", "FLOAT_CONST", "TRUE_CONST",
  "FALSE_CONST", "STRING_CONST", "INT", "FLOAT", "BOOL", "VOID",
  "IDENTIFIER", "ASSIGN", "FUNC", "START", "PRINT", "RETURN", "IF", "THEN",
  "ELSE", "END", "WHILE", "DO", "EQUAL", "GEQUAL", "LEQUAL", "NEQUAL",
  "AND", "OR", "_CLASS_", "THIS", "HAS", "WITH", "NEW", "'<'", "'>'",
  "'+'", "'-'", "'*'", "'/'", "UMINUS", "'.'", "'('", "')'", "','", "';'",
  "'&'", "'|'", "'!'", "$accept", "program", "function", "function_list",
  "statement_list", "variable_list", "expression_list", "parameter_list",
  "argument_list", "class_list", "class", "declaration_list", "statement",
  "declaration_statement", "assignment_statement", "if_statement",
  "while_statement", "return_statement", "print_statement", "expression",
  "call", "lvalue", "constant", "type", "variable", 0
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
     285,   286,   287,   288,   289,    60,    62,    43,    45,    42,
      47,   290,    46,    40,    41,    44,    59,    38,   124,    33
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    50,    51,    51,    52,    53,    53,    54,    54,    55,
      55,    56,    56,    57,    57,    58,    58,    59,    59,    60,
      61,    61,    62,    62,    62,    62,    62,    62,    62,    63,
      64,    65,    65,    66,    67,    68,    69,    69,    69,    69,
      69,    69,    69,    69,    69,    69,    69,    69,    69,    69,
      69,    69,    69,    69,    69,    69,    70,    70,    71,    71,
      72,    72,    72,    72,    72,    73,    73,    73,    73,    73,
      74
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     9,     2,     0,     1,     2,     1,
       3,     1,     3,     1,     0,     1,     0,     1,     2,     7,
       3,     0,     2,     2,     2,     2,     2,     2,     2,     2,
       3,     7,     5,     5,     2,     2,     1,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     2,
       2,     3,     1,     1,     1,     2,     4,     6,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       6,     0,     0,     2,     6,    17,    70,     0,     1,    65,
      66,    67,    68,     5,     0,    69,     3,    18,    21,     0,
       0,     0,     6,     0,     0,    14,     0,    20,    29,    13,
       0,     9,    19,     0,     0,    10,     0,    62,    63,    60,
      61,    64,     0,     0,     0,     0,    53,     0,     0,     0,
       0,     0,     7,     0,     0,     0,     0,     0,     0,     0,
      52,    54,    36,    58,     0,    11,    52,    58,    34,     0,
       0,    55,    49,     0,    50,     4,     8,    22,    23,    24,
      25,    27,    26,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    28,     0,    16,     0,
       0,     0,    51,    43,    45,    46,    44,    42,    41,    37,
      38,    39,    40,    59,    47,    48,    30,    15,     0,    12,
       0,     0,    16,    56,     0,    32,    33,     0,     0,    57,
      31
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     2,    13,     3,    51,    29,   117,    30,   118,     4,
       5,    20,    52,    53,    54,    55,    56,    57,    58,    59,
      66,    61,    62,    24,    67
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -81
static const yytype_int16 yypact[] =
{
     -17,    10,    28,   158,   -17,   -81,   -81,    -3,   -81,   -81,
     -81,   -81,   -81,   -81,    20,   -81,   158,   -81,   -81,    10,
      44,     4,   -81,    -7,    10,   158,    70,   -81,   -81,    12,
       0,   -81,   -81,   158,    34,   -81,   263,   -81,   -81,   -81,
     -81,   -81,     2,     2,     2,     2,   -81,   158,     2,     2,
       2,   169,   -81,    13,    14,    15,    25,    26,    29,   353,
      37,   -81,   -81,    -2,    30,   353,   -81,    41,   353,   283,
     309,   -81,    48,   328,   353,   -81,   -81,   -81,   -81,   -81,
     -81,   -81,   -81,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    10,     2,     2,   -81,     2,     2,     2,
     263,   263,   -81,   110,   157,   157,   110,   157,   157,    48,
      48,    -5,    -5,    50,   353,   353,   353,    30,    53,   353,
     122,   216,     2,   -81,   263,   -81,   -81,    54,    73,   -81,
     -81
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -81,   -81,   -81,     8,   -80,   -81,    59,   -81,   -10,   -81,
     111,   -81,   -48,     6,   -81,   -81,   -81,   -81,   -81,    19,
     -35,   -81,   -81,     1,    -1
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -70
static const yytype_int16 yytable[] =
{
       7,    60,    15,    76,    14,    37,    38,    39,    40,    41,
     -69,    97,    16,     1,     6,    15,    60,    14,    21,    15,
     120,   121,     6,    28,    15,    15,    23,    14,     8,    18,
      26,    31,    15,    46,    19,    63,    47,    93,    27,    35,
      48,    98,    94,    95,    34,    49,    15,    25,    71,    36,
      63,    50,     9,    10,    11,    12,     6,    33,    77,    78,
      79,    65,    68,    69,    70,    60,    60,    72,    73,    74,
      80,    81,    76,    76,    82,    99,   128,    22,     9,    10,
      11,    12,     6,    96,    98,    60,    60,    91,    92,    60,
      93,    32,   113,   122,   130,    94,    95,   123,   129,    63,
      63,    64,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   127,   114,   115,    17,   116,    65,   119,    63,
      63,     0,     0,    63,     0,    37,    38,    39,    40,    41,
       9,    10,    11,    12,     6,    84,    85,     0,    42,    43,
      44,    65,   124,   125,    45,    87,    88,    89,    90,    91,
      92,     0,    93,    46,     0,     0,    47,    94,    95,     0,
      48,     0,     0,     0,     0,    49,     9,    10,    11,    12,
       6,    50,    37,    38,    39,    40,    41,     9,    10,    11,
      12,     6,     0,     0,     0,    42,    43,    44,     0,     0,
      75,    45,     0,     0,    89,    90,    91,    92,     0,    93,
      46,     0,     0,    47,    94,    95,     0,    48,     0,     0,
       0,     0,    49,     0,     0,     0,     0,     0,    50,    37,
      38,    39,    40,    41,     9,    10,    11,    12,     6,     0,
       0,     0,    42,    43,    44,     0,     0,   126,    45,     0,
       0,     0,     0,     0,     0,     0,     0,    46,     0,     0,
      47,     0,     0,     0,    48,     0,     0,     0,     0,    49,
       0,     0,     0,     0,     0,    50,    37,    38,    39,    40,
      41,     9,    10,    11,    12,     6,     0,     0,     0,    42,
      43,    44,     0,     0,     0,    45,     0,     0,     0,     0,
       0,     0,     0,     0,    46,     0,     0,    47,     0,     0,
       0,    48,   100,     0,     0,     0,    49,    83,    84,    85,
      86,     0,    50,     0,     0,     0,     0,     0,    87,    88,
      89,    90,    91,    92,     0,    93,     0,     0,     0,     0,
      94,    95,   101,    83,    84,    85,    86,     0,     0,     0,
       0,     0,     0,     0,    87,    88,    89,    90,    91,    92,
       0,    93,    83,    84,    85,    86,    94,    95,     0,     0,
       0,     0,     0,    87,    88,    89,    90,    91,    92,     0,
      93,     0,   102,     0,     0,    94,    95,    83,    84,    85,
      86,     0,     0,     0,     0,     0,     0,     0,    87,    88,
      89,    90,    91,    92,     0,    93,     0,     0,     0,     0,
      94,    95
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-81))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int8 yycheck[] =
{
       1,    36,     3,    51,     3,     3,     4,     5,     6,     7,
      12,    13,     4,    30,    12,    16,    51,    16,    19,    20,
     100,   101,    12,    24,    25,    26,    20,    26,     0,    32,
      22,    25,    33,    31,    14,    36,    34,    42,    45,    33,
      38,    43,    47,    48,    44,    43,    47,    43,    47,    15,
      51,    49,     8,     9,    10,    11,    12,    45,    45,    45,
      45,    42,    43,    44,    45,   100,   101,    48,    49,    50,
      45,    45,   120,   121,    45,    45,   124,    33,     8,     9,
      10,    11,    12,    46,    43,   120,   121,    39,    40,   124,
      42,    21,    93,    43,    21,    47,    48,    44,    44,   100,
     101,    42,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,   122,    94,    95,     4,    97,    98,    99,   120,
     121,    -1,    -1,   124,    -1,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    25,    26,    -1,    16,    17,
      18,   122,    20,    21,    22,    35,    36,    37,    38,    39,
      40,    -1,    42,    31,    -1,    -1,    34,    47,    48,    -1,
      38,    -1,    -1,    -1,    -1,    43,     8,     9,    10,    11,
      12,    49,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    -1,    -1,    -1,    16,    17,    18,    -1,    -1,
      21,    22,    -1,    -1,    37,    38,    39,    40,    -1,    42,
      31,    -1,    -1,    34,    47,    48,    -1,    38,    -1,    -1,
      -1,    -1,    43,    -1,    -1,    -1,    -1,    -1,    49,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    -1,
      -1,    -1,    16,    17,    18,    -1,    -1,    21,    22,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    31,    -1,    -1,
      34,    -1,    -1,    -1,    38,    -1,    -1,    -1,    -1,    43,
      -1,    -1,    -1,    -1,    -1,    49,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    -1,    -1,    -1,    16,
      17,    18,    -1,    -1,    -1,    22,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    31,    -1,    -1,    34,    -1,    -1,
      -1,    38,    19,    -1,    -1,    -1,    43,    24,    25,    26,
      27,    -1,    49,    -1,    -1,    -1,    -1,    -1,    35,    36,
      37,    38,    39,    40,    -1,    42,    -1,    -1,    -1,    -1,
      47,    48,    23,    24,    25,    26,    27,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    35,    36,    37,    38,    39,    40,
      -1,    42,    24,    25,    26,    27,    47,    48,    -1,    -1,
      -1,    -1,    -1,    35,    36,    37,    38,    39,    40,    -1,
      42,    -1,    44,    -1,    -1,    47,    48,    24,    25,    26,
      27,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    35,    36,
      37,    38,    39,    40,    -1,    42,    -1,    -1,    -1,    -1,
      47,    48
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    30,    51,    53,    59,    60,    12,    74,     0,     8,
       9,    10,    11,    52,    73,    74,    53,    60,    32,    14,
      61,    74,    33,    63,    73,    43,    53,    45,    74,    55,
      57,    63,    21,    45,    44,    63,    15,     3,     4,     5,
       6,     7,    16,    17,    18,    22,    31,    34,    38,    43,
      49,    54,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    74,    56,    69,    70,    74,    69,    69,
      69,    73,    69,    69,    69,    21,    62,    45,    45,    45,
      45,    45,    45,    24,    25,    26,    27,    35,    36,    37,
      38,    39,    40,    42,    47,    48,    46,    13,    43,    45,
      19,    23,    44,    69,    69,    69,    69,    69,    69,    69,
      69,    69,    69,    74,    69,    69,    69,    56,    58,    69,
      54,    54,    43,    44,    20,    21,    21,    58,    62,    44,
      21
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

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


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
  YYSIZE_T yysize0 = yytnamerr (0, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  YYSIZE_T yysize1;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = 0;
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
                yysize1 = yysize + yytnamerr (0, yytname[yyx]);
                if (! (yysize <= yysize1
                       && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                  return 2;
                yysize = yysize1;
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

  yysize1 = yysize + yystrlen (yyformat);
  if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
    return 2;
  yysize = yysize1;

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


/* Prevent warnings from -Wmissing-prototypes.  */
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


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

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

       Refer to the stacks thru separate pointers, to allow yyoverflow
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
  int yytoken;
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

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

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
  *++yyvsp = yylval;

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
        case 2:

/* Line 1806 of yacc.c  */
#line 138 "src/parser.y"
    { root = CN( program_n, 1, (yyvsp[(1) - (1)]) ); }
    break;

  case 3:

/* Line 1806 of yacc.c  */
#line 139 "src/parser.y"
    { root = CN( program_n, 2, (yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]) ); }
    break;

  case 4:

/* Line 1806 of yacc.c  */
#line 140 "src/parser.y"
    { (yyval) = CN( function_n, 4, (yyvsp[(1) - (9)]), (yyvsp[(3) - (9)]), (yyvsp[(5) - (9)]), (yyvsp[(8) - (9)])); }
    break;

  case 5:

/* Line 1806 of yacc.c  */
#line 141 "src/parser.y"
    { (yyval) = CN( function_list_n, 2, (yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]) ); }
    break;

  case 6:

/* Line 1806 of yacc.c  */
#line 142 "src/parser.y"
    { (yyval) = NULL;}
    break;

  case 7:

/* Line 1806 of yacc.c  */
#line 143 "src/parser.y"
    { (yyval) = CN( statement_list_n, 1, (yyvsp[(1) - (1)]) ); }
    break;

  case 8:

/* Line 1806 of yacc.c  */
#line 144 "src/parser.y"
    { (yyval) = CN( statement_list_n, 2, (yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]) ); }
    break;

  case 9:

/* Line 1806 of yacc.c  */
#line 145 "src/parser.y"
    { (yyval) = CN( variable_list_n, 1, (yyvsp[(1) - (1)])); }
    break;

  case 10:

/* Line 1806 of yacc.c  */
#line 146 "src/parser.y"
    { (yyval) = CN( variable_list_n, 2, (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); }
    break;

  case 11:

/* Line 1806 of yacc.c  */
#line 147 "src/parser.y"
    { (yyval) = CN( expression_list_n, 1, (yyvsp[(1) - (1)]) ); }
    break;

  case 12:

/* Line 1806 of yacc.c  */
#line 148 "src/parser.y"
    { (yyval) = CN( expression_list_n, 2, (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]) ); }
    break;

  case 13:

/* Line 1806 of yacc.c  */
#line 149 "src/parser.y"
    { (yyval) = CN( parameter_list_n, 1, (yyvsp[(1) - (1)]) ); }
    break;

  case 14:

/* Line 1806 of yacc.c  */
#line 150 "src/parser.y"
    { (yyval) = NULL; }
    break;

  case 15:

/* Line 1806 of yacc.c  */
#line 151 "src/parser.y"
    { (yyval) = CN( argument_list_n, 1, (yyvsp[(1) - (1)]) ); }
    break;

  case 16:

/* Line 1806 of yacc.c  */
#line 152 "src/parser.y"
    { (yyval) = NULL; }
    break;

  case 17:

/* Line 1806 of yacc.c  */
#line 153 "src/parser.y"
    { (yyval) = CN( class_list_n, 1, (yyvsp[(1) - (1)]) ); }
    break;

  case 18:

/* Line 1806 of yacc.c  */
#line 154 "src/parser.y"
    { (yyval) = CN( class_list_n, 2, (yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]) ); }
    break;

  case 19:

/* Line 1806 of yacc.c  */
#line 155 "src/parser.y"
    { (yyval) = CN( class_n, 3, (yyvsp[(2) - (7)]), (yyvsp[(4) - (7)]), (yyvsp[(6) - (7)]) ); }
    break;

  case 20:

/* Line 1806 of yacc.c  */
#line 156 "src/parser.y"
    { (yyval) = CN( declaration_list_n, 2, (yyvsp[(1) - (3)]), (yyvsp[(2) - (3)])); }
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 157 "src/parser.y"
    { (yyval) = NULL ;}
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 158 "src/parser.y"
    { (yyval) = CN( statement_n, 1, (yyvsp[(1) - (2)]) ); }
    break;

  case 23:

/* Line 1806 of yacc.c  */
#line 159 "src/parser.y"
    { (yyval) = CN( statement_n, 1, (yyvsp[(1) - (2)]) ); }
    break;

  case 24:

/* Line 1806 of yacc.c  */
#line 160 "src/parser.y"
    { (yyval) = CN( statement_n, 1, (yyvsp[(1) - (2)]) ); }
    break;

  case 25:

/* Line 1806 of yacc.c  */
#line 161 "src/parser.y"
    { (yyval) = CN( statement_n, 1, (yyvsp[(1) - (2)]) ); }
    break;

  case 26:

/* Line 1806 of yacc.c  */
#line 162 "src/parser.y"
    { (yyval) = CN( statement_n, 1, (yyvsp[(1) - (2)]) ); }
    break;

  case 27:

/* Line 1806 of yacc.c  */
#line 163 "src/parser.y"
    { (yyval) = CN( statement_n, 1, (yyvsp[(1) - (2)]) ); }
    break;

  case 28:

/* Line 1806 of yacc.c  */
#line 164 "src/parser.y"
    { (yyval) = CN( statement_n, 1, (yyvsp[(1) - (2)]) ); }
    break;

  case 29:

/* Line 1806 of yacc.c  */
#line 165 "src/parser.y"
    { (yyval) = CN( declaration_statement_n, 2, (yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); }
    break;

  case 30:

/* Line 1806 of yacc.c  */
#line 166 "src/parser.y"
    { (yyval) = CN( assignment_statement_n, 2, (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]) ); }
    break;

  case 31:

/* Line 1806 of yacc.c  */
#line 167 "src/parser.y"
    { (yyval) = CN( if_statement_n, 3, (yyvsp[(2) - (7)]), (yyvsp[(4) - (7)]), (yyvsp[(6) - (7)]) ); }
    break;

  case 32:

/* Line 1806 of yacc.c  */
#line 168 "src/parser.y"
    { (yyval) = CN( if_statement_n, 2, (yyvsp[(2) - (5)]), (yyvsp[(4) - (5)]) ); }
    break;

  case 33:

/* Line 1806 of yacc.c  */
#line 169 "src/parser.y"
    { (yyval) = CN( while_statement_n, 2, (yyvsp[(2) - (5)]), (yyvsp[(4) - (5)]) ); }
    break;

  case 34:

/* Line 1806 of yacc.c  */
#line 170 "src/parser.y"
    { (yyval) = CN( return_statement_n, 1, (yyvsp[(2) - (2)]) ); }
    break;

  case 35:

/* Line 1806 of yacc.c  */
#line 171 "src/parser.y"
    { (yyval) = CN( print_statement_n, 1, (yyvsp[(2) - (2)]) ); }
    break;

  case 36:

/* Line 1806 of yacc.c  */
#line 172 "src/parser.y"
    { (yyval) = CNE( expression_n, constant_e, 1, (yyvsp[(1) - (1)])); }
    break;

  case 37:

/* Line 1806 of yacc.c  */
#line 173 "src/parser.y"
    { (yyval) = CNE( expression_n, add_e, 2, (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); }
    break;

  case 38:

/* Line 1806 of yacc.c  */
#line 174 "src/parser.y"
    { (yyval) = CNE( expression_n, sub_e, 2, (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); }
    break;

  case 39:

/* Line 1806 of yacc.c  */
#line 175 "src/parser.y"
    { (yyval) = CNE( expression_n, mul_e, 2, (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); }
    break;

  case 40:

/* Line 1806 of yacc.c  */
#line 176 "src/parser.y"
    { (yyval) = CNE( expression_n, div_e, 2, (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); }
    break;

  case 41:

/* Line 1806 of yacc.c  */
#line 177 "src/parser.y"
    { (yyval) = CNE( expression_n, less_e, 2, (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); }
    break;

  case 42:

/* Line 1806 of yacc.c  */
#line 178 "src/parser.y"
    { (yyval) = CNE( expression_n, greater_e, 2, (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); }
    break;

  case 43:

/* Line 1806 of yacc.c  */
#line 179 "src/parser.y"
    { (yyval) = CNE( expression_n, equal_e, 2, (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); }
    break;

  case 44:

/* Line 1806 of yacc.c  */
#line 180 "src/parser.y"
    { (yyval) = CNE( expression_n, nequal_e, 2, (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); }
    break;

  case 45:

/* Line 1806 of yacc.c  */
#line 181 "src/parser.y"
    { (yyval) = CNE( expression_n, gequal_e, 2, (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); }
    break;

  case 46:

/* Line 1806 of yacc.c  */
#line 182 "src/parser.y"
    { (yyval) = CNE( expression_n, lequal_e, 2, (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); }
    break;

  case 47:

/* Line 1806 of yacc.c  */
#line 183 "src/parser.y"
    { (yyval) = CNE( expression_n, and_e, 2, (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); }
    break;

  case 48:

/* Line 1806 of yacc.c  */
#line 184 "src/parser.y"
    { (yyval) = CNE( expression_n, or_e, 2, (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); }
    break;

  case 49:

/* Line 1806 of yacc.c  */
#line 185 "src/parser.y"
    { (yyval) = CNE( expression_n, uminus_e, 1, (yyvsp[(2) - (2)]) ); }
    break;

  case 50:

/* Line 1806 of yacc.c  */
#line 186 "src/parser.y"
    { (yyval) = CNE( expression_n, not_e, 1, (yyvsp[(2) - (2)]) ); }
    break;

  case 51:

/* Line 1806 of yacc.c  */
#line 187 "src/parser.y"
    { (yyval) = CNE( expression_n, class_field_e, 1, (yyvsp[(2) - (3)]) ); }
    break;

  case 52:

/* Line 1806 of yacc.c  */
#line 188 "src/parser.y"
    { (yyval) = CNE( expression_n, func_call_e, 1, (yyvsp[(1) - (1)])); }
    break;

  case 53:

/* Line 1806 of yacc.c  */
#line 189 "src/parser.y"
    { (yyval) = CNE( expression_n, this_e, 0); }
    break;

  case 54:

/* Line 1806 of yacc.c  */
#line 190 "src/parser.y"
    { (yyval) = CNE( expression_n, variable_e, 1, (yyvsp[(1) - (1)]) ); }
    break;

  case 55:

/* Line 1806 of yacc.c  */
#line 191 "src/parser.y"
    { (yyval) = CNE( expression_n, new_e, 1, (yyvsp[(2) - (2)])); }
    break;

  case 56:

/* Line 1806 of yacc.c  */
#line 192 "src/parser.y"
    { (yyval) = CNE( expression_n, meth_call_e, 2, (yyvsp[(1) - (4)]), (yyvsp[(3) - (4)])); }
    break;

  case 57:

/* Line 1806 of yacc.c  */
#line 193 "src/parser.y"
    { (yyval) = CNE( expression_n, meth_call_e, 3, (yyvsp[(1) - (6)]), (yyvsp[(3) - (6)]), (yyvsp[(5) - (6)])); }
    break;

  case 58:

/* Line 1806 of yacc.c  */
#line 194 "src/parser.y"
    { (yyval) = CNE( expression_n, variable_e, 1, (yyvsp[(1) - (1)])); }
    break;

  case 59:

/* Line 1806 of yacc.c  */
#line 195 "src/parser.y"
    { (yyval) = CNE( expression_n, variable_e, 2, (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); }
    break;

  case 60:

/* Line 1806 of yacc.c  */
#line 196 "src/parser.y"
    { (yyval) = CN(constant_n, 0); (yyval)->bool_const = true; (yyval)->data_type.base_type = BOOL_TYPE; }
    break;

  case 61:

/* Line 1806 of yacc.c  */
#line 197 "src/parser.y"
    { (yyval) = CN(constant_n, 0); (yyval)->bool_const = false; (yyval)->data_type.base_type = BOOL_TYPE; }
    break;

  case 62:

/* Line 1806 of yacc.c  */
#line 198 "src/parser.y"
    { (yyval) = CN(constant_n, 0); SetInteger((yyval), strdup(yytext)); }
    break;

  case 63:

/* Line 1806 of yacc.c  */
#line 199 "src/parser.y"
    { (yyval) = CN(constant_n, 0); SetFloat((yyval), strdup(yytext)); }
    break;

  case 64:

/* Line 1806 of yacc.c  */
#line 200 "src/parser.y"
    { (yyval) = CN(constant_n, 0); SetString((yyval), strdup(yytext)); }
    break;

  case 65:

/* Line 1806 of yacc.c  */
#line 201 "src/parser.y"
    { (yyval) = CNT(type_n, INT_TYPE, 0); }
    break;

  case 66:

/* Line 1806 of yacc.c  */
#line 202 "src/parser.y"
    { (yyval) = CNT(type_n, FLOAT_TYPE, 0); }
    break;

  case 67:

/* Line 1806 of yacc.c  */
#line 203 "src/parser.y"
    { (yyval) = CNT(type_n, BOOL_TYPE, 0); }
    break;

  case 68:

/* Line 1806 of yacc.c  */
#line 204 "src/parser.y"
    { (yyval) = CNT(type_n, VOID_TYPE, 0); }
    break;

  case 69:

/* Line 1806 of yacc.c  */
#line 205 "src/parser.y"
    { (yyval) = CNT(type_n, CLASS_TYPE, 1, (yyvsp[(1) - (1)])); }
    break;

  case 70:

/* Line 1806 of yacc.c  */
#line 206 "src/parser.y"
    { (yyval) = CNL(variable_n, strdup(yytext), 0); }
    break;



/* Line 1806 of yacc.c  */
#line 2138 "y.tab.c"
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

  *++yyvsp = yylval;


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

#if !defined(yyoverflow) || YYERROR_VERBOSE
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



/* Line 2067 of yacc.c  */
#line 208 "src/parser.y"
 

/*
 * This function is called with an error description when parsing fails.
 * Serious error diagnosis requires a lot of code (and imagination), so in the
 * interest of keeping this project on a manageable scale, we just chuck the
 * message/line number on the error stream and stop dead.
 */
int
yyerror ( const char *error )
{
    fprintf ( stderr, "\tError: %s detected at line %d with yytext: %s\n", error, yylineno, yytext );
    exit ( EXIT_FAILURE );
}

