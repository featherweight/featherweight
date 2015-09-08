<?xml version='1.0' encoding='UTF-8'?>
<Project Type="Project" LVVersion="14008000">
	<Item Name="My Computer" Type="My Computer">
		<Property Name="server.app.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="server.control.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="server.tcp.enabled" Type="Bool">false</Property>
		<Property Name="server.tcp.port" Type="Int">0</Property>
		<Property Name="server.tcp.serviceName" Type="Str">My Computer/VI Server</Property>
		<Property Name="server.tcp.serviceName.default" Type="Str">My Computer/VI Server</Property>
		<Property Name="server.vi.callsEnabled" Type="Bool">true</Property>
		<Property Name="server.vi.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="specify.custom.address" Type="Bool">false</Property>
		<Item Name="ftw" Type="Folder">
			<Item Name="actor" Type="Folder">
				<Item Name="connector" Type="Folder">
					<Item Name="FTW-Actor-Connector.lvclass" Type="LVClass" URL="../src/core/actor/connector/FTW-Actor-Connector.lvclass"/>
				</Item>
				<Item Name="context" Type="Folder">
					<Item Name="FTW-Actor-Context.lvclass" Type="LVClass" URL="../src/core/actor/context/FTW-Actor-Context.lvclass"/>
				</Item>
				<Item Name="instance" Type="Folder">
					<Item Name="FTW-Actor-Instance.lvclass" Type="LVClass" URL="../src/core/actor/instance/FTW-Actor-Instance.lvclass"/>
				</Item>
				<Item Name="logger" Type="Folder">
					<Item Name="instance" Type="Folder">
						<Item Name="FTW-Logger-Instance.lvclass" Type="LVClass" URL="../src/core/actor/logger/instance/FTW-Logger-Instance.lvclass"/>
					</Item>
					<Item Name="FTW-Logger.lvclass" Type="LVClass" URL="../src/core/actor/logger/FTW-Logger.lvclass"/>
				</Item>
				<Item Name="message" Type="Folder">
					<Item Name="FTW-Message.lvclass" Type="LVClass" URL="../src/core/actor/message/FTW-Message.lvclass"/>
				</Item>
				<Item Name="request" Type="Folder">
					<Item Name="FTW-Request.lvclass" Type="LVClass" URL="../src/core/actor/request/FTW-Request.lvclass"/>
				</Item>
				<Item Name="router" Type="Folder">
					<Item Name="FTW-Router.lvclass" Type="LVClass" URL="../src/core/actor/router/FTW-Router.lvclass"/>
				</Item>
				<Item Name="scheduler" Type="Folder">
					<Item Name="FTW-Scheduler.lvclass" Type="LVClass" URL="../src/core/actor/scheduler/FTW-Scheduler.lvclass"/>
				</Item>
				<Item Name="socket" Type="Folder">
					<Item Name="FTW-Socket.lvclass" Type="LVClass" URL="../src/core/actor/socket/FTW-Socket.lvclass"/>
				</Item>
				<Item Name="subscription" Type="Folder">
					<Item Name="FTW-Subscription.lvclass" Type="LVClass" URL="../src/core/actor/subscription/FTW-Subscription.lvclass"/>
				</Item>
				<Item Name="support" Type="Folder">
					<Item Name="FTW-Actor-DynamicLaunchOptions.vi" Type="VI" URL="../src/core/actor/support/FTW-Actor-DynamicLaunchOptions.vi"/>
					<Item Name="FTW-Actor-ValidateAddress.vi" Type="VI" URL="../src/core/actor/support/FTW-Actor-ValidateAddress.vi"/>
				</Item>
			</Item>
			<Item Name="application" Type="Folder">
				<Item Name="FTW-App-StringToVersion.vi" Type="VI" URL="../src/core/application/FTW-App-StringToVersion.vi"/>
				<Item Name="FTW-App-StringVersionToString.vi" Type="VI" URL="../src/core/application/FTW-App-StringVersionToString.vi"/>
				<Item Name="FTW-App-VersionToString.vi" Type="VI" URL="../src/core/application/FTW-App-VersionToString.vi"/>
			</Item>
			<Item Name="array" Type="Folder">
				<Item Name="shuffle" Type="Folder">
					<Item Name="FTW-Array-Shuffle.xnode" Type="XNode" URL="../src/core/array/shuffle/FTW-Array-Shuffle.xnode"/>
				</Item>
			</Item>
			<Item Name="database" Type="Folder">
				<Item Name="FTW-SQLite-Fetch" Type="Folder">
					<Item Name="FTW-SQLite-Fetch.xnode" Type="XNode" URL="../src/core/database/FTW-SQLite-Fetch/FTW-SQLite-Fetch.xnode"/>
				</Item>
				<Item Name="FTW-SQLite-Insert" Type="Folder">
					<Item Name="FTW-SQLite-Insert.xnode" Type="XNode" URL="../src/core/database/FTW-SQLite-Insert/FTW-SQLite-Insert.xnode"/>
				</Item>
				<Item Name="FTW-SQLite-Connector.lvclass" Type="LVClass" URL="../src/core/database/FTW-SQLite-Connector.lvclass"/>
			</Item>
			<Item Name="email" Type="Folder">
				<Item Name="FTW-Email-AddressValidator.vi" Type="VI" URL="../src/core/email/FTW-Email-AddressValidator.vi"/>
			</Item>
			<Item Name="error" Type="Folder">
				<Item Name="FTW-ERR-Assert-AbstractMethodCall.vi" Type="VI" URL="../src/core/error/FTW-ERR-Assert-AbstractMethodCall.vi"/>
				<Item Name="FTW-ERR-Assert-ConditionalDisable.vi" Type="VI" URL="../src/core/error/FTW-ERR-Assert-ConditionalDisable.vi"/>
				<Item Name="FTW-ERR-Assert-DeveloperError.vi" Type="VI" URL="../src/core/error/FTW-ERR-Assert-DeveloperError.vi"/>
				<Item Name="FTW-ERR-Assert-Truthy.vi" Type="VI" URL="../src/core/error/FTW-ERR-Assert-Truthy.vi"/>
				<Item Name="FTW-ERR-CallChain.vi" Type="VI" URL="../src/core/error/FTW-ERR-CallChain.vi"/>
				<Item Name="FTW-ERR-Clear.vi" Type="VI" URL="../src/core/error/FTW-ERR-Clear.vi"/>
				<Item Name="FTW-ERR-ExceptionType.ctl" Type="VI" URL="../src/core/error/FTW-ERR-ExceptionType.ctl"/>
				<Item Name="FTW-ERR-Ignore.vi" Type="VI" URL="../src/core/error/FTW-ERR-Ignore.vi"/>
				<Item Name="FTW-ERR-NoErrorConstant.vi" Type="VI" URL="../src/core/error/FTW-ERR-NoErrorConstant.vi"/>
				<Item Name="FTW-ERR-SerializeForLog.vi" Type="VI" URL="../src/core/error/FTW-ERR-SerializeForLog.vi"/>
				<Item Name="FTW-ERR-StatusError.vi" Type="VI" URL="../src/core/error/FTW-ERR-StatusError.vi"/>
				<Item Name="FTW-ERR-StatusException.vi" Type="VI" URL="../src/core/error/FTW-ERR-StatusException.vi"/>
				<Item Name="FTW-ERR-StatusOK.vi" Type="VI" URL="../src/core/error/FTW-ERR-StatusOK.vi"/>
				<Item Name="FTW-ERR-ThrowError.vi" Type="VI" URL="../src/core/error/FTW-ERR-ThrowError.vi"/>
				<Item Name="FTW-ERR-ThrowGenericError.vi" Type="VI" URL="../src/core/error/FTW-ERR-ThrowGenericError.vi"/>
				<Item Name="FTW-ERR-ThrowInfo.vi" Type="VI" URL="../src/core/error/FTW-ERR-ThrowInfo.vi"/>
				<Item Name="FTW-ERR-ThrowWarning.vi" Type="VI" URL="../src/core/error/FTW-ERR-ThrowWarning.vi"/>
				<Item Name="FTW-ERR-UnknownParameter.vi" Type="VI" URL="../src/core/error/FTW-ERR-UnknownParameter.vi"/>
			</Item>
			<Item Name="file" Type="Folder">
				<Item Name="FTW-File-CalculateRelativeFilepath.vi" Type="VI" URL="../src/core/file/FTW-File-CalculateRelativeFilepath.vi"/>
				<Item Name="FTW-File-CompareFilepaths.vi" Type="VI" URL="../src/core/file/FTW-File-CompareFilepaths.vi"/>
				<Item Name="FTW-File-CreateDirectory.vi" Type="VI" URL="../src/core/file/FTW-File-CreateDirectory.vi"/>
				<Item Name="FTW-File-Directory-Exists.vi" Type="VI" URL="../src/core/file/FTW-File-Directory-Exists.vi"/>
				<Item Name="FTW-File-Exists.vi" Type="VI" URL="../src/core/file/FTW-File-Exists.vi"/>
				<Item Name="FTW-File-Extension.vi" Type="VI" URL="../src/core/file/FTW-File-Extension.vi"/>
				<Item Name="FTW-File-FileInfo.vi" Type="VI" URL="../src/core/file/FTW-File-FileInfo.vi"/>
				<Item Name="FTW-File-GenerateLogFilename.vi" Type="VI" URL="../src/core/file/FTW-File-GenerateLogFilename.vi"/>
				<Item Name="FTW-File-IsRelative.vi" Type="VI" URL="../src/core/file/FTW-File-IsRelative.vi"/>
				<Item Name="FTW-File-ListDirectories.vi" Type="VI" URL="../src/core/file/FTW-File-ListDirectories.vi"/>
				<Item Name="FTW-File-ListDirectory-RegexFilter.vi" Type="VI" URL="../src/core/file/FTW-File-ListDirectory-RegexFilter.vi"/>
				<Item Name="FTW-File-RebaseFilepath.vi" Type="VI" URL="../src/core/file/FTW-File-RebaseFilepath.vi"/>
				<Item Name="FTW-File-Regex-Modify.vi" Type="VI" URL="../src/core/file/FTW-File-Regex-Modify.vi"/>
				<Item Name="FTW-File-ResolveSymbolicPaths.vi" Type="VI" URL="../src/core/file/FTW-File-ResolveSymbolicPaths.vi"/>
				<Item Name="FTW-File-ResourceDirectory.vi" Type="VI" URL="../src/core/file/FTW-File-ResourceDirectory.vi"/>
				<Item Name="FTW-File-SystemDirectories.vi" Type="VI" URL="../src/core/file/FTW-File-SystemDirectories.vi"/>
				<Item Name="FTW-File-TextRead.vi" Type="VI" URL="../src/core/file/FTW-File-TextRead.vi"/>
				<Item Name="FTW-File-TextWrite.vi" Type="VI" URL="../src/core/file/FTW-File-TextWrite.vi"/>
				<Item Name="FTW-File-UserDirectories.vi" Type="VI" URL="../src/core/file/FTW-File-UserDirectories.vi"/>
				<Item Name="FTW-File-ValidateFilepath.vi" Type="VI" URL="../src/core/file/FTW-File-ValidateFilepath.vi"/>
			</Item>
			<Item Name="json" Type="Folder">
				<Item Name="lib" Type="Folder">
					<Item Name="FTW-JSON-Core-ElementType.vi" Type="VI" URL="../src/core/json/lib/FTW-JSON-Core-ElementType.vi"/>
					<Item Name="FTW-JSON-Core-GetFlattenedValue.vi" Type="VI" URL="../src/core/json/lib/FTW-JSON-Core-GetFlattenedValue.vi"/>
					<Item Name="FTW-JSON-Core-LibraryError.vi" Type="VI" URL="../src/core/json/lib/FTW-JSON-Core-LibraryError.vi"/>
					<Item Name="FTW-JSON-Type.ctl" Type="VI" URL="../src/core/json/lib/FTW-JSON-Type.ctl"/>
				</Item>
				<Item Name="FTW-JSON-Deserialize.xnode" Type="XNode" URL="../src/core/json/FTW-JSON-Deserialize/FTW-JSON-Deserialize.xnode"/>
				<Item Name="FTW-JSON-ObjectManip-AddPair.vi" Type="VI" URL="../src/core/json/FTW-JSON-ObjectManip-AddPair.vi"/>
				<Item Name="FTW-JSON.lvclass" Type="LVClass" URL="../src/core/json/FTW-JSON.lvclass"/>
			</Item>
			<Item Name="numeric" Type="Folder">
				<Item Name="FTW-NUM-Counter.vi" Type="VI" URL="../src/core/numeric/FTW-NUM-Counter.vi"/>
				<Item Name="FTW-NUM-Increment.vi" Type="VI" URL="../src/core/numeric/FTW-NUM-Increment.vi"/>
				<Item Name="FTW-NUM-MovingAverage.vi" Type="VI" URL="../src/core/numeric/FTW-NUM-MovingAverage.vi"/>
			</Item>
			<Item Name="reflection" Type="Folder">
				<Item Name="FTW-Reflection-Array.vi" Type="VI" URL="../src/core/reflection/FTW-Reflection-Array.vi"/>
				<Item Name="FTW-Reflection-Cluster.vi" Type="VI" URL="../src/core/reflection/FTW-Reflection-Cluster.vi"/>
				<Item Name="FTW-Reflection-Enum.vi" Type="VI" URL="../src/core/reflection/FTW-Reflection-Enum.vi"/>
				<Item Name="FTW-Reflection-Type.vi" Type="VI" URL="../src/core/reflection/FTW-Reflection-Type.vi"/>
				<Item Name="FTW-Reflection-Types.ctl" Type="VI" URL="../src/core/reflection/FTW-Reflection-Types.ctl"/>
			</Item>
			<Item Name="regex" Type="Folder">
				<Item Name="core" Type="Folder"/>
				<Item Name="FTW-Regex-FilterArray.vi" Type="VI" URL="../src/core/regex/FTW-Regex-FilterArray.vi"/>
				<Item Name="FTW-Regex-ForceLiteral.vi" Type="VI" URL="../src/core/regex/FTW-Regex-ForceLiteral.vi"/>
				<Item Name="FTW-Regex-ReplaceAll.vi" Type="VI" URL="../src/core/regex/FTW-Regex-ReplaceAll.vi"/>
				<Item Name="FTW-Regex-ReplaceAndReturn.vi" Type="VI" URL="../src/core/regex/FTW-Regex-ReplaceAndReturn.vi"/>
				<Item Name="FTW-Regex-Replacements.vi" Type="VI" URL="../src/core/regex/FTW-Regex-Replacements.vi"/>
				<Item Name="FTW-Regex.vi" Type="VI" URL="../src/core/regex/FTW-Regex.vi"/>
			</Item>
			<Item Name="string" Type="Folder">
				<Item Name="FTW-STR-Array-Concatenate.vi" Type="VI" URL="../src/core/string/FTW-STR-Array-Concatenate.vi"/>
				<Item Name="FTW-STR-Array-Delimit.vi" Type="VI" URL="../src/core/string/FTW-STR-Array-Delimit.vi"/>
				<Item Name="FTW-STR-Display-Bytes.vi" Type="VI" URL="../src/core/string/FTW-STR-Display-Bytes.vi"/>
				<Item Name="FTW-STR-DisplayFormat-Bytes.ctl" Type="VI" URL="../src/core/string/FTW-STR-DisplayFormat-Bytes.ctl"/>
				<Item Name="FTW-STR-Encode-Base64.vi" Type="VI" URL="../src/core/string/FTW-STR-Encode-Base64.vi"/>
				<Item Name="FTW-STR-Encode-Hex.vi" Type="VI" URL="../src/core/string/FTW-STR-Encode-Hex.vi"/>
				<Item Name="FTW-STR-EncodingDirection.ctl" Type="VI" URL="../src/core/string/FTW-STR-EncodingDirection.ctl"/>
				<Item Name="FTW-STR-Explode.vi" Type="VI" URL="../src/core/string/FTW-STR-Explode.vi"/>
				<Item Name="FTW-STR-Indent.vi" Type="VI" URL="../src/core/string/FTW-STR-Indent.vi"/>
				<Item Name="FTW-STR-Random-Bytes.vi" Type="VI" URL="../src/core/string/FTW-STR-Random-Bytes.vi"/>
				<Item Name="FTW-STR-Random-Hex.vi" Type="VI" URL="../src/core/string/FTW-STR-Random-Hex.vi"/>
				<Item Name="FTW-STR-Random-UTF8chars.vi" Type="VI" URL="../src/core/string/FTW-STR-Random-UTF8chars.vi"/>
				<Item Name="FTW-STR-Repeat.vi" Type="VI" URL="../src/core/string/FTW-STR-Repeat.vi"/>
				<Item Name="FTW-STR-ReplaceAll.vi" Type="VI" URL="../src/core/string/FTW-STR-ReplaceAll.vi"/>
				<Item Name="FTW-STR-ReplaceWhitespace.vi" Type="VI" URL="../src/core/string/FTW-STR-ReplaceWhitespace.vi"/>
			</Item>
			<Item Name="sync" Type="Folder">
				<Item Name="barrier" Type="Folder">
					<Item Name="FTW-Sync-Synchronizer.xnode" Type="XNode" URL="../src/core/sync/barrier/FTW-Sync-Synchronizer.xnode"/>
				</Item>
			</Item>
			<Item Name="system" Type="Folder">
				<Item Name="FTW-System-CommandLineExecute.vi" Type="VI" URL="../src/core/system/FTW-System-CommandLineExecute.vi"/>
			</Item>
			<Item Name="time" Type="Folder">
				<Item Name="FTW-Time-Display-Elapsed.vi" Type="VI" URL="../src/core/time/FTW-Time-Display-Elapsed.vi"/>
				<Item Name="FTW-Time-Display-Timestamp.vi" Type="VI" URL="../src/core/time/FTW-Time-Display-Timestamp.vi"/>
				<Item Name="FTW-Time-DisplayFormat-Elapsed.ctl" Type="VI" URL="../src/core/time/FTW-Time-DisplayFormat-Elapsed.ctl"/>
				<Item Name="FTW-Time-DisplayFormat-Timestamp.ctl" Type="VI" URL="../src/core/time/FTW-Time-DisplayFormat-Timestamp.ctl"/>
				<Item Name="FTW-Time-Elapse.vi" Type="VI" URL="../src/core/time/FTW-Time-Elapse.vi"/>
				<Item Name="FTW-Time-Remaining.vi" Type="VI" URL="../src/core/time/FTW-Time-Remaining.vi"/>
				<Item Name="FTW-Time-RetryTimer.vi" Type="VI" URL="../src/core/time/FTW-Time-RetryTimer.vi"/>
				<Item Name="FTW-Time-Timer.vi" Type="VI" URL="../src/core/time/FTW-Time-Timer.vi"/>
				<Item Name="FTW-Time-Uptime.vi" Type="VI" URL="../src/core/time/FTW-Time-Uptime.vi"/>
			</Item>
			<Item Name="ui" Type="Folder">
				<Item Name="image" Type="Folder">
					<Item Name="FTW-Image-AppendToPicture.vi" Type="VI" URL="../src/core/ui/image/FTW-Image-AppendToPicture.vi"/>
					<Item Name="FTW-Image-ToPicture.vi" Type="VI" URL="../src/core/ui/image/FTW-Image-ToPicture.vi"/>
				</Item>
				<Item Name="menu" Type="Folder">
					<Item Name="FTW-Menu-BuildLevel.vi" Type="VI" URL="../src/core/ui/menu/FTW-Menu-BuildLevel.vi"/>
					<Item Name="FTW-Menu-DragDropDataAppend.vi" Type="VI" URL="../src/core/ui/menu/FTW-Menu-DragDropDataAppend.vi"/>
					<Item Name="FTW-Menu-Item.ctl" Type="VI" URL="../src/core/ui/menu/FTW-Menu-Item.ctl"/>
					<Item Name="FTW-Menu-TagDecode.vi" Type="VI" URL="../src/core/ui/menu/FTW-Menu-TagDecode.vi"/>
					<Item Name="FTW-Menu-TagEncode.vi" Type="VI" URL="../src/core/ui/menu/FTW-Menu-TagEncode.vi"/>
				</Item>
				<Item Name="os" Type="Folder">
					<Item Name="FTW-FileSystem-OpenDirectoryOrParent.vi" Type="VI" URL="../src/core/ui/os/FTW-FileSystem-OpenDirectoryOrParent.vi"/>
					<Item Name="FTW-FileSystem-OpenURIwithDefaultHandler.vi" Type="VI" URL="../src/core/ui/os/FTW-FileSystem-OpenURIwithDefaultHandler.vi"/>
				</Item>
				<Item Name="panel" Type="Folder">
					<Item Name="FTW-Panel-DeferPanelUpdates.vi" Type="VI" URL="../src/core/ui/panel/FTW-Panel-DeferPanelUpdates.vi"/>
					<Item Name="FTW-Panel-EnableControl.vi" Type="VI" URL="../src/core/ui/panel/FTW-Panel-EnableControl.vi"/>
					<Item Name="FTW-Panel-FrontPanel-Close.vi" Type="VI" URL="../src/core/ui/panel/FTW-Panel-FrontPanel-Close.vi"/>
					<Item Name="FTW-Panel-FrontPanel-Hide.vi" Type="VI" URL="../src/core/ui/panel/FTW-Panel-FrontPanel-Hide.vi"/>
					<Item Name="FTW-Panel-FrontPanel-Open.vi" Type="VI" URL="../src/core/ui/panel/FTW-Panel-FrontPanel-Open.vi"/>
					<Item Name="FTW-Panel-FrontPanel-SetCursor.vi" Type="VI" URL="../src/core/ui/panel/FTW-Panel-FrontPanel-SetCursor.vi"/>
				</Item>
				<Item Name="tree" Type="Folder">
					<Item Name="FTW-Tree-EditCell.vi" Type="VI" URL="../src/core/ui/tree/FTW-Tree-EditCell.vi"/>
					<Item Name="FTW-Tree-GetChildNodes.vi" Type="VI" URL="../src/core/ui/tree/FTW-Tree-GetChildNodes.vi"/>
					<Item Name="FTW-Tree-ItemToggleOpen.vi" Type="VI" URL="../src/core/ui/tree/FTW-Tree-ItemToggleOpen.vi"/>
					<Item Name="FTW-Tree-PointToItem.vi" Type="VI" URL="../src/core/ui/tree/FTW-Tree-PointToItem.vi"/>
				</Item>
			</Item>
			<Item Name="uri" Type="Folder">
				<Item Name="FTW-URI-Build.vi" Type="VI" URL="../src/core/uri/FTW-URI-Build.vi"/>
				<Item Name="FTW-URI-EscapeURL.vi" Type="VI" URL="../src/core/uri/FTW-URI-EscapeURL.vi"/>
				<Item Name="FTW-URI-FromFilepath.vi" Type="VI" URL="../src/core/uri/FTW-URI-FromFilepath.vi"/>
			</Item>
			<Item Name="viserver" Type="Folder">
				<Item Name="FTW-VIServer-AsyncCallOptions.vi" Type="VI" URL="../src/core/viserver/FTW-VIServer-AsyncCallOptions.vi"/>
				<Item Name="FTW-VIServer-GetClassDefaultData.vi" Type="VI" URL="../src/core/viserver/FTW-VIServer-GetClassDefaultData.vi"/>
				<Item Name="FTW-VIServer-LabVIEWinfo.vi" Type="VI" URL="../src/core/viserver/FTW-VIServer-LabVIEWinfo.vi"/>
				<Item Name="FTW-VIServer-OSinfo.vi" Type="VI" URL="../src/core/viserver/FTW-VIServer-OSinfo.vi"/>
				<Item Name="FTW-VIServer-VI-Metadata.vi" Type="VI" URL="../src/core/viserver/FTW-VIServer-VI-Metadata.vi"/>
			</Item>
		</Item>
		<Item Name="tests" Type="Folder">
			<Item Name="core" Type="Folder" URL="../tests/core">
				<Property Name="NI.DISK" Type="Bool">true</Property>
			</Item>
		</Item>
		<Item Name="FTW-Test.vi" Type="VI" URL="../tests/FTW-Test.vi"/>
		<Item Name="Dependencies" Type="Dependencies">
			<Item Name="vi.lib" Type="Folder">
				<Item Name="imagedata.ctl" Type="VI" URL="/&lt;vilib&gt;/picture/picture.llb/imagedata.ctl"/>
				<Item Name="Picture to Pixmap.vi" Type="VI" URL="/&lt;vilib&gt;/picture/pictutil.llb/Picture to Pixmap.vi"/>
				<Item Name="Rendezvous RefNum" Type="VI" URL="/&lt;vilib&gt;/Utility/rendezvs.llb/Rendezvous RefNum"/>
				<Item Name="Semaphore RefNum" Type="VI" URL="/&lt;vilib&gt;/Utility/semaphor.llb/Semaphore RefNum"/>
			</Item>
			<Item Name="FTW-ActorTemplate.vi" Type="VI" URL="../templates/FTW-ActorTemplate.vi"/>
			<Item Name="FTW-CodeGen-FindGObject.vi" Type="VI" URL="../src/codegen/FTW-CodeGen-FindGObject.vi"/>
			<Item Name="FTW-CodeGen-FindGObjects-Callback.vi" Type="VI" URL="../src/codegen/FTW-CodeGen-FindGObjects-Callback.vi"/>
			<Item Name="FTW-CodeGen-FindGObjects.vi" Type="VI" URL="../src/codegen/FTW-CodeGen-FindGObjects.vi"/>
			<Item Name="FTW-CodeGen-FindGObjectTaggedForScripting.vi" Type="VI" URL="../src/codegen/FTW-CodeGen-FindGObjectTaggedForScripting.vi"/>
			<Item Name="FTW-CodeGen-FindTerminalByID.vi" Type="VI" URL="../src/codegen/FTW-CodeGen-FindTerminalByID.vi"/>
			<Item Name="FTW-CodeGen-GetTerminals.vi" Type="VI" URL="../src/codegen/FTW-CodeGen-GetTerminals.vi"/>
			<Item Name="FTW-CodeGen-GetTypeInfo.vi" Type="VI" URL="../src/codegen/FTW-CodeGen-GetTypeInfo.vi"/>
			<Item Name="FTW-CodeGen-GetTypeInfoRemote.vi" Type="VI" URL="../src/codegen/FTW-CodeGen-GetTypeInfoRemote.vi"/>
			<Item Name="FTW-CodeGen-RelinkTerminals.vi" Type="VI" URL="../src/codegen/FTW-CodeGen-RelinkTerminals.vi"/>
			<Item Name="FTW-CodeGen-XNodeReply.vi" Type="VI" URL="../src/codegen/FTW-CodeGen-XNodeReply.vi"/>
			<Item Name="FTW-CodeGen-XNodeReplyType.ctl" Type="VI" URL="../src/codegen/FTW-CodeGen-XNodeReplyType.ctl"/>
			<Item Name="FTW-CodeGen-XNodeUpdateState.vi" Type="VI" URL="../src/codegen/FTW-CodeGen-XNodeUpdateState.vi"/>
			<Item Name="FTW-Collection-KeyValuePair.ctl" Type="VI" URL="../sandbox/deprecated/FTW-Collection-KeyValuePair.ctl"/>
			<Item Name="FTW-Image-Rectangle.vi" Type="VI" URL="../src/core/ui/image/FTW-Image-Rectangle.vi"/>
			<Item Name="FTW-JSON-Core-EncodingFlags.vi" Type="VI" URL="../src/core/json/lib/FTW-JSON-Core-EncodingFlags.vi"/>
			<Item Name="FTW-JSON-Escape.vi" Type="VI" URL="../sandbox/deprecated/FTW-JSON-Escape.vi"/>
			<Item Name="FTW-JSON-Format-String.vi" Type="VI" URL="../sandbox/deprecated/FTW-JSON-Format-String.vi"/>
			<Item Name="FTW-LibraryFilepath.vi" Type="VI" URL="../lib/FTW-LibraryFilepath.vi"/>
			<Item Name="ftw32.dll" Type="Document" URL="../lib/ftw32.dll"/>
			<Item Name="FTWLib-Jansson32.dll" Type="Document" URL="../lib/jansson/FTWLib-Jansson32.dll"/>
			<Item Name="FTWLib-Jansson32.so" Type="Document" URL="../lib/jansson/FTWLib-Jansson32.so"/>
			<Item Name="FTWLib-Jansson64.dll" Type="Document" URL="../lib/jansson/FTWLib-Jansson64.dll"/>
			<Item Name="FTWLib-JSON-LibraryFilepath.vi" Type="VI" URL="../lib/jansson/FTWLib-JSON-LibraryFilepath.vi"/>
			<Item Name="FTWLib-SQLite-LibraryFilepath.vi" Type="VI" URL="../lib/sqlite/FTWLib-SQLite-LibraryFilepath.vi"/>
			<Item Name="FTWLib-SQLite32.dll" Type="Document" URL="../lib/sqlite/FTWLib-SQLite32.dll"/>
			<Item Name="FTWLib-SQLite32.so" Type="Document" URL="../lib/sqlite/FTWLib-SQLite32.so"/>
			<Item Name="FTWLib-SQLite64.dll" Type="Document" URL="../lib/sqlite/FTWLib-SQLite64.dll"/>
			<Item Name="kernel32.dll" Type="Document" URL="kernel32.dll">
				<Property Name="NI.PreserveRelativePath" Type="Bool">true</Property>
			</Item>
		</Item>
		<Item Name="Build Specifications" Type="Build">
			<Item Name="Test" Type="EXE">
				<Property Name="App_INI_aliasGUID" Type="Str">{A6C5268F-58C5-4D8B-8DCE-9E7D5CA68FF7}</Property>
				<Property Name="App_INI_GUID" Type="Str">{8D01A6CB-7F2D-4620-AA38-1AC38A06BAF8}</Property>
				<Property Name="App_serverConfig.httpPort" Type="Int">8002</Property>
				<Property Name="Bld_autoIncrement" Type="Bool">true</Property>
				<Property Name="Bld_buildCacheID" Type="Str">{EF57F713-A9CB-4B69-ABA8-9EA0AD39F17D}</Property>
				<Property Name="Bld_buildSpecName" Type="Str">Test</Property>
				<Property Name="Bld_localDestDir" Type="Path">../build</Property>
				<Property Name="Bld_localDestDirType" Type="Str">relativeToProject</Property>
				<Property Name="Bld_previewCacheID" Type="Str">{DD5209A7-4460-4F06-B281-EEFFFFE8E6F1}</Property>
				<Property Name="Bld_version.build" Type="Int">30</Property>
				<Property Name="Bld_version.major" Type="Int">1</Property>
				<Property Name="Destination[0].destName" Type="Str">FTW-Test.exe</Property>
				<Property Name="Destination[0].path" Type="Path">../build/NI_AB_PROJECTNAME.exe</Property>
				<Property Name="Destination[0].path.type" Type="Str">relativeToProject</Property>
				<Property Name="Destination[0].preserveHierarchy" Type="Bool">true</Property>
				<Property Name="Destination[0].type" Type="Str">App</Property>
				<Property Name="Destination[1].destName" Type="Str">Support Directory</Property>
				<Property Name="Destination[1].path" Type="Path">../build/data</Property>
				<Property Name="Destination[1].path.type" Type="Str">relativeToProject</Property>
				<Property Name="DestinationCount" Type="Int">2</Property>
				<Property Name="Source[0].itemID" Type="Str">{BFCBE92A-C429-477E-8F7E-1FA9DDEFF2FE}</Property>
				<Property Name="Source[0].type" Type="Str">Container</Property>
				<Property Name="Source[1].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[1].itemID" Type="Ref"></Property>
				<Property Name="Source[1].type" Type="Str">VI</Property>
				<Property Name="Source[2].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[2].itemID" Type="Ref">/My Computer/FTW-Test.vi</Property>
				<Property Name="Source[2].sourceInclusion" Type="Str">TopLevel</Property>
				<Property Name="Source[2].type" Type="Str">VI</Property>
				<Property Name="Source[3].Container.applyDestination" Type="Bool">true</Property>
				<Property Name="Source[3].Container.applyInclusion" Type="Bool">true</Property>
				<Property Name="Source[3].Container.depDestIndex" Type="Int">0</Property>
				<Property Name="Source[3].destinationIndex" Type="Int">1</Property>
				<Property Name="Source[3].itemID" Type="Ref">/My Computer/tests/core</Property>
				<Property Name="Source[3].sourceInclusion" Type="Str">Include</Property>
				<Property Name="Source[3].type" Type="Str">Container</Property>
				<Property Name="Source[4].Container.applyDestination" Type="Bool">true</Property>
				<Property Name="Source[4].Container.depDestIndex" Type="Int">0</Property>
				<Property Name="Source[4].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[4].itemID" Type="Ref">/My Computer/ftw</Property>
				<Property Name="Source[4].type" Type="Str">Container</Property>
				<Property Name="SourceCount" Type="Int">5</Property>
				<Property Name="TgtF_companyName" Type="Str">Wirebird Labs LLC</Property>
				<Property Name="TgtF_fileDescription" Type="Str">Test</Property>
				<Property Name="TgtF_internalName" Type="Str">Test</Property>
				<Property Name="TgtF_legalCopyright" Type="Str">Copyright © 2014 Wirebird Labs LLC</Property>
				<Property Name="TgtF_productName" Type="Str">Test</Property>
				<Property Name="TgtF_targetfileGUID" Type="Str">{13863C70-152D-4603-9305-DF715873285F}</Property>
				<Property Name="TgtF_targetfileName" Type="Str">FTW-Test.exe</Property>
			</Item>
		</Item>
	</Item>
</Project>
