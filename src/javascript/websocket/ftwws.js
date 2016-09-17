/*

Overview
- The classes herein facilitate communciation between modern web browsers and Featherweight (FTW) websockets (i.e. sockets of type ws://<address>:<port>) 
- FTW on the LabVIEW side binds a socket (i.e. is the server) to which the browser can connect
- Derive from these classes if desired (see for details: https://developer.mozilla.org/en-US/docs/Web/JavaScript/Introduction_to_Object-Oriented_JavaScript)


Supported Semantics
 - Request-Response: the browser sends requests, the actor / server replies; FTW Inboxes and Additional Service Endpoints operate on this semantic
 - Publish-Subscribe: the browser subscribes to data published by the actor / server; the actor / server ignores any messages sent by the browser in this case

 
Error Handling
 - errors are console logged

 
Constructors
- FtwWebSocketClient(obj): base class from which the other two derive (provides core websocket wrapping)
- FtwWebSocketSubscriber(obj): overrides the wsType member to be "pub.sp.nanomsg.org" as required
- FtwWebSocketRequester(obj): overrides the wsType member to be "rep.sp.nanomsg.org" as required, and overrides send() and receive() to implement / prepend the required nanomsg header (with header collision avoidance)


Instantiation
- the single constructor argument "obj" is an object comprising the following elements:
--  REQUIRED?		OPTION						DEFAULT VALUE		DESCRIPTION
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-- Required		wsAddress											websocket url (ex. "ws://127.0.0.1:65430")
-- Optional		onOpen(event)					function(){}		callback executed when a connection is opened successfully, receives an event object as an input parameter
-- Optional		onMessage(event, msgObj) 		function(){}		callback executed when a message is received, receives an event object and message object as input parameters
-- Optional		onError(event, errStr) 			function(){}		callback executed when an error occurs, receives an event object and error string as input parameters
-- Optional		onClose(event) 					function(){}		callback executed when a connection is closed, receives an event object as an input parameter
-- Optional		debugMode 						false				boolean determining whether the library itself console logs communication and events for debug purposes (true turns on logging)
-- Optional		onOpenScope 					this (instance)		object or function object as scope in which to call onMessageScope
-- Optional		onMessageScope 					this (instance)		object or function object as scope in which to call onMessageScope
-- Optional		onErrorScope 					this (instance)		object or function object as scope in which to call onMessageScope
-- Optional		onCloseScope 					this (instance)		object or function object as scope in which to call onMessageScope


Functions
- open(evt): fires the user-provided onOpen callback when the websocket opens successfully
- error(evt): fires the user-provided onError callback when an error occurs
- close(evt): fires the user-provided onClose callback when the websocket is closed
- receive(evt): fires the user-provided onMessage callback when a message is received
- send(msg): call this function to send a msg to the server (msg can be either a json string or object)


Typical Usage
- for more details see ~ftw/examples/websocket
- the following example instantiates an instance of FtwWebSocketSubscriber and defines callbacks to console log activities

	var ftwws_requester = new FtwWebSocketSubscriber({
		
		"wsAddress"	:		"ws://127.0.0.1:65438", // replace the address and port specified here as desired, both corresponding to a bound FTW socket
		"onOpen"	: 		function(evt) { // callback executed when a connection is opened successfully (evt is the event object)
								console.log('Connection open!');	
							},	
		"onMessage"	:		function(evt, msgobj) { // callback executed when a message is received from an actor (evt is the event object, msg is an object)
								console.log('Message received: ' + JSON.stringify(msgobj, null, 4));
							},
		"onError"	:		function(evt, errmsg) { // callback executed when an error occurs (evt is the event object, err is an error string)
								console.log('Error: ' + errmsg);
							},
		"onClose"	:		function(evt) { // callback executed when the connection is closed (evt is the event object)
								console.log('Connection closed!');
							},
		"debugMode"	:		false
		
	});
	
- the following example instantiates an instance of FtwWebSocketRequester, sends a ping request "onopen", and defines callbacks to console log activities

	var ftwws_requester = new FtwWebSocketRequester({
		
		"wsAddress"	:		"ws://127.0.0.1:65439",	// replace the address and port specified here as desired, both corresponding to a bound FTW socket
		"onOpen"	: 		function(evt) { // callback executed when a connection is opened successfully (evt is the event object)
								console.log('Connection open!');
								this.send('{"FTW-Request-Header": "FBQ-Control", "FBQ-Request":"Ping"}'); //this refers to this instance, so we can use it here to call our send function
							},	
		"onMessage"	:		function(evt, msgobj) { // callback executed when a message is received from an actor (evt is the event object, msg is an object)
								console.log('Message received: ' + JSON.stringify(msgobj, null, 4));
							},
		"onError"	:		function(evt, errmsg) { // callback executed when an error occurs (evt is the event object, err is an error string)
								console.log('Error: ' + errmsg);
							},
		"onClose"	:		function(evt) { // callback executed when the connection is closed (evt is the event object)
								console.log('Connection closed!');
							},
		"debugMode"	:		false
		
	});

	
*/


