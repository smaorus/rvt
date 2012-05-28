# $Id: Makefile,v 1.5 2003/08/19 04:52:58 stefan Exp $
#
# This source file is a part of the ctool Project.
# Copyright (C) 2003 Stefan Seefeld
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Library General Public
# License as published by the Free Software Foundation; either
# version 2 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Library General Public License for more details.
#
# You should have received a copy of the GNU Library General Public
# License along with this library; if not, write to the
# Free Software Foundation, Inc., 675 Mass Ave, Cambridge,
# MA 02139, USA.

SHELL		:= /bin/sh

include ../local.mk

CPP_PATH:=/usr/bin/cpp

CTOOLFLAGS:= -D USE_GCC_4_CPP -D DEBUG

CPPFLAGS+= -D LIB_CPP=\"$(CPP_PATH)\" $(CTOOLFLAGS)
CXXFLAGS+= -g -Wall

SRC	:= lexer.cpp gram.cpp context.cpp decl.cpp express.cpp parseenv.cpp \
           project.cpp stemnt.cpp symbol.cpp token.cpp location.cpp \
           PrintTraversal.cpp
OBJ	:= $(patsubst %.cpp, %.o, $(SRC))
DEP	:= $(patsubst %.cpp, %.d, $(SRC))

vpath %.h  $(top_abs_builddir)/include $(top_abs_srcdir)/include
vpath %.cpp  $(srcdir)

.FORCE:
.PHONY: depend install clean distclean maintainer-clean dist

all: ../lib/libctool.a ../lib/libctool.so

../lib/libctool.a: $(OBJ)
	@echo creating $(@F)
	$(AR) cr $@ $(OBJ)
	$(RANLIB) $@

../lib/libctool.so: $(OBJ)
	@echo linking $(@F)
	$(CXX) $(SOFLAGS) -o $@ $(OBJ) $(LIBS)

depend:	$(DEP)

install: all

uninstall:

clean:
	rm -rf ../lib/libctool.a ../lib/libctool.so
	rm lexer.cpp gram.cpp gram.h $(OBJ) $(DEP)

distclean:	clean
	rm -f Makefile

maintainer-clean: distclean

%.o:	%.cpp
	@echo compiling $(@F)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

%.d:	%.cpp %.h
	@echo generating dependencies for $(<F)
	$(SHELL) -ec '$(MAKEDEP) $(CPPFLAGS) $< | sed "s/$*\\.o[ :]*/$*\\.d $*\\.o : /g" > $@'

lexer.cpp: lexer.l gram.h
	@echo generating lexer.cpp
	$(LEX) $<
	mv lex.yy.c lexer.cpp

gram.cpp gram.h:	gram.y
	@echo generating gram.cpp
	$(YACC) -d -b gram -o gram.cpp $<
	mv gram.hpp gram.h

ifneq (,$(findstring depend, $(MAKECMDGOALS)))
$(DEP): %.d:	.FORCE
endif

ifeq (,$(filter $(MAKECMDGOALS), depend doc clean distclean maintainer-clean))
-include $(DEP)
endif
