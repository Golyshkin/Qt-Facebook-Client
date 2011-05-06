#include <dialoglogin.h>
#include <FacebookNetwokManager.h>
#include <QtGui>
#include <DialogEvent.h>
#include <QSplashScreen>
#include <ThreadSleep.h>
#include <QWebView>
#include <QWidgetItem>
#include <QBoxLayout>
#include <QWebFrame>

FacebookDialog *DialogLogin::m_pInstance = NULL;

FacebookDialog *
DialogLogin::Instance( DialogEvent *pStartCmd )
{
   if ( m_pInstance == NULL )
   {
      m_pInstance = new DialogLogin( pStartCmd );
   }

   return m_pInstance;
}

DialogLogin::~DialogLogin()
{
   if ( m_pWebView )
   {
      delete m_pWebView;
   }

   if ( m_pSplashScreen )
   {
      delete m_pSplashScreen;
   }

   m_pInstance = NULL;
}

DialogLogin::DialogLogin( DialogEvent *pStartCmd, QWidget *parent)
: FacebookDialog( pStartCmd, parent ), m_pSplashScreen( NULL ), m_pWebView( NULL )
{
}

bool
DialogLogin::HandleUserEvent( const DialogEvent *pEvent )
{
   return true;
}

void
DialogLogin::SetUI()
{
   FacebookDialog::SetUI();

   QBoxLayout *pMainLayout = GetMainLayout();
   m_pWebView = new QWebView();

   // Enables linkClicked SIGNAL
   //m_pWebView->page()->setLinkDelegationPolicy( QWebPage::DelegateAllLinks );
   m_pWebView->page()->setNetworkAccessManager( GetDialogManager()->GetNetworkManager() );

   connect( GetDialogManager()->GetNetworkManager(), SIGNAL( FacebookNetwokManagerRequestStatus( FACEBOOK_REQUEST_T ) ),
                                                     SLOT( OnFaceBookNetwokManagerStatusChanged( FACEBOOK_REQUEST_T ) ) );

   connect( m_pWebView, SIGNAL( loadFinished(bool) ),         SLOT( OnWebViewLoadFinished() ) );
   connect( m_pWebView, SIGNAL( loadProgress(int) ),          SLOT( OnWebViewLoadProgress(int) ) );
   connect( m_pWebView, SIGNAL( linkClicked( const QUrl& ) ), SLOT( OnWebViewLinkClicked( const QUrl& ) ) );

   pMainLayout->addWidget( m_pWebView );

   QPixmap splashPicture( ":images/splashscreen/splash.png" );

   m_pSplashScreen = new QSplashScreen( splashPicture );
   m_pSplashScreen->setMask( splashPicture.mask() );
   m_pSplashScreen->show();

   m_pSplashScreen->showMessage( QObject::tr( "Configuring Network...   " ), Qt::AlignRight | Qt::AlignTop, Qt::white );
   SleeperThread::msleep( 1000 );

   QString baseAuthorizeUrl = "https://www.facebook.com/dialog/oauth";
   QString authURL = baseAuthorizeUrl  + "?"
                                       + "client_id=" + APPLICATION_ID
                                       + "&redirect_uri=http://www.facebook.com/connect/login_success.html&"
                                       + "type=user_agent&"
                                       + "display=popup&"
                                       + "scope=user_photos,user_videos,"
                                       + "user_activities,user_groups,user_interests,"
                                       + "user_likes,user_notes,user_online_presence,"
                                       + "user_status,read_friendlists,read_requests,"
                                       + "offline_access,friends_activities,friends_events,friends_groups,friends_likes,friends_notes,"
                                       + "friends_birthday,friends_online_presence,friends_location,friends_website,friends_work_history,"
                                       + "friends_online_presence,publish_stream,read_mailbox,read_stream";


   GetDialogManager()->GetNetworkManager()->SetRequestType( FACEBOOK_REQUEST_TOKEN_DATA );
   m_pWebView->load( authURL );
}

void
DialogLogin::OnFaceBookNetwokManagerStatusChanged( FACEBOOK_REQUEST_T aState )
{
   QString msg( "DialogLogin::OnFaceBookNetwokManagerStatusChanged = [%1]" );
   msg = msg.arg( aState);

   GetDialogManager()->GetLogger().Log( msg );
}

void
DialogLogin::OnWebViewLoadFinished()
{
   if ( m_pSplashScreen->isVisible() )
   {
      // JUST FOR SERGEY VETIUGOV REQIEST 8) - In Release version should be removed
      QString emailEditField = "document.all.email.value='Alexander.Golyshkin@gmail.com'";
      QString passEditField  = "document.all.pass.focus()";
      m_pWebView->page()->mainFrame()->evaluateJavaScript( emailEditField );
      m_pWebView->page()->mainFrame()->evaluateJavaScript( passEditField );
      // END REMOVE

      m_pSplashScreen->close();
      show();
   }
   else
   {
      if ( GetDialogManager()->GetNetworkManager()->IsAuthorized() == true )
      {
         GetDialogManager()->GetLogger().Log( "DialogLogin::User Authorized, Going to MainMenu" );

         disconnect();
         GetDialogManager()->ReplaceDialog( DIALOG_MAINMENU );
      }
   }
}

void
DialogLogin::OnWebViewLoadProgress( int aProgressState )
{
   m_pSplashScreen->showMessage( QObject::tr( QString( "Loading in Progress - [%1%]   " ).arg( aProgressState ).toAscii() ), Qt::AlignRight | Qt::AlignTop, Qt::white );
}

void
DialogLogin::OnWebViewLinkClicked( const QUrl& aURL )
{
   GetDialogManager()->GetLogger().Log( "DialogLogin::OnWebViewLinkClicked" );
   m_pWebView->load( aURL );
   GetDialogManager()->GetNetworkManager()->Request( FACEBOOK_REQUEST_TOKEN_DATA, aURL );
}
