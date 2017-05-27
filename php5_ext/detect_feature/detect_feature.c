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
#include "php_detect_feature.h"
static int le_detect_feature;

const zend_function_entry detect_feature_functions[] = {
	PHP_FE(detect_get_version,NULL)
	PHP_FE(detect_init_info,NULL)
        PHP_FE(detect_extract_feature,NULL)
        PHP_FE(detect_destroy_model,NULL)
	PHP_FE(detect_input_feature_db,	NULL)
        {NULL,NULL,NULL}
       // PHP_FE_END	/* Must be the last line in detect_feature_functions[] */
};
zend_module_entry detect_feature_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"detect_feature",
	detect_feature_functions,
	PHP_MINIT(detect_feature),
	PHP_MSHUTDOWN(detect_feature),
	PHP_RINIT(detect_feature),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(detect_feature),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(detect_feature),
#if ZEND_MODULE_API_NO >= 20010901
	PHP_DETECT_FEATURE_VERSION,
#endif
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_DETECT_FEATURE
ZEND_GET_MODULE(detect_feature)
#endif

PHP_MINIT_FUNCTION(detect_feature)
{
	return SUCCESS;
}
PHP_MSHUTDOWN_FUNCTION(detect_feature)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}

PHP_RINIT_FUNCTION(detect_feature)
{
	return SUCCESS;
}
PHP_RSHUTDOWN_FUNCTION(detect_feature)
{
	return SUCCESS;
}
PHP_MINFO_FUNCTION(detect_feature)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "detect_feature support", "enabled");
	php_info_print_table_end();
}

PHP_FUNCTION(detect_get_version)
{
  char *version;
  int len;
  char *ret;
  version = get_version(); 
  len = strlen(version);
  ret = (char*)emalloc(len);
  memcpy(ret, version, len);
  RETURN_STRINGL(ret,len,0);
}

PHP_FUNCTION(detect_init_info)
{
  char *detectModelPath;
  char *verifyModelPath;
  long minFaceWidth;
  int detect_len;
  int verify_len; 
  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ssl", &detectModelPath,&detect_len,&verifyModelPath, &verify_len,&minFaceWidth) == FAILURE) {
       return;
  }
 if( detect_init_info(detectModelPath,verifyModelPath,minFaceWidth) ){
     RETURN_TRUE;
   }else{
     RETURN_FALSE;
   }
}
PHP_FUNCTION(detect_input_feature_db)
{
	char *featureDB;
        int featureDB_len;
  if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"s",&featureDB,&featureDB_len) == FAILURE){
      return;
  } 
  if(detect_input_feature_db(featureDB)){
     RETURN_TRUE;
  }else{
     RETURN_FALSE;
  }       
}

PHP_FUNCTION(detect_extract_feature)
{
  char *imagePath;
  int str_len;
  int len;
  char *json_str;
  long int tagID;
  char *result_json;
  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "sl", &imagePath, &str_len,&tagID) == FAILURE) {
       return;
  }
  json_str = detect_extract_feature(imagePath,tagID);
  len = strlen(json_str);
  result_json = (char *)emalloc(len); 
  memcpy(result_json, json_str, len); 
  RETURN_STRINGL(result_json,len,0);
}

PHP_FUNCTION(detect_destroy_model)
{
   detect_destroy_model();
   RETURN_TRUE;
}
