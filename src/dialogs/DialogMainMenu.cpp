#include <DialogMainMenu.h>
#include <QtGui>
#include <DialogEvent.h>

FacebookDialog *DialogMainMenu::m_pInstance = NULL;

FacebookDialog *
DialogMainMenu::Instance( DialogEvent *pStartCmd )
{
   if ( m_pInstance == NULL )
   {
      m_pInstance = new DialogMainMenu( pStartCmd );
   }

   return m_pInstance;
}

DialogMainMenu::~DialogMainMenu()
{
   if ( m_pBackButton )
   {
      delete m_pBackButton;
   }
   if ( m_pPhotoImage )
   {
       delete m_pPhotoImage;
   }
   if ( m_pUserInfo )
   {
       delete m_pUserInfo;
   }
   if ( m_pUserStatus )
   {
       delete m_pUserStatus;
   }
   for( int i=0; i<MAIN_MENU_OPTIONS_NUMBER;i++ )
   if ( m_pMMOptions[i] )
   {
       delete ( m_pMMOptions[i] );
   }

   m_pInstance = NULL;
}

DialogMainMenu::DialogMainMenu( DialogEvent *pStartCmd, QWidget *parent ) : FacebookDialog( pStartCmd, parent )
{
}


bool
DialogMainMenu::HandleUserEvent( const DialogEvent *pEvent )
{
   return true;
}

void
DialogMainMenu::SetUI()
{
   FacebookDialog::SetUI();

   m_pLabel = new QLabel( tr( "Main Menu " ) );

   QBoxLayout *pMainLayout = GetMainLayout();

   QHBoxLayout *pMainMenuLayout = new QHBoxLayout;
   QVBoxLayout *pUserInfoLayout = new QVBoxLayout;
   QGridLayout *pMainMenuIconsLayout =new QGridLayout;

   m_pSignalMapper = new QSignalMapper(this);
   m_pPhotoImage = new QLabel();
   QPixmap *pPhoto = new QPixmap(USER_PHOTO_WIDTH,USER_PHOTO_HEIGHT);
   m_pPhotoImage->setPixmap(*pPhoto);
   m_pUserInfo = new QLabel(tr("Golyshkin Alexander"));
   m_pUserStatus =new QLabel(tr("I'm very Happy!!!"));


   int xpos=0, ypos=0;

   for(int i=0; i<MAIN_MENU_OPTIONS_NUMBER; i++)
   {
      m_pMMOptions[i]=new QPushButton();
      switch (i)
      {
      case Profile: m_pMMOptions[i]->setIcon( QIcon(":images/mainmenu/profile.png") );
          break;
      case Friends: m_pMMOptions[i]->setIcon( QIcon(":images/mainmenu/friends.png") );
          break;
      case News: m_pMMOptions[i]->setIcon( QIcon(":images/mainmenu/news.png") );
          break;
      case Messages: m_pMMOptions[i]->setIcon( QIcon(":images/mainmenu/messages.png") );
          break;
      case Groups: m_pMMOptions[i]->setIcon( QIcon(":images/mainmenu/groups.png") );
          break;
      case Events: m_pMMOptions[i]->setIcon( QIcon(":images/mainmenu/events.png") );
          break;
      case Photos: m_pMMOptions[i]->setIcon( QIcon(":images/mainmenu/photos.png") );
          break;
      case About:  m_pMMOptions[i]->setIcon( QIcon(":images/mainmenu/information.png") );
          break;
      case AboutQT: m_pMMOptions[i]->setIcon( QIcon(":images/mainmenu/aboutQT.png") );
          break;
      default:
          break;
      }
      connect(m_pMMOptions[i], SIGNAL(clicked()), m_pSignalMapper, SLOT(map()));
      m_pSignalMapper->setMapping(m_pMMOptions[i],i );

      m_pMMOptions[i]->setFlat(true);
      m_pMMOptions[i]->setContentsMargins ( QMargins( 0, 0, 0, 0 ) );
      m_pMMOptions[i]->setIconSize( QSize( 100, 100 ) );
      pMainMenuIconsLayout->addWidget(m_pMMOptions[i], xpos,ypos );
      ypos++;
      if(ypos>MAX_GRID_ROW-1)
      {
          ypos=0;
          xpos++;
      }
   }

   connect(m_pSignalMapper, SIGNAL(mapped(int)),this, SLOT(OnOptionsClick(int)));

   pUserInfoLayout->addWidget( m_pPhotoImage);
   pUserInfoLayout->addWidget( m_pUserInfo );
   pUserInfoLayout->addWidget( m_pUserStatus );
   pUserInfoLayout->addStretch( 1 );



   pMainMenuLayout->addLayout( pUserInfoLayout );
   pMainMenuLayout->addLayout(pMainMenuIconsLayout);

   pMainLayout->addLayout(pMainMenuLayout);
}

void
DialogMainMenu::OnBackClick()
{
   m_pDialogManager->PopDialog();
}

void
DialogMainMenu::OnOptionsClick(int option)
{
    switch ( (MAIN_MENU_OPTIONS_T)option )
    {
    case Profile:
        break;
    case Friends: GetDialogManager()->PushDialog( DIALOG_MYFRIENDS );
        break;
    case News:
    case Messages:
    case Groups:
    case Events:
    case Photos:
    case About:
        break;
    case AboutQT: qApp->aboutQt();
        break;
    }
option =-1;

}
