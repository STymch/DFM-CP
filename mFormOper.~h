//---------------------------------------------------------------------------
#ifndef mFormOperH
#define mFormOperH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
//#include "Main.h"
#include "DataModule.h"
//#include "frxClass.hpp"
//#include "frxExportBIFF.hpp"
//---------------------------------------------------------------------------
class TFormOperator : public TForm
{
__published:	// IDE-managed Components
    TEdit *Edit1;
    TEdit *Edit2;
    TLabel *Label1;
    TLabel *Label2;
    TBevel *Bevel1;
    TPanel *Panel1;
    TBitBtn *BitBtn1;
    TBitBtn *BitBtn2;
	TCheckBox *CheckBox1;
  TLabel *Label3;
  TEdit *Edit3;
        TLabel *Label4;
        TEdit *Edit4;
        TLabel *Label5;
        TEdit *Edit5;
        TLabel *Label6;
        TEdit *Edit6;
    void __fastcall BitBtn1Click(TObject *Sender);
    void __fastcall BitBtn2Click(TObject *Sender);
    void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
private:	// User declarations
    bool    bCanClose;
    bool    Create;
public:		// User declarations
    __fastcall TFormOperator(TComponent* Owner);
    __fastcall TFormOperator(TComponent* Owner, TDataModule1 *DM1, bool CreateF);
    TDataModule1  *DM;
};
extern PACKAGE TFormOperator *FormOperator;
//---------------------------------------------------------------------------
#endif
