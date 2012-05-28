dnl $Id: configure.ac,v 1.3 2003/08/19 05:23:27 stefan Exp $
dnl
dnl This source file is a part of the ctool Project.
dnl Copyright (C) 2003 Stefan Seefeld
dnl
dnl This library is free software; you can redistribute it and/or
dnl modify it under the terms of the GNU Library General Public
dnl License as published by the Free Software Foundation; either
dnl version 2 of the License, or (at your option) any later version.
dnl
dnl This library is distributed in the hope that it will be useful,
dnl but WITHOUT ANY WARRANTY; without even the implied warranty of
dnl MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
dnl Library General Public License for more details.
dnl
dnl You should have received a copy of the GNU Library General Public
dnl License along with this library; if not, write to the
dnl Free Software Foundation, Inc., 675 Mass Ave, Cambridge,
dnl MA 02139, USA.
dnl
dnl Process this file with autoconf to produce a configure script.

dnl ------------------------------------------------------------------
dnl Autoconf initialization
dnl ------------------------------------------------------------------
AC_PREREQ(2.53)
AC_REVISION($Revision: 1.3 $)
AC_INIT(CTool, 2.11, ctool-develop@lists.sourceforge.net)
AC_CONFIG_SRCDIR(COPYING)
dnl AC_CONFIG_AUX_DIR(config)

AC_CANONICAL_HOST

AC_PROG_MAKE_SET
AC_PROG_LEX
AC_PROG_YACC
AC_PROG_CPP
AC_PROG_CC
AC_PROG_CXX
AC_PROG_RANLIB
AC_PROG_INSTALL

dnl ------------------------------------------------------------------
dnl Environment (this needs to go before AC_LANG(C++)
dnl ------------------------------------------------------------------

AC_LANG(C)
AC_HEADER_STDC
AC_CHECK_FUNCS(getenv putenv setenv unsetenv)
AC_LANG(C++)

dnl ------------------------------------------------------------------
dnl General flags
dnl ------------------------------------------------------------------

AC_MSG_NOTICE([platform specific system utilities])
AC_CHECK_FUNCS(strsignal)
AC_CHECK_HEADERS(string.h)
AC_CHECK_DECLS([strsignal])
AC_HEADER_SYS_WAIT

dnl ------------------------------------------------------------------
dnl Output substitution
dnl ------------------------------------------------------------------

AC_CONFIG_FILES([local.mk])
AC_CONFIG_FILES([Makefile src/Makefile examples/Makefile examples/ctdemo/Makefile])

mkdir -p lib
mkdir -p bin

AC_OUTPUT
