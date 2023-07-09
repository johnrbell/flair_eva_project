var gateway = `ws://${window.location.hostname}/ws`;
var websocket;

// === === === === === === === === === === === === ===
// WebSocket Initilization
// === === === === === === === === === === === === ===
window.addEventListener('load', onLoad);
function onLoad(event){initWebSocket();}

// === === === === === === === === === === === === ===
// WebSocket Handling
// === === === === === === === === === === === === ===
function initWebSocket() {
    console.log('Trying to open a WebSocket connection...');
    websocket = new WebSocket(gateway);
    websocket.onopen  = onOpen;
    websocket.onclose = onClose;
}

function onOpen(event) {
    console.log('Connection opened');
}

function onClose(event) {
    console.log('Connection closed');
    setTimeout(initWebSocket, 2000);
}