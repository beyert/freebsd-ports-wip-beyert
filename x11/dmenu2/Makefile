# Created by: Timothy Beyer <beyert@cs.ucr.edu
# $FreeBSD:$

PORTNAME=	dmenu2
PORTVERSION=	0.2
CATEGORIES=	x11
MASTER_SITES=	https://bitbucket.org/melek/dmenu2/downloads/

MAINTAINER=	beyert@cs.ucr.edu
COMMENT=	X11 menu application designed for the dwm window manager

LICENSE=	MIT
LICENSE_FILE=	${WRKSRC}/LICENSE

LIB_DEPENDS=	libfontconfig.so:x11-fonts/fontconfig

OPTIONS_DEFINE=	XINERAMA
OPTIONS_DEFAULT=	XINERAMA

USE_XORG=	x11 xft
MAKE_ARGS=	CC="${CC}" PREFIX="${PREFIX}" MANPREFIX="${MANPREFIX}/man" \
		X11INC="${LOCALBASE}/include" X11LIB="${LOCALBASE}/lib" \
		XFTINC="-I${LOCALBASE}/include/freetype2"

PLIST_FILES=	bin/dmenu2 bin/dmenu2_path bin/dmenu2_run bin/stest2 \
		man/man1/dmenu2.1.gz man/man1/stest2.1.gz

XINERAMA_USE=	XORG=xinerama
XINERAMA_MAKE_ARGS_OFF=	XINERAMAFLAGS= XINERAMALIBS=

post-patch:
	${REINPLACE_CMD} 's|dmenu dmenu_run stest|dmenu2 dmenu2_run stest2|g' \
		${WRKSRC}/Makefile
	${REINPLACE_CMD} 's|/bin/dmenu|/bin/dmenu2|g' ${WRKSRC}/Makefile
	${REINPLACE_CMD} 's|/bin/stest|/bin/stest2|g' ${WRKSRC}/Makefile
	${REINPLACE_CMD} 's|/man1/dmenu.1|/man1/dmenu2.1|g' ${WRKSRC}/Makefile
	${REINPLACE_CMD} 's|/man1/stest.1|/man1/stest2.1|g' ${WRKSRC}/Makefile

pre-install:
	mv ${WRKSRC}/dmenu ${WRKSRC}/dmenu2
	mv ${WRKSRC}/dmenu_run ${WRKSRC}/dmenu2_run
	mv ${WRKSRC}/stest ${WRKSRC}/stest2
	${CHMOD} +x ${WRKSRC}/dmenu2_path
	${CP} -pR ${WRKSRC}/dmenu2_path ${STAGEDIR}${PREFIX}/bin/dmenu2_path

post-install:
	${STRIP_CMD} ${STAGEDIR}${PREFIX}/bin/dmenu2 \
		${STAGEDIR}${PREFIX}/bin/stest2

.include <bsd.port.mk>
