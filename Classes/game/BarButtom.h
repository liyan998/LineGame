#ifndef __BUTTOMBAR_H__
#define __BUTTOMBAR_H__

#include "cocos2d.h"
#include "cocostudio/CCSGUIReader.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"

using namespace cocos2d;


struct T_ButtonSkill
{
    int             m_iId;              //����ID
    std::string     m_oResPath;         //��Դ·��
    ui::Widget*     m_pRootPanel;       //coniter
};



class CButtomBar : public Layer
{

public:

    typedef std::function<void(int)> ClickProerty;

    CREATE_FUNC( CButtomBar )


    enum SkillButtonState
    {
        STATE_DISABLE,          //������
        STATE_AVLABLE           //����
    };

public:

    virtual bool init();

    virtual void onExit();

public:

    void addProerty(int id);                                                //��ӵ���

    void removeProerty(int id);                                             //�Ƴ�����

    void setProertyCallBack(ClickProerty fun);                              //���õ��߰��»ص�

    void setSkillCallBack(ui::Widget::ccWidgetTouchCallback callback);      //���ü��ܰ�ť�ص� 

    void setAllSkillButtonState(int state);

protected:

    void clickProerty(Ref* sender, ui::Widget::TouchEventType type, int id);

    T_ButtonSkill* getButtionSkillById(int id);

    void setSkillButtonState(int skillid, int state);                       //���ð�ť״̬

    void setSkillButtonState(T_ButtonSkill* pBS, int state);

private:

    ClickProerty                        m_pfProertycb;  //���߻ص�

    ui::Widget::ccWidgetTouchCallback   m_pfSkillcb;    //���ܻص�

    ui::ScrollView*                     m_pSkillContent;//���ܰ�ť�б�


    std::map< int, T_ButtonSkill* >     m_oAllSkillRes; //���ܰ�ť��Դ

    std::vector< T_ButtonSkill* >       m_oAllButton;   //���м���

};

#endif//__BUTTOMBAR_H__