#!/usr/bin/python
#
# command line API for controlling USB extension cord.
#

import sys
import usbpwrctrl

def printHelp():
    print(sys.argv[0] + " <device> <options>")
    print("where options are:")
    print("\tver                - prints version")
    print("\tset N {on|off}     - sets port N to on/off state")
    print("\tdefaulf N {on|off} - sets default port N state to on/off")
    print("\tports              - prints current ports' states")
    print("\tdefaults           - prints default ports' states")

def parseOnOff(str):
    if str=="on":
        return True
    else:
        if str=="off":
            return False
    printHelp()
    sys.exit(3)

def printStates(lst):
    for e in lst:
        if e:
            sys.stdout.write("on ")
        else:
            sys.stdout.write("off ")
    sys.stdout.write("\n")


# basic sanity check
if len(sys.argv)<1+2:
    printHelp()
    sys.exit(1)

# device init
dev=usbpwrctrl.Protocol(sys.argv[1])

#
# parse commands
#

if sys.argv[2]=="ver" and len(sys.argv)==1+2:
    print( dev.versionStr() )
    sys.exit(0)

if sys.argv[2]=="set" and len(sys.argv)==1+2+2:
    dev.set(int(sys.argv[3]), parseOnOff(sys.argv[4]))
    sys.exit(0)

if sys.argv[2]=="default" and len(sys.argv)==1+2+2:
    dev.setDefault(int(sys.argv[3]), parseOnOff(sys.argv[4]))
    sys.exit(0)

if sys.argv[2]=="ports" and len(sys.argv)==1+2:
    printStates( dev.status() )
    sys.exit(0)

if sys.argv[2]=="defaults" and len(sys.argv)==1+2:
    printStates( dev.statusDefault() )
    sys.exit(0)

# no matchin option
printHelp()
sys.exit(2)
