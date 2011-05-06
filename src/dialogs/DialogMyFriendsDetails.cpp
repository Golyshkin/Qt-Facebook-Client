#include <DialogMyFriendsDetails.h>

#include <QtGui>
#include <QHttp>
#include <QNetworkProxy>
#include <QWebView>
#include <parser.h>

#include <DialogMyFriends.h>
#include <DialogEvent.h>
#include <FacebookNetwokManager.h>
#include <DialogMyFriendsTableModel.h>
#include <HTMLButton.h>

FacebookDialog *DialogMyFriendsDetails::m_pInstance = NULL;

FacebookDialog *
DialogMyFriendsDetails::Instance( DialogEvent *pStartCmd )
{
   if ( m_pInstance == NULL )
   {
      m_pInstance = new DialogMyFriendsDetails( pStartCmd );
   }

   return m_pInstance;
}

DialogMyFriendsDetails::~DialogMyFriendsDetails()
{
   if ( m_pNameLabel )
   {
      delete m_pNameLabel;
   }

   if ( m_pBirthdayLabel )
   {
      delete m_pBirthdayLabel;
   }

   if ( m_pGenderLabel )
   {
      delete m_pGenderLabel;
   }

   if ( m_pWorkLabel )
   {
      delete m_pWorkLabel;
   }

   if ( m_pHTMLWebSiteButton )
   {
      delete m_pHTMLWebSiteButton;
   }

   if ( m_pHTMLLinkButton )
   {
      delete m_pHTMLLinkButton;
   }

   if ( m_pLivingLabel )
   {
      delete m_pLivingLabel;
   }

   m_pInstance = NULL;
}

DialogMyFriendsDetails::DialogMyFriendsDetails( DialogEvent *pStartCmd, QWidget *parent )
: FacebookDialog( pStartCmd, parent ), m_FriendId( (int)pStartCmd->Data() ),
  m_pNameLabel( NULL ), m_pBirthdayLabel( NULL ), m_pGenderLabel( NULL ),
  m_pWorkLabel( NULL ), m_pLivingLabel( NULL ),
  m_pHTMLLinkButton( NULL ), m_pHTMLWebSiteButton( NULL )
{
}

bool
DialogMyFriendsDetails::HandleUserEvent( const DialogEvent *pEvent )
{
   switch( pEvent->Cmd() )
   {
      case DialogEvent::DIALOG_CMD_UNKNOWN:
         break;
      case DialogEvent::DIALOG_CMD_DAILOG_STARTED:
      {
         connect( GetDialogManager()->GetNetworkManager(), SIGNAL( FacebookNetwokManagerFinished( FACEBOOK_REQUEST_T, const QByteArray& ) ),
                                                           SLOT( OnFacebookNetwokManagerFinished( FACEBOOK_REQUEST_T, const QByteArray& ) ) );
         RequestMyFriendsDetailsData();
         break;
     }
   }

   return true;
}

void
DialogMyFriendsDetails::RequestMyFriendsDetailsData()
{
   if ( GetDialogManager()->GetNetworkManager()->IsAuthorized() )
   {
      FacebookNetwokManager *pNetManager = GetDialogManager()->GetNetworkManager();
      QString request = QString( FACEBOOK_API_URL ) + QString::number( m_FriendId ) + QString( "?access_token=" ) + GetDialogManager()->GetNetworkManager()->GetTokenKey();

      pNetManager->Request( FACEBOOK_REQUEST_FRIEND_DATA, QUrl( request ) );
   }
}

