# Created by: Timothy Beyer <beyert@cs.ucr.edu>

PORTNAME=	vstplugin
PORTVERSION=	20220211
CATEGORIES=	audio
PKGNAMEPREFIX=	pd-

MAINTAINER=	beyert@cs.ucr.edu
COMMENT=	VST plugin support for Pd (metaport)

LICENSE=	BSD3CLAUSE

HOSTDIR=	${.CURDIR}/../vstplugin-host
BRIDGEDIR=	${.CURDIR}/../vstplugin-bridge

OPTIONS_INCLUDE=	PD
OPTIONS_EXCLUDE=	SC

DESCR=	${HOSTDIR}/pkg-descr
DISTINFO_FILE=	${HOSTDIR}/distinfo

.include "${HOSTDIR}/Makefile.include.pre.mk"
.include "${BRIDGEDIR}/Makefile.include.pre.mk"

USES:=	metaport

wine_PKGNAMESUFFIX=	-wine
wine_devel_PKGNAMESUFFIX=	-wine_devel

PD_HOST_PKGBASE=	${PKGNAMEPREFIX}${PORTNAME}-host
PD_HOST_PACKAGE=	audio/${PKGNAMEPREFIX}${PORTNAME}-host
PD_BRIDGE_PKGBASE=	${PKGNAMEPREFIX}${PORTNAME}-bridge${PKGNAMESUFFIX}
PD_BRIDGE_PACKAGE=	audio/${PKGNAMEPREFIX}${PORTNAME}-bridge@${FLAVOR}

RUN_DEPENDS+=	${PD_HOST_PKGBASE}>0:${PD_HOST_PACKAGE} \
		${PD_BRIDGE_PKGBASE}>0:${PD_BRIDGE_PACKAGE}

.include <bsd.port.options.mk>
.include "${BRIDGEDIR}/Makefile.include.conditionals.mk"
# make portlint happy
# .if ${PORT_OPTIONS:MWINE} || ${PORT_OPTIONS:MWINE_DEVEL} || \
#     ${PORT_OPTIONS:MVST2}
# .endif
.include <bsd.port.mk>
