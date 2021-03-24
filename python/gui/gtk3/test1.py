#!/usr/bin/env python3

import gi
gi.require_version('Gtk', '3.0')
from gi.repository import Gtk


class TestWindow(Gtk.Window):
    
    def __init__(self):
        Gtk.Window.__init__(self, title="TestWindow")

        self.button = Gtk.Button(label="Click Me")
        self.button.connect("clicked", self.on_button_clicked)
        self.add(self.button)

        self.label = Gtk.Label()
        self.label.set_label("Test")
        self.add(self.label)
        self.count=0

    def on_button_clicked(self, widget):
        print("Hello World")
        self.count = self.count + 1
        self.label.set_label("" + self.count)



win = TestWindow()
win.connect("destroy", Gtk.main_quit)
win.show_all()
Gtk.main()
