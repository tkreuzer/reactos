<?xml version="1.0"?>
<!DOCTYPE module SYSTEM "../../../tools/rbuild/project.dtd">
<module name="psapi_winetest" type="win32cui" installbase="bin" installname="psapi_winetest.exe" allowwarnings="true">
	<include base="psapi_winetest">.</include>
	<define name="__ROS_LONG64__" />
	<library>ntdll</library>
	<library>psapi</library>
	<file>testlist.c</file>
	<file>psapi_main.c</file>
</module>