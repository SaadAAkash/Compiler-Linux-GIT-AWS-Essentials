%{
#include <stdio.h>
#include<string.h>
#include<stdlib.h>


extern FILE *yyin;

int indxakash;
int labelakash;
char *curPlaceakash;

int index_of_t=0;
int variable=0;
int freeMode=0;

char varList[100][50];
char expList[100][50];

char asmbList[100][50];

char* codeList[100];

char argList[100][50];		

int argCount=0;
int varCount=0;
int expCount=0;

int label=0;

int arlength;
char* arlist[100];
FILE *fout;


char* t_incre() {
	char* str=(char *)malloc(50*sizeof(char)); 
	str[0] = 't';
	sprintf(str+1,"%d",variable++);
	return str;
}


char* mips_li(char* s)
{
	char* str =(char *) malloc(100);
	sprintf(str,"li $a0 %s\n",s);
	return str;
}


char* newSuperLabel()
{
	char* str="<<This is a mother label>>"; 
	return str;
}

// place 0 in ! at the end  
char* fit(char* temp)
{
	int len=strlen(temp);
	if(temp[len-1]=='!')
		temp[len-1]=0;
	return temp;

}


/////////////////strung manipulating : replace & appending /////////////////////////


char* str_append(const char *s1, const char *s2)
{
	int l1=strlen(s1);
	int l2=strlen(s2);
	char* res = (char*)malloc(l1+l2+2 ) ;
	int i,j;
	for(i=0;i<l1;i++)
		res[i]=s1[i];
	
	for(j=0;j<l2;j++,i++)
		res[i]=s2[j];
	res[i]=0;
	return res;
}

char *replace_str(char *str, char *orig, char *rep)
{
	char* buffer=(char *)malloc(strlen(str)*sizeof(char)); 
	char *p;
	int i=0;
	while(str[i])
	{
	    if (!(p=strstr(str+i,orig)))  
	    {
			return strcat(buffer,str+i);
	    }
	    strncpy(buffer+strlen(buffer),str+i,(p-str)-i);
	    buffer[p-str] = '\0';
	    strcat(buffer,rep);
	    i=(p-str)+strlen(orig);
	}
	return buffer;

}


///////////////labels str ////////////////////////////////

char* newlabel()
{
	char* str=(char *)malloc(50*sizeof(char)); 
	str[0] = 'L';
	sprintf(str+1,"%d ",label++);
	return str;
}

char* setLabel(char* label)
{
	char* str=(char *)malloc((6+strlen(label))*sizeof(char)); 
	sprintf(str,"%s:\n",label);
	return str;
}

char* genLabel(char* label)
{
	char* str=(char *)malloc((8+strlen(label))*sizeof(char)); 
	sprintf(str,"goto %s\n",label);
	return str;
}


////////////////branch /////////////////


char* genAsmLabel(char* label)
{
	char* str=(char *)malloc((3+strlen(label))*sizeof(char)); 
	sprintf(str,"b %s\n",label);
	return str;
}




////////////////////////ADD DUB MULT DIV MIPS ///////////////////
char* addAssembly(char* s1,char* s2)
{
	
	char* cd=(char *) malloc(1000);
	char* str =(char *) malloc(100);
	cd=str_append("",s1);
	sprintf(str,"sw $a0 0($sp) -->");
	cd =str_append(cd,str);
	sprintf(str,"addiu $sp $sp-4 -->");
	cd=str_append(cd,str);
	cd=str_append(cd,s2);
	sprintf(str,"lw $t1 4($sp) -->");
	cd=str_append(cd,str);
	sprintf(str,"add $a0 $a0 $t1 -- >");
	cd=str_append(cd,str);
	sprintf(str,"addiu $sp $sp 4\n");
	cd=str_append(cd,str);
	char* final=strdup(cd);
	free(cd);
	return final;
}

char* subAssembly(char* s1,char* s2)
{
	
		
	char* cd=(char *) malloc(1000);
	char* str =(char *) malloc(100);
	cd=str_append("",s1);
	sprintf(str,"sw $a0 0($sp)\n");
	cd =str_append(cd,str);
	sprintf(str,"addiu $sp $sp-4\n");
	cd=str_append(cd,str);
	cd=str_append(cd,s2);
	sprintf(str,"lw $t1 4($sp)\n");
	cd=str_append(cd,str);
	sprintf(str,"sub $a0 $a0 $t1\n");
	cd=str_append(cd,str);
	sprintf(str,"addiu $sp $sp 4\n");
	cd=str_append(cd,str);
	char* final=strdup(cd);
	free(cd);
	return final;
}

char* multAssembly(char* s1,char* s2)
{

	char* cd=(char *) malloc(1000);
	char* str =(char *) malloc(100);
	cd=str_append("",s1);
	sprintf(str,"sw $a0 0($sp)\n");
	cd =str_append(cd,str);
	sprintf(str,"addiu $sp $sp-4\n");
	cd=str_append(cd,str);
	cd=str_append(cd,s2);
	sprintf(str,"lw $t1 4($sp)\n");
	cd=str_append(cd,str);

	sprintf(str,"multu $a0 $t1\n");
	cd=str_append(cd,str);
	sprintf(str,"move $a0 $lo\n");
	cd=str_append(cd,str);
	sprintf(str,"addiu $sp $sp 4\n");
	cd=str_append(cd,str);
	char* final=strdup(cd);
	free(cd);
	return final;
}


char* div_asm(char* s1,char* s2)
{
	
		
	char* cd=(char *) malloc(1000);
	char* str =(char *) malloc(100);
	cd=str_append("",s1);
	sprintf(str,"sw $a0 0($sp)\n");
	cd =str_append(cd,str);
	sprintf(str,"addiu $sp $sp-4\n");
	cd=str_append(cd,str);
	cd=str_append(cd,s2);
	sprintf(str,"lw $t1 4($sp)\n");
	cd=str_append(cd,str);
	sprintf(str,"div $a0 $t1\n");
	cd=str_append(cd,str);
	sprintf(str,"move $a0 $lo\n");
	cd=str_append(cd,str);
	sprintf(str,"addiu $sp $sp 4\n");
	cd=str_append(cd,str);
	char* final=strdup(cd);
	free(cd);
	return final;
}

////////////////////////////////////

char* printARList()
{
	int i=0;
	char* cd="";
	char temp[100];
	for(i=0;i<arlength;i++)
	{
		sprintf(temp,"%d($SP)->",(arlength-i)*4);
		cd=str_append(cd,temp);
		cd=str_append(cd,arlist[i]);
	}
	cd=str_append(cd,"$SP->\n");
	return cd;
}

char* funcDefn(char* label,char* funcBody)
{
	FILE*  foutBeforeExit = fopen("ARBeforeExit.txt", "w");
	FILE*  foutAfterCall = fopen("ARAfterCall.txt", "w");
	char* str =(char *) malloc(100);

	char* cd=str_append(setLabel(label),"move $fp $sp\n");	//Now fp=end of the frame for callee	
	sprintf(str,"sw $ra 0($sp)\n");
	cd=str_append(cd,str);
	sprintf(str,"addiu $sp $sp -4\n");
	cd=str_append(cd,str);

	cd=str_append(cd,funcBody);
	fprintf(foutBeforeExit,printARList());
	sprintf(str,"lw $ra 4($sp)\n");
	cd=str_append(cd,str);
	int z=4*argCount+8;
	sprintf(str,"addiu $sp $sp %d\n",z);

	cd=str_append(cd,str);
	sprintf(str,"lw $fp 0($sp)\n");
	cd=str_append(cd,str);
	sprintf(str,"jr $ra \n");
	cd=str_append(cd,str);
	//cd=str_append(cd,"---------------------\n");
	arlength=0;
	fprintf(foutAfterCall,printARList());
	fclose(foutBeforeExit);
	fclose(foutAfterCall);
	return strdup(cd);
}


char* funcCall(char* name)
{
	arlength=0;

	FILE*  foutBeforeCall = fopen("ARBeforeCall.txt", "w");	
	FILE*  foutOnEntry=fopen("AROnEntry.txt", "w");
	fprintf(foutBeforeCall,printARList());

	char* cd;
	char* str =(char *) malloc(100);
	cd="<<Function Has been Called>>\n";
	arlist[arlength++]="old fp\n";
	sprintf(str,"sw $fp 0($sp)\n");
	cd=str_append(cd,str);
	sprintf(str,"addiu $sp $sp -4\n");
	cd=str_append(cd,str);


	int i=expCount-1;
	for(;i>=0;i--)
	{
		arlist[arlength++]=str_append(expList[i],"\n");
		cd=str_append(cd,asmbList[i]);
		sprintf(str,"sw $a0 0($sp)\n");
		cd=str_append(cd,str);
		sprintf(str,"addiu $sp $sp -4\n");
		cd=str_append(cd,str);
	}
	sprintf(str,"jal %s\n",name);
	cd=str_append(cd,str);

	fprintf(foutOnEntry,printARList());
	fclose(foutOnEntry);
	
	arlist[arlength++]="fp->return address\n";
	fclose(foutBeforeCall);

	return cd;
}


%}

