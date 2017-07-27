import numpy as np
import matplotlib.pyplot as plt
from matplotlib.patches import Circle

datos=np.loadtxt('map_data.txt')

fig,ax = plt.subplots(1)
ax.set_aspect('equal')

ax.imshow(datos,cmap='gray')

punto=np.loadtxt('output.dat')

x=punto[0]
y=punto[1]
r=punto[2]

circ = Circle((x,y),r,color='r',fill=False)
ax.add_patch(circ)


plt.show()
