# Created by: Timothy Beyer <beyert@cs.ucr.edu>

PORTNAME=	vstplugin
PORTVERSION=	20220211
CATEGORIES=	audio
PKGNAMEPREFIX=	sc3-
PKGNAMESUFFIX=	-bridge

MAINTAINER=	beyert@cs.ucr.edu
COMMENT=	Windows VST plugin support for SuperCollider via Wine

LICENSE=	BSD3CLAUSE
LICENSE_FILE=	${WRKSRC}/LICENSE.txt

HOSTDIR=	${.CURDIR}/../vstplugin-host
DESCR=	${HOSTDIR}/pkg-descr
DISTINFO_FILE=	${HOSTDIR}/distinfo
PATCHDIR=	${HOSTDIR}/files
FILESDIR=	${PATCHDIR}
BRIDGEDIR=	${.CURDIR}/../vstplugin-bridge
PLIST=	${BRIDGEDIR}/pkg-plist

OPTIONS_INCLUDE=	SC
OPTIONS_EXCLUDE=	PD

.include "${HOSTDIR}/Makefile.include.pre.mk"
.include "${BRIDGEDIR}/Makefile.include.pre.mk"
.include "${BRIDGEDIR}/Makefile.include.post.mk"
.include <bsd.port.options.mk>
.include "${BRIDGEDIR}/Makefile.include.conditionals.mk"
.include "${HOSTDIR}/Makefile.include.conditionals.mk"
.include "${HOSTDIR}/Makefile.include.targets.mk"
# make portlint happy
# .if ${PORT_OPTIONS:MWINE} || ${PORT_OPTIONS:MWINE_DEVEL} || \
#     ${PORT_OPTIONS:MVST2}
# .endif
.include <bsd.port.mk>
