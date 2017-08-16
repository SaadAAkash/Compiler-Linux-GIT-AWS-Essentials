%{
int indx=1,level=0,reg=0,param=0;
char func[4000]={0};
int t[8]={0};

#include <stdio.h>
#include <string.h>

char* putLevel(char* str,char* ret){
	
	int i;
	strcpy(ret,str);
	int len=strlen(str);
	for(i=0;i<len-1;i++){
		if(!strncmp(str+i,"#",1)){
			char temp[5]={0};
			sprintf(temp,"%d",level++);
			int x=level-1;
			char part2[200]={0};
			strcpy(part2,str+i+2);
			str[i]=0;

			char ret2[300]={0};
			putLevel(part2,ret2);
			sprintf(ret,"%s%s\n%sL%d:\n",str,temp,ret2,x);
			return ret;		
		}
	}
	
        return ret;
}

char* whileloop(char* s,char* res){

	
	char* part2 = strstr(s,"#");
	int len=strlen(s)-strlen(part2);
	char part1[200]={0};
	char* partt=strncpy(part1,s,len);
	char temp[200]={0};
	part2[0]=' ';
	sprintf(temp,"L%d:\n%s%d%s",level++,partt,level,part2);
	strcpy(res,temp);
	return res;

}
char ret[200]={0};
char* countarg(char* s, int* count){
	char var[10][50];
	int i=0,j;
	char *tok;
	tok=strtok(s,",");
	while(tok!=NULL){
		strcpy(var[i++],tok);
		tok=strtok(NULL,",");
	}
	char temp[100];
	strcpy(ret,"");
	int start=indx;
	for(j=0;j<i;j++){
		sprintf(temp,"t%d = %s\n",indx++,var[j]);
		strcat(ret,temp);
	}
	for(j=start;j<indx;j++){
		sprintf(temp,"param t%d\n",j);
		strcat(ret,temp);
	}
	*count=i;
	return ret;
}

void retTok(char *s,char* ret){
	
	char *tok;
	tok=strtok(s,"#");
	while(tok!=NULL){
		strcat(ret,tok);
		tok=strtok(NULL,"#");
	}
}

char* countarg2(char* s, int* count){
	char var[10][50];
	int i=0,j;
	char *tok;
	tok=strtok(s,",");
	while(tok!=NULL){
		strcpy(var[i++],tok);
		tok=strtok(NULL,",");
	}
	char temp[100];
	strcpy(ret,"");
	for(j=0;j<i;j++){
		sprintf(temp,"return %s\n",var[j]);
		strcat(ret,temp);
	}
	*count=i;
	return ret;
}

char* Load(char* s,int x,char* res)
{
	sprintf(res,"lw $t%d, %s\n",x,s);
	return res;
}

char* LoadI(char* s,int x,char* res)
{
	sprintf(res,"li $t%d, %s\n",x,s);
	return res;
}

char* LoadB(char* s,int x,char* res)
{
	int y=0;	
	if(!strcmp(s,"true"))
		y=1;	
	sprintf(res,"li $t%d, %d\n",x,y);
	return res;
}


int SubprogHead(char* s,char* res) {

	int i=0;
	char temp[50];
	int regs=retFreeReg();
	char var[20][10]={0};
	char *tok;
	tok=strtok(s,",");
	while(tok!=NULL){
		strcpy(var[i++],tok);
		tok=strtok(NULL,",");
	}
	int j=0;
	for(j=0;j<i;j++){
		sprintf(temp,"lw $t%d, %d($fp)\nsw $t%d, %s\n",regs,(j*4+4),regs,var[j]);
		strcat(res,temp);
	}
	return i;
}

void AssignSubprog(char* s, char* res){   // ( $4.asmvar , temp)

	int i=0;
	char temp[50];
	char var[20][10]={0};
	char *tok;
	tok=strtok(s,",");
	while(tok!=NULL){
		strcpy(var[i++],tok);
		tok=strtok(NULL,",");
	}
	int j=0;
	for(j=i-1;j>=0;j--){
		sprintf(temp,"sw $t%s, 0($sp)\naddi $sp, $sp, -4\n",var[j]);
		t[var[j][0]-'0']=0;
		strcat(res,temp);
	}
}

////////////////////////////////////////////////////
char* AddSub(int t1,int t2,char*op,char *res)
{
	char temp[50]={0};
	sprintf(temp,"%s $t%d, $t%d, $t%d\n",op,t1,t1,t2);
	strcpy(res,temp);
	return res;
}


char* MulDiv(int t1,int t2,char*op,char *res)   //MulDiv($1.asmret,$3.asmret,"div",temp); 
{
	char temp[50]={0};
	sprintf(temp,"%s $t%d, $t%d\nmflo $t%d\n",op,t1,t2,t1);
	strcpy(res,temp);
	return res;
}

char* RelationSum(int t1,int t2,char*op,char* res){
	
	char temp[50]={0};
	sprintf(temp,"%s $t%d, $t%d, $t%d\n",op,t1,t1,t2);
	strcpy(res,temp);
	return res;
}

//////////////////////////////////////////////////

int retFreeReg()
{

	int i=0;
	for(i=0;i<8;i++)
		if(t[i]==0)
			return i;
	return 1;
}


///////////////////////////////////////////////////////////////////

char block[30][500]={0};
int id=0;

void myReplace(char var[][200],int x,int y,char r,char* rep){

	int i,j;
	for(i=x;i<=y;i++){
		for(j=1;j<strlen(var[i]);j++){
			if(var[i][j]==r){
				char temp[80]={0},ret[200]={0};			
				strcpy(temp,var[i]+j+1);
				var[i][j]=0;
				sprintf(ret,"%s%s%s",var[i],rep,temp);
				strcpy(var[i],ret);
			}
		}
	}	

}

void optimize(char var[][200],int x,int y){

	int i;
	for(i=x; i<=y;i++){
		char* p=strstr(var[i],"=t");
		if(p!=NULL && strlen(var[i])<6){
			char z=var[i][0];
			char temp[10]={0};
			strcpy(temp,p+1);
			myReplace(var,i+1,y,z,temp);
		}

	}


}

void divBlock(char var[][200],int i,int j)  //basic block
{

	char ret[500]={0};
	int x;
	for(x=i;x<=j;x++){
		strcat(ret,var[x]);
		strcat(ret,"\n");
	}
	strcpy(block[id++],ret);  //block
}

void after_optimi(char var[][200],int len){

	int i=0,last=0;
	for(i=0;i<len;i++){
		char * p;
  		p= strstr (var[i],"goto");  //char *strstr(const char *haystack, const char *needle)
		if(p!=NULL){
			optimize(var,last,i);
			divBlock(var,last,i);  //divide block
			last=i+1;
		}
	}
	divBlock(var,last,len-1);
	printf("\n<-----After Optimization--------->\n\n");
	for(i=0;i<id;i++)
		printf("%s",block[i]);

}


void outputGen(char* str){
	
	freopen("out.txt","w",stdout);
	printf("%s\n",str);

	char *tok;
	int i=0;

	char var[500][200]={0};

	tok=strtok(str,"\n");  //new line alada

	while(tok!=NULL){
		strcpy(var[i++],tok);
		tok=strtok(NULL,"\n");
	}
	after_optimi(var,i);  //newlinesarray & its size
	
}

%}

