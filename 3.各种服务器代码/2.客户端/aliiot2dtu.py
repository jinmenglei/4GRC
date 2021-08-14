from linkkit import linkkit
import logging
import threading
import time


# config log
__log_format = '%(asctime)s-%(process)d-%(thread)d - %(name)s:%(module)s:%(funcName)s - %(levelname)s - %(message)s'
logging.basicConfig(format=__log_format)

lk = linkkit.LinkKit(
    host_name="cn-shanghai",
    product_key="xxxxxxxx",
    device_name="xxxxxxxx",
    device_secret="xxxxxxxxxxxxxxx")
lk.enable_logger(logging.INFO)


def on_device_dynamic_register(rc, value, userdata):
    if rc == 0:
        print("dynamic register device success, value:" + value)
    else:
        print("dynamic register device fail, message:" + value)


def on_connect(session_flag, rc, userdata):
    print("on_connect:%d,rc:%d" % (session_flag, rc))
    pass


def on_disconnect(rc, userdata):
    print("on_disconnect:rc:%d,userdata:" % rc)


def on_topic_message(topic, payload, qos, userdata):
    print("on_topic_message:" + topic + " payload:" + str(payload) + " qos:" + str(qos))
    pass


def on_subscribe_topic(mid, granted_qos, userdata):
    print("on_subscribe_topic mid:%d, granted_qos:%s" %
          (mid, str(','.join('%s' % it for it in granted_qos))))
    pass


def on_unsubscribe_topic(mid, userdata):
    print("on_unsubscribe_topic mid:%d" % mid)
    pass


def on_publish_topic(mid, userdata):
    print("on_publish_topic mid:%d" % mid)


lk.on_device_dynamic_register = on_device_dynamic_register
lk.on_connect = on_connect
lk.on_disconnect = on_disconnect
lk.on_topic_message = on_topic_message
lk.on_subscribe_topic = on_subscribe_topic
lk.on_unsubscribe_topic = on_unsubscribe_topic
lk.on_publish_topic = on_publish_topic


lk.config_device_info("Eth|03ACDEFF0032|Eth|03ACDEFF0031")
lk.connect_async()
lk.start_worker_loop()


def iot_send():
    while True:
        # qos = 0 的时候不要大于10hz
        time.sleep(0.01)
        rc, mid = lk.publish_topic(lk.to_full_topic("test"), bytes([0xAA, 0xBB, 0xCC, 0xDD]))
        if rc == 0:
            print("publish topic success:%r, mid:%r" % (rc, mid))
        else:
            print("publish topic fail:%d" % rc)


iot_task = threading.Thread(target=iot_send, args=())
iot_task.start()

while True:
    time.sleep(1)
