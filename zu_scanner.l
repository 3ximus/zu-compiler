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
%x X_STRING X_IGNORE_STRING X_COMMENT
%%

"//".*						; /* ignore comments */

\/\*						yy_push_state(X_COMMENT);
<X_COMMENT>\*\/				yy_pop_state();
<X_COMMENT>\/\*				yy_push_state(X_COMMENT);
<X_COMMENT>.				; /* ignore */
<X_COMMENT>.|\n

">="						return tGE;
"<="						return tLE;
"=="						return tEQ;
"!="						return tNE;

"><"						return tBREAK;
"<>"						return tCONTINUE;
"!!!"						return tRETURN;
"!!"						return tNLPRINT;

[#%$]						return tTYPE;

	/**
	 * 	IDENTIFICADORES
	 */

[_A-Za-z][A-Za-z0-9_]*		yylval.s = new std::string(yytext); return tIDENTIFIER;

	/**
	 * 	STRINGS
	 */

\"							yy_push_state(X_STRING); yylval.s = new std::string("");
<X_STRING>\"[\t\s]+\"		; /* string concatenation */
<X_STRING>\"				yy_pop_state(); return tSTRING;
<X_STRING>\\0				yy_pop_state(); yy_push_state(X_IGNORE_STRING);
<X_STRING>\\\"				*yylval.s += yytext + 1;
<X_STRING>.					*yylval.s += yytext;
<X_STRING>\n				yyerror("newline in string");

<X_IGNORE_STRING>\"			yy_pop_state(); return tSTRING;
<X_IGNORE_STRING>.			;
<X_IGNORE_STRING>\n			yyerror("newline in string");

	/**
	 * 	REAIS / INTEIROS
	 */

[0-9]\+\([\.]\?\([0-9]\+e[\-]\?[0-9]\+\)\|\.[0-9]\+\)			yylval.d = strtol(yytext, nullptr, 10); return tDOUBLE;		/* TODO Works on grep -- do i need all escape characters? */
[0]\|[0-9]\+\|0x[0-9a-fA-F]\+									yylval.i = strtol(yytext, nullptr, 10); return tINTEGER;	/* TODO Works on grep -- do i need all escape characters? */

	/**
	 *	SYMBOLS
	 */

[-()<>=+*/%;\[\]{}\.&|!]     	return *yytext; /* TODO i added a few more check if it is okay -- also, do i need to escape & ? */

[ \t\n]+						; /* ignore whitespace */

.                      	yyerror("Unknown character");

%%
// Very, very dirty hack: flex is a mess generating C++ scanners.
int zu_scanner::yywrap() { return 1; }
