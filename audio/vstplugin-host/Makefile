# Created by: Timothy Beyer <beyert@cs.ucr.edu>

PORTNAME=	vstplugin
PORTVERSION=	20220211
CATEGORIES=	audio
PKGNAMESUFFIX=	-host

MAINTAINER=	beyert@cs.ucr.edu
COMMENT=	VST plugin support for Pd and SuperCollider

LICENSE=	BSD3CLAUSE

PATCHDIR=
PLIST=

OPTIONS_INCLUDE=	PD SC

.include "Makefile.include.pre.mk"

USES:=	metaport

PD_PACKAGE=	audio/pd-${PORTNAME}${PKGNAMESUFFIX}
SC_PACKAGE=	audio/sc3-${PORTNAME}${PKGNAMESUFFIX}

RUN_DEPENDS+=	\
		pd-${PORTNAME}${PKGNAMESUFFIX}>0:${PD_PACKAGE} \
		sc3-${PORTNAME}${PKGNAMESUFFIX}>0:${SC_PACKAGE}

.include <bsd.port.options.mk>
.include "Makefile.include.conditionals.mk"
# make portlint happy
# .if ${PORT_OPTIONS:MVST2}
# .endif
.include "Makefile.include.targets.mk"
.include <bsd.port.mk>
