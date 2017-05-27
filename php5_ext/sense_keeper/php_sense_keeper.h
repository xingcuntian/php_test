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

#ifndef PHP_SENSE_KEEPER_H
#define PHP_SENSE_KEEPER_H
extern zend_module_entry sense_keeper_module_entry;
#define phpext_sense_keeper_ptr &sense_keeper_module_entry

#define PHP_SENSE_KEEPER_VERSION "0.1.0" /* Replace with version number for your extension */

#ifdef PHP_WIN32
#	define PHP_SENSE_KEEPER_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_SENSE_KEEPER_API __attribute__ ((visibility("default")))
#else
#	define PHP_SENSE_KEEPER_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif
#include "szst_sensekeeper_sync.h"

PHP_MINIT_FUNCTION(sense_keeper);
PHP_MSHUTDOWN_FUNCTION(sense_keeper);
PHP_RINIT_FUNCTION(sense_keeper);
PHP_RSHUTDOWN_FUNCTION(sense_keeper);
PHP_MINFO_FUNCTION(sense_keeper);

PHP_FUNCTION(sk_add_blacklist_user);
PHP_FUNCTION(sk_del_blacklist_user);
PHP_FUNCTION(sk_get_blacklist);
PHP_FUNCTION(sk_get_blacklist_user_info);
PHP_FUNCTION(sk_chg_blacklist_user_name);
PHP_FUNCTION(sk_chg_blacklist_user_card_number);
PHP_FUNCTION(sk_chg_blacklist_user_image);
PHP_FUNCTION(sk_get_blacklist_status);

PHP_FUNCTION(sk_add_viplist_user);
PHP_FUNCTION(sk_del_viplist_user);
PHP_FUNCTION(sk_get_viplist);
PHP_FUNCTION(sk_get_viplist_user_info);
PHP_FUNCTION(sk_chg_viplist_user_name);
PHP_FUNCTION(sk_chg_viplist_user_card_number);
PHP_FUNCTION(sk_chg_viplist_user_image);
PHP_FUNCTION(sk_get_viplist_status);

PHP_FUNCTION(sk_add_userlist_user);
PHP_FUNCTION(sk_del_userlist_user);
PHP_FUNCTION(sk_get_userlist);
PHP_FUNCTION(sk_get_userlist_user_info);
PHP_FUNCTION(sk_chg_userlist_user_name);
PHP_FUNCTION(sk_chg_userlist_user_card_number);
PHP_FUNCTION(sk_chg_userlist_user_image);
PHP_FUNCTION(sk_get_userlist_status);

PHP_FUNCTION(sk_add_guestlist_user);
PHP_FUNCTION(sk_del_guestlist_user);
PHP_FUNCTION(sk_get_guestlist);
PHP_FUNCTION(sk_get_guestlist_user_info);
PHP_FUNCTION(sk_chg_guestlist_user_name);
PHP_FUNCTION(sk_chg_guestlist_user_card_number);
PHP_FUNCTION(sk_chg_guestlist_user_image);
PHP_FUNCTION(sk_get_guestlist_status);

/* 
  	Declare any global variables you may need between the BEGIN
	and END macros here:     

ZEND_BEGIN_MODULE_GLOBALS(sense_keeper)
	long  global_value;
	char *global_string;
ZEND_END_MODULE_GLOBALS(sense_keeper)
*/

/* In every utility function you add that needs to use variables 
   in php_sense_keeper_globals, call TSRMLS_FETCH(); after declaring other 
   variables used by that function, or better yet, pass in TSRMLS_CC
   after the last function argument and declare your utility function
   with TSRMLS_DC after the last declared argument.  Always refer to
   the globals in your function as SENSE_KEEPER_G(variable).  You are 
   encouraged to rename these macros something shorter, see
   examples in any other php module directory.
*/

#ifdef ZTS
#define SENSE_KEEPER_G(v) TSRMG(sense_keeper_globals_id, zend_sense_keeper_globals *, v)
#else
#define SENSE_KEEPER_G(v) (sense_keeper_globals.v)
#endif

#endif	/* PHP_SENSE_KEEPER_H */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
