# Created by: Timothy Beyer <beyert@cs.ucr.edu>

PORTNAME=	sndobj
PORTVERSION=	20110603
CATEGORIES=	audio devel

MAINTAINER=	beyert@cs.ucr.edu
COMMENT=	SndObj library

LICENSE=	GPLv2+
LICENSE_FILE=	${WRKSRC}/License.txt

BUILD_DEPENDS=	pd:audio/pd
RUN_DEPENDS=	pd:audio/pd

USES=	scons compiler:c++11-lang python

#SCONS+=	instdir="${PREFIX}"
MAKE_ARGS+=	instdir="${STAGEDIR}" prefix="${PREFIX}" nostaticlib="False" \
	customCXXFLAGS="${CXXFLAGS}"

CXXFLAGS+=	-fPIC

USE_GITHUB=	yes
GH_TUPLE=	johnglover:${PORTNAME}:387bb00

post-patch:
#	@${REINPLACE_CMD} -e "s|STAGEDIR|${STAGEDIR}|g" \
#		-e "s|/usr/local|${PREFIX}|" \
#		${WRKSRC}/SConstruct
	@${MKDIR} ${STAGEDIR}${PYTHON_SITELIBDIR}
	@${REINPLACE_CMD} -e 's|gcc|${CC}|g' ${WRKSRC}/src/Makefile

.include <bsd.port.mk>
