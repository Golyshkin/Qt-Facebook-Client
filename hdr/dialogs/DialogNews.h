#ifndef DIALOGNEWS_H
#define DIALOGNEWS_H

#include <FacebookDialog.h>
#include <FacebookNetwokClient_def.h>

class QPushButton;
class DialogNewsListModel;

class DialogNews : public FacebookDialog
{
    Q_OBJECT

public:

    DialogNews( DialogEvent *pStartCmd = NULL, QWidget *parent = 0 );

    ~DialogNews();

    virtual void SetUI();

    virtual bool HandleUserEvent( const DialogEvent *pEvent );

    virtual DIALOGS_ID_T Id() const { return DIALOG_NEWS; }

    static FacebookDialog * Instance( DialogEvent *pStartCmd = NULL );

private slots:

    void OnFacebookNetwokManagerFinished( FACEBOOK_REQUEST_T aRequest, QByteArray aContent );

private:
   void RequestNewsData();
   static FacebookDialog *m_pInstance;
   DialogNewsListModel *m_pListModel;
};

#endif // DIALOGNEWS_H
