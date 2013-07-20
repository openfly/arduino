#!/usr/bin/env python
# matt@nycresistor.com

import sys
import string
import getopt
import serial

__version__ = "0.1"
app_name = "hdsp serial printer"

def sertoard(text4hdsp):
    ser = serial.Serial('/dev/ttyUSB0', 9600)
    print "sending text to hdsp: %s" % (text4hdsp)
    ser.write('$')
    ser.write(text4hdsp)
    ser.write('\r')
    ser.close()

def usage():
    print "use -o flag to set string to be displayed on HDSP2111 chip"

def main():

    # Grab command line arguments
    try:
        opts, args = getopt.getopt(sys.argv[1:], "ho:v", ["help", "output="])
    except getopt.GetoptError, err:
        print str(err)
        usage()
        sys.exit(2)
    output = None
    verbose = False

    for o, a in opts:
        if o == "-v":
            verbose = True
            print "%s - %s" % (app_name, __version__)
        elif o in ("-h", "--help"):
            usage()
            sys.exit()
        elif o in ("-o", "--output"):
            output = a
        else:
            assert False, "unhandled option"
    if (output):
        try:
            sertoard(output)
        except getopt.GetoptError, err:
            print str(err)
            sys.exit(2)

    else:
        sys.exit(2)


if __name__ == "__main__":
    main()


