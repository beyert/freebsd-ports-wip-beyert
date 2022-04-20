# $FreeBSD$

PORTNAME=	xenia
PORTVERSION=	0.20210609
CATEGORIES=	emulators games

MAINTAINER=	beyert@cs.ucr.edu
COMMENT=	Xbox 360 Emulator

LICENSE=	BSD3CLAUSE
LICENSE_FILE=	${WRKSRC}/LICENSE

ONLY_FOR_ARCHS=	amd64

BUILD_DEPENDS=	vulkan-loader>0:graphics/vulkan-loader \
	${LOCALBASE}/include/vulkan/vulkan.hpp:graphics/vulkan-headers
LIB_DEPENDS=	libvulkan.so:graphics/vulkan-loader \
	liblz4.so:archivers/liblz4 \
	libavcodec.so:multimedia/ffmpeg \
	libavutil.so:multimedia/ffmpeg

USES=		compiler:c++17-lang lua:build gmake python:build shebangfix \
	gl xorg sdl gnome gettext-runtime

SHEBANG_FILES=	${WRKSRC}/xenia-build

USE_LDCONFIG=	yes

USE_XORG=	x11 xcb
USE_GL=		gl glew glu
USE_SDL=	sdl2
USE_GNOME=	gtk30 pango atk cairo gdkpixbuf2 glib20

USE_GITHUB=	yes
GH_TUPLE=	xenia-project:xenia:14bac72 \
	xenia-project:premake-core:7eba282:premake_core/third_party/premake-core \
	xenia-project:premake-export-compile-commands:59e3e55:premake_export_compile_commands/third_party/premake-export-compile-commands \
	Enhex:premake-cmake:c4fec3e:premake_cmake/third_party/premake-cmake \
	Tencent:rapidjson:d87b698:rapidjson/third_party/rapidjson \
	xenia-project:snappy:303cd2c:snappy/third_party/snappy \
	KhronosGroup:SPIRV-Headers:2bf91d3:spirv_headers/third_party/spirv-headers \
	xenia-project:SPIRV-Tools:27a2bbb:spirv_tools/third_party/spirv-tools \
	xenia-project:utfcpp:f295c4b:utfcpp/third_party/utfcpp \
	zeux:volk:30a851b:volk/third_party/volk \
	xenia-project:xbyak:bc70e7e:xbyak/third_party/xbyak \
	Cyan4973:xxHash:4c881f7:xxhash/third_party/xxhash \
	Triang3l:premake-androidmk:01a84c7:premake_androidmk/third_party/premake-androidmk \
	xenia-project:FFmpeg:09eac85:ffmpeg/third_party/FFmpeg \
	openluopworld:aes_128:b5b7f55:aes_128/third_party/aes_128 \
	xenia-project:capstone:f9c6a90:capstone/third_party/capstone \
	discord:discord-rpc:eff23a7:discord_rpc/third_party/discord-rpc \
	fmtlib:fmt:27e3c0f:fmt/third_party/fmt \
	ocornut:imgui:ca30ef4:imgui/third_party/imgui \
	jarro2783:cxxopts:48e265d:cxxopts/third_party/cxxopts \
	HowardHinnant:date:97246a6:date/third_party/date \
	libsdl-org:SDL:d28437d:sdl2/third_party/SDL2 \
	microsoft:DirectXShaderCompiler:6b6f402:direct_x_shader_compiler/third_party/DirectXShaderCompiler \
	benvanik:binutils-ppc-cygwin:6f3f15d:binutils_ppc_cygwin/third_party/binutils-ppc-cygwin \
	catchorg:Catch2:5c88067:catch/third_party/catch \
	skystrife:cpptoml:fededad:cpptoml/third_party/cpptoml \
	xenia-project:disruptorplus:cb83e4b:disruptorplus/third_party/disruptorplus \
	boostorg:nowide:4412f9f:nowide/third_party/nowide

CFLAGS+=	-I${LOCALBASE}/include -ferror-limit=0
CXXFLAGS+=	-I${LOCALBASE}/include -ferror-limit=0

.include <bsd.port.pre.mk>

CFLAGS+=	-I${WRKSRC}/third_party/FFmpeg \
	-I${WRKSRC}/third_party/FFmpeg/libavutil \
	-I${WRKSRC}/third_party/fmt/include \
	-I${WRKSRC}/third_party/nowide/include
CXXFLAGS+=	-I${WRKSRC}/third_party/FFmpeg \
	-I${WRKSRC}/third_party/FFmpeg/libavutil \
	-I${WRKSRC}/third_party/fmt/include \
	-I${WRKSRC}/third_party/nowide/include

LDFLAGS+=	-L${LOCALBASE}/lib
#MAKE_ARGS+=	verbose=true

CONFIGURE_ARGS=	--enable-static \
		--disable-shared \
		--enable-pic \
		--disable-gpl \
		--enable-avresample \
		--cc="${CC}" \
		--cxx="${CXX}"

pre-patch:
	${CP} -pR ${WRKSRC}/third_party/aes_128/aes.h \
		${WRKSRC}/third_party/aes_128/unroll/

post-patch:
	${REINPLACE_CMD} 's|fseeko64|fseeko|g' \
		${WRKSRC}/src/xenia/base/filesystem_posix.cc
	${REINPLACE_CMD} 's|ftello64|ftello|g' \
		${WRKSRC}/src/xenia/base/filesystem_posix.cc
	${REINPLACE_CMD} 's|ftruncate64|ftruncate|g' \
		${WRKSRC}/src/xenia/base/filesystem_posix.cc \
		${WRKSRC}/src/xenia/base/memory_posix.cc
	${REINPLACE_CMD} 's|mmap64|mmap|g' \
		${WRKSRC}/src/xenia/base/memory_posix.cc

pre-build:
	${REINPLACE_CMD} "s|'make'|'gmake'|g" ${WRKSRC}/tools/build/premake \
		${WRKSRC}/xenia-build
	cd ${WRKSRC} && ./xenia-build setup
## necessary, but insufficient alone to build libavutil / libavcodec
.if !exists(${WRKSRC}/third_party/FFmpeg/Makefile)
	test -f ${WRKSRC}/third_party/FFmpeg/config.asm && \
		echo "no configure needed" || \
		(cd ${WRKSRC}/third_party/FFmpeg && ./configure ${CONFIGURE_ARGS})
.endif

PLIST_FILES=	bin/xenia

do-build:
#	cd ${WRKSRC} && ./xenia-build build
	cd ${WRKSRC}/build && ${GMAKE} ${MAKE_ARGS}

do-install:
	${INSTALL} ${WRKSRC}/build/bin/Linux/Checked/xenia \
		${STAGEDIR}/${PREFIX}/bin/xenia

.include <bsd.port.post.mk>
