#include <string.h>
#include <android/log.h>
#include "com_hitek_serialJNI_serialJNI.h"
#include <stdlib.h>
#include <stdio.h>
#include "mdbus.h"

#define TAG "serial-jni"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,TAG ,__VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,TAG ,__VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN,TAG ,__VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG ,__VA_ARGS__)
#define LOGF(...) __android_log_print(ANDROID_LOG_FATAL,TAG ,__VA_ARGS__)

#define BUF_SIZE 1024
class CMdBus* pCMdBus = NULL;

JNIEXPORT jboolean JNICALL Java_com_hitek_serialJNI_serialJNI_init
  (JNIEnv *env, jobject obj){
	int ret;
	LOGE("2222222\n");
	if(pCMdBus == NULL){
		pCMdBus = new CMdBus();
	}else{
		return true;
	}
	if(pCMdBus == NULL)
	{
		LOGE("Java_com_hitek_serialJNI_serialJNI_init pCMdBus is null\n");
		return false;
	}
	ret =pCMdBus->init_port();
	LOGE("Java_com_hitek_serialJNI_serialJNI_init ret = %d\n",ret);
	if(ret < 0)
		return false;
	return true;
}

JNIEXPORT jint JNICALL Java_com_hitek_serialJNI_serialJNI_mainloop
  (JNIEnv *env, jobject obj){
	LOGE("Java_com_hitek_serialJNI_serialJNI_mainloop here\n");
	
	if(pCMdBus == NULL)
	{
		LOGE("please init before read and wirte\n");
		return -1;
	}
	LOGE("111111111\n");
	pCMdBus->mdus_mainloop();
	
	return 0;
}

JNIEXPORT jbyteArray JNICALL Java_com_hitek_serialJNI_serialJNI_mdbusreadbyte
  (JNIEnv *env, jobject obj, jint type, jint stadr, jint len){
	unsigned char buf[BUF_SIZE] = {0};
  	jint res = -1;
	if(pCMdBus == NULL)
	{
		LOGE("please init before read and wirte\n");
		return NULL;
	}




	if(len >= 1024){
		len = 1024;
	}
	res = pCMdBus->mdbus_read_bit(type,buf,stadr,len);
	if(res < 0){
		return NULL;
	}
	jbyteArray result = env->NewByteArray(len);
	if(result != NULL){
		env->SetByteArrayRegion(result, 0, len,(jbyte *)buf);
	}
	return result;


}

JNIEXPORT jshortArray JNICALL Java_com_hitek_serialJNI_serialJNI_mdbusreadword
  (JNIEnv *env, jobject obj, jint type, jint stadr, jint len){
  
  	unsigned short buf[BUF_SIZE] = {0};
  	jint res = -1;
	if(pCMdBus == NULL)
	{
		LOGE("please init before read and wirte\n");
		return NULL;
	}

	if(len >= 1024){
		len = 1024;
	}
	res = pCMdBus->mdbus_read_word(type,buf,stadr,len);
	if(res < 0){
		return NULL;
	}
	jshortArray result = env->NewShortArray(len);
	if(result != NULL){
		env->SetShortArrayRegion(result, 0, len,(jshort *)buf);
	}
	return result;


}

JNIEXPORT jint JNICALL Java_com_hitek_serialJNI_serialJNI_mdbuswritebyte
  (JNIEnv *env, jobject obj, jint type, jbyteArray data, jint stadr, jint len){
  
	jint res = -1;
	unsigned char buf[BUF_SIZE] = {0};
	if(pCMdBus == NULL)
	{
		LOGE("please init before read and wirte");
		return -1;
	}
	if(len >= 1024){
		len = 1024;
	}

	if(data == NULL){
		return -1;
	}
	env->GetByteArrayRegion(data, 0, len,(jbyte *)buf);

	res = pCMdBus->mdbus_write_bit(type,buf,stadr,len);
	return res;
}

