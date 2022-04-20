# Created by: Timothy Beyer <beyert@cs.ucr.edu>

PORTNAME=	reposurgeon
PORTVERSION=	4.28
CATEGORIES=	devel
MASTER_SITES=	http://www.catb.org/~esr/reposurgeon/

MAINTAINER=	beyert@cs.ucr.edu
COMMENT=	Repository surgeon

LICENSE=	BSD2CLAUSE
LICENSE_FILE=	${WRKSRC}/COPYING

USES=	go:no_targets tar:xz gmake shebangfix

SHEBANG_LANG+=	awk
awk_OLD_CMD=	/bin/awk
awk_CMD=	${AWK}
SHEBANG_FILES=	${WRKSRC}/repository-editing.rb ${WRKSRC}/help-index.awk

BUILD_DEPENDS+=	asciidoctor:textproc/rubygem-asciidoctor

MAKE_ARGS+=	INSTALLABLES='$$(BINARIES)'

OPTIONS_DEFINE=	DOCS

pre-build:
	${REINPLACE_CMD} 's|AWK = awk --posix|AWK = ${AWK}|g' ${WRKSRC}/Makefile
	${REINPLACE_CMD} 's|AWK = awk|AWK = ${AWK}|g' ${WRKSRC}/Makefile
	${REINPLACE_CMD} 's| awk | ${AWK} |g' ${WRKSRC}/Makefile
	${REINPLACE_CMD} 's|poundsign.awk|${WRKSRC}/poundsign.awk|g' \
		${WRKSRC}/Makefile
	${REINPLACE_CMD} \
		's|	asciidoctor|	cd ${WRKSRC} \&\& ${LOCALBASE}/bin/asciidoctor|g' \
		${WRKSRC}/Makefile
	${REINPLACE_CMD} 's|	go|	${LOCALBASE}/bin/go|g' ${WRKSRC}/Makefile
	${REINPLACE_CMD} 's| repobench.adoc||g' ${WRKSRC}/Makefile
	${REINPLACE_CMD} 's| repobench | |g' ${WRKSRC}/Makefile
	${REINPLACE_CMD} 's|-o repo|-o ${WRKSRC}/repo|g' ${WRKSRC}/Makefile
	${REINPLACE_CMD} 's|\.\/|${WRKSRC}\/|g' ${WRKSRC}/Makefile
	${REINPLACE_CMD} 's|>surgeon|>${WRKSRC}/surgeon|g' ${WRKSRC}/Makefile
	${REINPLACE_CMD} 's|<NEWS.adoc|<${WRKSRC}/NEWS.adoc|g' ${WRKSRC}/Makefile
	${REINPLACE_CMD} 's|extractversion.sh|${WRKSRC}/extractversion.sh|g' \
		${WRKSRC}/Makefile

.include <bsd.port.mk>
