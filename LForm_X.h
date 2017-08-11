//---------------------------------------------------------------------------
#ifndef LForm_XH
#define LForm_XH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------

#include "Tools_proc.h"
#include "LCTM.h"
#include "LMessage.h"
#include "DefWinMessage.h"
#include "PlugIns.h"
//---------------------------------------------------------------------------
class TXForm_Y : public TForm
{
__published:  // IDE-managed Components

  TTimer *TimerRefresh;
  void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:    // User declarations
protected:  // User declarations
  BEGIN_MESSAGE_MAP
    MESSAGE_HANDLER(WM_COPYDATA, TMessage, AnswerEvent)
    MESSAGE_HANDLER(WM_MDIACTIVATE, TMessage, OnMdiActivate)
  END_MESSAGE_MAP(TForm)

  LCTM     *pST;
  LProfile *pProfile;
  bool NoDeactivate;
  bool FormActive;
  int       equBlock;
  int       equNumber;
  char      szTxt[550];
  char      szTmp[550];
  int       SendAlways;
  int       SendDisable;
  int       Interval;
  LMSG      recvMsg;
  COPYDATASTRUCT  *pCopy;
  BYTE      tmpBuf[LMAX_BUFF];
  InfoModule m_InfoModule;
  void __fastcall OnMdiActivate(TMessage& Msg);
  virtual void __fastcall MdiActivate(bool bActivate){};
public:    // User declarations
  WORD      Object_ID;
  __fastcall TXForm_Y(TComponent* Owner);
  void __fastcall AnswerEvent(TMessage& Msg);
  LCTM *__fastcall Get_pST(void) { return pST; };
  int  __fastcall Get_EquBlock(void) { return equBlock; };
  int  __fastcall Get_EquNumber(void) { return equNumber; };
  bool  __fastcall VerifyVersion(DWORD Version){return m_InfoModule.VerifyVersion(Version);};
  virtual void __fastcall RecvMessage(LMSG rMsg) { };
  virtual void __fastcall SetCurStation(LCTM* pST) { };
  //virtual void __fastcall LoadModuleInfo()=0;
};
//---------------------------------------------------------------------------
#endif
