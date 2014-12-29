#include "ShowArea.h"
#include "util/Util.h"      
#include "util/Math.h"
#include "EventSystem.h"



using namespace liyan998;   

//#define DEBUG_LINE

bool CShowArea::init()
{
    Sprite::init();   
    m_Model     = MODEL_OUT; 

    m_RefPath   = nullptr;        
    m_pHandle   = nullptr;

    //Size visibleSize = Director::getInstance()->getVisibleSize();

    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Size screen = Director::getInstance()->getVisibleSize();

    //--------------------------------------

    for (int i = 0; i < MAX_INDEX; i++)
    {
        m_Area[i] = SELECTID_NULL;
    }

    //------------------------------------

    log("CShowArea::init...");   

    auto pSprite = Sprite::create("HelloWorld.png");
    pSprite->setPosition(screen.width / 2 + origin.x, screen.height / 2 + origin.y);
	pSprite->setScale(2.0f); 
    addChild(pSprite);
                                        
    //-------------------------------------------------------------- 

    m_pDrawNode     = DrawNode::create(); 
    //m_pDrawNode->retain(); m_pClip->retain();

    m_pClip         = ClippingNode::create(); 
    ///m_pClip->retain();

    m_pClip->setInverted(true);
    m_pClip->setAlphaThreshold(0.f);   

    LayerColor* pLc = LayerColor::create(Color4B(0,0,0,200));
    m_pClip->addChild(pLc);

    m_pClip->setStencil(m_pDrawNode);

    //---------------------------------------------- 

    setMode(MODEL_OUT);

    //------------------------------------------

   unsigned int PARING = 40;
   Size tBroader;
   tBroader.width       = GRAD_NUMBER(screen.width - PARING * 2);
   tBroader.height     = GRAD_NUMBER(screen.height - PARING * 2);
   m_oAreaSize.size    = tBroader;
   m_oAreaSize.origin  = Vec2(
        GRAD_NUMBER(screen.width / 2 + origin.x - tBroader.width / 2),
        GRAD_NUMBER(screen.height / 2 + origin.y + tBroader.height / 2)
        );   

   m_oBorder.push_back(m_oAreaSize.origin);
   m_oBorder.push_back(Vec2(m_oAreaSize.origin.x + m_oAreaSize.size.width, m_oAreaSize.origin.y));
   m_oBorder.push_back(Vec2(m_oAreaSize.origin.x + m_oAreaSize.size.width, m_oAreaSize.origin.y - m_oAreaSize.size.height));
   m_oBorder.push_back(Vec2(m_oAreaSize.origin.x, m_oAreaSize.origin.y - m_oAreaSize.size.height));

   for (int i = 0; i < m_oBorder.size();i++)
   {
       CMargin* pBorderMargin = new CMargin();

       if (i + 1 >= m_oBorder.size())
       {
           pBorderMargin->setTaget(m_oBorder[i], m_oBorder[0]);
       }
       else
       {
           pBorderMargin->setTaget(m_oBorder[i] , m_oBorder[i + 1]);
       } 
       
       //int bordermarginAvDirect = CUtil::getNextAngle(pBorderMargin->m_Angle,1);
       //pBorderMargin->setAvableDirect(bordermarginAvDirect);
       //pBorderMargin->getAvableDirect(m_oBorder, m_oBorderEndPoint);      

      
       m_oBorderMargin.push_back(pBorderMargin);       
   }    
  
                                  
   //----------------------------------------

   unsigned int twh = 80;

   Rect rec(
       GRAD_NUMBER(screen.width / 2 + origin.x - twh / 2),
       GRAD_NUMBER(screen.height / 2 + origin.y + twh / 2),
       GRAD_NUMBER(twh),
       GRAD_NUMBER(twh)
       );

   addPoint(rec.origin);
   addPoint(Vec2(rec.origin.x + rec.size.width, rec.origin.y));
   addPoint(Vec2(rec.origin.x + rec.size.width, rec.origin.y - rec.size.height));
   addPoint(Vec2(rec.origin.x, rec.origin.y - rec.size.height));

   getAllPoint(m_oAllPoint);

   m_iRorate = CUtil::getRotateDirect(m_oAllPoint);

   createShape(SHAPEID_AREA, m_oAllPoint)->setColor(Color4F(1, 1, 0.5, 1), Color4F(1, 1, 0.5, 1));
   //createShape(SHAPEID_TEMP, m_oTempPoint)->setColor(Color4F(0, 1, 0.5, 1), Color4F(0, 1, 0.5, 1));;

   setState(STATE_CLOSE);          
    return true;
}                                  

void CShowArea::released()
{
    removeAllChildren(); 
}

void CShowArea::onExit()
{   
    Sprite::onExit();
    for (int i = 0; i < m_oBorderMargin.size(); i++)
    {
        delete m_oBorderMargin[i];
    }

    m_oBorderMargin.clear();
}

void CShowArea::flushMargin()
{                  

    log("flush margin");
    for (int i = 0; i < m_oAllMargin.size(); i++)
    {
        this->removeChildByTag(m_oAllMargin[i]);
    }

    m_oAllMargin.clear();
    m_oAreaEndPoint.clear();

    //----------------------------------------------------------
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

        pMarg->setAvableDirect(getMarginDirect(pMarg->m_Angle));
        pMarg->getAvableDirect(m_oAllPoint, m_oAreaEndPoint);

        pMarg->setTag(10 + i);
        addChild(pMarg);

        m_oAllMargin.push_back(pMarg->getTag());
    }
     
    checkMarginAvableDirect();
}



