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
    ShowMessage("�� ������� �������� ���� ��������!");
    CloseFlag = false;
  }
  if(Edit8->Text == "")
  {
    ShowMessage("�� ������� �������� ������������ ������������ �������!");
    CloseFlag = false;
  }
  try
  {
    D = Edit8->Text.ToDouble();
  }
  catch(...)
  {
    ShowMessage("������� ���������� �������� ������������ ������������ �������!");
    CloseFlag = false;
  }
  if(Edit9->Text == "")
  {
    ShowMessage("�� ������� �������� ������������ �������� �������!");
    CloseFlag = false;
  }
  try
  {
    D = Edit9->Text.ToDouble();
  }
  catch(...)
  {
    ShowMessage("������� ���������� �������� ������������ �������� �������!");
    CloseFlag = false;
  }
  if(Edit10->Text == "")
  {
    ShowMessage("�� ������� �������� ������������ ������������� �������!");
    CloseFlag = false;
  }
  try
  {
    D = Edit10->Text.ToDouble();
  }
  catch(...)
  {
    ShowMessage("������� ���������� �������� ������������ ������������� �������!");
    CloseFlag = false;
  }
  if(Edit11->Text == "")
  {
    ShowMessage("�� ������� �������� ����� ���������� ������������ �������!");
    CloseFlag = false;
  }
  try
  {
    D = Edit11->Text.ToDouble();
  }
  catch(...)
  {
    ShowMessage("������� ���������� �������� ������ ���������� ������������ �������!");
    CloseFlag = false;
  }
  if(Edit14->Text == "")
  {
    ShowMessage("�� ������� �������� ������ ���������� ������������ �������!");
    CloseFlag = false;
  }
  try
  {
    D = Edit14->Text.ToDouble();
  }
  catch(...)
  {
    ShowMessage("������� ���������� �������� ������� ���������� ������������ �������!");
    CloseFlag = false;
  }
  if(Edit12->Text == "")
  {
    ShowMessage("�� ������� �������� ����� ���������� ����������� �������!");
    CloseFlag = false;
  }
  try
  {
    D = Edit12->Text.ToDouble();
  }
  catch(...)
  {
    ShowMessage("������� ���������� �������� ������ ���������� ����������� �������!");
    CloseFlag = false;
  }
  if(Edit15->Text == "")
  {
    ShowMessage("�� ������� �������� ������ ���������� ����������� �������!");
    CloseFlag = false;
  }
  try
  {
    D = Edit15->Text.ToDouble();
  }
  catch(...)
  {
    ShowMessage("������� ���������� �������� ������� ���������� ������������� �������!");
    CloseFlag = false;
  }
  if(Edit14->Text == "")
  {
    ShowMessage("�� ������� �������� ����� ���������� ����������� �������!");
    CloseFlag = false;
  }
  try
  {
    D = Edit14->Text.ToDouble();
  }
  catch(...)
  {
    ShowMessage("������� ���������� �������� ������ ���������� ����������� �������!");
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
