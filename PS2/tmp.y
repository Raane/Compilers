program             : function_list                                     { root = CN( program_n, 1, $1 ); }
                    | class_list function_list                          { root = CN( program_n, 2, $1, $2 ); };
function            : type FUNC variable '(' parameter_list ')' START statement_list END    { $$ = CN( function_n, NULL, 3, $2, $4, $6 ); };    //TODO
function_list       : function_list function                            { $$ = CN( function_list_n, NULL, 2, $1, $2 ); }
                    | ;                                                                                                                         //TODO
statement_list      : statement                                         { $$ = CN( statement_list_n, NULL, 1, $1 ); }
                    | statement_list statement                          { $$ = CN( statement_list_n, NULL, 2, $1, $2 ); };
variable_list       : declaration_statement                                                                                                     //TODO
                    | variable_list ',' declaration_statement                                                                                   //TODO
                    /*variable                                          { $$ = CN( variable_list_n, NULL, 1, $1 ); }
                    | INDEXED_variable                                  { $$ = CN( variable_list_n, NULL, 1, $1 ); }
                    | variable_list ',' variable                        { $$ = CN( variable_list_n, NULL, 2, $1, $3 ); }
                    | variable_list ',' INDEXED_variable                { $$ = CN( variable_list_n, NULL, 2, $1, $3 ); };*/
expression_list     : expression                                        { $$ = CN( expression_list_n, NULL, 1, $1 ); }
                    | expression_list ',' expression                    { $$ = CN( expression_list_n, NULL, 2, $1, $3 ); };
parameter_list      : variable_list                                     { node_init ( $$ = malloc(sizeof(node_t)), parameter_list_n, NULL, 1, $1 ); }               //TODO
                    |                                                   { node_init ( $$ = NULL, parameter_list_n, NULL, 0 ); };
argument_list       : expression_list                                   { node_init ( $$ = malloc(sizeof(node_t)), argument_list_n, NULL, 1, $1 ); }
                    |                                                   { $$ = NULL; };
class_list          : class                                                                                                                     //TODO
                    | class_list class                                                                                                          //TODO
class               : _CLASS_ variable HAS declaration_list WITH function_list END                                                                //TODO
declaration_list    : declaration_list declaration_statement ','        { node_init ( $$ = malloc(sizeof(node_t)), declaration_list_n, NULL, 2, $1/*, $2*/ ); }
                    |                                                   { node_init ( $$ = NULL, declaration_list_n, NULL, 0 ); };
statement           : declaration_statement ','                         { $$ = CN( statement_n, NULL, 1, $1 ); }*/
                    | assignment_statement ','                          { $$ = CN( statement_n, NULL, 1, $1 ); }
                    | if_statement ','                                  { $$ = CN( statement_n, NULL, 1, $1 ); }
                    | while_statement ','                               { $$ = CN( statement_n, NULL, 1, $1 ); }
                    | print_statement ','                               { $$ = CN( statement_n, NULL, 1, $1 ); }
                    | return_statement ','                              { $$ = CN( statement_n, NULL, 1, $1 ); }
                    | call ';'                                          { $$ = CN( statement_n, NULL, 1, $1 ); };
declaration_statement : type variable                                                                                                           //TODO
assignment_statement: variable ASSIGN expression                        { $$ = CN( assignment_statement_n, NULL, 2, $1, $3 ); };                //TODO?
if_statement        : IF expression THEN statement_list ELSE statement END   { $$ = CN( if_statement_n, NULL, 3, $2, $4, $6 ); }                //TODO?
                    | IF expression THEN statement_list END                  { $$ = CN( if_statement_n, NULL, 2, $2, $4 ); };                   //TODO?
while_statement     : WHILE expression DO STATEMENTi_LIST END                 { $$ = CN( while_statement_n, NULL, 2, $2, $4 ); };
return_statement    : RETURN expression
print_statement     : PRINT expression_list                             { $$ = CN( print_statement_n, NULL, 1, $2 ); };
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
                    /*| INTEGER                                         { $$ = CN( expression_n, NULL, 1, $1 ); }
                    | variable                                          { $$ = CN( expression_n, NULL, 1, $1 ); }
                    | variable '(' argument_list ')'                    { $$ = CN( expression_n, STRDUP("F"), 2, $1, $3 ); }
                    | variable '[' expression ']'                       { $$ = CN( expression_n, STRDUP("A"), 2, $1, $3 ); };*/
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





/*PRINT_LIST          : PRINT_ITEM                                        { $$ = CN( print_list_n, NULL, 1, $1 ); }
                    | PRINT_LIST ',' PRINT_ITEM                         { $$ = CN( print_list_n, NULL, 2, $1, $3 ); };
DECLARATION_LIST    : DECLARATION_LIST /*DECLARATION*/                  { node_init ( $$ = malloc(sizeof(node_t)), declaration_list_n, NULL, 2, $1, $2 ); }
                    |                                                   { node_init ( $$ = NULL, declaration_list_n, NULL, 0 ); };
BLOCK               : '{' DECLARATION_LIST STATEMENT_LIST '}'           { $$ = CN( block_n, NULL, 2, $2, $3 ); };
RETURN_statement    : RETURN EXPRESSION                                 { $$ = CN( return_statement_n, NULL, 1, $2 ); };
DECLARATION         : VAR VARIABLE_LIST                               { $$ = CN( declaration_n, NULL, 1, $2 ); };
variable            : IDENTIFIER                                        { $$ = CN( variable_n, STRDUP((char *) $1), 0 ); };
INDEXED_variable    : variable /*'[' INTEGER ']'*/                      { $$ = CN( variable_n, NULL, 2, $1, $3 ); };
PRINT_ITEM          : EXPRESSION                                        { $$ = CN( print_item_n, NULL, 1, $1 ); }
;/*                    | TEXT                                           { $$ = CN( print_item_n, NULL, 1, $1 ); };

