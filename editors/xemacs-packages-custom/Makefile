# Created by: Michael Elbel (me@FreeBSD.org)

PORTNAME=	xemacs-packages
PORTVERSION=	14.2
CATEGORIES=	editors elisp
MASTER_SITES=	${MASTER_SITE_XEMACS}
MASTER_SITE_SUBDIR=	packages
PKGNAMESUFFIX=	-custom
#		apel-1.36-pkg.tar.gz
#		auctex-1.58-pkg.tar.gz
#		bbdb-1.34-pkg.tar.gz
#		c-support-1.24-pkg.tar.gz
DISTFILES=	\
		Sun-1.16-pkg.tar.gz \
		ada-1.14-pkg.tar.gz \
		apel-1.32-pkg.tar.gz \
		auctex-1.47-pkg.tar.gz \
		bbdb-1.32-pkg.tar.gz \
		build-1.14-pkg.tar.gz \
		c-support-1.22-pkg.tar.gz \
		calc-1.26-pkg.tar.gz \
		calendar-1.32-pkg.tar.gz \
		cc-mode-1.45-pkg.tar.gz \
		clearcase-1.10-pkg.tar.gz \
		cookie-1.15-pkg.tar.gz \
		crisp-1.15-pkg.tar.gz \
		debug-1.18-pkg.tar.gz \
		dictionary-1.16-pkg.tar.gz \
		dired-1.17-pkg.tar.gz \
		docbookide-0.08-pkg.tar.gz \
		ecb-1.22-pkg.tar.gz \
		ecrypto-0.20-pkg.tar.gz \
		edebug-1.21-pkg.tar.gz \
		ediff-1.68-pkg.tar.gz \
		edit-utils-2.37-pkg.tar.gz \
		edt-1.13-pkg.tar.gz \
		efs-1.33-pkg.tar.gz \
		eieio-1.05-pkg.tar.gz \
		elib-1.11-pkg.tar.gz \
		emerge-1.11-pkg.tar.gz \
		erc-0.21-pkg.tar.gz \
		escreen-1.01-pkg.tar.gz \
		eshell-1.10-pkg.tar.gz \
		eterm-1.17-pkg.tar.gz \
		eudc-1.39-pkg.tar.gz \
		footnote-1.16-pkg.tar.gz \
		forms-1.15-pkg.tar.gz \
		fortran-modes-1.05-pkg.tar.gz \
		frame-icon-1.11-pkg.tar.gz \
		fsf-compat-1.15-pkg.tar.gz \
		games-1.17-pkg.tar.gz \
		general-docs-1.04-pkg.tar.gz \
		gnats-1.17-pkg.tar.gz \
		gnus-1.91-pkg.tar.gz \
		haskell-mode-1.08-pkg.tar.gz \
		hm--html-menus-1.23-pkg.tar.gz \
		hyperbole-1.16-pkg.tar.gz \
		ibuffer-1.09-pkg.tar.gz \
		idlwave-1.32-pkg.tar.gz \
		igrep-1.14-pkg.tar.gz \
		ilisp-1.33-pkg.tar.gz \
		ispell-1.32-pkg.tar.gz \
		jde-1.51-pkg.tar.gz \
		mail-lib-1.79-pkg.tar.gz \
		mailcrypt-2.14-pkg.tar.gz \
		mew-1.19-pkg.tar.gz \
		mh-e-1.29-pkg.tar.gz \
		mine-1.16-pkg.tar.gz \
		misc-games-1.19-pkg.tar.gz \
		mmm-mode-1.02-pkg.tar.gz \
		net-utils-1.52-pkg.tar.gz \
		ocaml-0.05-pkg.tar.gz \
		oo-browser-1.04-pkg.tar.gz \
		os-utils-1.37-pkg.tar.gz \
		pc-1.28-pkg.tar.gz \
		pcl-cvs-1.66-pkg.tar.gz \
		pcomplete-1.04-pkg.tar.gz \
		perl-modes-1.09-pkg.tar.gz \
		pgg-1.06-pkg.tar.gz \
		prog-modes-2.10-pkg.tar.gz \
		ps-print-1.11-pkg.tar.gz \
		psgml-1.44-pkg.tar.gz \
		psgml-dtds-1.03-pkg.tar.gz \
		python-modes-1.07-pkg.tar.gz \
		reftex-1.34-pkg.tar.gz \
		re-builder-1.05-pkg.tar.gz \
		riece-1.23-pkg.tar.gz \
		rmail-1.14-pkg.tar.gz \
		ruby-modes-1.02-pkg.tar.gz \
		sasl-1.16-pkg.tar.gz \
		scheme-1.15-pkg.tar.gz \
		semantic-1.20-pkg.tar.gz \
		sgml-1.11-pkg.tar.gz \
		sh-script-1.22-pkg.tar.gz \
		sieve-1.18-pkg.tar.gz \
		slider-1.15-pkg.tar.gz \
		sml-mode-0.12-pkg.tar.gz \
		sounds-au-1.12-pkg.tar.gz \
		sounds-wav-1.12-pkg.tar.gz \
		speedbar-1.28-pkg.tar.gz \
		strokes-1.10-pkg.tar.gz \
		supercite-1.21-pkg.tar.gz \
		texinfo-1.30-pkg.tar.gz \
		text-modes-1.90-pkg.tar.gz \
		textools-1.15-pkg.tar.gz \
		time-1.14-pkg.tar.gz \
		tm-1.38-pkg.tar.gz \
		tooltalk-1.15-pkg.tar.gz \
		tpu-1.14-pkg.tar.gz \
		tramp-1.37-pkg.tar.gz \
		vc-1.41-pkg.tar.gz \
		vc-cc-1.22-pkg.tar.gz \
		vhdl-1.21-pkg.tar.gz \
		view-process-1.13-pkg.tar.gz \
		viper-1.55-pkg.tar.gz \
		vm-7.22-pkg.tar.gz \
		w3-1.32-pkg.tar.gz \
		x-symbol-1.10-pkg.tar.gz \
		xemacs-base-2.10-pkg.tar.gz \
		xemacs-devel-1.72-pkg.tar.gz \
		xetla-1.01-pkg.tar.gz \
		xlib-1.14-pkg.tar.gz \
		xslide-1.09-pkg.tar.gz \
		xslt-process-1.12-pkg.tar.gz \
		xwem-1.22-pkg.tar.gz \
		zenirc-1.16-pkg.tar.gz
