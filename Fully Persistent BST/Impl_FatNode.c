#include <stdlib.h>
#include "FatNode.h"

Modbox *CreateModbox(int fname, FatNode *fval, int v)
{
  Modbox *m=ALLOC(Modbox, 1);
  m->fieldName=fname;
  m->fieldVal=fval;
  m->V=v;
  m->next=NULL;
  return m;
}

FatNode *CreateFatNode(int i, int dt)
{
  FatNode *fn=ALLOC(FatNode, 1);
  fn->data=dt;
  fn->V=i;
  fn->childCount=fn->modCount=0;
  fn->p=NULL;
  return fn;
}