%union {
    struct prop{
     char *str, *ret, *asmbly, *asmvar;
     int asmret;
  } s;
}

%type <s> assignment vars exprs expr guard 
%type <s> disjunction conjunction negation relation returnstmts
%type <s> sum term factor subprogram subprogramDecl heading body
%type <s> selection stmt stmts iteration alts alt

%token <s> NUM REAL_NUM ID TRUE FALSE
%token ADD SUB MUL DIV
%token COMMA SEMICOLON ASSIGN OPEN CLOSE RET OPEN2 CLOSE2
%token AND OR NOT LT LEQ EQ NEQ GEQ GTH IF FI DO OD COLON QUES
%%

program:
 stmts {
	
	//all print
	outputGen($1.str);
	
}

;

stmts:
stmt 	{
	$$=$1; 
	char temp[5000]={0}; 
	sprintf(temp,"%s",$1.asmbly); 
	$$.asmbly=strdup(temp); 
	sprintf(temp,"%s",$1.str); 
	$$.str=strdup(temp);
}
| stmts SEMICOLON stmt {  char temp[8000]={0};
			sprintf(temp,"%s%s",$1.asmbly,$3.asmbly); $$.asmbly=strdup(temp);t[$3.asmret]=0; 
			sprintf(temp,"%s%s",$1.str,$3.str); $$.str=strdup(temp); }
