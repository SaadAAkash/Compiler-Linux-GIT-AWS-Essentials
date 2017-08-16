%{
#include "finalbison.tab.h"
#include<string.h>
%}

%%

"+"	{ return ADD; }
"-"	{ return SUB; }
"*"	{ return MUL; }
"/"	{ return DIV; }
"|"	{ return OR; }
"&"	{ return AND; }
"("     { return OP; }
")"     { return CP; }
":="	{ return ASSGN; }
","	{ return COMMA; }
";"	{ return SEMICOLON; }
"~="	{ return NEQL; }
"="	{ return EQL; }
"<"	{ return LESS; }
"<="	{ return LEQL; }
">"	{ return GREATER; }
">="	{ return GEQL; }
"~"	{ return NOT; }
"true" {return TRUE;}
"false" {return FALSE;}
"if" {return IF;}
"fi" {return FI;}
[A-Za-z][A-Za-z0-9]* { yylval = strdup(yytext); return ID; }
[0-9]+	{ yylval = strdup(yytext); return INTEGER; }
[0-9]+"."[0-9]+	{ yylval = strdup(yytext); return REAL; }
"?" {return QUES;}
"::" {return ELS;}
<<EOF>> {return 0;}


[ \t\n]   { ; }
.	{;}
 
%%
