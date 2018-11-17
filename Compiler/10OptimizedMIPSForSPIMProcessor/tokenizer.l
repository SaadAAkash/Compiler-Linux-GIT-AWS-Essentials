%{
	#include "parser.tab.h"
	#include<string.h>
extern FILE *yyin;
char nullStr[] = "";
%}
%%

[ \t\n\r] {;}

"if"	{return IF;}
"fi"	{return FI;}
"do"	{return DO;}
"od"	{return OD;}
"::"	{return COLON;}
"?"	{return QUES;}
":=" {return ASSIGN; }
";" { return SEMICOLON; }
"+" { return ADD; }
"-" { return SUB; }
"*" { return MUL; }
"/" { return DIV; }
"(" {return OPEN;}
")" {return CLOSE;}
"return" {return RET;}
"{" { return OPEN2; }
"}" {return CLOSE2; }
"true" { yylval.s.ret = strdup(yytext); yylval.s.str=strdup(nullStr);yylval.s.asmvar=strdup(nullStr); yylval.s.asmbly=strdup(nullStr);yylval.s.asmret=0;return TRUE; }
"false" { yylval.s.ret = strdup(yytext); yylval.s.str=strdup(nullStr); yylval.s.asmbly=strdup(nullStr);yylval.s.asmvar=strdup(nullStr);yylval.s.asmret=0;return FALSE;}
"," {return COMMA;}
[0-9]+ { yylval.s.ret = strdup(yytext); yylval.s.str=strdup(nullStr);yylval.s.asmvar=strdup(nullStr);yylval.s.asmbly=strdup(nullStr);yylval.s.asmret=0; return NUM; }
[0-9]*"."[0-9]+ { yylval.s.ret = strdup(yytext);yylval.s.asmvar=strdup(nullStr); yylval.s.str=strdup(nullStr);yylval.s.asmbly=strdup(nullStr);yylval.s.asmret=0;return REAL_NUM; }
[a-zA-Z][0-9a-zA-Z]* { yylval.s.ret = strdup(yytext); yylval.s.str=strdup(nullStr);yylval.s.asmvar=strdup(nullStr);yylval.s.asmbly=strdup(nullStr);yylval.s.asmret=0;return ID; }
"|" {return OR;}
"&" {return AND ; }
"~" {return NOT;}
"<" {return LT;}
"<=" {return LEQ;}
"=" {return EQ;}
"~=" {return NEQ;}
">=" {return GEQ;}
">" {return GTH;}
<<EOF>>     {return 0;}
. { printf("Invalid Input %s\n", yytext); }
%%

main(int argc, char**argv)
{
	char *in=argv[1];
	yyin = fopen(in, "r");
	yyparse();
}
