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
	

   Rect rec(250, 592, 80, 80);

   addPoint(rec.origin);
   addPoint(Vec2(rec.origin.x + rec.size.width, rec.origin.y));
   addPoint(Vec2(rec.origin.x + rec.size.width, rec.origin.y - rec.size.height));
   addPoint(Vec2(rec.origin.x, rec.origin.y - rec.size.height));

   getAllPoint(m_oAllPoint);

   createShape(SHAPEID_AREA, m_oAllPoint)->setColor(Color4F(1, 1, 0.5, 1), Color4F(1, 1, 0.5, 1));
   createShape(SHAPEID_TEMP, m_oTempPoint)->setColor(Color4F(0, 1, 0.5, 1), Color4F(0, 1, 0.5, 1));;

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

    //getShape(SHAPEID_TEMP)->draw(dn);
    
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


//TODO��黮�������Ƿ�պ�
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


// void CShowArea::setPlayerPosiztion(const Vec2& vec2, int index)
// {
//     CMargin* tMargin	= static_cast<CMargin*>(this->getChildByTag(m_oAllMargin[index])); 
//     const Vec2& refp	= CMath::getFootPoint(tMargin->m_oStart, tMargin->m_oTaget, vec2);
// 
//     //m_pPlayer->setPlayerPosition(refp);
// }

// 
// void CShowArea::setPlayerPosiztion()
// {
//     int setLine         = CMath::getRandom(0, m_oAllMargin.size() - 1);
// 
//     CMargin* margin     = static_cast<CMargin*>(this->getChildByTag(m_oAllMargin[setLine]));
// 
//     float rad           = CMath::getRadian(margin->m_oStart, margin->m_oTaget);
//     float dis           = ccpDistance(margin->m_oStart, margin->m_oTaget);
//     int ranint          = CMath::getRandom(0, dis);
// 
//     const Vec2& ps      = CMath::getVec2(margin->m_oStart, ranint, RADINA_TOGAME(rad));
// 
//     //m_pPlayer->setState(CMySprite::STATE_INIT);
//     //m_pPlayer->setPlayerPosition(ps);
// 
//     //setAreaIndex(0, setLine);
// 
//     log("sprite setPostion:%f, %f, %d", m_pPlayer->getPosition().x, m_pPlayer->getPosition().y, ranint);
// 
// }



void CShowArea::setPath(CPath* path)
{
    this->m_pPath = path;
}





//TODO �Ż������?
void CShowArea::clearAreaIndex()
{
    if (m_Area[0] == -1 || m_Area[1] == -1)
    {
        log("no area %d | %d", m_Area[0], m_Area[1]);
        return;
    }

    log("-----------------------------------------------------");
    log("area -- %d , %d", m_Area[0], m_Area[1]);

    int ddirect         = 0;      
    int pathdirect      = m_pPath->getDirect();   
    int start           = -1;
    int end             = -1;

    if (pathdirect < 0)
    {
        ddirect = DIRECT_ANTICCLOCKWISE;
    }else if (pathdirect > 0)
    {
        ddirect = DIRECT_CLOCKWISE;
    }else{ 

        ddirect = DIRECT_ANTICCLOCKWISE;
        if (m_Area[0] < m_Area[1])
        {
            ddirect = DIRECT_CLOCKWISE;
        }        
    }                

    switch (ddirect)
    {
    case DIRECT_ANTICCLOCKWISE:
        start   = m_Area[1];
        end     = m_Area[0];
        std::reverse(m_pPath->m_oAllPoint.begin(), m_pPath->m_oAllPoint.end());
        break;
    case DIRECT_CLOCKWISE:
        start   = m_Area[0];
        end     = m_Area[1]; 
        break;
    default:
        break;
    }            

    if (start == -1 || end == -1)
    {               
        
        return;
    }

    log("ddirect %d, start %d , end %d", ddirect, start, end); 
    insert(m_pPath->m_oAllPoint, start, end);   

    getAllPoint(m_oAllPoint);                        

    getShape(SHAPEID_AREA)->setShape(m_oAllPoint);

//     if (this->m_Model != MODEL_IN)
//     {
//         setMode(MODEL_IN);
//     }
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

    bool skip = false;

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
    log("Size : %d" , outputVec.size());      
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
            TPoint* currenttp   = head;           //��ǰ�ڵ�
            TPoint* previewtp   = head->preview;  //��һ���ڵ�
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


void CShowArea::insert(std::vector<Vec2>& allpint, int start, int end)
{
    
    if (start == end)
    {
        TPoint* current     = getPoint(start);
       
        TPoint* tlink       = getTempHead(allpint); 
        TPoint* tend        = getTempEnd(tlink);

        TPoint* next        = current->next;

        current->next       = tlink;
        tlink->preview      = current;

        tend->next          = next;
        next->preview       = tend;  

        resetId();
    }else{       
        TPoint* startp      = getPoint(start);   
        TPoint* clipStart   = startp->next;         //
        //clips
        clipStart->preview  = nullptr; 

        TPoint* endp        = getPoint(end);        
        TPoint* clipEnd     = endp->next;
        endp->next = nullptr;                       // 

        ///-------------------------------------------

        bool hasContent0    = false;
        TPoint* findhead    = clipStart;

        while (findhead != nullptr)
        {            
            TPoint* tDelref = findhead;  

            if (findhead == m_pHandle)
            {
                hasContent0 = true;                 
            }                            
            findhead = findhead->next;

            delete tDelref;
            tDelref = nullptr;
        }            

        //---------------------------------------------
        //connect
        TPoint* temptp      = getTempHead(m_pPath->m_oAllPoint);
        TPoint* tempep      = getTempEnd(temptp);

        startp->next        = temptp;
        temptp->preview     = startp;          
        
        tempep->next        = clipEnd;
        clipEnd->preview    = tempep;

        if (hasContent0){ m_pHandle = startp; }

        resetId();  
    }
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
