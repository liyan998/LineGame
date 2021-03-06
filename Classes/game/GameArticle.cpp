/************************************************************************/
/* 
道具


*/
/************************************************************************/

#include "GameElement.h"

#include "EventSystem.h"
#include "GameResMacros.h"
#include "GameLogic.h"

bool CGameArticle::init()
{
    Node::init();
    m_refPlayer = nullptr;

    m_iCategory = CGameElement::CATEGORY_PROERTY;
    m_iCollR    = 20;

    return true;
}

void CGameArticle::run(float time)
{
    if (m_iCreateType == CreateType::SYSTEM
        ||
        m_iCreateType == CreateType::DROP)
    {
        m_fCount += time;

        if (m_fCount >= 1)
        {            
            action_create();
            action_Disp();
            m_fCount = 0.0F;
        }
    }
}


void CGameArticle::print(DrawNode* dn)
{
    switch (m_State)

    {
    case STATE_ACTIVE:
    CGameElement::print(dn);
        break;
    default:
        break;
    }
}

void CGameArticle::setState(int state)
{
    this->m_State = state;

    switch (state)
    {
    case STATE_ACTIVE:
        
        setCurrentAnimation(m_pProperty->armtruename);
        getArmature()->getAnimation()->play(m_pProperty->playlab);
//         setCurrentAnimation(ARMATURE_PROPERTY);       
//         m_pSp->getAnimation()->play(PLAYLAB_PROPERTY_ADDHEALTH);
        break;
    case STATE_DISP:
        log("GameArticle dispter");
        clearCurrentAnimation();
        break;
    default:
        break;
    }


}

void CGameArticle::animation_effe()
{      
    setCurrentAnimation(ARMATURE_GUARD_DIE_REVIVE);
    getArmature()->getAnimation()->setMovementEventCallFunc(this, movementEvent_selector(CGameArticle::movementCallback));
    getArmature()->getAnimation()->play(PLAYLAB_GUARD_REVIVE);
}

void CGameArticle::released()
{
    clearCurrentAnimation();

    delete m_pProperty;
    m_pProperty = nullptr;
}

void CGameArticle::action_create()
{
    if (m_State != CGameArticle::STATE_DISP)
    {
        return;
    }

    log("time to up");
    if (m_iTimeCreate++ >= TIME_CREATE_ARTICLE)
    {
        delete m_pProperty;
        m_pProperty = nullptr;

        int pro = randProperty();
        setProperty(pro);

        Vec2 cp;
        randPosition(cp);
        setPosition(cp);

        setState(STATE_ACTIVE);
        m_iTimeCreate = 0;
    }
}


void CGameArticle::action_Disp()
{
    if (m_State != STATE_ACTIVE)
    {
        return;
    }
  
    //log("time to up %d , %d", m_iTimeDis,m_pProperty->liveTime);
    if (m_iTimeDis++ >= m_pProperty->liveTime)
    {
        if (m_iCreateType == CreateType::DROP)
        {
            animation_effe();            
        }
        else{
            setState(STATE_DISP);
        }


        m_iTimeDis = 0;
    }

}


void CGameArticle::movementCallback(Armature * armature, MovementEventType type, const std::string& name)
{
    switch (type)
    {
    case MovementEventType::COMPLETE:
    
    if (strcmp(name.c_str(), PLAYLAB_GUARD_REVIVE) == 0)
    {        
        if (m_refPlayer != nullptr && m_refPlayer->getSealState() == CGamePlayer::SealState::SEALSTATE_NONE)
        {
            CEventDispatcher::getInstrance()->dispatchEvent(m_pProperty->eventid, m_pProperty->pData );
        }
                
        switch (m_iCreateType)
        {
        case CreateType::PAY:
        case CreateType::DROP:
            static_cast<CGameLogic*>(this->getParent())->removeGameElement(this);
            break;
        case CreateType::SYSTEM:
            setState(STATE_DISP);
            break;
        }     
    }
        break;
    }
}

void CGameArticle::setProperty(int catetory)
{
    int link[] = 
    {
        T_Property::CATEGORY_ADDSPEED,
        T_Property::CATEGORY_ADDHEALTH,
        T_Property::CATEGORY_ADDTIME,
        T_Property::CATEGORY_ADDDPROTECT    
    };

    //---------------------------------------------------------------

    struct T_EventPropertyAddSpeed* pProAddsp = new struct T_EventPropertyAddSpeed;
    pProAddsp->addPart  = .3f;  //增加速度百分比
    pProAddsp->time     = 5;   //持续时间

    //---------------------------------------------------

    T_Property allProperty[] = 
    {
        {
            T_Property::CATEGORY_ADDSPEED,
            EVENT_PROPERTY_ADDSPEED, 
            pProAddsp,
            ARMATURE_PROPERTY,
            PLAYLAB_PROPERTY_ADDSPEED,
            7
        },
        { 
            T_Property::CATEGORY_ADDHEALTH, 
            EVENT_PROPERTY_ADDHEALTH, 
            new float(0.3f), 
            ARMATURE_PROPERTY, 
            PLAYLAB_PROPERTY_ADDHEALTH,
            13                                   //系统刷新存活时间
        },
        { 
            T_Property::CATEGORY_ADDTIME,
            EVENT_PROPERTY_ADDTIME, 
            new int(10), 
            ARMATURE_PROPERTY, 
            PLAYLAB_PROPERTY_ADDTIME,
            16
        },
        { 
            T_Property::CATEGORY_ADDDPROTECT, 
            EVENT_PROPERTY_ADDPROTECT, 
            PARM_NULL,
            ARMATURE_PROPERTY,
            PLAYLAB_PROPERTY_ADDPROTECT,
            20
        }
    };

    int size = sizeof(link) / sizeof(link[0]);
    int index = -1;
    for (int i = 0; i < size;i++)
    {        
        if (link[i] == catetory)
        {
            index = i;
            break;
        }     
    }
    if (index == -1)
    {
        log("error config ");
        return;
    }

    struct T_Property* pPro = new struct T_Property;

    pPro->category          = allProperty[index].category;
    pPro->eventid           = allProperty[index].eventid;
    pPro->pData             = allProperty[index].pData;
    pPro->armtruename       = allProperty[index].armtruename;
    pPro->playlab           = allProperty[index].playlab;
    pPro->liveTime          = allProperty[index].liveTime;

    setProperty(pPro);    
}


void CGameArticle::setProperty(T_Property* pProperty)
{
    this->m_pProperty = pProperty;
}


int CGameArticle::randProperty()
{
    int link[] =
    {        
        //T_Property::CATEGORY_ADDHEALTH,
        T_Property::CATEGORY_ADDTIME ,
        T_Property::CATEGORY_ADDSPEED,
        //T_Property::CATEGORY_ADDDPROTECT
    };

    int size = sizeof(link) / sizeof(link[0]);
    int index = CMath::getRandom(0, size - 1);


    return link[index];
}



void CGameArticle::setCreateType(int type)
{
    this->m_iCreateType = type;

    switch (type)
    {
    case CreateType::SYSTEM:
        setState(STATE_DISP);
        break;
    case CreateType::PAY:
    { 
                            Vec2 cp;
                            randPosition(cp);
                            setPosition(cp); 
    }
    case CreateType::DROP:                             
        setState(STATE_ACTIVE);    
        break;
    default:
        break;
    }
}