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



#line 402 "parser.tab.c" /* yacc.c:339  */

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
    NUMBER = 258,
    ADD = 259,
    SUB = 260,
    MUL = 261,
    DIV = 262,
    OP = 263,
    CP = 264,
    OB = 265,
    CB = 266,
    ret = 267,
    AssignOp = 268,
    id = 269,
    Semicolon = 270,
    List = 271,
    REAL = 272,
    True = 273,
    False = 274,
    GreaterRel = 275,
    GreaterEqualRel = 276,
    LessRel = 277,
    LessEqualRel = 278,
    NotEqualRel = 279,
    EqualRel = 280,
    Negate = 281,
    Or = 282,
    And = 283,
    ELSEE = 284,
    QMark = 285,
    ifStart = 286,
    ifEnd = 287,
    loopStart = 288,
    loopEnd = 289
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 338 "parser.y" /* yacc.c:355  */

  struct {

	char* var;
	char* asmbly;	

	char* next;
	char* code;
	
	char* trueLabel;
	char* falseLabel;
	
  } myStruct;

#line 492 "parser.tab.c" /* yacc.c:355  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 507 "parser.tab.c" /* yacc.c:358  */

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
#define YYFINAL  39
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   136

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  35
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  26
/* YYNRULES -- Number of rules.  */
#define YYNRULES  60
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  103

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
       0,   407,   407,   415,   421,   431,   435,   445,   457,   464,
     470,   479,   491,   500,   521,   528,   532,   537,   543,   549,
     559,   568,   576,   601,   608,   634,   663,   687,   706,   715,
     722,   727,   733,   743,   754,   762,   768,   792,   798,   822,
     828,   856,   862,   883,   905,   930,   952,   976,  1001,  1008,
    1018,  1038,  1059,  1066,  1085,  1104,  1109,  1113,  1114,  1115,
    1116
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "NUMBER", "ADD", "SUB", "MUL", "DIV",
  "OP", "CP", "OB", "CB", "ret", "AssignOp", "id", "Semicolon", "List",
  "REAL", "True", "False", "GreaterRel", "GreaterEqualRel", "LessRel",
  "LessEqualRel", "NotEqualRel", "EqualRel", "Negate", "Or", "And",
  "ELSEE", "QMark", "ifStart", "ifEnd", "loopStart", "loopEnd", "$accept",
  "program", "stmts", "stmt", "selection", "iteration", "subprogramDecl",
  "args", "heading", "body", "returnStmt", "alts", "alt", "guard",
  "assignment", "subprogram", "vars", "exprs", "expr", "disjunction",
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

#define YYPACT_NINF -41

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-41)))

#define YYTABLE_NINF -30

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      37,     4,   -10,    11,     4,     4,    44,    31,   -41,   -41,
     -41,   -41,    39,   -41,    12,   -41,   107,     4,   -41,   -41,
     -41,   -41,   100,   -21,   -41,    33,   -41,    42,    46,   -41,
     -41,    77,    -1,   -41,   -41,    63,    72,    16,    -2,   -41,
       2,    52,   -41,    70,    90,    -1,   104,   -41,     4,   -41,
     -41,    28,     4,     4,   107,   107,   100,   100,   100,   100,
     100,   100,   107,   107,     4,    93,   111,   -41,   -41,   -41,
      43,   103,   109,   112,   -41,   -41,   -41,   -41,    31,    46,
     -41,    -1,    -1,    67,    67,    67,    67,    67,    67,   -41,
     -41,   112,    72,   -41,     4,   116,     4,     4,   -41,   112,
     -41,   112,   -41
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,    30,     0,     0,     0,     2,     3,     6,
       7,     9,     0,     8,     0,    55,     0,     0,    56,    57,
      58,    59,     0,     0,    20,     0,    23,    34,    35,    37,
      39,    41,    48,    52,    29,     0,     0,     0,     0,     1,
       0,     0,    14,     0,     0,    49,     0,    40,     0,    11,
      13,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    28,    16,     0,    10,    12,     4,
       0,    56,     0,    24,    32,    31,    60,    21,    22,    36,
      38,    50,    51,    46,    47,    42,    43,    45,    44,    53,
      54,    26,     0,    17,     0,     0,    27,     0,    15,    19,
      18,    25,    33
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -41,   -41,   -31,    83,   -41,   -41,   -41,    38,   -41,   -41,
     -41,   102,    81,   -41,   -41,    88,   -41,   -40,   -17,   -41,
      80,    82,   114,    34,   -15,    49
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     6,     7,     8,     9,    10,    11,    66,    12,    42,
      95,    23,    24,    25,    13,    35,    14,    73,    26,    27,
      28,    29,    30,    31,    32,    33
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      46,    45,    -5,     1,    34,    62,    63,    15,    48,    16,
      70,    49,    17,    50,    -5,     2,     3,    -5,    18,    36,
      78,    19,    20,    21,    91,    43,    74,    48,    44,     1,
      22,    -5,    68,     4,    -5,     5,    -5,    -5,     1,    81,
      82,     2,     3,    -5,    39,    48,    40,    74,    67,    41,
       2,     3,    -5,     1,    99,    94,   101,    -5,    40,     4,
      -5,     5,    -5,    51,    -5,     2,     3,    -5,     4,    52,
       5,    54,    55,    15,    53,    16,    64,    74,    17,    74,
     102,    54,    55,     4,    71,     5,    65,    19,    20,    21,
      83,    84,    85,    86,    87,    88,    22,    56,    57,    58,
      59,    60,    61,    15,    75,    16,    37,    38,    17,    92,
      15,    89,    90,    76,    18,    17,   -29,    19,    20,    21,
      93,    18,    96,    69,    19,    20,    21,   100,    97,    77,
      98,    72,    79,     0,     0,    80,    47
};