| error stmt{
     $$ = $2;
     yyerrok  ;
     yyclearin;

}
|stmt error{
     $$ = $1;
     yyerrok  ;
     yyclearin;

}
    
;

stmt: { $$.str = strdup(""); $$.asmbly = strdup(""); }
| selection {$$ = $1;}
| iteration {$$ = $1; }
| assignment {$$ = $1;}
| subprogramDecl { $$=$1;}
| selection error 
 {
    	char str[500]={0};
	strcpy(str,"error is here\n"); strcat(str,$1.asmbly);$$.asmbly = strdup(str);
	printf("%s",$$.asmbly);
     	yyerrok  ;
     	yyclearin;
}
|error selection  
 {
   	char str[500]={0};strcpy(str,"error is here\n"); strcat(str,$2.asmbly);$$.asmbly = strdup(str);
     	yyerrok  ;
     	yyclearin;
	printf("%s",$$.asmbly);
}
| iteration error 
 {
	char str[500]={0};strcpy(str,"error is here\n"); strcat(str,$1.asmbly);$$.asmbly = strdup(str);
     	yyerrok  ;
     	yyclearin;
	printf("%s",$$.asmbly);
}
|error iteration
 {	char str[500]={0};strcpy(str,"error is here\n"); strcat(str,$2.asmbly);$$.asmbly = strdup(str);
  	yyerrok  ;
     	yyclearin;
	printf("%s",$$.asmbly);
}
| assignment error 
 {
    	char str[500]={0};strcpy(str,"error is here\n"); strcat(str,$1.asmbly);
	$$.asmbly = strdup(str);
     	yyerrok  ;
     	yyclearin;
	printf("%s",$$.asmbly);
}
|error assignment
 {	char str[500]={0};strcpy(str,"error is here\n"); strcat(str,$2.asmbly);
	$$.asmbly = strdup(str);
     	yyerrok  ;
     	yyclearin;
	printf("%s",$$.asmbly);
}

;

subprogramDecl: heading body
{
	char temp[1000]={0};
	sprintf(temp,"%s%s",$1.asmbly,$2.asmbly);	
	$$.asmbly=strdup(temp);
	strcpy(func,temp);
	$$.asmbly=strdup("");
	};

heading: ID OPEN vars CLOSE  //heading → id(args)
{
	char temp[500]={0};
	param=SubprogHead($3.ret,temp);
	sprintf($$.asmbly,"%s:\nmove $fp, $sp\nsw $ra, 0($sp)\naddi $sp, $sp, -4\n%s",$1.ret,temp);
};

body: OPEN2 stmts returnstmts CLOSE2
{
	$$.asmbly=strdup($2.asmbly);
	strcat($$.asmbly,$3.asmbly);

};

returnstmts: RET exprs{
	
	char temp[200];
	char temp2[600]={0};
	retTok($2.asmbly,temp2);
	$2.asmbly=strdup(temp2);

	int x=(param+2)*4;
	sprintf(temp,"%smove $a0, $t%d\nlw $ra, 4($sp)\naddi $sp, $sp, %d\nlw $fp, 0($sp)\njr $ra\n",$2.asmbly,$2.asmret,x);
	t[$2.asmret]=0;
	$$.asmbly=strdup(temp);
}
| RET {
	char temp[200];
	int x=(param+2)*4;
	sprintf(temp,"lw $ra, 4($sp)\naddi $sp, $sp, %d\nlw $fp, 0($sp)\njr $ra\n",x);
	$$.asmbly=strdup(temp);
};



selection :
IF alts FI{ $$=$2;char temp[500]={0}; putLevel($2.str,temp); $$.str=strdup(temp); putLevel($2.asmbly,temp);  $$.asmbly=strdup(temp);
}
/*| error alts FI{    	$$ = $2;	}
| IF alts error{  	$$ = $2;	}*/
;

