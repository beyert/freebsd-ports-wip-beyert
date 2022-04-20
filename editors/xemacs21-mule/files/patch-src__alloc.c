--- src/alloc.c.orig	2005-01-30 18:55:02.000000000 -0800
+++ src/alloc.c	2014-09-04 21:46:21.000000000 -0700
@@ -3367,21 +3367,6 @@
 	      Fset_frame_pointer (frame, cursor);
 	    }
 	}
-
-      /* Don't print messages to the stream device. */
-      if (!cursor_changed && !FRAME_STREAM_P (f))
-	{
-	  char *msg = (STRINGP (Vgc_message)
-		       ? GETTEXT ((char *) XSTRING_DATA (Vgc_message))
-		       : 0);
-	  Lisp_Object args[2], whole_msg;
-	  args[0] = build_string (msg ? msg :
-				  GETTEXT ((const char *) gc_default_message));
-	  args[1] = build_string ("...");
-	  whole_msg = Fconcat (2, args);
-	  echo_area_message (f, (Bufbyte *) 0, whole_msg, 0, -1,
-			     Qgarbage_collecting);
-	}
     }
 
   /***** Now we actually start the garbage collection. */
@@ -3531,21 +3516,6 @@
 	  char *msg = (STRINGP (Vgc_message)
 		       ? GETTEXT ((char *) XSTRING_DATA (Vgc_message))
 		       : 0);
-
-	  /* Show "...done" only if the echo area would otherwise be empty. */
-	  if (NILP (clear_echo_area (selected_frame (),
-				     Qgarbage_collecting, 0)))
-	    {
-	      Lisp_Object args[2], whole_msg;
-	      args[0] = build_string (msg ? msg :
-				      GETTEXT ((const char *)
-					       gc_default_message));
-	      args[1] = build_string ("... done");
-	      whole_msg = Fconcat (2, args);
-	      echo_area_message (selected_frame (), (Bufbyte *) 0,
-				 whole_msg, 0, -1,
-				 Qgarbage_collecting);
-	    }
 	}
     }
 
