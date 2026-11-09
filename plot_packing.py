import matplotlib.pyplot as plt
import pandas as pd

lx, ly = 100, 200
df = pd.read_csv("packing.csv")

fig, ax = plt.subplots(figsize=(8, 16))
ax.set_aspect('equal')

for _, row in df.iterrows():
    circle = plt.Circle((row['x'], row['y']), row['R'],
                        edgecolor='b', facecolor='none', lw=1)
    ax.add_patch(circle)

ax.set_xlim(0, lx)
ax.set_ylim(0, ly)
ax.set_xlabel('x')
ax.set_ylabel('y')

plt.show()