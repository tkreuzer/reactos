<?xml version="1.0"?>
<!DOCTYPE module SYSTEM "../../../tools/rbuild/project.dtd">
<module name="fastfat" type="kernelmodedriver" installbase="system32/drivers" installname="fastfat.sys">
	<bootstrap installbase="$(CDOUTPUT)" />
	<include base="fastfat">.</include>
	<library>ntoskrnl</library>
	<library>hal</library>
	<file>blockdev.c</file>
	<file>cleanup.c</file>
	<file>close.c</file>
	<file>create.c</file>
	<file>dir.c</file>
	<file>direntry.c</file>
	<file>dirwr.c</file>
	<file>ea.c</file>
	<file>fat.c</file>
	<file>fastio.c</file>
	<file>fcb.c</file>
	<file>finfo.c</file>
	<file>flush.c</file>
	<file>fsctl.c</file>
	<file>iface.c</file>
	<file>misc.c</file>
	<file>rw.c</file>
	<file>shutdown.c</file>
	<file>string.c</file>
	<file>volume.c</file>
	<file>vfatfs.rc</file>
	<pch>vfat.h</pch>
</module>