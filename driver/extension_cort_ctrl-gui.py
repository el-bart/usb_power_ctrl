#!/usr/bin/python
#
# GUI API for controlling USB extension cord.
#

import sys
import usbpwrctrl
import pygtk
pygtk.require('2.0')
import gtk

# default device to be used to communicate
defaultDevice="/dev/ttyUSB0"

def helpScreen():
    print(sys.argv[0])
    print("or")
    print(sys.argv[0] + " <device>")
    print("\nnote: if not specified, by default " + defaultDevice + " is used")
    sys.exit(1)

def boolToOnOff(state):
    if state:
        return "On"
    else:
        return "Off"

# basic sanity check
if len(sys.argv)==2 and ( sys.argv[1]=="--help" or sys.argv[1]=="-h" ):
    helpScreen()
if len(sys.argv)!=1 and len(sys.argv)!=2:
    helpScreen()

# choose proper device
if len(sys.argv)==2:
    device=sys.argv[1]
else:
    device=defaultDevice


#
# GUI creation
#
class MainWindow:
    def __init__(self):
        # device to communicate with
        dev = self._dev()

        # Create a new window
        self._window = gtk.Window(gtk.WINDOW_TOPLEVEL)
        self._window.set_title("USB pwr ctrl: " + device + " " + dev.versionStr() )
        self._window.connect("delete_event", self._delete_event)
        self._window.set_border_width(10)

        # top box for ports switches
        boxPorts = gtk.HBox(False, 10)
        boxPorts.show()
        self._window.add(boxPorts)

        # insert labels to the buttons
        box = gtk.VBox(False, 0)
        boxPorts.add(box)
        box.show()
        # empty space
        lab = gtk.Label("")
        box.pack_start(lab, True, True, 0)
        lab.show()
        # label for ports
        lab = gtk.Label("Current")
        box.pack_start(lab, True, True, 0)
        lab.show()
        # label for defaults
        lab = gtk.Label("Default")
        box.pack_start(lab, True, True, 0)
        lab.show()

        # read settings and current states from the device
        stateCurrent = dev.status()
        stateDefault = dev.statusDefault()

        # vbox for each port (0 to number of ports returned from the device)
        for i in range(0, len(stateCurrent)):
            # insert separator, only for non-first element
            if i>0:
                sep = gtk.VSeparator()
                boxPorts.add(sep)
                sep.show()
            # make vertical box
            box = gtk.VBox(False, 3)
            boxPorts.add(box)
            box.show()
            # add a label
            lab = gtk.Label("Port " + str(i))
            box.pack_start(lab, True, True, 0)
            lab.show()
            # add port button
            butPort = gtk.ToggleButton( boolToOnOff(stateCurrent[i]) )
            butPort.set_active( stateCurrent[i] )
            butPort.connect("clicked", self._togglePortState, i)
            box.pack_start(butPort, True, True, 2)
            butPort.show()
            # add default button
            butDef = gtk.ToggleButton( boolToOnOff(stateDefault[i]) )
            butDef.set_active( stateDefault[i] )
            butDef.connect("clicked", self._toggleDefaultState, i)
            box.pack_start(butDef, True, True, 0)
            butDef.show()

        # make main window visible now
        self._window.show()


    def _dev(self):
        return usbpwrctrl.Protocol(device)


    # changes given port's state to the oposite value
    def _togglePortState(self, widget, data):
        dev = self._dev()
        st  = not dev.status()[data]
        dev.set(data, st)
        widget.set_label( boolToOnOff(st) )


    # changes given port's default state to the oposite value
    def _toggleDefaultState(self, widget, data):
        dev = self._dev()
        st  = not dev.statusDefault()[data]
        dev.setDefault(data, st)
        widget.set_label( boolToOnOff(st) )


    # window delete
    def _delete_event(self, widget, event, data=None):
        gtk.main_quit()
        return False


# init main window
mw = MainWindow()
# run GUI
gtk.main()
