--- cmake/SearchForStuff.cmake.orig	2014-01-24 10:07:08.000000000 -0800
+++ cmake/SearchForStuff.cmake	2014-03-23 21:47:51.000000000 -0700
@@ -1,19 +1,19 @@
 #-------------------------------------------------------------------------------
 #						Search all libraries on the system
 #-------------------------------------------------------------------------------
-# Do not search Lib in /usr/lib64. Hope it is not overwritten in find_package or others macro
-SET(FIND_LIBRARY_USE_LIB64_PATHS FALSE)
+# Do not search Lib in /usr/local/lib. Hope it is not overwritten in find_package or others macro
+#SET(FIND_LIBRARY_USE_LIB64_PATHS FALSE)
 
-## Linux only libraries
-if(Linux)
+## UNIX only libraries
+if(UNIX)
     # Most plugins (if not all) and PCSX2 core need gtk2, so set the required flags
     find_package(GTK2 REQUIRED gtk)
     if(GTK2_FOUND)
         # From version 2.21.3 gtk moved gdk-pixbuf into a separate module
         # Cmake need to be fixed. For the moment uses a manual detection.
         find_path(GDK_PIXBUF_INCLUDE_DIRS NAMES gdk-pixbuf/gdk-pixbuf.h PATHS
-            /usr/include/gdk-pixbuf-2.0
-            /usr/include)
+            /usr/local/include/gdk-pixbuf-2.0
+            /usr/local/include)
         if (GDK_PIXBUF_INCLUDE_DIRS)
             set(GTK2_INCLUDE_DIRS "${GDK_PIXBUF_INCLUDE_DIRS}" "${GTK2_INCLUDE_DIRS}")
             # Remove duplicates when cmake will be fixed
@@ -22,7 +22,7 @@
     endif(GTK2_FOUND)
 
     find_package(X11)
-endif(Linux)
+endif(UNIX)
 
 ## Use cmake package to find module
 find_package(ALSA)
@@ -46,7 +46,17 @@
 else()
     set(wxWidgets_CONFIG_OPTIONS --unicode=yes)
 endif()
+
+# add from CMakeLists.txt in databases/pgagent
+SET(WX_VERSION "2.8")
+FIND_PACKAGE(WX REQUIRED)
+INCLUDE_DIRECTORIES(${WX_INCLUDE_DIRS})
+ADD_DEFINITIONS(${WX_DEFINITIONS})
+LINK_DIRECTORIES(${WX_LIBRARY_DIRS})
+
+set(wxWidgets_LIB_DIR "/usr/local/lib")
 find_package(wxWidgets COMPONENTS base core adv)
+set(wxWidgets_FOUND TRUE)
 find_package(ZLIB)
 
 ## Use pcsx2 package to find module
@@ -66,7 +76,7 @@
 
 # Note for include_directory: The order is important to avoid a mess between include file from your system and the one of pcsx2
 # If you include first 3rdparty, all 3rdpary include will have a higer priority...
-# If you include first /usr/include, all system include will have a higer priority over the pcsx2 one...
+# If you include first /usr/local/include, all system include will have a higer priority over the pcsx2 one...
 # Current implementation: 
 # 1/ include 3rdparty sub-directory that we will used (either request or fallback)
 # 2/ include system one
@@ -78,7 +88,7 @@
 #----------------------------------------
 #		    Use system include (if not 3rdparty one)
 #----------------------------------------
-if(Linux)
+if(UNIX)
 	if(GTK2_FOUND)
 		include_directories(${GTK2_INCLUDE_DIRS})
 	endif(GTK2_FOUND)
@@ -86,7 +96,7 @@
 	if(X11_FOUND)
 		include_directories(${X11_INCLUDE_DIR})
 	endif(X11_FOUND)
-endif(Linux)
+endif(UNIX)
 
 if(AIO_FOUND)
     include_directories(${AIO_INCLUDE_DIR})
@@ -146,26 +156,24 @@
 endif(SPARSEHASH_NEW_FOUND)
 
 if(wxWidgets_FOUND)
-    if(Linux)
+    if(UNIX)
         # Force the use of 32 bit library configuration on
-        # 64 bits machine with 32 bits library in /usr/lib32
+        # 64 bits machine with 32 bits library in /usr/local/lib32
         if(CMAKE_SIZEOF_VOID_P MATCHES "8")
             ## There is no guarantee that wx-config is a link to a 32 bits library. So you need to force the destinity
             # Library can go into 3 path major paths (+ multiarch but you will see that later when implementation is done)
-            # 1/ /usr/lib32 (32 bits only)
-            # 2/ /usr/lib64 (64 bits only)
-            # 3/ /usr/lib   (32 or 64 bits depends on distributions)
-            if (EXISTS "/usr/lib32/wx")
-                STRING(REGEX REPLACE "/usr/lib/wx" "/usr/lib32/wx" wxWidgets_INCLUDE_DIRS "${wxWidgets_INCLUDE_DIRS}")
-                STRING(REGEX REPLACE "/usr/lib64/wx" "/usr/lib32/wx" wxWidgets_INCLUDE_DIRS "${wxWidgets_INCLUDE_DIRS}")
-            endif (EXISTS "/usr/lib32/wx")
-            if (EXISTS "/usr/lib/wx")
-                STRING(REGEX REPLACE "/usr/lib64/wx" "/usr/lib/wx" wxWidgets_INCLUDE_DIRS "${wxWidgets_INCLUDE_DIRS}")
-            endif (EXISTS "/usr/lib/wx")
+            # 1/ /usr/local/lib32 (32 bits only)
+            # 3/ /usr/local/lib   (32 or 64 bits depends on distributions)
+            if (EXISTS "/usr/local/lib32/wx")
+                STRING(REGEX REPLACE "/usr/local/lib/wx" "/usr/local/lib32/wx" wxWidgets_INCLUDE_DIRS "${wxWidgets_INCLUDE_DIRS}")
+            endif (EXISTS "/usr/local/lib32/wx")
+            if (EXISTS "/usr/local/lib/wx")
+                STRING(REGEX REPLACE "/usr/local/lib/wx" "/usr/local/lib/wx" wxWidgets_INCLUDE_DIRS "${wxWidgets_INCLUDE_DIRS}")
+            endif (EXISTS "/usr/local/lib/wx")
             # Multiarch ubuntu/debian
-            STRING(REGEX REPLACE "/usr/lib/x86_64-linux-gnu" "/usr/lib/i386-linux-gnu" wxWidgets_INCLUDE_DIRS "${wxWidgets_INCLUDE_DIRS}")
+            STRING(REGEX REPLACE "/usr/local/lib/x86_64-linux-gnu" "/usr/local/lib/i386-linux-gnu" wxWidgets_INCLUDE_DIRS "${wxWidgets_INCLUDE_DIRS}")
         endif(CMAKE_SIZEOF_VOID_P MATCHES "8")
-    endif(Linux)
+    endif(UNIX)
 
 	include(${wxWidgets_USE_FILE})
 endif(wxWidgets_FOUND)
