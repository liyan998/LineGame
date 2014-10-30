#include "ShowArea.h"
#include "framework/util/Math.h"
#include "framework/util/Util.h"

using namespace liyan998;

//#define DEBUG_LINE

bool CShowArea::init()
{
    Sprite::init();   

    m_pPlayer   = NULL;
    m_pPath     = NULL;

    //--------------------------------------

    for (int i = 0; i < MAX_INDEX; i++)
    {
        m_Area[i] = SELECTID_NULL;
    }
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
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

    m_pShape = new CShape();
    m_pShape->setShape(m_oAllPoint);
	
    //createShape(m_oAllPoint);

    flush();

    setState(STATE_CLOSE);

    return true;
}





void printVector(std::vector<Vec2> &v)
{
    for (int i = 0; i < v.size();i++)
    {
        log("Vec2(%f, %f),", v[i].x , v[i].y);
    }
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

//////////////////////////////////////////////////////////////////////////


void CShowArea::flush()
{  
    flushMargin();

    //---------------------------------------------------
	
    m_pDrawNode->clear();   
    m_pShape->draw(m_pDrawNode);

	for (int i = 0 ;i < m_oAllPoint.size();i++)
	{		
		m_pDrawNode->drawDot(m_oAllPoint[i],2,Color4F(1,1,1,1));
	}

//     for (int i = 0; i < m_oTempPoint.size(); i++)
//     {
//         if (i + 1 < m_oTempPoint.size())
//         {
//             m_pDrawNode->drawSegment(m_oTempPoint[i], m_oTempPoint[i + 1], 2, Color4F(1, .5F, .5F, .5F));
//         }       
//     }
// 	for (int i = 0 ;i < m_oTempPoint.size();i++)
// 	{
// 		m_pDrawNode->drawDot(m_oTempPoint[i],2,Color4F(1,1,1,1));
// 	}


//     for (int i = 0; i < m_oAllMargin.size(); i++)
//     {
//         CMargin* pMarg = static_cast<CMargin*>(this->getChildByTag(m_oAllMargin[i]));
// 
//         log("pMarg->m_Angle :%d", pMarg->m_Angle);
//         Vec2 endP1 = CMath::getVec2(pMarg->getPosition(), 100, CMath::angleToRadian(90 + pMarg->m_Angle));
//         Vec2 endP2 = CMath::getVec2(pMarg->getPosition(), 100, CMath::angleToRadian(pMarg->m_Angle));
//         Vec2 endP3 = CMath::getVec2(pMarg->getPosition(), 100, CMath::angleToRadian(180 + pMarg->m_Angle));
// 
//         m_pDrawNode->drawSegment(pMarg->getPosition(), endP1, 1, Color4F(1, 1, 0, 1));
//         m_pDrawNode->drawSegment(pMarg->getPosition(), endP2, 1, Color4F(1, 0, 1, 1));
//         m_pDrawNode->drawSegment(pMarg->getPosition(), endP3, 1, Color4F(0, 1, 1, 1));
// 
//         m_pDrawNode->drawDot(pMarg->getPosition(), 4, Color4F(1, 0, 0, 1));
//     }
    	
//     switch (m_State)
//     {
//     case STATE_DRAWLINE:		
//         if (m_oTempPoint.size() > 0)
//         {
//             m_pDrawNode->drawSegment(m_oTempPoint[m_oTempPoint.size() - 1], m_pPlayer->getPosition(), 3, Color4F(1, 1, 1, 1));
//         }        
//         break;
//     }
   
}


void CShowArea::print(DrawNode* dn)
{


    for (int i = 0; i < m_oAllMargin.size();i++)
    {
        CMargin* pMarg = static_cast<CMargin*>(this->getChildByTag(m_oAllMargin[i]));
        dn->drawSegment(pMarg->m_oStart, pMarg->m_oTaget, 1, Color4F(1,1,1,1));

    }
}


void CShowArea::setPointer(const Vec2& pos)
{
    
    if (getState() != STATE_DRAWLINE)
    {
        log("draw tempPoint start");
        m_oTempPoint.push_back(m_pPlayer->getPosition());
        m_oStartPointer = pos;
        setState(STATE_DRAWLINE);
    }
    //----------------------------------------------
    m_oMovePointer        = pos;

    if ( CUtil::hasPointInPloyon( m_oAllPoint, m_pPlayer->getPosition() ) )
    {
        log("colleWidth Ployon");
    }
    float   dis           = ccpDistance(m_oStartPointer, m_oMovePointer);
    float   radina        = CMath::getRadian(m_oStartPointer, m_oMovePointer);
    int     angle         = CMath::radianToAngle(radina);
 
    if (angle == 0 || angle == 180 || angle == 90 || angle == -90) // up
    {            
        m_pPlayer->pointerMove(Vec2(dis, RADINA_TOGAME(radina)));    

    } else{

        log("no direct %d", angle);
        m_pPlayer->setAbsPosition();
        addTempPoint(m_pPlayer->getPosition());
        m_oStartPointer = m_oMovePointer;
    }   

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
            //log("CMargin Point:%f,%f", trec.origin.x, trec.origin.y);          
            return i;
        }
    }

    return SELECTID_NULL;
}

