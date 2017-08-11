//---------------------------------------------------------------------------

#ifndef mSetParamsH
#define mSetParamsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include "DataModule.h"

//---------------------------------------------------------------------------
class TSelectParamsForm : public TForm
{
__published:	// IDE-managed Components
        TPanel *Panel1;
        TGroupBox *GroupBox3;
        TLabel *Label44;
        TComboBox *ComboBox2;
        TRadioButton *Com3;
        TRadioButton *Com4;
        TRadioButton *Com5;
        TRadioButton *Com6;
        TRadioButton *Com7;
        TRadioButton *Com8;
        TRadioButton *Com9;
        TRadioButton *Com10;
        TRadioButton *Com1;
        TRadioButton *Com2;
        TGroupBox *GroupBox17;
        TRadioButton *RadioButton9;
        TRadioButton *RadioButton10;
        TRadioButton *RadioButton11;
        TGroupBox *GroupBox16;
        TRadioButton *ESOBtn;
        TRadioButton *OIMLBtn;
        TRadioButton *DSTUBtn;
        TGroupBox *GroupBox15;
        TRadioButton *KL1Btn;
        TRadioButton *KL2Btn;
        TRadioButton *KLABtn;
        TRadioButton *KLBBtn;
        TGroupBox *GroupBox13;
        TRadioButton *RadioButton8;
        TRadioButton *RadioButton12;
        TGroupBox *GroupBox1;
        TEdit *Edit1;
        TLabel *Label1;
        TGroupBox *GroupBox5;
        TLabel *Label47;
        TLabel *Label48;
        TLabel *Label49;
        TLabel *Label50;
        TLabel *Label51;
        TLabel *Label52;
        TLabel *Label70;
        TLabel *Label71;
        TLabel *Label73;
        TLabel *Label74;
        TLabel *Label2;
        TEdit *Edit8;
        TEdit *Edit9;
        TEdit *Edit10;
        TEdit *Edit11;
        TEdit *Edit12;
        TEdit *Edit13;
        TEdit *Edit18;
        TEdit *Edit19;
        TEdit *Edit24;
        TEdit *Edit27;
        TEdit *Edit17;
        TBitBtn *BitBtn1;
        TBitBtn *BitBtn2;
        TEdit *Edit2;
        TEdit *Edit3;
        TEdit *Edit4;
        TEdit *Edit5;
        TEdit *Edit6;
        TEdit *Edit7;
        TLabel *Label3;
        TLabel *Label4;
        TLabel *Label5;
        TButton *Button1;
        TEdit *Edit14;
        TEdit *Edit15;
        TLabel *Label6;
        void __fastcall ESOBtnClick(TObject *Sender);
        void __fastcall OIMLBtnClick(TObject *Sender);
        void __fastcall DSTUBtnClick(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall BitBtn2Click(TObject *Sender);
        void __fastcall BitBtn1Click(TObject *Sender);
        void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
private:	// User declarations
public:		// User declarations
        __fastcall TSelectParamsForm(TComponent* Owner, TDataModule1  *TDM, AnsiString S);
   bool CloseFlag;
   TDataModule1 *DM;
   AnsiString  MumComp;
   int         Diametr;
   AnsiString  Klass;
   int         Gost;
   AnsiString  Voda;
   float       Qn;      //Q куб.м/час
   float       Qt;      //Q куб.м/час
   float       Qm;      //Q куб.м/час
   float       dQm;     //Проценд погрешности
   float       dQt;
   float       dQn;
   float       QmL;     //QmL Левая граница  куб.м/час
   float       QmR;     //QmR Правая граница  куб.м/час
   float       QtL;     //QtL Левая граница  куб.м/час
   float       QtR;     //QtR Правая граница  куб.м/час
   float       QnL;     //QnL Левая граница  куб.м/час
   float       QnR;     //QnR Правая граница  куб.м/час
   float       CND;     // Цена наименьшего деления
   float       Vpr;     // Oбъем пролива
   bool        SettingFlag;
};
//---------------------------------------------------------------------------
extern PACKAGE TSelectParamsForm *SelectParamsForm;
//---------------------------------------------------------------------------
#endif
