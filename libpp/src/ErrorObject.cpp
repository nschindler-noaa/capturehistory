#include "ErrorObject.h"
using namespace std;

ostream& operator<<(ostream& os, const ErrorObject& err)
{
    err.writeObject(os);
    return os;
}
