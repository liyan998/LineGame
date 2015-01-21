
/************************************************************************/
/* 
 @auther    严黎刚
 @date      2014-10-28


*/
/************************************************************************/
#include "MySprite.h" 

#include "util/Math.h"
#include "util/Util.h"

#include "Margin.h"

#include "EventSystem.h" 

#include "GameElement.h"


using namespace liyan998;

bool CMySprite::init()
{
    Node::init();

    m_currentAngle      = ANGLE_NONE;
    m_fStep				= 6.f;
    m_iCountRecord      = 0;
    m_curMarginIndex    = SELECTID_NULL; 

    m_iMaxHealth        = 2;
    m_iHealth           = m_iMaxHealth;
  
    //----------------------------------------------------- 

    ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(
        RES_ANIMA_PNG_COOLKING,
        RES_ANIMA_PLS_COOLKING,
        RES_ANIMA_JSO_COOLKING
        );
    
    setCurrentAnimation(ARMATURE_COOLKING);
    getArmature()->setAnchorPoint(Vec2(0.5f, 0.2f));
    getArmature()->setOpacity(255 * 0.4);
    getArmature()->getAnimation()->playByIndex(0);


    //----------------------------------------------------

//     DrawNode* pDn = DrawNode::create();	
//     addChild(pDn);                                      
//     pDn->drawDot(Vec2::ZERO, 20, Color4F(1, 0, 0, 0.5));       
//     this->setAnchorPoint(Vec2::ZERO);
//     this->setContentSize(Size(40,40));

    //---------------------------------------------------

    //Rect& rec = this->getBoundingBox();     
    //log("bundBox:%f, %f, %f, %f", rec.origin.x, rec.origin.y, rec.size.width , rec.size.height);     

    CEventDispatcher::getInstrance()->regsiterEvent(EVENT_PROPERTY_ADDHEALTH, this);

    return true;
}

                
void CMySprite::actionEvent(int eventid, EventParm pData)
{
    switch (eventid)
    {
    case EVENT_PROPERTY_ADDHEALTH:       
        h_actionAddHealth(pData);
        break;
    default:
        break;
    }
}

void CMySprite::h_actionAddHealth(EventParm pData)
{
    float addpart = *(float*)pData;

    int addv = (int)(m_iMaxHealth * addpart);

    if (m_iHealth + addv >= m_iMaxHealth)
    {
        m_iHealth = m_iMaxHealth;
    }
    else
    {
        m_iHealth += addv;
    }
}


int CMySprite::getHealth()
{
    return this->m_iHealth;
}

inline
void CMySprite::setPlayerPosition(const Vec2& pos)
{
    m_oSpCurrentPos = pos;
    m_refPlayer->setPlayerPosition(pos);
}





void CMySprite::setSpStartPosition()
{
    log("sp Ready to Move");
    this->m_oSpStartPos = this->m_oSpCurrentPos; 
    CUtil::formartGrid(m_oSpStartPos);
   
}
                                  
/************************************************************************/
/*
@brief        设置精灵状态
@param[in]     state   状态值
@param[out]
@return        void
*/
/************************************************************************/
void CMySprite::setState(int state)                                                                           
{               
    log("------------------------------------------");
    this->m_State = state;   
    switch (state)
    {        
    case STATE_INIT:
    {                                                        
        int setLine = CMath::getRandom(0,3);
        CMargin* margin = m_refShowArea->getAreaMargin(setLine);
        m_curMarginIndex = setLine;
        float dis = ccpDistance(margin->m_oStart, margin->m_oTaget);
        int ranint = CMath::getRandom(0, dis);
        const Vec2& ps = CMath::getVec2(margin->m_oStart, ranint, CMath::angleToRadian(margin->m_Angle));

        setState(STATE_STANDER);
        setPlayerPosition(Vec2(GRAD_NUMBER(ps.x), GRAD_NUMBER(ps.y)));
        log("!!!!!%f , %f", ps.x, ps.y);  
    }
        break;
    case STATE_STANDER:          
        log("mysprite state STATE_STANDER");   
        break;
    case STATE_MOVE:     
        log("mysprite state STATE_MOVE");    
        m_currentAngle = ANGLE_NONE;            
        setSpStartPosition();       
        break;            
    case STATE_BACK:
        log("mysprite state STATE_BACK"); 
        clearRoad();
        m_refPlayer->setState(CGamePlayer::STATE_STOP);
        checkBack();
        break;
    case STATE_CLOSE:      
        log("mysprite state STATE_CLOSE");
        break;
    case STATE_DRAW:
        log("mysprite state STATE_DRAW"); 
        break;
    }
}                




/************************************************************************/
/* 
 @brief        设置移动起始点
 @param[in]     point   输入坐标
 @param[out]    
 @return        void 
*/
/************************************************************************/
void CMySprite::setDirectStartPosition(const Vec2& point)
{
    this->m_oDirectStart = point;
}


/************************************************************************/
/**
* @brief        屏幕指针按下
* @param[in]    vec2   输入坐标
* @param[out]
* @return       void
*/
/************************************************************************/
void CMySprite::onPressed(const Vec2& vec2)
{
    //log("~~~~~~~~~~~~~ %d",m_State);
    switch (m_State)
    {
    case STATE_INIT:
        break;
    case STATE_BACK:
       // onStander(vec2);
        break;
    case STATE_CLOSE:
        break;
    case STATE_STANDER: 

        if (m_refShowArea != nullptr)
        {
            m_refShowArea->resultArea.clear();
            m_refShowArea->addArea.clear();
        }
        
        onStander(vec2);
        break;
    case STATE_DRAW:
        break;
    case STATE_MOVE:
        break;
    default:
        break;
    }          
}