CMargin* CShowArea::getMargin(int index)
{
    if (index < 0 || index > m_oAllMargin.size() - 1)
    {
        return NULL;
    }
    return static_cast<CMargin*>(this->getChildByTag(m_oAllMargin[index]));
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
        if (m_pPath != NULL)
        {
            m_pPath->clearPoint();
        }        
        flush();
        break;
    }    
}


void CShowArea::setPlayerPosiztion(const Vec2& vec2, int index)
{
    CMargin* tMargin = static_cast<CMargin*>(this->getChildByTag(m_oAllMargin[index])); 
    Vec2& refp = CMath::getFootPoint(tMargin->m_oStart, tMargin->m_oTaget, vec2);

    log("refp:%f, %f  , %f , %f,  %f, %f ,  %f, %f", tMargin->m_oStart.x, tMargin->m_oStart.y ,
        tMargin->m_oTaget.x, tMargin->m_oTaget.y
        ,refp.x, refp.y, vec2.x, vec2.y);
    m_pPlayer->setPosition(refp);
}

// 
void CShowArea::setPlayerPosiztion()
{
    int setLine         = CMath::getRandom(0, m_oAllMargin.size() - 1);

    CMargin* margin     = static_cast<CMargin*>(this->getChildByTag(m_oAllMargin[setLine]));

    float rad           = CMath::getRadian(margin->m_oStart, margin->m_oTaget);
    float dis           = ccpDistance(margin->m_oStart, margin->m_oTaget);
    int ranint          = CMath::getRandom(0, dis);

    Vec2& ps            = CMath::getVec2(margin->m_oStart, ranint, RADINA_TOGAME(rad));

    m_pPlayer->setState(CMySprite::STATE_INIT);
    m_pPlayer->setPosition(ps);

    setAreaIndex(0, setLine);

    log("sprite setPostion:%f, %f, %d", m_pPlayer->getPosition().x, m_pPlayer->getPosition().y, ranint);

}

void CShowArea::setPlayer(CMySprite* sp)
{
    this->m_pPlayer = sp;
}

