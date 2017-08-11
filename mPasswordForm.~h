//---------------------------------------------------------------------------
#ifndef mPasswordFormH
#define mPasswordFormH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\Buttons.hpp>
#include <ComCtrls.hpp>
#include <Graphics.hpp>
#include "DataModule.h"
#include <ExtCtrls.hpp>
#include <deque>

using namespace std;
//---------------------------------------------------------------------------
class TPasswordForm : public TForm
{
__published:	// IDE-managed Components
  TPanel *Panel4;
  TPanel *Panel5;
  TImage *Image2;
  TLabel *Label5;
  TLabel *Label6;
  TPanel *Panel6;
  TEdit *Edit1;
  TPanel *Panel7;
  TEdit *Edit2;
  TBitBtn *OKBitBtn;
  TBitBtn *CancelBitBtn;
  void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
  void __fastcall OKBitBtnClick(TObject *Sender);
  void __fastcall CancelBitBtnClick(TObject *Sender);
private:	// User declarations
  int		        Attempt;
public:		// User declarations
  AnsiString    Name, Password, GroupName;
  bool CloseFlag;
public:		// User declarations
  __fastcall TPasswordForm(TComponent* Owner, TDataModule1 *DM1);
	int		        Result;
  DWORD         Rights;
  TDataModule1  *DM;
};
extern PACKAGE TPasswordForm *PasswordForm;
//---------------------------------------------------------------------------
#endif
