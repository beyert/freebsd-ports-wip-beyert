# Created by: Kimura Fuyuki <fuyuki@hadaly.org>

PORTNAME=	scmail
PORTVERSION=	1.3
PORTREVISION=	4
CATEGORIES=	mail
MASTER_SITES=	http://namazu.org/~satoru/scmail/
PKGNAMESUFFIX=	-restored

MAINTAINER=	beyert@cs.ucr.edu
COMMENT=	Mail filter written in Scheme

LICENSE=	BSD3CLAUSE
LICENSE_FILE=	${WRKSRC}/COPYING

NOT_FOR_ARCHS=	"alpha"

# needs gauche compiled with GDBM option enabled
BUILD_DEPENDS=	gosh:lang/gauche-094
RUN_DEPENDS=	gosh:lang/gauche-094

USES=	gmake

CONFLICTS=	gauche scmail

.include <bsd.port.pre.mk>

MAKE_JOBS_UNSAFE=	yes

.if exists(${LOCALBASE}/bin/gauche-config)
GAUCHE_MAJOR_VER!=	${LOCALBASE}/bin/gauche-config -V | ${AWK} -F. '{print $$1}'
GAUCHE_MINOR_VER!=	${LOCALBASE}/bin/gauche-config -V | ${AWK} -F. '{print $$2}'
PLIST_SUB+=	GAUCHE_MM_VER="-${GAUCHE_MAJOR_VER}.${GAUCHE_MINOR_VER}"
.else
GAUCHE_VER=	none
PLIST_SUB+=	GAUCHE_MM_VER=""
.endif

post-patch:
	${REINPLACE_CMD} -E -e "s,cp -f?p,${CP},g;s,/dot.scmail,," \
		${WRKSRC}/Makefile
	${REINPLACE_CMD} 's| update-doc||g' ${WRKSRC}/Makefile
	${TOUCH} ${WRKSRC}/scmail/bayesian-filter.scm.in

post-build:
	${CP} -pR ${WRKSRC} ${STAGEDIR}/
	${REINPLACE_CMD} 's|PREFIX = /usr/local|PREFIX = ${STAGEDIR}/usr/local|g' ${WRKSRC}/Makefile
	${REINPLACE_CMD} 's|/share/scmail|/share/examples/scmail|g' ${WRKSRC}/Makefile
	${REINPLACE_CMD} 's|SITELIBDIR = `gauche-config --sitelibdir`|SITELIBDIR = $${PREFIX}/share/gauche-0.9/site/lib|g' ${WRKSRC}/Makefile
	cd ${WRKSRC}; ${GMAKE} install

# Maintainer only; it actually forwards mails to @examples.com!
test:
	cd ${WRKSRC}; ${MAKE} check

.include <bsd.port.post.mk>
