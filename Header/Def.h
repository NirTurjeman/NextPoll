#ifndef _DEF_
#define _DEF_

// new type
typedef void* DATA; 

// Node
typedef struct node
{
    DATA            key;
    struct node*    next;
}NODE;

#endif
