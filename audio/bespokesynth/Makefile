# Created by: Timothy Beyer <beyert@cs.ucr.edu>

PORTNAME=	bespokesynth
PORTVERSION=	20220510
CATEGORIES=	audio

MAINTAINER=	beyert@cs.ucr.edu
COMMENT=	Software modular synth

LICENSE=	GPLv3
LICENSE_FILE=	${WRKSRC}/LICENSE

#BUILD_DEPENDS=	${LOCALBASE}/include/GLFW/glfw3.h:graphics/glfw \
#	${LOCALBASE}/include/GL/glx.h:graphics/libglvnd
#LIB_DEPENDS=	libportaudio.so:audio/portaudio \
#	libportmidi.so:audio/portmidi \
#	libglfw.so:graphics/glfw
#BUILD_DEPENDS=	${LOCALBASE}/include/wine/windows/winbase.h:emulators/wine
# ftp/curl might only be needed for JUCE demos, so maybe omit
LIB_DEPENDS=	libasound.so:audio/alsa-lib \
	libfreetype.so:print/freetype2 \
	libcurl.so:ftp/curl \
	libjack.so:audio/jack \
	libpng.so:graphics/png
#	libwine.so:emulators/wine
#	libsysinfo.so:devel/libsysinfo
#RUN_DEPENDS=	${LOCALBASE}/include/wine/windows/winbase.h:emulators/wine

USES=	compiler:c++11-lang cmake:insource python xorg gl \
	localbase:ldflags pkgconfig

OPTIONS_DEFINE=	VST2

VST2_DESC=	VST2 plugin support (restricted redistribution)

USE_XORG=	x11 xcomposite xcursor xext xinerama xorgproto xrandr
USE_GL=	gl

.include <bsd.port.options.mk>

CXXFLAGS+=	-I${LOCALBASE}/include

.if ${PORT_OPTIONS:MVST2}
.if defined(VSTSDK_BASE_DIR)
CMAKE_ARGS+=	-DBESPOKE_VST2_SDK_LOCATION=${VSTSDK_BASE_DIR}
.else
IGNORE+=	to use option VST2, need to obtain VST SDK and set variable VSTSDK_BASE_DIR=[directory_containing_pluginterfaces]; in poudriere, this path must be visible to the jail (typically in /distfiles or /wrkdirs paths)
.endif
.endif
# omitted -lglfw -lGLX -lsysinfo -lportmidi
LDFLAGS+=	-I${LOCALBASE}/include/freetype2 -lfreetype -lpthread -lGL \
	-lasound -lpng16

USE_GITHUB=	yes
GH_TUPLE=	BespokeSynth:BespokeSynth:6f97730 \
	juce-framework:JUCE:2f98020:JUCE/libs/JUCE \
	pybind:pybind11:04dd326:pybind11/libs/pybind11 \
	surge-synthesizer:tuning-library:eb8617b:tuninglibrary/libs/tuning-library \
	open-source-parsers:jsoncpp:9059f5c:jsoncpp/libs/json/jsoncpp \
	ODDSound:MTS-ESP:fcfaa59:MTSESP/libs/oddsound-mts/MTS-ESP \
	Ableton:link:a4e4c2f:link/libs/link \
	chriskohlhoff:asio:01b4e87:asiostandalone/libs/link/modules/asio-standalone

post-build:
	@${RM} -rf ${STAGEDIR}${PORTSDIR}

.include <bsd.port.mk>
