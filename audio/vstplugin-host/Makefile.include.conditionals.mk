# needed for required sys/eventfd.h in the VST plugin host ports
.if ${OSREL:R} < 13
BUILD_DEPENDS+=	${LOCALBASE}/include/libepoll-shim/sys/eventfd.h:devel/libepoll-shim
CXXFLAGS+=	-I${LOCALBASE}/include/libepoll-shim
LDFLAGS+=	-lepoll-shim
# need this to just make eventfd.h to work when epoll is not desired
CXXFLAGS+=	-DEPOLL_SHIM_DISABLE_WRAPPER_MACROS
.endif

.if ${FLAVORS} == ""
CMAKE_ARGS+=	-DBUILD_WINE=OFF -DSMTG_ADD_VSTGUI=ON
.endif

.if ${ARCH} == "amd64"
CMAKE_ARGS+=	-DBUILD_HOST_AMD64=ON -DBUILD_HOST32=OFF -DSTDFS=OFF
.endif

.if ${PORT_OPTIONS:MVST2}
.if defined(VSTSDK_BASE_DIR)
CMAKE_ARGS+=	-DVST2=ON -DVST2DIR="${VSTSDK_BASE_DIR}"
.else
CMAKE_ARGS+=	-DVST2=OFF
IGNORE+=	to use option VST2, need to obtain VST SDK and set variable VSTSDK_BASE_DIR=[directory_containing_pluginterfaces]; in poudriere, this path must be visible to the jail (typically in /distfiles or /wrkdirs paths)
.endif
.else
CMAKE_ARGS+=	-DVST2=OFF
.endif

# no idea why this is necessary...
.if "${USES}" == "metaport"
NO_BUILD=	yes
.endif

.if defined(NO_BUILD)
.undef USE_GITHUB
WRKDIR=	${WRKDIRPREFIX}${.CURDIR}/work
.endif
