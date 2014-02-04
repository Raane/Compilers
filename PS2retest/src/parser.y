%{
#include "nodetypes.h"
#include "tree.h"
#include <stdlib.h>

// This defines the type for every $$ value in the productions.
#define YYSTYPE node_t *

#define YYDEBUG 1

// This variable is located in vslc.c
extern int outputStage;

/*
 * Variables connecting the parser to the state of the scanner - defs. will be
 * generated as part of the scanner (lexical analyzer).
 */
extern char yytext[];
extern int yylineno;

/*
 * Wrapper functions for node_init. The main purpose of calling these functions
 * instead of node_init directly is to enable the debug output, as well as a reduction
 * of typing. These functions are named CN for "create
 * node", and L, T, or E if they take an additional label, type or expression_type argument
 * in addition. When the label, type or expression_type is not supplied, node_init is called
 * default values.
 */
 
node_t* CN(nodetype_t type, int n_children, ...){
	if( outputStage == 2 ) fprintf ( stderr, "Hit rule \"%s\" on text '%s' at line %d\n", type.text , yytext, yylineno );
	va_list child_list;
	va_start(child_list, n_children);
	node_t* to_return = node_init(type, NULL, NO_TYPE, default_e, n_children, child_list);
	va_end(child_list);
	return to_return;
}

node_t* CNL(nodetype_t type, char* label, int n_children, ...){
	if( outputStage == 2 ) fprintf ( stderr, "Hit rule \"%s\" on text '%s' at line %d\n", type.text , yytext, yylineno );
	va_list child_list;
	va_start(child_list, n_children);
	node_t* to_return = node_init(type, label, NO_TYPE, default_e, n_children, child_list);
	va_end(child_list);
	return to_return;
}

node_t* CNT(nodetype_t type, base_data_type_t base_type, int n_children, ...){
	if( outputStage == 2 ) fprintf ( stderr, "Hit rule \"%s\" on text '%s' at line %d\n", type.text , yytext, yylineno );
	va_list child_list;
	va_start(child_list, n_children);
	node_t* to_return = node_init(type, NULL, base_type, default_e, n_children, child_list);
	va_end(child_list);
	return to_return;
}

node_t* CNE(nodetype_t type, expression_type_t expression_type, int n_children, ...){
	if( outputStage == 2 ) fprintf ( stderr, "Hit rule \"%s\" on text '%s' at line %d\n", type.text , yytext, yylineno );
	va_list child_list;
	va_start(child_list, n_children);
	node_t* to_return = node_init(type, NULL, NO_TYPE, expression_type, n_children, child_list);
	va_end(child_list);
	return to_return;
}


// Helper for setting the value of an Integer node
static void SetInteger(node_t* node, char *string)
{
	node->int_const = atol ( string );
	node->data_type.base_type= INT_TYPE;
}

// Helper for setting the value of an float node
static void SetFloat(node_t* node, char *string)
{
	node->float_const = atof ( string );
	node->data_type.base_type= FLOAT_TYPE;
}


// Helper for setting the value of an string node
static void SetString(node_t* node, char *string)
{
	node->string_const = STRDUP( string );
	node->data_type.base_type= STRING_TYPE;
}

/*
 * Since the return value of yyparse is an integer (as defined by yacc/bison),
 * we need the top level production to finalize parsing by setting the root
 * node of the entire syntax tree inside its semantic rule instead. This global
 * variable will let us get a hold of the tree root after it has been
 * generated.
 */
node_t *root;


/*
 * These functions are referenced by the generated parser before their
 * definition. Prototyping them saves us a couple of warnings during build.
 */
int yyerror ( const char *error );  /* Defined below */
int yylex ( void );                 /* Defined in the generated scanner */
%}


/* Tokens for all the key words in VSL */
%token INT_CONST FLOAT_CONST TRUE_CONST FALSE_CONST STRING_CONST
%token INT FLOAT BOOL VOID IDENTIFIER
%token ASSIGN FUNC START PRINT RETURN IF THEN ELSE END WHILE DO
%token EQUAL GEQUAL LEQUAL NEQUAL AND OR  
%token _CLASS_ THIS HAS WITH NEW

/*
 * Operator precedences:
 * UMINUS refers to unary minus, since the '-' sign is allready used for
 * binary minus.
 */

%left AND OR
%left EQUAL NEQUAL
%left GEQUAL LEQUAL '<' '>'
%left '+' '-'
%left '*' '/'
%nonassoc UMINUS
%left '.' 

/*
 * The grammar productions follow below. These are mostly a straightforward
 * statement of the language grammar, with semantic rules building a tree data
 * structure which we can traverse in subsequent phases in order to understand
 * the parsed program. (The leaf nodes at the bottom need somewhat more
 * specific rules, but these should be manageable.)
 */ 

%%

