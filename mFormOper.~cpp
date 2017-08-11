//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "mFormOper.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "frxClass"
#pragma link "frxExportBIFF"
#pragma resource "*.dfm"
TFormOperator *FormOperator;
//extern deque <Operator>  OpList;
//extern deque <OpGroup>   GrList;
//---------------------------------------------------------------------------
__fastcall TFormOperator::TFormOperator(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
__fastcall TFormOperator::TFormOperator(TComponent* Owner, TDataModule1 *DM1, bool CreateF)
    : TForm(Owner)
{
    Create = CreateF;
    Edit3->ReadOnly = true;
    if(!CreateF)
      Edit1->Enabled = false;
    DM = DM1;  
}
//---------------------------------------------------------------------------
void __fastcall TFormOperator::BitBtn1Click(TObject *Sender)
{
    //
    bCanClose = true;
    if (Edit1->Text.IsEmpty() )
    {
        Application->MessageBox(" Не задано имя Оператора !", " ", MB_OK | MB_ICONERROR);
        Edit1->SetFocus();
        bCanClose = false;
        return;
    }
    if(Create)
    {
      for(int i = 0; i < (int)DM->OpList.size(); i++)
      {
        if(strcmp(DM->OpList[i].OpName, Trim(Edit1->Text).c_str()) == 0)
        {
          Application->MessageBox(" Задано не уникальное имя Оператора !", " ", MB_OK | MB_ICONERROR);
          Edit1->SetFocus();
          bCanClose = false;
          return;
        }
      }
      if(Edit2->Text.IsEmpty())
      {
        Application->MessageBox(" Не задан пароль Оператора !", " ", MB_OK | MB_ICONERROR);
        Edit2->SetFocus();
        bCanClose = false;
        return;
      }
      if(Edit4->Text.IsEmpty())
      {
        Application->MessageBox(" Не задана фамилия Оператора !", " ", MB_OK | MB_ICONERROR);
        Edit4->SetFocus();
        bCanClose = false;
        return;
      }
      if(Edit5->Text.IsEmpty())
      {
        Application->MessageBox(" Не задано имя Оператора !", " ", MB_OK | MB_ICONERROR);
        Edit5->SetFocus();
        bCanClose = false;
        return;
      }
      if(Edit6->Text.IsEmpty())
      {
        Application->MessageBox(" Не задано отчество Оператора !", " ", MB_OK | MB_ICONERROR);
        Edit6->SetFocus();
        bCanClose = false;
        return;
      }
    }
    
}
//---------------------------------------------------------------------------
void __fastcall TFormOperator::BitBtn2Click(TObject *Sender)
{
    bCanClose = true;
}
//---------------------------------------------------------------------------
void __fastcall TFormOperator::FormCloseQuery(TObject *Sender, bool &CanClose)
{
    CanClose = bCanClose;
}
//---------------------------------------------------------------------------
