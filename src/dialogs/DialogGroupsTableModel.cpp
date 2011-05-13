#include <DialogGroupsTableModel.h>
#include <QBrush>
#include <QFont>
#include <QModelIndex>

DialogGroupsTableModel::DialogGroupsTableModel( QObject *parent )
: QAbstractTableModel( parent )
{

}

DialogGroupsTableModel::DialogGroupsTableModel( const QList< QPair< QString, int > > & aGroupsList, QObject *parent )
: QAbstractTableModel( parent )
{

}

int
DialogGroupsTableModel::rowCount( const QModelIndex &parent ) const
{
   return m_ListOfGroups.count();
}

int
DialogGroupsTableModel::columnCount( const QModelIndex &parent ) const
{
   return 1;
}

QVariant
DialogGroupsTableModel::data( const QModelIndex &index, int role ) const
{
   int row = index.row();
//   int col = index.column();

   switch( role )
   {
      case Qt::DisplayRole:
         return m_ListOfGroups.at( row ).first;
      case Qt::DecorationRole:
         return QPixmap( ":images/mainmenu/groups.png" );
      case Qt::FontRole:
         return QFont( "Verdana", 14 );
      case Qt::BackgroundRole:
      {
         if ( row % 2 )
         {
            return QBrush( QColor( 235, 235, 235 ) );
         }
         else
         {
            return QBrush( QColor( 255, 255, 255 ) );
         }
      }
   }

   return QVariant();
}

QVariant
DialogGroupsTableModel::headerData( int section, Qt::Orientation orientation, int role ) const
{
   if ( role == Qt::DisplayRole )
   {
      if ( orientation == Qt::Horizontal )
      {
         switch ( section )
         {
            case 0:
               break;
               //return QString( tr( "Groups..." ) );
            default:
               break;
         }
      }
   }

   return QVariant();
}

Qt::ItemFlags
DialogGroupsTableModel::flags( const QModelIndex &index ) const
{
   return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

const QList< QPair< QString, int > > &
DialogGroupsTableModel::getGroupsList()
{
   return m_ListOfGroups;
}

void
DialogGroupsTableModel::AddGroup( QString aName, int aId )
{
   QModelIndex index = this->index( m_ListOfGroups.count(), 0 );

   beginInsertRows( index, m_ListOfGroups.count(), m_ListOfGroups.count() );

   m_ListOfGroups.append( QPair< QString, int >( aName, aId ) );

   endInsertRows();
}

void
DialogGroupsTableModel::UpdateTableContent()
{
   // Let know TableView about changed table model
   QModelIndex startIndex = index( 0, 0, QModelIndex() );
   QModelIndex endIndex = index( m_ListOfGroups.count(), 0, QModelIndex() );

   emit( dataChanged( startIndex, endIndex ) );
}
