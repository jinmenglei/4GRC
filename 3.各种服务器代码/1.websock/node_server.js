const WebSocket = require('ws')
const wsServer = new WebSocket.Server({ port: 5678 })

//ws client 列表
var list_ws = new Array();
wsServer.on('connection', (ws, req) => {
	let clientId = req.headers['sec-websocket-key']
	list_ws[clientId] = ws
	console.log(`client ${clientId} connected.`)

	ws.on('message', (message) => {
		handle(ws, message, wsClients[clientId])
	})

	ws.on('close', (message) => {
		console.log(`client ${clientId} closed.`)
		delete wsClients[clientId]
		delete list_ws[clientId]
	})
})

// handle message of the specific client and emit
function handle(ws, message, state) {
	//console.log(message.content)
	let shouldClose = false
	for (var index_ws in list_ws){
		if (list_ws[index_ws] !== ws){
			list_ws[index_ws].send(String(message))
		}
	}
	console.log(message)
	if (shouldClose) ws.close()	// 无话可说, 主动告辞
}
