/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "parser.y" /* yacc.c:339  */

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


#line 359 "parser.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "parser.tab.h".  */
#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    NUM = 258,
    REAL_NUM = 259,
    ID = 260,
    TRUE = 261,
    FALSE = 262,
    ADD = 263,
    SUB = 264,
    MUL = 265,
    DIV = 266,
    COMMA = 267,
    SEMICOLON = 268,
    ASSIGN = 269,
    OPEN = 270,
    CLOSE = 271,
    RET = 272,
    OPEN2 = 273,
    CLOSE2 = 274,
    AND = 275,
    OR = 276,
    NOT = 277,
    LT = 278,
    LEQ = 279,
    EQ = 280,
    NEQ = 281,
    GEQ = 282,
    GTH = 283,
    IF = 284,
    FI = 285,
    DO = 286,
    OD = 287,
    COLON = 288,
    QUES = 289
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 294 "parser.y" /* yacc.c:355  */

    struct prop{
     char *str, *ret, *asmbly, *asmvar;
     int asmret;
  } s;

#line 441 "parser.tab.c" /* yacc.c:355  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 456 "parser.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  43
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   173

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  35
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  25
/* YYNRULES -- Number of rules.  */
#define YYNRULES  65
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  110

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   289

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   313,   313,   323,   331,   334,   340,   349,   350,   351,
     352,   353,   354,   362,   369,   376,   382,   390,   400,   409,
     416,   423,   435,   445,   452,   460,   461,   467,   483,   487,
     543,   564,   585,   596,   609,   610,   613,   614,   620,   622,
     624,   625,   630,   631,   636,   637,   640,   641,   645,   649,
     653,   657,   663,   671,   672,   679,   687,   695,   696,   708,
     723,   729,   730,   733,   736,   737
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "NUM", "REAL_NUM", "ID", "TRUE", "FALSE",
  "ADD", "SUB", "MUL", "DIV", "COMMA", "SEMICOLON", "ASSIGN", "OPEN",
  "CLOSE", "RET", "OPEN2", "CLOSE2", "AND", "OR", "NOT", "LT", "LEQ", "EQ",
  "NEQ", "GEQ", "GTH", "IF", "FI", "DO", "OD", "COLON", "QUES", "$accept",
  "program", "stmts", "stmt", "subprogramDecl", "heading", "body",
  "returnstmts", "selection", "iteration", "alts", "alt", "guard",
  "assignment", "vars", "exprs", "subprogram", "expr", "disjunction",
  "conjunction", "negation", "relation", "sum", "term", "factor", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289
};
# endif

#define YYPACT_NINF -57

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-57)))

#define YYTABLE_NINF -39

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     107,     5,    -6,    16,     8,     8,    27,    19,    28,   -57,
      26,    39,    50,    64,   104,     2,   -57,    39,    50,    64,
      61,   -57,    65,   -57,   -57,   -57,   -57,   -57,   152,     8,
      86,    43,   -57,    21,   -57,    54,    68,   -57,   -57,   105,
      88,   -57,    77,   -57,     5,   -57,   110,   -57,   -57,   -57,
     -57,    80,   139,   -57,   -57,   -57,   -57,    41,     8,    88,
     101,   -57,   -57,     8,    73,     8,     8,   152,   152,    86,
      86,    86,    86,    86,    86,   152,   152,   -57,   -57,     7,
     -57,   108,   125,   126,   -57,   -57,   125,   -57,   -57,    19,
      68,   -57,    88,    88,   117,   117,   117,   117,   117,   117,
     -57,   -57,     8,   100,     8,     8,   125,   -57,   -57,   125
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,    34,     0,     0,     0,     0,     2,     0,    11,
       0,     0,     0,     0,     0,     0,     5,     0,     0,     0,
       0,    38,     0,    60,    61,    62,    64,    65,     0,     0,
       0,     0,    25,     0,    28,    39,    40,    42,    44,    46,
      53,    57,     0,     1,     0,     6,     0,    18,    12,    14,
      16,     0,     0,    34,    13,    15,    17,     0,    33,    54,
       0,    45,    23,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    24,     4,     0,
      35,    62,    29,     0,    36,    19,    31,    63,    26,    27,
      41,    43,    55,    56,    47,    48,    49,    50,    51,    52,
      58,    59,    22,     0,     0,    32,    21,    20,    37,    30
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -57,   -57,   -38,     3,   -57,   -57,   -57,   -57,    47,    53,
     142,    87,   -57,    69,   129,   -56,   111,    -4,   -57,    95,
      85,   122,    99,   -25,    59
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     6,     7,     8,     9,    10,    47,   103,    11,    12,
      31,    32,    33,    13,    14,    82,    22,    84,    35,    36,
      37,    38,    39,    40,    41
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      34,    34,    86,    59,    16,    -7,    15,    53,    79,    20,
       2,    23,    24,    25,    26,    27,     3,    28,    -7,     3,
      44,    21,    -7,    29,   102,    60,    89,    43,    -3,    45,
      30,     4,    44,     5,     4,    -7,     5,    -7,    -7,    -8,
      48,    -3,    92,    93,    46,    -3,   106,    78,    17,   109,
      -9,    49,    -8,    51,    18,    64,    -8,    85,    -3,    34,
      -3,    -3,    54,    -9,   -10,    50,    53,    -9,    55,    -8,
      19,    -8,    -8,    62,     1,    65,    63,   -10,     2,    58,
      -9,   -10,    -9,    -9,    56,    80,    -7,     3,    66,    23,
      24,    25,    26,    27,   -10,    28,   -10,   -10,    75,    76,
     108,    29,     4,    -7,     5,    -7,    -7,    -7,     1,    77,
      63,     1,     2,    67,    68,     2,    51,    87,    52,   107,
      -7,     3,   -38,    -7,     3,    67,    68,    -7,    69,    70,
      71,    72,    73,    74,   100,   101,     4,   104,     5,     4,
     105,     5,    23,    24,    81,    26,    27,    42,    28,    57,
      88,    91,    61,     0,    29,    23,    24,    25,    26,    27,
      90,    30,     0,    83,     0,     0,     0,    29,    94,    95,
      96,    97,    98,    99
};

