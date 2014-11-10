#include "MySprite.h"  
#include "util/Math.h"
#include "Margin.h"
#include "ShowArea.h"

using namespace liyan998;

bool CMySprite::init()
{
    Sprite::init();

    m_currentAngle      = ANGLE_NONE;
    m_fStep				= 2.f;
    m_iCountRecord      = 0;
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






void CMySprite::spriteMove()
{

}



//返回方向
//返回值范围
//90, 0 , -90, 180
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


void CMySprite::setPath(CPath* path)
{
	this->m_RefPath = path;
}


void CMySprite::setPlayer(CGamePlayer* sp)
{
    this->m_RefPlayer = sp;
}


void CMySprite::setShowArea(CShowArea* area)
{
    this->m_RefShowArea = area;
}


void CMySprite::setSpStartPosition()
{
    log("sp Ready to Move");
    this->m_oSpStartPosition = this->getPosition();
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
                       
                       int setLine = 0;

                       CMargin* margin = m_RefShowArea->getMargin(setLine);

                       float rad = CMath::getRadian(margin->m_oStart, margin->m_oTaget);
                       float dis = ccpDistance(margin->m_oStart, margin->m_oTaget);
                       int ranint = CMath::getRandom(0, dis);

                       const Vec2& ps = CMath::getVec2(margin->m_oStart, ranint, RADINA_TOGAME(rad));


                       setPlayerPosition(ps);
    }
        break;
    case STATE_STANDER:
        //m_currentAngle = ANGLE_NONE;
        //clearGuide();
        //this->unschedule(schedule_selector(CMySprite::run));
       
        log("mysprite state STATE_STANDER");
        break;
    case STATE_MOVE:     
        m_currentAngle = ANGLE_NONE;
        //schedule(schedule_selector(CMySprite::run));
        log("mysprite state STATE_MOVE");
        setSpStartPosition();       
        break;            
    case STATE_RUN:
        log("mysprite state STATE_RUN");
        //m_currentAngle = ANGLE_NONE;
        clearGuide();
        break;
    }
}                


/************************************************************************/
/*
@brief        设置玩家为之
@param[in]     pos   输入坐标
@param[out]
@return        void
*/
/************************************************************************/
void CMySprite::setPlayerPosition(const Vec2& pos)
{                                     
    this->setPosition(pos);       
    m_RefPlayer->setPlayerPosition(pos);
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

    int selectindex = m_RefShowArea->getTargetIndex(vec2);
    if (selectindex != SELECTID_NULL)
    {            
        log("location position");          

        CMargin* tMargin = m_RefShowArea->getMargin(selectindex);
        const Vec2& refp = CMath::getFootPoint(tMargin->m_oStart, tMargin->m_oTaget, vec2);
        // 
        setPlayerPosition(refp);
    }
    else
    {
        setState(STATE_MOVE);
        setDirectStartPosition(vec2);
		m_oAbsPosition = vec2;
		m_oEndPosition = m_oAbsPosition;
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
	m_oEndPosition = point;

	int distance = getAbsDistance();
	log("angle:%d , distance:%d",m_currentAngle, distance);


	Vec2 fixPos = CMath::getVec2(m_oSpStartPosition, distance, CMath::angleToRadian( m_currentAngle));
	
	//Vec2 fixPos = getPosition();   
	//fixPosition(point, fixPos);       
	this->setPosition(fixPos);      
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
	

	//float dis = ccpDistance(m_oPointerStart, inPos);
	//outPos = CMath::getVec2(m_AbPosition, dis, CMath::angleToRadian(fixangle));
    
}

/*********************************************************************/
/*
* @brief        检查方向
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
			m_currentAngle      = fixangle;
			return;
		}	

		setDirectStartPosition(inPos);
		m_iCountRecord = 0;
	}
}


void CMySprite::changeDirect(const Vec2& inPos,int fixangle)
{

	log("Current Angle: %d, fixAngle:%d", m_currentAngle, fixangle);
	//const Vec2& pos = getPosition();

	//log("angle :%d , fixangle:%d" , angle, fixangle);
	//addGuide(pos);
	//---------------------------------------------
	//setSpStartPosition();
	// 
	//m_RefPath->addPoint(pos);        //   

	//m_oPointerStart     = inPos;

	if (m_currentAngle != ANGLE_NONE)
	{
		m_oAbsPosition = inPos;
		m_oEndPosition = m_oAbsPosition;

		m_oSpStartPosition = getPosition();
	}

}


int CMySprite::getAbsDistance()
{
	//根据方向得到 距离

	if (m_currentAngle == ANGLE_NONE || m_currentAngle == ANGLE_ERROR)
	{
		return 0;
	}

	int distance = 0;


	if (90 == abs(m_currentAngle))
	{
		//log("up down");

		distance = static_cast<int>(abs(m_oAbsPosition.y - m_oEndPosition.y));

	}else{
		//log("right left");
		distance = static_cast<int>(abs(m_oAbsPosition.x - m_oEndPosition.x));

	}

	return distance;
}

/**
* @brief        渲染通道
* @param[in]    dn  渲染节点
* @param[out]   
* @return       void
*/
void CMySprite::print(DrawNode* dn)
{
    dn->drawDot(this->getPosition(), 20, Color4F(1, 0, 0, 0.5));  
        

	
//     int ta[] = { 0 , 200};   
//     for (int i = 0; i < 2;i++)
//     {
//         Vec2 endP = CMath::getVec2(m_oPointerStart, 100, CMath::angleToRadian(ta[i]));
//         dn->drawSegment(m_oPointerStart, endP, 1, Color4F(0, 1, 1, 1));
//     }    


    for (int i = 0; i < m_oTPath.size();i++)
    {
        dn->drawDot(m_oTPath[i], 10, Color4F(0, 1, 1, 1));  
    }               
        
    switch (m_State)
    {
    case STATE_DRAW:		

		dn->drawSegment(m_oSpStartPosition ,getPosition(), 1, Color4F(0, 1, 1, 1));
      
        break;
	case STATE_MOVE:
		dn->drawDot(m_oDirectStart, 3, Color4F(.03,0,1,1));
		dn->drawSegment(m_oAbsPosition, m_oEndPosition, 1, Color4F(0, 1, 1, 1));

		break;
    }    
}




void CMySprite::run(float tm)
{

    //log("follow! %f, %f", m_oFollow.x , m_oFollow.y);

}


void CMySprite::addGuide(const Vec2& point)
{
    m_oTPath.push_back(point);
}


void CMySprite::clearGuide()
{
    m_oTPath.clear();
}