#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#define DOUBLE float


int Ny;
int Nx;

double **Matrix(void);
void freePointer(double **matrix);
int aleatorio();
double radioMax(int x_0,int y_0,double **matrix);


int main(void){

  FILE *file;
  file=fopen("map_data.txt","r");

  int len=2000;
  char line_buffer[len];
  char *split_buffer;
  const char *delimiter;

  Nx=500;//por que sale segmentation fault si pongo 744X500
  Ny=1500;

  double **matrix=Matrix();
  double l;
 
  delimiter = " ";

  int i=0,j=0;

  while(fgets(line_buffer,len,file))
    {
      //printf("LINE IS: %s", line_buffer);
      split_buffer=strtok(line_buffer, delimiter);

      while(split_buffer!=NULL)
	{
	 
	  //printf("ITEM IN LINE: %s %d %d\n",split_buffer,i,j);
	  l=atof(split_buffer);
	  matrix[i][j]=l;
	  
	  //printf("%f\n",matrix[i][j]);
	  
	  split_buffer=strtok(NULL,delimiter);
	  j+=1;
	  
	}
     
      i+=1;   
    }

  int y_0=aleatorio()%1500;
  int x_0=aleatorio()%500;

  printf("%d %d\n",y_0,x_0);
  printf("%f\n",matrix[y_0][x_0]);
  
  if(matrix[y_0][x_0]==0.0)
    {
     double r=radioMax( x_0, y_0, matrix);
     
     printf("%f\n",r);
    }


  
  /* 
  freePointer(matrix);
 */
  
  return 0;
}


double **Matrix(void)
{
    int i;
    double **matrix;
    matrix = malloc(Ny*sizeof(double *));

    for(i = 0; i < Ny; i++)
    {
        matrix[i] = malloc(Nx*sizeof(double));
    }

    return matrix;
}


void freePointer(double **matrix)
 
{
    int i;
    for(i = 0; i<Ny; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
}

int aleatorio()
{
  srand(time(NULL));

  int  x=rand();
  return x;
  
}


double radioMax(int x_0,int y_0,double **matrix)
{
  
  double r;
  
  int i;
  
  i=0;
  
  while( (matrix[y_0][x_0+i]==0.0) && (matrix[y_0+i][x_0]==0.0) && (matrix[y_0-i][x_0]==0.0) && (matrix[y_0][x_0-i]==0.0) )//me gustaria para que tome tambien un circulo de unos.
    {
      r=i;
      
      i+=1;
    }

  return r; 
}




