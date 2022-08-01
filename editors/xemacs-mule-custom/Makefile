# Created by: KIRIYAMA Kazuhiko<kiri@pis.toba-cmt.ac.jp>

PORTNAME=	xemacs
PORTVERSION=	${XEMACS_VER}
PORTREVISION=	13
CATEGORIES=	editors
MASTER_SITES=	${MASTER_SITE_XEMACS}
MASTER_SITE_SUBDIR=	${PORTNAME}-${XEMACS_REL}
PKGNAMESUFFIX=	-mule-custom
DIST_SUBDIR=	${PORTNAME}

MAINTAINER=	beyert@cs.ucr.edu
COMMENT=	XEmacs (stable version) text editor with mule (Only the executables)

LICENSE=	GPLv2
LICENSE_FILE=	${WRKSRC}/COPYING

BUILD_DEPENDS=	${LOCALBASE}/lib/xemacs/mule-packages/pkginfo/MANIFEST.mule-base:editors/xemacs-mule-packages \
	autoconf2.13:devel/autoconf2.13
LIB_DEPENDS=	libpng16.so:graphics/png \
	libldap.so:net/openldap26-client \
	libaudio.so:audio/nas \
	libtiff.so:graphics/tiff \
	libcompface.so:mail/faces \
	libpq.so:databases/postgresql13-client
RUN_DEPENDS=	${LOCALBASE}/lib/xemacs/mule-packages/pkginfo/MANIFEST.mule-base:editors/xemacs-mule-packages

FLAVORS=	mule cannafreewnn cannawnn6 freewnn wnn6 canna
cannafreewnn_PKGNAMESUFFIX=	-canna+freewnn
cannafreewnn_DESCR=	${.CURDIR}/pkg-descr.ja
cannawnn6_PKGNAMESUFFIX=	-canna+wnn6
cannawnn6_DESCR=	${.CURDIR}/pkg-descr.ja
freewnn_PKGNAMESUFFIX=	-freewnn
freewnn_DESCR=	${.CURDIR}/pkg-descr.ja
wnn6_PKGNAMESUFFIX=	-wnn6
wnn6_DESCR=	${.CURDIR}/pkg-descr.ja
canna_PKGNAMESUFFIX=	-canna
canna_DESCR=	${.CURDIR}/pkg-descr.ja

USES=	jpeg xorg ncurses jpeg gettext-runtime pgsql makeinfo

CONFLICTS=	xemacs xemacs-devel xemacs-devel-mule

SSP_UNSAFE=	yes

XEMACS_REL=	21.4
XEMACS_VER=	${XEMACS_REL}.22
XEMACS_ARCH=	${CONFIGURE_TARGET}

OPTIONS_DEFINE=	NLS

NLS_USES=	gettext
# works, but now CLANG does as well...
#USE_GCC=	yes
USE_XORG=	xpm xbitmaps xaw xmu xt xext x11 sm ice xau
STRIP=
CONFIGURE_TARGET=${MACHINE_ARCH}--freebsd
CFLAGS+=	-I${LOCALBASE}/include/libpng16 -fcommon
LDFLAGS+=	-z muldefs
CC=	clang

# these two can be set in make.conf
WITHOUT_MOTIF=	yes
WITH_XAW3D=	yes

CONFIGURE_ENV=	CC="${CC}"
GNU_CONFIGURE=	yes
CONFIGURE_ARGS=	--with-x11 \
	--with-mule \
	--with-site-lisp \
	--site-libraries='${SITE_LIBRARIES}' \
	--site-includes='${SITE_INCLUDES}' \
	--with-xface \
	--with-sound=native \
	--with-pop \
	--with-xfs \
	--with-jpeg \
	--without-png \
	--with-tiff \
	--with-xpm \
	--infopath=${LOCALBASE}/lib/xemacs/info:${LOCALBASE}/info:/usr/info:${LOCALBASE}/lib/texmf/doc/info:/usr/lib/texmf/doc:/usr/share/info \
	--with-clash-detection \
	--with-database=berkdb \
	${WITH_XIM} \
	${WITH_MENUBARS} ${WITH_SCROLLBARS} \
	${WITH_DIALOGS} ${WITH_WIDGETS}
INFO_PATH=	lib/xemacs-${XEMACS_VER}/info
MAKE_ARGS=	prefix=${STAGEDIR}${PREFIX}
ALL_TARGET=	all dist
.if ${FLAVOR:U} == cannafreewnn || ${FLAVOR:U} == cannawnn6 || \
	${FLAVOR:U} == freewnn || ${FLAVOR:U} == wnn6 || ${FLAVOR:U} == canna
