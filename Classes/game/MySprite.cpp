
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
#include "ShowArea.h"
#include "GameView.h"

using namespace liyan998;

bool CMySprite::init()
{
    Sprite::init();

    m_currentAngle      = ANGLE_NONE;
    m_fStep				= 6.f;
    m_iCountRecord      = 0;
    m_curMarginIndex    = SELECTID_NULL; 

  
    //----------------------------------------------------- 


    //----------------------------------------------------

//     DrawNode* pDn = DrawNode::create();	
//     addChild(pDn);                                      
//     pDn->drawDot(Vec2::ZERO, 20, Color4F(1, 0, 0, 0.5));       
//     this->setAnchorPoint(Vec2::ZERO);
//     this->setContentSize(Size(40,40));

    //---------------------------------------------------

    //Rect& rec = this->getBoundingBox();     
    //log("bundBox:%f, %f, %f, %f", rec.origin.x, rec.origin.y, rec.size.width , rec.size.height);     

    return true;
}

                


/************************************************************************/
/*
@brief        得到修正角度值，修正范围 

@param[in]     angle   向量方向角度值
@param[out]

@return        修正角度值

                ANGLE_DOWN
                ANGLE_RIGHT
                ANGLE_UP
                ANGLE_LEFT
*/
/************************************************************************/
int CMySprite::getFixAngle(int angle)
{
	int errorMarign = 45;

	int angleList[] = { 90, 0 , -90, 180 ,270 };

	int size = sizeof(angleList) / sizeof(angleList[0]);
	for (int i = 0;i < size;i++)
	{
		if (angleList[i] == angle)
		{
			return angle;
		}else if(abs(angle - angleList[i]) < errorMarign)
		{
            if (angleList[i] == 270)
            {
                return -90;
            }
			return angleList[i];
		}
	}
    switch (m_currentAngle)
    {
    case ANGLE_DOWN:       
        if (angle >= ANGLE_DOWN + errorMarign && angle <= ANGLE_RIGHT - errorMarign)
        {
            //->down | right
            log("down | right");
            return ANGLE_RIGHT;
        }
        else if (angle >= ANGLE_LEFT - errorMarign && angle <= ANGLE_LEFT * 2 - errorMarign)
        {
            //->down | left
            log("down | left");
            return ANGLE_LEFT;
        }
        break;
    case ANGLE_UP:
        if (angle >= ANGLE_RIGHT + errorMarign && angle <= ANGLE_UP - errorMarign)
        {
            //-> up | right
            log("up | right");
            return ANGLE_RIGHT;
        }
        else if (angle >= ANGLE_UP + errorMarign && angle <= ANGLE_LEFT - errorMarign)
        {
            //-> up | left
            log("up | left");
            return ANGLE_LEFT;
        }
        break;
    case ANGLE_LEFT:
        if (angle >= ANGLE_LEFT + errorMarign && angle <= ANGLE_LEFT + 90 - errorMarign)
        {
            //->left | down
            log("left | down");
            return ANGLE_DOWN;
        }
        else if (angle >= ANGLE_UP + errorMarign && angle <= ANGLE_LEFT - errorMarign)
        {
            //->left | up
            log("left | up");
            return ANGLE_UP;
        }
        break;
    case ANGLE_RIGHT:
        if (angle >= ANGLE_DOWN + errorMarign && angle <= ANGLE_RIGHT - errorMarign)
        {
            //-> right | down
            log("right | down");
            return ANGLE_DOWN;
        }
        else if (angle >= ANGLE_RIGHT + errorMarign && angle <= ANGLE_UP - errorMarign)
        {
            //-> right | up
            log("right | up");
            return ANGLE_UP;
        }
        break;
    }
    return ANGLE_ERROR;
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
    this->m_State = state;   
    switch (state)
    {        
    case STATE_INIT:
    {                                                        
                       int setLine      = 0;     
                       CMargin* margin  = m_RefShowArea->getAreaMargin(setLine);
                       m_curMarginIndex = setLine;                                              
                       float dis        = ccpDistance(margin->m_oStart, margin->m_oTaget);
                       int ranint       = CMath::getRandom(0, dis);
                       const Vec2& ps   = CMath::getVec2(margin->m_oStart, ranint, CMath::angleToRadian(margin->m_Angle)); 

//                        ps.x = GRAD_NUMBER(ps.x);
//                        ps.y = GRAD_NUMBER(ps.y);
                       setState(STATE_STANDER);
                       setPlayerPosition(Vec2(GRAD_NUMBER(ps.x), GRAD_NUMBER(ps.y)));
                       log("!!!!!%f , %f", ps.x, ps.y);

    }
        break;
    case STATE_STANDER:
        //m_currentAngle = ANGLE_NONE;
        //clearGuide();
        clearGuide();
        //this->unschedule(schedule_selector(CMySprite::run));       
        log("mysprite state STATE_STANDER");
        //m_RefPlayer->setPlayerPosition(m_oSpCurrentPos);
        //log("current type:%d", m_RefShowArea->getPositionType(m_oSpCurrentPos));
        break;
    case STATE_MOVE:     
        //this->unschedule(schedule_selector(CMySprite::run));
        m_currentAngle = ANGLE_NONE;
        
        log("mysprite state STATE_MOVE");
        setSpStartPosition();       
        break;            
    case STATE_BACK:
        log("mysprite state STATE_BACK");
        //m_currentAngle = ANGLE_NONE;
       // clearGuide();  
        m_RefPlayer->setState(CGamePlayer::STATE_STOP);
        //schedule(schedule_selector(CMySprite::run));
        checkBack();
        break;
    case STATE_CLOSE:      
        log("mysprite state STATE_CLOSE");


        //m_RefShowArea->setState(CShowArea::STATE_CLOSE); 
        //clearGuide();                 
        //setState(STATE_STANDER); 
        break;
    case STATE_DRAW:
        log("mysprite state STATE_DRAW");
        //schedule(schedule_selector(CMySprite::run));

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
        break;
    case STATE_CLOSE:
        break;
    case STATE_STANDER: 

        if (m_RefShowArea != nullptr)
        {
            m_RefShowArea->resultArea.clear();
            m_RefShowArea->addArea.clear();
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
            log("draw _ inBorder~~~~~~");
            return;
        }
        if (!hasMoveAction())
        {
            log("don't move it");
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
            log("don't move it");
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
* @brief        屏幕指针释放
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
       m_RefShowArea->getAreaMoveAvable(m_oSpCurrentPos, abv);               
        break;
    case STATE_DRAW:
       m_RefPath->getMoveAble(m_currentAngle, m_oSpCurrentPos, abv);
        break;        
    }     




//     
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

    int dis = m_RefShowArea->getBorderDis(m_oSpStartPos, m_currentAngle); 
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

        m_RefPlayer->fixTargetPostion(m_oSpCurrentPos, stopVec2);
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
    fixPosition(inPoint, m_oSpCurrentPos); 
    if (m_oSpStartPos != m_oSpCurrentPos)
    {
        fixPath(inPoint);
    }

    int index = SELECTID_NULL;


    //-----------------------------------------------------------       
    //path over load
    if (m_RefPath->hasOverLoad(m_oSpStartPos, m_oSpCurrentPos, m_currentAngle))
    {
        //log("over load~~~~~~~~~~~~~~~~~~~~~");
        return;
    }


    //Area过界判断 
    if (m_RefShowArea->hasOverLoad(m_oSpStartPos, m_oSpCurrentPos, m_currentAngle, index))
    {
        log("over load in Area%d", index);
        if (m_RefPath->m_oAllPoint.size() > 0 && m_oSpCurrentPos == (*m_RefPath->m_oAllPoint.begin()))
        {
            log("start point == end point");
            m_RefPath->m_oAllPoint.clear();
            setState(STATE_BACK);
            return;
        } 


        addGuide(m_oSpCurrentPos);

        switch (m_RefShowArea->getPathType())
        {
        case POSITION_AREA_ENDPOINT + POSITION_AREA_ENDPOINT:
        case POSITION_AREA_LINE + POSITION_AREA_LINE:
        case POSITION_AREA_LINE + POSITION_AREA_ENDPOINT:
            m_RefShowArea->setAreaIndex(1, index);
            m_curMarginIndex = index;
            setState(STATE_CLOSE);
            return;
        }
    }
   



    int postiontype = m_RefShowArea->getPositionType(m_oSpCurrentPos);

    switch (postiontype)
    {
    case POSITION_AREA_ENDPOINT:       
    case POSITION_AREA_LINE:
        
        if (postiontype == POSITION_AREA_ENDPOINT)
        {
            addGuide(m_oSpCurrentPos); 
        }
        else
        {
            index = m_RefShowArea->getNearMargin(m_oSpCurrentPos);
            if (index == SELECTID_NULL)
            {
                m_RefPath->m_oAllPoint.clear();
                setState(STATE_BACK);
                return;
            }
            else if (m_RefPath->m_oAllPoint.size() > 0 && m_oSpCurrentPos == (*m_RefPath->m_oAllPoint.begin()))
            {
                log("start point == end point");
                m_RefPath->m_oAllPoint.clear();
                setState(STATE_BACK);
                return;
            }     

            addGuide(m_oSpCurrentPos);
            m_RefShowArea->setAreaIndex(1, index);
            m_curMarginIndex = index;           
        }                      
        setState(STATE_CLOSE);
        break;
    }


   
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
    int selectindex = m_RefShowArea->getTargetIndex(inPoint);
    if (selectindex != SELECTID_NULL)
    {
        m_curMarginIndex = selectindex;

        log("location position %d", selectindex);

        CMargin* tMargin = m_RefShowArea->getAreaMargin(selectindex);
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
       
    int posType = m_RefShowArea->getPositionType(m_oSpCurrentPos);
    
    switch (posType)
    {
    case POSITION_UNLOCK:
        log("POSITION_UNLOCK");                                                                       
        break;
    case POSITION_LOCK:
        log("POSITION_LOCK");
        {                           

            int startpostype = m_RefShowArea->getPositionType(m_oGuideLStart);
            //log("StartPositionType:%d", startpostype);                   
            if (startpostype == POSITION_AREA_LINE)
            {                                        
                int index = m_RefShowArea->getTargetIndex(m_oGuideLStart);
                m_RefShowArea->setAreaIndex(0, index);
            }

            addGuide(m_oGuideLStart);          
            setState(STATE_DRAW);
        }
        break;
    case POSITION_AREA_LINE:
    case POSITION_AREA_ENDPOINT:       
        log("POSITION_ENDPOINT + POSITION_LINE");
        //log("min %f, %f", m_oSpCurrentPos.x ,m_oSpCurrentPos.y);
        m_oGuideLStart = m_oSpCurrentPos;
        m_RefPlayer->setPlayerPosition(m_oSpCurrentPos);
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

    int dis = m_RefShowArea->getMiniAreaDis(m_oSpStartPos, m_currentAngle);
    if (dis == -1)
    {
        //
        m_oGuideLStart = m_oSpStartPos; 
        m_RefPlayer->setPlayerPosition(m_oSpCurrentPos);
        return false;
    }                                              

    //------------------------------------------------------------------------

    int currentdis = ccpDistance(m_oSpCurrentPos, m_oSpStartPos);
    //log("Dis:%d, currentDis:%d", dis,currentdis);  
     
    
    int postype = m_RefShowArea->getPositionType(m_oSpCurrentPos);

    if (currentdis >= dis)
    {          
        m_oSpCurrentPos = CMath::getVec2(m_oSpStartPos,dis, CMath::angleToRadian(m_currentAngle));

        CUtil::formartGrid(m_oSpCurrentPos);

        m_oSpStartPos   = m_oSpCurrentPos; 
        m_oAbsStartPos  = m_oAbsEndPos;
        m_oGuideLStart  = m_oSpCurrentPos;
        m_oSpTarget     = m_oSpCurrentPos;
        
        m_RefPlayer->setState(CGamePlayer::STATE_STANDER);
        m_RefPlayer->setTarget(m_oSpCurrentPos);
        m_RefPlayer->setPlayerPosition(m_oSpCurrentPos);

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
        if (m_RefPlayer->getStrackSize() < 1)
        {
            m_RefPlayer->setTarget(spPosition);
        }
        break;
    case STATE_BACK:

        int dis = ccpDistance(spPosition, m_RefPlayer->getPlsyerPosition());
        if (dis > m_fStep)
        {         
            //log("!!!!!!!!");
            return;
        }
        //log("ddddddddddd%d", dis);
        m_RefPlayer->setPlayerPosition(spPosition);

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

    int lastIndex = m_oTPath.size() - 1;
    Vec2 lasNode = m_oTPath[lastIndex];
    if (m_oSpCurrentPos == lasNode)
    {
        m_oSpStartPos   = m_oSpCurrentPos;

        m_oAbsStartPos  = inPoint;
        m_oAbsEndPos    = m_oAbsStartPos;
        
        m_oDirectStart  = inPoint;

        m_currentAngle = CMath::radianToAngle(RADINA_TOGAME(CMath::getRadian(m_oTPath[lastIndex -1], m_oSpCurrentPos)));
        //m_oSpStartPos = m_oTPath[lastIndex - 1];
        
        //fixPosition(inPoint, m_oSpCurrentPos);

       // log("m_currentAngle:%d---------%f, %f", m_currentAngle, m_oSpCurrentPos.x, m_oSpCurrentPos.y);
        
        
        m_RefPath->m_oAllPoint.erase(m_RefPath->m_oAllPoint.end() - 1);       
        m_oTPath.erase(m_oTPath.end() - 1);
        m_RefPlayer->backFollow();           
    }
    

}


/*********************************************************************/
/*
* @brief        退回上一个站点
* @param[in]
* @param[out]
* @return
*/
/*********************************************************************/
void CMySprite::backGuide()
{

    

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
		int fixangle	= getFixAngle(angle); 


        if (m_currentAngle == ANGLE_NONE)
        {
            Vec2 toNp = CMath::getVec2(m_oSpStartPos, GRAD_CELL, CMath::angleToRadian(fixangle));

            int tPostiontype = m_RefShowArea->getPositionType(toNp);

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
	 
//         Vec2 tVec2 = CMath::getVec2(m_oSpCurrentPos, GRAD_CELL, CMath::angleToRadian(fixangle));
// 
//         if (m_RefShowArea->getPositionType(tVec2) == POSITION_LINE)
//         {
//             return;
//         }   

        addGuide(m_oSpCurrentPos); 
//        m_oSpCurrentPos = tVec2;
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
            dn->drawSegment(m_oTPath[i], m_oTPath[i + 1], 4, Color4F(1, .3, .3, 1));
        }
        else
        {
            dn->drawSegment(m_oTPath[i], m_oSpCurrentPos, 4, Color4F(1, .3, .3, 1));
        }    
        dn->drawDot(m_oTPath[i], 10, Color4F(0, 1, 1, 1));  
    }            


    //可行走方向------------------------------------------
    std::vector<int> abv;
    switch (getState())
    {
    case STATE_MOVE:
        m_RefShowArea->getAreaMoveAvable(m_oSpCurrentPos, abv);
        break;
    case STATE_DRAW:
        m_RefPath->getMoveAble(m_currentAngle, m_oSpCurrentPos, abv);
        break;
    } 

    for (int i = 0; i < abv.size();i++)
    {
        Vec2 endp = CMath::getVec2(m_oSpCurrentPos, 120, CMath::angleToRadian(abv[i]));

        dn->drawSegment(m_oSpCurrentPos, endp, 1, Color4F(0, .3, .3, 1));
        
    }
        
    //手势系统
    switch (m_State)
    {                 
	case STATE_MOVE:
    case STATE_DRAW:
		dn->drawDot(m_oDirectStart, 10, Color4F(.03,0,1,1));
		dn->drawSegment(m_oAbsStartPos, m_oAbsEndPos, 1, Color4F(0, 1, 1, 1));
        dn->drawDot(m_oSpStartPos, 20, Color4F(1, 0, 0, .3));
		break;
    }    
}






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
                          
    log("+++++addGuid:%f ,%f", point.x ,point.y);
    m_oTPath.push_back(point);
    m_RefPath->m_oAllPoint.push_back(point);   

    if (m_State == STATE_DRAW)
    {
        m_RefPlayer->addFollow(point);
    }
}


void CMySprite::clearGuide()
{
    //log("guide clear");
    m_oTPath.clear();
    m_RefPath->clearPoint();
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
        m_RefPlayer->setPlayerPosition(m_oSpCurrentPos);

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
    //log("mysprite run");
    switch (m_State)
    {
    case STATE_INIT:
        break;
    case STATE_BACK:
        runback();
        break;
    case STATE_CLOSE:
        runGo();
        break;
    case STATE_STANDER:        
        break;
    case STATE_DRAW:         
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
    if (m_RefPlayer != nullptr && m_RefPlayer->getState() == CGamePlayer::STATE_STOP)
    {                                          
        m_RefShowArea->setState(CShowArea::STATE_CLOSE);
        float area = m_RefShowArea->getArea();
        log(" Area :%f", area);     

        if (area > WINPART)
        {
            //release  
            m_RefGameView->setState(CGameView::STATE_WIN);
        }
        else
        {                       
            setState(STATE_STANDER);
        }     
    } 
} 
           

void CMySprite::released()
{
    m_RefPlayer     = nullptr;
    m_RefPath       = nullptr;
    m_RefShowArea   = nullptr;
}