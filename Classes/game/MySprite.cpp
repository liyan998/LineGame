#include "MySprite.h"

#include "framework/util/Math.h"

using namespace liyan998;

bool CMySprite::init()
{
    Sprite::init();

    m_fStep = 2.f;

    DrawNode* pDn = DrawNode::create();
    addChild(pDn);

    pDn->drawDot(Vec2::ZERO, 20, Color4F(1, 0, 0, 0.5));
    
    this->setAnchorPoint(Vec2::ZERO);
    this->setContentSize(Size(40,40));
    Rect& rec = this->getBoundingBox();

    //log("bundBox:%f, %f, %f, %f", rec.origin.x, rec.origin.y, rec.size.width , rec.size.height);

    return true;
}

void CMySprite::move(const Vec2& point)
{
    //Vec2& nextPos = CMath::getVec2(this->getPosition(), m_fStep, radina - PI / 2);
    //setPosition(nextPos);

}

void CMySprite::pointerMove(Vec2& pointerVec)
{
    Vec2 pos = CMath::getVec2(m_AbPosition, pointerVec.x, pointerVec.y);

    setPosition(pos);
}


void CMySprite::setAbsPosition()
{
    log("Ready to Move");
    this->m_AbPosition = this->getPosition();
}



void CMySprite::setState(int state)
{

}


void CMySprite::setPointerStart(const Vec2& point)
{
    this->m_oPointerStart = point;
}