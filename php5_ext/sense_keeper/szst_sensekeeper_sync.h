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
 * 在SenseGuard系统中, 有5类用户: 黑名单用户、VIP用户、普通用户、访客、陌生人
 * 其中，黑名单用户、VIP用户、普通用户、访客的信息需要同步到SenseKeeper中，
 * 本接口描述了增加、删除用户的接口。
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

/*------ black list user ------------------------------------------------------------------------------*/

/*
 * 功能：添加黑名单用户
 * 输入：user_id,         在senseGuard系统中可唯一标识用户的标识符
 *       user_name,       用户名,以UTF-8编码，可以为null
 *       card_number,     用户对应IC的卡号，可以为null
 *       image_path,      存储黑名单用户的人脸图片的路径名，支持jpg格式
 *       face_image_path, 返回剪裁后的人脸图片，jpg格式
*/
int add_blacklist_user(const char *user_id, const char *user_name, const char *card_number, const char *image_path, const char *face_image_path);

/*
 * 功能：删除黑名单用户
 * 输入：user_id, 在senseGuard系统中可唯一标识用户的标识符
 * 输出：
*/
int del_blacklist_user(const char *user_id);

/*
 * 功能：获取黑名单用户列表
 * 输入：
 * 输出：user_list, 回传用户列表的指针，需调用free_userlist释放内存
 *       count,     用户的数量       
 */
int get_blacklist(char ***user_list, int &count);

/*
 * 功能：删除用户列表内存
 * 输入：user_list, 用户列表的指针
 *       count,     用户的数量
 * 输出：
 */
void free_userlist(char **user_list, int count);

/*
 * 功能：获取黑名单用户的注册图片
 * 输入：user_id,     在senseGuard系统中可唯一标识用户的标识符
 *       user_name,   保存用户名的内存，用户名以utf8编码，可以为null
 *       len1,        user_name内存大小
 *       card_number, 保存IC卡号的内存，可以为null 
 *       len2,        card_number内存大小
 * 输出： image_path,  存储黑名单用户的人脸图片的路径名，jpg格式
 *       user_name,   用户名
 *       card_number, IC卡号
*/
int get_blacklist_user_info(const char *user_id, char *user_name, int len1, char *card_number, int len2, const char *image_path);

/*
 * 功能：修改用户名
 * 输入：user_id,    用户的标识符
 *       user_name,  用户名, 以UTF-8编码，不能为null
*/
int chg_blacklist_user_name(const char * user_id, const char *user_name);

/*
 * 功能：修改用户名
 * 输入：user_id,     用户的标识符
 *       card_number, IC卡号, 不能为null
*/
int chg_blacklist_user_card_number(const char *user_id, const char *card_number);

/*
 * 功能：修改注册图片
 * 输入：user_id,         用户的标识符
 *       image_path,      存储黑名单用户的人脸图片的路径名，支持jpg格式
 *       face_image_path, 返回剪裁后的人脸图片，jpg格式
*/
int chg_blacklist_user_image(const char *user_id, const char *image_path, const char *face_image_path);
	
/*
 * 功能：获取黑名单用户列表的状态号
 * 输入：
 * 输出：cur_status, 当前状态号
 *      pre_status, 前一次状态号
*/
int get_blacklist_status(int &cur_status, int &pre_status);


/*------ VIP user list ------------------------------------------------------------------------------*/


int add_viplist_user(const char *user_id, const char *user_name, 
const char *card_number, const char *image_path, const char *face_image_path);

int del_viplist_user(const char *user_id);

int get_viplist(char ***user_list, int &count);

int get_viplist_user_info(const char *user_id, char *user_name, int len1, char *card_number, int len2, const char *image_path);

int chg_viplist_user_name(const char * user_id, const char *user_name);

int chg_viplist_user_card_number(const char *user_id, const char *card_number);

int chg_viplist_user_image(const char *user_id, const char *image_path, const char *face_image_path);

int get_viplist_status(int &cur_status, int &pre_status);

/*------ normal user list ------------------------------------------------------------------------------*/

int add_userlist_user(const char *user_id, const char *user_name, const char *card_number, const char *image_path, const char *face_image_path);

int del_userlist_user(const char *user_id);

int get_userlist(char ***user_list, int &count);

int get_userlist_user_info(const char *user_id, char *user_name, int len1, char *card_number, int len2, const char *image_path);
	
int chg_userlist_user_name(const char *user_id, const char *user_name);

int chg_userlist_user_card_number(const char *user_id, const char *card_number);

int chg_userlist_user_image(const char *user_id, const char *image_path, const char *face_image_path);

int get_userlist_status(int &cur_status, int &pre_status);

/*------ guest user list ------------------------------------------------------------------------------*/

int add_guestlist_user(const char *user_id, const char *user_name, const char *card_number, const char *image_path, const char *face_image_path);

int del_guestlist_user(const char *user_id);
	
int get_guestlist(char ***user_list, int &count);

int get_guestlist_user_info(const char *user_id, char *user_name, int len1, char *card_number, int len2, const char *image_path);
	
int chg_guestlist_user_name(const char *user_id, const char *user_name);

int chg_guestlist_user_card_number(const char *user_id, const char *card_number);

int chg_guestlist_user_image(const char *user_id, const char *image_path, const char *face_image_path);

int get_guestlist_status(int &cur_status, int &pre_status);

///////////////////////////////////////////////////


#endif