static const yytype_int8 yycheck[] =
{
       4,     5,    58,    28,     1,     0,     1,     5,    46,    15,
       5,     3,     4,     5,     6,     7,    14,     9,    13,    14,
      13,     5,    17,    15,    17,    29,    64,     0,     0,     1,
      22,    29,    13,    31,    29,    30,    31,    32,    33,     0,
       1,    13,    67,    68,    18,    17,   102,    44,     1,   105,
       0,     1,    13,    12,     1,    34,    17,    16,    30,    63,
      32,    33,    15,    13,     0,     1,     5,    17,    15,    30,
       1,    32,    33,    30,     1,    21,    33,    13,     5,    14,
      30,    17,    32,    33,    15,     5,    13,    14,    20,     3,
       4,     5,     6,     7,    30,     9,    32,    33,    10,    11,
     104,    15,    29,    30,    31,    32,    33,     0,     1,    32,
      33,     1,     5,     8,     9,     5,    12,    16,    14,    19,
      13,    14,    14,    13,    14,     8,     9,    17,    23,    24,
      25,    26,    27,    28,    75,    76,    29,    12,    31,    29,
      14,    31,     3,     4,     5,     6,     7,     5,     9,    20,
      63,    66,    30,    -1,    15,     3,     4,     5,     6,     7,
      65,    22,    -1,    52,    -1,    -1,    -1,    15,    69,    70,
      71,    72,    73,    74
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     5,    14,    29,    31,    36,    37,    38,    39,
      40,    43,    44,    48,    49,     1,    38,    43,    44,    48,
      15,     5,    51,     3,     4,     5,     6,     7,     9,    15,
      22,    45,    46,    47,    52,    53,    54,    55,    56,    57,
      58,    59,    45,     0,    13,     1,    18,    41,     1,     1,
       1,    12,    14,     5,    43,    44,    48,    49,    14,    58,
      52,    56,    30,    33,    34,    21,    20,     8,     9,    23,
      24,    25,    26,    27,    28,    10,    11,    32,    38,    37,
       5,     5,    50,    51,    52,    16,    50,    16,    46,    37,
      54,    55,    58,    58,    57,    57,    57,    57,    57,    57,
      59,    59,    17,    42,    12,    14,    50,    19,    52,    50
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    35,    36,    37,    37,    37,    37,    38,    38,    38,
      38,    38,    38,    38,    38,    38,    38,    38,    39,    40,
      41,    42,    42,    43,    44,    45,    45,    46,    47,    48,
      48,    48,    48,    48,    49,    49,    50,    50,    51,    52,
      53,    53,    54,    54,    55,    55,    56,    56,    56,    56,
      56,    56,    56,    57,    57,    57,    57,    58,    58,    58,
      59,    59,    59,    59,    59,    59
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     3,     2,     2,     0,     1,     1,
       1,     1,     2,     2,     2,     2,     2,     2,     2,     4,
       4,     2,     1,     3,     3,     1,     3,     3,     1,     3,
       5,     4,     4,     3,     1,     3,     1,     3,     1,     1,
       1,     3,     1,     3,     1,     2,     1,     3,     3,     3,
       3,     3,     3,     1,     2,     3,     3,     1,     3,     3,
       1,     1,     1,     3,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 313 "parser.y" /* yacc.c:1646  */
    {
	
	//all print
	outputGen((yyvsp[0].s).str);
	
}
#line 1624 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 323 "parser.y" /* yacc.c:1646  */
    {
	(yyval.s)=(yyvsp[0].s); 
	char temp[5000]={0}; 
	sprintf(temp,"%s",(yyvsp[0].s).asmbly); 
	(yyval.s).asmbly=strdup(temp); 
	sprintf(temp,"%s",(yyvsp[0].s).str); 
	(yyval.s).str=strdup(temp);
}
#line 1637 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 331 "parser.y" /* yacc.c:1646  */
    {  char temp[8000]={0};
			sprintf(temp,"%s%s",(yyvsp[-2].s).asmbly,(yyvsp[0].s).asmbly); (yyval.s).asmbly=strdup(temp);t[(yyvsp[0].s).asmret]=0; 
			sprintf(temp,"%s%s",(yyvsp[-2].s).str,(yyvsp[0].s).str); (yyval.s).str=strdup(temp); }
#line 1645 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 334 "parser.y" /* yacc.c:1646  */
    {
     (yyval.s) = (yyvsp[0].s);
     yyerrok  ;
     yyclearin;

}
#line 1656 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 340 "parser.y" /* yacc.c:1646  */
    {
     (yyval.s) = (yyvsp[-1].s);
     yyerrok  ;
     yyclearin;

}
#line 1667 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 349 "parser.y" /* yacc.c:1646  */
    { (yyval.s).str = strdup(""); (yyval.s).asmbly = strdup(""); }
#line 1673 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 350 "parser.y" /* yacc.c:1646  */
    {(yyval.s) = (yyvsp[0].s);}
#line 1679 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 351 "parser.y" /* yacc.c:1646  */
    {(yyval.s) = (yyvsp[0].s); }
#line 1685 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 352 "parser.y" /* yacc.c:1646  */
    {(yyval.s) = (yyvsp[0].s);}
#line 1691 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 353 "parser.y" /* yacc.c:1646  */
    { (yyval.s)=(yyvsp[0].s);}
#line 1697 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 355 "parser.y" /* yacc.c:1646  */
    {
    	char str[500]={0};
	strcpy(str,"error is here\n"); strcat(str,(yyvsp[-1].s).asmbly);(yyval.s).asmbly = strdup(str);
	printf("%s",(yyval.s).asmbly);
     	yyerrok  ;
     	yyclearin;
}
#line 1709 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 363 "parser.y" /* yacc.c:1646  */
    {
   	char str[500]={0};strcpy(str,"error is here\n"); strcat(str,(yyvsp[0].s).asmbly);(yyval.s).asmbly = strdup(str);
     	yyerrok  ;
     	yyclearin;
	printf("%s",(yyval.s).asmbly);
}
#line 1720 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 370 "parser.y" /* yacc.c:1646  */
    {
	char str[500]={0};strcpy(str,"error is here\n"); strcat(str,(yyvsp[-1].s).asmbly);(yyval.s).asmbly = strdup(str);
     	yyerrok  ;
     	yyclearin;
	printf("%s",(yyval.s).asmbly);
}
#line 1731 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 377 "parser.y" /* yacc.c:1646  */
    {	char str[500]={0};strcpy(str,"error is here\n"); strcat(str,(yyvsp[0].s).asmbly);(yyval.s).asmbly = strdup(str);
  	yyerrok  ;
     	yyclearin;
	printf("%s",(yyval.s).asmbly);
}
#line 1741 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 383 "parser.y" /* yacc.c:1646  */
    {
    	char str[500]={0};strcpy(str,"error is here\n"); strcat(str,(yyvsp[-1].s).asmbly);
	(yyval.s).asmbly = strdup(str);
     	yyerrok  ;
     	yyclearin;
	printf("%s",(yyval.s).asmbly);
}
#line 1753 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 391 "parser.y" /* yacc.c:1646  */
    {	char str[500]={0};strcpy(str,"error is here\n"); strcat(str,(yyvsp[0].s).asmbly);
	(yyval.s).asmbly = strdup(str);
     	yyerrok  ;
     	yyclearin;
	printf("%s",(yyval.s).asmbly);
}
#line 1764 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 401 "parser.y" /* yacc.c:1646  */
    {
	char temp[1000]={0};
	sprintf(temp,"%s%s",(yyvsp[-1].s).asmbly,(yyvsp[0].s).asmbly);	
	(yyval.s).asmbly=strdup(temp);
	strcpy(func,temp);
	(yyval.s).asmbly=strdup("");
	}
#line 1776 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 410 "parser.y" /* yacc.c:1646  */
    {
	char temp[500]={0};
	param=SubprogHead((yyvsp[-1].s).ret,temp);
	sprintf((yyval.s).asmbly,"%s:\nmove $fp, $sp\nsw $ra, 0($sp)\naddi $sp, $sp, -4\n%s",(yyvsp[-3].s).ret,temp);
}
#line 1786 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 417 "parser.y" /* yacc.c:1646  */
    {
	(yyval.s).asmbly=strdup((yyvsp[-2].s).asmbly);
	strcat((yyval.s).asmbly,(yyvsp[-1].s).asmbly);

}
#line 1796 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 423 "parser.y" /* yacc.c:1646  */
    {
	
	char temp[200];
	char temp2[600]={0};
	retTok((yyvsp[0].s).asmbly,temp2);
	(yyvsp[0].s).asmbly=strdup(temp2);

	int x=(param+2)*4;
	sprintf(temp,"%smove $a0, $t%d\nlw $ra, 4($sp)\naddi $sp, $sp, %d\nlw $fp, 0($sp)\njr $ra\n",(yyvsp[0].s).asmbly,(yyvsp[0].s).asmret,x);
	t[(yyvsp[0].s).asmret]=0;
	(yyval.s).asmbly=strdup(temp);
}
#line 1813 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 435 "parser.y" /* yacc.c:1646  */
    {
	char temp[200];
	int x=(param+2)*4;
	sprintf(temp,"lw $ra, 4($sp)\naddi $sp, $sp, %d\nlw $fp, 0($sp)\njr $ra\n",x);
	(yyval.s).asmbly=strdup(temp);
}
#line 1824 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 445 "parser.y" /* yacc.c:1646  */
    { (yyval.s)=(yyvsp[-1].s);char temp[500]={0}; putLevel((yyvsp[-1].s).str,temp); (yyval.s).str=strdup(temp); putLevel((yyvsp[-1].s).asmbly,temp);  (yyval.s).asmbly=strdup(temp);
}
#line 1831 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 452 "parser.y" /* yacc.c:1646  */
    { 
(yyval.s)=(yyvsp[-1].s); char temp[500]={0}; whileloop((yyvsp[-1].s).str,temp); (yyval.s).str=strdup(temp);
whileloop((yyvsp[-1].s).asmbly,temp); (yyval.s).asmbly=strdup(temp);
}
#line 1840 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 460 "parser.y" /* yacc.c:1646  */
    {  (yyval.s) = (yyvsp[0].s);}
#line 1846 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 461 "parser.y" /* yacc.c:1646  */
    {char temp[500]={0}; sprintf(temp,"%s%s",(yyvsp[-2].s).str,(yyvsp[0].s).str); (yyval.s).str=strdup(temp);
			sprintf((yyval.s).asmbly,"%s%s",(yyvsp[-2].s).asmbly,(yyvsp[0].s).asmbly); //printf("%s",$$.asmbly); 
}
#line 1854 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 467 "parser.y" /* yacc.c:1646  */
    {

	int label1=level++;
	int label2=level++;
	char temp[50]={0};
	sprintf(temp,"li $a0, 0\nbeq $t%d, $a0, L%d\n",(yyvsp[-2].s).asmret,label1);
	t[(yyvsp[-2].s).asmret]=0;
	sprintf((yyval.s).asmbly,"%s%s%sb L#\nL%d:\n",(yyvsp[-2].s).asmbly,temp,(yyvsp[0].s).asmbly,label1);
	(yyval.s).str=strdup("");
	char temp2[100]={0};
	sprintf(temp2,"%sif %s then goto L%d:\ngoto L%d\nL%d:\n%sgoto L#\nL%d:\n",(yyvsp[-2].s).str,(yyvsp[-2].s).ret,label1,label2,label1,(yyvsp[0].s).str,label2);
	(yyval.s).str=strdup(temp2);
}
#line 1872 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 483 "parser.y" /* yacc.c:1646  */
    {(yyval.s) = (yyvsp[0].s);
}
#line 1879 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 487 "parser.y" /* yacc.c:1646  */
    { 
	
	char var[10][50], exp[10][50], asmb[10][50],asmv[10][500]={0};
	int i=0,x,j=0,k=0;
	
	int countVarok = 0, countExprok = 0;	
	char *tok;
	sprintf((yyval.s).str, "%s%s", (yyvsp[-2].s).str,(yyvsp[0].s).str);
	tok=strtok((yyvsp[-2].s).ret,",");
	while(tok!=NULL){
		strcpy(var[countVarok++],tok);
		tok=strtok(NULL,",");
	}	
	tok=strtok((yyvsp[0].s).ret,",");
	while(tok!=NULL){
		strcpy(exp[countExprok++],tok);
		tok=strtok(NULL,",");
	}
	tok=strtok((yyvsp[0].s).asmvar,",");
	while(tok!=NULL){
		strcpy(asmb[k++],tok);
		tok=strtok(NULL,",");
	}
	k=0;
	//printf("%s",$3.asmbly);
	tok=strtok((yyvsp[0].s).asmbly,"#");
	while(tok!=NULL){
		strcpy(asmv[k++],tok);
		tok=strtok(NULL,"#");
	}
	
	if(countVarok != countExprok)
		strcat((yyval.s).str,"Invalid Assignment!!\n");
	else if(countVarok==1){
		char temp[50];
		sprintf(temp,"%s=%s\n",var[0],(yyvsp[0].s).ret);
		strcat((yyval.s).str,temp);
		sprintf((yyval.s).asmbly, "%s%s", (yyvsp[-2].s).asmbly,(yyvsp[0].s).asmbly);
		sprintf(temp,"sw $t%d, %s\n",(yyvsp[0].s).asmret,(yyvsp[-2].s).ret);
		strcat((yyval.s).asmbly,temp);
		t[(yyvsp[0].s).asmret]=0;
	}
	else{
		sprintf((yyval.s).asmbly, "%s", (yyvsp[-2].s).asmbly);
		//printf("%s",$1.asmbly);
		for(x=0;x<i;x++){
			char temp[50];
			sprintf(temp,"%s=%s\n",var[x],exp[x]);
			strcat((yyval.s).str,temp);
			sprintf(temp,"%ssw $t%s, %s\n",asmv[x],asmb[x],var[x]);
			strcat((yyval.s).asmbly,temp);
			t[asmb[x][0]-'0']=0;
		}
	}

}
#line 1940 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 544 "parser.y" /* yacc.c:1646  */
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
	retTok((yyvsp[0].s).asmbly,temp2);
	(yyvsp[0].s).asmbly=strdup(temp2);
    	char temp[500]={0};
	AssignSubprog((yyvsp[0].s).asmvar,temp);
	(yyval.s).asmbly=strdup("");
	sprintf((yyval.s).asmbly,"%ssw $fp, 0($sp)\naddi $sp, $sp, -4\n%sb %s\nsw $a0, %s\n",(yyvsp[0].s).asmbly,temp,(yyvsp[-2].s).ret,(yyvsp[-4].s).ret);
	//printf("%s",$$.asmbly);
	
}
#line 1965 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 565 "parser.y" /* yacc.c:1646  */
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
	retTok((yyvsp[0].s).asmbly,temp2);
	(yyvsp[0].s).asmbly=strdup(temp2);

	char temp[500]={0};
	AssignSubprog((yyvsp[0].s).asmvar,temp);
	(yyval.s).asmbly=strdup("");
	sprintf((yyval.s).asmbly,"%ssw $fp, 0($sp)\naddi $sp, $sp, -4\n%sb %s\n",(yyvsp[0].s).asmbly,temp,(yyvsp[-2].s).ret);
	//printf("%s",$$.asmbly);
	
}
#line 1990 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 586 "parser.y" /* yacc.c:1646  */
    {
    	int count1=0,count2=0;
	char *v=countarg2((yyvsp[-3].s).ret,&count1);
	char temp[200];
	sprintf(temp,"sw $fp, 0($sp)\naddi $sp, $sp, -4\nb %s\nsw $a0, %s\n",(yyvsp[-1].s).ret,(yyvsp[-3].s).ret);
	(yyval.s).asmbly=strdup(temp);
	sprintf(temp,"call %s, %d, %d\n", (yyvsp[-1].s).ret,count2,count1);
	strcat((yyval.s).str,temp);
	strcat((yyval.s).str,v);
}
#line 2005 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 597 "parser.y" /* yacc.c:1646  */
    {
	(yyval.s)=(yyvsp[-1].s);   	
	int count1=0,count2=0;
	char temp[50];
	sprintf(temp,"sw $fp, 0($sp)\naddi $sp, $sp, -4\nb %s\n",(yyvsp[-1].s).ret);
	(yyval.s).asmbly=strdup(temp);
	sprintf(temp,"call %s, %d, %d\n", (yyvsp[-1].s).ret,count2,count1);
	strcpy((yyval.s).str,"");
	strcat((yyval.s).str,temp);
}
#line 2020 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 609 "parser.y" /* yacc.c:1646  */
    { (yyval.s) = (yyvsp[0].s);}
