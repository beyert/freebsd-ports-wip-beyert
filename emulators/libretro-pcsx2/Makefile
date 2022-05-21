# Created by: Timothy Beyer <beyert@cs.ucr.edu>

PORTNAME=	libretro-pcsx2
PORTVERSION=	0.20201030
PORTREVISION=	1
CATEGORIES=	emulators games

MAINTAINER=	beyert@cs.ucr.edu
COMMENT=	Standalone port of pcsx2 to libretro

LICENSE=	GPLv3
LICENSE_FILE=	${WRKSRC}/COPYING.GPLv3

# fix on i386 later
BROKEN_i386=	fails to link: class member cannot be redeclared
ONLY_FOR_ARCHS=	amd64 i386

LIB_DEPENDS=	libcdio.so:sysutils/libcdio \
	libharfbuzz.so:print/harfbuzz \
	libportaudio.so:audio/portaudio \
	libpng16.so:graphics/png \
	libSoundTouch.so:audio/soundtouch

USES=	compiler:c++11-lib cmake

.include <bsd.port.pre.mk>

CPPFLAGS+=	-I${LOCALBASE}/include/wx-3.0
USE_CXXSTD=	c++11
USE_LDCONFIG=	yes
CMAKE_CPP_FLAGS=	${CPPFLAGS}
CMAKE_PREFIX_PATH=	${LOCALBASE}/include/wx-3.0
CMAKE_C_FLAGS=	${CFLAGS}
CMAKE_CXX_FLAGS=	${CFLAGS}
CMAKE_ARGS+=	-DLIBRETRO=yes
CMAKE_ARGS+=	-DwxWidgets_INCLUDE_DIRS="${LOCALBASE}/include/wx-3.0"
CMAKE_ARGS+=	-Dgtk_INCLUDE_DIR="${LOCALBASE}/include/gtk-3.0"

# lib depends on devel/ccache
WITH_CCACHE_BUILD=	yes

HAVE_GTK3=	true
USE_WX=	3.0+
USE_GL=	gl glew glu
USE_GNOME=	glib20

MAKE_JOBS_UNSAFE=	yes

USE_GITHUB=	yes
GH_ACCOUNT=	libretro
GH_PROJECT=	pcsx2
GH_TAGNAME=	1251fa4

PLIST_FILES=	lib/libretro/pcsx2_libretro.so

post-patch:
	@${CP} files/3rdparty_wxwidgets3.0_src_unix_fswatcher__kqueue.cpp \
		${WRKSRC}/3rdparty/wxwidgets3.0/src/unix/fswatcher_kqueue.cpp
.if ${ARCH} == i386
	@${REINPLACE_CMD} 's|-D_FILE_OFFSET_BITS=64|-D_FILE_OFFSET_BITS=32|' \
		${WRKSRC}/3rdparty/wxwidgets3.0/UsewxWidgets.cmake
.endif

do-install:
	@${MKDIR} ${STAGEDIR}/${PREFIX}/lib/libretro;
	${INSTALL_LIB} ${WRKDIR}/.build/pcsx2/pcsx2_libretro.so \
		${STAGEDIR}/${PREFIX}/lib/libretro;

.include <bsd.port.post.mk>
