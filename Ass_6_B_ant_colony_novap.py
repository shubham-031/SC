import random
import math
import pandas as pd
import matplotlib.pyplot as plt

# Recreated user inputs
random.seed(42)
   
paths = ["A->B", "A->C", "A->D"]
tau = [1, 1, 1]                    # initial pheromone
distances = [4.0, 15.0, 1.0]
eta = [1.0 / d for d in distances]        
                                           
alpha = 1.0           
beta = 1.0     
Q = 1.0       
                          
ants_paths_taken = [0, 1, 2]
ants_lengths = [distances[i] for i in ants_paths_taken]
    
# Compute deposit from each ant: Delta_tau = Q / Lk
delta_tau = [0.0] * len(paths)
for ant_idx, path_idx in enumerate(ants_paths_taken):
    Lk = ants_lengths[ant_idx]
    deposit = Q / Lk
    delta_tau[path_idx] += deposit                

# ----- NO VAPOURIZATION (no evaporation) -----   
# tau_updated is simply old tau plus deposits
tau_updated = [tau[i] + delta_tau[i] for i in range(len(paths))]

# Compute transition probabilities for 4th ant
numerators = [(tau_updated[i] ** alpha) * (eta[i] ** beta) for i in range(len(paths))]       
denominator = sum(numerators)
probabilities = [num / denominator for num in numerators]   

# Probabilistic choice for 4th ant    
r = random.random()
cum = 0.0
chosen_index = None
for i, p in enumerate(probabilities):
    cum += p
    if r <= cum:
        chosen_index = i    
        break

# Print table to console
print("Path | init_tau | delta_from_3_ants | tau_after_deposit | eta(1/d) | numerator | probability")
for i in range(len(paths)):
    print(f"{paths[i]:5s} | {tau[i]:8.3f} | {delta_tau[i]:16.6f} | {tau_updated[i]:17.6f} | {eta[i]:7.6f} | {numerators[i]:9.6f} | {probabilities[i]:10.6f}")

# --- Figure 1: pheromones and deposits (grouped bar chart) ---
x = range(len(paths))
width = 0.25

fig1, ax1 = plt.subplots(figsize=(7,4))
ax1.bar([p - width for p in x], tau, width, label='init_tau')
ax1.bar(x, delta_tau, width, label='delta_from_3_ants')
ax1.bar([p + width for p in x], tau_updated, width, label='tau_after_deposit')
ax1.set_xticks(x)
ax1.set_xticklabels(paths)
ax1.set_ylabel("Pheromone / Deposit value")
ax1.set_title("Initial pheromone, deposits from 3 ants, and updated pheromone (without vapourization)")
ax1.legend()
plt.tight_layout()
plt.show()

# --- Figure 2: probabilities for 4th ant ---
fig2, ax2 = plt.subplots(figsize=(7,3))
bars = ax2.bar(paths, probabilities)
ax2.set_ylabel("Probability")
ax2.set_title("Transition probabilities for 4th ant (without vapourization)")
# annotate probability values above bars
for rect, prob in zip(bars, probabilities):
    height = rect.get_height()
    ax2.annotate(f"{prob:.3f}", xy=(rect.get_x() + rect.get_width() / 2, height),
                 xytext=(0, 3), textcoords="offset points", ha="center", va="bottom", fontsize=9)
# mark chosen path
ax2.text(0.95, 0.85, f"Random draw r={r:.4f}\nChosen: {paths[chosen_index]}", transform=ax2.transAxes,
         ha="right", va="top", bbox=dict(boxstyle="round", fc="wheat", alpha=0.5))
plt.tight_layout()
plt.show()

# Print brief summary
print("Random draw (r) = {:.4f}".format(r))
print("Chosen path for 4th ant (probabilistic):", paths[chosen_index])      
print("Highest-probability (deterministic) path:", paths[probabilities.index(max(probabilities))])