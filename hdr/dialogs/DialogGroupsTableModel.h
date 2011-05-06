#ifndef DIALOGGROUPSTABLEMODEL_H
#define DIALOGGROUPSTABLEMODEL_H

#include <QAbstractTableModel>
#include <QList>
#include <QString>
#include <QPair>

 class DialogGroupsTableModel : public QAbstractTableModel
 {
     Q_OBJECT

 public:

     DialogGroupsTableModel( QObject *parent = NULL );

     DialogGroupsTableModel( const QList< QPair< QString, int > > & aGroupsList, QObject *parent = NULL );

     virtual int rowCount( const QModelIndex &parent ) const;

     virtual int columnCount( const QModelIndex &parent ) const;

     virtual QVariant data( const QModelIndex &index, int role ) const;

     virtual QVariant headerData( int section, Qt::Orientation orientation, int role ) const;

     virtual Qt::ItemFlags flags( const QModelIndex &index ) const;

     void AddGroup( QString aName, int aId );

     void UpdateTableContent();

     const QList< QPair< QString, int > > & getGroupsList();

 private:

     QList< QPair< QString, int > > m_ListOfGroups;
 };

#endif // DIALOGGROUPSTABLEMODEL_H
