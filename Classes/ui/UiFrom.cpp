#include "UiFrom.h"




bool CUIFrom::init()
{
    Layer::init();
    return true;
}

void CUIFrom::onEnter()
{
    Layer::onEnter();

    m_pUi = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("NewUi_1/NewUi_1.json");
    m_pButton = static_cast<Button*>(ui::Helper::seekWidgetByName(m_pUi, "Button_1"));   
    m_pButton->addTouchEventListener(this, toucheventselector(CUIFrom::onButtonClose));
   // addChild(m_pButton);
    addChild(m_pUi);
}


void CUIFrom::onButtonClose(Ref *pSender, TouchEventType type)
{
    switch (type)
    {
    case TouchEventType::TOUCH_EVENT_ENDED:
      
        log("exit");
        Director::getInstance()->end();
        break;
    }
}