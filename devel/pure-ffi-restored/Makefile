# Created by: Zhihao Yuan <lichray@gmail.com>

PORTNAME=	pure-ffi
PORTVERSION=	0.14
CATEGORIES=	devel
MASTER_SITES=	https://bitbucket.org/purelang/pure-lang/downloads/
PKGNAMESUFFIX=	-restored
DIST_SUBDIR=	pure

MAINTAINER=	beyert@cs.ucr.edu
COMMENT=	Pure language interface to libffi

LICENSE=	LGPL3+
LICENSE_FILE=	${WRKSRC}/COPYING.LESSER

BUILD_DEPENDS=	${LOCALBASE}/include/ffitarget.h:devel/libffi
LIB_DEPENDS=	libffi.so:devel/libffi

USES=	pkgconfig pure

PLIST_FILES=	lib/pure/ffi.pure \
		lib/pure/ffi.so

PORTDOCS=	README

PORTEXAMPLES=	*

OPTIONS_DEFINE=	DOCS EXAMPLES

post-install-DOCS-on:
	@${MKDIR} ${STAGEDIR}${DOCSDIR}
	${INSTALL_DATA} ${PORTDOCS:S|^|${WRKSRC}/|} ${STAGEDIR}${DOCSDIR}

post-install-EXAMPLES-on:
	@${MKDIR} ${STAGEDIR}${EXAMPLESDIR}
	@(cd ${WRKSRC}/examples/ && ${COPYTREE_SHARE} . ${STAGEDIR}${EXAMPLESDIR})

.include <bsd.port.mk>
