# Created by: Yuri Victorovich <yuri@rawbw.com>

PORTNAME=	stk
PORTVERSION=	4.6.2
PORTREVISION=	1
CATEGORIES=	audio
MASTER_SITES=	http://ccrma.stanford.edu/software/stk/release/

MAINTAINER=	yuri@FreeBSD.org
COMMENT=	Synthesis ToolKit in C++

LICENSE=	MIT
LICENSE_FILE=	${WRKSRC}/LICENSE

LIB_DEPENDS=	libjack.so:audio/jack

#USES=	cmake autoreconf compiler:c++11-lang dos2unix localbase pkgconfig
USES=	gmake autoreconf compiler:c++11-lang dos2unix localbase pkgconfig
USE_LDCONFIG=	yes

DOS2UNIX_GLOB=	*.cpp *.h

GNU_CONFIGURE=	yes
CONFIGURE_ARGS=	--with-jack --with-oss

#CMAKE_ARGS=	-DENABLE_OSS RAWWAVES=${DATADIR}/rawwaves/
#CMAKE_ARGS=	-DENABLE_OSS RAWWAVES=${DATADIR}/rawwaves/

LDFLAGS+=	-pthread

LIBDIR=	${PREFIX}/lib/${PORTNAME}

post-install:
	@cd ${WRKSRC} && ${COPYTREE_SHARE} rawwaves ${STAGEDIR}${DATADIR}
	@${RM} ${STAGEDIR}${DATADIR}/rawwaves/._* ${STAGEDIR}${DATADIR}/rawwaves/*.c
	@${STRIP_CMD} ${STAGEDIR}${PREFIX}/lib/libstk-${PORTVERSION}.so
.for f in bin sbin tcl
	@${MKDIR} ${STAGEDIR}${LIBDIR}/${f}
.endfor
# demo
	@${CP} -pR ${WRKSRC}/projects/demo/tcl/* ${STAGEDIR}${LIBDIR}/tcl/
.for ex in stk-demo
	${INSTALL_PROGRAM} \
		${WRKSRC}/projects/demo/${ex} \
		${STAGEDIR}${LIBDIR}/bin/${ex}
.endfor
.for f in Banded Drums Modal Physical Shakers StkDemo Voice
	@${REINPLACE_CMD} -e 's|wish < tcl|\#\!/bin/sh\nwish < ${LIBDIR}/tcl|' \
		-e 's|./stk-demo|${LIBDIR}/bin/stk-demo|g' \
		${WRKSRC}/projects/demo/${f}
	${INSTALL_DATA} ${WRKSRC}/projects/demo/${f} \
		${STAGEDIR}${LIBDIR}/sbin/${f}
.endfor
# effects
	@${CP} -p ${WRKSRC}/projects/effects/tcl/* ${STAGEDIR}${LIBDIR}/tcl/
.for ex in effects
	${INSTALL_PROGRAM} \
		${WRKSRC}/projects/effects/${ex} \
		${STAGEDIR}${LIBDIR}/bin/${ex}
.endfor
.for f in StkEffects
	@${REINPLACE_CMD} -e 's|wish < tcl|\#\!/bin/sh\nwish < ${LIBDIR}/tcl|' \
		-e 's|./effects|${LIBDIR}/bin/effects|g' \
		${WRKSRC}/projects/effects/${f}
	${INSTALL_DATA} ${WRKSRC}/projects/effects/${f} \
		${STAGEDIR}${LIBDIR}/sbin/${f}
.endfor
# eguitar
	@${CP} -p ${WRKSRC}/projects/eguitar/tcl/* ${STAGEDIR}${LIBDIR}/tcl/
.for ex in eguitar
	${INSTALL_PROGRAM} \
		${WRKSRC}/projects/eguitar/${ex} \
		${STAGEDIR}${LIBDIR}/bin/${ex}
.endfor
.for f in ElectricGuitar
	@${REINPLACE_CMD} -e 's|wish < tcl|\#\!/bin/sh\nwish < ${LIBDIR}/tcl|' \
		-e 's|./eguitar|${LIBDIR}/bin/eguitar|g' \
		${WRKSRC}/projects/eguitar/${f}
	${INSTALL_DATA} ${WRKSRC}/projects/eguitar/${f} \
		${STAGEDIR}${LIBDIR}/sbin/${f}
.endfor
# examples
.for ex in sine sineosc foursine \
	play record audioprobe duplex inetIn inetOut rtsine crtsine \
	bethree controlbee threebees playsmf grains
	${INSTALL_PROGRAM} \
		${WRKSRC}/projects/examples/${ex} \
		${STAGEDIR}${LIBDIR}/bin/${ex}
.endfor
# ragamatic
	@${CP} -pR ${WRKSRC}/projects/ragamatic/tcl/* ${STAGEDIR}${LIBDIR}/tcl/
.for ex in ragamat
	${INSTALL_PROGRAM} \
		${WRKSRC}/projects/ragamatic/${ex} \
		${STAGEDIR}${LIBDIR}/bin/${ex}
.endfor
.for f in Raga
	@${REINPLACE_CMD} -e 's|wish < tcl|\#\!/bin/sh\nwish < ${LIBDIR}/tcl|' \
		-e 's|./ragamat|${LIBDIR}/bin/ragamat|g' \
		${WRKSRC}/projects/ragamatic/${f}
	${INSTALL_DATA} ${WRKSRC}/projects/ragamatic/${f} \
		${STAGEDIR}${LIBDIR}/sbin/${f}
.endfor
	@${CHMOD} -R "+x" ${STAGEDIR}${LIBDIR}/sbin

.include <bsd.port.mk>
