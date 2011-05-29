#ifndef DIALOG_GROUPS_H
#define DIALOG_GROUPS_H

#include <QModelIndex>

#include <FacebookDialog.h>
#include <FacebookNetwokClient_def.h>

class QPushButton;
class QLabel;
class DialogGroupsTableModel;

class DialogGroups : public FacebookDialog
{
    Q_OBJECT

public:
    DialogGroups(DialogEvent *pStartCmd = NULL, QWidget *parent = 0 );
    ~DialogGroups();

    virtual void SetUI();

    virtual bool HandleUserEvent( const DialogEvent *pEvent );

    virtual DIALOGS_ID_T Id() const { return DIALOG_GROUPS; }

    static FacebookDialog * Instance( DialogEvent *pStartCmd = NULL );

private slots:

    void OnFacebookNetwokManagerFinished( FACEBOOK_REQUEST_T aRequest, const QByteArray& aContent );

    void OnItemClicked( const QModelIndex &aItemIndex );

private:

   void RequestGroupsData();

   static FacebookDialog *m_pInstance;

   DialogGroupsTableModel *m_pTableModel;
};

#endif // DIALOG_GROUPS_H