INSTALL_TARGET=	install-arch-dep
#.else
##MAN1=	ctags.1 etags.1 gnuattach.1 gnuclient.1 gnudoit.1 \
##	gnuserv.1 xemacs.1
.endif

.if defined(WITH_GTK)
CONFIGURE_ARGS+=	--with-gtk
USE_GNOME+=	gtk12
.endif

PKGDIR=	${.CURDIR}/../../editors/xemacs-mule-custom

PLIST_SUB=	XEMACS_VER=${XEMACS_VER} XEMACS_ARCH=${XEMACS_ARCH}

.include <bsd.port.options.mk>

# Undump and malloc do not behave on amd64 at the moment
.if ${ARCH} == "amd64"
CONFIGURE_ARGS+=	--with-system-malloc --pdump
PLIST_SUB+=	PDUMP=""
.else
PLIST_SUB+=	PDUMP="@comment "
.endif

pre-fetch:
.if !defined(WITH_GTK)
	@${ECHO_MSG} "If you want to use GTK, please set the environment variable WITH_GTK and recompile."
.endif
.if !defined(WITHOUT_MOTIF)
.if !defined(MOTIF_STATIC)
	@${ECHO_MSG} ""
	@${ECHO_MSG} "If your MOTIF library is actually lesstif, you might occasionally"
	@${ECHO_MSG} "experience locked-up frames."
	@${ECHO_MSG} "In this case, set the environment variable MOTIF_STATIC and recompile, "
	@${ECHO_MSG} "which will force the use of athena widgets for dialogs."
.endif
USES+=	motif

# hack to avoid shipping binaries linked with Motif
.if defined(MOTIF_STATIC)
WITH_DIALOGS=	--with-dialogs=athena
.else
WITH_DIALOGS=	--with-dialogs=motif
.endif

.if defined(PACKAGE_BUILDING)
CONFIGURE_ARGS+=	--with-offix=no
.endif
WITH_MENUBARS?=	--with-menubars=lucid
WITH_SCROLLBARS?=	-with-scrollbars=motif
WITH_WIDGETS?=	--with-widgets=motif
.endif
WITH_XIM?=	--with-xim=xlib
WITH_MENUBARS?=	--with-menubars=athena
#WITH_SCROLLBARS?=	--with-scrollbars=athena
# I prefer lucid over athena scrollbars...
WITH_SCROLLBARS?=	--with-scrollbars=lucid
WITH_DIALOGS?=	--with-dialogs=athena
WITH_WIDGETS?=	--with-widgets=athena

.if defined(WITH_XAW3D)
LIB_DEPENDS+=	libXaw3d.so:x11-toolkits/Xaw3d
CONFIGURE_ARGS+=	--with-athena=3d
.else
CONFIGURE_ARGS+=	--with-athena=xaw
.endif

BINNAMEEXT=	-mule
.if ${FLAVOR:U} == cannafreewnn
CONFIGURE_ARGS+=	--with-canna --with-wnn --with-wnn6=no
LIB_DEPENDS+=	libcanna.so:japanese/canna-lib \
	libwnn.so:japanese/FreeWnn-lib
PLIST_SUB+=	CANNA=""
.elif ${FLAVOR:U} == cannawnn6
SITE_INCLUDES=	${LOCALBASE}/include/wnn6
CONFIGURE_ARGS+=	--with-canna --with-wnn6
LIB_DEPENDS+=	libcanna.so:japanese/canna-lib \
	libwnn6.so:japanese/Wnn6-lib
PLIST_SUB+=	CANNA=""
.elif ${FLAVOR:U} == freewnn
CONFIGURE_ARGS+=	--with-wnn --with-canna=no --with-wnn6=no
LIB_DEPENDS+=	libwnn.so:japanese/FreeWnn-lib
.elif ${FLAVOR:U} == wnn6
SITE_INCLUDES=	${LOCALBASE}/include/wnn6
CONFIGURE_ARGS+=	--with-wnn6 --with-canna=no
LIB_DEPENDS+=	libwnn6.so:japanese/Wnn6-lib
.elif ${FLAVOR:U} == canna
CONFIGURE_ARGS+=	--with-canna --with-wnn=no --with-wnn6=no
LIB_DEPENDS+=	libcanna.so:japanese/canna-lib
PLIST_SUB+=	CANNA=""
.else
CONFIGURE_ARGS+=	--with-canna=no --with-wnn=no --with-wnn6=no
PLIST_SUB+=	CANNA="@comment "
.endif
SITE_INCLUDES+=	${LOCALBASE}/include
SITE_LIBRARIES+=	${LOCALBASE}/lib
# fix .so references in a few man pages
pre-configure::
.for f in etc/ctags.1 etc/gnuattach.1 etc/gnuclient.1 etc/gnudoit.1
	@${SED} -e 's/\.1/&.gz/' ${WRKSRC}/${f} > ${WRKDIR}/tmp_zot
	@${MV} ${WRKDIR}/tmp_zot ${WRKSRC}/${f}
