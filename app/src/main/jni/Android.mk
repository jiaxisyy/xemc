LOCAL_PATH := $(call my-dir)
 
include $(CLEAR_VARS) 
LOCAL_LDLIBS :=-llog
 
LOCAL_MODULE    := serialJNI
LOCAL_SRC_FILES := com_hitek_serialJNI_serialJNI.cpp \
					mdbus.cpp \
					MdsModlink.cpp \
					MdsParaCheck.cpp \
					RobotVar.cpp \
					UartHw.cpp
 
include $(BUILD_SHARED_LIBRARY)
