# Created by: Timothy Beyer <beyert@cs.ucr.edu>

PORTNAME=	RTcmix
DISTVERSION=	g20220620
CATEGORIES=	audio
PKGNAMEPREFIX=	pd-

MAINTAINER=	beyert@cs.ucr.edu
COMMENT=	PD external encapsulating the RTcmix audio language

LICENSE=	MIT

BUILD_DEPENDS=	${LOCALBASE}/include/m_pd.h:audio/pd cmix:audio/rtcmix
RUN_DEPENDS=	pd:audio/pd cmix:audio/rtcmix

USES=	gmake

DISTINFO_FILE=	${.CURDIR}/../rtcmix/distinfo

PLIST_FILES=	lib/pd-externals/rtcmix~/README.md \
		lib/pd-externals/rtcmix~/rtcmix~-help.pd \
		lib/pd-externals/rtcmix~/rtcmix~-meta.pd \
		lib/pd-externals/rtcmix~/rtcmix~.pd_freebsd

HAS_CONFIGURE=	yes
#CONFIGURE_SCRIPT=	${WRKSRC}/configure
USE_GITHUB=	yes
# we must use the upstream rtcmix repository, not because it imported
# pd-rtcmix, but because it includes the coveted makefile.conf
#
#GH_TUPLE=	jwmatthys:${PKGNAMEPREFIX}${PORTNAME}:9a08c2a
GH_TUPLE=	${PORTNAME}:${PORTNAME}:1c9039f

BUILD_WRKSRC=	${WRKSRC}/src/pd
INSTALL_WRKSRC=	${BUILD_WRKSRC}

MAKE_ARGS+=	PDINCLUDEDIR="${LOCALBASE}/include/pd" \
		pkglibdir="${PREFIX}/lib/pd-externals" stripflags="${STRIP}"

post-patch:
.if defined(LOCALBASE) || defined(PREFIX)
	@${REINPLACE_CMD} -e 's|/usr/local/include|${LOCALBASE}/include|g' \
		-e 's|prefix = /usr/local|prefix = ${PREFIX}|' \
		${BUILD_WRKSRC}/pd-lib-builder/Makefile.pdlibbuilder
.endif

.include <bsd.port.mk>