void CShowArea::setPath(CPath* path)
{
    this->m_pPath = path;
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
    if (m_Area[0] == -1 || m_Area[1] == -1)
    {
        log("no area %d - %d", m_Area[0], m_Area[1]);
        return;
    }

    log("-----------------------------------------------------");
    int delNum;
    int nodeCount       = m_Area[0] - m_Area[1];    
    bool isConllFirst   = CUtil::hasPointInPloyon(m_pPath->m_oAllPoint, m_oAllPoint[0]);

    int         startMargin;
    Vec2Iter    it;
    unsigned int direct = getDirect();

    log("direct 0x%x", direct);

    log("Path size:%d", m_pPath->m_oAllPoint.size());

    //包含起始点
    if ((nodeCount < 0 && direct == 0xff0000ff) || (nodeCount > 0 && direct == 0x00ffff00)) 
    {
        log("include first!!!!!!!!");
             
        if (direct == 0xff0000ff)
        {            
            log("Left ro");
            
            //删掉target point;
            delNum  = m_Area[1] + 1;
            it      = m_oAllPoint.begin() + delNum;
            m_oAllPoint.erase(it, m_oAllPoint.end());

            //删掉0 -- point1段
            it      = m_oAllPoint.begin();
            delNum  = m_Area[0] + 1;
            m_oAllPoint.erase(it, it + delNum);

            std::reverse(m_pPath->m_oAllPoint.begin(), m_pPath->m_oAllPoint.end());

            it = m_oAllPoint.end();
            m_oAllPoint.insert(it, m_pPath->m_oAllPoint.begin(), m_pPath->m_oAllPoint.end());
            
        }else if (direct == 0xffff00){
            log("Right ro");
            //del body
            it      = m_oAllPoint.begin() + m_Area[0] + 1;
            delNum  = m_oAllPoint.size() - 1 - m_Area[0];
            m_oAllPoint.erase(it, it + delNum);
            //del head
            delNum  = m_Area[1] + 1;
            it      = m_oAllPoint.begin();
            m_oAllPoint.erase(it, it + delNum);

            it      = m_oAllPoint.end();
            m_oAllPoint.insert(it, m_pPath->m_oAllPoint.begin(), m_pPath->m_oAllPoint.end());
        }     
    }
    else
    {
        delNum = static_cast<int>(abs(nodeCount));
        if (nodeCount > 0)                              //逆时针
        {
            startMargin = m_Area[1] + 1;

            it = m_oAllPoint.begin() + startMargin;
            m_oAllPoint.erase(it, it + delNum);

            it = m_oAllPoint.begin() + startMargin;
            std::reverse(m_pPath->m_oAllPoint.begin(), m_pPath->m_oAllPoint.end()); 
            m_oAllPoint.insert(it, m_pPath->m_oAllPoint.begin(), m_pPath->m_oAllPoint.end());

        }else if (nodeCount == 0)                       //在同一区域
        {
            log("same Line!");
        }else{                                          //顺时针
            startMargin = m_Area[0] + 1;

            it          = m_oAllPoint.begin() + startMargin;
            m_oAllPoint.erase(it, it + delNum);

            it          = m_oAllPoint.begin() + startMargin;           
            m_oAllPoint.insert(it, m_pPath->m_oAllPoint.begin(), m_pPath->m_oAllPoint.end());
        }       
    }

    log("close Area Clear Point");
    log("close solution :%d, %d", m_Area[0], m_Area[1]);
    log("remove point num:%d", delNum);
    log("direct:%d", nodeCount);
    m_pShape->setShape(m_oAllPoint);
}

CShape* CShowArea::createShape(std::vector<Vec2>& refAllPoint)
{
    CShape* tShape = new CShape();
    tShape->setShape(refAllPoint);

    m_oAllShape.push_back(tShape);

    return tShape;
}

void CShowArea::setAreaIndex(int index, int areaIndex)
{
    m_Area[index] = areaIndex;
}

/************************************************************************/
/* 
功能描述:      得到方向
返回值:        方向值
                0xff00 00ff 逆序
                0x00ff ff00 顺序

*/
/************************************************************************/
unsigned int CShowArea::getDirect()
{
    unsigned int result = 0;

    CMargin* startMargin    = static_cast<CMargin*>(this->getChildByTag(m_oAllMargin[m_Area[0]]));
    CMargin* endMargin      = static_cast<CMargin*>(this->getChildByTag(m_oAllMargin[m_Area[1]]));
    
    if (CUtil::hasPointInPloyon(m_pPath->m_oAllPoint, startMargin->m_oStart))
    {
        log("content Start - 1 point!");
        result |= 0xff000000;
    }
    else if (CUtil::hasPointInPloyon(m_pPath->m_oAllPoint, startMargin->m_oTaget)){

        log("content Start - 2 point!");
        result |= 0xff0000;
    }

    if (CUtil::hasPointInPloyon(m_pPath->m_oAllPoint, endMargin->m_oStart))
    {
        log("content End - 1 point!");
        result |= 0xff00;
    }
    else if (CUtil::hasPointInPloyon(m_pPath->m_oAllPoint, endMargin->m_oTaget)){

        log("content End - 2 point!");
        result |= 0xff;
    }

    return result;
}


bool CShowArea::hasPointInArea(const Vec2& point)
{

    if (CUtil::hasPointInPloyon(m_oAllPoint, point))
    {
        return true;
    }

    return false;
}



int* CShowArea::getMoveAble(const Vec2& pos)
{
    
    if (getTargetIndex(pos) == SELECTID_NULL)
    {

    }
    else
    {

    }
    return NULL;
}