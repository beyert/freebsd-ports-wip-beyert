# Created by: Timothy Beyer <beyert@cs.ucr.edu>
# $FreeBSD$

PORTNAME=	dmenu2
PORTVERSION=	0.0.20150210
CATEGORIES=	x11
MASTER_SITES=	https://bitbucket.org/melek/dmenu2/downloads/

MAINTAINER=	beyert@cs.ucr.edu
COMMENT=	dynamic menu extended

LICENSE=	MIT
LICENSE_FILE=	${WRKSRC}/LICENSE

LIB_DEPENDS=	libfreetype.so:print/freetype2 \
	libfontconfig.so:x11-fonts/fontconfig

USE_GITHUB=	yes
GH_TUPLE=	mrshankly:dmenu2:a4eb44b

OPTIONS_DEFINE=	XINERAMA
OPTIONS_DEFAULT=	XINERAMA

USE_XORG=	x11 xft
MAKE_ARGS=	CC="${CC}" PREFIX="${PREFIX}" MANPREFIX="${MANPREFIX}/man" \
		X11INC="${LOCALBASE}/include" X11LIB="${LOCALBASE}/lib" VERSION="0.2"

PLIST_FILES=	bin/dmenu2 bin/dmenu2_path bin/dmenu2_run bin/stest2 \
		man/man1/dmenu2.1.gz man/man1/stest2.1.gz

XINERAMA_USE=	XORG=xinerama
XINERAMA_MAKE_ARGS_OFF=	XINERAMAFLAGS= XINERAMALIBS=

post-patch:
	${REINPLACE_CMD} 's|/usr/include|${PREFIX}/include|g' \
		${WRKSRC}/Makefile
	${REINPLACE_CMD} 's|dmenu.1 stest.1|dmenu2.1 stest2.1|g' ${WRKSRC}/Makefile
	${MV} ${WRKSRC}/dmenu.1 ${WRKSRC}/dmenu2.1
	${MV} ${WRKSRC}/stest.1 ${WRKSRC}/stest2.1

pre-install:
	${CHMOD} +x ${WRKSRC}/dmenu2_path
	${CP} -pR ${WRKSRC}/dmenu2_path ${STAGEDIR}${PREFIX}/bin/dmenu2_path

post-install:
	${MV} ${STAGEDIR}${PREFIX}/bin/dmenu ${STAGEDIR}${PREFIX}/bin/dmenu2
	${MV} ${STAGEDIR}${PREFIX}/bin/dmenu_run ${STAGEDIR}${PREFIX}/bin/dmenu2_run
	${MV} ${STAGEDIR}${PREFIX}/bin/stest ${STAGEDIR}${PREFIX}/bin/stest2
	${STRIP_CMD} ${STAGEDIR}${PREFIX}/bin/dmenu2 \
		${STAGEDIR}${PREFIX}/bin/stest2

.include <bsd.port.mk>