/**********************************************************************/
/* 
* @brief        屏幕指针移动
* @param[in]    point   输入坐标
* @param[out]   
* @return       void
*/
/*********************************************************************/
void CMySprite::onMove(const Vec2& point)
{              
   
    switch (m_State)
    {
    case STATE_INIT:
        break;
    case STATE_BACK:
        break;
    case STATE_CLOSE:
        break;
    case STATE_STANDER:
        break;
    case STATE_DRAW:
    {   
        checkDirect(point);
        if (!hasInBorder())
        {
            //log("draw _ inBorder~~~~~~");
            return;
        }
        if (!hasMoveAction())
        {
            log("STATE_DRAW don't move it");
            return;
        }
        onDrawToClose(point);
        playerMove(m_oSpCurrentPos);
    }
        break;
    case STATE_MOVE:
    {                           
        checkDirect(point);
        //hasInBorder();
        hasBreakMoveInLine();
        if (!hasMoveAction())
        {
            log("STATE_MOVE don't move it");
            return;
        }                                                
        onMoveToDraw();     
        //-----------------------------------  
        fixPosition(point, m_oSpCurrentPos);        
        //---------------------------------   
        playerMove(m_oSpCurrentPos);      
        //----------------------------------------
    }
        break;
    default:
        break;
    }       
}




/**********************************************************************/
/*
* @brief        屏幕指针释放-
* @param[in]    point   输入坐标
* @param[out]
* @return       void
*/
/*********************************************************************/
void CMySprite::onReleased(const Vec2& pointer)
{                    
    switch (m_State)
    {
    case STATE_INIT:
        break;
    case STATE_BACK:
        break;
    case STATE_CLOSE:
        break;
    case STATE_STANDER:
        break;
    case STATE_DRAW:
        setState(CMySprite::STATE_BACK);
        break;
    case STATE_MOVE:
        setState(CMySprite::STATE_STANDER);
        break;
    default:
        break;
    }
}



/**********************************************************************/
/*
* @brief        在边界内移动，离开边界转换为划线状态
* @param[in]    inPoint   输入坐标
* @param[out]
* @return       void
*/
/*********************************************************************/
bool CMySprite::hasMoveAction()
{   
    std::vector<int> abv; 

    switch (getState())
    {
    case STATE_MOVE:                       
       m_refShowArea->getAreaMoveAvable(m_oSpCurrentPos, abv);
        break;
    case STATE_DRAW:
       m_refPath->getMoveAble(m_currentAngle, m_oSpCurrentPos, abv);
        break;        
    }     

    for (int i = 0; i < abv.size();i++)
    {
        if (m_currentAngle == abv[i])
        {    
           
            return true;
        }
    }                         

    return false;
}




/************************************************************************/
/* 
* @brief        是否与边界发生相交，限制在边界上
* @param[in]    
* @param[out]
* @return       bool    
*/
/************************************************************************/
bool CMySprite::hasInBorder()
{
    int dis = m_refShowArea->getBorderDis(m_oSpStartPos, m_currentAngle); 
    //log("dis = %d, angle:%d",dis,  m_currentAngle);
    if (dis == -1)
    {
        return false;
    }                               

    int currdis = ccpDistance(m_oSpStartPos, m_oSpCurrentPos);
    //log("border dis:%d  , current Dis:%d", dis, currdis); 

    if (currdis + GRAD_CELL >= dis)
    {                              
        Vec2 stopVec2 = CMath::getVec2(m_oSpStartPos, dis - GRAD_CELL, CMath::angleToRadian(m_currentAngle));
        CUtil::formartGrid(stopVec2);

        m_refPlayer->fixTargetPostion(m_oSpCurrentPos, stopVec2);
        m_oSpCurrentPos     = stopVec2;
        m_oAbsStartPos      = m_oAbsEndPos;


       // m_oSpStartPos       = m_oSpCurrentPos;

        //m_RefPlayer->setPlayerPosition(m_oSpCurrentPos);
        //m_RefPlayer->setTarget(m_oSpCurrentPos);

        //log("dis < currentdis %f,%f", m_oSpCurrentPos.x, m_oSpCurrentPos.y);

        return false;
    }

    return true;
}


