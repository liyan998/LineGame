
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
                       CMargin* margin  = m_RefShowArea->getMargin(setLine);
                       m_curMarginIndex = setLine;                                              
                       float dis        = ccpDistance(margin->m_oStart, margin->m_oTaget);
                       int ranint       = CMath::getRandom(0, dis);
                       const Vec2& ps   = CMath::getVec2(margin->m_oStart, ranint, CMath::angleToRadian(margin->m_Angle)); 

                       setState(STATE_STANDER);
                       setPlayerPosition(ps);
                       log("!!!!!%f , %f", ps.x, ps.y);

    }
        break;
    case STATE_STANDER:
        //m_currentAngle = ANGLE_NONE;
        //clearGuide();
        this->unschedule(schedule_selector(CMySprite::run));       
        log("mysprite state STATE_STANDER");
        break;
    case STATE_MOVE:     
        this->unschedule(schedule_selector(CMySprite::run));
        m_currentAngle = ANGLE_NONE;
        
        log("mysprite state STATE_MOVE");
        setSpStartPosition();       
        break;            
    case STATE_BACK:
        log("mysprite state STATE_BACK");
        //m_currentAngle = ANGLE_NONE;
       // clearGuide();  
        m_RefPlayer->setState(CGamePlayer::STATE_STOP);
        schedule(schedule_selector(CMySprite::run));
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
        schedule(schedule_selector(CMySprite::run));

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

    switch (m_State)
    {
    case STATE_INIT:
        break;
    case STATE_BACK:
        break;
    case STATE_CLOSE:
        break;
    case STATE_STANDER: 
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
    checkDirect(point);
    m_oAbsEndPos = point;
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
        
        fixPosition(point, m_oSpCurrentPos);
        if (m_RefShowArea->hasPointInArea(m_oSpCurrentPos))
        {                                                                
            int index = m_RefShowArea->getNearMargin(m_oSpCurrentPos);
                
            if (index == SELECTID_NULL)
            {
                return;
            }      

            CMargin* margin = m_RefShowArea->getMargin(index);
            Vec2 endp = CMath::getFootPoint(margin->m_oStart, margin->m_oTaget, m_oSpCurrentPos);

//             log("close  %f,%f | %f,%f ||  %f,%f",
//                 margin->m_oStart.x,
//                 margin->m_oStart.y,
//                 margin->m_oTaget.x,
//                 margin->m_oTaget.y,
//                 m_oSpCurrentPos.x,
//                 m_oSpCurrentPos.y
//                 );

            addGuide(endp);

            m_RefShowArea->setAreaIndex(1, index);
            setState(STATE_CLOSE);
        }
        playerMove(m_oSpCurrentPos);
        break;
    case STATE_MOVE:              
        //得到可行走方向               
        onMoveToDraw(point);
        //TODO可行走范围约束    
        //log("currentdirect:%d", m_currentAngle); 
        fixPosition(point, m_oSpCurrentPos);
        //-----------------------------------  
        //---------------------------------   
        playerMove(m_oSpCurrentPos);      
        //---------------------------------------- 1
        break;
    default:
        break;
    }       
}



void CMySprite::onStander(const Vec2& inPoint)
{
    int selectindex = m_RefShowArea->getTargetIndex(inPoint);
    if (selectindex != SELECTID_NULL)
    {
        m_curMarginIndex = selectindex;

        log("location position %d", selectindex);

        CMargin* tMargin = m_RefShowArea->getMargin(selectindex);
        Vec2 refp = CMath::getFootPoint(tMargin->m_oStart, tMargin->m_oTaget, inPoint);
        CMath::getIntPoint(refp);

        setPlayerPosition(refp);  
    }
    else
    {                       
        //
        setState(STATE_MOVE);
        setDirectStartPosition(inPoint);

        m_oAbsStartPos = inPoint;
        m_oAbsEndPos = m_oAbsStartPos;
    }

}

