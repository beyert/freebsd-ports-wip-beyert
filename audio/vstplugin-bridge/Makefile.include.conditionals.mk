.if ${FLAVORS} != ""
# set WINEARCH based on architecture
.if ${ARCH} == amd64
WINEARCH="x86_64"
.elif ${ARCH} == i386
WINEARCH="${ARCH}"
.endif

# set WINEVERSION based on FLAVOR, if specified
.if ${FLAVOR:Mwine_devel} || ${FLAVOR:Mwine}
PORT_OPTIONS_TEMP=
.for opt in ${PORT_OPTIONS}
.if ${opt} != "WINE_DEVEL" && ${opt} != "WINE"
PORT_OPTIONS_TEMP+=	${opt}
.endif
.endfor
PORT_OPTIONS=	${PORT_OPTIONS_TEMP}
.if ${FLAVOR:Mwine_devel}
PORT_OPTIONS+=	WINE_DEVEL
.else
PORT_OPTIONS+=	WINE
.endif
.else
OPTIONS_DEFAULT+=	WINE
.endif

# based on PORT_OPTIONS, set dependencies to wine version accordingly
.if ${PORT_OPTIONS:MWINE_DEVEL}
BUILD_DEPENDS+=	${LOCALBASE}/lib/wine/${WINEARCH}-unix/ntdll.so:emulators/wine-devel
RUN_DEPENDS+=	${LOCALBASE}/lib/wine/${WINEARCH}-unix/ntdll.so:emulators/wine-devel
.elif ${PORT_OPTIONS:MWINE}
BUILD_DEPENDS+=	${LOCALBASE}/lib/libwine.so:emulators/wine
LIB_DEPENDS+=	libwine.so:emulators/wine
RUN_DEPENDS+=	${LOCALBASE}/lib/wine/xaudio2_0.dll.so:emulators/wine
.endif
.endif

# no idea why this is necessary...
.if "${USES}" == "metaport"
NO_BUILD=	yes
.endif

.if defined(NO_BUILD)
.undef USE_GITHUB
WRKDIR=	${WRKDIRPREFIX}${.CURDIR}/work
.endif