void CMySprite::onDrawToClose(const Vec2& inPoint)
{                   
    //log("Draw To Close====================");
    fixPosition(inPoint, m_oSpCurrentPos); 
    if (m_oSpStartPos != m_oSpCurrentPos)
    {
        fixPath(inPoint);
    }
    //-------------------------------------
 

    //-----------------------------------------------------------       
    //path over load
    int index = SELECTID_NULL;
    if (m_refPath->hasOverLoad(m_oSpStartPos, m_oSpCurrentPos, m_currentAngle))
    {
        //log("over load~~~~~~~~~~~~~~~~~~~~~");
        return;
    }
    
    //Area过界判断 
    if (m_refShowArea->hasOverLoad(m_oSpStartPos, m_oSpCurrentPos, m_currentAngle, index))
    {
        log("over load in Area%d", index);
        if (m_refPath->m_oAllPoint.size() > 0 && m_oSpCurrentPos == (*m_refPath->m_oAllPoint.begin()))
        {
            log("start point == end point");
            m_refPath->m_oAllPoint.clear();
            setState(STATE_BACK);
            return;
        } 


        addGuide(m_oSpCurrentPos);

        switch (m_refShowArea->getPathType())
        {
        case POSITION_AREA_ENDPOINT + POSITION_AREA_ENDPOINT:
        case POSITION_AREA_LINE + POSITION_AREA_LINE:
        case POSITION_AREA_LINE + POSITION_AREA_ENDPOINT:
            m_refShowArea->setAreaIndex(1, index);
            m_curMarginIndex = index;
            setState(STATE_CLOSE);
            return;
        }
    }

    int postiontype = m_refShowArea->getPositionType(m_oSpCurrentPos);
    switch (postiontype)
    {
    case POSITION_AREA_ENDPOINT:       
    case POSITION_AREA_LINE:
        
        if (postiontype == POSITION_AREA_ENDPOINT)
        {
            if (m_refPath->m_oAllPoint.size() > 0 && m_oSpCurrentPos == (*m_refPath->m_oAllPoint.begin()))
            {
                log("start point == end point");
                m_refPath->m_oAllPoint.clear();
                setState(STATE_BACK);
                return;
            }

            addGuide(m_oSpCurrentPos); 
        }
        else
        {
            index = m_refShowArea->getNearMargin(m_oSpCurrentPos);
            if (index == SELECTID_NULL)
            {
                m_refPath->m_oAllPoint.clear();
                setState(STATE_BACK);
                return;
            }
            else if (m_refPath->m_oAllPoint.size() > 0 && m_oSpCurrentPos == (*m_refPath->m_oAllPoint.begin()))
            {
                log("start point == end point");
                m_refPath->m_oAllPoint.clear();
                setState(STATE_BACK);
                return;
            }     

            addGuide(m_oSpCurrentPos);
            m_refShowArea->setAreaIndex(1, index);
            m_curMarginIndex = index;           
        }                      
        setState(STATE_CLOSE);
        return;
    }



    //playerGoWay();


   
//     index = m_RefShowArea->getNearMargin(m_oSpCurrentPos);        
//     if (index == SELECTID_NULL)     
//     {
//         return;                                                 
//     }                       

    //------------------------------------------------------

//     CMargin* margin = m_RefShowArea->getMargin(index);
//     Vec2 endp = CMath::getFootPoint(margin->m_oStart, margin->m_oTaget, m_oSpStartPos);
//     CUtil::formartGrid(endp);    
//     //
//     if (m_RefPath->m_oAllPoint.size() > 0 && endp == (*m_RefPath->m_oAllPoint.begin()))
//     {
//         log("start point == end point");
//         m_RefPath->m_oAllPoint.clear();
//         setState(STATE_BACK);
//         return;
//     }                          
// 
//     int type = m_RefShowArea->getPositionType(endp);
//     log("type:%d" ,type);
// 
//     addGuide(endp);
// 
//     m_RefShowArea->setAreaIndex(1, index);
//     m_curMarginIndex = index;  
// 
//     setState(STATE_CLOSE);
}


void CMySprite::onStander(const Vec2& inPoint)
{
    int selectindex = m_refShowArea->getTargetIndex(inPoint);
    if (selectindex != SELECTID_NULL)
    {
        m_curMarginIndex = selectindex;

        log("location position %d", selectindex);

        CMargin* tMargin = m_refShowArea->getAreaMargin(selectindex);
        Vec2 refp = CMath::getFootPoint(tMargin->m_oStart, tMargin->m_oTaget, inPoint);
        CMath::getIntPoint(refp);

        setPlayerPosition(refp);      
    }
    else
    {                 //
        setState(STATE_MOVE);
        m_oDirectStart  = inPoint;
        m_oAbsStartPos  = inPoint;
        m_oAbsEndPos    = m_oAbsStartPos;
    }

}


