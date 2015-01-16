#include "GameLogic.h"

#include "ShowArea.h"
#include "GameResMacros.h"



bool CGameLogic::init()
{
    Node::init();
    log("Gamelogic init..."); 

    CEventDispatcher::getInstrance()->regsiterEvent(EVENT_CLOSE, this); 
    CEventDispatcher::getInstrance()->regsiterEvent(EVENT_HIT, this);

    CEventDispatcher::getInstrance()->regsiterEvent(EVENT_PROPERTY_ADDTIME, this);
    CEventDispatcher::getInstrance()->regsiterEvent(EVENT_PROPERTY_ADDHEALTH, this);

    CEventDispatcher::getInstrance()->regsiterEvent(EVENT_BOSSSKILL_START, this);
    CEventDispatcher::getInstrance()->regsiterEvent(EVENT_BOSSSKILL_END, this);
    CEventDispatcher::getInstrance()->regsiterEvent(EVENT_BOSSSKILL_TORNADO_CHANAGE, this);

    //-------------------------------------------------------------------------

    ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(
        RES_ANIMA_PNG_QINCAIDIE,
        RES_ANIMA_PLS_QINCAIDIE,
        RES_ANIMA_JSO_QINCAIDIE
        );

    ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(
        RES_ANIMA_PNG_DYB,
        RES_ANIMA_PLS_DYB,
        RES_ANIMA_JSO_DYB
        );

    ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(
        RES_ANIMA_PNG_PIPI_DIE,
        RES_ANIMA_PLS_PIPI_DIE,
        RES_ANIMA_JSO_PIPI_DIE
        );

    ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(
        RES_ANIMA_PNG_EFFE_DIEREBACK,
        RES_ANIMA_PLS_EFFE_DIEREBACK,
        RES_ANIMA_JSO_EFFE_DIEREBACK
        );

  
    ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(
        RES_ANIMA_PNG_PROPERTY,
        RES_ANIMA_PLS_PROPERTY,
        RES_ANIMA_JSO_PROPERTY
        );
    
    return true;
}   

void CGameLogic::onEnter()
{
    Node::onEnter();        
    log("Gamelogic onEnter.."); 

    Size size = Director::getInstance()->getWinSize();
    TTFConfig config("fonts/Marker Felt.ttf", 20);

    Vec2 orgin = Director::getInstance()->getVisibleOrigin();

    char str[15] = { 0 };
    sprintf(str, CHARSEQUEN_AREA,m_refShowArea->getArea() * 100 );

    auto label1 = Label::createWithTTF(config, str);
    label1->setAnchorPoint(Vec2(0.0f, 1));
    addChild(label1, 0, 200);
    label1->setPosition(Vec2(size.width - 200 + orgin.x,
        size.height - orgin.y));


    //str[15] = { 0 };
    sprintf(str, CHARSEQUEN_TIME, m_iTimer);

    auto label2 = Label::createWithTTF(config, str);
    label2->setAnchorPoint(Vec2(0.5f, 1));
    addChild(label2, 0, 100);
    label2->setPosition(Vec2(size.width / 2.0f + orgin.x, size.height - orgin.y));


    //str[15] = { 0 };
    sprintf(str, CHARSEQUEN_HEALTH, m_refSp->getHealth());
    auto label3 = Label::createWithTTF(config, str);
    label3->setAnchorPoint(Vec2(0, 1));
    addChild(label3, 0, 300);
    label3->setPosition(Vec2(orgin.x, size.height - orgin.y));

    //-----------------------------------------------------------

    createGameElement();    
}

void CGameLogic::onExit()
{
    Node::onExit();

    CEventDispatcher::getInstrance()->unRegsiterEvent(EVENT_CLOSE, this);    
    CEventDispatcher::getInstrance()->unRegsiterEvent(EVENT_HIT, this);

    CEventDispatcher::getInstrance()->unRegsiterEvent(EVENT_PROPERTY_ADDTIME, this);
    CEventDispatcher::getInstrance()->unRegsiterEvent(EVENT_PROPERTY_ADDHEALTH, this);

    CEventDispatcher::getInstrance()->unRegsiterEvent(EVENT_BOSSSKILL_START, this);
    CEventDispatcher::getInstrance()->unRegsiterEvent(EVENT_BOSSSKILL_END, this);
    CEventDispatcher::getInstrance()->unRegsiterEvent(EVENT_BOSSSKILL_TORNADO_CHANAGE, this);
}



