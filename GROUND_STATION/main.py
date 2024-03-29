from api import *
from com import *

from typing import List


class GroundStation:
    def __init__(self):
        self.distress_calls: List[DistressCall] = []

    def run(self):
        while True:
            msg = readline()
            
            if msg != bytes('', 'utf-8'):
                msg = msg.decode("utf-8")

                if msg[0] == "D":
                    self.distress_calls.append(DistressCall.from_new_distress_call(msg))
                    write_serial(self.distress_calls[-1].secret_key)
                    print("New upcoming distress Call")
                elif msg[0] == "U":
                    msg = msg[1:].split(" ")

                    latitude, longitude, code, secret_key = float(msg[0]), float(msg[1]), int(msg[2]), msg[3]

                    for call in self.distress_calls:
                        if call.secret_key == secret_key:
                            call.cordinates.latitude = latitude
                            call.cordinates.longitude = longitude
                            call.details += "," + code

                            update(secret_key, call.cordinates, code)
                            break
                else:
                    print(msg)



station = GroundStation()

station.run()