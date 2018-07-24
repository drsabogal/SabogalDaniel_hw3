#include <iostream>
#include <fstream>

using namespace std;

int main()
{
  /* para cargar las condiciones iniciales del problema se uso un arreglo de nxm el cual contenia todos los datos*/
  int m = 100;
  int n = 100;
  float datos[n*m];
  float inicial[m][n];
  ifstream archivo;
  archivo.open("init.dat");
  
  for(int i =0;i<(n*m);i++)
    {
      archivo >> datos[i];
      
    }
  archivo.close();
  /* para organiza los datos en una matriz que describiera las condiciones iniciales */
  int contador = 0;
  for(int i =0;i<n;i++)
    {
      for(int j =0;j<m;j++)
	{
	  inicial[i][j]= datos[contador];
	  contador++;
	}
    }
  
  float phiFu1[n][m];
  float phiPre1[n][m];
  float phiPa1[n][m];
  float dx = 0.01;
  float c = 300.0;
  float dt = (dx/c)*(0.5);
  float tf = 0.06;
  int ite = tf/dt;
  float final1[n][m];
  float corteP0[n];
  float corteP50[n];
  float corteP100[n];
  float corteP150[n];
  /* el siguiente codigo toma tres arreglos de la funcio phi que cambian en el tiempo, los arreglos van cambiado con el paso del tiempo en i, dichos arreglos son recorridos por dos for en las posiciones con variables j y k, para el primer paso de tiempo se utilizo la condicion de que la derivada es cero, el codigo arrojaba resultados estables hasta 150 pasos en el tiempo, por lo que a las 150 iteraciones un arreglo llamado final1 tomaba los valores de la funcion phi en ese instante de tiempo */
  for(int i =0;i < ite +1 ; i++)
    {
       for(int j=0;j<n;j++)
	    {
	      for(int k =0; k<m;k++)
		{
		  if(i==0)
		    {
		      phiPre1[j][k] = inicial[j][k]; 
		    }
		}

	    }
       for(int j=1;j< (n-1);j++)
	 {
	   for(int k=1; k < (m-1);k++)
	     {
	       if(i==0)
		 {
		   
		   phiFu1[j][k] = (((c*c)*(dt*dt)/(dx*dx))*(phiPre1[j+1][k] - 2.0*phiPre1[j][k] + phiPre1[j-1][k]) + ((c*c)*(dt*dt)/(dx*dx))*(phiPre1[j][k+1] -2.0*phiPre1[j][k] + phiPre1[j][k-1]) + 2.0*phiPre1[j][k])*(0.5);
		   phiPa1[j][k] = phiPre1[j][k];
		   phiPre1[j][k] = phiFu1[j][k];
		   
		 }
	       else
		 {
		   
		   phiFu1[j][k] = ((c*c)*(dt*dt)/(dx*dx))*(phiPre1[j+1][k]- 2.0*phiPre1[j][k] + phiPre1[j-1][k]) + ((c*c)*(dt*dt)/(dx*dx))*(phiPre1[j][k+1] -2.0*phiPre1[j][k] + phiPre1[j][k-1]) + 2.0*phiPre1[j][k] - phiPa1[j][k];
		   phiPa1[j][k] = phiPre1[j][k];
		   phiPre1[j][k] = phiFu1[j][k];
		   if(i==150)
		     {
			  
		       final1[j][k] = phiPre1[j][k];
		       
			 
		     }

		 }
		 
	     }
	   

	 }
       /* teniendo en cuenta que lo resultados arrojados solo eran estables en las 150 primeros pasos del tiempo, se tomo intervalos de 50 pasos para los cortes transversales*/
       if(i==0)
	 {
	   for(int t =0;t<n;t++)
	     {
	       corteP0[t] = phiPre1[49][t];
	     }
	 }
       if(i==50)
         {
           for(int t =0;t<n;t++)
             {
               corteP50[t] = phiPre1[49][t];
             }
         }
       if(i==100)
         {
           for(int t =0;t<n;t++)
             {
               corteP100[t] = phiPre1[49][t];
             }
         }
       if(i==150)
         {
           for(int t =0;t<n;t++)
             {
               corteP150[t] = phiPre1[49][t];
             }
         }

	   

    }

  /*Para la condicion de extremos abiertos se tuvo en cuenta los casos en donde el j y k estan junto al borde, debido a las condiciones de derivada espacial se cambia el valor de jo k por j+1 o k+1 segun el caso, adicionalmente se utiliza el mismo procedimiento que en el caso de extremos fijos para obtener los datos faltantes */
  float phiPre2[n][m];
  float phiPa2[n][m];
  float phiFu2[n][m];
  float final2[n][m];
  float corte2P0[n];
  float corte2P50[n];
  float corte2P100[n];
  float corte2P150[n];
  for(int i =0;i < ite +1 ; i++)
    {
      for(int j=0;j<n;j++)
	{
	  for(int k =0; k<m;k++)
	    {
	      if(i==0)
		{
		  phiPre2[j][k] = inicial[j][k];

		}
	    }

	}

      for(int j=1;j< n-1;j++)
	{
	  for(int k=1; k < m-1;k++)
	    {
	      if(i==0)
		{
		  if(j==1 && k==1)
		    {
		      phiFu2[j][k] = (((c*c)*(dt*dt)/(dx*dx))*(phiPre2[j+1][k]- 2.0*phiPre2[j][k] + phiPre2[j][k]) + ((c*c)*(dt*dt)/(dx*dx))*(phiPre2[j][k+1] -2.0*phiPre2[j][k] + phiPre2[j][k]) + 2.0*phiPre2[j][k])*(0.5);
		      phiPa2[j][k] = phiPre2[j][k];
		      phiPre2[j][k] = phiFu2[j][k];
		      
		    }
		  if(j==1 && k!=1)
		    {
		      phiFu2[j][k] = (((c*c)*(dt*dt)/(dx*dx))*(phiPre2[j+1][k]- 2.0*phiPre2[j][k] + phiPre2[j][k]) + ((c*c)*(dt*dt)/(dx*dx))*(phiPre2[j][k+1] -2.0*phiPre2[j][k] + phiPre2[j][k-1])+ 2.0*phiPre2[j][k])*(0.5);
                      phiPa2[j][k] = phiPre2[j][k];
                      phiPre2[j][k] = phiFu2[j][k];

		    }
		  if(k==1 && j!=1)
		    {
		      phiFu2[j][k] = (((c*c)*(dt*dt)/(dx*dx))*(phiPre2[j+1][k]- 2.0*phiPre2[j][k] + phiPre2[j-1][k]) + ((c*c)*(dt*dt)/(dx*dx))*(phiPre2[j][k+1] -2.0*phiPre2[j][k] + phiPre2[j][k])+ 2.0*phiPre2[j][k])*(0.5);
		      phiPa2[j][k] = phiPre2[j][k];
		      phiPre2[j][k] = phiFu2[j][k];

		    }
		  if(j == n-2 && k== m-2)
		    {
		      phiFu2[j][k] = (((c*c)*(dt*dt)/(dx*dx))*(phiPre2[j][k]- 2.0*phiPre2[j][k] + phiPre2[j-1][k]) + ((c*c)*(dt*dt)/(dx*dx))*(phiPre2[j][k] -2.0*phiPre2[j][k] + phiPre2[j][k-1])+2.0*phiPre2[j][k])*(0.5);
                      phiPa2[j][k] = phiPre2[j][k];
                      phiPre2[j][k] = phiFu2[j][k];
		    }
		  if(j== n-2 && k!= m-2)
		    {
		      phiFu2[j][k] = (((c*c)*(dt*dt)/(dx*dx))*(phiPre2[j][k]- 2.0*phiPre2[j][k] + phiPre2[j-1][k]) + ((c*c)*(dt*dt)/(dx*dx))*(phiPre2[j][k+1] -2.0*phiPre2[j][k] + phiPre2[j][k-1])+2.0*phiPre2[j][k])*(0.5);
		      phiPa2[j][k] = phiPre2[j][k];
		      phiPre2[j][k] = phiFu2[j][k];

		    }
		   if(k== m-2 && j!= n-2 )
		     {
		       phiFu2[j][k] = (((c*c)*(dt*dt)/(dx*dx))*(phiPre2[j+1][k]- 2.0*phiPre2[j][k] + phiPre2[j-1][k]) + ((c*c)*(dt*dt)/(dx*dx))*(phiPre2[j][k] -2.0*phiPre2[j][k] + phiPre2[j][k-1]) + 2.0*phiPre2[j][k])*(0.5);
		       phiPa2[j][k] = phiPre2[j][k];
		       phiPre2[j][k] = phiFu2[j][k];

		     }
		   else
		     {
		       phiFu2[j][k] = (((c*c)*(dt*dt)/(dx*dx))*(phiPre2[j+1][k]- 2.0*phiPre2[j][k] + phiPre2[j-1][k]) + ((c*c)*(dt*dt)/(dx*dx))*(phiPre2[j][k+1] -2.0*phiPre2[j][k] + phiPre2[j][k-1]) + 2.0*phiPre2[j][k])*(0.5);
		  phiPa2[j][k] = phiPre2[j][k];
		  phiPre2[j][k] = phiFu2[j][k];
		     }
		}
	      else
		{
		  if(j==1 && k ==1)
		    {
		      phiFu2[j][k] = ((c*c)*(dt*dt)/(dx*dx))*(phiPre2[j+1][k]- 2.0*phiPre2[j][k] + phiPre2[j][k]) + ((c*c)*(dt*dt)/(dx*dx))*(phiPre2[j][k+1] -2.0*phiPre2[j][k] + phiPre2[j][k]) + 2.0*phiPre2[j][k] - phiPa2[j][k];
		      phiPa2[j][k] = phiPre2[j][k];
		      phiPre2[j][k] = phiFu2[j][k];
		    }
		  if(j==1 && k!=1)
		    {
		      phiFu2[j][k] = ((c*c)*(dt*dt)/(dx*dx))*(phiPre2[j+1][k]- 2.0*phiPre2[j][k] + phiPre2[j][k]) + ((c*c)*(dt*dt)/(dx*dx))*(phiPre2[j][k+1] -2.0*phiPre2[j][k] + phiPre2[j][k-1]) + 2.0*phiPre2[j][k] - phiPa2[j][k];
		      phiPa2[j][k] = phiPre2[j][k];
		      phiPre2[j][k] = phiFu2[j][k];

		    }
		  if(k==1 && j!=1)
		    {
		      phiFu2[j][k] = ((c*c)*(dt*dt)/(dx*dx))*(phiPre2[j+1][k]- 2.0*phiPre2[j][k] + phiPre2[j-1][k]) + ((c*c)*(dt*dt)/(dx*dx))*(phiPre2[j][k+1] -2.0*phiPre2[j][k] + phiPre2[j][k]) + 2.0*phiPre2[j][k] - phiPa2[j][k];
		      phiPa2[j][k] = phiPre2[j][k];
		      phiPre2[j][k] = phiFu2[j][k];

		    }
		  if(j == n-2 && k== n-2)
		    {
		      phiFu2[j][k] = ((c*c)*(dt*dt)/(dx*dx))*(phiPre2[j][k]- 2.0*phiPre2[j][k] + phiPre2[j-1][k]) + ((c*c)*(dt*dt)/(dx*dx))*(phiPre2[j][k] -2.0*phiPre2[j][k] + phiPre2[j][k-1]) + 2.0*phiPre2[j][k] - phiPa2[j][k];
		      phiPa2[j][k] = phiPre2[j][k];
		      phiPre2[j][k] = phiFu2[j][k];
		    }
		  if(j == n-2 && k!= n-2)
		    {
		      phiFu2[j][k] = ((c*c)*(dt*dt)/(dx*dx))*(phiPre2[j][k]- 2.0*phiPre2[j][k] + phiPre2[j-1][k]) + ((c*c)*(dt*dt)/(dx*dx))*(phiPre2[j][k+1] -2.0*phiPre2[j][k] + phiPre2[j][k-1]) + 2.0*phiPre2[j][k] - phiPa2[j][k];
		      phiPa2[j][k] = phiPre2[j][k];
		      phiPre2[j][k] = phiFu2[j][k];


		    }
		  if(k== n-2 && j!= n-2)
		    {
		    phiFu2[j][k] = ((c*c)*(dt*dt)/(dx*dx))*(phiPre2[j+1][k]- 2.0*phiPre2[j][k] + phiPre2[j-1][k]) + ((c*c)*(dt*dt)/(dx*dx))*(phiPre2[j][k] -2.0*phiPre2[j][k] + phiPre2[j][k-1]) + 2.0*phiPre2[j][k] - phiPa2[j][k];
		  phiPa2[j][k] = phiPre2[j][k];
		  phiPre2[j][k] = phiFu2[j][k];
		    }
		  else
		    {
		      phiFu2[j][k] = ((c*c)*(dt*dt)/(dx*dx))*(phiPre2[j+1][k]- 2.0*phiPre2[j][k] + phiPre2[j-1][k]) + ((c*c)*(dt*dt)/(dx*dx))*(phiPre2[j][k+1] -2.0*phiPre2[j][k] + phiPre2[j][k-1]) + 2.0*phiPre2[j][k] - phiPa2[j][k];
		      phiPa2[j][k] = phiPre2[j][k];
		      phiPre2[j][k] = phiFu2[j][k];



		    }
		}



	    }


	}
      if(i==150)
	{
	  for (int j =1;j<n;j++)
	    {
	      for (int k =1;k<m;k++)
		{
		  final2[j][k] = phiPre2[j][k];
		}

	    }
	
	}
      if(i==0)
	{
	  for(int t =0;t<n;t++)
	    {
	      corte2P0[t] = phiPre2[49][t];
	    }
	}
      if(i==50)
	{
	  for(int t =0;t<n;t++)
	    {
	      corte2P50[t] = phiPre2[49][t];
	    }
	}
      if(i==100)
	{
	  for(int t =0;t<n;t++)
	    {
	      corte2P100[t] = phiPre2[49][t];
	    }
	}
      if(i==150)
	{
	  for(int t =0;t<n;t++)
	    {
	      corte2P150[t] = phiPre2[49][t];
	    }
	}







    }
  for(int j =1;j<n;j++)
    {
      for(int k =1; k<m ;k++)
	{
	  cout <<  inicial[j][k]<< "," << final1[j][k] << "," <<final2[j][k] << "," << j << "," << k << "," << corteP0[k] << "," << corteP50[k]<< "," << corteP100[k] << "," <<  corteP150[k] << "," <<corte2P0[k] << "," << corte2P50[k] << "," << corte2P100[k] << "," << corte2P150[k] << endl;
	}


      

    }
  return 0;
}
