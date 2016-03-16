%option c++ yyclass="zu_scanner" outfile="zu_scanner.cpp"
%option stack noyywrap yylineno 8bit
%{
/* $Id: zu_scanner.l,v 1.2 2016/03/16 22:16:34 ist169481 Exp $ */
// make relevant includes before including the parser's tab file
#include <string>
#include <cdk/ast/sequence_node.h>
#include <cdk/ast/expression_node.h>
#include "zu_scanner.h"
#include "zu_parser.tab.h"

// don't change this
#define yyerror LexerError
%}
%x X_STRING
%%

"//".*                 ; /* ignore comments */

">="                   return tGE;
"<="                   return tLE;
"=="                   return tEQ;
"!="                   return tNE;

[A-Za-z][A-Za-z0-9_]*  yylval.s = new std::string(yytext); return tIDENTIFIER;

\'                     yy_push_state(X_STRING); yylval.s = new std::string("");
<X_STRING>\'           yy_pop_state(); return tSTRING;
<X_STRING>\\\'         *yylval.s += yytext + 1;
<X_STRING>.            *yylval.s += yytext;
<X_STRING>\n           yyerror("newline in string");

[0-9]+                 yylval.i = strtol(yytext, nullptr, 10); return tINTEGER;

[-()<>=+*/%;{}.]       return *yytext;

[ \t\n]+               ; /* ignore whitespace */

.                      yyerror("Unknown character");

%%
// Very, very dirty hack: flex is a mess generating C++ scanners.
int zu_scanner::yywrap() { return 1; }
