///////////////////////////////////////////////////////////
//  DialogEvent.h
//  Implementation of the Class DialogEvent
//  Created on:      26-Apr-2011 9:24:47 AM
//  Original author: Golyshkin A.
///////////////////////////////////////////////////////////

#if !defined(EA_BECEDDCD_0C7E_4771_9B88_97BD6982995A__INCLUDED_)
#define EA_BECEDDCD_0C7E_4771_9B88_97BD6982995A__INCLUDED_

#include <QEvent>

class DialogEvent : public QEvent
{
public:

   enum DIALOG_CMD_T
   {
      DIALOG_CMD_UNKNOWN = 0,
      DIALOG_CMD_DAILOG_STARTED,
      DIALOG_CMD_FRIEND_ID
   };

   DialogEvent( DIALOG_CMD_T cmd, void *pData = NULL, int aDataSize = 0 );

   DialogEvent( DialogEvent& aDialogEvent );

   virtual ~DialogEvent();

   DIALOG_CMD_T Cmd() const { return m_Cmd; }

   void * Data() const { return m_pData; }

   int DataSize() const { return m_DataSize; }

private:

   void * m_pData;

   int m_DataSize;

   DIALOG_CMD_T m_Cmd;
};

#endif // !defined(EA_BECEDDCD_0C7E_4771_9B88_97BD6982995A__INCLUDED_)
