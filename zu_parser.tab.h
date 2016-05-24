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
extern YYSTYPE yylval;
