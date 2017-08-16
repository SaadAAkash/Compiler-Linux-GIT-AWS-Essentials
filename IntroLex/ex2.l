%%
is|was|were {printf("verb");}
[0-9]+ {printf("number");}
[A-Z]+ {printf("in A to Z");}
[a-z]+ {printf("in a to z");}
. {}
%%
int main(){
 yylex();
return 0;
}