/*When the value is referenced through a $$ or $n construction, yacc will automatically insert the appropriate union name, so that no unwanted conversions will take place*/
%union {
  struct {

	char* var;
	char* asmbly;	

	char* next;
	char* code;
	
	char* trueLabel;
	char* falseLabel;
	
  } myStruct;
}

%token NUMBER
%left ADD SUB 
%left MUL 
%left DIV 
%token OP CP
%token OB CB ret
%right AssignOp 
%token id
%token Semicolon List REAL True False
%token GreaterRel GreaterEqualRel LessRel LessEqualRel NotEqualRel EqualRel Negate
%token Or And ELSEE QMark ifStart ifEnd loopStart loopEnd
/* 

program → stmts |eof
stmts → stmt | stmts ; stmt
 
stmt → ϵ | selection | iteration |assignment | returnStmt
selection → if alts fi
iteration → do alts od
alts → alt |alts :: alt
alt → guard ? stmts
guard → expr


assignment → vars := exprs 
	|vars := subprogram := exprs // takes in a list of expr as parameter and returns a list of variables
	|:= subprogram := exprs // takes in a list of expr as parameter and does not return anything
	|vars := subprogram := //no parameters but returns variables
	|:= subprogram := // no parameter and no arguments

subprogram → id
vars → id |vars , id
exprs → expr | exprs , expr
expr → disjunction
disjunction → conjunction | disjunction or conjunction
conjunction → negation | conjunction & negation
negation → relation| ~ relation
relation → sum
|sum < s.um
|sum <= sum
|sum = sum
|sum ~= sum
|sum>= sum
|sum> sum

sum → term | - term | sum + term | sum - term 
term → factor | term * factor | term / factor 
factor → true | false | integer | real | id | ( expr ) 

*/

