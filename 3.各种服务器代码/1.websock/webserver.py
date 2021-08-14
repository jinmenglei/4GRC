import asyncio
import websockets


# 这是客户端list 简单的发送给另一个，不带注册功能
list_wc = []


async def recv_msg(websocket):
    if websocket not in list_wc:
        print("websocket client " + str(websocket))
        list_wc.append(websocket)
    while True:
        recv_text = await websocket.recv()
        for index in list_wc:
            if index != websocket:    
                await websocket.send(recv_text)


async def main_logic(websocket, path):
    await recv_msg(websocket)

# 把ip换成自己本地的ip，最好是在服务器上，新人开服务器才不到100一年，1m完全沟通
start_server = websockets.serve(main_logic, '0.0.0.0', 5678)

asyncio.get_event_loop().run_until_complete(start_server)
asyncio.get_event_loop().run_forever()
