//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "Tools_proc.h"

#include "LForm_X.h"  

//---------------------------------------------------------------------------
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
__fastcall TXForm_Y::TXForm_Y(TComponent* Owner)
  : TForm(Owner)
{
  SendAlways      = 0;
  SendDisable     = 0;
  Scaled          = false;
  PrintScale      = poNone;
  OldCreateOrder  = false;
  NoDeactivate = false;
  pProfile=NULL;
}
//---------------------------------------------------------------------------
void __fastcall TXForm_Y::AnswerEvent(TMessage& Msg)
{
  try
  {
    pCopy = (COPYDATASTRUCT *)Msg.LParam;
    memcpy(tmpBuf, pCopy->lpData, pCopy->cbData);
    memcpy((BYTE *)&recvMsg, tmpBuf, LMsgSize);
    if (recvMsg.data_len > 0)
    {
      recvMsg.pData = new byte [recvMsg.data_len];
      memcpy((BYTE *)recvMsg.pData, tmpBuf+LMsgSize, recvMsg.data_len);
    }
    RecvMessage(recvMsg);
    recvMsg.Free();
  }
  catch(Exception &exception)
  {
    /*AnsiString S = "(LForm_X) Получение структуры COPYDATASTRUCT \nОшибка - " +
      exception.Message;
    ShowError(Handle,S.c_str()); */
  }
  TForm::Dispatch(&Msg);
}
//---------------------------------------------------------------------------

void __fastcall TXForm_Y::OnMdiActivate(TMessage& Msg)
{
  if(Handle==(HWND)Msg.WParam)
  {
    FormActive=false;
    if(NoDeactivate)
      Show();
    else
      MdiActivate(false);
  }
  else if(Handle==(HWND)Msg.LParam)
  {
    FormActive=true;
    WindowState = wsMaximized;
    if(pST != NULL)
      SetCurStation(pST);
    MdiActivate(true);
  }
  TForm::Dispatch((void*)&Msg);
}
//---------------------------------------------------------------------------

void __fastcall TXForm_Y::FormClose(TObject *Sender, TCloseAction &Action)
{
  Action = caFree;
}
//---------------------------------------------------------------------------



