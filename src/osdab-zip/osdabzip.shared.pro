################
# Example project file to build 
# the OSDaB Zip code as a shared library
################

INCLUDEPATH += .

TEMPLATE = lib
QT -= gui
CONFIG += dll console debug
TARGET = osdabzip
DEFINES += OSDAB_ZIP_LIB OSDAB_ZIP_BUILD_LIB

# Input
HEADERS += zipglobal.h zip.h zip_p.h unzip.h unzip_p.h zipentry_p.h
SOURCES += zipglobal.cpp zip.cpp unzip.cpp
DESTDIR = bin
DLLDESTDIR = bin
MOC_DIR = tmp
OBJECTS_DIR = tmp
