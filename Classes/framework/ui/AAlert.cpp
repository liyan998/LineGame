#include "AAlert.h"

using namespace liyan998;

//�ر�Alert
void CAAlert::Close()
{
    Node* parent = this->getParent();

    parent->removeChild(this);

}