/************************************************************************/
/* 
* @brief       补充检查在边上的可行走方向

* @param[in]
* @param[out]
* @return      void 
*/
/************************************************************************/
void CShowArea::checkMarginAvableDirect()
{
    for (EndPointIterator iter = m_oAreaEndPoint.begin(); iter != m_oAreaEndPoint.end(); ++iter)
    {
        const Vec2& inPoint = iter->first;
        int amargin = iter->second;

        std::vector<int> avables;
        CUtil::getDirectFromFlag(amargin, avables);

        for (int i = 0; i < avables.size(); i++)
        {
            int revdirect = CUtil::getRevceDircet(avables[i]);

            Vec2 tPoint = CMath::getVec2(inPoint, GRAD_CELL, CMath::angleToRadian(revdirect));

            CUtil::formartGrid(tPoint);
         
            int gpt = getPositionType(tPoint);
            if (gpt == POSITION_AREA_LINE)
            {
                amargin |= CUtil::converDirectToFlag(revdirect);
                iter->second = amargin;
            }
        }
    } 
}

//////////////////////////////////////////////////////////////////////////


void CShowArea::flush()
{  
    flushMargin();

    //---------------------------------------------------
	
    m_pDrawNode->clear();   
    getShape(SHAPEID_AREA)->draw(m_pDrawNode);  
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

    for (int i = 0; i < m_oAllPoint.size();i++)
    {
        if (i + 1 < m_oAllPoint.size())
        {
            dn->drawSegment(m_oAllPoint[i], m_oAllPoint[i + 1], 1, Color4F(1, 0, 0, 1));
        }
        else
        {
            dn->drawSegment(m_oAllPoint[i], m_oAllPoint[0], 1, Color4F(1, 0, 0, 1));
        }
    }


    for (int i = 0; i < resultArea.size(); i++)
    {
        dn->drawDot(resultArea[i], 5, Color4F(1, 0, 0, 0.6));
    }
    for (int i = 0; i < addArea.size(); i++)
    {
        dn->drawDot(addArea[i], 10, Color4F(1, 1, 1, 0.2));
    }
//     for (int i = 0; i < m_RefPath->m_oAllPoint.size(); i++)
//     {
//         dn->drawDot(m_RefPath->m_oAllPoint[i], 10, Color4F(1, 1,0.5, 0.3));
//     }



    //log("c1 %d c2 %d", c1, c2);
//     getShape(SHAPEID_TEMP)->setShape(resultArea);
//     getShape(SHAPEID_TEMP)->setColor(Color4F(1, 0, 0.5, 1), Color4F(1, 0, 0.5, 0.3));
//     getShape(SHAPEID_TEMP)->draw(dn);
// 
    getShape(SHAPEID_AREA)->setShape(addArea);
    getShape(SHAPEID_AREA)->setColor(Color4F(0, 1, 0.5, 1), Color4F(1, 1, 0, 0.2));
    getShape(SHAPEID_AREA)->draw(dn);


    
    dn->drawPolygon(&m_oBorder[0], 4, Color4F(1, 1, 1, 0), 1, Color4F(1, 1, 1, 1));
    
}


/************************************************************************/
/* 
* @brief        得到当前sp起点到边界距离
* @param[in]    inSp 精灵起始位置
                angle 精灵运动方向
* @param[out]
* @return       void
*/
/************************************************************************/
int CShowArea::getBorderDis(const Vec2& inSP, int angle)
{      
    return  CUtil::getMinWallDis(m_oBorderMargin, inSP, angle);

//     Size visSize = Director::getInstance()->getVisibleSize();
//     Vec2 visVec = Director::getInstance()->getVisibleOrigin();
//   
//     Vec2 tve(Vec2::ZERO);
//     switch (angle)
//     {
//     case ANGLE_DOWN:
//         tve.x = inSP.x;
//         // tve.y = visVec.y;
//         break;
//     case ANGLE_LEFT:
//         //tve.x = visVec.x;
//         tve.y = inSP.y;
//         break;
//     case ANGLE_RIGHT:
//         tve.x = visSize.width + visVec.x;
//         tve.y = inSP.y;
//         break;
//     case ANGLE_UP:
//         tve.x = inSP.x + visVec.x;
//         tve.y = visSize.height + visVec.y;
//         break;
//     default:
//         break;
//     }
// 
//     int mindis = -1;
// 
//     for (int i = 0; i < m_oBorderMargin.size(); i++)
//     {
//         CMargin* maring = m_oBorderMargin[i];
// 
//         // log("p1: %f,%f \n  p2:%f,%f  \n p3:%f,%f \n p4:%f, %f", maring->m_oStart.x, maring->m_oStart.y, maring->m_oTaget.x, maring->m_oTaget.y, inSP.x, inSP.y, tve.x, tve.y);
//         if (liyan998::CMath::hasLineMutlLine(maring->m_oStart, maring->m_oTaget, inSP, tve))
//         {
//             Vec2 zu = CMath::getFootPoint(maring->m_oStart, maring->m_oTaget, inSP);
// 
//             int dis = static_cast<int>(ccpDistance(inSP, zu));
// 
//             if (mindis == -1 || dis < mindis)
//             {
//                 mindis = dis;
//             }
//         }
//     }
//     return mindis;
}
                                      

int CShowArea::getTargetIndex(const Vec2& rec)
{    
    for (int i = 0; i < m_oAllMargin.size(); i++)
    {
        CMargin* tpMagin = static_cast<CMargin*>(this->getChildByTag(m_oAllMargin[i]));//
        const Rect& trec = tpMagin->getBoundingBox();

        if (trec.containsPoint(rec))
        {
            //log("CMargin Point:%f,%f", trec.origin.x, trec.origin.y);          
            return i;
        }
    }

    return SELECTID_NULL;
}

