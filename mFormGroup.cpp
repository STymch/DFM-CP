//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "mFormGroup.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
#include "MainP.h"
TFormGroup *FormGroup;
//extern deque <Operator>  OpList;
//extern deque <OpGroup>   GrList;
//---------------------------------------------------------------------------
__fastcall TFormGroup::TFormGroup(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
__fastcall TFormGroup::TFormGroup(TComponent* Owner, TDataModule1 *DM1, boolean Newflag)
    : TForm(Owner)
{
    NewGroupF = Newflag;
    if(!Newflag) Edit1->Enabled = false;
    DM = DM1;
}
//---------------------------------------------------------------------------
void __fastcall TFormGroup::BitBtn1Click(TObject *Sender)
{
    //
  bCanClose = true;
  if (Edit1->Text.IsEmpty() )
  {
    Application->MessageBox(" �� ������ ������������ ������ !", " ", MB_OK | MB_ICONERROR);
    Edit1->SetFocus();
    bCanClose = false;
    return;
  }
  if(NewGroupF)
  {
    for(int i = 0; i < (int)DM->GrList.size(); i++)
    {
      if(strcmp(DM->GrList[i].GrName,Edit1->Text.c_str())== 0)
      {
        Application->MessageBox("������������ ������ �� ���������!", " ", MB_OK | MB_ICONERROR);
        Edit1->SetFocus();
        bCanClose = false;
        return;
      }
    }
  }
  if(Memo1->Text == "")
  {
    Application->MessageBox("�� ������ �������� ������ !", " ", MB_OK | MB_ICONERROR);
    Memo1->SetFocus();
    bCanClose = false;
    return;
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormGroup::BitBtn2Click(TObject *Sender)
{
    bCanClose = true;
}
//---------------------------------------------------------------------------
void __fastcall TFormGroup::FormCloseQuery(TObject *Sender, bool &CanClose)
{
    CanClose = bCanClose;
}
//---------------------------------------------------------------------------
