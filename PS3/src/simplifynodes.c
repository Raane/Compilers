#include "simplifynodes.h"

extern int outputStage; // This variable is located in vslc.c

Node_t* simplify_default ( Node_t *root, int depth )
{
    simplify_children(root, depth);
    //fprintf ( stderr, "Simplify %d \n", (root->nodetype) );
}


Node_t *simplify_types ( Node_t *root, int depth )
{
    if(outputStage == 4)
        fprintf ( stderr, "%*cSimplify %s \n", depth, ' ', root->nodetype.text );

}


Node_t *simplify_function ( Node_t *root, int depth )
{
    if(outputStage == 4)
        fprintf ( stderr, "%*cSimplify %s \n", depth, ' ', root->nodetype.text );
    simplify_children(root, depth);

    root->data_type = root->children[0]->data_type;
    root->label = root->children[1]->label;
    //free(root->children[0]);
    //free(root->children[1]);
    Node_t** newChildren = malloc((root->n_children-2) * sizeof(Node_t));
    int i=0;
    for(i=0;i<(root->n_children-2);i++) {
        newChildren[i] = root->children[i+2];
    }
    free(root->children);
    root->children = newChildren;
    root->n_children = root->n_children-2;
}


Node_t *simplify_class( Node_t *root, int depth )
{
    if(outputStage == 4)
        fprintf ( stderr, "%*cSimplify %s \n", depth, ' ', root->nodetype.text );
    simplify_children(root, depth);
}


Node_t *simplify_declaration_statement ( Node_t *root, int depth )
{
    if(outputStage == 4)
        fprintf ( stderr, "%*cSimplify %s \n", depth, ' ', root->nodetype.text );
    simplify_children(root, depth);

}


Node_t *simplify_single_child ( Node_t *root, int depth )
{
    if(outputStage == 4)
        fprintf ( stderr, "%*cSimplify %s \n", depth, ' ', root->nodetype.text );
    simplify_children(root, depth);

    //Node_t* child = root->children[0];
    //free(root);
    //TODO: Free stuff
    *root = *(root->children[0]);

}

Node_t *simplify_list_with_null ( Node_t *root, int depth )
{
    // here we can't look at all children, as some of them may be null
    if(outputStage == 4)
        fprintf ( stderr, "%*cSimplify %s \n", depth, ' ', root->nodetype.text );
    simplify_children(root, depth);

    Node_t* nonNullChild = root->children[1];
    free(root->children);
    root->children = malloc(sizeof(Node_t));
    root->children[0] = nonNullChild;

}


Node_t *simplify_list ( Node_t *root, int depth )
{
    if(outputStage == 4)
        fprintf ( stderr, "%*cSimplify %s \n", depth, ' ', root->nodetype.text );
    simplify_children(root, depth);

}


Node_t *simplify_expression ( Node_t *root, int depth )
{
    if(outputStage == 4)
        fprintf ( stderr, "%*cSimplify %s (%s) \n", depth, ' ', root->nodetype.text, root->expression_type.text );
    simplify_children(root, depth);
    *root = *(root->children[0]);

}

void simplify_children(Node_t *root, int depth) {
    int i;
    for(i=0;i<root->n_children;i++) {
        if(root->children[i]!=NULL) {
    //        fprintf ( stderr, "Simplify %d \n", (root->children[i]->nodetype) );
            root->children[i]->simplify(root->children[i], depth+1);
        }
    }
}
