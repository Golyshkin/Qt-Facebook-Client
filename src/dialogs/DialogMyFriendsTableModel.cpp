#include <DialogMyFriendsTableModel.h>
#include <QBrush>
#include <QFont>
#include <QModelIndex>

DialogMyFriendsTableModel::DialogMyFriendsTableModel( QObject *parent )
: QAbstractTableModel( parent )
{

}

DialogMyFriendsTableModel::DialogMyFriendsTableModel( const QList< QPair< QString, int > > & aFriendsList, QObject *parent )
: QAbstractTableModel( parent )
{

}

int 
DialogMyFriendsTableModel::rowCount( const QModelIndex &parent ) const
{
   return m_ListOfFriends.count();
}

int 
DialogMyFriendsTableModel::columnCount( const QModelIndex &parent ) const
{
   return 1;
}

QVariant 
DialogMyFriendsTableModel::data( const QModelIndex &index, int role ) const
{
   int row = index.row();
//   int col = index.column();

   switch( role )
   {
      case Qt::DisplayRole:
         return m_ListOfFriends.at( row ).first;
      case Qt::DecorationRole:
         return QPixmap( ":images/myfriends/face.png" );
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
DialogMyFriendsTableModel::headerData( int section, Qt::Orientation orientation, int role ) const
{
   if ( role == Qt::DisplayRole )
   {
      if ( orientation == Qt::Horizontal )
      {
         switch ( section )
         {
            case 0:
               break;
               //return QString( tr( "My Friends..." ) );
            default:
               break;
         }
      }
   }

   return QVariant();
}

Qt::ItemFlags 
DialogMyFriendsTableModel::flags( const QModelIndex &index ) const
{
   return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

const QList< QPair< QString, int > > &
DialogMyFriendsTableModel::getFriendsList()
{
   return m_ListOfFriends;
}

void
DialogMyFriendsTableModel::AddFriend( QString aName, int aId )
{
   QModelIndex index = this->index( m_ListOfFriends.count(), 0 );

   beginInsertRows( index, m_ListOfFriends.count(), m_ListOfFriends.count() );

   m_ListOfFriends.append( QPair< QString, int >( aName, aId ) );

   endInsertRows();
}

void
DialogMyFriendsTableModel::UpdateTableContent()
{
   // Let know TableView about changed table model
   QModelIndex startIndex = index( 0, 0, QModelIndex() );
   QModelIndex endIndex = index( m_ListOfFriends.count(), 0, QModelIndex() );

   emit( dataChanged( startIndex, endIndex ) );
}
