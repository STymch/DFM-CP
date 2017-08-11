//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;
//---------------------------------------------------------------------------
bool AskingMessage(AnsiString S)
{
   if (Application->MessageBox(&S[1],
      "ВНИМАНИЕ!!!",MB_YESNO | MB_ICONWARNING )== IDYES)
      return true;
   else
     return false;
}
//---------------------------------------------------------------------------
AnsiString ReplZPnaPunk1(AnsiString SI)           //float всегда с точкой
{
  AnsiString S;
  S = "";
  for(int i = 1; i <= SI.Length(); i++)
  {
    if(SI[i] == ',') S += '.';
    else S += SI[i];
  }
  return S;
}
//---------------------------------------------------------------------------
AnsiString ReplPunknaZP1(AnsiString SI)
{
  AnsiString S;
  S = "";
  for(int i = 1; i <= SI.Length(); i++)
  {
    if(SI[i] == '.') S += ',';
    else S += SI[i];
  }
  return S;
}
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm2::FormCloseQuery(TObject *Sender, bool &CanClose)
{
  if(CloseFlag)
    CanClose = true;
  else
    CanClose = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm2::BitBtn2Click(TObject *Sender)
{
  AnsiString S;

  S += "Вы уверены в закрытии окна? В этом случае прийдется проводить тест повторно!";
  if(!AskingMessage(S))
    return;
  CloseFlag = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm2::BitBtn1Click(TObject *Sender)
{
  CloseFlag = true;
  if(Edit1->Text == "")
  {
    ShowMessage(" Не введено начальное значение счетчика!");
    CloseFlag = false;
    return;
  }
  if(Edit2->Text == "")
  {
    ShowMessage(" Не введено конечное значение счетчика!");
    CloseFlag = false;
    return;
  }
  try
  {
    if(DecimalSeparator == '.')
      BegValue = (ReplZPnaPunk1(Edit1->Text)).ToDouble();
    else
      BegValue = (ReplPunknaZP1(Edit1->Text)).ToDouble();
  }
  catch(...)
  {
    ShowMessage(" Введено не числовое начальное значение счетчика!");
    CloseFlag = false;
    return;
  }
  try
  {
    if(DecimalSeparator == '.')
      EndValue = (ReplZPnaPunk1(Edit2->Text)).ToDouble();
    else
      EndValue = (ReplPunknaZP1(Edit2->Text)).ToDouble();
  }
  catch(...)
  {
    ShowMessage(" Введено не числовое конечное значение счетчика!");
    CloseFlag = false;
    return;
  }
  if(BegValue > EndValue)
  {
    ShowMessage(" Начальное значение больше конечного!");
    CloseFlag = false;
    return;
  }
}
//---------------------------------------------------------------------------


