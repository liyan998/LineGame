#include "Util.h"


bool CUtil::hasPointInPloyon(std::vector<Vec2>& refVector, Vec2& refPoint)
{ 
    unsigned int count = 0;
    int polySides = refVector.size();

    std::vector<float>  polyX;
    std::vector<float>  polyY;

    for (int i = 0; i < refVector.size(); i++)
    {
        polyX.push_back(refVector[i].x);
        polyY.push_back(refVector[i].y);
    }

    float x         = refPoint.x;
    float y         = refPoint.y;

    int j           = polySides - 1;
    bool  oddNodes  = false;

    for (int i = 0; i < polySides; i++)
    {
        if ((polyY[i] < y && polyY[j] >= y || polyY[j] < y && polyY[i] >= y)
            &&
            (polyX[i] <= x || polyX[j] <= x)
            )
        {
            oddNodes ^= (polyX[i] + (y - polyY[i]) / (polyY[j] - polyY[i])*(polyX[j] - polyX[i]) < x);
        }
        j = i;
    }

    return oddNodes; 
}


unsigned int CUtil::getCountPointInPloyon(std::vector<Vec2>& refPloyon, std::vector<Vec2>& refAllPoint)
{
    unsigned int count = 0;

    for (int i = 0; i < refAllPoint.size();i++)
    {
        if (hasPointInPloyon(refPloyon, refAllPoint[i]))
        {
            count++;
        }
    }
    return count;
}