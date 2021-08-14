import time
import serial  # 导入模块

# 串口读写模块
try:
    port = "COM4"  # 端口，GNU / Linux上的/ dev / ttyUSB0 等 或 Windows上的 COM3 等
    bps = 115200 # 波特率，标准值之一：50,75,110,134,150,200,300,600,1200,1800,2400,4800,9600,19200,38400,57600,115200
    timex = 5 # 超时设置,None：永远等待操作，0为立即返回请求结果，其他值为等待超时时间(单位为秒）

    # 打开串口，并得到串口对象
    ser = serial.Serial(port, bps, timeout=timex)
    print("串口详情参数：", ser)

    print(ser.port)  # 获取到当前打开的串口名
    print(ser.baudrate)  # 获取波特率

    # 循环接收数据，此为死循环，可用线程实现 这个是uart转sbus的协议，
    data_write = bytes([0x0F, 0x00, 0xAE, 0x04, 0x58, 0x02, 0x3A, 0x07, 0xF8, 0x07, 0xEA, 0x00, 0x08, 0x04, 0x04
                           , 0x04, 0x04, 0x04, 0x00, 0x04, 0x00, 0x04, 0x00, 0x04, 0x00, 0x04, 0x00, 0x04, 0x00
                           , 0x04, 0x00, 0x04, 0x00, 0x00, 0xD0])
    while True:
        time.sleep(0.050)
        ser.write(data_write)

except Exception as e:
    ser.close()  # 关闭串口
    print("---异常---：", e)
