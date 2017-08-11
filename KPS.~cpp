//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("mPasswordForm.cpp", PasswordForm);
USEFORM("FirmsForm.cpp", FirmForm);
USEFORM("OpAudit.cpp", AuditForm);
USEFORM("mFormGroup.cpp", FormGroup);
USEFORM("mFormOper.cpp", FormOperator);
USEFORM("DataModule.cpp", DataModule1); /* TDataModule: File Type */
USEFORM("Unit2.cpp", Form2);
USEFORM("Unit1.cpp", SubscrForm);
USEFORM("MainPForm.cpp", MainKPSForm);
USEFORM("mSetParams.cpp", SelectParamsForm);
USEFORM("ParamsN.cpp", ParamsForm);
USEFORM("QrepForm.cpp", Form4);
USEFORM("Unit3.cpp", PrintForm3);
//---------------------------------------------------------------------------
#include "Tools_proc.h"
#include "FirmsForm.h"
#include "mPasswordForm.h"
extern bool             SelfCloseFlag;
extern LProfile         *pProfile;
extern AnsiString       Dir;
AnsiString              sOpName;
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
//  AnsiString Dir;
  DWORD      dw_Result;
  AnsiString CurOpName;   //local
  AnsiString sOpName;

  // Установить текущим каталог в котором находится приложение
  ExeName = ParamStr(0);
  Dir = ExtractFileDir(Application->ExeName);
  SetCurrentDir(Dir);

  pProfile = new LProfile();
  pProfile->LoadParameter("Common", "LastName", "");
  sOpName = pProfile->GetValue()->AsStr(0);

  try
  {
    Application->Initialize();
    FirmForm = new TFirmForm(NULL);  /*"Версия 4.04"*/
    Application->ProcessMessages();
    Sleep(2000);
    Application->CreateForm(__classid(TMainKPSForm), &MainKPSForm);
                 delete FirmForm;
    FirmForm = NULL;
    if(!SelfCloseFlag)
      Application->Run();
    if(PasswordForm != NULL)
      delete PasswordForm;
    delete pProfile;
  }
  catch (Exception &exception)
  {
    Application->ShowException(&exception);
  }
  return 0;
}
//---------------------------------------------------------------------------
