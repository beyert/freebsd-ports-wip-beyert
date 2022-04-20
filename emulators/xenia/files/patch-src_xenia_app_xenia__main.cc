--- src/xenia/app/xenia_main.cc.orig	2021-06-09 19:56:36 UTC
+++ src/xenia/app/xenia_main.cc
@@ -226,7 +226,7 @@ int xenia_main(const std::vector<std::string>& args) {
     if (!cvars::portable &&
         !std::filesystem::exists(storage_root / "portable.txt")) {
       storage_root = xe::filesystem::GetUserFolder();
-#if defined(XE_PLATFORM_WIN32) || defined(XE_PLATFORM_GNU_LINUX)
+#if defined(XE_PLATFORM_WIN32) || defined(XE_PLATFORM_GNU_LINUX) || defined(XE_PLATFORM_FREEBSD)
       storage_root = storage_root / "Xenia";
 #else
       // TODO(Triang3l): Point to the app's external storage "files" directory
