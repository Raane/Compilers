%{
#include "parser.h"
#include "stdint.h"
#ifdef DUMP_TOKENS
    #define RETURN(t) do {                                      \
        fprintf ( stderr, "TOKEN ( %d,\t'%s' )\n", t, yytext );    \
        return t;                                               \
    } while ( 0 )
#else
    #define RETURN(t) return t
#endif
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
CONTINUE        { RETURN(CONTINUE); }
IF              { RETURN(IF); }
THEN            { RETURN(THEN); }
ELSE            { RETURN(ELSE); }
FI              { RETURN(FI); }
WHILE           { RETURN(WHILE); }
DO              { RETURN(DO); }
DONE            { RETURN(DONE); }
FOR             { RETURN(FOR); }
TO              { RETURN(TO); }
VAR             { RETURN(VAR); }
":="            { RETURN(ASSIGN); }
"+"             { RETURN('+'); }
"-"             { RETURN('-'); }
"*"             { RETURN('*'); }
"/"             { RETURN('/'); }
">"             { RETURN('>'); }
"<"             { RETURN('<'); }
"<="            { RETURN(GEQUAL); }
">="            { RETURN(LEQUAL); }
"=="            { RETURN(EQUAL); }
"!="            { RETURN(NEQUAL); }
"("              {RETURN('('); }
")"              {RETURN(')'); }
"{"              {RETURN('{'); }
"}"              {RETURN('}'); }
"//"[^\n]*      { }
{WHITESPACE}+   { }
{DIGIT}+        { yylval = atoi(yytext); RETURN(NUMBER); }
"\""[^\n]*"\""  { yylval = (intptr_t) yytext; RETURN(STRING); }
{LETTER}({LETTER}|{DIGIT})* { yylval = (intptr_t) yytext; RETURN(IDENTIFIER); }
%%
