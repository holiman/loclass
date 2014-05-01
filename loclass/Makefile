#-----------------------------------------------------------------------------
# This code is licensed to you under the terms of the GNU GPL, version 2 or,
# at your option, any later version. See the LICENSE.txt file for the text of
# the license.
#-----------------------------------------------------------------------------

CC=gcc
CXX=g++

#VPATH = ../common
OBJDIR = ./obj/

#LDLIBS = -L/opt/local/lib -L/usr/local/lib -lreadline -lpthread ../liblua/liblua.a
#LDFLAGS = $(COMMON_FLAGS)
CFLAGS = -std=c99 -I. -g -O4
#CFLAGS = -std=c99 -I. -I../include -I../common -I/opt/local/include -I../liblua -Wall $(COMMON_FLAGS) -g -O4 
CORESRCS = cipher.c  cipherutils.c  des.c  des.c  ikeys.c  main.c
COREOBJS = $(CORESRCS:%.c=$(OBJDIR)/%.o)

RM = rm -f
BINS = iclazz
CLEAN = iclazz $(CMDOBJS) $(OBJDIR)/*.o *.o


iclazz: $(COREOBJS)
	$(CXX) $(CXXFLAGS) $^ $(LDLIBS) -o $@

$(OBJDIR)/%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(RM) $(CLEAN)

