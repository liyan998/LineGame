#include "ShowArea.h"
#include "util/Util.h"      
#include "util/Math.h"



using namespace liyan998;   

//#define DEBUG_LINE

bool CShowArea::init()
{
    Sprite::init();   
    m_Model     = MODEL_OUT; 

    m_pPath     = nullptr;        
    m_pHandle   = nullptr;

    Size visibleSize = Director::getInstance()->getVisibleSize();

    //--------------------------------------

    for (int i = 0; i < MAX_INDEX; i++)
    {
        m_Area[i] = SELECTID_NULL;
    }

    //------------------------------------

    log("CShowArea::init...");   

    auto pSprite = Sprite::create("HelloWorld.png");
    pSprite->setPosition(visibleSize.width / 2, visibleSize.height / 2);
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
                                  
   //----------------------------------------    
	
   Vec2 origin = Director::getInstance()->getVisibleOrigin();
   Size screen = Director::getInstance()->getVisibleSize();

   Rect rec(
       GRAD_NUMBER(screen.width / 2 + origin.x - 40), 
       GRAD_NUMBER(screen.height / 2 + origin.y + 40),
       GRAD_NUMBER(80),       
       GRAD_NUMBER(80)
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

void CShowArea::flushMargin()
{                  

    log("flush margin");
    for (int i = 0; i < m_oAllMargin.size(); i++)
    {
        this->removeChildByTag(m_oAllMargin[i]);
    }

    m_oAllMargin.clear();
    m_oAllEndPoint.clear();

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
        pMarg->getAvableDirect(m_oAllPoint, m_oAllEndPoint);
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
    for (EndPointIterator iter = m_oAllEndPoint.begin(); iter != m_oAllEndPoint.end(); ++iter)
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
            if (gpt == POSITION_LINE)
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
    for (int i = 0; i < m_pPath->m_oAllPoint.size(); i++)
    {
        dn->drawDot(m_pPath->m_oAllPoint[i], 10, Color4F(1, 1,0.5, 0.3));
    }



    //log("c1 %d c2 %d", c1, c2);
//     getShape(SHAPEID_TEMP)->setShape(resultArea);
//     getShape(SHAPEID_TEMP)->setColor(Color4F(1, 0, 0.5, 1), Color4F(1, 0, 0.5, 0.3));
//     getShape(SHAPEID_TEMP)->draw(dn);
// 
    getShape(SHAPEID_AREA)->setShape(addArea);
    getShape(SHAPEID_AREA)->setColor(Color4F(0, 1, 0.5, 1), Color4F(1, 1, 0, 0.2));
    getShape(SHAPEID_AREA)->draw(dn);
    
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

CMargin* CShowArea::getMargin(int index)
{
    if (index < 0 || index > m_oAllMargin.size() - 1)
    {
        return NULL;
    }
    return static_cast<CMargin*>(this->getChildByTag(m_oAllMargin[index]));
}



bool CShowArea::isCloseArea()
{
    if (m_pPath == nullptr || m_pPath->m_oAllPoint.size() < 2)
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



int CShowArea::getPositionType(const Vec2& inPos)
{

    for (int i = 0; i < m_oAllMargin.size(); i++)
    {
        CMargin* tpMagin = static_cast<CMargin*>(this->getChildByTag(m_oAllMargin[i]));//

        if (inPos == tpMagin->m_oStart || inPos == tpMagin->m_oTaget)
        {
            return POSITION_ENDPOINT;
        }    
        else if (CUtil::hasPointInLine(tpMagin->m_oStart, tpMagin->m_oTaget, inPos))
        {
            return POSITION_LINE;
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
void CShowArea::getMoveAble(const Vec2& inPoint, std::vector<int>& outDirect)
{

    //节点上可行走方向
    EndPointIterator iter = m_oAllEndPoint.find(inPoint);
    if (iter != m_oAllEndPoint.end())
    {
        CUtil::getDirectFromFlag(iter->second, outDirect);
        return;
    }

    //边界上可行走方向
    int positiontype = getPositionType(inPoint);    
    if (positiontype == POSITION_LINE)
    {
        int marginIndex = hasPointInMargin(inPoint);       
        CMargin* tpMagin = getMargin(marginIndex);         
        CUtil::getDirectFromFlag(tpMagin->m_iAvable, outDirect);                  
        return;
    }

    outDirect.push_back(ANGLE_LEFT);
    outDirect.push_back(ANGLE_RIGHT);
    outDirect.push_back(ANGLE_DOWN);
    outDirect.push_back(ANGLE_UP);
}


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
    {                  
    }                                             
        break;
    case STATE_CLOSE:
        if (isCloseArea())
        {
            clearAreaIndex();
        }     
        
        if (m_pPath != NULL)
        {            
            m_pPath->clearPoint();
        }        

        for (int i = 0; i < MAX_INDEX; i++)
        {
            m_Area[i] = SELECTID_NULL;
        }

        flush();

        

        break;      
    }    
}




void CShowArea::setPath(CPath* path)
{
    this->m_pPath = path;
}
            

int CShowArea::getPathType()
{          
    if (m_pPath->m_oAllPoint.size() < 1)
    {
        return 0;
    }

    const Vec2& tVStart = m_pPath->m_oAllPoint[0];
    const Vec2& tVEnd   = *(m_pPath->m_oAllPoint.end() - 1);

    int startType = getPositionType(tVStart);
    int endType = getPositionType(tVEnd);

    log(" startType:%d endType:%d", startType, endType);

    int pathType = startType + endType;
    switch (pathType)
    {
    case POSITION_ENDPOINT + POSITION_ENDPOINT:
        log(" End + End");       
        break;
    case POSITION_LINE + POSITION_LINE:
        {
        log("Line + LIne");

        int ts = hasPointInMargin(tVStart);
        int tn = hasPointInMargin(tVEnd);

        setAreaIndex(0, ts);
        setAreaIndex(1, tn);
        }
        break;
    case POSITION_ENDPOINT + POSITION_LINE:
        {
            log("End + Line");
            if (startType == POSITION_ENDPOINT)
            {
                setAreaIndex(1, hasPointInMargin(tVEnd));
            }
            else{
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
//     if (m_Area[0] == -1 || m_Area[1] == -1)
//     {
//         log("no area %d | %d", m_Area[0], m_Area[1]);
//         return;
//     }   
    log("-----------------------------------------------------");
    log("area -- %d , %d", m_Area[0], m_Area[1]);

  
    int pathType = getPathType();
   
    switch (pathType)
	{
	case POSITION_ENDPOINT + POSITION_ENDPOINT:
		//log(" End + End");
		closedEnd_End();
		break;
	case POSITION_LINE + POSITION_LINE:
		//log("Line + LIne");
		closedLine_Line();				
		break;
	case POSITION_ENDPOINT + POSITION_LINE:
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

    const Vec2& vStart		= m_pPath->m_oAllPoint[0]; 
    const Vec2& vEnd		= *(m_pPath->m_oAllPoint.end() - 1);     

    EndPointIterator epIter = m_oAllEndPoint.find(vStart);

    TPoint* pStartPoint;
    TPoint* pEndPoint;            

	std::vector<Vec2> tV1, tV2;
    int pathdirect = CUtil::getRotateDirect(m_pPath->m_oAllPoint);   

    if (epIter != m_oAllEndPoint.end())
    {
        log("point in head");

        pStartPoint				= getPoint(vStart);       
        pEndPoint				= getPoint(m_Area[1]);  

		TPoint* pCurrentPoint	= pStartPoint;


        while (pCurrentPoint->id != pEndPoint->id)
        {
            pCurrentPoint = pCurrentPoint->next;
           // log("#%d", pCurrentPoint->id);
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
        pEndPoint				= getPoint(*(m_pPath->m_oAllPoint.end() - 1));

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

    if (pathdirect == DIRECT_CLOCKWISE)
    {
        tV1.insert(tV1.begin(), m_pPath->m_oAllPoint.rbegin(), m_pPath->m_oAllPoint.rend());
        tV2.insert(tV2.begin(), m_pPath->m_oAllPoint.begin(), m_pPath->m_oAllPoint.end());

        addArea.insert(addArea.begin(), tV1.begin(), tV1.end());
        resultArea.insert(resultArea.begin(), tV2.begin(), tV2.end());

    }
    else if (pathdirect == DIRECT_ANTICCLOCKWISE)
    {
        tV1.insert(tV1.begin(), m_pPath->m_oAllPoint.rbegin(), m_pPath->m_oAllPoint.rend());
        tV2.insert(tV2.begin(), m_pPath->m_oAllPoint.begin(), m_pPath->m_oAllPoint.end());

        addArea.insert(addArea.begin(), tV2.begin(), tV2.end());
        resultArea.insert(resultArea.begin(), tV1.begin(), tV1.end());
    }
    else{       
        
        tV1.insert(tV1.begin(), m_pPath->m_oAllPoint.rbegin(), m_pPath->m_oAllPoint.rend());
        tV2.insert(tV2.begin(), m_pPath->m_oAllPoint.begin(), m_pPath->m_oAllPoint.end()); 
        
        int area1 = CUtil::getCountPointInPloyon(tV1, tV2);
        int area2 = CUtil::getCountPointInPloyon(tV2, tV1);

        //log("area1:%d , area2:%d", area1, area2);

        if (area1 > area2)
        {
            addArea.insert(addArea.begin(), tV2.begin(), tV2.end());
            resultArea.insert(resultArea.begin(), tV1.begin(), tV1.end());
        }
        else
        {
            addArea.insert(addArea.begin(), tV1.begin(), tV1.end());
            resultArea.insert(resultArea.begin(), tV2.begin(), tV2.end());
        } 
    }

  selectArea();

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
	
	Vec2 start          = m_pPath->m_oAllPoint[0];
	Vec2 end            = *(m_pPath->m_oAllPoint.end() - 1);

	TPoint* pStart	    = getPoint(start);
	TPoint* pEnd	    = getPoint(end);

	TPoint* pCurrent    = pStart;

	while (pCurrent->vec != pEnd->vec)
	{
        log("#%d", pCurrent->id);
		toV1.push_back(pCurrent->vec);
		pCurrent = pCurrent->next;
	}
	toV1.push_back(pCurrent->vec);
	

	while (pCurrent->vec != pStart->vec)
	{
        log("$%d", pCurrent->id);
		toV2.push_back(pCurrent->vec);
		pCurrent = pCurrent->next;
	} 	
	toV2.push_back(pCurrent->vec);
	

	int pathdirect = CUtil::getRotateDirect(m_pPath->m_oAllPoint);

	if (pathdirect == DIRECT_CLOCKWISE)
	{
		toV1.insert(toV1.end(), m_pPath->m_oAllPoint.rbegin() + 1, m_pPath->m_oAllPoint.rend() - 1);	
		toV2.insert(toV2.end(), m_pPath->m_oAllPoint.begin() + 1, m_pPath->m_oAllPoint.end() - 1);
		//--------------------------------------------
		addArea.insert(addArea.begin(), toV1.begin(), toV1.end());
		resultArea.insert(resultArea.begin(), toV2.begin(), toV2.end() );
	}
	else if (pathdirect == DIRECT_ANTICCLOCKWISE)
	{
		toV1.insert(toV1.end(), m_pPath->m_oAllPoint.rbegin() + 1, m_pPath->m_oAllPoint.rend() - 1);
		toV2.insert(toV2.end(), m_pPath->m_oAllPoint.begin() + 1, m_pPath->m_oAllPoint.end() - 1);

		addArea.insert(addArea.begin(), toV2.begin(), toV2.end());
		resultArea.insert(resultArea.begin(), toV1.begin(), toV1.end());
	}
    else
    {      
        toV2.insert(toV2.end(), m_pPath->m_oAllPoint.begin() + 1, m_pPath->m_oAllPoint.end() - 1);
        toV1.insert(toV1.end(), m_pPath->m_oAllPoint.rbegin() + 1, m_pPath->m_oAllPoint.rend() - 1);
           
        int area1 = CUtil::getCountPointInPloyon(toV1, toV2);
        int area2 = CUtil::getCountPointInPloyon(toV2, toV1);

        if (area1 > area2)
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
	selectArea();
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
        CMargin* margin = getMargin(start);

        Vec2 sv = *m_pPath->m_oAllPoint.begin();
        Vec2 ev = *(m_pPath->m_oAllPoint.end() - 1);
        int angle = CMath::radianToAngle(RADINA_TOGAME(CMath::getRadian(sv, ev)));

        if (angle != margin->m_Angle)
        {
            std::reverse(m_pPath->m_oAllPoint.begin(), m_pPath->m_oAllPoint.end());
        }
        //-----------------------------------------------------------------------------

        tempV1.insert(tempV1.begin(), m_pPath->m_oAllPoint.begin(), m_pPath->m_oAllPoint.end());

        TPoint* tlink = getTempHead(m_pPath->m_oAllPoint);
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
            log("# %d",current->id);
        }
        tempV1.insert(tempV1.begin(), m_pPath->m_oAllPoint.crbegin(), m_pPath->m_oAllPoint.crend());

        current = startPoint;
        while (current->id != endPoint->id)
        {
            log("$ %d", current->id);    
            tempV2.push_back(current->vec);
            current = current->preview;
        }
        tempV2.insert(tempV2.begin(), m_pPath->m_oAllPoint.crbegin(), m_pPath->m_oAllPoint.crend());

        //--------------------------------------------------------------

        int c1 = CUtil::getCountPointInPloyon(tempV1, tempV2);
        int c2 = CUtil::getCountPointInPloyon(tempV2, tempV1);
        int rdirect = CUtil::getRotateDirect(m_pPath->m_oAllPoint);

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
	
	selectArea();
}


void CShowArea::selectArea()
{
    clearSameLineNode(addArea);
    clearSameLineNode(resultArea);


	std::vector<Vec2>* pResult;
	clearPoint();
	if (hasIncludeMaster())
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

    clearSameLineNode(m_oAllPoint);
	m_iRorate = CUtil::getRotateDirect(m_oAllPoint);

	log("Rotate:%d", m_iRorate);
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



bool CShowArea::hasIncludeMaster()
{ 
    return CUtil::hasPointInPloyon(addArea, Vec2(100, 500));
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


int CShowArea::getMiniWallDis(const Vec2& inSP, int angle)
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

    Size visSize = Director::getInstance()->getVisibleSize();  

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
    clearSameLineNode(outputVec);
    log("Size : %d" , outputVec.size());      
}


void CShowArea::clearSameLineNode(std::vector<Vec2>& outputVec)
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


