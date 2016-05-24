/* original parser id follows */
/* yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93" */
/* (use YYMAJOR/YYMINOR for ifdefs dependent on parser version) */

#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYPATCH 20150711

#define YYEMPTY        (-1)
#define yyclearin      (yychar = YYEMPTY)
#define yyerrok        (yyerrflag = 0)
#define YYRECOVERING() (yyerrflag != 0)
#define YYENOMEM       (-2)
#define YYEOF          0
#define YYPREFIX "yy"

#define YYPURE 0

#line 2 "zu_parser.y"
/* $Id: zu_parser.y,v 1.2 2016/03/16 22:16:34 ist169481 Exp $*/
/*-- don't change *any* of these: if you do, you'll break the compiler.*/
#include <cdk/compiler.h>
#include "ast/all.h"
#define LINE       compiler->scanner()->lineno()
#define yylex()    compiler->scanner()->scan()
#define yyerror(s) compiler->scanner()->error(s)
#define YYPARSE_PARAM_TYPE std::shared_ptr<cdk::compiler>
#define YYPARSE_PARAM      compiler
/*-- don't change *any* of these --- END!*/
#line 14 "zu_parser.y"
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
typedef union {
  int                 				 i;	/* integer value */
  double              				 d;
  std::string         				*s;	/* symbol name or string literal */
  cdk::basic_node     				*node;	/* node pointer */
  cdk::sequence_node  				*sequence;
  cdk::expression_node				*expression;
  zu::function_declaration_node 		*function;
  zu::block_node				*block;
  zu::lvalue_node				*lvalue;
  basic_type					*ztype;
} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
#line 74 "zu_parser.y"
/*-- The rules below will be included in yyparse, the main parsing function.*/
#line 54 "zu_parser.tab.c"

/* compatibility with bison */
#ifdef YYPARSE_PARAM
/* compatibility with FreeBSD */
# ifdef YYPARSE_PARAM_TYPE
#  define YYPARSE_DECL() yyparse(YYPARSE_PARAM_TYPE YYPARSE_PARAM)
# else
#  define YYPARSE_DECL() yyparse(void *YYPARSE_PARAM)
# endif
#else
# define YYPARSE_DECL() yyparse(void)
#endif

/* Parameters sent to lex. */
#ifdef YYLEX_PARAM
# define YYLEX_DECL() yylex(void *YYLEX_PARAM)
# define YYLEX yylex(YYLEX_PARAM)
#else
# define YYLEX_DECL() yylex(void)
# define YYLEX yylex()
#endif

/* Parameters sent to yyerror. */
#ifndef YYERROR_DECL
#define YYERROR_DECL() yyerror(const char *s)
#endif
#ifndef YYERROR_CALL
#define YYERROR_CALL(msg) yyerror(msg)
#endif

extern int YYPARSE_DECL();

