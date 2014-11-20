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

///////////////////////////////////////////////////////////

#define RADINA_TOGAME( radina ) PI / 2 - radina  

#define FTOI( fn ) static_cast<int>(fn)

#define GRAD_CELL 10
#define GRAD_NUMBER( x ) FTOI( x ) / GRAD_CELL * GRAD_CELL




//////////////////////////////////////////////////////////// 



#endif