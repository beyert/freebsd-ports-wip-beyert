--- lisp/gnus/binhex.el.orig	2006-03-16 06:02:38 UTC
+++ lisp/gnus/binhex.el
@@ -289,7 +289,9 @@ If HEADER-ONLY is non-nil only decode header and retur
     (save-excursion
       (goto-char start)
       (when (re-search-forward binhex-begin-line nil t)
-	(let ((cdir default-directory) default-process-coding-system)
+	(let ((cdir default-directory)
+	      (coding-system-for-read 'binary)
+	      (coding-system-for-write 'binary))
 	  (unwind-protect
 	      (progn
 		(set-buffer (setq work-buffer