CMargin* CShowArea::getAreaMargin(int index)
{
    if (index < 0 || index > m_oAllMargin.size() - 1)
    {
        return NULL;
    }
    return static_cast<CMargin*>(this->getChildByTag(m_oAllMargin[index]));
}

CMargin* CShowArea::getBorderMargin(const Vec2& inPoint)
{     
    if (getPositionType(inPoint) == POSITION_BORDER_LINE)
    {     
        for (int i = 0; i < m_oBorderMargin.size();i++)
        {      
            CMargin* margin = m_oBorderMargin[i];

            if (CUtil::hasPointInLine(margin->m_oStart, margin->m_oTaget, inPoint))
            {
                return margin;
            }
        }
    }   
    return nullptr;
}



bool CShowArea::isCloseArea()
{ 
    if (m_RefPath == nullptr || m_RefPath->m_oAllPoint.size() < 2)
    {
        return false;
    }
    return true;
}



int CShowArea::hasPointInMargin(const Vec2& point)
{
    for (int i = 0; i < m_oAllMargin.size(); i++)
    {
        CMargin* tpMagin = static_cast<CMargin*>(this->getChildByTag(m_oAllMargin[i]));//

        if (CUtil::hasPointInLine(tpMagin->m_oStart, tpMagin->m_oTaget, point))
        {
            return i;
        }   
    }

    return SELECTID_NULL;
}


/************************************************************************/
/*
@brief          得到当前坐标在游戏区域内的类型 
@param[in]		inPos   输入坐标
@return			int 位置类型      
                POSITION_AREA_ENDPOINT      在解锁安全区端点上
                POSITION_AREA_LINE          在解锁安全区线上
                POSITION_BORDER_ENDPOINT    在边界端点上
                POSITION_BORDER_LINE        在边界线上
                POSITION_LOCK               在锁定区域内
                POSITION_UNLOCK             在已解锁区域内 
*/
/************************************************************************/
int CShowArea::getPositionType(const Vec2& inPos)
{
    //area
    for (int i = 0; i < m_oAllMargin.size(); i++)
    {
        CMargin* tpMagin = static_cast<CMargin*>(this->getChildByTag(m_oAllMargin[i]));//

        if (inPos == tpMagin->m_oStart || inPos == tpMagin->m_oTaget)
        {
            return POSITION_AREA_ENDPOINT;
        }    
        else if (CUtil::hasPointInLine(tpMagin->m_oStart, tpMagin->m_oTaget, inPos))
        {
            return POSITION_AREA_LINE;
        }
    } 
    //border
    for (int i = 0; i < m_oBorderMargin.size(); i++)
    {
        CMargin* tpMagin = m_oBorderMargin[i];
        
        if (inPos == tpMagin->m_oStart ||  inPos == tpMagin->m_oTaget)
        {
            return POSITION_BORDER_ENDPOINT;
        }
        else if (CUtil::hasPointInLine(tpMagin->m_oStart, tpMagin->m_oTaget, inPos))
        {
            return POSITION_BORDER_LINE;
        }
    }
     
    if (!hasPointInArea(inPos))
    {
        return POSITION_LOCK;
    }
    else{
        return POSITION_UNLOCK;
    }                                 
}



//得到可行走方向
void CShowArea::getAreaMoveAvable(const Vec2& inPoint, std::vector<int>& outDirect)
{

    //节点上可行走方向
    EndPointIterator iter = m_oAreaEndPoint.find(inPoint);
    if (iter != m_oAreaEndPoint.end())
    {
        CUtil::getDirectFromFlag(iter->second, outDirect);
        return;
    }

    //边界上可行走方向
    int positiontype = getPositionType(inPoint);    
    if (positiontype == POSITION_AREA_LINE)
    {
        int marginIndex = hasPointInMargin(inPoint);       
        CMargin* tpMagin = getAreaMargin(marginIndex);         
        CUtil::getDirectFromFlag(tpMagin->m_iAvable, outDirect);                  
        return;
    }

    outDirect.push_back(ANGLE_LEFT);
    outDirect.push_back(ANGLE_RIGHT);
    outDirect.push_back(ANGLE_DOWN);
    outDirect.push_back(ANGLE_UP);
}





/************************************************************************/
/*
* @brief        根据当前边界方向，依赖边界解锁模式得到 在边界垂直方向上可行走方向
* @param[in]    direct  当前边界方向
* @param[out]
* @return       int     垂直于边界的可行走方向
*/
/************************************************************************/
int CShowArea::getMarginDirect(int direct)
{
    int parm    = m_Model == MODEL_IN ? 1 : -1;  
    parm        *= m_iRorate;
    int a1      = CUtil::getNextAngle(direct, parm); 

    return a1;
}



void CShowArea::setState(int sta)
{
    this->m_State = sta;
    switch (sta)
    { 
    case STATE_INIT:                                       
        break;
    case STATE_CLOSE: 
        if (m_RefPath != NULL)
        {
            m_RefPath->clearPoint();
        }

        for (int i = 0; i < MAX_INDEX; i++)
        {
            m_Area[i] = SELECTID_NULL;
        }

        flush();
        break;      
    }    
}