PROGRAM             : FUNCTION_LIST                                     { node_init ( root = malloc(sizeof(node_t)), program_n, NULL, 1, $1 ); };
FUNCTION_LIST       : FUNCTION                                          { node_init ( $$ = malloc(sizeof(node_t)), function_list_n, NULL, 1, $1 ); }
                    | FUNCTION_LIST FUNCTION                            { node_init ( $$ = malloc(sizeof(node_t)), function_list_n, NULL, 2, $1, $2 ); };
STATEMENT_LIST      : STATEMENT                                         { node_init ( $$ = malloc(sizeof(node_t)), statement_list_n, NULL, 1, $1 ); }
                    | STATEMENT_LIST STATEMENT                          { node_init ( $$ = malloc(sizeof(node_t)), statement_list_n, NULL, 2, $1, $2 ); };
PRINT_LIST          : PRINT_ITEM                                        { node_init ( $$ = malloc(sizeof(node_t)), print_list_n, NULL, 1, $1 ); }
                    | PRINT_LIST ',' PRINT_ITEM                         { node_init ( $$ = malloc(sizeof(node_t)), print_list_n, NULL, 2, $1, $3 ); };
EXPRESSION_LIST     : EXPRESSION                                        { node_init ( $$ = malloc(sizeof(node_t)), expression_list_n, NULL, 1, $1 ); }
                    | EXPRESSION_LIST ',' EXPRESSION                    { node_init ( $$ = malloc(sizeof(node_t)), expression_list_n, NULL, 2, $1, $3 ); };
VARIABLE_LIST       : VARIABLE                                          { node_init ( $$ = malloc(sizeof(node_t)), variable_list_n, NULL, 1, $1 ); }
                    | INDEXED_VARIABLE                                  { node_init ( $$ = malloc(sizeof(node_t)), variable_list_n, NULL, 1, $1 ); }
                    | VARIABLE_LIST ',' VARIABLE                        { node_init ( $$ = malloc(sizeof(node_t)), variable_list_n, NULL, 2, $1, $3 ); }
                    | VARIABLE_LIST ',' INDEXED_VARIABLE                { node_init ( $$ = malloc(sizeof(node_t)), variable_list_n, NULL, 2, $1, $3 ); };
DECLARATION_LIST    : DECLARATION_LIST DECLARATION                      { node_init ( $$ = malloc(sizeof(node_t)), declaration_list_n, NULL, 2, $1, $2 ); }
                    |                                                   { node_init ( $$ = NULL, declaration_list_n, NULL, 0 ); };
ARGUMENT_LIST       : EXPRESSION_LIST                                   { node_init ( $$ = malloc(sizeof(node_t)), argument_list_n, NULL, 1, $1 ); }
                    |                                                   { node_init ( $$ = NULL, argument_list_n, NULL, 0 ); };
PARAMETER_LIST      : VARIABLE_LIST                                     { node_init ( $$ = malloc(sizeof(node_t)), parameter_list_n, NULL, 1, $1 ); }
                    |                                                   { node_init ( $$ = NULL, parameter_list_n, NULL, 0 ); };
FUNCTION            : FUNC VARIABLE '(' PARAMETER_LIST ')' STATEMENT    { node_init ( $$ = malloc(sizeof(node_t)), function_n, NULL, 3, $2, $4, $6 ); };
STATEMENT           : ASSIGNMENT_STATEMENT                              { node_init ( $$ = malloc(sizeof(node_t)), statement_n, NULL, 1, $1 ); }
                    | RETURN_STATEMENT                                  { node_init ( $$ = malloc(sizeof(node_t)), statement_n, NULL, 1, $1 ); }
                    | PRINT_STATEMENT                                   { node_init ( $$ = malloc(sizeof(node_t)), statement_n, NULL, 1, $1 ); }
                    | NULL_STATEMENT                                    { node_init ( $$ = malloc(sizeof(node_t)), statement_n, NULL, 1, $1 ); }
                    | IF_STATEMENT                                      { node_init ( $$ = malloc(sizeof(node_t)), statement_n, NULL, 1, $1 ); }
                    | WHILE_STATEMENT                                   { node_init ( $$ = malloc(sizeof(node_t)), statement_n, NULL, 1, $1 ); }
                    | BLOCK                                             { node_init ( $$ = malloc(sizeof(node_t)), statement_n, NULL, 1, $1 ); };
BLOCK               : '{' DECLARATION_LIST STATEMENT_LIST '}'           { node_init ( $$ = malloc(sizeof(node_t)), block_n, NULL, 2, $2, $3 ); };
ASSIGNMENT_STATEMENT: VARIABLE ASSIGN EXPRESSION                        { node_init ( $$ = malloc(sizeof(node_t)), assignment_statement_n, NULL, 2, $1, $3 ); }
                    | VARIABLE '[' EXPRESSION ']' ASSIGN EXPRESSION     { node_init ( $$ = malloc(sizeof(node_t)), assignment_statement_n, NULL, 3, $1, $3, $6 ); };
