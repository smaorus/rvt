# $Id: makefile,v 1.4 2009-12-22 15:14:55 user Exp $
#
# This source file is a part of the C=C Project.
# Copyright (C) 2003 Benny Godlin
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

srcdir	= .
ctool_topdir	= $(srcdir)/ctool
ctool_srcdir	= $(ctool_topdir)/src
ctool_incdir	= $(ctool_topdir)/include/ctool
objdir          = $(srcdir)/Debug
generated_dir   = $(srcdir)/generated
tmpdir          = $(objdir)/tmp


SHELL	= /bin/sh
CXX	= g++
MAKEDEP	= mkdir -p $(objdir); $(CXX) -M
LDFLAGS	= -shared #
INCDIRS = -I$(ctool_topdir)/include -I$(ctool_topdir)/include/ctool
AR	= ar
RANLIB	= ranlib
LEX		= flex -f --nounistd
YACC	= bison
SOFLAGS	= -shared

CPP_PATH = /usr/bin/cpp

CTOOLFLAGS = -D USE_GCC_4_CPP

CPPFLAGS = $(INCDIRS) -I. -D LIB_CPP=\"$(CPP_PATH)\" $(CTOOLFLAGS)
#CXXFLAGS = -g -Wall
CXXFLAGS = -O3 -Wall -g3 -gstabs1

RV_SRC	 = rv_treecomp.cpp rv_funcpair.cpp rv_typeeqmac.cpp rv_traversal.cpp \
           rv_ctool.cpp rv_parse.cpp rv_temps.cpp rv_consts.cpp rv_msg.cpp \
	       rv_walk.cpp rv_collect.cpp rv_propagate.cpp rv_replace.cpp \
	       rv_indfunc.cpp rv_funcnode.cpp rv_funcdfs.cpp rv_semchecker.cpp \
	       rv_loops.cpp rv_arrays.cpp rv_etc.cpp rv_array_assume.cpp \
	       rv_graph.cpp rv_gen.cpp rv_genctx.cpp rv_decompose.cpp rv_dbg.cpp \
	       rv_options.cpp rv_main.cpp rv_dataflow.cpp rv_commands.cpp
CTOOLSRC = context.cpp decl.cpp express.cpp parseenv.cpp \
           project.cpp stemnt.cpp symbol.cpp token.cpp location.cpp \
           PrintTraversal.cpp
GEN_SRC  = rv_lexer.cpp rv_gram.cpp
OTHERSRC = gen_prog.cpp 

