# Created by: Timothy Beyer <beyert@cs.ucr.edu>

PORTNAME=	yefm
DISTVERSION=	0.2
CATEGORIES=	x11-fm

MAINTAINER=	beyert@cs.ucr.edu
COMMENT=	Simple 2 pane file manager based on Qt

LICENSE=	GPLv2
LICENSE_FILE=	${WRKSRC}/LICENSE

LIB_DEPENDS=	libinotify.so:devel/libinotify \
	libudev.so:devel/libudev-devd

USES=	compiler:c++11-lang dos2unix desktop-file-utils gl qt:5 qmake

LDFLAGS+=	-linotify

OPTIONS_DEFINE=	DOCS NLS

NLS_USES=	gettext-runtime

USE_GITHUB=	yes
GH_ACCOUNT=	yede
GH_TAGNAME=	2e13f52

USE_GCC=	yes

QMAKE_ARGS=	MANDIR=${PREFIX}/share/man \
		PREFIX=${PREFIX} \
		XDGDIR=${PREFIX}/etc/xdg \
		DOCDIR=${DOCSDIR} ${PORTNAME}.pro

DOS2UNIX_REGEX=	.*\.(h|cpp)
USE_GL=	gl
USE_QT=	concurrent core dbus gui widgets buildtools_build qmake_build

post-extract:
	${REINPLACE_CMD} 's|/usr|${PREFIX}|g' ${WRKSRC}/install.pri \
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
	${REINPLACE_CMD} 's|gnu_dev_||g' ${WRKSRC}/udev/yeudevnode.cpp
	${REINPLACE_CMD} -e 's|vfs.h|mount.h|g' \
		${WRKSRC}/global/yefileutils.cpp ${WRKSRC}/global/yeglobal.cpp
	${REINPLACE_CMD} 's|/proc|/compat/linux/proc|g' \
		${WRKSRC}/udev/yeudevmonitor.cpp

.include <bsd.port.mk>
