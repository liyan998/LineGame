#include "AAlert.h"

using namespace liyan998;

//¹Ø±ÕAlert
void CAAlert::Close()
{
    Node* parent = this->getParent();

    parent->removeChild(this);

}