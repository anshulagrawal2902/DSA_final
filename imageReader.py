from PIL import Image 
from colour import Color

file1 = open("image1.txt", "w")
image = Image.open('image1.bmp')
image_rgb = image.convert('RGB')

pixels = image.load()
width, height = image.size


for j in range( int (height)):
        for i in range( int(width)):
            r, g, b = image_rgb.getpixel((i, j))
            string =  str(r) + " " + str(g) + " " + str(b) + " " 
            file1.write(string)

