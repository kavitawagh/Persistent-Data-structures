//To implement version list
#ifndef _INT_DLL_H
#define _INT_DLL_H

typedef struct DLLNode
{
  struct DLLNode *prev, *next;
  int data;
}DLLNode;

typedef struct DLL
{
  struct DLLNode *head, *tail;
}DLL;

DLL *CreateDLL();
void InitDLL(DLL *dll);
DLLNode *DCreateNode(int dt);
int DInsertAfterX(DLL *dll, int X, int newDt);
int DInsertAtEnd(DLL *dll, int newDt);
void DMakeEmpty(DLL *dll);
int DDelete(DLL *dll, int dt);
int SearchDLL(DLL *dll, int dt);
void PrintDLL(DLL *dll);

#endif
