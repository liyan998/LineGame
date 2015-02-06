#ifndef __CAT_H__
#define __CAT_H__

/************************************************************************/
/* 
Ê·À³ß÷
*/
/************************************************************************/
class CCat : public CNpc
{
public:

    enum TagIndex
    {
        INDEX_CAT = 0x233,      //¶¯»­
        
    };




public:

    CREATE_FUNC( CCat )

public:

    virtual void onEnter();

    virtual bool init();

    virtual void run(float time);

    virtual void animation_move();

    virtual void collwithPlayerCallBack();

    virtual void animation_stop();

    //------------------------------------------

    //

};
#endif // !__CAT_H__
