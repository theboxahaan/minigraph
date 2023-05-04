import matplotlib.pyplot as plt
from matplotlib.patches import Rectangle



if __name__ == '__main__':
  with open('rec.log', 'r') as fd:
    s = []
    for l in fd.readlines():
      s.append(l.split(',')[:-1])
  fig, ax = plt.subplots()
  ax.plot([-85,-86], [40,41])
  i = 0
  for x, x_len, y, y_len in s:
    if i != 0:
      ax.add_patch(Rectangle((float(x), float(y)), float(x_len), float(y_len), facecolor='none', edgecolor='red'))
    else:
      ax.add_patch(Rectangle((float(x), float(y)), float(x_len), float(y_len), facecolor='none', edgecolor='blue'))
  plt.show()
 

