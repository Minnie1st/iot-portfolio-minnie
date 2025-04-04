from iotknit import *
import time
import threading

init("localhost")
prefix("switch")   

status = "off"

ac_sub = subscriber("r1")  

def on_message(msg):
    global status
    print(f"Received switch command: {msg}")
    if msg == "on":
        status = "on"
        print("AC is turned on")
    elif msg == "off":
        status = "off"
        print("AC is turned off")

def print_status():
    while True:
        print(f"AC is turned {status}")
        time.sleep(1)

ac_sub.subscribe_change("set", callback=on_message)

# 在单独的线程中运行状态打印
threading.Thread(target=print_status, daemon=True).start()

# 启动事件循环
run()