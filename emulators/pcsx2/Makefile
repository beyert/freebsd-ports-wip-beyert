# Created by: Timothy Beyer <beyert@cs.ucr.edu>
# $FreeBSD$

PORTNAME=	pcsx2
PORTVERSION=	1.2.1
CATEGORIES=	emulators
MASTER_SITES=	http://www.emuparadise.me/emulators/files/
DISTNAME=	${PORTNAME}-${PORTVERSION}-r5875-sources
EXTRACT_SUFX=	.7z

MAINTAINER=	beyert@cs.ucr.edu
COMMENT=	PlayStation 2 (PS2) emulator

LICENSE=	GPLv3
LICENSE_FILE=	${WRKSRC}/COPYING.GPLv3

BUILD_DEPENDS=	${LOCALBASE}/bin/svn:${PORTSDIR}/devel/subversion \
	${LOCALBASE}/include/google/sparsehash/sparsehashtable.h:${PORTSDIR}/devel/google-sparsehash
LIB_DEPENDS=	libcdio.so:${PORTSDIR}/sysutils/libcdio \
	portaudio2/libportaudio.so:${PORTSDIR}/audio/portaudio2 \
	libSoundTouch.so:${PORTSDIR}/audio/soundtouch
EXTRACT_DEPENDS=	7z:${PORTSDIR}/archivers/p7zip

# will make a version that depends on 32-bit libraries later...
ONLY_FOR_ARCHS=	i386 amd64
#ONLY_FOR_ARCHS=	i386

EXTRACT_CMD=	${LOCALBASE}/bin/7z
EXTRACT_BEFORE_ARGS=	x -o${WRKSRC}
EXTRACT_AFTER_ARGS=
CPPFLAGS+=	-I${LOCALBASE}/include -I/usr/include
LDFLAGS+=	-L${LOCALBASE}/lib -I/usr/lib
USE_GCC=	4.8
USE_LDCONFIG=	yes

HAVE_GTK2=	true
USE_GNOME+=	gtk20 glib20
USE_XORG=	ice x11 xv xext xxf86vm xtst xrandr xi
USE_SDL=	sdl
USE_GL=	gl glew glu

MAKE_JOBS_UNSAFE=	yes
USE_WX=	2.8
WX_COMPS=	wx contrib
WX_UNICODE=	yes
USES=	dos2unix cmake iconv gettext
DOS2UNIX_REGEX=	.*\.(c|h|cpp|hpp|txt|cmake)
CFLAGS+=	-L${LOCALBASE}/lib -L/usr/lib -I${LOCALBASE}/include -I/usr/include
CXXFLAGS+=	-L${LOCALBASE}/lib -L/usr/lib -I${LOCALBASE}/include -I/usr/include
CMAKE_C_FLAGS=	${CFLAGS}
CMAKE_CXX_FLAGS=	${CFLAGS}
CMAKE_ARGS+=	-DCMAKE_PREFIX_PATH="${LOCALBASE}"
CMAKE_ARGS+=	-DCMAKE_INSTALL_PREFIX="${LOCALBASE}"
CMAKE_ARGS+=	-DCMAKE_INCLUDE_PATH:STRING="${LOCALBASE}/include:/usr/include"
CMAKE_ARGS+=	-DCMAKE_LIBRARY_PATH="${LOCALBASE}/lib:/usr/lib"
CMAKE_ARGS+=	-DCMAKE_LIB_PATH:STRING="${LOCALBASE}/lib:/usr/lib"
CMAKE_ARGS+=	-DWX_CONFIG_PATH:FILEPATH="${WX_CONFIG}"
CMAKE_ARGS+=	-DPORTAUDIO_INCLUDE_DIR="${LOCALBASE}/include/portaudio2"

.include <bsd.port.mk>