%%


program: stmts 
{ 	
	printf("%s\n",$<myStruct.code>$); 
	printf("Assembly : \n%s\n",$<myStruct.asmbly>1);
	fprintf(fout, "%s\n", $<myStruct.asmbly>1);
	fclose(fout);
};

stmts: stmt 
{ 	
	$<myStruct.code>$=$<myStruct.code>1;	
	$<myStruct.asmbly>$=$<myStruct.asmbly>1;
};

| stmts Semicolon stmt 
{ 
	char* cd=str_append($<myStruct.code>1,"\n");
	$<myStruct.code>$=str_append(cd,$<myStruct.code>3);
	char* asmb=str_append($<myStruct.asmbly>1,"\n");
	$<myStruct.asmbly>$=str_append(asmb,$<myStruct.asmbly>3);
};


stmt : 
{
	$<myStruct.code>$="";
	$<myStruct.asmbly>$="";
}
|selection 
{	
	char* label=newlabel();
	char* result=replace_str($<myStruct.code>1,"--SuperLabel--",label);
	char* asmResult=replace_str($<myStruct.asmbly>1,"--SuperLabel--",label);
	$<myStruct.next>$=label;
	$<myStruct.code>$=str_append(result,setLabel($<myStruct.next>$));
	asmResult=str_append(asmResult,setLabel($<myStruct.next>$));
	$<myStruct.asmbly>$=str_append(asmResult,"\n");
}
|iteration 
{
	char* begin=newlabel();	//Label at Start of Loop 
	char* result=replace_str($<myStruct.code>1,"--SuperLabel--",begin);
	char* asmResult=replace_str($<myStruct.asmbly>1,"--SuperLabel--",begin);
	$<myStruct.next>$=begin;	
	char* temp=fit(str_append(setLabel(begin),result));  
	$<myStruct.code>$=temp;
	char* tempAsm= fit(str_append(setLabel(begin),asmResult));
	tempAsm=str_append(tempAsm,"\n");
	$<myStruct.asmbly>$=tempAsm;
}
|assignment
{
	$<myStruct.trueLabel>$="";
	$<myStruct.falseLabel>$="";
	$<myStruct.code>$=$<myStruct.code>1;
	$<myStruct.asmbly>$=$<myStruct.asmbly>1;
}
|subprogramDecl
{
	$<myStruct.code>$=$<myStruct.code>1;
	$<myStruct.asmbly>$=$<myStruct.asmbly>1;
};

selection : ifStart alts ifEnd 
{ 
	$<myStruct.trueLabel>$=$<myStruct.trueLabel>2;
	$<myStruct.falseLabel>$=$<myStruct.falseLabel>2;
	$<myStruct.var>$=$<myStruct.var>2;
	$<myStruct.code>$=$<myStruct.code>2;
	$<myStruct.next>$=$<myStruct.next>2;
	$<myStruct.asmbly>$=$<myStruct.asmbly>2;
}
| error alts ifEnd
{
	//printf("error in if\n");
	printf("%s\n",$<myStruct.asmbly>2);
	$<myStruct.trueLabel>$=$<myStruct.trueLabel>2;
	$<myStruct.falseLabel>$=$<myStruct.falseLabel>2;
	$<myStruct.var>$=$<myStruct.var>2;
	$<myStruct.code>$=$<myStruct.code>2;
	$<myStruct.next>$=$<myStruct.next>2;
	$<myStruct.asmbly>$=$<myStruct.asmbly>2;
};

