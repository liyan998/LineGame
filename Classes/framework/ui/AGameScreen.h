/************************************************************************/
/* 
作者:     严黎刚
日期:     2014-10-20

*/
/************************************************************************/
#ifndef __ACGAMESCREEN_H__
#define __ACGAMESCREEN_H__

#include "framework/System.h"
#include "framework/ui/AGameScene.h"
#include "framework/ui/AAlert.h"

//////////////////////////////////////////////////////////////////////////

#define CREATE_SCENE( scenename ) []{ return scenename::create(); }

#define ADD_SCENE(sid, sclassname) liyan998::MapPair( sid , CREATE_SCENE( ##sclassname## ))

//////////////////////////////////////////////////////////////////////////


namespace liyan998
{

    typedef int                                         IntMap_K;           //
    typedef IntMap_K                                    IntSceneID;         //
    typedef std::function<CAGameScene*()>               FUNMap_V;           //
    typedef std::pair< IntMap_K, FUNMap_V >             MapPair;            //
    typedef std::map< IntMap_K, FUNMap_V >::iterator    MapIter;            //

    //
    class CAGameScreen : public Scene
    {

    public:

        CAGameScreen();

    public:

        void InitScene(const MapPair&);

        void SetScene(IntSceneID);                                                      

        void SetAlert(IntSceneID);

    protected:
        std::map< IntMap_K, FUNMap_V >                  m_oAllScene;        //
        CAGameScene*                                    m_pCurrentScene;    //
        CAAlert*                                        m_pAlert;           //
    };
}

#endif//__ACGAMESCREEN_H__

