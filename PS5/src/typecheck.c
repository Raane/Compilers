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
        int i;
        for(i=0;i<function_symbol.nArguments;i++) {
            /* 
             * Note that there is no need to check for root->children[1] != NULL here as 
             * NULL would only occur when function_symbol.nArguments is 0.
             */
            if(root->children[1]->children[i]->typecheck(root->children[1]->children[i]) != function_symbol.argument_types[i]) {
                type_error(root);
            }
        }


    }

    //Insert additional checking here

}

data_type_t typecheck_variable(node_t* root){
    return tv(root);
}

data_type_t typecheck_assignment(node_t* root)
{

}
