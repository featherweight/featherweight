<?xml version='1.0' encoding='UTF-8'?>
<Project Type="Project" LVVersion="13008000">
	<Property Name="NI.LV.All.SourceOnly" Type="Bool">true</Property>
	<Property Name="NI.Project.Description" Type="Str"></Property>
	<Item Name="My Computer" Type="My Computer">
		<Property Name="CCSymbols" Type="Str"></Property>
		<Property Name="NI.SortType" Type="Int">1</Property>
		<Property Name="server.app.propertiesEnabled" Type="Bool">false</Property>
		<Property Name="server.control.propertiesEnabled" Type="Bool">false</Property>
		<Property Name="server.tcp.acl" Type="Str">0800000008000000</Property>
		<Property Name="server.tcp.enabled" Type="Bool">false</Property>
		<Property Name="server.tcp.port" Type="Int">0</Property>
		<Property Name="server.tcp.serviceName" Type="Str"></Property>
		<Property Name="server.tcp.serviceName.default" Type="Str">My Computer/VI Server</Property>
		<Property Name="server.vi.access" Type="Str"></Property>
		<Property Name="server.vi.callsEnabled" Type="Bool">false</Property>
		<Property Name="server.vi.propertiesEnabled" Type="Bool">false</Property>
		<Property Name="server.viscripting.showScriptingOperationsInContextHelp" Type="Bool">false</Property>
		<Property Name="server.viscripting.showScriptingOperationsInEditor" Type="Bool">true</Property>
		<Property Name="specify.custom.address" Type="Bool">false</Property>
		<Item Name="Actor" Type="Folder">
			<Item Name="Support" Type="Folder">
				<Item Name="FTW-Actor-DynamicLaunchOptions.vi" Type="VI" URL="../core/actor/support/FTW-Actor-DynamicLaunchOptions.vi"/>
				<Item Name="FTW-Actor-ValidateAddress.vi" Type="VI" URL="../core/actor/support/FTW-Actor-ValidateAddress.vi"/>
			</Item>
			<Item Name="FTW-Actor-Connector.lvclass" Type="LVClass" URL="../core/actor/connector/FTW-Actor-Connector.lvclass"/>
			<Item Name="FTW-Actor-Context.lvclass" Type="LVClass" URL="../core/actor/context/FTW-Actor-Context.lvclass"/>
			<Item Name="FTW-Actor-Instance.lvclass" Type="LVClass" URL="../core/actor/instance/FTW-Actor-Instance.lvclass"/>
			<Item Name="FTW-Logger-Instance.lvclass" Type="LVClass" URL="../core/actor/logger/instance/FTW-Logger-Instance.lvclass"/>
			<Item Name="FTW-Logger.lvclass" Type="LVClass" URL="../core/actor/logger/FTW-Logger.lvclass"/>
			<Item Name="FTW-Message.lvclass" Type="LVClass" URL="../core/actor/message/FTW-Message.lvclass"/>
			<Item Name="FTW-Request.lvclass" Type="LVClass" URL="../core/actor/request/FTW-Request.lvclass"/>
			<Item Name="FTW-Router.lvclass" Type="LVClass" URL="../core/actor/router/FTW-Router.lvclass"/>
			<Item Name="FTW-Scheduler.lvclass" Type="LVClass" URL="../core/actor/scheduler/FTW-Scheduler.lvclass"/>
			<Item Name="FTW-Socket.lvclass" Type="LVClass" URL="../core/actor/socket/FTW-Socket.lvclass"/>
		</Item>
		<Item Name="Application" Type="Folder">
			<Item Name="FTW-App-StringToVersion.vi" Type="VI" URL="../core/application/FTW-App-StringToVersion.vi"/>
			<Item Name="FTW-App-StringVersionToString.vi" Type="VI" URL="../core/application/FTW-App-StringVersionToString.vi"/>
			<Item Name="FTW-App-VersionToString.vi" Type="VI" URL="../core/application/FTW-App-VersionToString.vi"/>
		</Item>
		<Item Name="Database" Type="Folder">
			<Item Name="FTW-SQLite-Connector.lvclass" Type="LVClass" URL="../core/database/FTW-SQLite-Connector.lvclass"/>
			<Item Name="FTW-SQLite-Fetch.xnode" Type="XNode" URL="../core/database/FTW-SQLite-Fetch/FTW-SQLite-Fetch.xnode"/>
			<Item Name="FTW-SQLite-Insert.xnode" Type="XNode" URL="../core/database/FTW-SQLite-Insert/FTW-SQLite-Insert.xnode"/>
		</Item>
		<Item Name="Email" Type="Folder">
			<Item Name="FTW-Email-AddressValidator.vi" Type="VI" URL="../core/email/FTW-Email-AddressValidator.vi"/>
		</Item>
		<Item Name="Error" Type="Folder">
			<Item Name="FTW-ERR-Assert-AbstractMethodCall.vi" Type="VI" URL="../core/error/FTW-ERR-Assert-AbstractMethodCall.vi"/>
			<Item Name="FTW-ERR-Assert-ConditionalDisable.vi" Type="VI" URL="../core/error/FTW-ERR-Assert-ConditionalDisable.vi"/>
			<Item Name="FTW-ERR-Assert-DeveloperError.vi" Type="VI" URL="../core/error/FTW-ERR-Assert-DeveloperError.vi"/>
			<Item Name="FTW-ERR-CallChain.vi" Type="VI" URL="../core/error/FTW-ERR-CallChain.vi"/>
			<Item Name="FTW-ERR-Clear.vi" Type="VI" URL="../core/error/FTW-ERR-Clear.vi"/>
			<Item Name="FTW-ERR-ExceptionType.ctl" Type="VI" URL="../core/error/FTW-ERR-ExceptionType.ctl"/>
			<Item Name="FTW-ERR-Ignore.vi" Type="VI" URL="../core/error/FTW-ERR-Ignore.vi"/>
			<Item Name="FTW-ERR-NoErrorConstant.vi" Type="VI" URL="../core/error/FTW-ERR-NoErrorConstant.vi"/>
			<Item Name="FTW-ERR-SerializeForLog.vi" Type="VI" URL="../core/error/FTW-ERR-SerializeForLog.vi"/>
			<Item Name="FTW-ERR-StatusError.vi" Type="VI" URL="../core/error/FTW-ERR-StatusError.vi"/>
			<Item Name="FTW-ERR-StatusException.vi" Type="VI" URL="../core/error/FTW-ERR-StatusException.vi"/>
			<Item Name="FTW-ERR-StatusOK.vi" Type="VI" URL="../core/error/FTW-ERR-StatusOK.vi"/>
			<Item Name="FTW-ERR-ThrowError.vi" Type="VI" URL="../core/error/FTW-ERR-ThrowError.vi"/>
			<Item Name="FTW-ERR-ThrowGenericError.vi" Type="VI" URL="../core/error/FTW-ERR-ThrowGenericError.vi"/>
			<Item Name="FTW-ERR-ThrowWarning.vi" Type="VI" URL="../core/error/FTW-ERR-ThrowWarning.vi"/>
			<Item Name="FTW-ERR-UnknownParameter.vi" Type="VI" URL="../core/error/FTW-ERR-UnknownParameter.vi"/>
		</Item>
		<Item Name="File" Type="Folder">
			<Item Name="FTW-File-CalculateRelativeFilepath.vi" Type="VI" URL="../core/file/FTW-File-CalculateRelativeFilepath.vi"/>
			<Item Name="FTW-File-CompareFilepaths.vi" Type="VI" URL="../core/file/FTW-File-CompareFilepaths.vi"/>
			<Item Name="FTW-File-CreateDirectory.vi" Type="VI" URL="../core/file/FTW-File-CreateDirectory.vi"/>
			<Item Name="FTW-File-Directory-Exists.vi" Type="VI" URL="../core/file/FTW-File-Directory-Exists.vi"/>
			<Item Name="FTW-File-Exists.vi" Type="VI" URL="../core/file/FTW-File-Exists.vi"/>
			<Item Name="FTW-File-Extension.vi" Type="VI" URL="../core/file/FTW-File-Extension.vi"/>
			<Item Name="FTW-File-FileInfo.vi" Type="VI" URL="../core/file/FTW-File-FileInfo.vi"/>
			<Item Name="FTW-File-FindLibrary.vi" Type="VI" URL="../core/file/FTW-File-FindLibrary.vi"/>
			<Item Name="FTW-File-GenerateLogFilename.vi" Type="VI" URL="../core/file/FTW-File-GenerateLogFilename.vi"/>
			<Item Name="FTW-File-IsRelative.vi" Type="VI" URL="../core/file/FTW-File-IsRelative.vi"/>
			<Item Name="FTW-File-ListDirectories.vi" Type="VI" URL="../core/file/FTW-File-ListDirectories.vi"/>
			<Item Name="FTW-File-ListDirectory-RegexFilter.vi" Type="VI" URL="../core/file/FTW-File-ListDirectory-RegexFilter.vi"/>
			<Item Name="FTW-File-RebaseFilepath.vi" Type="VI" URL="../core/file/FTW-File-RebaseFilepath.vi"/>
			<Item Name="FTW-File-Regex-Modify.vi" Type="VI" URL="../core/file/FTW-File-Regex-Modify.vi"/>
			<Item Name="FTW-File-ResolveSymbolicPaths.vi" Type="VI" URL="../core/file/FTW-File-ResolveSymbolicPaths.vi"/>
			<Item Name="FTW-File-ResourceDirectory.vi" Type="VI" URL="../core/file/FTW-File-ResourceDirectory.vi"/>
			<Item Name="FTW-File-SystemDirectories.vi" Type="VI" URL="../core/file/FTW-File-SystemDirectories.vi"/>
			<Item Name="FTW-File-TextRead.vi" Type="VI" URL="../core/file/FTW-File-TextRead.vi"/>
			<Item Name="FTW-File-TextWrite.vi" Type="VI" URL="../core/file/FTW-File-TextWrite.vi"/>
			<Item Name="FTW-File-UserDirectories.vi" Type="VI" URL="../core/file/FTW-File-UserDirectories.vi"/>
			<Item Name="FTW-File-ValidateFilepath.vi" Type="VI" URL="../core/file/FTW-File-ValidateFilepath.vi"/>
		</Item>
		<Item Name="HTTP" Type="Folder">
			<Item Name="FTW-HTTP-MIMEtype.ctl" Type="VI" URL="../core/http/FTW-HTTP-MIMEtype.ctl"/>
			<Item Name="FTW-HTTP-ParseResponseHeaders.vi" Type="VI" URL="../core/http/FTW-HTTP-ParseResponseHeaders.vi"/>
			<Item Name="FTW-HTTP-ResponseCode.ctl" Type="VI" URL="../core/http/FTW-HTTP-ResponseCode.ctl"/>
			<Item Name="FTW-HTTPClient.lvclass" Type="LVClass" URL="../core/http/client/FTW-HTTPClient.lvclass"/>
		</Item>
		<Item Name="JSON" Type="Folder">
			<Item Name="FTW-JSON-Deserialize.xnode" Type="XNode" URL="../core/json/FTW-JSON-Deserialize/FTW-JSON-Deserialize.xnode"/>
			<Item Name="FTW-JSON-ObjectManip-AddPair.vi" Type="VI" URL="../core/json/FTW-JSON-ObjectManip-AddPair.vi"/>
			<Item Name="FTW-JSON.lvclass" Type="LVClass" URL="../core/json/FTW-JSON.lvclass"/>
		</Item>
		<Item Name="Numeric" Type="Folder">
			<Item Name="FTW-NUM-Counter.vi" Type="VI" URL="../core/numeric/FTW-NUM-Counter.vi"/>
			<Item Name="FTW-NUM-Increment.vi" Type="VI" URL="../core/numeric/FTW-NUM-Increment.vi"/>
			<Item Name="FTW-NUM-MovingAverage.vi" Type="VI" URL="../core/numeric/FTW-NUM-MovingAverage.vi"/>
		</Item>
		<Item Name="Reflection" Type="Folder">
			<Item Name="FTW-Reflection-Array.vi" Type="VI" URL="../core/reflection/FTW-Reflection-Array.vi"/>
			<Item Name="FTW-Reflection-Cluster.vi" Type="VI" URL="../core/reflection/FTW-Reflection-Cluster.vi"/>
			<Item Name="FTW-Reflection-Enum.vi" Type="VI" URL="../core/reflection/FTW-Reflection-Enum.vi"/>
			<Item Name="FTW-Reflection-Type.vi" Type="VI" URL="../core/reflection/FTW-Reflection-Type.vi"/>
			<Item Name="FTW-Reflection-Types.ctl" Type="VI" URL="../core/reflection/FTW-Reflection-Types.ctl"/>
		</Item>
		<Item Name="Regex" Type="Folder">
			<Item Name="FTW-Regex-FilterArray.vi" Type="VI" URL="../core/regex/FTW-Regex-FilterArray.vi"/>
			<Item Name="FTW-Regex-ForceLiteral.vi" Type="VI" URL="../core/regex/FTW-Regex-ForceLiteral.vi"/>
			<Item Name="FTW-Regex-ReplaceAll.vi" Type="VI" URL="../core/regex/FTW-Regex-ReplaceAll.vi"/>
			<Item Name="FTW-Regex-ReplaceAndReturn.vi" Type="VI" URL="../core/regex/FTW-Regex-ReplaceAndReturn.vi"/>
			<Item Name="FTW-Regex-Replacements.vi" Type="VI" URL="../core/regex/FTW-Regex-Replacements.vi"/>
			<Item Name="FTW-Regex.vi" Type="VI" URL="../core/regex/FTW-Regex.vi"/>
		</Item>
		<Item Name="String" Type="Folder">
			<Item Name="FTW-STR-Array-Concatenate.vi" Type="VI" URL="../core/string/FTW-STR-Array-Concatenate.vi"/>
			<Item Name="FTW-STR-Array-Delimit.vi" Type="VI" URL="../core/string/FTW-STR-Array-Delimit.vi"/>
			<Item Name="FTW-STR-Display-Bytes.vi" Type="VI" URL="../core/string/FTW-STR-Display-Bytes.vi"/>
			<Item Name="FTW-STR-DisplayFormat-Bytes.ctl" Type="VI" URL="../core/string/FTW-STR-DisplayFormat-Bytes.ctl"/>
			<Item Name="FTW-STR-Encode-Base64.vi" Type="VI" URL="../core/string/FTW-STR-Encode-Base64.vi"/>
			<Item Name="FTW-STR-Encode-Hex.vi" Type="VI" URL="../core/string/FTW-STR-Encode-Hex.vi"/>
			<Item Name="FTW-STR-EncodingDirection.ctl" Type="VI" URL="../core/string/FTW-STR-EncodingDirection.ctl"/>
			<Item Name="FTW-STR-Indent.vi" Type="VI" URL="../core/string/FTW-STR-Indent.vi"/>
			<Item Name="FTW-STR-Random-Bytes.vi" Type="VI" URL="../core/string/FTW-STR-Random-Bytes.vi"/>
			<Item Name="FTW-STR-Random-Hex.vi" Type="VI" URL="../core/string/FTW-STR-Random-Hex.vi"/>
			<Item Name="FTW-STR-Random-UTF8chars.vi" Type="VI" URL="../core/string/FTW-STR-Random-UTF8chars.vi"/>
			<Item Name="FTW-STR-Repeat.vi" Type="VI" URL="../core/string/FTW-STR-Repeat.vi"/>
			<Item Name="FTW-STR-ReplaceAll.vi" Type="VI" URL="../core/string/FTW-STR-ReplaceAll.vi"/>
			<Item Name="FTW-STR-ReplaceWhitespace.vi" Type="VI" URL="../core/string/FTW-STR-ReplaceWhitespace.vi"/>
		</Item>
		<Item Name="System" Type="Folder">
			<Item Name="FTW-System-CommandLineExecute.vi" Type="VI" URL="../core/system/FTW-System-CommandLineExecute.vi"/>
		</Item>
		<Item Name="Time" Type="Folder">
			<Item Name="FTW-Time-Display-Elapsed.vi" Type="VI" URL="../core/time/FTW-Time-Display-Elapsed.vi"/>
			<Item Name="FTW-Time-Display-Timestamp.vi" Type="VI" URL="../core/time/FTW-Time-Display-Timestamp.vi"/>
			<Item Name="FTW-Time-DisplayFormat-Elapsed.ctl" Type="VI" URL="../core/time/FTW-Time-DisplayFormat-Elapsed.ctl"/>
			<Item Name="FTW-Time-DisplayFormat-Timestamp.ctl" Type="VI" URL="../core/time/FTW-Time-DisplayFormat-Timestamp.ctl"/>
			<Item Name="FTW-Time-Elapse.vi" Type="VI" URL="../core/time/FTW-Time-Elapse.vi"/>
			<Item Name="FTW-Time-Remaining.vi" Type="VI" URL="../core/time/FTW-Time-Remaining.vi"/>
			<Item Name="FTW-Time-RetryTimer.vi" Type="VI" URL="../core/time/FTW-Time-RetryTimer.vi"/>
			<Item Name="FTW-Time-Timer.vi" Type="VI" URL="../core/time/FTW-Time-Timer.vi"/>
			<Item Name="FTW-Time-Uptime.vi" Type="VI" URL="../core/time/FTW-Time-Uptime.vi"/>
		</Item>
		<Item Name="UI" Type="Folder">
			<Item Name="Image" Type="Folder">
				<Item Name="FTW-Image-AppendToPicture.vi" Type="VI" URL="../core/ui/image/FTW-Image-AppendToPicture.vi"/>
				<Item Name="FTW-Image-ToPicture.vi" Type="VI" URL="../core/ui/image/FTW-Image-ToPicture.vi"/>
			</Item>
			<Item Name="Menu" Type="Folder">
				<Item Name="FTW-Menu-BuildLevel.vi" Type="VI" URL="../core/ui/menu/FTW-Menu-BuildLevel.vi"/>
				<Item Name="FTW-Menu-DragDropDataAppend.vi" Type="VI" URL="../core/ui/menu/FTW-Menu-DragDropDataAppend.vi"/>
				<Item Name="FTW-Menu-Item.ctl" Type="VI" URL="../core/ui/menu/FTW-Menu-Item.ctl"/>
				<Item Name="FTW-Menu-TagDecode.vi" Type="VI" URL="../core/ui/menu/FTW-Menu-TagDecode.vi"/>
				<Item Name="FTW-Menu-TagEncode.vi" Type="VI" URL="../core/ui/menu/FTW-Menu-TagEncode.vi"/>
			</Item>
			<Item Name="OS" Type="Folder">
				<Item Name="FTW-FileSystem-OpenDirectoryOrParent.vi" Type="VI" URL="../core/ui/os/FTW-FileSystem-OpenDirectoryOrParent.vi"/>
				<Item Name="FTW-FileSystem-OpenURIwithDefaultHandler.vi" Type="VI" URL="../core/ui/os/FTW-FileSystem-OpenURIwithDefaultHandler.vi"/>
			</Item>
			<Item Name="Panel" Type="Folder">
				<Item Name="FTW-Panel-DeferPanelUpdates.vi" Type="VI" URL="../core/ui/panel/FTW-Panel-DeferPanelUpdates.vi"/>
				<Item Name="FTW-Panel-EnableControl.vi" Type="VI" URL="../core/ui/panel/FTW-Panel-EnableControl.vi"/>
				<Item Name="FTW-Panel-FrontPanel-Close.vi" Type="VI" URL="../core/ui/panel/FTW-Panel-FrontPanel-Close.vi"/>
				<Item Name="FTW-Panel-FrontPanel-Hide.vi" Type="VI" URL="../core/ui/panel/FTW-Panel-FrontPanel-Hide.vi"/>
				<Item Name="FTW-Panel-FrontPanel-Open.vi" Type="VI" URL="../core/ui/panel/FTW-Panel-FrontPanel-Open.vi"/>
				<Item Name="FTW-Panel-FrontPanel-SetCursor.vi" Type="VI" URL="../core/ui/panel/FTW-Panel-FrontPanel-SetCursor.vi"/>
			</Item>
			<Item Name="Tree" Type="Folder">
				<Item Name="FTW-Tree-EditCell.vi" Type="VI" URL="../core/ui/tree/FTW-Tree-EditCell.vi"/>
				<Item Name="FTW-Tree-GetChildNodes.vi" Type="VI" URL="../core/ui/tree/FTW-Tree-GetChildNodes.vi"/>
				<Item Name="FTW-Tree-ItemToggleOpen.vi" Type="VI" URL="../core/ui/tree/FTW-Tree-ItemToggleOpen.vi"/>
				<Item Name="FTW-Tree-PointToItem.vi" Type="VI" URL="../core/ui/tree/FTW-Tree-PointToItem.vi"/>
			</Item>
		</Item>
		<Item Name="URI" Type="Folder">
			<Item Name="FTW-URI-Build.vi" Type="VI" URL="../core/uri/FTW-URI-Build.vi"/>
			<Item Name="FTW-URI-EscapeURL.vi" Type="VI" URL="../core/uri/FTW-URI-EscapeURL.vi"/>
			<Item Name="FTW-URI-FromFilepath.vi" Type="VI" URL="../core/uri/FTW-URI-FromFilepath.vi"/>
		</Item>
		<Item Name="Utils" Type="Folder">
			<Item Name="probes" Type="Folder">
				<Item Name="FTW-Probe-String.vi" Type="VI" URL="../../utils/probes/FTW-Probe-String.vi"/>
			</Item>
			<Item Name="FTW-DevUtil-CreateNewActor.vi" Type="VI" URL="../../utils/FTW-DevUtil-CreateNewActor.vi"/>
			<Item Name="FTW-DevUtil-FrontPanelCleanup.vi" Type="VI" URL="../../utils/FTW-DevUtil-FrontPanelCleanup.vi"/>
			<Item Name="FTW-DevUtil-RegisterProbes.vi" Type="VI" URL="../../utils/FTW-DevUtil-RegisterProbes.vi"/>
			<Item Name="FTW-DevUtil-XNode-AddItem.vi" Type="VI" URL="../../utils/FTW-DevUtil-XNode-AddItem.vi"/>
		</Item>
		<Item Name="VI Server" Type="Folder">
			<Item Name="FTW-VIServer-AsyncCallOptions.vi" Type="VI" URL="../core/viserver/FTW-VIServer-AsyncCallOptions.vi"/>
			<Item Name="FTW-VIServer-GetClassDefaultData.vi" Type="VI" URL="../core/viserver/FTW-VIServer-GetClassDefaultData.vi"/>
			<Item Name="FTW-VIServer-LabVIEWinfo.vi" Type="VI" URL="../core/viserver/FTW-VIServer-LabVIEWinfo.vi"/>
			<Item Name="FTW-VIServer-OSinfo.vi" Type="VI" URL="../core/viserver/FTW-VIServer-OSinfo.vi"/>
			<Item Name="FTW-VIServer-VI-Metadata.vi" Type="VI" URL="../core/viserver/FTW-VIServer-VI-Metadata.vi"/>
		</Item>
		<Item Name="Dependencies" Type="Dependencies">
			<Item Name="FTW-CodeGen.lvlib" Type="Library" URL="../codegen/FTW-CodeGen.lvlib"/>
			<Item Name="FTW-Collection-KeyValuePair.ctl" Type="VI" URL="../../sandbox/deprecated/FTW-Collection-KeyValuePair.ctl"/>
			<Item Name="FTW-JSON-Core-ElementType.vi" Type="VI" URL="../core/json/lib/FTW-JSON-Core-ElementType.vi"/>
			<Item Name="FTW-JSON-Core-GetFlattenedValue.vi" Type="VI" URL="../core/json/lib/FTW-JSON-Core-GetFlattenedValue.vi"/>
			<Item Name="FTW-JSON-Core-LibraryError.vi" Type="VI" URL="../core/json/lib/FTW-JSON-Core-LibraryError.vi"/>
			<Item Name="FTW-JSON-Core-LibraryFilepath.vi" Type="VI" URL="../core/json/lib/FTW-JSON-Core-LibraryFilepath.vi"/>
			<Item Name="FTW-JSON-Escape.vi" Type="VI" URL="../../sandbox/deprecated/FTW-JSON-Escape.vi"/>
			<Item Name="FTW-JSON-Format-String.vi" Type="VI" URL="../../sandbox/deprecated/FTW-JSON-Format-String.vi"/>
			<Item Name="FTW-JSON-Type.ctl" Type="VI" URL="../core/json/lib/FTW-JSON-Type.ctl"/>
			<Item Name="FTW-Socket-Core-LibraryFilepath.vi" Type="VI" URL="../core/actor/socket/FTW-Socket-Core-LibraryFilepath.vi"/>
			<Item Name="FTWLib-Jansson-LinuxRT.so" Type="Document" URL="../core/json/lib/FTWLib-Jansson-LinuxRT.so"/>
			<Item Name="FTWLib-Jansson-Win32.dll" Type="Document" URL="../core/json/lib/FTWLib-Jansson-Win32.dll"/>
			<Item Name="FTWLib-Jansson-Win64.dll" Type="Document" URL="../core/json/lib/FTWLib-Jansson-Win64.dll"/>
			<Item Name="FTWLib-nanomsg-LinuxRT.vi" Type="VI" URL="../../lib/nanomsg/FTWLib-nanomsg-LinuxRT.vi"/>
			<Item Name="FTWLib-nanomsg-Win32.vi" Type="VI" URL="../../lib/nanomsg/FTWLib-nanomsg-Win32.vi"/>
			<Item Name="FTWLib-nanomsg-Win64.vi" Type="VI" URL="../../lib/nanomsg/FTWLib-nanomsg-Win64.vi"/>
			<Item Name="FTWLib-nanomsg32.dll" Type="Document" URL="../../lib/nanomsg/FTWLib-nanomsg32.dll"/>
			<Item Name="FTWLib-nanomsg32.so" Type="Document" URL="../../lib/nanomsg/FTWLib-nanomsg32.so"/>
			<Item Name="FTWLib-nanomsg64.dll" Type="Document" URL="../../lib/nanomsg/FTWLib-nanomsg64.dll"/>
			<Item Name="FTWLib-SQLite3-LinuxRT.so" Type="Document" URL="../core/database/lib/FTWLib-SQLite3-LinuxRT.so"/>
			<Item Name="FTWLib-SQLite3-Win32.dll" Type="Document" URL="../core/database/lib/FTWLib-SQLite3-Win32.dll"/>
			<Item Name="FTWLib-SQLite3-Win64.dll" Type="Document" URL="../core/database/lib/FTWLib-SQLite3-Win64.dll"/>
		</Item>
		<Item Name="Build Specifications" Type="Build"/>
	</Item>
</Project>
