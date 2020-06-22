#ifndef _FATNODE_H
#define _FATNODE_H
#define MAXV 100 //Maximum versions (limit of acces poiter array)
#define MAXCHILD 10 //Maximum children of a node in Trie
#define ALLOC(X, Y) (X*)malloc((Y)*sizeof(X))

typedef struct Modbox
{
  int fieldName;
  struct FatNode *fieldVal;
  int V;   //version stamp
  struct Modbox *next;
}Modbox;

typedef struct FatNode
{
    int data, V, childCount,modCount;
    Modbox *childMods;
    struct FatNode *p;
}FatNode;

Modbox *CreateModbox(int fname, FatNode *fval, int v);
FatNode *CreateFatNode(int i, int dt);

#endif