iteration : loopStart alts loopEnd 
{ 
	$<myStruct.trueLabel>$=$<myStruct.trueLabel>2;
	$<myStruct.falseLabel>$=$<myStruct.falseLabel>2;
	$<myStruct.var>$=$<myStruct.var>2;
	$<myStruct.code>$=$<myStruct.code>2;
	$<myStruct.next>$=$<myStruct.next>2;
	$<myStruct.asmbly>$=$<myStruct.asmbly>2;
}
|error alts loopEnd
{
	//printf("error in loop\n");
	printf("%s\n",$<myStruct.asmbly>2);
	$<myStruct.trueLabel>$=$<myStruct.trueLabel>2;
	$<myStruct.falseLabel>$=$<myStruct.falseLabel>2;
	$<myStruct.var>$=$<myStruct.var>2;
	$<myStruct.code>$=$<myStruct.code>2;
	$<myStruct.next>$=$<myStruct.next>2;
	$<myStruct.asmbly>$=$<myStruct.asmbly>2;

};
/*
subprogramDecl → heading body
heading → id(args)
args → id, args | id
body → "{"stmts"}"
ReturnStmt → return exprs
*/


subprogramDecl : heading body 	
{		
	$<myStruct.var>$=$<myStruct.var>1;
	$<myStruct.code>$=$<myStruct.code>2;
	$<myStruct.asmbly>$=funcDefn($<myStruct.var>1,$<myStruct.asmbly>2);	
};	

args : id List args 		
{		
	strcpy(argList[argCount++],$<myStruct.var>1);			
}		
| id		
{		
	strcpy(argList[argCount++],$<myStruct.var>1);			
};	

heading : id OP args CP		
{	

	$<myStruct.var>$=$<myStruct.var>1;		
};		

body : OB stmts returnStmt CB		
{		
	$<myStruct.code>$=$<myStruct.code>2;
	$<myStruct.asmbly>$=$<myStruct.asmbly>2;		
};

returnStmt : ret exprs		
{		
	int i=0;
	for(i=0;i<expCount;i++)
	{
		//printf("Expr %d : %s\n",i,expList[i]);

	}	
};

alts : alt 
{ 
	$<myStruct.next>$=$<myStruct.next>1;
	$<myStruct.trueLabel>$=$<myStruct.trueLabel>1;
	$<myStruct.falseLabel>$=$<myStruct.falseLabel>1;
	$<myStruct.var>$=$<myStruct.var>1;
	$<myStruct.code>$=$<myStruct.code>1;
	$<myStruct.asmbly>$=$<myStruct.asmbly>1;
}
|alts ELSEE alt 
{ 
	$<myStruct.next>$=$<myStruct.next>1=$<myStruct.next>3;
	$<myStruct.code>$=str_append($<myStruct.code>1,$<myStruct.code>3);
	$<myStruct.asmbly>$=str_append($<myStruct.asmbly>1,$<myStruct.asmbly>3);
}
;

alt : guard QMark stmts
{
	$<myStruct.trueLabel>$=$<myStruct.trueLabel>1=newlabel();
	$<myStruct.falseLabel>$=$<myStruct.falseLabel>1=$<myStruct.next>1=$<myStruct.next>$=newSuperLabel(); 	//Devise how to add label
	char first[100];
	sprintf(first,"if F %s goto %s\n",$<myStruct.var>1,$<myStruct.trueLabel>1);
	char* cd = str_append(first,$<myStruct.code>3);
	cd=str_append($<myStruct.code>1,cd);
	cd=str_append(cd,genLabel($<myStruct.falseLabel>1));
	cd=str_append(cd,setLabel($<myStruct.trueLabel>1));
	$<myStruct.code>$=cd;

	char* cda;
	char* str =(char *) malloc(100);
	cda=str_append("",$<myStruct.asmbly>1);
	sprintf(str,"li $t1 0\n");
	cda=str_append(cda,str);
	sprintf(str,"beq $a0 $t1 %s\n",$<myStruct.trueLabel>1);
	cda=str_append(cda,str);
	cda=str_append(cda,$<myStruct.asmbly>3);
	cda=str_append(cda,genAsmLabel($<myStruct.falseLabel>1));
	cda=str_append(cda,setLabel($<myStruct.trueLabel>1));
	$<myStruct.asmbly>$=cda;
};

guard : expr 
{
	$<myStruct.var>$ = $<myStruct.var>1;
	$<myStruct.code>$=$<myStruct.code>1;
	$<myStruct.asmbly>$=$<myStruct.asmbly>1;
};

