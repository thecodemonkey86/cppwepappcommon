#ifndef PAGECONFIG_H
#define PAGECONFIG_H
#include <QString>
#include "controller/abstractpagecontroller.h"
#include "view/template/abstracttemplate.h"
#include "webappcommon_global.h"

class WEBAPPCOMMONSHARED_EXPORT PageConfig
{
public:
    PageConfig();
    virtual ~PageConfig();
    virtual AbstractPageController * createController()=0;
    virtual AbstractTemplate * createTemplate()=0;
    virtual QString controllerName() = 0;
    virtual HtmlTemplate* htmlTemplate(AbstractTemplate*body);
};

#endif // PAGECONFIG_H
