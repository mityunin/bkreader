#!/bin/sh
SHARE_DIR="/usr/share/"
BIN_DIR="/usr/bin/"
BKREADER="bkreader"
PATTERNS_DIR="/patterns"
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