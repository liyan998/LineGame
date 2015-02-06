#ifndef __BUTTOMBAR_H__
#define __BUTTOMBAR_H__

#include "cocos2d.h"
#include "cocostudio/CCSGUIReader.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"

using namespace cocos2d;


struct T_ButtonSkill
{
    int             m_iId;              //技能ID
    std::string     m_oResPath;         //资源路径
    ui::Widget*     m_pRootPanel;       //coniter
};



class CButtomBar : public Layer
{

public:

    typedef std::function<void(int)> ClickProerty;

    CREATE_FUNC( CButtomBar )


    enum SkillButtonState
    {
        STATE_DISABLE,          //不可用
        STATE_AVLABLE           //可用
    };

public:

    virtual bool init();

    virtual void onExit();

public:

    void addProerty(int id);                                                //添加道具

    void removeProerty(int id);                                             //移除道具

    void setProertyCallBack(ClickProerty fun);                              //设置道具按下回调

    void setSkillCallBack(ui::Widget::ccWidgetTouchCallback callback);      //设置技能按钮回调 

    void setAllSkillButtonState(int state);

protected:

    void clickProerty(Ref* sender, ui::Widget::TouchEventType type, int id);

    T_ButtonSkill* getButtionSkillById(int id);

    void setSkillButtonState(int skillid, int state);                       //设置按钮状态

    void setSkillButtonState(T_ButtonSkill* pBS, int state);

private:

    ClickProerty                        m_pfProertycb;  //道具回调

    ui::Widget::ccWidgetTouchCallback   m_pfSkillcb;    //技能回调

    ui::ScrollView*                     m_pSkillContent;//技能按钮列表


    std::map< int, T_ButtonSkill* >     m_oAllSkillRes; //技能按钮资源

    std::vector< T_ButtonSkill* >       m_oAllButton;   //所有技能

};

#endif//__BUTTOMBAR_H__