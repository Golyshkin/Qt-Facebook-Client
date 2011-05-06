#ifndef DIALOG_MY_FRIENDS_H
#define DIALOG_MY_FRIENDS_H

#include <QModelIndex>

#include <FacebookDialog.h>
#include <FacebookNetwokClient_def.h>

class QPushButton;
class QLabel;
class DialogMyFriendsTableModel;

class DialogMyFriends : public FacebookDialog
{
    Q_OBJECT

public:

    DialogMyFriends( DialogEvent *pStartCmd = NULL, QWidget *parent = 0 );

    ~DialogMyFriends();

    virtual void SetUI();

    virtual bool HandleUserEvent( const DialogEvent *pEvent );

    virtual DIALOGS_ID_T Id() const { return DIALOG_MYFRIENDS; }

    static FacebookDialog * Instance( DialogEvent *pStartCmd = NULL );

private slots:

    void OnFacebookNetwokManagerFinished( FACEBOOK_REQUEST_T aRequest, const QByteArray& aContent );

    void OnItemClicked( const QModelIndex &aItemIndex );

private:

   void RequestMyFriendsData();

   static FacebookDialog *m_pInstance;

   DialogMyFriendsTableModel *m_pTableModel;
};

#endif // DIALOG_MY_FRIENDS_H
