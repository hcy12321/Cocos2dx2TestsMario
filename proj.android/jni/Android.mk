LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
							../../Classes/AppDelegate.cpp \
							../../Classes/Item.cpp \
							../../Classes/ItemAddMushroom.cpp \
							../../Classes/ItemBattery.cpp \
							../../Classes/ItemBoss.cpp \
							../../Classes/ItemBridgeStartPos.cpp \
							../../Classes/ItemBullet.cpp \
							../../Classes/ItemDarkCloud.cpp \
							../../Classes/ItemFinalPoint.cpp \
							../../Classes/ItemFireString.cpp \
							../../Classes/ItemFlagPoint.cpp \
							../../Classes/ItemFlower.cpp \
							../../Classes/ItemFlyFish.cpp \
							../../Classes/ItemLadderLR.cpp \
							../../Classes/ItemLadderUD.cpp \
							../../Classes/ItemMove.cpp \
							../../Classes/ItemMushroom.cpp \
							../../Classes/ItemMushroomAddLife.cpp \
							../../Classes/ItemMushroomReward.cpp \
							../../Classes/ItemTortoise.cpp \
							../../Classes/ItemTortoiseFly.cpp \
							../../Classes/ItemTortoiseRound.cpp \
							../../Classes/LayerGame.cpp \
							../../Classes/LayerMenu.cpp \
							../../Classes/LayerStart.cpp \
							../../Classes/Mario.cpp \
							../../Classes/MenuCtrl.cpp \
							../../Classes/ProgressBar.cpp 

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += box2d_static
LOCAL_WHOLE_STATIC_LIBRARIES += chipmunk_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,cocos2dx)
$(call import-module,cocos2dx/platform/third_party/android/prebuilt/libcurl)
$(call import-module,CocosDenshion/android)
$(call import-module,extensions)
$(call import-module,external/Box2D)
$(call import-module,external/chipmunk)
