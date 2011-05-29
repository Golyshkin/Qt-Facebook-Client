#include <QtGui>

#include <DialogNews.h>
#include <DialogEvent.h>
#include <FacebookNetwokManager.h>
#include <DialogNewsListModel.h>
#include <parser.h>

FacebookDialog *DialogNews::m_pInstance = NULL;

FacebookDialog *
DialogNews::Instance( DialogEvent *pStartCmd )
{
   if ( m_pInstance == NULL )
   {
      m_pInstance = new DialogNews( pStartCmd );
   }

   return m_pInstance;
}

DialogNews::~DialogNews()
{
   m_pInstance = NULL;
}

DialogNews::DialogNews( DialogEvent *pStartCmd, QWidget *parent ) : FacebookDialog( pStartCmd, parent )
{
}

bool
DialogNews::HandleUserEvent( const DialogEvent *pEvent )
{
   switch( pEvent->Cmd() )
   {
      case DialogEvent::DIALOG_CMD_UNKNOWN:
         break;
      case DialogEvent::DIALOG_CMD_DAILOG_STARTED:
         RequestNewsData();
         break;
   }

   return true;
}

void
DialogNews::RequestNewsData()
{
   if ( GetDialogManager()->GetNetworkManager()->IsAuthorized() )
   {
      FacebookNetwokManager *pNetManager = GetDialogManager()->GetNetworkManager();
      QString request( FACEBOOK_API_URL );

      request += "/me/home?access_token=";
      request += GetDialogManager()->GetNetworkManager()->GetTokenKey();

      connect( pNetManager, SIGNAL( FacebookNetwokManagerFinished( FACEBOOK_REQUEST_T, QByteArray ) ),
                            SLOT( OnFacebookNetwokManagerFinished( FACEBOOK_REQUEST_T, QByteArray ) ) );

      GetDialogManager()->GetNetworkManager()->Request( FACEBOOK_REQUEST_MYFRIENDS_DATA, QUrl( request ) );
   }
}

void
DialogNews::SetUI()
{
   FacebookDialog::SetUI();

   QBoxLayout *pMainLayout = GetMainLayout();

   QListView *pListView = new QListView();

   m_pListModel = new DialogNewsListModel(this);

   pListView->setModel(m_pListModel);
   pListView->setWordWrap(true);

   pMainLayout->addWidget(pListView);
}

void
DialogNews::OnFacebookNetwokManagerFinished( FACEBOOK_REQUEST_T aRequest, QByteArray aContent )
{
   QJson::Parser parser;
   bool isOk = false;
   QVariantMap result = parser.parse( aContent, &isOk ).toMap();

   if ( !isOk )
   {
      qFatal( tr( "An error occured during parsing" ).toAscii() );
   }

   foreach ( QVariant NewsData, result["data"].toList() )
   {
      QVariantMap NewsBlock = NewsData.toMap();
      //QVariantMap nestedMap = NewsBlock["from"].toMap();
      m_pListModel->AddNews(NewsBlock["name"].toString(), NewsBlock["description"].toString());
   }

   disconnect( SIGNAL( FacebookNetwokManagerFinished( FACEBOOK_REQUEST_T, QString ) ) );
}
