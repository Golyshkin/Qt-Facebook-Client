#include <QtGui>

#include <DialogMyFriends.h>
#include <DialogEvent.h>
#include <FacebookNetwokManager.h>
#include <DialogMyFriendsTableModel.h>
#include <parser.h>

FacebookDialog *DialogMyFriends::m_pInstance = NULL;

FacebookDialog *
DialogMyFriends::Instance( DialogEvent *pStartCmd )
{
   if ( m_pInstance == NULL )
   {
      m_pInstance = new DialogMyFriends( pStartCmd );
   }

   return m_pInstance;
}

DialogMyFriends::~DialogMyFriends()
{
   m_pInstance = NULL;
}

DialogMyFriends::DialogMyFriends( DialogEvent *pStartCmd, QWidget *parent ) : FacebookDialog( pStartCmd, parent )
{
}

bool
DialogMyFriends::HandleUserEvent( const DialogEvent *pEvent )
{
   switch( pEvent->Cmd() )
   {
      case DialogEvent::DIALOG_CMD_UNKNOWN:
         break;
      case DialogEvent::DIALOG_CMD_DAILOG_STARTED:
         RequestMyFriendsData();
         break;
   }

   return true;
}

void
DialogMyFriends::RequestMyFriendsData()
{
   if ( GetDialogManager()->GetNetworkManager()->IsAuthorized() )
   {
      FacebookNetwokManager *pNetManager = GetDialogManager()->GetNetworkManager();
      QString request( FACEBOOK_API_URL );

      request += "me/friends?access_token=";
      request += GetDialogManager()->GetNetworkManager()->GetTokenKey();

      connect( pNetManager, SIGNAL( FacebookNetwokManagerFinished( FACEBOOK_REQUEST_T, const QByteArray& ) ),
                            SLOT( OnFacebookNetwokManagerFinished( FACEBOOK_REQUEST_T, const QByteArray& ) ) );

      GetDialogManager()->GetNetworkManager()->Request( FACEBOOK_REQUEST_MYFRIENDS_DATA, QUrl( request ) );
   }
}

void
DialogMyFriends::SetUI()
{
   FacebookDialog::SetUI();

   QBoxLayout *pMainLayout = GetMainLayout();

   m_pTableModel = new DialogMyFriendsTableModel( this );

   QSortFilterProxyModel *pProxyModel = new QSortFilterProxyModel( this );
   pProxyModel->setSourceModel( m_pTableModel );

   QTableView *pTableView = new QTableView();

   pTableView->setModel( pProxyModel );
   pTableView->setSortingEnabled( true );
   pTableView->setSelectionBehavior( QAbstractItemView::SelectRows );
   pTableView->horizontalHeader()->setStretchLastSection( true );
   pTableView->verticalHeader()->hide();
   pTableView->setEditTriggers( QAbstractItemView::NoEditTriggers );
   pTableView->setSelectionMode( QAbstractItemView::SingleSelection );
   pTableView->verticalHeader()->setDefaultSectionSize( 60 );

   pProxyModel->setFilterKeyColumn( 0 );
   pProxyModel->sort( 0, Qt::AscendingOrder );

   connect( pTableView->selectionModel(), SIGNAL( selectionChanged( const QItemSelection &, const QItemSelection & ) ),
                                    this, SIGNAL( selectionChanged( const QItemSelection & ) ) );

   connect( pTableView, SIGNAL( pressed(const QModelIndex &) ), SLOT( OnItemClicked(const QModelIndex &) ) );
   connect( pTableView, SIGNAL( activated(const QModelIndex &) ), SLOT( OnItemClicked(const QModelIndex &) ) );
   connect( pTableView, SIGNAL( clicked(const QModelIndex &) ), SLOT( OnItemClicked(const QModelIndex &) ) );
   connect( pTableView, SIGNAL( doubleClicked(const QModelIndex &) ), SLOT( OnItemClicked(const QModelIndex &) ) );

   pMainLayout->addWidget( pTableView );
   pTableView->setFocus();
}

void
DialogMyFriends::OnFacebookNetwokManagerFinished( FACEBOOK_REQUEST_T aRequest, const QByteArray& aContent )
{
   QJson::Parser parser;
   bool isOk = false;
   QVariantMap result = parser.parse( aContent, &isOk ).toMap();

   if ( !isOk )
   {
      GetDialogManager()->GetLogger().Log( "An error occured during parsing", FacebookLogger::PRIORITY_HI );
   }

   foreach ( QVariant friendsData, result[ "data" ].toList() )
   {
      QVariantMap friendData = friendsData.toMap();

      m_pTableModel->AddFriend( friendData[ "name" ].toString(), friendData[ "id" ].toInt() );
   }

   disconnect( SIGNAL( FacebookNetwokManagerFinished( FACEBOOK_REQUEST_T, QString ) ) );
}

void
DialogMyFriends::OnItemClicked( const QModelIndex &aItemIndex )
{
   int friendId = m_pTableModel->getFriendsList().at( aItemIndex.row() ).second;
   DialogEvent startCmd( DialogEvent::DIALOG_CMD_FRIEND_ID, (void *)friendId );

   GetDialogManager()->PushDialog( DIALOG_MYFRIENDS_DETAILS, &startCmd );
}
