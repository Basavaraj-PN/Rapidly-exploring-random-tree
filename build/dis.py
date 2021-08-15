
# import matplotlib.pyplot as plt
# image = plt.imread('/home/ravishankar/RRT/binMap.png')
# plt.imshow(image)

# import matplotlib.pyplot as plt
# import matplotlib.image as img

# image = img.imread('/home/ravishankar/RRT/binMap.png')
# plt.imshow(image)
# plt.show()

import matplotlib.pyplot as plt
from PIL import Image

image = Image.open('/home/ravishankar/RRT/binMap.png')
plt.imshow(image)
plt.show()