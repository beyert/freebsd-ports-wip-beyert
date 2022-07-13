post-patch:
.if defined(PREFIX)
	@${REINPLACE_CMD} -e 's|/usr/local/include|${LOCALBASE}/include|g' \
		-e 's|-L/usr/local/lib|-L${PREFIX}/lib|' \
		${WRKSRC}/CMakeLists.txt
.endif
