
#include "GameElement.h"

bool CBoss::init()
{
    Node::init();
    m_pSp = Sprite::create("CloseNormal.png");
    m_pSp->setScale(1.5f);

    addChild(m_pSp);
    return true;
}

void CBoss::run(float time)
{

}


//TODO ��ɶ���
void CBoss::animation_idle()
{

}

//TODO ��ɶ���
void CBoss::animation_attack()
{

}

//TODO ��ɶ���
void CBoss::animation_die()
{

}

//TODO ��ɶ���
void CBoss::animation_move()
{

}