#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "Trie.h"
#define INP_MAX_LEN 50

typedef struct ThreadArg{ int st, vr; char *c; int tn;}ThreadArg; //To pass parameters to thread

//Arrays to store NFA transitions
int *curState, *nextState, *finalState; char *inpSymbol;

//
int n, tcount /*thread count, changes as threads are created or died*/;
int tnmax /*Max thread number generated*/, path[INP_MAX_LEN]; /*Store root to child path for accepted string*/

//for thread synchronization
pthread_mutex_t lock=PTHREAD_MUTEX_INITIALIZER, lock2=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond=PTHREAD_COND_INITIALIZER;

char w[INP_MAX_LEN];  //input string
Trie tr;

void ProcessInput();
void *ThreadWork(void *ptr);

int main()
{
  printf("\nEnter total no. of transitions in NFA:"); scanf("%d", &n);
  curState=ALLOC(int, n);
  nextState=ALLOC(int, n);
  inpSymbol=ALLOC(char, n);
  printf("\nEnter NFA transitions (Initial state is 0):\n");
  int totStates=0;
  for(int i=0;i<n;i++)
  {
    scanf("%d %c %d", &curState[i], &inpSymbol[i], &nextState[i]);

    //get total no. of states
    if(curState[i]>totStates) totStates=curState[i];
    if(nextState[i]>totStates) totStates=nextState[i];
  }
  totStates++;
  finalState=ALLOC(int, totStates);
  int s;
  printf("\nEnter total no. of final states:"); scanf("%d", &s);
  for(int i=0;i<totStates;i++) finalState[i]=0;
  printf("\nEnter final states:");
  int k; char ch;
  for(int i=0;i<s;i++) {  scanf("%d", &k); finalState[k]=1;   }
  do
  {
    printf("\nEnter input string: "); scanf("%s", w);
    ProcessInput();
    printf("\nQuit (y/n)? "); scanf("%c", &ch); scanf("%c", &ch);
  }while(ch!='y');
  printf("\n");
  return 0;
}

void ProcessInput()
{
  pthread_t tid;
  ThreadArg arg;
  arg.st=0; arg.c=w; arg.tn=1;
  InitTrie(&tr);
  arg.vr=InsertNode_Trie(&tr, -1, arg.st); tcount=tnmax=1;
  pthread_create(&tid, NULL, ThreadWork, (void*)&arg);
  printf("\nThread: %d, Current State: %d, Unprocessed Input: %s (Thread created)", arg.vr, arg.st, arg.c);
  pthread_cond_wait(&cond, &lock2);
}

void *ThreadWork(void *ptr)
{
  //Extract thread parameters
  int vr=((ThreadArg*)ptr)->vr, st=((ThreadArg*)ptr)->st, tn=((ThreadArg*)ptr)->tn;
  char *c=((ThreadArg*)ptr)->c;
  do
  {
    //if finished reading the input string then
    if(*c=='\0')
    {
      //If thread is in one of the accepting states
      if(finalState[st])
      {
        //int pLen=getPath(&tr, vr, path);
        printf("\nThread: %d, Current State: %d, (Accepted)", tn, st);
        //printf("\nAcceptence Path: ");// for(int l=0;l<pLen;l++) printf(" - %d", path[l]);
      }
      else printf("\nThread: %d, Current State: %d, Unprocessed Input: %s (Thread died)", tn, st, c);
      pthread_mutex_lock(&lock2);
      tcount--;
      if(tcount==0) pthread_cond_signal(&cond);
      pthread_mutex_unlock(&lock2);
      pthread_exit(&vr);
    }

    int k=-1; int i;
    for(i=0; i<n; i++)
    {
      if(curState[i]==st && inpSymbol[i]==(*c) && k==-1) k=i;
      if(k>=0 && (curState[i]!=st || inpSymbol[i]!=(*c))) break;
    }

    if(k==-1)
    {
      pthread_mutex_lock(&lock2);
      tcount--;
      if(tcount==0) pthread_cond_signal(&cond);
      pthread_mutex_unlock(&lock2);
      printf("\nThread: %d, Current State: %d, Unprocessed Input: %s (Thread died)", tn, st, c);
      pthread_exit(&vr);
    }
    else
    {
      printf("\nThread: %d, Current State: %d, Unprocessed Input: %s", tn, st, c);
      st=nextState[k];
      pthread_mutex_lock(&lock);
      ((ThreadArg*)ptr)->vr=InsertNode_Trie(&tr, vr, st);
      pthread_mutex_unlock(&lock);
      c++;
      for(int j=k+1;j<i;j++)
      {
        ThreadArg arg;
        pthread_mutex_lock(&lock);

        tnmax++;
        arg.vr=InsertNode_Trie(&tr, vr, nextState[j]);
        arg.st=nextState[j]; arg.c=c; arg.tn=tnmax;
        pthread_mutex_unlock(&lock);
        pthread_mutex_lock(&lock2);
        tcount++;
        pthread_mutex_unlock(&lock2);
        pthread_t tid;
        pthread_create(&tid, NULL, ThreadWork, (void*)&arg);
        printf("\nThread: %d, Current State: %d, Unprocessed Input: %s (Thread created)", arg.tn, arg.st, arg.c);
      }
      vr=((ThreadArg*)ptr)->vr;
    }
  }while(1);
}
