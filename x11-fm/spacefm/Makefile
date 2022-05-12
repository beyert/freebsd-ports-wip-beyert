# Created by: Timothy Beyer <beyert@cs.ucr.edu>

PORTNAME=	spacefm
DISTVERSION=	20180504
CATEGORIES=	x11-fm

MAINTAINER=	beyert@cs.ucr.edu
COMMENT=	Multi-panel tabbed file and desktop manager

LICENSE=	GPLv3+
LICENSE_FILE=	${WRKSRC}/COPYING

LIB_DEPENDS=	libavutil.so:multimedia/ffmpeg \
	libffmpegthumbnailer.so:multimedia/ffmpegthumbnailer \
	libX11.so:x11/libX11 \
	libudev.so:devel/libudev-devd \
	libinotify.so:devel/libinotify \
	libstartup-notification-1.so:x11/startup-notification
RUN_DEPENDS=	bash:shells/bash
#BUILD_DEPENDS=	${LOCALBASE}/include/sys/inotify.h:devel/libinotify

FLAVORS=	gtk3 gtk2
FLAVOR?=	${FLAVORS:[1]}

USES=		desktop-file-utils gmake gnome localbase pathfix pkgconfig \
		xorg libtool shared-mime-info shebangfix gettext

gtk3_PKGNAMESUFFIX=	-gtk3
gtk2_PKGNAMESUFFIX=	-gtk2

gtk3_CONFLICTS_INSTALL=	${PORTNAME}-gtk2
gtk2_CONFLICTS_INSTALL=	${PORTNAME}-gtk3

CFLAGS+=	-fcommon

SHEBANG_FILES=	${WRKSRC}/src/spacefm-auth \
	${WRKSRC}/src/spacefm-auth.bash \

SHEBANG_FILES=	${WRKSRC}/src/spacefm-auth \
	${WRKSRC}/src/spacefm-auth.bash \
	${WRKSRC}/spacefm-installer

GNU_CONFIGURE=	yes
CONFIGURE_ARGS=	--with-bash-path=${LOCALBASE}/bin/bash \
	--sysconfdir=${PREFIX}/etc

.if ${FLAVOR:Mgtk2}
USE_GNOME=	gtk20
CONFIGURE_ARGS+=	--with-gtk2
.elif ${FLAVOR:Mgtk3}
USE_GNOME=	gtk30
CONFIGURE_ARGS+=	--with-gtk3
.endif

USE_GNOME+=	glib20 pango cairo gdkpixbuf2 intltool

USE_XORG=	x11 xcb xft xrandr xrender

USE_GITHUB=	yes
GH_ACCOUNT=	IgnorantGuru
GH_PROJECT=	spacefm
GH_TAGNAME=	e6f2918

LDFLAGS+=	-linotify

OPTIONS_DEFINE=	DOCS NLS

NLS_USES=		gettext-runtime
NLS_CONFIGURE_ENABLE=	nls

# disable until linprocfs support is fixed
#SUB_FILES=	pkg-message

.include <bsd.port.pre.mk>

post-patch:
	${REINPLACE_CMD} 's|blkcnt64_t|blkcnt_t|g' \
		${WRKSRC}/src/vfs/vfs-file-info.h
	${REINPLACE_CMD} 's|stat64|stat|g' ${WRKSRC}/src/main-window.c \
		${WRKSRC}/src/main.c ${WRKSRC}/src/cust-dialog.c \
		${WRKSRC}/src/item-prop.c ${WRKSRC}/src/mime-type/mime-type.c \
		${WRKSRC}/src/mime-type/mime-type.h \
		${WRKSRC}/src/vfs/vfs-file-info.c \
		${WRKSRC}/src/vfs/vfs-mime-type.c \
		${WRKSRC}/src/vfs/vfs-mime-type.h \
		${WRKSRC}/src/vfs/vfs-file-task.c \
		${WRKSRC}/src/vfs/vfs-volume-nohal.c \
		${WRKSRC}/src/ptk/ptk-file-browser.c \
		${WRKSRC}/src/ptk/ptk-clipboard.c \
		${WRKSRC}/src/ptk/ptk-file-archiver.c \
		${WRKSRC}/src/ptk/ptk-file-task.c \
		${WRKSRC}/src/ptk/ptk-file-misc.c \
		${WRKSRC}/src/ptk/ptk-file-properties.c
# should work, but causes a core dump
#	${REINPLACE_CMD} 's|/proc|/compat/linux/proc|g' \
#		${WRKSRC}/src/vfs/vfs-volume-nohal.c

.include <bsd.port.post.mk>
