<module name="quartz_winetest" type="win32cui" installbase="bin" installname="quartz_winetest.exe" allowwarnings="true">
	<include base="quartz_winetest">.</include>
	<define name="__ROS_LONG64__" />
	<file>avisplitter.c</file>
	<file>dsoundrender.c</file>
	<file>filtergraph.c</file>
	<file>filtermapper.c</file>
	<file>memallocator.c</file>
	<file>misc.c</file>
	<file>referenceclock.c</file>
	<file>videorenderer.c</file>
	<file>testlist.c</file>
	<library>wine</library>
	<library>oleaut32</library>
	<library>ole32</library>
	<library>advapi32</library>
	<library>ntdll</library>
</module>