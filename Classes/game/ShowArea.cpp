#include "ShowArea.h"
#include "util/Util.h"      
#include "util/Math.h"


using namespace liyan998;



#define DEBUG_LINE

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
  
    createShape(SHAPEID_AREA, m_oAllPoint)->setColor(Color4F(1, 1, 0.5, 1), Color4F(1, 1, 0.5, 1));
    createShape(SHAPEID_TEMP, m_oTempPoint)->setColor(Color4F(0, 1, 0.5, 1), Color4F(0, 1, 0.5, 1));;

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

//////////////////////////////////////////////////////////////////////////


void CShowArea::flush()
{  
    flushMargin();

    //---------------------------------------------------
	
    m_pDrawNode->clear();   
    getShape(SHAPEID_AREA)->draw(m_pDrawNode);
    
 

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

//     for (int i = 0; i < m_oTempPoint.size();i++)
//     {
// 
//         if (i + 1 > m_oTempPoint.size() - 1)
//         {
//             dn->drawSegment(m_oTempPoint[i], m_oTempPoint[0], 1, Color4F(1, 1, 0, 0.5));
//         }
//         else{
//             dn->drawSegment(m_oTempPoint[i], m_oTempPoint[i + 1], 1, Color4F(1, 1, 0, 0.5));
//         }
// 
//         dn->drawDot(m_oTempPoint[i], 10, Color4F(1,0,1,0.5));
//     }

    getShape(SHAPEID_TEMP)->draw(dn);
    
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
    if (m_pPath != NULL && m_pPath->m_oAllPoint.size() < 1)
    {
        return false;
    }



    return true;
}

bool CShowArea::hasPointInMargin(const Vec2& point)
{
    for (int i = 0; i < m_oAllMargin.size(); i++)
    {
        CMargin* tpMagin = static_cast<CMargin*>(this->getChildByTag(m_oAllMargin[i]));//

//         const Vec2& p1 ;
//         const Vec2& p2;
        switch (tpMagin->m_Angle)
        {
        case ANGLE_DOWN:
//             if (p1.x == point.x )
//             {
//             }
            break;
        case ANGLE_RIGHT:

            break;
        case ANGLE_UP:

            break;
        case ANGLE_LEFT:

            break;
        default:
            break;
        }
    }

    return false;
}




void CShowArea::setState(int sta)
{
    this->m_State = sta;
    switch (sta)
    {
    case STATE_CLOSE:
        if (isCloseArea())
        {
            clearAreaIndex();
        }     
        
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
    CMargin* tMargin	= static_cast<CMargin*>(this->getChildByTag(m_oAllMargin[index])); 
    Vec2& refp			= CMath::getFootPoint(tMargin->m_oStart, tMargin->m_oTaget, vec2); 

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



void CShowArea::clearAreaIndex()
{
    if (m_Area[0] == -1 || m_Area[1] == -1)
    {
        log("no area %d | %d", m_Area[0], m_Area[1]);
        return;
    }

    log("-----------------------------------------------------");
    int delNum			= 0;
    int nodeCount       = m_Area[0] - m_Area[1];       

    int startMargin;
    Vec2Iter  it;
     
    int pathdirect = m_pPath->getDirect();

    log("Path size:%d", m_pPath->m_oAllPoint.size());

    //包含起始点
    if ((nodeCount < 0 && pathdirect < 0) || (nodeCount > 0 && pathdirect >= 0))
    {
        log("include first!!!!!!!!");
             
        if (pathdirect < 0)
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
            
        }
        else if (pathdirect > 0)
        {
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
            log("left SSSSSS");
            startMargin = m_Area[1] + 1;

            it = m_oAllPoint.begin() + startMargin;
            m_oAllPoint.erase(it, it + delNum);

            it = m_oAllPoint.begin() + startMargin;
            std::reverse(m_pPath->m_oAllPoint.begin(), m_pPath->m_oAllPoint.end()); 
            m_oAllPoint.insert(it, m_pPath->m_oAllPoint.begin(), m_pPath->m_oAllPoint.end());

        }else if (nodeCount == 0)                       //在同一区域
        {
            log("same Line!");
            startMargin = m_Area[0] + 1;
            it = m_oAllPoint.begin() + startMargin;

            if (pathdirect < 0)                         //逆时针
            {
                std::reverse(m_pPath->m_oAllPoint.begin(), m_pPath->m_oAllPoint.end());
            }
            m_oAllPoint.insert(it, m_pPath->m_oAllPoint.begin(), m_pPath->m_oAllPoint.end());

        }else{                                          //顺时针
            log("right SSSSSS");
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

    getShape(SHAPEID_AREA)->setShape(m_oAllPoint);
}

CShape* CShowArea::createShape(int id ,std::vector<Vec2>& refAllPoint)
{
    CShape* tShape = new CShape();
    tShape->setShape(refAllPoint);

    m_oAllShape.insert(ShapePair(id, tShape));

    return tShape;
}


CShape* CShowArea::getShape(const int id)
{
    ShapeIterator iter = m_oAllShape.find(id);
    if (iter != m_oAllShape.end())
    {
        return iter->second;
    }
    return NULL;
}

void CShowArea::setAreaIndex(int index, int areaIndex)
{
    m_Area[index] = areaIndex;
}



bool CShowArea::hasPointInArea(const Vec2& point)
{
    if (CUtil::hasPointInPloyon(m_oAllPoint, point))
    {
        return true;
    }
    return false;
}