assignment: vars AssignOp exprs 
{ 
	char* assign="";
	char* asmb="";
	char first[200];
	if(varCount!=expCount)
	{
		//printf("Unbalanced Number of variables(%d) & Expressions(%d)\n",varCount,expCount);
	}
	else
	{
		int i;
		for(i=0;i<varCount;i++)
		{
			//printf("%s",codeList[i]);
			assign=str_append(assign,codeList[i]);
			asmb=str_append(asmb,asmbList[i]);
			sprintf(first,"%s = %s\n",varList[i],expList[i]);
			assign=str_append(assign,first);
			//free(codeList[i]);
		}
	}
	$<myStruct.code>$=strdup(assign);
	$<myStruct.asmbly>$=strdup(asmb);
	varCount=expCount=0;
}
|vars AssignOp subprogram AssignOp exprs
{
	char* params[100];
	int i=0;
	char* assign="";
	char* asmb="";
	char first[200];
	for(i=0;i<expCount;i++)
	{	
		params[i]=t_incre();
		sprintf(first,"%s = %s\n",params[i],expList[i]);
		assign=str_append(assign,first);
	}
	for(i=0;i<expCount;i++)
	{
		sprintf(first,"param %s\n",params[i]);
		assign=str_append(assign,first);
	}
	sprintf(first,"call %s, %d, %d\n",$<myStruct.var>3,expCount,varCount);
	assign=str_append(assign,first);
	for(i=0;i<varCount;i++)
	{
		sprintf(first,"return %s\n",varList[i]);
		assign=str_append(assign,first);
	}
	$<myStruct.code>$=strdup(assign);
	$<myStruct.asmbly>$=funcCall($<myStruct.var>3);
	varCount=expCount=0;
}
|AssignOp subprogram AssignOp exprs
{
	char* params[100];
	int i=0;
	char* assign="";
	char* asmb="";
	char first[200];
	for(i=0;i<expCount;i++)
	{	
		params[i]=t_incre();
		sprintf(first,"%s = %s\n",params[i],expList[i]);
		assign=str_append(assign,first);
	}
	for(i=0;i<expCount;i++)
	{
		sprintf(first,"param %s\n",params[i]);
		assign=str_append(assign,first);
	}
	sprintf(first,"call %s, %d\n",$<myStruct.var>2,expCount);
	assign=str_append(assign,first);
	$<myStruct.code>$=strdup(assign);
	$<myStruct.asmbly>$=funcCall($<myStruct.var>2);
	varCount=expCount=0;
}
|vars AssignOp subprogram AssignOp
{
	int i=0;
	char* assign="";
	char* asmb="";
	char first[200];
	sprintf(first,"call %s, %d\n",$<myStruct.var>3,varCount);
	assign=str_append(assign,first);
	for(i=0;i<varCount;i++)
	{
		sprintf(first,"return %s\n",varList[i]);
		assign=str_append(assign,first);
	}
	$<myStruct.code>$=strdup(assign);
	varCount=expCount=0;
	$<myStruct.asmbly>$=funcCall($<myStruct.var>3);
	//printf("vars := subprogram :=\n");
	//printf("no parameters but returns variables\n");
}
|AssignOp subprogram AssignOp
{
	char first[200];
	sprintf(first,"call %s\n",$<myStruct.var>2);
	$<myStruct.code>$=strdup(first);
	$<myStruct.asmbly>$=$<myStruct.asmbly>2;
	//printf(":= subprogram :=\n");
	//printf(" no parameter and no arguments\n");
};
subprogram: id
{
	$<myStruct.var>$ = $<myStruct.var>1;
	$<myStruct.code>$=$<myStruct.code>1;
	$<myStruct.asmbly>$=$<myStruct.asmbly>1;
};

vars: id
{
	//printf("Vars -> id %d %s\n",varCount,$1);
	strcpy(varList[varCount++],$<myStruct.var>1);
}
| vars List id
{
	//printf("Inside vars -> vars,id %d %s\n",varCount,$3);
	strcpy(varList[varCount++],$<myStruct.var>3);
};

exprs: expr 
{
	//printf("Inside exprs -> expr\n");	
	//printf("%s = %s\n",varList[expCount++],$1);
	//printf("%s\n",$<myStruct.code>1);
	codeList[expCount]=malloc(strlen($<myStruct.code>1));
	strcpy(codeList[expCount],$<myStruct.code>1);
	strcpy(asmbList[expCount],$<myStruct.asmbly>1);
	strcpy(expList[expCount++],$<myStruct.var>1);	
}
|exprs List expr 
{	
	//printf("Inside exprs -> exprs,expr\n");	
	//printf("%s = %s\n",varList[expCount++],$3);
	codeList[expCount]=malloc(strlen($<myStruct.code>3));
	strcpy(codeList[expCount],$<myStruct.code>3);
	strcpy(asmbList[expCount],$<myStruct.asmbly>3);
	strcpy(expList[expCount++],$<myStruct.var>3);	
}
;

expr: disjunction
{
	//printf("Expr -> Disjunction\n",$<myStruct.asmbly>1);
	$<myStruct.var>$ = $<myStruct.var>1;
	$<myStruct.code>$=$<myStruct.code>1;
	$<myStruct.asmbly>$=$<myStruct.asmbly>1;
};

