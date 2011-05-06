#ifndef DIALOG_MY_FRIENDS_TABLE_MODEL_H
#define DIALOG_MY_FRIENDS_TABLE_MODEL_H

#include <QAbstractTableModel>
#include <QList>
#include <QString>
#include <QPair>

 class DialogMyFriendsTableModel : public QAbstractTableModel
 {
     Q_OBJECT

 public:

     DialogMyFriendsTableModel( QObject *parent = NULL );

     DialogMyFriendsTableModel( const QList< QPair< QString, int > > & aFriendsList, QObject *parent = NULL );

     virtual int rowCount( const QModelIndex &parent ) const;
     
     virtual int columnCount( const QModelIndex &parent ) const;
     
     virtual QVariant data( const QModelIndex &index, int role ) const;
     
     virtual QVariant headerData( int section, Qt::Orientation orientation, int role ) const;
     
     virtual Qt::ItemFlags flags( const QModelIndex &index ) const;

     void AddFriend( QString aName, int aId );

     void UpdateTableContent();
     
     const QList< QPair< QString, int > > & getFriendsList();

 private:
     
     QList< QPair< QString, int > > m_ListOfFriends;
 };

 #endif
