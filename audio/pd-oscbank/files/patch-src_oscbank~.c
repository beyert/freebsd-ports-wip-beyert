--- src/oscbank~.c.orig	2012-02-28 17:40:14 UTC
+++ src/oscbank~.c
@@ -184,8 +184,8 @@ static void oscbank_index(t_oscbank *x, t_floatarg in)
 	int quietest_index = 0;
 	float freq = fabsf(x->infreq);
 
-	if( iindex < 0)	{
-		error("oscbank~ needs a positive index.");
+	if(iindex < 0)	{
+		pd_error(x, "oscbank~ needs a positive index.");
 		return;
 	}
 
