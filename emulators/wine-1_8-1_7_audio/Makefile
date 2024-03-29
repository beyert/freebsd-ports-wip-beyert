# Created by: Gerald Pfeifer <gerald@FreeBSD.org>
# $FreeBSD: head/emulators/wine/Makefile 423499 2016-10-08 09:17:22Z gerald $

PORTNAME=	wine
DISTVERSION=	1.8.5
PORTREVISION=	2
PORTEPOCH=	1
CATEGORIES=	emulators
MASTER_SITES=	SF/${PORTNAME}/Source \
		http://ibiblio.org/pub/linux/system/emulators/wine/
PKGNAMESUFFIX?=	-1_8
DISTFILES?=	${DISTNAME}${EXTRACT_SUFX} ${PORTNAME}-5.0.2.tar.xz

MAINTAINER?=	gerald@FreeBSD.org
COMMENT?=	Microsoft Windows compatibility environment

LICENSE=	LGPL21 LGPL3
LICENSE_COMB=	dual
LICENSE_FILE=	${WRKSRC}/LICENSE

BUILD_DEPENDS=	${LOCALBASE}/bin/flex:textproc/flex
LIB_DEPENDS=	libxml2.so:textproc/libxml2

INSTALLDIR=	${PREFIX}/${PKGBASE}
DOCSDIR=	${INSTALLDIR}/share/doc/${PORTNAME}
DESKTOPDIR=	${INSTALLDIR}/share/applications
DATADIR=	${INSTALLDIR}/share/${PORTNAME}
WINEDATADIR=	${PREFIX}/share/${PORTNAME}
#ETCDIR=	${INSTALLDIR}/etc/${PORTNAME}
ETCDIR=		${PREFIX}/etc/${PKGBASE}
#EXAMPLESDIR=	${INSTALLDIR}/share/examples/${PORTNAME}
EXAMPLESDIR=	${PREFIX}/share/examples/${PKGBASE}
#WWWDIR=	${INSTALLDIR}/www/${PORTNAME}
WWWDIR=		${PREFIX}/www/${PKGBASE}

CONFLICTS_INSTALL=	wine-staging-[0-9]* wine-devel-[0-9]* i386-wine-[0-9]* \
			i386-wine-staging-[0-9]* i386-wine-devel-[0-9]*

CPPFLAGS+=	-I${LOCALBASE}/include
LDFLAGS+=	-L${LOCALBASE}/lib
GNU_CONFIGURE=	yes
GNU_CONFIGURE_PREFIX=	${INSTALLDIR}
MANPREFIX=	${INSTALLDIR}
GNU_CONFIGURE_MANPREFIX=	${INSTALLDIR}
#		--prefix=${INSTALLDIR} --exec-prefix=${INSTALLDIR} \
#		--libdir=${WINELIBDIR} \
#		--bindir=${INSTALLDIR}/bin \
#		--datarootdir=${INSTALLDIR}/share \
#		--includedir=${INSTALLDIR}/include
CONFIGURE_ARGS+=--verbose --disable-tests \
		--without-alsa --without-capi --without-dbus \
		--without-gettext --without-gettextpo \
		--without-gphoto --without-gsm --without-gstreamer \
		--without-opencl \
		--without-osmesa \
		--with-oss \
		--without-sane \
		--without-tiff

CONFIGURE_ENV=	CPPBIN="${CPP}" FLEX="${LOCALBASE}/bin/flex"
WINELIBDIR?=	${INSTALLDIR}/lib
.if !defined(USE_LDCONFIG32)
USE_LDCONFIG=	${WINELIBDIR}
.endif
ONLY_FOR_ARCHS=	i386 amd64
USES=		bison compiler:c11 desktop-file-utils gmake shebangfix tar:bzip2
SHEBANG_FILES=	tools/make_requests tools/winemaker/winemaker \
		tools/winedump/function_grep.pl

MAKE_JOBS_UNSAFE=yes

SUB_FILES=	pkg-message
PKGMESSAGE=	${WRKDIR}/pkg-message

PORTDATA=	l_intl.nls wine.inf

OPTIONS_DEFINE=	CUPS DOCS DOSBOX GNUTLS HAL LDAP LIBXSLT MPG123 OPENAL V4L WINEMAKER X11 GECKO MONO
OPTIONS_DEFAULT=DOSBOX GNUTLS V4L WINEMAKER X11 GECKO
OPTIONS_SUB=	yes

DOSBOX_DESC=	Use DOSBox to run MS-DOS programs
LIBXSLT_DESC=	Use libxslt (only used by msxml3.dll)
WINEMAKER_DESC=	Fully support winemaker (requires Perl)
GECKO_DESC=	Bundle Gecko MSI package for Wine
MONO_DESC=	Bundle Mono MSI package for Wine

PORTSCOUT=	limitw:1,even

CUPS_CONFIGURE_WITH=	cups
CUPS_LIB_DEPENDS=	libcups.so:print/cups

DOSBOX_RUN_DEPENDS=	dosbox:emulators/dosbox

GECKO_RUN_DEPENDS=	${WINEDATADIR}/gecko/wine-gecko-2.47.1-x86.msi:emulators/wine-gecko


GNUTLS_CONFIGURE_WITH=	gnutls
GNUTLS_LIB_DEPENDS=	libgnutls.so:security/gnutls

