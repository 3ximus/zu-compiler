%{
// $Id: zu_parser.y,v 1.2 2016/03/16 22:16:34 ist169481 Exp $
//-- don't change *any* of these: if you do, you'll break the compiler.
#include <cdk/compiler.h>
#include "ast/all.h"
#define LINE       compiler->scanner()->lineno()
#define yylex()    compiler->scanner()->scan()
#define yyerror(s) compiler->scanner()->error(s)
#define YYPARSE_PARAM_TYPE std::shared_ptr<cdk::compiler>
#define YYPARSE_PARAM      compiler
//-- don't change *any* of these --- END!
%}

%union {
  int                 	 i;	/* integer value */
  double              	 d;
  std::string         	*s;	/* symbol name or string literal */
  cdk::basic_node     	*node;	/* node pointer */
  cdk::sequence_node  	*sequence;
  cdk::expression_node	*expression;
  zu::lvalue_node  		*lvalue;
};

%token <i> tINTEGER
%token <d> tDOUBLE
%token <s> tIDENTIFIER tSTRING
%token tBREAK tCONTINUE tRETURN
/* %token tFOR tIF tPRINT  tREAD  tBEGIN tEND */

%nonassoc tIFX /* create
/* %nonassoc tELSE */

%right '='
%right '['
%left tGE tLE tEQ tNE '>' '<'
%left '+' '-'
%left '*' '/' '%'
%nonassoc tUNARY /* not recognized by lexical analizer and is used to specify precedence */

%type <node> stmt program type
%type <sequence> list
%type <expression> expr
%type <lvalue> lval

%{
//-- The rules below will be included in yyparse, the main parsing function.
%}
%%

/*
program	: tBEGIN list tEND { compiler->ast(new zu::program_node(LINE, $2)); }
        ;
*/

/* TODO -- separar varias isntrucoes por virgula, fazer onde? */

list : stmt	     							{ $$ = new cdk::sequence_node(LINE, $1); }
	 | list stmt 							{ $$ = new cdk::sequence_node(LINE, $2, $1); }
	 ;

stmt : expr									{ $$ = new zu::evaluation_node(LINE, $1); }
     | expr '!'								{ $$ = new zu::print_node(LINE, $1); } /* TODO simple print ? */
     | expr '!!'							{ $$ = new zu::print_node(LINE, $1); } /* TODO new line print ? */
     | '[' list ';' list ';' list ']' stmt	{ $$ = new zu::for_node(LINE, $2, $4, $6, $8); }
     | '[' expr ']' '#' stmt %prec tIFX		{ $$ = new zu::if_node(LINE, $2, $5); }
     | '[' expr ']' '?' stmt ':' stmt		{ $$ = new zu::if_else_node(LINE, $2, $5, $7); }
     | '[' expr ']'							{ $$ = new zu::allocation_node(LINE, $2); }
     | tBREAK								{ $$ = new zu::break_node(LINE); }
     | tCONTINUE							{ $$ = new zu::continue_node(LINE); }
     | tRETURN								{ $$ = new zu::return_node(LINE); }
/*   | '{' list '}'							{ $$ = $2; } */ 				/* TODO not needed ?? */
/*	 | tPRINT expr ';'						{ $$ = new zu::print_node(LINE, $2); } */
     ;

expr : tINTEGER               				{ $$ = new cdk::integer_node(LINE, $1); }
     | tSTRING                				{ $$ = new cdk::string_node(LINE, $1); } /* TODO add concatenation case here ? */
     | tDOUBLE                				{ $$ = new cdk::double_node(LINE, $1); }
     | '@'									{ $$ = new zu::read_node(LINE); }
     | '-' expr %prec tUNARY  				{ $$ = new cdk::neg_node(LINE, $2); }
     | '~' expr %prec tUNARY  				{ $$ = new cdk::neg_node(LINE, $2); } /* TODO FIXME what is the node? */
     | expr '+' expr	      				{ $$ = new cdk::add_node(LINE, $1, $3); }
     | expr '-' expr	      				{ $$ = new cdk::sub_node(LINE, $1, $3); }
     | expr '*' expr	      				{ $$ = new cdk::mul_node(LINE, $1, $3); }
     | expr '/' expr	      				{ $$ = new cdk::div_node(LINE, $1, $3); }
     | expr '%' expr	      				{ $$ = new cdk::mod_node(LINE, $1, $3); }
     | expr '<' expr	      				{ $$ = new cdk::lt_node(LINE, $1, $3); }
     | expr '>' expr	      				{ $$ = new cdk::gt_node(LINE, $1, $3); }
     | expr tGE expr	      				{ $$ = new cdk::ge_node(LINE, $1, $3); }
     | expr tLE expr          				{ $$ = new cdk::le_node(LINE, $1, $3); }
     | expr tNE expr	      				{ $$ = new cdk::ne_node(LINE, $1, $3); }
     | expr tEQ expr	      				{ $$ = new cdk::eq_node(LINE, $1, $3); }
     | '(' expr ')'           				{ $$ = $2; }
     | lval                   				{ $$ = new zu::rvalue_node(LINE, $1); }  //FIXME
     | lval '=' expr          				{ $$ = new zu::assignment_node(LINE, $1, $3); }
     ;

lval : tIDENTIFIER ';'             			{ $$ = new zu::variable_node(LINE, $1); }
	 | type tIDENTIFIER						{ $$ = new zu::variable_node(LINE, $2); }	/* TODO vars ? */
	 | type tIDENTIFIER	'!'					{ $$ = new zu::variable_node(LINE, $2); }	/* TODO global vars ? */
	 | type tIDENTIFIER	'?'					{ $$ = new zu::variable_node(LINE, $2); }	/* TODO foreign vars ? */
     ;

type : '#'
	 | '%'
	 | '$'
	 | '<' type '>'
	 ;

%%
