#include <stdio.h>
#include <stdlib.h>
#include "Version_List.h"
#include "FatNode.h"
#include "Trie.h"

FatNode *_GetLeafNode(int i, FatNode *fn);

int InitTrie(Trie *T)
{
  if(!T) return 1;
  T->latestV=0;
  T->root[0]=NULL;
  InsertVersion(-1, 0);
  return 0;
}

int InsertNode_Trie(Trie *T, int parentV, int dt)
{
  int childV=T->latestV+1;
  FatNode *child=CreateFatNode(childV, dt);
  if(T->latestV==0)
  {
    T->latestV=1;
    T->root[1]=child;
    InsertVersion(0, 1);
    return T->latestV;
  }
  FatNode *parent=_GetLeafNode(parentV, T->root[parentV]);
  child->p=parent;
  if(parent->modCount==0)
  {
    parent->childMods=CreateModbox(parent->childCount, child, childV);
    parent->childCount++;
    parent->modCount++;
  }
  else if(parent->modCount==1)
  {
    if(parent->childMods->V==childV) parent->childMods->fieldVal=child;
    else
    {
      parent->childMods->next=CreateModbox(parent->childCount, child, childV);
      parent->childCount++;
      parent->modCount++;
    }
  }
  else
  {
    Modbox *m=parent->childMods;
    while(m->next)
    {
      if(m->V==childV) { m->fieldVal=child; break; } m=m->next;
    }
    if(!m->next)
    {
      if(m->V==childV) { m->fieldVal=child; }
      else
      {
        m->next=CreateModbox(parent->childCount, child, childV);
        parent->childCount++;
        parent->modCount++;
      }
    }
  }
  InsertVersion(parentV, childV);
  T->latestV=childV;
  T->root[T->latestV]=T->root[T->latestV-1];
  return T->latestV;
}

int getPath(Trie *T, int i, int *p)
{
  FatNode *l=_GetLeafNode(i, T->root[i]);
  int temp[i]; int j=0;
  while(l){ printf("%d ", l->data); temp[j++]=l->data; l=l->p; }
  i=0;
  while(i<j) p[i]=temp[j-i-1];
  return j;
}

FatNode *_GetLeafNode(int i, FatNode *fn)
{
  if(fn)
  {
    if(fn->modCount==0) return fn;

    int versions[fn->modCount];
    Modbox *m=fn->childMods;
    int k=0;
    while(m)
    {
      versions[k++]=m->V;
      m=m->next;
    }
    int v=GetLatestVersion(versions, k, i);
    if(v==-1) return fn;
    m=fn->childMods;
    while(m)
    {
      if(m->V==v)
        if(!m->fieldVal) return fn;
        else return _GetLeafNode(i, m->fieldVal);
      m=m->next;
    }
  }
}
