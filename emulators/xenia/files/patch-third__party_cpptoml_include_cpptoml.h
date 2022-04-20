--- third_party/cpptoml/include/cpptoml.h.orig	2018-10-22 20:28:28 UTC
+++ third_party/cpptoml/include/cpptoml.h
@@ -12,7 +12,7 @@
 #include <clocale>
 #include <cstdint>
 #include <cstring>
-#include <fstream>
+#include <boost/nowide/fstream.hpp>
 #include <iomanip>
 #include <map>
 #include <memory>
@@ -188,8 +188,7 @@ inline std::ostream& operator<<(std::ostream& os, cons
     fill_guard g{os};
     os.fill('0');
 
-    using std::setw;
-    os << setw(4) << dt.year << "-" << setw(2) << dt.month << "-" << setw(2)
+    os << std::setw(4) << dt.year << "-" << std::setw(2) << dt.month << "-" << std::setw(2)
        << dt.day;
 
     return os;
@@ -200,9 +199,8 @@ inline std::ostream& operator<<(std::ostream& os, cons
     fill_guard g{os};
     os.fill('0');
 
-    using std::setw;
-    os << setw(2) << ltime.hour << ":" << setw(2) << ltime.minute << ":"
-       << setw(2) << ltime.second;
+    os << std::setw(2) << ltime.hour << ":" << std::setw(2) << ltime.minute << ":"
+       << std::setw(2) << ltime.second;
 
     if (ltime.microsecond > 0)
     {
@@ -224,8 +222,6 @@ inline std::ostream& operator<<(std::ostream& os, cons
     fill_guard g{os};
     os.fill('0');
 
-    using std::setw;
-
     if (zo.hour_offset != 0 || zo.minute_offset != 0)
     {
         if (zo.hour_offset > 0)
@@ -236,7 +232,7 @@ inline std::ostream& operator<<(std::ostream& os, cons
         {
             os << "-";
         }
-        os << setw(2) << std::abs(zo.hour_offset) << ":" << setw(2)
+        os << std::setw(2) << std::abs(zo.hour_offset) << ":" << std::setw(2)
            << std::abs(zo.minute_offset);
     }
     else