#define tBREAK 257
#define tCONTINUE 258
#define tRETURN 259
#define tTYPE 260
#define tPRINTLN 261
#define tINTEGER 262
#define tDOUBLE 263
#define tIDENTIFIER 264
#define tSTRING 265
#define tIFX 266
#define tELSEX 267
#define tFDEC 268
#define tGEN 269
#define tEQ 270
#define tNE 271
#define tGE 272
#define tLE 273
#define tUNARY 274
#define apply 275
#define YYERRCODE 256
typedef short YYINT;
static const YYINT yylhs[] = {                           -1,
    0,    0,    5,    5,    1,    1,    1,    6,    6,    7,
    7,    2,    2,    2,    2,    2,    2,    2,    2,    2,
   11,   11,   11,   11,   11,    3,    3,   15,   15,   15,
   15,   15,   15,   15,   15,   15,   18,   18,   18,   21,
   21,   10,   10,   10,    4,    4,    8,    8,   20,   20,
   20,   20,   14,   14,   14,   14,   12,   12,   12,   13,
   13,   16,   16,   16,   16,   16,   16,   16,   16,   16,
   16,   16,   16,   16,   16,   16,   16,   16,   16,   16,
   16,   16,   16,   16,   16,   16,   19,   19,   19,   19,
   17,    9,    9,    9,
};
static const YYINT yylen[] = {                            2,
    1,    0,    1,    2,    2,    1,    2,    1,    3,    1,
    2,    2,    2,    2,    1,    1,    1,    1,    1,    1,
    3,    5,    3,    5,    1,    2,    4,    7,    5,    5,
    8,    6,    6,    8,    6,    6,    1,    1,    1,    1,
    2,    1,    3,    0,    2,    4,    2,    3,    1,    1,
    1,    3,    4,    3,    3,    2,    5,    5,    7,    8,
    8,    1,    1,    3,    3,    3,    3,    3,    3,    3,
    3,    3,    3,    3,    3,    3,    2,    2,    2,    1,
    3,    3,    1,    2,    3,    1,    1,    4,    6,    4,
    4,    3,    1,    0,
};
static const YYINT yydefred[] = {                         0,
    0,   50,    0,   49,   51,    0,    3,   25,    0,    0,
    0,    0,    0,    0,    4,    5,    0,    7,    0,   52,
    0,    0,    0,   15,   16,   17,   37,   38,    0,   40,
    0,    0,    0,    0,    0,   86,   56,   80,   10,    0,
    0,    0,   18,   19,   20,    0,    0,   62,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   77,   79,   78,    0,    0,    0,    8,    0,
    0,   47,   55,   11,   54,    0,    0,   14,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   12,   13,    0,    0,    0,   84,    0,   41,    0,
    0,    0,    0,    0,    0,    0,   30,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   48,   53,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   66,   67,   68,    0,    0,    0,    0,    0,
    0,    0,    0,   43,    0,   33,   36,   91,   81,    0,
    0,    9,    0,    0,    0,    0,    0,    0,   90,   88,
    0,    0,    0,    0,    0,    0,    0,    0,   57,   28,
    0,    0,   89,    0,    0,    0,   31,   34,    0,    0,
   59,   61,   60,
};
static const YYINT yydgoto[] = {                          6,
    7,   39,    8,   56,    9,   67,   41,   42,   68,   57,
   10,   43,   44,   45,   11,   46,   47,   48,   49,   58,
   51,
};
static const YYINT yysindex[] = {                       394,
  439,    0, -264,    0,    0,    0,    0,    0,  394,  -55,
 -115, -246,  -30,  -16,    0,    0,  -10,    0,  198,    0,
  439,  -18,   12,    0,    0,    0,    0,    0,   19,    0,
  733,  733,  733,  733,  347,    0,    0,    0,    0,    5,
  686,   63,    0,    0,    0,  -31,   -4,    0,  -40, -167,
 -158,  733,  439,  -21,   65,   77,   92,  -97,  439,  439,
  733,  733,    0,    0,    0,  447,  -39,   93,    0,  522,
  -93,    0,    0,    0,    0,   90,  711,    0,  733,  733,
  733,  733,  733,  733,  733,  733,  733,  733,  733,  733,
  733,    0,    0,  733,  733,  733,    0,  124,    0,  492,
  146,  733,  439,  733,  439,  439,    0,  135,  162,  163,
   34,  492,  558,  104,  733,  439,  733,  733,  -22,  149,
    0,    0,  685,  233,  699,  699,  413,  413,  413,  413,
  108,  108,    0,    0,    0,  597,  492,  611,  161,  492,
  174,  492,  186,    0,  733,    0,    0,    0,    0,  733,
  103,    0,  107,  492,  763,  763,  167,  171,    0,    0,
   79,  185,  189,  492,  646,  733,  733,  193,    0,    0,
   79,   79,    0,   67,   75,  763,    0,    0,  763,  763,
    0,    0,    0,
};
static const YYINT yyrindex[] = {                       267,
    0,    0,    0,    0,    0,    0,    0,    0,  277,    0,
  386,    0,    0,    0,    0,    0,    0,    0,  222,    0,
  257,    0,    0,    0,    0,    0,    0,    0,   29,    0,
    0,    0,    0,    0,  134,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   97,    0,  132,    0,
    1,    0,  257,  244,  248,  271,    0,    0,  257,  257,
  117,    0,    0,    0,    0,    0,    0,    0,    0,  140,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  222,    0,  154,
    0,    0,  257,    0,  257,  257,    0,  357,    0,    0,
    0,   87,    0,  164,  134,    0,  134,    0,  249,  170,
    0,    0,   24,  781,  225,  424,  315,  319,  356,  407,
  272,  302,    0,    0,    0,    0,   36,    0,   49,  220,
    0,  224,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  292,    0,    0,  245,  270,    0,    0,
    0,  183,  200,  365,    0,   88,   88,  726,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,
};
static const YYINT yygindex[] = {                         0,
  310,  520,   62,    0,    0,    0,  282,    0,   -3,  -50,
  -20,    0,    0,  326,    0,  971,    0,   73,    0,  101,
    0,
};
#define YYTABLESIZE 1138
static const YYINT yytable[] = {                         14,
   39,   93,  101,   16,  116,   91,   80,   17,  109,  110,
   89,   87,  156,   88,   69,   90,   22,   19,  103,  115,
   95,   59,   97,   21,    4,    5,    2,   92,   86,   34,
   85,   20,   32,   39,   33,   39,   39,   39,   39,  102,
  155,   39,   39,   39,   39,   39,   23,   39,   29,    1,
   96,   60,  141,   38,  143,  144,   75,  111,   61,   39,
   39,   87,   39,   72,   75,   87,   87,   75,   85,   87,
   87,   87,   87,   87,  148,   87,   85,  118,   40,   85,
   35,   29,   75,   29,   29,   29,   94,   87,   87,   87,
   87,   87,   79,   39,   85,  152,   98,    4,    5,    2,
   12,   13,   34,   76,  105,   32,   99,   33,   29,   12,
  118,  151,   17,  153,   37,   31,   75,   50,  118,   87,
  106,   87,    1,   39,   39,  104,   38,   93,   85,   63,
   93,   94,  107,   63,   63,   71,  118,   63,   63,   63,
   63,   63,   50,   63,   91,   93,  118,   75,  121,   89,
  118,  117,   87,   35,   90,   63,   63,   94,   63,  179,
   94,  166,  174,  175,   83,  167,  108,  180,   83,   83,
  120,   29,   83,   83,   83,   83,   83,   94,   83,   93,
   94,  157,   32,   93,   52,   17,  139,   75,   31,   63,
   83,   83,   94,   83,  150,  145,   82,   27,   93,   35,
   82,   82,  146,  147,   82,   82,   82,   82,   82,   52,
   82,  158,   27,   26,  162,   32,   71,   32,   32,   32,
   63,  161,   82,   82,   83,   82,  163,  102,   26,   78,
   54,  104,   35,  170,   35,   35,   35,   53,   81,   82,
   83,   84,   32,  177,  178,  171,   24,   25,   26,  172,
  176,   27,   28,   29,   30,   83,   82,   73,   52,   35,
   55,   39,   73,   22,   36,   73,    2,   24,   73,   91,
   39,   39,   39,   39,   89,   87,    1,   88,   22,   90,
   26,   81,   24,   73,   75,   81,   81,   82,   21,   87,
   81,   81,   86,   81,   85,   81,   85,   44,   87,   87,
   87,   87,   21,   21,   64,   32,   23,   81,   81,   64,
   81,   42,   64,   23,   64,   64,   64,   73,   15,   24,
   25,   26,   35,   77,   27,   28,   29,   30,   23,    0,
   64,   64,   92,   64,   65,   92,   18,   36,    0,   65,
   27,   28,   65,   30,   65,   65,   65,   71,   73,    0,
   92,   72,   71,    0,    0,   71,   72,   63,   71,   72,
   65,   65,   72,   65,   64,    0,   63,   63,   63,   63,
    0,    0,   81,   71,   71,    0,   71,   72,   72,    0,
   72,    4,    5,    2,   92,    6,   34,    0,   70,   32,
    0,   33,   83,   70,   65,   64,   70,   45,    0,   70,
   45,   83,   83,   83,   83,   46,    1,   71,   46,    0,
   38,   72,    0,    0,   70,   70,    0,   70,    6,    0,
    6,    6,    6,    0,   82,   65,    3,    0,    4,    5,
    2,    0,    0,   82,   82,   82,   82,   62,   71,   69,
    0,    0,   72,    0,   69,    6,    0,   69,   70,   91,
   69,    0,    0,    1,   89,   87,   74,   88,    0,   90,
    0,   74,    0,    0,   74,   69,   69,   74,   69,    0,
    0,    0,   31,    4,    5,    2,    0,    0,    0,   70,
    0,    0,   74,   91,   80,   73,    0,  114,   89,   87,
    0,   88,    0,   90,   73,   73,    0,    0,    1,   69,
    0,    0,   81,   82,   83,   84,   86,    0,   85,   81,
    0,    0,    0,    0,    0,    0,   74,    0,   81,   81,
   81,   81,    0,    0,    0,    0,    0,    0,   91,   80,
   69,    0,   64,   89,   87,    0,   88,    0,   90,    0,
    0,   64,   64,   64,   64,    0,    0,   74,    0,    0,
    0,   86,    0,   85,    0,    0,    0,    0,   91,   80,
   74,    0,   65,   89,   87,    0,   88,    0,   90,    0,
   79,   65,   65,   65,   65,   71,    0,    0,    0,   72,
    0,   86,    0,   85,   71,   71,   71,   71,   72,   72,
   72,   72,    0,    0,   91,   80,   74,    0,    0,   89,
   87,    0,   88,    0,   90,    0,    0,    0,   27,   28,
   29,   30,    0,    0,  119,   79,   70,   86,    0,   85,
    0,   36,    0,    0,    0,   70,   70,   70,   70,    0,
    0,    0,    0,   91,   80,    0,    0,    0,   89,   87,
    0,   88,    0,   90,    0,   79,    0,   91,   80,    0,
  149,    0,   89,   87,    0,   88,   86,   90,   85,    0,
    0,    0,    0,    0,    0,    0,    0,   69,    0,    0,
   86,    0,   85,    0,  168,  169,   69,   69,   69,   69,
    0,   79,   91,   80,   74,    0,    0,   89,   87,  159,
   88,    0,   90,   74,   74,  181,    0,    0,  182,  183,
    0,    0,    0,  160,    0,   86,    0,   85,    0,    0,
    0,    0,    0,    0,    0,    0,   81,   82,   83,   84,
   79,   91,   80,    0,    0,   34,   89,   87,   32,   88,
   33,   90,    0,    0,   79,   91,    0,    0,  173,    0,
   89,   87,    0,   88,   86,   90,   85,    0,    0,   38,
   34,    0,    0,   32,    0,   33,    0,    0,   86,    0,
   85,   81,   82,   83,   84,   58,    0,    0,   58,   79,
   58,    0,   34,    0,   38,   32,   35,   33,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   58,
    0,   81,   82,   83,   84,    0,   38,    0,    0,    0,
    0,   35,   34,    0,    0,   32,    0,   33,   17,    0,
   73,   31,    0,   76,    0,    0,   58,    0,   76,    0,
    0,   76,    0,   62,   76,    0,   38,   81,   82,   83,
   84,    0,    0,   17,    0,  122,   31,    0,    0,   76,
    0,    0,    0,    0,    0,    0,    0,    0,   58,    0,
   58,   58,    0,   35,    0,    0,    0,    0,   31,    0,
    0,    0,    0,    0,    0,    0,   81,   82,   83,   84,
    0,    0,    0,   76,    0,    0,    0,    0,    0,    0,
   81,   82,   83,   84,    0,   17,    0,    0,   31,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,   76,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   81,   82,   83,   84,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   24,   25,   26,    0,    0,   27,   28,   29,
   30,    0,    0,    0,   81,   82,   83,   84,    0,    0,
   36,    0,    0,    0,    0,    0,    0,   24,   25,   26,
   83,   84,   27,   28,   29,   30,    0,    0,    0,    0,
    0,    0,   58,   58,   58,   36,    0,   58,   58,   58,
   58,    0,    0,    0,   27,   28,   29,   30,    0,    0,
   58,   63,   64,   65,   66,   70,    0,   36,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   24,
   25,   26,  100,    0,   27,   28,   29,   30,    0,    0,
    0,  112,  113,    0,    0,    0,    0,   36,    0,    0,
    0,   76,    0,    0,    0,    0,    0,    0,    0,  123,
  124,  125,  126,  127,  128,  129,  130,  131,  132,  133,
  134,  135,    0,    0,  136,  137,  138,    0,    0,    0,
    0,    0,  140,    0,  142,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  112,    0,  112,  154,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  164,    0,    0,    0,    0,
  165,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  112,  112,
};
static const YYINT yycheck[] = {                        264,
    0,   33,   53,   59,   44,   37,   38,  123,   59,   60,
   42,   43,   35,   45,   35,   47,   33,  264,   40,   59,
   61,   40,   63,   40,   35,   36,   37,   59,   60,   40,
   62,   62,   43,   33,   45,   35,   36,   37,   38,   61,
   63,   41,   42,   43,   44,   45,   63,   47,    0,   60,
   91,   40,  103,   64,  105,  106,   33,   61,   40,   59,
   60,   33,   62,   59,   41,   37,   38,   44,   33,   41,
   42,   43,   44,   45,   41,   47,   41,   44,   17,   44,
   91,   33,   59,   35,   36,   37,   91,   59,   60,   61,
   62,   63,  124,   93,   59,  116,  264,   35,   36,   37,
    0,    1,   40,   42,   40,   43,  265,   45,   60,    9,
   44,  115,  123,  117,  125,  126,   93,   17,   44,   91,
   44,   93,   60,  123,  124,   61,   64,   41,   93,   33,
   44,   44,   41,   37,   38,   35,   44,   41,   42,   43,
   44,   45,   42,   47,   37,   59,   44,  124,   59,   42,
   44,   59,  124,   91,   47,   59,   60,   41,   62,   93,
   44,   59,  166,  167,   33,   59,  264,   93,   37,   38,
  264,  123,   41,   42,   43,   44,   45,   44,   47,   93,
   93,   33,    0,   44,   61,  123,   41,  125,  126,   93,
   59,   60,   59,   62,   91,   61,   33,   44,   59,    0,
   37,   38,   41,   41,   41,   42,   43,   44,   45,   61,
   47,   63,   59,   44,   41,   33,  116,   35,   36,   37,
  124,   61,   59,   60,   93,   62,   41,   61,   59,  261,
   33,   61,   33,  161,   35,   36,   37,   40,  270,  271,
  272,  273,   60,  171,  172,   61,  257,  258,  259,   61,
   58,  262,  263,  264,  265,  124,   93,   33,   61,   60,
   63,  261,   38,   44,  275,   41,    0,   44,   44,   37,
  270,  271,  272,  273,   42,   43,    0,   45,   59,   47,
   59,   33,   59,   59,  261,   37,   38,  124,   44,  261,
   42,   43,   60,   45,   62,   47,  261,   41,  270,  271,
  272,  273,   59,   59,   33,  123,   59,   59,   60,   38,
   62,   41,   41,   44,   43,   44,   45,   93,    9,  257,
  258,  259,  123,   42,  262,  263,  264,  265,   59,   -1,
   59,   60,   41,   62,   33,   44,   11,  275,   -1,   38,
  262,  263,   41,  265,   43,   44,   45,   33,  124,   -1,
   59,   33,   38,   -1,   -1,   41,   38,  261,   44,   41,
   59,   60,   44,   62,   93,   -1,  270,  271,  272,  273,
   -1,   -1,  124,   59,   60,   -1,   62,   59,   60,   -1,
   62,   35,   36,   37,   93,    0,   40,   -1,   33,   43,
   -1,   45,  261,   38,   93,  124,   41,   41,   -1,   44,
   44,  270,  271,  272,  273,   41,   60,   93,   44,   -1,
   64,   93,   -1,   -1,   59,   60,   -1,   62,   33,   -1,
   35,   36,   37,   -1,  261,  124,   33,   -1,   35,   36,
   37,   -1,   -1,  270,  271,  272,  273,   91,  124,   33,
   -1,   -1,  124,   -1,   38,   60,   -1,   41,   93,   37,
   44,   -1,   -1,   60,   42,   43,   33,   45,   -1,   47,
   -1,   38,   -1,   -1,   41,   59,   60,   44,   62,   -1,
   -1,   -1,  126,   35,   36,   37,   -1,   -1,   -1,  124,
   -1,   -1,   59,   37,   38,  261,   -1,   41,   42,   43,
   -1,   45,   -1,   47,  270,  271,   -1,   -1,   60,   93,
   -1,   -1,  270,  271,  272,  273,   60,   -1,   62,  261,
   -1,   -1,   -1,   -1,   -1,   -1,   93,   -1,  270,  271,
  272,  273,   -1,   -1,   -1,   -1,   -1,   -1,   37,   38,
  124,   -1,  261,   42,   43,   -1,   45,   -1,   47,   -1,
   -1,  270,  271,  272,  273,   -1,   -1,  124,   -1,   -1,
   -1,   60,   -1,   62,   -1,   -1,   -1,   -1,   37,   38,
   41,   -1,  261,   42,   43,   -1,   45,   -1,   47,   -1,
  124,  270,  271,  272,  273,  261,   -1,   -1,   -1,  261,
   -1,   60,   -1,   62,  270,  271,  272,  273,  270,  271,
  272,  273,   -1,   -1,   37,   38,   77,   -1,   -1,   42,
   43,   -1,   45,   -1,   47,   -1,   -1,   -1,  262,  263,
  264,  265,   -1,   -1,   93,  124,  261,   60,   -1,   62,
   -1,  275,   -1,   -1,   -1,  270,  271,  272,  273,   -1,
   -1,   -1,   -1,   37,   38,   -1,   -1,   -1,   42,   43,
   -1,   45,   -1,   47,   -1,  124,   -1,   37,   38,   -1,
   93,   -1,   42,   43,   -1,   45,   60,   47,   62,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  261,   -1,   -1,
   60,   -1,   62,   -1,  155,  156,  270,  271,  272,  273,
   -1,  124,   37,   38,  261,   -1,   -1,   42,   43,   93,
   45,   -1,   47,  270,  271,  176,   -1,   -1,  179,  180,
   -1,   -1,   -1,   93,   -1,   60,   -1,   62,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  270,  271,  272,  273,
  124,   37,   38,   -1,   -1,   40,   42,   43,   43,   45,
   45,   47,   -1,   -1,  124,   37,   -1,   -1,   93,   -1,
   42,   43,   -1,   45,   60,   47,   62,   -1,   -1,   64,
   40,   -1,   -1,   43,   -1,   45,   -1,   -1,   60,   -1,
   62,  270,  271,  272,  273,   40,   -1,   -1,   43,  124,
   45,   -1,   40,   -1,   64,   43,   91,   45,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   64,
   -1,  270,  271,  272,  273,   -1,   64,   -1,   -1,   -1,
   -1,   91,   40,   -1,   -1,   43,   -1,   45,  123,   -1,
  125,  126,   -1,   33,   -1,   -1,   91,   -1,   38,   -1,
   -1,   41,   -1,   91,   44,   -1,   64,  270,  271,  272,
  273,   -1,   -1,  123,   -1,  125,  126,   -1,   -1,   59,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  123,   -1,
  125,  126,   -1,   91,   -1,   -1,   -1,   -1,  126,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  270,  271,  272,  273,
   -1,   -1,   -1,   93,   -1,   -1,   -1,   -1,   -1,   -1,
  270,  271,  272,  273,   -1,  123,   -1,   -1,  126,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  124,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  270,  271,  272,  273,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  257,  258,  259,   -1,   -1,  262,  263,  264,
  265,   -1,   -1,   -1,  270,  271,  272,  273,   -1,   -1,
  275,   -1,   -1,   -1,   -1,   -1,   -1,  257,  258,  259,
  272,  273,  262,  263,  264,  265,   -1,   -1,   -1,   -1,
   -1,   -1,  257,  258,  259,  275,   -1,  262,  263,  264,
  265,   -1,   -1,   -1,  262,  263,  264,  265,   -1,   -1,
  275,   31,   32,   33,   34,   35,   -1,  275,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  257,
  258,  259,   52,   -1,  262,  263,  264,  265,   -1,   -1,
   -1,   61,   62,   -1,   -1,   -1,   -1,  275,   -1,   -1,
   -1,  261,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   79,
   80,   81,   82,   83,   84,   85,   86,   87,   88,   89,
   90,   91,   -1,   -1,   94,   95,   96,   -1,   -1,   -1,
   -1,   -1,  102,   -1,  104,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  115,   -1,  117,  118,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  145,   -1,   -1,   -1,   -1,
  150,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  166,  167,
};
#define YYFINAL 6
#ifndef YYDEBUG
#define YYDEBUG 1
#endif
#define YYMAXTOKEN 275
#define YYUNDFTOKEN 299
#define YYTRANSLATE(a) ((a) > YYMAXTOKEN ? YYUNDFTOKEN : (a))
#if YYDEBUG
static const char *const yyname[] = {

"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
"'!'",0,"'#'","'$'","'%'","'&'",0,"'('","')'","'*'","'+'","','","'-'",0,"'/'",0,
0,0,0,0,0,0,0,0,0,"':'","';'","'<'","'='","'>'","'?'","'@'",0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"'['",0,"']'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,"'{'","'|'","'}'","'~'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"tBREAK",
"tCONTINUE","tRETURN","tTYPE","tPRINTLN","tINTEGER","tDOUBLE","tIDENTIFIER",
"tSTRING","tIFX","tELSEX","tFDEC","tGEN","tEQ","tNE","tGE","tLE","tUNARY",
"apply",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"illegal-symbol",
};
static const char *const yyrule[] = {
"$accept : file",
"file : decs",
"file :",
"decs : dec",
"decs : decs dec",
"dec : vdec ';'",
"dec : fdec",
"dec : fdec blk",
"vars : vdec",
"vars : vars ',' vdec",
"itrs : itr",
"itrs : itrs itr",
"itr : expr ';'",
"itr : expr '!'",
"itr : expr tPRINTLN",
"itr : tBREAK",
"itr : tCONTINUE",
"itr : tRETURN",
"itr : cond",
"itr : iter",
"itr : blk",
"vdec : type tIDENTIFIER '!'",
"vdec : type tIDENTIFIER '!' '=' expr",
"vdec : type tIDENTIFIER '?'",
"vdec : type tIDENTIFIER '?' '=' expr",
"vdec : smp_vdec",
"smp_vdec : type tIDENTIFIER",
"smp_vdec : type tIDENTIFIER '=' expr",
"fdec : type tIDENTIFIER '(' fargs ')' '=' lit",
"fdec : type tIDENTIFIER '(' fargs ')'",
"fdec : '!' tIDENTIFIER '(' fargs ')'",
"fdec : type tIDENTIFIER '!' '(' fargs ')' '=' lit",
"fdec : type tIDENTIFIER '!' '(' fargs ')'",
"fdec : '!' tIDENTIFIER '!' '(' fargs ')'",
"fdec : type tIDENTIFIER '?' '(' fargs ')' '=' lit",
"fdec : type tIDENTIFIER '?' '(' fargs ')'",
"fdec : '!' tIDENTIFIER '?' '(' fargs ')'",
"lit : tINTEGER",
"lit : tDOUBLE",
"lit : str",
"str : tSTRING",
"str : str tSTRING",
"fargs : farg",
"fargs : farg ',' fargs",
"fargs :",
"farg : type tIDENTIFIER",
"farg : type tIDENTIFIER '=' expr",
"blk_var : smp_vdec ';'",
"blk_var : blk_var smp_vdec ';'",
"type : '#'",
"type : '%'",
"type : '$'",
"type : '<' type '>'",
"blk : '{' blk_var itrs '}'",
"blk : '{' blk_var '}'",
"blk : '{' itrs '}'",
"blk : '{' '}'",
"cond : '[' expr ']' '#' itr",
"cond : '[' expr ']' '?' itr",
"cond : '[' expr ']' '?' itr ':' itr",
"iter : '[' exprs ';' exprs ';' exprs ']' itr",
"iter : '[' vars ';' exprs ';' exprs ']' itr",
"expr : lit",
"expr : fcal",
"expr : expr '+' expr",
"expr : expr '-' expr",
"expr : expr '*' expr",
"expr : expr '/' expr",
"expr : expr '%' expr",
"expr : expr '<' expr",
"expr : expr '>' expr",
"expr : expr tGE expr",
"expr : expr tLE expr",
"expr : expr tEQ expr",
"expr : expr tNE expr",
"expr : expr '|' expr",
"expr : expr '&' expr",
"expr : '~' expr",
"expr : '-' expr",
"expr : '+' expr",
"expr : '@'",
"expr : '[' expr ']'",
"expr : '(' expr ')'",
"expr : lval",
"expr : lval '?'",
"expr : lval '=' expr",
"expr : apply",
"lval : tIDENTIFIER",
"lval : lval '[' expr ']'",
"lval : '(' expr ')' '[' expr ']'",
"lval : fcal '[' expr ']'",
"fcal : tIDENTIFIER '(' exprs ')'",
"exprs : exprs ',' expr",
"exprs : expr",
"exprs :",

};
#endif

