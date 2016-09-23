/*

Attribution
- written by: Jassem Shahrani 09/2016

Overview
- The classes herein facilitate communciation between modern web browsers and Featherweight (FTW) websockets (i.e. sockets of type ws://<address>:<port>) 
- FTW on the LabVIEW side binds a socket (i.e. is the server) to which the browser can connect
- Derive from these classes if desired (see for details: https://developer.mozilla.org/en-US/docs/Web/JavaScript/Introduction_to_Object-Oriented_JavaScript)
- Intentionally does not use other libraries to remain standalone

Supported Semantics
 - Request-Response: the browser sends requests, the actor / server replies; FTW Inboxes and Additional Service Endpoints operate on this semantic
 - Publish-Subscribe: the browser subscribes to data published by the actor / server; the actor / server ignores any messages sent by the browser in this case

 
Error Handling
 - Errors are console logged

 Debug Mode
  - prints various statements to the console to help sanity check what's happening
 
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

	var ftwwsSubscriber = new FtwWebSocketSubscriber({
		
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
	
- the following example instantiates an instance of FtwWebSocketRequester, sends a ping request "onopen", and defines standard callbacks to console log activities

	var ftwwsRequester = new FtwWebSocketRequester({
		
		"wsAddress"	:		"ws://127.0.0.1:65439",	// replace the address and port specified here as desired, both corresponding to a bound FTW socket
		"onOpen"	: 		function(evt) { // callback executed when a connection is opened successfully (evt is the event object)
								console.log('Connection open!');
								this.send({"FTW-Request-Header": "FBQ-Control", "FBQ-Request":"Ping"}); //this refers to this instance, so we can use it here to call our send function
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

- the following example instantiates an instance of FtwWebSocketRequester, sends a ping request "onopen", defines callbacks to console log activities, AND defines a custom send callback
 
		var ftwwsRequester = new FtwWebSocketRequster({
		
		"wsAddress"	:		"ws://127.0.0.1:65440",	// replace the address and port specified here as desired, both corresponding to a bound FTW socket
		"onOpen"	: 		function(evt) { // callback executed when a connection is opened successfully (evt is the event object)
								console.log('<p>Connection open!</p>');	
								
								//Supplying send() with a callback function including scope and arguments
								var myArgs = {"usefulString": "useful in your callback", "usefulNumber": 9};
								var myMsg = {"FTW-Request-Header": "FBQ-Control", "FBQ-Request":"Ping"};
								var aClass = function(str) {
									this.str = str;
									this.func = function(replyObj, args) {
										console.log("Class was instantiated with string argument: " + this.str);
										console.log("Our callback function received reply:");
										console.log(JSON.stringify(replyObj));
										console.log("Our callback function received custom arguments:");
										console.log(JSON.stringify(args));
									}
								}
								var myClass = new aClass("Love me!");
								
								console.log('Sending message = ' + JSON.stringify(myMsg) + ' while specifying a custom callback function, arguments = ' + JSON.stringify(myArgs) + ', and scope = instance of "aClass".');	
								
								// we send this message and expect our callback function to be invoked printing console messages
								//   send(msg,   callback,     args,   scope);
								this.send(myMsg, myClass.func, myArgs, myClass);	
							},
		"onError"	:		function(evt, errmsg) { // callback executed when an error occurs (evt is the event object, err is an error string)
								console.log('<p>Error: ' + errmsg + '</p>');
							},
		"onClose"	:		function(evt) { // callback executed when the connection is closed (evt is the event object)
								console.log('<p>Connection closed!</p>');
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
	
	this.log = function(anything) {
		if (this.debugMode) {
			console.log(anything);
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
	this.reservedHeaders = []; //flat list of headers currently in use
	this.callbackRegistry = {}; //callback function dictionary with reservedHeaders as keys and {'scope': scope, 'callback': callback} as values
	
	//Function: reserve an available header (a 4 byte UTF-8 character with most significant bit = 1) and return it as a string for use
	// - algorithm: march from start to end through all the 4-byte UTF-8 characters (which all have MSB = 1) to reduce likliehood of collisions, and wrap around if necessary (must send 1,048,576 messages before this happens, and surely they won't ALL be still waiting for replies :)
	// - returns: the available header as a string
	this.reserveHeader = function() {
		if (this.reservedHeaders.indexOf(this.nextHeader) == -1) {
			this.reservedHeaders[this.reservedHeaders.length] = this.nextHeader; //reserve the header
			return String.fromCodePoint(this.nextHeader);
		}
		else {
			this.nextHeader = (this.nextHeader != this.END) ? this.nextHeader + 1 : this.START ; //compute the next value in the series, wrapping around if necessary
			return this.reserveHeader(); //try the next value
		}
		//note: techincally if all the headers are reserved and NEVER become unreserved, then this will be an infinite recursion. However if all the headers are truly in use then the application (or machine) should be failing for other reasons while waiting on 1,048,576 messages
		//TODO: track how many headers we've tried before success and if there are truly NO headers left, fall out of the recursion
	};
	
	//Function: release the specified header (where the header is taken as a string for convenience bc that's how it's received)
	// - returns: true if successfully, false if (crazily) it did not find the the header in the reserved list
	this.unreserveHeader = function(headerString) {
		var index = this.reservedHeaders.indexOf(headerString.codePointAt(0)); //we expect only a single 4-byte character as the headerString
		if (index != -1) {
			this.reservedHeaders.splice(index, 1); //remove the element, releasing it as "available" on subsequent checks
			return true;
		}
		else {
			console.log("FtwWebSocketRequster expected to find and remove / release header " + humanReadableHdrStr + " from the reservedHeaders array, but it was no longer there. Scary!");
			return false;
		}
	};
	
	//register the callback function for a given header so we can call the corresponding callbacks when we receive replies
	this.registerCallback = function(headerString, callback, args, scope) {
		
		//use human readable keys for debugging sanity (just in case)
		var humanReadableHdrStr = this.headerStringToHumanReadableCodepointString(headerString);
		
		this.callbackRegistry[humanReadableHdrStr] = {'scope': scope, 'callback': callback, 'args': args};
		
		this.log('FtwWebSocketRequster registered a callback corresponding to header string: ' + humanReadableHdrStr + ' with the following info: ');
		this.log(this.callbackRegistry[humanReadableHdrStr]);
	};
		
	//call the callback function with provided scope and args
	this.invokeCallback = function(headerString, replyObj) {
		
		var callback = null, scope = null, args = null;
		
		//use human readable keys for debugging sanity (just in case)
		var humanReadableHdrStr = this.headerStringToHumanReadableCodepointString(headerString);
		
		//for sanity, make sure we have the key / header string in our registry
		if (this.callbackRegistry.hasOwnProperty(humanReadableHdrStr)) {
			
			//note: callback registry entries are of form: {'scope': scope, 'callback': callback, 'args': args}
			scope = this.callbackRegistry[humanReadableHdrStr]['scope']; //defaults to the "this" reference if not originally provided on send
			callback = this.callbackRegistry[humanReadableHdrStr]['callback']; //defaults to a no-op function -- function(){} -- if not originally provided on send
			args = this.callbackRegistry[humanReadableHdrStr]['args']; //defaults to an empty object -- {} -- if not originally provided on send
			
			//execute the callback in the provided scope (recall: this is graceful even if the user doesn't supply a callback because callback = function(){}, scope = this, args = {} which effectively calls a no-op function with "this" scope and no custom arguments <- a reply element will get injected into args)
			callback.call(scope, replyObj, args);
			
			this.log('The current callback registry is: ');
			this.log(this.callbackRegistry);
			
			//"unregister" the callback to keep our callbackRegistry from growing unnecessarily over time
			delete this.callbackRegistry[humanReadableHdrStr];
			
			this.log('FtwWebSocketRequster executed a callback corresponding to header: ' + humanReadableHdrStr + '.');
		}
		else {
			console.log("FtwWebSocketRequster expected to find header " + humanReadableHdrStr + " as a key in the callbackRegistry, but it was gone. Scary!");
		}
	};
	
	this.headerStringToHumanReadableCodepointString = function(headerString) {
		return 'U+' + headerString.codePointAt(0).toString(16); //human readable string representing the code point
	}
	
}
FtwWebSocketRequster.prototype = Object.create(WebSocketClient.prototype);
FtwWebSocketRequster.prototype.constructor = FtwWebSocketRequster;

FtwWebSocketRequster.prototype.send = function(msg, callback, args, scope) {
	
	//ensure the message is either string or object
	if (!isString(msg) && !isObject(msg)) {
		console.log('FtwWebSocketRequster: Argument msg of method FtwWebSocket.send must be either a string representing json or an object');
		return null;
	}
	
	//ensure callback, scope, and args are legit
	callback = (isFunction(callback)) ? callback : function(){};
	scope = (isObject(scope) || isFunction(scope)) ? scope : this;
	args = (isObject(args)) ? args : {};
	
	//convert the message to string if necessary
	var strmsg = (isString(msg)) ? msg : JSON.stringify(msg);
	
	//find and reserve a header
	var strhdr = this.reserveHeader();
	
	//register the callback function
	this.registerCallback(strhdr, callback, args, scope);
	
	//send the message
	this.ws.send(this.TextEncoder.encode(strhdr + strmsg));
	this.log('FtwWebSocket sent message: ' + strmsg + " (with a required nanomsg header: " + this.headerStringToHumanReadableCodepointString(strhdr) + ').');
};

FtwWebSocketRequster.prototype.receive = function(evt) {
	var reply = this.TextDecoder.decode(new Uint8Array(evt.data)); //this is now a javascript string (2-byte characters)
	var strhdr = reply.substr(0,2); //pick off the header (4 bytes)
	var strmsg = reply.substr(2); //pick off the message (rest of string; we expect this to be a json string)
	var objmsg = null; //we parse the json below into an object (or at least try)
	
	//make sure the reply is valid JSON
	var replyIsValidJSON = true;
	try {
		objmsg = JSON.parse(strmsg);
	} catch (e) {
		replyIsValidJSON = false;
		console.log('FtwWebSocketRequster expected the reply be a JSON. It could be that the server did not reflect the header (nanomsg standard) correctly, or that the reply content was simply not JSON.');
	}
	
	//if we successfully found our header and we do have a JSON reply, execute the callback function
	var foundHeaderInRegistry = this.unreserveHeader(strhdr);
	if (replyIsValidJSON && foundHeaderInRegistry) {
		this.invokeCallback(strhdr, objmsg);
	}
	
	// still also execute the onMessage callback in the event they'd like to use this as a catch all and do something on "all" received messages
	// note: by default onMessage will be a no-op function, which effectively renders this silent (satisfies the case where the user wants only their send/receive handlers to fire)
	this.onMessage.call(this.onMessageScope, evt, objmsg); //call onMessage in the defined scope, passing the evt and the message as an object

	
};
