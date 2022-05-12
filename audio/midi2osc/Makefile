# Created by: Timothy Beyer <beyert@cs.ucr.edu>

PORTNAME=	midi2osc
PORTVERSION=	20201009
CATEGORIES=	audio

MAINTAINER=	beyert@cs.ucr.edu
COMMENT=	Simple MIDI to OpenSoundControl bridge

LICENSE=	MIT
LICENSE_FILE=	${WRKSRC}/LICENSE.txt

BUILD_DEPENDS=	${LOCALBASE}/include/GLFW/glfw3.h:graphics/glfw \
	${LOCALBASE}/include/GL/glx.h:graphics/libglvnd
LIB_DEPENDS=	libportaudio.so:audio/portaudio \
	libportmidi.so:audio/portmidi \
	libglfw.so:graphics/glfw

USES=	compiler:c++11-lang gmake

.include <bsd.port.options.mk>

PLIST_FILES=	bin/midi2osc

CFLAGS+=	-I${WRKSRC}/imgui -I${WRKSRC}/imgui/examples/libs/gl3w \
	-I${LOCALBASE}/include
CXXFLAGS+=	${CFLAGS}
LDFLAGS+=	-L${LOCALBASE}/lib -lportmidi -lglfw -lGLX -lpthread
LIBS+=	${LDFLAGS}

USE_GITHUB=	yes
GH_TUPLE=	mmalex:midi2osc:4d883b8 \
	ocornut:imgui:2889a14:imgui/imgui

do-install:
	@${INSTALL} ${WRKSRC}/midi2osc ${STAGEDIR}${LOCALBASE}/bin/midi2osc

.include <bsd.port.mk>
