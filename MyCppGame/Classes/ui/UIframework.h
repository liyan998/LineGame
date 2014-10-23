#ifndef __UIFRAMEWORK_H__
#define __UIFRAMEWORK_H__

#include "cocos2d.h"

using namespace cocos2d;

//----------------------------

#define WIDTH   640
#define HEIGHT  960

//UI²ÎÊý
struct TUIParm
{
    std::string     resName;
    Point           ancPoint;    
    Point           posPoint;
    int             iTagId;
};


class CPanel;
class UIElement;

#include "Panel.h"
#include "UIElement.h"


#endif//__UIFRAMEWORK_H__