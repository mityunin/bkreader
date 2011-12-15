#############################################################################
# Makefile for building: bin/bkreader
# Generated by qmake (2.01a) (Qt 4.7.4) on: ?? ???. 5 19:28:51 2011
# Project:  bkreader.pro
# Template: app
# Command: /usr/bin/qmake-qt4 -o Makefile bkreader.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_WEBKIT -DQT_NO_DEBUG -DQT_XML_LIB -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -pipe -O2 -Wall -W -D_REENTRANT $(DEFINES)
CXXFLAGS      = -pipe -O2 -Wall -W -D_REENTRANT $(DEFINES)
INCPATH       = -I/usr/share/qt4/mkspecs/linux-g++ -I. -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtGui -I/usr/include/qt4/QtXml -I/usr/include/qt4 -Ibuild -Ibuild
LINK          = g++
LFLAGS        = -Wl,-O1
LIBS          = $(SUBLIBS)  -L/usr/lib/i386-linux-gnu -lz -lQtXml -lQtGui -lQtCore -lpthread 
AR            = ar cqs
RANLIB        = 
QMAKE         = /usr/bin/qmake-qt4
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
STRIP         = strip
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = build/

####### Files

SOURCES       = src/mainwindowimpl.cpp \
		src/main.cpp \
		src/book.cpp \
		src/pageline.cpp \
		src/fb2.cpp \
		src/readerutils.cpp \
		src/pagetemplate.cpp \
		src/bookprops.cpp \
		src/booksettings.cpp \
		src/hyphenator.cpp \
		src/osdab-zip/zipglobal.cpp \
		src/osdab-zip/zip.cpp \
		src/osdab-zip/unzip.cpp \
		src/library.cpp build/moc_mainwindowimpl.cpp \
		build/moc_pagetemplate.cpp \
		build/moc_booksettings.cpp \
		build/moc_zip_p.cpp \
		build/moc_unzip_p.cpp \
		build/moc_library.cpp
OBJECTS       = build/mainwindowimpl.o \
		build/main.o \
		build/book.o \
		build/pageline.o \
		build/fb2.o \
		build/readerutils.o \
		build/pagetemplate.o \
		build/bookprops.o \
		build/booksettings.o \
		build/hyphenator.o \
		build/zipglobal.o \
		build/zip.o \
		build/unzip.o \
		build/library.o \
		build/moc_mainwindowimpl.o \
		build/moc_pagetemplate.o \
		build/moc_booksettings.o \
		build/moc_zip_p.o \
		build/moc_unzip_p.o \
		build/moc_library.o
DIST          = /usr/share/qt4/mkspecs/common/g++.conf \
		/usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/release.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		bkreader.pro
QMAKE_TARGET  = bkreader
DESTDIR       = bin/
TARGET        = bin/bkreader

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile $(TARGET)

$(TARGET): build/ui_mainwindow.h build/ui_booksettings.h build/ui_library.h $(OBJECTS)  
	@$(CHK_DIR_EXISTS) bin/ || $(MKDIR) bin/ 
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: bkreader.pro  /usr/share/qt4/mkspecs/linux-g++/qmake.conf /usr/share/qt4/mkspecs/common/g++.conf \
		/usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/release.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/lib/i386-linux-gnu/libQtXml.prl \
		/usr/lib/i386-linux-gnu/libQtGui.prl \
		/usr/lib/i386-linux-gnu/libQtCore.prl
	$(QMAKE) -o Makefile bkreader.pro
/usr/share/qt4/mkspecs/common/g++.conf:
/usr/share/qt4/mkspecs/common/unix.conf:
/usr/share/qt4/mkspecs/common/linux.conf:
/usr/share/qt4/mkspecs/qconfig.pri:
/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri:
/usr/share/qt4/mkspecs/features/qt_functions.prf:
/usr/share/qt4/mkspecs/features/qt_config.prf:
/usr/share/qt4/mkspecs/features/exclusive_builds.prf:
/usr/share/qt4/mkspecs/features/default_pre.prf:
/usr/share/qt4/mkspecs/features/release.prf:
/usr/share/qt4/mkspecs/features/default_post.prf:
/usr/share/qt4/mkspecs/features/warn_on.prf:
/usr/share/qt4/mkspecs/features/qt.prf:
/usr/share/qt4/mkspecs/features/unix/thread.prf:
/usr/share/qt4/mkspecs/features/moc.prf:
/usr/share/qt4/mkspecs/features/resources.prf:
/usr/share/qt4/mkspecs/features/uic.prf:
/usr/share/qt4/mkspecs/features/yacc.prf:
/usr/share/qt4/mkspecs/features/lex.prf:
/usr/lib/i386-linux-gnu/libQtXml.prl:
/usr/lib/i386-linux-gnu/libQtGui.prl:
/usr/lib/i386-linux-gnu/libQtCore.prl:
qmake:  FORCE
	@$(QMAKE) -o Makefile bkreader.pro

