#include <stdio.h>
#include <stdlib.h>
//bfs cu coada


typedef struct{
    int n; //noduri, mughii
    int **adj;
}Graf;

typedef struct nodetype //coada
{
    int key;
    struct nodetype *next;
}queue;

//1
queue *create(int givenkey)
{
    queue *p =(queue*)malloc(sizeof(queue));
    p->key = givenkey;
    p->next = NULL;
    return p;
}

//2
void insertLast( queue** first,queue** last, int givenkey)
{
    queue* p = create(givenkey);
    if(*first == NULL)
    {
        *first = p;
        *last = p;
    }
    else
    {
        (*last)->next = p;
        *last = p;
    }
}

//3
int deleteFirst(queue** first, queue**last)
{
    queue* p = *first;
    int val= p->key;

    *first=(*first)->next;
    free(p);

    if(*first ==NULL)
    {
        *last = NULL;
    }
    return val;
}

//4
void bfs(Graf g, int s) //s=nodul de la care pornim
{
   queue *first = NULL, *last = NULL ;
   insertLast(&first, &last, s); //punem nodul de inceput dupa fiecare nod in coada


    int *vizitat; //alocare dinamica punem 0
    vizitat = (int*)calloc(g.n +1, sizeof(int));

    vizitat[s] =1;

    while(first!= NULL)
    {
        int val = deleteFirst(&first, &last);
        printf("%d", val);

        for(int i =1; i<=g.n; i++)
        {
            if(vizitat[i] == 0 && g.adj[val][i]==1)
            {
                insertLast(&first, &last, i);
                vizitat[i] =1;
            }
        }
    }
}

int main()
{
    FILE* f =fopen("grafbfs.txt", "r");
    if(f==NULL)
    {
        return 0;
    }

    Graf g;
    fscanf(f, "%d", &g.n);
    g.adj=(int**)calloc(g.n+1, sizeof(int*));

    for(int i=0;i<=g.n;i++)
        g.adj[i]=(int*)calloc(g.n+1,sizeof(int));

    int x,y;

    while(fscanf(f,"%d %d",&x,&y)==2)
    {
        g.adj[x][y]=1;
    }

    bfs(g,1);

    return 0;
}