iteration:
DO alts OD { 
$$=$2; char temp[500]={0}; whileloop($2.str,temp); $$.str=strdup(temp);
whileloop($2.asmbly,temp); $$.asmbly=strdup(temp);
}
/*| error alts OD{    	$$ = $2;	}
| DO alts error{ $$ = $2;	}*/
;
alts:
alt {  $$ = $1;}
| alts COLON alt  {char temp[500]={0}; sprintf(temp,"%s%s",$1.str,$3.str); $$.str=strdup(temp);
			sprintf($$.asmbly,"%s%s",$1.asmbly,$3.asmbly); //printf("%s",$$.asmbly); 
}
;

alt:
guard QUES stmts {

	int label1=level++;
	int label2=level++;
	char temp[50]={0};
	sprintf(temp,"li $a0, 0\nbeq $t%d, $a0, L%d\n",$1.asmret,label1);
	t[$1.asmret]=0;
	sprintf($$.asmbly,"%s%s%sb L#\nL%d:\n",$1.asmbly,temp,$3.asmbly,label1);
	$$.str=strdup("");
	char temp2[100]={0};
	sprintf(temp2,"%sif %s then goto L%d:\ngoto L%d\nL%d:\n%sgoto L#\nL%d:\n",$1.str,$1.ret,label1,label2,label1,$3.str,label2);
	$$.str=strdup(temp2);
}
;

guard:
expr {$$ = $1;
}
;

assignment: vars ASSIGN exprs { 
	
	char var[10][50], exp[10][50], asmb[10][50],asmv[10][500]={0};
	int i=0,x,j=0,k=0;
	
	int countVarok = 0, countExprok = 0;	
	char *tok;
	sprintf($$.str, "%s%s", $1.str,$3.str);
	tok=strtok($1.ret,",");
	while(tok!=NULL){
		strcpy(var[countVarok++],tok);
		tok=strtok(NULL,",");
	}	
	tok=strtok($3.ret,",");
	while(tok!=NULL){
		strcpy(exp[countExprok++],tok);
		tok=strtok(NULL,",");
	}
	tok=strtok($3.asmvar,",");
	while(tok!=NULL){
		strcpy(asmb[k++],tok);
		tok=strtok(NULL,",");
	}
	k=0;
	//printf("%s",$3.asmbly);
	tok=strtok($3.asmbly,"#");
	while(tok!=NULL){
		strcpy(asmv[k++],tok);
		tok=strtok(NULL,"#");
	}
	
	if(countVarok != countExprok)
		strcat($$.str,"Invalid Assignment!!\n");
	else if(countVarok==1){
		char temp[50];
		sprintf(temp,"%s=%s\n",var[0],$3.ret);
		strcat($$.str,temp);
		sprintf($$.asmbly, "%s%s", $1.asmbly,$3.asmbly);
		sprintf(temp,"sw $t%d, %s\n",$3.asmret,$1.ret);
		strcat($$.asmbly,temp);
		t[$3.asmret]=0;
	}
	else{
		sprintf($$.asmbly, "%s", $1.asmbly);
		//printf("%s",$1.asmbly);
		for(x=0;x<i;x++){
			char temp[50];
			sprintf(temp,"%s=%s\n",var[x],exp[x]);
			strcat($$.str,temp);
			sprintf(temp,"%ssw $t%s, %s\n",asmv[x],asmb[x],var[x]);
			strcat($$.asmbly,temp);
			t[asmb[x][0]-'0']=0;
		}
	}

}
| vars ASSIGN subprogram ASSIGN exprs
{
    	/*int count1=0,count2=0;
	char v[200]={0};
	strcpy(v,countarg2($1.ret,&count1));
    	char *e=countarg($5.ret,&count2);
	char temp[50];
	sprintf(temp,"call %s, %d, %d\n", $3.ret,count2,count1);
	strcat($$.str,e);
	strcat($$.str,temp);
	strcat($$.str,v);*/
	char temp2[600]={0};
	retTok($5.asmbly,temp2);
	$5.asmbly=strdup(temp2);
    	char temp[500]={0};
	AssignSubprog($5.asmvar,temp);
	$$.asmbly=strdup("");
	sprintf($$.asmbly,"%ssw $fp, 0($sp)\naddi $sp, $sp, -4\n%sb %s\nsw $a0, %s\n",$5.asmbly,temp,$3.ret,$1.ret);
	//printf("%s",$$.asmbly);
	
}
|ASSIGN subprogram ASSIGN exprs
{    	
	/*int count1=0,count2=0;
    	char *e=countarg($4.ret,&count2);
	char temp[50];
	sprintf(temp,"call %s, %d, %d\n", $2.ret,count2,count1);
	$$=$2;
	strcpy($$.str,"");
	strcat($$.str,e);
	strcat($$.str,temp);*/
	char temp2[600]={0};
	retTok($4.asmbly,temp2);
	$4.asmbly=strdup(temp2);

	char temp[500]={0};
	AssignSubprog($4.asmvar,temp);
	$$.asmbly=strdup("");
	sprintf($$.asmbly,"%ssw $fp, 0($sp)\naddi $sp, $sp, -4\n%sb %s\n",$4.asmbly,temp,$2.ret);
	//printf("%s",$$.asmbly);
	
}
|vars ASSIGN subprogram ASSIGN
{
    	int count1=0,count2=0;
	char *v=countarg2($1.ret,&count1);
	char temp[200];
	sprintf(temp,"sw $fp, 0($sp)\naddi $sp, $sp, -4\nb %s\nsw $a0, %s\n",$3.ret,$1.ret);
	$$.asmbly=strdup(temp);
	sprintf(temp,"call %s, %d, %d\n", $3.ret,count2,count1);
	strcat($$.str,temp);
	strcat($$.str,v);
}
|ASSIGN subprogram ASSIGN
{
	$$=$2;   	
	int count1=0,count2=0;
	char temp[50];
	sprintf(temp,"sw $fp, 0($sp)\naddi $sp, $sp, -4\nb %s\n",$2.ret);
	$$.asmbly=strdup(temp);
	sprintf(temp,"call %s, %d, %d\n", $2.ret,count2,count1);
	strcpy($$.str,"");
	strcat($$.str,temp);
}
;

