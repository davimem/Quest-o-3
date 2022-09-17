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
  double **Mt;
  int i,j;
  Mt=(double **)malloc(m*sizeof(double *));
  for(i=0; i<m; i++) Mt[i]=(double *)malloc(n * sizeof(double));
  
  for(i=0; i<m;i++)
  {
    for(j=0; j<n;j++)    
    {
      Mt[i][j]=M[j][i];
    }
  }
  return Mt;
}

int main()
{
  double **M, **N, **Mt, **Nt, **MN, **MNt, **NtMt;
  int m1, m2, n1, n2,i;
  
  M = LeMatriz("m1.dat", &m1, &m2);
  N = LeMatriz("m2.dat", &n1, &n2);
  printf("Matriz M:\n");
  ImprimeMatriz(M, m1, m2);
  printf("Matriz N:\n");
  ImprimeMatriz(N, n1, n2);

  Mt=Transposta(M, m1, m2);
  printf("Matriz Mt:\n");
  ImprimeMatriz(Mt, m1, m2);

  Nt = Transposta(N, n1, n2);
  printf("Matriz Nt:\n");
  ImprimeMatriz(Nt, n2, n1);

  MN= MultiplicaMatriz(M, m1, m2, N, n1, n2);
  printf("Matriz M*N:\n");
  ImprimeMatriz(MN, m1, n2);
  
  MNt= Transposta(MN, m1, m2);
  printf("Matriz (M*N)t:\n");
  ImprimeMatriz(MNt, m1, n2);

  NtMt= MultiplicaMatriz(Nt, n1, n2, Mt, m1, m2);
  printf("Matriz Nt*Mt:\n");
  ImprimeMatriz(NtMt, m1, n2);

  i=ComparaMatriz(MNt, NtMt, m1, m2);
  
  if(i==0) printf("As matrizes sao iguais!\n");
  else printf("As matrizes sao diferentes!\n");

  return 0;
}