#line 2026 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 610 "parser.y" /* yacc.c:1646  */
    { strcpy((yyval.s).ret,(yyvsp[-2].s).ret); strcat((yyval.s).ret,","); strcat((yyval.s).ret, (yyvsp[0].s).ret); sprintf((yyval.s).str,"%s%s",(yyvsp[-2].s).str, (yyvsp[0].s).str);
			sprintf((yyval.s).asmbly,"%s%s",(yyvsp[-2].s).asmbly,(yyvsp[0].s).asmbly); }
#line 2033 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 613 "parser.y" /* yacc.c:1646  */
    { (yyval.s) = (yyvsp[0].s) ; }
#line 2039 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 614 "parser.y" /* yacc.c:1646  */
    { strcpy((yyval.s).ret,(yyvsp[-2].s).ret); strcat((yyval.s).ret,","); strcat((yyval.s).ret, (yyvsp[0].s).ret); sprintf((yyval.s).str,"%s%s",(yyvsp[-2].s).str, (yyvsp[0].s).str);
			sprintf((yyval.s).asmbly,"%s#%s",(yyvsp[-2].s).asmbly,(yyvsp[0].s).asmbly);(yyval.s).asmvar = strdup(""); sprintf((yyval.s).asmvar,"%s,%s",(yyvsp[-2].s).asmvar,(yyvsp[0].s).asmvar);
			}
