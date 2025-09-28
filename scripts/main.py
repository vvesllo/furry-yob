from PIL import Image


image = Image.open("map.png")
out_string = ""

for i in range(25):
    for j in range(25):
        if (image.getpixel((j, i)) == (0, 0, 0, 255)):
            out_string += "1"
        else:
            out_string += "0"

    out_string += "\n"

print(out_string)

