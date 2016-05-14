# Created by: Timothy Beyer <beyert@cs.ucr.edu>
# $FreeBSD$

PORTNAME=	racer
DISTVERSION=	1.2.5
CATEGORIES=	devel

MAINTAINER=	beyert@cs.ucr.edu
COMMENT=	Utility intended to provide Rust code completion for editors and IDEs

LICENSE=	MIT
LICENSE_FILE=	${WRKSRC}/LICENSE-MIT

BUILD_DEPENDS=	cargo:devel/cargo
RUN_DEPENDS=	rustdoc:lang/rust

USE_GITHUB=	yes
GH_ACCOUNT=	phildawes
GH_TAGNAME=	${DISTVERSION}

MAKE_ENV=	RUST_SRC_PATH=${PREFIX}/share/rust/src

RUST_ARCH_x86_64=	x86_64 # dragonfly
RUST_ARCH_amd64=	x86_64
RUST_ARCH_i386=		i686
RUST_TARGET=		${RUST_ARCH_${ARCH}}-unknown-${OPSYS:tl}

do-build:
	cd ${WRKSRC} && cargo build --release

do-install:
	@${MKDIR} ${STAGEDIR}${PREFIX}/lib/rustlib/${RUST_TARGET}
	@${CP} -pR ${WRKSRC}/target/release/libracer.rlib \
		${STAGEDIR}${PREFIX}/lib/rustlib/${RUST_TARGET}/
	@${CP} -pR ${WRKSRC}/target/release/deps/* \
		${STAGEDIR}${PREFIX}/lib/rustlib/${RUST_TARGET}/
	@${CP} -pR ${WRKSRC}/target/release/racer ${STAGEDIR}${PREFIX}/bin/

post-install:
	@${STRIP_CMD} ${STAGEDIR}${PREFIX}/bin/racer

.include <bsd.port.mk>
