--- config.mk.orig	2013-11-26 00:15:04.000000000 -0800
+++ config.mk	2016-05-08 22:54:09.201999000 -0700
@@ -13,7 +13,7 @@
 XINERAMAFLAGS = -DXINERAMA
 
 # Xft, comment if you don't want it
-XFTINC = -I/usr/include/freetype2
+XFTINC = -I/usr/local/include/freetype2
 XFTLIBS  = -lXft -lXrender -lfreetype -lz -lfontconfig
 
 # includes and libs
@@ -21,10 +21,10 @@
 LIBS = -L${X11LIB} -lX11 ${XINERAMALIBS} ${XFTLIBS}
 
 # flags
-CPPFLAGS = -D_BSD_SOURCE -D_POSIX_C_SOURCE=2 -DVERSION=\"${VERSION}\" ${XINERAMAFLAGS}
+CPPFLAGS+= -D_BSD_SOURCE -D_POSIX_C_SOURCE=2 -DVERSION=\"${VERSION}\" ${XINERAMAFLAGS}
 #CFLAGS   = -g -std=c99 -pedantic -Wall -O0 ${INCS} ${CPPFLAGS}
-CFLAGS   = -std=c99 -pedantic -Wall -Os ${INCS} ${CPPFLAGS}
-LDFLAGS  = -s ${LIBS}
+CFLAGS  += -std=c99 ${INCS} ${CPPFLAGS}
+LDFLAGS  += -s ${LIBS}
 
 # compiler and linker
 CC = cc
