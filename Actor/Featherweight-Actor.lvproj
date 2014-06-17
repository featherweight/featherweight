<?xml version='1.0' encoding='UTF-8'?>
<Project Type="Project" LVVersion="12008004">
	<Property Name="NI.LV.All.SourceOnly" Type="Bool">true</Property>
	<Item Name="My Computer" Type="My Computer">
		<Property Name="CCSymbols" Type="Str">DISABLE_ZMQ,FALSE;</Property>
		<Property Name="specify.custom.address" Type="Bool">false</Property>
		<Item Name="Include" Type="Folder">
			<Item Name="FTW-JSON-Deserialize.xnode" Type="XNode" URL="../../Core/utils/CodeGen/JSON Deserialize/FTW-JSON-Deserialize.xnode"/>
		</Item>
		<Item Name="ZMQ" Type="Folder">
			<Item Name="FTW-ZMQ-Win32.dll" Type="Document" URL="../src/ZMQ/FTW-ZMQ-Win32.dll"/>
			<Item Name="libzmq32.dll" Type="Document" URL="../src/ZMQ/libzmq32.dll"/>
		</Item>
		<Item Name="FTW-Actor.lvlib" Type="Library" URL="../src/FTW-Actor.lvlib"/>
		<Item Name="Dependencies" Type="Dependencies">
			<Item Name="FTW-App-StringVersionToString.vi" Type="VI" URL="../../Core/src/Application/FTW-App-StringVersionToString.vi"/>
			<Item Name="FTW-App-VersionToString.vi" Type="VI" URL="../../Core/src/Application/FTW-App-VersionToString.vi"/>
			<Item Name="FTW-ERR-CallChain.vi" Type="VI" URL="../../Core/src/Error/FTW-ERR-CallChain.vi"/>
			<Item Name="FTW-ERR-Clear.vi" Type="VI" URL="../../Core/src/Error/FTW-ERR-Clear.vi"/>
			<Item Name="FTW-ERR-ExceptionType.ctl" Type="VI" URL="../../Core/src/Error/FTW-ERR-ExceptionType.ctl"/>
			<Item Name="FTW-ERR-NoErrorConstant.vi" Type="VI" URL="../../Core/src/Error/FTW-ERR-NoErrorConstant.vi"/>
			<Item Name="FTW-ERR-SerializeForLog.vi" Type="VI" URL="../../Core/src/Error/FTW-ERR-SerializeForLog.vi"/>
			<Item Name="FTW-ERR-StatusError.vi" Type="VI" URL="../../Core/src/Error/FTW-ERR-StatusError.vi"/>
			<Item Name="FTW-ERR-StatusException.vi" Type="VI" URL="../../Core/src/Error/FTW-ERR-StatusException.vi"/>
			<Item Name="FTW-ERR-StatusOK.vi" Type="VI" URL="../../Core/src/Error/FTW-ERR-StatusOK.vi"/>
			<Item Name="FTW-ERR-ThrowError.vi" Type="VI" URL="../../Core/src/Error/FTW-ERR-ThrowError.vi"/>
			<Item Name="FTW-ERR-ThrowGenericError.vi" Type="VI" URL="../../Core/src/Error/FTW-ERR-ThrowGenericError.vi"/>
			<Item Name="FTW-ERR-ThrowImpossibleError.vi" Type="VI" URL="../../Core/src/Error/FTW-ERR-ThrowImpossibleError.vi"/>
			<Item Name="FTW-File-CreateDirectory.vi" Type="VI" URL="../../Core/src/File/FTW-File-CreateDirectory.vi"/>
			<Item Name="FTW-File-Directory-Exists.vi" Type="VI" URL="../../Core/src/File/FTW-File-Directory-Exists.vi"/>
			<Item Name="FTW-File-FindLibrary.vi" Type="VI" URL="../../Core/src/File/FTW-File-FindLibrary.vi"/>
			<Item Name="FTW-File-GenerateLogFilename.vi" Type="VI" URL="../../Core/src/File/FTW-File-GenerateLogFilename.vi"/>
			<Item Name="FTW-File-IsRelative.vi" Type="VI" URL="../../Core/src/File/FTW-File-IsRelative.vi"/>
			<Item Name="FTW-File-ListDirectories.vi" Type="VI" URL="../../Core/src/File/FTW-File-ListDirectories.vi"/>
			<Item Name="FTW-File-ListDirectory-RegexFilter.vi" Type="VI" URL="../../Core/src/File/FTW-File-ListDirectory-RegexFilter.vi"/>
			<Item Name="FTW-File-ResolveSymbolicPaths.vi" Type="VI" URL="../../Core/src/File/FTW-File-ResolveSymbolicPaths.vi"/>
			<Item Name="FTW-File-SystemDirectories.vi" Type="VI" URL="../../Core/src/File/FTW-File-SystemDirectories.vi"/>
			<Item Name="FTW-File-TextWrite.vi" Type="VI" URL="../../Core/src/File/FTW-File-TextWrite.vi"/>
			<Item Name="FTW-File-ValidateFilepath.vi" Type="VI" URL="../../Core/src/File/FTW-File-ValidateFilepath.vi"/>
			<Item Name="FTW-JSON-Core-ElementType.vi" Type="VI" URL="../../Core/src/JSON/FTW-JSON-Core-ElementType.vi"/>
			<Item Name="FTW-JSON-Core-GetFlattenedValue.vi" Type="VI" URL="../../Core/src/JSON/FTW-JSON-Core-GetFlattenedValue.vi"/>
			<Item Name="FTW-JSON-Core-LibraryError.vi" Type="VI" URL="../../Core/src/JSON/FTW-JSON-Core-LibraryError.vi"/>
			<Item Name="FTW-JSON-Core-LibraryFilepath.vi" Type="VI" URL="../../Core/src/JSON/FTW-JSON-Core-LibraryFilepath.vi"/>
			<Item Name="FTW-JSON-Escape.vi" Type="VI" URL="../../Core/src/JSON/FTW-JSON-Escape.vi"/>
			<Item Name="FTW-JSON-Format-String.vi" Type="VI" URL="../../Core/src/JSON/FTW-JSON-Format-String.vi"/>
			<Item Name="FTW-JSON-ObjectManip-AddPair.vi" Type="VI" URL="../../Core/src/JSON/FTW-JSON-ObjectManip-AddPair.vi"/>
			<Item Name="FTW-JSON-Type.ctl" Type="VI" URL="../../Core/src/JSON/FTW-JSON-Type.ctl"/>
			<Item Name="FTW-NUM-Counter.vi" Type="VI" URL="../../Core/src/Numeric/FTW-NUM-Counter.vi"/>
			<Item Name="FTW-Reflection-Array.vi" Type="VI" URL="../../Core/src/Reflection/FTW-Reflection-Array.vi"/>
			<Item Name="FTW-Reflection-Cluster.vi" Type="VI" URL="../../Core/src/Reflection/FTW-Reflection-Cluster.vi"/>
			<Item Name="FTW-Reflection-Enum.vi" Type="VI" URL="../../Core/src/Reflection/FTW-Reflection-Enum.vi"/>
			<Item Name="FTW-Reflection-Type.vi" Type="VI" URL="../../Core/src/Reflection/FTW-Reflection-Type.vi"/>
			<Item Name="FTW-Reflection-Types.ctl" Type="VI" URL="../../Core/src/Reflection/FTW-Reflection-Types.ctl"/>
			<Item Name="FTW-Regex-FilterArray.vi" Type="VI" URL="../../Core/src/Regex/FTW-Regex-FilterArray.vi"/>
			<Item Name="FTW-Regex-ReplaceAll.vi" Type="VI" URL="../../Core/src/Regex/FTW-Regex-ReplaceAll.vi"/>
			<Item Name="FTW-Regex.vi" Type="VI" URL="../../Core/src/Regex/FTW-Regex.vi"/>
			<Item Name="FTW-STR-Array-Delimit.vi" Type="VI" URL="../../Core/src/String/FTW-STR-Array-Delimit.vi"/>
			<Item Name="FTW-STR-Encode-Base64.vi" Type="VI" URL="../../Core/src/String/FTW-STR-Encode-Base64.vi"/>
			<Item Name="FTW-STR-Random-Hex.vi" Type="VI" URL="../../Core/src/String/FTW-STR-Random-Hex.vi"/>
			<Item Name="FTW-STR-ReplaceWhitespace.vi" Type="VI" URL="../../Core/src/String/FTW-STR-ReplaceWhitespace.vi"/>
			<Item Name="FTW-Time-Display-Timestamp.vi" Type="VI" URL="../../Core/src/Time/FTW-Time-Display-Timestamp.vi"/>
			<Item Name="FTW-Time-DisplayFormat-Timestamp.ctl" Type="VI" URL="../../Core/src/Time/FTW-Time-DisplayFormat-Timestamp.ctl"/>
			<Item Name="FTW-Time-Elapse.vi" Type="VI" URL="../../Core/src/Time/FTW-Time-Elapse.vi"/>
			<Item Name="FTW-Time-Timer.vi" Type="VI" URL="../../Core/src/Time/FTW-Time-Timer.vi"/>
			<Item Name="FTW-ZMQ-Win64.dll" Type="Document" URL="../src/ZMQ/FTW-ZMQ-Win64.dll"/>
			<Item Name="FTWLib-Jansson-LinuxRT.so" Type="Document" URL="../../Core/src/JSON/FTWLib-Jansson-LinuxRT.so"/>
			<Item Name="FTWLib-Jansson-Win32.dll" Type="Document" URL="../../Core/src/JSON/FTWLib-Jansson-Win32.dll"/>
			<Item Name="FTWLib-Jansson-Win64.dll" Type="Document" URL="../../Core/src/JSON/FTWLib-Jansson-Win64.dll"/>
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
				<Property Name="Source[0].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[0].itemID" Type="Str">{CA5BC796-FFD1-4B93-A2AD-BC1F705041D2}</Property>
				<Property Name="Source[0].Library.allowMissingMembers" Type="Bool">true</Property>
				<Property Name="Source[0].Library.atomicCopy" Type="Bool">true</Property>
				<Property Name="Source[0].Library.LVLIBPtopLevel" Type="Bool">true</Property>
				<Property Name="Source[0].sourceInclusion" Type="Str">TopLevel</Property>
				<Property Name="Source[0].type" Type="Str">Library</Property>
				<Property Name="Source[1].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[1].itemID" Type="Ref">/My Computer/FTW-Actor.lvlib</Property>
				<Property Name="Source[1].Library.allowMissingMembers" Type="Bool">true</Property>
				<Property Name="Source[1].Library.atomicCopy" Type="Bool">true</Property>
				<Property Name="Source[1].Library.LVLIBPtopLevel" Type="Bool">true</Property>
				<Property Name="Source[1].preventRename" Type="Bool">true</Property>
				<Property Name="Source[1].sourceInclusion" Type="Str">TopLevel</Property>
				<Property Name="Source[1].type" Type="Str">Library</Property>
				<Property Name="Source[2].Container.applyInclusion" Type="Bool">true</Property>
				<Property Name="Source[2].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[2].itemID" Type="Ref">/My Computer/ZMQ</Property>
				<Property Name="Source[2].sourceInclusion" Type="Str">Include</Property>
				<Property Name="Source[2].type" Type="Str">Container</Property>
				<Property Name="SourceCount" Type="Int">3</Property>
				<Property Name="TgtF_autoIncrement" Type="Bool">true</Property>
				<Property Name="TgtF_companyName" Type="Str">Featherweight</Property>
				<Property Name="TgtF_fileDescription" Type="Str">Featherweight Actor Packed Library</Property>
				<Property Name="TgtF_fileVersion.build" Type="Int">353</Property>
				<Property Name="TgtF_fileVersion.minor" Type="Int">3</Property>
				<Property Name="TgtF_internalName" Type="Str">FTW-Actor</Property>
				<Property Name="TgtF_legalCopyright" Type="Str">featherweight.io</Property>
				<Property Name="TgtF_productName" Type="Str">Featherweight Actor Packed Library</Property>
				<Property Name="TgtF_targetfileGUID" Type="Str">{7E0E72D8-043C-40A6-86D2-860B81572F8B}</Property>
				<Property Name="TgtF_targetfileName" Type="Str">FTW-Actor.lvlibp</Property>
			</Item>
			<Item Name="My Packed Library" Type="Packed Library">
				<Property Name="Bld_buildCacheID" Type="Str">{BD1FD876-78DB-4C98-8CCA-BF07999ED0A0}</Property>
				<Property Name="Bld_buildSpecName" Type="Str">My Packed Library</Property>
				<Property Name="Bld_excludeInlineSubVIs" Type="Bool">true</Property>
				<Property Name="Bld_localDestDir" Type="Path">../builds</Property>
				<Property Name="Bld_localDestDirType" Type="Str">relativeToProject</Property>
				<Property Name="Bld_previewCacheID" Type="Str">{5E64D95E-C41C-4597-8D21-C2DFF0A38ECF}</Property>
				<Property Name="Destination[0].destName" Type="Str">FTW-Actor.lvlibp</Property>
				<Property Name="Destination[0].path" Type="Path">../builds/FTW-Actor.lvlibp</Property>
				<Property Name="Destination[0].path.type" Type="Str">relativeToProject</Property>
				<Property Name="Destination[0].preserveHierarchy" Type="Bool">true</Property>
				<Property Name="Destination[0].type" Type="Str">App</Property>
				<Property Name="Destination[1].destName" Type="Str">Support Directory</Property>
				<Property Name="Destination[1].path" Type="Path">../builds</Property>
				<Property Name="Destination[1].path.type" Type="Str">relativeToProject</Property>
				<Property Name="DestinationCount" Type="Int">2</Property>
				<Property Name="PackedLib_callersAdapt" Type="Bool">true</Property>
				<Property Name="Source[0].itemID" Type="Str">{8936CFBD-794E-40E6-9140-EF7F6288ED1A}</Property>
				<Property Name="Source[0].type" Type="Str">Container</Property>
				<Property Name="Source[1].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[1].itemID" Type="Ref">/My Computer/FTW-Actor.lvlib</Property>
				<Property Name="Source[1].Library.allowMissingMembers" Type="Bool">true</Property>
				<Property Name="Source[1].Library.atomicCopy" Type="Bool">true</Property>
				<Property Name="Source[1].Library.LVLIBPtopLevel" Type="Bool">true</Property>
				<Property Name="Source[1].preventRename" Type="Bool">true</Property>
				<Property Name="Source[1].sourceInclusion" Type="Str">TopLevel</Property>
				<Property Name="Source[1].type" Type="Str">Library</Property>
				<Property Name="Source[2].Container.applyInclusion" Type="Bool">true</Property>
				<Property Name="Source[2].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[2].itemID" Type="Ref">/My Computer/Include</Property>
				<Property Name="Source[2].sourceInclusion" Type="Str">Include</Property>
				<Property Name="Source[2].type" Type="Str">Container</Property>
				<Property Name="SourceCount" Type="Int">3</Property>
				<Property Name="TgtF_autoIncrement" Type="Bool">true</Property>
				<Property Name="TgtF_companyName" Type="Str">Featherweight</Property>
				<Property Name="TgtF_enableDebugging" Type="Bool">true</Property>
				<Property Name="TgtF_fileDescription" Type="Str">Featherweight Packed Library</Property>
				<Property Name="TgtF_fileVersion.build" Type="Int">355</Property>
				<Property Name="TgtF_fileVersion.major" Type="Int">0</Property>
				<Property Name="TgtF_fileVersion.minor" Type="Int">3</Property>
				<Property Name="TgtF_internalName" Type="Str">FTW-Actor</Property>
				<Property Name="TgtF_legalCopyright" Type="Str">featherweight.io</Property>
				<Property Name="TgtF_productName" Type="Str">Featherweight Packed Library</Property>
				<Property Name="TgtF_targetfileGUID" Type="Str">{8FD1C9A3-FE71-4C13-BDB3-380B163DF73A}</Property>
				<Property Name="TgtF_targetfileName" Type="Str">FTW-Actor.lvlibp</Property>
			</Item>
		</Item>
	</Item>
</Project>
