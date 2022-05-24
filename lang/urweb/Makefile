# Created by: Timothy Beyer <beyert@cs.ucr.edu>

PORTNAME=	urweb
PORTVERSION=	20200209
CATEGORIES=	lang www

MAINTAINER=	beyert@cs.ucr.edu
COMMENT=	Ultimate host for embedded domain-specific languages

LICENSE=	BSD3CLAUSE
LICENSE_FILE=	${WRKSRC}/LICENSE

ONLY_FOR_ARCHS=	amd64 i386

BUILD_DEPENDS=	mlton:lang/mlton
LIB_DEPENDS=	libicudata.so:devel/icu \
		libgmp.so:math/gmp

USES=	autoreconf gmake libtool ssl tar:tgz

CONFIGURE_ENV=	CCARGS="-I${LOCALBASE}/include"
GNU_CONFIGURE=	yes

USE_GITHUB=	yes
USE_LDCONFIG=	yes
CFLAGS+=	-pthread

OPTIONS_DEFINE=	ELISP PGSQL SQLITE MYSQL
OPTIONS_DEFAULT=	ELISP PGSQL
OPTIONS_EXCLUDE=	NLS DOCS
ELISP_DESC=	Install contributed Emacs Lisp

.include <bsd.port.options.mk>

CONFIGURE_ARGS+=	--with-openssl=${OPENSSLBASE}

.if ${PORT_OPTIONS:MELISP}
PLIST_SUB+=	ELISP=""
CONFIGURE_ARGS+=	with_emacs=yes
.else
PLIST_SUB+=	ELISP="@comment "
CONFIGURE_ARGS+=	with_emacs=no
.endif

.if ${PORT_OPTIONS:MPGSQL}
USES+=	pgsql
WANT_PGSQL=	server
.else
CONFIGURE_ENV+=	PGHEADER="no"
.endif

.if ${PORT_OPTIONS:MSQLITE}
USES+=	sqlite
.else
CONFIGURE_ENV+=	SQHEADER="no"
.endif

.if ${PORT_OPTIONS:MMYSQL}
USES+=	mysql
.else
CONFIGURE_ENV+=	MSHEADER="no"
.endif

post-patch:
	@${REINPLACE_CMD} -e "s|postgresql/libpq-fe.h|libpq-fe.h|g" \
		${WRKSRC}/configure.ac
	@${REINPLACE_CMD} -e "s|uw_Basis_int true|uw_Basis_int utrue|" \
		-e "s|uw_Basis_int false|uw_Basis_int ufalse|" \
		-e "s|uw_Basis_bool true|uw_Basis_bool utrue|" \
		-e "s|uw_Basis_bool false|uw_Basis_bool ufalse|" \
		-e "s|\&true|\&utrue|g" -e "s|\&false|\&ufalse|g" \
		-e "s|abs(ret)|llabs(ret)|" \
		${WRKSRC}/src/c/urweb.c

.include <bsd.port.mk>
