#include <DialogGroupsDetails.h>


#include <QtGui>
#include <QHttp>
#include <QNetworkProxy>
#include <QWebView>
#include <parser.h>

#include <DialogGroups.h>
#include <DialogEvent.h>
#include <FacebookNetwokManager.h>
#include <DialogGroupsTableModel.h>
#include <HTMLButton.h>

FacebookDialog *DialogGroupsDetails::m_pInstance = NULL;

FacebookDialog *
DialogGroupsDetails::Instance( DialogEvent *pStartCmd )
{
   if ( m_pInstance == NULL )
   {
      m_pInstance = new DialogGroupsDetails( pStartCmd );
   }

   return m_pInstance;
}

DialogGroupsDetails::~DialogGroupsDetails()
{
   if ( m_pNameLabel )
   {
      delete m_pNameLabel;
   }
   if ( m_pLbl )
   {
      delete m_pLbl;
   }
   m_pInstance = NULL;
}

DialogGroupsDetails::DialogGroupsDetails( DialogEvent *pStartCmd, QWidget *parent )
: FacebookDialog( pStartCmd, parent ), m_GroupId( (int)pStartCmd->Data() ),
  m_pNameLabel( NULL )
{
}

bool
DialogGroupsDetails::HandleUserEvent( const DialogEvent *pEvent )
{
   switch( pEvent->Cmd() )
   {
      case DialogEvent::DIALOG_CMD_UNKNOWN:
         break;
      case DialogEvent::DIALOG_CMD_DAILOG_STARTED:
      {
         connect( GetDialogManager()->GetNetworkManager(), SIGNAL( FacebookNetwokManagerFinished( FACEBOOK_REQUEST_T, const QByteArray& ) ),
                                                           SLOT( OnFacebookNetwokManagerFinished( FACEBOOK_REQUEST_T, const QByteArray& ) ) );
         RequestGroupsDetailsData();
         break;
     }
   }

   return true;
}

void
DialogGroupsDetails::RequestGroupsDetailsData()
{
   if ( GetDialogManager()->GetNetworkManager()->IsAuthorized() )
   {
      FacebookNetwokManager *pNetManager = GetDialogManager()->GetNetworkManager();
      QString request = QString( FACEBOOK_API_URL ) + QString::number( m_GroupId ) + QString( "?access_token=" ) + GetDialogManager()->GetNetworkManager()->GetTokenKey();

      pNetManager->Request( FACEBOOK_REQUEST_GROUP_DETAILS, QUrl( request ) );
   }
}

void
DialogGroupsDetails::SetUI()
{
   FacebookDialog::SetUI();

   QBoxLayout *pMainLayout = GetMainLayout();
   QHBoxLayout *pHLayoutMain  = new QHBoxLayout;
   QVBoxLayout *pVLayoutLeft  = new QVBoxLayout;
   QVBoxLayout *pVLayoutRight = new QVBoxLayout;

   QPixmap image( ":images/mainmenu/groups.png" );
   m_pLbl = new QLabel();
   m_pLbl->setPixmap(image);

   pVLayoutLeft->addWidget(m_pLbl);
   pVLayoutLeft->addStretch();

   m_pNameLabel = new QLabel( tr( "<b>Name:</b> ") );

   pVLayoutRight->addWidget( m_pNameLabel );
   pVLayoutRight->addStretch();

   pHLayoutMain->addLayout( pVLayoutLeft );
   pHLayoutMain->addLayout( pVLayoutRight );
   pMainLayout->addLayout( pHLayoutMain );
}

void
DialogGroupsDetails::OnFacebookNetwokManagerFinished( FACEBOOK_REQUEST_T aRequest, const QByteArray& aContent )
{
   if ( aRequest == FACEBOOK_REQUEST_GROUP_DETAILS )
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
   }
}