.endfor
	@${REINPLACE_CMD} -e 's/^mandir=@mandir@/mandir=@mandir@\/man1/' \
	${WRKSRC}/Makefile.in.in
	(cd ${WRKSRC} && ${LOCALBASE}/bin/autoconf2.13)

pre-build:
	@${FIND} ${WRKSRC} \( -name \*.orig -o -name \*~ \) -exec ${RM} -f \{} \;
	@${RM} -f ${WRKSRC}/lib-src/DOC* ${WRKSRC}/src/xemacs
#.if [ -f ${WRKSRC}/man/xemacs-faq.texi.new ]; then
#	@iconv -c -f ISO-8859-1 -t UTF8 ${WRKSRC}/man/xemacs-faq.texi > ${WRKSRC}/man/xemacs-faq.texi.new
#	@${REINPLACE_CMD} 's|iso-2022-8|utf-8|g'${WRKSRC}/man/xemacs-faq.texi.new
#	@${CP} ${WRKSRC}/man/xemacs-faq.texi.new ${WRKSRC}/man/xemacs-faq.texi
#.endif

post-install::
.for f in b2m ctags ellcc etags gnuclient xemacs-${XEMACS_VER}
	${STRIP_CMD} ${STAGEDIR}${PREFIX}/bin/${f}
.endfor
.for f in ctags etags
	${MV} ${STAGEDIR}${PREFIX}/bin/${f} ${STAGEDIR}${PREFIX}/bin/${f}-xemacs
.endfor
	${MKDIR} ${STAGEDIR}${PREFIX}/${INFO_PATH}
	${CP} ${WRKSRC}/info/* ${STAGEDIR}${PREFIX}/${INFO_PATH}/
# For some reason install no longer makes ${PREFIX}/lib/xemacs/site-lisp.
# Do what PLIST does for pkg_add.
	${MKDIR} ${STAGEDIR}${PREFIX}/lib/xemacs/site-lisp
#	${CHMOD} 755 ${STAGEDIR}${PREFIX}/lib/xemacs/site-lisp
.for f in etc info man pkginfo
	${MKDIR} ${STAGEDIR}${PREFIX}/lib/xemacs/mule-packages/${f}
	${MKDIR} ${STAGEDIR}${PREFIX}/lib/xemacs/site-packages/${f}
	${MKDIR} ${STAGEDIR}${PREFIX}/lib/xemacs/xemacs-packages/${f}
.endfor
	${MKDIR} ${STAGEDIR}${PREFIX}/lib/xemacs/site-packages/lisp
	${RM} -f ${STAGEDIR}${PREFIX}/bin/send-pr
.if defined(WITH_GTK)
	@${ECHO_MSG} "Please be aware that GTK support is buggy. Do not report bugs to"
	@${ECHO_MSG} "the maintainer."
	@${ECHO_MSG} "Please also be aware that the package's name was automagically changed"
	@${ECHO_MSG} "to ${PORTNAME}${PKGNAMESUFFIX}-${XEMACS_VER}."
.endif
.if ${FLAVOR:U} == cannafreewnn || ${FLAVOR:U} == cannawnn6 || \
	${FLAVOR:U} == freewnn || ${FLAVOR:U} == wnn6 || ${FLAVOR:U} == canna
#	@${MKDIR} ${PREFIX}/man/ja/man1
#	@${INSTALL_MAN} ${WRKSRC}/etc/xemacs-ja.1 ${STAGEDIR}${PREFIX}/man/ja/man1/xemacs.1
	@${LN} -sf ja ${STAGEDIR}${PREFIX}/lib/xemacs/mule-packages/etc/app-defaults/ja_JP.eucJP
.endif

.include <bsd.port.mk>
