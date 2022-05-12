--- src/lread.c.orig	2005-01-31 02:55:21 UTC
+++ src/lread.c
@@ -2278,10 +2278,7 @@ retry:
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
@@ -2303,10 +2300,7 @@ retry:
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
