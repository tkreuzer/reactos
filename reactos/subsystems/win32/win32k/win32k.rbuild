<?xml version="1.0"?>
<!DOCTYPE group SYSTEM "../../../tools/rbuild/project.dtd">
<group>
<module name="win32k" type="kernelmodedriver" installbase="system32" installname="win32k.sys" crt="libcntpr">
	<importlibrary definition="win32k.pspec" />
	<library>pseh</library>
	<library>ntoskrnl</library>
	<library>hal</library>
	<library>ftfd</library>
	<library>dxguid</library>
	<file>win32k.rc</file>
	<include base="win32k">.</include>
	<include base="win32k">include</include>
	<include base="win32k" root="intermediate">.</include>
	<include base="ntoskrnl">include</include>
	<include base="freetype">include</include>
	<include base="ReactOS">include/reactos/subsys</include>
	<include base="ReactOS">include/reactos/drivers</include>
	<compilerflag compilerset="gcc">-fms-extensions</compilerflag>
	<compilerflag compilerset="msc">/wd4276</compilerflag>
	<define name="LANGPACK" />
	<define name="_WIN32K_" />
	<pch>pch.h</pch>

	<directory name="dib" root="intermediate">
		<file>dib8gen.c</file>
		<file>dib16gen.c</file>
		<file>dib32gen.c</file>
	</directory>

	<directory name="dib">
		<file>dib1bpp.c</file>
		<file>dib4bpp.c</file>
		<file>dib8bpp.c</file>
		<file>dib16bpp.c</file>
		<file>dib24bpp.c</file>
		<file>dib32bpp.c</file>
		<file>dib.c</file>
		<file>floodfill.c</file>
		<file>stretchblt.c</file>

		<if property="ARCH" value="i386">
			<directory name="i386">
				<file>dib24bpp_hline.s</file>
				<file>dib32bpp_hline.s</file>
				<file>dib32bpp_colorfill.s</file>
			</directory>
		</if>
		<ifnot property="ARCH" value="i386">
			<file>dib24bppc.c</file>
			<file>dib32bppc.c</file>
		</ifnot>
	</directory>
	<directory name="eng">
		<file>alphablend.c</file>
		<file>bitblt.c</file>
		<file>engbrush.c</file>
		<file>engevent.c</file>
		<file>clip.c</file>
		<file>copybits.c</file>
		<file>debug.c</file>
		<file>device.c</file>
		<file>driverobj.c</file>
		<file>error.c</file>
		<file>float.c</file>
		<if property="ARCH" value="i386">
			<directory name="i386">
				<file>floatobj.S</file>
			</directory>
		</if>
		<file>gradient.c</file>
		<file>lineto.c</file>
		<file>mapping.c</file>
		<file>mem.c</file>
		<file>engmisc.c</file>
		<file>mouse.c</file>
		<file>paint.c</file>
		<file>perfcnt.c</file>
		<file>semaphor.c</file>
		<file>sort.c</file>
		<file>string.c</file>
		<file>stretchblt.c</file>
		<file>surface.c</file>
		<file>transblt.c</file>
		<file>engwindow.c</file>
		<file>xlate.c</file>
	</directory>
	<directory name="ldr">
		<file>loader.c</file>
	</directory>
	<directory name="main">
		<file>dllmain.c</file>
	</directory>
	<directory name="misc">
		<file>driver.c</file>
		<file>err.c</file>
		<file>file.c</file>
		<file>math.c</file>
		<file>rtlstr.c</file>
		<file>copy.c</file>
		<file>registry.c</file>
		<file>usrheap.c</file>
		<if property="ARCH" value="i386">
			<directory name="i386">
				<file>cos_asm.s</file>
				<file>sin_asm.s</file>
				<file>atan2_asm.s</file>
				<file>floor_asm.s</file>
				<file>ceil_asm.s</file>
			</directory>
		</if>
	</directory>
	<directory name="ntddraw">
		<file>ddraw.c</file>
		<file>dd.c</file>
		<file>ddsurf.c</file>
		<file>d3d.c</file>
		<file>dvp.c</file>
		<file>mocomp.c</file>
		<file>eng.c</file>
		<file>dxeng.c</file>
	</directory>
	<directory name="ntuser">
		<file>accelerator.c</file>
		<file>callback.c</file>
		<file>callproc.c</file>
		<file>caret.c</file>
		<file>class.c</file>
		<file>clipboard.c</file>
		<file>csr.c</file>
		<file>cursoricon.c</file>
		<file>defwnd.c</file>
		<file>desktop.c</file>
		<file>display.c</file>
		<file>event.c</file>
		<file>focus.c</file>
		<file>guicheck.c</file>
		<file>hook.c</file>
		<file>hotkey.c</file>
		<file>input.c</file>
		<file>keyboard.c</file>
		<file>kbdlayout.c</file>
		<file>menu.c</file>
		<file>message.c</file>
		<file>metric.c</file>
		<file>misc.c</file>
		<file>monitor.c</file>
		<file>msgqueue.c</file>
		<file>ntstubs.c</file>
		<file>ntuser.c</file>
		<file>painting.c</file>
		<file>prop.c</file>
		<file>scrollbar.c</file>
		<file>session.c</file>
		<file>simplecall.c</file>
		<file>sysparams.c</file>
		<file>timer.c</file>
		<file>useratom.c</file>
		<file>vis.c</file>
		<file>windc.c</file>
		<file>window.c</file>
		<file>winpos.c</file>
		<file>winsta.c</file>
		<file>object.c</file>
	</directory>
	<directory name="objects">
		<file>arc.c</file>
		<file>bezier.c</file>
		<file>bitblt.c</file>
		<file>bitmaps.c</file>
		<file>brush.c</file>
		<file>cliprgn.c</file>
		<file>coord.c</file>
		<file>dcattr.c</file>
		<file>dclife.c</file>
		<file>dcobjs.c</file>
		<file>dcstate.c</file>
		<file>dcutil.c</file>
		<file>device.c</file>
		<file>dibobj.c</file>
		<file>drawing.c</file>
		<file>fillshap.c</file>
		<file>font.c</file>
		<file>freetype.c</file>
		<file>gdibatch.c</file>
		<file>gdiobj.c</file>
		<file>icm.c</file>
		<file>line.c</file>
		<file>metafile.c</file>
		<file>palette.c</file>
		<file>path.c</file>
		<file>pen.c</file>
		<file>polyfill.c</file>
		<file>print.c</file>
		<file>rect.c</file>
		<file>region.c</file>
		<file>stockobj.c</file>
		<file>text.c</file>
		<file>wingl.c</file>
		<file>xformobj.c</file>
	</directory>
	<directory name="stubs">
		<file>stubs.c</file>
		<file>umpdstubs.c</file>
	</directory>
</module>
</group>