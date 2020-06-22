#include <stdio.h>
#include "Int_DLL.h"
#include "Version_List.h"

DLL vl;
int _CompareAB(DLL *dll, int A, int B);

int InsertVersion(int parent, int i)
{
  if(i>=0)
  {
    DInsertAfterX(&vl, parent, i);
    return 0;
  }
  return 1;
}

int GetLatestVersion(int *field_versions, int n, int i)
{
  if(field_versions)
  {
    int rightmost=-1;
    for(int j=0;j<n;j++)
    {
      if(_CompareAB(&vl, *(field_versions+j), i)==0) return i;
      else if(_CompareAB(&vl, *(field_versions+j), i)==-1 && _CompareAB(&vl, *(field_versions+j), rightmost)==1)
        rightmost=*(field_versions+j);
    }
    return rightmost;
  }
  return -1;
}

void PrintVersionList()
{
  PrintDLL(&vl);
}

int _CompareAB(DLL *dll, int A, int B)
{
  DLLNode *h=dll->head;
  int first=-1, second=-1;
  while(h)
  {
    if(h->data==A)
    {
      if(first==-1) first=A;
      else second=A;
    }
    if(h->data==B)
    {
      if(first==-1) first=B;
      else second=B;
    }
    if(first>0 && second>0) break;
    h=h->next;
  }
  if(first<0 && second<0) return 2;
  else if(first==second) return 0;
  else if(second==-1)
    if(first==A) return -1;
    else /*if first==B*/ return 1;
  else
    if(first==A) return 1;
    else return -1;
  return 2;
}
