# Created by: Timothy Beyer <beyert@cs.ucr.edu>

PORTNAME=	RTcmix
DISTVERSION=	g20220620
CATEGORIES=	audio

MAINTAINER=	beyert@cs.ucr.edu
COMMENT=	Real-time language for sound synthesis and signal-processing

LICENSE=	APACHE20
LICENSE_FILE=	${WRKSRC}/LICENSE

LIB_DEPENDS=	libsndio.so:audio/sndio \
		liblo.so:audio/liblo

USES=	bison compiler:c++11-lib dos2unix gmake pkgconfig shebangfix xorg
OPTIONS_SUB=	yes

USE_XORG=	x11

SHEBANG_FILES=	docs/pod/syn.in

DOS2UNIX_FILES=	src/control/midi/portmidi/pm_common/pminternal.h \
		src/control/midi/portmidi/pm_common/pmutil.c \
		src/control/midi/portmidi/pm_common/pmutil.h \
		src/control/midi/portmidi/pm_common/portmidi.h \
		src/control/midi/portmidi/pm_common/portmidi.c

HAS_CONFIGURE=	yes
CONFIGURE_ARGS=	--with-osc --x-libraries=${LOCALBASE}/lib \
		--x-includes=${LOCALBASE}/include
USE_GITHUB=	yes
GH_TUPLE=	${PORTNAME}:${PORTNAME}:1c9039f

OPTIONS_DEFINE=	ALSA DOCS EXAMPLES JACK
OPTIONS_DEFAULT=	JACK

ALSA_CONFIGURE_WITH=	alsa
ALSA_LIB_DEPENDS=	libasound.so:audio/alsa-lib
JACK_CONFIGURE_WITH=	jack
JACK_LIB_DEPENDS=	libjack.so:audio/jack

DISABLE_MAKE_JOBS=	yes

# perl is needed for pod2man, pod2html; ghostscript is needed for ps2pdf
DOCS_USES=	ghostscript:agpl,build perl5
DOCS_BUILD_DEPENDS=	groff:textproc/groff \
		ps2pdf:print/ghostscript9-agpl-base
DOCS_USE=	PERL5

CFLAGS+=	-I${WRKSRC}/include -I${WRKSRC}/genlib -I${WRKSRC}/src/rtcmix
CXXFLAGS+=	-I${WRKSRC}/include

LDFLAGS_=	-L${LOCALBASE}/lib -llo

MFLAGS_=	MAKE="${GMAKE}" DESTDIR="${STAGEDIR}${PREFIX}/bin" \
		BINDIR="${STAGEDIR}${PREFIX}/bin" \
		RTLIB_INSTALL_DIR="${STAGEDIR}${PREFIX}/lib" \
		MANDESTDIR="${STAGEDIR}${MANPREFIX}/man" \
		HTMLDESTDIR="${STAGEDIR}${DOCSDIR}"
#		LIBDESTDIR="${WRKSRC}/shlib"

.include <bsd.port.pre.mk>

#MAKE_ARGS+=	LIBDIR="${WRKSRC}/lib" RANLIB="${RANLIB}" INSTALL="cp -f"
MAKE_ARGS+=	INSTALL="install -s" \
		${MFLAGS_} MFLAGS='${MFLAGS_}' \
		ARCH=FREEBSD CC="${CC}" CXX="${CXX}" AUDIODRIVER=OSS \
		LDFLAGS_="${LDFLAGS_}" PICFLAGS="-fPIC"

post-patch:
	@${CP} -pR ${FILESDIR}/pm_sndio ${WRKSRC}/src/control/midi/portmidi/
	@${RM} ${WRKSRC}/utils/resample/README.orig

post-install:
#	@${CHMOD} 644 ${WRKSRC}/shlib/*
#	${CP} -p ${WRKSRC}/shlib/* ${STAGEDIR}${PREFIX}/lib/
	${INSTALL_LIB} ${WRKSRC}/shlib/* ${STAGEDIR}${PREFIX}/lib/
	@${MKDIR} ${STAGEDIR}${DATADIR}
.for i in makefile.conf README LICENSE THANKS
	${INSTALL_DATA} ${WRKSRC}/${i} ${STAGEDIR}${DATADIR}/
.endfor
##	@${INSTALL_DATA} ${WRKSRC}/src/rtcmix/RTcmix.h ${PREFIX}/include/

post-install-DOCS-on:
	@${MKDIR} ${STAGEDIR}${DOCSDIR}
	@cd ${WRKSRC}/docs/pod && \
		${GMAKE} ${MAKE_ARGS} ps pdf installman installhtml installsyn
	${INSTALL_DATA} ${WRKSRC}/docs/pod/*.ps ${STAGEDIR}${DOCSDIR}/
	${INSTALL_DATA} ${WRKSRC}/docs/pod/*.pdf ${STAGEDIR}${DOCSDIR}/

post-install-EXAMPLES-on:
	@${MKDIR} ${STAGEDIR}${EXAMPLESDIR}
	@${CP} -pR ${WRKSRC}/docs/sample_code ${STAGEDIR}${EXAMPLESDIR}/
	@${CP} -pR ${WRKSRC}/docs/sample_scores ${STAGEDIR}${EXAMPLESDIR}/

.include <bsd.port.post.mk>