JNIEXPORT jint JNICALL Java_com_hitek_serialJNI_serialJNI_mdbuswriteword
  (JNIEnv *env, jobject obj, jint type, jshortArray data, jint stadr, jint len){
	LOGE("Java_com_hitek_serialJNI_serialJNI_mdbuswriteword is called");
	jint res = -1;
	unsigned short buf[BUF_SIZE] = {0};
	if(pCMdBus == NULL)
	{
		LOGE("please init before read and wirte");
		return -1;
	}
	if(len >= 1024){
		len = 1024;
	}

	if(data == NULL){
		return -1;
	}
	env->GetShortArrayRegion(data, 0, len,(jshort *)buf);

	res = pCMdBus->mdbus_write_word(type,buf,stadr,len);
	return res;
}

JNIEXPORT jintArray JNICALL Java_com_hitek_serialJNI_serialJNI_mdbusreaddword
  (JNIEnv *env, jobject obj, jint type, jint stadr, jint len){

	unsigned int buf[BUF_SIZE] = {0};
	jint res = -1;
	if(pCMdBus == NULL)
	{
		LOGE("please init before read and wirte\n");
		return NULL;
	}

	if(len >= 1024){
		len = 1024;
	}
	res = pCMdBus->mdbus_read_dword(type,buf,stadr,len);
	if(res < 0){
		return NULL;
	}
	jintArray result = env->NewIntArray(len);
	if(result != NULL){
		env->SetIntArrayRegion(result, 0, len,(jint *)buf);
	}
	return result;

}

JNIEXPORT jint JNICALL Java_com_hitek_serialJNI_serialJNI_mdbuswritedword
  (JNIEnv *env, jobject obj, jint type, jintArray data, jint stadr, jint len){

  	LOGE("Java_com_hitek_serialJNI_serialJNI_mdbuswritedword is called");
	jint res = -1;
	unsigned int buf[BUF_SIZE] = {0};
	if(pCMdBus == NULL)
	{
		LOGE("please init before read and wirte");
		return -1;
	}
	if(len >= 1024){
		len = 1024;
	}

	if(data == NULL){
		return -1;
	}
	env->GetIntArrayRegion(data, 0, len,(jint *)buf);

	res = pCMdBus->mdbus_write_dword(type,buf,stadr,len);
	return res;

}

JNIEXPORT jfloatArray JNICALL Java_com_hitek_serialJNI_serialJNI_mdbusreadreal
  (JNIEnv *env, jobject obj, jint type, jint stadr, jint len){

	float buf[BUF_SIZE] = {0};
	jint res = -1;
	if(pCMdBus == NULL)
	{
		LOGE("please init before read and wirte\n");
		return NULL;
	}

	if(len >= 1024){
		len = 1024;
	}
	res = pCMdBus->mdbus_read_real(type,buf,stadr,len);
	if(res < 0){
		return NULL;
	}
	jfloatArray result = env->NewFloatArray(len);
	if(result != NULL){
		env->SetFloatArrayRegion(result, 0, len,(jfloat *)buf);
	}
	return result;

}

JNIEXPORT jint JNICALL Java_com_hitek_serialJNI_serialJNI_mdbuswritereal
  (JNIEnv *env, jobject obj, jint type, jfloatArray data, jint stadr, jint len){

  	LOGE("Java_com_hitek_serialJNI_serialJNI_mdbuswritereal is called");
	jint res = -1;
	float buf[BUF_SIZE] = {0};
	
	if(pCMdBus == NULL)
	{
		LOGE("please init before read and wirte");
		return -1;
	}
	if(len >= 1024){
		len = 1024;
	}

	if(data == NULL){
		return -1;
	}
	env->GetFloatArrayRegion(data, 0, len,(jfloat *)buf);

	res = pCMdBus->mdbus_write_real(type,buf,stadr,len);
	return res;

}

JNIEXPORT void JNICALL Java_com_hitek_serialJNI_serialJNI_destory
  (JNIEnv * env, jobject obj){
	//LOGD("Java_com_hitek_serialJNI_serialJNI_destory is called\n");
	if(pCMdBus!=NULL){
		delete pCMdBus;
		pCMdBus=NULL;
	}
}


