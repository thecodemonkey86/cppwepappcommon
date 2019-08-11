#ifndef PAGECONFIG_H
#define PAGECONFIG_H

#include "mvc/controller/abstractpagecontroller.h"
#include "mvc/view/abstractview.h"

/**
 * @brief defines a page configuration which consists of a controller and a view. In order to be used with class PageManager, all sublasses of this class must define a public static method name(), i.e. an unique page identifier
 */
class PageConfig
{
public:
    PageConfig()  = default;
    virtual ~PageConfig() = default;

    /**
     * @brief makes an instance of the controller and registers a view at the controller
     * @return
     */
    virtual unique_ptr<AbstractPageController> createController()=0;

    /**
     * @brief runs the controller which got defined by createController
     * @param requestData
     * @param sessionData
     * @param serverData
     * @param httpHeader
     * @param sqlCon
     * @param outStream
     */
    void run(RequestData * requestData, SessionData * sessionData, ServerData * serverData, HttpHeader * httpHeader, const QSqlDatabase & sqlCon, FCGX_Stream *outStream);
};

#endif // PAGECONFIG_H
