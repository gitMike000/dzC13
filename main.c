#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> // for use boolean type

#include "geek.h"

//const int n = 6;
#define nn 6
const int SZ = 6;

int matrix[nn][nn] = {
        {0, 1, 1, 0, 0, 0},
        {0, 0, 0, 1, 1, 1},
        {0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 0},
};
int visitedDepth[nn] = {0};

//int matrix1[nn][nn] = {
//        {1, 1, 1, 1, 0, 0},
//        {1, 0, 0, 1, 1, 1},
//        {1, 0, 1, 0, 0, 1},
//        {1, 1, 0, 0, 0, 0},
//        {0, 1, 0, 0, 0, 1},
//        {0, 1, 1, 0, 1, 0},
//};

// --stack
#define T char
#define SIZE 1000
int cursor = -1;
T Stack[SIZE];
bool push(T data)
{
    if (cursor < SIZE)
    {
        Stack[++cursor] = data;
        return true;
    }
    else
    {
        printf("Stack overflow\n");
        return false;
    }
}
T pop()
{
    if (cursor != -1)
        return Stack[cursor--];
    else
    {
        printf("Stack is empty\n");
        return -1;
    }
}

// Task 1
void depthTravers(int st) {
    int r;
    printf("%d ", st);

    visitedDepth[st] = 1;
    for (r = 0; r < nn; ++r) {
        if (matrix[st][r] == 1 && !visitedDepth[r]) {
            depthTravers(r);
        }
    }
}

void resetArr() {
    for (int i = 0; i < nn; ++i) {
        visitedDepth[i] = 0;
    }
}

void depthTraversStack(int st) {
    int r=0;
    printf("%d ", st);
    visitedDepth[st] = 1;
     do {
     if (r==nn) {r=pop();st=pop();}
//     else r=0;
     while (r < nn) {
      if (matrix[st][r] == 1 && !visitedDepth[r]) {
          push(st);
          push(r+1);
          visitedDepth[r] = 1;
          printf("%d ", r);
          st=r;
          r=0;
          break;
      }
      r++;
     }
    } while (cursor>=0);
    resetArr();
}

void depthTest() {
    int f[3]={0,2,1};
    for (int i=0;i<3;i++) {
     printf("Recursive ");
     depthTravers(f[i]);
     resetArr();
     printf("\n");
     printf("Stack     ");
     depthTraversStack(f[i]);
     printf("\n");
    }
}

// Task 2a

void clearVisited(int* arr, int size) {
    for (int i = 0; i < size; ++i) {
        arr[i] = 0;
    }
}

void sortMax(int* visited, int size) {
    for (int i=0;i<size;i++) {
        int max=visited[i];
        int ind=i;
        for (int j=1;j<size;j++) {
         if (visited[j]>max) {max=visited[j]; ind=j;}
        }
        if (max>0) printf("node=%d, count of link=%d\n",ind, max);
        visited[ind]=0;
    }
}

void adjacencyCount(int** matrix1, int start, const int size) {
    printf("Start node=%d\n",start);
    TwoLinkList* queue = (TwoLinkList*) malloc(sizeof(TwoLinkList));
    initTwoLinkList(queue);
    int visited[size];
    clearVisited(visited, size);
    TwoLinkEnqueue(queue, start);
    while (queue->size > 0) {
        int indx = TwoLinkDequeue(queue);
        if (visited[indx] > 0) continue;
        for (int i = 0; i < size; ++i) {
            if (get2dInt(matrix1, indx, i) == 1) {
                TwoLinkEnqueue(queue, i);
                visited[indx]++;
            }
        }
    }
    sortMax(visited,size);
    free(queue);
}

void adjacencyTest1(int** adjacency) {
    adjacencyCount(adjacency, 0, SZ);
    printf("\n");
    adjacencyCount(adjacency, 2, SZ);
    printf("\n");
}

//Task 2b

void traverRec(int** Cmatrix,TwoLinkList* queue, int* visited,int start, const int size) {
    int indx;
    while (true) {
     if (queue->size < 1) return;
     indx = TwoLinkDequeue(queue);
     if (visited[indx]>0) continue;
     break;
    }
    if ((start==indx) || (get2dInt(Cmatrix, start, indx) == 1) )
     for (int i = 0; i < size; ++i) {
      if (get2dInt(Cmatrix, indx, i) == 1)  {
           TwoLinkEnqueue(queue, i);
           visited[indx]++;
     }
    }
    traverRec(Cmatrix,queue,visited,start,size);
}


void traversalCount(int** Cmatrix, int start, const int size) {
    printf("Start node=%d\n",start);
    TwoLinkList* queue = (TwoLinkList*) malloc(sizeof(TwoLinkList));
    initTwoLinkList(queue);
    int visited[size];
    clearVisited(visited, size);
    TwoLinkEnqueue(queue, start);
    traverRec(Cmatrix,queue,visited,start,size);
    sortMax(visited,size);
    free(queue);
}

void widthTest2(int** adjacency) {

    traversalCount(adjacency, 0, SZ);
    printf("\n");
    traversalCount(adjacency, 2, SZ);
    printf("\n");
}

int main()
{
//  Task 1
    printf("Task 1\n");
    depthTest();

//  Task 2a

    int** adjacency = init2dIntArray(adjacency, SZ, SZ);
    // analog matrix1
    set2dInt(adjacency, 0, 0, 1);
    set2dInt(adjacency, 0, 1, 1);
    set2dInt(adjacency, 0, 2, 1);
    set2dInt(adjacency, 0, 3, 1);
    set2dInt(adjacency, 1, 0, 1);
    set2dInt(adjacency, 1, 3, 1);
    set2dInt(adjacency, 1, 4, 1);
    set2dInt(adjacency, 1, 5, 1);
    set2dInt(adjacency, 2, 0, 1);
    set2dInt(adjacency, 2, 2, 1);
    set2dInt(adjacency, 2, 5, 1);
    set2dInt(adjacency, 3, 0, 1);
    set2dInt(adjacency, 3, 1, 1);
    set2dInt(adjacency, 4, 1, 1);
    set2dInt(adjacency, 4, 5, 1);
    set2dInt(adjacency, 5, 1, 1);
    set2dInt(adjacency, 5, 2, 1);
    set2dInt(adjacency, 5, 4, 1);

    printf("\nTask 2a\n");
    adjacencyTest1(adjacency);

//  Task 2b
    printf("\nTask 2b\n");
    widthTest2(adjacency);

    free2dIntArray(adjacency,SZ,SZ);

    return 0;
}
