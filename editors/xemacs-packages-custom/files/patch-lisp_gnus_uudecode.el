--- lisp/gnus/uudecode.el.orig	2006-03-16 06:02:45 UTC
+++ lisp/gnus/uudecode.el
@@ -100,7 +100,8 @@ used is specified by `uudecode-decoder-program'."
 			      (make-temp-name "uu")
 			      uudecode-temporary-file-directory))))
 	(let ((cdir default-directory)
-	      default-process-coding-system)
+	      (coding-system-for-read 'binary)
+	      (coding-system-for-write 'binary))
 	  (unwind-protect
 	      (with-temp-buffer
 		(insert "begin 600 " (file-name-nondirectory tempfile) "\n")
