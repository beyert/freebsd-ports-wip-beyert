FLAVORS=	wine wine_devel

OPTIONS_DEFAULT+=	WINE

OPTIONS_SINGLE=	WINEVERSION
OPTIONS_SINGLE_WINEVERSION=	WINE WINE_DEVEL

WINEVERSION_DESC=	Version of wine to use for FreeBSD->Windows VST Bridge
WINE_DESC=	Wine stable (emulators/wine)
WINE_DEVEL_DESC=	Wine devel (emulators/wine-devel)

wine_PKGNAMESUFFIX=	-bridge-wine
wine_devel_PKGNAMESUFFIX=	-bridge-wine_devel
