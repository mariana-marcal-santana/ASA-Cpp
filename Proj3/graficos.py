import matplotlib.pyplot as plt

# Dados fornecidos
num_toys_sets = [1500, 6000, 11500, 17000, 22500, 28000, 33500, 39000, 44500, 50000, 55500, 61000, 66500, 72000, 77500]
time_values = [0.1728, 0.7266, 1.9214, 3.3728, 5.2790, 8.5032, 11.3131, 14.1684, 18.8155, 20.8724, 21.7322, 25.0563, 29.1044, 33.1525, 37.4927]

# Criar o gráfico com pontos unidos por linhas
plt.figure(figsize=(10, 6))
plt.plot(num_toys_sets, time_values, marker='o', linestyle='-', color='b')

# Adicionar rótulos e título

plt.xlabel('NºToys + NºSets')
plt.ylabel('Time (s)')

# Exibir o gráfico
plt.grid(True)
plt.show()
