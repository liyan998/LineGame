#include "BarButtom.h"
#include "Skill.h"

using namespace ui;


bool CButtomBar::init()
{
    Layer::init();  

    cocos2d::SpriteFrameCache* scache = cocos2d::SpriteFrameCache::getInstance();
    cocos2d::TextureCache* tcache = cocos2d::Director::getInstance()->getTextureCache();

    scache->addSpriteFramesWithFile("UI/YXJM_PNG/YXJM.plist", tcache->getTextureForKey("UI/YXJM_PNG/YXJM.png"));
    scache->addSpriteFramesWithFile("UI/Props_Icon_PNG/Props_Icon.plist", tcache->getTextureForKey("UI/Props_Icon_PNG/Props_Icon.png"));
    //-------------------------------------------------------------------------------

    cocos2d::Size winsize = cocos2d::Director::getInstance()->getVisibleSize();
    Vec2 orgin = Director::getInstance()->getVisibleOrigin();

    ui::Widget* m_BtmMenu = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("UI/YXJM_dibu.json");
    m_BtmMenu->ignoreAnchorPointForPosition(false);
    m_BtmMenu->setAnchorPoint(cocos2d::Vec2(0.5, 0.0));
    m_BtmMenu->setPosition(cocos2d::Vec2(winsize.width / 2 + orgin.x, orgin.y));
    m_BtmMenu->setScale(0.48);
    m_BtmMenu->setTag(1000);
   
    m_pSkillContent = dynamic_cast<ui::ScrollView*>(ui::Helper::seekWidgetByName(m_BtmMenu, "ScrollView_7"));
    addChild(m_BtmMenu);

    //------------------------------------------------------------

    T_ButtonSkill* tpFreezeSkill    = new T_ButtonSkill();
    tpFreezeSkill->m_iId            = PlayerSkillID::ID_FREEZE;
    tpFreezeSkill->m_oResPath       = "UI/YXJM_daoju_Freezing.json";

    T_ButtonSkill* tpConfuseSkill   = new T_ButtonSkill();
    tpConfuseSkill->m_iId           = PlayerSkillID::ID_CONFUSE;
    tpConfuseSkill->m_oResPath      = "UI/YXJM_daoju_Taunt.json";

    //-----------------------------------------------------------------------------

    m_oAllSkillRes.insert(std::pair<int, T_ButtonSkill*>(PlayerSkillID::ID_FREEZE,  tpFreezeSkill));
    m_oAllSkillRes.insert(std::pair<int, T_ButtonSkill*>(PlayerSkillID::ID_CONFUSE, tpConfuseSkill));

    //---------------------------------------------

    addProerty(PlayerSkillID::ID_FREEZE);

   
    //setAllSkillButtonState(SkillButtonState::STATE_DISABLE);

    return true;
}


void CButtomBar::onExit()
{
    Layer::onExit();

    std::map<int, T_ButtonSkill*>::iterator iter;

    for (iter = m_oAllSkillRes.begin();iter != m_oAllSkillRes.end(); iter++)
    {
        delete iter->second;          
    }
    m_oAllSkillRes.clear();    
}

void CButtomBar::setProertyCallBack(ClickProerty callback)
{
    this->m_pfProertycb = callback;
}

void CButtomBar::setSkillCallBack(ui::Widget::ccWidgetTouchCallback callback)
{
    ui::Widget* m_BtmMenu = (ui::Widget*)getChildByTag(1000);
    ui::Button* button = dynamic_cast<ui::Button*>(ui::Helper::seekWidgetByName(m_BtmMenu, "Button_jineng"));
    button->addTouchEventListener(callback);
}

void CButtomBar::clickProerty(cocos2d::Ref* sender, ui::Widget::TouchEventType type, int id)
{
    if (type == Widget::TouchEventType::ENDED)
    {
//         Button* button = static_cast<Button*>(sender);
//         button->setBright(!button->isBright());
        m_pfProertycb(id);
    }
}

//添加技能栏技能
void CButtomBar::addProerty(int id)
{
    std::map<int, T_ButtonSkill*>::iterator iter = m_oAllSkillRes.find(id);

    if (iter != m_oAllSkillRes.end())
    {
        T_ButtonSkill* tpSkill  = iter->second;

        Widget* layer           = cocostudio::GUIReader::getInstance()->widgetFromJsonFile(tpSkill->m_oResPath.c_str());
        tpSkill->m_pRootPanel   = layer;
        Button* button          = dynamic_cast<ui::Button*>(ui::Helper::seekWidgetByName(layer,"Button_daoju"));
                
        button->setTouchEnabled(true);
        button->addTouchEventListener(CC_CALLBACK_2(CButtomBar::clickProerty, this, tpSkill->m_iId));

        m_pSkillContent->addChild( layer );

        m_oAllButton.push_back( tpSkill );
    }
}

T_ButtonSkill* CButtomBar::getButtionSkillById(int id)
{
   
    for (int i = 0; i < m_oAllButton.size(); i++)
    {
        if (m_oAllButton[i]->m_iId == id)
        {
            return m_oAllButton[i];           
        }
    }

    return nullptr;
}

void CButtomBar::setSkillButtonState(T_ButtonSkill* pBS, int state)
{
    Button* button = dynamic_cast<ui::Button*>(ui::Helper::seekWidgetByName(pBS->m_pRootPanel, "Button_daoju"));

    switch (state)
    {
    case SkillButtonState::STATE_DISABLE:
        button->setBright(false);      
        button->setEnabled(false);
        break;
    case SkillButtonState::STATE_AVLABLE:  
        button->setEnabled(true);
        button->setBright(true);
        break;
    default:
        break;
    }
}


void CButtomBar::setSkillButtonState(int skillid, int state)
{
    T_ButtonSkill* pBs = getButtionSkillById(skillid);
 
    //----------------------------------
    if (pBs == nullptr)
    {
        return;
    }

    setSkillButtonState(pBs, state);
}


void CButtomBar::setAllSkillButtonState(int state)
{
    for (int i = 0; i < m_oAllButton.size();i++)
    {
        setSkillButtonState(m_oAllButton[i], state);
    }
}