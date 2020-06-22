#include <stdio.h>
#include <stdlib.h>
#include "Int_DLL.h"

DLLNode *_SearchDLL(DLL *dll, int dt);
DLLNode *_DDelete(DLL *dll, int dt);

DLL *CreateDLL()
{
    DLL *d=(DLL*)malloc(sizeof(DLL));
    d->head=d->tail=NULL;
    return d;
}

void InitDLL(DLL *dll)
{
  if(dll)
  {
    dll->head=dll->tail=NULL;
  }
}

DLLNode *DCreateNode(int dt)
{
  DLLNode *node=(DLLNode*)malloc(sizeof(DLLNode));
  node->data=dt;
  node->prev=NULL;
  node->next=NULL;
  return node;
}

DLLNode *_SearchDLL(DLL *dll, int dt)
{
  if(!dll || !dll->head)  return NULL;
  DLLNode *n=dll->head;
  while(n)
  {
    if(n->data==dt) return n;
    n=n->next;
  }
  return NULL;
}

//Insert the node 'newNode' after the node 'X' in DLL if 'X' is not null.
//insert the node 'newNode' at the front of DLL, if 'X' is null
int DInsertAfterX(DLL *dll, int X, int newDt)
{
  if(!dll) return 1;

  DLLNode *xn=_SearchDLL(dll, X);
  DLLNode *newNode=DCreateNode(newDt);
  if(!dll->head)  //DLL is empty
  {
    dll->head=dll->tail=newNode;
  }
  else if(xn)
  {
    newNode->next=xn->next;
    newNode->prev=xn;
    xn->next=newNode;
    if(newNode->next) newNode->next->prev=newNode;
    if(dll->tail==xn) dll->tail=newNode;
  }
  else
  {
    newNode->next=dll->head;
    dll->head->prev=newNode;
    dll->head=newNode;
  }
  return 0;
}

int DInsertAtEnd(DLL *dll, int newDt)
{
  if(!dll) return 1;
  DLLNode *newNode=DCreateNode(newDt);
  if(newNode)
  {
    if(!dll->head)  //DLL is empty
    {
      dll->head=dll->tail=newNode;
    }
    else
    {
      newNode->next=dll->tail->next;
      newNode->prev=dll->tail;
      dll->tail->next=newNode;
      dll->tail=newNode;
    }
    return 0;
  }
  return 1;
}

//Delete all the nodes in DLL and make DLL empty.
void DMakeEmpty(DLL *dll)
{
  if(!dll) return;
  while(dll->head) _DDelete(dll, dll->head->data);
}

void PrintDLL(DLL *dll)
{
  printf("\n");
  if(dll)
  {
    DLLNode *h=dll->head;
    while(h){ printf("%d ", h->data); h=h->next; }
  }
}

int DDelete(DLL *dll, int dt)
{
  if(!dll) return 1;
  DLLNode *delNode=_DDelete(dll, dt);
  if(delNode)
  {
    delNode->next=NULL;
    delNode->prev=NULL;
    free(delNode);
    return 0;
  }
  return 1;
}

DLLNode *_DDelete(DLL *dll, int dt)
{
  if(!dll) return NULL;
  DLLNode *delNode=_SearchDLL(dll, dt);
  if(!delNode)  return NULL;
  if(delNode==dll->head && delNode==dll->tail)
  {
    dll->head=dll->tail=NULL;
  }
  else if(delNode==dll->head)
  {
    delNode->next->prev=NULL;
    dll->head=delNode->next;
  }
  else if(delNode==dll->tail)
  {
    delNode->prev->next=NULL;
    dll->tail=delNode->prev;
  }
  else
  {
    delNode->prev->next=delNode->next;
    delNode->next->prev=delNode->prev;
  }
  return delNode;
}
