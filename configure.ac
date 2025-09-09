dnl   configuration script for the SPARC book.
dnl   Process this file with autoconf to produce configure.
dnl

define(SPARC_CONFIGURE_COPYRIGHT, [[
Copyright (C) 2016-2025 Artyom V. Poptsov <poptsov.artyom@gmail.com>

This file is part of Science, Programming, Art and Radioelectronics Club (SPARC)
book.

Science, Programming, Art and Radioelectronics Club (SPARC) book © 2016-2025 by
Artyom V. Poptsov is licensed under CC BY-SA 4.0

You should have received a copy of the Creative Commons Attribution-ShareAlike
4.0 International along with SPARC book.  If not, see
<https://creativecommons.org/licenses/by-sa/4.0/>.
]])

AC_INIT([SPARC], [5.0.0], [poptsov.artyom@gmail.com],
        [sparc],
        [https://github.com/artyom-poptsov/SPARC])

AC_COPYRIGHT(SPARC_CONFIGURE_COPYRIGHT)
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([build-aux/m4])

AM_INIT_AUTOMAKE([
  gnu
  silent-rules
  -Wall
  -Wno-portability
  color-tests
])

m4_ifdef([AM_SILENT_RULES], [AM_SILENT_RULES([yes])], [AC_SUBST([AM_DEFAULT_VERBOSITY],1)])

AC_CONFIG_FILES([Makefile])

# Generate a Makefile, based on the results.
AC_OUTPUT