static const yytype_int8 yycheck[] =
{
      17,    16,     0,     1,    14,     6,     7,     3,    29,     5,
      41,    32,     8,    34,    12,    13,    14,    15,    14,     8,
      51,    17,    18,    19,    64,    13,    43,    29,    16,     1,
      26,    29,    34,    31,    32,    33,    34,     0,     1,    54,
      55,    13,    14,    15,     0,    29,    15,    64,    32,    10,
      13,    14,    15,     1,    94,    12,    96,    29,    15,    31,
      32,    33,    34,    30,    12,    13,    14,    15,    31,    27,
      33,     4,     5,     3,    28,     5,    13,    94,     8,    96,
      97,     4,     5,    31,    14,    33,    14,    17,    18,    19,
      56,    57,    58,    59,    60,    61,    26,    20,    21,    22,
      23,    24,    25,     3,    14,     5,     4,     5,     8,    16,
       3,    62,    63,     9,    14,     8,    13,    17,    18,    19,
       9,    14,    13,    40,    17,    18,    19,    11,    16,    48,
      92,    43,    52,    -1,    -1,    53,    22
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,    13,    14,    31,    33,    36,    37,    38,    39,
      40,    41,    43,    49,    51,     3,     5,     8,    14,    17,
      18,    19,    26,    46,    47,    48,    53,    54,    55,    56,
      57,    58,    59,    60,    14,    50,     8,    46,    46,     0,
      15,    10,    44,    13,    16,    59,    53,    57,    29,    32,
      34,    30,    27,    28,     4,     5,    20,    21,    22,    23,
      24,    25,     6,     7,    13,    14,    42,    32,    34,    38,
      37,    14,    50,    52,    53,    14,     9,    47,    37,    55,
      56,    59,    59,    58,    58,    58,    58,    58,    58,    60,
      60,    52,    16,     9,    12,    45,    13,    16,    42,    52,
      11,    52,    53
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    35,    36,    37,    37,    38,    38,    38,    38,    38,
      39,    39,    40,    40,    41,    42,    42,    43,    44,    45,
      46,    46,    47,    48,    49,    49,    49,    49,    49,    50,
      51,    51,    52,    52,    53,    54,    54,    55,    55,    56,
      56,    57,    57,    57,    57,    57,    57,    57,    58,    58,
      58,    58,    59,    59,    59,    60,    60,    60,    60,    60,
      60
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     3,     0,     1,     1,     1,     1,
       3,     3,     3,     3,     2,     3,     1,     4,     4,     2,
       1,     3,     3,     1,     3,     5,     4,     4,     3,     1,
       1,     3,     1,     3,     1,     1,     3,     1,     3,     1,
       2,     1,     3,     3,     3,     3,     3,     3,     1,     2,
       3,     3,     1,     3,     3,     1,     1,     1,     1,     1,
       3
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
#line 408 "parser.y" /* yacc.c:1646  */
    { 	
	printf("%s\n",(yyval.myStruct.code)); 
	printf("Assembly : \n%s\n",(yyvsp[0].myStruct.asmbly));
	fprintf(fout, "%s\n", (yyvsp[0].myStruct.asmbly));
	fclose(fout);
}
#line 1668 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 416 "parser.y" /* yacc.c:1646  */
    { 	
	(yyval.myStruct.code)=(yyvsp[0].myStruct.code);	
	(yyval.myStruct.asmbly)=(yyvsp[0].myStruct.asmbly);
}
#line 1677 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 422 "parser.y" /* yacc.c:1646  */
    { 
	char* cd=str_append((yyvsp[-2].myStruct.code),"\n");
	(yyval.myStruct.code)=str_append(cd,(yyvsp[0].myStruct.code));
	char* asmb=str_append((yyvsp[-2].myStruct.asmbly),"\n");
	(yyval.myStruct.asmbly)=str_append(asmb,(yyvsp[0].myStruct.asmbly));
}
#line 1688 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 431 "parser.y" /* yacc.c:1646  */
    {
	(yyval.myStruct.code)="";
	(yyval.myStruct.asmbly)="";
}
#line 1697 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 436 "parser.y" /* yacc.c:1646  */
    {	
	char* label=newlabel();
	char* result=replace_str((yyvsp[0].myStruct.code),"--SuperLabel--",label);
	char* asmResult=replace_str((yyvsp[0].myStruct.asmbly),"--SuperLabel--",label);
	(yyval.myStruct.next)=label;
	(yyval.myStruct.code)=str_append(result,setLabel((yyval.myStruct.next)));
	asmResult=str_append(asmResult,setLabel((yyval.myStruct.next)));
	(yyval.myStruct.asmbly)=str_append(asmResult,"\n");
}
#line 1711 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 446 "parser.y" /* yacc.c:1646  */
    {
	char* begin=newlabel();	//Label at Start of Loop 
	char* result=replace_str((yyvsp[0].myStruct.code),"--SuperLabel--",begin);
	char* asmResult=replace_str((yyvsp[0].myStruct.asmbly),"--SuperLabel--",begin);
	(yyval.myStruct.next)=begin;	
	char* temp=fit(str_append(setLabel(begin),result));  
	(yyval.myStruct.code)=temp;
	char* tempAsm= fit(str_append(setLabel(begin),asmResult));
	tempAsm=str_append(tempAsm,"\n");
	(yyval.myStruct.asmbly)=tempAsm;
}
#line 1727 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 458 "parser.y" /* yacc.c:1646  */
    {
	(yyval.myStruct.trueLabel)="";
	(yyval.myStruct.falseLabel)="";
	(yyval.myStruct.code)=(yyvsp[0].myStruct.code);
	(yyval.myStruct.asmbly)=(yyvsp[0].myStruct.asmbly);
}
#line 1738 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 465 "parser.y" /* yacc.c:1646  */
    {
	(yyval.myStruct.code)=(yyvsp[0].myStruct.code);
	(yyval.myStruct.asmbly)=(yyvsp[0].myStruct.asmbly);
}
#line 1747 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 471 "parser.y" /* yacc.c:1646  */
    { 
	(yyval.myStruct.trueLabel)=(yyvsp[-1].myStruct.trueLabel);
	(yyval.myStruct.falseLabel)=(yyvsp[-1].myStruct.falseLabel);
	(yyval.myStruct.var)=(yyvsp[-1].myStruct.var);
	(yyval.myStruct.code)=(yyvsp[-1].myStruct.code);
	(yyval.myStruct.next)=(yyvsp[-1].myStruct.next);
	(yyval.myStruct.asmbly)=(yyvsp[-1].myStruct.asmbly);
}
#line 1760 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 480 "parser.y" /* yacc.c:1646  */
    {
	//printf("error in if\n");
	printf("%s\n",(yyvsp[-1].myStruct.asmbly));
	(yyval.myStruct.trueLabel)=(yyvsp[-1].myStruct.trueLabel);
	(yyval.myStruct.falseLabel)=(yyvsp[-1].myStruct.falseLabel);
	(yyval.myStruct.var)=(yyvsp[-1].myStruct.var);
	(yyval.myStruct.code)=(yyvsp[-1].myStruct.code);
	(yyval.myStruct.next)=(yyvsp[-1].myStruct.next);
	(yyval.myStruct.asmbly)=(yyvsp[-1].myStruct.asmbly);
}
#line 1775 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 492 "parser.y" /* yacc.c:1646  */
    { 
	(yyval.myStruct.trueLabel)=(yyvsp[-1].myStruct.trueLabel);
	(yyval.myStruct.falseLabel)=(yyvsp[-1].myStruct.falseLabel);
	(yyval.myStruct.var)=(yyvsp[-1].myStruct.var);
	(yyval.myStruct.code)=(yyvsp[-1].myStruct.code);
	(yyval.myStruct.next)=(yyvsp[-1].myStruct.next);
	(yyval.myStruct.asmbly)=(yyvsp[-1].myStruct.asmbly);
}
#line 1788 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 501 "parser.y" /* yacc.c:1646  */
    {
	//printf("error in loop\n");
	printf("%s\n",(yyvsp[-1].myStruct.asmbly));
	(yyval.myStruct.trueLabel)=(yyvsp[-1].myStruct.trueLabel);
	(yyval.myStruct.falseLabel)=(yyvsp[-1].myStruct.falseLabel);
	(yyval.myStruct.var)=(yyvsp[-1].myStruct.var);
	(yyval.myStruct.code)=(yyvsp[-1].myStruct.code);
	(yyval.myStruct.next)=(yyvsp[-1].myStruct.next);
	(yyval.myStruct.asmbly)=(yyvsp[-1].myStruct.asmbly);

}
#line 1804 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 522 "parser.y" /* yacc.c:1646  */
    {		
	(yyval.myStruct.var)=(yyvsp[-1].myStruct.var);
	(yyval.myStruct.code)=(yyvsp[0].myStruct.code);
	(yyval.myStruct.asmbly)=funcDefn((yyvsp[-1].myStruct.var),(yyvsp[0].myStruct.asmbly));	
}
#line 1814 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 529 "parser.y" /* yacc.c:1646  */
    {		
	strcpy(argList[argCount++],(yyvsp[-2].myStruct.var));			
}
#line 1822 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 533 "parser.y" /* yacc.c:1646  */
    {		
	strcpy(argList[argCount++],(yyvsp[0].myStruct.var));			
}
#line 1830 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 538 "parser.y" /* yacc.c:1646  */
    {	

	(yyval.myStruct.var)=(yyvsp[-3].myStruct.var);		
}
#line 1839 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 544 "parser.y" /* yacc.c:1646  */
    {		
	(yyval.myStruct.code)=(yyvsp[-2].myStruct.code);
	(yyval.myStruct.asmbly)=(yyvsp[-2].myStruct.asmbly);		
}
#line 1848 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 550 "parser.y" /* yacc.c:1646  */
    {		
	int i=0;
	for(i=0;i<expCount;i++)
	{
		//printf("Expr %d : %s\n",i,expList[i]);

	}	
}
#line 1861 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 560 "parser.y" /* yacc.c:1646  */
    { 
	(yyval.myStruct.next)=(yyvsp[0].myStruct.next);
	(yyval.myStruct.trueLabel)=(yyvsp[0].myStruct.trueLabel);
	(yyval.myStruct.falseLabel)=(yyvsp[0].myStruct.falseLabel);
	(yyval.myStruct.var)=(yyvsp[0].myStruct.var);
	(yyval.myStruct.code)=(yyvsp[0].myStruct.code);
	(yyval.myStruct.asmbly)=(yyvsp[0].myStruct.asmbly);
}
#line 1874 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 569 "parser.y" /* yacc.c:1646  */
    { 
	(yyval.myStruct.next)=(yyvsp[-2].myStruct.next)=(yyvsp[0].myStruct.next);
	(yyval.myStruct.code)=str_append((yyvsp[-2].myStruct.code),(yyvsp[0].myStruct.code));
	(yyval.myStruct.asmbly)=str_append((yyvsp[-2].myStruct.asmbly),(yyvsp[0].myStruct.asmbly));
}
#line 1884 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 577 "parser.y" /* yacc.c:1646  */
    {
	(yyval.myStruct.trueLabel)=(yyvsp[-2].myStruct.trueLabel)=newlabel();
	(yyval.myStruct.falseLabel)=(yyvsp[-2].myStruct.falseLabel)=(yyvsp[-2].myStruct.next)=(yyval.myStruct.next)=newSuperLabel(); 	//Devise how to add label
	char first[100];
	sprintf(first,"if F %s goto %s\n",(yyvsp[-2].myStruct.var),(yyvsp[-2].myStruct.trueLabel));
	char* cd = str_append(first,(yyvsp[0].myStruct.code));
	cd=str_append((yyvsp[-2].myStruct.code),cd);
	cd=str_append(cd,genLabel((yyvsp[-2].myStruct.falseLabel)));
	cd=str_append(cd,setLabel((yyvsp[-2].myStruct.trueLabel)));
	(yyval.myStruct.code)=cd;

	char* cda;
	char* str =(char *) malloc(100);
	cda=str_append("",(yyvsp[-2].myStruct.asmbly));
	sprintf(str,"li $t1 0\n");
	cda=str_append(cda,str);
	sprintf(str,"beq $a0 $t1 %s\n",(yyvsp[-2].myStruct.trueLabel));
	cda=str_append(cda,str);
	cda=str_append(cda,(yyvsp[0].myStruct.asmbly));
	cda=str_append(cda,genAsmLabel((yyvsp[-2].myStruct.falseLabel)));
	cda=str_append(cda,setLabel((yyvsp[-2].myStruct.trueLabel)));
	(yyval.myStruct.asmbly)=cda;
}
#line 1912 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 602 "parser.y" /* yacc.c:1646  */
    {
	(yyval.myStruct.var) = (yyvsp[0].myStruct.var);
	(yyval.myStruct.code)=(yyvsp[0].myStruct.code);
	(yyval.myStruct.asmbly)=(yyvsp[0].myStruct.asmbly);
}
#line 1922 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 609 "parser.y" /* yacc.c:1646  */
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
	(yyval.myStruct.code)=strdup(assign);
	(yyval.myStruct.asmbly)=strdup(asmb);
	varCount=expCount=0;
}
#line 1952 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 635 "parser.y" /* yacc.c:1646  */
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
	sprintf(first,"call %s, %d, %d\n",(yyvsp[-2].myStruct.var),expCount,varCount);
	assign=str_append(assign,first);
	for(i=0;i<varCount;i++)
	{
		sprintf(first,"return %s\n",varList[i]);
		assign=str_append(assign,first);
	}
	(yyval.myStruct.code)=strdup(assign);
	(yyval.myStruct.asmbly)=funcCall((yyvsp[-2].myStruct.var));
	varCount=expCount=0;
}
#line 1985 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 664 "parser.y" /* yacc.c:1646  */
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
	sprintf(first,"call %s, %d\n",(yyvsp[-2].myStruct.var),expCount);
	assign=str_append(assign,first);
	(yyval.myStruct.code)=strdup(assign);
	(yyval.myStruct.asmbly)=funcCall((yyvsp[-2].myStruct.var));
	varCount=expCount=0;
}
#line 2013 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 688 "parser.y" /* yacc.c:1646  */
    {
	int i=0;
	char* assign="";
	char* asmb="";
	char first[200];
	sprintf(first,"call %s, %d\n",(yyvsp[-1].myStruct.var),varCount);
	assign=str_append(assign,first);
	for(i=0;i<varCount;i++)
	{
		sprintf(first,"return %s\n",varList[i]);
		assign=str_append(assign,first);
	}
	(yyval.myStruct.code)=strdup(assign);
	varCount=expCount=0;
	(yyval.myStruct.asmbly)=funcCall((yyvsp[-1].myStruct.var));
	//printf("vars := subprogram :=\n");
	//printf("no parameters but returns variables\n");
}
#line 2036 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 707 "parser.y" /* yacc.c:1646  */
    {
	char first[200];
	sprintf(first,"call %s\n",(yyvsp[-1].myStruct.var));
	(yyval.myStruct.code)=strdup(first);
	(yyval.myStruct.asmbly)=(yyvsp[-1].myStruct.asmbly);
	//printf(":= subprogram :=\n");
	//printf(" no parameter and no arguments\n");
}
#line 2049 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 716 "parser.y" /* yacc.c:1646  */
    {
	(yyval.myStruct.var) = (yyvsp[0].myStruct.var);
	(yyval.myStruct.code)=(yyvsp[0].myStruct.code);
	(yyval.myStruct.asmbly)=(yyvsp[0].myStruct.asmbly);
}
#line 2059 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 723 "parser.y" /* yacc.c:1646  */
    {
	//printf("Vars -> id %d %s\n",varCount,$1);
	strcpy(varList[varCount++],(yyvsp[0].myStruct.var));
}
#line 2068 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 728 "parser.y" /* yacc.c:1646  */
    {
	//printf("Inside vars -> vars,id %d %s\n",varCount,$3);
	strcpy(varList[varCount++],(yyvsp[0].myStruct.var));
}
#line 2077 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 734 "parser.y" /* yacc.c:1646  */
    {
	//printf("Inside exprs -> expr\n");	
	//printf("%s = %s\n",varList[expCount++],$1);
	//printf("%s\n",$<myStruct.code>1);
	codeList[expCount]=malloc(strlen((yyvsp[0].myStruct.code)));
	strcpy(codeList[expCount],(yyvsp[0].myStruct.code));
	strcpy(asmbList[expCount],(yyvsp[0].myStruct.asmbly));
	strcpy(expList[expCount++],(yyvsp[0].myStruct.var));	
}
#line 2091 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 744 "parser.y" /* yacc.c:1646  */
    {	
	//printf("Inside exprs -> exprs,expr\n");	
	//printf("%s = %s\n",varList[expCount++],$3);
	codeList[expCount]=malloc(strlen((yyvsp[0].myStruct.code)));
	strcpy(codeList[expCount],(yyvsp[0].myStruct.code));
	strcpy(asmbList[expCount],(yyvsp[0].myStruct.asmbly));
	strcpy(expList[expCount++],(yyvsp[0].myStruct.var));	
}
#line 2104 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 755 "parser.y" /* yacc.c:1646  */
    {
	//printf("Expr -> Disjunction\n",$<myStruct.asmbly>1);
	(yyval.myStruct.var) = (yyvsp[0].myStruct.var);
	(yyval.myStruct.code)=(yyvsp[0].myStruct.code);
	(yyval.myStruct.asmbly)=(yyvsp[0].myStruct.asmbly);
}
#line 2115 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 763 "parser.y" /* yacc.c:1646  */
    {
	(yyval.myStruct.var)=(yyvsp[0].myStruct.var);
	(yyval.myStruct.code)=(yyvsp[0].myStruct.code);
	(yyval.myStruct.asmbly)=(yyvsp[0].myStruct.asmbly);
}
#line 2125 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 769 "parser.y" /* yacc.c:1646  */
    { 
	char* str=(char*)malloc(100* sizeof(char));	
	char* newvar=t_incre(); 
	sprintf(str,"%s = %s | %s \n", newvar, (yyvsp[-2].myStruct.var), (yyvsp[0].myStruct.var)); 
	(yyval.myStruct.var)=newvar;
	char *cd=str_append((yyvsp[-2].myStruct.code),(yyvsp[0].myStruct.code));
	(yyval.myStruct.code)=str_append(cd,str);


	sprintf(str,"move $t1 $a0\n");
	cd=str_append((yyvsp[-2].myStruct.asmbly),str);
	cd=str_append(cd,(yyvsp[0].myStruct.asmbly));
	sprintf(str,"or $a0 $t1 $a0\n");
	cd=str_append(cd,str);
	(yyval.myStruct.asmbly)=strdup(cd);

	//if(printDebug==1)printf("Or Print : %s\n",$<myStruct.code>$);
	free(cd);
	free(str);

}
#line 2151 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 793 "parser.y" /* yacc.c:1646  */
    {
	(yyval.myStruct.var)=(yyvsp[0].myStruct.var);
	(yyval.myStruct.code)=(yyvsp[0].myStruct.code);
	(yyval.myStruct.asmbly)=(yyvsp[0].myStruct.asmbly);
}
#line 2161 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 799 "parser.y" /* yacc.c:1646  */
    {
	char* str=(char*)malloc(100* sizeof(char));		
	char* newvar=t_incre(); 
	sprintf(str,"%s = %s & %s \n", newvar, (yyvsp[-2].myStruct.var), (yyvsp[0].myStruct.var)); 
	(yyval.myStruct.var)=newvar;
	char *cd=str_append((yyvsp[-2].myStruct.code),(yyvsp[0].myStruct.code));
	(yyval.myStruct.code)=str_append(cd,str);

	sprintf(str,"move $t1 $a0\n");
	cd=str_append((yyvsp[-2].myStruct.asmbly),str);
	cd=str_append(cd,(yyvsp[0].myStruct.asmbly));
	sprintf(str,"and $a0 $t1 $a0\n");
	cd=str_append(cd,str);
	(yyval.myStruct.asmbly)=strdup(cd);

	free(cd);
	free(str);

	//printf("Conjunction and Negation\n");
}
#line 2186 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 823 "parser.y" /* yacc.c:1646  */
    {
	(yyval.myStruct.var)=(yyvsp[0].myStruct.var);
	(yyval.myStruct.code)=(yyvsp[0].myStruct.code);
	(yyval.myStruct.asmbly)=(yyvsp[0].myStruct.asmbly);
}
#line 2196 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 829 "parser.y" /* yacc.c:1646  */
    {
	char rel[30]; 
	rel[0] = '~'; 
	sprintf(rel+1,"%s",(yyvsp[0].myStruct.var));

	char* str=(char*)malloc(100* sizeof(char));		
	char* newvar=t_incre(); 
	sprintf(str,"%s = %s\n",newvar,rel); 
	(yyval.myStruct.var)=newvar;
	char *cd=strdup((yyvsp[0].myStruct.code));
	(yyval.myStruct.code)=str_append(cd,str);

	sprintf(str,"not $a0 $a0\n");
	(yyval.myStruct.asmbly)=str_append((yyvsp[0].myStruct.asmbly),str);
	free(cd);
	free(str);
}
#line 2218 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 857 "parser.y" /* yacc.c:1646  */
    {
	(yyval.myStruct.var)=(yyvsp[0].myStruct.var);
	(yyval.myStruct.code)=(yyvsp[0].myStruct.code);
	(yyval.myStruct.asmbly)=(yyvsp[0].myStruct.asmbly);
}
#line 2228 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 863 "parser.y" /* yacc.c:1646  */
    {
	char* str=(char*)malloc(100* sizeof(char));		
	char* newvar=t_incre(); 
	sprintf(str,"%s = %s < %s \n", newvar, (yyvsp[-2].myStruct.var), (yyvsp[0].myStruct.var)); 
	(yyval.myStruct.var)=newvar;
	char *cd=str_append((yyvsp[0].myStruct.code),(yyvsp[-2].myStruct.code));
	(yyval.myStruct.code)=str_append(cd,str);
	char *asmb=(char*)malloc(100* sizeof(char));
	sprintf(asmb,"move $t1 $a0\n");
	char* cda=str_append((yyvsp[0].myStruct.asmbly),asmb);
	sprintf(asmb,"slt $a0 $a0 $t1\n");
	cda=str_append(cda,(yyvsp[-2].myStruct.asmbly));
	(yyval.myStruct.asmbly)=str_append(cda,asmb);

	free(cda);
	free(cd);
	free(str);
	free(asmb);
	//printf("relation -> sum < sum\n");
}
#line 2253 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 884 "parser.y" /* yacc.c:1646  */
    {
	char* str=(char*)malloc(100* sizeof(char));		
	char* newvar=t_incre(); 
	sprintf(str,"%s = %s <= %s \n",newvar, (yyvsp[-2].myStruct.var), (yyvsp[0].myStruct.var)); 
	(yyval.myStruct.var)=newvar;
	char *cd=str_append((yyvsp[0].myStruct.code),(yyvsp[-2].myStruct.code));
	(yyval.myStruct.code)=str_append(cd,str);

	char *asmb=(char*)malloc(100* sizeof(char));
	sprintf(asmb,"move $t1 $a0\n");
	char* cda=str_append((yyvsp[0].myStruct.asmbly),asmb);
	sprintf(asmb,"sle $a0 $a0 $t1\n");
	cda=str_append(cda,(yyvsp[-2].myStruct.asmbly));
	(yyval.myStruct.asmbly)=str_append(cda,asmb);

	free(cda);
	free(cd);
	free(str);
	free(asmb);
	//printf("relation -> sum <= sum\n");
}
#line 2279 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 906 "parser.y" /* yacc.c:1646  */
    {

	char* str=(char*)malloc(100* sizeof(char));		
	char* newvar=t_incre(); 
	sprintf(str,"%s = (%s == %s) \n",newvar, (yyvsp[-2].myStruct.var), (yyvsp[0].myStruct.var)); 
	(yyval.myStruct.var)=newvar;
	char *cd=str_append((yyvsp[0].myStruct.code),(yyvsp[-2].myStruct.code));
	(yyval.myStruct.code)=str_append(cd,str);

	char* asmb=(char*)malloc(100* sizeof(char));	
	sprintf(asmb,"move $t1 $a0\n");
	char* cda=str_append((yyvsp[0].myStruct.asmbly),asmb);
	sprintf(asmb,"seq $a0 $a0 $t1\n");
	cda=str_append(cda,(yyvsp[-2].myStruct.asmbly));
	(yyval.myStruct.asmbly)=str_append(cda,asmb);

	//if(printDebug==1)printf("Print : %s\n",$<myStruct.code>$);
	//printf("Eq %s %s\n",$<myStruct.var>1,$<myStruct.var>3);
	free(cda);
	free(cd);
	free(str);
	free(asmb);
	//printf("relation -> sum == sum\n");
}
#line 2308 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 931 "parser.y" /* yacc.c:1646  */
    {
	char* str=(char*)malloc(100* sizeof(char));		
	char* newvar=t_incre(); 
	sprintf(str,"%s = (%s != %s) \n",newvar, (yyvsp[-2].myStruct.var), (yyvsp[0].myStruct.var)); 
	(yyval.myStruct.var)=newvar;
	char *cd=str_append((yyvsp[0].myStruct.code),(yyvsp[-2].myStruct.code));
	(yyval.myStruct.code)=str_append(cd,str);

	char *asmb=(char*)malloc(100* sizeof(char));
	sprintf(asmb,"move $t1 $a0\n");
	char* cda=str_append((yyvsp[0].myStruct.asmbly),asmb);
	sprintf(asmb,"sne $a0 $a0 $t1\n");
	cda=str_append(cda,(yyvsp[-2].myStruct.asmbly));
	(yyval.myStruct.asmbly)=str_append(cda,asmb);

	free(cda);
	free(cd);
	free(str);
	free(asmb);
	//printf("relation -> sum != sum\n");
}
#line 2334 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 953 "parser.y" /* yacc.c:1646  */
    {
	char* str=(char*)malloc(100* sizeof(char));
	char* newvar=t_incre(); 
	sprintf(str,"%s = %s > %s \n",newvar, (yyvsp[-2].myStruct.var), (yyvsp[0].myStruct.var)); 
	(yyval.myStruct.var)=newvar;
	char *cd=str_append((yyvsp[0].myStruct.code),(yyvsp[-2].myStruct.code));
	(yyval.myStruct.code)=str_append(cd,str);

	char *asmb=(char*)malloc(100* sizeof(char));
	sprintf(asmb,"move $t1 $a0\n");
	char* cda=str_append((yyvsp[0].myStruct.asmbly),asmb);
	sprintf(asmb,"sgt $a0 $a0 $t1\n");
	cda=str_append(cda,(yyvsp[-2].myStruct.asmbly));
	(yyval.myStruct.asmbly)=str_append(cda,asmb);


	free(asmb);
	free(cda);
	free(cd);
	free(str);

	//printf("relation -> sum > sum\n");
}
#line 2362 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 977 "parser.y" /* yacc.c:1646  */
    {

	char* str=(char*)malloc(100* sizeof(char));		
	char* newvar=t_incre(); 
	sprintf(str,"%s = %s >= %s \n", newvar, (yyvsp[-2].myStruct.var), (yyvsp[0].myStruct.var)); 
	(yyval.myStruct.var)=newvar;
	char *cd=str_append((yyvsp[0].myStruct.code),(yyvsp[-2].myStruct.code));
	(yyval.myStruct.code)=str_append(cd,str);

	char* asmb=(char*)malloc(100* sizeof(char));
	sprintf(asmb,"move $t1 $a0\n");
	char* cda=str_append((yyvsp[0].myStruct.asmbly),asmb);
	sprintf(asmb,"sge $a0 $a0 $t1\n");
	cda=str_append(cda,(yyvsp[-2].myStruct.asmbly));
	(yyval.myStruct.asmbly)=str_append(cda,asmb);

	free(asmb);
	free(cda);
	free(cd);
	free(str);

	//printf("relation -> sum >= sum\n");
}
#line 2390 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 1002 "parser.y" /* yacc.c:1646  */
    { 
		//printf("Sum -> Term\n"); 
		(yyval.myStruct.var) = (yyvsp[0].myStruct.var); 
		(yyval.myStruct.code)= (yyvsp[0].myStruct.code);
		(yyval.myStruct.asmbly)=(yyvsp[0].myStruct.asmbly);
	}
