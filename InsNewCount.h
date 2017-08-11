//---------------------------------------------------------------------------

#ifndef InsNewCountH
#define InsNewCountH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TInsertNewType : public TForm
{
__published:	// IDE-managed Components
        TEdit *Edit1;
        TBitBtn *BitBtn1;
        TBitBtn *BitBtn2;
        TGroupBox *GroupBox5;
        TLabel *Label47;
        TLabel *Label48;
        TLabel *Label49;
        TLabel *Label50;
        TLabel *Label51;
        TLabel *Label52;
        TEdit *Edit8;
        TEdit *Edit9;
        TEdit *Edit10;
        TEdit *Edit11;
        TEdit *Edit12;
        TEdit *Edit13;
        TEdit *Edit14;
        TEdit *Edit15;
        TEdit *Edit16;
        TEdit *Edit17;
        TEdit *Edit18;
        TEdit *Edit19;
        TLabel *Label1;
        void __fastcall BitBtn1Click(TObject *Sender);
        void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
private:	// User declarations
public:		// User declarations
        __fastcall TInsertNewType(TComponent* Owner);
        bool CloseFlag;
};
//---------------------------------------------------------------------------
extern PACKAGE TInsertNewType *InsertNewType;
//---------------------------------------------------------------------------
#endif
