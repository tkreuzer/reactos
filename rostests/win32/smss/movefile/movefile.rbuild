<module name="movefile" type="win32cui" installbase="system32" installname="movefiletest.exe">
	<include base="movefile">.</include>
	<library>advapi32</library>
	<library>user32</library>
	<file>movefile.cpp</file>
	<file>movefile.rc</file>