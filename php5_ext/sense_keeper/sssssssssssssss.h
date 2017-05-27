/*
 * Copyright (c) 2017 SenseTime
 * v1.0 April 10, 2017 by shezhonghua@sensetime.com
*/
#ifndef SZ_ST_SENSE_KEEPER_SYNC_H
#define SZ_ST_SENSE_KEEPER_SYNC_H

#define SK_OK                            0  // 成功
#define SK_ERROR                        -1  // 未知错误
#define SK_ERR_INVALIAD_ARGS            -2  // 参数错误
#define SK_ERR_SYNC_SERVICE_IS_STOP     -3  // 同步服务未启动
#define SK_ERR_SYNC_SERVICE_IS_BUSY     -4  // 同步服务忙
#define SK_ERR_INVALID_IMAGE            -5  // 输入图像检测失败
#define SK_ERR_SIMILAR_IMAGE_EXISTED    -6  // 存在相似的图片
#define SK_ERR_USER_EXISTED             -7  // 用户已经存在
#define SK_ERR_USERLIST_OVERFLOW        -8  // 用户列表已满
#define SK_ERR_WRITE_IMAGE              -9  // 写图片文件失败
#define SK_ERR_NO_SUCH_USER             -10 // 没有这个用户
#define SK_ERR_BUFFER_SPACE             -11 // buffer空间不足


//////////////////////////

/*
 * 在SenseKeeper系统中, 有5类用户: 黑名单用户、VIP用户、普通用户、访客、陌生人
 * 其中，黑名单用户、VIP用户、普通用户、访客的图片需要同步到SenseKeeper中，
 * 本接口描述了增加、删除用户的接口。如果需要更改图片，则先删除再新增。
 *
*/

/*
 * 功能：获取szst_sensekeeper_sync库的版本号
*/
const char* get_library_version();

/*
 * 功能：获取Synchronization Service的版本号
*/
const char* get_sync_service_version();

/*
 * 功能：添加黑名单用户
 * 输入：user_id,         在senseGuard系统中可唯一标识用户的标识符
 *       image_path,      存储黑名单用户的人脸图片的路径名，支持jpg和png格式
 * 输出：face_image_path, 返回剪裁后的人脸图片，jpg格式
 * 
 * 返回值：SK_OK
 *         SK_ERR_INVALIAD_ARGS
 *         SK_ERR_SYNC_SERVICE_IS_STOP   
 *         SK_ERR_SYNC_SERVICE_IS_BUSY
 *         SK_ERR_INVALID_IMAGE
 *         SK_ERR_USER_EXISTED
 *         SK_ERR_SIMILAR_IMAGE_EXISTED
 *         SK_ERR_USERLIST_OVERFLOW
 *         SK_ERR_WRITE_IMAGE
*/
int add_blacklist_user(const char *user_id, const char *image_path, const char *face_image_path);

/*
 * 功能：删除黑名单用户
 * 输入：user_id, 在senseGuard系统中可唯一标识用户的标识符
 * 输出：
 * 返回值：SK_OK
 *         SK_ERR_INVALIAD_ARGS
 *         SK_ERR_SYNC_SERVICE_IS_STOP   
 *         SK_ERR_SYNC_SERVICE_IS_BUSY
 *         SK_ERR_NO_SUCH_USER
*/
int del_blacklist_user(const char *user_id);

/*
 * 功能：获取黑名单用户列表
 * 输入：
 * 输出：user_list, 回传用户列表的指针，需调用free_userlist释放内存
 *       count,     用户的数量
 * 返回值：SK_OK
 *         SK_ERR_INVALIAD_ARGS
 *         SK_ERR_SYNC_SERVICE_IS_STOP   
 *         SK_ERR_SYNC_SERVICE_IS_BUSY        
 */
int get_blacklist(char ***user_list, int &count);

/*
 * 功能：删除用户列表内存
 * 输入：user_list, 用户列表的指针
 *       count,     用户的数量
 * 输出：
 * 返回值：       
 */
void free_userlist(char **user_list, int count);

/*
 * 功能：获取黑名单用户的注册图片
 * 输入：user_id,     在senseGuard系统中可唯一标识用户的标识符
 * 输出：image_path,  存储黑名单用户的人脸图片的路径名，jpg格式
 *
 * 返回值：SK_OK
 *         SK_ERR_INVALIAD_ARGS
 *         SK_ERR_SYNC_SERVICE_IS_STOP   
 *         SK_ERR_SYNC_SERVICE_IS_BUSY
 *         SK_ERR_NO_SUCH_USER
 *         SK_ERR_WRITE_IMAGE
 *         SK_ERR_BUFFER_SPACE
*/
int get_blacklist_user_image(const char *user_id, char *image_path);

