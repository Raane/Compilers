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
program             : function_list                                     { root = CN( program_n, 1, $1 ); }
                    | class_list function_list                          { root = CN( program_n, 2, $1, $2 ); };
function            : type FUNC variable '(' parameter_list ')' START statement_list END    { $$ = CN( function_n, 3, $2, $4, $6 ); };    //TODO
function_list       : function_list function                            { $$ = CN( function_list_n, 2, $1, $2 ); }
                    | ;                                                                                                                         //TODO
statement_list      : statement                                         { $$ = CN( statement_list_n, 1, $1 ); }
                    | statement_list statement                          { $$ = CN( statement_list_n, 2, $1, $2 ); };
variable_list       : declaration_statement                             { root = CN( program_n, , ); }                                                                        //TODO
                    | variable_list ',' declaration_statement                                                                                   //TODO
                    | variable_list ',' INDEXED_variable                { $$ = CN( variable_list_n, 2, $1, $3 ); };*/
expression_list     : expression                                        { $$ = CN( expression_list_n, 1, $1 ); }
                    | expression_list ',' expression                    { $$ = CN( expression_list_n, 2, $1, $3 ); };
parameter_list      : variable_list                                     { node_init ( $$ = malloc(sizeof(node_t)), parameter_list_n, NULL, 1, $1 ); }               //TODO
                    |                                                   { node_init ( $$ = NULL, parameter_list_n, NULL, 0 ); };
argument_list       : expression_list                                   { node_init ( $$ = malloc(sizeof(node_t)), argument_list_n, NULL, 1, $1 ); }
                    |                                                   { $$ = NULL; };
class_list          : class                                                                                                                     //TODO
                    | class_list class                                                                                                          //TODO
class               : _CLASS_ variable HAS declaration_list WITH function_list END                                                                //TODO
declaration_list    : declaration_list declaration_statement ','        { node_init ( $$ = malloc(sizeof(node_t)), declaration_list_n, 2, $1/*, $2*/ ); }
                    |                                                   { node_init ( $$ = NULL, declaration_list_n, NULL, 0 ); };
statement           : declaration_statement ','                         { $$ = CN( statement_n, 1, $1 ); }*/
                    | assignment_statement ','                          { $$ = CN( statement_n, 1, $1 ); }
                    | if_statement ','                                  { $$ = CN( statement_n, 1, $1 ); }
                    | while_statement ','                               { $$ = CN( statement_n, 1, $1 ); }
                    | print_statement ','                               { $$ = CN( statement_n, 1, $1 ); }
                    | return_statement ','                              { $$ = CN( statement_n, 1, $1 ); }
                    | call ';'                                          { $$ = CN( statement_n, 1, $1 ); };
declaration_statement : type variable                                                                                                           //TODO
assignment_statement: variable ASSIGN expression                        { $$ = CN( assignment_statement_n, 2, $1, $3 ); };                //TODO?
if_statement        : IF expression THEN statement_list ELSE statement END   { $$ = CN( if_statement_n, 3, $2, $4, $6 ); }                //TODO?
                    | IF expression THEN statement_list END                  { $$ = CN( if_statement_n, 2, $2, $4 ); };                   //TODO?
while_statement     : WHILE expression DO STATEMENTi_LIST END                 { $$ = CN( while_statement_n, 2, $2, $4 ); };
return_statement    : RETURN expression
print_statement     : PRINT expression_list                             { $$ = CN( print_statement_n, 1, $2 ); };
expression          : constant                                                                                                                  //TODO
                    | expression '+' expression                         { $$ = CN( expression_n, STRDUP("+"), 2, $1, $3 ); }
                    | expression '-' expression                         { $$ = CN( expression_n, STRDUP("-"), 2, $1, $3 ); }
                    | expression '*' expression                         { $$ = CN( expression_n, STRDUP("*"), 2, $1, $3 ); }
                    | expression '/' expression                         { $$ = CN( expression_n, STRDUP("/"), 2, $1, $3 ); }
                    | expression '>' expression                         { $$ = CN( expression_n, STRDUP("/"), 2, $1, $3 ); }
                    | expression '<' expression                         { $$ = CN( expression_n, STRDUP("/"), 2, $1, $3 ); }
                    | expression '==' expression                         { $$ = CN( expression_n, STRDUP("/"), 2, $1, $3 ); }
                    | expression '!=' expression                         { $$ = CN( expression_n, STRDUP("/"), 2, $1, $3 ); }
                    | expression '>=' expression                         { $$ = CN( expression_n, STRDUP("/"), 2, $1, $3 ); }
                    | expression '<=' expression                         { $$ = CN( expression_n, STRDUP("/"), 2, $1, $3 ); }
                    | expression '&&' expression                         { $$ = CN( expression_n, STRDUP("/"), 2, $1, $3 ); }
                    | expression '||' expression                         { $$ = CN( expression_n, STRDUP("/"), 2, $1, $3 ); }
                    | '-' expression                                    { $$ = CN( expression_n, STRDUP("-"), 1, $2 ); }                                     //TODO?
                    | '!' expression                                    { $$ = CN( expression_n, STRDUP("-"), 1, $2 ); }                                     //TODO?
                    | '(' expression ')'                                { $$ = CN( expression_n, NULL, 1, $2 ); }
                    | call
                    | THIS
                    | lvalue
                    | NEW type  ;
call                : variable '(' argument_list ')'                    { $$ = CN( expression_n, STRDUP("F"), 2, $1, $3 ); }                    //TODO
                    | expression '.' variable '(' argument_list ')'     { $$ = CN( expression_n, STRDUP("A"), 2, $1, $3 ); };*/                 //TODO
lvalue              : variable                                                                                                                  //TODO
                    | expression '.' variable                                                                                                   //TODO
constant            : TRUE_CONST                                                                                                                //TODO
                    | FALSE_CONST                                                                                                               //TODO
                    | INT_CONST                                                                                                                 //TODO
                    | FLOAT_CONST                                                                                                               //TODO
                    | STRING_CONST                                                                                                              //TODO
type                : INT
                    | FLOAT
                    | BOOL
                    | VOID
                    | variable
variable            : IDENTIFIER

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
