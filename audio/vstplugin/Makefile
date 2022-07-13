# Created by: Timothy Beyer <beyert@cs.ucr.edu>

PORTNAME=	vstplugin
PORTVERSION=	20220211
CATEGORIES=	audio

MAINTAINER=	beyert@cs.ucr.edu
COMMENT=	VST plugin support for Pd and SuperCollider (metaport)

LICENSE=	BSD3CLAUSE

HOSTDIR=	${.CURDIR}/../vstplugin-host
BRIDGEDIR=	${.CURDIR}/../vstplugin-bridge

OPTIONS_INCLUDE=	PD SC

DESCR=	${HOSTDIR}/pkg-descr
DISTINFO_FILE=	${HOSTDIR}/distinfo

.include "${HOSTDIR}/Makefile.include.pre.mk"
.include "${BRIDGEDIR}/Makefile.include.pre.mk"

USES:=	metaport

wine_PKGNAMESUFFIX=	-wine
wine_devel_PKGNAMESUFFIX=	-wine_devel

HOST_PACKAGE=	audio/${PORTNAME}-host
BRIDGE_PACKAGE=	audio/${PORTNAME}-bridge@${FLAVOR}

RUN_DEPENDS+=	${PORTNAME}-host>0:${HOST_PACKAGE} \
		${PORTNAME}-bridge${PKGNAMESUFFIX}>0:${BRIDGE_PACKAGE}

.include <bsd.port.options.mk>
.include "${BRIDGEDIR}/Makefile.include.conditionals.mk"
# make portlint happy
# .if ${PORT_OPTIONS:MWINE} || ${PORT_OPTIONS:MWINE_DEVEL} || \
#     ${PORT_OPTIONS:MVST2}
# .endif
.include <bsd.port.mk>
