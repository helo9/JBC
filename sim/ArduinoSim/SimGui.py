import gi
import struct
import zmq
from enum import IntEnum
from functools import partial

gi.require_version("Gtk", "3.0")
from gi.repository import Gtk, GLib

class AnalogPins(IntEnum):
    A0 = 50
    A1 = 51

def main():
    context = zmq.Context()
    socket = context.socket(zmq.REQ)
    socket.connect("tcp://127.0.0.1:5557")

    simcon = Connector(socket)

    handler = Handler(simcon)

    builder = Gtk.Builder()
    builder.add_from_file("sim/ArduinoSim/SimGui.glade")
    builder.connect_signals(handler)

    window = builder.get_object("main_window")

    heater1 = builder.get_object("heater1")
    heater2 = builder.get_object("heater2")

    assert heater1
    assert heater2

    window.show_all()

    updateHeatersFun = partial(
        updateHeaters,
        heater_button1=heater1, 
        heater_button2=heater2,
        get_values=simcon.read_heaters
    )


    GLib.timeout_add(250, updateHeatersFun)
    Gtk.main()

def updateHeaters(heater_button1, heater_button2, get_values):
    h1, h2 = get_values()
    heater_button1.set_state(h1)
    heater_button2.set_state(h2)
    return True


class Handler:

    def __init__(self, simulator_connection):
        self.simulator_connection = simulator_connection

    def onDestroy(self, *args):
        Gtk.main_quit()
    
    def onValueUpdate(self, temperature_spinbutton):
        self.simulator_connection.write_temperature(temperature_spinbutton.get_value())

    def triggerUpdate(self):
        self.simulator_connection.read_heaters()
        return True

class Connector:
    
    def __init__(self, socket):
        self.socket = socket

    def write_temperature(self, temperature: float):
        msg = struct.pack("!cci", b"W", bytes([AnalogPins.A0]), int(temperature))
        self.socket.send(msg)
        self.socket.recv()

    def read_heaters(self):   
        msg = struct.pack("!cc", b"R", bytes([0]))
        self.socket.send(msg)
        heater1_on = self.socket.recv()[-1] > 0
        msg = struct.pack("!cc", b"R", bytes([1]))
        self.socket.send(msg)
        heater2_on = self.socket.recv()[-1] > 0

        return heater1_on, heater2_on

if __name__=="__main__":
    main()
