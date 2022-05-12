# Created by: Timothy Beyer <beyert@cs.ucr.edu>

PORTNAME=	libretro-reicast
PORTVERSION=	0.20201231
CATEGORIES=	emulators games

MAINTAINER=	beyert@cs.ucr.edu
COMMENT=	Standalone port of reicast to libretro

LICENSE=	BSD3CLAUSE LGPL21 GPLv2
LICENSE_COMB=	multi
LICENSE_FILE=	${WRKSRC}/LICENSE

LIB_DEPENDS=	libcurl.so:ftp/curl \
	libasound.so:audio/alsa-lib \
	libao.so:audio/libao \
	libevdev.so:devel/libevdev \
	libpulse.so:audio/pulseaudio \
	libudev.so:devel/libudev-devd

USES=		compiler cmake gl xorg
USE_GCC=	yes

USE_LDCONFIG=	yes
CMAKE_ARGS=	-DLIBRETRO_CORE=ON \
	-DOPENGL_EGL_INCLUDE_DIR:PATH=${LOCALBASE}/include/EGL \
	-DOPENGL_GLX_INCLUDE_DIR:PATH=${LOCALBASE}/include/GL \
	-DOPENGL_INCLUDE_DIR:PATH=${LOCALBASE}/include/GL \
	-DOPENGL_opengl_LIBRARY:PATH=${LOCALBASE}/lib/libGL.so

CXXFLAGS+=	-Wno-c++11-extensions
USE_GITHUB=	yes
GH_ACCOUNT=	reicast
GH_PROJECT=	reicast-emulator
GH_TAGNAME=	0bd6ea3

USE_GL=	gl egl gbm

PLIST_FILES=	lib/libretro/reicast_libretro.so

do-install:
	${MKDIR} ${STAGEDIR}/${PREFIX}/lib/libretro;
	${INSTALL_LIB} ${WRKDIR}/.build/libreicast.so \
		${STAGEDIR}/${PREFIX}/lib/libretro/reicast_libretro.so;

.include <bsd.port.mk>
