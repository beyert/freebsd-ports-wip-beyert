# Created by: Timothy Beyer <beyert@cs.ucr.edu>

PORTNAME=	jpc
PORTVERSION=	20180311
CATEGORIES=	audio
PKGNAMEPREFIX=	pd-

MAINTAINER=	beyert@cs.ucr.edu
COMMENT=	JPC externals for PureData

LICENSE=	BSL MIT LGPL20+ GPLv2 GPLv2+
LICENSE_COMB=	multi
LICENSE_FILE_BSL=	${WRKSRC}/LICENSE.md
LICENSE_FILE_MIT=	${WRKSRC}/README.md
LICENSE_FILE_LGPL20=	${WRKSRC}/README.md
LICENSE_FILE_GPLv2=	${WRKSRC}/README.md
LICENSE_FILE_GPLv2+ =	${WRKSRC}/README.md

BUILD_DEPENDS=	pd:audio/pd
# needed for robot~
LIB_DEPENDS=	libfftw3f.so:math/fftw3-float
RUN_DEPENDS=	pd:audio/pd

USES=	cmake pkgconfig
USE_GITHUB=	yes
GH_TUPLE=	jpcima:${PKGNAMEPREFIX}externals:9fe8bba \
	Microsoft:GSL:64a7dae:GSL/thirdparty/GSL

CMAKE_BUILD_TYPE=	Release
CMAKE_ARGS=	-DPD_INCLUDE_BASEDIR="${LOCALBASE}/include"

OPTIONS_DEFINE=	DOCS

.include <bsd.port.options.mk>

do-install:
	@${MKDIR} ${STAGEDIR}${PREFIX}/lib/pd-externals/${PORTNAME}
	@${FIND} ${WRKSRC} -name "*.pd" -exec ${INSTALL_DATA} {} \
		${STAGEDIR}${PREFIX}/lib/pd-externals/${PORTNAME} \;
	@${FIND} ${WRKSRC} -name "*.pd_freebsd" -exec ${INSTALL_PROGRAM} {} \
		${STAGEDIR}${PREFIX}/lib/pd-externals/${PORTNAME} \;
	@${FIND} ${STAGEDIR}${PREFIX}/lib/pd/pd-externals/${PORTNAME} \
		-name "*.pd_freebsd" | ${XARGS} ${STRIP_CMD} ${STRIP}
.for i in LICENSE.md README.md
	${INSTALL_DATA} ${WRKSRC}/${i} \
		${STAGEDIR}${PREFIX}/lib/pd-externals/${PORTNAME}
.endfor
.if ${PORT_OPTIONS:MDOCS}
	@${MKDIR} ${STAGEDIR}${DOCSDIR}
.for i in LICENSE.md README.md
	${INSTALL_DATA} ${WRKSRC}/${i} ${STAGEDIR}${DOCSDIR}
.endfor
.endif

.include <bsd.port.mk>