#line 2401 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 1009 "parser.y" /* yacc.c:1646  */
    { 
		//printf("Sum -> - Term\n");
		char str[30]; 
		str[0] = '-'; 
		sprintf(str+1,"%s",(yyvsp[0].myStruct.var)); 
		(yyval.myStruct.var) = strdup(str); 
		(yyval.myStruct.code)= (yyvsp[0].myStruct.code);
		(yyval.myStruct.asmbly)=mips_li(str);		
	}
#line 2415 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 1019 "parser.y" /* yacc.c:1646  */
    { 
		//printf("Sum -> Sum+ Term\n");
		char* str=(char*)malloc(100* sizeof(char));	
		char* newvar=t_incre(); 
		sprintf(str,"%s = %s + %s \n",newvar, (yyvsp[-2].myStruct.var), (yyvsp[0].myStruct.var)); 
		(yyval.myStruct.var)=newvar;
		char *cd=str_append((yyvsp[0].myStruct.code),(yyvsp[-2].myStruct.code));
		(yyval.myStruct.code)=str_append(cd,str);

			//store,  add, load, addiu (overflow not checkd, )
		char* asmb=addAssembly((yyvsp[0].myStruct.asmbly),(yyvsp[-2].myStruct.asmbly));
		(yyval.myStruct.asmbly)=strdup(asmb);
		//printf("Print : %s\n",$<myStruct.code>$);
		free((yyvsp[-2].myStruct.var));
		free((yyvsp[0].myStruct.var));
		free(cd);
		free(str);
		free(asmb);
	}
