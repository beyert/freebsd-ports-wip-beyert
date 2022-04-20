# Created by: Timothy Beyer <beyert@cs.ucr.edu>

PORTNAME=	nxssh
DISTVERSION=	20181125
CATEGORIES=	net

MAINTAINER=	beyert@cs.ucr.edu
COMMENT=	Modified openssh client, used by rxclient (formerly opennx)

LICENSE=	BEERWARE BSD2CLAUSE BSD3CLAUSE ISCL MIT POWELL
LICENSE_COMB=	multi
LICENSE_NAME_BEERWARE=	Beer-Ware License v42 by Poul-Henning Kamp
LICENSE_NAME_POWELL=	Any purpose Patrick Powell License
LICENSE_FILE=	${WRKSRC}/LICENCE
LICENSE_FILE_BEERWARE=	${LICENSE_FILE}
LICENSE_FILE_POWELL=	${LICENSE_FILE}
LICENSE_PERMS_BEERWARE=	${_LICENSE_PERMS_DEFAULT}
LICENSE_PERMS_POWELL=	${_LICENSE_PERMS_DEFAULT}

BUILD_DEPENDS=	${LOCALBASE}/include/nx/NX.h:x11/nxcomp

USES=	autoreconf localbase:ldflags gmake
GNU_CONFIGURE=	yes

USE_GITHUB=	yes
GH_ACCOUNT=	Etersoft
GH_PROJECT=	${PORTNAME}
GH_TAGNAME=	ce04e93

PLIST_FILES=	bin/nxssh \
	bin/nxssh-keygen \
	bin/nxsshd

do-install:
.for file in ${PLIST_FILES}
	@${INSTALL} ${WRKSRC}/${file:C/bin\///} \
		${STAGEDIR}${PREFIX}/bin/${file:C/bin\///}
.endfor

.include <bsd.port.mk>
