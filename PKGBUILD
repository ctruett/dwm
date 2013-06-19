# $Id: PKGBUILD 60970 2011-12-19 21:33:58Z spupykin $
# Maintainer: Sergej Pupykin <pupykin.s+arch@gmail.com>
# Contributor: Dag Odenhall <dag.odenhall@gmail.com>
# Contributor: Grigorios Bouzakis <grbzks@gmail.com>

pkgname=dwm
pkgver=6.0
pkgrel=1
pkgdesc="A dynamic window manager for X"
url="http://dwm.suckless.org"
arch=('i686' 'x86_64')
license=('MIT')
options=(zipman)
depends=('libx11' 'libxinerama')
install=dwm.install
source=(http://dl.suckless.org/dwm/dwm-$pkgver.tar.gz
	tcl.h
	dwm.c
	config.h
	bstack.c
	bstackhoriz.c
	dwm.desktop)

md5sums=(
	'8bb00d4142259beb11e13473b81c0857'
	'e92edfb03207d6b7d51f0c6ae6237fa9'
	'acc4bc2a801949613272193ddc528a2e'
	'bc810c6907dd06f7e1f98a80fc611501'
	'9064c678b6f18094611448ba29f87bff'
	'c3c7d80ecfd8d8f46145462f4b1e7add'
	'939f403a71b6e85261d09fc3412269ee')



build() {
  cd $srcdir/$pkgname-$pkgver
  cp $srcdir/config.h config.h
  cp $srcdir/tcl.h tcl.h
  cp $srcdir/dwm.c dwm.c
  cp $srcdir/bstack.c bstack.c
  cp $srcdir/bstackhoriz.c bstackhoriz.c
  sed -i 's/CPPFLAGS =/CPPFLAGS +=/g' config.mk
  sed -i 's/^CFLAGS = -g/#CFLAGS += -g/g' config.mk
  sed -i 's/^#CFLAGS = -std/CFLAGS += -std/g' config.mk
  sed -i 's/^LDFLAGS = -g/#LDFLAGS += -g/g' config.mk
  sed -i 's/^#LDFLAGS = -s/LDFLAGS += -s/g' config.mk
  make X11INC=/usr/include/X11 X11LIB=/usr/lib/X11
}

package() {
  cd $srcdir/$pkgname-$pkgver
  make PREFIX=/usr DESTDIR=$pkgdir install
  install -m644 -D LICENSE $pkgdir/usr/share/licenses/$pkgname/LICENSE
  install -m644 -D README $pkgdir/usr/share/doc/$pkgname/README
  install -m644 -D $srcdir/dwm.desktop $pkgdir/usr/share/xsessions/dwm.desktop
}
