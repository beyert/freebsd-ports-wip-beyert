# Created by: Martin Cracauer <cracauer@cons.org>

PORTNAME=	scsh
PORTVERSION=	0.6.7
CATEGORIES=	lang scheme
MASTER_SITES=	SF ftp://ftp.scsh.net/pub/scsh/0.6/
PKGNAMESUFFIX=	-restored

MAINTAINER=	beyert@cs.ucr.edu
COMMENT=	Unix shell embedded into Scheme, with access to all Posix calls

LICENSE=	BSD3CLAUSE
LICENSE_FILE=	${WRKSRC}/COPYING

ONLY_FOR_ARCHS=	i386

USES=		gmake

CONFLICTS=	scheme48

LDFLAGS+=	-Wl,-E

OPTIONS_DEFINE=	DOCS

.include <bsd.port.pre.mk>

GNU_CONFIGURE=	yes
CONFIGURE_ARGS=	--with-lib-dirs-list='("${PREFIX}/lib/scsh/0.6")'

ALL_TARGET=	enough

post-install:
	@${STRIP_CMD} ${STAGEDIR}${PREFIX}/bin/scsh
.if ${PORT_OPTIONS:MDOCS}
	@${MKDIR} ${STAGEDIR}${DOCSDIR}
	@${MV} ${STAGEDIR}${PREFIX}/lib/${PORTNAME}/doc/* ${STAGEDIR}${DOCSDIR}/
	@${RMDIR} ${STAGEDIR}${PREFIX}/lib/${PORTNAME}/doc
	@(cd ${WRKSRC} && \
		${INSTALL_DATA} README RELEASE COPYING ${STAGEDIR}${DOCSDIR})
#	@(cd ${WRKSRC} && \
#	@${RM} -f ${STAGEDIR}${DOCSDIR}
#	@${LN} -fs ${STAGEDIR}${PREFIX}/lib/scsh/doc ${STAGEDIR}${DOCSDIR}
.else
	@${RM} -rf ${STAGEDIR}${PREFIX}/lib/scsh/doc
	@${RM} -rf ${STAGEDIR}${DOCSDIR}
.endif
	@(cd ${WRKSRC} && \
	 ${CP} -R emacs ${STAGEDIR}${PREFIX}/lib/scsh/)
	@${CAT} ${PKGMESSAGE}

.include <bsd.port.post.mk>