vars: ID { $$ = $1;}
    | vars COMMA ID { strcpy($$.ret,$1.ret); strcat($$.ret,","); strcat($$.ret, $3.ret); sprintf($$.str,"%s%s",$1.str, $3.str);
			sprintf($$.asmbly,"%s%s",$1.asmbly,$3.asmbly); }
;
exprs: expr { $$ = $1 ; }
    | exprs COMMA expr { strcpy($$.ret,$1.ret); strcat($$.ret,","); strcat($$.ret, $3.ret); sprintf($$.str,"%s%s",$1.str, $3.str);
			sprintf($$.asmbly,"%s#%s",$1.asmbly,$3.asmbly);$$.asmvar = strdup(""); sprintf($$.asmvar,"%s,%s",$1.asmvar,$3.asmvar);
			}
;

subprogram:
ID {$$ = $1;}
;
expr: disjunction { $$= $1; }
;
disjunction: conjunction { $$ = $1;}
	| disjunction OR conjunction {char st[50];sprintf(st,"t%d=%s | %s\n",indx,$1.ret,$3.ret); 
					sprintf($$.str,"%s%s%s",$1.str,$3.str,st);sprintf($$.ret,"t%d",indx++); char temp[200]={0}; 
					RelationSum($1.asmret,$3.asmret,"or",temp); sprintf($$.asmbly,"%s%s%s",$1.asmbly,$3.asmbly,temp);
					$$.asmret=$1.asmret;sprintf($$.asmvar,"%d",$1.asmret); t[$3.asmret]=0;}
;
conjunction: negation {$$ = $1; }
	| conjunction AND negation { char st[50]; sprintf(st,"t%d=%s & %s\n",indx,$1.ret,$3.ret); 
				     sprintf($$.str,"%s%s%s",$1.str,$3.str,st); sprintf($$.ret,"t%d",indx++); char temp[200]={0}; 
				     RelationSum($1.asmret,$3.asmret,"and",temp); sprintf($$.asmbly,"%s%s%s",$1.asmbly,$3.asmbly,temp);
				     $$.asmret=$1.asmret;sprintf($$.asmvar,"%d",$1.asmret); t[$3.asmret]=0; }
