

%{
# include "parser.tab.h"
#include<string.h>
%}
%%
[ \t]   { /* ignore white space */ }

"+"	{ return ADD; }
"-"	{ return SUB; }
"*"	{ return MUL; }
"/"	{ return DIV; }
"("     { return OP; }
")"     { return CP; }
"{"		{ return OB; }
"}"		{ return CB; }
":="	{ return AssignOp; }

","	{ return List; }

";"	{ return Semicolon; }

">"	{ return GreaterRel; }
">="	{ return GreaterEqualRel; }

"<"	{ return LessRel; }
"<="	{ return LessEqualRel; }
"~="	{ return NotEqualRel; }
"="	{ return EqualRel; }
"~"	{ return Negate; }

"|"	{ return Or; }
"&" 	{ return And; }

"true"  { return True; }
"false" { return False; }


"::"	{ return ELSEE; }

"?"	{ return QMark; }

"if"	{ return ifStart; }
"fi"	{ return ifEnd; }

"do"	{ return loopStart; }
"od"	{ return loopEnd; }

"return" { return ret; }
[0-9]+	{ yylval.myStruct.var = strdup(yytext); return NUMBER; }
[0-9]+\.[0-9]+	{ yylval.myStruct.var = strdup(yytext); return REAL; }
[A-Za-z][A-Za-z0-9]* { yylval.myStruct.var = strdup(yytext); return id; }

"\n"	{ }
<<EOF>>   { return 0;}
%%

