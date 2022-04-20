# Created by: Timothy Beyer <beyert@cs.ucr.edu>

PORTNAME=	mrpeach
PORTVERSION=	20170712
CATEGORIES=	audio
PKGNAMEPREFIX=	pd-

MAINTAINER=	beyert@cs.ucr.edu
COMMENT=	Bag of tricks for Pure Data

LICENSE=	GPLv2+
LICENSE_FILE=	${WRKSRC}/LICENSE.txt

BUILD_DEPENDS=	pd:audio/pd
RUN_DEPENDS=	pd:audio/pd

USES=	gmake

USE_GITHUB=	yes
GH_TUPLE=	avilleret:${PORTNAME}:54557da

CFLAGS+=	-rdynamic -shared

MAKE_ARGS=	LDFLAGS="${LDFLAGS}" CFLAGS="${CFLAGS}" PD_PATH="${LOCALBASE}" \
	PD_INCLUDE="${LOCALBASE}/include/pd"

.include <bsd.port.options.mk>

post-patch:
.if defined(PREFIX)
	@${REINPLACE_CMD} -e 's|/usr/local/include|${LOCALBASE}/include|g' \
		-e 's|prefix = /usr/local|prefix = ${PREFIX}|' \
		-e 's|PD_PATH = /usr/local|PD_PATH = ${PREFIX}|' \
		${WRKSRC}/Makefile
.endif

.include <bsd.port.mk>
