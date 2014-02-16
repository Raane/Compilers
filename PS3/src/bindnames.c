#include "bindnames.h"
extern int outputStage; // This variable is located in vslc.c
char* thisClass;

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

int bind_constant ( node_t *root, int stackOffset)
{
    int i;
    for(i=0;i<root->n_children;i++) {
        if(root->children[i]!=NULL) {
            root->children[i]->bind_names(root->children[i], stackOffset+1);
        }
    }
    if(outputStage == 6)
        fprintf ( stderr, "CONSTANT\n" );
    if(root->data_type.base_type == STRING_TYPE) {
        strings_add(root->string_const);
    }
    return 0;
}


