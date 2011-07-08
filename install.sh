#!/bin/sh
SHARE_DIR="/usr/share/"
BIN_DIR="/usr/bin/"
BKREADER="bkreader"
PATTERNS_DIR="/patterns"
APPLICATIONS_DIR="/usr/share/applications/"
APP_ICON="/usr/share/icons/hicolor/128x128/apps/bkreader.png"
DESKTOP_FILE="bkreader.desktop"
qmake-qt4
make clean
make
install -m 755 -p bin/bkreader $BIN_DIR$BKREADER
if [ ! -d $SHARE_DIR$BKREADER ] ; then
  mkdir $SHARE_DIR$BKREADER
fi
if [ ! -d $SHARE_DIR$BKREADER$PATTERNS ] ; then
  mkdir $SHARE_DIR$BKREADER$PATTERNS
fi
cp -r bin/patterns $SHARE_DIR$BKREADER$PATTERNS
if [ -f $APPLICATIONS_DIR$DESKTOP_FILE ] ; then
  rm -f $APPLICATIONS_DIR$DESKTOP_FILE
fi
cp $DESKTOP_FILE $APPLICATIONS_DIR$DESKTOP_FILE
if [ -f $APP_ICON ] ; then
  xdg-icon-resource uninstall --size 128 bkreader.png
fi
xdg-icon-resource install --novendor --size 128 bkreader.png 