#line 2439 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 1039 "parser.y" /* yacc.c:1646  */
    { 
		//printf("Sum -> Sum- Term\n");
		char* str=(char*)malloc(100* sizeof(char));	
		char* newvar=t_incre(); 
		sprintf(str,"%s = %s - %s \n",newvar, (yyvsp[-2].myStruct.var), (yyvsp[0].myStruct.var)); 
		(yyval.myStruct.var)=newvar;
		char *cd=str_append((yyvsp[0].myStruct.code),(yyvsp[-2].myStruct.code));
		(yyval.myStruct.code)=str_append(cd,str);
		char* asmb=subAssembly((yyvsp[0].myStruct.asmbly),(yyvsp[-2].myStruct.asmbly));
		(yyval.myStruct.asmbly)=strdup(asmb);
		//if(printDebug==1)printf("Print : %s\n",$<myStruct.code>$);
		free((yyvsp[-2].myStruct.var));
		free((yyvsp[0].myStruct.var));
		free(cd);
		free(str);
		free(asmb);
	}
#line 2461 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 1060 "parser.y" /* yacc.c:1646  */
    { 
		//printf("Term -> Factor\n"); 
		(yyval.myStruct.var) = (yyvsp[0].myStruct.var); 
		(yyval.myStruct.code) = (yyvsp[0].myStruct.code);
		(yyval.myStruct.asmbly)=(yyvsp[0].myStruct.asmbly);
	}
