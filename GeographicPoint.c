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

  int iteraciones=100000;

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
  //lee el archivo de datos
  while(fgets(line_buffer,len,file))
    {              
      split_buffer=strtok(line_buffer, delimiter);

      while(split_buffer!=NULL)
	{ 
	  l=atof(split_buffer);
	  
	  matrix[i][j]=l;
	  
	  split_buffer=strtok(NULL,delimiter);
	  
	  j+=1;
	  
	}
      j=0;
      
      i+=1;   
    }
  fclose(file);
  
  
  
  int x_0;
  int y_0;
  int c=0;
  
  //saca un numero que no toque tierra
  while(c == 0)
    {
      x_0=rand()%744;
      y_0=rand()%500;
      double f=matrix[pos_y(y_0)][pos_x(x_0)];
      if(f==0.0)
	{
	  c+=1;
	}
    }
   
  double r_0=radioMax(pos_x(x_0),pos_y(y_0),matrix);
  
  lista_x[0]=pos_x(x_0);
  lista_y[0]=pos_y(y_0);
  lista_r[0]=r_0;

  
  int k;
  
  int radio;
  int x;
  int y;

  radio=0;
  x=0;
  y=0;
 
  //hace la caminata aleatoria 
  
  for(k=0;k<iteraciones;k++)
    {
      int y_2;
      int x_2;

      int y_1=lista_y[k];
      int x_1=lista_x[k];
          	
      
      int s=0;

      while(s == 0)
	{
	  int z1;
	  int z2;
	  
	  int a;
	  int b;
	  
	  a=0;
	  b=0;
	  
	  z1=rand()%10;
	  z2=rand()%10;
	  //hace un paso cercano al punto escogido pero "al azar"
	  if(6<z2)
	    {
	      b=5;
	    }
	  if(z2<3)
	    {
	      a=-5;
	    }
	  if(6<z1)
	    {
	      a=5;
	    }
	  if(z1<3)
	    {
	      b=-5;
	    }
	
       
	  double g=matrix[pos_y(y_1+b)][pos_x(x_1+a)];
      
	  if(g==0.0)
	    {
	      
	      y_2=y_1+b;
	      x_2=x_1+a;
	      s+=1;
	    }
	}
  
   
      double r_2=radioMax( pos_x(x_2),pos_y(y_2), matrix);
      double r_1=radioMax(pos_x(x_1),pos_y(y_1),matrix); 
      double alfa=r_2/r_1;
     //ponerle un delta al paso de la caminada 
     
     if(alfa>=1.0)
       {
	 lista_x[k+1]=pos_x(x_2);
	 lista_y[k+1]=pos_y(y_2);
	 lista_r[k+1]=r_2;
       }
     else
       {
	 double  beta = (double)rand() / (double)RAND_MAX ;
	 if(beta<=alfa)
	   {
	     lista_x[k+1]=pos_x(x_2);
	     lista_y[k+1]=pos_y(y_2);
	     lista_r[k+1]=r_2;
	   }
	 else
	   {
	     lista_x[k+1]=pos_x(x_1);
	     lista_y[k+1]=pos_y(y_1);
	     lista_r[k+1]=r_1;
	     
	   }
       }
    

      if(lista_r[k+1]>=radio)
	{
	  radio=lista_r[k+1];
	  x=lista_x[k+1];
	  y=lista_y[k+1];
	  
	}
      // printf("%f %f %f\n",lista_x[k+1],lista_y[k+1],lista_r[k+1]);
    }
  
  FILE *out;
  
  out=fopen("output.dat","w");
  
  fprintf(out,"%d %d %d\n",x,y,radio);
  
  fclose(out);
  
  
  freePointer(matrix);
 
  
  return 0;
}

//crea una matriz con pointers
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

//libera memoria

void freePointer(double **matrix)
 
{
    int i;
    for(i = 0; i<Ny; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
}



//encuentra el radio maximo dado dos puntos
double radioMax(int x_0,int y_0,double **matrix)
{
  
  double r;
  
  int i;
  int j;

  int t=0;
  
  r=0.0;

  int a;
  int b;
      
  a=1;
  b=1;

  while(t==0)
    {
      
      for(j=-a;j<a+1;j+=1)
	{
	  for(i=-b;i<b+1;i+=1)
	    {
	      if(matrix[pos_y(y_0+j)][pos_x(x_0+i)]==1.0)
		{
		  t+=1;		  		
		}
	      if(matrix[pos_y(y_0+j)][pos_x(x_0+i)]==0.0)
		{
		  r=sqrt( pow(i,2) + pow(j,2) ) ;
		  
		}
	      
	    } 
	}
      a+=1;
      b+=1;
      
    }

  
   return r; 
}



//condicion periodica en x
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



//condicion periodica en y
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
