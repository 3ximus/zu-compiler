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
  int                 				 i;	/* integer value */
  double              				 d;
  std::string         				*s;	/* symbol name or string literal */
  cdk::basic_node     				*node;	/* node pointer */
  cdk::sequence_node  				*sequence;
  cdk::expression_node				*expression;
  zu::function_declaration_node 	*function;
  zu::lvalue_node					*lvalue;
  basic_type						*ztype;
};


/* ZU TOKENS */
%token tBREAK tCONTINUE tRETURN tTYPE tPRINTLN 

/* LITERALS && IDENTIFIERS */
%token <i> tINTEGER
%token <d> tDOUBLE
%token <s> tIDENTIFIER tSTRING

/* PRECEDENCES */

%nonassoc tIFX
%nonassoc tELSEX
%nonassoc ':'

%right '='
%left '|'
%left '&'
%nonassoc '~'
%left tEQ tNE
%left tGE tLE '>' '<'
%left '+' '-'
%left '*' '/' '%'
%right '('
%right '['
%right '{'
%left ';'

%nonassoc tUNARY

/* TYPES OF NON-TERMINAL SYMBOLS */

%type <node> dec arg var itr 	 		 /* declaration, argument, variable, instruction */
%type <sequence> decs args vars itrs exprs fargs /* declarations,arguments,variables,instructions,expressions,function arguments*/  

%type <node> vdec blk cond iter  /* variable declaration, block, condtional instruction, iteraion instruction */
%type <function> fdec 		 /* function declaration */

%type <expression> expr fcal lit /* expression, function call, literal */
%type <lvalue> lval
%type <ztype> type
%type <s> str

%{
//-- The rules below will be included in yyparse, the main parsing function.
%}

%%

file : decs		{ compiler->ast( $1 ); }	
     |			{ compiler->ast(new cdk::nil_node(LINE)); }
     ;

decs : dec		{ $$ = new cdk::sequence_node(LINE, $1); }
     | dec decs		{ $$ = new cdk::sequence_node(LINE, $1, $2); }
     ;

dec  : vars ';' 	{ $$ = $1; }
     | fdec     	{ $$ = $1; }
     | fdec blk		{ $$ = new zu::function_body_node(LINE, $1, $2); }
     ;

vars : var		{ $$ = new cdk::sequence_node(LINE, $1); }
     | var ',' vars	{ $$ = new cdk::sequence_node(LINE, $1, $3); } 
     ;

var  : vdec		{ $$ = $1; }
     ;

itrs : itr		{ $$ = new cdk::sequence_node(LINE, $1); }
     | itrs itr		{ $$ = new cdk::sequence_node(LINE, $2, $1); }
     ;

itr  : expr ';'		{ $$ = new zu::evaluation_node(LINE, $1); }
     | expr '!'		{ $$ = new zu::print_node(LINE, $1, false); }
     | expr tPRINTLN	{ $$ = new zu::print_node(LINE, $1, true); }
     | tBREAK		{ $$ = new zu::break_node(LINE); }
     | tCONTINUE	{ $$ = new zu::continue_node(LINE); }
     | tRETURN		{ $$ = new zu::return_node(LINE); }
     | cond		{ $$ = $1; }
     | iter		{ $$ = $1; }
     | blk 		{ $$ = $1; }
     ;

vdec : type tIDENTIFIER				{ $$ = new zu::variable_node(LINE, $1, $2, false, false, NULL); }
     | type tIDENTIFIER '!'			{ $$ = new zu::variable_node(LINE, $1, $2, true, false, NULL); }
     | type tIDENTIFIER '?'			{ $$ = new zu::variable_node(LINE, $1, $2, false, true, NULL); }
     | type tIDENTIFIER '=' expr		{ $$ = new zu::variable_node(LINE, $1, $2, false, false, $4); }
     | type tIDENTIFIER '!' '=' expr		{ $$ = new zu::variable_node(LINE, $1, $2, true, false, $5); }
     | type tIDENTIFIER '?' '=' expr		{ $$ = new zu::variable_node(LINE, $1, $2, false, true, $5); }
     ;

fdec : type tIDENTIFIER '(' fargs ')' '=' lit	{ $$ = new zu::function_declaration_node(LINE, $1, $2, false, false, $4, $7); }
     | type tIDENTIFIER '(' fargs ')'		{ $$ = new zu::function_declaration_node(LINE, $1, $2, false, false, $4, NULL); }
     | '!'  tIDENTIFIER '(' fargs ')' 		{ $$ = new zu::function_declaration_node(LINE, new basic_type(0, basic_type::TYPE_VOID), $2, false, false, $4, NULL); }
     | type tIDENTIFIER '!' '(' fargs ')' '=' lit	{ $$ = new zu::function_declaration_node(LINE, $1, $2, true, false, $5, $8); }
     | type tIDENTIFIER '!' '(' fargs ')' 		{ $$ = new zu::function_declaration_node(LINE, $1, $2, true, false, $5, NULL); }
     | '!'  tIDENTIFIER '!' '(' fargs ')' 		{ $$ = new zu::function_declaration_node(LINE, new basic_type(0, basic_type::TYPE_VOID), $2, true, false, $5, NULL); }
     | type tIDENTIFIER '?' '(' fargs ')' '=' lit	{ $$ = new zu::function_declaration_node(LINE, $1, $2, false, true,  $5, $8); }
     | type tIDENTIFIER '?' '(' fargs ')' 		{ $$ = new zu::function_declaration_node(LINE, $1, $2, false, true,  $5, NULL); }
     | '!'  tIDENTIFIER '?' '(' fargs ')' 		{ $$ = new zu::function_declaration_node(LINE, new basic_type(0, basic_type::TYPE_VOID), $2, false, true, $5, NULL); }
     ;

