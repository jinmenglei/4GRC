#!/usr/bin/env python
#coding=utf-8
import hmac
import base64
from hashlib import sha1
import time
from paho.mqtt.client import MQTT_LOG_INFO, MQTT_LOG_NOTICE, MQTT_LOG_WARNING, MQTT_LOG_ERR, MQTT_LOG_DEBUG
from paho.mqtt import client as mqtt
import logging

__log_format = '%(asctime)s-%(process)d-%(thread)d - %(name)s:%(module)s:%(funcName)s - %(levelname)s - %(message)s'
logging.basicConfig(format=__log_format)
log_ins = logging.getLogger("mqtt")
# 实例 ID，购买后从产品控制台获取
instanceId = 'post-cn-xxxx'

# 账号AccessKey 从阿里云账号控制台获取
accessKey = 'xxxxxxxx'

# 账号secretKey 从阿里云账号控制台获取
secretKey = 'xxxxxxxxxx'

# MQTT GroupID,创建实例后从 MQTT 控制台创建
groupId = 'xxxxxxxxx'

# MQTT ClientID，由 GroupID 和后缀组成，需要保证全局唯一替换xxxx就行，别把@@@给改了
client_id=groupId+'@@@'+'xxxxxxxx'

# Topic， 其中第一级父级 Topic 需要从控制台创建
topic = 'xxxxx'

# MQTT 接入点域名，实例初始化之后从控制台获取
brokerUrl='xxxxxxxxx'


def on_log(client, userdata, level, buf):
    if level == MQTT_LOG_INFO:
        head = 'INFO'
    elif level == MQTT_LOG_NOTICE:
        head = 'NOTICE'
    elif level == MQTT_LOG_WARNING:
        head = 'WARN'
    elif level == MQTT_LOG_ERR:
        head = 'ERR'
    elif level == MQTT_LOG_DEBUG:
        head = 'DEBUG'
    else:
        head = level
    print('%s: %s' % (head, buf))


def on_connect(client, userdata, flags, rc):
    print('Connected with result code ' + str(rc))
    client.subscribe(topic, 0)
    # 用publish发送，qos=0不要超过10hz，这个的数据过来的时候不是顺序的，不好用
    # for i in range(1, 11):
    #     print(i)
    #     rc = client.publish(topic, str(str(i) + "123456789"), qos=0)
    #     print ('rc: %s' % rc)
    #     time.sleep(0.1)


def on_message(client, userdata, msg):
    print(msg.topic + ' ' + str(msg.payload))


def on_disconnect(client, userdata, rc):
    if rc != 0:
        print('Unexpected disconnection %s' % rc)


client = mqtt.Client(client_id, protocol=mqtt.MQTTv311, clean_session=True)
client.on_log = on_log
client.on_connect = on_connect
client.on_message = on_message
client.on_disconnect = on_disconnect
# username和 Password 签名模式下的设置方法，参考文档 https://help.aliyun.com/document_detail/
# 48271.html?spm=a2c4g.11186623.6.553.217831c3BSFry7
userName ='Signature'+'|'+accessKey+'|'+instanceId
password = base64.b64encode(hmac.new(secretKey.encode(), client_id.encode(), sha1).digest()).decode()
client.username_pw_set(userName, password)
# ssl设置，并且port=8883
#client.tls_set(ca_certs=None, certfile=None, keyfile=None, cert_reqs=ssl.CERT_REQUIRED, tls_version=
# ssl.PROTOCOL_TLS, ciphers=None)
client.connect(brokerUrl, 1883, 60)
client.loop_forever()