/**********************************************************************/
/*
* @brief        在边界内移动，离开边界转换为划线状态
* @param[in]    inPoint   输入坐标
* @param[out]
* @return       void
*/
/*********************************************************************/
void CMySprite::onMoveToDraw()
{
    if (m_curMarginIndex == SELECTID_NULL)
    {
        return;
    }  

    //CUtil::formartGrid(m_oSpCurrentPos); 
       
    int posType = m_refShowArea->getPositionType(m_oSpCurrentPos);
    
    switch (posType)
    {
    case POSITION_UNLOCK:                                                                      
        break;
    case POSITION_LOCK:
        {                           

            int startpostype = m_refShowArea->getPositionType(m_oGuideLStart);
            //log("StartPositionType:%d", startpostype);                   
            if (startpostype == POSITION_AREA_LINE)
            {                                        
                int index = m_refShowArea->getTargetIndex(m_oGuideLStart);
                m_refShowArea->setAreaIndex(0, index);
            }

            addGuide(m_oGuideLStart);          
            setState(STATE_DRAW);
        }
        break;
    case POSITION_AREA_LINE:
    case POSITION_AREA_ENDPOINT:       
       // log("POSITION_ENDPOINT + POSITION_LINE");
        //log("min %f, %f", m_oSpCurrentPos.x ,m_oSpCurrentPos.y);
        m_oGuideLStart = m_oSpCurrentPos;
        m_refPlayer->setPlayerPosition(m_oSpCurrentPos);
        break;

    }


    //log("Start : %f, %f  , Current:%f, %f", m_oSpStartPos.x, m_oSpStartPos.y, m_oSpCurrentPos.x, m_oSpCurrentPos.y);
    //     
//     int tindex = m_RefShowArea->hasPointInMargin(m_oSpCurrentPos);
//     CMargin* margin = m_RefShowArea->getMargin(m_curMarginIndex);



    //是否在边界上
//         if (tindex != SELECTID_NULL)
//         {                
//             m_curMarginIndex = tindex;
//             m_RefPlayer->setPlayerPosition(m_oSpCurrentPos);
//             m_oGuideLStart = m_oSpCurrentPos; 
//         }
//         else
//         {
//             int tangle1 = CUtil::getRevceDircet(margin->m_Angle);
//     
//             if (m_currentAngle == tangle1 || m_currentAngle == margin->m_Angle)
//             {
//                 int dis1 = ccpDistance(m_oSpCurrentPos, margin->m_oStart);
//                 int dis2 = ccpDistance(m_oSpCurrentPos, margin->m_oTaget);             
//           
//                 if (dis1 < dis2)
//                 {
//                     m_oGuideLStart = margin->m_oStart;
//                 }
//                 else
//                 {
//                     m_oGuideLStart = margin->m_oTaget;
//                 }           
//             }
//             
//             
//             
//     
//             //------------------------------------------------
//             //draw   
//     
//             m_oAbsStartPos = m_oAbsEndPos;       
//             addGuide(m_oGuideLStart);          
//             m_RefShowArea->setAreaIndex(0, m_curMarginIndex); 
//             setState(STATE_DRAW);
//         }
}

bool CMySprite::hasBreakMoveInLine()
{                   
    CUtil::formartGrid(m_oSpCurrentPos);

    int dis = m_refShowArea->getMiniAreaDis(m_oSpStartPos, m_currentAngle);
    if (dis == -1)
    {
        //
        m_oGuideLStart = m_oSpStartPos; 
        m_refPlayer->setPlayerPosition(m_oSpCurrentPos);
        return false;
    }                                              

    //------------------------------------------------------------------------

    int currentdis = ccpDistance(m_oSpCurrentPos, m_oSpStartPos);
    //log("Dis:%d, currentDis:%d", dis,currentdis);  
     
    
    int postype = m_refShowArea->getPositionType(m_oSpCurrentPos);

    if (currentdis >= dis)
    {          
        m_oSpCurrentPos = CMath::getVec2(m_oSpStartPos,dis, CMath::angleToRadian(m_currentAngle));

        CUtil::formartGrid(m_oSpCurrentPos);

        m_oSpStartPos   = m_oSpCurrentPos; 
        m_oAbsStartPos  = m_oAbsEndPos;
        m_oGuideLStart  = m_oSpCurrentPos;
        m_oSpTarget     = m_oSpCurrentPos;
        
        m_refPlayer->setState(CGamePlayer::STATE_STANDER);
        m_refPlayer->setTarget(m_oSpCurrentPos);
        m_refPlayer->setPlayerPosition(m_oSpCurrentPos);

        return true;
    }
    return false;
}

/*********************************************************************/
/*
* @brief        精灵移动
* @param[in]    spPosition   输入坐标
* @param[out]   
* @return       void
*/
/*********************************************************************/
void CMySprite::playerMove(const Vec2& spPosition)
{                                                        
     switch (m_State)
    {
    case STATE_MOVE:
    case STATE_DRAW:
    case STATE_CLOSE:
        if (m_refPlayer->getStrackSize() < 1)
        {
            m_refPlayer->setTarget(spPosition);
        }
        break;
    case STATE_BACK:
        if (m_refPlayer->m_bFlow)
        {
            m_refPlayer->setPlayerPosition(spPosition);
        }
        else
        {
            int dis = ccpDistance(spPosition, m_refPlayer->getPlayerPosition());
            if (dis < m_fStep )
            {             
                m_refPlayer->m_bFlow = true;           
            }
        }

        break;
    } 
}


/*********************************************************************/
/*
* @brief        根据规则修正点轨迹
* @param[in]    inPos   输入坐标
* @param[out]   outPos  输出修正后的坐标
* @return       void
*/
/*********************************************************************/
void CMySprite::fixPosition(const Vec2& inPos, Vec2& outPos)
{                                                                        
    int distance = getAbsDistance();  
    //log("distance:%d, currentDirect:%d",distance, m_currentAngle);
    outPos = CMath::getVec2(m_oSpStartPos, distance, CMath::angleToRadian(m_currentAngle)); 
    CUtil::formartGrid(outPos);    
}



