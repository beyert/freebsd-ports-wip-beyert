# Created by: Timothy Beyer <beyert@cs.ucr.edu>

PORTNAME=	Mi4Pd
PORTVERSION=	20210910
CATEGORIES=	audio
PKGNAMEPREFIX=	pd-

MAINTAINER=	beyert@cs.ucr.edu
COMMENT=	Technobear Mutable Instruments for Pure Data

LICENSE=	MIT
LICENSE_FILE=	${WRKSRC}/README.md

BUILD_DEPENDS=	pd:audio/pd
RUN_DEPENDS=	pd:audio/pd

USES=	cmake

CFLAGS+=	-fPIC

USE_GITHUB=	yes
GH_TUPLE=	TheTechnobear:${PORTNAME}:f4aa6e9

INSTALL_TARGET=	all

do-install:
	@${MKDIR} ${STAGEDIR}${PREFIX}/lib/pd-externals/Mi4Pd
.for m in brds clds clds_reverb grids lmnts rngs rngs_chorus \
	rngs_ensemble rngs_reverb wrps
.if "${m}" == "grids"
	${INSTALL_LIB} ${BUILD_WRKSRC}/release/lib/${m}.pd_freebsd \
		${STAGEDIR}${PREFIX}/lib/pd-externals/Mi4Pd/
.else
	${INSTALL_LIB} ${BUILD_WRKSRC}/release/lib/${m}~.pd_freebsd \
		${STAGEDIR}${PREFIX}/lib/pd-externals/Mi4Pd/
.endif
.endfor
.for m in brds clds clds_reverb grds lmnts rngs_reverb wrps
.if "${m}" == "grds"
	${INSTALL_DATA} ${WRKSRC}/${m}/grids-help.pd \
		${STAGEDIR}${PREFIX}/lib/pd-externals/Mi4Pd/
.else
	${INSTALL_DATA} ${WRKSRC}/${m}/${m}~-help.pd \
		${STAGEDIR}${PREFIX}/lib/pd-externals/Mi4Pd/
.endif
.endfor
	${INSTALL_DATA} ${WRKSRC}/README.md \
		${STAGEDIR}${PREFIX}/lib/pd-externals/Mi4Pd/

.include <bsd.port.mk>
