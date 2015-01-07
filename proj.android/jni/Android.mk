LOCAL_PATH := $(call my-dir)

#---------------------------------------------------------------------------

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/extensions)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/extensions/GUI/CCControlExtension)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/HelloWorldScene.cpp \
                   ../../Classes/MyGame.cpp \
                   ../../Classes/framework/ui/AAlert.cpp \
                   ../../Classes/framework/ui/AGameScreen.cpp \
                   ../../Classes/game/EventDispatcher.cpp \
                   ../../Classes/game/GameView.cpp \
                   ../../Classes/game/Margin.cpp \
                   ../../Classes/game/MySprite.cpp \
                   ../../Classes/game/Path.cpp \
                   ../../Classes/game/GameArticle.cpp \
                   ../../Classes/game/AnimaAxis.cpp \
                   ../../Classes/game/GameElement.cpp \
				   ../../Classes/game/ButterFly.cpp \
				   ../../Classes/game/Boss.cpp\
                   ../../Classes/game/Npc.cpp \
                   ../../Classes/game/Enemy.cpp \
                   ../../Classes/game/Game1Player.cpp \
				   ../../Classes/game/GameLogic.cpp \
                   ../../Classes/game/Shape.cpp \
                   ../../Classes/game/ShowArea.cpp \
                   ../../Classes/game/Test.cpp \
                   ../../Classes/game/util/DateTime.cpp \
                   ../../Classes/game/util/Math.cpp \
                   ../../Classes/game/util/triangulate.cpp \
                   ../../Classes/game/util/Util.cpp \
                   ../../Classes/ui/GameScreen.cpp \
                   ../../Classes/ui/Panel.cpp \
                   ../../Classes/ui/UIElement.cpp \
                   ../../Classes/ui/UiFrom.cpp 

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocostudio_static

# LOCAL_WHOLE_STATIC_LIBRARIES += box2d_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosbuilder_static
LOCAL_WHOLE_STATIC_LIBRARIES += spine_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocostudio_static
# LOCAL_WHOLE_STATIC_LIBRARIES += cocos_network_static

include $(BUILD_SHARED_LIBRARY)

#---------------------------------------------------------------------------

$(call import-module,.)
$(call import-module,audio/android)
$(call import-module,extensions)
$(call import-module,editor-support/cocostudio)

# $(call import-module,Box2D)
$(call import-module,editor-support/cocosbuilder)
$(call import-module,editor-support/spine)
$(call import-module,editor-support/cocostudio)
# $(call import-module,network)

