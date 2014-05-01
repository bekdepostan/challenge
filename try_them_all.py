import os
import sys
import string
import hashlib

if __name__ == "__main__":

    input_file = sys.argv[1]
    hashed_password = sys.argv[2].lower()
    salt = sys.argv[3].lower()

    print '[DEBUG] hashed password is ' + hashed_password
    print '[DEBUG] salt is ' + salt

    f = open(input_file, 'r')
    for line in f:
        # os.linesep == <LF> for Unix ('\n')
        line = line.strip(os.linesep)
        if hashlib.md5(line + salt).hexdigest() == hashed_password:
            print '[SUCCESS] Plain text password is ' + line
            f.close()
            sys.exit(0)

    f.close()
    print '[FAILURE] Can not find plain text password for the hash ' + hashed_password + ' with salt ' + salt
