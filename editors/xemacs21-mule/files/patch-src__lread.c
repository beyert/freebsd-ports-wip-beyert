--- src/lread.c.orig	2005-01-30 18:55:21.000000000 -0800
+++ src/lread.c	2014-10-09 15:49:52.000000000 -0700
@@ -2278,10 +2278,7 @@
 	      ch = reader_nextchar (readcharfun);
 	      if (ch != ')')
 		{
-		  unreadchar (readcharfun, ch);
-		  return Fsignal (Qinvalid_read_syntax,
-				  list1 (build_string
-					 ("Weird old-backquote syntax")));
+
 		}
 	      return list2 (Qbacktick, tem);
 	    }
@@ -2303,10 +2300,7 @@
 		  ch = reader_nextchar (readcharfun);
 		  if (ch != ')')
 		    {
-		      unreadchar (readcharfun, ch);
-		      return Fsignal (Qinvalid_read_syntax,
-				      list1 (build_string
-					     ("Weird old-backquote syntax")));
+
 		    }
 		  return list2 (comma_type, tem);
 		}
