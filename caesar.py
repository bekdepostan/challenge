import sys
import string

if __name__ == "__main__":

    input_string = sys.argv[1]
    shift = int(sys.argv[2])

    output_string = ""

    for i in input_string:
        char = i.lower()
        if char in string.ascii_lowercase:
            char = chr(((ord(char) - ord('a') + shift) % 26) + ord('a'))
        output_string += char

    print 'Output string is ' + output_string
