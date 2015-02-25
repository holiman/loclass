
####### Compiler, tools and options


CC            = gcc
#CC 				=i686-w64-mingw32-gcc

CXX           = g++

DEFINES       = 
CFLAGS        = -m64 -pipe -g -Wall -W $(DEFINES)
CXXFLAGS      = -m64 -pipe -g -Wall -W $(DEFINES)
#INCPATH       = -I/usr/share/qt4/mkspecs/linux-g++-64 -I.
LINK          = g++
LFLAGS        = -m64
LIBS          = $(SUBLIBS)    
AR            = ar cqs
RANLIB        = 
#QMAKE         = /usr/bin/qmake-qt4
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
STRIP         = strip
#INSTALL_FILE  = install -m 644 -p
#INSTALL_DIR   = $(COPY_DIR)
#INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = main.c \
		optimized_cipher.c\
		cipher.c \
		cipherutils.c \
		ikeys.c \
		des.c \
		elite_crack.c \
		fileutils.c \
		hash1_brute.c
OBJECTS       = main.o \
		optimized_cipher.o\
		cipher.o \
		cipherutils.o \
		ikeys.o \
		des.o \
		elite_crack.o \
		fileutils.o\
		hash1_brute.o

TARGET        = loclass

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




$(TARGET):  $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)
	{ test -n "$(DESTDIR)" && DESTDIR="$(DESTDIR)" || DESTDIR=.; } && test $$(gdb --version | sed -e 's,[^0-9]\+\([0-9]\)\.\([0-9]\).*,\1\2,;q') -gt 72 && gdb --nx --batch --quiet -ex 'set confirm off' -ex "save gdb-index $$DESTDIR" -ex quit '$(TARGET)' && test -f $(TARGET).gdb-index && objcopy --add-section '.gdb_index=$(TARGET).gdb-index' --set-section-flags '.gdb_index=readonly' '$(TARGET)' '$(TARGET)' && rm -f $(TARGET).gdb-index || true

dist: 
	@$(CHK_DIR_EXISTS) .tmp/loclass1.0.0 || $(MKDIR) .tmp/loclass1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) .tmp/loclass1.0.0/ && (cd `dirname .tmp/loclass1.0.0` && $(TAR) loclass1.0.0.tar loclass1.0.0 && $(COMPRESS) loclass1.0.0.tar) && $(MOVE) `dirname .tmp/loclass1.0.0`/loclass1.0.0.tar.gz . && $(DEL_FILE) -r .tmp/loclass1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


check: first

compiler_rcc_make_all:
compiler_rcc_clean:
compiler_uic_make_all:
compiler_uic_clean:
compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: 

####### Compile

main.o: main.c cipherutils.h \
		cipher.h \
		ikeys.h \
		elite_crack.h
	$(CC) -c $(CFLAGS) $(INCPATH) -o main.o main.c

cipher.o: cipher.c cipher.h \
		cipherutils.h \
		fileutils.h\
		optimized_cipher.h
	$(CC) -c $(CFLAGS) $(INCPATH) -o cipher.o cipher.c

cipherutils.o: cipherutils.c cipherutils.h \
		fileutils.h
	$(CC) -c $(CFLAGS) $(INCPATH) -o cipherutils.o cipherutils.c

ikeys.o: ikeys.c cipherutils.h \
		des.h
	$(CC) -c $(CFLAGS) $(INCPATH) -o ikeys.o ikeys.c

des.o: des.c des.h
	$(CC) -c $(CFLAGS) $(INCPATH) -o des.o des.c

elite_crack.o: elite_crack.c cipherutils.h \
		cipher.h \
		ikeys.h \
		elite_crack.h \
		fileutils.h \
		des.h
	$(CC) -c $(CFLAGS) $(INCPATH) -o elite_crack.o elite_crack.c

fileutils.o: fileutils.c fileutils.h
	$(CC) -c $(CFLAGS) $(INCPATH) -o fileutils.o fileutils.c

optimized_cipher.o: optimized_cipher.c optimized_cipher.h
	$(CC) -c $(CFLAGS) $(INCPATH) -o optimized_cipher.o optimized_cipher.c

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

