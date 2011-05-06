///////////////////////////////////////////////////////////
//  TelecaFacebookDialog.cpp
//  Implementation of the Class TelecaFacebookDialog
//  Created on:      26-Apr-2011 9:24:49 AM
//  Original author: Golyshkin A.
///////////////////////////////////////////////////////////

#include <QtGui>
#include <FacebookDialog.h>
#include <DialogManager.h>

FacebookDialog::FacebookDialog( DialogEvent *pStartCmd, QWidget *parent )
: QDialog( parent ), m_pBackButton( NULL ), m_pHomeButton( NULL ), m_pHLine( NULL ), m_pMainLayout( NULL ) {}

FacebookDialog::~FacebookDialog()
{
   if ( m_pBackButton )
   {
      delete m_pBackButton;
   }

   if ( m_pHomeButton )
   {
      delete m_pHomeButton;
   }

   if ( m_pHLine )
   {
      delete m_pHLine;
   }
}

void
FacebookDialog::SetUI()
{
   QRect deskSize = QApplication::desktop()->geometry();

   setAttribute( Qt::WA_DeleteOnClose, true );

   setWindowFlags( Qt::WindowSystemMenuHint );

   setWindowTitle( tr( "Teleca Facebook Client (c) 2011" ) );
   setWindowOpacity( DialogManager::DIALOG_OPASITY / 100 );

   setFixedSize( FACEBOOK_DIALOG_WIDTH, FACEBOOK_DIALOG_HEIGH );
   setGeometry( ( deskSize.width() - FACEBOOK_DIALOG_WIDTH ) / 2, ( deskSize.height() - FACEBOOK_DIALOG_HEIGH ) / 2, FACEBOOK_DIALOG_HEIGH, FACEBOOK_DIALOG_WIDTH );

   m_pMainLayout = new QVBoxLayout( this );
   m_pMainLayout->setContentsMargins ( QMargins( 0, 0, 0, 0 ) );

   if ( Id() != DIALOG_LOGIN && Id() != DIALOG_MAINMENU )
   {
      m_pBackButton = new QPushButton( "Back" );
      m_pBackButton->setIcon( QIcon( ":images/common/back.png" ) );
      m_pBackButton->setFlat( true );
      m_pBackButton->setContentsMargins ( QMargins( 0, 0, 0, 0 ) );
      m_pBackButton->setIconSize( QSize( 40, 40 ) );

      connect( m_pBackButton, SIGNAL( clicked() ), this, SLOT( OnBackClick() ) );

      m_pHomeButton = new QPushButton( "Home" );
      m_pHomeButton->setIcon( QIcon( ":images/common/home.png" ) );
      m_pHomeButton->setFlat( true );
      m_pHomeButton->setContentsMargins ( QMargins( 0, 0, 0, 0 ) );
      m_pHomeButton->setIconSize( QSize( 40, 40 ) );

      connect( m_pHomeButton, SIGNAL( clicked() ), SLOT( OnMainMenuClick() ) );

      QHBoxLayout *pHLayout = new QHBoxLayout;

      pHLayout->addStretch( 1 );
      pHLayout->addWidget( m_pHomeButton );
      pHLayout->addWidget( m_pBackButton );

      m_pMainLayout->addLayout( pHLayout );

      m_pHLine = new QFrame;
      m_pHLine->setFrameShape( QFrame::HLine );
      m_pHLine->setFrameShadow( QFrame::Sunken );
      m_pMainLayout->addWidget( m_pHLine );
   }

   setLayout( m_pMainLayout );
}
