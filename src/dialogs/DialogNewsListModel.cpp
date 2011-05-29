#include <DialogNewsListModel.h>
#include <QModelIndex>
#include <QFont>

DialogNewsListModel::DialogNewsListModel( QObject *parent )
: QAbstractListModel( parent )
{

}

int
DialogNewsListModel::rowCount( const QModelIndex &parent ) const
{
   return News.size();
}

QVariant
DialogNewsListModel::data( const QModelIndex &index, int role ) const
{
   switch( role )
   {
      case Qt::DisplayRole:
         return News.at(index.row()); //.at( row ).first;
    /*  case Qt::DecorationRole:
         return QPixmap( ":images/myfriends/face.png" );*/
      case Qt::FontRole:
         return QFont( "Verdana", 10 );
   }

   return QVariant();
}

void
DialogNewsListModel::AddNews( QString aTitle, QString aText )
{
    beginInsertRows(QModelIndex(), News.size(), News.size());
    News.append((QString::QString(aTitle + "\n\n" + aText + "\n\n")));
    endInsertRows();
}
