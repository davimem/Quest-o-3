#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

double** LeMatriz(char nome[20],int *m, int *n)
{
  FILE *arq;
  int i,j;
  double **a;
  
  arq=fopen(nome,"r");
  
  fscanf(arq,"%d",m);
  fscanf(arq,"%d",n);

  a=(double **) malloc(sizeof(double *) * *m);
  
  for(i=0; i<*m; i++) a[i]=(double *)malloc(*n * sizeof(double));
  
  for(i=0; i<*m; i++)
  {
    for(j=0;j<*n; j++)
    {
      fscanf(arq,"%lf",&a[i][j]);
    }
  }
  
  return a;
}

double **MultiplicaMatriz(double **M, int m1, int m2, double **N, int n1, int n2)
{
  double **S,t;
  int i, j,k;
  
  if(m2!=n1)
  {
    printf("A mutiplicacao nao pode ser feita!\n"); 
    return NULL;
  }
  
  S=malloc(m1*sizeof(double *));
  for(i=0; i<m1; i++) S[i]=malloc(n2 * sizeof(double));

  for(i=0; i<m1; i++)
  {
    for(j=0; j<n2; j++)
    {
      t=0;
      for(k=0; k<m2; k++)
      {
        t+=M[i][k]*N[k][j];
      }
      S[i][j]=t;
    }
  }
  
  return S;
}

int ComparaMatriz(double **M,double **N,int m1,int m2)
{
  int i,c=1;
  if(m1!=m2) return 1;

  for(i=0; i<m1; i++)
  {
    c=memcmp(M[i], N[i], m1*sizeof(*M[i]));
    if(c!=0) return 1;
  }
  
  return 0;
}

void ImprimeMatriz(double **M, int m, int n)
{
  int i,j;
  
  for (i=0; i<m; i++) 
  {
    for(j=0;j<n;j++)
    {
      printf("%.2lf ",M[i][j]);
    }
    puts("");
  }  
  puts("");
}

double **Transposta(double **M, int m, int n)
{
  int i,j;
  double **S;

  S=malloc(n*sizeof(double *));
  for(i=0; i<n; i++) S[i]=malloc(m * sizeof(double));
  
  for(i=0; i<m; i++)
  {
    for(j=0; j<n;j++)    
    {
      S[n][m]=M[m][n];
    }
  }
  
  return S;
}

int main()
{
  double **M, **N, **Mt, **Nt;
  int m1, m2, n1, n2;
  
  M = LeMatriz("m1.dat", &m1, &m2);
  N = LeMatriz("m2.dat", &n1, &n2);
  ImprimeMatriz(M, m1, m2);
  ImprimeMatriz(N, n1, n2);

  Mt = Transposta(M, m1, m2);
  ImprimeMatriz(Mt, m2, m1);

  Nt = Transposta(N, n1, n2);
  ImprimeMatriz(Nt, n2, n1);
}