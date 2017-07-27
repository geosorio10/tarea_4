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
int pos_x(int x);
int pos_y(int y);


int main(void)
{
  
  srand(time(NULL));
  
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
  
  Nx=744;
  Ny=500;

  double **matrix=Matrix();
  double l;
 
  delimiter = " ";

  int i=0;
  int j=0;
  
  while(fgets(line_buffer,len,file))
    {  
      

      //printf("LINE IS: %s", line_buffer);
      split_buffer=strtok(line_buffer, delimiter);

      while(split_buffer!=NULL)
	{
	  //int  j=0;
	 //printf("%d\n",j);
	  //printf("ITEM IN LINE: %s %d %d\n",split_buffer,i,j);
	  l=atof(split_buffer);
	  matrix[i][j]=l;
	  
	  //printf("%f %d %d\n",matrix[i][j],i,j);
	  
	  split_buffer=strtok(NULL,delimiter);
	  j+=1;
	  
	}
      j=0;
      i+=1;   
    }


  
  int y_0=rand()%500;
  int x_0=rand()%744;

    
  double r_0=radioMax(x_0,y_0,matrix);
  
  lista_x[0]=x_0;
  lista_y[0]=y_0;
  lista_r[0]=r_0;
  //printf("%f\n",lista_r[0]);
  
  int k;
  int radio;
  int x;
  int y;

  radio=0;
  x=0;
  y=0;
  //asegurarse que el punto cae en el mar
  
  for(k=0;k<iteraciones;k++)
    {
      int y_2=rand()%500;
      int x_2=rand()%744;
      
      int y_1=lista_y[k];
      int x_1=lista_x[k];
      //while para mirar que el numero cae en el mar
            	
      if( (matrix[pos_y(y_2)][pos_x(x_2)]==0.0) && (matrix[pos_y(y_1)][pos_x(x_1)]==0.0) )
    {
      
     double r_2=radioMax( x_2, y_2, matrix);
     double r_1=radioMax(x_1,y_1,matrix); 
     double alfa=r_2/r_1;
     //ponerle un delta al paso de la caminada 
     
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

      if(lista_r[k+1]>=radio)
	{
	  radio=lista_r[k+1];
	  x=lista_x[k+1];
	  y=lista_y[k+1];
	}
      
     printf("%f\t%f\t%f\n",lista_x[k],lista_y[k],lista_r[k]);
    
     
    }
    
   printf("%d %d %d\n",x,y,radio);
  
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
  
  while( (matrix[pos_y(y_0)][pos_x(x_0+i)]==0.0) && (matrix[pos_y(y_0+i)][pos_x(x_0)]==0.0) && (matrix[pos_y(y_0-i)][pos_x(x_0)]==0.0) && (matrix[pos_y(y_0)][pos_x(x_0-i)]==0.0) )//me gustaria para que tome tambien un circulo de unos.
    {
      r=i;
      
      i+=1;
    }

  return r; 
}




int pos_x(int x)
{
  int indice;
  if(x>=0)
    {
      indice=x%744;
    }
  if(x<0)
    {
      indice = x%744 + 744;
    }
  return indice;
}




int pos_y(int y)
{
  int indice;
  if(y>=0)
    {
      indice=y%500;
    }
  if(y<0)
    {
      indice=y%500 +500 ;
    }
  
  return indice;
}
