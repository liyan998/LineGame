#include "GameElement.h"

bool CCat::init()
{
    CNpc::init();



    return true;
}

void CCat::onEnter()
{
    CNpc::onEnter();



}



void CCat::run(float time)
{
    CNpc::changeLiveDie(time);


}