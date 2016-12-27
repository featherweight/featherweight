<?xml version='1.0' encoding='UTF-8'?>
<Project Type="Project" LVVersion="15008000">
	<Property Name="NI.LV.All.SourceOnly" Type="Bool">true</Property>
	<Property Name="NI.Project.Description" Type="Str"></Property>
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
		<Item Name="_codegen" Type="Folder">
			<Item Name="codegen" Type="Folder">
				<Item Name="FTW-CodeGen-ChooseImplementation.vi" Type="VI" URL="../codegen/FTW-CodeGen-ChooseImplementation.vi"/>
				<Item Name="FTW-CodeGen-CleanUpWires.vi" Type="VI" URL="../codegen/FTW-CodeGen-CleanUpWires.vi"/>
				<Item Name="FTW-CodeGen-FindGObject.vi" Type="VI" URL="../codegen/FTW-CodeGen-FindGObject.vi"/>
				<Item Name="FTW-CodeGen-FindGObjects-Callback.vi" Type="VI" URL="../codegen/FTW-CodeGen-FindGObjects-Callback.vi"/>
				<Item Name="FTW-CodeGen-FindGObjects.vi" Type="VI" URL="../codegen/FTW-CodeGen-FindGObjects.vi"/>
				<Item Name="FTW-CodeGen-FindGObjectTaggedForScripting.vi" Type="VI" URL="../codegen/FTW-CodeGen-FindGObjectTaggedForScripting.vi"/>
				<Item Name="FTW-CodeGen-FindTerminalByID.vi" Type="VI" URL="../codegen/FTW-CodeGen-FindTerminalByID.vi"/>
				<Item Name="FTW-CodeGen-FindTerminalTypeByID.vi" Type="VI" URL="../codegen/FTW-CodeGen-FindTerminalTypeByID.vi"/>
				<Item Name="FTW-CodeGen-GetTerminals.vi" Type="VI" URL="../codegen/FTW-CodeGen-GetTerminals.vi"/>
				<Item Name="FTW-CodeGen-GetTypeInfo.vi" Type="VI" URL="../codegen/FTW-CodeGen-GetTypeInfo.vi"/>
				<Item Name="FTW-CodeGen-GetTypeInfoRemote.vi" Type="VI" URL="../codegen/FTW-CodeGen-GetTypeInfoRemote.vi"/>
				<Item Name="FTW-CodeGen-OneGObjectOrNone.vi" Type="VI" URL="../codegen/FTW-CodeGen-OneGObjectOrNone.vi"/>
				<Item Name="FTW-CodeGen-RegenerateAfterAdapt.vi" Type="VI" URL="../codegen/FTW-CodeGen-RegenerateAfterAdapt.vi"/>
				<Item Name="FTW-CodeGen-RelinkTerminals.vi" Type="VI" URL="../codegen/FTW-CodeGen-RelinkTerminals.vi"/>
				<Item Name="FTW-CodeGen-SetConstantValue.vi" Type="VI" URL="../codegen/FTW-CodeGen-SetConstantValue.vi"/>
				<Item Name="FTW-CodeGen-XNodeReply.vi" Type="VI" URL="../codegen/FTW-CodeGen-XNodeReply.vi"/>
				<Item Name="FTW-CodeGen-XNodeReplyType.ctl" Type="VI" URL="../codegen/FTW-CodeGen-XNodeReplyType.ctl"/>
				<Item Name="FTW-CodeGen-XNodeUpdateState.vi" Type="VI" URL="../codegen/FTW-CodeGen-XNodeUpdateState.vi"/>
			</Item>
			<Item Name="support" Type="Folder">
				<Item Name="FTW-CodeGen-Image-AppendToPicture.vi" Type="VI" URL="../codegen/support/FTW-CodeGen-Image-AppendToPicture.vi"/>
				<Item Name="FTW-CodeGen-Image-Rectangle.vi" Type="VI" URL="../codegen/support/FTW-CodeGen-Image-Rectangle.vi"/>
				<Item Name="FTW-CodeGen-Image-Subset.vi" Type="VI" URL="../codegen/support/FTW-CodeGen-Image-Subset.vi"/>
				<Item Name="FTW-CodeGen-Image-ToPicture.vi" Type="VI" URL="../codegen/support/FTW-CodeGen-Image-ToPicture.vi"/>
			</Item>
			<Item Name="FTW-Actor-Ask.xnode" Type="XNode" URL="../codegen/xnode/FTW-Actor-Ask.xnode"/>
			<Item Name="FTW-Actor-Spawn.xnode" Type="XNode" URL="../codegen/xnode/FTW-Actor-Spawn.xnode"/>
			<Item Name="FTW-Array-Shuffle.xnode" Type="XNode" URL="../codegen/xnode/FTW-Array-Shuffle.xnode"/>
			<Item Name="FTW-Dataflow-Synchronizer.xnode" Type="XNode" URL="../codegen/xnode/FTW-Dataflow-Synchronizer.xnode"/>
			<Item Name="FTW-dotNet-SQL-Fetch.xnode" Type="XNode" URL="../codegen/xnode/FTW-dotNet-SQL-Fetch.xnode"/>
			<Item Name="FTW-dotNet-SQL-Insert.xnode" Type="XNode" URL="../codegen/xnode/FTW-dotNet-SQL-Insert.xnode"/>
			<Item Name="FTW-JSON-Fetch.xnode" Type="XNode" URL="../codegen/xnode/FTW-JSON-Fetch.xnode"/>
			<Item Name="FTW-SQLite-Fetch.xnode" Type="XNode" URL="../codegen/xnode/FTW-SQLite-Fetch.xnode"/>
			<Item Name="FTW-SQLite-Insert.xnode" Type="XNode" URL="../codegen/xnode/FTW-SQLite-Insert.xnode"/>
		</Item>
		<Item Name="_kernel" Type="Folder">
			<Item Name="FTW-KernelFilepath.vi" Type="VI" URL="../lib/FTW-KernelFilepath.vi"/>
			<Item Name="ftw32.dll" Type="Document" URL="../lib/ftw32.dll"/>
		</Item>
		<Item Name="_utils" Type="Folder">
			<Item Name="linker" Type="Folder">
				<Item Name="FTW-Linker-DecodeBitmap.vi" Type="VI" URL="../utils/linker/FTW-Linker-DecodeBitmap.vi"/>
				<Item Name="FTW-Linker-Flags-buttons.ctl" Type="VI" URL="../utils/linker/FTW-Linker-Flags-buttons.ctl"/>
				<Item Name="FTW-Linker-Flags-iState.ctl" Type="VI" URL="../utils/linker/FTW-Linker-Flags-iState.ctl"/>
				<Item Name="FTW-Linker-Flags-iStyle.ctl" Type="VI" URL="../utils/linker/FTW-Linker-Flags-iStyle.ctl"/>
				<Item Name="FTW-Linker-Flags-viflags.ctl" Type="VI" URL="../utils/linker/FTW-Linker-Flags-viflags.ctl"/>
				<Item Name="FTW-Linker-Flags-viflags2.ctl" Type="VI" URL="../utils/linker/FTW-Linker-Flags-viflags2.ctl"/>
				<Item Name="FTW-Linker-Flags-wStyle.ctl" Type="VI" URL="../utils/linker/FTW-Linker-Flags-wStyle.ctl"/>
				<Item Name="FTW-Linker-LabVIEWFiletype.ctl" Type="VI" URL="../utils/linker/FTW-Linker-LabVIEWFiletype.ctl"/>
				<Item Name="FTW-Linker-LinkerInfoStructure.ctl" Type="VI" URL="../utils/linker/FTW-Linker-LinkerInfoStructure.ctl"/>
				<Item Name="FTW-Linker-LVFileStaticLinks.vi" Type="VI" URL="../utils/linker/FTW-Linker-LVFileStaticLinks.vi"/>
			</Item>
			<Item Name="metrics" Type="Folder">
				<Item Name="FTW-DevUtil-VIMetrics.vi" Type="VI" URL="../utils/metrics/FTW-DevUtil-VIMetrics.vi"/>
			</Item>
			<Item Name="FTW-DevUtil-FrontPanelCleanup.vi" Type="VI" URL="../utils/FTW-DevUtil-FrontPanelCleanup.vi"/>
			<Item Name="FTW-DevUtil-VIDetails.vi" Type="VI" URL="../utils/FTW-DevUtil-VIDetails.vi"/>
		</Item>
		<Item Name="ftw" Type="Folder">
			<Item Name="actor" Type="Folder">
				<Item Name="connector" Type="Folder">
					<Item Name="FTW-Connector-Construct.vi" Type="VI" URL="../src/socket/connector/FTW-Connector-Construct.vi"/>
					<Item Name="FTW-Connector-Core-Ask.vi" Type="VI" URL="../src/socket/connector/core/FTW-Connector-Core-Ask.vi"/>
					<Item Name="FTW-Connector-Destroy.vi" Type="VI" URL="../src/socket/connector/FTW-Connector-Destroy.vi"/>
					<Item Name="FTW-Connector-QueryActorInstanceStatus.vi" Type="VI" URL="../src/socket/connector/FTW-Connector-QueryActorInstanceStatus.vi"/>
					<Item Name="FTW-Connector-SendPoisonPill.vi" Type="VI" URL="../src/socket/connector/FTW-Connector-SendPoisonPill.vi"/>
				</Item>
				<Item Name="inbox" Type="Folder">
					<Item Name="core" Type="Folder">
						<Item Name="FTW-Inbox-Core-Configuration.vi" Type="VI" URL="../src/socket/inbox/core/FTW-Inbox-Core-Configuration.vi"/>
						<Item Name="FTW-Inbox-Core-ConstructMessagePipe.vi" Type="VI" URL="../src/socket/inbox/core/FTW-Inbox-Core-ConstructMessagePipe.vi"/>
						<Item Name="FTW-Inbox-Core-ConstructMessageRouter.vi" Type="VI" URL="../src/socket/inbox/core/FTW-Inbox-Core-ConstructMessageRouter.vi"/>
						<Item Name="FTW-Inbox-Core-LoadMessageRouterPrototype.vi" Type="VI" URL="../src/socket/inbox/core/FTW-Inbox-Core-LoadMessageRouterPrototype.vi"/>
						<Item Name="FTW-Inbox-Core-MessageRouter.vi" Type="VI" URL="../src/socket/inbox/core/FTW-Inbox-Core-MessageRouter.vi"/>
						<Item Name="FTW-Inbox-Core-RoutingRule.ctl" Type="VI" URL="../src/socket/inbox/core/FTW-Inbox-Core-RoutingRule.ctl"/>
					</Item>
					<Item Name="FTW-Inbox-Construct.vi" Type="VI" URL="../src/socket/inbox/FTW-Inbox-Construct.vi"/>
					<Item Name="FTW-Inbox-Destroy.vi" Type="VI" URL="../src/socket/inbox/FTW-Inbox-Destroy.vi"/>
				</Item>
				<Item Name="publisher" Type="Folder">
					<Item Name="FTW-Publisher-Construct.vi" Type="VI" URL="../src/socket/publisher/FTW-Publisher-Construct.vi"/>
					<Item Name="FTW-Publisher-Destroy.vi" Type="VI" URL="../src/socket/publisher/FTW-Publisher-Destroy.vi"/>
					<Item Name="FTW-Publisher-Publish.vi" Type="VI" URL="../src/socket/publisher/FTW-Publisher-Publish.vi"/>
				</Item>
				<Item Name="request" Type="Folder">
					<Property Name="NI.SortType" Type="Int">3</Property>
					<Item Name="core" Type="Folder">
						<Item Name="FTW-Request-Core-InterpretResponse.vi" Type="VI" URL="../src/actor/request/core/FTW-Request-Core-InterpretResponse.vi"/>
					</Item>
					<Item Name="FTW-Request-AddMetaData.vi" Type="VI" URL="../src/actor/request/FTW-Request-AddMetaData.vi"/>
					<Item Name="FTW-Request-InterpretResponse.vi" Type="VI" URL="../src/actor/request/FTW-Request-InterpretResponse.vi"/>
					<Item Name="FTW-Request-Receive.vi" Type="VI" URL="../src/actor/request/FTW-Request-Receive.vi"/>
					<Item Name="FTW-Request-Reply.vi" Type="VI" URL="../src/actor/request/FTW-Request-Reply.vi"/>
					<Item Name="FTW-Request-ReplyToPoisonPill.vi" Type="VI" URL="../src/actor/request/FTW-Request-ReplyToPoisonPill.vi"/>
					<Item Name="FTW-Request-Unknown.vi" Type="VI" URL="../src/actor/request/FTW-Request-Unknown.vi"/>
				</Item>
				<Item Name="subscriber" Type="Folder">
					<Item Name="FTW-Subscriber-Construct.vi" Type="VI" URL="../src/socket/subscriber/FTW-Subscriber-Construct.vi"/>
					<Item Name="FTW-Subscriber-Destroy.vi" Type="VI" URL="../src/socket/subscriber/FTW-Subscriber-Destroy.vi"/>
				</Item>
				<Item Name="supervisor" Type="Folder">
					<Item Name="core" Type="Folder">
						<Item Name="FTW-Supervisor-Core-SerializeEvent.vi" Type="VI" URL="../src/actor/supervisor/core/FTW-Supervisor-Core-SerializeEvent.vi"/>
						<Item Name="FTW-Supervisor.lvclass" Type="LVClass" URL="../src/actor/supervisor/core/FTW-Supervisor.lvclass"/>
					</Item>
					<Item Name="FTW-Supervisor-Connect.vi" Type="VI" URL="../src/actor/supervisor/FTW-Supervisor-Connect.vi"/>
					<Item Name="FTW-Supervisor-Launch.vi" Type="VI" URL="../src/actor/supervisor/FTW-Supervisor-Launch.vi"/>
					<Item Name="FTW-Supervisor-LogEvent.vi" Type="VI" URL="../src/actor/supervisor/FTW-Supervisor-LogEvent.vi"/>
					<Item Name="FTW-Supervisor-Shutdown.vi" Type="VI" URL="../src/actor/supervisor/FTW-Supervisor-Shutdown.vi"/>
				</Item>
				<Item Name="support" Type="Folder">
					<Item Name="FTW-Actor-CloneName.vi" Type="VI" URL="../src/actor/support/FTW-Actor-CloneName.vi"/>
					<Item Name="FTW-Actor-DynamicLaunchOptions.vi" Type="VI" URL="../src/actor/support/FTW-Actor-DynamicLaunchOptions.vi"/>
					<Item Name="FTW-Socket-Core-ReturnCode.vi" Type="VI" URL="../src/socket/support/FTW-Socket-Core-ReturnCode.vi"/>
					<Item Name="FTW-Socket-Core-TransportScheme.ctl" Type="VI" URL="../src/socket/support/FTW-Socket-Core-TransportScheme.ctl"/>
					<Item Name="FTW-Socket-Core-ValidateAddress.vi" Type="VI" URL="../src/socket/support/FTW-Socket-Core-ValidateAddress.vi"/>
				</Item>
				<Item Name="FTW-Actor-Instance.lvclass" Type="LVClass" URL="../src/actor/instance/FTW-Actor-Instance.lvclass"/>
				<Item Name="FTW-Scheduler.lvclass" Type="LVClass" URL="../src/actor/scheduler/FTW-Scheduler.lvclass"/>
			</Item>
			<Item Name="application" Type="Folder">
				<Item Name="FTW-App-StringToVersion.vi" Type="VI" URL="../src/application/FTW-App-StringToVersion.vi"/>
				<Item Name="FTW-App-StringVersionToString.vi" Type="VI" URL="../src/application/FTW-App-StringVersionToString.vi"/>
				<Item Name="FTW-App-VersionToString.vi" Type="VI" URL="../src/application/FTW-App-VersionToString.vi"/>
			</Item>
			<Item Name="core" Type="Folder">
				<Item Name="type" Type="Folder">
					<Item Name="FTW-Type-Actor-Connector.ctl" Type="VI" URL="../src/core/type/FTW-Type-Actor-Connector.ctl"/>
					<Item Name="FTW-Type-Actor-Inbox.ctl" Type="VI" URL="../src/core/type/FTW-Type-Actor-Inbox.ctl"/>
					<Item Name="FTW-Type-JSON.ctl" Type="VI" URL="../src/core/type/FTW-Type-JSON.ctl"/>
					<Item Name="FTW-Type-Regex.ctl" Type="VI" URL="../src/core/type/FTW-Type-Regex.ctl"/>
					<Item Name="FTW-Type-Socket-Consumer.ctl" Type="VI" URL="../src/core/type/FTW-Type-Socket-Consumer.ctl"/>
					<Item Name="FTW-Type-Socket-Producer.ctl" Type="VI" URL="../src/core/type/FTW-Type-Socket-Producer.ctl"/>
					<Item Name="FTW-Type-Socket-Publisher.ctl" Type="VI" URL="../src/core/type/FTW-Type-Socket-Publisher.ctl"/>
					<Item Name="FTW-Type-Socket-Subscriber.ctl" Type="VI" URL="../src/core/type/FTW-Type-Socket-Subscriber.ctl"/>
					<Item Name="FTW-Type-SQLite.ctl" Type="VI" URL="../src/core/type/FTW-Type-SQLite.ctl"/>
				</Item>
			</Item>
			<Item Name="database" Type="Folder">
				<Item Name="core" Type="Folder">
					<Item Name="FTW-SQLite-Core-AccessMode.ctl" Type="VI" URL="../src/database/core/FTW-SQLite-Core-AccessMode.ctl"/>
					<Item Name="FTW-SQLite-Core-Construct.vi" Type="VI" URL="../src/database/core/FTW-SQLite-Core-Construct.vi"/>
					<Item Name="FTW-SQLite-Core-DatabaseType.ctl" Type="VI" URL="../src/database/core/FTW-SQLite-Core-DatabaseType.ctl"/>
					<Item Name="FTW-SQLite-Core-LibraryReturnValue.vi" Type="VI" URL="../src/database/core/FTW-SQLite-Core-LibraryReturnValue.vi"/>
					<Item Name="FTW-SQLite-Core-PrepareStatement.vi" Type="VI" URL="../src/database/core/FTW-SQLite-Core-PrepareStatement.vi"/>
					<Item Name="FTW-SQLite-Core-QueryDebug.vi" Type="VI" URL="../src/database/core/FTW-SQLite-Core-QueryDebug.vi"/>
				</Item>
				<Item Name="FTW-SQLite-Backup.vi" Type="VI" URL="../src/database/FTW-SQLite-Backup.vi"/>
				<Item Name="FTW-SQLite-CloseConnection.vi" Type="VI" URL="../src/database/FTW-SQLite-CloseConnection.vi"/>
				<Item Name="FTW-SQLite-CreateEphemeralDatabase.vi" Type="VI" URL="../src/database/FTW-SQLite-CreateEphemeralDatabase.vi"/>
				<Item Name="FTW-SQLite-ExecuteScript.vi" Type="VI" URL="../src/database/FTW-SQLite-ExecuteScript.vi"/>
				<Item Name="FTW-SQLite-OpenConnection-Path.vi" Type="VI" URL="../src/database/FTW-SQLite-OpenConnection-Path.vi"/>
				<Item Name="FTW-SQLite-RandomBLOB.vi" Type="VI" URL="../src/database/FTW-SQLite-RandomBLOB.vi"/>
			</Item>
			<Item Name="dataflow" Type="Folder">
				<Item Name="FTW-Dataflow-Parallelize.vi" Type="VI" URL="../src/dataflow/FTW-Dataflow-Parallelize.vi"/>
			</Item>
			<Item Name="email" Type="Folder">
				<Item Name="FTW-Email-AddressValidator.vi" Type="VI" URL="../src/email/FTW-Email-AddressValidator.vi"/>
			</Item>
			<Item Name="error" Type="Folder">
				<Item Name="FTW-ERR-Assert-AbstractMethodCall.vi" Type="VI" URL="../src/error/FTW-ERR-Assert-AbstractMethodCall.vi"/>
				<Item Name="FTW-ERR-Assert-ConditionalDisable.vi" Type="VI" URL="../src/error/FTW-ERR-Assert-ConditionalDisable.vi"/>
				<Item Name="FTW-ERR-Assert-DeveloperError.vi" Type="VI" URL="../src/error/FTW-ERR-Assert-DeveloperError.vi"/>
				<Item Name="FTW-ERR-Assert-Truthy.vi" Type="VI" URL="../src/error/FTW-ERR-Assert-Truthy.vi"/>
				<Item Name="FTW-ERR-CallChain.vi" Type="VI" URL="../src/error/FTW-ERR-CallChain.vi"/>
				<Item Name="FTW-ERR-Clear.vi" Type="VI" URL="../src/error/FTW-ERR-Clear.vi"/>
				<Item Name="FTW-ERR-ExceptionType.ctl" Type="VI" URL="../src/error/FTW-ERR-ExceptionType.ctl"/>
				<Item Name="FTW-ERR-Explanation.vi" Type="VI" URL="../src/error/FTW-ERR-Explanation.vi"/>
				<Item Name="FTW-ERR-Ignore.vi" Type="VI" URL="../src/error/FTW-ERR-Ignore.vi"/>
				<Item Name="FTW-ERR-NoErrorConstant.vi" Type="VI" URL="../src/error/FTW-ERR-NoErrorConstant.vi"/>
				<Item Name="FTW-ERR-PrependExplanation.vi" Type="VI" URL="../src/error/FTW-ERR-PrependExplanation.vi"/>
				<Item Name="FTW-ERR-SerializeForLog.vi" Type="VI" URL="../src/error/FTW-ERR-SerializeForLog.vi"/>
				<Item Name="FTW-ERR-StatusError.vi" Type="VI" URL="../src/error/FTW-ERR-StatusError.vi"/>
				<Item Name="FTW-ERR-StatusException.vi" Type="VI" URL="../src/error/FTW-ERR-StatusException.vi"/>
				<Item Name="FTW-ERR-StatusOK.vi" Type="VI" URL="../src/error/FTW-ERR-StatusOK.vi"/>
				<Item Name="FTW-ERR-ThrowError.vi" Type="VI" URL="../src/error/FTW-ERR-ThrowError.vi"/>
				<Item Name="FTW-ERR-ThrowGenericError.vi" Type="VI" URL="../src/error/FTW-ERR-ThrowGenericError.vi"/>
				<Item Name="FTW-ERR-ThrowInfo.vi" Type="VI" URL="../src/error/FTW-ERR-ThrowInfo.vi"/>
				<Item Name="FTW-ERR-ThrowInvalidReferenceError.vi" Type="VI" URL="../src/error/FTW-ERR-ThrowInvalidReferenceError.vi"/>
				<Item Name="FTW-ERR-ThrowWarning.vi" Type="VI" URL="../src/error/FTW-ERR-ThrowWarning.vi"/>
			</Item>
			<Item Name="expression" Type="Folder">
				<Item Name="FTW-Expr-BooleanExpressionResult.ctl" Type="VI" URL="../src/expression/FTW-Expr-BooleanExpressionResult.ctl"/>
				<Item Name="FTW-Expression-Lexicon-Engine.txt" Type="Document" URL="../src/expression/FTW-Expression-Lexicon-Engine.txt"/>
				<Item Name="FTW-Expression-Lexicon.txt" Type="Document" URL="../src/expression/FTW-Expression-Lexicon.txt"/>
				<Item Name="FTW-Expression.lvclass" Type="LVClass" URL="../src/expression/FTW-Expression.lvclass"/>
			</Item>
			<Item Name="file" Type="Folder">
				<Item Name="FTW-File-CalculateRelativeFilepath.vi" Type="VI" URL="../src/file/FTW-File-CalculateRelativeFilepath.vi"/>
				<Item Name="FTW-File-CompareFilepaths.vi" Type="VI" URL="../src/file/FTW-File-CompareFilepaths.vi"/>
				<Item Name="FTW-File-CreateDirectory.vi" Type="VI" URL="../src/file/FTW-File-CreateDirectory.vi"/>
				<Item Name="FTW-File-Directory-Exists.vi" Type="VI" URL="../src/file/FTW-File-Directory-Exists.vi"/>
				<Item Name="FTW-File-Exists.vi" Type="VI" URL="../src/file/FTW-File-Exists.vi"/>
				<Item Name="FTW-File-Extension.vi" Type="VI" URL="../src/file/FTW-File-Extension.vi"/>
				<Item Name="FTW-File-FileInfo.vi" Type="VI" URL="../src/file/FTW-File-FileInfo.vi"/>
				<Item Name="FTW-File-IsRelative.vi" Type="VI" URL="../src/file/FTW-File-IsRelative.vi"/>
				<Item Name="FTW-File-ListDirectories.vi" Type="VI" URL="../src/file/FTW-File-ListDirectories.vi"/>
				<Item Name="FTW-File-ListDirectory-RegexFilter.vi" Type="VI" URL="../src/file/FTW-File-ListDirectory-RegexFilter.vi"/>
				<Item Name="FTW-File-RebaseFilepath.vi" Type="VI" URL="../src/file/FTW-File-RebaseFilepath.vi"/>
				<Item Name="FTW-File-ResolveSymbolicPaths.vi" Type="VI" URL="../src/file/FTW-File-ResolveSymbolicPaths.vi"/>
				<Item Name="FTW-File-ResourceDirectory.vi" Type="VI" URL="../src/file/FTW-File-ResourceDirectory.vi"/>
				<Item Name="FTW-File-SystemDirectories.vi" Type="VI" URL="../src/file/FTW-File-SystemDirectories.vi"/>
				<Item Name="FTW-File-TextRead.vi" Type="VI" URL="../src/file/FTW-File-TextRead.vi"/>
				<Item Name="FTW-File-TextWrite.vi" Type="VI" URL="../src/file/FTW-File-TextWrite.vi"/>
				<Item Name="FTW-File-UserDirectories.vi" Type="VI" URL="../src/file/FTW-File-UserDirectories.vi"/>
				<Item Name="FTW-File-ValidateFilepath.vi" Type="VI" URL="../src/file/FTW-File-ValidateFilepath.vi"/>
			</Item>
			<Item Name="http" Type="Folder">
				<Item Name="FTW-HTTP-MIMEtype.ctl" Type="VI" URL="../src/http/FTW-HTTP-MIMEtype.ctl"/>
				<Item Name="FTW-HTTP-ParseResponseHeaders.vi" Type="VI" URL="../src/http/FTW-HTTP-ParseResponseHeaders.vi"/>
				<Item Name="FTW-HTTP-ResponseCode.ctl" Type="VI" URL="../src/http/FTW-HTTP-ResponseCode.ctl"/>
				<Item Name="FTW-HTTPClient.lvclass" Type="LVClass" URL="../src/http/client/FTW-HTTPClient.lvclass"/>
			</Item>
			<Item Name="json" Type="Folder">
				<Item Name="core" Type="Folder">
					<Item Name="FTW-JSON-Core-ElementType.vi" Type="VI" URL="../src/json/core/FTW-JSON-Core-ElementType.vi"/>
					<Item Name="FTW-JSON-Core-EncodingFlags.vi" Type="VI" URL="../src/json/core/FTW-JSON-Core-EncodingFlags.vi"/>
					<Item Name="FTW-JSON-Core-Type.ctl" Type="VI" URL="../src/json/core/FTW-JSON-Core-Type.ctl"/>
				</Item>
				<Item Name="FTW-JSON-CompareEquality.vi" Type="VI" URL="../src/json/FTW-JSON-CompareEquality.vi"/>
				<Item Name="FTW-JSON-Construct-FromBuffer.vi" Type="VI" URL="../src/json/FTW-JSON-Construct-FromBuffer.vi"/>
				<Item Name="FTW-JSON-Construct-NewObject.vi" Type="VI" URL="../src/json/FTW-JSON-Construct-NewObject.vi"/>
				<Item Name="FTW-JSON-Destroy.vi" Type="VI" URL="../src/json/FTW-JSON-Destroy.vi"/>
				<Item Name="FTW-JSON-Duplicate.vi" Type="VI" URL="../src/json/FTW-JSON-Duplicate.vi"/>
				<Item Name="FTW-JSON-JoinMode.ctl" Type="VI" URL="../src/json/FTW-JSON-JoinMode.ctl"/>
				<Item Name="FTW-JSON-Object-DeleteAllElements.vi" Type="VI" URL="../src/json/FTW-JSON-Object-DeleteAllElements.vi"/>
				<Item Name="FTW-JSON-Object-DeleteElement.vi" Type="VI" URL="../src/json/FTW-JSON-Object-DeleteElement.vi"/>
				<Item Name="FTW-JSON-Object-GetElement-Bool.vi" Type="VI" URL="../src/json/FTW-JSON-Object-GetElement-Bool.vi"/>
				<Item Name="FTW-JSON-Object-GetElement-DBL.vi" Type="VI" URL="../src/json/FTW-JSON-Object-GetElement-DBL.vi"/>
				<Item Name="FTW-JSON-Object-GetElement-Integer.vi" Type="VI" URL="../src/json/FTW-JSON-Object-GetElement-Integer.vi"/>
				<Item Name="FTW-JSON-Object-GetElement-String.vi" Type="VI" URL="../src/json/FTW-JSON-Object-GetElement-String.vi"/>
				<Item Name="FTW-JSON-Object-Join-String.vi" Type="VI" URL="../src/json/FTW-JSON-Object-Join-String.vi"/>
				<Item Name="FTW-JSON-Object-Join.vi" Type="VI" URL="../src/json/FTW-JSON-Object-Join.vi"/>
				<Item Name="FTW-JSON-Object-Keys.vi" Type="VI" URL="../src/json/FTW-JSON-Object-Keys.vi"/>
				<Item Name="FTW-JSON-Object-SetElement-Bool.vi" Type="VI" URL="../src/json/FTW-JSON-Object-SetElement-Bool.vi"/>
				<Item Name="FTW-JSON-Object-SetElement-DBL.vi" Type="VI" URL="../src/json/FTW-JSON-Object-SetElement-DBL.vi"/>
				<Item Name="FTW-JSON-Object-SetElement-Integer.vi" Type="VI" URL="../src/json/FTW-JSON-Object-SetElement-Integer.vi"/>
				<Item Name="FTW-JSON-Object-SetElement-null.vi" Type="VI" URL="../src/json/FTW-JSON-Object-SetElement-null.vi"/>
				<Item Name="FTW-JSON-Object-SetElement-String.vi" Type="VI" URL="../src/json/FTW-JSON-Object-SetElement-String.vi"/>
				<Item Name="FTW-JSON-ObjectManip-AddPair.vi" Type="VI" URL="../src/json/FTW-JSON-ObjectManip-AddPair.vi"/>
				<Item Name="FTW-JSON-Serialize.vi" Type="VI" URL="../src/json/FTW-JSON-Serialize.vi"/>
				<Item Name="FTW-JSON-SerializeAndDestroy.vi" Type="VI" URL="../src/json/FTW-JSON-SerializeAndDestroy.vi"/>
				<Item Name="FTW-JSON-SerializeElement.vi" Type="VI" URL="../src/json/FTW-JSON-SerializeElement.vi"/>
				<Item Name="FTW-JSON-SetFlags-Encoding.vi" Type="VI" URL="../src/json/FTW-JSON-SetFlags-Encoding.vi"/>
				<Item Name="FTW-JSON-Type.ctl" Type="VI" URL="../src/json/FTW-JSON-Type.ctl"/>
			</Item>
			<Item Name="math" Type="Folder">
				<Item Name="FTW-Math-Counter.vi" Type="VI" URL="../src/math/FTW-Math-Counter.vi"/>
				<Item Name="FTW-Math-Increment.vi" Type="VI" URL="../src/math/FTW-Math-Increment.vi"/>
				<Item Name="FTW-Math-MovingAverage.vi" Type="VI" URL="../src/math/FTW-Math-MovingAverage.vi"/>
				<Item Name="FTW-Math-Statistics.vi" Type="VI" URL="../src/math/FTW-Math-Statistics.vi"/>
			</Item>
			<Item Name="reflection" Type="Folder">
				<Item Name="core" Type="Folder">
					<Item Name="FTW-Reflection-ConPaneInterface-Function.ctl" Type="VI" URL="../src/reflection/core/FTW-Reflection-ConPaneInterface-Function.ctl"/>
					<Item Name="FTW-Reflection-ConPaneInterface-Terminal.ctl" Type="VI" URL="../src/reflection/core/FTW-Reflection-ConPaneInterface-Terminal.ctl"/>
				</Item>
				<Item Name="FTW-Reflection-Array.vi" Type="VI" URL="../src/reflection/FTW-Reflection-Array.vi"/>
				<Item Name="FTW-Reflection-Cluster.vi" Type="VI" URL="../src/reflection/FTW-Reflection-Cluster.vi"/>
				<Item Name="FTW-Reflection-ConPaneInterface.vi" Type="VI" URL="../src/reflection/FTW-Reflection-ConPaneInterface.vi"/>
				<Item Name="FTW-Reflection-Enum.vi" Type="VI" URL="../src/reflection/FTW-Reflection-Enum.vi"/>
				<Item Name="FTW-Reflection-FTWObject.vi" Type="VI" URL="../src/reflection/FTW-Reflection-FTWObject.vi"/>
				<Item Name="FTW-Reflection-Type.vi" Type="VI" URL="../src/reflection/FTW-Reflection-Type.vi"/>
				<Item Name="FTW-Reflection-TypeDescriptorToDefaultData.vi" Type="VI" URL="../src/reflection/FTW-Reflection-TypeDescriptorToDefaultData.vi"/>
				<Item Name="FTW-Reflection-Types.ctl" Type="VI" URL="../src/reflection/FTW-Reflection-Types.ctl"/>
			</Item>
			<Item Name="regex" Type="Folder">
				<Item Name="FTW-Regex-CapturingGroups.vi" Type="VI" URL="../src/regex/FTW-Regex-CapturingGroups.vi"/>
				<Item Name="FTW-Regex-Construct.vi" Type="VI" URL="../src/regex/FTW-Regex-Construct.vi"/>
				<Item Name="FTW-Regex-Destroy.vi" Type="VI" URL="../src/regex/FTW-Regex-Destroy.vi"/>
				<Item Name="FTW-Regex-Execute.vi" Type="VI" URL="../src/regex/FTW-Regex-Execute.vi"/>
				<Item Name="FTW-Regex-FilterArray.vi" Type="VI" URL="../src/regex/FTW-Regex-FilterArray.vi"/>
				<Item Name="FTW-Regex-ForceLiteral.vi" Type="VI" URL="../src/regex/FTW-Regex-ForceLiteral.vi"/>
				<Item Name="FTW-Regex-ReplaceAll.vi" Type="VI" URL="../src/regex/FTW-Regex-ReplaceAll.vi"/>
				<Item Name="FTW-Regex-ReplaceAndReturn.vi" Type="VI" URL="../src/regex/FTW-Regex-ReplaceAndReturn.vi"/>
				<Item Name="FTW-Regex.vi" Type="VI" URL="../src/regex/FTW-Regex.vi"/>
			</Item>
			<Item Name="string" Type="Folder">
				<Item Name="FTW-STR-Array-Concatenate.vi" Type="VI" URL="../src/string/FTW-STR-Array-Concatenate.vi"/>
				<Item Name="FTW-STR-Array-Delimit.vi" Type="VI" URL="../src/string/FTW-STR-Array-Delimit.vi"/>
				<Item Name="FTW-STR-Display-Bytes.vi" Type="VI" URL="../src/string/FTW-STR-Display-Bytes.vi"/>
				<Item Name="FTW-STR-DisplayFormat-Bytes.ctl" Type="VI" URL="../src/string/FTW-STR-DisplayFormat-Bytes.ctl"/>
				<Item Name="FTW-STR-Encode-Base64.vi" Type="VI" URL="../src/string/FTW-STR-Encode-Base64.vi"/>
				<Item Name="FTW-STR-Encode-Hex.vi" Type="VI" URL="../src/string/FTW-STR-Encode-Hex.vi"/>
				<Item Name="FTW-STR-EncodingDirection.ctl" Type="VI" URL="../src/string/FTW-STR-EncodingDirection.ctl"/>
				<Item Name="FTW-STR-Explode.vi" Type="VI" URL="../src/string/FTW-STR-Explode.vi"/>
				<Item Name="FTW-STR-Indent.vi" Type="VI" URL="../src/string/FTW-STR-Indent.vi"/>
				<Item Name="FTW-STR-Random-Bytes.vi" Type="VI" URL="../src/string/FTW-STR-Random-Bytes.vi"/>
				<Item Name="FTW-STR-Random-Hex.vi" Type="VI" URL="../src/string/FTW-STR-Random-Hex.vi"/>
				<Item Name="FTW-STR-Repeat.vi" Type="VI" URL="../src/string/FTW-STR-Repeat.vi"/>
				<Item Name="FTW-STR-ReplaceAll.vi" Type="VI" URL="../src/string/FTW-STR-ReplaceAll.vi"/>
				<Item Name="FTW-STR-ReplaceWhitespace.vi" Type="VI" URL="../src/string/FTW-STR-ReplaceWhitespace.vi"/>
			</Item>
			<Item Name="system" Type="Folder">
				<Item Name="core" Type="Folder">
					<Item Name="FTW-System-CommandLineToArgv.vi" Type="VI" URL="../src/system/core/FTW-System-CommandLineToArgv.vi"/>
				</Item>
				<Item Name="FTW-System-CommandLineExecute.vi" Type="VI" URL="../src/system/FTW-System-CommandLineExecute.vi"/>
				<Item Name="FTW-System-CPULoadAverage.vi" Type="VI" URL="../src/system/FTW-System-CPULoadAverage.vi"/>
				<Item Name="FTW-System-CurrentProcessResourceUsage.vi" Type="VI" URL="../src/system/FTW-System-CurrentProcessResourceUsage.vi"/>
			</Item>
			<Item Name="time" Type="Folder">
				<Item Name="FTW-Time-Display-Elapsed.vi" Type="VI" URL="../src/time/FTW-Time-Display-Elapsed.vi"/>
				<Item Name="FTW-Time-Display-Timestamp.vi" Type="VI" URL="../src/time/FTW-Time-Display-Timestamp.vi"/>
				<Item Name="FTW-Time-DisplayFormat-Elapsed.ctl" Type="VI" URL="../src/time/FTW-Time-DisplayFormat-Elapsed.ctl"/>
				<Item Name="FTW-Time-DisplayFormat-Timestamp.ctl" Type="VI" URL="../src/time/FTW-Time-DisplayFormat-Timestamp.ctl"/>
				<Item Name="FTW-Time-RelativeTimer.vi" Type="VI" URL="../src/time/FTW-Time-RelativeTimer.vi"/>
				<Item Name="FTW-Time-Remaining.vi" Type="VI" URL="../src/time/FTW-Time-Remaining.vi"/>
			</Item>
			<Item Name="ui" Type="Folder">
				<Item Name="menu" Type="Folder">
					<Item Name="FTW-Menu-BuildLevel.vi" Type="VI" URL="../src/ui/menu/FTW-Menu-BuildLevel.vi"/>
					<Item Name="FTW-Menu-Item.ctl" Type="VI" URL="../src/ui/menu/FTW-Menu-Item.ctl"/>
				</Item>
				<Item Name="os" Type="Folder">
					<Item Name="FTW-FileSystem-OpenDirectoryOrParent.vi" Type="VI" URL="../src/ui/os/FTW-FileSystem-OpenDirectoryOrParent.vi"/>
					<Item Name="FTW-FileSystem-OpenURIwithDefaultHandler.vi" Type="VI" URL="../src/ui/os/FTW-FileSystem-OpenURIwithDefaultHandler.vi"/>
				</Item>
				<Item Name="panel" Type="Folder">
					<Item Name="FTW-Panel-DeferPanelUpdates.vi" Type="VI" URL="../src/ui/panel/FTW-Panel-DeferPanelUpdates.vi"/>
					<Item Name="FTW-Panel-EnableControl.vi" Type="VI" URL="../src/ui/panel/FTW-Panel-EnableControl.vi"/>
					<Item Name="FTW-Panel-FrontPanel-Close.vi" Type="VI" URL="../src/ui/panel/FTW-Panel-FrontPanel-Close.vi"/>
					<Item Name="FTW-Panel-FrontPanel-Hide.vi" Type="VI" URL="../src/ui/panel/FTW-Panel-FrontPanel-Hide.vi"/>
					<Item Name="FTW-Panel-FrontPanel-Open.vi" Type="VI" URL="../src/ui/panel/FTW-Panel-FrontPanel-Open.vi"/>
					<Item Name="FTW-Panel-FrontPanel-SetCursor.vi" Type="VI" URL="../src/ui/panel/FTW-Panel-FrontPanel-SetCursor.vi"/>
				</Item>
				<Item Name="tree" Type="Folder">
					<Item Name="FTW-Tree-EditCell.vi" Type="VI" URL="../src/ui/tree/FTW-Tree-EditCell.vi"/>
					<Item Name="FTW-Tree-GetChildNodes.vi" Type="VI" URL="../src/ui/tree/FTW-Tree-GetChildNodes.vi"/>
					<Item Name="FTW-Tree-ItemToggleOpen.vi" Type="VI" URL="../src/ui/tree/FTW-Tree-ItemToggleOpen.vi"/>
					<Item Name="FTW-Tree-PointToItem.vi" Type="VI" URL="../src/ui/tree/FTW-Tree-PointToItem.vi"/>
				</Item>
			</Item>
			<Item Name="uri" Type="Folder">
				<Item Name="FTW-URI-Build.vi" Type="VI" URL="../src/uri/FTW-URI-Build.vi"/>
				<Item Name="FTW-URI-EscapeURL.vi" Type="VI" URL="../src/uri/FTW-URI-EscapeURL.vi"/>
				<Item Name="FTW-URI-FromFilepath.vi" Type="VI" URL="../src/uri/FTW-URI-FromFilepath.vi"/>
			</Item>
			<Item Name="viserver" Type="Folder">
				<Item Name="FTW-VIServer-AsyncCallOptions.vi" Type="VI" URL="../src/viserver/FTW-VIServer-AsyncCallOptions.vi"/>
				<Item Name="FTW-VIServer-GetClassDefaultData.vi" Type="VI" URL="../src/viserver/FTW-VIServer-GetClassDefaultData.vi"/>
				<Item Name="FTW-VIServer-LabVIEWinfo.vi" Type="VI" URL="../src/viserver/FTW-VIServer-LabVIEWinfo.vi"/>
				<Item Name="FTW-VIServer-OSinfo.vi" Type="VI" URL="../src/viserver/FTW-VIServer-OSinfo.vi"/>
				<Item Name="FTW-VIServer-VI-Metadata.vi" Type="VI" URL="../src/viserver/FTW-VIServer-VI-Metadata.vi"/>
			</Item>
			<Item Name="windows" Type="Folder">
				<Item Name="file" Type="Folder">
					<Item Name="FTW-File-FileVersion.vi" Type="VI" URL="../src/windows/file/FTW-File-FileVersion.vi"/>
				</Item>
				<Item Name="security" Type="Folder">
					<Item Name="FTW-Crypto-AES256.vi" Type="VI" URL="../src/windows/security/FTW-Crypto-AES256.vi"/>
					<Item Name="FTW-Crypto-FileHash.vi" Type="VI" URL="../src/windows/security/FTW-Crypto-FileHash.vi"/>
					<Item Name="FTW-Crypto-HMAC-Hasher.vi" Type="VI" URL="../src/windows/security/FTW-Crypto-HMAC-Hasher.vi"/>
					<Item Name="FTW-Crypto-PublicKeySignature-GenerateKeys.vi" Type="VI" URL="../src/windows/security/FTW-Crypto-PublicKeySignature-GenerateKeys.vi"/>
					<Item Name="FTW-Crypto-PublicKeySignature-Sign.vi" Type="VI" URL="../src/windows/security/FTW-Crypto-PublicKeySignature-Sign.vi"/>
					<Item Name="FTW-Crypto-PublicKeySignature-Verify.vi" Type="VI" URL="../src/windows/security/FTW-Crypto-PublicKeySignature-Verify.vi"/>
					<Item Name="FTW-Crypto-String-Sign.vi" Type="VI" URL="../src/windows/security/FTW-Crypto-String-Sign.vi"/>
					<Item Name="FTW-Crypto-String-Verify.vi" Type="VI" URL="../src/windows/security/FTW-Crypto-String-Verify.vi"/>
				</Item>
				<Item Name="sql" Type="Folder">
					<Item Name="FTW-dotNET-SQL-CloseConnection.vi" Type="VI" URL="../src/windows/sql/FTW-dotNET-SQL-CloseConnection.vi"/>
					<Item Name="FTW-dotNET-SQL-ConnectionEventsCallback.vi" Type="VI" URL="../src/windows/sql/FTW-dotNET-SQL-ConnectionEventsCallback.vi"/>
					<Item Name="FTW-dotNET-SQL-ExecuteScript.vi" Type="VI" URL="../src/windows/sql/FTW-dotNET-SQL-ExecuteScript.vi"/>
					<Item Name="FTW-dotNET-SQL-OpenConnection.vi" Type="VI" URL="../src/windows/sql/FTW-dotNET-SQL-OpenConnection.vi"/>
					<Item Name="FTW-dotNET-SQL-OpenConnectionWithEvents.vi" Type="VI" URL="../src/windows/sql/FTW-dotNET-SQL-OpenConnectionWithEvents.vi"/>
				</Item>
				<Item Name="string" Type="Folder">
					<Item Name="FTW-STR-UTF8.vi" Type="VI" URL="../src/windows/string/FTW-STR-UTF8.vi"/>
					<Item Name="FTW-STR-UTF16.vi" Type="VI" URL="../src/windows/string/FTW-STR-UTF16.vi"/>
				</Item>
				<Item Name="transfer" Type="Folder">
					<Item Name="FTW-TransferClient-Callback-ProgressDownload.vi" Type="VI" URL="../src/windows/transfer/FTW-TransferClient-Callback-ProgressDownload.vi"/>
					<Item Name="FTW-TransferClient-Callback-ProgressUpload.vi" Type="VI" URL="../src/windows/transfer/FTW-TransferClient-Callback-ProgressUpload.vi"/>
					<Item Name="FTW-TransferClient-Callback-StatusDownload.vi" Type="VI" URL="../src/windows/transfer/FTW-TransferClient-Callback-StatusDownload.vi"/>
					<Item Name="FTW-TransferClient-Callback-StatusUpload.vi" Type="VI" URL="../src/windows/transfer/FTW-TransferClient-Callback-StatusUpload.vi"/>
					<Item Name="FTW-TransferClient-Cancel.vi" Type="VI" URL="../src/windows/transfer/FTW-TransferClient-Cancel.vi"/>
					<Item Name="FTW-TransferClient-Construct.vi" Type="VI" URL="../src/windows/transfer/FTW-TransferClient-Construct.vi"/>
					<Item Name="FTW-TransferClient-Destroy.vi" Type="VI" URL="../src/windows/transfer/FTW-TransferClient-Destroy.vi"/>
					<Item Name="FTW-TransferClient-dotNET-CreateURI.vi" Type="VI" URL="../src/windows/transfer/FTW-TransferClient-dotNET-CreateURI.vi"/>
					<Item Name="FTW-TransferClient-Download.vi" Type="VI" URL="../src/windows/transfer/FTW-TransferClient-Download.vi"/>
					<Item Name="FTW-TransferClient-DownloadBegin.vi" Type="VI" URL="../src/windows/transfer/FTW-TransferClient-DownloadBegin.vi"/>
					<Item Name="FTW-TransferClient-InitializeEvents.vi" Type="VI" URL="../src/windows/transfer/FTW-TransferClient-InitializeEvents.vi"/>
					<Item Name="FTW-TransferClient-TransferProgress.ctl" Type="VI" URL="../src/windows/transfer/FTW-TransferClient-TransferProgress.ctl"/>
					<Item Name="FTW-TransferClient-TransferStatus.ctl" Type="VI" URL="../src/windows/transfer/FTW-TransferClient-TransferStatus.ctl"/>
					<Item Name="FTW-TransferClient-Upload.vi" Type="VI" URL="../src/windows/transfer/FTW-TransferClient-Upload.vi"/>
					<Item Name="FTW-TransferClient-UploadBegin.vi" Type="VI" URL="../src/windows/transfer/FTW-TransferClient-UploadBegin.vi"/>
				</Item>
				<Item Name="xml" Type="Folder">
					<Item Name="FTW-XML-Construct.vi" Type="VI" URL="../src/windows/xml/FTW-XML-Construct.vi"/>
					<Item Name="FTW-XML-Destroy.vi" Type="VI" URL="../src/windows/xml/FTW-XML-Destroy.vi"/>
					<Item Name="FTW-XML-Element-Add.vi" Type="VI" URL="../src/windows/xml/FTW-XML-Element-Add.vi"/>
					<Item Name="FTW-XML-Element-Append.vi" Type="VI" URL="../src/windows/xml/FTW-XML-Element-Append.vi"/>
					<Item Name="FTW-XML-Element-GetFirstChild.vi" Type="VI" URL="../src/windows/xml/FTW-XML-Element-GetFirstChild.vi"/>
					<Item Name="FTW-XML-Element-GetNextSibling.vi" Type="VI" URL="../src/windows/xml/FTW-XML-Element-GetNextSibling.vi"/>
					<Item Name="FTW-XML-Element-GetValue.vi" Type="VI" URL="../src/windows/xml/FTW-XML-Element-GetValue.vi"/>
					<Item Name="FTW-XML-Query-Elements.vi" Type="VI" URL="../src/windows/xml/FTW-XML-Query-Elements.vi"/>
					<Item Name="FTW-XML-Query-ElementValue.vi" Type="VI" URL="../src/windows/xml/FTW-XML-Query-ElementValue.vi"/>
					<Item Name="FTW-XML-Query-ElementXML.vi" Type="VI" URL="../src/windows/xml/FTW-XML-Query-ElementXML.vi"/>
					<Item Name="FTW-XML-Query-FirstElement.vi" Type="VI" URL="../src/windows/xml/FTW-XML-Query-FirstElement.vi"/>
					<Item Name="FTW-XML-Query-UpdateFirstElementXML.vi" Type="VI" URL="../src/windows/xml/FTW-XML-Query-UpdateFirstElementXML.vi"/>
					<Item Name="FTW-XML-ValidateTagName.vi" Type="VI" URL="../src/windows/xml/FTW-XML-ValidateTagName.vi"/>
				</Item>
			</Item>
		</Item>
		<Item Name="templates" Type="Folder">
			<Item Name="FTW-ActorTemplate.vi" Type="VI" URL="../templates/FTW-ActorTemplate.vi"/>
		</Item>
		<Item Name="tests" Type="Folder">
			<Item Name="core" Type="Folder" URL="../tests/core">
				<Property Name="NI.DISK" Type="Bool">true</Property>
			</Item>
			<Item Name="FTW-TestBootstrapper.lvclass" Type="LVClass" URL="../tests/bootstrapper/FTW-TestBootstrapper.lvclass"/>
		</Item>
		<Item Name="FTW-Test.json" Type="Document" URL="../tests/FTW-Test.json"/>
		<Item Name="FTW-Test.vi" Type="VI" URL="../tests/FTW-Test.vi"/>
		<Item Name="Dependencies" Type="Dependencies">
			<Item Name="vi.lib" Type="Folder">
				<Item Name="System Exec.vi" Type="VI" URL="/&lt;vilib&gt;/Platform/system.llb/System Exec.vi"/>
			</Item>
			<Item Name="DOMUserDefRef.dll" Type="Document" URL="DOMUserDefRef.dll">
				<Property Name="NI.PreserveRelativePath" Type="Bool">true</Property>
			</Item>
			<Item Name="FTW-JSON-Core-GetFlattenedValue.vi" Type="VI" URL="../codegen/xnode/json/fetch/FTW-JSON-Core-GetFlattenedValue.vi"/>
			<Item Name="mscorlib" Type="VI" URL="mscorlib">
				<Property Name="NI.PreserveRelativePath" Type="Bool">true</Property>
			</Item>
			<Item Name="System" Type="VI" URL="System">
				<Property Name="NI.PreserveRelativePath" Type="Bool">true</Property>
			</Item>
			<Item Name="System.Core" Type="Document" URL="System.Core">
				<Property Name="NI.PreserveRelativePath" Type="Bool">true</Property>
			</Item>
			<Item Name="System.Data" Type="Document" URL="System.Data">
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
