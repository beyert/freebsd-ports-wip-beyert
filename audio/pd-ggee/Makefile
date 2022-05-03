# Created by: Timothy Beyer <beyert@cs.ucr.edu>

PORTNAME=	ggee
PORTVERSION=	0.28
CATEGORIES=	audio
PKGNAMEPREFIX=	pd-

MAINTAINER=	beyert@cs.ucr.edu
COMMENT=	Library by Guenter Geiger of PD externals, without STK

LICENSE=	TclTk
LICENSE_GROUPS=	COPYFREE OSI
LICENSE_NAME=	TCL/Tk License
LICENSE_FILE=	${WRKSRC}/LICENSE.txt
LICENSE_PERMS=	${_LICENSE_PERMS_DEFAULT}

BUILD_DEPENDS=	pd:audio/pd
RUN_DEPENDS=	pd:audio/pd

USES=	gmake

USE_GITHUB=	yes
GH_TUPLE=	pd-externals:${PORTNAME}:55f75d2

MAKE_ARGS+=	PDINCLUDEDIR=${LOCALBASE}/include/pd \
	pkglibdir=${PREFIX}/lib/pd-externals stripflags="${STRIP}"

post-patch:
.if defined(LOCALBASE) || defined(PREFIX)
	@${REINPLACE_CMD} -e 's|/usr/local/include|${LOCALBASE}/include|g' \
		-e 's|prefix = /usr/local|prefix = ${PREFIX}|' \
		${WRKSRC}/Makefile.pdlibbuilder
.endif

#post-build:
#	@${FIND} ${STAGEDIR}${PREFIX}/lib/pd-externals/${PORTNAME} \
#		-name "*.pd_freebsd" | ${XARGS} ${STRIP_CMD} ${STRIP}

.include <bsd.port.mk>