void CShowArea::setClose(const Vec2& inBoss)
{                
    if (!isCloseArea())
    {
        return;
    }       

    //clearAreaIndex();

    ///////////////////////////
    clearSameDirectNode(addArea);
    clearSameDirectNode(resultArea); 

    //BOSS位置确定最终解锁区域
    std::vector<Vec2>* pResult;
    clearPoint();
    if (hasIncludeMaster(inBoss))
    {
        pResult = &addArea;
        if (this->m_Model != MODEL_IN)
        {
            setMode(MODEL_IN);
        }
    }
    else
    {
        pResult = &resultArea;
    }

    for (int i = 0; i < pResult->size(); i++)
    {
        addPoint((*pResult)[i]);
    }

    getAllPoint(m_oAllPoint);

    clearSameDirectNode(m_oAllPoint);
    m_iRorate = CUtil::getRotateDirect(m_oAllPoint);

    log("Rotate:%d", m_iRorate);

    //     if (m_iRorate == DIRECT_ANTICCLOCKWISE)
    //     {
    //         log("fan roate~~~~~~~~~~~~~~~~~~");
    //     }
    getShape(SHAPEID_AREA)->setShape(m_oAllPoint); 

    log("ShowArea Set close");
    setState(STATE_CLOSE);
}


void CShowArea::setPath(CPath* path)
{
    this->m_RefPath = path;
}
            

int CShowArea::getPathType()
{          
    if (m_RefPath->m_oAllPoint.size() < 1)
    {
        return 0;
    }

    const Vec2& tVStart = m_RefPath->m_oAllPoint[0];
    const Vec2& tVEnd   = *(m_RefPath->m_oAllPoint.end() - 1);

    int startType = getPositionType(tVStart);
    int endType = getPositionType(tVEnd);

    log(" startType:%d endType:%d", startType, endType);

    int pathType = startType + endType;
    switch (pathType)
    {
    case POSITION_AREA_ENDPOINT + POSITION_AREA_ENDPOINT:
        log(" End + End");       
        break;
    case POSITION_AREA_LINE + POSITION_AREA_LINE:
        {
        log("Line + LIne");

        int ts = hasPointInMargin(tVStart);
        int tn = hasPointInMargin(tVEnd);

        setAreaIndex(0, ts);
        setAreaIndex(1, tn);
        }
        break;
    case POSITION_AREA_ENDPOINT + POSITION_AREA_LINE:
        {
            log("End + Line");
            if (startType == POSITION_AREA_ENDPOINT)
            {
                setAreaIndex(1, hasPointInMargin(tVEnd));
            }
            else
            {
                setAreaIndex(0, hasPointInMargin(tVStart));
            } 
        } 
        break;
    default:
        log("No close!");
        return 0;
    }                    
    return pathType;
}

void CShowArea::clearAreaIndex()
{                    
    log("-----------------------------------------------------");
    log("area -- %d , %d", m_Area[0], m_Area[1]);
    log("currentDirect:%d", m_iRorate);   
  
    int pathType = getPathType();
   
    switch (pathType)
	{
	case POSITION_AREA_ENDPOINT + POSITION_AREA_ENDPOINT:
		//log(" End + End");
		closedEnd_End();
		break;
	case POSITION_AREA_LINE + POSITION_AREA_LINE:
		//log("Line + LIne");
		closedLine_Line();				
		break;
	case POSITION_AREA_ENDPOINT + POSITION_AREA_LINE:
		//log("End + Line");
		closedLine_End();
		break;
    default:
        return;
	}
	//----------------------------------------------
	
    
}


void CShowArea::closedLine_End()
{    

    const Vec2& vStart		= m_RefPath->m_oAllPoint[0]; 
    const Vec2& vEnd		= *(m_RefPath->m_oAllPoint.end() - 1);     

    EndPointIterator epIter = m_oAreaEndPoint.find(vStart);

    TPoint* pStartPoint;
    TPoint* pEndPoint;            

	std::vector<Vec2> tV1, tV2;
    int pathdirect = CUtil::getRotateDirect(m_RefPath->m_oAllPoint);   

    if (epIter != m_oAreaEndPoint.end())
    {
        log("point in head");

        pStartPoint				= getPoint(vStart);       
        pEndPoint				= getPoint(m_Area[1]);  

		TPoint* pCurrentPoint	= pStartPoint;


        while (pCurrentPoint->id != pEndPoint->id)
        {
            pCurrentPoint = pCurrentPoint->next;
           //log("#%d", pCurrentPoint->id);
            tV1.push_back(pCurrentPoint->vec);
        }

		pStartPoint = pStartPoint->preview;
		while (pCurrentPoint->id != pStartPoint->id)
		{
			pCurrentPoint = pCurrentPoint->next;
			//log("$%d", pCurrentPoint->id);
			tV2.push_back(pCurrentPoint->vec);
		}     
    }
    else
    {
        log("point in brot");   
        pStartPoint				= getPoint(m_Area[0]);        
        pEndPoint				= getPoint(*(m_RefPath->m_oAllPoint.end() - 1));

		TPoint* pCurrentPoint	= pStartPoint->next;       
					
        while (pCurrentPoint->id != pEndPoint->id)
        {
            //log("#%d", pCurrentPoint->id);
            tV1.push_back(pCurrentPoint->vec);

            pCurrentPoint = pCurrentPoint->next;
        }                                          		

		while (pCurrentPoint->id != pStartPoint->id)
		{
			pCurrentPoint = pCurrentPoint->next;

			//log("$%d", pCurrentPoint->id);
			tV2.push_back(pCurrentPoint->vec);
		}
    }

    log("pathdirect:%d" ,pathdirect);  
        
    tV1.insert(tV1.begin(), m_RefPath->m_oAllPoint.rbegin(), m_RefPath->m_oAllPoint.rend());
    tV2.insert(tV2.begin(), m_RefPath->m_oAllPoint.begin(), m_RefPath->m_oAllPoint.end());         

    int area1 = CUtil::getCountPointInRec(tV1, tV2);
    int area2 = CUtil::getCountPointInRec(tV2, tV1);

    log("V1:%d , V2:%d", tV1.size(), tV2.size());
    log("area1:%d , area2:%d", area1, area2);

    if (area1 < area2)
    {
        addArea.insert(addArea.begin(), tV2.begin(), tV2.end());
        resultArea.insert(resultArea.begin(), tV1.begin(), tV1.end());
    }
    else
    {
        addArea.insert(addArea.begin(), tV1.begin(), tV1.end());
        resultArea.insert(resultArea.begin(), tV2.begin(), tV2.end());
    }       
    //selectArea();  
}

