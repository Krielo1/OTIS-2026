import pandas as pd
import matplotlib.pyplot as plt
import os

csv_path = 'build/simulation_results.csv'
if not os.path.exists(csv_path):
    csv_path = 'simulation_results.csv' 

try:
    df = pd.read_csv(csv_path)
except FileNotFoundError:
    print("Ошибка: Сначала запустите build.bat, чтобы создать simulation_results.csv")
    exit()

models = df['Model'].unique()

fig, axes = plt.subplots(1, 3, figsize=(18, 5))
fig.suptitle('Результаты моделирования (Вариант 27)', fontsize=16)

for i, model_name in enumerate(models):
    ax = axes[i]
    model_data = df[df['Model'] == model_name]
    
    for signal in model_data['Signal'].unique():
        sig_data = model_data[model_data['Signal'] == signal]
        ax.plot(sig_data['Step'], sig_data['y'], label=signal)
    
    ax.set_title(model_name)
    ax.set_xlabel('Шаг (t)')
    ax.set_ylabel('Выход y(t)')
    ax.legend()
    ax.grid(True)

plt.tight_layout()
plt.savefig('doc/graphs/plot_results.png') 
print("Графики сохранены в doc/graphs/plot_results.png")
plt.show()