disjunction: conjunction
{
	$<myStruct.var>$=$<myStruct.var>1;
	$<myStruct.code>$=$<myStruct.code>1;
	$<myStruct.asmbly>$=$<myStruct.asmbly>1;
} 
| disjunction Or conjunction
{ 
	char* str=(char*)malloc(100* sizeof(char));	
	char* newvar=t_incre(); 
	sprintf(str,"%s = %s | %s \n", newvar, $<myStruct.var>1, $<myStruct.var>3); 
	$<myStruct.var>$=newvar;
	char *cd=str_append($<myStruct.code>1,$<myStruct.code>3);
	$<myStruct.code>$=str_append(cd,str);


	sprintf(str,"move $t1 $a0\n");
	cd=str_append($<myStruct.asmbly>1,str);
	cd=str_append(cd,$<myStruct.asmbly>3);
	sprintf(str,"or $a0 $t1 $a0\n");
	cd=str_append(cd,str);
	$<myStruct.asmbly>$=strdup(cd);

	//if(printDebug==1)printf("Or Print : %s\n",$<myStruct.code>$);
	free(cd);
	free(str);

};


conjunction: negation
{
	$<myStruct.var>$=$<myStruct.var>1;
	$<myStruct.code>$=$<myStruct.code>1;
	$<myStruct.asmbly>$=$<myStruct.asmbly>1;
}
| conjunction And negation
{
	char* str=(char*)malloc(100* sizeof(char));		
	char* newvar=t_incre(); 
	sprintf(str,"%s = %s & %s \n", newvar, $<myStruct.var>1, $<myStruct.var>3); 
	$<myStruct.var>$=newvar;
	char *cd=str_append($<myStruct.code>1,$<myStruct.code>3);
	$<myStruct.code>$=str_append(cd,str);

	sprintf(str,"move $t1 $a0\n");
	cd=str_append($<myStruct.asmbly>1,str);
	cd=str_append(cd,$<myStruct.asmbly>3);
	sprintf(str,"and $a0 $t1 $a0\n");
	cd=str_append(cd,str);
	$<myStruct.asmbly>$=strdup(cd);

	free(cd);
	free(str);

	//printf("Conjunction and Negation\n");
};

//negation → relation| ~ relation

negation: relation
{
	$<myStruct.var>$=$<myStruct.var>1;
	$<myStruct.code>$=$<myStruct.code>1;
	$<myStruct.asmbly>$=$<myStruct.asmbly>1;
}
| Negate relation
{
	char rel[30]; 
	rel[0] = '~'; 
	sprintf(rel+1,"%s",$<myStruct.var>2);

	char* str=(char*)malloc(100* sizeof(char));		
	char* newvar=t_incre(); 
	sprintf(str,"%s = %s\n",newvar,rel); 
	$<myStruct.var>$=newvar;
	char *cd=strdup($<myStruct.code>2);
	$<myStruct.code>$=str_append(cd,str);

	sprintf(str,"not $a0 $a0\n");
	$<myStruct.asmbly>$=str_append($<myStruct.asmbly>2,str);
	free(cd);
	free(str);
};
/*
relation → sum
|sum < sum
|sum <= sum
|sum = sum
|sum ~= sum
|sum>= sum
|sum> sum
*/