;
negation : relation {$$ = $1; }
	| NOT relation { char st[50]; sprintf(st,"~%s",$2.ret); $$.str=$2.str;$$.ret=st;	
	 		 sprintf($$.asmbly,"%snot t%d t%d\n",$2.asmbly,$2.asmret,$2.asmret);sprintf($$.asmvar,"%d",$2.asmret); 					$$.asmret=$2.asmret;}
;
relation: sum {$$ = $1; }
	| sum LT sum {char st[50];sprintf(st,"t%d=%s < %s\n",indx,$1.ret,$3.ret); sprintf($$.str,"%s%s%s",$1.str,$3.str,st);
			sprintf($$.ret,"t%d",indx++); char temp[200]={0}; 
			RelationSum($1.asmret,$3.asmret,"slt",temp); sprintf($$.asmbly,"%s%s%s",$1.asmbly,$3.asmbly,temp);
			$$.asmret=$1.asmret;sprintf($$.asmvar,"%d",$1.asmret); t[$3.asmret]=0; }
	| sum LEQ sum {char st[50];sprintf(st,"t%d=%s <= %s\n",indx,$1.ret,$3.ret); sprintf($$.str,"%s%s%s",$1.str,$3.str,st);
			sprintf($$.ret,"t%d",indx++);char temp[200]={0}; 
			RelationSum($1.asmret,$3.asmret,"sle",temp); sprintf($$.asmbly,"%s%s%s",$1.asmbly,$3.asmbly,temp);
			$$.asmret=$1.asmret;sprintf($$.asmvar,"%d",$1.asmret); t[$3.asmret]=0; }
	| sum EQ sum {char st[50];sprintf(st,"t%d=%s = %s\n",indx,$1.ret,$3.ret); sprintf($$.str,"%s%s%s",$1.str,$3.str,st);
			sprintf($$.ret,"t%d",indx++); char temp[200]={0}; 
			RelationSum($1.asmret,$3.asmret,"seq",temp); sprintf($$.asmbly,"%s%s%s",$1.asmbly,$3.asmbly,temp);
			$$.asmret=$1.asmret;sprintf($$.asmvar,"%d",$1.asmret); t[$3.asmret]=0; }
	| sum NEQ sum {char st[50];sprintf(st,"t%d=%s ~= %s\n",indx,$1.ret,$3.ret); sprintf($$.str,"%s%s%s",$1.str,$3.str,st);
			sprintf($$.ret,"t%d",indx++); char temp[200]={0}; 
			RelationSum($1.asmret,$3.asmret,"sne",temp); sprintf($$.asmbly,"%s%s%s",$1.asmbly,$3.asmbly,temp);
			$$.asmret=$1.asmret;sprintf($$.asmvar,"%d",$1.asmret); t[$3.asmret]=0; }
	| sum GEQ sum {char st[50];sprintf(st,"t%d=%s >= %s\n",indx,$1.ret,$3.ret); sprintf($$.str,"%s%s%s",$1.str,$3.str,st);
			sprintf($$.ret,"t%d",indx++); char temp[200]={0}; 
			
				RelationSum($1.asmret,$3.asmret,"sge",temp); 
			sprintf($$.asmbly,"%s%s%s",$1.asmbly,$3.asmbly,temp);
			$$.asmret=$1.asmret;sprintf($$.asmvar,"%d",$1.asmret); t[$3.asmret]=0; }
	| sum GTH sum {char st[50];sprintf(st,"t%d=%s > %s\n",indx,$1.ret,$3.ret); sprintf($$.str,"%s%s%s",$1.str,$3.str,st);
			sprintf($$.ret,"t%d",indx++); char temp[200]={0};t[$3.asmret]=0; 
				RelationSum($1.asmret,$3.asmret,"slt",temp); 
			
			sprintf($$.asmbly,"%s%s%s",$1.asmbly,$3.asmbly,temp);

			$$.asmret=$1.asmret; sprintf($$.asmvar,"%d",$1.asmret); }
