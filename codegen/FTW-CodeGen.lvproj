<?xml version='1.0' encoding='UTF-8'?>
<Project Type="Project" LVVersion="15008000">
	<Property Name="NI.LV.All.SourceOnly" Type="Bool">true</Property>
	<Item Name="My Computer" Type="My Computer">
		<Property Name="NI.SortType" Type="Int">1</Property>
		<Property Name="server.app.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="server.control.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="server.tcp.enabled" Type="Bool">false</Property>
		<Property Name="server.tcp.port" Type="Int">0</Property>
		<Property Name="server.tcp.serviceName" Type="Str">My Computer/VI Server</Property>
		<Property Name="server.tcp.serviceName.default" Type="Str">My Computer/VI Server</Property>
		<Property Name="server.vi.callsEnabled" Type="Bool">true</Property>
		<Property Name="server.vi.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="specify.custom.address" Type="Bool">false</Property>
		<Item Name="framework" Type="Folder">
			<Item Name="FTW-CodeGen-ChooseImplementation.vi" Type="VI" URL="../framework/FTW-CodeGen-ChooseImplementation.vi"/>
			<Item Name="FTW-CodeGen-FindGObject.vi" Type="VI" URL="../framework/FTW-CodeGen-FindGObject.vi"/>
			<Item Name="FTW-CodeGen-FindGObjects.vi" Type="VI" URL="../framework/FTW-CodeGen-FindGObjects.vi"/>
			<Item Name="FTW-CodeGen-FindTerm-Adaptive.vi" Type="VI" URL="../framework/FTW-CodeGen-FindTerm-Adaptive.vi"/>
			<Item Name="FTW-CodeGen-FindTerm-Ref.vi" Type="VI" URL="../framework/FTW-CodeGen-FindTerm-Ref.vi"/>
			<Item Name="FTW-CodeGen-FindTerm-Variant.vi" Type="VI" URL="../framework/FTW-CodeGen-FindTerm-Variant.vi"/>
			<Item Name="FTW-CodeGen-FindTerm.vi" Type="VI" URL="../framework/FTW-CodeGen-FindTerm.vi"/>
			<Item Name="FTW-CodeGen-GetErrors.vi" Type="VI" URL="../framework/FTW-CodeGen-GetErrors.vi"/>
			<Item Name="FTW-CodeGen-GetTerminals.vi" Type="VI" URL="../framework/FTW-CodeGen-GetTerminals.vi"/>
			<Item Name="FTW-CodeGen-InitializeCache.vi" Type="VI" URL="../framework/FTW-CodeGen-InitializeCache.vi"/>
			<Item Name="FTW-CodeGen-RelinkTerminals.vi" Type="VI" URL="../framework/FTW-CodeGen-RelinkTerminals.vi"/>
			<Item Name="FTW-CodeGen-SetConstantValue.vi" Type="VI" URL="../framework/FTW-CodeGen-SetConstantValue.vi"/>
			<Item Name="FTW-CodeGen-TerminalTypeAdaption.vi" Type="VI" URL="../framework/FTW-CodeGen-TerminalTypeAdaption.vi"/>
			<Item Name="FTW-CodeGen-TraverseGObjects.vi" Type="VI" URL="../framework/FTW-CodeGen-TraverseGObjects.vi"/>
			<Item Name="FTW-CodeGen-UpdateCodegenCache.vi" Type="VI" URL="../framework/FTW-CodeGen-UpdateCodegenCache.vi"/>
			<Item Name="FTW-CodeGen-XNodeAdaptiveTerminal-Controller.ctl" Type="VI" URL="../framework/FTW-CodeGen-XNodeAdaptiveTerminal-Controller.ctl"/>
			<Item Name="FTW-CodeGen-XNodeAdaptiveTerminal-ControllerBehavior.ctl" Type="VI" URL="../framework/FTW-CodeGen-XNodeAdaptiveTerminal-ControllerBehavior.ctl"/>
			<Item Name="FTW-CodeGen-XNodeAdaptiveTerminal-Dependent.ctl" Type="VI" URL="../framework/FTW-CodeGen-XNodeAdaptiveTerminal-Dependent.ctl"/>
			<Item Name="FTW-CodeGen-XNodeAdaptiveTerminal.ctl" Type="VI" URL="../framework/FTW-CodeGen-XNodeAdaptiveTerminal.ctl"/>
			<Item Name="FTW-CodeGen-XNodeCommonState.ctl" Type="VI" URL="../framework/FTW-CodeGen-XNodeCommonState.ctl"/>
			<Item Name="FTW-CodeGen-XNodeReply.vi" Type="VI" URL="../framework/FTW-CodeGen-XNodeReply.vi"/>
			<Item Name="FTW-CodeGen-XNodeReplyType.ctl" Type="VI" URL="../framework/FTW-CodeGen-XNodeReplyType.ctl"/>
			<Item Name="FTW-CodeGen-XNodeUpdateState.vi" Type="VI" URL="../framework/FTW-CodeGen-XNodeUpdateState.vi"/>
		</Item>
		<Item Name="support" Type="Folder">
			<Item Name="FTW-CodeGen-Callback-FindGObject.vi" Type="VI" URL="../support/FTW-CodeGen-Callback-FindGObject.vi"/>
			<Item Name="FTW-CodeGen-Callback-FindGObjects.vi" Type="VI" URL="../support/FTW-CodeGen-Callback-FindGObjects.vi"/>
			<Item Name="FTW-CodeGen-EnumerateVIServerClassHierarchy.vi" Type="VI" URL="../support/FTW-CodeGen-EnumerateVIServerClassHierarchy.vi"/>
			<Item Name="FTW-CodeGen-GetTypeInfo.vi" Type="VI" URL="../support/FTW-CodeGen-GetTypeInfo.vi"/>
			<Item Name="FTW-CodeGen-GetTypeInfoRemote.vi" Type="VI" URL="../support/FTW-CodeGen-GetTypeInfoRemote.vi"/>
			<Item Name="FTW-CodeGen-Image-AppendToPicture.vi" Type="VI" URL="../support/FTW-CodeGen-Image-AppendToPicture.vi"/>
			<Item Name="FTW-CodeGen-Image-Rectangle.vi" Type="VI" URL="../support/FTW-CodeGen-Image-Rectangle.vi"/>
			<Item Name="FTW-CodeGen-Image-Subset.vi" Type="VI" URL="../support/FTW-CodeGen-Image-Subset.vi"/>
			<Item Name="FTW-CodeGen-Image-ToPicture.vi" Type="VI" URL="../support/FTW-CodeGen-Image-ToPicture.vi"/>
		</Item>
		<Item Name="xnodes" Type="Folder">
			<Item Name="FTW-Actor-Ask.xnode" Type="XNode" URL="../xnode/FTW-Actor-Ask.xnode"/>
			<Item Name="FTW-Actor-Spawn.xnode" Type="XNode" URL="../xnode/FTW-Actor-Spawn.xnode"/>
			<Item Name="FTW-Array-Shuffle.xnode" Type="XNode" URL="../xnode/FTW-Array-Shuffle.xnode"/>
			<Item Name="FTW-Dataflow-Synchronizer.xnode" Type="XNode" URL="../xnode/FTW-Dataflow-Synchronizer.xnode"/>
			<Item Name="FTW-dotNet-SQL-Fetch.xnode" Type="XNode" URL="../xnode/FTW-dotNet-SQL-Fetch.xnode"/>
			<Item Name="FTW-dotNet-SQL-Insert.xnode" Type="XNode" URL="../xnode/FTW-dotNet-SQL-Insert.xnode"/>
			<Item Name="FTW-JSON-Fetch.xnode" Type="XNode" URL="../xnode/FTW-JSON-Fetch.xnode"/>
			<Item Name="FTW-SQLite-Fetch.xnode" Type="XNode" URL="../xnode/FTW-SQLite-Fetch.xnode"/>
			<Item Name="FTW-SQLite-Insert.xnode" Type="XNode" URL="../xnode/FTW-SQLite-Insert.xnode"/>
		</Item>
		<Item Name="FTW-CodeGen-StaticLinks.lvclass" Type="LVClass" URL="../static/FTW-CodeGen-StaticLinks.lvclass"/>
		<Item Name="FTW-DevUtil-VIDetails.vi" Type="VI" URL="../../utils/FTW-DevUtil-VIDetails.vi"/>
		<Item Name="Dependencies" Type="Dependencies">
			<Item Name="FTW-Actor-Core-SpawnHandshake.vi" Type="VI" URL="../../src/actor/core/FTW-Actor-Core-SpawnHandshake.vi"/>
			<Item Name="FTW-Actor-Core-SpawnOptions.ctl" Type="VI" URL="../../src/actor/core/FTW-Actor-Core-SpawnOptions.ctl"/>
			<Item Name="FTW-Actor-Core-SpawnPrelude.vi" Type="VI" URL="../../src/actor/core/FTW-Actor-Core-SpawnPrelude.vi"/>
			<Item Name="FTW-Actor-DynamicLaunchOptions.vi" Type="VI" URL="../../src/actor/support/FTW-Actor-DynamicLaunchOptions.vi"/>
			<Item Name="FTW-Connector-Construct.vi" Type="VI" URL="../../src/socket/connector/FTW-Connector-Construct.vi"/>
			<Item Name="FTW-Connector-Core-Ask-Unvalidated.vi" Type="VI" URL="../../src/socket/connector/core/FTW-Connector-Core-Ask-Unvalidated.vi"/>
			<Item Name="FTW-DevUtil-CLFNPrototype.ctl" Type="VI" URL="../../utils/metrics/FTW-DevUtil-CLFNPrototype.ctl"/>
			<Item Name="FTW-DevUtil-CLFNPrototypes.vi" Type="VI" URL="../../utils/metrics/FTW-DevUtil-CLFNPrototypes.vi"/>
			<Item Name="FTW-DevUtil-StaticLinks.vi" Type="VI" URL="../../utils/metrics/FTW-DevUtil-StaticLinks.vi"/>
			<Item Name="FTW-DevUtil-VIMetrics.ctl" Type="VI" URL="../../utils/metrics/FTW-DevUtil-VIMetrics.ctl"/>
			<Item Name="FTW-DevUtil-VIMetrics.vi" Type="VI" URL="../../utils/metrics/FTW-DevUtil-VIMetrics.vi"/>
			<Item Name="FTW-ERR-Assert-ConditionalDisable.vi" Type="VI" URL="../../src/error/FTW-ERR-Assert-ConditionalDisable.vi"/>
			<Item Name="FTW-ERR-Assert-DeveloperError.vi" Type="VI" URL="../../src/error/FTW-ERR-Assert-DeveloperError.vi"/>
			<Item Name="FTW-ERR-Assert-Truthy.vi" Type="VI" URL="../../src/error/FTW-ERR-Assert-Truthy.vi"/>
			<Item Name="FTW-ERR-CallChain.vi" Type="VI" URL="../../src/error/FTW-ERR-CallChain.vi"/>
			<Item Name="FTW-ERR-Clear.vi" Type="VI" URL="../../src/error/FTW-ERR-Clear.vi"/>
			<Item Name="FTW-ERR-ExceptionType.ctl" Type="VI" URL="../../src/error/FTW-ERR-ExceptionType.ctl"/>
			<Item Name="FTW-ERR-Explanation.vi" Type="VI" URL="../../src/error/FTW-ERR-Explanation.vi"/>
			<Item Name="FTW-ERR-Ignore.vi" Type="VI" URL="../../src/error/FTW-ERR-Ignore.vi"/>
			<Item Name="FTW-ERR-NoErrorConstant.vi" Type="VI" URL="../../src/error/FTW-ERR-NoErrorConstant.vi"/>
			<Item Name="FTW-ERR-PrependExplanation.vi" Type="VI" URL="../../src/error/FTW-ERR-PrependExplanation.vi"/>
			<Item Name="FTW-ERR-SerializeForLog.vi" Type="VI" URL="../../src/error/FTW-ERR-SerializeForLog.vi"/>
			<Item Name="FTW-ERR-StatusError.vi" Type="VI" URL="../../src/error/FTW-ERR-StatusError.vi"/>
			<Item Name="FTW-ERR-StatusException.vi" Type="VI" URL="../../src/error/FTW-ERR-StatusException.vi"/>
			<Item Name="FTW-ERR-StatusOK.vi" Type="VI" URL="../../src/error/FTW-ERR-StatusOK.vi"/>
			<Item Name="FTW-ERR-ThrowError.vi" Type="VI" URL="../../src/error/FTW-ERR-ThrowError.vi"/>
			<Item Name="FTW-ERR-ThrowGenericError.vi" Type="VI" URL="../../src/error/FTW-ERR-ThrowGenericError.vi"/>
			<Item Name="FTW-ERR-ThrowInfo.vi" Type="VI" URL="../../src/error/FTW-ERR-ThrowInfo.vi"/>
			<Item Name="FTW-ERR-ThrowInvalidReferenceError.vi" Type="VI" URL="../../src/error/FTW-ERR-ThrowInvalidReferenceError.vi"/>
			<Item Name="FTW-ERR-ThrowWarning.vi" Type="VI" URL="../../src/error/FTW-ERR-ThrowWarning.vi"/>
			<Item Name="FTW-Inbox-Core-ConstructMessagePipe.vi" Type="VI" URL="../../src/socket/inbox/core/FTW-Inbox-Core-ConstructMessagePipe.vi"/>
			<Item Name="FTW-JSON-Construct-FromBuffer.vi" Type="VI" URL="../../src/json/FTW-JSON-Construct-FromBuffer.vi"/>
			<Item Name="FTW-JSON-Core-ElementType.vi" Type="VI" URL="../../src/json/core/FTW-JSON-Core-ElementType.vi"/>
			<Item Name="FTW-JSON-Core-EncodingFlags.vi" Type="VI" URL="../../src/json/core/FTW-JSON-Core-EncodingFlags.vi"/>
			<Item Name="FTW-JSON-Core-GetFlattenedValue.vi" Type="VI" URL="../xnode/json/fetch/FTW-JSON-Core-GetFlattenedValue.vi"/>
			<Item Name="FTW-JSON-Core-LibraryReturnValue.vi" Type="VI" URL="../../src/json/core/FTW-JSON-Core-LibraryReturnValue.vi"/>
			<Item Name="FTW-JSON-Core-NumericType.vi" Type="VI" URL="../../src/json/core/FTW-JSON-Core-NumericType.vi"/>
			<Item Name="FTW-JSON-Core-Type.ctl" Type="VI" URL="../../src/json/core/FTW-JSON-Core-Type.ctl"/>
			<Item Name="FTW-JSON-Destroy.vi" Type="VI" URL="../../src/json/FTW-JSON-Destroy.vi"/>
			<Item Name="FTW-JSON-Object-SetElement-String.vi" Type="VI" URL="../../src/json/FTW-JSON-Object-SetElement-String.vi"/>
			<Item Name="FTW-JSON-ObjectManip-AddPair.vi" Type="VI" URL="../../src/json/FTW-JSON-ObjectManip-AddPair.vi"/>
			<Item Name="FTW-JSON-SerializeAndDestroy.vi" Type="VI" URL="../../src/json/FTW-JSON-SerializeAndDestroy.vi"/>
			<Item Name="FTW-JSON-Type.ctl" Type="VI" URL="../../src/json/FTW-JSON-Type.ctl"/>
			<Item Name="FTW-KernelFilepath.vi" Type="VI" URL="../../lib/FTW-KernelFilepath.vi"/>
			<Item Name="FTW-Linker-DecodeBitmap.vi" Type="VI" URL="../../utils/linker/FTW-Linker-DecodeBitmap.vi"/>
			<Item Name="FTW-Linker-Flags-buttons.ctl" Type="VI" URL="../../utils/linker/FTW-Linker-Flags-buttons.ctl"/>
			<Item Name="FTW-Linker-Flags-iState.ctl" Type="VI" URL="../../utils/linker/FTW-Linker-Flags-iState.ctl"/>
			<Item Name="FTW-Linker-Flags-iStyle.ctl" Type="VI" URL="../../utils/linker/FTW-Linker-Flags-iStyle.ctl"/>
			<Item Name="FTW-Linker-Flags-viflags.ctl" Type="VI" URL="../../utils/linker/FTW-Linker-Flags-viflags.ctl"/>
			<Item Name="FTW-Linker-Flags-viflags2.ctl" Type="VI" URL="../../utils/linker/FTW-Linker-Flags-viflags2.ctl"/>
			<Item Name="FTW-Linker-Flags-wStyle.ctl" Type="VI" URL="../../utils/linker/FTW-Linker-Flags-wStyle.ctl"/>
			<Item Name="FTW-Linker-LabVIEWFiletype.ctl" Type="VI" URL="../../utils/linker/FTW-Linker-LabVIEWFiletype.ctl"/>
			<Item Name="FTW-Linker-LinkerInfoStructure.ctl" Type="VI" URL="../../utils/linker/FTW-Linker-LinkerInfoStructure.ctl"/>
			<Item Name="FTW-Linker-LVFileStaticLinks.vi" Type="VI" URL="../../utils/linker/FTW-Linker-LVFileStaticLinks.vi"/>
			<Item Name="FTW-Reflection-Array.vi" Type="VI" URL="../../src/reflection/FTW-Reflection-Array.vi"/>
			<Item Name="FTW-Reflection-Cluster.vi" Type="VI" URL="../../src/reflection/FTW-Reflection-Cluster.vi"/>
			<Item Name="FTW-Reflection-ConPaneInterface-Function.ctl" Type="VI" URL="../../src/reflection/core/FTW-Reflection-ConPaneInterface-Function.ctl"/>
			<Item Name="FTW-Reflection-ConPaneInterface-Terminal.ctl" Type="VI" URL="../../src/reflection/core/FTW-Reflection-ConPaneInterface-Terminal.ctl"/>
			<Item Name="FTW-Reflection-ConPaneInterface.vi" Type="VI" URL="../../src/reflection/FTW-Reflection-ConPaneInterface.vi"/>
			<Item Name="FTW-Reflection-Core-FlatEnum.vi" Type="VI" URL="../../src/reflection/core/FTW-Reflection-Core-FlatEnum.vi"/>
			<Item Name="FTW-Reflection-FTWObject.vi" Type="VI" URL="../../src/reflection/FTW-Reflection-FTWObject.vi"/>
			<Item Name="FTW-Reflection-Type.vi" Type="VI" URL="../../src/reflection/FTW-Reflection-Type.vi"/>
			<Item Name="FTW-Reflection-TypeDescriptorToDefaultData.vi" Type="VI" URL="../../src/reflection/FTW-Reflection-TypeDescriptorToDefaultData.vi"/>
			<Item Name="FTW-Reflection-Types.ctl" Type="VI" URL="../../src/reflection/FTW-Reflection-Types.ctl"/>
			<Item Name="FTW-Reflection-VIServer.vi" Type="VI" URL="../../src/reflection/FTW-Reflection-VIServer.vi"/>
			<Item Name="FTW-Regex-Construct.vi" Type="VI" URL="../../src/regex/FTW-Regex-Construct.vi"/>
			<Item Name="FTW-Regex-Destroy.vi" Type="VI" URL="../../src/regex/FTW-Regex-Destroy.vi"/>
			<Item Name="FTW-Regex-Execute.vi" Type="VI" URL="../../src/regex/FTW-Regex-Execute.vi"/>
			<Item Name="FTW-Regex.vi" Type="VI" URL="../../src/regex/FTW-Regex.vi"/>
			<Item Name="FTW-Request-Core-InterpretResponse.vi" Type="VI" URL="../../src/actor/request/core/FTW-Request-Core-InterpretResponse.vi"/>
			<Item Name="FTW-Request-InterpretResponse.vi" Type="VI" URL="../../src/actor/request/FTW-Request-InterpretResponse.vi"/>
			<Item Name="FTW-Socket-Core-ReturnCode.vi" Type="VI" URL="../../src/socket/support/FTW-Socket-Core-ReturnCode.vi"/>
			<Item Name="FTW-Socket-Core-TransportScheme.ctl" Type="VI" URL="../../src/socket/support/FTW-Socket-Core-TransportScheme.ctl"/>
			<Item Name="FTW-Socket-Core-ValidateAddress.vi" Type="VI" URL="../../src/socket/support/FTW-Socket-Core-ValidateAddress.vi"/>
			<Item Name="FTW-SQLite-Core-LibraryReturnValue.vi" Type="VI" URL="../../src/database/core/FTW-SQLite-Core-LibraryReturnValue.vi"/>
			<Item Name="FTW-SQLite-Core-PrepareStatement.vi" Type="VI" URL="../../src/database/core/FTW-SQLite-Core-PrepareStatement.vi"/>
			<Item Name="FTW-SQLite-Core-QueryDebug.vi" Type="VI" URL="../../src/database/core/FTW-SQLite-Core-QueryDebug.vi"/>
			<Item Name="FTW-STR-Array-Delimit.vi" Type="VI" URL="../../src/string/FTW-STR-Array-Delimit.vi"/>
			<Item Name="FTW-STR-Random-Hex.vi" Type="VI" URL="../../src/string/FTW-STR-Random-Hex.vi"/>
			<Item Name="FTW-STR-ReplaceWhitespace.vi" Type="VI" URL="../../src/string/FTW-STR-ReplaceWhitespace.vi"/>
			<Item Name="FTW-Time-RelativeTimer.vi" Type="VI" URL="../../src/time/FTW-Time-RelativeTimer.vi"/>
			<Item Name="FTW-Type-Actor-Connector.ctl" Type="VI" URL="../../src/core/type/FTW-Type-Actor-Connector.ctl"/>
			<Item Name="FTW-Type-JSON.ctl" Type="VI" URL="../../src/core/type/FTW-Type-JSON.ctl"/>
			<Item Name="FTW-Type-Regex.ctl" Type="VI" URL="../../src/core/type/FTW-Type-Regex.ctl"/>
			<Item Name="FTW-Type-SQLite.ctl" Type="VI" URL="../../src/core/type/FTW-Type-SQLite.ctl"/>
			<Item Name="ftw32.dll" Type="Document" URL="../../lib/ftw32.dll"/>
			<Item Name="mscorlib" Type="VI" URL="mscorlib">
				<Property Name="NI.PreserveRelativePath" Type="Bool">true</Property>
			</Item>
			<Item Name="System.Data" Type="Document" URL="System.Data">
				<Property Name="NI.PreserveRelativePath" Type="Bool">true</Property>
			</Item>
		</Item>
		<Item Name="Build Specifications" Type="Build"/>
	</Item>
</Project>
