# Created by: Timothy Beyer <beyert@cs.ucr.edu>

PORTNAME=	pd-ggee
PORTVERSION=	0.28
CATEGORIES=	audio

MAINTAINER=	beyert@cs.ucr.edu
COMMENT=	Library by Guenter Geiger of PD externals

LICENSE=	TclTk
LICENSE_GROUPS=	COPYFREE OSI
LICENSE_NAME=	TCL/Tk License
LICENSE_FILE=	${WRKSRC}/LICENSE.txt
LICENSE_PERMS=	${_LICENSE_PERMS_DEFAULT}

BUILD_DEPENDS=	pd:audio/pd
RUN_DEPENDS=	pd:audio/pd

USES=	gmake

USE_GITHUB=	yes
GH_TUPLE=	pd-externals:ggee:55f75d2 \
	thestk:stk:893ff3d:thestk/experimental/stk

MAKE_ARGS+=	PDINCLUDEDIR=${LOCALBASE}/include/pd \
	pkglibdir=${PREFIX}/lib/pd-externals stripflags="${STRIP}"

post-build:
	cd ${WRKSRC}/experimental && \
	${MAKE} RM="rm" CC="${CC}" STRIP="${STRIP_CMD}" PREFIX="${PREFIX}" \
		LOCALBASE="${LOCALBASE}" \
		-f Makefile.freebsd stk.pd_freebsd

post-patch:
.if defined(LOCALBASE) || defined(PREFIX)
	@${REINPLACE_CMD} -e 's|/usr/local/include|${LOCALBASE}/include|g' \
		-e 's|prefix = /usr/local|prefix = ${PREFIX}|' \
		${WRKSRC}/Makefile.pdlibbuilder
.endif

.include <bsd.port.mk>