inline
void CGameLogic::createGameElement()
{
    //Vec2 origin = Director::getInstance()->getVisibleOrigin();
    m_pBoss = CDragon::create();
    m_pBoss->m_refShowArea  = m_refShowArea;
    m_pBoss->m_refSp        = m_refSp;
    m_pBoss->m_refPlayer    = m_refPlayer;

    Vec2 cp;
    m_pBoss->randPosition(cp);
    m_pBoss->setPosition(cp);

    addChild(m_pBoss);

    m_oAllElement.push_back(m_pBoss);
    m_oAllRander.push_back(m_pBoss); 

    //------------------------------------------------

    const int numNpc = 2;
    for (int i = 0; i < numNpc;i++)
    {
        auto npc = CNpc::create();
        npc->m_refShowArea  = m_refShowArea;
        npc->m_refSp        = m_refSp;
        npc->m_refPlayer    = m_refPlayer;

        Vec2 cp;
        npc->randPosition(cp);
        npc->setPosition(cp);

        addChild(npc);

      m_oAllElement.push_back(npc);
      m_oAllRander.push_back(npc);
    }

    //------------------------------------------

    const int numArticle = 3;
    for (int i = 0; i < numArticle; i++)
    {
        auto article = CGameArticle::create();
        article->m_refShowArea = m_refShowArea;          

        article->setProperty(article->randProperty());

        if (i == 0)
        {
            article->setCreateType(CGameArticle::SYSTEM);
        }
        else
        {
            article->setCreateType(CGameArticle::PAY);
        }

        addChild(article);

        m_oAllElement.push_back(article);
        m_oAllRander.push_back(article);
    }

    //----------------------------

    auto tornado = CTornado::create();
    tornado->setTag(1000);
    tornado->setState(CTornado::STATE_DISAPPEAR);

    tornado->m_refPlayer = m_refPlayer;
    tornado->m_refShowArea = m_refShowArea;

    Vec2 tp;
    tornado->randPosition(tp);
    tornado->setPosition(tp);

    //m_oAllRander.push_back(tornado);
    m_oAllElement.push_back(tornado);

    addChild(tornado);
}


void CGameLogic::actionEvent(int evenid, EventParm pData)
{      
    switch (evenid)
    {
    case EVENT_CLOSE:
        h_ActionClose(pData);
        break; 
    case EVENT_HIT:
        h_ActionHit(pData);
        break;
    case EVENT_PROPERTY_ADDTIME:
        h_ActionAddHealth(pData);
        break;
    case EVENT_PROPERTY_ADDHEALTH:
        flushHealth(m_refSp->getHealth());
        break;
    case EVENT_BOSSSKILL_START:
        h_ActionBossSkill(pData);
        break;
    case EVENT_BOSSSKILL_END:
        h_ActionBossSkillEnd(pData);
        break;
    case EVENT_BOSSSKILL_TORNADO_CHANAGE:
        h_ActionBossSkillTornadChange(pData);
        break;
    default:
        break;
    }
}


void CGameLogic::h_ActionBossSkillTornadChange(EventParm pData)
{
    int color = (*(int*)pData);

    CTornado* pTornado = (CTornado*)getChildByTag(1000);
    if (pTornado != nullptr)
    {
        pTornado->setStyle(color);
    }
}




void CGameLogic::h_ActionBossSkillEnd(EventParm pData)
{
    int skillid = *((int*)pData);

    if (skillid == CBoss::Skill::SKILL_T_TORNADO)
    {
        CTornado* pTornado = (CTornado*)getChildByTag(1000);
        if (pTornado != nullptr)
        {
            pTornado->setState(CTornado::STATE_DISAPPEAR);
        }
    }
}

void CGameLogic::h_ActionBossSkill(EventParm pData)
{
    T_RandSkill* tPRandskill = (*(T_RandSkill**)pData);
    int skillid = tPRandskill->m_iSkillId;

    if (skillid == CBoss::Skill::SKILL_T_TORNADO)
    {
        T_SkillDrogTornado* tPTornado = static_cast<T_SkillDrogTornado*>(tPRandskill->m_pSkill);
        CTornado* pTornado = (CTornado*)getChildByTag(1000);  
        
        if (pTornado != nullptr)
        {
            Vec2 tp;
            pTornado->randPosition(tp);
            pTornado->setPosition(tp);

            pTornado->setStyle(tPTornado->currentColor);
            pTornado->setState(CTornado::STATE_LIVE);
        }
    }
}

