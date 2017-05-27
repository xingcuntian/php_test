#ifndef DETECT_FEATURE_H_
#define DETECT_FEATURE_H_
//获取版本号
char* get_version();
/// @brief 加载模型和初始化对象和保存要对比的人脸数据
/// @param[in] detectModelPath M_Detect_Craft_2.0.model文件路径
/// @param[in] verifyModelPath M_DetectionAlignmentTracking_1.0.model文件路径
/// @param[in] minFaceWidth 最小人脸宽度限定
/// @return 成功返回true
bool detect_init_info(char* detectModelPath, char* verifyModelPath, int minFaceWidth);

/// @brief 销毁已加载的模型和释放资源
void detect_destroy_model();

/// @param[in] faceDBJson 库中人脸特征数据 特征库无数据则传入 faceDBJson = ""
/// @return 成功返回true
bool detect_input_feature_db(char* featureDB);

/// @brief 销毁已加载的模型和对象
/// @param[in] imagePath 要检测的图片文件路径
/// @param[in] tagID 值0不进行图片的处理，值为1则进行图片处理
/// @return 返回JSON格式的数据
/* Error code:
 * 400	More than one face.
 * 401	Face pixel width is less than set value.
 * 402	Feature extraction failure.
 * 403	Image path is empty.
 * 404	Image loading failed
 */
char* detect_extract_feature(char* imagePath, int tagID);

#endif /* DETECT_FEATURE_H_ */
