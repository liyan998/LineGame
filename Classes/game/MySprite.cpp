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


void CMySprite::setAbsPosition()
{
    log("Ready to Move");
    this->m_AbPosition = this->getPosition();
}



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
        setAbsPosition();       
        break;            
    case STATE_RUN:
        log("mysprite state STATE_RUN");
        //m_currentAngle = ANGLE_NONE;
        clearGuide();
        break;
    }
}

void CMySprite::setPlayerPosition(const Vec2& pos)
{                                     
    this->setPosition(pos);       
    m_RefPlayer->setPlayerPosition(pos);
}





void CMySprite::setPointerStart(const Vec2& point)
{
    this->m_oPointerStart = point;
	log("startPoint: %f, %f", m_oPointerStart.x, m_oPointerStart.y);

    setState(STATE_DRAW);
}


void CMySprite::onPressed(const Vec2& vec2)
{

    int selectindex = m_RefShowArea->getTargetIndex(vec2);
    if (selectindex != SELECTID_NULL)
    {
        //
        log("location position");
        //m_pShowArea->setAreaIndex(0, selectindex);
       // m_RefShowArea->setPlayerPosiztion(vec2, selectindex);

        CMargin* tMargin = m_RefShowArea->getMargin(selectindex);
        const Vec2& refp = CMath::getFootPoint(tMargin->m_oStart, tMargin->m_oTaget, vec2);
        // 
        setPlayerPosition(refp);
    }
    else
    {
        setState(STATE_MOVE);
        setPointerStart(vec2);
    }

}

void CMySprite::move(const Vec2& point)
{
    float radian    = RADINA_TOGAME(CMath::getRadian(m_oPointerStart, point));
    int angle       = CMath::radianToAngle(radian);
    int fixangle    = getFixAngle(angle);

    if (fixangle == ANGLE_ERROR)
    {
        log("angle:%d , fixangle:%d!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!", (angle), fixangle);
        return;
    }      





    //------------------------------------------------------------------ 


    if (m_currentAngle == ANGLE_NONE || m_currentAngle != fixangle)
    {
        log("Current Angle: %d, fixAngle:%d", m_currentAngle, fixangle);
        const Vec2& pos = getPosition(); 

                                             
        addGuide(pos);
        //         //---------------------------------------------
        setAbsPosition();
        // 
       // m_RefPath->addPoint(pos);        // 



        m_oPointerStart = point;
        m_currentAngle = fixangle;
        return;
    }

    float dis       = ccpDistance(m_oPointerStart, point);
    Vec2 position   = CMath::getVec2(m_AbPosition, dis, CMath::angleToRadian(fixangle));
    this->setPosition(position);



    if (m_oTPath.size() == 1)
    {
        m_RefPlayer->movePlayerTo(m_oTPath[0], position);
    }


    //m_RefPlayer->setPlayerPosition(position);

}


void CMySprite::print(DrawNode* dn)
{
    dn->drawDot(this->getPosition(), 20, Color4F(1, 0, 0, 0.5));  
        

//     dn->drawDot(m_oPointerStart, 10, Color4F(0,1,1,1));
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
        dn->drawSegment(m_AbPosition, getPosition(), 1, Color4F(0, 1, 1, 1));
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