/*********************************************************************/
/*
* @brief        修正path
* @param[in]    
* @param[out]   
* @return       
*/
/*********************************************************************/
void CMySprite::fixPath(const Vec2& inPoint)
{                               
    if (m_oTPath.size() < 2)
    {
        return;
    }
    //是否与路径尾节点重合

    int lastIndex   = m_oTPath.size() - 1;
    Vec2 lasNode    = m_oTPath[lastIndex];

    if (m_oSpCurrentPos == lasNode)
    {
        m_oSpStartPos   = m_oSpCurrentPos;

        m_oAbsStartPos  = inPoint;
        m_oAbsEndPos    = m_oAbsStartPos;
        
        m_oDirectStart  = inPoint;

        m_currentAngle  = CMath::radianToAngle(RADINA_TOGAME(CMath::getRadian(m_oTPath[lastIndex -1], m_oSpCurrentPos)));
        //m_oSpStartPos = m_oTPath[lastIndex - 1];
        
        //fixPosition(inPoint, m_oSpCurrentPos);

       // log("m_currentAngle:%d---------%f, %f", m_currentAngle, m_oSpCurrentPos.x, m_oSpCurrentPos.y);
        
        
        m_refPath->m_oAllPoint.erase(m_refPath->m_oAllPoint.end() - 1);       
        m_oTPath.erase(m_oTPath.end() - 1);
        m_refPlayer->backFollow();           
    }
    

}


/*********************************************************************/
/*
* @brief        设置玩家运动轨迹
* @param[in]
* @param[out]
* @return
*/
/*********************************************************************/
void CMySprite::playerGoWay()
{
    if (m_refPlayer->getPlayerPosition() != m_oSpCurrentPos && m_oTPathMargin.size() > 0)
    {    

        Vec2 t_oSp(Vec2::ZERO);
        Vec2 t_oEp(Vec2::ZERO);

        if (m_oTPathMargin.size() > 0)
        {
            t_oSp = m_oTPathMargin[m_oTPathMargin.size() - 1]->m_oStart;
        }
        else if (m_oTRoad.size() > 0)
        {
            t_oSp = m_oTRoad[m_oTRoad.size() - 1];
        }

        int t_iDis = CUtil::getFixDictance(m_refPlayer->m_iCurrentDirect,t_oSp, m_refPlayer->getPlayerPosition());

        t_oEp = CMath::getVec2(t_oSp, t_iDis, CMath::angleToRadian(m_refPlayer->m_iCurrentDirect));

        CUtil::formartGrid(t_oEp ,m_refPlayer->getStep());
        m_oTPathMargin[m_oTPathMargin.size() - 1]->m_oTaget = t_oEp;
        
//         Vec2 tp = m_RefPlayer->getPlsyerPosition(); 
//         Vec2 tsp = m_oTPathMargin[0]->m_oStart;
//         
//         m_oTPathMargin[0]->m_Angle = m_RefPlayer->m_iCurrentDirect;   
// 
// 
//         int dis = static_cast<int>(ccpDistance(tsp, tp));
//        
//         
//         m_oTPathMargin[0]->m_oTaget = CMath::getVec2(tsp, dis, CMath::angleToRadian(m_RefPlayer->m_iCurrentDirect));
// 
//         CUtil::formartGrid(m_oTPathMargin[0]->m_oTaget);

        //CUtil::formartGrid(tp, m_RefPlayer->getStep());

        //log("current Target :", m_RefPlayer->m_iCurrentDirect);
        //m_oTPathMargin[0]->setTaget(m_oTPathMargin[0]->m_oStart,tp);
       // m_oTPathMargin[0]->m_oTaget = m_oSpCurrentPos;
    }

}

/*********************************************************************/
/*
* @brief        检查方向,改变方向时改变 成员 当前角度值 m_currentAngle
* @param[in]    inPos   输入坐标
* @param[out]   
* @return       void
*/
/*********************************************************************/
void CMySprite::checkDirect(const Vec2& inPos)
{
	if (m_iCountRecord++ > 3)
	{     
        float radian	= RADINA_TOGAME(CMath::getRadian(m_oDirectStart, inPos));
		int angle		= CMath::radianToAngle(radian);
        int fixangle    = CUtil::getFixDirect(m_currentAngle,angle);

        if (m_currentAngle == ANGLE_NONE)
        {
            Vec2 toNp = CMath::getVec2(m_oSpStartPos, GRAD_CELL, CMath::angleToRadian(fixangle));

            int tPostiontype = m_refShowArea->getPositionType(toNp);

            log("Start next Postion:%d",  tPostiontype);
            switch(tPostiontype)
            {
            case POSITION_BORDER_LINE:                
                return;
            }        
        }                                

		if (m_currentAngle == ANGLE_NONE || m_currentAngle != fixangle)
		{  
			changeDirect(inPos, fixangle);	
			m_currentAngle = fixangle;
			return;
		}	

		setDirectStartPosition(inPos);
		m_iCountRecord = 0;          
	}                      

    m_oAbsEndPos = inPos;       
}



/*********************************************************************/
/*
* @brief        改变方向时调用  
                影响成员 
                m_oAbsStartPos,
                m_oAbsEndPos,
                m_oSpStartPos

* @param[in]    inPos       输入坐标
                fixangle    修正后的方向值
* @param[out]
* @return       void
*/
/*********************************************************************/
void CMySprite::changeDirect(const Vec2& inPos,int fixangle)
{
	log("Current Angle: %d, fixAngle:%d", m_currentAngle, fixangle);	

	//log("angle :%d , fixangle:%d" , angle, fixangle);
	//
	//---------------------------------------------   
    
     if (!hasRevceDircet(m_currentAngle, fixangle)&& getState() == STATE_DRAW)
     {
        addGuide(m_oSpCurrentPos); 
     }                                
	

    //迭代关系
	if (m_currentAngle != ANGLE_NONE)
	{
		m_oAbsStartPos  = inPos;
		m_oAbsEndPos    = m_oAbsStartPos;  

        //-----------------------------------------
        m_oSpStartPos   = m_oSpCurrentPos;       
        
	}           

}


