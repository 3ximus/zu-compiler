%option c++ yyclass="zu_scanner" outfile="zu_scanner.cpp"
%option stack noyywrap yylineno 8bit debug
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

INTEGER		0|([1-9][0-9]*)
HEX_INT		0x[0-9a-fA-F]+

EXPONENT	[eE][+\-]?[0-9]+
DEC			\.[0-9]+
DOUBLE		[0-9]+(({DEC}?{EXPONENT})|{DEC})

%x X_STRING X_IGNORE_STRING X_COMMENT X_STRING_SPEC

%%

	{ set_debug(1); }

"//".*						; /* ignore comments */

\/\*						yy_push_state(X_COMMENT);
<X_COMMENT>\*\/				yy_pop_state();
<X_COMMENT>\/\*				yy_push_state(X_COMMENT);
<X_COMMENT>.|\n				; /* ignore */

">="						return tGE;
"<="						return tLE;
"=="						return tEQ;
"!="						return tNE;

"><"						return tBREAK;
"<>"						return tCONTINUE;
"!!!"						return tRETURN;
"!!"						return tPRINTLN;

[#%$]						return *yytext; /* zu_types */

	/**
	 * 	IDENTIFICADORES
	 */

[_A-Za-z][A-Za-z0-9_]*		yylval.s = new std::string(yytext); return tIDENTIFIER;

	/**
	 * 	STRINGS
	 */

\"							{ yy_push_state(X_STRING); yylval.s = new std::string(""); }
<X_STRING>\"				{ yy_pop_state(); return tSTRING; }
<X_STRING>\\ 				yy_push_state(X_STRING_SPEC);
<X_STRING>\\\"				*yylval.s += yytext + 1;
<X_STRING>.					*yylval.s += yytext;
<X_STRING>\n				yyerror("new line in string");

<X_STRING_SPEC>n	 					{ yy_pop_state(); *yylval.s += std::string(1,10); }
<X_STRING_SPEC>r	 					{ yy_pop_state(); *yylval.s += std::string(1,13); }
<X_STRING_SPEC>t	 					{ yy_pop_state(); *yylval.s += std::string(1,9); }
<X_STRING_SPEC>[\"\\]					{ yy_pop_state(); *yylval.s += yytext; }
<X_STRING_SPEC>0[0-9a-fA-F]+			{ yy_pop_state(); *yylval.s += std::string(1,strtol(yytext, nullptr, 16)); }
<X_STRING_SPEC>[1-9a-fA-F][0-9a-fA-F]*	{ yy_pop_state(); *yylval.s += std::string(1,strtol(yytext, nullptr, 16)); }
<X_STRING_SPEC>0						{ yy_pop_state(); yy_pop_state(); yy_push_state(X_IGNORE_STRING); }
<X_STRING_SPEC>.|\n						yyerror("Invalid special character");

<X_IGNORE_STRING>\"			{ yy_pop_state(); return tSTRING; }
<X_IGNORE_STRING>.			; /* ignore everything else */
<X_IGNORE_STRING>\n			yyerror("newline in string");

	/**
	 * 	REAIS / INTEIROS
	 */

{DOUBLE}					{ yylval.d = strtol(yytext, nullptr, 10); if(errno == ERANGE) yyerror("Invalid number range, overflow occurred"); return tDOUBLE; }
{INTEGER}					{ yylval.i = strtol(yytext, nullptr, 10); if(errno == ERANGE) yyerror("Invalid number range, overflow occurred"); return tINTEGER; }
{HEX_INT}					{ yylval.i = strtol(yytext, nullptr, 16); if(errno == ERANGE) yyerror("Invalid number range, overflow occurred"); return tINTEGER; } /* TODO should i ofset to remove the 0x ? */

	/**
	 *	SYMBOLS
	 */

[,;:()\[\]{}] 				return *yytext;
[-<>=+*/%&|!?]     			return *yytext;

[ \t\n]+					; /* ignore whitespace */

.                      		yyerror("Unknown character");

%%
// Very, very dirty hack: flex is a mess generating C++ scanners.
int zu_scanner::yywrap() { return 1; }