;
sum: term { $$ = $1;}
    | SUB term { 
			char st[50];sprintf(st,"-%s\n",$2.ret); $$.ret=st; sprintf($$.asmbly,"%snegu t%d t%d\n",$2.asmbly,$2.asmret,$2.asmret);
			$$.asmret=$2.asmret; 

			sprintf($$.asmvar,"%d",$2.asmret);//$$.asmbly=Load(st,$$.asmbly);

		}
    | sum ADD term {
				char st[50]; sprintf(st,"t%d=%s + %s\n",indx,$1.ret,$3.ret);sprintf($$.str,"%s%s%s",$1.str,$3.str,st);
			 sprintf($$.ret,"t%d",indx++); char temp[200]={0}; 

			 AddSub($1.asmret,$3.asmret,"add",temp); sprintf($$.asmbly,"%s%s%s",$1.asmbly,$3.asmbly,temp);

			 $$.asmret=$1.asmret; sprintf($$.asmvar,"%d",$1.asmret);t[$3.asmret]=0;
		}
    | sum SUB term {char st[50]; sprintf(st,"t%d=%s - %s\n",indx,$1.ret,$3.ret);sprintf($$.str,"%s%s%s",$1.str,$3.str,st);
			 sprintf($$.ret,"t%d",indx++); char temp[200]={0}; 

			 AddSub($1.asmret,$3.asmret,"sub",temp); sprintf($$.asmbly,"%s%s%s",$1.asmbly,$3.asmbly,temp);

			 $$.asmret=$1.asmret;sprintf($$.asmvar,"%d",$1.asmret); t[$3.asmret]=0;
		}
;
term: factor { $$ = $1 ;}
    | term MUL factor { 
		    sprintf($$.str,"t%d=%s * %s\n",indx,$1.ret,$3.ret); 
		    sprintf($$.ret,"t%d",indx++); 
			char temp[200]={0}; 

			MulDiv($1.asmret,$3.asmret,"multu",temp); 

			sprintf($$.asmbly,"%s%s%s",$1.asmbly,$3.asmbly,temp);
			$$.asmret=$1.asmret;

			sprintf($$.asmvar,"%d",$1.asmret); t[$3.asmret]=0; }

    | term DIV factor {
			sprintf($$.str,"t%d=%s / %s\n",indx,$1.ret,$3.ret); 
			sprintf($$.ret,"t%d",indx++);
			char temp[200]={0}; 
			
			MulDiv($1.asmret,$3.asmret,"div",temp); 

			sprintf($$.asmbly,"%s%s%s",$1.asmbly,$3.asmbly,temp);
			$$.asmret=$1.asmret;

			sprintf($$.asmvar,"%d",$1.asmret); 
			t[$3.asmret]=0;

			}
;
factor:  NUM { 
		$1.asmret=retFreeReg(); 
		LoadI($1.ret,$1.asmret,$1.asmbly);
		sprintf($1.asmvar,"%d",$1.asmret);
		t[$1.asmret]=1; $$ = $1; }

    | REAL_NUM { $1.asmret=retFreeReg(); LoadI($1.ret,$1.asmret,$1.asmbly);sprintf($1.asmvar,"%d",$1.asmret);t[$1.asmret]=1;$$=$1;  }
    | ID { $1.asmret=retFreeReg(); Load($1.ret,$1.asmret,$1.asmbly);t[$1.asmret]=1;sprintf($1.asmvar,"%d",$1.asmret);$$=$1;
	 }

    | OPEN expr CLOSE { sprintf($2.asmvar,"%d",$2.asmret);$$ = $2; 
			}

    | TRUE { $1.asmret=retFreeReg(); LoadB($1.ret,$1.asmret,$1.asmbly);t[$1.asmret]=1;sprintf($1.asmvar,"%d",$1.asmret);$$=$1; }
    | FALSE { $1.asmret=retFreeReg(); LoadB($1.ret,$1.asmret,$1.asmbly);sprintf($1.asmvar,"%d",$1.asmret);t[$1.asmret]=1;$$=$1 ;}
; 

%%


yyerror(char *s)
{
	//fprintf(stderr, "error: %s\n", s);
}
