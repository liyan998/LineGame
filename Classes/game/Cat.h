#ifndef __CAT_H__
#define __CAT_H__

/************************************************************************/
/* 
ʷ����
*/
/************************************************************************/
class CCat : public CNpc
{

public:

    CREATE_FUNC( CCat )

public:

    virtual void onEnter();

    virtual bool init();

    virtual void run(float time);

    //

};
#endif // !__CAT_H__
