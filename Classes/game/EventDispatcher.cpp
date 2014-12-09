#include "EventSystem.h"

#include "System.h"


CEventDispatcher* m_pEvent = nullptr;


CEventDispatcher* CEventDispatcher::getInstrance()
{
    if (m_pEvent == nullptr)
    {                                     
        m_pEvent = new CEventDispatcher();
    }

    return m_pEvent;
}


void CEventDispatcher::regsiterEvent(int eventid, CEventHandler* pHandler)
{     
    Iter_AllEVentHandler iter_eventhandler = m_oAllHandler.find(eventid);
 
    T_AllEventHandler* tvector;

    if (iter_eventhandler != m_oAllHandler.end())
    {                                      
        tvector = iter_eventhandler->second;

        for (Iter_AllHandler iter = tvector->begin(); iter != tvector->end();++iter)
        {

            if (*iter == pHandler)
            {                  
                return;
            }
        }    

        tvector->push_back(pHandler);             
      
    }
    else
    {                                        
        tvector = new T_AllEventHandler();
        tvector->push_back(pHandler);        
        m_oAllHandler.insert(Pair_EventHandler(eventid, tvector));
    } 
}


void CEventDispatcher::unRegsiterEvent(int eventid, CEventHandler* pHandler)
{

    Iter_AllEVentHandler iter_eventhandler = m_oAllHandler.find(eventid);

    if (iter_eventhandler != m_oAllHandler.end())
    {
        T_AllEventHandler* pAllHandler = iter_eventhandler->second;


        for (Iter_AllHandler iter = pAllHandler->begin(); iter != pAllHandler->end(); ++iter)
        {
            
            if (pHandler == (*iter))
            {
                //log("===");
                pAllHandler->erase(iter);
                break;
            }  
        }

        //log("__Size%d", pAllHandler->size());
    }
}



void CEventDispatcher::dispatchEvent(int eventid, EventParm parm)
{                                                              
    Iter_AllEVentHandler iter_eventhandler = m_oAllHandler.find(eventid);

    if (iter_eventhandler != m_oAllHandler.end())
    {
        T_AllEventHandler* pAllHandler = iter_eventhandler->second;
        

        for (Iter_AllHandler iter = pAllHandler->begin(); iter != pAllHandler->end();++iter)
        {                     
            (*iter)->actionEvent(eventid, parm);
        }
    }

    delete parm;
    parm = nullptr;
    
}








