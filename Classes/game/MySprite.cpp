#include "MySprite.h"

#include "framework/util/Math.h"

using namespace liyan998;

bool CMySprite::init()
{
    Sprite::init();

	m_currentAngle		= -1;
    m_fStep				= 2.f;

	m_avibleAngle[0] = 0;
	m_avibleAngle[1] = 90;
	m_avibleAngle[2] = 180;
	m_avibleAngle[3] = -90;

    DrawNode* pDn = DrawNode::create();	
    addChild(pDn);

    pDn->drawDot(Vec2::ZERO, 20, Color4F(1, 0, 0, 0.5));
    
    this->setAnchorPoint(Vec2::ZERO);
    this->setContentSize(Size(40,40));
    Rect& rec = this->getBoundingBox();

    //log("bundBox:%f, %f, %f, %f", rec.origin.x, rec.origin.y, rec.size.width , rec.size.height);

    return true;
}

void CMySprite::move(const Vec2& point)
{
	float radian = RADINA_TOGAME( CMath::getRadian( m_oPointerStart, point ) );
	
	int angle =  CMath::radianToAngle( radian );	
	int fixangle = getFixAngle(angle);
	log("angle:%d , fixangle:%d", (angle), fixangle);	

	if (m_currentAngle != fixangle)
	{
		log("no direct %d , currentAngle:%d", angle, m_currentAngle);

		//记录节点改变方向
		setAbsPosition();
		m_RefPath->addPoint(getPosition());
		m_oPointerStart = point;
		m_currentAngle = fixangle;
	}
	
         
		

	float dis		= ccpDistance(m_oPointerStart , point);
	Vec2 position	= CMath::getVec2(m_AbPosition, dis, CMath::angleToRadian(fixangle));
	this->setPosition(position);
 
}

//返回方向
//返回值范围
//90, 0 , -90, 180
int CMySprite::getFixAngle(int angle)
{
	int errorMarign = 20;

	int angleList[] = { 90, 0 , -90, 180};

	int size = sizeof(angleList) / sizeof(angleList[0]);
	for (int i = 0;i < size;i++)
	{
		if (angleList[i] == angle)
		{
			return angle;
		}else if(abs(angle - angleList[i]) < errorMarign)
		{
			return angleList[i];
		}
	}



	if (angle > -90 + 20 && angle < 0 - 20)
	{//-> right | down
		return -90;
	}else if(0)
	{
	}

	return 0;
}


void CMySprite::setPath(CPath* path)
{
	this->m_RefPath = path;
}


void CMySprite::pointerMove(const Vec2& pointerVec)
{
    Vec2 pos = CMath::getVec2(m_AbPosition, pointerVec.x, pointerVec.y);
    setPosition(pos);
}


void CMySprite::setAbsPosition()
{
    log("Ready to Move");
    this->m_AbPosition = this->getPosition();
}



void CMySprite::setState(int state)
{

}


void CMySprite::setPointerStart(const Vec2& point)
{
    this->m_oPointerStart = point;
	log("startPoint: %f, %f", m_oPointerStart.x, m_oPointerStart.y);
}

void CMySprite::print(DrawNode* dn)
{


}