RETURN_STATEMENT    : RETURN EXPRESSION                                 { node_init ( $$ = malloc(sizeof(node_t)), return_statement_n, NULL, 1, $2 ); };
PRINT_STATEMENT     : PRINT PRINT_LIST                                  { node_init ( $$ = malloc(sizeof(node_t)), print_statement_n, NULL, 1, $2 ); };
IF_STATEMENT        : IF EXPRESSION THEN STATEMENT END                  { node_init ( $$ = malloc(sizeof(node_t)), if_statement_n, NULL, 2, $2, $4 ); }
                    | IF EXPRESSION THEN STATEMENT ELSE STATEMENT END   { node_init ( $$ = malloc(sizeof(node_t)), if_statement_n, NULL, 3, $2, $4, $6 ); };
WHILE_STATEMENT     : WHILE EXPRESSION DO STATEMENT END                 { node_init ( $$ = malloc(sizeof(node_t)), while_statement_n, NULL, 2, $2, $4 ); };
EXPRESSION          : EXPRESSION '+' EXPRESSION                         { node_init ( $$ = malloc(sizeof(node_t)), expression_n, STRDUP("+"), 2, $1, $3 ); }
                    | EXPRESSION '-' EXPRESSION                         { node_init ( $$ = malloc(sizeof(node_t)), expression_n, STRDUP("-"), 2, $1, $3 ); }
                    | EXPRESSION '*' EXPRESSION                         { node_init ( $$ = malloc(sizeof(node_t)), expression_n, STRDUP("*"), 2, $1, $3 ); }
                    | EXPRESSION '/' EXPRESSION                         { node_init ( $$ = malloc(sizeof(node_t)), expression_n, STRDUP("/"), 2, $1, $3 ); }
                    | '-' EXPRESSION %prec UMINUS                       { node_init ( $$ = malloc(sizeof(node_t)), expression_n, STRDUP("-"), 1, $2 ); }
                    | EXPRESSION '^' EXPRESSION                         { node_init ( $$ = malloc(sizeof(node_t)), expression_n, STRDUP("^"), 2, $1, $3 ); }
                    | '(' EXPRESSION ')'                                { node_init ( $$ = malloc(sizeof(node_t)), expression_n, NULL, 1, $2 ); }
                    | INTEGER                                           { node_init ( $$ = malloc(sizeof(node_t)), expression_n, NULL, 1, $1 ); }
                    | VARIABLE                                          { node_init ( $$ = malloc(sizeof(node_t)), expression_n, NULL, 1, $1 ); }
                    | VARIABLE '(' ARGUMENT_LIST ')'                    { node_init ( $$ = malloc(sizeof(node_t)), expression_n, STRDUP("F"), 2, $1, $3 ); }
                    | VARIABLE '[' EXPRESSION ']'                       { node_init ( $$ = malloc(sizeof(node_t)), expression_n, STRDUP("A"), 2, $1, $3 ); };
DECLARATION         : VAR VARIABLE_LIST                                 { node_init ( $$ = malloc(sizeof(node_t)), declaration_n, NULL, 1, $2 ); };
VARIABLE            : IDENTIFIER                                        { node_init ( $$ = malloc(sizeof(node_t)), variable_n, STRDUP((char *) $1), 0 ); };
INDEXED_VARIABLE    : VARIABLE '[' INTEGER ']'                          { node_init ( $$ = malloc(sizeof(node_t)), variable_n, NULL, 2, $1, $3 ); };
INTEGER             : NUMBER                                            { int32_t* i = (int32_t *) malloc(sizeof(int32_t)); *i = (int) $1; node_init ( $$ = malloc(sizeof(node_t)), integer_n, i, 0 ); };
PRINT_ITEM          : EXPRESSION                                        { node_init ( $$ = malloc(sizeof(node_t)), print_item_n, NULL, 1, $1 ); }
                    | TEXT                                              { node_init ( $$ = malloc(sizeof(node_t)), print_item_n, NULL, 1, $1 ); };
TEXT                : STRING                                            { node_init ( $$ = malloc(sizeof(node_t)), text_n, STRDUP((char *) $1), 0 ); };

%% 

/*
 * This function is called with an error description when parsing fails.
 * Serious error diagnosis requires a lot of code (and imagination), so in the
 * interest of keeping this project on a manageable scale, we just chuck the
 * message/line number on the error stream and stop dead.
 */
int
yyerror ( const char *error )
{
    fprintf ( stderr, "\tError: %s detected at line %d with yytext: %s\n", error, yylineno, yytext );
    exit ( EXIT_FAILURE );
}
