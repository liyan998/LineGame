/************************************************************************/
/*                                                                      */
/************************************************************************/

#ifndef __PANEL_H__
#define __PANEL_H__

#include "UIframework.h"

class CPanel : public Layer
{
public:

    CREATE_FUNC(CPanel)

public:

    //
    virtual bool init()    override;

    //
    virtual void onEnter() override;

    //
    virtual void onExit()  override;

    //
    void addUIElement(const TUIParm&);

    void menuCloseCallback(Ref*);

 
};


#endif