/*
 * 功能：获取黑名单用户列表的状态号
 * 输入：
 * 输出：cur_status, 当前状态号
 *       pre_status, 前一次状态号
 *
 * 返回值：SK_OK
 *         SK_ERR_INVALIAD_ARGS
 *         SK_ERR_SYNC_SERVICE_IS_STOP   
 *         SK_ERR_SYNC_SERVICE_IS_BUSY
*/
int get_blacklist_status(int &cur_status, int &pre_status);

//////////////////////////////////////

/*
 * 功能：添加VIP用户
 * 输入：user_id,         在senseGuard系统中可唯一标识用户的标识符
 *       image_path,      存储黑名单用户的人脸图片的路径名，支持jpg和png格式
 * 输出：face_image_path, 返回剪裁后的人脸图片，jpg格式
 * 
 * 返回值：SK_OK
 *         SK_ERR_INVALIAD_ARGS
 *         SK_ERR_SYNC_SERVICE_IS_STOP   
 *         SK_ERR_SYNC_SERVICE_IS_BUSY
 *         SK_ERR_INVALID_IMAGE
 *         SK_ERR_USER_EXISTED
 *         SK_ERR_SIMILAR_IMAGE_EXISTED
 *         SK_ERR_USERLIST_OVERFLOW
 *         SK_ERR_WRITE_IMAGE
*/
int add_viplist_user(const char *user_id, const char *image_path, const char *face_image_path);

/*
 * 功能：删除VIP用户
 * 输入：user_id, 在senseGuard系统中可唯一标识用户的标识符
 * 输出：
 * 返回值：SK_OK
 *         SK_ERR_INVALIAD_ARGS
 *         SK_ERR_SYNC_SERVICE_IS_STOP   
 *         SK_ERR_SYNC_SERVICE_IS_BUSY
 *         SK_ERR_NO_SUCH_USER
*/
int del_viplist_user(const char *user_id);

/*
 * 功能：获取VIP用户列表
 * 输入：
 * 输出：user_list, 回传用户列表的指针，需调用free_userlist释放内存
 *       count,     用户的数量
 * 返回值：SK_OK
 *         SK_ERR_INVALIAD_ARGS
 *         SK_ERR_SYNC_SERVICE_IS_STOP   
 *         SK_ERR_SYNC_SERVICE_IS_BUSY        
 */
int get_viplist(char ***user_list, int &count);

/*
 * 功能：获取VIP用户的注册图片
 * 输入：user_id,     在senseGuard系统中可唯一标识用户的标识符
 * 输出：image_path,  存储黑名单用户的人脸图片的路径名，jpg格式
 *
 * 返回值：SK_OK
 *         SK_ERR_INVALIAD_ARGS
 *         SK_ERR_SYNC_SERVICE_IS_STOP   
 *         SK_ERR_SYNC_SERVICE_IS_BUSY
 *         SK_ERR_NO_SUCH_USER
 *         SK_ERR_WRITE_IMAGE
 *         SK_ERR_BUFFER_SPACE
*/
int get_viplist_user_image(const char *user_id, char *image_path);

/*
 * 功能：获取VIP用户列表的状态号
 * 输入：
 * 输出：cur_status, 当前状态号
 *       pre_status, 前一次状态号
 *
 * 返回值：SK_OK
 *         SK_ERR_INVALIAD_ARGS
 *         SK_ERR_SYNC_SERVICE_IS_STOP   
 *         SK_ERR_SYNC_SERVICE_IS_BUSY
*/
int get_viplist_status(int &cur_status, int &pre_status);


/*
 * 功能：添加普通用户
 * 输入：user_id,         在senseGuard系统中可唯一标识用户的标识符
 *       image_path,      存储黑名单用户的人脸图片的路径名，支持jpg和png格式
 * 输出：face_image_path, 返回剪裁后的人脸图片，jpg格式
 * 
 * 返回值：SK_OK
 *         SK_ERR_INVALIAD_ARGS
 *         SK_ERR_SYNC_SERVICE_IS_STOP   
 *         SK_ERR_SYNC_SERVICE_IS_BUSY
 *         SK_ERR_INVALID_IMAGE
 *         SK_ERR_USER_EXISTED
 *         SK_ERR_SIMILAR_IMAGE_EXISTED
 *         SK_ERR_USERLIST_OVERFLOW
 *         SK_ERR_WRITE_IMAGE
*/
int add_userlist_user(const char *user_id, const char *image_path, const char *face_image_path);

/*
 * 功能：删除普通用户
 * 输入：user_id, 在senseGuard系统中可唯一标识用户的标识符
 * 输出：
 * 返回值：SK_OK
 *         SK_ERR_INVALIAD_ARGS
 *         SK_ERR_SYNC_SERVICE_IS_STOP   
 *         SK_ERR_SYNC_SERVICE_IS_BUSY
 *         SK_ERR_NO_SUCH_USER
*/
int del_userlist_user(const char *user_id);

