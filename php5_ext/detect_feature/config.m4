dnl $Id$
dnl config.m4 for extension detect_feature

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(detect_feature, for detect_feature support,
dnl Make sure that the comment is aligned:
dnl [  --with-detect_feature             Include detect_feature support])

dnl Otherwise use enable:

 PHP_ARG_ENABLE(detect_feature, whether to enable detect_feature support,
dnl Make sure that the comment is aligned:
 [  --enable-detect_feature           Enable detect_feature support])

if test "$PHP_DETECT_FEATURE" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-detect_feature -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/detect_feature.h"  # you most likely want to change this
  dnl if test -r $PHP_DETECT_FEATURE/$SEARCH_FOR; then # path given as parameter
  dnl   DETECT_FEATURE_DIR=$PHP_DETECT_FEATURE
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for detect_feature files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       DETECT_FEATURE_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$DETECT_FEATURE_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the detect_feature distribution])
  dnl fi

  dnl # --with-detect_feature -> add include path
  dnl PHP_ADD_INCLUDE($DETECT_FEATURE_DIR/include)

  dnl # --with-detect_feature -> check for lib and symbol presence
  dnl LIBNAME=detect_feature # you may want to change this
  dnl LIBSYMBOL=detect_feature # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $DETECT_FEATURE_DIR/lib, DETECT_FEATURE_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_DETECT_FEATURELIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong detect_feature lib version or lib not found])
  dnl ],[
  dnl   -L$DETECT_FEATURE_DIR/lib -lm
  dnl ])
  dnl
  dnl PHP_SUBST(DETECT_FEATURE_SHARED_LIBADD)

  PHP_NEW_EXTENSION(detect_feature, detect_feature.c, $ext_shared)
fi
