#include "AGameScreen.h"


using namespace liyan998;

CAGameScreen::CAGameScreen():
m_pCurrentScene(NULL),
m_pAlert(NULL)
{

}


void CAGameScreen::InitScene(const MapPair& oMp)
{
    m_oAllScene.insert(oMp);
    log("Add Scene ID:%d ", oMp.first);
}

void CAGameScreen::SetScene(IntSceneID id)
{
    if (m_pCurrentScene && m_pCurrentScene->getTag() == id)
    {
        log("Same scene id:%d", id);
        return;
    }
    
    MapIter iter = m_oAllScene.find(id);
    if (iter != m_oAllScene.end())
    {
        //find

        if (!m_pCurrentScene)
        {            
            removeChild(m_pCurrentScene);
        }

        //
        if (!m_pAlert)
        {
            removeChild(m_pAlert);
            m_pAlert = NULL;
        }

        m_pCurrentScene = iter->second();
        m_pCurrentScene->setTag(iter->first);
        addChild(m_pCurrentScene);

    }else{
        log("Scene ID:%d not find", id);
    }
}

void CAGameScreen::SetAlert(IntSceneID id)
{

    MapIter mapiter = m_oAllScene.find(id);

    if (mapiter != m_oAllScene.end())
    {

    }
}