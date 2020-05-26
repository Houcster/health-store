LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := MyGame_shared

LOCAL_MODULE_FILENAME := libMyGame

LOCAL_SRC_FILES := $(LOCAL_PATH)/hellocpp/main.cpp \
$(LOCAL_PATH)/../../../Classes/AppDelegate.cpp \
$(LOCAL_PATH)/../../../Classes/MainMenuScene.cpp \
$(LOCAL_PATH)/../../../Classes/GamingScene.cpp \
$(LOCAL_PATH)/../../../Classes/MyBodyParser.cpp \
$(LOCAL_PATH)/../../../Classes/Items.cpp \
$(LOCAL_PATH)/../../../Classes/Baskets.cpp \
$(LOCAL_PATH)/../../../Classes/GameOverScene.cpp \
$(LOCAL_PATH)/../../../Classes/LevelCompleteScene.cpp \
$(LOCAL_PATH)/../../../Classes/LogoSplashScene.cpp \
$(LOCAL_PATH)/../../../Classes/SettingsScene.cpp \
$(LOCAL_PATH)/../../../Classes/RulesScene.cpp \
$(LOCAL_PATH)/../../../Classes/InfoScene.cpp

LOCAL_CPPFLAGS := -DSDKBOX_ENABLED
LOCAL_LDLIBS := -landroid \
-llog
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../Classes
LOCAL_WHOLE_STATIC_LIBRARIES := PluginChartboost \
sdkbox \
PluginAdMob \
PluginSdkboxAds \
PluginUnityAds \
PluginIAP

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cc_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)
$(call import-add-path, $(LOCAL_PATH))

$(call import-module, cocos)
$(call import-module, ./sdkbox)
$(call import-module, ./PluginChartboost)
$(call import-module, ./PluginAdMob)
$(call import-module, ./PluginSdkboxAds)
$(call import-module, ./PluginUnityAds)
$(call import-module, ./PluginIAP)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
