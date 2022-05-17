# Created by: Timothy Beyer <beyert@cs.ucr.edu>

PORTNAME=	fbneo
PORTVERSION=	20220516
CATEGORIES=	emulators games

MAINTAINER=	beyert@cs.ucr.edu
COMMENT=	Final Burn Neo standalone

LICENSE=	FBNeo
LICENSE_NAME=	FBNeo
LICENSE_FILE=	${WRKSRC}/src/license.txt
LICENSE_PERMS=	dist-mirror pkg-mirror auto-accept

LIB_DEPENDS=	libpng.so:graphics/png

USES=	compiler:c++11-lib gmake gl 7z perl5 shebangfix sdl
USE_LDCONFIG=	yes
USE_GL+=	gl
USE_PERL5=	build
USE_SDL+=	sdl2 image2

SHEBANG_FILES=	${WRKSRC}/src/dep/scripts/cave_sprite_func.pl \
	${WRKSRC}/src/dep/scripts/cave_tile_func.pl \
	${WRKSRC}/src/dep/scripts/neo_sprite_func.pl \
	${WRKSRC}/src/dep/scripts/psikyo_tile_func.pl \
	${WRKSRC}/src/dep/scripts/toa_gp9001_func.pl \
	${WRKSRC}/src/dep/scripts/gamelist.pl

PLIST_FILES=	bin/fbneo

USE_GITHUB=	yes
GH_ACCOUNT=	libretro
GH_PROJECT=	FBNeo
GH_TAGNAME=	48ce2d0

MAKEFILE=	${WRKSRC}/makefile.sdl2

MAKE_ARGS+=	INCLUDE_7Z_SUPPORT=1 RELEASEBUILD=1 INCLUDE_LIB_PNGH=1 \
	LSB_FIRST=1 PERL=1

post-patch:
	@${REINPLACE_CMD} 's|= gcc|= ${CC}|' \
		${WRKSRC}/makefile.sdl2
	@${REINPLACE_CMD} 's|:= gcc|:= ${CC}|' \
		${WRKSRC}/src/burner/libretro/Makefile \
		${WRKSRC}/src/burner/libretro/libretro-common/samples/utils/Makefile \
		${WRKSRC}/src/burner/libretro/libretro-common/audio/dsp_filters/Makefile

do-install:
	${INSTALL} ${WRKSRC}/${PORTNAME} ${STAGEDIR}/${PREFIX}/bin/${PORTNAME}

.include <bsd.port.mk>
