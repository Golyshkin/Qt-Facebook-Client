#ifndef DIALOGMYFRIENDSDETAILS_H
#define DIALOGMYFRIENDSDETAILS_H

#include <FacebookDialog.h>
#include <FacebookNetwokClient_def.h>
#include <QVariantMap>
#include <QUrl>

class QLabel;
class QHttp;
class QWebView;
class HTMLButton;

class DialogMyFriendsDetails : public FacebookDialog
{
    Q_OBJECT

public:

    DialogMyFriendsDetails( DialogEvent *pStartCmd = NULL, QWidget *parent = 0 );

    ~DialogMyFriendsDetails();

    virtual void SetUI();

    virtual bool HandleUserEvent( const DialogEvent *pEvent );

    virtual DIALOGS_ID_T Id() const { return DIALOG_MYFRIENDS_DETAILS; }

    static FacebookDialog * Instance( DialogEvent *pStartCmd = NULL );

private slots:

    void OnFacebookNetwokManagerFinished( FACEBOOK_REQUEST_T aRequest, const QByteArray& aContent );

    void OnProfileLinkClicked();

    void OnWebLinkClicked();

private:

   void RequestMyFriendsDetailsData();

   int m_FriendId;

   QLabel *m_pNameLabel, *m_pBirthdayLabel, *m_pGenderLabel,
          *m_pWorkLabel, *m_pLivingLabel;

   QUrl m_LinkToProfileUrl, m_WebLinkUrl;

   QWebView *m_pWebView;

   HTMLButton *m_pHTMLLinkButton, *m_pHTMLWebSiteButton;

   static FacebookDialog *m_pInstance;
};


#endif // DIALOGMYFRIENDSDETAILS_H
