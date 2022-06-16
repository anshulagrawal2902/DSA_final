from PIL import Image 

f = open("Qimage1.txt")
List = []
data = f.read()
lst = (data.split())
lst = list(map(int, lst))

#write Name of original bitmap file
image = Image.open('image1.bmp')
image_rgb = image.convert('RGB')
pixels = image.load()
width, height = image.size
lst = bytes(lst)
img = Image.frombytes('RGB', (int(width), int(height)), lst)
img.save("Qimage1.png")
# img.show()

