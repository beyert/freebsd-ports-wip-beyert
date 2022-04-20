# Created by: Timothy Beyer <beyert@cs.ucr.edu>

PORTNAME=	flext
PORTVERSION=	20210505
CATEGORIES=	audio devel
PKGNAMEPREFIX=	pd-

MAINTAINER=	beyert@cs.ucr.edu
COMMENT=	C++ development layer for Pure Data and Max

LICENSE=	GPLv2+
LICENSE_FILE=	${WRKSRC}/license.txt

BUILD_DEPENDS=	pd:audio/pd
LIB_DEPENDS=	libsndobj.so:audio/sndobj \
	libstk-4.6.2.so:audio/stk
RUN_DEPENDS=	pd:audio/pd

USES=	gmake compiler:c++11-lang autoreconf libtool
AC_CONFIG_FILES=	configure.ac

CXXFLAGS+=	-I${LOCALBASE}/include -fPIC
LDFLAGS+=	-L${LOCALBASE}/lib

HAS_CONFIGURE=	yes
#CONFIGURE_SCRIPT=	${WRKSRC}/Makefile.in
#CONFIGURE_SCRIPT=	${WRKSRC}/configure
CONFIGURE_ARGS=	--with-sdkdir=${LOCALBASE}/include/pd \
	--with-sndobjdir=${LOCALBASE}/include/SndObj \
	--with-stkdir=${LOCALBASE}/include/stk

AUTORECONF_ARGS=	${WRKSRC}/configure.ac

USE_GITHUB=	yes
GH_TUPLE=	grrrr:${PORTNAME}:a760d04

INSTALL_TARGET=	install-strip

#post-configure:
#	cd ${WRKSRC} && ./configure ${CONFIGURE_ARGS}
#do-configure:
#	cd ${WRKSRC} && autoreconf ./configure.ac && ./configure

#MAKE_ARGS=	PD_INCLUDE=${LOCALBASE}/include/pd

post-patch:
.if defined(PREFIX)
	@${REINPLACE_CMD} -e 's|/usr/local/include|${LOCALBASE}/include|g' \
		-e 's|prefix = /usr/local|prefix = ${PREFIX}|' \
		${WRKSRC}/Makefile.am
.endif

.include <bsd.port.mk>
