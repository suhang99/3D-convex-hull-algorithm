import matplotlib.pyplot as plt

hull_time = []
collision_time = []
x = []

with open('result/hull_time.txt', 'r') as f:
    cnt = 10
    lines = f.readlines()
    for line in lines:
        line = line.strip('\n')
        hull_time.append(round(float(line),3))
        x.append(cnt*cnt)
        cnt += 20
with open('result/collision_time.txt', 'r') as f:
    lines = f.readlines()
    for line in lines:
        line = line.strip('\n')
        collision_time.append(round(float(line),3))

fig, ax = plt.subplots()
ax.plot(x, hull_time)
ax.set(xlabel='#points', ylabel='Time (s)', title='Convex hull algorithm')
fig.savefig('result/hull_time.png')
plt.show()

fig, ax = plt.subplots()
ax.plot(x, collision_time)
ax.set(xlabel='#points', ylabel='Time (s)', title='Collision detection')
fig.savefig('result/collision_time.png')
plt.show()
