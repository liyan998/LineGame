/************************************************************************/
/* 


*/
/************************************************************************/
#ifndef __SYSTEM_H__
#define __SYSTEM_H__

#include "cocos2d.h"
                        
using namespace cocos2d; 


////////////////////////////////////////////////////////////

#define PI              3.14159F  

////////////////////////////////////////////////////////////

#define ANGLE_UP        90
#define ANGLE_LEFT      180
#define ANGLE_RIGHT     0
#define ANGLE_DOWN      -90  

#define ANGLE_NONE      2000000
#define ANGLE_ERROR     1000000 

////////////////////////////////////////////////////////////

#define FLAG_UP         0xF000
#define FLAG_DOWN       0x0F00
#define FLAG_LEFT       0x00F0
#define FLAG_RIGHT      0x000F


////////////////////////////////////////////////////////////

#define RADINA_TOGAME( radina ) PI / 2 - radina  



////////////////////////////////////////////////////////////

#define FTOI( fn ) static_cast<int>(fn)

#define GRAD_CELL 10
#define GRAD_NUMBER( x ) FTOI( x ) / GRAD_CELL * GRAD_CELL 

////////////////////////////////////////////////////////////

#define POSITION_ENDPOINT   10  //端点上
#define POSITION_LINE       11  //直线上 
#define POSITION_LOCK       20  //未解锁区域 
#define POSITION_UNLOCK     30  //解锁区域

////////////////////////////////////////////////////////////

#define DIRECT_CLOCKWISE        1		//闭合类型顺时针
#define DIRECT_ANTICCLOCKWISE   -1		//闭合类型逆时针

////////////////////////////////////////////////////////////S



#endif