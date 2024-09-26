#ifndef VECTOR_H
#define VECTOR_H

#include "Sphere.h"

// this is the implementation of a vector, like in c++, for the purposes of the ray tracer
// this means there is limited function, as it's used to hold surfaces
// only needs to be able to add to the list structure and clean the list structure (no remove or insert)

// STRUCT (node) //////////////////////////////////////////////////////////////////
typedef struct Node {
    Node *next;
    Sphere sphere;
} Node

// STRUCT (vector) //////////////////////////////////////////////////////////////////

typedef struct Vector {
    Node *head;
    int size;
} Vector;

// FUNCTIONS ///////////////////////////////////////////////////////////////////////

// ********************************
    //NODE CREATE CAN TAKE A void *shape as an argument so that it can take in different types, just:
        //Sphere sphere = (Sphere *)shape to cast it
// ********************************

Node* node_create(Node *next, Sphere sphere) {
    Node *node = malloc(sizeof(Node));
    node.next = next;
    node.sphere = sphere;
    
    return node;
}

void node_delete(Node *node) {
    free(node);
}

void vector_add(Sphere sphere) {
    
}

void vector_clear() {

}

void vector_delete() {

}

#endif
