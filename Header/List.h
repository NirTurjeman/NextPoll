//
//  List.h
//  finalProject
//
//  Created by NirTurjeman on 01/04/2024.
//

#ifndef List_h
#define List_h

#include <stdio.h>
#include "Def.h"
typedef enum {False, True} BOOL;    // a boolean type
typedef struct
{
    NODE head;
}LIST;

//--Functions--//
BOOL        L_init(LIST* pList);// create new list
NODE*       L_insert(NODE* pNode, DATA Value);// add new node after *pNode
BOOL        L_delete(NODE* pNode , void (*freeKey)(void*));// erase node after *pNode
const NODE* L_find(const NODE* pNode, DATA Value,int (*compare)(const void*,const void*));// return a pointer to the node
BOOL     L_free(LIST* pList,void (*freeKey)(void*));// free list memory
int         L_print(const LIST* pList,void(*print)(const void*));// print the list content
#endif /* List_h */
