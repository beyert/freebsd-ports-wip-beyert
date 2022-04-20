--- src/xenia/config.cc.orig	2021-06-09 19:56:36 UTC
+++ src/xenia/config.cc
@@ -8,6 +8,7 @@
  */
 
 #include "config.h"
+#include <fstream>
 
 #include "third_party/cpptoml/include/cpptoml.h"
 #include "third_party/fmt/include/fmt/format.h"
@@ -18,14 +19,13 @@
 #include "xenia/base/string.h"
 #include "xenia/base/string_buffer.h"
 
-std::shared_ptr<cpptoml::table> ParseFile(
-    const std::filesystem::path& filename) {
-  std::ifstream file(filename);
-  if (!file.is_open()) {
-    throw cpptoml::parse_exception(xe::path_to_utf8(filename) +
+std::shared_ptr<cpptoml::table> ParseFile(const std::filesystem::path& fn) {
+  std::ifstream ifn(fn);
+  if (!ifn.is_open()) {
+    throw cpptoml::parse_exception(xe::path_to_utf8(fn) +
                                    " could not be opened for parsing");
   }
-  cpptoml::parser p(file);
+  cpptoml::parser p(ifn);
   return p.parse();
 }
 