#line 2047 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 620 "parser.y" /* yacc.c:1646  */
    {(yyval.s) = (yyvsp[0].s);}
#line 2053 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 622 "parser.y" /* yacc.c:1646  */
    { (yyval.s)= (yyvsp[0].s); }
#line 2059 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 624 "parser.y" /* yacc.c:1646  */
    { (yyval.s) = (yyvsp[0].s);}
#line 2065 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 625 "parser.y" /* yacc.c:1646  */
    {char st[50];sprintf(st,"t%d=%s | %s\n",indx,(yyvsp[-2].s).ret,(yyvsp[0].s).ret); 
					sprintf((yyval.s).str,"%s%s%s",(yyvsp[-2].s).str,(yyvsp[0].s).str,st);sprintf((yyval.s).ret,"t%d",indx++); char temp[200]={0}; 
					RelationSum((yyvsp[-2].s).asmret,(yyvsp[0].s).asmret,"or",temp); sprintf((yyval.s).asmbly,"%s%s%s",(yyvsp[-2].s).asmbly,(yyvsp[0].s).asmbly,temp);
					(yyval.s).asmret=(yyvsp[-2].s).asmret;sprintf((yyval.s).asmvar,"%d",(yyvsp[-2].s).asmret); t[(yyvsp[0].s).asmret]=0;}
