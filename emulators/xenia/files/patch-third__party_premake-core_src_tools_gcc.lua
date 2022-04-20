--- third_party/premake-core/src/tools/gcc.lua.orig	2020-11-27 20:23:57 UTC
+++ third_party/premake-core/src/tools/gcc.lua
@@ -516,9 +516,17 @@
 					table.insert(static_syslibs, "-l" .. name)
 				elseif endswith(name, ":shared") then
 					name = string.sub(name, 0, -8)
-					table.insert(shared_syslibs, "-l" .. name)
+					if string.len(name) > 0 then
+						table.insert(shared_syslibs, "-l" .. name)
+					else
+						table.insert(shared_syslibs, "" .. name)
+					end
 				else
-					table.insert(shared_syslibs, "-l" .. name)
+					if string.len(name) > 0 then
+						table.insert(shared_syslibs, "-l" .. name)
+					else
+						table.insert(shared_syslibs, "" .. name)
+					end
 				end
 			end
 		end