/*
 * 功能：获取普通用户列表
 * 输入：
 * 输出：user_list, 回传用户列表的指针，需调用free_userlist释放内存
 *       count,     用户的数量
 * 返回值：SK_OK
 *         SK_ERR_INVALIAD_ARGS
 *         SK_ERR_SYNC_SERVICE_IS_STOP   
 *         SK_ERR_SYNC_SERVICE_IS_BUSY        
 */
int get_userlist(char ***user_list, int &count);

/*
 * 功能：获取普通用户的注册图片
 * 输入：user_id,     在senseGuard系统中可唯一标识用户的标识符
 *       len,         image_path内存的长度
 * 输出：image_path,  存储黑名单用户的人脸图片的路径名，jpg格式
 *
 * 返回值：SK_OK
 *         SK_ERR_INVALIAD_ARGS
 *         SK_ERR_SYNC_SERVICE_IS_STOP   
 *         SK_ERR_SYNC_SERVICE_IS_BUSY
 *         SK_ERR_NO_SUCH_USER
 *         SK_ERR_WRITE_IMAGE
 *         SK_ERR_BUFFER_SPACE
*/
int get_userlist_user_image(const char *user_id, char *image_path);

/*
 * 功能：获取普通用户列表的状态号
 * 输入：
 * 输出：cur_status, 当前状态号
 *       pre_status, 前一次状态号
 *
 * 返回值：SK_OK
 *         SK_ERR_INVALIAD_ARGS
 *         SK_ERR_SYNC_SERVICE_IS_STOP   
 *         SK_ERR_SYNC_SERVICE_IS_BUSY
*/
int get_userlist_status(int &cur_status, int &pre_status);


/*
 * 功能：添加访客用户
 * 输入：user_id,         在senseGuard系统中可唯一标识用户的标识符
 *       image_path,      存储黑名单用户的人脸图片的路径名，支持jpg和png格式
 * 输出：face_image_path, 返回剪裁后的人脸图片，jpg格式
 * 
 * 返回值：SK_OK
 *         SK_ERR_INVALIAD_ARGS
 *         SK_ERR_SYNC_SERVICE_IS_STOP   
 *         SK_ERR_SYNC_SERVICE_IS_BUSY
 *         SK_ERR_INVALID_IMAGE
 *         SK_ERR_USER_EXISTED
 *         SK_ERR_SIMILAR_IMAGE_EXISTED
 *         SK_ERR_USERLIST_OVERFLOW
 *         SK_ERR_WRITE_IMAGE
*/
int add_guestlist_user(const char *user_id, const char *image_path, const char *face_image_path);

/*
 * 功能：删除访客用户
 * 输入：user_id, 在senseGuard系统中可唯一标识用户的标识符
 * 输出：
 * 返回值：SK_OK
 *         SK_ERR_INVALIAD_ARGS
 *         SK_ERR_SYNC_SERVICE_IS_STOP   
 *         SK_ERR_SYNC_SERVICE_IS_BUSY
 *         SK_ERR_NO_SUCH_USER
*/
int del_guestlist_user(const char *user_id);
/*
 * 功能：获取访客用户列表
 * 输入：
 * 输出：user_list, 回传用户列表的指针，需调用free_userlist释放内存
 *       count,     用户的数量
 * 返回值：SK_OK
 *         SK_ERR_INVALIAD_ARGS
 *         SK_ERR_SYNC_SERVICE_IS_STOP   
 *         SK_ERR_SYNC_SERVICE_IS_BUSY        
 */
int get_guestlist(char ***user_list, int &count);

/*
 * 功能：获取访客用户的注册图片
 * 输入：user_id,     在senseGuard系统中可唯一标识用户的标识符
 * 输出：image_path,  存储黑名单用户的人脸图片的路径名，jpg格式
 *
 * 返回值：SK_OK
 *         SK_ERR_INVALIAD_ARGS
 *         SK_ERR_SYNC_SERVICE_IS_STOP   
 *         SK_ERR_SYNC_SERVICE_IS_BUSY
 *         SK_ERR_NO_SUCH_USER
 *         SK_ERR_WRITE_IMAGE
 *         SK_ERR_BUFFER_SPACE
*/
int get_guestlist_user_image(const char *user_id, char *image_path);

/*
 * 功能：获取访客用户列表的状态号
 * 输入：
 * 输出：cur_status, 当前状态号
 *       pre_status, 前一次状态号
 *
 * 返回值：SK_OK
 *         SK_ERR_INVALIAD_ARGS
 *         SK_ERR_SYNC_SERVICE_IS_STOP   
 *         SK_ERR_SYNC_SERVICE_IS_BUSY
*/
int get_guestlist_status(int &cur_status, int &pre_status);

///////////////////////////////////////////////////


#endif