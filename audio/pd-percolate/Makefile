# Created by: Timothy Beyer <beyert@cs.ucr.edu>

PORTNAME=	percolate
PORTVERSION=	20200109
CATEGORIES=	audio
PKGNAMEPREFIX=	pd-

MAINTAINER=	beyert@cs.ucr.edu
COMMENT=	Variety of synthesis and signal processing algorithms for PD

LICENSE=	PERCOLATE
LICENSE_NAME=	Columbia PeRColate non-commercial license (MAX version)
LICENSE_FILE=	${WRKSRC}/README.md
LICENSE_PERMS=	dist-mirror pkg-mirror auto-accept

BUILD_DEPENDS=	pd:audio/pd
RUN_DEPENDS=	pd:audio/pd

USES=	dos2unix gmake

DOS2UNIX_FILES=	${BUILD_WRKSRC}/${MAKEFILE}

USE_GITHUB=	yes
GH_TUPLE=	megrimm:${PKGNAMEPREFIX}${PORTNAME}:4313e8c

BUILD_WRKSRC=	${WRKSRC}/PeRColate_source
INSTALL_WRKSRC=	${BUILD_WRKSRC}
MAKEFILE=	makefile
ALL_TARGET=	pd_freebsd

OPTIONS_DEFINE=	DOCS

.include <bsd.port.options.mk>

post-patch:
.if defined(PREFIX)
	@${REINPLACE_CMD} -e 's|/usr/local/include|${LOCALBASE}/include|g' \
		-e 's|prefix = /usr/local|prefix = ${PREFIX}|' \
		${BUILD_WRKSRC}/${MAKEFILE}
.endif

do-install:
	@${MKDIR} ${STAGEDIR}${PREFIX}/lib/pd-externals/${PORTNAME}
	@${FIND} ${WRKSRC}/PeRColate_help -name "*.pd" -exec ${INSTALL_DATA} {} \
		${STAGEDIR}${PREFIX}/lib/pd-externals/${PORTNAME} \;
	@${FIND} ${BUILD_WRKSRC} -name "*.pd_freebsd" -exec ${INSTALL_PROGRAM} {} \
		${STAGEDIR}${PREFIX}/lib/pd-externals/${PORTNAME} \;
	@${FIND} ${STAGEDIR}${PREFIX}/lib/pd/pd-externals/${PORTNAME} \
		-name "*.pd_freebsd" | ${XARGS} ${STRIP_CMD} ${STRIP}
.for i in README.md
	${INSTALL_DATA} ${WRKSRC}/${i} \
		${STAGEDIR}${PREFIX}/lib/pd-externals/${PORTNAME}
.endfor
.if ${PORT_OPTIONS:MDOCS}
	@${MKDIR} ${STAGEDIR}${DOCSDIR}
.for i in PeRColate_manual.pdf README.md
	${INSTALL_DATA} ${WRKSRC}/${i} ${STAGEDIR}${DOCSDIR}
.endfor
.endif

.include <bsd.port.mk>
