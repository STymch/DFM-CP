//---------------------------------------------------------------------------
#include <vcl\vcl.h>
//#include <winsock2.h>
#pragma hdrstop

#include "DataModule.h"
#include "mPasswordForm.h"
//#include "ctm_Help.hh"
TPasswordForm *PasswordForm;
//---------------------------------------------------------------------------
#pragma resource "*.dfm"

// extern TStringList  *pOperList;
// extern TAudit 	    *Audit;
// AnsiString	        LoginName;
// AnsiString	        LoginPass;

//extern deque <Operator>  OpList;
//extern deque <OpGroup>   GrList;
//extern AnsiString      OpName;
//---------------------------------------------------------------------------
__fastcall TPasswordForm::TPasswordForm(TComponent* Owner, TDataModule1 *DM1)
	: TForm(Owner)
{
  	Result = 0;
       Attempt = 0;
       Caption = "";
        DM = DM1;
  	Edit1->Text = DM->OpName;
//  	Edit1->Text = DM->CurOpName;
  	Edit2->Text = "";
}
//---------------------------------------------------------------------------
void __fastcall TPasswordForm::FormCloseQuery(TObject *Sender, bool &CanClose)
{
  if(CloseFlag)
  		CanClose = true;
  else
  		CanClose = false;
}
//---------------------------------------------------------------------------
void __fastcall TPasswordForm::CancelBitBtnClick(TObject *Sender)
{
	Result   = false;
  CloseFlag = true;
}
//---------------------------------------------------------------------------
void __fastcall TPasswordForm::OKBitBtnClick(TObject *Sender)
{
    // Нажата кнопка применить
    // Нажата кнопка применить
  AnsiString S;
  int rCount;

  Name = Trim(Edit1->Text);
  Password = Trim(Edit2->Text);
  int r = -1;
  for(int i = 0; i < (int)DM->OpList.size(); i++)
  {
//    if((strcmp(DM->OpList[i].OpName,Name.c_str()) == 0) &&
//       (strcmp(DM->OpList[i].Password1,Password.c_str()) == 0))
    if((Trim((AnsiString)DM->OpList[i].OpName) == Name) &&
       (Trim((AnsiString)DM->OpList[i].Password1) == Password))
    {
      r = i;
      GroupName = Trim((AnsiString)DM->OpList[i].GroupName);
      for(int j = 0; j < (int)DM->GrList.size(); j++)
      {
        S = DM->GrList[j].GrName;
        S = Trim(S.SubString(1,24));
//        if(S.Length() > 24)
//          S = S.SubString(1,24);
        if(S == GroupName)
        {
          Rights = DM->GrList[j].PRights;
          break;
        }
      }
      break;
    }
  }
  if(r == -1)
  {
    Attempt++;
    if(Attempt > 2)
    {
      Result = false;
      CloseFlag = true;
      return;
    }
    else
    {
      Edit2->Text = "";
      CloseFlag = false;
      return;
    }
  }
  Result = true;
  CloseFlag = true;
}
//---------------------------------------------------------------------------


