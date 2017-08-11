//---------------------------------------------------------------------------
#include <vcl.h>
#include <stdio.h>
#pragma hdrstop
#include "FirmsForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//#pragma link "cxContainer"
//#pragma link "cxControls"
//#pragma link "cxEdit"
//#pragma link "cxGroupBox"
//#pragma link "GIFImage"
#pragma link "GIFImage"
#pragma resource "*.dfm"
//#include "Tools_proc.h"
TFirmForm *FirmForm;
//---------------------------------------------------------------------------
__fastcall TFirmForm::TFirmForm(TComponent* Owner)
    : TForm(Owner)
{
//  Label1->Caption="Программа Тарификации";
//  Label3->Caption="Регистрационный номер 0BE.004.002";
}
//---------------------------------------------------------------------------
__fastcall TFirmForm::TFirmForm(TComponent* Owner, char* Capt, char* Mod, char* SN)
    : TForm(Owner)
{
//  Label1->Caption = Capt;
//  Label2->Caption = Mod;
//  Label3->Caption = SN;
}
//---------------------------------------------------------------------------

void __fastcall TFirmForm::FormCloseQuery(TObject *Sender, bool &CanClose)
{
  CanClose = true;
}
//---------------------------------------------------------------------------

void __fastcall TFirmForm::FormClose(TObject *Sender, TCloseAction &Action)
{
  Action = caFree;
}
//---------------------------------------------------------------------------

void __fastcall TFirmForm::FormCreate(TObject *Sender)
{
/*
  // Прочитать и вывести версию приложения
  struct TVerTranslation
  {
      WORD    Language;
      WORD    CharSet;
  };
  // Получить указать на объект Авторизации
  DWORD dwValue;
  DWORD struct_Size = GetFileVersionInfoSize(ExeName.c_str(), &dwValue);
  if (struct_Size==0)
  {
    Label3->Caption = "Версия  4.04.09";
    return;
  }
  void *Data = new char[struct_Size + 10];
  if (!GetFileVersionInfo(ExeName.c_str(), 0, struct_Size, Data))
  {
    delete [] Data;
    Label3->Caption = "Версия  4.04.09";
    return;
  }
  // Язык и кодовая таблица
  UINT Bytes;
  TVerTranslation *Trans;
  if (!VerQueryValue(Data, "\\VarFileInfo\\Translation",&(void*)Trans, &Bytes))
  {
    delete [] Data;
    return;
  }

  AnsiString BaseStr = "StringFileInfo\\"+IntToHex(Trans->Language,4)+
                               IntToHex(Trans->CharSet,4)+"\\FileVersion";
  VS_FIXEDFILEINFO *FixInfo;
  if (!VerQueryValue(Data, "\\", &(void*)FixInfo, &Bytes))
  {
    delete [] Data;
    Label3->Caption = "Версия  4.04.09";
    return;
  }
  char * ptr;
  if( !VerQueryValue(Data, BaseStr.c_str(), &(void*)ptr,&Bytes))
  {
    delete [] Data;
    Label3->Caption = "Версия  4.04.09";
    return;
  }
  AnsiStrRScan(ptr,'.')[0]='\0';
   Label3->Caption = "Версия  " + StrPas(ptr);
  delete [] Data;
*/
//    Label3->Caption = "Версия 4.04";
}
//---------------------------------------------------------------------------

