'''
Title: MQTT Publisher
Author: 咪路 <mail@mirumo.org>
License: MIT (https://opensource.org/license/mit/)
'''

import paho.mqtt.client as mqtt
import time

brokerHost = '127.0.0.1'
brokerPort = 1883
topic = ''
payload = ''

def onConnect(client, userData, flag, rc):
    print('Connected to mqtt broker')
    client.publish(topic, payload)

client = mqtt.Client()
client.on_connect = onConnect

client.connect(brokerHost, brokerPort)
time.sleep(5)
