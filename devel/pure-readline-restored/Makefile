# Created by: Zhihao Yuan <lichray@gmail.com>

PORTNAME=	pure-readline
PORTVERSION=	0.3
PORTREVISION=	2
CATEGORIES=	devel
MASTER_SITES=	https://bitbucket.org/purelang/pure-lang/downloads/
PKGNAMESUFFIX=	-restored
DIST_SUBDIR=	pure

MAINTAINER=	beyert@cs.ucr.edu
COMMENT=	Readline interface for the Pure language

LICENSE=	BSD3CLAUSE GPLv3+
LICENSE_COMB=	dual

USES=	pkgconfig pure readline

PORTDOCS=	README
PLIST_FILES=	lib/pure/readline.pure \
		lib/pure/readline.so

OPTIONS_DEFINE=	DOCS

post-install:
	@${STRIP_CMD} ${STAGEDIR}${PREFIX}/lib/pure/readline.so

post-install-DOCS-on:
	@${MKDIR} ${STAGEDIR}${DOCSDIR}
	${INSTALL_DATA} ${PORTDOCS:S|^|${WRKSRC}/|} ${STAGEDIR}${DOCSDIR}

.include <bsd.port.mk>
