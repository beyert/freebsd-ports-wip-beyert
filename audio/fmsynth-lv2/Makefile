# Created by: Timothy Beyer <beyert@cs.ucr.edu>

PORTNAME=	fmsynth
PORTVERSION=	20200628
CATEGORIES=	audio
PKGNAMESUFFIX=	-lv2

MAINTAINER=	beyert@cs.ucr.edu
COMMENT=	FM synthesizer implementation using libfmsynth, as an LV2 plugin

LICENSE=	MIT
LICENSE_FILE=	${WRKSRC}/COPYING

# audio/lv2 needed for include file symlink
BUILD_DEPENDS=	lv2>0:audio/lv2 \
		${LOCALBASE}/bin/ttl2c:audio/ttl2c \
		${LOCALBASE}/include/lvtk-1/lvtk/lvtk.hpp:audio/lvtk-1 \
		${LOCALBASE}/include/gtkmm-2.4/gtkmm.h:x11-toolkits/gtkmm24
LIB_DEPENDS=	libharfbuzz.so:print/harfbuzz \
		libfontconfig.so:x11-fonts/fontconfig \
		libfreetype.so:print/freetype2

USES=	gmake compiler:c++11-lang gnome pkgconfig

USE_GITHUB=	yes
GH_ACCOUNT=	Themaister
GH_PROJECT=	lib${PORTNAME}
GH_TAGNAME=	b989b5c

USE_GNOME=	gtk20 gtkmm24 glibmm pangomm atkmm cairomm pango atk cairo \
	gdkpixbuf2 glib20 libsigc++20

OPTIONS_DEFINE=	NLS

NLS_USES=	gettext-runtime

CXXFLAGS+=	-I${LOCALBASE}/include/lvtk-1 -I${LOCALBASE}/include

MAKEFILE=	GNUmakefile
BUILD_WRKSRC=	${WRKSRC}/lv2

post-patch:
	${REINPLACE_CMD} 's|/usr|${PREFIX}|g' ${BUILD_WRKSRC}/GNUmakefile

do-install:
	@${MKDIR} ${STAGEDIR}${PREFIX}/lib/lv2
	@${CP} -pR ${BUILD_WRKSRC}/fmsynth.lv2 ${STAGEDIR}${PREFIX}/lib/lv2
	@${STRIP_CMD} ${STAGEDIR}${PREFIX}/lib/lv2/fmsynth.lv2/fmsynth.so
	@${STRIP_CMD} ${STAGEDIR}${PREFIX}/lib/lv2/fmsynth.lv2/fmsynth_gui.so

.include <bsd.port.mk>
