#include "bindnames.h"
extern int outputStage; // This variable is located in vslc.c
char* thisClass;

int b_d(node_t* root, int stack_offset);
int b_c(node_t* root, int stack_offset);

int bind_default ( node_t *root, int stackOffset)
{
    return b_d(root,stackOffset);
}


int bind_function ( node_t *root, int stackOffset)
{

    if(outputStage == 6)
        fprintf ( stderr, "FUNCTION: Start: %s\n", root->label);

    int i;
    for(i=0;i<root->n_children;i++) {
        if(root->children[i] != NULL) {
            root->children[i]->bind_names(root->children[i], stackOffset);
        }
    }

    if(outputStage == 6)
        fprintf ( stderr, "FUNCTION: End\n");

}

int bind_declaration_list ( node_t *root, int stackOffset)
{
    if(outputStage == 6)
        fprintf ( stderr, "DECLARATION_LIST: Start\n");

    int i;
    for(i=0;i<root->n_children;i++) {
        if(root->children[i] != NULL) {
            root->children[i]->bind_names(root->children[i], stackOffset);
        }
    }


    if(outputStage == 6)
        fprintf ( stderr, "DECLARATION_LIST: End\n");

}

int bind_class ( node_t *root, int stackOffset)
{
    if(outputStage == 6)
        fprintf(stderr, "CLASS: Start: %s\n", root->children[0]->label);

    int i;
    for(i=0;i<root->n_children;i++) {
        if(root->children[i] != NULL) {
            root->children[i]->bind_names(root->children[i], stackOffset);
        }
    }


    if(outputStage == 6)
        fprintf(stderr, "CLASS: End\n");

}

function_symbol_t* create_function_symbol(node_t* function_node)
{

}

int bind_function_list ( node_t *root, int stackOffset)
{
    if(outputStage == 6)
        fprintf ( stderr, "FUNCTION_LIST: Start\n");

    int i;
    for(i=0;i<root->n_children;i++) {
        if(root->children[i] != NULL) {
            root->children[i]->bind_names(root->children[i], stackOffset);
        }
    }


    if(outputStage == 6)
        fprintf ( stderr, "FUNCTION_LIST: End\n");

}

int bind_constant ( node_t *root, int stackOffset)
{
    return b_c(root, stackOffset);
}


symbol_t* create_symbol(node_t* declaration_node, int stackOffset)
{

}

int bind_declaration ( node_t *root, int stackOffset)
{

    if(outputStage == 6)
        fprintf(stderr, "DECLARATION: parameter/variable : '%s', offset: %d\n", root->label, stackOffset);

}

int bind_variable ( node_t *root, int stackOffset)
{
    if(outputStage == 6)
        fprintf ( stderr, "VARIABLE: access: %s\n", root->label);

}

int bind_expression( node_t* root, int stackOffset)
{
    if(outputStage == 6)
        fprintf( stderr, "EXPRESSION: Start: %s\n", root->expression_type.text);

    int i;
    for(i=0;i<root->n_children;i++) {
        if(root->children[i] != NULL) {
            root->children[i]->bind_names(root->children[i], stackOffset);
        }
    }


    if(outputStage == 6)
        fprintf( stderr, "EXPRESSION: End\n");

}

