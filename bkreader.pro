TEMPLATE = app
QT = gui core xml
CONFIG += qt warn_on console debug
DESTDIR = bin
OBJECTS_DIR = build
MOC_DIR = build
UI_DIR = build
FORMS = ui/mainwindow.ui \
    src/booksettings.ui
HEADERS = src/mainwindowimpl.h \
 src/book.h \
 src/pageline.h \
 src/fb2.h \
 src/readerutils.h \
 src/pagetemplate.h \
    src/bookprops.h \
    src/booksettings.h \
    src/hyphenator.h \
    src/osdab-zip/zipglobal.h \
    src/osdab-zip/zipentry_p.h \
    src/osdab-zip/zip_p.h \
    src/osdab-zip/zip.h \
    src/osdab-zip/unzip_p.h \
    src/osdab-zip/unzip.h
SOURCES = src/mainwindowimpl.cpp \
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
    src/osdab-zip/unzip.cpp



unix:!macx:!symbian: LIBS += -lz
