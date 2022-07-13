# Created by: Yuri Victorovich <yuri@rawbw.com>

PORTNAME=	lvtk
PORTVERSION=	1.2.0
CATEGORIES=	audio
PKGNAMESUFFIX=	-1

MAINTAINER=	beyert@cs.ucr.edu
COMMENT=	Wraps the LV2 C API and extensions into easy to use C++ classes

LICENSE=	GPLv3
LICENSE_FILE=	${WRKSRC}/COPYING

# need ttl2c for plugin examples and UIs
BUILD_DEPENDS=	lv2>0:audio/lv2 \
		${LOCALBASE}/bin/ttl2c:audio/ttl2c \
		${LOCALBASE}/include/gtkmm-2.4/gtkmm.h:x11-toolkits/gtkmm24
LIB_DEPENDS=	libharfbuzz.so:print/harfbuzz \
		libfontconfig.so:x11-fonts/fontconfig \
		libfreetype.so:print/freetype2

USES=	pkgconfig python:2.7,build gnome waf
USE_GITHUB=	yes
GH_TAGNAME=	7c0ffdf

USE_GNOME=	gtk20 gtkmm24 glibmm pangomm atkmm cairomm pango atk cairo \
	gdkpixbuf2 glib20 libsigc++20

OPTIONS_DEFINE=	NLS

NLS_USES=	gettext-runtime

post-install:
# first 3 are the bare minimum, the last 5 oddly do not overlap with current
# versions of llvm-2
	@if [ -f ${STAGEDIR}${PREFIX}/include/lvtk-2/lvtk/version.h ]; then \
		${MV} ${STAGEDIR}${PREFIX}/include/lvtk-2 \
			${STAGEDIR}${PREFIX}/include/lvtk-1; \
		${MV} ${STAGEDIR}${PREFIX}/lib/lv2/lvtk.lv2 \
			${STAGEDIR}${PREFIX}/lib/lv2/lvtk-1.lv2; \
		${MV} ${STAGEDIR}${PREFIX}/libdata/pkgconfig/lvtk-2.pc \
			${STAGEDIR}${PREFIX}/libdata/pkgconfig/lvtk-1.pc; \
		${MV} ${STAGEDIR}${PREFIX}/libdata/pkgconfig/lvtk-gtkui-2.pc \
			${STAGEDIR}${PREFIX}/libdata/pkgconfig/lvtk-gtkui-1.pc; \
		${MV} ${STAGEDIR}${PREFIX}/libdata/pkgconfig/lvtk-plugin-2.pc \
			${STAGEDIR}${PREFIX}/libdata/pkgconfig/lvtk-plugin-1.pc; \
		${MV} ${STAGEDIR}${PREFIX}/libdata/pkgconfig/lvtk-ui-2.pc \
			${STAGEDIR}${PREFIX}/libdata/pkgconfig/lvtk-ui-1.pc; \
		${MV} ${STAGEDIR}${PREFIX}/lib/liblvtk_plugin2.a \
			${STAGEDIR}${PREFIX}/lib/liblvtk_plugin1.a; \
		${MV} ${STAGEDIR}${PREFIX}/lib/liblvtk_ui2.a \
			${STAGEDIR}${PREFIX}/lib/liblvtk_ui1.a; \
	fi
	@${REINPLACE_CMD} 's|lvtk-2|lvtk-1|' \
		${STAGEDIR}${PREFIX}/libdata/pkgconfig/lvtk-1.pc
	@${REINPLACE_CMD} -e 's|lvtk-2|lvtk-1|' -e 's|_ui2|_ui1|' \
		${STAGEDIR}${PREFIX}/libdata/pkgconfig/lvtk-gtkui-1.pc \
		${STAGEDIR}${PREFIX}/libdata/pkgconfig/lvtk-ui-1.pc
	@${REINPLACE_CMD} -e 's|lvtk-2|lvtk-1|' -e 's|_plugin2|_plugin1|' \
		${STAGEDIR}${PREFIX}/libdata/pkgconfig/lvtk-plugin-1.pc
	@${STRIP_CMD} ${STAGEDIR}${PREFIX}/lib/lv2/lvtk-1.lv2/beep.so
	@${STRIP_CMD} ${STAGEDIR}${PREFIX}/lib/lv2/lvtk-1.lv2/beep_ui.so
	@${STRIP_CMD} ${STAGEDIR}${PREFIX}/lib/lv2/lvtk-1.lv2/silence.so
	@${STRIP_CMD} ${STAGEDIR}${PREFIX}/lib/lv2/lvtk-1.lv2/silence_ui.so
	@${STRIP_CMD} ${STAGEDIR}${PREFIX}/lib/lv2/lvtk-1.lv2/workhorse.so
	@${STRIP_CMD} ${STAGEDIR}${PREFIX}/lib/lv2/lvtk-1.lv2/workhorse_ui.so

.include <bsd.port.mk>
