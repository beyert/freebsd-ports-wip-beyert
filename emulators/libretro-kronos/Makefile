# $FreeBSD$

PORTNAME=	libretro-kronos
PORTVERSION=	0.20210617
CATEGORIES=	emulators games

MAINTAINER=	beyert@cs.ucr.edu
COMMENT=	Sega Saturn and ST-V emulator forked from uoYabause for libretro

LICENSE=	GPLv2
LICENSE_FILE=	${WRKSRC}/yabause/COPYING

LIB_DEPENDS=	libGL.so.1:graphics/mesa-libs

USES=		compiler:c++11-lib cmake gmake gl
USE_LDCONFIG=	yes

USE_GITHUB=	yes
GH_ACCOUNT=	FCare
GH_PROJECT=	Kronos
GH_TAGNAME=	a39f95a

USE_GL=	gl glew glu

CFLAGS+=	-I${LOCALBASE}/include
CXXFLAGS+=	-I${LOCALBASE}/include
LDFLAGS+=	-L${LOCALBASE}/lib

PLIST_FILES=	lib/libretro/kronos_libretro.so

cmake_ARGS=	noninja
CMAKE_SOURCE_PATH=	${WRKSRC}/yabause

MAKE_ARGS=	USE_RTHREADS=1

pre-build:
	cd ${CMAKE_SOURCE_PATH} && ${CMAKE_BIN} .
	cd ${WRKSRC}/yabause/src && ${MAKE} m68kmake

.include <bsd.port.pre.mk>

do-build:
	cd ${WRKSRC}/yabause/src/libretro && ${DO_MAKE_BUILD}

post-patch:
.if ${ARCH} != "amd64"
	@${REINPLACE_CMD} -e "s/HAVE_SSE = 1/HAVE_SSE = 0/" ${WRKSRC}/yabause/src/libretro/Makefile
.endif

do-install:
	${MKDIR} ${STAGEDIR}/${PREFIX}/lib/libretro;
	${INSTALL_LIB} ${WRKSRC}/yabause/src/libretro/kronos_libretro.so ${STAGEDIR}/${PREFIX}/lib/libretro;

.include <bsd.port.post.mk>