SRC	 = $(RV_SRC) $(patsubst %.cpp, $(ctool_srcdir)/%.cpp, $(CTOOLSRC))
HDR	 = $(patsubst $(srcdir)/include/%, %, $(wildcard $(ctool_incdir)/*.h))
OBJ	 = $(patsubst %.cpp, $(objdir)/%.o, $(RV_SRC) $(CTOOLSRC) $(GEN_SRC) )
DEP	 = $(patsubst %.cpp, $(objdir)/%.d, $(RV_SRC) $(CTOOLSRC) $(GEN_SRC) $(OTHERSRC) )

CTOOLLY	 = $(ctool_topdir)/lexer.cpp $(ctool_topdir)/gram.cpp
CTOOLOBJ = $(patsubst %.cpp, $(objdir)/%.o, $(CTOOLSRC) $(CTOOLLY) )

.FORCE:
.PHONY: depend install clean distclean maintainer-clean dist

all: $(objdir)/rvt # $(objdir)/gen_prog
	rm -rf $(tmpdir)
# ../lib/librvt.a ../lib/librvt.so

#../lib/librvt.a: $(OBJ)
#	@echo creating $(@F)
#	$(AR) cr $@ $(OBJ)
#	$(RANLIB) $@

#../lib/librvt.so: $(OBJ)
#	@echo linking $(@F)
#	$(CXX) $(SOFLAGS) -o $@ $(OBJ) $(LIBS)

$(objdir)/rvt: $(OBJ)
	@echo linking $(@F)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJ) 
# -lefence -g3

depend:	$(DEP)

tags:   ./*.h $(HDR) $(SRC) 
	ctags ./*.h $(HDR) $(SRC) 

$(objdir)/gen_prog: $(objdir)/gen_prog.o
	@echo linking $(@F)
	$(CXX) -g -o $(objdir)/$@ $^ 
# use -lefence to debug memory.

test_gen_prog: gen_prog
	@echo Testing $<
	\rm -f gp_test.*
	./$< -o gp_test
	gcc -g -Wall gp_test.c -o gp_test
	./gp_test

install: all
	chmod a+rx $(srcdir)/tools/scripts/*
	$(srcdir)/tools/scripts/make_cbmc # build cbmc, goto-cc, goto-instrument

test_rvt: install
	mkdir -p $(srcdir)/test/run; cd $(srcdir)/test/run; echo Tests will run at "`whoami`@`hostname`:`pwd`"; perl ../rvtest/rvtest.pl ../../$(objdir)/rvt

uninstall:
	# $(INSTALL) ../lib/librvt.a $(DESTDIR)$(libdir)
	# $(INSTALL) ../lib/librvt.so $(DESTDIR)$(libdir)
	# $(INSTALL) -d $(DESTDIR)$(includedir)/ctool
	# for header in $(HDR); do \
    #       $(INSTALL) $$header $(DESTDIR)$(includedir)/ctool; \
    #     done



clean:
	rm -rf ../lib/librvt.a ../lib/librvt.so rvt
#	rm -f $(OBJ) $(DEP)
	rm -rf $(tmpdir) $(objdir) $(generated_dir)

distclean:	clean
	rm -f Makefile

maintainer-clean: distclean

$(objdir)/%.o:	%.cpp $(objdir)/%.d
	@echo compiling $(@F)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

$(objdir)/%.o:	$(ctool_srcdir)/%.cpp
	@echo compiling $(@F)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

$(objdir)/%.o:	$(generated_dir)/%.cpp
	@echo compiling $(@F)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

$(objdir)/%.d:	%.cpp %.h
	@echo generating dependencies for $(<F)
	$(SHELL) -ec '$(MAKEDEP) $(CPPFLAGS) $< | sed "s#$*\\.o[ :]*#\\$(objdir)/$*\\.d \\$(objdir)/$*\\.o : #g" > $@'

$(objdir)/%.d:	%.cpp
	@echo generating dependencies for $(<F)
	$(SHELL) -ec '$(MAKEDEP) $(CPPFLAGS) $< | sed "s#$*\\.o[ :]*#\\$(objdir)/$*\\.d \\$(objdir)/$*\\.o : #g" > $@'

$(objdir)/%.d:	$(ctool_srcdir)/%.cpp $(ctool_incdir)/%.h
	@echo generating dependencies for $(<F)
	$(SHELL) -ec '$(MAKEDEP) $(CPPFLAGS) $< | sed "s#$*\\.o[ :]*#\\$(objdir)/$*\\.d \\$(objdir)/$*\\.o : #g" > $@'

$(objdir)/%.d:	$(generated_dir)/%.cpp $(generated_dir)/%.h
	@echo generating dependencies for $(<F)
	$(SHELL) -ec '$(MAKEDEP) $(CPPFLAGS) $< | sed "s#$*\\.o[ :]*#\\$(objdir)/$*\\.d \\$(objdir)/$*\\.o : #g" > $@'

$(generated_dir)/rv_lexer.cpp: $(srcdir)/rv_lexer.l $(generated_dir)/rv_gram.h
	@echo generating $(@F)
	$(LEX) $<
	mv lex.yy.c $(generated_dir)/rv_lexer.cpp

$(generated_dir)/rv_gram.cpp: $(srcdir)/rv_gram.y
	@echo generating $(@F)
	mkdir -p $(generated_dir) $(tmpdir)
	$(YACC) -y -o $(generated_dir)/rv_gram.cpp $<

$(generated_dir)/rv_gram.h: $(srcdir)/rv_gram.y
	@echo generating $(@F)
	mkdir -p $(generated_dir) $(tmpdir)
	$(YACC) -y --defines=$(generated_dir)/rv_gram.h -o $(tmpdir)/y.tab.c $<

ifneq (,$(findstring depend, $(MAKECMDGOALS)))
$(DEP): $(objdir)/%.d:	.FORCE
endif

ifeq (,$(filter $(MAKECMDGOALS), depend doc clean distclean maintainer-clean tags))
-include $(DEP)
endif