/*********************************************************************/
/*
* @brief        判断是否相向运动
* @param[in]    direct      当前方向
                fixangle    转向方向
* @param[out]
* @return       true 相向方向， false
*/
/*********************************************************************/
bool CMySprite::hasRevceDircet(int direct, int fixangle)
{
    //log("%d", (direct == ANGLE_UP) && (fixangle == ANGLE_DOWN));
    
    if ((direct == ANGLE_LEFT) && (fixangle == ANGLE_RIGHT))
    {
        return true;
    }
    else if ((direct == ANGLE_RIGHT) && (fixangle == ANGLE_LEFT))
    {
        return true;
    }else if ((direct == ANGLE_UP) && (fixangle == ANGLE_DOWN))
    {
        return true;
    }else if ((direct == ANGLE_DOWN) && (fixangle == ANGLE_UP))
    {
        return true;
    }

    return false; 
}

/*********************************************************************/
/*
* @brief        得到距离
* @param[in]    

* @param[out]
* @return       距离值
*/
/*********************************************************************/
int CMySprite::getAbsDistance()
{
	//根据方向得到 距离

	if (m_currentAngle == ANGLE_NONE || m_currentAngle == ANGLE_ERROR)
	{
		return 0;
	}               
	int distance = 0; 

	if (ANGLE_UP == abs(m_currentAngle))
	{
		//log("up down");        
		distance = static_cast<int>(abs(m_oAbsStartPos.y - m_oAbsEndPos.y)); 
	}else{
		//log("right left");
		distance = static_cast<int>(abs(m_oAbsStartPos.x - m_oAbsEndPos.x)); 
	}
    return distance;
}

/*********************************************************************/
/**
* @brief        渲染通道
* @param[in]    dn  渲染节点
* @param[out]   
* @return       void
*/
/*********************************************************************/
void CMySprite::print(DrawNode* dn)
{                                       
    dn->drawDot(this->m_oSpCurrentPos, 10, Color4F(1, 0, 0, 0.5));

    for (int i = 0; i < m_oTPath.size();i++)
    {            
        if (i + 1 < m_oTPath.size())
        {
            dn->drawSegment(m_oTPath[i], m_oTPath[i + 1], 0.51, Color4F(1, .3, .3, 0.31));
        }
        else
        {
            dn->drawSegment(m_oTPath[i], m_oSpCurrentPos, 0.51, Color4F(1, .3, .3,0.31));
        }   

        //dn->drawDot(m_oTPath[i], 1, Color4F(0, 1, 1, 1));  
    }
         
    if (m_State != STATE_BACK)
    {
        for (int i = 0; i < m_oTPathMargin.size();i++)
        {
            dn->drawSegment(m_oTPathMargin[i]->m_oStart, m_oTPathMargin[i]->m_oTaget, 1, Color4F(1, .3, .3, 1));
        } 
    }

// 
//     if (m_oTPathMargin.size() > 0)
//     {                                            
//        
//         Vec2 t_oSp = m_oTPathMargin[m_oTPathMargin.size() - 1]->m_oStart;
// 
//         Vec2 tt = m_RefPlayer->getPlsyerPosition();
//         CUtil::formartGrid(tt, m_RefPlayer->getStep());
//         //log("%f , %f -- %d", tt.x, tt.y, m_RefPlayer->m_iCurrentDirect);
// 
//         int t_iDis = FTOI(ccpDistance(t_oSp, tt));
//         Vec2 t_oEp = CMath::getVec2(t_oSp, t_iDis, CMath::angleToRadian(m_RefPlayer->m_iCurrentDirect));
//         
//         CUtil::formartGrid(t_oEp , m_RefPlayer->getStep());
//         dn->drawSegment(t_oSp, t_oEp, 1, Color4F(1, 1, 1, 1));
//         dn->drawDot(t_oSp, 5, Color4F(1, 1, 1, 1));
//     }
//     else if (m_oTRoad.size() > 0)
//     {
//         
//        
//        Vec2 t_oSp = m_oTRoad[m_oTRoad.size() - 1];
// 
// 
//         int t_iDis = FTOI(ccpDistance(t_oSp, m_RefPlayer->getPlsyerPosition()));
//         Vec2 t_oEp = CMath::getVec2(t_oSp, t_iDis, CMath::angleToRadian(m_RefPlayer->m_iCurrentDirect));
//        
// 
//         dn->drawSegment(t_oSp, t_oEp, 1, Color4F(1, 1, 1, 1));
//         dn->drawDot(t_oSp, 5, Color4F(1, 1, 1, 1));
//     }
 
    

    //可行走方向------------------------------------------
//     std::vector<int> abv;
//     switch (getState())
//     {
//     case STATE_MOVE:
//         m_RefShowArea->getAreaMoveAvable(m_oSpCurrentPos, abv);
//         break;
//     case STATE_DRAW:
//         m_RefPath->getMoveAble(m_currentAngle, m_oSpCurrentPos, abv);
//         break;
//     } 
// 
//     for (int i = 0; i < abv.size();i++)
//     {
//         Vec2 endp = CMath::getVec2(m_oSpCurrentPos, 120, CMath::angleToRadian(abv[i]));
// 
//         dn->drawSegment(m_oSpCurrentPos, endp, 1, Color4F(0, .3, .3, 1));
//         
//     }
        
    //手势系统
    switch (m_State)
    {                 
	case STATE_MOVE:
    case STATE_DRAW:
		dn->drawSegment(m_oAbsStartPos, m_oAbsEndPos, 1, Color4F(0, 1, 1, 1));
		dn->drawDot(m_oDirectStart, 10, Color4F(.03,0,1,1));
        dn->drawDot(m_oSpStartPos, 20, Color4F(1, 0, 0, .3));
		break;
    }    
}


