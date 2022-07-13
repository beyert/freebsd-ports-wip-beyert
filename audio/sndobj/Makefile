# Created by: Timothy Beyer <beyert@cs.ucr.edu>

PORTNAME=	sndobj
PORTVERSION=	20110603
CATEGORIES=	audio devel

MAINTAINER=	beyert@cs.ucr.edu
COMMENT=	SndObj library

LICENSE=	GPLv2+
LICENSE_FILE=	${WRKSRC}/License.txt

BUILD_DEPENDS=	pd:audio/pd ${PYNUMPY}
RUN_DEPENDS=	pd:audio/pd ${PYNUMPY}

USES=	scons compiler:c++11-lang python

OPTIONS_DEFINE=		ALSA JACK
OPTIONS_SUB=		yes
OPTIONS_DEFAULT=	ALSA JACK

ALSA_CONFIGURE_ENABLE=	alsa
ALSA_LIB_DEPENDS=	libasound.so:audio/alsa-lib
JACK_CONFIGURE_ENABLE=	jack
JACK_LIB_DEPENDS=	libjack.so:audio/jack

MAKE_ARGS+=	instdir="${STAGEDIR}" prefix="${PREFIX}" nostaticlib="False" \
	customCXXFLAGS="${CXXFLAGS}"

CXXFLAGS+=	-fPIC

USE_GITHUB=	yes
GH_TUPLE=	johnglover:${PORTNAME}:387bb00

post-patch:
	@${MKDIR} ${STAGEDIR}${PYTHON_SITELIBDIR}
	@${REINPLACE_CMD} -e 's|gcc|${CC}|g' ${WRKSRC}/src/Makefile

.include <bsd.port.mk>