int      yydebug;
int      yynerrs;

int      yyerrflag;
int      yychar;
YYSTYPE  yyval;
YYSTYPE  yylval;

/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH  10000
#endif
#endif

#define YYINITSTACKSIZE 200

typedef struct {
    unsigned stacksize;
    YYINT    *s_base;
    YYINT    *s_mark;
    YYINT    *s_last;
    YYSTYPE  *l_base;
    YYSTYPE  *l_mark;
} YYSTACKDATA;
/* variables for the parser stack */
static YYSTACKDATA yystack;

#if YYDEBUG
#include <stdio.h>		/* needed for printf */
#endif

#include <stdlib.h>	/* needed for malloc, etc */
#include <string.h>	/* needed for memset */

/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(YYSTACKDATA *data)
{
    int i;
    unsigned newsize;
    YYINT *newss;
    YYSTYPE *newvs;

    if ((newsize = data->stacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return YYENOMEM;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = (int) (data->s_mark - data->s_base);
    newss = (YYINT *)realloc(data->s_base, newsize * sizeof(*newss));
    if (newss == 0)
        return YYENOMEM;

    data->s_base = newss;
    data->s_mark = newss + i;

    newvs = (YYSTYPE *)realloc(data->l_base, newsize * sizeof(*newvs));
    if (newvs == 0)
        return YYENOMEM;

    data->l_base = newvs;
    data->l_mark = newvs + i;

    data->stacksize = newsize;
    data->s_last = data->s_base + newsize - 1;
    return 0;
}

#if YYPURE || defined(YY_NO_LEAKS)
static void yyfreestack(YYSTACKDATA *data)
{
    free(data->s_base);
    free(data->l_base);
    memset(data, 0, sizeof(*data));
}
#else
#define yyfreestack(data) /* nothing */
#endif

#define YYABORT  goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR  goto yyerrlab

int
YYPARSE_DECL()
{
    int yym, yyn, yystate;
#if YYDEBUG
    const char *yys;

    if ((yys = getenv("YYDEBUG")) != 0)
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = YYEMPTY;
    yystate = 0;

#if YYPURE
    memset(&yystack, 0, sizeof(yystack));
#endif

    if (yystack.s_base == NULL && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
    yystack.s_mark = yystack.s_base;
    yystack.l_mark = yystack.l_base;
    yystate = 0;
    *yystack.s_mark = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = YYLEX) < 0) yychar = YYEOF;
#if YYDEBUG
        if (yydebug)
        {
            yys = yyname[YYTRANSLATE(yychar)];
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
        {
            goto yyoverflow;
        }
        yystate = yytable[yyn];
        *++yystack.s_mark = yytable[yyn];
        *++yystack.l_mark = yylval;
        yychar = YYEMPTY;
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;

    YYERROR_CALL("syntax error");

    goto yyerrlab;

yyerrlab:
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yystack.s_mark]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yystack.s_mark, yytable[yyn]);
#endif
                if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
                {
                    goto yyoverflow;
                }
                yystate = yytable[yyn];
                *++yystack.s_mark = yytable[yyn];
                *++yystack.l_mark = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yystack.s_mark);