#line 2472 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 1067 "parser.y" /* yacc.c:1646  */
    { 
		//printf("Term -> Term * Factor\n"); 
		char* str=(char*)malloc(100* sizeof(char));	
		char* newvar=t_incre(); 
		
	sprintf(str,"%s = %s * %s \n",newvar, (yyvsp[-2].myStruct.var), (yyvsp[0].myStruct.var)); 
		(yyval.myStruct.var)=newvar;
		char *cd=str_append((yyvsp[0].myStruct.code),(yyvsp[-2].myStruct.code));
		(yyval.myStruct.code)=str_append(cd,str);
		char* asmb=multAssembly((yyvsp[0].myStruct.asmbly),(yyvsp[-2].myStruct.asmbly));
		(yyval.myStruct.asmbly)=strdup(asmb);
		//if(printDebug==1)printf("Print : %s\n",$<myStruct.code>$);
		free((yyvsp[-2].myStruct.var));
		free((yyvsp[0].myStruct.var));
		free(cd);
		free(str);
		free(asmb);
	}
#line 2495 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 1086 "parser.y" /* yacc.c:1646  */
    { 
		char* str=(char*)malloc(100* sizeof(char));
		char* newvar=t_incre(); 
		sprintf(str,"%s = %s / %s \n",newvar, (yyvsp[-2].myStruct.var), (yyvsp[0].myStruct.var)); 
		(yyval.myStruct.var)=newvar;
		char *cd=str_append((yyvsp[0].myStruct.code),(yyvsp[-2].myStruct.code));
		(yyval.myStruct.code)=str_append(cd,str);
		char* asmb=div_asm((yyvsp[0].myStruct.asmbly),(yyvsp[-2].myStruct.asmbly));
		(yyval.myStruct.asmbly)=strdup(asmb);
		//if(printDebug==1)	printf("Print : %s\n",$<myStruct.code>$);
		free((yyvsp[-2].myStruct.var));
		free((yyvsp[0].myStruct.var));
		free(asmb);
		free(cd);
		free(str);
	}
