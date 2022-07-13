# Created by: Timothy Beyer <beyert@cs.ucr.edu>

PORTNAME=	vstplugin
PORTVERSION=	20220211
CATEGORIES=	audio
PKGNAMEPREFIX=	pd-
PKGNAMESUFFIX=	-host

MAINTAINER=	beyert@cs.ucr.edu
COMMENT=	VST plugin support for Pd

LICENSE=	BSD3CLAUSE
LICENSE_FILE=	${WRKSRC}/LICENSE.txt

ONLY_FOR_ARCHS=	amd64 i386
IGNORE_i386=	vst3sdk fails to build

HOSTDIR=	${.CURDIR}/../vstplugin-host
DESCR=	${HOSTDIR}/pkg-descr
DISTINFO_FILE=	${HOSTDIR}/distinfo
PATCHDIR=	${HOSTDIR}/files
FILESDIR=	${PATCHDIR}

OPTIONS_INCLUDE=	PD
OPTIONS_EXCLUDE=	SC

.include "${HOSTDIR}/Makefile.include.pre.mk"
.include <bsd.port.options.mk>
.include "${HOSTDIR}/Makefile.include.conditionals.mk"
# make portlint happy
# .if ${PORT_OPTIONS:MVST2}
# .endif
.include "${HOSTDIR}/Makefile.include.targets.mk"
.include <bsd.port.mk>
