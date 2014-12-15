#ifndef __UTIL_H__
#define __UTIL_H__

#include "../System.h"
#include "../Margin.h"

class CUtil
{
public:

    //���Ƿ���ployon��
    static bool hasPointInPloyon(const std::vector<Vec2>& refVector,const Vec2& refPoint);
 
    //������ployon�ڵĵ����
    static unsigned int getCountPointInPloyon(std::vector<Vec2>& refPloyon, std::vector<Vec2>& refAllPoint);

    //����һ�����ϰ�����һ�����ϸ���
    static unsigned int getCountPointInRec(const std::vector<Vec2>& refRec1, const std::vector<Vec2>& refRec2);
    
    //���Ƿ����߶���
    static bool hasPointInLine(const Vec2& lineP1, const Vec2& lineP2, const Vec2& outPoint);

    //��õ���ֱ�ߵ�λ�ù�ϵ
    static float getDisPointLine(const Vec2& lineP1, const Vec2& lineP2, const Vec2& outPoint);

    //�õ���vector
    static void getSubVector(const std::vector<Vec2>& resource, int start, int end, std::vector<Vec2>& result);
    
    //�õ�������з���
    static int getRevceDircet(int direct);

	//�õ���ת����
	static int getRotateDirect(const std::vector<Vec2>& allpoint);
	static int getRotateDirect(const std::vector<Vec2>&allpoint, const std::vector<Vec2>&path);	
	static int getRL(int currentDirect, int angle);

    //ת������ֵ
    static unsigned int converDirectToFlag(int inDirect);
    static int converFlagToDirect(unsigned int inFlag);

    //�õ�����
    static void getDirectFromFlag(unsigned int inFlag , std::vector<int>& outDirects);

    //��ʽ������
    static void formartGrid(Vec2& inoutPoint);

    static void formartGrid(Vec2& inoutPoint, int grid);

    //����Ļƥ��
    //static Vec2 originPosition(const Vec2& inPoint);

    //���ݵ�ǰ����õ�Ȩֵ��Ӧ����ȨֵΪ˳ʱ1����ʱ-1
    static int getNextAngle(int currentangle, int d);

    //�õ���С�ϰ�����
    static int getMinWallDis(const std::vector<CMargin*>& inAllMargin, const Vec2& inSP,int angle);
    static int getUDLR_atMarginDis(CMargin* pMaring ,const Vec2& inPoint, int direct);

    //�õ�FIX��ķ���
    static int getFixDirect(int currentdirect, int angle);

    //�õ�����
    static int getFixDictance(int direct, const Vec2& startP, const Vec2& endP);


};


 

#endif//__UTIL_H__