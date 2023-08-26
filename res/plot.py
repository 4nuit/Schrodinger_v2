import numpy as np
import matplotlib.pyplot as plt

# Charger les données du fichier en utilisant numpy.loadtxt et en spécifiant le délimiteur
data = np.loadtxt('res.mat')

# Convertir les données en une matrice 2D
#matrix = np.reshape(data, (374, 374))
# Afficher la matrice en tant qu'image
#plt.imshow(matrix)
plt.title("Densité nucléaire")
plt.xlabel("z(m)")
plt.ylabel("r(m)")
plt.imshow(data, extent=[-20,20,-10,10])
plt.show()
