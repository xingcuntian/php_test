/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2013 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifndef PHP_DETECT_FEATURE_H
#define PHP_DETECT_FEATURE_H
#include "detect_feature.h"
extern zend_module_entry detect_feature_module_entry;
#define phpext_detect_feature_ptr &detect_feature_module_entry

#define PHP_DETECT_FEATURE_VERSION "0.1.0" /* Replace with version number for your extension */

#ifdef PHP_WIN32
#	define PHP_DETECT_FEATURE_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_DETECT_FEATURE_API __attribute__ ((visibility("default")))
#else
#	define PHP_DETECT_FEATURE_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

PHP_MINIT_FUNCTION(detect_feature);
PHP_MSHUTDOWN_FUNCTION(detect_feature);
PHP_RINIT_FUNCTION(detect_feature);
PHP_RSHUTDOWN_FUNCTION(detect_feature);
PHP_MINFO_FUNCTION(detect_feature);

PHP_FUNCTION(confirm_detect_feature_compiled);	/* For testing, remove later. */
PHP_FUNCTION(detect_get_version);
PHP_FUNCTION(detect_init_info);
PHP_FUNCTION(detect_extract_feature);
PHP_FUNCTION(detect_destroy_model);
PHP_FUNCTION(detect_input_feature_db);
/* 
  	Declare any global variables you may need between the BEGIN
	and END macros here:     

ZEND_BEGIN_MODULE_GLOBALS(detect_feature)
	long  global_value;
	char *global_string;
ZEND_END_MODULE_GLOBALS(detect_feature)
*/

/* In every utility function you add that needs to use variables 
   in php_detect_feature_globals, call TSRMLS_FETCH(); after declaring other 
   variables used by that function, or better yet, pass in TSRMLS_CC
   after the last function argument and declare your utility function
   with TSRMLS_DC after the last declared argument.  Always refer to
   the globals in your function as DETECT_FEATURE_G(variable).  You are 
   encouraged to rename these macros something shorter, see
   examples in any other php module directory.
*/

#ifdef ZTS
#define DETECT_FEATURE_G(v) TSRMG(detect_feature_globals_id, zend_detect_feature_globals *, v)
#else
#define DETECT_FEATURE_G(v) (detect_feature_globals.v)
#endif

#endif	/* PHP_DETECT_FEATURE_H */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
