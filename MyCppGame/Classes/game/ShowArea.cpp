#include "ShowArea.h"
#include "framework/util/Math.h"

using namespace liyan998;

bool CShowArea::init()
{
    Sprite::init();   

    log("CShowArea::init...");

    m_pDrawNode = DrawNode::create();   
    addChild(m_pDrawNode);

    m_oAllPoint.push_back(Vec2(70,      592.));
    m_oAllPoint.push_back(Vec2(261,     592));
    m_oAllPoint.push_back(Vec2(261,     400.));
    m_oAllPoint.push_back(Vec2(70.,     400.));

    int size = m_oAllPoint.size();

    for (int i = 0; i < size; i++)
    {
        CMargin* pMarg = CMargin::create();
        if (i + 1 < size)
        {
            pMarg->setTaget(m_oAllPoint[i], m_oAllPoint[i + 1]);
        }
        else
        {
            pMarg->setTaget(m_oAllPoint[i], m_oAllPoint[0]);
        }

        pMarg->setTag(10 + i);
        addChild(pMarg);
        m_oAllMargin.push_back(pMarg);
    }
    flush();

    setState(STATE_CLOSE);

    return true;
}



void CShowArea::flush()
{  
    m_pDrawNode->clear();   
    m_pDrawNode->drawPolygon(&m_oAllPoint[0], m_oAllPoint.size(), Color4F(1, 0, 0, 0.5), 4, Color4F(0, 0, 1, 1));

    switch (m_State)
    {
    case STATE_DRAWLINE:        
        for (int i = 0; i < m_oTempPoint.size();i++)
        {
            if (i + 1 < m_oTempPoint.size())
            {
                m_pDrawNode->drawSegment(m_oTempPoint[i], m_oTempPoint[i + 1], 2, Color4F(1, .5F, .5F, .5F));
            }else{
                m_pDrawNode->drawSegment(m_oTempPoint[i], m_oMovePointer, 2, Color4F(1, .5F, .5F, .5F));
            }            
        }
        
        break;
    }
   
}


void CShowArea::setPointer(const Vec2& pos)
{
    log("Pointer: x:%f, y:%f", pos.x, pos.y);

    if (getState() != STATE_DRAWLINE)
    {
        m_oTempPoint.push_back( pos );
        setState(STATE_DRAWLINE);
    }
    //取法向量
    log("normal vector = index %d", m_CurrentIndex);
    //log("vector:",m_oAllMargin[i].);
    m_oMovePointer = pos;
    flush();
}

int CShowArea::getTargetIndex(const Vec2& rec)
{
    
    for (int i = 0; i < m_oAllMargin.size(); i++)
    {
        CMargin* tpMagin = m_oAllMargin[i];//
        Rect& trec = tpMagin->getBoundingBox();

        if (trec.containsPoint(rec))
        {
            log("CMargin Point:%f,%f", trec.origin.x, trec.origin.y);
            m_CurrentIndex = i;
            return i;
        }
    }

    return SELECTID_NULL;
}

//TODO检查划线区域是否闭合
bool CShowArea::isCloseArea()
{

    return true;
}


CShowArea::State CShowArea::getState()
{
    return this->m_State;
}


void CShowArea::setState(State sta)
{
    this->m_State = sta;
    switch (sta)
    {
    case STATE_CLOSE:

        m_oTempPoint.clear();
        flush();
        break;
    }
    
}

void CShowArea::setPlayerPosiztion(Sprite* pSp)
{
    int setLine = CMath::getRandom(0, m_oAllMargin.size() - 1);

    CMargin* margin = m_oAllMargin[setLine];

    float rad = CMath::getRadian(margin->m_oStart, margin->m_oTaget);

    float dis = ccpDistance(margin->m_oStart, margin->m_oTaget);

    int ranint = CMath::getRandom(0, dis);
    Vec2& ps = CMath::getVec2(margin->m_oStart, ranint, rad);

    pSp->setPosition(ps);

    log("sprite setPostion:%f, %f", pSp->getPosition().x  , pSp->getPosition().y);


}


// bool CShowArea::onTouchBegan(Touch* touches, Event *event)
// {
//     log("CGameView::onTouchBegan<<<<<<<<<<");
//     auto local = touches->getLocation();
// 
//     log("getTargetIndex %d",getTargetIndex(local.x, local.y));
//     return true;
// }

// void CShowArea::onTouchEnded(Touch* touches, Event *event)
// {
//     auto local = touches->getLocation();
//     log("CGameView::onTouchEnded>>>>>>>>>>>%f, %f", local.x, local.y);
//     Node* node = event->getCurrentTarget();
// 
//     log("node tag %d", node->getTag());
// 
//    
// }

// void CShowArea::onTouchMove(Touch* touches, Event *event)
// {
//     log("CGameView::onTouchMove-------------");
//     Sprite* pMargin = static_cast<Sprite*>(event->getCurrentTarget());
//    
// }