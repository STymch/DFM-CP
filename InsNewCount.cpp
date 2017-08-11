//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "InsNewCount.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TInsertNewType *InsertNewType;
//---------------------------------------------------------------------------
__fastcall TInsertNewType::TInsertNewType(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TInsertNewType::BitBtn1Click(TObject *Sender)
{
  double D;
  CloseFlag = true;
  if(Edit1->Text == "")
  {
    ShowMessage("Ќе введено значение типа счетчика!");
    CloseFlag = false;
  }
  if(Edit8->Text == "")
  {
    ShowMessage("Ќе введено значение номинального минимального расхода!");
    CloseFlag = false;
  }
  try
  {
    D = Edit8->Text.ToDouble();
  }
  catch(...)
  {
    ShowMessage("¬ведено нечисловое значение номинального минимального расхода!");
    CloseFlag = false;
  }
  if(Edit9->Text == "")
  {
    ShowMessage("Ќе введено значение номинального среднего расхода!");
    CloseFlag = false;
  }
  try
  {
    D = Edit9->Text.ToDouble();
  }
  catch(...)
  {
    ShowMessage("¬ведено нечисловое значение номинального среднего расхода!");
    CloseFlag = false;
  }
  if(Edit10->Text == "")
  {
    ShowMessage("Ќе введено значение номинального максимального расхода!");
    CloseFlag = false;
  }
  try
  {
    D = Edit10->Text.ToDouble();
  }
  catch(...)
  {
    ShowMessage("¬ведено нечисловое значение номинального максимального расхода!");
    CloseFlag = false;
  }
  if(Edit11->Text == "")
  {
    ShowMessage("Ќе введено значение левое отклонение минимального расхода!");
    CloseFlag = false;
  }
  try
  {
    D = Edit11->Text.ToDouble();
  }
  catch(...)
  {
    ShowMessage("¬ведено нечисловое значение левого отклонени€ минимального расхода!");
    CloseFlag = false;
  }
  if(Edit14->Text == "")
  {
    ShowMessage("Ќе введено значение правое отклонение минимального расхода!");
    CloseFlag = false;
  }
  try
  {
    D = Edit14->Text.ToDouble();
  }
  catch(...)
  {
    ShowMessage("¬ведено нечисловое значение правого отклонени€ минимального расхода!");
    CloseFlag = false;
  }
  if(Edit12->Text == "")
  {
    ShowMessage("Ќе введено значение левое отклонение переходного расхода!");
    CloseFlag = false;
  }
  try
  {
    D = Edit12->Text.ToDouble();
  }
  catch(...)
  {
    ShowMessage("¬ведено нечисловое значение левого отклонени€ переходного расхода!");
    CloseFlag = false;
  }
  if(Edit15->Text == "")
  {
    ShowMessage("Ќе введено значение правое отклонение переходного расхода!");
    CloseFlag = false;
  }
  try
  {
    D = Edit15->Text.ToDouble();
  }
  catch(...)
  {
    ShowMessage("¬ведено нечисловое значение правого отклонени€ максимального расхода!");
    CloseFlag = false;
  }
  if(Edit14->Text == "")
  {
    ShowMessage("Ќе введено значение левое отклонение переходного расхода!");
    CloseFlag = false;
  }
  try
  {
    D = Edit14->Text.ToDouble();
  }
  catch(...)
  {
    ShowMessage("¬ведено нечисловое значение левого отклонени€ переходного расхода!");
    CloseFlag = false;
  }

}
//---------------------------------------------------------------------------
void __fastcall TInsertNewType::FormCloseQuery(TObject *Sender, bool &CanClose)
{
  if(CloseFlag)
    CanClose = true;
  else
    CanClose = false;
}
//---------------------------------------------------------------------------