/**********************************************************************/
/**
* @brief        解锁起点在 在端点上， 终点在端点上
				
				解锁算法：删除原始区域两个端点，将path区域添加进入原始区域
				解锁区域：path区域	
				
* @param[in]    
* @param[out]
* @return      
*/
/*********************************************************************/
void CShowArea::closedEnd_End()
{
	std::vector<Vec2> toV1, toV2;
	
	Vec2 start          = m_RefPath->m_oAllPoint[0];
	Vec2 end            = *(m_RefPath->m_oAllPoint.end() - 1);

	TPoint* pStart	    = getPoint(start);
	TPoint* pEnd	    = getPoint(end);

	TPoint* pCurrent    = pStart;

	while (pCurrent->vec != pEnd->vec)
	{
        //log("#%d", pCurrent->id);
		toV1.push_back(pCurrent->vec);
		pCurrent = pCurrent->next;
	}
	toV1.push_back(pCurrent->vec);
	

	while (pCurrent->vec != pStart->vec)
	{
        //log("$%d", pCurrent->id);
		toV2.push_back(pCurrent->vec);
		pCurrent = pCurrent->next;
	} 	
	toV2.push_back(pCurrent->vec);
	

	int pathdirect = CUtil::getRotateDirect(m_RefPath->m_oAllPoint);

	toV1.insert(toV1.end(), m_RefPath->m_oAllPoint.rbegin() + 1, m_RefPath->m_oAllPoint.rend() - 1);	
	toV2.insert(toV2.end(), m_RefPath->m_oAllPoint.begin() + 1, m_RefPath->m_oAllPoint.end() - 1);

    int area1 = CUtil::getCountPointInRec(toV1, toV2);
    int area2 = CUtil::getCountPointInRec(toV2, toV1);

    //log("V1:%d , V2:%d", toV1.size(), toV2.size());
    //log("area1:%d , area2:%d", area1, area2);

    if (area1 < area2)
    {
        addArea.insert(addArea.begin(), toV2.begin(), toV2.end());
        resultArea.insert(resultArea.begin(), toV1.begin(), toV1.end());
    }
    else
    {
        addArea.insert(addArea.begin(), toV1.begin(), toV1.end());
        resultArea.insert(resultArea.begin(), toV2.begin(), toV2.end());
    }
	
}

