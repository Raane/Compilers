#include "simplifynodes.h"

extern int outputStage; // This variable is located in vslc.c
void simplify_children( Node_t *root, int depth );

Node_t* simplify_default ( Node_t *root, int depth )
{
    simplify_children(root, depth);
}


Node_t *simplify_types ( Node_t *root, int depth )
{
    if(outputStage == 4)
        fprintf ( stderr, "%*cSimplify %s \n", depth, ' ', root->nodetype.text );
    if(root->data_type.base_type == CLASS_TYPE) {
        root->data_type.class_name = root->children[0]->label;
        free(root->children[0]);
        Node_t** newChildren = malloc((root->n_children-1) * sizeof(Node_t));
        int i=0;
        for(i=0;i<(root->n_children-1);i++) {
            newChildren[i] = root->children[i+1];
        }
        free(root->children);
        root->children = newChildren;
        root->n_children = root->n_children-1;
    }
}


Node_t *simplify_function ( Node_t *root, int depth )
{
    if(outputStage == 4)
        fprintf ( stderr, "%*cSimplify %s \n", depth, ' ', root->nodetype.text );
    simplify_children(root, depth);

    root->data_type = root->children[0]->data_type;
    root->label = root->children[1]->label;
    free(root->children[0]);
    free(root->children[1]);
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

    root->label = root->children[0]->label;
    free(root->children[0]);
    Node_t** newChildren = malloc((root->n_children-1) * sizeof(Node_t));
    int i=0;
    for(i=0;i<(root->n_children-1);i++) {
        newChildren[i] = root->children[i+1];
    }
    free(root->children);
    root->children = newChildren;
    root->n_children = root->n_children-1;
}


Node_t *simplify_declaration_statement ( Node_t *root, int depth )
{
    if(outputStage == 4)
        fprintf ( stderr, "%*cSimplify %s \n", depth, ' ', root->nodetype.text );
    simplify_children(root, depth);

    //TODO: This is copy pasted, could be hard coded more, as this is just ripped from function
    root->data_type = root->children[0]->data_type;
    root->label = root->children[1]->label;
    free(root->children[0]);
    free(root->children[1]);
    Node_t** newChildren = malloc((root->n_children-2) * sizeof(Node_t));
    int i=0;
    for(i=0;i<(root->n_children-2);i++) {
        newChildren[i] = root->children[i+2];
    }
    free(root->children);
    root->children = newChildren;
    root->n_children = root->n_children-2;
}


Node_t *simplify_single_child ( Node_t *root, int depth )
{
    if(outputStage == 4)
        fprintf ( stderr, "%*cSimplify %s \n", depth, ' ', root->nodetype.text );
    simplify_children(root, depth);

    Node_t* child = root->children[0];
    free(root->children);
    *root = *child;

}

Node_t *simplify_list_with_null ( Node_t *root, int depth )
{
    // here we can't look at all children, as some of them may be null
    if(outputStage == 4)
        fprintf ( stderr, "%*cSimplify %s \n", depth, ' ', root->nodetype.text );
    simplify_children(root, depth);
    
    if(root->children[0]==NULL) {
        Node_t* nonNullChild = root->children[1];
        free(root->children);
        root->children = malloc(sizeof(Node_t));
        root->children[0] = nonNullChild;
        root->n_children = root->n_children-1;
    } else if(root->children[0]->nodetype.index==root->nodetype.index) {
        Node_t** newChildren = malloc((root->children[0]->n_children+1) * sizeof(Node_t));
        int i=0;
        for(i=0;i<(root->children[0]->n_children+1);i++) {
            newChildren[i] = root->children[0]->children[i];
        }
        newChildren[root->children[0]->n_children] = root->children[1];
        root->n_children = root->children[0]->n_children+1;
        free(root->children);
        root->children = newChildren;
    }
}


Node_t *simplify_list ( Node_t *root, int depth )
{
    if(outputStage == 4)
        fprintf ( stderr, "%*cSimplify %s \n", depth, ' ', root->nodetype.text );
    simplify_children(root, depth);
    if(root->n_children==2) {
        Node_t** newChildren = malloc((root->children[0]->n_children+1) * sizeof(Node_t));
        int i=0;
        for(i=0;i<(root->children[0]->n_children+1);i++) {
            newChildren[i] = root->children[0]->children[i];
        }
        newChildren[root->children[0]->n_children] = root->children[1];
        root->n_children = root->children[0]->n_children+1;
        free(root->children);
        root->children = newChildren;
    }
}

Node_t *simplify_expression ( Node_t *root, int depth )
{
    if(outputStage == 4)
        fprintf ( stderr, "%*cSimplify %s (%s) \n", depth, ' ', root->nodetype.text, root->expression_type.text );
    simplify_children(root, depth);
    if(root->expression_type.index==DEFAULT_E || root->expression_type.index==CONSTANT_E || root->expression_type.index==VARIABLE_E) {
        *root = *(root->children[0]);
    }

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
