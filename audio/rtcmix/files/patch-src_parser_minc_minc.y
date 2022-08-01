--- src/parser/minc/minc.y.orig	2022-06-20 19:29:55 UTC
+++ src/parser/minc/minc.y
@@ -358,7 +358,7 @@ exp: rstmt				{ MPRINT("exp: rstmt"); $$ = $1; }
     | expblk                { MPRINT("exp: expblk");   $$ = $1; }
 	| '{' '}'				{ MPRINT("exp: {}");	$$ = new NodeList(new NodeEmptyListElem()); }
 	| TOK_ARG_QUERY		    { $$ = parseArgumentQuery(yytext, &flerror); }
-	| TOK_ARG			    { $$ = parseScoreArgument(yytext, &flerror) }
+	| TOK_ARG			    { $$ = parseScoreArgument(yytext, &flerror); }
     
 	| TOK_TRUE			{ $$ = new NodeConstf(1.0); }
 	| TOK_FALSE			{ $$ = new NodeConstf(0.0); }
