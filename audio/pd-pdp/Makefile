# Created by: Timothy Beyer <beyert@cs.ucr.edu>

PORTNAME=	pdp
#DISTVERSION=	20140106
DISTVERSION=	0.12.7
CATEGORIES=	audio

MAINTAINER=	beyert@cs.ucr.edu
COMMENT=	Packet processing library for pure data

LICENSE=	GPLv2
LICENSE_FILE_GPLv2=	${WRKSRC}/COPYING

BUILD_DEPENDS=	pd:audio/pd
RUN_DEPENDS=	pd:audio/pd
LIB_DEPENDS+=	libpng16.so:graphics/png \
	libgsl.so:math/gsl

USES=	autoreconf gmake xorg gl sdl

USE_GITHUB=	yes
GH_TUPLE=	zwizwa:pdp:287d887

GNU_CONFIGURE=	yes
USE_XORG=	x11 xv xext
USE_GL+=	gl glu
USE_SDL+=	sdl

CONFIGURE_ENV+=	STAGEDIR="${STAGEDIR}" prefix="${PREFIX}" \
	PDP_datadir="${DATADIR}" PDP_docsdir="${DOCSDIR}" \
	PDP_examplesdir="${EXAMPLESDIR}" localbase="${LOCALBASE}" \
	MAKE="gmake" STRIP="${STRIP_CMD}" STRIP_ARGS="${STRIP}"

OPTIONS_DEFINE=	DOCS EXAMPLES

.include <bsd.port.options.mk>

post-install:
.if ! ${PORT_OPTIONS:MDOCS}
	@${RM} -r ${STAGEDIR}${DOCSDIR}
.endif
.if ! ${PORT_OPTIONS:MEXAMPLES}
	@${RM} -r ${STAGEDIR}${EXAMPLESDIR}
.endif

.include <bsd.port.mk>
