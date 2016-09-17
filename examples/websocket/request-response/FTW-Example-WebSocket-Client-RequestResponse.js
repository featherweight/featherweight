/*
Example: 		WebSocket browser client to FTW actor.
Description: 	This example creates a FtwWebSocketRequester and logs activity to a div with id "activity-log".
				A message / request is sent as soon as the socket connection is opened, and 1 second after recieving a given reply.
				Run the VI in the same folder (acts as the server) and open the HTML file in a browser to view.
*/

//wait for DOM to load
jQuery(document).ready(function($) {
	
	//get a reference to the activity-log div which we'll use to indicate progress to the user in the page
	var activity_log = $('#activity-log');
	activity_log.append("<p>Attemping WebSocket connection.</p>");
	
	// FtwWebSocketRequester Test
	var ftwws_requester = new FtwWebSocketRequster({
		
		"wsAddress"	:		"ws://127.0.0.1:65439",																															// replace the address and port specified here as desired, both corresponding to a bound FTW socket
		"onOpen"	: 		function(evt) { // callback executed when a connection is opened successfully (evt is the event object)
								activity_log.append('<p>Connection open!</p>');	
								this.send('{"FTW-Request-Header": "FBQ-Control", "FBQ-Request":"Ping"}');	
							},	
		"onMessage"	:		function(evt, msgobj) { // callback executed when a message is received from an actor (evt is the event object, msg is an object)
								activity_log.append('<p>Message received: ' + JSON.stringify(msgobj, null, 4) + '</p>');
								var _this = this; //pass "this" through scope so we can call our send() function within
								setTimeout(function() { // delay 1 second and send another message
									_this.send('{"FTW-Request-Header": "FBQ-Control", "FBQ-Request":"Ping"}');
								}, 1000);
								$('html, body').animate({scrollTop:$(document).height()}, 'slow'); //scroll to bottom to show latest received message
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

