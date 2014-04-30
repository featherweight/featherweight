<?xml version='1.0' encoding='UTF-8'?>
<Project Type="Project" LVVersion="12008004">
	<Property Name="NI.LV.All.SourceOnly" Type="Bool">true</Property>
	<Item Name="My Computer" Type="My Computer">
		<Property Name="CCSymbols" Type="Str">DISABLE_ZMQ,FALSE;</Property>
		<Property Name="NI.SortType" Type="Int">1</Property>
		<Property Name="server.app.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="server.control.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="server.tcp.acl" Type="Str">0800000008000000</Property>
		<Property Name="server.tcp.enabled" Type="Bool">false</Property>
		<Property Name="server.tcp.port" Type="Int">0</Property>
		<Property Name="server.tcp.serviceName" Type="Str"></Property>
		<Property Name="server.tcp.serviceName.default" Type="Str">My Computer/VI Server</Property>
		<Property Name="server.vi.access" Type="Str"></Property>
		<Property Name="server.vi.callsEnabled" Type="Bool">true</Property>
		<Property Name="server.vi.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="server.viscripting.showScriptingOperationsInContextHelp" Type="Bool">false</Property>
		<Property Name="server.viscripting.showScriptingOperationsInEditor" Type="Bool">false</Property>
		<Property Name="specify.custom.address" Type="Bool">false</Property>
		<Item Name="Source" Type="Folder">
			<Item Name="ZMQ" Type="Folder">
				<Item Name="FTW-ZMQ-Win32.dll" Type="Document" URL="../src/ZMQ/FTW-ZMQ-Win32.dll"/>
				<Item Name="libzmq32.dll" Type="Document" URL="../src/ZMQ/libzmq32.dll"/>
			</Item>
			<Item Name="FTW-Actor.lvlib" Type="Library" URL="../src/FTW-Actor.lvlib"/>
		</Item>
		<Item Name="Dependencies" Type="Dependencies">
			<Item Name="FTW-ERR-Clear.vi" Type="VI" URL="../../Core/src/Error/FTW-ERR-Clear.vi"/>
			<Item Name="FTW-ERR-NoErrorConstant.vi" Type="VI" URL="../../Core/src/Error/FTW-ERR-NoErrorConstant.vi"/>
			<Item Name="FTW-ERR-ThrowGenericError.vi" Type="VI" URL="../../Core/src/Error/FTW-ERR-ThrowGenericError.vi"/>
			<Item Name="FTW-ERR-ThrowImpossibleError.vi" Type="VI" URL="../../Core/src/Error/FTW-ERR-ThrowImpossibleError.vi"/>
			<Item Name="FTW-JSON-ToLabVIEW.vi" Type="VI" URL="../../Core/src/JSON/FTW-JSON-ToLabVIEW.vi"/>
			<Item Name="FTW-JSON-ToLabVIEW_0E3E72F634BF4A9AB33E22111E055A26_001.vi" Type="VI" URL="/&lt;instcachedir&gt;/0/FTW-JSON-ToLabVIEW_0E3E72F634BF4A9AB33E22111E055A26.lvgen/FTW-JSON-ToLabVIEW_0E3E72F634BF4A9AB33E22111E055A26_001.vi"/>
		</Item>
		<Item Name="Build Specifications" Type="Build">
			<Item Name="Featherweight Actor Packed Library" Type="Packed Library">
				<Property Name="Bld_buildCacheID" Type="Str">{3825E264-9FDD-423E-99F3-413EAB4A0330}</Property>
				<Property Name="Bld_buildSpecName" Type="Str">Featherweight Actor Packed Library</Property>
				<Property Name="Bld_excludeInlineSubVIs" Type="Bool">true</Property>
				<Property Name="Bld_localDestDir" Type="Path">../Builds</Property>
				<Property Name="Bld_localDestDirType" Type="Str">relativeToProject</Property>
				<Property Name="Bld_previewCacheID" Type="Str">{6ED864F0-AA54-4248-B424-EB84D922BF16}</Property>
				<Property Name="Destination[0].destName" Type="Str">FTW-Actor.lvlibp</Property>
				<Property Name="Destination[0].path" Type="Path">../Builds/FTW-Actor.lvlibp</Property>
				<Property Name="Destination[0].path.type" Type="Str">relativeToProject</Property>
				<Property Name="Destination[0].preserveHierarchy" Type="Bool">true</Property>
				<Property Name="Destination[0].type" Type="Str">App</Property>
				<Property Name="Destination[1].destName" Type="Str">Support Directory</Property>
				<Property Name="Destination[1].path" Type="Path">../Builds</Property>
				<Property Name="Destination[1].path.type" Type="Str">relativeToProject</Property>
				<Property Name="DestinationCount" Type="Int">2</Property>
				<Property Name="Source[0].itemID" Type="Str">{33D76BC3-4704-4371-91AD-B82BC51D8519}</Property>
				<Property Name="Source[0].type" Type="Str">Container</Property>
				<Property Name="Source[1].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[1].itemID" Type="Ref">/My Computer/Source/FTW-Actor.lvlib</Property>
				<Property Name="Source[1].Library.allowMissingMembers" Type="Bool">true</Property>
				<Property Name="Source[1].Library.atomicCopy" Type="Bool">true</Property>
				<Property Name="Source[1].Library.LVLIBPtopLevel" Type="Bool">true</Property>
				<Property Name="Source[1].preventRename" Type="Bool">true</Property>
				<Property Name="Source[1].sourceInclusion" Type="Str">TopLevel</Property>
				<Property Name="Source[1].type" Type="Str">Library</Property>
				<Property Name="Source[2].Container.applySaveSettings" Type="Bool">true</Property>
				<Property Name="Source[2].itemID" Type="Ref">/My Computer/Source</Property>
				<Property Name="Source[2].properties[0].type" Type="Str">Remove front panel</Property>
				<Property Name="Source[2].properties[0].value" Type="Bool">false</Property>
				<Property Name="Source[2].properties[1].type" Type="Str">Remove block diagram</Property>
				<Property Name="Source[2].properties[1].value" Type="Bool">false</Property>
				<Property Name="Source[2].propertiesCount" Type="Int">2</Property>
				<Property Name="Source[2].type" Type="Str">Container</Property>
				<Property Name="SourceCount" Type="Int">3</Property>
				<Property Name="TgtF_autoIncrement" Type="Bool">true</Property>
				<Property Name="TgtF_companyName" Type="Str">Featherweight</Property>
				<Property Name="TgtF_fileDescription" Type="Str">Featherweight Actor Packed Library</Property>
				<Property Name="TgtF_fileVersion.build" Type="Int">346</Property>
				<Property Name="TgtF_fileVersion.minor" Type="Int">3</Property>
				<Property Name="TgtF_internalName" Type="Str">FTW-Actor</Property>
				<Property Name="TgtF_legalCopyright" Type="Str">featherweight.io</Property>
				<Property Name="TgtF_productName" Type="Str">Featherweight Actor Packed Library</Property>
				<Property Name="TgtF_targetfileGUID" Type="Str">{7E0E72D8-043C-40A6-86D2-860B81572F8B}</Property>
				<Property Name="TgtF_targetfileName" Type="Str">FTW-Actor.lvlibp</Property>
			</Item>
		</Item>
	</Item>
</Project>
