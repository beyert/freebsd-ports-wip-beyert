# Created by: Timothy Beyer <beyert@cs.ucr.edu>

PORTNAME=	vstplugin
PORTVERSION=	20220211
CATEGORIES=	audio
PKGNAMESUFFIX=	-bridge

MAINTAINER=	beyert@cs.ucr.edu
COMMENT=	Windows VST plugin support for Pd and SuperCollider via Wine

LICENSE=	BSD3CLAUSE

.include "Makefile.include.pre.mk"

HOSTDIR=	${.CURDIR}/../vstplugin-host
DESCR=	${HOSTDIR}/pkg-descr
DISTINFO_FILE=	${HOSTDIR}/distinfo
PLIST=

OPTIONS_INCLUDE=	PD SC

.include "${HOSTDIR}/Makefile.include.pre.mk"

USES:=	metaport

PD_PACKAGE=	audio/pd-${PORTNAME}-bridge@${FLAVOR}
SC_PACKAGE=	audio/sc3-${PORTNAME}-bridge@${FLAVOR}

RUN_DEPENDS+=	\
		pd-${PORTNAME}${PKGNAMESUFFIX}>0:${PD_PACKAGE} \
		sc3-${PORTNAME}${PKGNAMESUFFIX}>0:${SC_PACKAGE}

.include "Makefile.include.post.mk"
.include <bsd.port.options.mk>
.include "Makefile.include.conditionals.mk"
.include "${HOSTDIR}/Makefile.include.conditionals.mk"
.include "${HOSTDIR}/Makefile.include.targets.mk"
# make portlint happy
# .if ${PORT_OPTIONS:MWINE} || ${PORT_OPTIONS:MWINE_DEVEL} || \
#     ${PORT_OPTIONS:MVST2}
# .endif
.include <bsd.port.mk>
