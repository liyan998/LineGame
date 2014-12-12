#include "DateTime.h"
#include <cstdlib>
#include <time.h>
#include <algorithm>


#include "../System.h"


long long CDateTime::getCurrentTimeMilis()
{                     
    struct timeval now;
    gettimeofday(&now, NULL);
    return (now.tv_sec * 1000 + now.tv_usec / 1000);
}