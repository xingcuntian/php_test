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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_sense_keeper.h"

static int le_sense_keeper;

const zend_function_entry sense_keeper_functions[] = {
	PHP_FE(sk_add_blacklist_user,	NULL)
	PHP_FE(sk_del_blacklist_user,	NULL)
	PHP_FE(sk_get_blacklist,	NULL)
	// PHP_FE(sk_free_userlist,	NULL)
	PHP_FE(sk_get_blacklist_user_info, NULL)
	PHP_FE(sk_chg_blacklist_user_name, NULL)
	PHP_FE(sk_chg_blacklist_user_card_number, NULL)
	PHP_FE(sk_chg_blacklist_user_image,	NULL)
	PHP_FE(sk_get_blacklist_status,	NULL)

	 PHP_FE(sk_add_viplist_user,	NULL)
	 PHP_FE(sk_del_viplist_user,	NULL)
	 PHP_FE(sk_get_viplist,	NULL)
	 PHP_FE(sk_get_viplist_user_info,	NULL)
	 PHP_FE(sk_chg_viplist_user_name,	NULL)
	 PHP_FE(sk_chg_viplist_user_card_number,	NULL)
	 PHP_FE(sk_chg_viplist_user_image,	NULL)
	 PHP_FE(sk_get_viplist_status,	NULL)

	 PHP_FE(sk_add_userlist_user,	NULL)
	 PHP_FE(sk_del_userlist_user,	NULL)
	 PHP_FE(sk_get_userlist,	NULL)
	 PHP_FE(sk_get_userlist_user_info,	NULL)
	 PHP_FE(sk_chg_userlist_user_name,	NULL)
	 PHP_FE(sk_chg_userlist_user_card_number,	NULL)
	 PHP_FE(sk_chg_userlist_user_image,	NULL)
	 PHP_FE(sk_get_userlist_status,	NULL)

	 PHP_FE(sk_add_guestlist_user,	NULL)
	 PHP_FE(sk_del_guestlist_user,	NULL)
	 PHP_FE(sk_get_guestlist,	NULL)
	 PHP_FE(sk_get_guestlist_user_info,	NULL)
	 PHP_FE(sk_chg_guestlist_user_name,	NULL)
	 PHP_FE(sk_chg_guestlist_user_card_number,	NULL)
	 PHP_FE(sk_chg_guestlist_user_image,	NULL)
	 PHP_FE(sk_get_guestlist_status,	NULL)

	PHP_FE_END
};
/* }}} */

/* {{{ sense_keeper_module_entry
 */
zend_module_entry sense_keeper_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"sense_keeper",
	sense_keeper_functions,
	PHP_MINIT(sense_keeper),
	PHP_MSHUTDOWN(sense_keeper),
	PHP_RINIT(sense_keeper),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(sense_keeper),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(sense_keeper),
#if ZEND_MODULE_API_NO >= 20010901
	PHP_SENSE_KEEPER_VERSION,
#endif
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_SENSE_KEEPER
ZEND_GET_MODULE(sense_keeper)
#endif


