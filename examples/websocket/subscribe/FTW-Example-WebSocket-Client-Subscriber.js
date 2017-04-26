/*
Attribution:	Written by Jassem Shahrani 09/2016
Example: 		WebSocket browser client to FTW actor.
Description: 	This example creates a FtwWebSocketSubscriber and logs activity to a div with id "activity-log".  
				Run the VI in the same folder (acts as the server) and open the HTML file in a browser to view.
*/

//wait for DOM to load
jQuery(document).ready(function($) {
	
	//get a reference to the activity-log div which we'll use to indicate progress to the user in the page
	var activity_log = $('#activity-log');
	activity_log.append("<p>Attemping WebSocket connection.</p>");
	
	// FtwWebSocketRequester Test
	var ftwwsSubscriber = new FtwWebSocketSubscriber({
		
		"wsAddress"	:		"ws://127.0.0.1:65438",																															// replace the address and port specified here as desired, both corresponding to a bound FTW socket
		"onOpen"	: 		function(evt) { // callback executed when a connection is opened successfully (evt is the event object)
								activity_log.append('<p>Connection open!</p>');	
							},	
		"onMessage"	:		function(evt, msgobj) { // callback executed when a message is received from an actor (evt is the event object, msg is an object)
								activity_log.append('<p>Message received: ' + JSON.stringify(msgobj, null, 4) + '</p>');
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

