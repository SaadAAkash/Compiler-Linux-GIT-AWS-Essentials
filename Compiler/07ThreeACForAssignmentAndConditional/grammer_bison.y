%{
#include<stdio.h>
#include<stdlib.h>

#define YYSTYPE char*


int t_number = 1;

void t_num_incre(char t[]); 

int vars_num = 0;
int expr_num = 0;

char vars_arr[100][100];
char expr_arr[100][100];
%}


/* declare tokens */
%token NUMBER
%token ADD SUB MUL DIV
%token ASSIGN SEMICOLON COMMA ID REAL INTEGER
%token OP CP EOL
%token True False
%token EQUAL NTEQUAL NEG
%token GRTHAN LSTHAN LSEQUAL GREQUAL OR AND
%%

/* 
THE GIVEN GRAMMR (EXTENDED):
assignment → vars := exprs;
vars → id |vars , id
exprs → expr | exprs , expr
expr → sum
sum → term | - term | sum + term | sum - term
term → factor | term * factor | term / factor
factor → true | false | integer | real | id | ( expr )
///////////////////////////////////
expr → disjunction
disjunction → conjunction | disjunction or conjunction
conjunction → negation | conjunction & negation
negation → relation| ~ relation
relation → sum
|sum < sum
|sum <= sum
|sum = sum
|sum ~= sum
|sum>= sum
|sum> sum

*/

assignment:  vars ASSIGN exprs SEMICOLON {
					if(vars_num != expr_num)
						printf("No of var and no of expr not equal. Sorry!\n");
					else
					{
						printf("No of Var and no of expr equal.\n");						
						int i;					
						for(i = 0;i < vars_num ; i++)	
						{
							printf("%s = %s\n",vars_arr[i],expr_arr[i]);
						}
					}
					printf("Finished!\n");		
					}
;

/*****baad********/
//| ID COMMA ID ASSIGN expr COMMA expr SEMICOL  { printf("%s = %s\n",$$, $3); printf("\nFinished!\n\n"); }
//;

vars: ID	{
		printf( "**vars -> id\n" );		
		strcpy(vars_arr[vars_num++],$1);
		printf("HEREEEEEEEEE $ 1= %s\n ", $1); 
		}
|vars COMMA ID  {
		printf( "**vars -> vars , id\n" );		
		strcpy(vars_arr[vars_num++],$3);
		printf("HEREEEEEEEEE $ 3= %s\n ", $3); 
				

		}

;

exprs: expr  { 
		printf( "**exprs -> expr\n" );
		strcpy(expr_arr[expr_num++],$1);
		printf("HEREEEEEEEEE $ 1= %s\n ", $1); 
		
		}
| exprs COMMA expr { 
		
		printf( "**exprs -> exprs , expr\n" );
		strcpy(expr_arr[expr_num++],$3);
		printf("HEREEEEEEEEE $ 3= %s\n ", $3); 
		
		}
;

expr:disjunction { 
		$$ = $1; 
		printf( "**expr -> disjunc\n" );
		}
;

disjunction:	conjunction  { 
			$$ = $1; printf( "**disjunc->conjunc\n");
						
			}
| disjunction OR conjunction 	{ 

			char str[100]; 
			t_num_incre(str); 
			printf( "**disjunc -> disjunc | conjunc \n" );
			printf("%s = %s | %s \n", str, $1, $3); 
			$$ = strdup(str); 

} 
;


conjunction: negation {
			$$ = $1;
			printf("**conjunc -> neg\n");
		}
| conjunction AND negation { 
		char str[100]; 
		t_num_incre(str);
		printf( "**conjunc -> conjunc AND neg \n" );
		printf("%s = %s & %s \n", str, $1, $3); 
		$$ = strdup(str); 
		}
;

negation: relation 	{$$ =$1;}
| NEG relation		{ 
			char str[100]; 
			t_num_incre(str); 
			printf( "neg -> neg relation \n" );
			printf("%s = ~ %s  \n", str, $2); 
			$$ = strdup(str); 
			}