dist: 
	@$(CHK_DIR_EXISTS) build/bkreader1.0.0 || $(MKDIR) build/bkreader1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) build/bkreader1.0.0/ && $(COPY_FILE) --parents src/mainwindowimpl.h src/book.h src/pageline.h src/fb2.h src/readerutils.h src/pagetemplate.h src/bookprops.h src/booksettings.h src/hyphenator.h src/osdab-zip/zipglobal.h src/osdab-zip/zipentry_p.h src/osdab-zip/zip_p.h src/osdab-zip/zip.h src/osdab-zip/unzip_p.h src/osdab-zip/unzip.h src/library.h build/bkreader1.0.0/ && $(COPY_FILE) --parents src/mainwindowimpl.cpp src/main.cpp src/book.cpp src/pageline.cpp src/fb2.cpp src/readerutils.cpp src/pagetemplate.cpp src/bookprops.cpp src/booksettings.cpp src/hyphenator.cpp src/osdab-zip/zipglobal.cpp src/osdab-zip/zip.cpp src/osdab-zip/unzip.cpp src/library.cpp build/bkreader1.0.0/ && $(COPY_FILE) --parents ui/mainwindow.ui src/booksettings.ui src/library.ui build/bkreader1.0.0/ && (cd `dirname build/bkreader1.0.0` && $(TAR) bkreader1.0.0.tar bkreader1.0.0 && $(COMPRESS) bkreader1.0.0.tar) && $(MOVE) `dirname build/bkreader1.0.0`/bkreader1.0.0.tar.gz . && $(DEL_FILE) -r build/bkreader1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


check: first

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: build/moc_mainwindowimpl.cpp build/moc_pagetemplate.cpp build/moc_booksettings.cpp build/moc_zip_p.cpp build/moc_unzip_p.cpp build/moc_library.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) build/moc_mainwindowimpl.cpp build/moc_pagetemplate.cpp build/moc_booksettings.cpp build/moc_zip_p.cpp build/moc_unzip_p.cpp build/moc_library.cpp
build/moc_mainwindowimpl.cpp: build/ui_mainwindow.h \
		src/book.h \
		src/fb2.h \
		src/pageline.h \
		src/readerutils.h \
		src/hyphenator.h \
		src/mainwindowimpl.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) src/mainwindowimpl.h -o build/moc_mainwindowimpl.cpp

build/moc_pagetemplate.cpp: src/pageline.h \
		src/readerutils.h \
		src/hyphenator.h \
		src/book.h \
		src/fb2.h \
		src/booksettings.h \
		src/library.h \
		src/pagetemplate.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) src/pagetemplate.h -o build/moc_pagetemplate.cpp

build/moc_booksettings.cpp: src/readerutils.h \
		src/booksettings.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) src/booksettings.h -o build/moc_booksettings.cpp

build/moc_zip_p.cpp: src/osdab-zip/zip.h \
		src/osdab-zip/zipglobal.h \
		src/osdab-zip/zipentry_p.h \
		src/osdab-zip/zip_p.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) src/osdab-zip/zip_p.h -o build/moc_zip_p.cpp

build/moc_unzip_p.cpp: src/osdab-zip/unzip.h \
		src/osdab-zip/zipglobal.h \
		src/osdab-zip/zipentry_p.h \
		src/osdab-zip/unzip_p.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) src/osdab-zip/unzip_p.h -o build/moc_unzip_p.cpp

build/moc_library.cpp: src/library.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) src/library.h -o build/moc_library.cpp

compiler_rcc_make_all:
compiler_rcc_clean:
compiler_image_collection_make_all: build/qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) build/qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all: build/ui_mainwindow.h build/ui_booksettings.h build/ui_library.h
compiler_uic_clean:
	-$(DEL_FILE) build/ui_mainwindow.h build/ui_booksettings.h build/ui_library.h
