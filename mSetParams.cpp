//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "DataModule.h"
#include "mSetParams.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TSelectParamsForm *SelectParamsForm;
//---------------------------------------------------------------------------
__fastcall TSelectParamsForm::TSelectParamsForm(TComponent* Owner, TDataModule1  *TDM, AnsiString S)
        : TForm(Owner)
{
  CloseFlag = false;
  DM = TDM;
  if(S == "Com1") Com1->Checked = true;
  if(S == "Com2") Com2->Checked = true;
  if(S == "Com3") Com3->Checked = true;
  if(S == "Com4") Com4->Checked = true;
  if(S == "Com5") Com5->Checked = true;
  if(S == "Com6") Com6->Checked = true;
  if(S == "Com7") Com7->Checked = true;
  if(S == "Com8") Com8->Checked = true;
  if(S == "Com9") Com9->Checked = true;
  if(S == "Com10") Com10->Checked = true;
  SettingFlag = false;
}
//---------------------------------------------------------------------------

void __fastcall TSelectParamsForm::ESOBtnClick(TObject *Sender)
{
  if(ESOBtn->Checked)
  {
    KLABtn->Enabled = false;
    KLBBtn->Enabled = false;
    KL1Btn->Enabled = true;
    KL2Btn->Enabled = true;
    KL2Btn->Checked = true;
  }
}
//---------------------------------------------------------------------------
void __fastcall TSelectParamsForm::OIMLBtnClick(TObject *Sender)
{
  if(OIMLBtn->Checked)
  {
    KLABtn->Enabled = false;
    KLBBtn->Enabled = false;
    KL1Btn->Enabled = true;
    KL2Btn->Enabled = true;
    KL2Btn->Checked = true;
  }
}
//---------------------------------------------------------------------------
void __fastcall TSelectParamsForm::DSTUBtnClick(TObject *Sender)
{
  if(DSTUBtn->Checked)
  {
    KLABtn->Enabled = true;
    KLBBtn->Enabled = true;
    KL1Btn->Enabled = false;
    KL2Btn->Enabled = false;
    KLBBtn->Checked = true;
  }
}
//---------------------------------------------------------------------------
void __fastcall TSelectParamsForm::Button1Click(TObject *Sender)
{
  AnsiString S, S1, S2, S3;
  int        i;

  if(ESOBtn->Checked)
    Gost = 1;          // ДСТУ EN ISO 4064-1
  if(OIMLBtn->Checked)
    Gost = 2;          //ДСТУ OIML R 49-1
  if(DSTUBtn->Checked)
    Gost = 3;          //ДСТУ 3580
  if(RadioButton9->Checked)
    Diametr = 10;
  if(RadioButton10->Checked)
    Diametr = 15;
  if(RadioButton11->Checked)
    Diametr = 20;
  if(KL1Btn->Checked)
    Klass = KL1Btn->Caption;
  if(KL2Btn->Checked)
    Klass = KL2Btn->Caption;
  if(KLABtn->Checked)
    Klass = KLABtn->Caption;
  if(KLBBtn->Checked)
    Klass = KLBBtn->Caption;
  if(RadioButton8->Checked)
    Voda = "Х";
  if(RadioButton12->Checked)
    Voda = "Г";
  if( Gost == 3)
  {
    for(i = 0; i < (int)DM->DiamOldList.size(); i++)
    {
      S = DM->DiamOldList[i].Klass;
      if((DM->DiamOldList[i].Diametr == Diametr) && ( S == Klass))
      {
        Qn = DM->DiamOldList[i].Qn;
        Qt = DM->Round(Qn * DM->DiamOldList[i].KQt, 4);
        Qm = DM->Round(Qn * DM->DiamOldList[i].KQm, 4);
        Edit8->Text = S.sprintf("%3.2f", Qm*1000);
        Edit9->Text = S.sprintf("%3.2f", Qt*1000);
        Edit10->Text = S.sprintf("%3.2f", Qn*1000);
        break;
      }
    }
  }
  else
  {
    for(i = 0; i < (int)DM->DiamNewList.size(); i++)
    {
      S = DM->DiamNewList[i].Klass;
      if((DM->DiamNewList[i].Diametr == Diametr) && ( S == Klass))
      {
        Qn = DM->DiamNewList[i].Qn;
        Qt = DM->Round(Qn * DM->DiamNewList[i].KQt, 4);
        Qm = DM->Round(Qn * DM->DiamNewList[i].KQm, 4);
        Edit8->Text = S.sprintf("%3.2f", Qm*1000);
        Edit9->Text = S.sprintf("%3.2f", Qt*1000);
        Edit10->Text = S.sprintf("%3.2f", Qn*1000);
        break;
      }
    }
  }
  if( Gost == 1)     //ДСТУ EN ISO 4064-1
  {
    S1 = "Qmin";
    for(i = 0; i < (int)DM->ISODopList.size(); i++)
    {
      S = DM->ISODopList[i].Klass;
      S2 = DM->ISODopList[i].QTipe;
      S3 = DM->ISODopList[i].Voda;
      if((S == Klass) && ( S1 == S2) && ( S3 == Voda))
      {
        dQm = DM->ISODopList[i].Pogr;
        Edit11->Text = S.sprintf("%3.2f", dQm);
        break;
      }
    }
    S1 = "Qt";
    for(i = 0; i < (int)DM->ISODopList.size(); i++)
    {
      S = DM->ISODopList[i].Klass;
      S2 = DM->ISODopList[i].QTipe;
      S3 = DM->ISODopList[i].Voda;
      if((S == Klass) && ( S1 == S2) && ( S3 == Voda))
      {
        dQt = DM->ISODopList[i].Pogr;
        Edit12->Text = S.sprintf("%3.2f", dQt);
        break;
      }
    }
    S1 = "Qn";
    for(i = 0; i < (int)DM->ISODopList.size(); i++)
    {
      S = DM->ISODopList[i].Klass;
      S2 = DM->ISODopList[i].QTipe;
      S3 = DM->ISODopList[i].Voda;
      if((S == Klass) && ( S1 == S2) && ( S3 == Voda))
      {
        dQn = DM->ISODopList[i].Pogr;
        Edit13->Text = S.sprintf("%3.2f", dQn);
        break;
      }
    }
  }
  if( Gost == 2)     //ДСТУ LCNE OIML R 49-1
  {
    S1 = "Qmin";
    for(i = 0; i < (int)DM->LNCEDopList.size(); i++)
    {
      S = DM->LNCEDopList[i].Klass;
      S2 = DM->LNCEDopList[i].QTipe;
      S3 = DM->LNCEDopList[i].Voda;
      if((S == Klass) && ( S1 == S2) && ( S3 == Voda))
      {
        dQm = DM->LNCEDopList[i].Pogr;
        Edit11->Text = S.sprintf("%3.2f", dQm);
        break;
      }
    }
    S1 = "Qt";
    for(i = 0; i < (int)DM->LNCEDopList.size(); i++)
    {
      S = DM->LNCEDopList[i].Klass;
      S2 = DM->LNCEDopList[i].QTipe;
      S3 = DM->LNCEDopList[i].Voda;
      if((S == Klass) && ( S1 == S2) && ( S3 == Voda))
      {
        dQt = DM->LNCEDopList[i].Pogr;
        Edit12->Text = S.sprintf("%3.2f", dQt);
        break;
      }
    }
    S1 = "Qn";
    for(i = 0; i < (int)DM->LNCEDopList.size(); i++)
    {
      S = DM->LNCEDopList[i].Klass;
      S2 = DM->LNCEDopList[i].QTipe;
      S3 = DM->LNCEDopList[i].Voda;
      if((S == Klass) && ( S1 == S2) && ( S3 == Voda))
      {
        dQn = DM->LNCEDopList[i].Pogr;
        Edit13->Text = S.sprintf("%3.2f", dQn);
        break;
      }
    }
  }
  if( Gost == 3)     //ДСТУ 3580
  {
    S1 = "Qmin";
    for(i = 0; i < (int)DM->OLDDopList.size(); i++)
    {
      S = DM->OLDDopList[i].Klass;
      S2 = DM->OLDDopList[i].QTipe;
      S3 = DM->OLDDopList[i].Voda;
      if((S == Klass) && ( S1 == S2) && ( S3 == Voda))
      {
        dQm = DM->OLDDopList[i].Pogr;
        Edit11->Text = S.sprintf("%3.2f", dQm);
        break;
      }
    }
    S1 = "Qt";
    for(i = 0; i < (int)DM->OLDDopList.size(); i++)
    {
      S = DM->OLDDopList[i].Klass;
      S2 = DM->OLDDopList[i].QTipe;
      S3 = DM->OLDDopList[i].Voda;
      if((S == Klass) && ( S1 == S2) && ( S3 == Voda))
      {
        dQt = DM->OLDDopList[i].Pogr;
        Edit12->Text = S.sprintf("%3.2f", dQt);
        break;
      }
    }
    S1 = "Qn";
    for(i = 0; i < (int)DM->OLDDopList.size(); i++)
    {
      S = DM->OLDDopList[i].Klass;
      S2 = DM->OLDDopList[i].QTipe;
      S3 = DM->OLDDopList[i].Voda;
      if((S == Klass) && ( S1 == S2) && ( S3 == Voda))
      {
        dQn = DM->OLDDopList[i].Pogr;
        Edit13->Text = S.sprintf("%3.2f", dQn);
        break;
      }
    }
  }
  QmL = DM->Round(Qm * DM->QminLGr, 4); QmR = DM->Round(Qm * DM->QminRGr, 4);
  QtL = DM->Round(Qt * DM->QtLGr, 4);   DM->Round(QtR = Qt * DM->QtRGr, 4);
  QnL = DM->Round(Qt * DM->QnLGr, 4);   DM->Round(QnR = Qn * DM->QnRGr, 4);
  Edit2->Text = S.sprintf("%3.2f", QmL * 1000);
  Edit3->Text = S.sprintf("%3.2f", QmR * 1000);
  Edit4->Text = S.sprintf("%3.2f", QtL * 1000);
  Edit5->Text = S.sprintf("%3.2f", QtR * 1000);
  Edit6->Text = S.sprintf("%3.2f", QnL * 1000);
  Edit7->Text = S.sprintf("%3.2f", QnR * 1000);
  try
  {
    if(DecimalSeparator == '.')
      CND = (DM->ReplZPnaPunk2(Edit1->Text)).ToDouble();
    else
      CND = (DM->ReplPunknaZP2(Edit1->Text)).ToDouble();
  }
  catch(...)
  {
    ShowMessage("Были введены нечисловые данные цены наименьшего деления! Исправьте!");
    CloseFlag = false;
  }
  Vpr = CND * DM->VKonst;                     //Liters
  Edit17->Text = S.sprintf("%3.2f", Vpr);
  Edit18->Text = S.sprintf("%3.2f", Vpr);
  Edit19->Text = S.sprintf("%3.2f", Vpr);
  Edit24->Text = (AnsiString)DM->TXolL;       //Левая граница темп. холодной воды
  Edit14->Text = (AnsiString)DM->TXolR;       //Правая граница темп. холодной воды
  Edit27->Text = (AnsiString)DM->TGorL;
  Edit15->Text = (AnsiString)DM->TGorR;
  SettingFlag = true;
    if(Com1->Checked) MumComp = "Com1";
    if(Com2->Checked) MumComp = "Com2";
    if(Com3->Checked) MumComp = "Com3";
    if(Com4->Checked) MumComp = "Com4";
    if(Com5->Checked) MumComp = "Com5";
    if(Com6->Checked) MumComp = "Com6";
    if(Com7->Checked) MumComp = "Com7";
    if(Com8->Checked) MumComp = "Com8";
    if(Com9->Checked) MumComp = "Com9";
    if(Com10->Checked) MumComp = "Com10";
}
//---------------------------------------------------------------------------
void __fastcall TSelectParamsForm::BitBtn2Click(TObject *Sender)
{
  if(SettingFlag)
  {
    DM->Vmin = DM->Vn = DM->Vt = Vpr; //Объемы пролива литры
    DM->Qn = Qn;               //Объемы пролива кубометров в час
    DM->Qt = Qt;               //Объемы пролива кубометров в час л/час
    DM->Qmin = Qm;             //Объемы пролива кубометров в час л/час
    DM->QnLitr = Qn * 1000;                    //величина объема пролива л/час
    DM->QtLitr = Qt * 1000;                    //величина объема пролива л/час
    DM->QminLitr = Qm * 1000;                  //величина объема пролива л/час

    DM->QminL = QmL; DM->QminR = QmR;  //Правые и левые границы отклонений адля устаноления скорости потока Mkub
    DM->QtL = QtL;   DM->QtR = QtR;    //Правые и левые границы отклонений адля устаноления скорости потока Mkub
    DM->QnomL = QnL; DM->QnomR = QnR;   //Правые и левые границы отклонений адля устаноления скорости потока Mkub

    DM->DnL  = DM->DnR = dQn;         //Допустимые Проценты на меньшее и больше отличия пролива %
    DM->DtL  = DM->DtR = dQt;         //Допустимые Проценты на меньшее и больше отличия пролива %
    DM->DminL = DM->DminR = dQm;      //Допустимые Проценты на меньшее и больше отличия пролива %
    DM->Diametr = Diametr;
    CloseFlag = true;
  }
  else
  {
    ShowMessage("Не была проведена установка параметров!");
    CloseFlag = false;
  }
}
//---------------------------------------------------------------------------
void __fastcall TSelectParamsForm::BitBtn1Click(TObject *Sender)
{
  CloseFlag = true;
}
//---------------------------------------------------------------------------
void __fastcall TSelectParamsForm::FormCloseQuery(TObject *Sender,
      bool &CanClose)
{
  if(CloseFlag == true)
    CanClose = true;
  else
    CanClose = false;
}
//---------------------------------------------------------------------------




