# Created by: Zhihao Yuan <lichray@gmail.com>

PORTNAME=	pure
PORTVERSION=	0.64
PORTREVISION=	10
CATEGORIES=	lang
MASTER_SITES=	https://bitbucket.org/purelang/pure-lang/downloads/
PKGNAMESUFFIX=	-restored
EXTRACT_ONLY=	${DISTNAME}.tar.gz

MAINTAINER=	beyert@cs.ucr.edu
COMMENT=	Modern-style functional programming language

LICENSE=	GPLv3 LGPL3
LICENSE_COMB=	dual

LIB_DEPENDS=	libgmp.so:math/gmp \
		libmpfr.so:math/mpfr \
		libpcreposix.so:devel/pcre \
		libLLVM-${LLVM_VERSION:C/./&./}.so:devel/llvm${LLVM_VERSION}-restored

USES=		gmake iconv libedit pathfix pkgconfig

SUB_FILES=	pkg-message

GNU_CONFIGURE=	yes
CONFIGURE_ARGS=	--with-libgmp-prefix=${LOCALBASE} --enable-release \
		--with-pcre	\
		--with-tool-prefix=${LOCALBASE}/llvm${LLVM_VERSION}/bin
EXTRACT_AFTER_ARGS=--no-same-owner --no-same-permissions --exclude texmacs
TEST_TARGET=	check  # XXX: some tests fail
USE_LDCONFIG=	yes

PORTDOCS=	*
PORTEXAMPLES=	*

OPTIONS_DEFINE=	DOCS EMACS ETC EXAMPLES

EMACS_DESC=	Compile pure-mode.el with Emacs
ETC_DESC=	Copy Pure syntax highlighting to ${DATADIR}/etc

.if !defined(LLVM_VERSION)
.	for v in 33 34 35
.		if exists(${LOCALBASE}/bin/llvm-config$v)
LLVM_VERSION=	$v
.		endif
.	endfor
.endif
LLVM_VERSION?=	35	# Pure does not build with llvm36
SUB_LIST+=	LLVM_VERSION=${LLVM_VERSION}
.if ${LLVM_VERSION} >= 35
USES+=	compiler:c++11-lib
.endif

OPTIONS_DEFAULT=	ETC

OPTIONS_SUB=	yes

EMACS_CONFIGURE_WITH=	elisp

post-patch:
	${REINPLACE_CMD} -e	\
	    's,defcustom pure-docs-dir .*,defcustom pure-docs-dir "${DOCSDIR}",' \
		${WRKSRC}/etc/pure-mode.el.in
	${REINPLACE_CMD} \
	    -e 's,default_doc =.*;$$,default_doc = "${DOCSDIR}/index.html";,' \
	    -e 's,"+interp.libdir+"docs,${DOCSDIR},g' \
		${WRKSRC}/lexer.cc

.include <bsd.port.options.mk>

.if ${PORT_OPTIONS:MDOCS}
DISTFILES+=	${EXTRACT_ONLY} ${PORTNAME}-docs-${PORTVERSION}.tar.gz
.endif

.if ${PORT_OPTIONS:MEMACS}
USES+=			emacs:build
MAKE_ARGS+=	emacs_prefix=${PREFIX}
.endif

# automatically disable readline support if editline support is available
.if exists(/usr/include/edit/readline/readline.h)
CONFIGURE_ARGS+=	--without-readline
.endif

.include <bsd.port.pre.mk>

.if empty(ICONV_LIB)
CONFIGURE_ARGS+=ac_cv_lib_iconv_libiconv=no ac_cv_lib_iconv_iconv=no
.endif

post-install:
	${STRIP_CMD} ${STAGEDIR}${PREFIX}/bin/pure	\
		${STAGEDIR}${PREFIX}/lib/libpure.so.*.*

post-install-ETC-on:
	@${MKDIR} ${STAGEDIR}${DATADIR}/etc/
	@(cd ${WRKSRC} && ${RM} etc/*.in && ${COPYTREE_SHARE} etc/ ${STAGEDIR}${DATADIR})

post-install-DOCS-on:
	@${MKDIR} ${STAGEDIR}${DOCSDIR}
	${TAR} -C ${STAGEDIR}${DOCSDIR} --strip-components 1	\
		--exclude Makefile --exclude '*.tm'	\
		${EXTRACT_AFTER_ARGS}	\
		-xpf ${_DISTDIR}${_DISTFILES:M*-docs*}
	${FIND} ${STAGEDIR}${DOCSDIR} -type f | ${XARGS} ${CHMOD} ${SHAREMODE}

post-install-EXAMPLES-on:
	@${MKDIR} ${STAGEDIR}${EXAMPLESDIR}
	@(cd ${WRKSRC}/examples && ${COPYTREE_SHARE} . ${STAGEDIR}${EXAMPLESDIR})

.include <bsd.port.post.mk>
