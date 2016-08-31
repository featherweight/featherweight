/*
Example: 		WebSocket browser client to FTW actor.
Description: 	This example attemps to: 
				1. open a WebSocket connection of type "rep.sp.nanomsg.org" to a FTW actor on localhost (127.0.0.1) with a specified port
				2. send an intial "Ping" request with required header
				3. read and display the response (validate the received header, must match the request header, display error if mismatched) 
				4. periodically (every 1 second) send a "Rand" request and display the response
				5. close the WebSocket when the window is closed
*/

//wait for DOM to load
jQuery(document).ready(function($) {
	
	//get a reference to the activity-log div which we'll use to indicate progress to the user in the page
	var activity_log = $('#activity-log');
	
	//keep send message count
	var count = 0;
	
	//note: we make send_header global here so we can compare it in our onmessage handler
	var send_header = "\u00FF\u00FF"; //viable message header (note: we use two 2-byte UTF-8 characters to satisfy the nanomsg header requirements: 4 bytes with most significant bit = 1)
	
	//function to format and send messages to send
	var sendRequest = function(request_hdr) {
		count++;
		var send_message = '{"FTW-Request-Header": "'+request_hdr+'", "Count": "'+count+'"}'; //construct a dummy message (we expect this to get reflected back)
		var send_buffer = new TextEncoder('utf-8').encode(send_header + send_message); //prepend the header to the message and UTF-8 encode
		activity_log.append('<p>Request: '+send_message+'</p>');
		ws.send(send_buffer); //send the message
	}
	
	//check for required and convenient browser assets
	var ws_available = "WebSocket" in window; //required
	var td_available = "TextDecoder" in window; //convenient
	var te_available = "TextEncoder" in window; //convenient

	//if browser assets used in this example are available, proceed (otherwise alert an error message otherwise)
	if (ws_available && td_available && te_available) {
		
		activity_log.append("<p>Attemping WebSocket connection.</p>");

		var ws = new WebSocket('ws://127.0.0.1:65439', 'rep.sp.nanomsg.org'); //open the websocket
		ws.binaryType = "arraybuffer"; //the required binaryType for FTW (nanomsg) messages


		//define the onerror handler (fires when an error occurs)
		ws.onerror = function(event){

			var msg = (event.data != undefined)? event.data : "No error data received."; //create the error message
			console.log(msg); //log the error message
			activity_log.append("<p>WebSocket Error: "+msg+"</p>");
		};

		//define the onmessage handler (fires when a message is received from the server)
		ws.onmessage = function(event){
			
			var receive_str = new TextDecoder('utf-8').decode(new Uint8Array(event.data)); //decode the received data to string
			var receive_header = receive_str.substr(0,2); //pick off the reply's header
			
			//validate we received the same header we sent, else log an error
			if (receive_header == send_header) {
				
				var receive_message = receive_str.substr(2); //pick off the reply's message 
				console.log("Response Received: "+receive_message); //log the reply
				activity_log.append("<p>Response: "+receive_message+"</p><br />");

			}
			else { //log an error if we don't receive the header we expected
				
				console.log("Error: Unexpected header received.\nHeader: "+receive_header+" (expected: "+send_header+")\nMessage: "+receive_message); //log error message
				activity_log.append("<p>"+"Error: Unexpected header received.\nHeader: "+receive_header+" (expected: "+send_header+")\nMessage: "+receive_message+"</p><br />");
			}
			
			//scroll to bottom to show latest received message
			$('html, body').animate({scrollTop:$(document).height()}, 'slow');
			
			//delay 1 second and send another message
			setTimeout(function() {
				sendRequest("Rand");
			}, 1000);
			
		};

		//define the onclose function (fires when the websocket closes)
		ws.onclose = function (event) {
			
			activity_log.append('<p>WebSocket connection closed. </p>');
			activity_log.append('<p>Note: error on close expected - see <a href="https://github.com/featherweight/featherweight/issues/101" target="_blank">issue 101</a></p>');
		};
		
		//define the onopen function (fires when the websocket successfully opens)
		ws.onopen = function (event) {
			
			activity_log.append('<p>WebSocket connection open. </p>');
			sendRequest("Ping");
			
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
		if (!te_available) { message += "\nTextEncoder"; }
		message += "\n\nNote: WebSocket is required although TexDecoder and TextEncoder can be replaced with more fundamental functions if necessary.";
		alert(message);
		
	}
});

