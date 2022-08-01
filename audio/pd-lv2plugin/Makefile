# Created by: Timothy Beyer <beyert@cs.ucr.edu>

PORTNAME=	lv2plugin
PORTVERSION=	0.3
CATEGORIES=	audio
MASTER_SITES=	https://bitbucket.org/agraef/pd-lv2plugin/downloads/
PKGNAMEPREFIX=	pd-
DISTNAME=	${PKGNAMEPREFIX}${PORTNAME}-${PORTVERSION}

MAINTAINER=	beyert@cs.ucr.edu
COMMENT=	Simple LV2 host so that you can run LV2 plugins inside Pd

LICENSE=	BSD3CLAUSE
LICENSE_FILE=	${WRKSRC}/COPYING

BUILD_DEPENDS=	${LOCALBASE}/include/m_pd.h:audio/pd \
		${LOCALBASE}/include/pure/runtime.h:lang/pure-restored \
		${LOCALBASE}/lib/pure/lilv.pure:audio/pure-lilv
RUN_DEPENDS=	${LOCALBASE}/include/m_pd.h:audio/pd \
		pure:lang/pure-restored \
		${LOCALBASE}/lib/pure/lilv.pure:audio/pure-lilv \
		${LOCALBASE}/lib/pd/extra/pure/lib/pd.pure:audio/pd-pure

USES=	gmake pkgconfig pure
USE_LDCONFIG=	yes

MAKE_ARGS+=	CC=${CC} purelib=${LOCALBASE}/lib/pure

post-patch:
.if defined(LOCALBASE) || defined(PREFIX)
	@${REINPLACE_CMD} -e 's|prefix = /usr/local|prefix = ${PREFIX}|' \
		${WRKSRC}/Makefile
.endif

post-install:
	@${STRIP_CMD} \
		${STAGEDIR}${PREFIX}/lib/pd-externals/lv2plugin~/lv2plugin~.pd_freebsd

.include <bsd.port.mk>
