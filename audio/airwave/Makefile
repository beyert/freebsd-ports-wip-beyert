# Created by: Timothy Beyer <beyert@cs.ucr.edu>

PORTNAME=	airwave
PORTVERSION=	20200715
CATEGORIES=	audio

MAINTAINER=	beyert@cs.ucr.edu
COMMENT=	Wine based bridge to use Windows 32/64-bit VST 2.4 plugins

LICENSE=	MIT
LICENSE_FILE=	${WRKSRC}/LICENSE

ONLY_FOR_ARCHS=	amd64 i386
IGNORE_i386=	vst3sdk fails to build

BUILD_DEPENDS=	${LOCALBASE}/lib/libwine.so:emulators/wine
LIB_DEPENDS=	libwine.so:emulators/wine
RUN_DEPENDS=	${LOCALBASE}/lib/wine/xaudio2_0.dll.so:emulators/wine

USES=	compiler:c++11-lib cmake qt:5

CONFLICTS_INSTALL=	airwave-wine-devel

.if defined(VSTSDK_INCLUDE_DIR)
CMAKE_ARGS+=	-DVSTSDK_INCLUDE_DIR=${VSTSDK_INCLUDE_DIR}
# redistribution is restricted of VST2 source headers in mandatory
# VSTSDK_INCLUDE_DIR, but these are not distfiles; while those specific
# headers cannot be redistributed, binary only distribution of aggregate
# binaries is possible (such a combination is not FOSS, however)
RESTRICTED=	yes
.else
IGNORE+=	need to obtain VST SDK and set variable VSTSDK_INCLUDE_DIR=[directory_containing_aeffect_header]; in poudriere, this path must be visible to the jail (typically in /distfiles or /wrkdirs paths)
.endif

.include <bsd.port.options.mk>

.if ${ARCH} == "amd64"
CMAKE_ARGS+=	-DVSTSDK_PATH=${LOCALBASE}/include/vst3sdk
.else
.if defined(VST3SDK_INCLUDE_DIR)
CMAKE_ARGS+=	-DVSTSDK_PATH=${VST3SDK_INCLUDE_DIR}
.else
IGNORE+=	need to extract ${LOCALBASE}/include/vst3sdk from an amd64 system and set VST3SDK_INCLUDE_DIR=[amd64_vst3sdk_include_path]
.endif
.endif

.if ${ARCH} == "amd64"
CMAKE_ARGS+=	-DDISABLE_32BIT=yes -DPLATFORM_64BIT=yes
PLIST_SUB+=	WINE32="@comment " WINE64=""
VERSION=	64
.else
CMAKE_ARGS+=	-DDISABLE_64BIT=yes -DPLATFORM_32BIT=yes
PLIST_SUB+=	WINE32="" WINE64="@comment "
VERSION=	32
.endif

USE_QT=	qmake_build buildtools_build core widgets gui network

USE_XORG=	x11

USE_GITHUB=	yes
GH_ACCOUNT=	psycha0s
GH_PROJECT=	${PORTNAME}
GH_TAGNAME=	e44976c

.if ${ARCH} == "amd64"
BUILD_DEPENDS+=	${LOCALBASE}/include/vst3sdk/vstbus.h:audio/vst3sdk
.elif ${ARCH} == "i386"
BUILD_DEPENDS+=	${LOCALBASE}/include/vst3sdk/vstbus.h:audio/vst3sdk-i386
.endif

post-patch:
	@${REINPLACE_CMD} -e 's|-Wall|-I/usr/src/sys/compat -Wall|' \
		-e 's|$${PROJECT_NAME}-plugin|$${PROJECT_NAME}-plugin${VERSION}|g' \
		${WRKSRC}/CMakeLists.txt
#	@${REINPLACE_CMD} -e 's|$${PLUGIN_BASENAME}|$${PLUGIN_BASENAME}${VERSION}|g' \
#		-e 's|DESTINATION bin|DESTINATION lib/${PORTNAME}|' \
#		${WRKSRC}/src/plugin/CMakeLists.txt
	@${REINPLACE_CMD} -e 's|DESTINATION bin|DESTINATION lib/${PORTNAME}|' \
		${WRKSRC}/src/plugin/CMakeLists.txt
	@${REINPLACE_CMD} \
		-e 's|TARGET_NAME $${PROJECT_NAME}-manager|TARGET_NAME $${PROJECT_NAME}-manager${VERSION}|g' \
		-e 's|DESTINATION bin|DESTINATION lib/${PORTNAME}|' \
		${WRKSRC}/src/manager/CMakeLists.txt
	@${REINPLACE_CMD} 's|/bin|/lib/${PORTNAME}|g' \
		${WRKSRC}/src/common/storage.cpp
.if ${ARCH} == "amd64"
	@${REINPLACE_CMD} 's|"wine"|"wine${VERSION}"|g' \
		${WRKSRC}/src/common/storage.cpp
.endif
# WINE_PREFIX_NAME is similar to WINEPREFIX, but without the path,
# the tilde, or the path separator of the home directory included;
# the default is .wine on i386, and .wine-wow64 on amd64
.if defined(WINE_PREFIX_NAME)
	@${REINPLACE_CMD} 's|"/.wine"|"/${WINE_PREFIX_NAME}"|' \
		${WRKSRC}/src/common/storage.cpp
.else
.if ${ARCH} == "amd64"
	@${REINPLACE_CMD} 's|"/.wine"|"/.wine-wow64"|' \
		${WRKSRC}/src/common/storage.cpp
.endif
.endif
	@${CP} -p ${WRKSRC}/src/manager/${PORTNAME}-manager.desktop.in \
		${WRKSRC}/src/manager/${PORTNAME}-manager${VERSION}.desktop.in
	@${CP} -p ${WRKSRC}/src/manager/resources/${PORTNAME}-manager.png \
		${WRKSRC}/src/manager/resources/${PORTNAME}-manager${VERSION}.png

post-install:
#	@${MKDIR} ${STAGEDIR}${LOCALBASE}/lib/airwave
.if ${ARCH} == "amd64"
	@cd ${STAGEDIR}${LOCALBASE}/lib && \
		${LN} -s airwave/airwave-plugin64.so libairwave-plugin64.so && \
		${LN} -s airwave/airwave-host-64.exe.so libairwave-host-64.exe.so
	@cd ${STAGEDIR}${LOCALBASE}/bin && \
		${LN} -s ../lib/airwave/airwave-host-64.exe airwave-host-64.exe && \
		${LN} -s ../lib/airwave/airwave-manager64 airwave-manager64
.else
	@cd ${STAGEDIR}${LOCALBASE}/lib && \
		${LN} -s airwave/airwave-plugin32.so libairwave-plugin32.so && \
		${LN} -s airwave/airwave-host-64.exe.so libairwave-host-32.exe.so
	@cd ${STAGEDIR}${LOCALBASE}/bin && \
		${LN} -s ../lib/airwave/airwave-host-32.exe airwave-host-32.exe && \
		${LN} -s ../lib/airwave/airwave-manager32 airwave-manager32
.endif

.include <bsd.port.mk>
