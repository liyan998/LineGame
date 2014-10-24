/************************************************************************/
/* 


*/
/************************************************************************/
#ifndef __UIELEMENT_H__
#define __UIELEMENT_H__

#include "UIframework.h"

#define TAG_ICON    0x10001
#define TAG_LAB     0x10002

class CUIElement : public MenuItemImage
{
public:
    
    CREATE_FUNC(CUIElement)

public:

    void setLab(Sprite*);

    void setIcon(Sprite*);


};

#endif//__UIELEMENT_H__