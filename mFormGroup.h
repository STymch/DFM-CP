//---------------------------------------------------------------------------
#ifndef mFormGroupH
#define mFormGroupH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <CheckLst.hpp>
#include "DataModule.h"
//---------------------------------------------------------------------------
class TFormGroup : public TForm
{
__published:	// IDE-managed Components
    TLabel *Label1;
    TLabel *Label2;
    TEdit *Edit1;
    TPanel *Panel1;
    TBitBtn *BitBtn1;
    TBitBtn *BitBtn2;
    TBevel *Bevel1;
    TMemo *Memo1;
	TCheckBox *CheckBox1;
  TCheckListBox *CheckListBox1;
    void __fastcall BitBtn1Click(TObject *Sender);
    void __fastcall BitBtn2Click(TObject *Sender);
    void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
private:	// User declarations
    bool    bCanClose;
public:		// User declarations
    __fastcall TFormGroup(TComponent* Owner);
    __fastcall TFormGroup(TComponent* Owner, TDataModule1 *DM1, boolean Newflag);
    bool          NewGroupF;
    TDataModule1  *DM;
};
extern PACKAGE TFormGroup *FormGroup;
//---------------------------------------------------------------------------
#endif