/*********************************************************************/
/**
* @brief        添加节点给各分支
* @param[in]
* @param[out]
* @return       void
*/
/*********************************************************************/
void CMySprite::addGuide(const Vec2& point)
{                            
    //同一个点不添加            
    for (int i = 0; i < m_oTPath.size();i++)
    {
        if (m_oTPath[i] == point)
        {
            log("reover!");
            return;
        }
    }
    //同一条直线上不添加  

    m_oSpStartPos = point;     
    if (m_oTPath.size() == 0)
    {
        addRoad(point);
    } 
              
    //---------------------------
    //log("+++++addGuid:%f ,%f", point.x ,point.y);

    m_oTPath.push_back(point);
    m_refPath->addPoint(point);

    //----------------------------  

    if (m_State == STATE_DRAW)
    {
        m_refPlayer->addFollow(point);
    }
}


/*********************************************************************/
/**
* @brief        添加行走过路径节点
* @param[in]
* @param[out]
* @return       void
*/
/*********************************************************************/
void CMySprite::addRoad(const Vec2& inPoint)
{      
    log("addRoad Direct:%d",m_currentAngle);


    CMargin* tpathmargin = new CMargin();
    if (m_oTRoad.size() > 0)
    {              
        const Vec2& lastVec2 = m_oTRoad[m_oTRoad.size() - 1];
        tpathmargin->setTaget(lastVec2, inPoint);
        m_oTPathMargin.push_back(tpathmargin); 

        m_oTPathMargin[m_oTPathMargin.size() - 1]->m_oStart = inPoint;
    }
    else if (m_oTRoad.size() == 0)
    {
        tpathmargin->setTaget(inPoint, inPoint);
        m_oTPathMargin.push_back(tpathmargin);
    }

    m_oTRoad.push_back(inPoint);

 
//     CMargin* tpathmargin = new CMargin();
//     if (m_oTRoad.size() == 0)
//     {
//         tpathmargin->setTaget(inPoint, inPoint);
//         m_oTPathMargin.push_back(tpathmargin);
//     }
//     else if (m_oTRoad.size() > 0)
//     {
//         const Vec2& lastVec2 = m_oTRoad[m_oTRoad.size() - 1];
//        
//         tpathmargin->setTaget(lastVec2, inPoint);
//         m_oTPathMargin.push_back(tpathmargin);
// 
//         m_oTPathMargin[0]->m_oStart = inPoint;
//     }

   // m_oTRoad.push_back(inPoint);                                  
}



/*********************************************************************/
/**
* @brief        清除导线
* @param[in]
* @param[out]
* @return       void
*/
/*********************************************************************/
void CMySprite::clearGuide()
{
    log("guide clear");
    m_oTPath.clear();
    m_oTRoad.clear();
    m_refPath->clearPoint();

    
    clearRoad();
}


inline
void CMySprite::clearRoad()
{
    log("clearRoad");
    for (int i = 0; i < m_oTPathMargin.size(); i++)
    {
        delete m_oTPathMargin[i];
    }
    m_oTPathMargin.clear();
}

/*********************************************************************/
/**
* @brief        原路返回
* @param[in]    
* @param[out]
* @return       void
*/
/*********************************************************************/
void CMySprite::checkBack()
{                                 
    if (m_oTPath.size() == 0)
    {
        log("Back complete!");

        //adsorption(m_oSpCurrentPos, m_oSpCurrentPos);
        m_refPlayer->setPlayerPosition(m_oSpCurrentPos);
        m_refPlayer->m_bFlow = false;

        clearGuide(); 
        setState(STATE_STANDER);      
    }
	else
	{
        int lastIndex   = m_oTPath.size() - 1;
        m_oSpTarget     = m_oTPath[lastIndex];

        float radina    = RADINA_TOGAME(CMath::getRadian(m_oSpCurrentPos, m_oSpTarget));
        m_currentAngle  = CMath::radianToAngle(radina);       
    }   
}


void CMySprite::run(float tm)
{
    getArmature()->setPosition(m_oSpCurrentPos);
    //log("mysprite run");
    switch (m_State)
    {
    case STATE_INIT:
        break;
    case STATE_BACK:
        runback();
        break;
    case STATE_CLOSE:
        playerGoWay();
        runGo();
        break;
    case STATE_STANDER:        
        break;
    case STATE_DRAW: 
        
        playerGoWay();
       m_refPlayer->checkPosition(m_oSpCurrentPos);
        break;
    case STATE_MOVE:       
        break;
    default:
        break;
    } 
}
                    

