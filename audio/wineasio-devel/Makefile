# Created by: Timothy Beyer <beyert@cs.ucr.edu>

PORTNAME=	wineasio
PORTVERSION=	20210302
CATEGORIES=	audio
PKGNAMESUFFIX=	-devel

MAINTAINER=	beyert@cs.ucr.edu
COMMENT=	ASIO to JACK driver for WINE development version

LICENSE=	LGPL21 GPLv2
LICENSE_COMB=	multi
LICENSE_FILE_LGPL21=	${WRKSRC}/COPYING.LIB
LICENSE_FILE_GPLv2=	${WRKSRC}/COPYING.GUI

ONLY_FOR_ARCHS=	amd64 i386

BUILD_DEPENDS=	${LOCALBASE}/include/wine/windows/winbase.h:emulators/wine-devel
##LIB_DEPENDS=	wine/${WINEARCH}-unix/libwine.so.1.0:emulators/wine-devel
#LIB_DEPENDS=	${LOCABASE}/lib/wine/${WINEARCH}-unix/xaudio2_0.dll.so:emulators/wine-devel
LIB_DEPENDS=	libjack.so:audio/jack
RUN_DEPENDS=	${LOCALBASE}/bin/wine:emulators/wine-devel \
	${LOCALBASE}/bin/jackd:audio/jack

USES=	compiler:c++11-lib gmake pkgconfig

CONFLICTS_INSTALL=	wineasio

.include <bsd.port.options.mk>

.if ${ARCH} == "amd64"
WINEARCH=	x86_64
.else
WINEARCH=	${ARCH}
.endif
PLIST_SUB+=	WINEARCH=${WINEARCH}

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
		-e 's|/usr/lib/$$(ARCH)-linux-gnu/wine|${PREFIX}/lib/wine/${WINEARCH}-unix|' \
		${WRKSRC}/Makefile.mk
#		-e 's|wineasio_dll_DLL_PATH =|wineasio_dll_DLL_PATH = ${PREFIX}/lib/wine/${WINEARCH}-windows|'
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
	${MKDIR} ${STAGEDIR}${PREFIX}/lib/wine/${WINEARCH}-unix
	${MKDIR} ${STAGEDIR}${PREFIX}/lib/wine/${WINEARCH}-windows
	${INSTALL}  ${WRKSRC}/build${ALL_TARGET}/wineasio.dll.so \
		${STAGEDIR}${PREFIX}/lib/wine/${WINEARCH}-unix/
	${INSTALL}  ${WRKSRC}/build${ALL_TARGET}/wineasio.dll \
		${STAGEDIR}${PREFIX}/lib/wine/${WINEARCH}-windows/

#CFLAGS+=	-I${LOCALBASE}/include/wine -I${LOCALBASE}/include/wine/windows \
#	-I/home/beyert/.i386-wine-pkg/usr/local/include/wine \
#	-I/home/beyert/.i386-wine-pkg/usr/local/include/wine/windows \
#	-D__WINESRC__

#LDFLAGS+=	-L${LOCALBASE}/lib/wine/x86_64-unix -L${LOCALBASE}/lib/wine/x86_64-windows
#MAKE_ARGS+=	PREFIX=${PREFIX}
#wineasio_dll_LDFLAGS+="-L${LOCALBASE}/lib/wine/x86_64-windows"
##	-L${LOCALBASE}/lib/wine/x86_64-unix
##	-L/home/beyert/.i386-wine-pkg/usr/local/lib32/wine/i386-windows
##	-L/home/beyert/.i386-wine-pkg/usr/local/lib32/wine/i386-unix

.include <bsd.port.mk>
