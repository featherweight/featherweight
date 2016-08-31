/*
Example: 		WebSocket browser client to FTW actor.
Description: 	This example attemps to: 
				1. open a WebSocket connection of type "pub.sp.nanomsg.org" to a FTW actor on localhost (127.0.0.1) with a specified port
				2. display received messages
				3. close the WebSocket when the browser window is closed
				Note: there is no header attached to messages such as in the request-response case
*/

//wait for DOM to load
jQuery(document).ready(function($) {
	
	//get a reference to the activity-log div which we'll use to indicate progress to the user in the page
	var activity_log = $('#activity-log');

	//check for required and convenient browser assets
	var ws_available = "WebSocket" in window; //required
	var td_available = "TextDecoder" in window; //convenient

	//if browser assets used in this example are available, proceed (otherwise alert an error message otherwise)
	if (ws_available && td_available) {
		
		activity_log.append("<p>Attemping WebSocket connection.</p>");

		var ws = new WebSocket('ws://127.0.0.1:65438', 'pub.sp.nanomsg.org'); //open the websocket
		ws.binaryType = "arraybuffer"; //the required binaryType for FTW (nanomsg) messages

		//define the onerror handler (fires when an error occurs)
		ws.onerror = function(event){

			var msg = (event.data != undefined)? event.data : "No error data received."; //create the error message
			console.log(msg); //log the error message
			activity_log.append("<p>WebSocket Error: "+msg+"</p>");
		};

		//define the onmessage handler (fires when a message is received from the server)
		ws.onmessage = function(event){
			
			var receive_message = new TextDecoder('utf-8').decode(new Uint8Array(event.data)); //decode the received data to string
			console.log("Response Received: "+receive_message); //log the reply
			activity_log.append("<p>Message Received: "+receive_message+"</p>");
			
			//scroll to bottom to show latest received message
			$('html, body').animate({scrollTop:$(document).height()}, 'slow');
		};

		//define the onclose function (fires when the websocket closes)
		ws.onclose = function (event) {
			
			activity_log.append('<p>WebSocket connection closed. </p>');
		};
		
		//define the onopen function (fires when the websocket successfully opens)
		ws.onopen = function (event) {
			
			activity_log.append('<p>WebSocket connection open. </p>');
		};
		
		//close the websocket when the window is closed
		$(window).unload(function() {
			
			ws.close(); //close the WebSocket
			return "WebSocket has been closed."; //some browsers will display this
		});
	}
	else { //alert the user to use a modern browser with WebSocket, TextEncoder, and TextDecoder support.

		var message = "You may need to upgrade to a modern browser. The following key components are not supported:\n";
		if (!ws_available) { message += "\nWebSocket"; }
		if (!td_available) { message += "\nTextDecoder"; }
		message += "\n\nNote: WebSocket is required although TexDecoder can be replaced with more fundamental functions if necessary.";
		alert(message);
		
	}
});