//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "Tools_proc.h"
#include "mPasswordForm.h"
#include "MainPForm.h"
//#include "sqlite3ext.h"
//#include "sqlite3.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "_GClass"
#pragma link "AbRMeter"
#pragma link "AbDBCtrls"
#pragma resource "*.dfm"
TMainKPSForm *MainKPSForm;
//=== ���������� ������ =====================================================
LProfile   *pProfile;
AnsiString      Dir;
extern AnsiString  sOpName;
bool          SelfCloseFlag;
//InfoLaunch    st_InfoLaunch;
char *AccRigth[] = {"����� - ������ � ������ ","����� - �������� ����� � ����.","����� - �������������� ������",
                    "P������������� ����������", "�����-������� �����", " "};
//char *RegKey[] = "Software\\KPS";
char Base64[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
                  'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
                  '0','1','2','3','4','5','6','7','8','9',' ','/'};
 OVERLAPPED over;
 OVERLAPPED overlappedwr;
//---------------------------------------------------------------------------
bool AskingMessage0(AnsiString S)
{
   if (Application->MessageBox(&S[1],
      "��������!!!",MB_YESNO | MB_ICONWARNING )== IDYES)
      return true;
   else
     return false;
}
//---------------------------------------------------------------------------
double Round0(double Value, int Precision)
{
  int i, Mod;
  double D;
  long M;
  try
  {
    i = 0; Mod = 1;
    while(i < Precision)
    {
      Mod *= 10;
      i++;
    }
    D = Value * Mod;
    M = floor(D);
    if((D - (double)M) > 0.6)
      M++;
    D = (double)M / Mod;
  }
  catch(...)
  {
    return Value;
  }
  return D;
}
//---------------------------------------------------------------------------
AnsiString ReplZPnaPunk(AnsiString SI)           //float ������ � ������
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
AnsiString ReplPunknaZP(AnsiString SI)           //float ������ � ������
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
AnsiString GetProgramName(AnsiString SI)
{
  AnsiString S;

  int j = SI.AnsiPos(".");
  for(int i = j; i > 1; i--)
  {
    if(SI[i] == '\\')
    {
      S = SI.SubString(i+1,SI.Length() - i);
      break;
    }
  }
  return S;
}
//---------------------------------------------------------------------------
bool PrintProcessList(AnsiString FName)
{
  PROCESSENTRY32 peProcessEntry;
  TCHAR szBuff[1024];
  DWORD dwTemp;
  AnsiString S;
  int Count = 0;
  HANDLE CONST hSnapshot = CreateToolhelp32Snapshot(
                             TH32CS_SNAPPROCESS, 0);
  if(INVALID_HANDLE_VALUE == hSnapshot) {
    return false;
  }

  peProcessEntry.dwSize = sizeof(PROCESSENTRY32);
  Process32First(hSnapshot, &peProcessEntry);
  do {
    S.sprintf("L=== %08X   ---  %s ===\r\n",
             peProcessEntry.th32ProcessID, peProcessEntry.szExeFile);
      if( (AnsiString)peProcessEntry.szExeFile == FName)
        Count++;
     } while(Process32Next(hSnapshot, &peProcessEntry));

  CloseHandle(hSnapshot);
  if(Count > 1)
    return true;
  else
    return false;
}
//---------------------------------------------------------------------------
__fastcall TMainKPSForm::TMainKPSForm(TComponent* Owner)
        : TForm(Owner)
{
  AnsiString  S;
  OpGroup     G;
  Operator    O;
  SelfCloseFlag = false;
  int j;
  float A,B,C;
  csSendToPort = new TCriticalSection();
  ComPortFlag = false;
/////////////////////////////////////////////////////////////////////////
  S = Application->ExeName;
  S = GetProgramName(S);
  Dir = ExtractFileDir(Application->ExeName);
  if(PrintProcessList(S))
  {
    SelfCloseFlag = true;
    Close();
    return;
  }
/////////////////////////////////////////////////////////////////////////
  S = SlashSep(Dir, "DB");
  BaseName = S;
  if(!DirectoryExists(S))
  {
    if (!CreateDir(S))
    {
      S = "�� ������� ����� ��� ��� ������";
      ShowMessage(S);
      SelfCloseFlag = true;
      return;
    }
  }
  Reg = new TRegIniFile("Software\\KPS");
  DM = new TDataModule1(this);
//
  DM->Table1->DatabaseName = BaseName;
  DM->Table2->DatabaseName = BaseName;
  DM->Table3->DatabaseName = BaseName;
  DM->Query1->DatabaseName = BaseName;
  SetCurrentDir(BaseName);
  if(!DM->PGroupsBaseExist())
  {
    if(DM->PGroupsBaseCreated() )
    {
      OpGroup O;
      strcpy(O.GrName, "��������������");
      strcpy(O.GrFullName, "��������� ��������������");
      O.PRights = 0x3FFF;
      O.UndeleteF = 1;
      DM->InsertGroupPx(&O);
    }
    else
    {
      SelfCloseFlag = true;
      return;
    }
  }
  else
  {
  }
  if(!DM->POperatorsBaseExist())
  {
    if(DM->POperatorsBaseCreated() )
    {
      Operator O;
      strcpy(O.OpName, "Admin");
      strcpy(O.Password1, "pass");
      strcpy(O.GroupName, "��������������");
      strcpy(O.SurName, "I");
      strcpy(O.Name, "I");
      strcpy(O.FName, "I");
      O.UndeleteF = 1;
      DM->InsertOperatorPx(&O);
    }
    else
    {
      SelfCloseFlag = true;
      return;
    }
  }
  ParamsForm = new TParamsForm(this, DM, rParams);
  if(!DM->PParametersBaseExist())
  {
    if(DM->PParametersBaseCreated() )
    {
      TDateTime DT;
      DT = Now();
      S = "INSERT INTO Parameters ";
      S += "(Qn10a,DQn10Kta,DQt10Kma,Qn10b,DQn10Ktb,DQt10Kmb,Qn15a,DQn15Kta, DQt15Kma, Qn15b, DQn15Ktb,DQt15Kmb,";
      S += "Qn20a,DQn20Kta,DQt20Kma,Qn20b,DQn20Ktb,DQt20Kmb,QnE101,DQn10Kt1,DQt10Km1,QnE102,DQn10Kt2,DQt10Km2,";
      S += "QnE151,DQn15Kt1,DQt15Km1,QnE152,DQn15Kt2,DQt15Km2,QnE201,DQn20Kt1,DQt20Km1,QnE202,DQn20Kt2,DQt20Km2,";
      S += "PISOQmX1,PISOQmG1,PISOQtX1,PISOQtG1,PISOQnX1,PISOQnG1,PISOQmX2,PISOQmG2,PISOQtX2,PISOQtG2,PISOQnX2,PISOQnG2,";
      S += "POIMLQmX1,POIMLQmG1,POIMLQtX1,POIMLQtG1,POIMLQnX1,POIMLQnG1,POIMLQmX2,POIMLQmG2,POIMLQtX2,POIMLQtG2,POIMLQnX2,POIMLQnG2,";  //POIMLQmG2
      S += "POLDQmXA,POLDQmGA,POLDQtXA,POLDQtGA,POLDQnXA,POLDQnGA,POLDQmXB,POLDQmGB,POLDQtXB,POLDQtGB,POLDQnXB,POLDQnGB,";
      S += "QminLGr,QminRGr,QtLGr,QtRGr,QnLGr,QnRGr,TXolL,TXolR,TGorL,TGorR,VKonst,TimeConst) VALUES (";
      S += "'" + ParamsForm->Qn10a->Text + "','" + ParamsForm->DQn10Kta->Text + "','" + ParamsForm->DQt10Kma->Text + "','";
      S += ParamsForm->Qn10b->Text + (AnsiString)"','" + ParamsForm->DQn10Ktb->Text + (AnsiString)"','" + ParamsForm->DQt10Kmb->Text + (AnsiString)"','";
      S += ParamsForm->Qn15a->Text + (AnsiString)"','" + ParamsForm->DQn15Kta->Text + (AnsiString)"','" + ParamsForm->DQt15Kma->Text + (AnsiString)"','";
      S += ParamsForm->Qn15b->Text + (AnsiString)"','" + ParamsForm->DQn15Ktb->Text + (AnsiString)"','" + ParamsForm->DQt15Kmb->Text + (AnsiString)"','";
      S += ParamsForm->Qn20a->Text + (AnsiString)"','" + ParamsForm->DQn20Kta->Text + (AnsiString)"','" + ParamsForm->DQt20Kma->Text + (AnsiString)"','";
      S += ParamsForm->Qn20b->Text + (AnsiString)"','" + ParamsForm->DQn20Ktb->Text + (AnsiString)"','" + ParamsForm->DQt20Kmb->Text + (AnsiString)"','";
      S += ParamsForm->QnE101->Text + (AnsiString)"','" + ParamsForm->DQn10Kt1->Text + (AnsiString)"','" + ParamsForm->DQt10Km1->Text + (AnsiString)"','";
      S += ParamsForm->QnE102->Text + (AnsiString)"','" + ParamsForm->DQn10Kt2->Text + (AnsiString)"','" + ParamsForm->DQn10Kt2->Text + (AnsiString)"','";
      S += ParamsForm->QnE151->Text + (AnsiString)"','" + ParamsForm->DQn15Kt1->Text + (AnsiString)"','" + ParamsForm->DQt15Km1->Text + (AnsiString)"','";
      S += ParamsForm->QnE152->Text + (AnsiString)"','" + ParamsForm->DQn15Kt2->Text + (AnsiString)"','" + ParamsForm->DQt15Km2->Text + (AnsiString)"','";
      S += ParamsForm->QnE201->Text + (AnsiString)"','" + ParamsForm->DQn20Kt1->Text + (AnsiString)"','" + ParamsForm->DQt20Km1->Text + (AnsiString)"','";
      S += ParamsForm->QnE202->Text + (AnsiString)"','" + ParamsForm->DQn20Kt2->Text + (AnsiString)"','" + ParamsForm->DQt20Km2->Text + (AnsiString)"','";
      S += ParamsForm->PISOQmX1->Text + (AnsiString)"','" + ParamsForm->PISOQmG1->Text + (AnsiString)"','" + ParamsForm->PISOQtX1->Text + (AnsiString)"','";
      S += ParamsForm->PISOQtG1->Text + (AnsiString)"','" + ParamsForm->PISOQnX1->Text + (AnsiString)"','" + ParamsForm->PISOQnG1->Text + (AnsiString)"','";
      S += ParamsForm->PISOQmX2->Text + (AnsiString)"','" + ParamsForm->PISOQmG2->Text + (AnsiString)"','" + ParamsForm->PISOQtX2->Text + (AnsiString)"','";
      S += ParamsForm->PISOQtG2->Text + (AnsiString)"','" + ParamsForm->PISOQnX2->Text + (AnsiString)"','" + ParamsForm->PISOQnG2->Text + (AnsiString)"','";
      S += ParamsForm->POIMLQmX1->Text + (AnsiString)"','" + ParamsForm->POIMLQmG1->Text + (AnsiString)"','" + ParamsForm->POIMLQtX1->Text + (AnsiString)"','";
      S += ParamsForm->POIMLQtG1->Text + (AnsiString)"','" + ParamsForm->POIMLQnX1->Text + (AnsiString)"','" + ParamsForm->POIMLQnG1->Text + (AnsiString)"','";
      S += ParamsForm->POIMLQmX2->Text + (AnsiString)"','" + ParamsForm->POIMLQmG2->Text + (AnsiString)"','" + ParamsForm->POIMLQtX2->Text + (AnsiString)"','";
      S += ParamsForm->POIMLQtG2->Text + (AnsiString)"','" + ParamsForm->POIMLQnX2->Text + (AnsiString)"','" + ParamsForm->POIMLQnG2->Text + (AnsiString)"','";
      S += ParamsForm->POLDQmXA->Text + (AnsiString)"','" + ParamsForm->POLDQmGA->Text + (AnsiString)"','" + ParamsForm->POLDQtXA->Text + (AnsiString)"','";
      S += ParamsForm->POLDQtGA->Text + (AnsiString)"','" + ParamsForm->POLDQnXA->Text + (AnsiString)"','" + ParamsForm->POLDQnGA->Text + (AnsiString)"','";
      S += ParamsForm->POLDQmXB->Text + (AnsiString)"','" + ParamsForm->POLDQmGB->Text + (AnsiString)"','" + ParamsForm->POLDQtXB->Text + (AnsiString)"','";
      S += ParamsForm->POLDQtGB->Text + (AnsiString)"','" + ParamsForm->POLDQnXB->Text + (AnsiString)"','" + ParamsForm->POLDQnGB->Text + (AnsiString)"','";
      S += ParamsForm->QminLGr->Text + (AnsiString)"','" + ParamsForm->QminRGr->Text + (AnsiString)"','" + ParamsForm->QtLGr->Text + (AnsiString)"','";
      S += ParamsForm->QtRGr->Text + (AnsiString)"','" + ParamsForm->QnLGr->Text + (AnsiString)"','" + ParamsForm->QnRGr->Text + (AnsiString)"','";
      S += ParamsForm->TXolL->Text + (AnsiString)"','" + ParamsForm->TXolR->Text + (AnsiString)"','" + ParamsForm->TGorL->Text + (AnsiString)"','";
      S += ParamsForm->TGorR->Text + (AnsiString)"','" + ParamsForm->VKonst->Text + (AnsiString)"','" + ParamsForm->TimeConst->Text + (AnsiString)"')";
      DM->InsertParametersPx(S);
    }
    else
    {
      SelfCloseFlag = true;
      return;
    }
  }
//  WorkWSReestr();
  pProfile->LoadParameter("Common", "ServerName", "A");
  DM->ServerName = pProfile->GetValue()->AsStr(0);
  DBName = "KPA"; //
  if(DM->ServerName == "A")
  {
    S = "�� ������ ��� ������� � ��������";
    ShowMessage(S);
    SelfCloseFlag = true;
    return;
  }
  pProfile->LoadParameter("Grenc", "CountGr", 0);
  int CountGr = pProfile->GetValue()->AsInt(0);
  Grenc Gr;
  for(j = 1;  j <= CountGr; j++ )
  {
    S = (AnsiString)j;
    pProfile->LoadParameter("Grenc", S, "0");
    Gr.LGr = pProfile->GetValue()->AsFloat(0);
    Gr.RGr = pProfile->GetValue()->AsFloat(1);
    Gr.Const = pProfile->GetValue()->AsFloat(2);
    DM->GrencList.push_back(Gr);
  }
  pProfile->LoadParameter("Common", "Number", 0);
  CamerNUM = pProfile->GetValue()->AsInt(0);
  pProfile->LoadParameter("Common", "Comport", "Com3");
  ComportName = pProfile->GetValue()->AsStr(0);
  pProfile->LoadParameter("Common", "MaxUValue", 725);
  MaxUValue = pProfile->GetValue()->AsInt(0);
  pProfile->LoadParameter("Common", "MinUValue", 530);
  MinUValue = pProfile->GetValue()->AsInt(0);
  pProfile->LoadParameter("Common", "HavUValue", 512);
  HavUValue = pProfile->GetValue()->AsInt(0);
  pProfile->LoadParameter("Common", "BegTicCount", 100000);
  BegTicCount = pProfile->GetValue()->AsInt(0);
  pProfile->LoadParameter("Common", "Flag_Q_Control_Off", 0);
  Flag_Q_Control_Off = pProfile->GetValue()->AsInt(0);

  pProfile->LoadParameter("Common", "StartStopExt", 0);
  StartStopExt = pProfile->GetValue()->AsInt(0);
  pProfile->LoadParameter("Common", "QMA", 0);
  QMA = pProfile->GetValue()->AsInt(0);
  pProfile->LoadParameter("Common", "UpdateScreen", 1);
  UpdateScreen = pProfile->GetValue()->AsInt(0);
  if(UpdateScreen == 0) UpdateScreen = 1;
  pProfile->LoadParameter("Common", "Video", 0);
  FlagVideo = pProfile->GetValue()->AsInt(0);
  pProfile->LoadParameter("Common", "PhotoPrio", 1);
  PhotoPrio = pProfile->GetValue()->AsInt(0);

  StatusBar1->Panels->Items[1]->Text = "�������� ��������� ���������, �������� ����� ����������!";
  ProgramState = 0;
  Label45->Caption = ProgramState;
  reader = 0;
  Q0 = Q1 = Q2 = 0.0;
  Vertuschka = 0;
  delete ParamsForm;
  DM->OpName = OldOpName;
  //������� ���������� ��� �������
  FeelOperatorsTable();
  FeelGroupsTable();
  if(!PassShow())
  {
    SelfCloseFlag = true;
//  Priznak = 1;
    Close();
    return;
  }
//  WorkWSReestr();
//    ������ � �������
  CamerWorkingFlag = true;
  if(!CameraWorking())
  {
    FullFileName = SlashSep(Dir, "2.bmp");
    CamerImage->Picture->LoadFromFile(FullFileName);
    CamerImage->Repaint();
    CamerWorkingFlag = false;
    ShowMessage(" ��� ���������� ������! ���������� ������ � ������������� ���������");
    SelfCloseFlag = true;
  }
  else
  {
    FullFileName = SlashSep(Dir, "2.bmp");
    CamerImage->Picture->LoadFromFile(FullFileName);
    CamerImage->Repaint();
  }
  int t = rStStop;
  if(!(DM->OpRights & t))
    TickTestBtn->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TMainKPSForm::SvjazSettingClick(TObject *Sender)
{
  try
  {
    if(!FlagVvodaParamsProliv) return;              //�� ������� ��������� ������� � ���������
    if(ComPortFlag) return;                    //������� ��� �������
    if(reader)
      DelComPortAndReader();
    ProgressBar1->Visible = false;
    if(!TickTestBtn->Checked)
    {
      Label36->Visible = false;
      Label39->Visible = false;
    }
    DTAnswer = Now();
    reader = 0;
    pProfile->LoadParameter("Common", "Comport", "Com3");
    ComportName = pProfile->GetValue()->AsStr(0);
//    RestartFlag = false;
  //  ������ � ��� ������
  //  AnsiString portname;
    DCB   dcb;  //struct
    if(!ComPortOpen())
    {
      FullFileName = SlashSep(Dir, "3.bmp");
      ComPortImage->Picture->LoadFromFile(FullFileName);
      ComPortImage->Repaint();
      ComPortFlag = false;
      FlagGetDate = false;
      FullFileName = SlashSep(Dir, "3.bmp");
      PriborImage->Picture->LoadFromFile(FullFileName);
      PriborImage->Repaint();
      PriborImageState = false;
      StatusBar1->Panels->Items[1]->Text = " �������� ����� ����������������� �����! B������� ������ ����� ����� � ���������!";
      Beep();
      return;
    }
    else
    {
      FullFileName = SlashSep(Dir, "2.bmp");
      ComPortImage->Picture->LoadFromFile(FullFileName);
      ComPortImage->Repaint();
      ComPortFlag = true;
//      FlagGetDate = true;
      ProgramState = 1;
      Label45->Caption = ProgramState;
    }
    if(QminRb->Checked)
    {
      QminRb->Checked = false;
      QminRb->Checked = true;
    }
    if(QtRb->Checked)
    {
      QtRb->Checked = false;
      QtRb->Checked = true;
    }
    if(QnomRb->Checked)
    {
      QnomRb->Checked = false;
      QnomRb->Checked = true;
    }
    SvjazSetting->Enabled = false;
    SvjazSetting->Color = clInactiveCaption;
    StatusBar1->Panels->Items[1]->Text = "��������� �������� �����!";
    ClearPanel->Enabled = true;
    ClearPanel->Color = clLime;
    TimerTickCount = 0;
    Timer1->Interval = 3000;
    Timer1->Enabled = true;
    StartProlivBtn->Enabled = true;
    StartProlivBtn->Color = clLime;
    FlagProliva = false;
  }
  catch(...)
  {
    StatusBar1->Panels->Items[1]->Text = " ��������� ���������� ��������� ��������� ����� �� ������!";
  }
  StatusBar1->Panels->Items[1]->Text = "��������� ������� ���������� ������!";
}
//---------------------------------------------------------------------------
bool TMainKPSForm::CameraWorking(void)
{
  hWndC = capCreateCaptureWindow("",WS_DISABLED,0,0,0,0,0,0); // ������� ���� ������
  CamerConectFlag = capDriverConnect(hWndC,CamerNUM);           // ���������� � ������ ������ (���������� ��������)
  if(!CamerConectFlag)
  {
    for(int i = 0; i < 9; i++)
    {
      CamerConectFlag = capDriverConnect(hWndC,CamerNUM);           // ���������� � ������ ������ (���������� ��������)
      Sleep(50);
      if(CamerConectFlag) break;
    }
    if(!CamerConectFlag)
    {
//      ImageList1->Draw(CamerImage->Canvas,0,0,3,true);
      FullFileName = SlashSep(Dir, "3.bmp");
      CamerImage->Picture->LoadFromFile(FullFileName);
      CamerImage->Repaint();
      DestroyWindow(hWndC);                // ������� ����
      return false;
    }
    else
    {
      FullFileName = SlashSep(Dir, "2.bmp");
      CamerImage->Picture->LoadFromFile(FullFileName);
      CamerImage->Repaint();
    }
  }
  else
  {
    FullFileName = SlashSep(Dir, "2.bmp");
    CamerImage->Picture->LoadFromFile(FullFileName);
    CamerImage->Repaint();
  }
  return true;
};
//---------------------------------------------------------------------------
bool TMainKPSForm::ComPortOpen(void)
{
//  AnsiString   portname;
  DCB          dcb;  //struct
  COMMTIMEOUTS timeouts;
  char         C[128];                                                           //CREATE_NEW|
  try
  {
    ComPort = NULL;
    ComPort = CreateFile(ComportName.c_str(),GENERIC_READ|GENERIC_WRITE,0, NULL,OPEN_EXISTING,FILE_FLAG_OVERLAPPED, NULL);
    if(ComPort == INVALID_HANDLE_VALUE)
    {
      if(ComPort == INVALID_HANDLE_VALUE)
      {
        for( int i = 0; i < 2; i++)
        {
          CloseHandle(ComPort); //������� ����
          Sleep(200);
          ComPort = CreateFile(ComportName.c_str(),GENERIC_READ|GENERIC_WRITE,0, NULL,OPEN_EXISTING,FILE_FLAG_OVERLAPPED, NULL);
          if(ComPort != INVALID_HANDLE_VALUE)
            break;
        }
        if(ComPort == INVALID_HANDLE_VALUE)
        {
          return false;
        }
      }
    }
    //������� ��������� �� �����
    if(!GetCommState(ComPort, &dcb)) //?���� �� �������
    {
      RdCOMClose();
      ShowMessage ("�� ������� ������� DCB");
      return false;
    }
    dcb.BaudRate = DM->Speed; //�������� ������� 115200 ���
    dcb.fBinary = TRUE; //�������� �������� ����� ������
    dcb.fOutxCtsFlow = FALSE; //�������� ����� �������� �� �������� CTS
    dcb.fOutxDsrFlow = FALSE; //��������� ����� �������� �� �������� DSR
    dcb.fDtrControl = DTR_CONTROL_DISABLE; //��������� ������������� ����� DTR
    dcb.fDsrSensitivity = FALSE; //��������� ��������������� �������� � ��������� ����� DSR
    dcb.fNull = FALSE; //��������� ����� ������� ������
    dcb.fRtsControl = RTS_CONTROL_DISABLE; //��������� ������������� ����� RTS
    dcb.fAbortOnError = FALSE; //��������� ��������� ���� �������� ������ ������ ��� ������
    dcb.ByteSize = 8; //������ 8 ����� � �����
    dcb.Parity = 0; //��������� �������� ��������
    dcb.StopBits = 0; //������ ���� ���� ���
    //��������� ��������� ��� � ����
    if(!SetCommState(ComPort, &dcb)) //���� �� �������  - ������� ������� � ������ ���������
    {
      RdCOMClose();
      ShowMessage(" �� ������� ���������� BCB");
      return false;
    }
    //���������� ��������
    timeouts.ReadIntervalTimeout = 0; //������� ����� ����� ���������
    timeouts.ReadTotalTimeoutMultiplier = 0; //����� ������� �������� ������
    timeouts.ReadTotalTimeoutConstant = 0; //��������� ��� ������ �������� �������� ������
    timeouts.WriteTotalTimeoutMultiplier = 1; //����� ������� �������� ������
    timeouts.WriteTotalTimeoutConstant = 10; //��������� ��� ������ �������� �������� ������
    //�������� ��������� ��������� � ����
    if(!SetCommTimeouts(ComPort, &timeouts))
    {
      RdCOMClose();                             //���� �� �������
      ShowMessage(" �� ������� �������� ��������� ��������� � ����");
      return false;
    }
    //���������� ������� ������� ������ � �������
    SetupComm(ComPort,2000,2000);
    PurgeComm(ComPort, PURGE_RXCLEAR);         //    �������� ����� �����
    reader = new TThreadReader(false, ComPort); //    ������ ������ ������
    TDateTime DT = Now();
    reader->DT = DT;        //        ��� �������� ������ ���������� � ��������
    HWND hWnd;
    LPCTSTR lpszClass;
    LPCTSTR lpszWindow;	                       // ��������� ����� ����
    hWnd = GetForegroundWindow();
    reader->Form1Handle = hWnd;
    reader->FreeOnTerminate = true;
    return true;
  }
  catch(...)
  {
    StatusBar1->Panels->Items[1]->Text = " ��������� ���������� ��������� ComPortOpen �� ������!";
  }
  return true;
}
//---------------------------------------------------------------------------
void   TMainKPSForm::KommandIntoIS(int Code)
{
  BuffOut[0] = Code; //0x43;          //����������  ������� ������� ����������
  memset(BuffOut+1,0,4);
  pBuffOut = BuffOut + 0;  //[0];
  BuffOutLen = 5;
    reader->Suspend();                       //
  writer = new TThreadWriter(true, ComPort,pBuffOut, BuffOutLen);
    BYTE A,B;
    int  C;
    memcpy(&A, &writer->wrbuf2[0] ,1);
    memcpy(&B, &writer->wrbuf2[1] ,1);
    memcpy(&C, &writer->wrbuf2[2] ,4);
    AnsiString SS = (AnsiString)A + (AnsiString)" " + (AnsiString)B + (AnsiString)" " + (AnsiString)C;
    Label55->Caption = SS;
  delete writer;
    reader->Resume();                       //
}
//---------------------------------------------------------------------------
void  __fastcall TMainKPSForm::AnswerEvent(TMessage& Msg)
{
  AnsiString S;
  int        i;
  float      d1, d2, f;
  BYTE       B;
  try
  {
    FlagGetDate = true;
    IntPaketCount++;
    if(!PriborImageState)
    {
      PriborImageState = true; // ����� �� �������� � ������ ����� �������
      FullFileName = SlashSep(Dir, "2.bmp");
      PriborImage->Picture->LoadFromFile(FullFileName);
      PriborImage->Canvas->Refresh();
    }
    DTAnswer = Now();
    memcpy(&BufferVVODA, &reader->Cbufrd, 32);
    memcpy(&DM->RecData.Uval.RD.Status,   BufferVVODA+1, 1);   //���� ���������
    memcpy(&DM->RecData.Uval.RD.TVozd,    BufferVVODA+2, 4);   //� �������
    memcpy(&DM->RecData.Uval.RD.Vlagnost, BufferVVODA+6, 4);   //���������
    memcpy(&DM->RecData.Uval.RD.TVodY,    BufferVVODA+10, 4);  //� ����
    memcpy(&DM->RecData.Uval.RD.Napruga,  BufferVVODA+14, 2);  //U �������
    memcpy(&DM->RecData.Uval.RD.Q,        BufferVVODA+16, 4);  //Q
    memcpy(&DM->RecData.Uval.RD.TimeInt,  BufferVVODA+20, 4);  //��������
    memcpy(&DM->RecData.Uval.RD.CountN,   BufferVVODA+24, 4);  //������� �����������
    memcpy(&DM->RecData.Uval.RD.Count,    BufferVVODA+28, 4);  //������� �����
    Label56->Caption = (AnsiString)reader->ErrCount;
    if(FlagRead_T_After_Proliv)
    {
      FlagRead_T_After_Proliv = false;
      TempratEndProliv = DM->RecData.Uval.RD.TVodY;
    }

    int g = Panel3->Caption.ToInt();
    g++;
    if(g > 9) g = 0;
    Panel3->Caption = (AnsiString)g;
    Vertuschka++;      //��������� �������� �� ����
    if(Vertuschka == 3) Vertuschka = 0;
    switch(Vertuschka)
    {
      case 0: Q0 = DM->RecData.Uval.RD.Q; break;
      case 1: Q1 = DM->RecData.Uval.RD.Q; break;
      case 2: Q2 = DM->RecData.Uval.RD.Q; break;
    }
    if(QMA != 0)
      QSA = Round0((Q0 + Q1 + Q2)/3, 4);
    else
      QSA = DM->RecData.Uval.RD.Q;
    Label43->Caption = S.sprintf("%4.2f", DM->RecData.Uval.RD.TVodY); //T vody
    if(IntPaketCount%UpdateScreen == 0)
    {
      Label37->Caption = S.sprintf("%5.3f", Round0(QSA,3));      //metry 3
      Label38->Caption = S.sprintf("%5.1f", Round0(QSA*1000,1)); //liytr 3
      AbDB270Meter1->Value = Round0((QSA*1000), 0);
    }
    Label24->Caption = S.sprintf("%4.2f", DM->RecData.Uval.RD.TVozd); //T vozd
    Label54->Caption = S.sprintf("%4.2f", DM->RecData.Uval.RD.Vlagnost); //T vlaga
    float f = Round0(0.005 * DM->RecData.Uval.RD.Napruga,2); //U
    Label32->Caption = S.sprintf("%4.2f",f);

    B = DM->RecData.Uval.RD.Status;
//    S.sprintf("%x",B);
//    Label58->Caption = S;


    if(DM->RecData.Uval.RD.Status != 0)
    {
      B = DM->RecData.Uval.RD.Status;
      if(B & 0x01)  //��� � 0
      {    //(�������� ����� ������ �� ����������������� �����, ��������� �������� ������
//      SendLastCommand();
      }
      else
      {
      }
      if(B & 0x02)    //��� � 1
      {    //������ ������� ����������� ����
        Image6->Visible = true;
        Temp->Visible = true;
//        StatusBar1->Panels->Items[1]->Text = "������ ������� �����������! �������� �� ����������� ";
//        Beep();
      }
      else
      {
        Image6->Visible = false;
        Temp->Visible = false;
      }
/*
      if(B & 0x04)    //��� � 2
      {    //�������� ��������� ���������� ����� �����������
        Image7->Visible = true;
        MaxQ->Visible = true;
//        StatusBar1->Panels->Items[1]->Text = "�������� ����� ����: �������� ��������� ���������� ����� �����������!";
        Beep();
      }
      else
      {
        Image7->Visible = false;
        MaxQ->Visible = false;
      }
      if(B & 0x08)    //��� � 3
      {    //����� ����������� ������ �����������
        Image4->Visible = true;
        MinQ->Visible = true;
//        StatusBar1->Panels->Items[1]->Text = "�������� ����� ����: ����� ����������� ������ �����������!";
        Beep();
      }
      else
      {
        Image4->Visible = false;
        MinQ->Visible = false;
      }
*/
/*
      if(B & 0x10)   //��� � 4
      {    //������ ���������� �������
        Image2->Visible = true;
        Bat->Visible = true;
//        StatusBar1->Panels->Items[1]->Text = "������ ����������: ������ ���������� �������!";
      }
      else
      {
        Image2->Visible = false;
        Bat->Visible = false;
      }
*/
      if(B & 0x20)   //��� � 5
      {    //������ ������� ����������� � ��������� �������
        Image3->Visible = true;
        Label13->Visible = true;
//        StatusBar1->Panels->Items[1]->Text = "������ ������� ����������� � ��������� �������! ������� ������ �������!";
        Beep();
      }
      else
      {
        Image3->Visible = false;
        Label13->Visible = false;
      }
/*
      if(B & 0x40)   //��� � 6
      {    //�������� ���������� �������
        Image5->Visible = true;
        Label12->Visible = true;
//        StatusBar1->Panels->Items[1]->Text = "������ ����������: �������� ���������� �������!";
      }
      else
      {
        Image5->Visible = false;
        Label12->Visible = false;
      }
*/
      if(B & 0x80)   //��� � 7
      {
//        Label58->Caption = "1";
        Image7->Visible = true;
        Knopka->Visible = true;
        if((StartStopExt)&&(TickTestBtn->Checked))
        {
          if(ProgramState < 2)
          {
            Start_Stop();  //������ �����_����
            StatusBar1->Panels->Items[1]->Text = "�����-���� �� ����������";
//            Image7->Visible = true;
//            Knopka->Visible = true;
            return;
          }
        }
      }
      else         ///if(B & 0x80 == 0 )   //��� � 7
      {
//        Label58->Caption = "0";
        Image7->Visible = false;
        Knopka->Visible = false;
        if((StartStopExt)&&(TickTestBtn->Checked))
        {
          if(ProgramState == 3)
          {
//            Image7->Visible = false;
//            Knopka->Visible = false;
            Stop_Start();    //STOP �����_����
            return;
          }
        }
      }
    }
    else
    {
      Image2->Visible = false;
      Image3->Visible = false;
      Image5->Visible = false;
      Image6->Visible = false;
      Image7->Visible = false;
      Label12->Visible = false;
      Bat->Visible = false;
      Temp->Visible = false;
      Label13->Visible = false;
      Knopka->Visible = false;
    }
    if(DM->RecData.Uval.RD.Status == 0 )
    {
//      Label58->Caption = "0";
      Image7->Visible = false;
      Knopka->Visible = false;
      if((StartStopExt)&&(TickTestBtn->Checked))
      {
        if(ProgramState == 3)
        {
//          Image7->Visible = false;
//          Knopka->Visible = false;
          Stop_Start();     //STOP �����_����
          return;
        }
      }
    }
    if((DM->RecData.Uval.RD.Napruga < MaxUValue)&&(DM->RecData.Uval.RD.Napruga > MinUValue))
    {
      Image2->Visible = false;
      Bat->Visible = false;
      Image5->Visible = false;
      Label12->Visible = false;
//      StatusBar1->Panels->Items[1]->Text = "";
    }
    if((DM->RecData.Uval.RD.Napruga < MinUValue)&&(DM->RecData.Uval.RD.Napruga > HavUValue))
    {
      Image2->Visible = true;
      Bat->Visible = true;
//      StatusBar1->Panels->Items[1]->Text = "�������: ������ ���������� �������!";
      Beep();
    }
    if((DM->RecData.Uval.RD.Napruga > MaxUValue)||(DM->RecData.Uval.RD.Napruga < HavUValue))
    {
      Image5->Visible = true;
      Label12->Visible = true;
//      StatusBar1->Panels->Items[1]->Text = "�������: ��������� ���������� �������! ��������� ������";
//      ShowMessage{"�������: ��������� ���������� �������! ��������� ������ � ������� �������");
//      KommandIntoIS(0x50);
      Beep();
    }
    if(ProgramState == 2)  //���� ������
    {
      if(!((QSA <= QmaxCurProliv)&&(QSA >= QminCurProliv)))
      {
        switch (NumCodeProv)
        {
          case 0: EndCalcMin = false; BegCalcMin = false; break;
          case 1: EndCalcT = false;   BegCalcT = false;   break;
          case 2: EndCalcN = false;   BegCalcN = false;   break;
        }
        S.sprintf("������������ ������ �� ����� ����� = %5.4f", QSA);
        ShowMessage(S);
        ClearPanelClick(NULL);
//Pozor  ������� ������
          return;
      }
    }
    if(ProgramState == 2)  //���� ������
    {
      ForCurCountValue = CurCountValue;
      CurCountValue = DM->RecData.Uval.RD.Count;  //�������� �������� �� ��������� ������ DM->RecData.Uval.RD.Count
      CountRecivedAnswer++;              // ����� ���������� �� �� �������
      if(CountRecivedAnswer == 1)
        TempratBegProliv = DM->RecData.Uval.RD.TVodY;
      SummOF_Q_Proliva += DM->RecData.Uval.RD.Q;       //C���� ���� Q �������
      AnsiString SSS;
      int z = MaxProlivCountValue - CurCountValue;
      i = z;
      if( CurCountValue > MaxProlivCountValue) z = 0;

      for( int j = 0; j < (int)DM->GrencList.size(); j++)
      {
        if((QSA >= DM->GrencList[j].LGr)&&(QSA <= DM->GrencList[j].RGr))
        {
          i = (int)((float)i  / DM->GrencList[j].Const);
          break;
        }
      }

//      if(i  <=  MaxProlivCountValue)
//      {
//        Label57->Caption = SSS.sprintf("%3.2f�",(float)i/1000);
//         float f = (((int)dVImp - i)/1000)/QSA;
//        SSS = "0c";
//        Label35->Caption = SSS; ///////.sprintf("%d�", (int)f);
//      }
      if((CurCountValue == 0))  //������ ���� ���������� �������  (CurCountValue <= TicBetween)||
      {
        FlagBegProliva = false;  //��������� ������ (�� ����� ����� ������ �� ���� ��������� ��������� )
        KommandIntoIS(0x43);      //���������� � ������ ������� ���������� �������
        ProgressBar1->Visible = false; //Position = MaxProlivCountValue;
        StopTime = Now();
        QSredneeProliva = SummOF_Q_Proliva/CountRecivedAnswer;   //  m3/h
        TimeOfProliv = DM->RecData.Uval.RD.TimeInt; //milisek
        Label51->Visible = true;
        Label52->Visible = true;
        Label47->Visible = true;
        Label48->Visible = true;
        Label52->Caption = S.sprintf("%4.3f",(float)TimeOfProliv/1000);
        Label48->Caption = S.sprintf("%4.3f",QSredneeProliva);
        Label57->Caption = SSS.sprintf("%3.2f�",(float)i/1000);
        f = ((MaxProlivCountValue - i)/1000)/QSA;
        SSS = "0c";
        Label35->Caption = SSS; ///////.sprintf("%d�", (int)f);
//        if(FlagVideo == 0)
//          ShowProliv2End();
      }
      else
      {
        if(i  <=  ProgressBar1->Max)
        {
          ProgressBar1->Position = i;
          ProgressBar1->Repaint();
          Label39->Caption = (AnsiString)i;
          Label57->Caption = SSS.sprintf("%3.2f�",(float)i/1000);
          f = (3.6*(MaxProlivCountValue - i)/1000)/QSA;
          SSS = (AnsiString)(int)f + "c";
          Label35->Caption = SSS; ///////.sprintf("%d�", (int)f);
        }
      }
    }
    if(ProgramState == 3)  //���� �������� ����������
    {
      CountRecivedAnswer++;              // ����� ���������� �� �� �������
      SummOF_Q_Proliva += DM->RecData.Uval.RD.Q;       //C���� ���� Q �������
      Label39->Caption = (AnsiString)(BegTicCount - DM->RecData.Uval.RD.Count);   //tiki
      Label52->Caption =  S.sprintf("%4.3f",(float)DM->RecData.Uval.RD.TimeInt/1000);//(AnsiString)(DM->RecData.Uval.RD.TimeInt);               //msek
    }
  }
  catch(...)
  {
    StatusBar1->Panels->Items[1]->Text = " ��������� ���������� ��������� AnswerEvent �� ������!";
  }
}
//---------------------------------------------------------------------------
void TMainKPSForm::RdCOMClose()
{
  try
  {
    if(reader) reader->Terminate(); //???? ????? ?????? ????????, ????????? ???; ????????
    if(ComPortFlag)
      CloseHandle(ComPort); //������� ����
    ComPort=0; //???????? ?????????? ??? ??????????? ?????
  }
  catch(...)
  {
  }
}
/*
//---------------------------------------------------------------------------
void __fastcall TMainKPSForm::SendIntoPort(AnsiString S)
{
   memset(bufwr,0,sizeof(bufwr));
   PurgeComm(ComPort, PURGE_TXCLEAR);
   strcpy(bufwr,S.c_str());
   writer = new TThreadWriter(false, ComPort, S);
   writer->FreeOnTerminate = true;
}
*/
//---------------------------------------------------------------------------
void TMainKPSForm::FeelOperatorsTable(void)
{
  AnsiString S;
  Operator   O;
  // ������� ����� � ���
  S  = "Select * from Operators.db order by OpName;";
//  if(!DM->SQLRead(S))
  if(!DM->OperatorsRead(S))
  {
    ShowMessage("�� ���� ������� ������� ���������� � ���");
    return;
  }
  DM->OpList.clear();
  DM->Query2->First();
  while(!DM->Query2->Eof)
  {
    strcpy(O.OpName, Trim(DM->Query2->FieldByName("OpName")->AsString).c_str());
    strcpy(O.GroupName, Trim(DM->Query2->FieldByName("GroupName")->AsString).c_str());
    strcpy(O.SurName, Trim(DM->Query2->FieldByName("SurName")->AsString).c_str());
    strcpy(O.Name, Trim(DM->Query2->FieldByName("Name")->AsString).c_str());
    strcpy(O.FName, Trim(DM->Query2->FieldByName("FName")->AsString).c_str());
    AnsiString S =  Trim(DM->Query2->FieldByName("Password1")->AsString);
    for(int i = 1; i <= S.Length(); i++)    S[i] = S[i] + i;
    strcpy(O.Password1, S.c_str());
    O.UndeleteF = DM->Query2->FieldByName("UndeleteF")->AsInteger; //��������� � ����
    DM->OpList.push_back(O);
    DM->Query2->Next();
  }
  DM->Query2->Close();
}
/*
//---------------------------------------------------------------------------
AnsiString TMainKPSForm::CreateDBSQLGet(AnsiString DBName)
{
    //��������� SQL ������ �������� ����������� ��
  AnsiString S;

  S = "CREATE DATABASE " + DBName ;
  S = S + " ON (name = '" +  DBName + "', filename = '" +
      Dir + "\\DB\\" + DBName + ".MDF" + "', size = 5)";
  S = S + " LOG ON (name = '" +  DBName + "_LOG" + "', filename = '" +
      Dir + "\\DB\\" + DBName + "_LOG.LDF" + "', size = 5)";
  return S;
}
*/
//---------------------------------------------------------------------------
/*
void __fastcall TMainKPSForm::FeelGroupsTable(void)
{
  OpGroup G;
  // ������� ����� � ���
  DM->Query1->Close();
  DM->Query1->Prepare();
  DM->Query1->SQL->Clear();
  DM->Query1->SQL->Add("Select * from Groups.db order by GrName");
  DM->Query1->Open();
  DM->Query1->First();
  DM->GrList.erase(DM->GrList.begin(), DM->GrList.end());
  while(!DM->Query1->Eof)
  {
    strcpy(G.GrName, DM->Query1->FieldByName("GrName")->AsString.c_str());
    strcpy(G.GrFullName, DM->Query1->FieldByName("GrFullName")->AsString.c_str());
    G.UndeleteF = DM->Query1->FieldByName("UndeleteF")->AsBoolean; //��������� � ����
    G.PRights      = DM->Query1->FieldByName("PRights")->AsInteger;
    DM->GrList.push_back(G);
    DM->Query1->Next();
  }
  DM->Query1->Close();
}
*/
//---------------------------------------------------------------------------
void TMainKPSForm::FeelGroupsTable(void)
{
  AnsiString S;
  OpGroup    G;
  // ������� ����� � ���
  S = "Select * from Groups.db order by GrName";
//  if(!DM->SQLRead(S))
  if(!DM->GroupsRead(S))   //GroupsRead
  {
    ShowMessage("�� ���� ������� ������� ����� � ���");
    return;
  }
  DM->Query1->First();        //ADOQuery1
  DM->GrList.clear();
  while(!DM->Query1->Eof)
  {
    strcpy(G.GrName, DM->Query1->FieldByName("GrName")->AsString.c_str());        //vos  ADOQuery1
    strcpy(G.GrFullName, DM->Query1->FieldByName("GrFullName")->AsString.c_str());
    G.UndeleteF = DM->Query1->FieldByName("UndeleteF")->AsInteger; //��������� � ����
    G.PRights      = DM->Query1->FieldByName("PRights")->AsInteger;
    DM->GrList.push_back(G);
    DM->Query1->Next();
  }
  DM->Query1->Close();
}
//---------------------------------------------------------------------------
bool TMainKPSForm::PassShow(void)
{
  PasswordForm = new TPasswordForm(this, DM);
  if(PasswordForm->ShowModal() != ID_OK)
  {
    delete PasswordForm;
    PasswordForm = NULL;
    return false;
  }
  if(PasswordForm->Result)
  {
    DM->OpName      = PasswordForm->Name;    //������� ��������
    DM->OpRights    = PasswordForm->Rights;  //����� ������� �������� ���������
    DM->GroupName   = PasswordForm->GroupName;
  }
  else
  {
    delete PasswordForm;
    PasswordForm = NULL;
    return false;
  }
  delete PasswordForm;
  PasswordForm = NULL;
  return true;
}
/*
//---------------------------------------------------------------------------
void __fastcall TMainForm::PassShow(void)
{
  PasswordForm = new TPasswordForm(NULL, DM);
  if(PasswordForm->ShowModal() != ID_OK)
  {
    SelfCloseFlag = true;
    return;
  }
  if(PasswordForm->Result)
  {
    DM->CurOpName   = PasswordForm->Name;    //������� ��������
    DM->OpRights    = PasswordForm->Rights;  //����� ������� �������� ���������
    DM->GroupName   = PasswordForm->GroupName;
  }
  else
  {
    SelfCloseFlag = true;
    return;
  }
  delete PasswordForm;
  PasswordForm = NULL;
}
*/
//---------------------------------------------------------------------------
void __fastcall TMainKPSForm::OpDispClick(TObject *Sender)
{        //����� ���������� ����������
  TStringList* KList;
  AnsiString S;
  int i;

  if(!(DM->OpRights & rAudit)) return;
  AuditForm = new TAuditForm(this, DM);
  KList = new TStringList;
  for(i = 0; i < 3; i++)
  {
    S = AccRigth[i];
    KList->Add(S);
  }
  AuditForm->CheckListBox1->Clear();
  for(i = 0; i < 3; i++)
  {
     AuditForm->CheckListBox1->Items->Add(KList->Strings[i]);
     AuditForm->CheckListBox1->Checked[i] = false;
  }
  AuditForm->ShowModal();
  delete AuditForm;
  delete KList;
}
//---------------------------------------------------------------------------
/*   ����� �����
void __fastcall TMainKPSForm::SaveParametersClick(TObject *Sender)
{
  AnsiString S;
  if(!ComparePar())
  {
    TDateTime DT;
    DT = Now();
    S =  "UPDATE Parameters SET ";
    S += "PortNum = '" + (ComboBox1->Text)  + (AnsiString)"',";
    S += "PortSpeed = " + ComboBox2->Text + ",";
    S += "TimeOut = " + (AnsiString)Edit7->Text.ToInt() + ",";
    S += "Camer = '" +   ComboBox3->Text  + (AnsiString)"',";
    S += "MinRash = " +  ReplZPnaPunk((AnsiString)(ReplPunknaZP(Edit8->Text).ToDouble()))   + (AnsiString)",";
    S += "MidRash = " +  ReplZPnaPunk((AnsiString)(ReplPunknaZP(Edit9->Text).ToDouble()))   + (AnsiString)",";
    S += "MaxRash = " +  ReplZPnaPunk((AnsiString)(ReplPunknaZP(Edit10->Text).ToDouble()))   + (AnsiString)",";
    S += "MinLDop = " +  ReplZPnaPunk((AnsiString)(ReplPunknaZP(Edit11->Text).ToDouble()))   + (AnsiString)",";
    S += "MinRDop = " +  ReplZPnaPunk((AnsiString)(ReplPunknaZP(Edit14->Text).ToDouble()))   + (AnsiString)",";
    S += "MidLDop = " +  ReplZPnaPunk((AnsiString)(ReplPunknaZP(Edit12->Text).ToDouble()))   + (AnsiString)",";
    S += "MidRDop = " +  ReplZPnaPunk((AnsiString)(ReplPunknaZP(Edit15->Text).ToDouble()))   + (AnsiString)",";
    S += "MaxLDop = " +  ReplZPnaPunk((AnsiString)(ReplPunknaZP(Edit13->Text).ToDouble()))   + (AnsiString)",";
    S += "MaxRDop = " +  ReplZPnaPunk((AnsiString)(ReplPunknaZP(Edit16->Text).ToDouble()))   + (AnsiString)",";
    S += "MinV = " +  ReplZPnaPunk((AnsiString)(ReplPunknaZP(Edit17->Text).ToDouble()))   + (AnsiString)",";
    S += "MidV = " +  ReplZPnaPunk((AnsiString)(ReplPunknaZP(Edit18->Text).ToDouble()))   + (AnsiString)",";
    S += "MaxV = " +  ReplZPnaPunk((AnsiString)(ReplPunknaZP(Edit19->Text).ToDouble()))   + (AnsiString)",";
    S += "DP = '" +   DT.FormatString("dd-mm-yyyy  hh:nn:ss") + (AnsiString)"',";
    S += "OpNameL = '" + DM->OpName +"';";
    if(!DM->SQLWRITE(S))
    {
      S = "�� �������� �������  - Parameters" + DM->ErrorString;
      ShowMessage(S);
//      SelfCloseFlag = true;
      return;
    }
    Label60->Caption = DT.FormatString("dd-mm-yyyy");
//    Label62->Caption = DM->OpName;
  }
}
*/
//---------------------------------------------------------------------------
bool __fastcall TMainKPSForm::ComparePar(void)
{
  bool Result;
/*

  Result = true;
  if((AnsiString)CurParameters.PortNum   != ComboBox1->Text) Result = false;
  if((AnsiString)CurParameters.PortSpeed != ComboBox2->Text) Result = false;
  if((AnsiString)CurParameters.TimeOut   != Edit7->Text) Result = false;
  if((AnsiString)CurParameters.Camer     != ComboBox3->Text) Result = false;
  if( ((CurParameters.MinRash - ReplPunknaZP(Edit8->Text).ToDouble()) > 0.01)
   || ((ReplPunknaZP(Edit8->Text).ToDouble() - CurParameters.MinRash) > 0.01) ) Result = false;
  if( ((CurParameters.MidRash - ReplPunknaZP(Edit9->Text).ToDouble()) > 0.01)
   || ((ReplPunknaZP(Edit9->Text).ToDouble() - CurParameters.MidRash) > 0.01) ) Result = false;
  if( ((CurParameters.MaxRash - ReplPunknaZP(Edit10->Text).ToDouble()) > 0.01)
   || ((ReplPunknaZP(Edit10->Text).ToDouble() - CurParameters.MaxRash) > 0.01) ) Result = false;
  if( ((CurParameters.MinLDop - ReplPunknaZP(Edit11->Text).ToDouble()) > 0.01)
   || ((ReplPunknaZP(Edit11->Text).ToDouble() - CurParameters.MinLDop) > 0.01) ) Result = false;
  if( ((CurParameters.MinRDop - ReplPunknaZP(Edit14->Text).ToDouble()) > 0.01)
   || ((ReplPunknaZP(Edit14->Text).ToDouble() - CurParameters.MinRDop) > 0.01) ) Result = false;
  if( ((CurParameters.MidLDop - ReplPunknaZP(Edit12->Text).ToDouble()) > 0.01)
   || ((ReplPunknaZP(Edit12->Text).ToDouble() - CurParameters.MidLDop) > 0.01) ) Result = false;
  if( ((CurParameters.MidRDop - ReplPunknaZP(Edit15->Text).ToDouble()) > 0.01)
   || ((ReplPunknaZP(Edit15->Text).ToDouble() - CurParameters.MidRDop) > 0.01) ) Result = false;
  if( ((CurParameters.MaxLDop - ReplPunknaZP(Edit13->Text).ToDouble()) > 0.01)
   || ((ReplPunknaZP(Edit13->Text).ToDouble() - CurParameters.MaxLDop) > 0.01) ) Result = false;
  if( ((CurParameters.MaxRDop - ReplPunknaZP(Edit16->Text).ToDouble()) > 0.01)
   || ((ReplPunknaZP(Edit16->Text).ToDouble() - CurParameters.MaxRDop) > 0.01) ) Result = false;
  if( ((CurParameters.MinV    - ReplPunknaZP(Edit17->Text).ToDouble()) > 0.01)
   || ((ReplPunknaZP(Edit17->Text).ToDouble() - CurParameters.MinV   ) > 0.01) ) Result = false;
  if( ((CurParameters.MidV    - ReplPunknaZP(Edit18->Text).ToDouble()) > 0.01)
   || ((ReplPunknaZP(Edit18->Text).ToDouble() - CurParameters.MidV   ) > 0.01) ) Result = false;
  if( ((CurParameters.MaxV    - ReplPunknaZP(Edit19->Text).ToDouble()) > 0.01)
   || ((ReplPunknaZP(Edit19->Text).ToDouble() - CurParameters.MaxV   ) > 0.01) ) Result = false;
*/
  return Result;
}
//---------------------------------------------------------------------------
void __fastcall TMainKPSForm::Button1Click(TObject *Sender)
{
/*
  AnsiString S = "Drop table Parameters";
/*
    if(!DM->SQLWRITE(S))
    {
      S = "�� ������� �������  - Parameters" + DM->ErrorString;
      ShowMessage(S);
      return;
    }
   S = "Drop table Parameters";
    if(!DM->SQLWRITE(S))
    {
      S = "�� ������� �������  - Parameters" + DM->ErrorString;
      ShowMessage(S);
      return;
    }
   S = "Drop table OPERATORS";
    if(!DM->SQLWRITE(S))
    {
      S = "�� ������� �������  - OPERATORS" + DM->ErrorString;
      ShowMessage(S);
      return;
    }
   S = "Drop table Groups";
    if(!DM->SQLWRITE(S))
    {
      S = "�� ������� �������  - Groups" + DM->ErrorString;
      ShowMessage(S);
      return;
    }
*/
}
//---------------------------------------------------------------------------
void TMainKPSForm::Start_Stop(void)
{
  int i;

//  Double dVImp;
  int    Impuls;
  if(!FlagVvodaParamsProliv)
  {
    ShowMessage("�� ��������� ��������� �������!");
    return;
  }
  if(!ComPortFlag)
  {
    ShowMessage("������� ���������� ����� ��������!");
    return;
  }
  if(!FlagGetDate)
  {
    ShowMessage("��� ����� � ������������� ��������!");
    return;
  }
////  if(ReadCadrsFlag)
  if(FlagTestVideo)
  {
    ShowMessage("�������� ������������ �����!�������� � ��������� ��������.");
    return;
  }
  if(PhotoSB->Down)
  {
    ShowMessage("�������� ��������� ���� � �������!�������� � ��������� ��������.");
    return;
  }
////    BeginTickCountValue = DM->RecData.Uval.RD.CountN;
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    csSendToPort->Enter();                  //������ ����������
    ProgramState = 3;   //���� ������ ������� �������� �������
    CountRecivedAnswer = 0;   // ����� ���������� �� �� �������
    SummOF_Q_Proliva = 0;       //C���� ���� Q �������

    Impuls = BegTicCount;
    memset(&BuffOut,0,5);
    BuffOut[0] = 0x43;                      //����� ������ �������
    memcpy(BuffOut+1,&Impuls,4);
    pBuffOut = BuffOut + 0;
    BuffOutLen = 5;
    reader->Suspend();                       //
    writer = new TThreadWriter(false, ComPort, pBuffOut, BuffOutLen);  //Pusk proliva
    BYTE A, B;
    int  C;
    memcpy(&A, &writer->wrbuf2[0] ,1);
    memcpy(&B, &writer->wrbuf2[1] ,1);
    memcpy(&C, &writer->wrbuf2[2] ,4);
    AnsiString SS = (AnsiString)A + (AnsiString)" " + (AnsiString)B + (AnsiString)" " + (AnsiString)C;
    Label55->Caption = SS;
    delete  writer;
    reader->Resume();                       //
    csSendToPort->Leave();
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    GroupBox3->Enabled = false;
    Label45->Caption = ProgramState;
    StartTime = Now();
    StartProlivBtn->Enabled = false;
    StartProlivBtn->Color = clInactiveCaption;
    ClearPanel->Enabled = true;
    ClearPanel->Color = clLime;
    Label39->Caption = 0;
    Label48->Caption = 0;
    Label50->Caption = 0;
    Label52->Caption = 0;
    StatusBar1->Panels->Items[1]->Text = "�����-���� �� ����������!";
  return;
}
//---------------------------------------------------------------------------
void __fastcall TMainKPSForm::StartProlivBtnClick(TObject *Sender)
{
  int i;

//  Double dVImp;
  int    Impuls;
  if(!FlagVvodaParamsProliv)
  {
    ShowMessage("�� ��������� ��������� �������!");
    return;
  }
  if(!ComPortFlag)
  {
    ShowMessage("������� ���������� ����� ��������!");
    return;
  }
  if(!FlagGetDate)
  {
    ShowMessage("��� ����� � ������������� ��������!");
    return;
  }
////  if(ReadCadrsFlag)
  if(FlagTestVideo)
  {
    ShowMessage("�������� ������������ �����!�������� � ��������� ��������.");
    return;
  }
  if(PhotoSB->Down)
  {
    ShowMessage("�������� ��������� ���� � �������!�������� � ��������� ��������.");
    return;
  }
  if(FlagTickControl)     //
  {
////    BeginTickCountValue = DM->RecData.Uval.RD.CountN;
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    csSendToPort->Enter();                  //������ ����������
    ProgramState = 3;        //���� ������ ������� �������� �������
    CountRecivedAnswer = 0;   // ����� ���������� �� �� �������
    SummOF_Q_Proliva = 0;       //C���� ���� Q �������

    Impuls = BegTicCount;
    memset(&BuffOut,0,5);
    BuffOut[0] = 0x43;                      //����� ������ �������
    memcpy(BuffOut+1,&Impuls,4);
    pBuffOut = BuffOut + 0;
    BuffOutLen = 5;
    reader->Suspend();                       //
    writer = new TThreadWriter(false, ComPort, pBuffOut, BuffOutLen);  //Pusk proliva
    BYTE A, B;
    int  C;
    memcpy(&A, &writer->wrbuf2[0] ,1);
    memcpy(&B, &writer->wrbuf2[1] ,1);
    memcpy(&C, &writer->wrbuf2[2] ,4);
    AnsiString SS = (AnsiString)A + (AnsiString)" " + (AnsiString)B + (AnsiString)" " + (AnsiString)C;
    Label55->Caption = SS;
    delete  writer;
    reader->Resume();                       //
    csSendToPort->Leave();
    GroupBox3->Enabled = false;
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    Label45->Caption = ProgramState;
    StartTime = Now();
    StartProlivBtn->Enabled = false;
    StartProlivBtn->Color = clInactiveCaption;
    ClearPanel->Enabled = true;
    ClearPanel->Color = clLime;
    Label39->Caption = 0;
    Label48->Caption = 0;
    Label50->Caption = 0;
    Label52->Caption = 0;
    StatusBar1->Panels->Items[1]->Text = "����������� ����!";
    return;
  }
//if(!FlagVvodaSubscr)
//{
//  ShowMessage("�� ������� ��������� ��������� � ��������� ��������!");
//  return;
//}
  if(!CamerWorkingFlag)                    //(ComPortFlag &&
  {
    ShowMessage("��� ������� �����������!");
    return;
  }
  if(QminRb->Checked)
  {
    EndCalcMin = false;
    BegCalcMin = true;
    NumCodeProv = 0;
  }
  if(QtRb->Checked)
  {
    EndCalcT = false;
    BegCalcT = true;
    NumCodeProv = 1;
  }
  if(QnomRb->Checked)
  {
    EndCalcN = false;
    BegCalcN = true;
    NumCodeProv = 2;
  }
  switch(NumCodeProv)
  {
    case 0:
      QminCurProliv = DM->QminL;
      QmaxCurProliv = DM->QminR;
      dVImp = DM->Vmin * 1000;        // Litrs * 1000
      Impuls = (int)dVImp;
      break;
    case 1:
      QminCurProliv = DM->QtL;
      QmaxCurProliv = DM->QtR;
      dVImp = DM->Vt * 1000;     //������������ ������� � �������� � ��������� �������
      Impuls = (int)dVImp;           // Litrs * 1000
      break;
    case 2:
      QminCurProliv = DM->QnomL;
      QmaxCurProliv = DM->QnomR;
      dVImp = DM->Vn * 1000;   //������������ ������� � �������� � ��������� �������
      Impuls = (int)dVImp;          // Litrs * 1000
      break;
  }
  MaxProlivCountValue = dVImp;
  for( int i = 0; i < (int)DM->GrencList.size(); i++)
  {
    if((QSA >= DM->GrencList[i].LGr)&&(QSA <= DM->GrencList[i].RGr))
    {
      MaxProlivCountValue = (int)(MaxProlivCountValue * DM->GrencList[i].Const);
      break;
    }
  }
  if(AvtomatStartFlag)
  {
     RBDisabling();
     DisabledQSelection();
     StatusBar1->Panels->Items[1]->Text = "��������� �������� ������!";
     if(!((QSA <= QmaxCurProliv)&&(QSA >= QminCurProliv)))
     {
       FlagCiklaAvtomata = true;
       while(!((QSA <= QmaxCurProliv)&&(QSA >= QminCurProliv)))
       {
         if(!FlagCiklaAvtomata)
         {
           EndCalcN = false;
           BegCalcN = false;
           return;
         }
         Application->ProcessMessages();
         Sleep(100);
         Application->ProcessMessages();
       }
       FlagCiklaAvtomata = false;
     }
  }
  else
  {
    if(!((QSA <= QmaxCurProliv)&&(QSA >= QminCurProliv)))
    {
      EndCalcN = false;
      BegCalcN = false;
      ShowMessage("���� ����������: ����� ����������� ��� ���������� ������!");
      return;
    }
  }
  KommandIntoIS(0x54);            //������� �������� ����������� ����
  Application->ProcessMessages();
  Sleep(150);
  Application->ProcessMessages();
  Sleep(150);
  Application->ProcessMessages();
  Sleep(150);
  Application->ProcessMessages();
  Sleep(150);
  Application->ProcessMessages();
  Sleep(150);
  Application->ProcessMessages();
  Sleep(150);
  Application->ProcessMessages();
  Sleep(150);
  Application->ProcessMessages();
  Sleep(150);
  Application->ProcessMessages();
  Sleep(150);
  Application->ProcessMessages();
  Sleep(150);
  Application->ProcessMessages();
  KommandIntoIS(0x48);            //������� �������� ����������� ������� � ���������
  Application->ProcessMessages();
  Sleep(100);
  Application->ProcessMessages();
  Sleep(100);
  Application->ProcessMessages();
  Sleep(100);
  Application->ProcessMessages();
  Sleep(100);
  Application->ProcessMessages();
  Sleep(100);
  Application->ProcessMessages();
  Sleep(100);
  Application->ProcessMessages();
  Sleep(100);
  Application->ProcessMessages();
  Sleep(100);
  Application->ProcessMessages();
  Sleep(100);
  Application->ProcessMessages();
  Sleep(100);
  Application->ProcessMessages();
  Sleep(100);

  FlagProliva = true;
  memset(&BuffOut,0,5);
  BuffOut[0] = 0x43;                      //����� ������ �������
//  memcpy(BuffOut+1,&Impuls,4);      //MaxProlivCountValue
  memcpy(BuffOut+1,&MaxProlivCountValue,4);      //MaxProlivCountValue
  pBuffOut = BuffOut + 0;
  BuffOutLen = 5;                       //
  FlagBegProliva = true; CountCadr = 0;   //������ ������
  Image1->Visible = true;
  Label51->Visible = false;
  Label52->Visible = false;
  Label47->Visible = false;
  Label48->Visible = false;
  if(FlagVideo > 0)
  {
     ShowProliv();
  }
  else
  {
     ShowProliv4();
  }
}
//---------------------------------------------------------------------------
void TMainKPSForm::ShowProliv4(void)
{
  AnsiString S;
  bool b;
  TDateTime TD;

  while(FlagBegProliva)   //��������������� � ������ � ��������� �� ������. �������
  {
    if(CountCadr == 0)
    {
      if(PhotoPrio == 0)
      {
        writer = new TThreadWriter(false, ComPort, pBuffOut, BuffOutLen);  //Pusk proliva
        delete  writer;
        StartTime = Now();
      }
      b = capGrabFrame(hWndC);    // ���������� � ����� ���� � ������
      b = capFileSaveDIB(hWndC, "A.bmp"); //�������� ���� � ����
      StartVTime = Now();
      if (b)
      {                         // ���� ��� ����������
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        csSendToPort->Enter();                  //������ ����������
        CamerWorkingFlag = true;
        if(PhotoPrio > 0)
        {
          writer = new TThreadWriter(false, ComPort, pBuffOut, BuffOutLen);  //Pusk proliva
          delete  writer;
          StartTime = Now();
        }
        FullFileName = SlashSep(Dir, "A.bmp");
        Image1->Picture->LoadFromFile(FullFileName);
//        TD = Now();
        Image1->Canvas->Font->Style = TFontStyles()<< fsBold;
        Image1->Canvas->Font->Size = 18;
        S = StartVTime.FormatString("dd.mm.yyyy hh:nn:ss");
        Image1->Canvas->TextOut(Image1->Left + 10, Image1->Top + 430 , S);     //  + 16
        StatusBar1->Panels->Items[1]->Text = "����������� ����!";
        switch(NumCodeProv)
        {
          case 0:
            FullFileName = SlashSep(Dir, "FotoMinBeg.bmp");
            Image1->Picture->SaveToFile(FullFileName); break;                 // ��� � ���� ����������
          case 1:
            FullFileName = SlashSep(Dir, "FotoMidBeg.bmp");
            Image1->Picture->SaveToFile(FullFileName); break;                 // ��� � ���� ����������
          case 2:
            FullFileName = SlashSep(Dir, "FotoMaxBeg.bmp");
            Image1->Picture->SaveToFile(FullFileName); break;
        }
//        StartTime = Now();
//        Label45->Caption = ProgramState;
        RBDisabling();
        DisabledQSelection();    //�������� ������� Q ������ �������
        ProgressBar1->Min = 0;
        ProgressBar1->Max = MaxProlivCountValue;
        ProgressBar1->Visible = true;
        ProgressBar1->Position = 0;
        ProgressBar1->Repaint();
        CountRecivedAnswer = 0;   // ����� ���������� �� �� �������
        SummOF_Q_Proliva = 0;       //C���� ���� Q �������
      }
      csSendToPort->Leave();
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
      Application->ProcessMessages();
      ProgramState = 2;
    }
    CountCadr++;
    Application->ProcessMessages();
    Sleep(20);
    Application->ProcessMessages();
  }
  if(ProgramState == 2)
  {
    b = capGrabFrame(hWndC);    // ���������� � ����� ���� � ������
    b = capFileSaveDIB(hWndC, "A.bmp"); //�������� ���� � ����
    StopVTime = Now();
    if (b)
    {                         // ���� ��� ����������
      FullFileName = SlashSep(Dir, "A.bmp");
      Image1->Picture->LoadFromFile(FullFileName);
//      TD = Now();
      Image1->Canvas->Font->Style = TFontStyles()<< fsBold;
      Image1->Canvas->Font->Size = 18;
      S = StopVTime.FormatString("dd.mm.yyyy hh:nn:ss");
      Image1->Canvas->TextOut(Image1->Left + 10, Image1->Top + 430 , S);     //  + 16
      switch(NumCodeProv)
      {
        case 0:
          FullFileName = SlashSep(Dir, "FotoMinEnd.bmp");
          Image1->Picture->SaveToFile(FullFileName); break;                 // ��� � ���� ����������
        case 1:
          FullFileName = SlashSep(Dir,"FotoMidEnd.bmp");
          Image1->Picture->SaveToFile(FullFileName); break;                 // ��� � ���� ����������
        case 2:
          FullFileName = SlashSep(Dir, "FotoMaxEnd.bmp");
          Image1->Picture->SaveToFile(FullFileName); break;
      }                    // ��� � ���� ����������
      ProgramState = 1;
      Label45->Caption = ProgramState;
      StatusBar1->Panels->Items[1]->Text = " ���� ��������, ���� ������ �� ���������!";
      StartProlivBtnState = true;
      RBEnabling();
      StartProlivBtn->Enabled = false;     //Pusk
      StartProlivBtn->Color = clInactiveCaption;
      KommandIntoIS(0x54);                 //�������� ����������� ����
      FullFileName = SlashSep(Dir, "Foto.jpg");
      Image1->Picture->LoadFromFile(FullFileName);
      Application->ProcessMessages();
      Sleep(1500);
      Application->ProcessMessages();
      Sleep(1000);
      FlagRead_T_After_Proliv = true;
      Application->ProcessMessages();
      EnabledQSelection();
      FlagProliva = false;
      ResultPanelClick(this);
      Application->ProcessMessages();
    }
  }
  else
  {
    EnabledQSelection();
    Screen->Cursor  =  SaveCursor;
    FullFileName = SlashSep(Dir, "Foto.jpg");
    Image1->Picture->LoadFromFile(FullFileName);
    Application->ProcessMessages();
    StatusBar1->Panels->Items[1]->Text = "���� �������� �� ���������� ��������� ��������� ��������!";
  }
}
//---------------------------------------------------------------------------
void TMainKPSForm::ShowProliv(void)
{
  AnsiString S;
  TDateTime DT;

  SaveCursor = Screen->Cursor;
  Screen->Cursor = crHourGlass;
  while(FlagBegProliva)   //��������������� � ������ � ��������� �� ������. �������
  {
    if(CountCadr == 0)
    {
      if(PhotoPrio == 0)
      {
        writer = new TThreadWriter(false, ComPort, pBuffOut, BuffOutLen);  //Pusk proliva
        delete  writer;
        StartTime = Now();
      }
    }
    bool b = capGrabFrame(hWndC);    // ���������� � ����� ���� � ������
    b = capFileSaveDIB(hWndC, "A.bmp"); //�������� ���� � ����
    if(CountCadr == 0)
       StartVTime = Now();
    else
       StopVTime = Now();
    if (b)
    {                         // ���� ��� ����������
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
      csSendToPort->Enter();                  //������ ����������
      CamerWorkingFlag = true;
      CountCadr++;
      if(CountCadr == 1)
      {
        if(PhotoPrio > 0)
        {
          writer = new TThreadWriter(false, ComPort, pBuffOut, BuffOutLen);  //Pusk proliva
          delete  writer;
          StartTime = Now();
        }
      }
      FullFileName = SlashSep(Dir, "A.bmp");
      Image1->Picture->LoadFromFile(FullFileName);
//      TD = Now();
      Image1->Canvas->Font->Style = TFontStyles()<< fsBold;
      Image1->Canvas->Font->Size = 18;
      if(CountCadr == 1)
      {
         S = StartVTime.FormatString("dd.mm.yyyy hh:nn:ss");
      }
      else
      {
         DT = Now();
         S = DT.FormatString("dd.mm.yyyy hh:nn:ss");
      }
      Image1->Canvas->TextOut(Image1->Left + 10, Image1->Top + 430 , S);     //  + 16
      if(CountCadr == 1)
      {
        StatusBar1->Panels->Items[1]->Text = "����������� ����!";
        switch(NumCodeProv)
        {
          case 0:
            FullFileName = SlashSep(Dir, "FotoMinBeg.bmp");
            Image1->Picture->SaveToFile(FullFileName); break;                 // ��� � ���� ����������
          case 1:
            FullFileName = SlashSep(Dir, "FotoMidBeg.bmp");
            Image1->Picture->SaveToFile(FullFileName); break;                 // ��� � ���� ����������
          case 2:
            FullFileName = SlashSep(Dir, "FotoMaxBeg.bmp");
            Image1->Picture->SaveToFile(FullFileName); break;
        }
//        StartTime = Now();
//        Label45->Caption = ProgramState;
        RBDisabling();
        DisabledQSelection();    //�������� ������� Q ������ �������
        ProgressBar1->Min = 0;
        ProgressBar1->Max = MaxProlivCountValue;
        ProgressBar1->Visible = true;
        ProgressBar1->Position = 0;
        ProgressBar1->Repaint();
        CountRecivedAnswer = 0;   // ����� ���������� �� �� �������
        SummOF_Q_Proliva = 0;       //C���� ���� Q �������
      }
      csSendToPort->Leave();
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
      Application->ProcessMessages();
      if(CountCadr == 1)
      {
        ProgramState = 2;
      }
    }
    Application->ProcessMessages();
  }
  if(ProgramState == 2)
  {
    switch(NumCodeProv)
    {
      case 0:
        FullFileName = SlashSep(Dir, "FotoMinEnd.bmp");
        Image1->Picture->SaveToFile(FullFileName); break;                 // ��� � ���� ����������
      case 1:
        FullFileName = SlashSep(Dir, "FotoMidEnd.bmp");
        Image1->Picture->SaveToFile(FullFileName); break;                 // ��� � ���� ����������
      case 2:
        FullFileName = SlashSep(Dir, "FotoMaxEnd.bmp");
        Image1->Picture->SaveToFile(FullFileName); break;                                  
    }                    // ��� � ���� ����������
    ProgramState = 1;
    Label45->Caption = ProgramState;
    StatusBar1->Panels->Items[1]->Text = " ���� ��������, ���� ������ �� ���������!";
    StartProlivBtnState = true;
    RBEnabling();
    StartProlivBtn->Enabled = false;     //Pusk
    StartProlivBtn->Color = clInactiveCaption;
    Screen->Cursor  =  SaveCursor;
    KommandIntoIS(0x54);                 //�������� ����������� ����
    FullFileName = SlashSep(Dir, "Foto.jpg");
    Image1->Picture->LoadFromFile(FullFileName);
    Application->ProcessMessages();
    Sleep(1500);
    Application->ProcessMessages();
    Sleep(1000);
    FlagRead_T_After_Proliv = true;
    Application->ProcessMessages();
    EnabledQSelection();
//    if(AvtomatStartFlag)
//    {
//      StartProlivBtn->Enabled = true;     //Pusk
//      StartProlivBtn->Color = clLime;
//    }
    FlagProliva = false;
    ResultPanelClick(this);
    Application->ProcessMessages();
  }
  else
  {
    EnabledQSelection();
    Screen->Cursor  =  SaveCursor;
    FullFileName = SlashSep(Dir, "Foto.jpg");
    Image1->Picture->LoadFromFile(FullFileName);
    Application->ProcessMessages();
    StatusBar1->Panels->Items[1]->Text = "���� �������� �� ���������� ��������� ��������� ��������!";
  }
}
//---------------------------------------------------------------------------
void TMainKPSForm::RBDisabling(void)
{
  StartProlivBtnState = StartProlivBtn->Enabled;
  StartProlivBtn->Enabled = false;     //Pusk
  StartProlivBtn->Color = clInactiveCaption;
  ClearPanel->Enabled = true;    //sbros
  ClearPanel->Color = clLime;
  Abonent->Enabled = false;      //Abonent
  Abonent->Color = clInactiveCaption;
  Nastrojka->Enabled = false;    //Nastrojka
  Nastrojka->Color = clInactiveCaption;
  Parameters->Enabled = false;       //Parametri
  Parameters->Color = clInactiveCaption;
  OtchetPanel->Enabled = false;       //Otchot
  OtchetPanel->Color = clInactiveCaption;
  OperatorsP->Enabled = false;   //���������
  OperatorsP->Color = clInactiveCaption;
  QminRb->Enabled = false;       //
  QtRb->Enabled = false;         // Radiobuttons
  QnomRb->Enabled = false;       //
}
//---------------------------------------------------------------------------
void TMainKPSForm::RBEnabling(void)
{
//  SpeedButton2->Enabled = true; //Poslablenie
//  SpeedButton2->Font->Color = clLime;
  StartProlivBtn->Enabled = StartProlivBtnState;     //Pusk
  if(StartProlivBtnState)
    StartProlivBtn->Color = clLime;
  else
    StartProlivBtn->Color = clInactiveCaption;
  ClearPanel->Enabled = false;    //sbros
  ClearPanel->Color = clInactiveCaption;
  Abonent->Enabled = true;      //Abonent
  Abonent->Color = clLime;
  Nastrojka->Enabled = true;    //Nastrojka
  Nastrojka->Color = clLime;
  Parameters->Enabled = true;       //Parametri
  Parameters->Color = clLime;
  OperatorsP->Enabled = true;   //���������
  OperatorsP->Color = clLime;
  QminRb->Enabled = true;       //
  QtRb->Enabled = true;         // Radiobuttons
  QnomRb->Enabled = true;       //
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void TMainKPSForm::DisabledQSelection(void)
{
  QminRb->Enabled = false;
  QtRb->Enabled   = false;
  QnomRb->Enabled = false;
  GroupBox3->Enabled = false;
}
//---------------------------------------------------------------------------
void TMainKPSForm::EnabledQSelection(void)
{
  QminRb->Enabled = true;
  QtRb->Enabled   = true;
  QnomRb->Enabled = true;
  GroupBox3->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TMainKPSForm::ResultPanelClick(TObject *Sender)
{
  AnsiString S;
  int   N;

  try
  {
    ProgramState = 1;
    FlagProliva = false;
    Application->ProcessMessages();
    Form2 = new TForm2(this);
    Application->ProcessMessages();
    switch (NumCodeProv)
    {
      case 0:
      FullFileName = SlashSep(Dir, "FotoMinBeg.bmp");
      Form2->Image1->Picture->LoadFromFile(FullFileName);
      FullFileName = SlashSep(Dir, "FotoMinEnd.bmp");
      Form2->Image2->Picture->LoadFromFile(FullFileName);
      break;
      case 1:
      FullFileName = SlashSep(Dir, "FotoMidBeg.bmp");
      Form2->Image1->Picture->LoadFromFile(FullFileName);
      FullFileName = SlashSep(Dir, "FotoMidEnd.bmp");
      Form2->Image2->Picture->LoadFromFile(FullFileName);
      break;
      case 2:
      FullFileName = SlashSep(Dir, "FotoMaxBeg.bmp");
      Form2->Image1->Picture->LoadFromFile(FullFileName);
      FullFileName = SlashSep(Dir, "FotoMaxEnd.bmp");
      Form2->Image2->Picture->LoadFromFile(FullFileName);
      break;
    }
    Form2->Edit3->Text = S.sprintf("%3.2f",TempratBegProliv );
    Form2->Edit4->Text = S.sprintf("%3.2f",TempratBegProliv );
    Form2->Edit5->Text = S.sprintf("%3.2f",DM->RecData.Uval.RD.TVozd);
    Form2->Edit6->Text = S.sprintf("%3.2f",DM->RecData.Uval.RD.Vlagnost);
    Application->ProcessMessages();
    if(Form2->ShowModal() == IDOK)
    {
      Application->ProcessMessages();
      RBEnabling();
      EtapeCalculate(Form2->BegValue, Form2->EndValue);
//      FlagProliva = false;
      switch (NumCodeProv)
      {
       case 0:
         EndCalcMin = true;
       break;
       case 1:
         EndCalcT = true;
       break;
       case 2:
         EndCalcN = true;
       break;
      }
      if( EndCalcMin &  EndCalcT & EndCalcN)
      {
        OtchetPanel->Enabled = true; //��������� ������� ���������
        OtchetPanel->Color = clLime;
      }
      StartProlivBtn->Enabled = true;     //Pusk
      StartProlivBtn->Color = clLime;
      Application->ProcessMessages();
    }
    StartProlivBtn->Enabled = true;     //Pusk
    StartProlivBtn->Color = clLime;
    delete Form2;
    Application->ProcessMessages();
  }
  catch(...)
  {
    StatusBar1->Panels->Items[1]->Text = " ��������� ���������� ��������� ResultPanelClick �� ������!";
  }
}
//---------------------------------------------------------------------------

void TMainKPSForm::EtapeCalculate(float BegValue, float EndValue)
{
  AnsiString S;
  Double D,D1,D2,D3;
  Double Drez, Dis;
  try
  {
    D = (EndValue - BegValue); //metri
    D1 = D*1000;               //litri
    switch (NumCodeProv)    //����� ��������� ������ ��������� ����������� �������� � % ���������� �� �����
    {
      case 0:
        Edit21->Text = S.sprintf("%9.6f",BegValue);
        Edit1->Text = S.sprintf("%9.6f",EndValue);
        Label10->Caption = S.sprintf("%8.6f",D);
//        Label14->Caption = S.sprintf("%9.6f",DM->Vmin/1000);
        Label17->Caption = S.sprintf("%6.5f",DM->Vmin/1000);
        Drez = Round0(D1, 2); Dis = Round0(DM->Vmin, 2);
        if(Drez > Dis)
        {
          D2 = Round0(((Drez - Dis)/Dis)*100,2);
          Label20->Caption =  S.sprintf("%4.2f",D2);
          if(D2 > DM->DminR)
          {
             Label20->Font->Color = clRed;
             StatusBar1->Panels->Items[1]->Text = "���� ��������: �� ��������!";
          }
          else
          {
             Label20->Font->Color = clGreen;
             StatusBar1->Panels->Items[1]->Text = "���� ��������: ��������!";
          }
        }
        else
        {
          D2 = Round0(((Dis - Drez)/Dis)*100,2);
          Label20->Caption =  S.sprintf("%4.2f",-D2);
          if(D2 >= DM->DminL)
          {
             Label20->Font->Color = clRed;
             StatusBar1->Panels->Items[1]->Text = "���� ��������: �� ��������!";
          }
          else
          {
             Label20->Font->Color = clGreen;
             StatusBar1->Panels->Items[1]->Text = "���� ��������: ��������!";
          }
        }
      break;
      case 1:
        Edit22->Text = S.sprintf("%9.6f",BegValue);
        Edit2->Text = S.sprintf("%9.6f",EndValue);
        Label33->Caption = S.sprintf("%8.6f",D);
//        Label24->Caption = S.sprintf("%9.6f",DM->Vt/1000);
        Label26->Caption = S.sprintf("%6.5f",DM->Vt/1000);
        Drez = Round0(D1, 2); Dis = Round0(DM->Vt, 2);
        if(D1 > DM->Vmin)
        {
          D2 = Round0(((Drez - Dis)/Dis)*100,2);
          Label28->Caption =  S.sprintf("%4.2f",D2);
          if(D2 > DM->DtR)
          {
             Label28->Font->Color = clRed;
             StatusBar1->Panels->Items[1]->Text = "���� ��������: �� ��������!";
          }
          else
          {
             Label28->Font->Color = clGreen;
             StatusBar1->Panels->Items[1]->Text = "���� ��������: ��������!";
          }
        }
        else
        {
          D2 = Round0(((Dis - Drez)/Dis)*100,2);
          Label28->Caption =  S.sprintf("%4.2f",-D2);
          if(D2 > DM->DtL)
          {
             Label28->Font->Color = clRed;
             StatusBar1->Panels->Items[1]->Text = "���� ��������: �� ��������!";
          }
          else
          {
             Label28->Font->Color = clGreen;
             StatusBar1->Panels->Items[1]->Text = "���� ��������: ��������!";
          }
        }
      break;
      case 2:
        Edit23->Text = S.sprintf("%9.6f",BegValue);
        Edit3->Text = S.sprintf("%9.6f",EndValue);
        Label46->Caption = S.sprintf("%8.6f",D);
//        Label25->Caption = S.sprintf("%9.6f",DM->Vn/1000);
        Label27->Caption = S.sprintf("%6.5f",DM->Vn/1000);
        Drez = Round0(D1, 2); Dis = Round0(DM->Vn, 2);
        if(Drez > Dis)
        {
          D2 = Round0(((Drez - Dis)/Dis)*100,2);
          Label29->Caption =  S.sprintf("%4.2f",D2);
          if(D2 > DM->DnR)
          {
             Label29->Font->Color = clRed;
             StatusBar1->Panels->Items[1]->Text = "���� ��������: �� ��������!";
          }
          else
          {
             Label29->Font->Color = clGreen;
             StatusBar1->Panels->Items[1]->Text = "���� ��������: ��������!";
          }
        }
        else
        {
          D2 = Round0(((Dis - Drez)/Dis)*100,2);
          Label29->Caption =  S.sprintf("%4.2f",-D2);
          if(D2 > DM->DnL)
          {
             Label29->Font->Color = clRed;
             StatusBar1->Panels->Items[1]->Text = "���� ��������: �� ��������!";
          }
          else
          {
             Label29->Font->Color = clGreen;
             StatusBar1->Panels->Items[1]->Text = "���� ��������: ��������!";
          }
        }
      break;
    }
    if(abs(TempratBegProliv - TempratEndProliv) > 5.0)
    {
      StatusBar1->Panels->Items[1]->Text = "������������ �������� ���������� ����!";
    }
  }
  catch(...)
  {
    StatusBar1->Panels->Items[1]->Text = " ��������� ���������� ��������� EtapeCalculate �� ������!";
  }
}
//---------------------------------------------------------------------------
void TMainKPSForm::WorkWSReestr(void)
{
  if(Reg->KeyExists("Proliv"))  //
  {
    ReadFromReestr();
  }
  else
  {
    WriteIntoReestr();
  }
}
//---------------------------------------------------------------------------
void TMainKPSForm::WriteIntoReestr(void)
{
  ParamsForm = new TParamsForm(this, DM, rParams);
  WriteIntoReestrEdited();
  delete ParamsForm;
}
//---------------------------------------------------------------------------
void TMainKPSForm::WriteIntoReestrEdited(void)
{
  Diametry D;
  try
  {
    DM->DiamOldList.clear();
    D.Diametr = ParamsForm->d10a->Text.ToInt();
    strcpy(D.Klass, ParamsForm->Dk10a->Text.c_str());
    if(DecimalSeparator == '.')
    {
      D.Qn = ReplZPnaPunk(ParamsForm->Qn10a->Text).ToDouble();
      D.KQt = ReplZPnaPunk(ParamsForm->DQn10Kta->Text).ToDouble();
      D.KQm = ReplZPnaPunk(ParamsForm->DQt10Kma->Text).ToDouble();
    }
    else
    {
      D.Qn = ReplPunknaZP(ParamsForm->Qn10a->Text).ToDouble();
      D.KQt = ReplPunknaZP(ParamsForm->DQn10Kta->Text).ToDouble();
      D.KQm = ReplPunknaZP(ParamsForm->DQt10Kma->Text).ToDouble();
    }
    DM->DiamOldList.push_back(D);
    //2
    D.Diametr = ParamsForm->d10b->Text.ToInt();
    strcpy(D.Klass, ParamsForm->Dk10b->Text.c_str());
    if(DecimalSeparator == '.')
    {
      D.Qn = ReplZPnaPunk(ParamsForm->Qn10b->Text).ToDouble();
      D.KQt = ReplZPnaPunk(ParamsForm->DQn10Ktb->Text).ToDouble();
      D.KQm = ReplZPnaPunk(ParamsForm->DQt10Kmb->Text).ToDouble();
    }
    else
    {
      D.Qn = ReplPunknaZP(ParamsForm->Qn10b->Text).ToDouble();
      D.KQt = ReplPunknaZP(ParamsForm->DQn10Ktb->Text).ToDouble();
      D.KQm = ReplPunknaZP(ParamsForm->DQt10Kmb->Text).ToDouble();
    }
    DM->DiamOldList.push_back(D);
    //3
    D.Diametr = ParamsForm->d15a->Text.ToInt();
    strcpy(D.Klass, ParamsForm->Dk15a->Text.c_str());
    if(DecimalSeparator == '.')
    {
      D.Qn = ReplZPnaPunk(ParamsForm->Qn15a->Text).ToDouble();
      D.KQt = ReplZPnaPunk(ParamsForm->DQn15Kta->Text).ToDouble();
      D.KQm = ReplZPnaPunk(ParamsForm->DQt15Kma->Text).ToDouble();
    }
    else
    {
      D.Qn = ReplPunknaZP(ParamsForm->Qn15a->Text).ToDouble();
      D.KQt = ReplPunknaZP(ParamsForm->DQn15Kta->Text).ToDouble();
      D.KQm = ReplPunknaZP(ParamsForm->DQt15Kma->Text).ToDouble();
    }
    DM->DiamOldList.push_back(D);
    //4
    D.Diametr = ParamsForm->d15b->Text.ToInt();
    strcpy(D.Klass, ParamsForm->Dk15b->Text.c_str());
    if(DecimalSeparator == '.')
    {
      D.Qn = ReplZPnaPunk(ParamsForm->Qn15b->Text).ToDouble();
      D.KQt = ReplZPnaPunk(ParamsForm->DQn15Ktb->Text).ToDouble();
      D.KQm = ReplZPnaPunk(ParamsForm->DQt15Kmb->Text).ToDouble();
    }
    else
    {
      D.Qn = ReplPunknaZP(ParamsForm->Qn15b->Text).ToDouble();
      D.KQt = ReplPunknaZP(ParamsForm->DQn15Ktb->Text).ToDouble();
      D.KQm = ReplPunknaZP(ParamsForm->DQt15Kmb->Text).ToDouble();
    }
    DM->DiamOldList.push_back(D);
    //5
    D.Diametr = ParamsForm->d20a->Text.ToInt();
    strcpy(D.Klass, ParamsForm->Dk20a->Text.c_str());
    if(DecimalSeparator == '.')
    {
      D.Qn = ReplZPnaPunk(ParamsForm->Qn20a->Text).ToDouble();
      D.KQt = ReplZPnaPunk(ParamsForm->DQn20Kta->Text).ToDouble();
      D.KQm = ReplZPnaPunk(ParamsForm->DQt20Kma->Text).ToDouble();
    }
    else
    {
      D.Qn = ReplPunknaZP(ParamsForm->Qn20a->Text).ToDouble();
      D.KQt = ReplPunknaZP(ParamsForm->DQn20Kta->Text).ToDouble();
      D.KQm = ReplPunknaZP(ParamsForm->DQt20Kma->Text).ToDouble();
    }
    DM->DiamOldList.push_back(D);
    //6
    D.Diametr = ParamsForm->d20b->Text.ToInt();
    strcpy(D.Klass, ParamsForm->Dk20b->Text.c_str());
    if(DecimalSeparator == '.')
    {
      D.Qn = ReplZPnaPunk(ParamsForm->Qn20b->Text).ToDouble();
      D.KQt = ReplZPnaPunk(ParamsForm->DQn20Ktb->Text).ToDouble();
      D.KQm = ReplZPnaPunk(ParamsForm->DQt20Kmb->Text).ToDouble();
    }
    else
    {
      D.Qn = ReplPunknaZP(ParamsForm->Qn20b->Text).ToDouble();
      D.KQt = ReplPunknaZP(ParamsForm->DQn20Ktb->Text).ToDouble();
      D.KQm = ReplPunknaZP(ParamsForm->DQt20Kmb->Text).ToDouble();
    }
    DM->DiamOldList.push_back(D);

    DM->DiamNewList.clear();

    D.Diametr = ParamsForm->dE101->Text.ToInt();
    strcpy(D.Klass, ParamsForm->Ek101->Text.c_str());
    if(DecimalSeparator == '.')
    {
      D.Qn = ReplZPnaPunk(ParamsForm->QnE101->Text).ToDouble();
      D.KQt = ReplZPnaPunk(ParamsForm->DQn10Kt1->Text).ToDouble();
      D.KQm = ReplZPnaPunk(ParamsForm->DQt10Km1->Text).ToDouble();
    }
    else
    {
      D.Qn = ReplPunknaZP(ParamsForm->QnE101->Text).ToDouble();
      D.KQt = ReplPunknaZP(ParamsForm->DQn10Kt1->Text).ToDouble();
      D.KQm = ReplPunknaZP(ParamsForm->DQt10Km1->Text).ToDouble();
    }
    DM->DiamNewList.push_back(D);
    //2
    D.Diametr = ParamsForm->dE102->Text.ToInt();
    strcpy(D.Klass, ParamsForm->Ek102->Text.c_str());
    if(DecimalSeparator == '.')
    {
      D.Qn = ReplZPnaPunk(ParamsForm->QnE102->Text).ToDouble();
      D.KQt = ReplZPnaPunk(ParamsForm->DQn10Kt2->Text).ToDouble();
      D.KQm = ReplZPnaPunk(ParamsForm->DQt10Km2->Text).ToDouble();
    }
    else
    {
      D.Qn = ReplPunknaZP(ParamsForm->QnE102->Text).ToDouble();
      D.KQt = ReplPunknaZP(ParamsForm->DQn10Kt2->Text).ToDouble();
      D.KQm = ReplPunknaZP(ParamsForm->DQt10Km2->Text).ToDouble();
    }
    DM->DiamNewList.push_back(D);
    //3
    D.Diametr = ParamsForm->dE151->Text.ToInt();
    strcpy(D.Klass, ParamsForm->Ek151->Text.c_str());
    if(DecimalSeparator == '.')
    {
      D.Qn = ReplZPnaPunk(ParamsForm->QnE151->Text).ToDouble();
      D.KQt = ReplZPnaPunk(ParamsForm->DQn15Kt1->Text).ToDouble();
      D.KQm = ReplZPnaPunk(ParamsForm->DQt15Km1->Text).ToDouble();
    }
    else
    {
      D.Qn = ReplPunknaZP(ParamsForm->QnE151->Text).ToDouble();
      D.KQt = ReplPunknaZP(ParamsForm->DQn15Kt1->Text).ToDouble();
      D.KQm = ReplPunknaZP(ParamsForm->DQt15Km1->Text).ToDouble();
    }
    DM->DiamNewList.push_back(D);
    //4
    D.Diametr = ParamsForm->dE152->Text.ToInt();
    strcpy(D.Klass, ParamsForm->Ek152->Text.c_str());
    if(DecimalSeparator == '.')
    {
      D.Qn = ReplZPnaPunk(ParamsForm->QnE152->Text).ToDouble();
      D.KQt = ReplZPnaPunk(ParamsForm->DQn15Kt2->Text).ToDouble();
      D.KQm = ReplZPnaPunk(ParamsForm->DQt15Km2->Text).ToDouble();
    }
    else
    {
      D.Qn = ReplPunknaZP(ParamsForm->QnE152->Text).ToDouble();
      D.KQt = ReplPunknaZP(ParamsForm->DQn15Kt2->Text).ToDouble();
      D.KQm = ReplPunknaZP(ParamsForm->DQt15Km2->Text).ToDouble();
    }
    DM->DiamNewList.push_back(D);
    //5
    D.Diametr = ParamsForm->dE201->Text.ToInt();
    strcpy(D.Klass, ParamsForm->Ek201->Text.c_str());
    if(DecimalSeparator == '.')
    {
      D.Qn = ReplZPnaPunk(ParamsForm->QnE201->Text).ToDouble();
      D.KQt = ReplZPnaPunk(ParamsForm->DQn20Kt1->Text).ToDouble();
      D.KQm = ReplZPnaPunk(ParamsForm->DQt20Km1->Text).ToDouble();
    }
    else
    {
      D.Qn = ReplPunknaZP(ParamsForm->QnE201->Text).ToDouble();
      D.KQt = ReplPunknaZP(ParamsForm->DQn20Kt1->Text).ToDouble();
      D.KQm = ReplPunknaZP(ParamsForm->DQt20Km1->Text).ToDouble();
    }
    DM->DiamNewList.push_back(D);
    //6
    D.Diametr = ParamsForm->dE202->Text.ToInt();
    strcpy(D.Klass, ParamsForm->Ek202->Text.c_str());
    if(DecimalSeparator == '.')
    {
      D.Qn = ReplZPnaPunk(ParamsForm->QnE202->Text).ToDouble();
      D.KQt = ReplZPnaPunk(ParamsForm->DQn20Kt2->Text).ToDouble();
      D.KQm = ReplZPnaPunk(ParamsForm->DQt20Km2->Text).ToDouble();
    }
    else
    {
      D.Qn = ReplPunknaZP(ParamsForm->QnE202->Text).ToDouble();
      D.KQt = ReplPunknaZP(ParamsForm->DQn20Kt2->Text).ToDouble();
      D.KQm = ReplPunknaZP(ParamsForm->DQt20Km2->Text).ToDouble();
    }
    DM->DiamNewList.push_back(D);

  }
  catch(...)
  {
    ShowMessage("� ������ <�������� � ��������������� Q> ������� �� ������n�� ��������");
    delete ParamsForm;
    return;
  }
  try
  {
    DopustPogr P;
    DM->ISODopList.clear();
    //ISO
    strcpy(P.Klass, ParamsForm->KlISOQmX1->Text.c_str()); //Klass
    strcpy(P.QTipe, ParamsForm->QISOQmX1->Text.c_str());  //Vid Q
    strcpy(P.Voda,  ParamsForm->VISOQmX1->Text.c_str());  //Tip Vody
    P.Pogr = ParamsForm->PISOQmX1->Text.ToInt();          //Pogreschnost
    DM->ISODopList.push_back(P); //1
    strcpy(P.Klass, ParamsForm->KlISOQmG1->Text.c_str());
    strcpy(P.QTipe, ParamsForm->QISOQmG1->Text.c_str());
    strcpy(P.Voda,  ParamsForm->VISOQmG1->Text.c_str());
    P.Pogr = ParamsForm->PISOQmG1->Text.ToInt();
    DM->ISODopList.push_back(P); //2
    strcpy(P.Klass, ParamsForm->KlISOQtX1->Text.c_str());
    strcpy(P.QTipe, ParamsForm->QISOQtX1->Text.c_str());
    strcpy(P.Voda,  ParamsForm->VISOQtX1->Text.c_str());
    P.Pogr = ParamsForm->PISOQtX1->Text.ToInt();
    DM->ISODopList.push_back(P); //3
    strcpy(P.Klass, ParamsForm->KlISOQtG1->Text.c_str());
    strcpy(P.QTipe, ParamsForm->QISOQtG1->Text.c_str());
    strcpy(P.Voda,  ParamsForm->VISOQtG1->Text.c_str());
    P.Pogr = ParamsForm->PISOQtG1->Text.ToInt();
    DM->ISODopList.push_back(P); //4
    strcpy(P.Klass, ParamsForm->KlISOQnX1->Text.c_str());
    strcpy(P.QTipe, ParamsForm->QISOQnX1->Text.c_str());
    strcpy(P.Voda,  ParamsForm->VISOQnX1->Text.c_str());
    P.Pogr = ParamsForm->PISOQnX1->Text.ToInt();
    DM->ISODopList.push_back(P); //5
    strcpy(P.Klass, ParamsForm->KlISOQnG1->Text.c_str());
    strcpy(P.QTipe, ParamsForm->QISOQnG1->Text.c_str());
    strcpy(P.Voda,  ParamsForm->VISOQnG1->Text.c_str());
    P.Pogr = ParamsForm->PISOQnG1->Text.ToInt();
    DM->ISODopList.push_back(P); //6
    strcpy(P.Klass, ParamsForm->KlISOQmX2->Text.c_str());
    strcpy(P.QTipe, ParamsForm->QISOQmX2->Text.c_str());
    strcpy(P.Voda,  ParamsForm->VISOQmX2->Text.c_str());
    P.Pogr = ParamsForm->PISOQmX2->Text.ToInt();
    DM->ISODopList.push_back(P); //7
    strcpy(P.Klass, ParamsForm->KlISOQmG2->Text.c_str());
    strcpy(P.QTipe, ParamsForm->QISOQmG2->Text.c_str());
    strcpy(P.Voda,  ParamsForm->VISOQmG2->Text.c_str());
    P.Pogr = ParamsForm->PISOQmG2->Text.ToInt();
    DM->ISODopList.push_back(P); //8
    strcpy(P.Klass, ParamsForm->KlISOQtX2->Text.c_str());
    strcpy(P.QTipe, ParamsForm->QISOQtX2->Text.c_str());
    strcpy(P.Voda,  ParamsForm->VISOQtX2->Text.c_str());
    P.Pogr = ParamsForm->PISOQtX2->Text.ToInt();
    DM->ISODopList.push_back(P); //9
    strcpy(P.Klass, ParamsForm->KlISOQtG2->Text.c_str());
    strcpy(P.QTipe, ParamsForm->QISOQtG2->Text.c_str());
    strcpy(P.Voda,  ParamsForm->VISOQtG2->Text.c_str());
    P.Pogr = ParamsForm->PISOQtG2->Text.ToInt();
    DM->ISODopList.push_back(P); //10
    strcpy(P.Klass, ParamsForm->KlISOQnX2->Text.c_str());
    strcpy(P.QTipe, ParamsForm->QISOQnX2->Text.c_str());
    strcpy(P.Voda,  ParamsForm->VISOQnX2->Text.c_str());
    P.Pogr = ParamsForm->PISOQnX2->Text.ToInt();
    DM->ISODopList.push_back(P); //11
    strcpy(P.Klass, ParamsForm->KlISOQnG2->Text.c_str());
    strcpy(P.QTipe, ParamsForm->QISOQnG2->Text.c_str());
    strcpy(P.Voda,  ParamsForm->VISOQnG2->Text.c_str());
    P.Pogr = ParamsForm->PISOQnG2->Text.ToInt();
    DM->ISODopList.push_back(P); //12
    //LCNE OIML R 49-1
    DM->LNCEDopList.clear();
    strcpy(P.Klass, ParamsForm->KlOIMLQmX1->Text.c_str()); //Klass
    strcpy(P.QTipe, ParamsForm->QOIMLQmX1->Text.c_str());  //Vid Q
    strcpy(P.Voda,  ParamsForm->VOIMLQmX1->Text.c_str());  //Tip Vody
    P.Pogr = ParamsForm->POIMLQmX1->Text.ToInt();          //Pogreschnost
    DM->LNCEDopList.push_back(P); //1
    strcpy(P.Klass, ParamsForm->KlOIMLQmG1->Text.c_str());
    strcpy(P.QTipe, ParamsForm->QOIMLQmG1->Text.c_str());
    strcpy(P.Voda,  ParamsForm->VOIMLQmG1->Text.c_str());
    P.Pogr = ParamsForm->POIMLQmG1->Text.ToInt();
    DM->LNCEDopList.push_back(P); //2
    strcpy(P.Klass, ParamsForm->KlOIMLQtX1->Text.c_str());
    strcpy(P.QTipe, ParamsForm->QOIMLQtX1->Text.c_str());
    strcpy(P.Voda,  ParamsForm->VOIMLQtX1->Text.c_str());
    P.Pogr = ParamsForm->POIMLQtX1->Text.ToInt();
    DM->LNCEDopList.push_back(P); //3
    strcpy(P.Klass, ParamsForm->KlOIMLQtG1->Text.c_str());
    strcpy(P.QTipe, ParamsForm->QOIMLQtG1->Text.c_str());
    strcpy(P.Voda,  ParamsForm->VOIMLQtG1->Text.c_str());
    P.Pogr = ParamsForm->POIMLQtG1->Text.ToInt();
    DM->LNCEDopList.push_back(P); //4
    strcpy(P.Klass, ParamsForm->KlOIMLQnX1->Text.c_str());
    strcpy(P.QTipe, ParamsForm->QOIMLQnX1->Text.c_str());
    strcpy(P.Voda,  ParamsForm->VOIMLQnX1->Text.c_str());
    P.Pogr = ParamsForm->POIMLQnX1->Text.ToInt();
    DM->LNCEDopList.push_back(P); //5
    strcpy(P.Klass, ParamsForm->KlOIMLQnG1->Text.c_str());
    strcpy(P.QTipe, ParamsForm->QOIMLQnG1->Text.c_str());
    strcpy(P.Voda,  ParamsForm->VOIMLQnG1->Text.c_str());
    P.Pogr = ParamsForm->POIMLQnG1->Text.ToInt();
    DM->LNCEDopList.push_back(P); //6
    strcpy(P.Klass, ParamsForm->KlOIMLQmX2->Text.c_str());  //7
    strcpy(P.QTipe, ParamsForm->QOIMLQmX2->Text.c_str());
    strcpy(P.Voda,  ParamsForm->VOIMLQmX2->Text.c_str());
    P.Pogr = ParamsForm->POIMLQmX2->Text.ToInt();
    DM->LNCEDopList.push_back(P); //7
    strcpy(P.Klass, ParamsForm->KlOIMLQmG2->Text.c_str());  //8
    strcpy(P.QTipe, ParamsForm->VOIMLQmG2->Text.c_str());
    strcpy(P.Voda,  ParamsForm->VOIMLQmG2->Text.c_str());
    P.Pogr = ParamsForm->POIMLQmG2->Text.ToInt();
    DM->LNCEDopList.push_back(P); //8
    strcpy(P.Klass, ParamsForm->KlOIMLQtX2->Text.c_str());  //9
    strcpy(P.QTipe, ParamsForm->QOIMLQtX2->Text.c_str());
    strcpy(P.Voda,  ParamsForm->VOIMLQtX2->Text.c_str());
    P.Pogr = ParamsForm->POIMLQtX2->Text.ToInt();
    DM->LNCEDopList.push_back(P); //9
    strcpy(P.Klass, ParamsForm->KlOIMLQtG2->Text.c_str());   //10
    strcpy(P.QTipe, ParamsForm->QOIMLQtG2->Text.c_str());
    strcpy(P.Voda,  ParamsForm->VOIMLQtG2->Text.c_str());
    P.Pogr = ParamsForm->POIMLQtG2->Text.ToInt();
    DM->LNCEDopList.push_back(P); //10
    strcpy(P.Klass, ParamsForm->KlOIMLQnX2->Text.c_str());   //11
    strcpy(P.QTipe, ParamsForm->QOIMLQnX2->Text.c_str());
    strcpy(P.Voda,  ParamsForm->VOIMLQnX2->Text.c_str());
    P.Pogr = ParamsForm->POIMLQnX2->Text.ToInt();
    DM->LNCEDopList.push_back(P); //11
    strcpy(P.Klass, ParamsForm->KlOIMLQnG2->Text.c_str());   //12
    strcpy(P.QTipe, ParamsForm->QOIMLQnG2->Text.c_str());
    strcpy(P.Voda,  ParamsForm->VOIMLQnG2->Text.c_str());
    P.Pogr = ParamsForm->POIMLQnG2->Text.ToInt();
    DM->LNCEDopList.push_back(P); //12
    //���� 3580
    DM->OLDDopList.clear();
    strcpy(P.Klass, ParamsForm->KlOLDQmXA->Text.c_str()); //Klass
    strcpy(P.QTipe, ParamsForm->QOLDQmXA->Text.c_str());  //Vid Q
    strcpy(P.Voda,  ParamsForm->VOLDQmXA->Text.c_str());  //Tip Vody
    P.Pogr = ParamsForm->POLDQmXA->Text.ToInt();          //Pogreschnost
    DM->OLDDopList.push_back(P); //1
    strcpy(P.Klass, ParamsForm->KlOLDQmGA->Text.c_str());
    strcpy(P.QTipe, ParamsForm->QOLDQmGA->Text.c_str());
    strcpy(P.Voda,  ParamsForm->VOLDQmGA->Text.c_str());
    P.Pogr = ParamsForm->POLDQmGA->Text.ToInt();
    DM->OLDDopList.push_back(P); //2
    strcpy(P.Klass, ParamsForm->KlOLDQtXA->Text.c_str());
    strcpy(P.QTipe, ParamsForm->QOLDQtXA->Text.c_str());
    strcpy(P.Voda,  ParamsForm->VOLDQtXA->Text.c_str());
    P.Pogr = ParamsForm->POLDQtXA->Text.ToInt();
    DM->OLDDopList.push_back(P); //3
    strcpy(P.Klass, ParamsForm->KlOLDQtGA->Text.c_str());
    strcpy(P.QTipe, ParamsForm->QOLDQtGA->Text.c_str());
    strcpy(P.Voda,  ParamsForm->VOLDQtGA->Text.c_str());
    P.Pogr = ParamsForm->POLDQtGA->Text.ToInt();
    DM->OLDDopList.push_back(P); //4
    strcpy(P.Klass, ParamsForm->KlOLDQnXA->Text.c_str());
    strcpy(P.QTipe, ParamsForm->QOLDQnXA->Text.c_str());
    strcpy(P.Voda,  ParamsForm->VOLDQnXA->Text.c_str());
    P.Pogr = ParamsForm->POLDQnXA->Text.ToInt();
    DM->OLDDopList.push_back(P); //5
    strcpy(P.Klass, ParamsForm->KlOLDQnGA->Text.c_str());
    strcpy(P.QTipe, ParamsForm->QOLDQnGA->Text.c_str());
    strcpy(P.Voda,  ParamsForm->VOLDQnGA->Text.c_str());
    P.Pogr = ParamsForm->POLDQnGA->Text.ToInt();
    DM->OLDDopList.push_back(P); //6
    strcpy(P.Klass, ParamsForm->KlOLDQmXB->Text.c_str());  //7
    strcpy(P.QTipe, ParamsForm->QOLDQmXB->Text.c_str());
    strcpy(P.Voda,  ParamsForm->VOLDQmXB->Text.c_str());
    P.Pogr = ParamsForm->POLDQmXB->Text.ToInt();
    DM->OLDDopList.push_back(P); //7
    strcpy(P.Klass, ParamsForm->KlOLDQmGB->Text.c_str());  //8
    strcpy(P.QTipe, ParamsForm->VOLDQmGB->Text.c_str());
    strcpy(P.Voda,  ParamsForm->VOLDQmGB->Text.c_str());
    P.Pogr = ParamsForm->POLDQmGB->Text.ToInt();
    DM->OLDDopList.push_back(P); //8
    strcpy(P.Klass, ParamsForm->KlOLDQtXB->Text.c_str());  //9
    strcpy(P.QTipe, ParamsForm->QOLDQtXB->Text.c_str());
    strcpy(P.Voda,  ParamsForm->VOLDQtXB->Text.c_str());
    P.Pogr = ParamsForm->POLDQtXB->Text.ToInt();
    DM->OLDDopList.push_back(P); //9
    strcpy(P.Klass, ParamsForm->KlOLDQtGB->Text.c_str());   //10
    strcpy(P.QTipe, ParamsForm->QOLDQtGB->Text.c_str());
    strcpy(P.Voda,  ParamsForm->VOLDQtGB->Text.c_str());
    P.Pogr = ParamsForm->POLDQtGB->Text.ToInt();
    DM->OLDDopList.push_back(P); //10
    strcpy(P.Klass, ParamsForm->KlOLDQnXB->Text.c_str());   //11
    strcpy(P.QTipe, ParamsForm->QOLDQnXB->Text.c_str());
    strcpy(P.Voda,  ParamsForm->VOLDQnXB->Text.c_str());
    P.Pogr = ParamsForm->POLDQnXB->Text.ToInt();
    DM->OLDDopList.push_back(P); //11
    strcpy(P.Klass, ParamsForm->KlOLDQnGB->Text.c_str());   //12
    strcpy(P.QTipe, ParamsForm->QOLDQnGB->Text.c_str());
    strcpy(P.Voda,  ParamsForm->VOLDQnGB->Text.c_str());
    P.Pogr = ParamsForm->POLDQnGB->Text.ToInt();
    DM->OLDDopList.push_back(P); //12
  }
  catch(...)
  {
    ShowMessage("� ������ ������������ ������� �� ������n�� ��������");
    delete ParamsForm;
    return;
  }
  try
  {
    if(DecimalSeparator == '.')
    {
      DM->QminLGr = ReplZPnaPunk(ParamsForm->QminLGr->Text).ToDouble();
      DM->QminRGr = ReplZPnaPunk(ParamsForm->QminRGr->Text).ToDouble();
      DM->QtLGr = ReplZPnaPunk(ParamsForm->QtLGr->Text).ToDouble();
      DM->QtRGr = ReplZPnaPunk(ParamsForm->QtRGr->Text).ToDouble();
      DM->QnLGr = ReplZPnaPunk(ParamsForm->QnLGr->Text).ToDouble();
      DM->QnRGr = ReplZPnaPunk(ParamsForm->QnRGr->Text).ToDouble();
      DM->TXolL = ReplZPnaPunk(ParamsForm->TXolL->Text).ToDouble();
      DM->TXolR = ReplZPnaPunk(ParamsForm->TXolR->Text).ToDouble();
      DM->TGorL = ReplZPnaPunk(ParamsForm->TGorL->Text).ToDouble();
      DM->TGorR = ReplZPnaPunk(ParamsForm->TGorR->Text).ToDouble();
      DM->VKonst = ReplZPnaPunk(ParamsForm->VKonst->Text).ToDouble();
      DM->TimeConst = ReplZPnaPunk(ParamsForm->TimeConst->Text).ToDouble();
    }
    else
    {
      DM->QminLGr = ReplPunknaZP(ParamsForm->QminLGr->Text).ToDouble();
      DM->QminRGr = ReplPunknaZP(ParamsForm->QminRGr->Text).ToDouble();
      DM->QtLGr   = ReplPunknaZP(ParamsForm->QtLGr->Text).ToDouble();
      DM->QtRGr   = ReplPunknaZP(ParamsForm->QtRGr->Text).ToDouble();
      DM->QnLGr   = ReplPunknaZP(ParamsForm->QnLGr->Text).ToDouble();
      DM->QnRGr   = ReplPunknaZP(ParamsForm->QnRGr->Text).ToDouble();
      DM->TXolL   = ReplPunknaZP(ParamsForm->TXolL->Text).ToDouble();
      DM->TXolR   = ReplPunknaZP(ParamsForm->TXolR->Text).ToDouble();
      DM->TGorL   = ReplPunknaZP(ParamsForm->TGorL->Text).ToDouble();
      DM->TGorR   = ReplPunknaZP(ParamsForm->TGorR->Text).ToDouble();
      DM->VKonst   = ReplPunknaZP(ParamsForm->VKonst->Text).ToDouble();
      DM->TimeConst   = ReplPunknaZP(ParamsForm->TimeConst->Text).ToDouble();
    }
  }
  catch(...)
  {
    ShowMessage("� ������ ������ ������� �� ������n�� ��������");
    delete ParamsForm;
    return;
  }
  if(!DM->InsertParametersPx(ParamsForm->SQLString))
  {
    AnsiString S = "�� �������� �������  - Parameters" + DM->ErrorString;
    ShowMessage(S);
    return;
  }
}

/*
  Reg->WriteInteger("Proliv","Params",1); //�������� � ��������������� Q�������� � ��������������� Q

  Reg->WriteString("Proliv","Qn10a",ParamsForm->Qn10a->Text);
  Reg->WriteString("Proliv","DQn10Kta",ParamsForm->DQn10Kta->Text);
  Reg->WriteString("Proliv","DQt10Kma",ParamsForm->DQt10Kma->Text);

  Reg->WriteString("Proliv","Qn10b",ParamsForm->Qn10b->Text);
  Reg->WriteString("Proliv","DQn10Ktb",ParamsForm->DQn10Ktb->Text);
  Reg->WriteString("Proliv","DQt10Kmb",ParamsForm->DQt10Kmb->Text);

  Reg->WriteString("Proliv","Qn15a",ParamsForm->Qn15a->Text);
  Reg->WriteString("Proliv","DQn15Kta",ParamsForm->DQn15Kta->Text);
  Reg->WriteString("Proliv","DQt15Kma",ParamsForm->DQt15Kma->Text);

  Reg->WriteString("Proliv","Qn15b",ParamsForm->Qn15b->Text);
  Reg->WriteString("Proliv","DQn15Ktb",ParamsForm->DQn15Ktb->Text);
  Reg->WriteString("Proliv","DQt15Kmb",ParamsForm->DQt15Kmb->Text);

  Reg->WriteString("Proliv","Qn20a",ParamsForm->Qn20a->Text);
  Reg->WriteString("Proliv","DQn20Kta",ParamsForm->DQn20Kta->Text);
  Reg->WriteString("Proliv","DQt20Kma",ParamsForm->DQt20Kma->Text);

  Reg->WriteString("Proliv","Qn20b",ParamsForm->Qn20b->Text);
  Reg->WriteString("Proliv","DQn20Ktb",ParamsForm->DQn20Ktb->Text);
  Reg->WriteString("Proliv","DQt20Kmb",ParamsForm->DQt20Kmb->Text);

  Reg->WriteString("Proliv","QnE101",ParamsForm->QnE101->Text);
  Reg->WriteString("Proliv","DQn10Kt1",ParamsForm->DQn10Kt1->Text);
  Reg->WriteString("Proliv","DQt10Km1",ParamsForm->DQt10Km1->Text);

  Reg->WriteString("Proliv","QnE102",ParamsForm->QnE102->Text);
  Reg->WriteString("Proliv","DQn10Kt2",ParamsForm->DQn10Kt2->Text);
  Reg->WriteString("Proliv","DQt10Km2",ParamsForm->DQt10Km2->Text);

  Reg->WriteString("Proliv","QnE151",ParamsForm->QnE151->Text);
  Reg->WriteString("Proliv","DQn15Kt1",ParamsForm->DQn15Kt1->Text);
  Reg->WriteString("Proliv","DQt15Km1",ParamsForm->DQt15Km1->Text);

  Reg->WriteString("Proliv","QnE152",ParamsForm->QnE152->Text);
  Reg->WriteString("Proliv","DQn15Kt2",ParamsForm->DQn15Kt2->Text);
  Reg->WriteString("Proliv","DQt15Km2",ParamsForm->DQt15Km2->Text);

  Reg->WriteString("Proliv","QnE201",ParamsForm->QnE201->Text);
  Reg->WriteString("Proliv","DQn20Kt1",ParamsForm->DQn20Kt1->Text);
  Reg->WriteString("Proliv","DQt20Km1",ParamsForm->DQt20Km1->Text);

  Reg->WriteString("Proliv","QnE202",ParamsForm->QnE202->Text);
  Reg->WriteString("Proliv","DQn20Kt2",ParamsForm->DQn20Kt2->Text);
  Reg->WriteString("Proliv","DQt20Km2",ParamsForm->DQt20Km2->Text);

  //������� ������������
  Reg->WriteString("Proliv","PISOQmX1",ParamsForm->PISOQmX1->Text);
  Reg->WriteString("Proliv","PISOQmG1",ParamsForm->PISOQmG1->Text);
  Reg->WriteString("Proliv","PISOQtX1",ParamsForm->PISOQtX1->Text);
  Reg->WriteString("Proliv","PISOQtG1",ParamsForm->PISOQtG1->Text);
  Reg->WriteString("Proliv","PISOQnX1",ParamsForm->PISOQnX1->Text);
  Reg->WriteString("Proliv","PISOQnG1",ParamsForm->PISOQnG1->Text);
  Reg->WriteString("Proliv","PISOQmX2",ParamsForm->PISOQmX2->Text);
  Reg->WriteString("Proliv","PISOQmG2",ParamsForm->PISOQmG2->Text);
  Reg->WriteString("Proliv","PISOQtX2",ParamsForm->PISOQtX2->Text);
  Reg->WriteString("Proliv","PISOQtG2",ParamsForm->PISOQtG2->Text);
  Reg->WriteString("Proliv","PISOQnX2",ParamsForm->PISOQnX2->Text);
  Reg->WriteString("Proliv","PISOQnG2",ParamsForm->PISOQnG2->Text);

  Reg->WriteString("Proliv","POIMLQmX1",ParamsForm->POIMLQmX1->Text);
  Reg->WriteString("Proliv","POIMLQmG1",ParamsForm->POIMLQmG1->Text);
  Reg->WriteString("Proliv","POIMLQtX1",ParamsForm->POIMLQtX1->Text);
  Reg->WriteString("Proliv","POIMLQtG1",ParamsForm->POIMLQtG1->Text);
  Reg->WriteString("Proliv","POIMLQnX1",ParamsForm->POIMLQnX1->Text);
  Reg->WriteString("Proliv","POIMLQnG1",ParamsForm->POIMLQnG1->Text);
  Reg->WriteString("Proliv","POIMLQmX2",ParamsForm->POIMLQmX2->Text);
  Reg->WriteString("Proliv","POIMLQmG2",ParamsForm->POIMLQmG2->Text);
  Reg->WriteString("Proliv","POIMLQtX2",ParamsForm->POIMLQtX2->Text);
  Reg->WriteString("Proliv","POIMLQtG2",ParamsForm->POIMLQtG2->Text);
  Reg->WriteString("Proliv","POIMLQnX2",ParamsForm->POIMLQnX2->Text);
  Reg->WriteString("Proliv","POIMLQnG2",ParamsForm->POIMLQnG2->Text);

  Reg->WriteString("Proliv","POLDQmXA",ParamsForm->POLDQmXA->Text);
  Reg->WriteString("Proliv","POLDQmGA",ParamsForm->POLDQmGA->Text);
  Reg->WriteString("Proliv","POLDQtXA",ParamsForm->POLDQtXA->Text);
  Reg->WriteString("Proliv","POLDQtGA",ParamsForm->POLDQtGA->Text);
  Reg->WriteString("Proliv","POLDQnXA",ParamsForm->POLDQnXA->Text);
  Reg->WriteString("Proliv","POLDQnGA",ParamsForm->POLDQnGA->Text);
  Reg->WriteString("Proliv","POLDQmXB",ParamsForm->POLDQmXB->Text);
  Reg->WriteString("Proliv","POLDQmGB",ParamsForm->POLDQmGB->Text);
  Reg->WriteString("Proliv","POLDQtXB",ParamsForm->POLDQtXB->Text);
  Reg->WriteString("Proliv","POLDQtGB",ParamsForm->POLDQtGB->Text);
  Reg->WriteString("Proliv","POLDQnXB",ParamsForm->POLDQnXB->Text);
  Reg->WriteString("Proliv","POLDQnGB",ParamsForm->POLDQnGB->Text);

  Reg->WriteString("Proliv","QminLGr",ParamsForm->QminLGr->Text);
  Reg->WriteString("Proliv","QminRGr",ParamsForm->QminRGr->Text);
  Reg->WriteString("Proliv","QtLGr",ParamsForm->QtLGr->Text);
  Reg->WriteString("Proliv","QtRGr",ParamsForm->QtRGr->Text);
  Reg->WriteString("Proliv","QnLGr",ParamsForm->QnLGr->Text);
  Reg->WriteString("Proliv","QnRGr",ParamsForm->QnRGr->Text);
  Reg->WriteString("Proliv","TXolL",ParamsForm->TXolL->Text);
  Reg->WriteString("Proliv","TXolR",ParamsForm->TXolR->Text);
  Reg->WriteString("Proliv","TGorL",ParamsForm->TGorL->Text);
  Reg->WriteString("Proliv","TGorR",ParamsForm->TGorR->Text);
  Reg->WriteString("Proliv","VKonst",ParamsForm->VKonst->Text);
  Reg->WriteString("Proliv","TimeConst",ParamsForm->TimeConst->Text);
}
*/
//---------------------------------------------------------------------------
void TMainKPSForm::ReadFromReestr(void)
{
  ParamsForm = new TParamsForm(this, DM, rParams);
  ReadFromReestrToChange();
  delete ParamsForm;
}
//---------------------------------------------------------------------------
void TMainKPSForm::ReadFromReestrToChange(void)
{
//  Reg->ReadString("Proliv","Params",1); //�������� � ��������������� Q�������� � ��������������� Q
/*
  ParamsForm->Qn10a->Text    = Reg->ReadString("Proliv","Qn10a","0");
  ParamsForm->DQn10Kta->Text = Reg->ReadString("Proliv","DQn10Kta","0");
  ParamsForm->DQt10Kma->Text = Reg->ReadString("Proliv","DQt10Kma","0");
  ParamsForm->Qn10b->Text    = Reg->ReadString("Proliv","Qn10b","0");
  ParamsForm->DQn10Ktb->Text = Reg->ReadString("Proliv","DQn10Ktb","0");
  ParamsForm->DQt10Kmb->Text = Reg->ReadString("Proliv","DQt10Kmb","0");
  ParamsForm->Qn15a->Text    = Reg->ReadString("Proliv","Qn15a","0");
  ParamsForm->DQn15Kta->Text = Reg->ReadString("Proliv","DQn15Kta","0");
  ParamsForm->DQt15Kma->Text = Reg->ReadString("Proliv","DQt15Kma","0");
  ParamsForm->Qn15b->Text    = Reg->ReadString("Proliv","Qn15b","0");
  ParamsForm->DQn15Ktb->Text = Reg->ReadString("Proliv","DQn15Ktb","0");
  ParamsForm->DQt15Kmb->Text = Reg->ReadString("Proliv","DQt15Kmb","0");
  ParamsForm->Qn20a->Text    = Reg->ReadString("Proliv","Qn20a","0");
  ParamsForm->DQn20Kta->Text = Reg->ReadString("Proliv","DQn20Kta","0");
  ParamsForm->DQt20Kma->Text = Reg->ReadString("Proliv","DQt20Kma","0");
  ParamsForm->Qn20b->Text    = Reg->ReadString("Proliv","Qn20b","0");
  ParamsForm->DQn20Ktb->Text = Reg->ReadString("Proliv","DQn20Ktb","0");
  ParamsForm->DQt20Kmb->Text = Reg->ReadString("Proliv","DQt20Kmb","0");
  ParamsForm->QnE101->Text   = Reg->ReadString("Proliv","QnE101","0");
  ParamsForm->DQn10Kt1->Text = Reg->ReadString("Proliv","DQn10Kt1","0");
  ParamsForm->DQt10Km1->Text = Reg->ReadString("Proliv","DQt10Km1","0");
  ParamsForm->QnE102->Text   = Reg->ReadString("Proliv","QnE102","0");
  ParamsForm->DQn10Kt2->Text = Reg->ReadString("Proliv","DQn10Kt2","0");
  ParamsForm->DQt10Km2->Text = Reg->ReadString("Proliv","DQt10Km2","0");
  ParamsForm->QnE151->Text   = Reg->ReadString("Proliv","QnE151","0");
  ParamsForm->DQn15Kt1->Text = Reg->ReadString("Proliv","DQn15Kt1","0");
  ParamsForm->DQt15Km1->Text = Reg->ReadString("Proliv","DQt15Km1","0");
  ParamsForm->QnE152->Text   = Reg->ReadString("Proliv","QnE152","0");
  ParamsForm->DQn15Kt2->Text = Reg->ReadString("Proliv","DQn15Kt2","0");
  ParamsForm->DQt15Km2->Text = Reg->ReadString("Proliv","DQt15Km2","0");
  ParamsForm->QnE201->Text   = Reg->ReadString("Proliv","QnE201","0");
  ParamsForm->DQn20Kt1->Text = Reg->ReadString("Proliv","DQn20Kt1","0");
  ParamsForm->DQt20Km1->Text = Reg->ReadString("Proliv","DQt20Km1","0");
  ParamsForm->QnE202->Text   = Reg->ReadString("Proliv","QnE202","0");
  ParamsForm->DQn20Kt2->Text = Reg->ReadString("Proliv","DQn20Kt2","0");
  ParamsForm->DQt20Km2->Text = Reg->ReadString("Proliv","DQt20Km2","0");


  ParamsForm->PISOQmX1->Text = Reg->ReadString("Proliv","PISOQmX1","0");
  ParamsForm->PISOQmG1->Text = Reg->ReadString("Proliv","PISOQmG1","0");
  ParamsForm->PISOQtX1->Text = Reg->ReadString("Proliv","PISOQtX1","0");
  ParamsForm->PISOQtG1->Text = Reg->ReadString("Proliv","PISOQtG1","0");
  ParamsForm->PISOQnX1->Text = Reg->ReadString("Proliv","PISOQnX1","0");
  ParamsForm->PISOQnG1->Text = Reg->ReadString("Proliv","PISOQnG1","0");
  ParamsForm->PISOQmX2->Text = Reg->ReadString("Proliv","PISOQmX2","0");
  ParamsForm->PISOQmG2->Text = Reg->ReadString("Proliv","PISOQmG2","0");
  ParamsForm->PISOQtX2->Text = Reg->ReadString("Proliv","PISOQtX2","0");
  ParamsForm->PISOQtG2->Text = Reg->ReadString("Proliv","PISOQtG2","0");
  ParamsForm->PISOQnX2->Text = Reg->ReadString("Proliv","PISOQnX2","0");
  ParamsForm->PISOQnG2->Text = Reg->ReadString("Proliv","PISOQnG2","0");

  ParamsForm->POIMLQmX1->Text = Reg->ReadString("Proliv","POIMLQmX1","0");
  ParamsForm->POIMLQmG1->Text = Reg->ReadString("Proliv","POIMLQmG1","0");
  ParamsForm->POIMLQtX1->Text = Reg->ReadString("Proliv","POIMLQtX1","0");
  ParamsForm->POIMLQtG1->Text = Reg->ReadString("Proliv","POIMLQtG1","0");
  ParamsForm->POIMLQnX1->Text = Reg->ReadString("Proliv","POIMLQnX1","0");
  ParamsForm->POIMLQnG1->Text = Reg->ReadString("Proliv","POIMLQnG1","0");
  ParamsForm->POIMLQmX2->Text = Reg->ReadString("Proliv","POIMLQmX2","0");
  ParamsForm->POIMLQmG2->Text = Reg->ReadString("Proliv","POIMLQmG2","0");
  ParamsForm->POIMLQtX2->Text = Reg->ReadString("Proliv","POIMLQtX2","0");
  ParamsForm->POIMLQtG2->Text = Reg->ReadString("Proliv","POIMLQtG2","0");
  ParamsForm->POIMLQnX2->Text = Reg->ReadString("Proliv","POIMLQnX2","0");
  ParamsForm->POIMLQnG2->Text = Reg->ReadString("Proliv","POIMLQnG2","0");

  ParamsForm->POLDQmXA->Text = Reg->ReadString("Proliv","POLDQmXA","0");
  ParamsForm->POLDQmGA->Text = Reg->ReadString("Proliv","POLDQmGA","0");
  ParamsForm->POLDQtXA->Text = Reg->ReadString("Proliv","POLDQtXA","0");
  ParamsForm->POLDQtGA->Text = Reg->ReadString("Proliv","POLDQtGA","0");
  ParamsForm->POLDQnXA->Text = Reg->ReadString("Proliv","POLDQnXA","0");
  ParamsForm->POLDQnGA->Text = Reg->ReadString("Proliv","POLDQnGA","0");
  ParamsForm->POLDQmXB->Text = Reg->ReadString("Proliv","POLDQmXB","0");
  ParamsForm->POLDQmGB->Text = Reg->ReadString("Proliv","POLDQmGB","0");
  ParamsForm->POLDQtXB->Text = Reg->ReadString("Proliv","POLDQtXB","0");
  ParamsForm->POLDQtGB->Text = Reg->ReadString("Proliv","POLDQtGB","0");
  ParamsForm->POLDQnXB->Text = Reg->ReadString("Proliv","POLDQnXB","0");
  ParamsForm->POLDQnGB->Text = Reg->ReadString("Proliv","POLDQnGB","0");

  ParamsForm->QminLGr->Text  = Reg->ReadString("Proliv","QminLGr","0");
  ParamsForm->QminRGr->Text  = Reg->ReadString("Proliv","QminRGr","0");
  ParamsForm->QtLGr->Text    = Reg->ReadString("Proliv","QtLGr","0");
  ParamsForm->QtRGr->Text    = Reg->ReadString("Proliv","QtRGr","0");
  ParamsForm->QnLGr->Text    = Reg->ReadString("Proliv","QnLGr","0");
  ParamsForm->QnRGr->Text    = Reg->ReadString("Proliv","QnRGr","0");
  ParamsForm->TXolL->Text    = Reg->ReadString("Proliv","TXolL","0");
  ParamsForm->TXolR->Text    = Reg->ReadString("Proliv","TXolR","0");
  ParamsForm->TGorL->Text    = Reg->ReadString("Proliv","TGorL","0");
  ParamsForm->TGorR->Text    = Reg->ReadString("Proliv","TGorR","0");
  ParamsForm->VKonst->Text   = Reg->ReadString("Proliv","VKonst","0");
  ParamsForm->TimeConst->Text = Reg->ReadString("Proliv","TimeConst","0");
*/
    AnsiString S = "SELECT * FROM Parameters;";
    if(DM->ParametersRead(S))
    {
      DM->Query3->First();
      ParamsForm->Qn10a->Text = Trim(DM->Query3->FieldByName("Qn10a")->AsString);      // vos ADOQuery1
      ParamsForm->DQn10Kta->Text = Trim(DM->Query3->FieldByName("DQn10Kta")->AsString);
      ParamsForm->DQt10Kma->Text = Trim(DM->Query3->FieldByName("DQt10Kma")->AsString);
      ParamsForm->Qn10b->Text = Trim(DM->Query3->FieldByName("Qn10b")->AsString);
      ParamsForm->DQn10Ktb->Text = Trim(DM->Query3->FieldByName("DQn10Ktb")->AsString);
      ParamsForm->DQt10Kmb->Text = Trim(DM->Query3->FieldByName("DQt10Kmb")->AsString);
      ParamsForm->Qn15a->Text = Trim(DM->Query3->FieldByName("Qn15a")->AsString);
      ParamsForm->DQn15Kta->Text = Trim(DM->Query3->FieldByName("DQn15Kta")->AsString);
      ParamsForm->DQt15Kma->Text = Trim(DM->Query3->FieldByName("DQt15Kma")->AsString);
      ParamsForm->Qn15b->Text = Trim(DM->Query3->FieldByName("Qn15b")->AsString);
      ParamsForm->DQn15Ktb->Text = Trim(DM->Query3->FieldByName("DQn15Ktb")->AsString);
      ParamsForm->DQt15Kmb->Text = Trim(DM->Query3->FieldByName("DQt15Kmb")->AsString);
      ParamsForm->Qn20a->Text = Trim(DM->Query3->FieldByName("Qn20a")->AsString);
      ParamsForm->DQn20Kta->Text = Trim(DM->Query3->FieldByName("DQn20Kta")->AsString);
      ParamsForm->DQt20Kma->Text = Trim(DM->Query3->FieldByName("DQt20Kma")->AsString);
      ParamsForm->Qn20b->Text = Trim(DM->Query3->FieldByName("Qn20b")->AsString);
      ParamsForm->DQn20Ktb->Text = Trim(DM->Query3->FieldByName("DQn20Ktb")->AsString);
      ParamsForm->DQt20Kmb->Text = Trim(DM->Query3->FieldByName("DQt20Kmb")->AsString);
      ParamsForm->QnE101->Text = Trim(DM->Query3->FieldByName("QnE101")->AsString);
      ParamsForm->DQn10Kt1->Text = Trim(DM->Query3->FieldByName("DQn10Kt1")->AsString);
      ParamsForm->DQt10Km1->Text = Trim(DM->Query3->FieldByName("DQt10Km1")->AsString);
      ParamsForm->QnE102->Text = Trim(DM->Query3->FieldByName("QnE102")->AsString);
      ParamsForm->DQn10Kt2->Text = Trim(DM->Query3->FieldByName("DQn10Kt2")->AsString);
      ParamsForm->DQn10Kt2->Text = Trim(DM->Query3->FieldByName("DQn10Kt2")->AsString);
      ParamsForm->QnE151->Text = Trim(DM->Query3->FieldByName("QnE151")->AsString);
      ParamsForm->DQn15Kt1->Text = Trim(DM->Query3->FieldByName("DQn15Kt1")->AsString);
      ParamsForm->DQt15Km1->Text = Trim(DM->Query3->FieldByName("DQt15Km1")->AsString);
      ParamsForm->QnE152->Text = Trim(DM->Query3->FieldByName("QnE152")->AsString);
      ParamsForm->DQn15Kt2->Text = Trim(DM->Query3->FieldByName("DQn15Kt2")->AsString);
      ParamsForm->DQt15Km2->Text = Trim(DM->Query3->FieldByName("DQt15Km2")->AsString);
      ParamsForm->QnE201->Text = Trim(DM->Query3->FieldByName("QnE201")->AsString);
      ParamsForm->DQn20Kt1->Text = Trim(DM->Query3->FieldByName("DQn20Kt1")->AsString);
      ParamsForm->DQt20Km1->Text = Trim(DM->Query3->FieldByName("DQt20Km1")->AsString);
      ParamsForm->QnE202->Text = Trim(DM->Query3->FieldByName("QnE202")->AsString);
      ParamsForm->DQn20Kt2->Text = Trim(DM->Query3->FieldByName("DQn20Kt2")->AsString);
      ParamsForm->DQt20Km2->Text = Trim(DM->Query3->FieldByName("DQt20Km2")->AsString);
      ParamsForm->PISOQmX1->Text = Trim(DM->Query3->FieldByName("PISOQmX1")->AsString);
      ParamsForm->PISOQmG1->Text = Trim(DM->Query3->FieldByName("PISOQmG1")->AsString);
      ParamsForm->PISOQtX1->Text = Trim(DM->Query3->FieldByName("PISOQtX1")->AsString);
      ParamsForm->PISOQtG1->Text = Trim(DM->Query3->FieldByName("PISOQtG1")->AsString);
      ParamsForm->PISOQnX1->Text = Trim(DM->Query3->FieldByName("PISOQnX1")->AsString);
      ParamsForm->PISOQnG1->Text = Trim(DM->Query3->FieldByName("PISOQnG1")->AsString);
      ParamsForm->PISOQmX2->Text = Trim(DM->Query3->FieldByName("PISOQmX2")->AsString);
      ParamsForm->PISOQmG2->Text = Trim(DM->Query3->FieldByName("PISOQmG2")->AsString);
      ParamsForm->PISOQtX2->Text = Trim(DM->Query3->FieldByName("PISOQtX2")->AsString);
      ParamsForm->PISOQtG2->Text = Trim(DM->Query3->FieldByName("PISOQtG2")->AsString);
      ParamsForm->PISOQnX2->Text = Trim(DM->Query3->FieldByName("PISOQnX2")->AsString);
      ParamsForm->PISOQnG2->Text = Trim(DM->Query3->FieldByName("PISOQnG2")->AsString);
      ParamsForm->POIMLQmX1->Text = Trim(DM->Query3->FieldByName("POIMLQmX1")->AsString);
      ParamsForm->POIMLQmG1->Text = Trim(DM->Query3->FieldByName("POIMLQmG1")->AsString);
      ParamsForm->POIMLQtX1->Text = Trim(DM->Query3->FieldByName("POIMLQtX1")->AsString);
      ParamsForm->POIMLQtG1->Text = Trim(DM->Query3->FieldByName("POIMLQtG1")->AsString);
      ParamsForm->POIMLQnX1->Text = Trim(DM->Query3->FieldByName("POIMLQnX1")->AsString);
      ParamsForm->POIMLQnG1->Text = Trim(DM->Query3->FieldByName("POIMLQnG1")->AsString);
      ParamsForm->POIMLQmX2->Text = Trim(DM->Query3->FieldByName("POIMLQmX2")->AsString);
      ParamsForm->POIMLQmG2->Text = Trim(DM->Query3->FieldByName("POIMLQmG2")->AsString);
      ParamsForm->POIMLQtX2->Text = Trim(DM->Query3->FieldByName("POIMLQtX2")->AsString);
      ParamsForm->POIMLQtG2->Text = Trim(DM->Query3->FieldByName("POIMLQtG2")->AsString);
      ParamsForm->POIMLQnX2->Text = Trim(DM->Query3->FieldByName("POIMLQnX2")->AsString);
      ParamsForm->POIMLQnG2->Text = Trim(DM->Query3->FieldByName("POIMLQnG2")->AsString);
      ParamsForm->POLDQmXA->Text = Trim(DM->Query3->FieldByName("POLDQmXA")->AsString);
      ParamsForm->POLDQmGA->Text = Trim(DM->Query3->FieldByName("POLDQmGA")->AsString);
      ParamsForm->POLDQtXA->Text = Trim(DM->Query3->FieldByName("POLDQtXA")->AsString);
      ParamsForm->POLDQtGA->Text = Trim(DM->Query3->FieldByName("POLDQtGA")->AsString);
      ParamsForm->POLDQnXA->Text = Trim(DM->Query3->FieldByName("POLDQnXA")->AsString);
      ParamsForm->POLDQnGA->Text = Trim(DM->Query3->FieldByName("POLDQnGA")->AsString);
      ParamsForm->POLDQmXB->Text = Trim(DM->Query3->FieldByName("POLDQmXB")->AsString);
      ParamsForm->POLDQmGB->Text = Trim(DM->Query3->FieldByName("POLDQmGB")->AsString);
      ParamsForm->POLDQtXB->Text = Trim(DM->Query3->FieldByName("POLDQtXB")->AsString);
      ParamsForm->POLDQtGB->Text = Trim(DM->Query3->FieldByName("POLDQtGB")->AsString);
      ParamsForm->POLDQnXB->Text = Trim(DM->Query3->FieldByName("POLDQnXB")->AsString);
      ParamsForm->POLDQnGB->Text = Trim(DM->Query3->FieldByName("POLDQnGB")->AsString);
      ParamsForm->QminLGr->Text = Trim(DM->Query3->FieldByName("QminLGr")->AsString);
      ParamsForm->QminRGr->Text = Trim(DM->Query3->FieldByName("QminRGr")->AsString);
      ParamsForm->QtLGr->Text = Trim(DM->Query3->FieldByName("QtLGr")->AsString);
      ParamsForm->QtRGr->Text = Trim(DM->Query3->FieldByName("QtRGr")->AsString);
      ParamsForm->QnLGr->Text = Trim(DM->Query3->FieldByName("QnLGr")->AsString);
      ParamsForm->TXolL->Text = Trim(DM->Query3->FieldByName("TXolL")->AsString);
      ParamsForm->TXolR->Text = Trim(DM->Query3->FieldByName("TXolR")->AsString);
      ParamsForm->TGorL->Text = Trim(DM->Query3->FieldByName("TGorL")->AsString);
      ParamsForm->TGorR->Text = Trim(DM->Query3->FieldByName("TGorR")->AsString);
      ParamsForm->VKonst->Text = Trim(DM->Query3->FieldByName("VKonst")->AsString);
      ParamsForm->TimeConst->Text = Trim(DM->Query3->FieldByName("TimeConst")->AsString);
      DM->Query3->Close();
    }
    else
    {
      S = "��� ������� � ������� - Parameters " + DM->ErrorString;
      ShowMessage(S);
      SelfCloseFlag = true;
      return;
    }
  try
  {
    Diametry D;
    DM->DiamOldList.clear();
    D.Diametr = ParamsForm->d10a->Text.ToInt();
    strcpy(D.Klass, ParamsForm->Dk10a->Text.c_str());
    if(DecimalSeparator == '.')
    {
      D.Qn = ReplZPnaPunk(ParamsForm->Qn10a->Text).ToDouble();
      D.KQt = ReplZPnaPunk(ParamsForm->DQn10Kta->Text).ToDouble();
      D.KQm = ReplZPnaPunk(ParamsForm->DQt10Kma->Text).ToDouble();
    }
    else
    {
      D.Qn = ReplPunknaZP(ParamsForm->Qn10a->Text).ToDouble();
      D.KQt = ReplPunknaZP(ParamsForm->DQn10Kta->Text).ToDouble();
      D.KQm = ReplPunknaZP(ParamsForm->DQt10Kma->Text).ToDouble();
    }
    DM->DiamOldList.push_back(D);
    //2
    D.Diametr = ParamsForm->d10b->Text.ToInt();
    strcpy(D.Klass, ParamsForm->Dk10b->Text.c_str());
    if(DecimalSeparator == '.')
    {
      D.Qn = ReplZPnaPunk(ParamsForm->Qn10b->Text).ToDouble();
      D.KQt = ReplZPnaPunk(ParamsForm->DQn10Ktb->Text).ToDouble();
      D.KQm = ReplZPnaPunk(ParamsForm->DQt10Kmb->Text).ToDouble();
    }
    else
    {
      D.Qn = ReplPunknaZP(ParamsForm->Qn10b->Text).ToDouble();
      D.KQt = ReplPunknaZP(ParamsForm->DQn10Ktb->Text).ToDouble();
      D.KQm = ReplPunknaZP(ParamsForm->DQt10Kmb->Text).ToDouble();
    }
    DM->DiamOldList.push_back(D);
    //3
    D.Diametr = ParamsForm->d15a->Text.ToInt();
    strcpy(D.Klass, ParamsForm->Dk15a->Text.c_str());
    if(DecimalSeparator == '.')
    {
      D.Qn = ReplZPnaPunk(ParamsForm->Qn15a->Text).ToDouble();
      D.KQt = ReplZPnaPunk(ParamsForm->DQn15Kta->Text).ToDouble();
      D.KQm = ReplZPnaPunk(ParamsForm->DQt15Kma->Text).ToDouble();
    }
    else
    {
      D.Qn = ReplPunknaZP(ParamsForm->Qn15a->Text).ToDouble();
      D.KQt = ReplPunknaZP(ParamsForm->DQn15Kta->Text).ToDouble();
      D.KQm = ReplPunknaZP(ParamsForm->DQt15Kma->Text).ToDouble();
    }
    DM->DiamOldList.push_back(D);
    //4
    D.Diametr = ParamsForm->d15b->Text.ToInt();
    strcpy(D.Klass, ParamsForm->Dk15b->Text.c_str());
    if(DecimalSeparator == '.')
    {
      D.Qn = ReplZPnaPunk(ParamsForm->Qn15b->Text).ToDouble();
      D.KQt = ReplZPnaPunk(ParamsForm->DQn15Ktb->Text).ToDouble();
      D.KQm = ReplZPnaPunk(ParamsForm->DQt15Kmb->Text).ToDouble();
    }
    else
    {
      D.Qn = ReplPunknaZP(ParamsForm->Qn15b->Text).ToDouble();
      D.KQt = ReplPunknaZP(ParamsForm->DQn15Ktb->Text).ToDouble();
      D.KQm = ReplPunknaZP(ParamsForm->DQt15Kmb->Text).ToDouble();
    }
    DM->DiamOldList.push_back(D);
    //5
    D.Diametr = ParamsForm->d20a->Text.ToInt();
    strcpy(D.Klass, ParamsForm->Dk20a->Text.c_str());
    if(DecimalSeparator == '.')
    {
      D.Qn = ReplZPnaPunk(ParamsForm->Qn20a->Text).ToDouble();
      D.KQt = ReplZPnaPunk(ParamsForm->DQn20Kta->Text).ToDouble();
      D.KQm = ReplZPnaPunk(ParamsForm->DQt20Kma->Text).ToDouble();
    }
    else
    {
      D.Qn = ReplPunknaZP(ParamsForm->Qn20a->Text).ToDouble();
      D.KQt = ReplPunknaZP(ParamsForm->DQn20Kta->Text).ToDouble();
      D.KQm = ReplPunknaZP(ParamsForm->DQt20Kma->Text).ToDouble();
    }
    DM->DiamOldList.push_back(D);
    //6
    D.Diametr = ParamsForm->d20b->Text.ToInt();
    strcpy(D.Klass, ParamsForm->Dk20b->Text.c_str());
    if(DecimalSeparator == '.')
    {
      D.Qn = ReplZPnaPunk(ParamsForm->Qn20b->Text).ToDouble();
      D.KQt = ReplZPnaPunk(ParamsForm->DQn20Ktb->Text).ToDouble();
      D.KQm = ReplZPnaPunk(ParamsForm->DQt20Kmb->Text).ToDouble();
    }
    else
    {
      D.Qn = ReplPunknaZP(ParamsForm->Qn20b->Text).ToDouble();
      D.KQt = ReplPunknaZP(ParamsForm->DQn20Ktb->Text).ToDouble();
      D.KQm = ReplPunknaZP(ParamsForm->DQt20Kmb->Text).ToDouble();
    }
    DM->DiamOldList.push_back(D);

    DM->DiamNewList.clear();
    D.Diametr = ParamsForm->dE101->Text.ToInt();
    strcpy(D.Klass, ParamsForm->Ek101->Text.c_str());
    if(DecimalSeparator == '.')
    {
      D.Qn = ReplZPnaPunk(ParamsForm->QnE101->Text).ToDouble();
      D.KQt = ReplZPnaPunk(ParamsForm->DQn10Kt1->Text).ToDouble();
      D.KQm = ReplZPnaPunk(ParamsForm->DQt10Km1->Text).ToDouble();
    }
    else
    {
      D.Qn = ReplPunknaZP(ParamsForm->QnE101->Text).ToDouble();
      D.KQt = ReplPunknaZP(ParamsForm->DQn10Kt1->Text).ToDouble();
      D.KQm = ReplPunknaZP(ParamsForm->DQt10Km1->Text).ToDouble();
    }
    DM->DiamNewList.push_back(D);
    //2
    D.Diametr = ParamsForm->dE102->Text.ToInt();
    strcpy(D.Klass, ParamsForm->Ek102->Text.c_str());
    if(DecimalSeparator == '.')
    {
      D.Qn = ReplZPnaPunk(ParamsForm->QnE102->Text).ToDouble();
      D.KQt = ReplZPnaPunk(ParamsForm->DQn10Kt2->Text).ToDouble();
      D.KQm = ReplZPnaPunk(ParamsForm->DQt10Km2->Text).ToDouble();
    }
    else
    {
      D.Qn = ReplPunknaZP(ParamsForm->QnE102->Text).ToDouble();
      D.KQt = ReplPunknaZP(ParamsForm->DQn10Kt2->Text).ToDouble();
      D.KQm = ReplPunknaZP(ParamsForm->DQt10Km2->Text).ToDouble();
    }
    DM->DiamNewList.push_back(D);
    //3
    D.Diametr = ParamsForm->dE151->Text.ToInt();
    strcpy(D.Klass, ParamsForm->Ek151->Text.c_str());
    if(DecimalSeparator == '.')
    {
      D.Qn = ReplZPnaPunk(ParamsForm->QnE151->Text).ToDouble();
      D.KQt = ReplZPnaPunk(ParamsForm->DQn15Kt1->Text).ToDouble();
      D.KQm = ReplZPnaPunk(ParamsForm->DQt15Km1->Text).ToDouble();
    }
    else
    {
      D.Qn = ReplPunknaZP(ParamsForm->QnE151->Text).ToDouble();
      D.KQt = ReplPunknaZP(ParamsForm->DQn15Kt1->Text).ToDouble();
      D.KQm = ReplPunknaZP(ParamsForm->DQt15Km1->Text).ToDouble();
    }
    DM->DiamNewList.push_back(D);
    //4
    D.Diametr = ParamsForm->dE152->Text.ToInt();
    strcpy(D.Klass, ParamsForm->Ek152->Text.c_str());
    if(DecimalSeparator == '.')
    {
      D.Qn = ReplZPnaPunk(ParamsForm->QnE152->Text).ToDouble();
      D.KQt = ReplZPnaPunk(ParamsForm->DQn15Kt2->Text).ToDouble();
      D.KQm = ReplZPnaPunk(ParamsForm->DQt15Km2->Text).ToDouble();
    }
    else
    {
      D.Qn = ReplPunknaZP(ParamsForm->QnE152->Text).ToDouble();
      D.KQt = ReplPunknaZP(ParamsForm->DQn15Kt2->Text).ToDouble();
      D.KQm = ReplPunknaZP(ParamsForm->DQt15Km2->Text).ToDouble();
    }
    DM->DiamNewList.push_back(D);
    //5
    D.Diametr = ParamsForm->dE201->Text.ToInt();
    strcpy(D.Klass, ParamsForm->Ek201->Text.c_str());
    if(DecimalSeparator == '.')
    {
      D.Qn = ReplZPnaPunk(ParamsForm->QnE201->Text).ToDouble();
      D.KQt = ReplZPnaPunk(ParamsForm->DQn20Kt1->Text).ToDouble();
      D.KQm = ReplZPnaPunk(ParamsForm->DQt20Km1->Text).ToDouble();
    }
    else
    {
      D.Qn = ReplPunknaZP(ParamsForm->QnE201->Text).ToDouble();
      D.KQt = ReplPunknaZP(ParamsForm->DQn20Kt1->Text).ToDouble();
      D.KQm = ReplPunknaZP(ParamsForm->DQt20Km1->Text).ToDouble();
    }
    DM->DiamNewList.push_back(D);
    //6
    D.Diametr = ParamsForm->dE202->Text.ToInt();
    strcpy(D.Klass, ParamsForm->Ek202->Text.c_str());
    if(DecimalSeparator == '.')
    {
      D.Qn = ReplZPnaPunk(ParamsForm->QnE202->Text).ToDouble();
      D.KQt = ReplZPnaPunk(ParamsForm->DQn20Kt2->Text).ToDouble();
      D.KQm = ReplZPnaPunk(ParamsForm->DQt20Km2->Text).ToDouble();
    }
    else
    {
      D.Qn = ReplPunknaZP(ParamsForm->QnE202->Text).ToDouble();
      D.KQt = ReplPunknaZP(ParamsForm->DQn20Kt2->Text).ToDouble();
      D.KQm = ReplPunknaZP(ParamsForm->DQt20Km2->Text).ToDouble();
    }
    DM->DiamNewList.push_back(D);

  }
  catch(...)
  {
    ShowMessage("� ������ <�������� � ��������������� Q> ������� �� ������n�� ��������");
    delete ParamsForm;
    return;
  }
  try
  {
    DopustPogr P;
    DM->ISODopList.clear();
    //ISO
    strcpy(P.Klass, ParamsForm->KlISOQmX1->Text.c_str()); //Klass
    strcpy(P.QTipe, ParamsForm->QISOQmX1->Text.c_str());  //Vid Q
    strcpy(P.Voda,  ParamsForm->VISOQmX1->Text.c_str());  //Tip Vody
    if(DecimalSeparator == '.')
      P.Pogr = ReplZPnaPunk(ParamsForm->PISOQmX1->Text).ToDouble();          //Pogreschnost
    else
      P.Pogr = ReplPunknaZP(ParamsForm->PISOQmX1->Text).ToDouble();          //Pogreschnost
    DM->ISODopList.push_back(P); //1
    strcpy(P.Klass, ParamsForm->KlISOQmG1->Text.c_str());
    strcpy(P.QTipe, ParamsForm->QISOQmG1->Text.c_str());
    strcpy(P.Voda,  ParamsForm->VISOQmG1->Text.c_str());
    if(DecimalSeparator == '.')
      P.Pogr = ReplZPnaPunk(ParamsForm->PISOQmG1->Text).ToDouble();          //Pogreschnost
    else
      P.Pogr = ReplPunknaZP(ParamsForm->PISOQmG1->Text).ToDouble();          //Pogreschnost
    DM->ISODopList.push_back(P); //2
    strcpy(P.Klass, ParamsForm->KlISOQtX1->Text.c_str());
    strcpy(P.QTipe, ParamsForm->QISOQtX1->Text.c_str());
    strcpy(P.Voda,  ParamsForm->VISOQtX1->Text.c_str());
    if(DecimalSeparator == '.')
      P.Pogr = ReplZPnaPunk(ParamsForm->PISOQtX1->Text).ToDouble();          //Pogreschnost
    else
      P.Pogr = ReplPunknaZP(ParamsForm->PISOQtX1->Text).ToDouble();          //Pogreschnost
    DM->ISODopList.push_back(P); //3
    strcpy(P.Klass, ParamsForm->KlISOQtG1->Text.c_str());
    strcpy(P.QTipe, ParamsForm->QISOQtG1->Text.c_str());
    strcpy(P.Voda,  ParamsForm->VISOQtG1->Text.c_str());
    if(DecimalSeparator == '.')
      P.Pogr = ReplZPnaPunk(ParamsForm->PISOQtG1->Text).ToDouble();          //Pogreschnost
    else
      P.Pogr = ReplPunknaZP(ParamsForm->PISOQtG1->Text).ToDouble();          //Pogreschnost
    DM->ISODopList.push_back(P); //4
    strcpy(P.Klass, ParamsForm->KlISOQnX1->Text.c_str());
    strcpy(P.QTipe, ParamsForm->QISOQnX1->Text.c_str());
    strcpy(P.Voda,  ParamsForm->VISOQnX1->Text.c_str());
    if(DecimalSeparator == '.')
      P.Pogr = ReplZPnaPunk(ParamsForm->PISOQnX1->Text).ToDouble();          //Pogreschnost
    else
      P.Pogr = ReplPunknaZP(ParamsForm->PISOQnX1->Text).ToDouble();          //Pogreschnost
    DM->ISODopList.push_back(P); //5
    strcpy(P.Klass, ParamsForm->KlISOQnG1->Text.c_str());
    strcpy(P.QTipe, ParamsForm->QISOQnG1->Text.c_str());
    strcpy(P.Voda,  ParamsForm->VISOQnG1->Text.c_str());
    if(DecimalSeparator == '.')
      P.Pogr = ReplZPnaPunk(ParamsForm->PISOQnG1->Text).ToDouble();          //Pogreschnost
    else
      P.Pogr = ReplPunknaZP(ParamsForm->PISOQnG1->Text).ToDouble();          //Pogreschnost
    DM->ISODopList.push_back(P); //6
    strcpy(P.Klass, ParamsForm->KlISOQmX2->Text.c_str());
    strcpy(P.QTipe, ParamsForm->QISOQmX2->Text.c_str());
    strcpy(P.Voda,  ParamsForm->VISOQmX2->Text.c_str());
    if(DecimalSeparator == '.')
      P.Pogr = ReplZPnaPunk(ParamsForm->PISOQmX2->Text).ToDouble();          //Pogreschnost
    else
      P.Pogr = ReplPunknaZP(ParamsForm->PISOQmX2->Text).ToDouble();          //Pogreschnost
    DM->ISODopList.push_back(P); //7
    strcpy(P.Klass, ParamsForm->KlISOQmG2->Text.c_str());
    strcpy(P.QTipe, ParamsForm->QISOQmG2->Text.c_str());
    strcpy(P.Voda,  ParamsForm->VISOQmG2->Text.c_str());
    P.Pogr = ParamsForm->PISOQmG2->Text.ToInt();
    if(DecimalSeparator == '.')
      P.Pogr = ReplZPnaPunk(ParamsForm->PISOQmG2->Text).ToDouble();          //Pogreschnost
    else
      P.Pogr = ReplPunknaZP(ParamsForm->PISOQmG2->Text).ToDouble();          //Pogreschnost
    DM->ISODopList.push_back(P); //8
    strcpy(P.Klass, ParamsForm->KlISOQtX2->Text.c_str());
    strcpy(P.QTipe, ParamsForm->QISOQtX2->Text.c_str());
    strcpy(P.Voda,  ParamsForm->VISOQtX2->Text.c_str());
    if(DecimalSeparator == '.')
      P.Pogr = ReplZPnaPunk(ParamsForm->PISOQtX2->Text).ToDouble();          //Pogreschnost
    else
      P.Pogr = ReplPunknaZP(ParamsForm->PISOQtX2->Text).ToDouble();          //Pogreschnost
    DM->ISODopList.push_back(P); //9
    strcpy(P.Klass, ParamsForm->KlISOQtG2->Text.c_str());
    strcpy(P.QTipe, ParamsForm->QISOQtG2->Text.c_str());
    strcpy(P.Voda,  ParamsForm->VISOQtG2->Text.c_str());
    if(DecimalSeparator == '.')
      P.Pogr = ReplZPnaPunk(ParamsForm->PISOQtG2->Text).ToDouble();          //Pogreschnost
    else
      P.Pogr = ReplPunknaZP(ParamsForm->PISOQtG2->Text).ToDouble();          //Pogreschnost
    DM->ISODopList.push_back(P); //10
    strcpy(P.Klass, ParamsForm->KlISOQnX2->Text.c_str());
    strcpy(P.QTipe, ParamsForm->QISOQnX2->Text.c_str());
    strcpy(P.Voda,  ParamsForm->VISOQnX2->Text.c_str());
    if(DecimalSeparator == '.')
      P.Pogr = ReplZPnaPunk(ParamsForm->PISOQnX2->Text).ToDouble();          //Pogreschnost
    else
      P.Pogr = ReplPunknaZP(ParamsForm->PISOQnX2->Text).ToDouble();          //Pogreschnost
    DM->ISODopList.push_back(P); //11
    strcpy(P.Klass, ParamsForm->KlISOQnG2->Text.c_str());
    strcpy(P.QTipe, ParamsForm->QISOQnG2->Text.c_str());
    strcpy(P.Voda,  ParamsForm->VISOQnG2->Text.c_str());
    if(DecimalSeparator == '.')
      P.Pogr = ReplZPnaPunk(ParamsForm->PISOQnG2->Text).ToDouble();          //Pogreschnost
    else
      P.Pogr = ReplPunknaZP(ParamsForm->PISOQnG2->Text).ToDouble();          //Pogreschnost
    DM->ISODopList.push_back(P); //12
    //LCNE OIML R 49-1
    DM->LNCEDopList.clear();
    strcpy(P.Klass, ParamsForm->KlOIMLQmX1->Text.c_str()); //Klass
    strcpy(P.QTipe, ParamsForm->QOIMLQmX1->Text.c_str());  //Vid Q
    strcpy(P.Voda,  ParamsForm->VOIMLQmX1->Text.c_str());  //Tip Vody
    if(DecimalSeparator == '.')
      P.Pogr = ReplZPnaPunk(ParamsForm->POIMLQmX1->Text).ToDouble();          //Pogreschnost
    else
      P.Pogr = ReplPunknaZP(ParamsForm->POIMLQmX1->Text).ToDouble();          //Pogreschnost
    DM->LNCEDopList.push_back(P); //1
    strcpy(P.Klass, ParamsForm->KlOIMLQmG1->Text.c_str());
    strcpy(P.QTipe, ParamsForm->QOIMLQmG1->Text.c_str());
    strcpy(P.Voda,  ParamsForm->VOIMLQmG1->Text.c_str());
    if(DecimalSeparator == '.')
      P.Pogr = ReplZPnaPunk(ParamsForm->POIMLQmG1->Text).ToDouble();          //Pogreschnost
    else
      P.Pogr = ReplPunknaZP(ParamsForm->POIMLQmG1->Text).ToDouble();          //Pogreschnost
    DM->LNCEDopList.push_back(P); //2
    strcpy(P.Klass, ParamsForm->KlOIMLQtX1->Text.c_str());
    strcpy(P.QTipe, ParamsForm->QOIMLQtX1->Text.c_str());
    strcpy(P.Voda,  ParamsForm->VOIMLQtX1->Text.c_str());
    if(DecimalSeparator == '.')
      P.Pogr = ReplZPnaPunk(ParamsForm->POIMLQtX1->Text).ToDouble();          //Pogreschnost
    else
      P.Pogr = ReplPunknaZP(ParamsForm->POIMLQtX1->Text).ToDouble();          //Pogreschnost
    DM->LNCEDopList.push_back(P); //3
    strcpy(P.Klass, ParamsForm->KlOIMLQtG1->Text.c_str());
    strcpy(P.QTipe, ParamsForm->QOIMLQtG1->Text.c_str());
    strcpy(P.Voda,  ParamsForm->VOIMLQtG1->Text.c_str());
    if(DecimalSeparator == '.')
      P.Pogr = ReplZPnaPunk(ParamsForm->POIMLQtG1->Text).ToDouble();          //Pogreschnost
    else
      P.Pogr = ReplPunknaZP(ParamsForm->POIMLQtG1->Text).ToDouble();          //Pogreschnost
    DM->LNCEDopList.push_back(P); //4
    strcpy(P.Klass, ParamsForm->KlOIMLQnX1->Text.c_str());
    strcpy(P.QTipe, ParamsForm->QOIMLQnX1->Text.c_str());
    strcpy(P.Voda,  ParamsForm->VOIMLQnX1->Text.c_str());
    if(DecimalSeparator == '.')
      P.Pogr = ReplZPnaPunk(ParamsForm->POIMLQnX1->Text).ToDouble();          //Pogreschnost
    else
      P.Pogr = ReplPunknaZP(ParamsForm->POIMLQnX1->Text).ToDouble();          //Pogreschnost
    DM->LNCEDopList.push_back(P); //5
    strcpy(P.Klass, ParamsForm->KlOIMLQnG1->Text.c_str());
    strcpy(P.QTipe, ParamsForm->QOIMLQnG1->Text.c_str());
    strcpy(P.Voda,  ParamsForm->VOIMLQnG1->Text.c_str());
    if(DecimalSeparator == '.')
      P.Pogr = ReplZPnaPunk(ParamsForm->POIMLQnG1->Text).ToDouble();          //Pogreschnost
    else
      P.Pogr = ReplPunknaZP(ParamsForm->POIMLQnG1->Text).ToDouble();          //Pogreschnost
    DM->LNCEDopList.push_back(P); //6
    strcpy(P.Klass, ParamsForm->KlOIMLQmX2->Text.c_str());  //7
    strcpy(P.QTipe, ParamsForm->QOIMLQmX2->Text.c_str());
    strcpy(P.Voda,  ParamsForm->VOIMLQmX2->Text.c_str());
    if(DecimalSeparator == '.')
      P.Pogr = ReplZPnaPunk(ParamsForm->POIMLQmX2->Text).ToDouble();          //Pogreschnost
    else
      P.Pogr = ReplPunknaZP(ParamsForm->POIMLQmX2->Text).ToDouble();          //Pogreschnost
    DM->LNCEDopList.push_back(P); //7
    strcpy(P.Klass, ParamsForm->KlOIMLQmG2->Text.c_str());  //8
    strcpy(P.QTipe, ParamsForm->VOIMLQmG2->Text.c_str());
    strcpy(P.Voda,  ParamsForm->VOIMLQmG2->Text.c_str());
    if(DecimalSeparator == '.')
      P.Pogr = ReplZPnaPunk(ParamsForm->POIMLQmG2->Text).ToDouble();          //Pogreschnost
    else
      P.Pogr = ReplPunknaZP(ParamsForm->POIMLQmG2->Text).ToDouble();          //Pogreschnost
    DM->LNCEDopList.push_back(P); //8
    strcpy(P.Klass, ParamsForm->KlOIMLQtX2->Text.c_str());  //9
    strcpy(P.QTipe, ParamsForm->QOIMLQtX2->Text.c_str());
    strcpy(P.Voda,  ParamsForm->VOIMLQtX2->Text.c_str());
    if(DecimalSeparator == '.')
      P.Pogr = ReplZPnaPunk(ParamsForm->POIMLQtX2->Text).ToDouble();          //Pogreschnost
    else
      P.Pogr = ReplPunknaZP(ParamsForm->POIMLQtX2->Text).ToDouble();          //Pogreschnost
    DM->LNCEDopList.push_back(P); //9
    strcpy(P.Klass, ParamsForm->KlOIMLQtG2->Text.c_str());   //10
    strcpy(P.QTipe, ParamsForm->QOIMLQtG2->Text.c_str());
    strcpy(P.Voda,  ParamsForm->VOIMLQtG2->Text.c_str());
    if(DecimalSeparator == '.')
      P.Pogr = ReplZPnaPunk(ParamsForm->POIMLQtG2->Text).ToDouble();          //Pogreschnost
    else
      P.Pogr = ReplPunknaZP(ParamsForm->POIMLQtG2->Text).ToDouble();          //Pogreschnost
    DM->LNCEDopList.push_back(P); //10
    strcpy(P.Klass, ParamsForm->KlOIMLQnX2->Text.c_str());   //11
    strcpy(P.QTipe, ParamsForm->QOIMLQnX2->Text.c_str());
    strcpy(P.Voda,  ParamsForm->VOIMLQnX2->Text.c_str());
    if(DecimalSeparator == '.')
      P.Pogr = ReplZPnaPunk(ParamsForm->POIMLQnX2->Text).ToDouble();          //Pogreschnost
    else
      P.Pogr = ReplPunknaZP(ParamsForm->POIMLQnX2->Text).ToDouble();          //Pogreschnost
    DM->LNCEDopList.push_back(P); //11
    strcpy(P.Klass, ParamsForm->KlOIMLQnG2->Text.c_str());   //12
    strcpy(P.QTipe, ParamsForm->QOIMLQnG2->Text.c_str());
    strcpy(P.Voda,  ParamsForm->VOIMLQnG2->Text.c_str());
    if(DecimalSeparator == '.')
      P.Pogr = ReplZPnaPunk(ParamsForm->POIMLQnG2->Text).ToDouble();          //Pogreschnost
    else
      P.Pogr = ReplPunknaZP(ParamsForm->POIMLQnG2->Text).ToDouble();          //Pogreschnost
    DM->LNCEDopList.push_back(P); //12
    //���� 3580
    DM->OLDDopList.clear();
    strcpy(P.Klass, ParamsForm->KlOLDQmXA->Text.c_str()); //Klass
    strcpy(P.QTipe, ParamsForm->QOLDQmXA->Text.c_str());  //Vid Q
    strcpy(P.Voda,  ParamsForm->VOLDQmXA->Text.c_str());  //Tip Vody
    if(DecimalSeparator == '.')
      P.Pogr = ReplZPnaPunk(ParamsForm->POLDQmXA->Text).ToDouble();          //Pogreschnost
    else
      P.Pogr = ReplPunknaZP(ParamsForm->POLDQmXA->Text).ToDouble();          //Pogreschnost
    DM->OLDDopList.push_back(P); //1
    strcpy(P.Klass, ParamsForm->KlOLDQmGA->Text.c_str());
    strcpy(P.QTipe, ParamsForm->QOLDQmGA->Text.c_str());
    strcpy(P.Voda,  ParamsForm->VOLDQmGA->Text.c_str());
    if(DecimalSeparator == '.')
      P.Pogr = ReplZPnaPunk(ParamsForm->POLDQmGA->Text).ToDouble();          //Pogreschnost
    else
      P.Pogr = ReplPunknaZP(ParamsForm->POLDQmGA->Text).ToDouble();          //Pogreschnost
    DM->OLDDopList.push_back(P); //2
    strcpy(P.Klass, ParamsForm->KlOLDQtXA->Text.c_str());
    strcpy(P.QTipe, ParamsForm->QOLDQtXA->Text.c_str());
    strcpy(P.Voda,  ParamsForm->VOLDQtXA->Text.c_str());
    if(DecimalSeparator == '.')
      P.Pogr = ReplZPnaPunk(ParamsForm->POLDQtXA->Text).ToDouble();          //Pogreschnost
    else
      P.Pogr = ReplPunknaZP(ParamsForm->POLDQtXA->Text).ToDouble();          //Pogreschnost
    DM->OLDDopList.push_back(P); //3
    strcpy(P.Klass, ParamsForm->KlOLDQtGA->Text.c_str());
    strcpy(P.QTipe, ParamsForm->QOLDQtGA->Text.c_str());
    strcpy(P.Voda,  ParamsForm->VOLDQtGA->Text.c_str());
    if(DecimalSeparator == '.')
      P.Pogr = ReplZPnaPunk(ParamsForm->POLDQtGA->Text).ToDouble();          //Pogreschnost
    else
      P.Pogr = ReplPunknaZP(ParamsForm->POLDQtGA->Text).ToDouble();          //Pogreschnost
    DM->OLDDopList.push_back(P); //4
    strcpy(P.Klass, ParamsForm->KlOLDQnXA->Text.c_str());
    strcpy(P.QTipe, ParamsForm->QOLDQnXA->Text.c_str());
    strcpy(P.Voda,  ParamsForm->VOLDQnXA->Text.c_str());
    if(DecimalSeparator == '.')
      P.Pogr = ReplZPnaPunk(ParamsForm->POLDQnXA->Text).ToDouble();          //Pogreschnost
    else
      P.Pogr = ReplPunknaZP(ParamsForm->POLDQnXA->Text).ToDouble();          //Pogreschnost
    DM->OLDDopList.push_back(P); //5
    strcpy(P.Klass, ParamsForm->KlOLDQnGA->Text.c_str());
    strcpy(P.QTipe, ParamsForm->QOLDQnGA->Text.c_str());
    strcpy(P.Voda,  ParamsForm->VOLDQnGA->Text.c_str());
    if(DecimalSeparator == '.')
      P.Pogr = ReplZPnaPunk(ParamsForm->POLDQnGA->Text).ToDouble();          //Pogreschnost
    else
      P.Pogr = ReplPunknaZP(ParamsForm->POLDQnGA->Text).ToDouble();          //Pogreschnost
    DM->OLDDopList.push_back(P); //6
    strcpy(P.Klass, ParamsForm->KlOLDQmXB->Text.c_str());  //7
    strcpy(P.QTipe, ParamsForm->QOLDQmXB->Text.c_str());
    strcpy(P.Voda,  ParamsForm->VOLDQmXB->Text.c_str());
    if(DecimalSeparator == '.')
      P.Pogr = ReplZPnaPunk(ParamsForm->POLDQmXB->Text).ToDouble();          //Pogreschnost
    else
      P.Pogr = ReplPunknaZP(ParamsForm->POLDQmXB->Text).ToDouble();          //Pogreschnost
    DM->OLDDopList.push_back(P); //7
    strcpy(P.Klass, ParamsForm->KlOLDQmGB->Text.c_str());  //8
    strcpy(P.QTipe, ParamsForm->VOLDQmGB->Text.c_str());
    strcpy(P.Voda,  ParamsForm->VOLDQmGB->Text.c_str());
    if(DecimalSeparator == '.')
      P.Pogr = ReplZPnaPunk(ParamsForm->POLDQmGB->Text).ToDouble();          //Pogreschnost
    else
      P.Pogr = ReplPunknaZP(ParamsForm->POLDQmGB->Text).ToDouble();          //Pogreschnost
    DM->OLDDopList.push_back(P); //8
    strcpy(P.Klass, ParamsForm->KlOLDQtXB->Text.c_str());  //9
    strcpy(P.QTipe, ParamsForm->QOLDQtXB->Text.c_str());
    strcpy(P.Voda,  ParamsForm->VOLDQtXB->Text.c_str());
    if(DecimalSeparator == '.')
      P.Pogr = ReplZPnaPunk(ParamsForm->POLDQtXB->Text).ToDouble();          //Pogreschnost
    else
      P.Pogr = ReplPunknaZP(ParamsForm->POLDQtXB->Text).ToDouble();          //Pogreschnost
    DM->OLDDopList.push_back(P); //9
    strcpy(P.Klass, ParamsForm->KlOLDQtGB->Text.c_str());   //10
    strcpy(P.QTipe, ParamsForm->QOLDQtGB->Text.c_str());
    strcpy(P.Voda,  ParamsForm->VOLDQtGB->Text.c_str());
    if(DecimalSeparator == '.')
      P.Pogr = ReplZPnaPunk(ParamsForm->POLDQtGB->Text).ToDouble();          //Pogreschnost
    else
      P.Pogr = ReplPunknaZP(ParamsForm->POLDQtGB->Text).ToDouble();          //Pogreschnost
    DM->OLDDopList.push_back(P); //10
    strcpy(P.Klass, ParamsForm->KlOLDQnXB->Text.c_str());   //11
    strcpy(P.QTipe, ParamsForm->QOLDQnXB->Text.c_str());
    strcpy(P.Voda,  ParamsForm->VOLDQnXB->Text.c_str());
    if(DecimalSeparator == '.')
      P.Pogr = ReplZPnaPunk(ParamsForm->POLDQnXB->Text).ToDouble();          //Pogreschnost
    else
      P.Pogr = ReplPunknaZP(ParamsForm->POLDQnXB->Text).ToDouble();          //Pogreschnost
    DM->OLDDopList.push_back(P); //11
    strcpy(P.Klass, ParamsForm->KlOLDQnGB->Text.c_str());   //12
    strcpy(P.QTipe, ParamsForm->QOLDQnGB->Text.c_str());
    strcpy(P.Voda,  ParamsForm->VOLDQnGB->Text.c_str());
    if(DecimalSeparator == '.')
      P.Pogr = ReplZPnaPunk(ParamsForm->POLDQnGB->Text).ToDouble();          //Pogreschnost
    else
      P.Pogr = ReplPunknaZP(ParamsForm->POLDQnGB->Text).ToDouble();          //Pogreschnost
    DM->OLDDopList.push_back(P); //12
  }
  catch(...)
  {
    ShowMessage("� ������ ������������ ������� �� ������n�� ��������");
    delete ParamsForm;
    return;
  }
  try
  {
    if(DecimalSeparator == '.')
    {
      DM->QminLGr = ReplZPnaPunk(ParamsForm->QminLGr->Text).ToDouble();
      DM->QminRGr = ReplZPnaPunk(ParamsForm->QminRGr->Text).ToDouble();
      DM->QtLGr = ReplZPnaPunk(ParamsForm->QtLGr->Text).ToDouble();
      DM->QtRGr = ReplZPnaPunk(ParamsForm->QtRGr->Text).ToDouble();
      DM->QnLGr = ReplZPnaPunk(ParamsForm->QnLGr->Text).ToDouble();
      DM->QnRGr = ReplZPnaPunk(ParamsForm->QnRGr->Text).ToDouble();
      DM->TXolL = ReplZPnaPunk(ParamsForm->TXolL->Text).ToDouble();
      DM->TXolR = ReplZPnaPunk(ParamsForm->TXolR->Text).ToDouble();
      DM->TGorL = ReplZPnaPunk(ParamsForm->TGorL->Text).ToDouble();
      DM->TGorR = ReplZPnaPunk(ParamsForm->TGorR->Text).ToDouble();
      DM->VKonst = ReplZPnaPunk(ParamsForm->VKonst->Text).ToDouble();
      DM->TimeConst = ReplZPnaPunk(ParamsForm->TimeConst->Text).ToDouble();
    }
    else
    {
      DM->QminLGr = ReplPunknaZP(ParamsForm->QminLGr->Text).ToDouble();
      DM->QminRGr = ReplPunknaZP(ParamsForm->QminRGr->Text).ToDouble();
      DM->QtLGr   = ReplPunknaZP(ParamsForm->QtLGr->Text).ToDouble();
      DM->QtRGr   = ReplPunknaZP(ParamsForm->QtRGr->Text).ToDouble();
      DM->QnLGr   = ReplPunknaZP(ParamsForm->QnLGr->Text).ToDouble();
      DM->QnRGr   = ReplPunknaZP(ParamsForm->QnRGr->Text).ToDouble();
      DM->TXolL   = ReplPunknaZP(ParamsForm->TXolL->Text).ToDouble();
      DM->TXolR   = ReplPunknaZP(ParamsForm->TXolR->Text).ToDouble();
      DM->TGorL   = ReplPunknaZP(ParamsForm->TGorL->Text).ToDouble();
      DM->TGorR   = ReplPunknaZP(ParamsForm->TGorR->Text).ToDouble();
      DM->VKonst   = ReplPunknaZP(ParamsForm->VKonst->Text).ToDouble();
      DM->TimeConst   = ReplPunknaZP(ParamsForm->TimeConst->Text).ToDouble();
    }
  }
  catch(...)
  {
    ShowMessage("� ������ ������ ������� �� ������n�� ��������");
    delete ParamsForm;
    return;
  }
}
//-----------------------------------------------------------------------------
//void __fastcall TMainKPSForm::SaveParamsClick(TObject *Sender)
//{
//   WriteIntoReestr();
//}
//---------------------------------------------------------------------------
void __fastcall TMainKPSForm::Timer1Timer(TObject *Sender)
{
  AnsiString S;
  TDateTime  DT;
  if(!ComPortFlag) return; // ��� ��������- ��� ������
  TimerTickCount++;
  if(TimerTickCount == 1)
  {
    Timer1->Interval = 1000;
    return;
  }
  DT = Now();
  if( SecondsBetween(DT, DTAnswer) > 10)        //  5 ������
  {
    if(FlagGetDate)   // ������ ������
    {
      FlagGetDate = false;
      FullFileName = SlashSep(Dir, "3.bmp");
      PriborImage->Picture->LoadFromFile(FullFileName);
      PriborImage->Refresh();
      PriborImageState = false;
//      Timer1->Enabled = false;      //����� ������� ����� �� "������ ������"
//      DelComPortAndReader();
    }
  }
  if(FlagStartAvtomat)
  {
    FlagStartAvtomat = false;
    StartProlivBtnClick(this);
  }
}
//---------------------------------------------------------------------------
void TMainKPSForm::DelComPortAndReader(void)
{
  try
  {
//    RestartFlag = true;
    ComPortFlag = false;
    if(ProgramState == 2)
    {
      ProgramState = 0;
      FlagBegProliva = false;
      Application->ProcessMessages();
      Sleep(1000);
      Application->ProcessMessages();
      Label45->Caption = ProgramState;
      KommandIntoIS(0x43);
      EnabledQSelection();
    }
////    ReadCadrsFlag = false;
  }
  catch(...)
  {
     StatusBar1->Panels->Items[1]->Text = " ��������� ���������� ��������� DelComPortAndReader �� ������ �� ������� ��������!";
  }
  try
  {
    FullFileName = SlashSep(Dir, "Foto.jpg");
    Image1->Picture->LoadFromFile(FullFileName);
    Application->ProcessMessages();
    //������� ������ ������
    if(reader)
    {
      reader->Terminate(); //???? ????? ?????? ????????, ????????? ???; ????????
      CloseHandle(ComPort); //������� ����
//      reader = NULL;
      ComPort = 0; //???????? ?????????? ??? ??????????? ?????
      reader = 0;
    }
  }
  catch(...)
  {
     StatusBar1->Panels->Items[1]->Text = " ��������� ���������� ��������� DelComPortAndReader �� ������ �� ������� �������� ��������!";
  }
  FullFileName = SlashSep(Dir, "3.bmp");
  ComPortImage->Picture->LoadFromFile(FullFileName);
  ComPortImage->Repaint();
  FullFileName = SlashSep(Dir, "3.bmp");
  PriborImage->Picture->LoadFromFile(FullFileName);
  PriborImageState = false;
  PriborImage->Repaint();
  //���������� �����
  SvjazSetting->Enabled = true;
  SvjazSetting->Color = clLime;
  //���������� ������
  RBEnabling();
  Timer1->Enabled = false;
  ClearPanel->Enabled = false;
  ClearPanel->Color = clInactiveCaption;
  StatusBar1->Panels->Items[1]->Text = "��������� ������� ������� ������ '���������� �����'!";
  ShowHideLabels(false);
  Label57->Caption = "0";
  Label35->Caption = "0";
  StartProlivBtn->Enabled = false;
  StartProlivBtn->Color = clInactiveCaption;
  ProgressBar1->Visible = false;
}
//---------------------------------------------------------------------------
void TMainKPSForm::ShowCalculation(void)   //��� ������ 3 (�� ����� � ����)
{
  AnsiString S;

  ProgramState = 1;
  Label45->Caption = ProgramState;
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  csSendToPort->Enter();                  //������ ����������
  StartProlivBtn->Enabled = true;
  StartProlivBtn->Color = clLime;
  ClearPanel->Enabled = false;
  ClearPanel->Color = clInactiveCaption;
//  StopTime = Now();
  int i = DM->RecData.Uval.RD.TimeInt;              //Interval v mcek
  double q = Round0(SummOF_Q_Proliva / CountRecivedAnswer, 5);
  Label48->Caption = S.sprintf("%4.3f", Round0(q,3));
  double v = Round0(353.67766 * q /(DM->Diametr * DM->Diametr),3);
  Label50->Caption = S.sprintf("%3.2f", v);
  Label52->Caption = S.sprintf("%4.3f",(float)i/1000);
  for( int i = 0; i < (int)DM->GrencList.size(); i++)
  {
    if((QSA >= DM->GrencList[i].LGr)&&(QSA <= DM->GrencList[i].RGr))
    {
      Label39->Caption  = (int)(Label39->Caption.ToInt() * DM->GrencList[i].Const);
      break;
    }
  }

  csSendToPort->Leave();
  KommandIntoIS(0x43);      //���������� � ������ ������� ���������� �������
  GroupBox3->Enabled = true;
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
}
//      Label39->Caption = (AnsiString)(BegTicCount - DM->RecData.Uval.RD.Count);   //tiki
//      Label52->Caption = (AnsiString)(DM->RecData.Uval.RD.TimeInt);               //msek
//---------------------------------------------------------------------------
void TMainKPSForm::Stop_Start(void)
{
  if(FlagTickControl)
  {
    StatusBar1->Panels->Items[1]->Text = "���� ��������!";
    ShowCalculation();
    return;
  }
}
//---------------------------------------------------------------------------
void __fastcall TMainKPSForm::ClearPanelClick(TObject *Sender)
{
  AnsiString S;
  if(FlagTickControl)
  {
    StatusBar1->Panels->Items[1]->Text = "���� ��������!";
    ShowCalculation();
    return;
  }
  if(FlagCiklaAvtomata)
  {
    RBEnabling();
    EnabledQSelection();
    FlagCiklaAvtomata = false;
    return;
  }
  FlagProliva = false;
  EnabledQSelection();
  DelComPortAndReader();
}
//---------------------------------------------------------------------------
void __fastcall TMainKPSForm::NastrojkaClick(TObject *Sender)
{
  AnsiString S;
  SelectParamsForm = new TSelectParamsForm(this, DM, ComportName);
  if(SelectParamsForm->ShowModal() == ID_OK)
  {
    ComportName = SelectParamsForm->MumComp;
    pProfile->StoreParameter("Common", "Comport", ComportName);
    Label60->Caption = S.sprintf("%7.3f", DM->Qmin);    //Kub Metrs
    Label68->Caption = S.sprintf("%7.3f", DM->Qt);      //Kub Metrs
    Label72->Caption = S.sprintf("%7.3f", DM->Qn);      //Kub Metrs
    Label17->Caption = S.sprintf("%5.5f", DM->Vmin/1000);      //Kub Metrs;
    Label26->Caption = S.sprintf("%5.5f", DM->Vt/1000);      //Kub Metrs;
    Label27->Caption = S.sprintf("%5.5f", DM->Vn/1000);      //Kub Metrs;
    BODA = SelectParamsForm->Voda;
    SetPanelsColors();
    if(!FlagVvodaParamsProliv)
    {
      SvjazSetting->Enabled = true;
      SvjazSetting->Color = clLime;
    }  
    FlagVvodaParamsProliv = true;
    QnomRb->Checked = false;
    QnomRb->Checked = true;
    StatusBar1->Panels->Items[1]->Text = "��������� ������� ������� ������ '���������� �����'!";
  }
  delete SelectParamsForm;
}
//---------------------------------------------------------------------------
void  TMainKPSForm::SetPanelsColors(void)
{
  AnsiString S;      
  double Delta, Min, Max;

  if(QminRb->Checked)
  {
    Label11->Caption = S.sprintf("%6.3f", DM->QminL);
    Label21->Caption = S.sprintf("%6.3f", DM->QminR);
    Delta = DM->QminR - DM->QminL;
    Min = DM->QminL - Delta;
    Max = DM->QminR + Delta;
  }
  if(QtRb->Checked)
  {
    Label11->Caption = S.sprintf("%6.3f", DM->QtL);
    Label21->Caption = S.sprintf("%6.3f", DM->QtR);
    Delta = DM->QtR - DM->QtL;
    Min = DM->QtL - Delta;
    Max = DM->QtR + Delta;
  }
  if(QnomRb->Checked)
  {
    Label11->Caption = S.sprintf("%6.3f", DM->QnomL);
    Label21->Caption = S.sprintf("%6.3f", DM->QnomR);
    Delta = DM->QnomR - DM->QnomL;
    Min = (DM->QnomL - Delta);///1000;
    Max = (DM->QnomR + Delta);///1000;
  }
  AbDB270Meter1->SignalSettings->ValueFrom = Min * 1000;
  AbDB270Meter1->SignalSettings->ValueTo = Max * 1000;
}
//---------------------------------------------------------------------------
void __fastcall TMainKPSForm::ParametersClick(TObject *Sender)
{
  ParamsForm = new TParamsForm(this, DM, rParams);
  ReadFromReestrToChange();
  ParamsForm->SetCopiDate();
  if(ParamsForm->ShowModal() == ID_OK)
  {
    if(ParamsForm->FlChange)
    {
       WriteIntoReestrEdited();
    }
  }
  delete ParamsForm;
}
//---------------------------------------------------------------------------

void __fastcall TMainKPSForm::AbonentClick(TObject *Sender)
{
  SubscrForm = new TSubscrForm(this, DM);
  if(DM->SbR.SurName != "")
    SubscrForm->SurNameEdit->Text = DM->SbR.SurName;
  if(DM->SbR.Name != "")
   SubscrForm->NameEdit->Text = DM->SbR.Name;
  if(DM->SbR.FName != "")
    SubscrForm->FNameEdit->Text = DM->SbR.FName;
  if(DM->SbR.City != "")
    SubscrForm->TaunEdit->Text = DM->SbR.City;
  if(DM->SbR.Street != "")
    SubscrForm->StreetEdit->Text = DM->SbR.Street;
  if(DM->SbR.Haus != "")
    SubscrForm->HausEdit->Text = DM->SbR.Haus;
  if(DM->SbR.Korpus != "")
    SubscrForm->KorpEdit->Text = DM->SbR.Korpus;
  if(DM->SbR.Bit != "")
    SubscrForm->BitEdit->Text = DM->SbR.Bit;
  if(SubscrForm->ShowModal() == ID_OK)
  {
    strcpy(DM->SbR.SurName, SubscrForm->SurNameEdit->Text.c_str());
    strcpy(DM->SbR.Name,    SubscrForm->NameEdit->Text.c_str());
    strcpy(DM->SbR.FName,   SubscrForm->FNameEdit->Text.c_str());
    strcpy(DM->SbR.City,    SubscrForm->TaunEdit->Text.c_str());
    strcpy(DM->SbR.Street,  SubscrForm->StreetEdit->Text.c_str());
    strcpy(DM->SbR.Haus,    SubscrForm->HausEdit->Text.c_str());
    strcpy(DM->SbR.Korpus,  SubscrForm->KorpEdit->Text.c_str());
    strcpy(DM->SbR.Bit,     SubscrForm->BitEdit->Text.c_str());
    strcpy(DM->SbR.Tipe,    SubscrForm->CountTipe->Text.c_str());
    strcpy(DM->SbR.NSch,    SubscrForm->CountN->Text.c_str());
    DM->SbR.Day =  SubscrForm->Edit5->Text.ToInt();
    DM->SbR.Month =  SubscrForm->Edit1->Text.ToInt();
    DM->SbR.Year =  SubscrForm->Edit2->Text.ToInt();
    DM->SbR.Dolgota = SubscrForm->Edit3->Text.ToDouble();
    DM->SbR.Shirota = SubscrForm->Edit4->Text.ToDouble();
    FlagVvodaSubscr = true;
  }
  delete SubscrForm;
}
//---------------------------------------------------------------------------

void __fastcall TMainKPSForm::FormClose(TObject *Sender,
      TCloseAction &Action)
{
  RdCOMClose();
  delete DM;
//  Action = caFree;
}
//---------------------------------------------------------------------------
void __fastcall TMainKPSForm::OtchetPanelClick(TObject *Sender)
{
  AnsiString S;
  if(!(EndCalcMin && EndCalcT && EndCalcN))
  {
    ShowMessage("��� ���������� ���������!");
    return;
  }
/* ����� � ������ �����
  ContrDT = Now();
  TDateTime DT1 = DateTimePicker1->Date + NULL;
    //Save Results to DB
  S = "INSERT INTO Controls( NumSCH, Makedate, Controldate, SurName, Name, FName, Taun, Street, Haus, Korp, Bit, Result, OpName, Type) VALUES ";
  S += (AnsiString)"('" + Edit20->Text  + (AnsiString)"','";                      //NumSCH
  S += DT1.FormatString("dd-mm-yyyy hh:nn:ss") + (AnsiString)"','";                           //Makedate
  S += ContrDT.FormatString("dd-mm-yyyy hh:nn:ss") + (AnsiString)"','";                                //Controldate
  S += SurNameEdit->Text + (AnsiString)"','";                                                         //SurName
  S += NameEdit->Text    + (AnsiString)"','";                                                          //Name
  S += FNameEdit->Text   + (AnsiString)"','" ;                                                         //FName
  S += TaunEdit->Text    + (AnsiString)"','";                                                          //Taun
  S += StreetEdit->Text  + (AnsiString)"','" ;                                                         //Street
  S += HausEdit->Text    + (AnsiString)"','";                                                          //Korpus
  S += KorpEdit->Text    + (AnsiString)"','";                                                          //Korpus
  S += BitEdit->Text     + (AnsiString)"','";                                                          //Bit
  S += ResultEdit->Text  + (AnsiString)"','";                                                          //Result
  S += OldOpName         + (AnsiString)"','";                           //MaxLDop
  S += TypeEdit->Text    + (AnsiString)"');";                           //Type
  if(!DM->SQLWRITE(S))
  {
    S = "�� �������� �������  - Controls" + DM->ErrorString;
    ShowMessage(S);
    return;
  }
*/
  PrintForm3 = new TPrintForm3(this);
  PrintForm3->QRLabel15->Caption = FirmName;
  PrintForm3->QRLabel16->Caption = ContrDT.FormatString("dd.mm.yyyy");
  PrintForm3->QRLabel17->Caption = DM->SbR.Tipe;
  PrintForm3->QRLabel18->Caption = DM->SbR.NSch + (AnsiString)" " + DM->SbR.BornDate.FormatString("dd.mm.yyyy");
  PrintForm3->QRLabel37->Caption = S.sprintf("%6.5f",DM->Vmin);
  PrintForm3->QRLabel38->Caption = S.sprintf("%6.5f",DM->Vt);
  PrintForm3->QRLabel39->Caption = S.sprintf("%6.5f",DM->Vn);
  PrintForm3->QRLabel40->Caption = S.sprintf("%6.5f",MinBegSCH);
  PrintForm3->QRLabel41->Caption = S.sprintf("%6.5f",MidBegSCH);
  PrintForm3->QRLabel42->Caption = S.sprintf("%6.5f",MaxBegSCH);
  PrintForm3->QRLabel43->Caption = S.sprintf("%6.5f",MinEndSCH);
  PrintForm3->QRLabel44->Caption = S.sprintf("%6.5f",MidEndSCH);
  PrintForm3->QRLabel45->Caption = S.sprintf("%6.5f",MaxEndSCH);
  PrintForm3->QRLabel46->Caption = S.sprintf("%5.4f",MinDelta);
  PrintForm3->QRLabel47->Caption = S.sprintf("%5.4f",MidDelta);
  PrintForm3->QRLabel48->Caption = S.sprintf("%5.4f",MaxDelta);
  PrintForm3->QRLabel49->Caption = S.sprintf("%6.5f",MinEtalon);
  PrintForm3->QRLabel50->Caption = S.sprintf("%6.5f",MidEtalon);
  PrintForm3->QRLabel51->Caption = S.sprintf("%6.5f",MaxEtalon);
  PrintForm3->QRLabel52->Caption = S.sprintf("%3.2f",MinPerc);
  PrintForm3->QRLabel53->Caption = S.sprintf("%3.2f",MidPerc);
  PrintForm3->QRLabel54->Caption = S.sprintf("%3.2f",MaxPerc);
  FullFileName = SlashSep(Dir, "FotoMinBeg.bmp");
  PrintForm3->QRImage1->Picture->LoadFromFile(FullFileName);
  FullFileName = SlashSep(Dir, "FotoMinEnd.bmp");
  PrintForm3->QRImage4->Picture->LoadFromFile(FullFileName);
  FullFileName = SlashSep(Dir, "FotoMidBeg.bmp");
  PrintForm3->QRImage2->Picture->LoadFromFile(FullFileName);
  FullFileName = SlashSep(Dir, "FotoMidEnd.bmp");
  PrintForm3->QRImage5->Picture->LoadFromFile(FullFileName);
  FullFileName = SlashSep(Dir, "FotoMaxBeg.bmp");
  PrintForm3->QRImage3->Picture->LoadFromFile(FullFileName);
  FullFileName = SlashSep(Dir, "FotoMaxEnd.bmp");
  PrintForm3->QRImage6->Picture->LoadFromFile(FullFileName);
  PrintForm3->QuickRep1->Preview();
  PrintForm3->QuickRep1->Print();
  delete PrintForm3;
  FlagVvodaParamsProliv = false;
  FlagVvodaSubscr = false;
}
//---------------------------------------------------------------------------
void __fastcall TMainKPSForm::QminRbClick(TObject *Sender)
{
  AnsiString S;
  Double     Delta, Min, Max;
  if(QminRb->Checked)
  {
    if(Label21->Caption != "0")
    {
      Label11->Caption = S.sprintf("%6.3f", DM->QminL);
      Label21->Caption = S.sprintf("%6.3f", DM->QminR);
      Delta = DM->QminR - DM->QminL;
      Min = DM->QminL - Delta;
      Max = DM->QminR + Delta;
      AbDB270Meter1->ScaleSettings->Steps = 3;
      AbDB270Meter1->SectorSettings->Sector1Color =clRed;
      AbDB270Meter1->SectorSettings->Sector2Color =clLime;
      AbDB270Meter1->SectorSettings->Sector3Color =clRed;
      AbDB270Meter1->SignalSettings->ValueFrom = Min*1000;
      AbDB270Meter1->SignalSettings->ValueTo = Max*1000;
    }
    StatusBar1->Panels->Items[1]->Text = "";
  }
}
//---------------------------------------------------------------------------
void __fastcall TMainKPSForm::QtRbClick(TObject *Sender)
{
  AnsiString S;
  Double     Delta, Min, Max;

  if(QtRb->Checked)
  {
    if(Label21->Caption != "0")
    {
      Label11->Caption = S.sprintf("%6.3f", DM->QtL);
      Label21->Caption = S.sprintf("%6.3f", DM->QtR);
      Delta = DM->QtR - DM->QtL;
      Min = DM->QtL - Delta;
      Max = DM->QtR + Delta;
      AbDB270Meter1->ScaleSettings->Steps = 3;
      AbDB270Meter1->SectorSettings->Sector1Color =clRed;
      AbDB270Meter1->SectorSettings->Sector2Color =clLime;
      AbDB270Meter1->SectorSettings->Sector3Color =clRed;
      AbDB270Meter1->SignalSettings->ValueFrom = Min*1000;
      AbDB270Meter1->SignalSettings->ValueTo = Max*1000;
    }
    StatusBar1->Panels->Items[1]->Text = "";
  }
}
//---------------------------------------------------------------------------
void __fastcall TMainKPSForm::QnomRbClick(TObject *Sender)
{
  AnsiString S;
  Double     Delta, Min, Max;

  if(QnomRb->Checked)
  {
    if(Label21->Caption != "0")
    {
      Label11->Caption = S.sprintf("%6.3f", DM->QnomL);
      Label21->Caption = S.sprintf("%6.3f", DM->QnomR);
//      Delta = DM->QnomR - DM->QnomL;
      Min = DM->QnomL;//(DM->QnomL - 2*Delta);///1000;
      Max = (DM->QnomR);///1000;
      AbDB270Meter1->ScaleSettings->Steps = 3;
      AbDB270Meter1->SectorSettings->Sector1Color =clYellow;
      AbDB270Meter1->SectorSettings->Sector2Color =clYellow;
      AbDB270Meter1->SectorSettings->Sector3Color =clLime;
      AbDB270Meter1->SignalSettings->ValueFrom = Min*1000;
      AbDB270Meter1->SignalSettings->ValueTo = Max*1000;
    }
    StatusBar1->Panels->Items[1]->Text = "";
  }
}
//---------------------------------------------------------------------------
void __fastcall TMainKPSForm::Image1Click(TObject *Sender)
{
  if(!FlagVvodaParamsProliv)
  {
    ShowMessage("�� ������� ������ �������� � ���������!");
    return;
  }
  if(FlagProliva)
  {
    ShowMessage("�� ����� ������� ������������ ����� ���������!");
    return;
  }
  if(PhotoSB->Down)
  {
    ShowMessage("�� ����� ��������� ���� ������������ ����� ���������!");
    return;
  }
  FlagTestVideo = !FlagTestVideo;
  if(FlagTestVideo)                      //��������� ����� �����
  {
    RBDisabling();
    Beep();
    TestVideo();
  }
  else                                   //��������� ����� �����
  {
    RBEnabling();
    Beep();
  }
}
//---------------------------------------------------------------------------
void TMainKPSForm::TestVideo(void)
{
  SaveCursor = Screen->Cursor;
  Screen->Cursor = crHourGlass;
  while(FlagTestVideo)
  {
    bool b = capGrabFrame(hWndC);    // ���������� � ����� ���� � ������
    b = capFileSaveDIB(hWndC, "A.bmp"); //�������� ���� � ����
    if(b)
    {                         // ���� ��� ����������
      FullFileName = SlashSep(Dir, "A.bmp");
      Image1->Picture->LoadFromFile(FullFileName);
      Application->ProcessMessages();
    }
    Application->ProcessMessages();
  }
  Screen->Cursor  =  SaveCursor;
  FullFileName = SlashSep(Dir, "Foto.jpg");
  Image1->Picture->LoadFromFile(FullFileName);
}
//---------------------------------------------------------------------------
void TMainKPSForm::TestVideo1(void)
{
  SaveCursor = Screen->Cursor;
  Screen->Cursor = crHourGlass;

  Graphics::TBitmap *Buffer=new Graphics::TBitmap; // ���� ������ ���� �����
  while(FlagTestVideo)
  {
    Application->ProcessMessages();                                      // ����������� ������
    capGrabFrame(hWndC);                 // ���������� � ����� ���� � ������
    bool capOK=capEditCopy(hWndC);       // �������� ���� � ����� ������
    TClipboard *pCB=Clipboard();                     // ����� ������ windows
    Buffer->LoadFromClipboardFormat(CF_BITMAP,pCB->GetAsHandle(CF_BITMAP),0);// ��������� �� ������
    Image1->Canvas->Draw(0,0,Buffer);  // �� � ��������, ����������
    Application->ProcessMessages();
    pCB->Free();
  }
  FullFileName = SlashSep(Dir, "Foto.jpg");
  Image1->Picture->LoadFromFile(FullFileName);
  delete Buffer;
  capDriverDisconnect(hWndC);          // ����������� �� ������ (��������� ������)
  DestroyWindow(hWndC);                // ������� ����

}
//---------------------------------------------------------------------------
void TMainKPSForm::ConvertPhotoToCode64(AnsiString FName)
{
  AnsiString S;
  int i, j, si, C;
  int A, B;
  BYTE *BList;
  char  H;

  Image1->Picture->Bitmap->LoadFromFile(FName);
  TMemoryStream *ms = new TMemoryStream; // ??????? ?????
  Image1->Picture->Bitmap->SaveToStream(ms); // ????????? ??????????? ? ?????
  si = ms->Size;
  //  ShowMessage(IntToStr(ms->Size));
  BList = new BYTE[si];
  ms->Position = 0;
  ms->ReadBuffer(BList, si);
  ms->Clear();
  i = 0; j = 0;
  do
  {
    if(j == 0)
    {
      A = BList[i];
      H = Base64[((A >> 2) & 0x3F)];
      S += H;
      i++;
    }
    if(j == 1)
    {
      B = BList[i];
      H = Base64[(((A & 0x03) << 4) | ((B & 0xF0) >>4 ))];
      S += H;
      i++;
    }
    if(j == 2)
    {
      A = BList[i];
      H = Base64[(((A & 0xC0) >> 6) | ((B & 0x0F) << 2 ))];
      S += H;
      i++;
    }
    if(j == 3)
    {
      H = Base64[(A & 0x3F)];
      S += H;
    }
    j++;
    if(j == 4) j = 0;
  }
  while(i <= si);
  ShowMessage(S.Length());
}
//---------------------------------------------------------------------------

void __fastcall TMainKPSForm::PhotoSBClick(TObject *Sender)
{
  if(!FlagVvodaParamsProliv)
  {
    PhotoSB->Down = false;
    ShowMessage("�� ������� ������ ��������!");
    return;
  }
  if(FlagProliva)
  {
    PhotoSB->Down = false;
    ShowMessage("�� ����� ������� ��������� ���� ���������!");
    return;
  }
  if(FlagTestVideo)
  {
    PhotoSB->Down = false;
    ShowMessage("�� ����� ����� ����� ��������� ���� ���������!");
    return;
  }
  if(PhotoSB->Down)
  {
    FlagPhotoPlomb = true;
    RBDisabling();
    Beep();
    GettingPhotoWPlomb();
  }
  else
  {
    RBEnabling();
    Beep();
  }
}
//---------------------------------------------------------------------------
void  TMainKPSForm::GettingPhotoWPlomb(void)
{
  while(PhotoSB->Down)
  {
    if(FlagPhotoPlomb)
    {
      bool b = capGrabFrame(hWndC);    // ���������� � ����� ���� � ������
      b = capFileSaveDIB(hWndC, "A.bmp"); //�������� ���� � ����
      if(b)
      {                         // ���� ��� ����������
        FullFileName = SlashSep(Dir, "A.bmp");
        Image1->Picture->LoadFromFile(FullFileName);
        Application->ProcessMessages();
        FullFileName = SlashSep(Dir, "C.bmp");
        Image1->Picture->SaveToFile(FullFileName);                  // � � ���� ����������
        Application->ProcessMessages();
        FlagPhotoPlomb = false;
      }
    }
    Application->ProcessMessages();
  }
  FullFileName = SlashSep(Dir, "Foto.jpg");
  Image1->Picture->LoadFromFile(FullFileName);
}
//---------------------------------------------------------------------------
void  TMainKPSForm::ShowHideLabels(bool TF)
{
      Label36->Visible = TF;
      Label39->Visible = TF;
      Label47->Visible = TF;
      Label48->Visible = TF;
      Label49->Visible = TF;
      Label50->Visible = TF;
      Label51->Visible = TF;
      Label52->Visible = TF;
      Label39->Caption = 0;
      Label48->Caption = 0;
      Label50->Caption = 0;
      Label52->Caption = 0;
}
//---------------------------------------------------------------------------
void __fastcall TMainKPSForm::HandStartBtnClick(TObject *Sender)
{
  if(HandStartBtn->Checked)
  {
//    StartProlivBtn->Visible = true;
    AvtomatStartFlag = false;
    ShowHideLabels(false);
    StartProlivBtn->Caption = "�����";
    ClearPanel->Caption = "�����";
    FlagTickControl = false;
    StatusBar1->Panels->Items[1]->Text = "";
    if(StartStopExt > 0)
    {
      StartProlivBtn->Visible = true;
      ClearPanel->Visible = true;
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TMainKPSForm::AvtomatStartBtnClick(TObject *Sender)
{
  if(AvtomatStartBtn->Checked)
  {
//    StartProlivBtn->Visible = false;
    AvtomatStartFlag = true;
    ShowHideLabels(false);
    StartProlivBtn->Caption = "���";
    ClearPanel->Caption = "�����";
    FlagTickControl = false;
    StatusBar1->Panels->Items[1]->Text = "";
    if(StartStopExt > 0)
    {
      StartProlivBtn->Visible = true;
      ClearPanel->Visible = true;
    }
  }
}
//---------------------------------------------------------------------------

void __fastcall TMainKPSForm::TickTestBtnClick(TObject *Sender)
{
  if(TickTestBtn->Checked)
  {
//    StartProlivBtn->Visible = true;
    FlagTickControl = true;
    AvtomatStartFlag = false;
    ShowHideLabels(true);
    StartProlivBtn->Caption = "�����";
    ClearPanel->Caption = "����";
    StatusBar1->Panels->Items[1]->Text = "";
    if(StartStopExt > 0)
    {
      StartProlivBtn->Visible = false;
      ClearPanel->Visible = false;
      StatusBar1->Panels->Items[1]->Text = "�����-���� �� ����������";
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TMainKPSForm::Panel4Click(TObject *Sender)
{
  AnsiString S;
  S += "�� ������� � �������� ���������?";
  if(!AskingMessage0(S))
    return;
  if(ProgramState == 2)
    ClearPanelClick(this);
  Close();
}
//---------------------------------------------------------------------------

void __fastcall TMainKPSForm::FormDestroy(TObject *Sender)
{
//  RdCOMClose();
//  delete DM;
}
//---------------------------------------------------------------------------

void __fastcall TMainKPSForm::OperatorsPClick(TObject *Sender)
{
  if(!DM->OpRights & rAudit)
  {
    ShowMessage("� ��� ��� ���� ��� ������ � �����������!");
    return;
  }
  TStringList* KList;
  AnsiString S;
  int i;

//  if(!(DM->OpRights & rAudit)) return;
  AuditForm = new TAuditForm(this, DM);
  KList = new TStringList;
  for(i = 0; i < 5; i++)
  {
    S = AccRigth[i];
    KList->Add(S);
  }
  AuditForm->CheckListBox1->Clear();
  for(i = 0; i < 5; i++)
  {
     AuditForm->CheckListBox1->Items->Add(KList->Strings[i]);
     AuditForm->CheckListBox1->Checked[i] = false;
  }
  AuditForm->ShowModal();
  delete AuditForm;
  delete KList;

}
//---------------------------------------------------------------------------
void __fastcall TMainKPSForm::PopupMenu1Popup(TObject *Sender)
{
  unsigned short hour;
  unsigned short min;
  unsigned short sec;
  unsigned short msec;

  AnsiString S;
  StartTime.DecodeTime(&hour, &min, &sec, &msec);
  BegCommStart1->Caption = "BegCommAfterStart =" + (AnsiString)min + ":" + (AnsiString)sec+ ":" + (AnsiString)msec;
  StartVTime.DecodeTime(&hour, &min, &sec, &msec);
  BegCadrStart1->Caption = "GegCadrAfterStart =" + (AnsiString)min + ":" + (AnsiString)sec+ ":" + (AnsiString)msec;
  StopTime.DecodeTime(&hour, &min, &sec, &msec);
  EndCommStop1->Caption = "EndCommAfterStart= =" + (AnsiString)min + ":" + (AnsiString)sec+ ":" + (AnsiString)msec;
  StopVTime.DecodeTime(&hour, &min, &sec, &msec);
  EndCadrStop1->Caption = "EndCadrAfterStart= =" + (AnsiString)min + ":" + (AnsiString)sec+ ":" + (AnsiString)msec;
}
//---------------------------------------------------------------------------



