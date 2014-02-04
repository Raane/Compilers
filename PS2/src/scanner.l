%{
/* This %{ ... %} section is code that is glued into the generated scanner. */
#include "parser.h"
#define YYDEBUG 1
extern int outputStage; // This variable is located in vslc.c
    #define RETURN(t) do {                                             \
        if ( outputStage == 1 )                                        \
            fprintf ( stderr, "TOKEN ( %d,\t'%s' )\n", t, yytext );    \
        return t;                                                      \
    } while ( 0 )
    
    
%}

%option array
%option noyywrap
%option yylineno

DIGIT [0-9]
WHITESPACE [\ \n\t]
LETTER [a-zA-Z]

%%
FUNC            { RETURN(FUNC); }
PRINT           { RETURN(PRINT); }
RETURN          { RETURN(RETURN); }
IF              { RETURN(IF); }
THEN            { RETURN(THEN); }
ELSE            { RETURN(ELSE); }
END             { RETURN(END); }
WHILE           { RETURN(WHILE); }
DO              { RETURN(DO); }
INT             { RETURN(INT); }
BOOL            { RETURN(BOOL); }
FLOAT           { RETURN(FLOAT); }
CLASS           { RETURN(_CLASS_); }
HAS             { RETURN(HAS); }
WITH            { RETURN(WITH); }
START           { RETURN(START); }
VIOD            { RETURN(VOID); }
THIS            { RETURN(THIS); }
NEW             { RETURN(NEW); }
TRUE            { RETURN(FALSE); }
FALSE           { RETURN(FALSE); }
":="            { RETURN(ASSIGN); }
"<="            { RETURN(GEQUAL); }
">="            { RETURN(LEQUAL); }
"=="            { RETURN(EQUAL); }
"!="            { RETURN(NEQUAL); }
"&&"            { RETURN(AND); }
"||"            { RETURN(OR); }
"//"[^\n]*      { }
{WHITESPACE}+   { }
{DIGIT}+                    { yylval = atoi(yytext); RETURN(INT_CONST); }
{DIGIT}+"."{DIGIT}+         { yylval = atoi(yytext); RETURN(FLOAT_CONST); }
"\""[^\n]*"\""              { yylval = (intptr_t) yytext; RETURN(STRING_CONST); }
{LETTER}({LETTER}|{DIGIT})* { yylval = (intptr_t) yytext; RETURN(IDENTIFIER); }
.                           { RETURN( yytext[0] ); }
%%
