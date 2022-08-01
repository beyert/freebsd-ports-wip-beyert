# Created by: Timothy Beyer <beyert@cs.ucr.edu>

PORTNAME=	wineasio
PORTVERSION=	20210302
CATEGORIES=	audio

MAINTAINER=	beyert@cs.ucr.edu
COMMENT=	ASIO to JACK driver for ${WINE_PORT}

LICENSE=	LGPL21 GPLv2
LICENSE_COMB=	multi
LICENSE_FILE_LGPL21=	${WRKSRC}/COPYING.LIB
LICENSE_FILE_GPLv2=	${WRKSRC}/COPYING.GUI

ONLY_FOR_ARCHS=	amd64 i386

BUILD_DEPENDS=	\
		${LOCALBASE}/include/wine/windows/winbase.h:emulators/${WINE_PORT}
LIB_DEPENDS=	libjack.so:audio/jack
RUN_DEPENDS=	${LOCALBASE}/bin/wine:emulators/${WINE_PORT} \
		${LOCALBASE}/bin/jackd:audio/jack

FLAVORS=	wine wine_devel

USES=	compiler:c++11-lib gmake pkgconfig

wine_PKGNAMESUFFIX=	-wine
wine_devel_PKGNAMESUFFIX=	-wine_devel

.include <bsd.port.options.mk>

.if ${ARCH} == "amd64"
WINEARCH=	x86_64
.else
WINEARCH=	${ARCH}
.endif

WINE_PORT=	${FLAVOR:wine_%=wine-%}

.if ${FLAVOR:Mwine}
UNIX_SUFFIX=	wine
WINDOWS_SUFFIX=	wine/fakedlls
.elif ${FLAVOR:Mwine_devel}
UNIX_SUFFIX=	wine/${WINEARCH}-unix
WINDOWS_SUFFIX=	wine/${WINEARCH}-windows
.endif
PLIST_SUB+=	UNIX_SUFFIX=${UNIX_SUFFIX}
PLIST_SUB+=	WINDOWS_SUFFIX=${WINDOWS_SUFFIX}

USE_GCC=	yes

USE_GITHUB=	yes
GH_TUPLE=	wineasio:wineasio:0a97f2f \
		falkTX:rtaudio:e03448b:wineasio/rtaudio

.if ${ARCH} == i386
ALL_TARGET=	32
.else
ALL_TARGET=	64
.endif

post-patch:
	@${REINPLACE_CMD} -e 's|CC = gcc|CC = ${CC}|' \
		-e 's|= \/usr|= ${PREFIX}|' \
		-e 's|/usr/lib/$$(ARCH)-linux-gnu/wine|${PREFIX}/lib/${UNIX_SUFFIX}/|' \
		${WRKSRC}/Makefile.mk
#		-e 's|wineasio_dll_DLL_PATH =|wineasio_dll_DLL_PATH = ${PREFIX}/lib/${WINDOWS_SUFFIX}|'
	@${REINPLACE_CMD} -e 's/unsigned long/ULONG/g' \
		-e 's/long long int/LONGLONG/g' \
		-e 's/long int/LONG/g' \
		-e 's/long/LONG/g' \
		-e 's/(\*bufferSwitch)/(CALLBACK *bufferSwitch)/g' \
		-e 's/(\*sampleRateDidChange)/(CALLBACK *sampleRateDidChange)/g' \
		-e 's/(\*asioMessage)/(CALLBACK *asioMessage)/g' \
		-e 's/(\*bufferSwitchTimeInfo)/(CALLBACK *bufferSwitchTimeInfo)/g' \
	${WRKSRC}/rtaudio/include/asio.h

post-build:
# dll generation method used same as in arch-linux PKG-BUILD:
# https://aur.archlinux.org/cgit/aur.git/tree/PKGBUILD?h=wineasio-git
	cd ${WRKSRC}/build${ALL_TARGET} && winebuild -m${ALL_TARGET} \
		--dll --fake-module -E ../wineasio.dll.spec \
		asio.c.o main.c.o regsvr.c.o > wineasio.dll

do-install:
	${MKDIR} ${STAGEDIR}${PREFIX}/lib/${UNIX_SUFFIX}
	${MKDIR} ${STAGEDIR}${PREFIX}/lib/${WINDOWS_SUFFIX}
	${INSTALL}  ${WRKSRC}/build${ALL_TARGET}/wineasio.dll.so \
		${STAGEDIR}${PREFIX}/lib/${UNIX_SUFFIX}/
	${INSTALL}  ${WRKSRC}/build${ALL_TARGET}/wineasio.dll \
		${STAGEDIR}${PREFIX}/lib/${WINDOWS_SUFFIX}/

.include <bsd.port.mk>
