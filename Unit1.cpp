//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "DataModule.h"

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TSubscrForm *SubscrForm;
//---------------------------------------------------------------------------
__fastcall TSubscrForm::TSubscrForm(TComponent* Owner, TDataModule1  *TDM)
        : TForm(Owner)
{
  DM = TDM;
}
//----------------------------------------------------------------------------
void TSubscrForm::ControLNaCislo(AnsiString S)
{
//  float F;
  try
  {
    if(DecimalSeparator == '.')
      (DM->ReplZPnaPunk2(S)).ToDouble();
    else
      (DM->ReplPunknaZP2(S)).ToDouble();
  }
  catch(...)
  {
    CloseFlag = false;
    ShowMessage("���� ������� ���������� �������� ���������� ������ � ������� ��� ���� ������������!! ���������");
  }
}
//----------------------------------------------------------------------------
void __fastcall TSubscrForm::BitBtn2Click(TObject *Sender)
{
  CloseFlag = true;
  if(CountN->Text == "")
  {
    ShowMessage("�� ������ ����� ��������!");
    CloseFlag = false;
    return;
  }
  if(CountTipe->Text == "")
  {
    ShowMessage("�� ������ ��� ��������!");
    CloseFlag = false;
    return;
  }
  if(SurNameEdit->Text == "")
  {
    ShowMessage("�� ������� ������� ��������!");
    CloseFlag = false;
    return;
  }
  if(NameEdit->Text == "")
  {
    ShowMessage("�� ������� ��� ��������!");
    CloseFlag = false;
    return;
  }
  if(TaunEdit->Text == "")
  {
    ShowMessage("�� ������ �����!");
    CloseFlag = false;
    return;
  }
  if(StreetEdit->Text == "")
  {
    ShowMessage("�� ������� �����!");
    CloseFlag = false;
    return;
  }
  if(HausEdit->Text == "")
  {
    ShowMessage("�� ������ ����� ����!");
    CloseFlag = false;
    return;
  }
  if(Edit3->Text == "")
  {
    ShowMessage("�� ������� �������!");
    CloseFlag = false;
    return;
  }
  ControLNaCislo(Edit3->Text);
  if(Edit4->Text == "")
  {
    ShowMessage("�� ������� ������!");
    CloseFlag = false;
    return;
  }
  ControLNaCislo(Edit4->Text);
  ControLNaCislo(Edit1->Text);
  ControLNaCislo(Edit2->Text);
  ControLNaCislo(Edit5->Text);
}
//---------------------------------------------------------------------------

void __fastcall TSubscrForm::FormCloseQuery(TObject *Sender,
      bool &CanClose)
{
  if(CloseFlag)  CanClose = true;
  else  CanClose = false;
}
//---------------------------------------------------------------------------

void __fastcall TSubscrForm::BitBtn1Click(TObject *Sender)
{
  CloseFlag = true;
}
//---------------------------------------------------------------------------

