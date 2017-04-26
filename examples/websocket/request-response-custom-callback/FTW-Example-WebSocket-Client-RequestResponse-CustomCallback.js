/*
Attribution:	Written by Jassem Shahrani 09/2016
Example: 		WebSocket browser client to FTW actor.
Description: 	This example creates a FtwWebSocketRequester and logs activity to a div with id "activity-log".
				A message / request is sent as soon as the socket connection is opened, and 1 second after recieving a given reply.
				Message here are caught as catch-all by the onMessage handler, which performs the 1 second wait before sending again.
				Run the VI in the same folder (acts as the server) and open the HTML file in a browser to view.
				
				Note: see the request-response-custom-callback folder / example for how to register a custom callback on a given send operation
*/

//wait for DOM to load
jQuery(document).ready(function($) {
	
	//get a reference to the activity-log div which we'll use to indicate progress to the user in the page
	var activity_log = $('#activity-log');
	activity_log.append("<p>Attemping WebSocket connection.</p>");
	
	// FtwWebSocketRequester Test
	var ftwwsRequester = new FtwWebSocketRequster({
		
		"wsAddress"	:		"ws://127.0.0.1:65440",																															// replace the address and port specified here as desired, both corresponding to a bound FTW socket
		"onOpen"	: 		function(evt) { // callback executed when a connection is opened successfully (evt is the event object)
								activity_log.append('<p>Connection open!</p>');	
								
								//Supplying send() with a callback function including scope and arguments
								var myArgs = {"usefulString": "useful in your callback", "usefulNumber": 9};
								var myMsg = {"FTW-Request-Header": "FBQ-Control", "FBQ-Request":"Ping"};
								var aClass = function(str) {
									this.str = str;
									this.func = function(replyObj, args) {
										activity_log.append("<p>Class was instantiated with string argument: " + this.str + "</p>");
										activity_log.append("<p>Our callback function received reply: </p>");
										activity_log.append("<p>" + JSON.stringify(replyObj) + "</p>");
										activity_log.append("<p>Our callback function received custom arguments: </p>");
										activity_log.append("<p>" + JSON.stringify(args) + "</p>");
									}
								}
								var myClass = new aClass("Love me!");
								
								activity_log.append('<p>Sending message = ' + JSON.stringify(myMsg) + ' while specifying a custom callback function, arguments = ' + JSON.stringify(myArgs) + ', and scope = instance of "aClass".</p>');	
								
								// we send this message and expect our callback function to be invoked printing console messages
								//   send(msg,   callback,     args,   scope);
								this.send(myMsg, myClass.func, myArgs, myClass);	
							},
		"onError"	:		function(evt, errmsg) { // callback executed when an error occurs (evt is the event object, err is an error string)
								activity_log.append('<p>Error: ' + errmsg + '</p>');
							},
		"onClose"	:		function(evt) { // callback executed when the connection is closed (evt is the event object)
								activity_log.append('<p>Connection closed!</p>');
							},
		"debugMode"	:		false
		
	});

	
	
});