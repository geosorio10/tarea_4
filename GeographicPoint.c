#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>


int Ny;
int Nx;

double **Matrix(void);
void freePointer(double **matrix);
double radioMax(int x_0,int y_0,double **matrix);
int aleatorio();


int main(void){
  
  
  
  FILE *file;
  file=fopen("map_data.txt","r");

  int len=2000;
  char line_buffer[len];
  char *split_buffer;
  const char *delimiter;

  int iteraciones=100;

  double *lista_x=malloc(iteraciones*sizeof(double));
  double *lista_y=malloc(iteraciones*sizeof(double));
  double *lista_r=malloc(iteraciones*sizeof(double));
  
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
  
  double r_0=radioMax(x_0,y_0,matrix);
  
  lista_x[0]=x_0;
  lista_y[0]=y_0;
  lista_r[0]=r_0;
  
  
  int k;
  
  for(k=0;k<iteraciones;k++)
    {
      int y_2=aleatorio()%1500;
      int x_2=aleatorio()%500;
      
      int y_1=lista_y[k];
      int x_1=lista_x[k];
            	
     if( (matrix[y_2][x_2]==0.0) && (matrix[y_1][x_1]==0.0) )
    {
      
     double r_2=radioMax( x_2, y_2, matrix);
     double r_1=radioMax(x_1,y_1,matrix); 
     double alfa=r_2/r_1;
     
     if(alfa>=1.0)
       {
	 lista_x[k+1]=x_2;
	 lista_y[k+1]=y_2;
	 lista_r[k+1]=r_2;
       }
     else
       {
	 double  beta = (double)rand() / (double)RAND_MAX ;
	 if(beta<=alfa)
	   {
	     lista_x[k+1]=x_2;
	     lista_y[k+1]=y_2;
	     lista_r[k+1]=r_2;
	   }
	 else
	   {
	     lista_x[k+1]=x_1;
	     lista_y[k+1]=y_1;
	     lista_r[k+1]=r_1;
	     
	   }
       }
    }
     printf("%f\t%f\t%f\n",lista_x[k],lista_y[k],lista_r[k]);
     
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





int aleatorio()
{
  srand(time(NULL));

  int  x=rand();
  return x;
  
}
