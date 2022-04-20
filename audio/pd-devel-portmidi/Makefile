# Created by: trevor

PORTNAME=	pd
DISTVERSION=	0.52-1
CATEGORIES=	audio

MAINTAINER=	beyert@cs.ucr.edu
COMMENT=	MIDI-capable real-time audio processor/synthesizer

# license of expr~ changed to BSD3 months prior to version 0.47-1
LICENSE=	BSD3CLAUSE
LICENSE_FILE_BSD3CLAUSE=	${WRKSRC}/LICENSE.txt

RUN_DEPENDS=	xdg-open:devel/xdg-utils \
		dejavu>0:x11-fonts/dejavu

USES=	autoreconf dos2unix gmake libtool pkgconfig shebangfix \
		tcl:wrapper tk:wrapper

USE_GITHUB=	yes
GH_TUPLE=	pure-data:pure-data:20609d9

OPTIONS_DEFINE=		NLS PORTMIDI ALSA DOCS JACK LIBPD
OPTIONS_SUB=		yes
OPTIONS_DEFAULT=	NLS JACK PORTMIDI LIBPD

NLS_USES=	gettext

ALSA_CONFIGURE_ENABLE=	alsa
ALSA_LIB_DEPENDS=	libasound.so:audio/alsa-lib
JACK_CONFIGURE_ENABLE=	jack
JACK_LIB_DEPENDS=	libjack.so:audio/jack

PORTMIDI_DESC=	Midi device support via portmidi and sndio
PORTMIDI_EXTRA_PATCHES=	\
	${PATCHDIR}/extra-patch-portmidi_portmidi_porttime_ptfreebsd.c \
	${PATCHDIR}/extra-patch-portmidi_Makefile.am \
	${PATCHDIR}/extra-patch-src_Makefile.am \
	${PATCHDIR}/extra-patch-src_s__midi__oss__pm.c
PORTMIDI_LIB_DEPENDS=	libsndio.so:audio/sndio

LIBPD_DESC=	Build separate libpd library

.include <bsd.port.options.mk>

.if ${PORT_OPTIONS:MLIBPD}
PLIST_SUB+=	LIBPD=""
CONFIGURE_ARGS+=	--enable-libpd --enable-libpd-utils \
	--enable-libpd-instance --enable-libpd-extra
.if ! ${PORT_OPTIONS:MNLS}
CONFIGURE_ARGS+=	--disable-libpd-setlocale
.endif
.else
PLIST_SUB+=	LIBPD="@comment "
.endif
SHEBANG_FILES=	tcl/pkg_mkIndex.tcl
SHEBANG_LANG=	tclsh
tclsh_CMD=	${LOCALBASE}/bin/tclsh
GNU_CONFIGURE=	yes
CONFIGURE_ENV=	ac_cv_lib_pthread_pthread_create=no
CONFIGURE_ARGS+=	--enable-portmidi --with-local-portmidi

CFLAGS+=	-fcommon
CPPFLAGS+=	-I${LOCALBASE}/include -I/usr/include
LDFLAGS+=	-L${LOCALBASE}/lib -L/usr/lib -pthread
.if ${PORT_OPTIONS:MPORTMIDI}
LDFLAGS+=	-lsndio
.endif

DESKTOP_ENTRIES="Pd" "" "${PREFIX}/lib/pd/tcl/pd.ico" "pd" "" ${FALSE}

post-extract:
.if ${PORT_OPTIONS:MPORTMIDI}
	@${CP} -pr ${FILESDIR}/portmidi ${WRKSRC}/portmidi/
.endif

post-patch:
	${FIND} ${PATCH_WRKSRC} -name "*.[ch]" | ${GREP} -v "extra/pd~/pd~.c" | \
		${XARGS} ${SED} -i.bak -e \
		's|__FreeBSD_kernel__|__FreeBSD__|g ; \
		 s|__x86_64__|__amd64__|g'
	${FIND} ${WRKSRC}/extra -name "*.c" | ${XARGS} ${SED} -i.bak -e \
		 's|<alloca\.h>|<stdlib.h>|g'
	@${REINPLACE_CMD} -e \
		'/^pkgconfigdir/s|=.*|= $$(prefix)/libdata/pkgconfig| ; \
		 s|make -C|$$(MAKE) -C|' ${WRKSRC}/Makefile.am
	@${REINPLACE_CMD} -e \
		's|$$(LN_S) $$(DESTDIR)$$(bindir)/pd $$(DESTDIR)$$(libpdbindir)/pd|cd $$(DESTDIR) \&\& $$(LN_S) .$$(bindir)/pd .$$(libpdbindir)/pd|' \
		-e '/^pd_LDADD/s| =.*| = $$(LIBM)|' \
		-e 's|LINUX|FREEBSD|' \
		${WRKSRC}/src/Makefile.am
	@${REINPLACE_CMD} -e \
		's|PD_BASEDIR/LICENSE|${DOCSDIR}/LICENSE|g ; \
		 s|PD_BASEDIR/doc/1|${DOCSDIR}/1|g' \
			${WRKSRC}/doc/1.manual/1.introduction.txt

do-install:
.for i in src man tcl po extra
	(cd ${WRKSRC}/${i} && ${SETENV} ${MAKE_ENV} ${MAKE_CMD} \
		${MAKE_FLAGS} ${MAKEFILE} ${MAKE_ARGS} ${INSTALL_TARGET})
.endfor
	(cd ${WRKSRC} && ${INSTALL_DATA} pd.pc \
		${STAGEDIR}${PREFIX}/libdata/pkgconfig)
	${MKDIR} ${STAGEDIR}${DOCSDIR}
	(${TAR} -C ${WRKSRC}/doc --exclude "*.bak" --exclude "*.orig" \
		-cf - . | ${TAR} -C ${STAGEDIR}${DOCSDIR} --unlink -xf -)
.for i in LICENSE.txt README.txt
	(cd ${WRKSRC} && ${INSTALL_DATA} ${i} ${STAGEDIR}${DOCSDIR})
.endfor
	${LN} -sf ../../${DOCSDIR_REL} ${STAGEDIR}${PREFIX}/lib/pd/doc
	${FIND} ${STAGEDIR}${PREFIX}/lib/pd -name "*.pd_freebsd" | ${XARGS} \
		${STRIP_CMD}

post-install:
.if ${PORT_OPTIONS:MLIBPD}
	${STRIP_CMD} ${STAGEDIR}${PREFIX}/lib/libpd.so.0.0.0
.endif

.include <bsd.port.mk>
