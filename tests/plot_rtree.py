import matplotlib.pyplot as plt
from matplotlib.patches import Rectangle



if __name__ == '__main__':
  with open('rec.log', 'r') as fd:
    s = []
    for l in fd.readlines():
      s.append(l.split(',')[:-1])
  fig, ax = plt.subplots()
  ax.plot([0,700], [0,700])
  for x, x_len, y, y_len in s:
    ax.add_patch(Rectangle((float(x), float(y)), float(x_len), float(y_len), facecolor='none', edgecolor='red'))
  plt.show()
 

