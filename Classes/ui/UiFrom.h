#ifndef __UIFROM_H__
#define __UIFROM_H__

#include "framework/ui/Panel.h"

class CUIFrom : public liyan998::CPanel
{
public:

    CREATE_FUNC( CUIFrom )


public:

    virtual bool init()         override;

    virtual void onEnter()      override;

    void onButtonClose(Ref *pSender, TouchEventType type);

private:

    Widget*     m_pUi;
    Button*     m_pButton;
};
#endif