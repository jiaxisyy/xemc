#ifndef __MDBUS_H__
#define __MDBUS_H__

#include <android/log.h>
#define TAG "serial-jni"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,TAG ,__VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,TAG ,__VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN,TAG ,__VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG ,__VA_ARGS__)
#define LOGF(...) __android_log_print(ANDROID_LOG_FATAL,TAG ,__VA_ARGS__)


class CMdBus{
public:
	CMdBus();
	~CMdBus();
	
	int init_port();
	int mdbus_read_bit(int type, unsigned char *buf, unsigned int stadr, unsigned int len);
	int mdbus_write_bit(int type, unsigned char *buf, unsigned int stadr, unsigned int len);
	int mdbus_read_word(int type, unsigned short *buf, unsigned int stadr, unsigned int len);
	int mdbus_write_word(int type, unsigned short *buf, unsigned int stadr, unsigned int len);

	int mdbus_read_dword(int type, unsigned int *buf, unsigned int stadr, unsigned int len);
	int mdbus_write_dword(int type, unsigned int *buf, unsigned int stadr, unsigned int len);
	int mdbus_read_real(int type, float *buf, unsigned int stadr, unsigned int len);
	int mdbus_write_real(int type, float *buf, unsigned int stadr, unsigned int len);
	
	int mdus_mainloop(void);
private:
	int port_fd;
};

#define DEV_PATH "/dev/ttyO1"
#endif