HAL_CONFIGURE_WITH=	hal
HAL_LIB_DEPENDS=	libhal.so:sysutils/hal

LDAP_CONFIGURE_WITH=	ldap
LDAP_USE=		OPENLDAP=yes

LIBXSLT_CONFIGURE_WITH=	xslt
LIBXSLT_LIB_DEPENDS=	libxslt.so:textproc/libxslt

MONO_RUN_DEPENDS=	${WINEDATADIR}/mono/wine-mono-4.5.6.msi:emulators/wine-mono

MPG123_CONFIGURE_WITH=	mpg123
MPG123_LIB_DEPENDS=	libmpg123.so:audio/mpg123

OPENAL_CONFIGURE_WITH=	openal
OPENAL_USES=		openal

V4L_CONFIGURE_WITH=	v4l
V4L_LIB_DEPENDS=	libv4l1.so:multimedia/libv4l

WINEMAKER_RUN_DEPENDS=	p5-XML-LibXML>0:textproc/p5-XML-LibXML

X11_CONFIGURE_WITH=	x cms fontconfig freetype glu jpeg opengl png xinerama xinput2 xrandr xrender
X11_USES=		jpeg
X11_USE=		GL=glu XORG=xcomposite,xcursor,xi,xinerama,xrandr,xrender
X11_LIB_DEPENDS=	libfontconfig.so:x11-fonts/fontconfig \
			libfreetype.so:print/freetype2 \
			liblcms2.so:graphics/lcms2 \
			libpng.so:graphics/png

.include <bsd.port.pre.mk>

.if ${ARCH} == amd64
# Wine is composed of three parts:
#  - wine (aka this port) is the 32-bit component and runs 32-bit programs (on FreeBSD/i386)
#  - wine64 (aka this part of this port) is the 64-bit component and runs 64-bit programs
#    (on FreeBSD/amd64)
#  - wow64 (a subset of emulators/i386-wine-devel) is a part of the 64-bit component that runs
#    32-bit programs (on FreeBSD/amd64)
# We also currently have:
#  - "wine32" (aka emulators/i386-wine-devel) is the 32-bit component and runs 32-bit programs
#    (on FreeBSD/amd64).  This will be superseded by wow64.

# --libdir is required since Wine defaults to "${PREFIX}/lib64" on amd64.
#CONFIGURE_ARGS+=	--enable-win64 --libdir=${INSTALLDIR}/lib
CONFIGURE_ARGS+=	--enable-win64 --libdir=${WINELIBDIR}
PLIST_SUB+=		WINE32="@comment " WINE64=""

# Force the use of GCC where it is the system compiler since
# COMPILER_VERSION will be 42 (the GCC version) even if clang
# is CHOSEN_COMPILER_TYPE in that case.
.if ${OPSYS} == FreeBSD && ${OSVERSION} < 1000054
USE_GCC=		yes
.else
. if ${CHOSEN_COMPILER_TYPE} == clang && ${COMPILER_VERSION} < 38
CPPFLAGS+=		-D__builtin_ms_va_list=__builtin_va_list \
			-D__builtin_ms_va_start=__builtin_va_start \
			-D__builtin_ms_va_end=__builtin_va_end \
			-D__builtin_ms_va_copy=__builtin_va_copy
. endif
.endif

# Wine assumes a WoW64 package is available however WoW64 is not yet available on FreeBSD.
post-patch:
	${REINPLACE_CMD} 's|/wine|/wine64|g' ${WRKSRC}/tools/wineapploader.in

.else
PLIST_SUB+=		WINE32="" WINE64="@comment "
.endif

PLIST_SUB+=	PKGBASE="${PKGBASE}"

TTF_OVERRIDES=	courier.ttf fixedsys.ttf ms_sans_serif.ttf small_fonts.ttf small_fonts_jp.ttf

pre-build:
.for ttf in ${TTF_OVERRIDES}
	${CP} -p ${WRKDIR}/${PORTNAME}-5.0.2/fonts/${ttf} ${WRKSRC}/fonts/${ttf}
.endfor
	cd ${WRKSRC} && ${MAKE_CMD} depend

pre-install:
	@${MKDIR} ${STAGEDIR}${WINELIBDIR}
	@${MKDIR} ${STAGEDIR}${DOCSDIR}
	@${MKDIR} ${STAGEDIR}${DESKTOPDIR}
	@${MKDIR} ${STAGEDIR}${DATADIR}
#INSTALLDIR=     ${PREFIX}/${PKGBASE}

post-install:
	@${MV} -f ${STAGEDIR}${WINELIBDIR}/libwine.so.1.0 \
	          ${STAGEDIR}${WINELIBDIR}/libwine.so.1
	@${LN} -sf libwine.so.1 ${STAGEDIR}/${WINELIBDIR}/libwine.so
	@${MKDIR} ${STAGEDIR}${DOCSDIR}
.for i in README ANNOUNCE AUTHORS
	${INSTALL_DATA} ${WRKSRC}/${i} ${STAGEDIR}${DOCSDIR}
.endfor
	${INSTALL_DATA} ${WRKSRC}/programs/winedbg/README ${STAGEDIR}${DOCSDIR}/README.winedbg
	${INSTALL_DATA} ${WRKSRC}/tools/winedump/README ${STAGEDIR}${DOCSDIR}/README.winedump

.include <bsd.port.post.mk>