#line 2074 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 630 "parser.y" /* yacc.c:1646  */
    {(yyval.s) = (yyvsp[0].s); }
#line 2080 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 631 "parser.y" /* yacc.c:1646  */
    { char st[50]; sprintf(st,"t%d=%s & %s\n",indx,(yyvsp[-2].s).ret,(yyvsp[0].s).ret); 
				     sprintf((yyval.s).str,"%s%s%s",(yyvsp[-2].s).str,(yyvsp[0].s).str,st); sprintf((yyval.s).ret,"t%d",indx++); char temp[200]={0}; 
				     RelationSum((yyvsp[-2].s).asmret,(yyvsp[0].s).asmret,"and",temp); sprintf((yyval.s).asmbly,"%s%s%s",(yyvsp[-2].s).asmbly,(yyvsp[0].s).asmbly,temp);
				     (yyval.s).asmret=(yyvsp[-2].s).asmret;sprintf((yyval.s).asmvar,"%d",(yyvsp[-2].s).asmret); t[(yyvsp[0].s).asmret]=0; }
#line 2089 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 636 "parser.y" /* yacc.c:1646  */
    {(yyval.s) = (yyvsp[0].s); }
#line 2095 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 637 "parser.y" /* yacc.c:1646  */
    { char st[50]; sprintf(st,"~%s",(yyvsp[0].s).ret); (yyval.s).str=(yyvsp[0].s).str;(yyval.s).ret=st;	
	 		 sprintf((yyval.s).asmbly,"%snot t%d t%d\n",(yyvsp[0].s).asmbly,(yyvsp[0].s).asmret,(yyvsp[0].s).asmret);sprintf((yyval.s).asmvar,"%d",(yyvsp[0].s).asmret); 					(yyval.s).asmret=(yyvsp[0].s).asmret;}
