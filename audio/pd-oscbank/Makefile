# Created by: Timothy Beyer <beyert@cs.ucr.edu>

PORTNAME=	pd-oscbank
DISTVERSION=	20120228
CATEGORIES=	audio

MAINTAINER=	beyert@cs.ucr.edu
COMMENT=	Pd oscbank~ external for additive synthesis

LICENSE=	BSD3CLAUSE
LICENSE_FILE_BSD3CLAUSE=	${WRKSRC}/LICENSE

BUILD_DEPENDS=	pd:audio/pd
RUN_DEPENDS=	pd:audio/pd

OPTIONS_DEFINE=	DOCS

.include <bsd.port.options.mk>

USE_GITHUB=	yes
GH_TUPLE=	richardeakin:${PORTNAME}:a9f2fe3

BUILD_WRKSRC=	${WRKSRC}/src
INSTALL_WRKSRC=	${WRKSRC}/src
ALL_TARGET=	pd_freebsd
MAKE_ENV+=	STRIP_CMD="${STRIP_CMD}" RM="${RM}" COMPILER="${CC}" \
	LOCALBASE="${LOCALBASE}"

do-install:
	@${MKDIR} ${STAGEDIR}${PREFIX}/lib/pd-externals/oscbank~
	@${FIND} ${WRKSRC}/src -name "*.pd" -exec ${INSTALL_DATA} {} \
		${STAGEDIR}${PREFIX}/lib/pd-externals/oscbank~ \;
	@${FIND} ${WRKSRC}/src -name "*.pd_freebsd" -exec ${INSTALL_PROGRAM} {} \
		${STAGEDIR}${PREFIX}/lib/pd-externals/oscbank~ \;
.if ${PORT_OPTIONS:MDOCS}
	@${MKDIR} ${STAGEDIR}${DOCSDIR}
	@${CP} ${WRKSRC}/README ${WRKSRC}/LICENSE ${STAGEDIR}${DOCSDIR}
.endif

.include <bsd.port.mk>
