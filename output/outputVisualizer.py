from matplotlib import pyplot as plt
import numpy as np
import sys

def parseArgs():
    '''
    Function to parse command line arguments
    '''

    help_msg = """\
usage: python outputVisualizer.py <file_to_visualize> [options]

positional arguments:
    file_to_visualize    the file to visualize

optional arguments:
    -h, --help           show this help message and exit
    -s, --save           save the plot to a file
    -n, --no-show        do not show the plot"""

    output_filename = None
    no_show = False

    if len(sys.argv) < 2:
        print(help_msg)
        sys.exit(0)
    
    if sys.argv[1] in ['-h', '--help']:
        print(help_msg)
        sys.exit(0)
    
    input_filename = sys.argv[1]

    argv_index = 2

    while True:
        if argv_index >= len(sys.argv):
            break

        if sys.argv[argv_index] in ['-s', '--save']:
            output_filename = sys.argv[argv_index + 1]
            argv_index += 2
            continue

        if sys.argv[argv_index] in ['-n', '--no-show']:
            no_show = True
            argv_index += 1
            continue
    
    return input_filename, output_filename, no_show

def main():

    # Parse arguments
    input_filename, output_filename, no_show = parseArgs()

    # Read input file
    with open(input_filename, 'r') as f:
        width, height = f.readline().split(',')
        width = int(width)
        height = int(height)

        pixel_data = []
        for line in f.readlines():
            pixel_data.append([float(x) for x in line.split(',')])
        pixels = np.array(pixel_data)

        pixels = pixels.reshape((height, width, 3))

    # Plot the image
    plt.matshow(pixels)

    # Save the image
    if output_filename is not None:
        plt.savefig(output_filename)

    # Show the image
    if not no_show:
        plt.show()


if __name__ == '__main__':
    main()
