#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define MAX 200

typedef struct obst{
  int key;
  struct obst *esq, *dir;
}obst;

int cost[MAX][MAX];
int w[MAX][MAX];
int raiz[MAX][MAX];
int q[MAX];
int freq[MAX];
int keys[MAX];
int d=0;

int sum(int freq[], int i, int j)
{
    int s = 0;
    for (int k = i; k <=j; k++)
       s += freq[k];
    return s;
}

void optimalSearchTree(int n)
{
  int j,x;
    for(int i = 0; i <= n; i++)  {
           w[i][i] = q[i];
           for(int j = i + 1; j <= n; j++)
              w[i][j] = w[i][j-1] + freq[j] + q[j];
     }


    for (int i = 0; i <= n; i++)
        cost[i][i] = w[i][i];
    for(int i=0; i < n; i++ ){
        j = i + 1;
        cost[i][j] = cost[i][i] + cost[j][j] + w[i][j];
        raiz[i][j] = j;
    }
    for (int L=2; L<=n; L++)
    {

        for (int i=0; i<=n-L; i++)
        {

            int j,m,min;
            j = i+L;
            m = raiz[i][j-1];
            min = cost[i][m-1] + cost[m][j];

            for (int k=m+1; k <= raiz[i+1][j]; k++)
            {
                x = cost[i][k-1] + cost[k][j];
                if(x < min){
                  m = k;
                  min = x;
                  }
            }
            cost[i][j] = w[i][j] + min;
            raiz[i][j] = m;
          }
        }

  /*  printf("\nThe weight matrix W:\n");
for(int i = 0; i <= n; i++) {
  for(int j = i; j <= n; j++)
        printf("%d  ", w[i][j]);
        printf("\n");
      }
//Display Cost matrix C
      printf("\nThe cost matrix C:\n");
  for(int i = 0; i <= n; i++) {
      for(int j = i; j <= n; j++)
      printf("%d  ", cost[i][j]);
            printf("\n");
      }
//Display root matrix R
      printf("\nThe root matrix R:\n");
      for (int i = 0; i <= n; i++) {
        for(int j = i; j <= n; j++)
            printf("%d  ", raiz[i][j]);
            printf("\n");
      }*/
}


obst *CONSTRUCT_obst(int i,int j){
      obst *p;

      if(i == j)
        p = NULL;
      else{
          p = (obst *)malloc(sizeof(obst));
          p->key = keys[raiz[i][j]];

          p->esq = CONSTRUCT_obst(i, raiz[i][j] - 1);
          p->dir = CONSTRUCT_obst(raiz[i][j], j);
      }
      return p;
}

void constroi_avore_otima(obst *no){

  if (no == NULL)
    return;
     constroi_avore_otima(no->esq);
     printf("chave: d%d fesq: nil fdir: nil\n", d);
     printf("chave: %d ", no->key);
 if(no->esq != NULL)
		 printf("fesq: %d ", no->esq->key);
	else
	   printf("fesq: d%d ", d);
     d++;
 if(no->dir != NULL)
		 printf("fdir: %d\n", no->dir->key);
   else
		 printf("fdir: d%d\n", d);
  	 constroi_avore_otima(no->dir);
}


int main() {
  int i, k,n;
  obst *arvore;

     scanf("%d", &n);
		for(i = 1; i <= n; ++i) {
             scanf("%d", &keys[i]);
       }
		for(i = 1; i <= n; ++i){
			scanf("%d",&freq[i]);
		}
       for(i = 0; i <= n; i++) {
             scanf("%d",&q[i]);
       }

	    optimalSearchTree(n);
	    arvore = CONSTRUCT_obst(0,n);
      constroi_avore_otima(arvore);
      printf("chave: d%d fesq: nil fdir: nil\n", d);
   return 0;
}
