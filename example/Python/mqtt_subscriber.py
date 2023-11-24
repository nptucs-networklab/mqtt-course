'''
Author: 咪路 <mail@mirumo.org>
License: MIT (https://opensource.org/license/mit/)
'''

import paho.mqtt.client as mqtt

brokerHost = '127.0.0.1'
brokerPort = 1883
topics = [
]

def onConnect(client, userData, flag, rc):
    print('Connected to mqtt broker')
    for topic in topics:
        client.subscribe('TEST')

def onMessage(client, userData, packet):
    topic = packet.topic
    msg = packet.payload.decode('utf-8')
    print(f'{topic}: {msg}')

client = mqtt.Client()

client.on_connect = onConnect
client.on_message = onMessage


client.connect(brokerHost, brokerPost)
client.loop_forever()