/*
---------------------------------------------------------------------------------
Helper Functions 
---------------------------------------------------------------------------------
*/
function isObject(anything) {
	return (typeof(anything) == "object");
}
function isString(anything) {
	return (typeof(anything) == "string");
}
function isFunction(anything) {
	return (typeof(anything) == "function");
}
function isBoolean(anything) {
	return (typeof(anything) == "boolean");
}


/*
---------------------------------------------------------------------------------
Check Browser Facilities 
---------------------------------------------------------------------------------
*/
var ws_available = "WebSocket" in window; //required
var td_available = "TextDecoder" in window; //convenient
var te_available = "TextEncoder" in window; //convenient
if (!ws_available || !td_available || !te_available) {
	var message = "You may need to upgrade to a modern browser. The following key components are not supported:\n";
	if (!ws_available) { message += "\nWebSocket"; }
	if (!td_available) { message += "\nTextDecoder"; }
	if (!te_available) { message += "\nTextEncoder"; }
	message += "\n\nNote: WebSocket is required although TexDecoder and TextEncoder can be replaced with more fundamental functions if necessary.";
	alert(message);
}


/*
---------------------------------------------------------------------------------
Class WebSocketClient 
---------------------------------------------------------------------------------
*/
var WebSocketClient = function(obj) {
	
	//if required elements were not passed, return immediately
	if (!isObject(obj) || !isString(obj.wsAddress) || !isString(obj.wsType)) {
		console.log('Argument "obj" must be an object containing (at least) string elements "wsAddress" and "wsType".');
		return null;
	}
	
	//members
	this.wsAddress = obj.wsAddress;  //exists by way of the check above
	this.wsType = obj.wsType; //exists by way of the check above
	
	this.ws = new WebSocket(this.wsAddress, this.wsType);
	
	this.ws.binaryType = (isString(obj.wsBinaryType)) ? obj.wsBinaryType : "arraybuffer";
	
	this.onOpen = (isFunction(obj.onOpen)) ? obj.onOpen : function(){};
	this.onMessage = (isFunction(obj.onMessage)) ? obj.onMessage : function(){};
	this.onError = (isFunction(obj.onError)) ? obj.onError : function(){};
	this.onClose = (isFunction(obj.onClose)) ? obj.onClose : function(){};
	
	this.onOpenScope = (isObject(obj.onOpenScope)) ? obj.onOpenScope : this;
	this.onMessageScope = (isObject(obj.onMessageScope)) ? obj.onMessageScope : this;
	this.onErrorScope = (isObject(obj.onErrorScope)) ? obj.onErrorScope : this;
	this.onCloseScope = (isObject(obj.onCloseScope)) ? obj.onCloseScope : this;
	
	this.debugMode = (isBoolean(obj.debugMode)) ? obj.debugMode : false;
	
	this.TextEncoder = new TextEncoder('utf-8');
	this.TextDecoder = new TextDecoder('utf-8');
	
	var _this = this;
	
	this.log = function(msg) {
		if (this.debugMode) {
			console.log(msg);
		}
	};
	
	this.ws.onopen = function(evt) {
		_this.log('FtwWebSocket open (' + _this.wsAddress + ', ' + _this.wsType + ').'); //do this first, so in the event the user-provided function borks, we at least know we successfully opened
		_this.open(evt);
	};
	
	this.ws.onmessage = function(evt) {
		_this.log('FtwWebSocket message received: ' + _this.TextDecoder.decode(new Uint8Array(evt.data))); //do this first, so in the event the user-provided function borks, we at least know we received the message
		_this.receive(evt);
	};
	
	this.ws.onerror = function(evt) {
		var errmsg = (evt.data != undefined)? evt.data : "No error data received."; //create the error message
		_this.log('FtwWebSocket error: ' + errmsg); //do this first, so in the event the user-provided function borks, we at least know we received the message
		_this.error(evt);
	};	
	
	this.ws.onclose = function(evt) {
		_this.close(evt);
		_this.log('FtwWebSocket closed.'); //do this first, so in the event the user-provided function borks, we at least know we received the message
	};

};

WebSocketClient.prototype.open = function(evt) {
	this.onOpen.call(this.onOpenScope, evt); //call onOpen in the defined scope, passing the evt argument
};

WebSocketClient.prototype.error = function(evt) {
	var errmsg = (evt.data != undefined)? evt.data : "No error data received."; //create the error message
	this.onError.call(this.onErrorScope, evt, errmsg); //call onOpen in the defined scope, passing the evt argument
};

