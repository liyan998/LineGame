#include "ShowArea.h"
#include "framework/util/Math.h"

using namespace liyan998;

//#define DEBUG_LINE

bool CShowArea::init()
{
    Sprite::init();   

    m_pPlayer = NULL;

    //--------------------------------------

    for (int i = 0; i < MAX_INDEX; i++)
    {
        m_Area[i] = SELECTID_NULL;
    }


	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!???????????????????????????????????????


    //------------------------------------

    log("CShowArea::init...");

    Size visibleSize = Director::getInstance()->getVisibleSize();
    auto pSprite = Sprite::create("HelloWorld.png");
    pSprite->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	pSprite->setScale(2.0f);
#ifdef DEBUG_LINE
    addChild(pSprite);
#endif
    //--------------------------------------------------------------

    m_pClip = ClippingNode::create();
    m_pClip->setInverted(true);
    m_pClip->setAlphaThreshold(0.f);
#ifdef DEBUG_LINE
   addChild(m_pClip);
#endif


    LayerColor* pLc = LayerColor::create(Color4B(0,0,0,200));
    m_pClip->addChild(pLc);
    //----------------------------------------------

    m_pDrawNode = DrawNode::create(); 
#ifdef DEBUG_LINE
   m_pClip->setStencil(m_pDrawNode);
#else
   addChild(m_pDrawNode);
#endif
   
    //----------------------------------------    

	Rect rec(300,592, 200 , 200);

    m_oAllPoint.push_back(rec.origin);
    m_oAllPoint.push_back(Vec2(rec.origin.x + rec.size.width , rec.origin.y ));
	m_oAllPoint.push_back(Vec2(rec.origin.x + rec.size.width , rec.origin.y - rec.size.height));
	m_oAllPoint.push_back(Vec2(rec.origin.x , rec.origin.y - rec.size.height ));
	

    flush();

    setState(STATE_CLOSE);

    return true;
}



void CShowArea::flushMargin()
{

    for (int i = 0; i < m_oAllMargin.size(); i++)
    {
        this->removeChildByTag(m_oAllMargin[i]);
    }

    m_oAllMargin.clear();
  
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
        m_oAllMargin.push_back(pMarg->getTag());
    }

}


void printVector(std::vector<Vec2> &v)
{
    for (int i = 0; i < v.size();i++)
    {
        log("Vec2(%f, %f),", v[i].x , v[i].y);
    }
}

void CShowArea::flush()
{  
    flushMargin();

    //---------------------------------------------------
	
    m_pDrawNode->clear();   
	//m_pDrawNode->drawPolygon(&m_oAllPoint[0], m_oAllPoint.size(), Color4F(1, 0, 1, .5f), 1, Color4F(0, 0, 1, 1));

	Vector2dVector res;
	Vector2dVector vv;
	for (int i = 0;i < m_oAllPoint.size();i++)
	{
		res.push_back(Vector2d(m_oAllPoint[i].x, m_oAllPoint[i].y));
	}
	Triangulate::Process(res, vv);

	int tcount = vv.size()/3;
	for (int i=0; i<tcount; i++)
	{
		const Vector2d &p1 = vv[i * 3 + 0];
		const Vector2d &p2 = vv[i * 3 + 1];
		const Vector2d &p3 = vv[i * 3 + 2];	
		Vec2 tvec1[] = {
			Vec2(p1.GetX(), p1.GetY()),
			Vec2(p2.GetX(), p2.GetY()),
			Vec2(p3.GetX(), p3.GetY())
		};
		m_pDrawNode->drawPolygon(tvec1, 3,Color4F(1, 0, 1, .5f), 0, Color4F(0, 0, 0, 0));
	}

	for (int i = 0 ;i < m_oAllPoint.size();i++)
	{		
		m_pDrawNode->drawDot(m_oAllPoint[i],2,Color4F(1,1,1,1));
	}

    for (int i = 0; i < m_oTempPoint.size(); i++)
    {
        if (i + 1 < m_oTempPoint.size())
        {
            m_pDrawNode->drawSegment(m_oTempPoint[i], m_oTempPoint[i + 1], 2, Color4F(1, .5F, .5F, .5F));
        }       
    }
	for (int i = 0 ;i < m_oTempPoint.size();i++)
	{
		m_pDrawNode->drawDot(m_oTempPoint[i],2,Color4F(1,1,1,1));
	}
	
    switch (m_State)
    {
    case STATE_DRAWLINE:		
        m_pDrawNode->drawSegment(m_oStartPointer, m_oMovePointer, 3, Color4F(1, 1, 1, 1));
        break;
    }
   
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

    //log("normal vector = index %d", m_CurrentIndex);  
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
        CMargin* tpMagin = static_cast<CMargin*>(this->getChildByTag(m_oAllMargin[i]));//
        Rect& trec = tpMagin->getBoundingBox();

        if (trec.containsPoint(rec))
        {
            log("CMargin Point:%f,%f", trec.origin.x, trec.origin.y);          
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

        clearAreaIndex();

        m_oTempPoint.clear();
        flush();
        break;
    }
    
}

// 
void CShowArea::setPlayerPosiztion(Sprite* pSp)
{
    int setLine = CMath::getRandom(0, m_oAllMargin.size() - 1);
	
	log("setLine random:%d ", setLine);

    CMargin* margin     = static_cast<CMargin*>(this->getChildByTag(m_oAllMargin[setLine]));

    float rad           = CMath::getRadian(margin->m_oStart, margin->m_oTaget);
    float dis           = ccpDistance(margin->m_oStart, margin->m_oTaget);
    int ranint          = CMath::getRandom(0, dis);
	log(" ranint random:%d ", setLine);
    Vec2& ps            = CMath::getVec2(margin->m_oStart, ranint, rad);

    pSp->setPosition(ps);

    setAreaIndex(0, setLine);

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

void CShowArea::clearAreaIndex()
{
    log("-----------------------------------------------------");
    
    int direct = m_Area[0] - m_Area[1];
    int delNum = static_cast<int>(abs(direct));

    log("close Area Clear Point");
    log("close solution :%d, %d", m_Area[0], m_Area[1]);
    log("remove point num:%d", delNum);
    log("direct:%d", direct);    
	//printVector(m_oTempPoint);

	if (direct > 0)
	{
		std::reverse(m_oTempPoint.begin(), m_oTempPoint.end());
	}

	if (m_Area[1] ==0)
	{
		log("outer error");
		//删除头部分
		Vec2Iter it = m_oAllPoint.begin();
		//TODO删除个数
		m_oAllPoint.erase(it);
		it = m_oAllPoint.begin();
		m_oAllPoint.insert(it, m_oTempPoint.begin(), m_oTempPoint.end());

	}else{
		

		int startMargin = m_Area[0] + 1;
		Vec2Iter it = m_oAllPoint.begin() + startMargin;
		log("res Size:%d", m_oAllPoint.size());
		m_oAllPoint.erase(it, it + delNum);
		log("del Size:%d", m_oAllPoint.size());
		it = m_oAllPoint.begin() + startMargin;
		m_oAllPoint.insert(it, m_oTempPoint.begin(), m_oTempPoint.end());
		log("ins Size:%d", m_oAllPoint.size());
	}

	

}

void CShowArea::setAreaIndex(int index, int areaIndex)
{
    m_Area[index] = areaIndex;
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