void
DialogMyFriendsDetails::SetUI()
{
   FacebookDialog::SetUI();

   QBoxLayout *pMainLayout    = GetMainLayout();
   QHBoxLayout *pHLayoutMain  = new QHBoxLayout;
   QVBoxLayout *pVLayoutLeft  = new QVBoxLayout;
   QVBoxLayout *pVLayoutRight = new QVBoxLayout;

   m_pWebView = new QWebView();
   QString pictureUrl = QString( FACEBOOK_API_URL ) + QString::number( m_FriendId ) + "/picture";
   QString msg = QString( "<body LEFTMARGIN=\"0\" TOPMARGIN=\"0\" RIGHTMARGIN=\"0\" BOTTOMMARGIN=\"0\"><img src='%1?type=large' height='206' width='180' vspace='0' hspace='0' border='0'/></body>" ).arg( pictureUrl );

   m_pWebView->setContentsMargins( QMargins( 0, 0, 0, 0 ) );
   m_pWebView->setAutoFillBackground( true );
   m_pWebView->setContentsMargins( QMargins( 0, 0, 0, 0 ) );
   m_pWebView->setFixedSize( 180, 206 );
   m_pWebView->setEnabled( false );
   m_pWebView->setHtml( msg );

   pVLayoutLeft->addWidget( m_pWebView );
   pVLayoutLeft->addStretch();

   m_pNameLabel = new QLabel( tr( "<b>Name:</b> ") );
   m_pBirthdayLabel = new QLabel ( tr( "<b>Birthday:</b> " ) );
   m_pGenderLabel = new QLabel( tr( "<b>Gender:</b> " ) );
   m_pLivingLabel = new QLabel( tr( "<b>Living:</b> " ) );
   m_pWorkLabel = new QLabel( tr( "<b>Work:</b> " ) );
   m_pHTMLWebSiteButton = new HTMLButton( tr( "<b>WebSite:</b> " ) );
   m_pHTMLLinkButton = new HTMLButton( tr( "<b>Link:</b> " ) );

   connect( m_pHTMLWebSiteButton, SIGNAL( clicked() ), SLOT( OnWebLinkClicked() ) );
   connect( m_pHTMLLinkButton, SIGNAL( clicked() ), SLOT( OnProfileLinkClicked() ) );

   pVLayoutRight->addWidget( m_pNameLabel );
   pVLayoutRight->addWidget( m_pBirthdayLabel );
   pVLayoutRight->addWidget( m_pGenderLabel );
   pVLayoutRight->addWidget( m_pLivingLabel );
   pVLayoutRight->addWidget( m_pWorkLabel );
   pVLayoutRight->addWidget( m_pHTMLWebSiteButton );
   pVLayoutRight->addWidget( m_pHTMLLinkButton );
   pVLayoutRight->addStretch();

   pHLayoutMain->addLayout( pVLayoutLeft );
   pHLayoutMain->addLayout( pVLayoutRight );
   pMainLayout->addLayout( pHLayoutMain );
}

void
DialogMyFriendsDetails::OnFacebookNetwokManagerFinished( FACEBOOK_REQUEST_T aRequest, const QByteArray& aContent )
{
   if ( aRequest == FACEBOOK_REQUEST_FRIEND_DATA )
   {
      QJson::Parser parser;
      bool isOk = false;
      QVariantMap result = parser.parse( aContent, &isOk ).toMap();
      QString tmpStr;

      if ( !isOk )
      {
         GetDialogManager()->GetLogger().Log( "An error occured during parsing", FacebookLogger::PRIORITY_CRITICAL );
      }

      // NAME
      tmpStr = result[ "name" ].toString();

      if ( tmpStr.count() )
      {
         QString str = m_pNameLabel->text();
         str += tmpStr;
         m_pNameLabel->setText( str );
      }

      // BIRTHDAY
      tmpStr = result[ "birthday" ].toString();

      if ( tmpStr.count() )
      {
         QString str = m_pBirthdayLabel->text();
         str += tmpStr;
         m_pBirthdayLabel->setText( str );
      }

      // GENDER
      tmpStr = result[ "gender" ].toString();

      if ( tmpStr.count() )
      {
         QString str = m_pGenderLabel->text();
         str += tmpStr;
         m_pGenderLabel->setText( str );
      }

      // LOCATION
      QVariantMap location = result[ "location" ].toMap();
      tmpStr = location[ "name" ].toString();

      if ( tmpStr.count() )
      {
         QString str = m_pLivingLabel->text();
         str += tmpStr;
         m_pLivingLabel->setText( str );
      }

      // WORK
      foreach ( QVariant workList, result[ "work" ].toList() )
      {
         QVariantMap employerHistory = workList.toMap();
         QVariantMap employer = employerHistory[ "employer" ].toMap();

         tmpStr = employer[ "name" ].toString();

         if ( tmpStr.count() )
         {
            QString str = m_pWorkLabel->text();
            str += tmpStr;
            m_pWorkLabel->setText( str );
         }

         break;
      }

      // WEB
      tmpStr = result[ "website" ].toString();

      if ( tmpStr.count() )
      {
         QString str = m_pHTMLWebSiteButton->text();

         m_WebLinkUrl.setUrl( tmpStr, QUrl::TolerantMode );

         str += QString( "<a href=\"%1\" target=\"_blank\">%1</a>" ).arg( tmpStr );

         m_pHTMLWebSiteButton->setText( str );
      }

      // LINK
      tmpStr = result[ "link" ].toString();

      if ( tmpStr.count() )
      {
         QString str = m_pHTMLLinkButton->text();

         m_LinkToProfileUrl.setUrl( tmpStr, QUrl::TolerantMode );

         str += QString( "<a href=\"%1\" target=\"_blank\">%1</a>" ).arg( tmpStr );

         m_pHTMLLinkButton->setText( str );
      }
   }
}

void
DialogMyFriendsDetails::OnProfileLinkClicked()
{
   if ( !m_LinkToProfileUrl.isEmpty() )
   {
      QDesktopServices::openUrl( m_LinkToProfileUrl );
   }
}

void
DialogMyFriendsDetails::OnWebLinkClicked()
{
   if ( !m_WebLinkUrl.isEmpty() )
   {
      QDesktopServices::openUrl( m_WebLinkUrl );
   }
}