void CMySprite::onMoveToDraw(const Vec2& inPoint)
{  
    if (m_curMarginIndex == SELECTID_NULL)
    {
        return;
    }                                

    CMargin* margin = m_RefShowArea->getMargin(m_curMarginIndex);

    if (CUtil::hasPointInLine(margin->m_oStart, margin->m_oTaget, m_oSpCurrentPos))
    {
        //log("true  %f,%f | %f,%f ||  %f,%f",
//             margin->m_oStart.x,
//             margin->m_oStart.y,
//             margin->m_oTaget.x,
//             margin->m_oTaget.y,
//             m_oSpCurrentPos.x,
//             m_oSpCurrentPos.y
//             );
        m_RefPlayer->setPlayerPosition(m_oSpCurrentPos);
    }
    else
    {
        //draw
        float dis = CUtil::getDisPointLine(margin->m_oStart, margin->m_oTaget, m_oSpCurrentPos);
        Vec2 startpoint = m_oSpCurrentPos;
        if (dis > 0)
        {
            startpoint = CMath::getFootPoint(margin->m_oStart, margin->m_oTaget, m_oSpCurrentPos);          
        }

        log("AreaIndex:%d", m_curMarginIndex);
        addGuide(startpoint);
        m_RefShowArea->setAreaIndex(0, m_curMarginIndex);  
        
        setState(STATE_DRAW);
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
	  
    
    //else if 距离 > mstep

        //setTarget



                                                             
    //log("distance:%d , size:%d", distance, m_oTPath.size()); 
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
    //log("angle:%d , distance:%d", m_currentAngle, distance);
    outPos = CMath::getVec2(m_oSpStartPos, distance, CMath::angleToRadian(m_currentAngle)); 
    CMath::getIntPoint(outPos);
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
		//
		float radian	= RADINA_TOGAME(CMath::getRadian(m_oDirectStart, inPos));
		int angle		= CMath::radianToAngle(radian);
		int fixangle	= getFixAngle(angle); 

		if (m_currentAngle == ANGLE_NONE || m_currentAngle != fixangle)
		{
			changeDirect(inPos, fixangle);	
			m_currentAngle = fixangle;
			return;
		}	

		setDirectStartPosition(inPos);
		m_iCountRecord = 0;
	}
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
	    //m_RefPath->addPoint(pos);        //    路径
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
            dn->drawSegment(m_oTPath[i], m_oTPath[i + 1], 4, Color4F(1, .3, .3, 1));
        }
        else
        {
            dn->drawSegment(m_oTPath[i], m_oSpCurrentPos, 4, Color4F(1, .3, .3, 1));
        }    
        dn->drawDot(m_oTPath[i], 10, Color4F(0, 1, 1, 1));  
    }               
        
    switch (m_State)
    {                 
	case STATE_MOVE:

		dn->drawDot(m_oDirectStart, 3, Color4F(.03,0,1,1));
		dn->drawSegment(m_oAbsStartPos, m_oAbsEndPos, 1, Color4F(0, 1, 1, 1));

		break;
    }    
}






void CMySprite::addGuide(const Vec2& point)
{
    log("add guide line %f ,%f",point.x, point.y);
    m_oTPath.push_back(point);
    m_RefPath->m_oAllPoint.push_back(point);

	m_RefPlayer->addFollow(point);   
}


void CMySprite::clearGuide()
{
    log("guide clear");
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

        adsorption(m_oSpCurrentPos, m_oSpCurrentPos);

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


void CMySprite::checkGo()
{

   

}


void CMySprite::runGo()
{
    if (m_RefPlayer->getState() == CGamePlayer::STATE_STANDER)
    {
        m_RefShowArea->setState(CShowArea::STATE_CLOSE);
        clearGuide();
        setState(STATE_STANDER);
    } 
}




void CMySprite::adsorption(const Vec2& inpoint, Vec2& outPoint)
{       
    int selectindex = m_RefShowArea->getTargetIndex(inpoint);

    if (selectindex == SELECTID_NULL)
    {
        return;
    }  
    //是否在直线上

    CMargin* margin = m_RefShowArea->getMargin(selectindex);
    
    float dis = CMath::getPointToLineDis(margin->m_oStart, margin->m_oTaget, inpoint);

    //log("diis : %f", dis);
    if (dis == 0 && !CUtil::hasPointInLine(margin->m_oStart, margin->m_oTaget, inpoint))
    {           
        float dis1 = ccpDistance(margin->m_oStart, inpoint);
        float dis2 = ccpDistance(margin->m_oTaget, inpoint);

        if (dis1 > dis2)
        {
            outPoint = margin->m_oTaget;
        }
        else
		{
            outPoint = margin->m_oStart;
        }       
    }
    else
    {
        outPoint = CMath::getFootPoint(margin->m_oStart, margin->m_oTaget, inpoint);
        CMath::getIntPoint(outPoint);   
    }

}