#line 2516 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 1105 "parser.y" /* yacc.c:1646  */
    {  	(yyval.myStruct.var)=(yyvsp[0].myStruct.var);   //same as $$ =$1
	(yyval.myStruct.code)="";                   
	(yyval.myStruct.asmbly)=mips_li((yyvsp[0].myStruct.var)); // $$ = load ( $1 ) 
}
#line 2525 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 1109 "parser.y" /* yacc.c:1646  */
    { (yyval.myStruct.var)=(yyvsp[0].myStruct.var); 
	(yyval.myStruct.code)="";
	 (yyval.myStruct.asmbly)=mips_li((yyvsp[0].myStruct.var));
}
#line 2534 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 1113 "parser.y" /* yacc.c:1646  */
    { (yyval.myStruct.var) =(yyvsp[0].myStruct.var); (yyval.myStruct.code)=""; (yyval.myStruct.asmbly)=mips_li((yyvsp[0].myStruct.var));}
#line 2540 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 1114 "parser.y" /* yacc.c:1646  */
    { (yyval.myStruct.var) ="True"; (yyval.myStruct.code)=""; (yyval.myStruct.asmbly)=mips_li("True");}
#line 2546 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 1115 "parser.y" /* yacc.c:1646  */
    { (yyval.myStruct.var) ="False"; (yyval.myStruct.code)="";	(yyval.myStruct.asmbly)=mips_li("False");}
#line 2552 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 1117 "parser.y" /* yacc.c:1646  */
    { 
		
		(yyval.myStruct.var) = (yyvsp[-1].myStruct.var); 
		(yyval.myStruct.code)= (yyvsp[-1].myStruct.code);
		(yyval.myStruct.asmbly)=(yyvsp[-1].myStruct.asmbly);
	}
#line 2563 "parser.tab.c" /* yacc.c:1646  */
    break;


#line 2567 "parser.tab.c" /* yacc.c:1646  */
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
#line 1124 "parser.y" /* yacc.c:1906  */

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

