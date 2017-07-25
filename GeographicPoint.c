#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define DOUBLE float


int Ny;
int Nx;

double **Matrix(void);
void freePointer(double **matrix);


int main(void){

  FILE *file;
  file=fopen("map_data.txt","r");

  int len=1500;
  char line_buffer[len];
  char *split_buffer;
  const char *delimiter;
  Nx=1500;
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
	  //printf("ITEM IN LINE: %s\n",split_buffer);
	  //printf("ITEM IN LINE: %s %d %d\n",split_buffer,i,j);
	  l=atof(split_buffer);
	  matrix[i][j]=l;
	  printf("%f\n",matrix[i][j]);
	  split_buffer=strtok(NULL,delimiter);
	  j+=1;
	  
	}
      
      i+=1;   
    }
  
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
