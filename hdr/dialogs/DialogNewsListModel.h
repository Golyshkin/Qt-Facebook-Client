#ifndef DIALOGNEWSLISTMODEL_H
#define DIALOGNEWSLISTMODEL_H

#include <QAbstractListModel>
#include <QList>
#include <QStringList>

class DialogNewsListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    DialogNewsListModel(QObject *parent = 0);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    void AddNews( QString aTitle, QString aText );

private:
    QStringList News;
};

#endif // DIALOGNEWSLISTMODEL_H
