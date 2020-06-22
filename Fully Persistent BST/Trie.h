#ifndef _TRIE_H
#define _TRIE_H

#include "FatNode.h"

typedef struct Trie
{
  FatNode *root[MAXV];
  int latestV; //Latest version of Trie;
}Trie;

int InitTrie(Trie *T);
int InsertNode_Trie(Trie *T, int parentV, int dt);
int getPath(Trie *T, int i, int *p);

#endif
