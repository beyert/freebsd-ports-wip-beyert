# Created by: Zhihao Yuan <lichray@gmail.com>

PORTNAME=	pure-stldict
PORTVERSION=	0.8
CATEGORIES=	devel
MASTER_SITES=	https://bitbucket.org/purelang/pure-lang/downloads/
PKGNAMESUFFIX=	-restored
DIST_SUBDIR=	pure

MAINTAINER=	beyert@cs.ucr.edu
COMMENT=	Pure interface to C++ STL map/unordered_map

LICENSE=	LGPL3+
LICENSE_FILE=	${WRKSRC}/COPYING.LESSER

USES=	compiler:c++0x pkgconfig pure

CXXFLAGS+=	-std=c++0x -DHAVE_STD_IS_PERMUTATION

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
