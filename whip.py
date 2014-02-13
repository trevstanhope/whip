"""
Whip.py
Concise tool for managing
"""

import serial, os, ast

class whip:

    # Initialize system
    def __init__(self):
        self.slaves = {}

    # Load a controllers configuration file
    def load(self, configfile='default.cfg'):
        config = open(os.path.abspath(configfile), 'r')
        self.slaves = ast.literal_eval(config)
        
    # Connect controller
    def connect(self, name='temp', baud='9600', dev='COM5'):
        socket = serial.Serial(dev, baud)
        self.slaves[name] = {'socket':socket,
                                  'commands':[],
                                  'name':name,
                                  'baud':baud,
                                  'dev':dev}

    # Add command for an action
    def add(self, command, name='temp'):
        self.slaves[name]['commands'].append(command)

    # Do action
    def do(self, command, name='temp'):
        if command in self.slaves[name]['commands']:
            self.slaves[name]['socket'].write(command)
        else:
            raise Exception('Unknown command')

    # Check status of a controller
    def status(self, name='temp'):
        if name in self.slaves:
            try:
                return self.slaves[name]['socket'].readline()
            except Exception as error:
                return None
        else:
            raise Exception('Unknown controller')

    # List commands of a controller
    def commands(self, name='temp'):
        print(self.slaves[name]['commands'])

    # Disconnect from controllers
    def disconnect(self,names=None):
        if names:
            for conn in names:
                self.slaves[name]['socket'].close()
        else:
            for conn in self.slaves:
                self.slave[conn]['socket'].close()    
        
        
    
