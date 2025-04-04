from iotknit import *

init("localhost")  # use a MQTT broker on localhost

prefix("switch")  # all actors below are prefixed with /led

switch = publisher("r1")  # create a Thingi interface that publishes to led/led1

def Callback(msg):
    global led1Status

    print("received: [temp]", msg)
    try:
        t=int(msg)
    except ValueError:
        return
    if (t>=25):
        switch.publish("set", "on")  # publish updated state
        print("sending: [r1]", "on")
    else:
        switch.publish("set", "off")
        print("sending: [r1]", "off")


prefix("temp-measure")  # all sensors below are prefixed with /button

button1 = subscriber("temp1")  # create a Thingi interface that can have
                                 # subscribes only to button/button1
button1.subscribe_change(callback=Callback)

run()  # you can also do a while loop here call process() instead