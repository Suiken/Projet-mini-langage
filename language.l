%option noyywrap
%{

#include "language.h"
#include <stdlib.h>
#include "language_tree.h"

%}
/* tout ce qui est lié aux calculs */
empty    [ \t]+
comms 	("//").+
comms_multi "/*"((.*)(\n))+"*/"

num   [0-9]
int    {num}+
exp  [eE][+-]?{int}

real      {int}("."{int})?{exp}?

while	"tantque"
endwhile "fintantque"
if	"si"
endif	"finsi"
bool 	"vrai"|"faux"
type	"reel"|"booleen"
afficher "afficher"
variable	[a-z]+
%%

{empty}  { /* Nothing */ }
{comms}  { /* Etant donné que c'est des commentaire, on ne fait rien */ }
{comms_multi} { /*Pareil que la ligne précédente */ }


"("   return(OP_PAR);
")"   return(CL_PAR);


{real}    {
    yylval.node = createNode(NTNUM);
    yylval.node->val = atof(yytext);
    return(NUM);
    }

{while} {
    yylval.node = createNode(NTWHILE);
    yylval.node->var = strdup(yytext);
    return(WHILE);
}

{endwhile} {
    return(ENDWHILE);
}

{if} 	{
    yylval.node = createNode(NTIF);
    yylval.node->var = strdup(yytext);
    return(IF);
    }

{endif}	{
    return(ENDIF);
    }

{bool}  {
    yylval.node = createNode(NTBOOL);
    yylval.node->var = strdup(yytext);
    return(BOOL);
    }

{type} {
   yylval.node = createNode(NTTYPE);
   yylval.node->var = strdup(yytext);
   return(TYPE);
   }

{afficher} {
   yylval.node = createNode(NTAFFI);
   yylval.node->var = strdup(yytext);
   return(AFFI);
}

{variable}  {
    yylval.node = createNode(NTVAR);
    yylval.node->var = strdup(yytext);
    return(VARIABLE);
    }

">"   { yylval.node = createNode(NTSUP); return(SUP); }
">="  { yylval.node = createNode(NTSUP_EG); return(SUP_EG); }
"<"   { yylval.node = createNode(NTINF); return(INF); }
"<="  { yylval.node = createNode(NTINF_EG); return(INF_EG); }
"=="  { yylval.node = createNode(NTEG_EG); return(EG_EG); }

"+"   { yylval.node = createNode(NTPLUS); return(PLUS); }
"-"   { yylval.node = createNode(NTMIN); return(MIN); }
"*"   { yylval.node = createNode(NTMULT); return(MULT); }
"/"   { yylval.node = createNode(NTDIV); return(DIV); }
"^"   { yylval.node = createNode(NTPOW); return(POW); }
"%"   { yylval.node = createNode(NTMOD); return(MOD); }
"="   { yylval.node = createNode(NTEGAL); return(EGAL); }

";"    { return(COLON); }

"\n"   { return(EOL); }
