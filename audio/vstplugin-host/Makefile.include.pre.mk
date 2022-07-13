ONLY_FOR_ARCHS=	amd64 i386
IGNORE_i386=	vst3sdk fails to build

USES=	compiler:c++17-lang cmake pkgconfig xorg

USE_XORG+=	x11

OPTIONS_DEFINE=	PD SC VST2

OPTIONS_DEFAULT=	PD SC
OPTIONS_SUB=	yes

VST2_DESC=	VST2 plugin support (restricted redistribution)

#CMAKE_BUILD_TYPE=	Release
CMAKE_ARGS=	-DVST3=ON -DBRIDGE=ON
#		-DVST3DIR="${LOCALBASE}/include/vst3sdk"

PD_BUILD_DEPENDS=	pd:audio/pd
##		${LOCALBASE}/include/vst3sdk/vstbus.h:audio/vst3sdk
PD_VARS=	CMAKE_ARGS+=-DPD=ON \
		CMAKE_ARGS+=-DPD_DIR="${LOCALBASE}/lib/pd" \
		CMAKE_ARGS+=-DPD_INCLUDEDIR="${LOCALBASE}/include/pd" \
		CMAKE_ARGS+=-DPD_INSTALLDIR="${LOCALBASE}/lib/pd-externals"
# -DPD_INCLUDE_BASEDIR="${LOCALBASE}/include"
PD_VARS_OFF=	CMAKE_ARGS+=-DPD=OFF
## use in-tree vst3sdk instead
PD_RUN_DEPENDS=	pd:audio/pd
PD_PLIST_SUB=	PD="@comment "
PD_PLIST_SUB_OFF=	PD=""

PD_DESC=	Pd external

SC_BUILD_DEPENDS=	${LOCALBASE}/bin/scsynth:audio/supercollider
SC_VARS=	CMAKE_ARGS+=-DSC=ON \
	CMAKE_ARGS+=-DSC_INSTALLDIR="${PREFIX}/lib/SuperCollider" \
	CMAKE_ARGS+=-DSC_INCLUDEDIR="${PREFIX}/include/SuperCollider"
SC_VARS_OFF=	CMAKE_ARGS+=-DSC=OFF
SC_PLIST_SUB=	SC="@comment "
SC_PLIST_SUB_OFF=	SC=""

SC_DESC=	SuperCollider plugin

#.if !defined(NO_BUILD) && "${NO_BUILD}" != "yes"
#.if !defined(NO_BUILD)
#.if "${NO_BUILD}" != "yes"
USE_GITHUB=	yes
# needs in-tree vst3sdk, cannot use port
GH_TUPLE=	Spacechild1:${PORTNAME}:cb20070 \
		steinbergmedia:vst3_base:f69df71:pd_vstplugin_vst3_base/vst/VST_SDK/VST3_SDK/base \
		steinbergmedia:vst3_cmake:fe588a3:pd_vstplugin_vst3_cmake/vst/VST_SDK/VST3_SDK/cmake \
		steinbergmedia:vst3_pluginterfaces:2ad397a:pd_vstplugin_vst3_pluginterfaces/vst/VST_SDK/VST3_SDK/pluginterfaces \
		steinbergmedia:vst3_public_sdk:bc459fe:pd_vstplugin_vst3_public_sdk/vst/VST_SDK/VST3_SDK/public.sdk \
		steinbergmedia:vstgui:6431f63:pd_vstplugin_vst3_vstgui/vst/VST_SDK/VST3_SDK/vstgui4
#.endif

CFLAGS+=	-I${LOCALBASE}/include -I/usr/include -D__BSD_VISIBLE \
		-DSTATIC_LIBS=ON

OPTIONS_SLAVE=	${OPTIONS_INCLUDE}
