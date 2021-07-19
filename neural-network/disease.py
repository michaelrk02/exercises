import math
import numpy as np

symptoms = np.array([[
    float(input('Merasakan batuk? (0/1) ')), # Batuk
    float(input('Merasakan kelelahan? (0/1) ')), # Kelelahan
    float(input('Merasakan demam? (0/1) ')), # Demam
    float(input('Merasakan sakit kepala? (0/1) ')), # Sakit kepala
    float(input('Merasakan kehilangan penciuman? (0/1) ')), # Kehilangan penciuman
    float(input('Merasakan sesak napas? (0/1) ')) # Sesak napas
]]).transpose()

weights = np.array([
    [0.0, 2.0, 2.0, 4.0, 0.0, 0.0],
    [2.0, 2.0, 2.0, 0.0, 4.0, 4.0]
])

bias = -5.0

sigmoid = lambda x: 1.0 / (1.0 + math.exp(-x))
input_layer = np.append(symptoms, [[1.0]], 0)
network = np.append(weights, [[bias], [bias]], 1)

output_layer = np.matmul(network, input_layer)

for i in range(0, 2):
    output_layer[i][0] = sigmoid(output_layer[i][0])

print("Kemungkinan menderita flu: %.4f" % (output_layer[0][0]))
print("Kemungkinan menderita COVID-19: %.4f" % (output_layer[1][0]))

