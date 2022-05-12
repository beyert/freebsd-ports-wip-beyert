--- scheme/env/command.scm.orig	2004-03-11 09:52:54 UTC
+++ scheme/env/command.scm
@@ -422,7 +422,7 @@
               ((char=? (string-ref line 0) #\n) #f)
               (else (loop count)))))))
 
-(define *y-or-n-eof-count* 100)
+(define *y-or-n-eof-count* 0)
 
 (define (read-line port)
   (let loop ((l '()))
