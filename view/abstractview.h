#ifndef ABSTRACTVIEW_H
#define ABSTRACTVIEW_H
#include "webappcommon_global.h"
#include "mvc/mvcmessage.h"
using namespace std;

class WEBAPPCOMMONSHARED_EXPORT AbstractView
{
public:
    AbstractView();
    ~AbstractView();
    virtual void update(const MvcMessage&)=0;
};

#endif // ABSTRACTVIEW_H
