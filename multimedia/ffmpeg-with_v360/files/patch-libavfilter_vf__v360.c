--- libavfilter/vf_v360.c.orig	2021-10-24 20:47:07 UTC
+++ libavfilter/vf_v360.c
@@ -162,6 +162,7 @@ static const AVOption v360_options[] = {
     {    "iv_fov", "input vertical field of view",  OFFSET(iv_fov), AV_OPT_TYPE_FLOAT,  {.dbl=45.f},     0.00001f,               360.f,TFLAGS, "iv_fov"},
     {    "id_fov", "input diagonal field of view",  OFFSET(id_fov), AV_OPT_TYPE_FLOAT,  {.dbl=0.f},           0.f,               360.f,TFLAGS, "id_fov"},
     {"alpha_mask", "build mask in alpha plane",      OFFSET(alpha), AV_OPT_TYPE_BOOL,   {.i64=0},               0,                   1, FLAGS, "alpha"},
+    {"reset_rot", "reset_rotation",      OFFSET(reset_rot), AV_OPT_TYPE_BOOL,   {.i64=0},               0,                   1, TFLAGS, "reset_rot"},
     { NULL }
 };
 
@@ -4703,6 +4704,13 @@ static int filter_frame(AVFilterLink *inlink, AVFrame 
     return ff_filter_frame(outlink, out);
 }
 
+static void reset_rot(V360Context *s)
+{
+    s->rot_quaternion[0][0] = 1.f;
+    s->rot_quaternion[0][1] = s->rot_quaternion[0][2] = s->rot_quaternion[0][3] = 0.f;
+
+}
+
 static int process_command(AVFilterContext *ctx, const char *cmd, const char *args,
                            char *res, int res_len, int flags)
 {
@@ -4710,11 +4718,15 @@ static int process_command(AVFilterContext *ctx, const
     int ret;
 
     s->yaw = s->pitch = s->roll = 0.f;
+    s->reset_rot = 0;
 
     ret = ff_filter_process_command(ctx, cmd, args, res, res_len, flags);
     if (ret < 0)
         return ret;
 
+    if (s->reset_rot)
+        reset_rot(s);
+
     return config_output(ctx->outputs[0]);
 }
 
@@ -4722,8 +4734,7 @@ static av_cold int init(AVFilterContext *ctx)
 {
     V360Context *s = ctx->priv;
 
-    s->rot_quaternion[0][0] = 1.f;
-    s->rot_quaternion[0][1] = s->rot_quaternion[0][2] = s->rot_quaternion[0][3] = 0.f;
+    reset_rot(s);
 
     return 0;
 }