DIST_SUBDIR=	xemacs

MAINTAINER=	ports@FreeBSD.org
COMMENT=	Basic XEmacs elisp packages(xemacs-packages)

LICENSE=	GPLv2

NO_BUILD=	yes
WRKSRC=	${WRKDIR}/${PACKAGES_SUBDIR}

XEMACSDIR=	${PREFIX}/lib/xemacs
PACKAGES_SUBDIR=	xemacs-packages

FIXME=	gnus/binhex.elc gnus/uudecode.elc

do-extract:
	@${MKDIR} ${WRKSRC}
.for f in ${DISTFILES}
	-@${EXTRACT_CMD} ${EXTRACT_BEFORE_ARGS} ${DISTDIR}/${DIST_SUBDIR}/${f} \
		${EXTRACT_AFTER_ARGS} -C ${WRKSRC}
.endfor

post-patch:
	cd ${WRKSRC}/lisp; ${RM} ${FIXME}
	${FIND} ${WRKSRC} -name \*.orig -exec ${RM} -f \{} \;

do-install:
	${MKDIR} ${STAGEDIR}${XEMACSDIR}/${PACKAGES_SUBDIR}
	(cd ${WRKSRC} && ${COPYTREE_SHARE} \* ${STAGEDIR}${XEMACSDIR}/${PACKAGES_SUBDIR})

post-install:
	@${ECHO_MSG} "    This port installs packages for XEmacs. These packages should be sufficient"
	@${ECHO_MSG} "for common XEmacs functionality. If you are a non-Latin XEmacs user, installing"
	@${ECHO_MSG} "the xemacs-mule-packages port instead is recommended."
	@${ECHO_MSG} "    You can also install these packages by running XEmacs as root and using the"
	@${ECHO_MSG} "'Manage Packages' menu within the 'Options' menu of the menubar."
	@${ECHO_MSG} "However, installing the packages using this method defeats the purpose of"
	@${ECHO_MSG} "installing this port."

.include <bsd.port.mk>