void CMySprite::runback()
{
    int distance = ccpDistance(m_oSpCurrentPos, m_oSpTarget);

    if (distance <= m_fStep)
    {
        if (m_oTPath.size() > 0)
        {
            std::vector<Vec2>::iterator it = m_oTPath.end() - 1;

            m_oSpCurrentPos = *it; 
            m_oTPath.erase(it);
        }                 
        log("next");
        checkBack();
        return;
    }

    m_oSpCurrentPos = CMath::getVec2(m_oSpCurrentPos, m_fStep, CMath::angleToRadian(m_currentAngle));

    //m_RefPlayer->setPlayerPosition(m_oSpCurrentPos);
    playerMove(m_oSpCurrentPos);
}




void CMySprite::runGo()
{
    if (m_refPlayer != nullptr && m_refPlayer->getState() == CGamePlayer::STATE_STOP)
    {                                          
        //m_RefShowArea->setState(CShowArea::STATE_CLOSE);

        CEventDispatcher::getInstrance()->dispatchEvent(EVENT_CLOSE, PARM_NULL);
        setState(STATE_STANDER);
//         float area = m_RefShowArea->getArea();
//         log(" Area :%f", area);     
// 
//         if (area > WINPART)
//         {
//             //release  
//             m_RefGameView->setState(CGameView::STATE_WIN);
//         }
//         else
//         {                       
//             setState(STATE_STANDER);
//         }     
    } 
} 
  
/*********************************************************************/
/**
* @brief        得到点在导线上的距离
* @param[in]
* @param[out]
* @return       void
*/
/*********************************************************************/
int CMySprite::getPathDis(const Vec2& inPoint, int direct)
{         

    Size visSize = Director::getInstance()->getVisibleSize();
    Vec2 visVec = Director::getInstance()->getVisibleOrigin();

   Vec2 tve(Vec2::ZERO);
    switch (direct)
    {
    case ANGLE_DOWN:
        tve.x = inPoint.x;
        // tve.y = visVec.y;
        break;
    case ANGLE_LEFT:
        //tve.x = visVec.x;
        tve.y = inPoint.y;
        break;
    case ANGLE_RIGHT:
        tve.x = visSize.width + visVec.x;
        tve.y = inPoint.y;
        break;
    case ANGLE_UP:
        tve.x = inPoint.x + visVec.x;
        tve.y = visSize.height + visVec.y;
        break;
    default:
        break;
    }

    int mindis = -1;

    for (int i = 0; i < m_oTPathMargin.size(); i++)
    {
        CMargin* maring = m_oTPathMargin[i];

        if (liyan998::CMath::hasLineMutlLine(maring->m_oStart, maring->m_oTaget, inPoint, tve))
        {      
            Vec2 zu = CMath::getFootPoint(maring->m_oStart, maring->m_oTaget, inPoint);

            int dis = static_cast<int>(ccpDistance(inPoint, zu)); 

            if (mindis == -1 || dis < mindis)
            {
                mindis = dis;
            }
        }
    }
    return mindis;
                     
}

void CMySprite::released()
{   
    CEventDispatcher::getInstrance()->unRegsiterEvent(EVENT_PROPERTY_ADDHEALTH, this);

    m_refPlayer     = nullptr;
    m_refPath       = nullptr;
    m_refShowArea   = nullptr;

    removeAllChildrenWithCleanup(true);
}

bool CMySprite::attiack(int value, CEnemy* pEnemy)
{
    if (m_refPlayer->getState() == CGamePlayer::STATE_DIE)
    {
        return false;
    }


    if (m_iHealth - value <= 0)
    {
        m_iHealth = 0;
        m_refPlayer->setState(CGamePlayer::STATE_DIE);
        //CEventDispatcher::getInstrance()->dispatchEvent(EVENT_PLAYERDIE, PARM_NULL);
        return false;
    }    
 
    if (m_refPlayer->hasInProtected())
    {
        switch (pEnemy->m_iCategory)
        {
        case CEnemy::CATEGORY_BOSS:
            log("Boss is attack protect player");
            //setState(CMySprite::STATE_BACK);
            setCollPlayer();
            break;
        case CEnemy::CATEGORY_NPC:
            log("npc is attack protect player");
            pEnemy->setState(CNpc::STATE_DIE);           
            break;
        }
        m_refPlayer->setProtectReleased();
    }
    else
    {
        m_iHealth -= value;
        log("attack! %d", m_iHealth);
        //setState(CMySprite::STATE_BACK);
        setCollPlayer();
    }
               
    m_refPlayer->animation_attack();

    CEventDispatcher::getInstrance()->dispatchEvent(EVENT_HIT, new CEnemy*(pEnemy));
    return true;
}


void CMySprite::setCollPlayer()
{
    //clearRoad();
    if (m_oTPath.size() > 0)
    {
        m_oSpCurrentPos = m_oTPath[0];
        setPlayerPosition(m_oSpCurrentPos);
    }

    m_refPlayer->setState(CGamePlayer::STATE_STOP);

    clearGuide();  

    setState(STATE_STANDER);
}


bool CMySprite::hasSkillLightCountTime()
{
    switch (m_State)
    {
    case STATE_DRAW:
    case STATE_CLOSE:
    case STATE_BACK:
        return false;
    case STATE_STANDER:
    case STATE_MOVE:
        default:
        return true;
    }
}