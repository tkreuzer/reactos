<?xml version="1.0"?>
<!DOCTYPE module SYSTEM "../../../../tools/rbuild/project.dtd">
<module name="d3d8" type="win32dll" installbase="system32" installname="d3d8.dll" unicode="yes">
	<importlibrary definition="d3d8.spec" />
	<include base="d3d8">.</include>
	<include base="ReactOS">include/reactos/wine</include>
	<define name="__WINESRC__" />
	<define name="USE_WIN32_OPENGL" />

	<library>uuid</library>
	<library>wine</library>
	<library>user32</library>
	<library>gdi32</library>
	<library>advapi32</library>
	<library>wined3d</library>

	<file>cubetexture.c</file>
	<file>d3d8_main.c</file>
	<file>device.c</file>
	<file>directx.c</file>
	<file>indexbuffer.c</file>
	<file>pixelshader.c</file>
	<file>surface.c</file>
	<file>swapchain.c</file>
	<file>texture.c</file>
	<file>vertexbuffer.c</file>
	<file>vertexdeclaration.c</file>
	<file>vertexshader.c</file>
	<file>volume.c</file>
	<file>volumetexture.c</file>
	<file>version.rc</file>

	<dependency>wineheaders</dependency>
</module>