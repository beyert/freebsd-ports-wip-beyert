# Created by: Timothy Beyer

PORTNAME=	opengit
DISTVERSION=	20191020
CATEGORIES=	devel

MAINTAINER=	beyert@cs.ucr.edu
COMMENT=	Open Source replacement for GPL git

LICENSE=	BSD2CLAUSE
LICENSE_FILE=	${WRKSRC}/LICENSE

MAKE_ARGS=	PREFIX=${PREFIX}

USE_GITHUB=	yes
GH_ACCOUNT=	khanzf
GH_TAGNAME=	4c8cb00

pre-install:
	${MKDIR} ${STAGEDIR}/usr/lib
	${MKDIR} ${STAGEDIR}/usr/tests

post-install:
	${MV} ${STAGEDIR}/usr/lib/* ${STAGEDIR}/usr/local/lib/
	${MV} ${STAGEDIR}/usr/tests/* ${STAGEDIR}/usr/local/tests/
	${MV} ${STAGEDIR}/ogit ${STAGEDIR}/usr/local/bin/
	${RMDIR} ${STAGEDIR}/usr/lib
	${RMDIR} ${STAGEDIR}/usr/tests

#post-patch:
#	${REINPLACE_CMD} 's|lib|local/lib|g' ${WRKSRC}/Makefile
#	${REINPLACE_CMD} 's|src|local/src|g' ${WRKSRC}/Makefile
#	${MKDIR} ${WRKSRC}/local
#	${MV} ${WRKSRC}/lib ${WRKSRC}/local/
#	${MV} ${WRKSRC}/src ${WRKSRC}/local/

.include <bsd.port.mk>
