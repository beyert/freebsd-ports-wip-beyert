# Created by Timothy Beyer <beyert@cs.ucr.edu>

PORTNAME=	libretro-kronos
PORTVERSION=	0.20210601
# post 2.1.5_release, pre 2.2.0_official_release
CATEGORIES=	emulators games

MAINTAINER=	beyert@cs.ucr.edu
COMMENT=	Sega Saturn and ST-V emulator forked from uoYabause for libretro

LICENSE=	GPLv2
LICENSE_FILE=	${WRKSRC}/yabause/COPYING

LIB_DEPENDS=	libGL.so:graphics/mesa-libs

# standalone uses solely cmake, whereas retroarch core uses cmake and gmake
USES=	compiler:c++11-lang cmake gmake gl sdl qt:5 pkgconfig
USE_LDCONFIG=	yes

USE_SDL=	sdl2

USE_GITHUB=	yes
GH_ACCOUNT=	FCare
GH_PROJECT=	Kronos
GH_TAGNAME=	a39f95a

USE_GL=	gl glew glu

USE_QT=	qmake_build buildtools_build core opengl

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

.if ${CHOSEN_COMPILER_TYPE} == clang && ${OPSYS} == FreeBSD
# clang13 runs out of memory
LLVM_VER=	12
BUILD_DEPENDS+=	clang++${LLVM_VER}:devel/llvm${LLVM_VER}
CC=	${LOCALBASE}/bin/clang${LLVM_VER}
CXX=	${LOCALBASE}/bin/clang++${LLVM_VER}
.endif

do-build:
	cd ${WRKSRC}/yabause/src/libretro && ${DO_MAKE_BUILD}

post-patch:
.if ${ARCH} != "amd64"
	@${REINPLACE_CMD} -e "s/HAVE_SSE = 1/HAVE_SSE = 0/" \
		${WRKSRC}/yabause/src/libretro/Makefile
.endif

do-install:
	@${MKDIR} ${STAGEDIR}/${PREFIX}/lib/libretro;
	${INSTALL_LIB} ${WRKSRC}/yabause/src/libretro/kronos_libretro.so \
		${STAGEDIR}/${PREFIX}/lib/libretro;

.include <bsd.port.post.mk>