void CGameLogic::h_ActionAddHealth(EventParm pData)
{
    int time = *((int*)pData);
    if (m_iTimer - time > 0)
    {
        m_iTimer -= time;
    }
    else
    {
        m_iTimer = 0;
    }

    flushTime(m_iTimer);
}

void CGameLogic::h_ActionClose(EventParm pData)
{
    switch (m_refShowArea->getPathType())
    {
    case POSITION_AREA_ENDPOINT + POSITION_AREA_ENDPOINT:
    case POSITION_AREA_LINE + POSITION_AREA_LINE:
    case POSITION_AREA_LINE + POSITION_AREA_ENDPOINT:
    {
        if (!m_refShowArea->isCloseArea())
        {
            return;
        }
        m_refShowArea->clearAreaIndex();

        clearGameElement();
        m_refShowArea->setClose(m_pBoss->getPosition());
        m_refSp->clearGuide();

        dropObject();

        float area = m_refShowArea->getArea();       
        flushArea(area);

        if (area > WINPART)
        {         
            CEventDispatcher::getInstrance()->dispatchEvent(EVENT_WIN, PARM_NULL);
        } 
    }
        break;
    default:
        m_refSp->clearGuide();
        return;        
    }     
}


/************************************************************************/
/*
@brief          �����Ȧס��������Ϸ����
@param[in]
@param[out]
@return         void
*/
/************************************************************************/
void CGameLogic::clearGameElement()
{
    int rmode = m_refShowArea->hasIncludeMaster(m_pBoss->getPosition()) ? MODEL_IN: MODEL_OUT;
    
    for (int i = 0; i < m_oAllElement.size();i++)
    {
        CGameElement* t_pEelment = m_oAllElement[i];
        int category = t_pEelment->getCategory();
        switch (category)
        {
        case CGameElement::CATEGORY_NPC:
        {
            CNpc* tpNpc = static_cast<CNpc*>(t_pEelment);
            clearNpc(tpNpc, rmode);
        }   
            break;
        case CGameElement::CATEGORY_PROERTY:
        {
            CGameArticle* tpGameArticle = static_cast<CGameArticle*>(t_pEelment);
            clearGameObject(tpGameArticle, rmode);
        }           
            break;
        case CGameElement::CATEGORY_TORNADO:
        {
            CTornado* tPTornado = static_cast<CTornado*>(t_pEelment);
            clearTornado(tPTornado, rmode);
        }           
            break;
        }
    } 
}

void CGameLogic::clearTornado(CTornado* pTornado, int mode)
{
    bool hasIn = m_refShowArea->hasIncludeMaster(pTornado->getPosition());

    switch (mode)
    {
    case MODEL_IN:
        if (!hasIn)
        {          
            CEventDispatcher::getInstrance()->dispatchEvent(EVENT_BOSSSKILL_TORNADO_SURROUND, 0);                       
        }
        break;
    case MODEL_OUT:
        if (hasIn)
        {
            CEventDispatcher::getInstrance()->dispatchEvent(EVENT_BOSSSKILL_TORNADO_SURROUND, 0);            
        }
        break;
    default:
        break;
    }
}

void CGameLogic::clearNpc(CNpc* pNpc, int mode)
{      
    bool hasIn = m_refShowArea->hasIncludeMaster(pNpc->getPosition());
    switch (mode)
    {
    case MODEL_IN:      
        //log("MODEL_IN");
        if (!hasIn)
        {
            pNpc->setState(CNpc::STATE_DIE);
            m_oAllDrop.push_back(pNpc->getPosition());
        }
        break;
    case MODEL_OUT:
        //log("MODEL_OUT");
        if (hasIn)
        {
            pNpc->setState(CNpc::STATE_DIE);
            m_oAllDrop.push_back(pNpc->getPosition());
        }         
        break;
    }
}