relation: sum
{
	$<myStruct.var>$=$<myStruct.var>1;
	$<myStruct.code>$=$<myStruct.code>1;
	$<myStruct.asmbly>$=$<myStruct.asmbly>1;
}
| sum LessRel sum
{
	char* str=(char*)malloc(100* sizeof(char));		
	char* newvar=t_incre(); 
	sprintf(str,"%s = %s < %s \n", newvar, $<myStruct.var>1, $<myStruct.var>3); 
	$<myStruct.var>$=newvar;
	char *cd=str_append($<myStruct.code>3,$<myStruct.code>1);
	$<myStruct.code>$=str_append(cd,str);
	char *asmb=(char*)malloc(100* sizeof(char));
	sprintf(asmb,"move $t1 $a0\n");
	char* cda=str_append($<myStruct.asmbly>3,asmb);
	sprintf(asmb,"slt $a0 $a0 $t1\n");
	cda=str_append(cda,$<myStruct.asmbly>1);
	$<myStruct.asmbly>$=str_append(cda,asmb);

	free(cda);
	free(cd);
	free(str);
	free(asmb);
	//printf("relation -> sum < sum\n");
}
| sum LessEqualRel sum
{
	char* str=(char*)malloc(100* sizeof(char));		
	char* newvar=t_incre(); 
	sprintf(str,"%s = %s <= %s \n",newvar, $<myStruct.var>1, $<myStruct.var>3); 
	$<myStruct.var>$=newvar;
	char *cd=str_append($<myStruct.code>3,$<myStruct.code>1);
	$<myStruct.code>$=str_append(cd,str);

	char *asmb=(char*)malloc(100* sizeof(char));
	sprintf(asmb,"move $t1 $a0\n");
	char* cda=str_append($<myStruct.asmbly>3,asmb);
	sprintf(asmb,"sle $a0 $a0 $t1\n");
	cda=str_append(cda,$<myStruct.asmbly>1);
	$<myStruct.asmbly>$=str_append(cda,asmb);

	free(cda);
	free(cd);
	free(str);
	free(asmb);
	//printf("relation -> sum <= sum\n");
}
| sum EqualRel sum
{

	char* str=(char*)malloc(100* sizeof(char));		
	char* newvar=t_incre(); 
	sprintf(str,"%s = (%s == %s) \n",newvar, $<myStruct.var>1, $<myStruct.var>3); 
	$<myStruct.var>$=newvar;
	char *cd=str_append($<myStruct.code>3,$<myStruct.code>1);
	$<myStruct.code>$=str_append(cd,str);

	char* asmb=(char*)malloc(100* sizeof(char));	
	sprintf(asmb,"move $t1 $a0\n");
	char* cda=str_append($<myStruct.asmbly>3,asmb);
	sprintf(asmb,"seq $a0 $a0 $t1\n");
	cda=str_append(cda,$<myStruct.asmbly>1);
	$<myStruct.asmbly>$=str_append(cda,asmb);

	//if(printDebug==1)printf("Print : %s\n",$<myStruct.code>$);
	//printf("Eq %s %s\n",$<myStruct.var>1,$<myStruct.var>3);
	free(cda);
	free(cd);
	free(str);
	free(asmb);
	//printf("relation -> sum == sum\n");
}
| sum NotEqualRel sum
{
	char* str=(char*)malloc(100* sizeof(char));		
	char* newvar=t_incre(); 
	sprintf(str,"%s = (%s != %s) \n",newvar, $<myStruct.var>1, $<myStruct.var>3); 
	$<myStruct.var>$=newvar;
	char *cd=str_append($<myStruct.code>3,$<myStruct.code>1);
	$<myStruct.code>$=str_append(cd,str);

	char *asmb=(char*)malloc(100* sizeof(char));
	sprintf(asmb,"move $t1 $a0\n");
	char* cda=str_append($<myStruct.asmbly>3,asmb);
	sprintf(asmb,"sne $a0 $a0 $t1\n");
	cda=str_append(cda,$<myStruct.asmbly>1);
	$<myStruct.asmbly>$=str_append(cda,asmb);

	free(cda);
	free(cd);
	free(str);
	free(asmb);
	//printf("relation -> sum != sum\n");
}
| sum GreaterRel sum
{
	char* str=(char*)malloc(100* sizeof(char));
	char* newvar=t_incre(); 
	sprintf(str,"%s = %s > %s \n",newvar, $<myStruct.var>1, $<myStruct.var>3); 
	$<myStruct.var>$=newvar;
	char *cd=str_append($<myStruct.code>3,$<myStruct.code>1);
	$<myStruct.code>$=str_append(cd,str);

	char *asmb=(char*)malloc(100* sizeof(char));
	sprintf(asmb,"move $t1 $a0\n");
	char* cda=str_append($<myStruct.asmbly>3,asmb);
	sprintf(asmb,"sgt $a0 $a0 $t1\n");
	cda=str_append(cda,$<myStruct.asmbly>1);
	$<myStruct.asmbly>$=str_append(cda,asmb);


	free(asmb);
	free(cda);
	free(cd);
	free(str);

	//printf("relation -> sum > sum\n");
}
| sum GreaterEqualRel sum
{

	char* str=(char*)malloc(100* sizeof(char));		
	char* newvar=t_incre(); 
	sprintf(str,"%s = %s >= %s \n", newvar, $<myStruct.var>1, $<myStruct.var>3); 
	$<myStruct.var>$=newvar;
	char *cd=str_append($<myStruct.code>3,$<myStruct.code>1);
	$<myStruct.code>$=str_append(cd,str);

	char* asmb=(char*)malloc(100* sizeof(char));
	sprintf(asmb,"move $t1 $a0\n");
	char* cda=str_append($<myStruct.asmbly>3,asmb);
	sprintf(asmb,"sge $a0 $a0 $t1\n");
	cda=str_append(cda,$<myStruct.asmbly>1);
	$<myStruct.asmbly>$=str_append(cda,asmb);

	free(asmb);
	free(cda);
	free(cd);
	free(str);

	//printf("relation -> sum >= sum\n");
};

sum: term	
	{ 
		//printf("Sum -> Term\n"); 
		$<myStruct.var>$ = $<myStruct.var>1; 
		$<myStruct.code>$= $<myStruct.code>1;
		$<myStruct.asmbly>$=$<myStruct.asmbly>1;
	}
| SUB term 
	{ 
		//printf("Sum -> - Term\n");
		char str[30]; 
		str[0] = '-'; 
		sprintf(str+1,"%s",$<myStruct.var>2); 
		$<myStruct.var>$ = strdup(str); 
		$<myStruct.code>$= $<myStruct.code>2;
		$<myStruct.asmbly>$=mips_li(str);		
	}
