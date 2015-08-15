#include "session.h"
#include "basebean.h"
#include <QString>
#include <QVariant>
#include <QDate>
#include "nullable.h"
#include "beanquery.h"
#include "sessiondata.h"
Session::Session () {
loaded = false;
sessionDatas = new QSet<SessionData>();
}
QString Session::getTableName () {
return QString(TABLENAME);
}
QString Session::getId () const {
return id;
}
QVariant Session::getExpirationDate () {
return expirationDate;
}
QList<SessionData>* Session::getSessionDatas () {
if (!loaded){
load();
}

QList<SessionData>* result = new QList<SessionData> ();
sessionDatas->reserve(sessionDatas->size());
typename QSet<SessionData>::const_iterator i = sessionDatas->constBegin();
while (i != sessionDatas->constEnd()){
result->append(*i);
++i;
}
return result;
}
Session* Session::setExpirationDate (const QVariant& expirationDate) {
this->expirationDateModified=true;
this->expirationDate=expirationDate;
return this;
}
Session* Session::setExpirationDateInternal (const QVariant& expirationDate) {
this->expirationDate=expirationDate;
return this;
}
Session* Session::setId (const QString& id) {
if (!insert){
this->idModified = true;
this->_previousId = this->id;
}

this->id=id;
return this;
}
Session* Session::setIdInternal (const QString& id) {
this->id=id;
return this;
}
QString Session::getInsertFields () {
return QString("id,expiration_date");
}
QString Session::getInsertValuePlaceholders () {
return QString("?,?");
}
QList<QVariant>* Session::getInsertParams () {
QList<QVariant>* params=new QList<QVariant>();
params->append(id);
params->append(expirationDate);
return params;
}
QString Session::getUpdateFields (QList<QVariant>* params) {
QString query;
if (idModified){
params->append(id);
query += QString(",id=?");
}

if (expirationDateModified){
params->append(expirationDate);
query += QString(",expiration_date=?");
}

return query.mid(1);
}
QString Session::getUpdateCondition () {
return QString("id=?");
}
QList<QVariant>* Session::getUpdateConditionParams () {
QList<QVariant>* params=new QList<QVariant>();
if (!idModified){
params->append(id);
} else {
params->append(_previousId);
}

return params;
}
Session* Session::getById (QString id) {
SqlQuery*q = sqlCon->buildQuery();
QSqlQuery* res= q->select(Session::getSelectFields(QString("b1"))+QChar(',')+SessionData::getSelectFields(QString("b2")))->from(QString(Session::TABLENAME),QString("b1"))->leftJoin(SessionData::TABLENAME,QString("b2"),QString("b1.id = b2.session_id"))->where(QString("b1.id=?"),id)->execQuery();
if (res->next()){
Session* b1 = Session::getByRecord(res->record(),QString("b1"));
b1->loaded = true;
do {
SessionData* b2 = SessionData::getByRecord(res->record(),QString("b2"));
if (!b1->sessionDatas->contains(*b2)){
b1->sessionDatas->insert(*b2);
}

} while(res->next());
delete res;
delete q;
return b1;
}

delete res;
delete q;
throw new SqlException(sqlCon);
}
QString Session::getSelectFields (const QString& alias) {
if (alias.isEmpty()){
return QString("id as session__id,expiration_date as session__expiration_date") ;
} else {
return alias + QString(".id as ") + alias + QString("__id")+QChar(',')+alias + QString(".expiration_date as ") + alias + QString("__expiration_date") ;
}

}
Session* Session::getByRecord (const QSqlRecord& record,const QString& alias) {
Session* bean = new Session ();
return bean->setExpirationDateInternal(record.value(alias + QString("__expiration_date")))->setIdInternal(record.value(alias + QString("__id")).toString());
}
BeanQuery<Session>* Session::createQuery () {
return new BeanQuery<Session> (sqlCon->buildQuery()) ;
}
QString Session::getAllSelectFields (QString artistTableAlias) {
return Session::getSelectFields(QString(artistTableAlias))+QChar(',')+SessionData::getSelectFields(QString("b2"));
}
void Session::addRelatedTableJoins (BeanQuery<Session>* query) {
query->leftJoin(SessionData::TABLENAME,QString("b2"),QString("b1.id = b2.session_id"));
}
QList<Session*>* Session::fetchList (QSqlQuery* res) {
QList<Session*>* beans = new QList<Session*>();
Session* b1 = NULL;
while (res->next()){
b1 = Session::getByRecord(res->record(),QString("b1"));
b1->loaded = true;
beans->append(b1);
if (!res->record().value(QString("b2__id")).isNull()){
SessionData* b2 = SessionData::getByRecord(res->record(),QString("b2"));
if (!b1->sessionDatas->contains(*b2)){
b1->sessionDatas->insert(*b2);
} else {
delete b2;
}

}

}
return beans;
}
Session* Session::fetchOne (QSqlQuery* res) {
Session* b1 = NULL;
if (res->next()){
b1 = Session::getByRecord(res->record(),QString("b1"));
if (!res->record().value(QString("b2__id")).isNull()){
SessionData* b2 = SessionData::getByRecord(res->record(),QString("b2"));
if (!b1->sessionDatas->contains(*b2)){
b1->sessionDatas->insert(*b2);
} else {
delete b2;
}

}

}

return b1;
}
void Session::load () {
loaded = true;
SqlQuery* q = sqlCon->buildQuery();
QSqlQuery* res = q->select(SessionData::getSelectFields(QString("b2")))->from(Session::TABLENAME ,QString("b1"))->leftJoin(SessionData::TABLENAME,QString("b2"),QString("b1.id = b2.session_id"))->where(QString("b1.id = ?"),getId())->execQuery();
if (res->next()){
do {
SessionData* b2 = SessionData::getByRecord(res->record(),QString("b2"));
if (!this->sessionDatas->contains(*b2)){
this->sessionDatas->insert(*b2);
}

} while(res->next());
}

}
bool Session::remove () {
SqlQuery* q = sqlCon->buildQuery()->deleteFrom(QString(Session::TABLENAME))->where(QString("id = ?"),getId());
return q->execute();
}
void Session::setLoaded () {
this->loaded = true;
}
const char* Session::TABLENAME = "session" ;