PHP_MINIT_FUNCTION(sense_keeper)
{
	/* If you have INI entries, uncomment these lines 
	REGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}

PHP_MSHUTDOWN_FUNCTION(sense_keeper)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}

PHP_RINIT_FUNCTION(sense_keeper)
{
	return SUCCESS;
}

PHP_RSHUTDOWN_FUNCTION(sense_keeper)
{
	return SUCCESS;
}

PHP_MINFO_FUNCTION(sense_keeper)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "sense_keeper support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}

//================blacklist GROUP=========================
PHP_FUNCTION(sk_add_blacklist_user)
{
	char *user_id = NULL;
	char *user_name = NULL;
	char *card_number = NULL;
	char *image_path = NULL;
	char *face_image_path = NULL;
	int user_id_len,user_name_len,card_number_len,image_path_len,face_image_path_len;
	long ret;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "sssss",&user_id,&user_id_len,&user_name,&user_name_len,&card_number,&card_number_len,&image_path,&image_path_len,&face_image_path,&face_image_path_len))
	{
		return;
	}
	ret = add_blacklist_user(user_id,user_name,card_number,image_path,face_image_path);
	RETURN_LONG(ret);
}

PHP_FUNCTION(sk_del_blacklist_user)
{
	char *user_id = NULL;
	int  user_id_len;
	long ret;
	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s",&user_id,&user_id_len)){
		return;
	}
	ret = del_blacklist_user(user_id);
	RETURN_LONG(ret);
}

PHP_FUNCTION(sk_get_blacklist)
{
	char **user_list;
	int  count,i;
	long ret;
	ret = get_blacklist(&user_list,count);
	//printf("first string: %s  count = %d\n", user_list[0], count);
    array_init(return_value);
	add_assoc_long(return_value, "code", ret);
	if( ret == 0 ){
		zval *subarray;
		ALLOC_INIT_ZVAL(subarray);
		array_init(subarray);
		for( i=0; i< count; i++ ) {
		   add_next_index_string(subarray, user_list[i],1);
		}
		add_assoc_zval(return_value,"user_list",subarray);
    }
}


PHP_FUNCTION(sk_get_blacklist_user_info)
{
	char *user_id = NULL;
	char user_name[32] = {0};
	char card_number[32] = {0};

	char *image_path = NULL;
	int user_id_len,image_path_len;
	long ret;
	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"ss",&user_id,&user_id_len,&image_path,&image_path_len)) {
		return;
	}
	ret = get_blacklist_user_info(user_id,user_name,32,card_number,32,image_path);
	array_init(return_value);
	add_assoc_long(return_value,"code",ret);
	if ( ret == 0 ) {
		add_assoc_string(return_value,"user_name",user_name,1);
		add_assoc_string(return_value,"card_number",card_number,1);
		add_assoc_string(return_value,"image_path",image_path,1);
	}
}


PHP_FUNCTION(sk_chg_blacklist_user_name)
{
	char *user_id = NULL;
	char *user_name = NULL;
	int user_id_len,user_name_len;
	long ret;
	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"ss",&user_id,&user_id_len,&user_name,&user_name_len)){
		return;	
	}
	ret = chg_blacklist_user_name(user_id,user_name);
	RETURN_LONG(ret);

}


PHP_FUNCTION(sk_chg_blacklist_user_card_number)
{
	char *user_id = NULL;
	char *card_number = NULL;
	int user_id_len,card_number_len;
	long ret;
	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"ss",&user_id,&user_id_len,&card_number,&card_number_len)){
		return;	
	}
	ret = chg_blacklist_user_card_number(user_id,card_number);
	RETURN_LONG(ret);
}

PHP_FUNCTION(sk_chg_blacklist_user_image)
{
	char *user_id;
	char *image_path;
	char *face_image_path;
	int user_id_len,image_path_len,face_image_path_len;
	long ret;
	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"sss",&user_id,&user_id_len,&image_path,&image_path_len,&face_image_path,&face_image_path_len)){
		return;
	}
	ret = chg_blacklist_user_image(user_id,image_path,face_image_path);
	array_init(return_value);
	add_assoc_long(return_value,"code",ret);
	if (ret == 0) {
		add_assoc_string(return_value,"face_image_path",face_image_path,1);
	}
}

PHP_FUNCTION(sk_get_blacklist_status)
{
	int cur_status;
	int pre_status;
	long ret;
	array_init(return_value);
	ret = get_blacklist_status(cur_status,pre_status);
	add_assoc_long(return_value,"code",ret);
	if (ret == 0 ){
	  add_assoc_long(return_value,"cur_status",cur_status);
	  add_assoc_long(return_value,"pre_status",pre_status);
	}
}

// //=====================viplist GROUP=======================================================================

PHP_FUNCTION(sk_add_viplist_user)
{
	char *user_id = NULL;
	char *user_name = NULL;
	char *card_number = NULL;
	char *image_path = NULL;
	char *face_image_path = NULL;
	int user_id_len,user_name_len,card_number_len,image_path_len,face_image_path_len,return_code;
	long ret;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "sssss",&user_id,&user_id_len,&user_name,&user_name_len,&card_number,&card_number_len,&image_path,&image_path_len,&face_image_path,&face_image_path_len))
	{
		return;
	}
	ret = add_viplist_user(user_id,user_name,card_number,image_path,face_image_path);
	RETURN_LONG(ret)
}

PHP_FUNCTION(sk_del_viplist_user)
{
	char *user_id = NULL;
	int  user_id_len;
	long ret;
	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s",&user_id,&user_id_len)){
		return;
	}
	ret = del_viplist_user(user_id);
	RETURN_LONG(ret);
}

PHP_FUNCTION(sk_get_viplist)
{
	char **user_list;
	int count,i;
	long ret;
	ret = get_viplist(&user_list,count);
	array_init(return_value);
	add_assoc_long(return_value, "code", ret);
	if( ret == 0 ){
		zval *subarray;
		ALLOC_INIT_ZVAL(subarray);
		array_init(subarray);
		for( i=0; i< count; i++ ) {
		   add_next_index_string(subarray, user_list[i],1);
		}
		add_assoc_zval(return_value,"user_list",subarray);
    }
}

PHP_FUNCTION(sk_get_viplist_user_info)
{
	char *user_id = NULL;
	char user_name[32] = {0};
	char card_number[32] = {0};

	char *image_path = NULL;
	int user_id_len,image_path_len;
	long ret;
	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"ss",&user_id,&user_id_len,&image_path,&image_path_len)) {
		return;
	}
	ret = get_viplist_user_info(user_id,user_name,32,card_number,32,image_path);
	array_init(return_value);
	add_assoc_long(return_value,"code",ret);
	if ( ret == 0 ) {
		add_assoc_string(return_value,"user_name",user_name,1);
		add_assoc_string(return_value,"card_number",card_number,1);
		add_assoc_string(return_value,"image_path",image_path,1);
	}
}

PHP_FUNCTION(sk_chg_viplist_user_name)
{
	char *user_id = NULL;
	char *user_name = NULL;
	int user_id_len,user_name_len;
	long ret;
	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"ss",&user_id,&user_id_len,&user_name,&user_name_len)){
		return;	
	}
	ret = chg_viplist_user_name(user_id,user_name);
	RETURN_LONG(ret);
}

PHP_FUNCTION(sk_chg_viplist_user_card_number) 
{
	char *user_id = NULL;
	char *card_number = NULL;
	int user_id_len,card_number_len;
	long ret;
	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"ss",&user_id,&user_id_len,&card_number,&card_number_len)){
		return;	
	}
	ret = chg_viplist_user_card_number(user_id,card_number);
	RETURN_LONG(ret);
}

PHP_FUNCTION(sk_chg_viplist_user_image)
{
	char *user_id;
	char *image_path;
	char *face_image_path;
	int user_id_len,image_path_len,face_image_path_len;
	long ret;
	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"sss",&user_id,&user_id_len,&image_path,&image_path_len,&face_image_path,&face_image_path_len)){
		return;
	}
	ret = chg_viplist_user_image(user_id,image_path,face_image_path);
	array_init(return_value);
	add_assoc_long(return_value,"code",ret);
	if (ret == 0) {
		add_assoc_string(return_value,"face_image_path",face_image_path,1);
	}
}

PHP_FUNCTION(sk_get_viplist_status)
{
	int cur_status;
	int pre_status;
	long ret;
	array_init(return_value);
	ret = get_viplist_status(cur_status,pre_status);
	add_assoc_long(return_value,"code",ret);
	if (ret == 0 ){
	  add_assoc_long(return_value,"cur_status",cur_status);
	  add_assoc_long(return_value,"pre_status",pre_status);
	}
}

// //=====================userlist GROUP=======================================================================

PHP_FUNCTION(sk_add_userlist_user)
{
	char *user_id = NULL;
	char *user_name = NULL;
	char *card_number = NULL;
	char *image_path = NULL;
	char *face_image_path = NULL;
	int user_id_len,user_name_len,card_number_len,image_path_len,face_image_path_len,return_code;
	long ret;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "sssss",&user_id,&user_id_len,&user_name,&user_name_len,&card_number,&card_number_len,&image_path,&image_path_len,&face_image_path,&face_image_path_len))
	{
		return;
	}
	ret = add_userlist_user(user_id,user_name,card_number,image_path,face_image_path);
	RETURN_LONG(ret)
}

PHP_FUNCTION(sk_del_userlist_user)
{
	char *user_id = NULL;
	int  user_id_len;
	long ret;
	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s",&user_id,&user_id_len)){
		return;
	}
	ret = del_userlist_user(user_id);
	RETURN_LONG(ret);
}

PHP_FUNCTION(sk_get_userlist)
{
	char **user_list;
	int count,i;
	long ret;
	ret = get_userlist(&user_list,count);
	array_init(return_value);
	add_assoc_long(return_value, "code", ret);
	if( ret == 0 ){
		zval *subarray;
		ALLOC_INIT_ZVAL(subarray);
		array_init(subarray);
		for( i=0; i< count; i++ ) {
		   add_next_index_string(subarray, user_list[i],1);
		}
		add_assoc_zval(return_value,"user_list",subarray);
    }
}


PHP_FUNCTION(sk_get_userlist_user_info)
{
	char *user_id = NULL;
	char user_name[32] = {0};
	char card_number[32] = {0};

	char *image_path = NULL;
	int user_id_len,image_path_len;
	long ret;
	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"ss",&user_id,&user_id_len,&image_path,&image_path_len)) {
		return;
	}
	ret = get_userlist_user_info(user_id,user_name,32,card_number,32,image_path);
	array_init(return_value);
	add_assoc_long(return_value,"code",ret);
	if ( ret == 0 ) {
		add_assoc_string(return_value,"user_name",user_name,1);
		add_assoc_string(return_value,"card_number",card_number,1);
		add_assoc_string(return_value,"image_path",image_path,1);
	}
}


PHP_FUNCTION(sk_chg_userlist_user_name)
{
	char *user_id = NULL;
	char *user_name = NULL;
	int user_id_len,user_name_len;
	long ret;
	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"ss",&user_id,&user_id_len,&user_name,&user_name_len)){
		return;	
	}
	ret = chg_userlist_user_name(user_id,user_name);
	RETURN_LONG(ret);
}

PHP_FUNCTION(sk_chg_userlist_user_card_number) 
{
	char *user_id = NULL;
	char *card_number = NULL;
	int user_id_len,card_number_len;
	long ret;
	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"ss",&user_id,&user_id_len,&card_number,&card_number_len)){
		return;	
	}
	ret = chg_userlist_user_card_number(user_id,card_number);
	RETURN_LONG(ret);
}

PHP_FUNCTION(sk_chg_userlist_user_image)
{
	char *user_id;
	char *image_path;
	char *face_image_path;
	int user_id_len,image_path_len,face_image_path_len;
	long ret;
	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"sss",&user_id,&user_id_len,&image_path,&image_path_len,&face_image_path,&face_image_path_len)){
		return;
	}
	ret = chg_userlist_user_image(user_id,image_path,face_image_path);
	array_init(return_value);
	add_assoc_long(return_value,"code",ret);
	if (ret == 0) {
		add_assoc_string(return_value,"face_image_path",face_image_path,1);
	}
}

PHP_FUNCTION(sk_get_userlist_status)
{
	int cur_status;
	int pre_status;
	long ret;
	array_init(return_value);
	ret = get_userlist_status(cur_status,pre_status);
	add_assoc_long(return_value,"code",ret);
	if (ret == 0 ){
	  add_assoc_long(return_value,"cur_status",cur_status);
	  add_assoc_long(return_value,"pre_status",pre_status);
	}
}

// //=====================guestlist GROUP=======================================================================
PHP_FUNCTION(sk_add_guestlist_user)
{
	char *user_id = NULL;
	char *user_name = NULL;
	char *card_number = NULL;
	char *image_path = NULL;
	char *face_image_path = NULL;
	int user_id_len,user_name_len,card_number_len,image_path_len,face_image_path_len,return_code;
	long ret;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "sssss",&user_id,&user_id_len,&user_name,&user_name_len,&card_number,&card_number_len,&image_path,&image_path_len,&face_image_path,&face_image_path_len))
	{
		return;
	}
	ret = add_guestlist_user(user_id,user_name,card_number,image_path,face_image_path);
	RETURN_LONG(ret)
}

PHP_FUNCTION(sk_del_guestlist_user)
{
	char *user_id = NULL;
	int  user_id_len;
	long ret;
	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s",&user_id,&user_id_len)){
		return;
	}
	ret = del_guestlist_user(user_id);
	RETURN_LONG(ret);
}

PHP_FUNCTION(sk_get_guestlist)
{
	char **user_list;
	int count,i;
	long ret;
	ret = get_guestlist(&user_list,count);
	array_init(return_value);
	add_assoc_long(return_value, "code", ret);
	if( ret == 0 ){
		zval *subarray;
		ALLOC_INIT_ZVAL(subarray);
		array_init(subarray);
		for( i=0; i< count; i++ ) {
		   add_next_index_string(subarray, user_list[i],1);
		}
		add_assoc_zval(return_value,"user_list",subarray);
    }
}

PHP_FUNCTION(sk_get_guestlist_user_info)
{
	char *user_id = NULL;
	char user_name[32] = {0};
	char card_number[32] = {0};

	char *image_path = NULL;
	int user_id_len,image_path_len;
	long ret;
	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"ss",&user_id,&user_id_len,&image_path,&image_path_len)) {
		return;
	}
	ret = get_guestlist_user_info(user_id,user_name,32,card_number,32,image_path);
	array_init(return_value);
	add_assoc_long(return_value,"code",ret);
	if ( ret == 0 ) {
		add_assoc_string(return_value,"user_name",user_name,1);
		add_assoc_string(return_value,"card_number",card_number,1);
		add_assoc_string(return_value,"image_path",image_path,1);
	}
}

PHP_FUNCTION(sk_chg_guestlist_user_name)
{
	char *user_id = NULL;
	char *user_name = NULL;
	int user_id_len,user_name_len;
	long ret;
	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"ss",&user_id,&user_id_len,&user_name,&user_name_len)){
		return;	
	}
	ret = chg_guestlist_user_name(user_id,user_name);
	RETURN_LONG(ret);
}

PHP_FUNCTION(sk_chg_guestlist_user_card_number) 
{
	char *user_id = NULL;
	char *card_number = NULL;
	int user_id_len,card_number_len;
	long ret;
	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"ss",&user_id,&user_id_len,&card_number,&card_number_len)){
		return;	
	}
	ret = chg_guestlist_user_card_number(user_id,card_number);
	RETURN_LONG(ret);
}

PHP_FUNCTION(sk_chg_guestlist_user_image)
{
	char *user_id;
	char *image_path;
	char *face_image_path;
	int user_id_len,image_path_len,face_image_path_len;
	long ret;
	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"sss",&user_id,&user_id_len,&image_path,&image_path_len,&face_image_path,&face_image_path_len)){
		return;
	}
	ret = chg_guestlist_user_image(user_id,image_path,face_image_path);
	array_init(return_value);
	add_assoc_long(return_value,"code",ret);
	if (ret == 0) {
		add_assoc_string(return_value,"face_image_path",face_image_path,1);
	}
}

PHP_FUNCTION(sk_get_guestlist_status)
{
	int cur_status;
	int pre_status;
	long ret;
	array_init(return_value);
	ret = get_guestlist_status(cur_status,pre_status);
	add_assoc_long(return_value,"code",ret);
	if (ret == 0 ){
	  add_assoc_long(return_value,"cur_status",cur_status);
	  add_assoc_long(return_value,"pre_status",pre_status);
	}
}
