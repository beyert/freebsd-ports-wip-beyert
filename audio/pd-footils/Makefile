# Created by: Timothy Beyer <beyert@cs.ucr.edu>

PORTNAME=	footils
PORTVERSION=	20220416
CATEGORIES=	audio
PKGNAMEPREFIX=	pd-

MAINTAINER=	beyert@cs.ucr.edu
COMMENT=	Restored externals for Pure Data written by Frank Barknecht

LICENSE=	GPLv2+ GPLv2 PDOLD RX7
LICENSE_COMB=	multi
LICENSE_GROUPS_PDOLD=	COPYFREE
LICENSE_GROUPS_RX7=	COPYFREE
LICENSE_NAME_PDOLD=	Pure Data 0.35 license
LICENSE_NAME_RX7=	RX7 any purpose copyright notice intact license
LICENSE_PERMS_PDOLD=	${_LICENSE_PERMS_DEFAULT} auto-accept
LICENSE_PERMS_RX7=	${_LICENSE_PERMS_DEFAULT} auto-accept
LICENSE_FILE_GPLv2+ =	${WRKSRC}/LICENSE-fluid.txt
LICENSE_FILE_GPLv2=	${WRKSRC}/LICENSE-rx-saturno.txt
LICENSE_FILE_PDOLD=	${WRKSRC}/LICENSE-knob.txt
LICENSE_FILE_RX7=	${WRKSRC}/LICENSE-rx7.txt

# flext may become optional later once modules are divided into options, but is
# statically linked at compile time to shabby~, shaffy~, syncgrain and even
# fluid~; none of the other externals use flext
BUILD_DEPENDS=	pd:audio/pd \
	${LOCALBASE}/include/flext/flext.h:audio/pd-flext
LIB_DEPENDS=	libfluidsynth.so:audio/fluidsynth
# for now, we must build all modules, but this may change later
RUN_DEPENDS=	pd:audio/pd

USES=	gmake compiler:c++11-lang sdl

MAKE_ARGS=	MAKE="${GMAKE}" LOCALBASE="${LOCALBASE}" PREFIX="${PREFIX}" \
	STAGEDIR="${STAGEDIR}"

USE_SDL=	sdl

USE_GITHUB=	yes
GH_TUPLE=	beyert:${PKGNAMEPREFIX}${PORTNAME}:819fb62

OPTIONS_DEFINE=	EXAMPLES

post-patch:
.if defined(PREFIX)
	@${REINPLACE_CMD} -e 's|/usr/local/include|${LOCALBASE}/include|g' \
		-e 's|prefix = /usr/local|prefix = ${PREFIX}|' \
		${WRKSRC}/Makefile
.endif

post-patch-EXAMPLES-on:
MAKE_ARGS+=	INSTALL_EXAMPLES="yes"

.include <bsd.port.mk>