lit  : tINTEGER			{ $$ = new cdk::integer_node(LINE, $1); }
     | tDOUBLE			{ $$ = new cdk::double_node(LINE, $1); }
     | str			{ $$ = new cdk::string_node(LINE, $1); }
     ;

str  : tSTRING			{ $$ = $1; }
     | str tSTRING 	{ $$ = new std::string(*$1 + *$2); }
     ;

// Function arguments

fargs : args			{ $$ = $1; }
      |				{ $$ = NULL; }
      ;

args : arg			{ $$ = new cdk::sequence_node(LINE, $1); }
     | args ',' arg		{ $$ = new cdk::sequence_node(LINE, $3, $1); }
     ;

arg  : type tIDENTIFIER		{ $$ = new zu::variable_node(LINE, $1, $2, false, false, NULL); }
     ;

// Zu types

type : '#'						{ $$ = new basic_type(4, basic_type::TYPE_INT); }
     | '%'						{ $$ = new basic_type(8, basic_type::TYPE_DOUBLE); }
     | '$'						{ $$ = new basic_type(4, basic_type::TYPE_STRING); }
     | '<' type '>'					{ $$ = new basic_type(4, basic_type::TYPE_POINTER); $$->_subtype = $2; }
     ;

blk  : '{' decs itrs '}'				{ $$ = new zu::block_node(LINE, $2, $3); }
     | '{' decs '}'					{ $$ = new zu::block_node(LINE, $2, NULL); }
     | '{' itrs '}'					{ $$ = new zu::block_node(LINE, NULL, $2); }
     | '{' '}'						{ $$ = new zu::block_node(LINE, NULL, NULL); }
     ;

cond :  '[' expr ']' '#' itrs %prec tIFX		{ $$ = new zu::if_node(LINE, $2, $5); }
     |  '[' expr ']' '?' itrs				{ $$ = new zu::if_else_node(LINE, $2, $5, NULL); }
     |  '[' expr ']' '?' itrs ':' itrs			{ $$ = new zu::if_else_node(LINE, $2, $5, $7); }
     ;

iter : '[' exprs ';' exprs ';' exprs ']' itrs		{ $$ = new zu::for_node(LINE, $2, $4, $6, $8); }
     | '[' vars ';' exprs ';' exprs ']' itrs		{ $$ = new zu::for_node(LINE, $2, $4, $6, $8); }
     ;

expr : lit  						{ $$ = $1; }
     | fcal 						{ $$ = $1; }
     | expr '+' expr					{ $$ = new cdk::add_node(LINE, $1, $3); }
     | expr '-' expr					{ $$ = new cdk::sub_node(LINE, $1, $3); }
     | expr '*' expr					{ $$ = new cdk::mul_node(LINE, $1, $3); }
     | expr '/' expr					{ $$ = new cdk::div_node(LINE, $1, $3); }
     | expr '%' expr					{ $$ = new cdk::mod_node(LINE, $1, $3); }
     | expr '<' expr					{ $$ = new cdk::lt_node(LINE, $1, $3); }
     | expr '>' expr					{ $$ = new cdk::gt_node(LINE, $1, $3); }
     | expr tGE expr					{ $$ = new cdk::ge_node(LINE, $1, $3); }
     | expr tLE expr					{ $$ = new cdk::le_node(LINE, $1, $3); }
     | expr tEQ expr					{ $$ = new cdk::eq_node(LINE, $1, $3); }
     | expr tNE expr					{ $$ = new cdk::ne_node(LINE, $1, $3); }
     | expr '|' expr					{ $$ = new zu::or_node(LINE, $1, $3); }
     | expr '&' expr					{ $$ = new zu::and_node(LINE, $1, $3); }
     | '~' expr %prec tUNARY  				{ $$ = new zu::not_node(LINE, $2); }
     | '-' expr %prec tUNARY  				{ $$ = new zu::simetry_node(LINE, $2); }
     | '+' expr %prec tUNARY  				{ $$ = new zu::identity_node(LINE, $2); }
     | expr '?'						{ $$ = new zu::position_node(LINE, $1); }
     | '@'						{ $$ = new zu::read_node(LINE); } /* FIXME speacial read and print */
     | '[' expr ']'					{ $$ = new zu::allocation_node(LINE, $2); }
     | '(' expr ')'					{ $$ = $2; }
     | lval 						{ $$ = $1; }
     | lval '=' expr					{ $$ = new zu::assignment_node(LINE, $1, $3); }
     ;

lval : tIDENTIFIER					{ $$ = new zu::id_node(LINE, $1); }
     | lval '[' expr ']'				{ $$ = new zu::index_node(LINE, $1, $3); }
     | fcal '[' expr ']'				{ $$ = new zu::index_node(LINE, $1, $3); }
     ;

fcal : tIDENTIFIER '(' exprs ')' 			{ $$ = new zu::function_call_node(LINE, $1, $3); }
     | tIDENTIFIER '(' ')'				{ $$ = new zu::function_call_node(LINE, $1, NULL); }
     ;

exprs : expr ',' exprs					{ $$ = new cdk::sequence_node(LINE, $1, $3); }
      | expr						{ $$ = new cdk::sequence_node(LINE, $1); }
      |							{ $$ = new cdk::sequence_node(LINE,NULL); }
      ;

%%
