/*
  +----------------------------------------------------------------------+
  | PHP-X                                                               |
  +----------------------------------------------------------------------+
  | This source file is subject to version 2.0 of the Apache license,    |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.apache.org/licenses/LICENSE-2.0.html                      |
  | If you did not receive a copy of the Apache2.0 license and are unable|
  | to obtain it through the world-wide-web, please send a note to       |
  | license@swoole.com so we can mail you a copy immediately.            |
  +----------------------------------------------------------------------+
  | Author: Tianfeng Han  <mikan.tenny@gmail.com>                        |
  +----------------------------------------------------------------------+
*/

#include "phpx.h"

#include "zend_smart_str.h"

using namespace std;

namespace php
{

Variant Variant::serialize()
{
    smart_str serialized_data = { 0 };
    php_serialize_data_t var_hash;
    PHP_VAR_SERIALIZE_INIT(var_hash);
    php_var_serialize(&serialized_data, ptr(), &var_hash TSRMLS_CC);
    PHP_VAR_SERIALIZE_DESTROY(var_hash);
    Variant retval(serialized_data.s->val, serialized_data.s->len);
    smart_str_free(&serialized_data);
    retval.addRef();
    return retval;
}

Variant Variant::unserialize()
{
    php_unserialize_data_t var_hash;
    Variant retval;
    PHP_VAR_UNSERIALIZE_INIT(var_hash);

    char *data = Z_STRVAL_P(ptr());
    size_t length = Z_STRLEN_P(ptr());
    if (php_var_unserialize(retval.ptr(), (const uchar **) &data, (const uchar *) data + length, &var_hash))
    {
        retval.addRef();
        return retval;
    }
    else
    {
        return nullptr;
    }
}

Variant Variant::jsonEncode(zend_long options, zend_long depth)
{
    smart_str buf = { 0 };
    JSON_G(error_code) = PHP_JSON_ERROR_NONE;
    JSON_G(encode_max_depth) = (int) depth;

    php_json_encode(&buf, ptr(), (int) options);

    if (JSON_G(error_code) != PHP_JSON_ERROR_NONE && !(options & PHP_JSON_PARTIAL_OUTPUT_ON_ERROR))
    {
        smart_str_free(&buf);
        return false;
    }
    else
    {
        smart_str_0(&buf);
        return buf.s;
    }
}

Variant Variant::jsonDecode(zend_long options, zend_long depth)
{
    smart_str buf = { 0 };
    JSON_G(error_code) = PHP_JSON_ERROR_NONE;

    if (this->length() == 0)
    {
        JSON_G(error_code) = PHP_JSON_ERROR_SYNTAX;
        return nullptr;
    }

    options |= PHP_JSON_OBJECT_AS_ARRAY;
    Variant retval;
    php_json_decode_ex(retval.ptr(), Z_STRVAL_P(ptr()), Z_STRLEN_P(ptr()), options, depth);
    retval.addRef();
    return retval;
}

}