| sum ADD term 
	{ 
		//printf("Sum -> Sum+ Term\n");
		char* str=(char*)malloc(100* sizeof(char));	
		char* newvar=t_incre(); 
		sprintf(str,"%s = %s + %s \n",newvar, $<myStruct.var>1, $<myStruct.var>3); 
		$<myStruct.var>$=newvar;
		char *cd=str_append($<myStruct.code>3,$<myStruct.code>1);
		$<myStruct.code>$=str_append(cd,str);

			//store,  add, load, addiu (overflow not checkd, )
		char* asmb=addAssembly($<myStruct.asmbly>3,$<myStruct.asmbly>1);
		$<myStruct.asmbly>$=strdup(asmb);
		//printf("Print : %s\n",$<myStruct.code>$);
		free($<myStruct.var>1);
		free($<myStruct.var>3);
		free(cd);
		free(str);
		free(asmb);
	} 
| sum SUB term 
	{ 
		//printf("Sum -> Sum- Term\n");
		char* str=(char*)malloc(100* sizeof(char));	
		char* newvar=t_incre(); 
		sprintf(str,"%s = %s - %s \n",newvar, $<myStruct.var>1, $<myStruct.var>3); 
		$<myStruct.var>$=newvar;
		char *cd=str_append($<myStruct.code>3,$<myStruct.code>1);
		$<myStruct.code>$=str_append(cd,str);
		char* asmb=subAssembly($<myStruct.asmbly>3,$<myStruct.asmbly>1);
		$<myStruct.asmbly>$=strdup(asmb);
		//if(printDebug==1)printf("Print : %s\n",$<myStruct.code>$);
		free($<myStruct.var>1);
		free($<myStruct.var>3);
		free(cd);
		free(str);
		free(asmb);
	} 
;


term: factor 
	{ 
		//printf("Term -> Factor\n"); 
		$<myStruct.var>$ = $<myStruct.var>1; 
		$<myStruct.code>$ = $<myStruct.code>1;
		$<myStruct.asmbly>$=$<myStruct.asmbly>1;
	}
| term MUL factor 
	{ 
		//printf("Term -> Term * Factor\n"); 
		char* str=(char*)malloc(100* sizeof(char));	
		char* newvar=t_incre(); 
		
	sprintf(str,"%s = %s * %s \n",newvar, $<myStruct.var>1, $<myStruct.var>3); 
		$<myStruct.var>$=newvar;
		char *cd=str_append($<myStruct.code>3,$<myStruct.code>1);
		$<myStruct.code>$=str_append(cd,str);
		char* asmb=multAssembly($<myStruct.asmbly>3,$<myStruct.asmbly>1);
		$<myStruct.asmbly>$=strdup(asmb);
		//if(printDebug==1)printf("Print : %s\n",$<myStruct.code>$);
		free($<myStruct.var>1);
		free($<myStruct.var>3);
		free(cd);
		free(str);
		free(asmb);
	}
| term DIV factor 
	{ 
		char* str=(char*)malloc(100* sizeof(char));
		char* newvar=t_incre(); 
		sprintf(str,"%s = %s / %s \n",newvar, $<myStruct.var>1, $<myStruct.var>3); 
		$<myStruct.var>$=newvar;
		char *cd=str_append($<myStruct.code>3,$<myStruct.code>1);
		$<myStruct.code>$=str_append(cd,str);
		char* asmb=div_asm($<myStruct.asmbly>3,$<myStruct.asmbly>1);
		$<myStruct.asmbly>$=strdup(asmb);
		//if(printDebug==1)	printf("Print : %s\n",$<myStruct.code>$);
		free($<myStruct.var>1);
		free($<myStruct.var>3);
		free(asmb);
		free(cd);
		free(str);
	}
; 

factor: NUMBER 
{  	$<myStruct.var>$=$<myStruct.var>1;   //same as $$ =$1
	$<myStruct.code>$="";                   
	$<myStruct.asmbly>$=mips_li($<myStruct.var>1); // $$ = load ( $1 ) 
}
 | id { $<myStruct.var>$=$<myStruct.var>1; 
	$<myStruct.code>$="";
	 $<myStruct.asmbly>$=mips_li($<myStruct.var>1);
}
 | REAL { $<myStruct.var>$ =$<myStruct.var>1; $<myStruct.code>$=""; $<myStruct.asmbly>$=mips_li($<myStruct.var>1);}
 | True { $<myStruct.var>$ ="True"; $<myStruct.code>$=""; $<myStruct.asmbly>$=mips_li("True");}
 | False { $<myStruct.var>$ ="False"; $<myStruct.code>$="";	$<myStruct.asmbly>$=mips_li("False");}
 | OP expr CP 
	{ 
		
		$<myStruct.var>$ = $<myStruct.var>2; 
		$<myStruct.code>$= $<myStruct.code>2;
		$<myStruct.asmbly>$=$<myStruct.asmbly>2;
	} ;

%%
main()
{
  printf("> "); 
  yyin = fopen("input3.txt", "r");
  fout = fopen("output.txt", "w");
  if (fout == NULL)
  {
	    printf("Error opening file!\n");
	    exit(1);
  }
  yyparse();
}

yyerror(char *s)
{
  fprintf(stderr, "error here: %s\n", s);
}

