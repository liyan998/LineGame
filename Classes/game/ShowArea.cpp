#include "ShowArea.h"
#include "framework/util/Math.h"

using namespace liyan998;

bool CShowArea::init()
{
    Sprite::init();   

    m_pPlayer = NULL;

    log("CShowArea::init...");

    Size visibleSize = Director::getInstance()->getVisibleSize();
    auto pSprite = Sprite::create("HelloWorld.png");
    pSprite->setPosition(visibleSize.width / 2, visibleSize.height / 2);
    addChild(pSprite);

    //--------------------------------------------------------------

    m_pClip = ClippingNode::create();
    m_pClip->setInverted(true);
    m_pClip->setAlphaThreshold(0.f);
   // addChild(m_pClip);


    LayerColor* pLc = LayerColor::create(Color4B(0,0,0,200));
    m_pClip->addChild(pLc);
    //----------------------------------------------

    m_pDrawNode = DrawNode::create();  
   // m_pClip->setStencil(m_pDrawNode);
    addChild(m_pDrawNode);

    //----------------------------------------

    

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
    m_pDrawNode->drawPolygon(&m_oAllPoint[0], m_oAllPoint.size(), Color4F(1, 0, 1, .5f), 5, Color4F(0, 0, 1, 1));

   
    for (int i = 0; i < m_oTempPoint.size(); i++)
    {
        if (i + 1 < m_oTempPoint.size())
        {
            m_pDrawNode->drawSegment(m_oTempPoint[i], m_oTempPoint[i + 1], 2, Color4F(1, .5F, .5F, .5F));
        }       
    }
    switch (m_State)
    {
    case STATE_DRAWLINE:        
        
        
        m_pDrawNode->drawSegment(m_oStartPointer, m_oMovePointer, 3, Color4F(1, 1, 1, 1));
        break;
    }
    //m_pClip->setStencil(m_pDrawNode);
}


void CShowArea::setPointer(const Vec2& pos)
{
    log("Pointer: x:%f, y:%f", pos.x, pos.y);

    if (getState() != STATE_DRAWLINE)
    {
        m_oTempPoint.push_back(m_pPlayer->getPosition());
        m_oStartPointer = pos;
        setState(STATE_DRAWLINE);
    }

    //----------------------------------------------
    //取法向量

    log("normal vector = index %d", m_CurrentIndex);  
    m_oMovePointer = pos;

    //---------------------------------------------
    float radina = CMath::getRadian(m_oStartPointer, m_oMovePointer);

    log("Angle:%f", CMath::radianToAngle(radina));
    m_pPlayer->move(radina);


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

//
void CShowArea::setPlayerPosiztion(Sprite* pSp)
{
    int setLine = CMath::getRandom(0, m_oAllMargin.size() - 1);

    CMargin* margin     = m_oAllMargin[setLine];

    float rad           = CMath::getRadian(margin->m_oStart, margin->m_oTaget);
    float dis           = ccpDistance(margin->m_oStart, margin->m_oTaget);
    int ranint          = CMath::getRandom(0, dis);

    Vec2& ps            = CMath::getVec2(margin->m_oStart, ranint, rad);

    pSp->setPosition(ps);

    log("sprite setPostion:%f, %f, %d", pSp->getPosition().x  , pSp->getPosition().y, ranint);
}

void CShowArea::setPlayer(CMySprite* sp)
{
    this->m_pPlayer = sp;
}


void CShowArea::runMove(float inv)
{
    
}

void CShowArea::addTempPoint(const Vec2& vec)
{
    m_oTempPoint.push_back(vec);

    log("Add Point Size:%d",m_oTempPoint.size());
    flush();
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