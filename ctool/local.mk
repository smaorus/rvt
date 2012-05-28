# $Id: local.mk.in,v 1.2 2003/08/19 05:23:27 stefan Exp $
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

# Places to install libraries, binaries, etc, from Autoconf's info page

prefix		= /usr/local
exec_prefix	= ${prefix}
bindir		= ${exec_prefix}/bin
sbindir		= ${exec_prefix}/sbin
libexecdir	= ${exec_prefix}/libexec
datadir		= ${prefix}/share
sysconfdir	= ${prefix}/etc
sharedstatedir	= ${prefix}/com
localstatedir	= ${prefix}/var
libdir		= ${exec_prefix}/lib
includedir	= ${prefix}/include
oldincludedir	= /usr/include
infodir		= ${prefix}/info
mandir		= ${prefix}/man

abs_top_builddir= ..
abs_top_srcdir	= ..

CXX		= g++
MAKEDEP		= $(CXX) -M
CFLAGS		= 
CXXFLAGS	= -g -O2
LDFLAGS		= -shared #
LIBS		= 
AR		= ar
RANLIB		= ranlib
INSTALL		= ./install.sh -c
LEX			= flex
YACC		= bison

CPPFLAGS	= -I$(abs_top_builddir)/include -I$(abs_top_srcdir)/include 
LDFLAGS     = 
SOFLAGS		= -shared
CXXFLAGS	= 
LIBS		= 