void CShowArea::closedLine_Line()
{
	
    int start = m_Area[0];
    int end = m_Area[1];

    std::vector<Vec2> tempV1, tempV2;
    if (start == end)
    {
        TPoint* current = getPoint(start);

        //------------------------------------------------------
        CMargin* margin = getAreaMargin(start);

        Vec2 sv = *m_RefPath->m_oAllPoint.begin();
        Vec2 ev = *(m_RefPath->m_oAllPoint.end() - 1);
        int angle = CMath::radianToAngle(RADINA_TOGAME(CMath::getRadian(sv, ev)));

        if (angle != margin->m_Angle)
        {
            std::reverse(m_RefPath->m_oAllPoint.begin(), m_RefPath->m_oAllPoint.end());
        }
        //-----------------------------------------------------------------------------

        tempV1.insert(tempV1.begin(), m_RefPath->m_oAllPoint.begin(), m_RefPath->m_oAllPoint.end());

        TPoint* tlink = getTempHead(m_RefPath->m_oAllPoint);
        TPoint* tend = getTempEnd(tlink);

        TPoint* next = current->next;

        current->next = tlink;
        tlink->preview = current;

        tend->next = next;
        next->preview = tend;

        resetId();
        getAllPoint(tempV2);

        int c1 = CUtil::getCountPointInPloyon(tempV1, tempV2);
        int c2 = CUtil::getCountPointInPloyon(tempV2, tempV1);

        if (c1 > c2)
        {
            resultArea.insert(resultArea.begin(), tempV1.begin(), tempV1.end());
            addArea.insert(addArea.begin(), tempV2.begin(), tempV2.end());
        }
        else
        {
            resultArea.insert(resultArea.begin(), tempV2.begin(), tempV2.end());
            addArea.insert(addArea.begin(), tempV1.begin(), tempV1.end());
        }
    }
    else
    {
        TPoint* startPoint = getPoint(start);
        TPoint* endPoint = getPoint(end);

        TPoint* current = startPoint;
        while (current->id != endPoint->id)
        {
            current = current->next;
            tempV1.push_back(current->vec);
            //log("# %d",current->id);
        }
        tempV1.insert(tempV1.begin(), m_RefPath->m_oAllPoint.crbegin(), m_RefPath->m_oAllPoint.crend());

        current = startPoint;
        while (current->id != endPoint->id)
        {
            //log("$ %d", current->id);    
            tempV2.push_back(current->vec);
            current = current->preview;
        }
        tempV2.insert(tempV2.begin(), m_RefPath->m_oAllPoint.crbegin(), m_RefPath->m_oAllPoint.crend());

        //--------------------------------------------------------------

        int c1 = CUtil::getCountPointInPloyon(tempV1, tempV2);
        int c2 = CUtil::getCountPointInPloyon(tempV2, tempV1);
        int rdirect = CUtil::getRotateDirect(m_RefPath->m_oAllPoint);

        log("c1:%d , c2:%d" , c1, c2);
        if (c1 > c2)
        {

            if (rdirect > 0)
            {
                resultArea.insert(resultArea.begin(), tempV1.rbegin(), tempV1.rend());
                addArea.insert(addArea.begin(), tempV2.rbegin(), tempV2.rend());
            }
            else
            {
                resultArea.insert(resultArea.begin(), tempV1.begin(), tempV1.end());
                addArea.insert(addArea.begin(), tempV2.begin(), tempV2.end());
            }
        }
        else
        {
            if (rdirect > 0)
            {
                resultArea.insert(resultArea.begin(), tempV2.rbegin(), tempV2.rend());
                addArea.insert(addArea.begin(), tempV1.rbegin(), tempV1.rend());
            }
            else
            {
                resultArea.insert(resultArea.begin(), tempV2.begin(), tempV2.end());
                addArea.insert(addArea.begin(), tempV1.begin(), tempV1.end());
            }
        }
    }
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


/**********************************************************************/
/*
* @brief        point是否在已解锁区域内，一般模式 
* @param[in]    point   输入坐标
* @param[out]
* @return       bool   在反转模式下 不在区域内为返回结果
                       在一般模式下 在区域内为返回结果
*/
/*********************************************************************/
bool CShowArea::hasPointInArea(const Vec2& point)
{                
    bool result = CUtil::hasPointInPloyon(m_oAllPoint, point);

    switch (m_Model)
    {
    case MODEL_IN: 
        return !result;
    case MODEL_OUT: 
        return result; 
    } 
    return result;
}



bool CShowArea::hasIncludeMaster(const Vec2& bossPosition)
{      
    return CUtil::hasPointInPloyon(addArea, bossPosition);
}


/************************************************************************/
/* 




*/
/************************************************************************/
bool CShowArea::hasOverLoad(const Vec2& inSP ,Vec2& inCP, int angle, int& outIndex)
{       
    //log("hasOverLoad:%f, %f, %d", inSP.x , inSP.y , angle);
    Size visSize    = Director::getInstance()->getVisibleSize();
    Vec2 visVec     = Director::getInstance()->getVisibleOrigin();

    Vec2 tve(Vec2::ZERO);
    switch (angle)
    {
    case ANGLE_DOWN:
        tve.x = inSP.x;        
        break;
    case ANGLE_LEFT:       
        tve.y = inSP.y;
        break;
    case ANGLE_RIGHT:
        tve.x = visSize.width;
        tve.y = inSP.y;
        break;
    case ANGLE_UP: 
        tve.x = inSP.x;
        tve.y = visSize.height;
        break;
    default:
        break;
    }        

    int mindis = -1;
    int tindex = SELECTID_NULL;
    for (int i = 0; i < m_oAllMargin.size(); i++)
    {
        CMargin* maring = static_cast<CMargin*>(this->getChildByTag(m_oAllMargin[i]));

        int r1 = CUtil::getNextAngle(angle, -1);
        int r2 = CUtil::getNextAngle(angle, 1);

        if (r1 != maring->m_Angle && r2 != maring->m_Angle)
        {
            continue;
        }

        if (CMath::hasLineMutlLine(maring->m_oStart, maring->m_oTaget, inSP, tve))
        {
            int dis = static_cast<int>(CMath::getPointToLineDis(maring->m_oStart, maring->m_oTaget, inSP));

            if (dis == 0)
            {
                continue;
            }

            //log("dis:%d", dis);
            if (mindis == -1 || dis < mindis)
            {
                mindis = dis;
                tindex = i;
            }
        }
    }

    //当前距离
    int currentdis = static_cast<int>(ccpDistance(inCP, inSP));

    //log("MiniDis:%d  CurrentDis:%d", mindis, currentdis);

    if (mindis != -1 && currentdis > mindis)
    {

        inCP = CMath::getVec2(inSP, mindis, CMath::angleToRadian(angle));
        CUtil::formartGrid(inCP);
       //log("inCP:%f,%f", inCP.x , inCP.y);

        outIndex = tindex;
        return true;
    } 
    return false;
}

/************************************************************************/
/* 
* @brief        到最小解锁区域边界距离
* @param[in]    inSP    SP起始坐标
                angle   sp当前角度
* @param[out]
* @return
*/
/************************************************************************/
int CShowArea::getMiniAreaDis(const Vec2& inSP, int angle)
{                                                  
    std::vector<CMargin*> tAllMargin;
    for (int i = 0; i < m_oAllMargin.size(); i++)
    {
        CMargin* maring = static_cast<CMargin*>(this->getChildByTag(m_oAllMargin[i]));
        tAllMargin.push_back(maring);
    } 
   return  CUtil::getMinWallDis(tAllMargin, inSP, angle);  
}

int CShowArea::getNearMargin(const Vec2& point)
{
    for (int i = 0; i < m_oAllMargin.size(); i++)
    {
        CMargin* tpMagin = static_cast<CMargin*>(this->getChildByTag(m_oAllMargin[i]));// 

        if (tpMagin->boundingBox().containsPoint(point))
        {             
            return i;
        } 
    } 
    return SELECTID_NULL; 
}






int CShowArea::getMode()
{
    return this->m_Model;
}


void CShowArea::setMode(int mode)
{                            
    this->m_Model = mode;

    switch (mode)
    {
    case MODEL_IN:

        m_pClip->retain();
        this->removeChild(m_pClip,true);
        this->addChild(m_pDrawNode);

        break;
    case MODEL_OUT:         

        m_pDrawNode->retain();
        this->removeChild(m_pDrawNode, true);
        this->addChild(m_pClip);

        break;
    }
}

float CShowArea::getArea()
{   

    Vector2dVector resvv;

    for (int i = 0; i < m_oAllPoint.size();i++)
    {          
        resvv.push_back( Vector2d( m_oAllPoint[i].x, m_oAllPoint[i].y ) );
    }              

    Vector2dVector vv; 
    Triangulate::Process(resvv, vv);

    int tcount = vv.size() / 3;

    float total = 0;
    for (int i = 0; i < tcount; i++)
    {
        const Vector2d &p1 = vv[i * 3 + 0];
        const Vector2d &p2 = vv[i * 3 + 1];
        const Vector2d &p3 = vv[i * 3 + 2];
        Vec2 tvec1[] =
        {
            Vec2(p1.GetX(), p1.GetY()),
            Vec2(p2.GetX(), p2.GetY()),
            Vec2(p3.GetX(), p3.GetY())
        };
       
        total += CMath::getTraingleArea(tvec1[0], tvec1[1], tvec1[2]);       
    }

    //--------------------------------------------------------------------

    Size visSize = m_oAreaSize.size;  

    float totalarea = visSize.width * visSize.height;
    float currentarea = total;

    float area = currentarea / totalarea;

    if (m_Model == MODEL_IN)
    {
        area = 1 - area;
    }
    //log("area:%f", area);
    return area;
}



/************************************************************************/
/*
@brief          得到在未解锁区域内的随机坐标    
@param[out]		outPoint    随机位置坐标  
@return			void
*/
/************************************************************************/
void CShowArea::getRandVec2(Vec2& outPoint)
{ 
    Vec2 tP(Vec2::ZERO);
    bool reCreate = false;
    do 
    {  
        tP.x = CMath::getRandom(m_oAreaSize.origin.x, m_oAreaSize.size.width);
        tP.y = CMath::getRandom(m_oAreaSize.origin.y - m_oAreaSize.size.height, m_oAreaSize.size.height);
        
        CUtil::formartGrid(tP);

        int postiontype = getPositionType(tP);

        switch (postiontype)
        {
        case POSITION_AREA_ENDPOINT:
        case POSITION_AREA_LINE:
        case POSITION_UNLOCK:
        case POSITION_BORDER_ENDPOINT:
        case POSITION_BORDER_LINE:
            reCreate = true;
            break;
        default:
            reCreate = false;
            break;
        } 
        log("is complete random:%d" ,reCreate);
          
    } while (reCreate);

    outPoint = tP;
}




/////////////////////////////////////////////////////////////////////////////////////

void CShowArea::addPoint(const Vec2& point)
{
    TPoint* tp  = new TPoint();   
    tp->vec     = point;

    if (m_pHandle == nullptr)
    {
        m_pHandle   = tp;
        tp->id      = 0;
        tp->isEnd   = true;          
    }
    else
    {
        TPoint* head        = m_pHandle;  
        TPoint* preview     = head;

        int count           = 1;

        while (head->next != nullptr)
        {
            if (head->isEnd)
            {
                break;
            }

            count++;
           
            preview         = preview->next;
            head            = head->next;               
        } 
                      
        if (head->isEnd)
        {
            head->isEnd     = false;
        }

        tp->isEnd           = true;
        tp->id              = count;
        tp->preview         = preview;
        tp->next            = m_pHandle;

        head->next          = tp;  

        m_pHandle->preview  = tp;        
    } 
}


void CShowArea::getAllPoint(std::vector<Vec2>& outputVec)
{
    outputVec.clear();
    
    TPoint* head        = m_pHandle;
    TPoint* realhead    = m_pHandle;
    bool skip           = false;

    while (head != nullptr)
    {    
        if (skip && head == m_pHandle)
        {
            break;
        }                    
                    
        outputVec.push_back(head->vec); 

        head = head->next;         
        if (!skip)
        {
            skip = true;
        }
    }      

    log("Size : %d", outputVec.size());
    clearSamePointNode(outputVec);
    clearSameDirectNode(outputVec);
    log("Size : %d" , outputVec.size());      
}


void CShowArea::clearSameDirectNode(std::vector<Vec2>& outputVec)
{                       
    int direct = ANGLE_NONE;
    Vec2 prV(Vec2::ZERO);
    std::vector<Vec2> alldelid;  

    for (int i = 0; i < outputVec.size(); i++)
    {  
        if (prV == Vec2::ZERO)
        {
            prV = outputVec[0];

        }
        else
        {
            int td = CMath::radianToAngle(RADINA_TOGAME(CMath::getRadian(prV, outputVec[i])));

            //log("Td:%d", td);
            if (td == direct)
            {
                alldelid.push_back(prV);
            }

//             if (prV == outputVec[i])
//             {
//                 //log("Del :%f, %f", prV.x, prV.y);
//                 alldelid.push_back(prV);
//             }                 

            direct = td;
            prV = outputVec[i];
        }  
    }      

    for (int i = 0; i < alldelid.size();i++)
    {
        for (Vec2Iter j = outputVec.begin(); j != outputVec.end(); ++j)
        {
                     
            if (*j == alldelid[i])
            {          
                //log("del %f, %f", alldelid[i].x, alldelid[i].y);
                outputVec.erase(j);
                break;
            }
        }
    } 

    clearPoint();

    for (int i = 0; i < outputVec.size(); i++)
    {                
        addPoint(outputVec[i]);
    }
}


void CShowArea::clearSamePointNode(std::vector<Vec2>& outPutVec)
{
    std::vector<int> allDel;

    for (int i = 0; i < outPutVec.size();i++)
    {
        for (int j = i; j < outPutVec.size();j++)
        {               
            if (i != j && outPutVec[i] == outPutVec[j])
            {      
                log("Del same node ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
                allDel.push_back(i);                
            }
        }
    }
}



unsigned int CShowArea::resetId()
{
    TPoint* head = m_pHandle;      

    unsigned int count = 0;

    TPoint* realhead = head;
    bool skip = false;
    while (head != nullptr)
    {
        
        if (skip && realhead == head)         
        {
            break;
        }

        head->id    = count++;         
        head        = head->next;   

        if (!skip)
        {
            skip = true;
        }
    }

    return count;
}


void CShowArea::delPoint(int index)
{                                  
    if (m_pHandle == nullptr)
    {
        log("link is null!");
        return;
    }                                  
    TPoint* head ;
// 
    if (index == m_pHandle->id)  
    {
        head = m_pHandle->next;  
        TPoint* preview = m_pHandle->preview;
        TPoint* next = m_pHandle->next;

        delete m_pHandle;
        m_pHandle = nullptr;

        preview->next = head;
        head->preview = preview; 

        log("head is delete"); 

        m_pHandle = head;      

        return;
    }           
    //----------------------------------------------------     
    head        = m_pHandle;

    bool skip   = false;
    
    TPoint* realHead = head;

    while (head != nullptr)
    {
        if (skip && head == realHead)
        {
            break;
        }

        if (head->id == index)
        {
            TPoint* currenttp   = head;           //锟斤拷前锟节碉拷
            TPoint* previewtp   = head->preview;  //锟斤拷一锟斤拷锟节碉拷
            TPoint* nexttp      = head->next;

            previewtp->next     = nexttp;
            nexttp->preview     = previewtp;

            delete currenttp;
            currenttp           = nullptr;

            log("body is delete");

            return;
        }

       
        if (!skip)
        {
            skip = true;
        }
        head        = head->next;               
    }
    log("no id:%d element", index);
}




TPoint* CShowArea::getPoint(int index)
{                                 
    TPoint* head        = m_pHandle; 

    TPoint* realHead    = head;   
    bool skip           = false; 

    while (head != nullptr)
    {
        if (skip && head == realHead)
        {
            break;
        }                        
        //--------------------------------------

        if (head->id == index)
        {
            return head;
        }                               
        head = head->next;

        //--------------------------------------

        if (!skip)
        {
            skip = true;
        }                               
    }                           
    return nullptr;
}


TPoint* CShowArea::getPoint(const Vec2& inPosition)
{
	TPoint* head        = m_pHandle; 

	TPoint* realHead    = head;   
	bool skip           = false; 

	while (head != nullptr)
	{
		if (skip && head == realHead)
		{
			break;
		}                        
		//--------------------------------------

		if (head->vec == inPosition)
		{
			return head;
		}                               
		head = head->next;

		//--------------------------------------

		if (!skip)
		{
			skip = true;
		}                               
	}                           
	return nullptr;

}





/*
TPoint* current     = m_pHandle;
bool skip           = false;
TPoint* realHead    = current;

while (current != nullptr)
{
if (skip && current == realHead)
{
break;
}





current = current->next;

if (!skip)
{
skip = true;
}
}
*/
TPoint* CShowArea::getTempHead(const std::vector<Vec2>& allpoint)
{
    TPoint* thead = nullptr;
    
    for (int i = 0; i < allpoint.size(); i++)
    {                                                                
        TPoint* tp = new TPoint();
        tp->vec = allpoint[i];

        if (thead == nullptr)
        {
            thead               = tp; 
            thead->id           = 1000;
        }
        else
        {
            int count           = 1001;
            TPoint* head        = thead;
            TPoint* preview     = head;  

            while (head->next != nullptr)
            {
                count++;
                preview         = preview->next;
                head            = head->next; 
            }
          
            tp->id              = count;
            tp->preview         = preview; 
            head->next          = tp;          
        }
    }
    return thead;
}


TPoint* CShowArea::getTempEnd(TPoint* hp)
{
    TPoint* head = hp;
    while (head->next != nullptr)
    {                                       
        if (head->isEnd)
        {
            return head;
        }                 
        head = head->next;
    }

    return head;
}

void CShowArea::clearPoint()
{
       
    TPoint* current     = m_pHandle;
    bool skip           = false;
    TPoint* realHead    = current;

    while (current != nullptr)
    {
        if (skip && current == realHead)
        {
            break;
        }

        TPoint* temp    = current;
        current         = current->next;

        delete temp;
        temp = nullptr;

        if (!skip)
        {
            skip = true;
        }
    }

    m_pHandle = nullptr;

}

void CShowArea::printPoint(TPoint* hp)
{                       

    TPoint* head = hp;

    TPoint* realhead = hp;

    bool skip = false;

    log("==============================");

    if (head == nullptr)

    {
        log("link no node");
        return;
    }

    while (head != nullptr)
    {                                     
        if (skip && head == realhead)
        {
            break;
        }

        log("TP:%d, \tpreview:%d  \tnext:%d", 
            head->id, 
            head->preview != nullptr ? head->preview->id : -1,
            head->next != nullptr ? head->next->id : -1
            );
        head = head->next;                                                

        if (!skip)
        {
            skip = true;
        }
    }
}




/************************************************************************/
/*
@brief			

@param[in]		int start
				int end   
@param[out]

@return			int
*/
/************************************************************************/