#line 2102 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 640 "parser.y" /* yacc.c:1646  */
    {(yyval.s) = (yyvsp[0].s); }
#line 2108 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 641 "parser.y" /* yacc.c:1646  */
    {char st[50];sprintf(st,"t%d=%s < %s\n",indx,(yyvsp[-2].s).ret,(yyvsp[0].s).ret); sprintf((yyval.s).str,"%s%s%s",(yyvsp[-2].s).str,(yyvsp[0].s).str,st);
			sprintf((yyval.s).ret,"t%d",indx++); char temp[200]={0}; 
			RelationSum((yyvsp[-2].s).asmret,(yyvsp[0].s).asmret,"slt",temp); sprintf((yyval.s).asmbly,"%s%s%s",(yyvsp[-2].s).asmbly,(yyvsp[0].s).asmbly,temp);
			(yyval.s).asmret=(yyvsp[-2].s).asmret;sprintf((yyval.s).asmvar,"%d",(yyvsp[-2].s).asmret); t[(yyvsp[0].s).asmret]=0; }
#line 2117 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 645 "parser.y" /* yacc.c:1646  */
    {char st[50];sprintf(st,"t%d=%s <= %s\n",indx,(yyvsp[-2].s).ret,(yyvsp[0].s).ret); sprintf((yyval.s).str,"%s%s%s",(yyvsp[-2].s).str,(yyvsp[0].s).str,st);
			sprintf((yyval.s).ret,"t%d",indx++);char temp[200]={0}; 
			RelationSum((yyvsp[-2].s).asmret,(yyvsp[0].s).asmret,"sle",temp); sprintf((yyval.s).asmbly,"%s%s%s",(yyvsp[-2].s).asmbly,(yyvsp[0].s).asmbly,temp);
			(yyval.s).asmret=(yyvsp[-2].s).asmret;sprintf((yyval.s).asmvar,"%d",(yyvsp[-2].s).asmret); t[(yyvsp[0].s).asmret]=0; }
#line 2126 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 649 "parser.y" /* yacc.c:1646  */
    {char st[50];sprintf(st,"t%d=%s = %s\n",indx,(yyvsp[-2].s).ret,(yyvsp[0].s).ret); sprintf((yyval.s).str,"%s%s%s",(yyvsp[-2].s).str,(yyvsp[0].s).str,st);
			sprintf((yyval.s).ret,"t%d",indx++); char temp[200]={0}; 
			RelationSum((yyvsp[-2].s).asmret,(yyvsp[0].s).asmret,"seq",temp); sprintf((yyval.s).asmbly,"%s%s%s",(yyvsp[-2].s).asmbly,(yyvsp[0].s).asmbly,temp);
			(yyval.s).asmret=(yyvsp[-2].s).asmret;sprintf((yyval.s).asmvar,"%d",(yyvsp[-2].s).asmret); t[(yyvsp[0].s).asmret]=0; }