#endif
                if (yystack.s_mark <= yystack.s_base) goto yyabort;
                --yystack.s_mark;
                --yystack.l_mark;
            }
        }
    }
    else
    {
        if (yychar == YYEOF) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = yyname[YYTRANSLATE(yychar)];
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = YYEMPTY;
        goto yyloop;
    }

yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    if (yym)
        yyval = yystack.l_mark[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);
    switch (yyn)
    {
case 1:
#line 79 "zu_parser.y"
	{ compiler->ast( yystack.l_mark[0].sequence ); }
break;
case 2:
#line 80 "zu_parser.y"
	{ compiler->ast(new cdk::nil_node(LINE)); }
break;
case 3:
#line 83 "zu_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE, yystack.l_mark[0].node); }
break;
case 4:
#line 84 "zu_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE, yystack.l_mark[0].node, yystack.l_mark[-1].sequence); }
break;
case 5:
#line 87 "zu_parser.y"
	{ yyval.node = yystack.l_mark[-1].node; }
break;
case 6:
#line 88 "zu_parser.y"
	{ yyval.node = yystack.l_mark[0].function; }
break;
case 7:
#line 89 "zu_parser.y"
	{ yyval.node = new zu::function_body_node(LINE, yystack.l_mark[-1].function, yystack.l_mark[0].block); }
break;
case 8:
#line 92 "zu_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE, yystack.l_mark[0].node); }
break;
case 9:
#line 93 "zu_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE, yystack.l_mark[0].node, yystack.l_mark[-2].sequence); }
break;
case 10:
#line 96 "zu_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE, yystack.l_mark[0].node); }
break;
case 11:
#line 97 "zu_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE, yystack.l_mark[0].node, yystack.l_mark[-1].sequence); }
break;
case 12:
#line 100 "zu_parser.y"
	{ yyval.node = new zu::evaluation_node(LINE, yystack.l_mark[-1].expression); }
break;
case 13:
#line 101 "zu_parser.y"
	{ yyval.node = new zu::print_node(LINE, yystack.l_mark[-1].expression, false); }
break;
case 14:
#line 102 "zu_parser.y"
	{ yyval.node = new zu::print_node(LINE, yystack.l_mark[-1].expression, true); }
break;
case 15:
#line 103 "zu_parser.y"
	{ yyval.node = new zu::break_node(LINE); }
break;
case 16:
#line 104 "zu_parser.y"
	{ yyval.node = new zu::continue_node(LINE); }
break;
case 17:
#line 105 "zu_parser.y"
	{ yyval.node = new zu::return_node(LINE); }
break;
case 18:
#line 106 "zu_parser.y"
	{ yyval.node = yystack.l_mark[0].node; }
break;
case 19:
#line 107 "zu_parser.y"
	{ yyval.node = yystack.l_mark[0].node; }
break;
case 20:
#line 108 "zu_parser.y"
	{ yyval.node = yystack.l_mark[0].block; }
break;
case 21:
#line 111 "zu_parser.y"
	{ yyval.node = new zu::variable_node(LINE, yystack.l_mark[-2].ztype, yystack.l_mark[-1].s, true, false, NULL, false); }
break;
case 22:
#line 112 "zu_parser.y"
	{ yyval.node = new zu::variable_node(LINE, yystack.l_mark[-4].ztype, yystack.l_mark[-3].s, true, false, yystack.l_mark[0].expression, false); }
break;
case 23:
#line 113 "zu_parser.y"
	{ yyval.node = new zu::variable_node(LINE, yystack.l_mark[-2].ztype, yystack.l_mark[-1].s, false, true, NULL, false); }
break;
case 24:
#line 114 "zu_parser.y"
	{ yyval.node = new zu::variable_node(LINE, yystack.l_mark[-4].ztype, yystack.l_mark[-3].s, false, true, yystack.l_mark[0].expression, false); }
break;
case 25:
#line 115 "zu_parser.y"
	{ yyval.node = yystack.l_mark[0].node; }
break;
case 26:
#line 118 "zu_parser.y"
	{ yyval.node = new zu::variable_node(LINE, yystack.l_mark[-1].ztype, yystack.l_mark[0].s, false, false, NULL, false); }
break;
case 27:
#line 119 "zu_parser.y"
	{ yyval.node = new zu::variable_node(LINE, yystack.l_mark[-3].ztype, yystack.l_mark[-2].s, false, false, yystack.l_mark[0].expression, false); }
break;
case 28:
#line 122 "zu_parser.y"
	{ yyval.function = new zu::function_declaration_node(LINE, yystack.l_mark[-6].ztype, yystack.l_mark[-5].s, false, false, yystack.l_mark[-3].sequence, yystack.l_mark[0].expression); }
break;
case 29:
#line 123 "zu_parser.y"
	{ yyval.function = new zu::function_declaration_node(LINE, yystack.l_mark[-4].ztype, yystack.l_mark[-3].s, false, false, yystack.l_mark[-1].sequence, NULL); }
break;
case 30:
#line 124 "zu_parser.y"
	{ yyval.function = new zu::function_declaration_node(LINE, new basic_type(0, basic_type::TYPE_VOID), yystack.l_mark[-3].s, false, false, yystack.l_mark[-1].sequence, NULL); }
break;
case 31:
#line 125 "zu_parser.y"
	{ yyval.function = new zu::function_declaration_node(LINE, yystack.l_mark[-7].ztype, yystack.l_mark[-6].s, true, false, yystack.l_mark[-3].sequence, yystack.l_mark[0].expression); }
break;
case 32:
#line 126 "zu_parser.y"
	{ yyval.function = new zu::function_declaration_node(LINE, yystack.l_mark[-5].ztype, yystack.l_mark[-4].s, true, false, yystack.l_mark[-1].sequence, NULL); }
break;
case 33:
#line 127 "zu_parser.y"
	{ yyval.function = new zu::function_declaration_node(LINE, new basic_type(0, basic_type::TYPE_VOID), yystack.l_mark[-4].s, true, false, yystack.l_mark[-1].sequence, NULL); }
break;
case 34:
#line 128 "zu_parser.y"
	{ yyval.function = new zu::function_declaration_node(LINE, yystack.l_mark[-7].ztype, yystack.l_mark[-6].s, false, true,  yystack.l_mark[-3].sequence, yystack.l_mark[0].expression); }
break;
case 35:
#line 129 "zu_parser.y"
	{ yyval.function = new zu::function_declaration_node(LINE, yystack.l_mark[-5].ztype, yystack.l_mark[-4].s, false, true,  yystack.l_mark[-1].sequence, NULL); }
break;
case 36:
#line 130 "zu_parser.y"
	{ yyval.function = new zu::function_declaration_node(LINE, new basic_type(0, basic_type::TYPE_VOID), yystack.l_mark[-4].s, false, true, yystack.l_mark[-1].sequence, NULL); }
break;
case 37:
#line 133 "zu_parser.y"
	{ yyval.expression = new cdk::integer_node(LINE, yystack.l_mark[0].i); }
break;
case 38:
#line 134 "zu_parser.y"
	{ yyval.expression = new cdk::double_node(LINE, yystack.l_mark[0].d); }
break;
case 39:
#line 135 "zu_parser.y"
	{ yyval.expression = new cdk::string_node(LINE, yystack.l_mark[0].s); }
break;
case 40:
#line 138 "zu_parser.y"
	{ yyval.s = yystack.l_mark[0].s; }
break;
case 41:
#line 139 "zu_parser.y"
	{ yyval.s = new std::string(*yystack.l_mark[-1].s + *yystack.l_mark[0].s); }
break;
case 42:
#line 144 "zu_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE, yystack.l_mark[0].node); }
break;
case 43:
#line 145 "zu_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE, yystack.l_mark[-2].node, yystack.l_mark[0].sequence); }
break;
case 44:
#line 146 "zu_parser.y"
	{ yyval.sequence = NULL; }
break;
case 45:
#line 149 "zu_parser.y"
	{ yyval.node = new zu::variable_node(LINE, yystack.l_mark[-1].ztype, yystack.l_mark[0].s, false, false, NULL, true); }
break;
case 46:
#line 150 "zu_parser.y"
	{ yyval.node = new zu::variable_node(LINE, yystack.l_mark[-3].ztype, yystack.l_mark[-2].s, false, false, yystack.l_mark[0].expression, true); }
break;
case 47:
#line 153 "zu_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE, yystack.l_mark[-1].node); }
break;
case 48:
#line 154 "zu_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE, yystack.l_mark[-1].node, yystack.l_mark[-2].sequence); }
break;
case 49:
#line 159 "zu_parser.y"
	{ yyval.ztype = new basic_type(4, basic_type::TYPE_INT); }
break;
case 50:
#line 160 "zu_parser.y"
	{ yyval.ztype = new basic_type(8, basic_type::TYPE_DOUBLE); }
break;
case 51:
#line 161 "zu_parser.y"
	{ yyval.ztype = new basic_type(4, basic_type::TYPE_STRING); }
break;
case 52:
#line 162 "zu_parser.y"
	{ yyval.ztype = new basic_type(4, basic_type::TYPE_POINTER); yyval.ztype->_subtype = yystack.l_mark[-1].ztype; }
break;
case 53:
#line 165 "zu_parser.y"
	{ yyval.block = new zu::block_node(LINE, yystack.l_mark[-2].sequence, yystack.l_mark[-1].sequence); }
break;
case 54:
#line 166 "zu_parser.y"
	{ yyval.block = new zu::block_node(LINE, yystack.l_mark[-1].sequence, NULL); }
break;
case 55:
#line 167 "zu_parser.y"
	{ yyval.block = new zu::block_node(LINE, NULL, yystack.l_mark[-1].sequence); }
break;
case 56:
#line 168 "zu_parser.y"
	{ yyval.block = new zu::block_node(LINE, NULL, NULL); }
break;
case 57:
#line 171 "zu_parser.y"
	{ yyval.node = new zu::if_node(LINE, yystack.l_mark[-3].expression, yystack.l_mark[0].node); }
break;
case 58:
#line 172 "zu_parser.y"
	{ yyval.node = new zu::if_else_node(LINE, yystack.l_mark[-3].expression, yystack.l_mark[0].node, new cdk::sequence_node(LINE, new cdk::nil_node(LINE))); }
break;
case 59:
#line 173 "zu_parser.y"
	{ yyval.node = new zu::if_else_node(LINE, yystack.l_mark[-5].expression, yystack.l_mark[-2].node, yystack.l_mark[0].node); }
break;
case 60:
#line 176 "zu_parser.y"
	{ yyval.node = new zu::for_node(LINE, yystack.l_mark[-6].sequence, yystack.l_mark[-4].sequence, yystack.l_mark[-2].sequence, yystack.l_mark[0].node); }
break;
case 61:
#line 177 "zu_parser.y"
	{ yyval.node = new zu::for_node(LINE, yystack.l_mark[-6].sequence, yystack.l_mark[-4].sequence, yystack.l_mark[-2].sequence, yystack.l_mark[0].node); }
break;
case 62:
#line 180 "zu_parser.y"
	{ yyval.expression = yystack.l_mark[0].expression; }
break;
case 63:
#line 181 "zu_parser.y"
	{ yyval.expression = yystack.l_mark[0].expression; }
break;
case 64:
#line 182 "zu_parser.y"
	{ yyval.expression = new cdk::add_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 65:
#line 183 "zu_parser.y"
	{ yyval.expression = new cdk::sub_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 66:
#line 184 "zu_parser.y"
	{ yyval.expression = new cdk::mul_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 67:
#line 185 "zu_parser.y"
	{ yyval.expression = new cdk::div_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 68:
#line 186 "zu_parser.y"
	{ yyval.expression = new cdk::mod_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 69:
#line 187 "zu_parser.y"
	{ yyval.expression = new cdk::lt_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 70:
#line 188 "zu_parser.y"
	{ yyval.expression = new cdk::gt_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 71:
#line 189 "zu_parser.y"
	{ yyval.expression = new cdk::ge_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 72:
#line 190 "zu_parser.y"
	{ yyval.expression = new cdk::le_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 73:
#line 191 "zu_parser.y"
	{ yyval.expression = new cdk::eq_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 74:
#line 192 "zu_parser.y"
	{ yyval.expression = new cdk::ne_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 75:
#line 193 "zu_parser.y"
	{ yyval.expression = new zu::or_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 76:
#line 194 "zu_parser.y"
	{ yyval.expression = new zu::and_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 77:
#line 195 "zu_parser.y"
	{ yyval.expression = new zu::not_node(LINE, yystack.l_mark[0].expression); }
break;
case 78:
#line 196 "zu_parser.y"
	{ yyval.expression = new cdk::neg_node(LINE, yystack.l_mark[0].expression); }
break;
case 79:
#line 197 "zu_parser.y"
	{ yyval.expression = new zu::identity_node(LINE, yystack.l_mark[0].expression); }
break;
case 80:
#line 198 "zu_parser.y"
	{ yyval.expression = new zu::read_node(LINE); }
break;
case 81:
#line 199 "zu_parser.y"
	{ yyval.expression = new zu::allocation_node(LINE, yystack.l_mark[-1].expression); }
break;
case 82:
#line 200 "zu_parser.y"
	{ yyval.expression = yystack.l_mark[-1].expression; }
break;
case 83:
#line 201 "zu_parser.y"
	{ yyval.expression = yystack.l_mark[0].lvalue; }
break;
case 84:
#line 202 "zu_parser.y"
	{ yyval.expression = new zu::position_node(LINE, yystack.l_mark[-1].lvalue); }
break;
case 85:
#line 203 "zu_parser.y"
	{ yyval.expression = new zu::assignment_node(LINE, yystack.l_mark[-2].lvalue, yystack.l_mark[0].expression); }
break;
case 86:
#line 204 "zu_parser.y"
	{ yyval.expression = yystack.l_mark[0].expression; }
break;
case 87:
#line 207 "zu_parser.y"
	{ yyval.lvalue = new zu::id_node(LINE, yystack.l_mark[0].s); }
break;
case 88:
#line 208 "zu_parser.y"
	{ yyval.lvalue = new zu::index_node(LINE, yystack.l_mark[-3].lvalue, yystack.l_mark[-1].expression); }
break;
case 89:
#line 209 "zu_parser.y"
	{ yyval.lvalue = new zu::index_node(LINE, yystack.l_mark[-4].expression, yystack.l_mark[-1].expression); }
break;
case 90:
#line 210 "zu_parser.y"
	{ yyval.lvalue = new zu::index_node(LINE, yystack.l_mark[-3].expression, yystack.l_mark[-1].expression); }
break;
case 91:
#line 213 "zu_parser.y"
	{ yyval.expression = new zu::function_call_node(LINE, yystack.l_mark[-3].s, yystack.l_mark[-1].sequence); }
break;
case 92:
#line 216 "zu_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE, yystack.l_mark[0].expression, yystack.l_mark[-2].sequence); }
break;
case 93:
#line 217 "zu_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE, yystack.l_mark[0].expression); }
break;
case 94:
#line 218 "zu_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE, new cdk::nil_node(LINE)); }
break;
#line 1170 "zu_parser.tab.c"
    }
    yystack.s_mark -= yym;
    yystate = *yystack.s_mark;
    yystack.l_mark -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yystack.s_mark = YYFINAL;
        *++yystack.l_mark = yyval;
        if (yychar < 0)
        {
            if ((yychar = YYLEX) < 0) yychar = YYEOF;
#if YYDEBUG
            if (yydebug)
            {
                yys = yyname[YYTRANSLATE(yychar)];
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == YYEOF) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yystack.s_mark, yystate);
#endif
    if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
    {
        goto yyoverflow;
    }
    *++yystack.s_mark = (YYINT) yystate;
    *++yystack.l_mark = yyval;
    goto yyloop;

yyoverflow:
    YYERROR_CALL("yacc stack overflow");

yyabort:
    yyfreestack(&yystack);
    return (1);

yyaccept:
    yyfreestack(&yystack);
    return (0);
}
