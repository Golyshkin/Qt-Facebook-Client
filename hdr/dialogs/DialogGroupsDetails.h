#ifndef DIALOGGROUPSDETAILS_H
#define DIALOGGROUPSDETAILS_H

#include <FacebookDialog.h>
#include <FacebookNetwokClient_def.h>
#include <QVariantMap>

class QLabel;
class QHttp;
class QWebView;

class DialogGroupsDetails : public FacebookDialog
{
    Q_OBJECT

public:

    DialogGroupsDetails( DialogEvent *pStartCmd = NULL, QWidget *parent = 0 );

    ~DialogGroupsDetails();

    virtual void SetUI();

    virtual bool HandleUserEvent( const DialogEvent *pEvent );

    virtual DIALOGS_ID_T Id() const { return DIALOG_GROUPS_DETAILS; }

    static FacebookDialog * Instance( DialogEvent *pStartCmd = NULL );

private slots:

    void OnFacebookNetwokManagerFinished( FACEBOOK_REQUEST_T aRequest, const QByteArray& aContent );

private:

   void RequestGroupsDetailsData();

   int m_GroupId;

   QLabel *m_pNameLabel;

   QLabel *m_pLbl;

   static FacebookDialog *m_pInstance;
};

#endif // DIALOGGROUPSDETAILS_H
