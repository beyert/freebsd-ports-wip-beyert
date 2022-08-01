# Created by: Timothy Beyer <beyert@cs.ucr.edu>

PORTNAME=	yefm
PORTVERSION=	0.2
CATEGORIES=	x11-fm

MAINTAINER=	beyert@cs.ucr.edu
COMMENT=	Simple 2 pane file manager based on Qt

LICENSE=	GPLv2
LICENSE_FILE=	${WRKSRC}/LICENSE

LIB_DEPENDS=	libinotify.so:devel/libinotify \
		libudev.so:devel/libudev-devd

USES=	compiler:c++11-lang dos2unix desktop-file-utils gl qt:5 qmake pkgconfig

USE_GL=	gl
USE_QT=	qmake_build buildtools_build core widgets gui dbus

USE_GCC=	yes

LDFLAGS+=	-linotify

OPTIONS_DEFINE=	DOCS NLS

NLS_USES=	gettext-runtime

USE_GITHUB=	yes
GH_ACCOUNT=	yede
GH_TAGNAME=	2e13f52

QMAKE_ARGS+=	MANDIR="${PREFIX}/share/man" \
		DOCDIR="${DOCSDIR}" \
		XDGDIR="${PREFIX}/etc/xdg"
QMAKE_SOURCE_PATH=	${PORTNAME}.pro

DOS2UNIX_REGEX=	.*\.(h|cpp)

.include <bsd.port.pre.mk>

# USE_GCC doesn't set this variable correctly, for an unknown reason...
COMPILER_TYPE=	gcc

.if ${CHOSEN_COMPILER_TYPE} == gcc
# Workaround for Bug#224137: devel/qt5-qmake: Doesn't use the right compiler if
# USE_GCC is selected; thank you to the maintainer of multimedia/webcamoid!
BINARY_ALIAS=	g++=${CXX} gcc=${CC}
.endif

.if ${OSREL:R} < 13
BUILD_DEPENDS+=	${LOCALBASE}/include/libepoll-shim/sys/eventfd.h:devel/libepoll-shim
CXXFLAGS+=	-I${LOCALBASE}/include/libepoll-shim
LDFLAGS+=	-lepoll-shim
.endif

post-extract:
	@${REINPLACE_CMD} 's|/usr|${PREFIX}|g' ${WRKSRC}/install.pri \
		${WRKSRC}/app-dirs.pri \
		${WRKSRC}/actionmgr/yecustomactions.cpp \
		${WRKSRC}/actionmgr/yecustomactionsdlg.cpp \
		${WRKSRC}/actionmgr/yemimeactions.cpp \
		${WRKSRC}/app/yeiconcache.cpp \
		${WRKSRC}/app/yeiconloader.cpp \
		${WRKSRC}/app/yeicontheme.cpp \
		${WRKSRC}/dialogs/yesettingsdlg.cpp \
		${WRKSRC}/global/yefileutils.cpp \
		${WRKSRC}/global/yemime.cpp \
		${WRKSRC}/mimedlg/yemimemodel.cpp \
		${WRKSRC}/mimetypes/inqt5/qstandardpaths_unix.cpp \
		${WRKSRC}/mimetypes/qmimedatabase.cpp
	@${REINPLACE_CMD} 's|gnu_dev_||g' ${WRKSRC}/udev/yeudevnode.cpp
	@${REINPLACE_CMD} -e 's|vfs.h|mount.h|g' \
		${WRKSRC}/global/yefileutils.cpp ${WRKSRC}/global/yeglobal.cpp
	@${REINPLACE_CMD} 's|/proc|/compat/linux/proc|g' \
		${WRKSRC}/udev/yeudevmonitor.cpp

.include <bsd.port.post.mk>
