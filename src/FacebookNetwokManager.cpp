///////////////////////////////////////////////////////////
//  FacebookNetwokManager.cpp
//  Implementation of the Class FacebookNetwokManager
//  Created on:      26-Apr-2011 11:40:27 AM
//  Original author: Golyshkin A.
///////////////////////////////////////////////////////////

#include <QNetworkRequest>
#include <QNetworkReply>
#include <QStringList>
#include <FacebookNetwokManager.h>
#include <FacebookNetwokClient_def.h>
#include <FacebookLogger.h>

FacebookNetwokManager::FacebookNetwokManager( FacebookLogger * const pLogger )
: QNetworkAccessManager(), m_RequestType( FACEBOOK_REQUEST_NO ), m_pFacebookLogger( pLogger )
{
   connect( this, SIGNAL( finished(QNetworkReply *) ), this, SLOT( OnLoadComplete(QNetworkReply *) ) );
}

FacebookNetwokManager::~FacebookNetwokManager()
{
   disconnect( this, SIGNAL( finished( QNetworkReply *) ) );
}

bool
FacebookNetwokManager::SetRequestType( FACEBOOK_REQUEST_T aRequestType )
{
   // This check means that FacebookNetwokManager is not busy now by another request
   if ( m_RequestType == FACEBOOK_REQUEST_NO )
   {
      m_RequestType = aRequestType;
      emit FacebookNetwokManagerRequestStatus( m_RequestType );

      return true;
   }

   return false;
}

bool
FacebookNetwokManager::Request( FACEBOOK_REQUEST_T aRequestType, const QUrl aURL )
{
   // This check means that FacebookNetwokManager is not busy now by another request
   if ( m_RequestType == FACEBOOK_REQUEST_NO )
   {
      m_RequestType = aRequestType;
      emit FacebookNetwokManagerRequestStatus( m_RequestType );

      m_NetworkRequest.setUrl( aURL );
      get( m_NetworkRequest );

      return true;
   }

   return false;
}

void
FacebookNetwokManager::ClearRequestType()
{
   m_RequestType = FACEBOOK_REQUEST_NO;
   emit FacebookNetwokManagerRequestStatus( FACEBOOK_REQUEST_NO );
}

void
FacebookNetwokManager::OnLoadComplete( QNetworkReply *pRequest )
{
   switch ( m_RequestType )
   {
      case FACEBOOK_REQUEST_TOKEN_DATA:
      {
         ParseTokenRequest( pRequest );
         break;
      }
      case FACEBOOK_REQUEST_MYFRIENDS_DATA:
      {
         ParseMyFriendsRequest( pRequest );
         break;
      }
      case FACEBOOK_REQUEST_GROUPS_DATA:
      {
         ParseGroupsRequest( pRequest );
         break;
      }
      default: // If not required special parsing just returning the result
      {
         emit FacebookNetwokManagerFinished( m_RequestType, pRequest->readAll() );
         ClearRequestType();
         break;
      }
   }
}

void
FacebookNetwokManager::ParseTokenRequest( QNetworkReply *pRequest )
{
   m_pFacebookLogger->Log( "FacebookNetwokManager::ParseTokenRequest()" );

   if ( pRequest->error() == QNetworkReply::NoError)
   {
      QString redUrl;

      if ( pRequest->header( QNetworkRequest::ContentTypeHeader ).toString().contains( "html" ) )
      {
         QString URL = pRequest->url().toString();

         if ( URL.contains( "login_success.html#access_token" ) )
         {
            // The login was succesful now we going to get it
            QStringList fistIteration  = URL.split( "#access_token=" );
            QStringList lastIteration  = fistIteration[ 1 ].split( "&" );

            m_Token = lastIteration[ 0 ];

            m_pFacebookLogger->Log( "FacebookNetwokManager::ParseTokenRequest: Authenficated by token=[" + m_Token + "]" );

            // FacebookNetwokManager finished current task and waiting another request
            ClearRequestType();
         }
      }
   }
}

void
FacebookNetwokManager::ParseMyFriendsRequest( QNetworkReply *pRequest )
{
   m_pFacebookLogger->Log( "FacebookNetwokManager::ParseMyFriendsRequest()" );

   if ( pRequest->error() == QNetworkReply::NoError )
   {
      // FacebookNetwokManager finished current task and waiting another request
      emit FacebookNetwokManagerFinished( m_RequestType, pRequest->readAll() );

      ClearRequestType();
   }
}

void
FacebookNetwokManager::ParseGroupsRequest( QNetworkReply *pRequest )
{
   m_pFacebookLogger->Log( "FacebookNetwokManager::ParseGroupsRequest()" );

   if ( pRequest->error() == QNetworkReply::NoError )
   {
      // FacebookNetwokManager finished current task and waiting another request
      emit FacebookNetwokManagerFinished( m_RequestType, pRequest->readAll() );

      ClearRequestType();
   }
}

