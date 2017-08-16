%{
#include <stdio.h>
#include <string.h>
#include<stdlib.h>

#define YYSTYPE char*

int yylex();

void yyerror(char *s);

extern FILE* yyin;
//extern FILE* yyin2;

int t_number = 1;

void t_num_incre(char t[]); 
%}

/* declare tokens */
%token NUMBER
%token ADD SUB MUL DIV ABS
%token ASSIGN SEMICOL COMMA ID REAL INTEGER
%token OP CP
%token EOL

%%


/* 
THE GIVEN GRAMMR:

assign → vars := exprs;
vars → id |vars , id
exprs → expr | exprs , expr
expr → sum
sum → term | - term | sum + term | sum - term
term → factor | term * factor | term / factor
factor → true | false | integer | real | id | ( expr )

*/

assign:  ID ASSIGN expr SEMICOL { printf("%s = %s\n",$$, $3); printf( "assignment -> vars := exprs\n" ); printf("\nFinished!\n\n"); }  //ekhane $$ == $1 == new
| ID COMMA ID ASSIGN expr COMMA expr SEMICOL  { printf("%s = %s\n",$$, $3); printf("\nFinished!\n\n"); }
;

expr: sum { $$ = $1;  printf( "exprs -> expr\n" ); printf( "expr -> sum\n" ); }
;

sum: term	{ $$ = $1; printf( "sum -> term\n" );}
| SUB term 	{ 
			char str[100]; str[0] = '-'; 
			sprintf(str+1,"%s",$2); 
			$$ = str; 

			printf( "sum -> -term\n" );
	    	
	    	}
| sum ADD term { /*add();*/ 
			char str[100]; 
			t_num_incre(str); 
			/*printf("%s = %s \n", str, $1); 
			$$ = strdup(str);  
			t_num_incre(str);*/
			
			printf( "sum -> sum + term\n" );

			printf("%s = %s + %s \n", str, $1, $3); 
			$$ = strdup(str); 
		} 
| sum SUB term { 
			char str[100]; 
			t_num_incre(str); 
			/*printf("%s = %s \n", str, $1); 
			$$ = strdup(str);  
			t_num_incre(str);*/

			printf( "sum -> sum + term\n" );


			printf("%s = %s - %s \n", str, $1, $3); 
			$$ = strdup(str); 
		} 
;

term: fact { $$ = $1;  printf( "term -> fact\n" ); }
| term MUL fact { 
			char str[100]; 
			t_num_incre(str);
 			printf("%s = %s \n", str, $1); 
			$$ = strdup(str);  
			t_num_incre(str);


			printf( "term -> term * fact\n" );

			printf("%s = %s * %s \n", str, $$, $3); 
			$$ = strdup(str); 
		}
| term DIV fact { 
			char str[100]; 
			t_num_incre(str); 
			printf("%s = %s \n", str, $1);   //t1 = sgn
			$$ = strdup(str);  //$$ = t1
			t_num_incre(str);  //t2 return krbe


			printf( "term -> term/fact\n" );


			printf("%s = %s / %s \n", str, $$, $3);  // t2 = t1 / step 
			$$ = strdup(str); 
		}
; 


fact: NUMBER { $$ = $1; printf( "fact -> num\n" ); }
| ID { $$ = $1; printf( "fact -> id\n" );}
| OP expr CP { $$ = $2; printf( "ok\n" );}
;
%%

/*
int main()
{
	printf("\nTaking input from the file 1.....\n");
	FILE* fp = fopen("input.txt", "r");
	yyin = fp;
	printf("\nOutput for the file no 1 input ==> \n");

*/	//yyparse();
/*
	printf("\nTaking input from the file 2.....\n");
	FILE* fp2 = fopen("input2.txt", "r");
	yyin2 = fp2;
	printf("\nOutput for the file no 2 input ==> \n");
	yyparse();
	return 0;
*/
//}

int main(int argc, char** argv)
{
	printf("\nTaking input from the file.....\n");
	FILE* fp = fopen( argv[1], "r");
	yyin = fp;
	printf("\nOutput for the file input ==> \n");
	yyparse();

}

void yyerror(char *s)
{
	//fprintf(stderr, "Error found: %s\n", s);

}

void t_num_incre(char t[]) {
	t[0] = 't';
	sprintf(t+1,"%d",t_number++);  //printing the "1" in "t1"
}

void add()
{
	//char str[100]; t_num_incre(str); printf("%s = %s + %s \n", str, $1, $3); $$ = strdup(str);
}