#line 2135 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 653 "parser.y" /* yacc.c:1646  */
    {char st[50];sprintf(st,"t%d=%s ~= %s\n",indx,(yyvsp[-2].s).ret,(yyvsp[0].s).ret); sprintf((yyval.s).str,"%s%s%s",(yyvsp[-2].s).str,(yyvsp[0].s).str,st);
			sprintf((yyval.s).ret,"t%d",indx++); char temp[200]={0}; 
			RelationSum((yyvsp[-2].s).asmret,(yyvsp[0].s).asmret,"sne",temp); sprintf((yyval.s).asmbly,"%s%s%s",(yyvsp[-2].s).asmbly,(yyvsp[0].s).asmbly,temp);
			(yyval.s).asmret=(yyvsp[-2].s).asmret;sprintf((yyval.s).asmvar,"%d",(yyvsp[-2].s).asmret); t[(yyvsp[0].s).asmret]=0; }
#line 2144 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 657 "parser.y" /* yacc.c:1646  */
    {char st[50];sprintf(st,"t%d=%s >= %s\n",indx,(yyvsp[-2].s).ret,(yyvsp[0].s).ret); sprintf((yyval.s).str,"%s%s%s",(yyvsp[-2].s).str,(yyvsp[0].s).str,st);
			sprintf((yyval.s).ret,"t%d",indx++); char temp[200]={0}; 
			
				RelationSum((yyvsp[-2].s).asmret,(yyvsp[0].s).asmret,"sge",temp); 
			sprintf((yyval.s).asmbly,"%s%s%s",(yyvsp[-2].s).asmbly,(yyvsp[0].s).asmbly,temp);
			(yyval.s).asmret=(yyvsp[-2].s).asmret;sprintf((yyval.s).asmvar,"%d",(yyvsp[-2].s).asmret); t[(yyvsp[0].s).asmret]=0; }
#line 2155 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 663 "parser.y" /* yacc.c:1646  */
    {char st[50];sprintf(st,"t%d=%s > %s\n",indx,(yyvsp[-2].s).ret,(yyvsp[0].s).ret); sprintf((yyval.s).str,"%s%s%s",(yyvsp[-2].s).str,(yyvsp[0].s).str,st);
			sprintf((yyval.s).ret,"t%d",indx++); char temp[200]={0};t[(yyvsp[0].s).asmret]=0; 
				RelationSum((yyvsp[-2].s).asmret,(yyvsp[0].s).asmret,"slt",temp); 
			
			sprintf((yyval.s).asmbly,"%s%s%s",(yyvsp[-2].s).asmbly,(yyvsp[0].s).asmbly,temp);

			(yyval.s).asmret=(yyvsp[-2].s).asmret; sprintf((yyval.s).asmvar,"%d",(yyvsp[-2].s).asmret); }
#line 2167 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 671 "parser.y" /* yacc.c:1646  */
    { (yyval.s) = (yyvsp[0].s);}
#line 2173 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 672 "parser.y" /* yacc.c:1646  */
    { 
			char st[50];sprintf(st,"-%s\n",(yyvsp[0].s).ret); (yyval.s).ret=st; sprintf((yyval.s).asmbly,"%snegu t%d t%d\n",(yyvsp[0].s).asmbly,(yyvsp[0].s).asmret,(yyvsp[0].s).asmret);
			(yyval.s).asmret=(yyvsp[0].s).asmret; 

			sprintf((yyval.s).asmvar,"%d",(yyvsp[0].s).asmret);//$$.asmbly=Load(st,$$.asmbly);

		}
#line 2185 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 679 "parser.y" /* yacc.c:1646  */
    {
				char st[50]; sprintf(st,"t%d=%s + %s\n",indx,(yyvsp[-2].s).ret,(yyvsp[0].s).ret);sprintf((yyval.s).str,"%s%s%s",(yyvsp[-2].s).str,(yyvsp[0].s).str,st);
			 sprintf((yyval.s).ret,"t%d",indx++); char temp[200]={0}; 

			 AddSub((yyvsp[-2].s).asmret,(yyvsp[0].s).asmret,"add",temp); sprintf((yyval.s).asmbly,"%s%s%s",(yyvsp[-2].s).asmbly,(yyvsp[0].s).asmbly,temp);

			 (yyval.s).asmret=(yyvsp[-2].s).asmret; sprintf((yyval.s).asmvar,"%d",(yyvsp[-2].s).asmret);t[(yyvsp[0].s).asmret]=0;
		}
#line 2198 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 687 "parser.y" /* yacc.c:1646  */
    {char st[50]; sprintf(st,"t%d=%s - %s\n",indx,(yyvsp[-2].s).ret,(yyvsp[0].s).ret);sprintf((yyval.s).str,"%s%s%s",(yyvsp[-2].s).str,(yyvsp[0].s).str,st);
			 sprintf((yyval.s).ret,"t%d",indx++); char temp[200]={0}; 

			 AddSub((yyvsp[-2].s).asmret,(yyvsp[0].s).asmret,"sub",temp); sprintf((yyval.s).asmbly,"%s%s%s",(yyvsp[-2].s).asmbly,(yyvsp[0].s).asmbly,temp);

			 (yyval.s).asmret=(yyvsp[-2].s).asmret;sprintf((yyval.s).asmvar,"%d",(yyvsp[-2].s).asmret); t[(yyvsp[0].s).asmret]=0;
		}
