%{
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "language_tree.h"
#include "language_eval.h"

extern int  yyparse();
extern FILE *yyin;

void yyerror(char *s);
int yylex();
int exec(Node *node);

int yydebug = 1;

Node root;
%}

%union {
	struct Node *node;
}

%token	 <node> SUP INF SUP_EG INF_EG EG_EG
%token	 <node> WHILE ENDWHILE
%token	 <node> IF ENDIF
%token	 <node> AFFI
%token	 <node> TYPE
%token   <node> NUM VARIABLE BOOL
%token   <node> PLUS MIN MULT DIV POW MOD EGAL
%token   OP_PAR CL_PAR COLON
%token   EOL

%type   <node> Instlist
%type   <node> Inst
%type   <node> Expr
%type 	<node> Aff
%type 	<node> Decl
%type	<node> Comp
%type 	<node> Autre
%type	<node> If
%type	<node> While

%left EGAL
%left EG_EG SUP SUP_EG INF INF_EG
%left OR
%left AND
%left EQ NEQ
%left GT LT GET LET
%left PLUS MIN
%left MULT  DIV  MOD
%left NEG NOT
%right  POW
%left TYPE

%start Input
%%

Input:
      { /* Nothing ... */ }
  | Line Input { /* Nothing ... */ }


Line:
    EOL {  }
  | Instlist EOL { exec($1); printf("");  }
  ; 

Instlist:
    Inst { $$ = nodeChildren(createNode(NTINSTLIST), $1, createNode(NTEMPTY)); } 
  | Instlist Inst { $$ = nodeChildren(createNode(NTINSTLIST), $1, $2); }
  | If { $$ = $1; }
  | While { $$ = $1; }
  ;

Inst:
  Expr COLON { $$ = $1; }
  | Aff COLON { $$ = $1; }
  | Decl COLON { $$ = $1; }
  | Comp COLON { $$ = $1; }
  | Autre COLON { $$ = $1; }
  ;


Expr:
  NUM		       { $$ = $1; }
  | VARIABLE	       { $$ = $1; }
  | Expr PLUS Expr     { $$ = nodeChildren($2, $1, $3); }
  | Expr MIN Expr      { $$ = nodeChildren($2, $1, $3); }
  | Expr MULT Expr     { $$ = nodeChildren($2, $1, $3); }
  | Expr DIV Expr      { $$ = nodeChildren($2, $1, $3); }
  | MIN Expr %prec NEG { $$ = nodeChildren($1, createNode(NTEMPTY), $2); }
  | Expr POW Expr      { $$ = nodeChildren($2, $1, $3); }
  | Expr MOD Expr      { $$ = nodeChildren($2, $1, $3); }
  | OP_PAR Expr CL_PAR { $$ = $2; }
  ;

Aff:
  VARIABLE EGAL Expr { $$ = nodeChildren($2, $1, $3); }
  | VARIABLE EGAL Comp {$$ = nodeChildren($2, $1, $3); }
  ;

Decl:
  TYPE VARIABLE       		{ $$ = nodeChildren(createNode(NTDECL), $2, $1); }
  ;

Comp:
  BOOL { $$ = $1; }
  | Expr EG_EG Expr { $$ = nodeChildren(createNode(NTEG_EG), $1, $3);}
  | Expr SUP Expr { $$ = nodeChildren(createNode(NTSUP), $1, $3); } 
  | Expr SUP_EG Expr { $$ = nodeChildren(createNode(NTSUP_EG), $1, $3); }
  | Expr INF Expr { $$ = nodeChildren(createNode(NTINF), $1, $3); }
  | Expr INF_EG Expr { $$ = nodeChildren(createNode(NTINF_EG), $1, $3); }
  ;

Autre:
  AFFI OP_PAR Expr CL_PAR { $$ = nodeChildren(createNode(NTPRIN), $1, $3); }
  | AFFI OP_PAR Comp CL_PAR { $$ = nodeChildren(createNode(NTPRIN), $1, $3); }
  ;

If:
  IF OP_PAR Comp CL_PAR EOL Instlist EOL ENDIF { $$ = nodeChildren(createNode(NTIF), $3, $6); } 
  ;

While:
  WHILE OP_PAR Comp CL_PAR EOL Instlist EOL ENDWHILE { $$ = nodeChildren(createNode(NTWHILE), $3, $6); }
  ;
%%


 

int exec(Node *node) {
  //printGraph(node);
  eval(node);
  return 1;
}

 

void yyerror(char *s) {
  printf("%s\n", s);
}

 

int main(int arc, char **argv) {
   if ((arc == 3) && (strcmp(argv[1], "-f") == 0)) {
    
    FILE *fp=fopen(argv[2],"r");
    if(!fp) {
      printf("Impossible d'ouvrir le fichier à executer.\n");
      exit(0);
    }      
    yyin=fp;
    yyparse();
		  
    fclose(fp);
  }else{
    yyparse();
  }  
  exit(0);
  printf("\n");
}
