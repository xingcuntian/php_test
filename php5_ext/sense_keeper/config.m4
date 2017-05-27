dnl $Id$
dnl config.m4 for extension sense_keeper

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(sense_keeper, for sense_keeper support,
dnl Make sure that the comment is aligned:
dnl [  --with-sense_keeper             Include sense_keeper support])

dnl Otherwise use enable:

PHP_ARG_ENABLE(sense_keeper, whether to enable sense_keeper support,
dnl Make sure that the comment is aligned:
[  --enable-sense_keeper           Enable sense_keeper support])

if test "$PHP_SENSE_KEEPER" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-sense_keeper -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/sense_keeper.h"  # you most likely want to change this
  dnl if test -r $PHP_SENSE_KEEPER/$SEARCH_FOR; then # path given as parameter
  dnl   SENSE_KEEPER_DIR=$PHP_SENSE_KEEPER
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for sense_keeper files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       SENSE_KEEPER_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$SENSE_KEEPER_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the sense_keeper distribution])
  dnl fi

  dnl # --with-sense_keeper -> add include path
  dnl PHP_ADD_INCLUDE($SENSE_KEEPER_DIR/include)

  dnl # --with-sense_keeper -> check for lib and symbol presence
  dnl LIBNAME=sense_keeper # you may want to change this
  dnl LIBSYMBOL=sense_keeper # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $SENSE_KEEPER_DIR/lib, SENSE_KEEPER_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_SENSE_KEEPERLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong sense_keeper lib version or lib not found])
  dnl ],[
  dnl   -L$SENSE_KEEPER_DIR/lib -lm
  dnl ])
  dnl
  dnl PHP_SUBST(SENSE_KEEPER_SHARED_LIBADD)

  PHP_NEW_EXTENSION(sense_keeper, sense_keeper.c, $ext_shared)
fi