WebSocketClient.prototype.close = function(evt) {
	this.onClose.call(this.onCloseScope, evt); //call onOpen in the defined scope, passing the evt argument
};

WebSocketClient.prototype.receive = function(evt) {
	var msgobj = JSON.parse(this.TextDecoder.decode(new Uint8Array(evt.data)));
	this.onMessage.call(this.onMessageScope, evt, msgobj); //call onMessage in the defined scope, passing the evt and msg arguments
};

WebSocketClient.prototype.send = function(msg) {
	if (!isString(msg) && !isObject(msg)) {
		console.log('Argument msg of method FtwWebSocket.send must be either a string representing json or an object');
		return null;
	}
	var strmsg = (isString(msg)) ? msg : JSON.stringify(msg);
	this.ws.send(this.TextEncoder.encode(strmsg));
	this.log('FtwWebSocket sent message: ' + strmsg);
};


/*
---------------------------------------------------------------------------------
Class FtwWebSocketSubscriber 
---------------------------------------------------------------------------------
*/
function FtwWebSocketSubscriber(obj) {
	obj.wsType = "pub.sp.nanomsg.org"; //we'll connect to the server's publish socket
	WebSocketClient.call(this, obj); //call parent constructor
}
FtwWebSocketSubscriber.prototype = Object.create(WebSocketClient.prototype);
FtwWebSocketSubscriber.prototype.constructor = FtwWebSocketSubscriber;


/*
---------------------------------------------------------------------------------
Class FtwWebSocketRequster 
---------------------------------------------------------------------------------
*/
function FtwWebSocketRequster(obj) {
	obj.wsType = "rep.sp.nanomsg.org"; //we'll connect to the server's reply socket
	WebSocketClient.call(this, obj); //call parent constructor
	
	//members
	this.START = parseInt("10000", 16); //first 4 byte UTF-8 encoding
	this.END = parseInt("10FFFF", 16); //last 4 byte UTF-8 encoding
	this.nextHeader = this.START; //first available header
	this.headersInUse = []; //flat list of headers currently in use
	
	//Function: reserve an available header (a 4 byte UTF-8 character with most significant bit = 1) and return it as a string for use
	// - algorithm: march from start to end through all the 4-byte UTF-8 characters (which all have MSB = 1) to reduce likliehood of collisions, and wrap around if necessary (must send 1,048,576 messages before this happens, and surely they won't all be still waiting for replies :)
	this.reserveHeader = function() {
		if (this.headersInUse.indexOf(this.nextHeader) == -1) {
			this.headersInUse[this.headersInUse.length] = this.nextHeader; //reserve the header
			return String.fromCodePoint(this.nextHeader);
		}
		else {
			this.nextHeader = (this.nextHeader != this.END) ? this.nextHeader + 1 : this.START ; //compute the next value in the series, wrapping around if necessary
			return this.getNextAvailableHeader(); //try that value
		}
	};
	
	//Function: release the specified header (where the header is taken as a string for convenience bc that's how it's received)
	this.unreserveHeader = function(headerString) {
		var index = this.headersInUse.indexOf(headerString.codePointAt(0)); //we expect only a single 4-byte character as the headerString
		if (index != -1) {
			this.headersInUse.splice(index, 1); //remove the element, releasing it as "available" on subsequence checks
		}
		else {
			console.log("Expected to find and remove / release header \\u" + headerString.toString(16) + " from the headersInUse array, but it was no longer there. Scary!");
		}
	};

}
FtwWebSocketRequster.prototype = Object.create(WebSocketClient.prototype);
FtwWebSocketRequster.prototype.constructor = FtwWebSocketRequster;

FtwWebSocketRequster.prototype.send = function(msg) {
	if (!isString(msg) && !isObject(msg)) {
		console.log('Argument msg of method FtwWebSocket.send must be either a string representing json or an object');
		return null;
	}
	var strhdr = this.reserveHeader();
	var strmsg = (isString(msg)) ? msg : JSON.stringify(msg);
	this.ws.send(this.TextEncoder.encode(strhdr + strmsg));
	this.log('FtwWebSocket sent message: ' + strmsg + " (with a required nanomsg header \\u" + strhdr.codePointAt(0) + ').');
};

FtwWebSocketRequster.prototype.receive = function(evt) {
	var reply = this.TextDecoder.decode(new Uint8Array(evt.data)); //this is now a javascript string (2-byte characters)
	var strhdr = reply.substr(0,2); //pick off the header
	var strmsg = reply.substr(2); //pick off the message
	this.unreserveHeader(strhdr);
	this.onMessage.call(this.onMessageScope, evt, JSON.parse(strmsg)); //call onMessage in the defined scope, passing the evt and the message as an object
};
