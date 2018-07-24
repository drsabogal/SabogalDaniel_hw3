import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
matriz = np.genfromtxt("particula.txt", usecols = (0,1,2,3))
t = matriz[:,0]
x = matriz[:,1]
y = matriz[:,2]
z = matriz[:,3]
#se crean las primeras figuras tomadas del punto 1
plt.figure()
ax = plt.axes(projection = '3d')
ax.plot3D(x,y,z)
plt.savefig("ODE.pdf")

plt.figure()
plt.plot(x,y)
plt.savefig("ODE1.pdf")

plt.figure()
plt.plot(x,z)
plt.savefig("ODE2.pdf")

plt.figure()
plt.plot(t,y)
plt.savefig("ODE3.pdf")
#se crean las feguras del punto dos, para este caso se tiene en cuenta las condiciones de frontera y para los cortes se utilizan subplots
matriz1 = np.genfromtxt("parcial.txt",delimiter = ",", usecols = (0,1,2,3,4,5,6,7,8,9,10,11,12))
z1i = matriz1[:,0]
z1c = matriz1[:,1]
z1a = matriz1[:,2]
x1 = matriz1[:,3]
y1 = matriz1[:,4]
corte10 = matriz1[:,5]
corte150 = matriz1[:,6]
corte1100 = matriz1[:,7]
corte1150 = matriz1[:,8]
corte20 = matriz1[:,9]
corte250 = matriz1[:,10]
corte2100 = matriz1[:,11]
corte2150 = matriz1[:,12]
corteP0 = corte10[0:99]
corteP50 = corte150[0:99]
corteP100 = corte1100[0:99]
corteP150 = corte1150[0:99]
corte2P0 = corte20[0:97]
corte2P50 = corte250[0:97]
corte2P100 = corte2100[0:97]
corte2P150 = corte2150[0:97]

plt.figure()
ax = plt.axes(projection = '3d')
ax.plot3D(x1,y1,z1i)
plt.savefig("PDE.pdf")

plt.figure()
ax = plt.axes(projection = '3d')
ax.plot3D(x1,y1,z1c)
plt.savefig("PDE1.pdf")

plt.figure()
ax = plt.axes(projection = '3d')
ax.plot3D(x1,y1,z1a)
plt.savefig("PDE2.pdf")

plt.figure()
plt.subplot(2,2,1)
plt.plot(corteP0)
plt.subplot(2,2,2)
plt.plot(corteP50)
plt.subplot(2,2,3)
plt.plot(corteP100)
plt.subplot(2,2,4)
plt.plot(corteP150)
plt.savefig("CORTES1.pdf")

plt.figure()
plt.subplot(2,2,1)
plt.plot(corte2P0)
plt.subplot(2,2,2)
plt.plot(corte2P50)
plt.subplot(2,2,3)
plt.plot(corte2P100)
plt.subplot(2,2,4)
plt.plot(corte2P150)
plt.savefig("CORTES2.pdf")
