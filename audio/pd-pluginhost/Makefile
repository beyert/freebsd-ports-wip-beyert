# Created by: Timothy Beyer <beyert@cs.ucr.edu>

PORTNAME=	pluginhost
DISTVERSION=	g20150319
CATEGORIES=	audio
PKGNAMEPREFIX=	pd-

MAINTAINER=	beyert@cs.ucr.edu
COMMENT=	DSSI and LADSPA Plugin host for Pure Data

LICENSE=	GPLv2
LICENSE_FILE=	${BUILD_WRKSRC}/LICENSE.txt

BUILD_DEPENDS=	${LOCALBASE}/include/m_pd.h:audio/pd \
		${LOCALBASE}/include/dssi.h:audio/dssi \
		${LOCALBASE}/include/ladspa.h:audio/ladspa
RUN_DEPENDS=	${LOCALBASE}/include/m_pd.h:audio/pd \
		${LOCALBASE}/include/dssi.h:audio/dssi \
		${LOCALBASE}/include/ladspa.h:audio/ladspa

USES=	gmake

#CFLAGS+=	-I${LOCALBASE}/include -I/usr/include
#LDFLAGS+=	-L${LOCALBASE}/lib -lc

PLIST_FILES=	lib/pd-externals/pluginhost~/LICENSE.txt \
		lib/pd-externals/pluginhost~/README.txt \
		lib/pd-externals/pluginhost~/pluginhost~-help.pd \
		lib/pd-externals/pluginhost~/pluginhost~-meta.pd \
		lib/pd-externals/pluginhost~/pluginhost~.pd_freebsd

ALL_TARGET=	install

USE_GITHUB=	yes
GH_TUPLE=	BirminghamConservatoire:ix7:9b5ca96

BUILD_WRKSRC=	${WRKSRC}/${PORTNAME}~
INSTALL_WRKSRC=	${BUILD_WRKSRC}

#CFLAGS_i386=	-fPIC
#LDFLAGS_i386=	-Wl,-z,notext

MAKE_ARGS+=	PREFIX=${PREFIX} STAGEDIR=${STAGEDIR}
#		INSTALLDIR=${STAGEDIR}${PREFIX}/lib/pd-externals/pluginhost~

.include <bsd.port.mk>
