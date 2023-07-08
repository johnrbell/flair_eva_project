var gateway = `ws://${window.location.hostname}/ws`;
var websocket;

// === === === === === === === === === === === === ===
// initilization
// === === === === === === === === === === === === ===

window.addEventListener('load', onLoad);
function onLoad(event){initWebSocket();}
function initWebSocket(){websocket = new WebSocket(gateway);}