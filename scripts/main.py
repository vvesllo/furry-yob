from PIL import Image


image = Image.open("map.png")
out_string = ""
size = image.size

for i in range(size[1]):
    for j in range(size[0]):
        if (image.getpixel((j, i)) == (0, 0, 0, 255)):
            out_string += "1"
        elif (image.getpixel((j, i)) == (255, 0, 0, 255)):
            out_string += "2"
        else:
            out_string += "0"

    out_string += "\n"

with open("map.txt", "w") as f:
    print(out_string, file=f)

