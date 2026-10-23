import pandas as pd
import matplotlib.pyplot as plt
import os
import tkinter as tk
from tkinter import ttk

csv_path = 'build/simulation_results.csv'
if not os.path.exists(csv_path):
    csv_path = 'simulation_results.csv'

try:
    df = pd.read_csv(csv_path)
except FileNotFoundError:
    print("Ошибка: Файл simulation_results.csv не найден.")
    exit()

def show_plot():
    models = df['Model'].unique()
    fig, axes = plt.subplots(1, len(models), figsize=(10 * len(models), 6), num="График")
    fig.suptitle('Результаты моделирования (Вариант 27)', fontsize=16)

    if len(models) == 1:
        axes = [axes]

    for i, model_name in enumerate(models):
        ax = axes[i]
        model_data = df[df['Model'] == model_name]
        
        for signal in model_data['Signal'].unique():
            sig_data = model_data[model_data['Signal'] == signal]
            ax.plot(sig_data['Step'], sig_data['y'], label=signal, linewidth=2)
        
        ax.set_title(model_name, fontsize=14)
        ax.set_xlabel('Шаг (t)', fontsize=12)
        ax.set_ylabel('Выход y(t)', fontsize=12)
        ax.legend(fontsize=12)
        ax.grid(True, linestyle='--', alpha=0.7)

    plt.tight_layout()
    plt.savefig('doc/graphs/plot_results.png') 
    plt.show()

root = tk.Tk()
root.title("Результаты симуляции")
root.geometry("900x700")

btn = tk.Button(root, text="Показать график", command=show_plot, font=("Arial", 12), bg="#4CAF50", fg="white")
btn.pack(pady=10)

frame = ttk.Frame(root)
frame.pack(fill='both', expand=True, padx=10, pady=10)

scrollbar = ttk.Scrollbar(frame)
scrollbar.pack(side='right', fill='y')

tree = ttk.Treeview(frame, yscrollcommand=scrollbar.set)
tree.pack(side='left', fill='both', expand=True)
scrollbar.config(command=tree.yview)

columns = ['Model', 'Signal', 'Step', 'u', 'y']
tree['columns'] = columns
tree['show'] = 'headings'

for col in columns:
    tree.heading(col, text=col)
    tree.column(col, width=100, anchor='center')

for _, row in df[columns].iterrows():
    tree.insert('', 'end', values=list(row))

print("Окно с таблицей открыто. Нажмите кнопку, чтобы увидеть график.")
root.mainloop()