build/ui_mainwindow.h: ui/mainwindow.ui
	/usr/bin/uic-qt4 ui/mainwindow.ui -o build/ui_mainwindow.h

build/ui_booksettings.h: src/booksettings.ui
	/usr/bin/uic-qt4 src/booksettings.ui -o build/ui_booksettings.h

build/ui_library.h: src/library.ui
	/usr/bin/uic-qt4 src/library.ui -o build/ui_library.h

compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean compiler_uic_clean 

####### Compile

build/mainwindowimpl.o: src/mainwindowimpl.cpp src/mainwindowimpl.h \
		build/ui_mainwindow.h \
		src/book.h \
		src/fb2.h \
		src/pageline.h \
		src/readerutils.h \
		src/hyphenator.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/mainwindowimpl.o src/mainwindowimpl.cpp

build/main.o: src/main.cpp src/mainwindowimpl.h \
		build/ui_mainwindow.h \
		src/book.h \
		src/fb2.h \
		src/pageline.h \
		src/readerutils.h \
		src/hyphenator.h \
		src/pagetemplate.h \
		src/booksettings.h \
		src/library.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/main.o src/main.cpp

build/book.o: src/book.cpp src/book.h \
		src/fb2.h \
		src/pageline.h \
		src/readerutils.h \
		src/hyphenator.h \
		src/osdab-zip/unzip.h \
		src/osdab-zip/zipglobal.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/book.o src/book.cpp

build/pageline.o: src/pageline.cpp src/pageline.h \
		src/readerutils.h \
		src/hyphenator.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/pageline.o src/pageline.cpp

build/fb2.o: src/fb2.cpp src/fb2.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/fb2.o src/fb2.cpp

build/readerutils.o: src/readerutils.cpp src/readerutils.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/readerutils.o src/readerutils.cpp

build/pagetemplate.o: src/pagetemplate.cpp src/pagetemplate.h \
		src/pageline.h \
		src/readerutils.h \
		src/hyphenator.h \
		src/book.h \
		src/fb2.h \
		src/booksettings.h \
		src/library.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/pagetemplate.o src/pagetemplate.cpp

build/bookprops.o: src/bookprops.cpp src/bookprops.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/bookprops.o src/bookprops.cpp

build/booksettings.o: src/booksettings.cpp src/booksettings.h \
		src/readerutils.h \
		build/ui_booksettings.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/booksettings.o src/booksettings.cpp

build/hyphenator.o: src/hyphenator.cpp src/hyphenator.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/hyphenator.o src/hyphenator.cpp

build/zipglobal.o: src/osdab-zip/zipglobal.cpp src/osdab-zip/zipglobal.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/zipglobal.o src/osdab-zip/zipglobal.cpp

build/zip.o: src/osdab-zip/zip.cpp src/osdab-zip/zip.h \
		src/osdab-zip/zipglobal.h \
		src/osdab-zip/zip_p.h \
		src/osdab-zip/zipentry_p.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/zip.o src/osdab-zip/zip.cpp

build/unzip.o: src/osdab-zip/unzip.cpp src/osdab-zip/unzip.h \
		src/osdab-zip/zipglobal.h \
		src/osdab-zip/unzip_p.h \
		src/osdab-zip/zipentry_p.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/unzip.o src/osdab-zip/unzip.cpp

build/library.o: src/library.cpp src/library.h \
		build/ui_library.h \
		src/osdab-zip/unzip.h \
		src/osdab-zip/zipglobal.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/library.o src/library.cpp

build/moc_mainwindowimpl.o: build/moc_mainwindowimpl.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/moc_mainwindowimpl.o build/moc_mainwindowimpl.cpp

build/moc_pagetemplate.o: build/moc_pagetemplate.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/moc_pagetemplate.o build/moc_pagetemplate.cpp

build/moc_booksettings.o: build/moc_booksettings.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/moc_booksettings.o build/moc_booksettings.cpp

build/moc_zip_p.o: build/moc_zip_p.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/moc_zip_p.o build/moc_zip_p.cpp

build/moc_unzip_p.o: build/moc_unzip_p.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/moc_unzip_p.o build/moc_unzip_p.cpp

build/moc_library.o: build/moc_library.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/moc_library.o build/moc_library.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

