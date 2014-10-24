#include "UIElement.h"


//
void CUIElement::setIcon(Sprite* ps)
{
    ps->setPosition( Point(0, ps->getContentSize().height  / 2));
    ps->setTag(TAG_ICON);
    addChild(ps);
}


//
void CUIElement::setLab(Sprite* ps)
{    
    ps->setPosition(Point(0, -13));
    ps->setScale(0.7f);
    ps->setTag(TAG_LAB);
    addChild(ps);
}