;

relation: sum		{ $$ = $1; }
|sum LSTHAN sum		{ 
			char str[100]; 
			t_num_incre(str); printf("**rel -> sum<sum\n");
			printf("%s = %s < %s \n", str, $1, $3); 
			$$ = strdup(str); 
			}
|sum LSEQUAL sum	{ 
			char str[100]; 
			t_num_incre(str); 
			printf("%s = %s <= %s \n", str, $1, $3); 
			$$ = strdup(str); }
|sum EQUAL sum		{ 
			char str[100]; 
			t_num_incre(str); 
			printf("%s = %s == %s \n", str, $1, $3); 
			$$ = strdup(str); }
|sum NTEQUAL sum	{ 
			char str[100]; 
			t_num_incre(str); 
			printf("%s = %s != %s \n", str, $1, $3); 
			$$ = strdup(str); }
|sum GREQUAL sum	{ 
			char str[100]; 
			t_num_incre(str); 
			printf("%s = %s >= %s \n", str, $1, $3); 
			$$ = strdup(str); }
|sum GRTHAN sum		{ 
			char str[100]; 
			t_num_incre(str); 
			printf("%s = %s > %s \n", str, $1, $3); 
			$$ = strdup(str); }

;

sum: term 	{ 
			$$ = $1; 
			printf( "**sum -> term\n" );
		}
| SUB term 	{ 
			char str[100]; 
			str[0] = '-'; 
			sprintf(str+1,"%s",$2); 
			$$ = str; 

			printf( "**sum -> -term\n" );
	    	
	    	}
| sum ADD term { /*add();*/ 
			char str[100]; 
			t_num_incre(str); 
			
			
			printf( "**sum -> sum + term\n" );

			printf("%s = %s + %s \n", str, $1, $3); 
			$$ = strdup(str); 
		} 
| sum SUB term { 
			char str[100]; 
			t_num_incre(str); 

			printf( "**sum -> sum + term\n" );


			printf("%s = %s - %s \n", str, $1, $3); 
			$$ = strdup(str); 
		} 
;

term: fact { 
		$$ = $1;  
		printf( "**term -> fact\n" ); 
		}
| term MUL fact { 
			char str[100]; 
			t_num_incre(str);
 			printf("%s = %s \n", str, $1); 
			$$ = strdup(str);  
			t_num_incre(str);


			printf( "**term -> term * fact\n" );

			printf("%s = %s * %s \n", str, $$, $3); 
			$$ = strdup(str); 
		}
| term DIV fact { 
			char str[100]; 
			t_num_incre(str); 
			printf("%s = %s \n", str, $1);   //t1 = sgn
			$$ = strdup(str);  //$$ = t1
			t_num_incre(str);  //t2 return krbe


			printf( "**term -> term/fact\n" );


			printf("%s = %s / %s \n", str, $$, $3);  // t2 = t1 / step 
			$$ = strdup(str); 
		}
; 


fact: NUMBER { 
		$$ = $1; 
		printf( "**fact -> num\n" ); 
		}
| ID { 
		$$ = $1; 
		printf( "**fact -> id\n" );
		printf("HEREEEEEEEEE $ 1= %s\n ", $1); 	
	}
| OP expr CP { 
		$$ = $2; 
		printf( "**fact -> ( expr )\n" );
		printf("HEREEEEEEEEE $ 2= %s\n ", $2); 		
		}
|True   {
		$$ = $1;
		printf( "**fact -> true\n" );
	}
|False	{
		$$ = $1;
		printf( "**fact -> false\n" );
	}
;





%%
main()
{
  yyparse();
}

yyerror(char *s)
{
  
}

void t_num_incre(char t[]) 
{
	t[0] = 't';
	sprintf(t+1,"%d",t_number++);  //printing the "1" in "t1"
}
