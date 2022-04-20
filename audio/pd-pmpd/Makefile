# Created by: Timothy Beyer <beyert@cs.ucr.edu>

PORTNAME=	pmpd
PORTVERSION=	0.12
CATEGORIES=	audio
PKGNAMEPREFIX=	pd-

MAINTAINER=	beyert@cs.ucr.edu
#COMMENT=	PD Externals providing real-time simulations and physical behaviors
COMMENT=	Physical Modelling for PureData

LICENSE=	GPLv2
LICENSE_FILE=	${WRKSRC}/LICENSE.txt

BUILD_DEPENDS=	pd:audio/pd
RUN_DEPENDS=	pd:audio/pd

USES=	cmake
USE_GITHUB=	yes
GH_TUPLE=	avilleret:${PKGNAMEPREFIX}${PORTNAME}:4eeb5be

CMAKE_ARGS=	-DPUREDATA_INCLUDE_DIRS="${LOCALBASE}/include/pd" \
	-DLOCALBASE_INCLUDE_DIR="${LOCALBASE}/include" \
	-DPD_EXTERNALSDIR="${LOCALBASE}/lib/pd-externals"
CFLAGS+=	-rdynamic -shared
#LDFLAGS+=	"-L${LOCALBASE}/lib"

OPTIONS_DEFINE=	DOCS EXAMPLES

.include <bsd.port.options.mk>

.if ${PORT_OPTIONS:MDOCS}
CMAKE_ARGS+=	-DINSTALL_DOCUMENTATION:BOOL=ON -DPMPD_DOCSDIR="${DOCSDIR}"
#PLIST_SUB+=	DOCSDIR="${DOCSDIR_REL}"
.else
CMAKE_ARGS+=	-DINSTALL_DOCUMENTATION:BOOL=OFF
#PLIST_SUB+=	DOCSDIR="@comment"
.endif

.if ${PORT_OPTIONS:MEXAMPLES}
CMAKE_ARGS+=	-DINSTALL_EXAMPLES:BOOL=ON -DPMPD_EXAMPLESDIR="${EXAMPLESDIR}"
#PLIST_SUB+=	EXAMPLESDIR="${EXAMPLESDIR_REL}"
.else
CMAKE_ARGS+=	-DINSTALL_EXAMPLES:BOOL=OFF
#PLIST_SUB+=	EXAMPLESDIR="@comment"
.endif

#post-patch:
#	@${REINPLACE_CMD} -e 's| -undefined dynamic_lookup||' \
#		${WRKSRC}/CMakeLists.txt

.include <bsd.port.mk>
