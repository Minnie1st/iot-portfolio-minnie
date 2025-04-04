from iotknit import *
import time

init("localhost")  # 连接到本地 MQTT broker
prefix("temp-measure")  # 和你原来的控制器保持一致

temp_pub = publisher("temp1")  # 发布到 topic: temp-measure/temp1

temperature = 22  # 初始温度
increasing = True  # 升温方向控制

while True:
    # 发送温度
    print(f"Publishing temperature: {temperature}")
    temp_pub.publish(str(temperature))

    # 控制温度升降
    if increasing:
        temperature += 1
        if temperature >= 30:
            increasing = False
    else:
        temperature -= 1
        if temperature <= 22:
            increasing = True

    time.sleep(2)  # 每2秒发一次
