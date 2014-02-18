#include "bindnames.h"
extern int outputStage; // This variable is located in vslc.c
char* thisClass;

/*
 * The default for a node that doesn't require any special actions is to call all their childrens bind_names functions.
 */
int bind_default ( node_t *root, int stackOffset)
{
    int i;
    for(i=0;i<root->n_children;i++) {
        if(root->children[i]!=NULL) {
            root->children[i]->bind_names(root->children[i], stackOffset+1);
        }
    }
    return 0;
}

/*
 * After printing CONSTANT to stderr for tesing purposes, the constants type is checked.
 * If it is a string, this string will be sent to symtab for storage in the data segment
 * of the finished asembly code.
 */
int bind_constant ( node_t *root, int stackOffset)
{
    if(outputStage == 6)
        fprintf ( stderr, "CONSTANT\n" );
    int i;
    for(i=0;i<root->n_children;i++) {
        if(root->children[i]!=NULL) {
            root->children[i]->bind_names(root->children[i], stackOffset+1);
        }
    }
    if(root->data_type.base_type == STRING_TYPE) {
        strings_add(root->string_const);
    }
    return 0;
}


