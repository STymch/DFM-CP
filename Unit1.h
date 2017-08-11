//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TSubscrForm : public TForm
{
__published:	// IDE-managed Components
        TGroupBox *GroupBox8;
        TLabel *Label54;
        TLabel *Label56;
        TLabel *Label69;
        TEdit *CountN;
        TEdit *CountTipe;
        TGroupBox *GroupBox7;
        TLabel *Label65;
        TLabel *Label66;
        TLabel *Label67;
        TEdit *SurNameEdit;
        TEdit *NameEdit;
        TEdit *FNameEdit;
        TGroupBox *GroupBox6;
        TLabel *Label57;
        TLabel *Label58;
        TLabel *Label59;
        TLabel *Label63;
        TLabel *Label64;
        TEdit *TaunEdit;
        TEdit *StreetEdit;
        TEdit *HausEdit;
        TEdit *KorpEdit;
        TEdit *BitEdit;
        TBitBtn *BitBtn1;
        TBitBtn *BitBtn2;
        TGroupBox *GroupBox1;
        TEdit *Edit1;
        TEdit *Edit2;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *Label4;
        TEdit *Edit3;
        TEdit *Edit4;
        TLabel *Label5;
        TEdit *Edit5;
        void __fastcall BitBtn2Click(TObject *Sender);
        void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
        void __fastcall BitBtn1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TSubscrForm(TComponent* Owner, TDataModule1  *TDM);
        void ControLNaCislo(AnsiString S);
  TDataModule1 *DM;
  bool         CloseFlag;
};
//---------------------------------------------------------------------------
extern PACKAGE TSubscrForm *SubscrForm;
//---------------------------------------------------------------------------
#endif