void CGameLogic::clearGameObject(CGameArticle* pGameAricle, int mode)
{
    if (pGameAricle->getState() != CGameArticle::STATE_ACTIVE)
    {
        return;
    }    

    bool hasIn = m_refShowArea->hasIncludeMaster(pGameAricle->getPosition());
    switch (mode)
    {
    case MODEL_IN:
        //
        //log("MODEL_IN");
        if (!hasIn)
        {
            pGameAricle->animation_effe();           
        }
        break;
    case MODEL_OUT:
        //log("MODEL_OUT");
        if (hasIn)
        {
            pGameAricle->animation_effe();           
        }
        break;
    }
}


void CGameLogic::h_ActionHit(EventParm pData)
{    
    flushHealth(m_refSp->getHealth());
    CEnemy* pEnemy = (CEnemy*)(*(CEnemy**)pData);
    m_oBong = pEnemy->getPosition();    
}


void CGameLogic::flushArea(float area)
{
    Label* lab = (Label*)getChildByTag(200);

    char str[15] = { 0 };
    sprintf(str, CHARSEQUEN_AREA, area * 100);
    lab->setString(str);
}

void CGameLogic::flushHealth(int health)
{
    Label* lab = (Label*)this->getChildByTag(300);
    char str[15] = { 0 };
    sprintf(str, CHARSEQUEN_HEALTH, health);
    lab->setString(str);
}

void CGameLogic::flushTime(int time)
{
    Label* lab = (Label*)this->getChildByTag(100);

    char str[15] = { 0 };
    sprintf(str, CHARSEQUEN_TIME,time);
    lab->setString(str);
}

void CGameLogic::run(float time)
{
    for (int i = 0; i < m_oAllElement.size();i++)
    {
        m_oAllElement[i]->run(time);
    }

    if ((m_fCounter += time) > 1)
    {
        flushTime(m_iTimer);
        //log("m_iTimer %d", m_iTimer);

        if (m_iTimer++ >= TIMEOUT)
        {
            CEventDispatcher::getInstrance()->dispatchEvent(EVENT_TIMEOUT, PARM_NULL);
            m_iTimer = 0;
        }
        m_fCounter = 0.0f;
    }
}

void CGameLogic::print(DrawNode* dn)
{                                   
    for (int i = 0; i < m_oAllRander.size();i++)
    {
        m_oAllRander[i]->print(dn);
    }

    dn->drawDot(m_oBong, 4, Color4F(0,0,1,1));
}


void CGameLogic::setState(int state)
{

}


void CGameLogic::released()
{
    m_oAllElement.clear();
    m_oAllRander.clear();

    this->removeAllChildren();
}

/************************************************************************/
/*
@brief          �Ƴ���Ϸ����
@param[in]      CGameElement ��ϷԪ��
@param[out]
@return         void
*/
/************************************************************************/
void CGameLogic::removeGameElement(CGameElement* pElement)
{
    for (int i = 0; i < m_oAllRander.size();i++)
    {
        if (m_oAllRander[i] == pElement)
        {
            m_oAllRander.erase(m_oAllRander.begin() + i);
            break;
        }        
    }
    for (int i = 0; i < m_oAllElement.size(); i++)
    {
        if (m_oAllElement[i] == pElement)
        {
            m_oAllElement.erase(m_oAllElement.begin() + i);
            break;
        }
    }

    pElement->m_refShowArea = nullptr;
    pElement->released();

    removeChild(pElement);
}

/************************************************************************/
/* 
@brief          ����
@param[in]      
@param[out]
@return         void
*/
/************************************************************************/
void CGameLogic::dropObject()
{
    if (m_oAllDrop.size() == 0)
    {
        return;
    }

    for (int i = 0; i < m_oAllDrop.size(); i++)
    {
        int randnum = CMath::getRandom(1, 100);
        if (randnum <= 100)
        {
            //log("drop object ~~~~~~~~~~~~~~~~~~");
            auto article = CGameArticle::create();
            article->m_refShowArea = m_refShowArea;

            article->setProperty(article->randProperty());        
            article->setCreateType(CGameArticle::CreateType::DROP);   
           
            addChild(article);

            Vec2 cp;
            article->randPosition(cp);
            article->setPosition(m_oAllDrop[i]);

            auto moveto = MoveTo::create(0.81, cp);
            article->runAction(moveto);

            m_oAllElement.push_back(article);
            m_oAllRander.push_back(article);
        }
    }

    m_oAllDrop.clear();

}