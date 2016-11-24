#ifndef PAGEMANAGER2_H
#define PAGEMANAGER2_H
#include <QString>
#include <memory>
#include <vector>
#include "exception/qtexception.h"
#include <QHash>
#include "webappcommon_global.h"

using namespace std;
#include "page_config/pageconfig.h"

class WEBAPPCOMMONSHARED_EXPORT PageManager2
{
private:
    QHash<QString,shared_ptr<PageConfig>> pages;


public:
  PageManager2();
    static QString getControllerUrl(const QString&name);
    static QString baseUrl;
    void runController(const QString&name, RequestData * requestData, SessionData * sessionData, ServerData * serverData, HttpHeader * httpHeader, Sql*sqlCon);
    void addPage(const shared_ptr<PageConfig> &config);
    template<class T> static QString getControllerUrl() {
         return QStringLiteral("%1?controller=%2").arg(baseUrl,T::controllerName());
    }
    template<class T> static QString getControllerUrl(const QString&action) {
         return QStringLiteral("%1?controller=%2&action=%3").arg(baseUrl,T::controllerName(),action);
    }
    static QString getBaseUrl();
    static void setBaseUrl(const QString &value);
};

#endif // PAGEMANAGER2_H