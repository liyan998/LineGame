#include "MySprite.h"

bool CMySprite::init()
{
    Sprite::init();

    DrawNode* pDn = DrawNode::create();
    addChild(pDn);

    pDn->drawDot(Vec2::ZERO, 20, Color4F(1, 0, 0, 0.5));
    
    this->setAnchorPoint(Vec2::ZERO);
    this->setContentSize(Size(40,40));
    Rect& rec = this->getBoundingBox();

    //log("bundBox:%f, %f, %f, %f", rec.origin.x, rec.origin.y, rec.size.width , rec.size.height);

    return true;
}