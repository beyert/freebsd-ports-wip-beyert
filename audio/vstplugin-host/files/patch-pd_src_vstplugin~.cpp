--- pd/src/vstplugin~.cpp.orig	2022-02-11 10:14:58 UTC
+++ pd/src/vstplugin~.cpp
@@ -283,9 +283,9 @@ static void readIniFile(){
         try {
             gPluginDict.read(path);
         } catch (const Error& e){
-            error("couldn't read cache file: %s", e.what());
+            pd_error("couldn't read cache file: %s", e.what());
         } catch (const std::exception& e){
-            error("couldn't read cache file: unexpected exception (%s)", e.what());
+            pd_error("couldn't read cache file: unexpected exception (%s)", e.what());
         }
     }
 }
@@ -301,7 +301,7 @@ static void writeIniFile(){
         }
         gPluginDict.write(dir + "/" CACHE_FILE);
     } catch (const Error& e){
-        error("couldn't write cache file: %s", e.what());
+        pd_error("couldn't write cache file: %s", e.what());
     }
 }
 
@@ -382,7 +382,7 @@ void postBug(const char *fmt, T... args){
 template<bool async = false, typename... T>
 void postError(const char *fmt, T... args){
     PdScopedLock<async> lock;
-    error(fmt, args...);
+    pd_error(fmt, args...);
 }
 
 
