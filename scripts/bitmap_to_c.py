import argparse
import logging
from PIL import Image 


def print_ascii(mono_pixels: list[list[bool]]):
    for row in mono_pixels:
        for pixel in row:
            if pixel:
                print('o', end='')
            else:
                print('_', end='')
        print('')


def print_c(mono_pixels: list[list[bool]]):
    print('{')
    for row_index, row in enumerate(mono_pixels):
        data = 0
        col_index = 0
        print('\t{', end='')

        while col_index < len(row):
            if row[col_index]:
                data = data | (1 << (7 - col_index % 8))
            if col_index % 8 == 7:
                # Current byte is complete. Print it
                print(f'0x{data:02x}', end='')
                if col_index < len(row) - 1:
                    # Print delimiter if not last column in row
                    print(', ', end='')
                data = 0
            col_index += 1

        print('}', end='')
        if row_index < len(mono_pixels) - 1:
            # Print delimiter if not last row
            print(',', end='')
        print()

    print('}')


def process(image_path: str):
    img = Image.open(image_path)
    width = img.size[0]
    height = img.size[1]
    pixels = list(img.getdata())

    mono_pixels = [[None for i in range(width)] for j in range(height)]
    for (pixel_index, pixel_value) in enumerate(pixels):
        col_index = pixel_index % width
        row_index = pixel_index // width

        mono_pixels[row_index][col_index] = not (pixel_value == (255, 255, 255))

    # print_ascii(mono_pixels)
    print_c(mono_pixels)


def main():
    parser = argparse.ArgumentParser(
        prog='bitmap_to_c',
        description='Script to convert bitmap images to C arrays'
    )
    parser.add_argument('--img',
        required=True,
        help='Bitmap image to convert'
    )
    args = parser.parse_args()
    logging.basicConfig(level='INFO')

    process(args.img)


if __name__ == "__main__":
    main()