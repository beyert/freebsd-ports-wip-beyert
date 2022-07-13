# Created by: Timothy Beyer <beyert@cs.ucr.edu>

PORTNAME=	ekext
PORTVERSION=	20150729
CATEGORIES=	audio
PKGNAMEPREFIX=	pd-

MAINTAINER=	beyert@cs.ucr.edu
COMMENT=	Pd externals written by Dr. Edward Kelly

LICENSE=	BSD3CLAUSE GPLv2+ GPLv3 PDOLD
LICENSE_COMB=	multi
LICENSE_GROUPS_PDOLD=	COPYFREE
LICENSE_NAME_PDOLD=	Pure Data 0.35 license
LICENSE_PERMS_PDOLD=	${_LICENSE_PERMS_DEFAULT} auto-accept
LICENSE_FILE_BSD3CLAUSE =	${WRKSRC}/LICENSE.txt
LICENSE_FILE_GPLv2+ =	${WRKSRC}/lpreson~.c
LICENSE_FILE_GPLv3=	${WRKSRC}/cup-help.pd
LICENSE_FILE_PDOLD=	${WRKSRC}/peakit~_license.txt

BUILD_DEPENDS=	pd:audio/pd
RUN_DEPENDS=	pd:audio/pd

USES=	gmake

USE_GITHUB=	yes
GH_TUPLE=	beyert:${PORTNAME}:a1d15ce

MAKE_ARGS+=	PDINCLUDEDIR="${LOCALBASE}/include/pd" \
	pkglibdir="${PREFIX}/lib/pd-externals" stripflags="${STRIP}"

post-patch:
.if defined(PREFIX)
	@${REINPLACE_CMD} -e 's|/usr/local/include|${LOCALBASE}/include|g' \
		-e 's|prefix = /usr/local|prefix = ${PREFIX}|' \
		-e 's|PD_PATH = /usr/local|PD_PATH = ${PREFIX}|' \
		-e 's|-L/usr/local/lib|-L${PREFIX}/lib|' \
		${WRKSRC}/Makefile
.endif

.include <bsd.port.mk>
