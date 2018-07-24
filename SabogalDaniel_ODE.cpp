#include <iostream>

using namespace std;
/* El siguiente codigo utiliza leapfrog para resolver la ecuacion diferencial de segundo orden, para dar el primer paso utiliza el metodo de euler */
int main()
{
  float Bx = 0.0;
  float By = 0.0;
  float Bz = 3.0;
  float v0x = 0.0;
  float v0y = 1.0;
  float v0z = 2.0;
  float x0 = 1.0;
  float y0 = 0.0;
  float z0 = 0.0;
  float m = 2.5;
  float q = 1.5;
  float dt = 0.001;
  float tf = 7.0;
  int n = tf/dt;
  float x[n];
  float y[n];
  float z[n];
  float vx[n];
  float vy[n];
  float vz[n];
  float ax[n];
  float ay[n];
  float az[n];
  x[0] = x0;
  y[0] = y0;
  z[0] = z0;
  vx[0] = v0x;
  vy[0] = v0y;
  vz[0] = v0z;
  ax[0] = (q/m)*(Bz*vy[0] - By*vz[0]);
  ay[0] = (q/m)*(Bx*vz[0] - Bz*vx[0]);
  az[0] = (q/m)*(By*vx[0] - Bx*vy[0]);
  for(int i = 0; i<n; i++)
    {
      if(i==0)
	{
	  x[i+1] = dt*vx[i] + x[i];
	  y[i+1] = dt*vy[i] + y[i];
	  z[i+1] = dt*vz[i] + z[i];
	  vx[i+1] = dt*(q/m)*(Bz*vy[i] - By*vz[i]) + vx[i];
	  vy[i+1] = dt*(q/m)*(Bx*vz[i] - Bz*vx[i]) + vy[i];
	  vz[i+1] = dt*(q/m)*(By*vx[i] - Bx*vy[i]) + vz[i];
	  
	}
      else
	{
	  ax[i] = (q/m)*(Bz*vy[i] - By*vz[i]);
	  ay[i] = (q/m)*(Bx*vz[i] - Bz*vx[i]);
	  az[i] = (q/m)*(By*vx[i] - Bx*vy[i]);
	  vx[i+1] = ax[i]*2.0*dt + vx[i-1];
	  vy[i+1] = ay[i]*2.0*dt + vy[i-1];
	  vz[i+1] = az[i]*2.0*dt + vz[i-1];
	  x[i+1] = vx[i]*2.0*dt + x[i-1];
	  y[i+1] = vy[i]*2.0*dt + y[i-1];
	  z[i+1] = vz[i]*2.0*dt + z[i-1];
	  

	}



    }
  for(int j = 0; j < n; j++)
    {

      cout << j*dt <<" " << x[j] << " " << y[j] << " " << z[j] <<endl;



    }





  return 0;
}
