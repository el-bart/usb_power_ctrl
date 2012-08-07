#!/usr/bin/python
#
# module for controlling USB power controller device
#

import re
import serial

#
# class for handling USB power controller device
#
class Protocol:
    # create instance for a given device (ex. "/dev/ttyUSB0")
    def __init__(self, devName):
        self._devName=devName
        self._dev=serial.Serial(port=devName,
                                baudrate=9600,
                                timeout=1)
        if self._dev.isOpen()!=True:
            raise Exception("cannot open device " + self._devName)
        # check for minimal supported version
        v=self.version()
        # version v0.2.0 is sufficient for this driver
        # note - last digit is not checked, since it is just a bugfix
        if not ( int(v[0])>0 or ( int(v[0])==0 and int(v[1])>=2 ) ):
            raise Exception("unsupported version: " + self.versionStr())

    # returns version as a string
    def versionStr(self):
        ret=self.hello()
        lst=ret.split();
        return lst[ len(lst)-1 ]

    # returns version as a list of values
    def version(self):
        return self.versionStr().replace("v","").split(".")

    # sends hello greeting and return an answer
    def hello(self):
        return self._execCmd("hello\n")

    # sets state of a given port to a given state
    # port    - port number
    # powerOn - True/False
    def set(self, port, powerOn):
        self._setImpl("port", port, powerOn)

    # sets default state of a given port to a given state
    # port    - port number
    # powerOn - True/False
    def setDefault(self, port, powerOn):
        self._setImpl("default", port, powerOn)

    # gets status of current port settings
    def status(self):
        return self._statusImpl("port")

    # gets status of default port settings
    def statusDefault(self):
        return self._statusImpl("default")


    def _setImpl(self, op, port, powerOn):
        if powerOn:
            s="on"
        else:
            s="off"
        self._execCmd(op + " " + str(port) + " " + s)

    def _statusImpl(self, op):
        resp=self._execCmd("status " + op)
        r   =re.compile("[0-9]=")
        lst =r.sub("", resp).split()
        lst =[True if e=='on' else False for e in lst]
        return lst

    def _execCmd(self, cmd):
        self._dev.write(cmd + "\n")
        resp=self._dev.readline()
        if resp.split()[0]=="ERROR:":
            raise Exception("unable to communicate with the device - it says: " + resp)
        return resp


# sanity check
if __name__=="__main__":
    raise Exception("this is a module and should NOT be used as a raw script!")
