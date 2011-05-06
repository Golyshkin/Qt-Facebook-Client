#include <QtGui>

#include <DialogGroups.h>
#include <DialogEvent.h>
#include <FacebookNetwokManager.h>
#include <DialogGroupsTableModel.h>
#include <parser.h>

FacebookDialog *DialogGroups::m_pInstance = NULL;

FacebookDialog *
DialogGroups::Instance( DialogEvent *pStartCmd )
{
   if ( m_pInstance == NULL )
   {
      m_pInstance = new DialogGroups( pStartCmd );
   }

   return m_pInstance;
}

DialogGroups::~DialogGroups()
{
   m_pInstance = NULL;
}

DialogGroups::DialogGroups( DialogEvent *pStartCmd, QWidget *parent ) : FacebookDialog( pStartCmd, parent )
{
}

bool
DialogGroups::HandleUserEvent( const DialogEvent *pEvent )
{
   switch( pEvent->Cmd() )
   {
      case DialogEvent::DIALOG_CMD_UNKNOWN:
         break;
      case DialogEvent::DIALOG_CMD_DAILOG_STARTED:
         RequestGroupsData();
         break;
   }

   return true;
}

void
DialogGroups::RequestGroupsData()
{
   if ( GetDialogManager()->GetNetworkManager()->IsAuthorized() )
   {
      FacebookNetwokManager *pNetManager = GetDialogManager()->GetNetworkManager();
      QString request( FACEBOOK_API_URL );

      request += "/me/groups?access_token=";
      request += GetDialogManager()->GetNetworkManager()->GetTokenKey();

      connect( pNetManager, SIGNAL( FacebookNetwokManagerFinished( FACEBOOK_REQUEST_T, const QByteArray& ) ),
                            SLOT( OnFacebookNetwokManagerFinished( FACEBOOK_REQUEST_T, const QByteArray& ) ) );

      GetDialogManager()->GetNetworkManager()->Request( FACEBOOK_REQUEST_GROUPS_DATA, QUrl( request ) );
   }
}

void
DialogGroups::SetUI()
{
   FacebookDialog::SetUI();

   QBoxLayout *pMainLayout = GetMainLayout();

   m_pTableModel = new DialogGroupsTableModel( this );

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
   connect( pTableView, SIGNAL( sortByColumn(int) ), SLOT( OnSortClicked( int ) ) );

   pMainLayout->addWidget( pTableView );
}

void
DialogGroups::OnBackClick()
{
   m_pDialogManager->PopDialog();
}

void
DialogGroups::OnFacebookNetwokManagerFinished( FACEBOOK_REQUEST_T aRequest, QByteArray aContent )
{
   QJson::Parser parser;
   bool isOk = false;
   QVariantMap result = parser.parse( aContent, &isOk ).toMap();

   if ( !isOk )
   {
      GetDialogManager()->GetLogger().Log( "An error occured during parsing", FacebookLogger::PRIORITY_HI );
   }

   foreach ( QVariant groupsData, result[ "data" ].toList() )
   {
      QVariantMap groupData = groupsData.toMap();

      m_pTableModel->AddGroup( groupData[ "name" ].toString(), groupData[ "id" ].toInt() );
   }

   disconnect( GetDialogManager()->GetNetworkManager(), SIGNAL( FacebookNetwokManagerFinished( FACEBOOK_REQUEST_T, QString ) ) );
}

void
DialogGroups::OnSortClicked( int aColumn )
{
   Q_UNUSED( aColumn );

   m_pTableModel->UpdateTableContent();
}
