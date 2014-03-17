#include "typecheck.h"
extern int outputStage;

data_type_t td(node_t* root);
data_type_t te(node_t* root);
data_type_t tv(node_t* root);

void type_error(node_t* root){
    fprintf(stderr, "Type error at:\n");
    if(root != NULL){
        fprintf(stderr,"%s", root->nodetype.text);
        if(root->nodetype.index == EXPRESSION){
            fprintf(stderr," (%s)", root->expression_type.text);
        }
        fprintf(stderr,"\n");
    }
    fprintf(stderr,"Exiting\n");
    exit(-1);
}

int equal_types(data_type_t a, data_type_t b)
{
    return a.base_type == b.base_type;
}

data_type_t typecheck_default(node_t* root)
{
    return td(root);
}

data_type_t typecheck_expression(node_t* root)
{
    data_type_t toReturn;

    if(outputStage == 10)
        fprintf( stderr, "Type checking expression %s\n", root->expression_type.text);

    toReturn = te(root);

    if(root->expression_type.index == FUNC_CALL_E || root->expression_type.index == METH_CALL_E) {
        function_symbol_t *function_symbol = function_get(root->children[0]->label);
                /*
                 * The if clause check that the number of arguments match the number in the call.
                 * In the else clause the arguments types are checked against the symbol table entry.
                 */
        if((root->children[1] == NULL && function_symbol->nArguments != 0) ||
                (root->children[1] != NULL && root->children[1]->n_children != function_symbol->nArguments )) {
            type_error(root);
        } else {
            int i;
            for(i=0;i<function_symbol->nArguments;i++) {
                if(!equal_types(root->children[1]->children[i]->typecheck(root->children[1]->children[i]), function_symbol->argument_types[i])) {
                    type_error(root);
                }
            }
        }
        toReturn = function_symbol->return_type;
    }
    return toReturn;
}

data_type_t typecheck_variable(node_t* root){
    return tv(root);
}

data_type_t typecheck_assignment(node_t* root)
{
    data_type_t type_left = root->children[0]->typecheck(root->children[0]);
    data_type_t type_right = root->children[1]->typecheck(root->children[1]);
    if(!equal_types(type_left, type_right)) {
        type_error(root);
    }
    return type_left;
}
