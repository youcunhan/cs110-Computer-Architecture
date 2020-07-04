#include <stdlib.h>
#include <stdio.h>
#include<pthread.h>

/* A global mutex lock. */
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

/* A global condition variable. */
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void* findmin(int);
void *updatetable(int);

int num_per_thread, maxnum;
/*Define n, s, t*/
int n, s, t;
int *min, *k;
int* distance;
int* isvisit;
int* previsit;
/*Define the adjacency matrix*/
int** matrix;

int compare(int a, int b){
  if(a == 0) return 0;
  else if(b == 0) return 1;
  else return a < b;
}

/* Calculate the shortest distance given the input. */
void
dist (int max_threads)
{
  maxnum = max_threads;
  /*Get the input of n, s, t*/
  if(scanf("%d %d %d", &n, &s, &t) != 3){
    printf("Error! Can't find any more input!\n");
    exit(-1);
  }


  num_per_thread = n/max_threads;

  /*Define the adjacency matrix*/
  matrix = malloc(n * sizeof(int*));
  /*Alloc memory for the adjacency matrix*/
  for (int i = 0; i < n; i++)
  {
    matrix[i] = malloc(n * sizeof(int));
  }
  /*Get the input*/
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      if(scanf("%d", matrix[i] + j) != 1){
        printf("Error! Can't find any more input!\n");
        exit(-1);
      }
    }
  }
  // for (int i = 0; i < n; i++)
  // {
  //   for (int j = 0; j < n; j++)
  //   {
  //     printf("%d ",matrix[i][j]);
  //   }
  //   printf("\n");
  // }
  /*Define values*/
  /*distance between two points*/
  distance = malloc(n * sizeof(int));
  /*record whether a point is visited*/
  isvisit = malloc(n * sizeof(int));
  /*trace the path*/
  previsit = malloc(n * sizeof(int));
  /*Initialize the isvisit*/
  for (int i = 0; i < n; i++)
  {
    isvisit[i] = 0;
  }
  /*Initialize the distance*/
  for (int i = 0; i < n; i++)
  {
    distance[i] = matrix[s][i];
    previsit[i] = s;
  }
  /*Let the source obtained in isvisited*/
  isvisit[s] = 1;

  /*malloc the min and its index*/
  min = malloc(sizeof(int));
  k = malloc(sizeof(int));
  /*Define threads*/
  pthread_t *threads = malloc (sizeof (*threads) * max_threads);
  while(isvisit[t] != 1){
    /*Find nearest point*/
    *min = 0, *k = 0;
    for (int i = 0; i < max_threads; ++i)
    {
      pthread_create (threads + i, NULL, findmin, i);
    }
      

    /* Join threads. */
    for (int i = 0; i < max_threads; ++i)
      pthread_join (threads[i], NULL);


    isvisit[*k] = 1;

    /*updatetable*/
    for (int i = 0; i < max_threads; ++i)
    {
      pthread_create (threads + i, NULL, updatetable, i);
    }
    /* Join threads. */
    for (int i = 0; i < max_threads; ++i)
      pthread_join (threads[i], NULL);
    
  }
  /*free threads*/
  free (threads);
  pthread_mutex_destroy (&mutex);
  pthread_cond_destroy (&cond);

  /*output the distance*/
  printf("%d\n", distance[t]);
  /*reverse the trace*/
  int num = 0;
  int *reverse_output = malloc(n * sizeof(int));
  int tmp = t;
  /*trace the path from t to s*/
  while(tmp!=s){
    reverse_output[num] = tmp;
    tmp = previsit[tmp];
    num++;
  }
  /*source*/
  reverse_output[num] = s;
  num++;
  /*ready to trace path*/
  for (int i = num - 1; i >= 0; i--)
  {
    printf("%d\n", reverse_output[i]);
  }
  /*free all alloced momery*/
  free(reverse_output);
  /*free all alloced momery*/
  free(min);
  /*free all alloced momery*/
  free(k);
  /*free all alloced momery*/
  free(isvisit);
  /*free all alloced momery*/
  free(previsit);
  /*free all alloced momery*/
  free(distance);
  /*free all alloced momery*/
  for (int i = 0; i < n; i++)
  {
    free(matrix[i]);
  }
  /*free all alloced momery*/
  free(matrix);
}

void *findmin(int threadnum){
  /*deal with data between threadnum * num_per_thread ~ (threadnum + 1)* num_per_thread*/
  int end;
  /*last thread should deal with the rest data*/
  if(threadnum == maxnum - 1) end = n;
  else end = (threadnum + 1)* num_per_thread;
  /*findmin*/
  for (int i = threadnum * num_per_thread; i < end; i++)
  {
    /*only consider unvisited points*/
    if(!isvisit[i] && compare(distance[i], *min)){
      *min = distance[i];
      *k = i;
    }
  }
  /*return*/
  return NULL;
}

void *updatetable(int threadnum){
  /*deal with data between threadnum * num_per_thread ~ (threadnum + 1)* num_per_thread*/
  int end;
  /*last thread should deal with the rest data*/
  if(threadnum == maxnum - 1) end = n;
  else end = (threadnum + 1) * num_per_thread;
  for (int i = threadnum * num_per_thread; i < end; i++)
    {
      /*only consider unvisited points*/
      if(i != s && matrix[*k][i] != 0 && !isvisit[i] &&  compare(distance[*k] + matrix[*k][i], distance[i])){
        distance[i] = distance[*k] + matrix[*k][i];
        previsit[i] = *k;
      }
    }
  /*return*/
  return NULL;
}