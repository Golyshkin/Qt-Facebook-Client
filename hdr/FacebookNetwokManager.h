///////////////////////////////////////////////////////////
//  FacebookNetwokManager.h
//  Implementation of the Class FacebookNetwokManager
//  Created on:      26-Apr-2011 11:40:27 AM
//  Original author: Golyshkin A.
///////////////////////////////////////////////////////////

#if !defined(EA_816C13A9_74EC_4ad9_B7B6_13A656C28583__INCLUDED_)
#define EA_816C13A9_74EC_4ad9_B7B6_13A656C28583__INCLUDED_

#include <QNetworkAccessManager.h>
#include <QUrl>
#include <QNetworkRequest>
#include <FacebookNetwokClient_def.h>

class FacebookLogger;
class QNetworkReply;

class FacebookNetwokManager : public QNetworkAccessManager
{
   Q_OBJECT

public:

   FacebookNetwokManager( FacebookLogger * const pLogger );

   virtual ~FacebookNetwokManager();

   const QString& GetTokenKey() const { return m_Token; }

   bool Request( FACEBOOK_REQUEST_T aRequestType, const QUrl aURL );

   bool RequestIsActive() const { return m_RequestType == FACEBOOK_REQUEST_NO ? false : true; }

   bool SetRequestType( FACEBOOK_REQUEST_T aRequestType );

   bool IsAuthorized() { return m_Token.length() > 0 ? true : false; }

   FACEBOOK_REQUEST_T GetExecutingRequestType() const { return m_RequestType; }

private slots:

   void OnLoadComplete( QNetworkReply *pRequest );

signals:

   void FacebookNetwokManagerRequestStatus( FACEBOOK_REQUEST_T aRequestType );

   void FacebookNetwokManagerFinished( FACEBOOK_REQUEST_T aRequestType, const QByteArray& aContent );

protected:

   FacebookNetwokManager( const FacebookNetwokManager& theFacebookNetwokManager);

private:

   void ParseTokenRequest( QNetworkReply *pRequest );

   void ParseMyFriendsRequest( QNetworkReply *pRequest );

   void ParseGroupsRequest( QNetworkReply *pRequest );

   void ClearRequestType();

private:

   FACEBOOK_REQUEST_T m_RequestType;

   QNetworkRequest m_NetworkRequest;

   FacebookLogger *m_pFacebookLogger;

   QString m_Token;
};

#endif // !defined(EA_816C13A9_74EC_4ad9_B7B6_13A656C28583__INCLUDED_)
