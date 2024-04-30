#include <stdio.h>
#include <stdlib.h>
#include "List.h"

BOOL L_init(LIST* pList)
{
    if ( pList == NULL )
        return False;    // no list to initialize

    pList->head.next = NULL;
    return True;
}
NODE* L_insert(NODE* pNode, DATA Value)
{
    NODE* tmp;

    if ( !pNode )
        return NULL;

    tmp = (NODE*)malloc(sizeof(NODE));    // new node
    
    if ( tmp != NULL )  {
        tmp->key = Value;
        tmp->next = pNode->next;
        pNode->next = tmp;
    }
    return tmp;
}
BOOL L_delete(NODE* pNode , void (*freeKey)(void*))
{
    NODE* tmp;
    if (!pNode)
        return False;
    tmp = pNode->next;
    if(!tmp)
        return False;
    
    pNode->next = tmp->next;
    if (freeKey) {
        freeKey(tmp->key);
    }
    free(tmp);
    return True;
}
const NODE* L_find(const NODE* pNode, DATA Value,int (*compare)(const void*,const void*))
{
    while (pNode != NULL)
    {
        if (compare(pNode->key,Value)==0)
            return pNode;
        pNode = pNode->next;
    }
    return NULL;
}
BOOL L_free(LIST* pList,void (*freeKey)(void*))
{
    NODE *tmp;
    if ( !pList )
        return False;

    for (tmp = &(pList->head); L_delete(tmp, freeKey););
    return True;
}
int L_print(const LIST* pList,void(*print)(const void*))
{
    NODE    *tmp;
    int        c = 0;

    if ( !pList )
        return False;

    printf("\n");
    tmp = pList->head.next;
    while(tmp != NULL)
    {
        print(tmp->key);
        c++;
        tmp = tmp->next;
    }
    printf("\n");
    return c;
}
