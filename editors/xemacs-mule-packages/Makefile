# Created by: KIRIYAMA Kazuhiko <kiri@pis.toba-cmt.ac.jp>

PORTNAME=	xemacs-mule-packages
PORTVERSION=	4.6
CATEGORIES=	editors elisp
MASTER_SITES=	${MASTER_SITE_XEMACS:S|%SUBDIR%|packages|}
DISTFILES=	\
		edict-1.16-pkg.tar.gz \
		egg-its-1.27-pkg.tar.gz \
		latin-euro-standards-1.07-pkg.tar.gz \
		latin-unity-1.20-pkg.tar.gz \
		leim-1.24-pkg.tar.gz \
		locale-1.24-pkg.tar.gz \
		lookup-1.15-pkg.tar.gz \
		mule-base-1.49-pkg.tar.gz \
		mule-ucs-1.14-pkg.tar.gz \
		skk-1.23-pkg.tar.gz
DIST_SUBDIR=	xemacs

MAINTAINER=	ports@FreeBSD.org
COMMENT=	XEmacs elisp packages for Mule(mule-packages)

LICENSE=	GPLv2

NO_BUILD=	yes
WRKSRC=		${WRKDIR}/${PACKAGES_SUBDIR}

XEMACSDIR=	${PREFIX}/lib/xemacs
PACKAGES_SUBDIR=	mule-packages

do-extract:
	@${MKDIR} ${WRKSRC}
.for f in ${DISTFILES}
	-@${EXTRACT_CMD} ${EXTRACT_BEFORE_ARGS} ${DISTDIR}/${DIST_SUBDIR}/${f} \
		${EXTRACT_AFTER_ARGS} -C ${WRKSRC}
.endfor

do-install:
	${MKDIR} ${STAGEDIR}${XEMACSDIR}
	${CP} -R ${WRKSRC} ${STAGEDIR}${XEMACSDIR}

post-install:
	@${ECHO_MSG} "    This port installs packages for XEmacs with mule. These packages should be"
	@${ECHO_MSG} "installed altogether with xemacs-packages."
	@${ECHO_MSG} "    You can also install these packages by running XEmacs as root and using the"
	@${ECHO_MSG} "'Manage Packages' menu within the 'Options' menu of the menubar."
	@${ECHO_MSG} "However, installing the packages using this method defeats the purpose of"
	@${ECHO_MSG} "installing this port."

.include <bsd.port.mk>
