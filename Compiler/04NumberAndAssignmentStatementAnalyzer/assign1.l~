signed [+-][0-9]*[.]?[0-9]+
decimal [0-9]+[.][0-9]+
scientific ({signed}|{decimal})[e|E][+-][0-9]+
div6 [0369]|[258][0369]*[147]|[147]([0369]|[147][0369]*[258])*[258]
%%
[0-9]+{5,}  	{ printf("Overflow %s\n",yytext); }
{decimal}	{printf("Decimal %s\n",yytext);}
{scientific}    {printf("Scientific %s\n",yytext);}
{signed} 	{ printf("Signed %s\n",yytext); }
0x[0-9A-F]{1,4}	{ printf("Hex %s\n",yytext); }
[a-zA-Z][a-zA-Z0-9]*	{ printf("Id %s\n",yytext); }
"="		{ printf("AssignOP %s\n",yytext); } 
"+"		{ printf("AddOP %s\n",yytext); }
"*"		{ printf("MultOP %s\n",yytext); }
"<"|">"|">="|"<="	{ printf("Relop %s\n",yytext); }
"<<"		{ printf("LeftShift %s\n",yytext); }
">>"		{ printf("RightShift %s\n",yytext); }
{div6}		{ printf("Div 6\n");}
%%