#line 2210 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 695 "parser.y" /* yacc.c:1646  */
    { (yyval.s) = (yyvsp[0].s) ;}
#line 2216 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 696 "parser.y" /* yacc.c:1646  */
    { 
		    sprintf((yyval.s).str,"t%d=%s * %s\n",indx,(yyvsp[-2].s).ret,(yyvsp[0].s).ret); 
		    sprintf((yyval.s).ret,"t%d",indx++); 
			char temp[200]={0}; 

			MulDiv((yyvsp[-2].s).asmret,(yyvsp[0].s).asmret,"multu",temp); 

			sprintf((yyval.s).asmbly,"%s%s%s",(yyvsp[-2].s).asmbly,(yyvsp[0].s).asmbly,temp);
			(yyval.s).asmret=(yyvsp[-2].s).asmret;

			sprintf((yyval.s).asmvar,"%d",(yyvsp[-2].s).asmret); t[(yyvsp[0].s).asmret]=0; }
#line 2232 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 708 "parser.y" /* yacc.c:1646  */
    {
			sprintf((yyval.s).str,"t%d=%s / %s\n",indx,(yyvsp[-2].s).ret,(yyvsp[0].s).ret); 
			sprintf((yyval.s).ret,"t%d",indx++);
			char temp[200]={0}; 
			
			MulDiv((yyvsp[-2].s).asmret,(yyvsp[0].s).asmret,"div",temp); 

			sprintf((yyval.s).asmbly,"%s%s%s",(yyvsp[-2].s).asmbly,(yyvsp[0].s).asmbly,temp);
			(yyval.s).asmret=(yyvsp[-2].s).asmret;

			sprintf((yyval.s).asmvar,"%d",(yyvsp[-2].s).asmret); 
			t[(yyvsp[0].s).asmret]=0;

			}
#line 2251 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 723 "parser.y" /* yacc.c:1646  */
    { 
		(yyvsp[0].s).asmret=retFreeReg(); 
		LoadI((yyvsp[0].s).ret,(yyvsp[0].s).asmret,(yyvsp[0].s).asmbly);
		sprintf((yyvsp[0].s).asmvar,"%d",(yyvsp[0].s).asmret);
		t[(yyvsp[0].s).asmret]=1; (yyval.s) = (yyvsp[0].s); }
#line 2261 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 729 "parser.y" /* yacc.c:1646  */
    { (yyvsp[0].s).asmret=retFreeReg(); LoadI((yyvsp[0].s).ret,(yyvsp[0].s).asmret,(yyvsp[0].s).asmbly);sprintf((yyvsp[0].s).asmvar,"%d",(yyvsp[0].s).asmret);t[(yyvsp[0].s).asmret]=1;(yyval.s)=(yyvsp[0].s);  }
#line 2267 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 730 "parser.y" /* yacc.c:1646  */
    { (yyvsp[0].s).asmret=retFreeReg(); Load((yyvsp[0].s).ret,(yyvsp[0].s).asmret,(yyvsp[0].s).asmbly);t[(yyvsp[0].s).asmret]=1;sprintf((yyvsp[0].s).asmvar,"%d",(yyvsp[0].s).asmret);(yyval.s)=(yyvsp[0].s);
	 }
#line 2274 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 733 "parser.y" /* yacc.c:1646  */
    { sprintf((yyvsp[-1].s).asmvar,"%d",(yyvsp[-1].s).asmret);(yyval.s) = (yyvsp[-1].s); 
			}
#line 2281 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 736 "parser.y" /* yacc.c:1646  */
    { (yyvsp[0].s).asmret=retFreeReg(); LoadB((yyvsp[0].s).ret,(yyvsp[0].s).asmret,(yyvsp[0].s).asmbly);t[(yyvsp[0].s).asmret]=1;sprintf((yyvsp[0].s).asmvar,"%d",(yyvsp[0].s).asmret);(yyval.s)=(yyvsp[0].s); }
#line 2287 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 737 "parser.y" /* yacc.c:1646  */
    { (yyvsp[0].s).asmret=retFreeReg(); LoadB((yyvsp[0].s).ret,(yyvsp[0].s).asmret,(yyvsp[0].s).asmbly);sprintf((yyvsp[0].s).asmvar,"%d",(yyvsp[0].s).asmret);t[(yyvsp[0].s).asmret]=1;(yyval.s)=(yyvsp[0].s) ;}
#line 2293 "parser.tab.c" /* yacc.c:1646  */
    break;


#line 2297 "parser.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 740 "parser.y" /* yacc.c:1906  */



yyerror(char *s)
{
	//fprintf(stderr, "error: %s\n", s);
}
