//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "Tools_proc.h"
#include "mPasswordForm.h"

#include "MainP.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//pragma link "cxGridCustomTableView"
#pragma resource "*.dfm"
TMainForm *MainForm;

//=== Глобальные данные =====================================================
LProfile   *pProfile;
AnsiString      Dir;
extern AnsiString  sOpName;
bool          SelfCloseFlag;
InfoLaunch  st_InfoLaunch;
char *AccRigth[] = {"Аудит - Доступ к аудиту ","Аудит - создание групп и опер.","Аудит - Редактирование пароля",  " "};
//char *RegKey[] = "Software\\KPS";
//---------------------------------------------------------------------------
double Round(double Value, int Precision)
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
    if((D - (double)M) > 0.5)
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
AnsiString ReplZPnaPunk(AnsiString SI)           //float всегда с точкой
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
AnsiString ReplPunknaZP(AnsiString SI)
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
__fastcall TMainForm::TMainForm(TComponent* Owner)
        : TForm(Owner)
{
  AnsiString  Dir, S;
  OpGroup     G;
  Operator    O;
  SelfCloseFlag = false;
/////////////////////////////////////////////////////////////////////////

  Reg = new TRegIniFile("Software\\KPS");
  Dir = ExtractFileDir(Application->ExeName);
  DM = new TDataModule1(this);
  WorkWSReestr();
  pProfile->LoadParameter("Common", "ServerName", "A");
  DM->ServerName = pProfile->GetValue()->AsStr(0);
  DBName = "KPC"; //
  if(DM->ServerName == "A")
  {
    S = "Не задано имя сервера в инифайле";
    ShowMessage(S);
    SelfCloseFlag = true;
    return;
  }
  pProfile->LoadParameter("Common", "Number", 0);
  NUM = pProfile->GetValue()->AsInt(0);
  pProfile->LoadParameter("Common", "Comport", "Com3");
  ComboBox1->Text = pProfile->GetValue()->AsStr(0);
/*
//      Временно отключил эту часть, чтобы не создавать новую БД
  S = SlashSep(Dir, "DB");
  if(!DirectoryExists(S))
  {
    if (!CreateDir(S))
    {
      S = "Не создана папка для баз данных";
      ShowMessage(S);
      SelfCloseFlag = true;
      return;
    }
  }
  S = Dir + "\\DB\\" + DBName + ".MDF";
  if(!FileExists(S))  //Проверяется наличие базы данных в каталоге DB станции
  {
    if(!DM->ConnectionStringSetting("master"))
    {
      S = "Ошибка подкючения к серверу БД 'master' - " + DM->ErrorString;
      ShowMessage(S);
      SelfCloseFlag = true;
      return;
    }
    S = CreateDBSQLGet(DBName); //SQL запрос на создание БД
    if(!DM->SQLWRITE(S))
    {
      S = "Не создана база данных абонентов - " + DM->ErrorString;
      ShowMessage(S);
      SelfCloseFlag = true;
      return;
    }
  }
  if(!DM->ConnectionStringSetting(DBName))     // New DataBase
  {
    S = "Ошибка подкючения к серверу БД - " + DM->ErrorString;
    ShowMessage(S);
    SelfCloseFlag = true;
    return;
  }
  if(!DM->IsTableExist("Operators"))
  {
    S = "CREATE TABLE Operators (OpInd int IDENTITY, OpName char(16),";
    S += "Password1 char(16), GroupName char(16) NULL, UndeleteF TINYINT NULL)";
    if(!DM->SQLWRITE(S))
    {
      S = "Не создана таблица операторов - " + DM->ErrorString;
      ShowMessage(S);
      SelfCloseFlag = true;
      return;
    }
    //Перед записью перезапустить таблицу после создания
    if(!DM->RestartDB())
    {
      S = "Не рестартовала база после создания таблицы - " + DM->ErrorString;
      ShowMessage(S);
      SelfCloseFlag = true;
      return;
    }
    S = "INSERT INTO OPERATORS (OpName, Password1, GroupName, UndeleteF) VALUES ('Admin', 'pass','Администраторы', 1)";
    if(!DM->SQLWRITE(S))
    {
      S = "Не заполнена таблица операторов - " + DM->ErrorString;
      ShowMessage(S);
      SelfCloseFlag = true;
      return;
    }
  }
  if(!DM->IsTableExist("Groups"))
  {
    S = "CREATE TABLE Groups (GrInd int IDENTITY, GrName char(16),";
    S += "PRights int NULL, GrFullName char(64), UndeleteF TINYINT NULL)";
    if(!DM->SQLWRITE(S))
    {
      S = "Не создана таблица групп - " + DM->ErrorString;
      ShowMessage(S);
      SelfCloseFlag = true;
      return;
    }
    //Перед записью перезапустить таблицу после создания
    if(!DM->RestartDB())
    {
      S = "Не создана таблица операторов - " + DM->ErrorString;
      ShowMessage(S);
      SelfCloseFlag = true;
      return;
    }
    S = "INSERT INTO Groups (GrName, PRights, GrFullName, UndeleteF) VALUES ('Администраторы', -1,'Системные администраторы', 1)";
    if(!DM->SQLWRITE(S))
    {
      S = "Не заполнена таблица операторов - " + DM->ErrorString;
      ShowMessage(S);
      SelfCloseFlag = true;
      return;
    }
  }
*///Конец временной проверки
/*
  if(!DM->IsTableExist("Parameters"))
  {
    S = "CREATE TABLE Parameters (INDL int IDENTITY, IND int NULL, PortNum char(24) NULL, PortSpeed int NULL, TimeOut int NULL,";
    S += "Camer char(64) NULL,  MinRash float NULL, MidRash float NULL, MaxRash float NULL, MinLDop float NULL,";
    S += "MinRDop float NULL, MidLDop float NULL, MidRDop float NULL, MaxLDop float NULL, MaxRDop float NULL,";
    S += "MinV float NULL, MidV float NULL, MaxV float NULL, DP DATETIME NULL, OpNameL char(24) NULL)";
    if(!DM->SQLWRITE(S))
    {
      S = "Не создана таблица  - DVIG" + DM->ErrorString;
      ShowMessage(S);
      SelfCloseFlag = true;
      return;
    }
    //Перед записью перезапустить таблицу после создания
    if(!DM->RestartDB())
    {
      S = "Не создана таблица Parameters - " + DM->ErrorString;
      ShowMessage(S);
      SelfCloseFlag = true;
      return;
    }
    TDateTime DT;
    DT = Now();
    S = "INSERT INTO Parameters ";
    S += "(PortNum,PortSpeed,TimeOut,Camer,MinRash,MidRash,MaxRash,MinLDop,MinRDop,MidLDop,MidRDop,MaxLDop,MaxRDop,MinV,MidV,MaxV,DP) VALUES ";
    S += (AnsiString)"('" + ComboBox1->Text  + (AnsiString)"',";       //PortNum
    S += (AnsiString)ComboBox2->Text.ToInt() + (AnsiString)",";                            //PortSpeed
    S += (AnsiString)Edit7->Text.ToInt()  + (AnsiString)",";                                //TimeOut
    S += (AnsiString)"'" + ComboBox3->Text  + (AnsiString)"',";                            //Camer
    S += ReplZPnaPunk((AnsiString)(ReplPunknaZP(Edit8->Text).ToDouble()))   + (AnsiString)",";                           //MinRash
    S += ReplZPnaPunk((AnsiString)(ReplPunknaZP(Edit9->Text).ToDouble()))  + (AnsiString)"," ;                           //MidRash
    S += ReplZPnaPunk((AnsiString)(ReplPunknaZP(Edit10->Text).ToDouble()))   + (AnsiString)",";                          //MaxRash
    S += ReplZPnaPunk((AnsiString)(ReplPunknaZP(Edit11->Text).ToDouble())) + (AnsiString)"," ;                           //MinLDop
    S += ReplZPnaPunk((AnsiString)(ReplPunknaZP(Edit14->Text).ToDouble())) +  (AnsiString)",";                           //MinRDop
    S += ReplZPnaPunk((AnsiString)(ReplPunknaZP(Edit12->Text).ToDouble()))   +  (AnsiString)",";                         //MidLDop
    S += ReplZPnaPunk((AnsiString)(ReplPunknaZP(Edit15->Text).ToDouble()))   +  (AnsiString)",";                         //MidRDop
    S += ReplZPnaPunk((AnsiString)(ReplPunknaZP(Edit13->Text).ToDouble()))  + (AnsiString)",";                           //MaxLDop
    S += ReplZPnaPunk((AnsiString)(ReplPunknaZP(Edit16->Text).ToDouble()))  + (AnsiString)",";                           //MaxRDop
    S += ReplZPnaPunk((AnsiString)(ReplPunknaZP(Edit17->Text).ToDouble()))  + (AnsiString)",";                           //MinV
    S += ReplZPnaPunk((AnsiString)(ReplPunknaZP(Edit18->Text).ToDouble())) + (AnsiString)",";                            //MidV
    S += ReplZPnaPunk((AnsiString)(ReplPunknaZP(Edit19->Text).ToDouble())) + (AnsiString)",";                            //MaxV
    S += (AnsiString)"'" + DT.FormatString("dd-mm-yyyy  hh:nn:ss") + (AnsiString)"');";     //DP
    if(!DM->SQLWRITE(S))
    {
      S = "Не заполнена таблица  - Parameters" + DM->ErrorString;
      ShowMessage(S);
//      SelfCloseFlag = true;
      return;
    }
  }
  else   //Записать параметры из БД в память и страницу
  {
//---------------------------------------------------------------------------
    S = "SELECT * FROM Parameters ;";
    if(DM->SQLRead(S))
    {
      DM->ADOQuery1->First();
      memset(&CurParameters,0,sizeof(Params));
      CurParameters.INDL        =  DM->ADOQuery1->FieldByName("INDL")->AsInteger;
      CurParameters.IND         =  DM->ADOQuery1->FieldByName("IND")->AsInteger;
      strcpy(CurParameters.PortNum, Trim(DM->ADOQuery1->FieldByName("PortNum")->AsString).c_str());
      strcpy(CurParameters.Camer,    Trim(DM->ADOQuery1->FieldByName("Camer")->AsString).c_str());
      strcpy(CurParameters.OpNameL,    Trim(DM->ADOQuery1->FieldByName("OpNameL")->AsString).c_str());
      CurParameters.PortSpeed   =  DM->ADOQuery1->FieldByName("PortSpeed")->AsInteger;
      CurParameters.TimeOut     =  DM->ADOQuery1->FieldByName("TimeOut")->AsInteger;
      CurParameters.MinRash     =  DM->ADOQuery1->FieldByName("MinRash")->AsFloat;
      CurParameters.MidRash     =  DM->ADOQuery1->FieldByName("MidRash")->AsFloat;
      CurParameters.MaxRash     =  DM->ADOQuery1->FieldByName("MaxRash")->AsFloat;
      CurParameters.MinLDop     =  DM->ADOQuery1->FieldByName("MinLDop")->AsFloat;
      CurParameters.MinRDop     =  DM->ADOQuery1->FieldByName("MinRDop")->AsFloat;
      CurParameters.MidLDop     =  DM->ADOQuery1->FieldByName("MidLDop")->AsFloat;
      CurParameters.MidRDop     =  DM->ADOQuery1->FieldByName("MidRDop")->AsFloat;
      CurParameters.MaxLDop     =  DM->ADOQuery1->FieldByName("MaxLDop")->AsFloat;
      CurParameters.MaxRDop     =  DM->ADOQuery1->FieldByName("MaxRDop")->AsFloat;
      CurParameters.MinV        =  DM->ADOQuery1->FieldByName("MinV")->AsFloat;
      CurParameters.MidV        =  DM->ADOQuery1->FieldByName("MidV")->AsFloat;
      CurParameters.MaxV        =  DM->ADOQuery1->FieldByName("MaxV")->AsFloat;
      CurParameters.DP          =  DM->ADOQuery1->FieldByName("DP")->AsDateTime;
      //Заполнить форму значениями
      ComboBox1->Text = CurParameters.PortNum;
      ComboBox2->Text = CurParameters.PortSpeed;
      Edit7->Text     = CurParameters.TimeOut;
      ComboBox3->Text = CurParameters.Camer;
      Edit8->Text     = S.sprintf("%7.3f",CurParameters.MinRash);
      Edit9->Text     = S.sprintf("%7.3f",CurParameters.MidRash);
      Edit10->Text    = S.sprintf("%7.3f",CurParameters.MaxRash);
      Edit11->Text    = S.sprintf("%7.3f",CurParameters.MinLDop);
      Edit12->Text    = S.sprintf("%7.3f",CurParameters.MidLDop);
      Edit13->Text    = S.sprintf("%7.3f",CurParameters.MaxLDop);
      Edit14->Text    = S.sprintf("%7.3f",CurParameters.MinRDop);
      Edit15->Text    = S.sprintf("%7.3f",CurParameters.MidRDop);
      Edit16->Text    = S.sprintf("%7.3f",CurParameters.MaxRDop);
      Edit17->Text    = S.sprintf("%7.3f",CurParameters.MinV);
      Edit18->Text    = S.sprintf("%7.3f",CurParameters.MidV);
      Edit19->Text    = S.sprintf("%7.3f",CurParameters.MaxV);
      Label60->Caption = CurParameters.DP.FormatString("dd-mm-yyyy");
//      Label62->Caption = CurParameters.OpNameL;
    }
    else
    {
      S = "Нет доступа к таблице - Parameters " + DM->ErrorString;
      ShowMessage(S);
      SelfCloseFlag = true;
      return;
    }
  }
*/
/*////////////////////
  if(!DM->IsTableExist("Controls"))
  {
    S = "CREATE TABLE Controls (INDL int IDENTITY, IND int NULL, NumSCH char(24) NULL,  Makedate DATETIME NULL, Controldate DATETIME NULL,SurName char(24) NULL, Name char(24) NULL,";
    S += "FName char(24) NULL,  Taun char(24) NULL, Street char(24) NULL, Haus  char(8) NULL, Korp char(8) NULL, Bit char(8) NULL, Result char(128) NULL, Type char(24) NULL,";
    S += "Qmin float NULL, Qt float NULL, Qn float NULL, SHminB float NULL,SHminE float NULL, CHtB  float NULL, CHtE float NULL, CHnB float NULL,";
    S += "DCHmin float NULL, DCHt float NULL, DCHn float NULL, IZMmin float NULL, IZMt float NULL, IZMn float NULL, PRCmin float NULL, PRCt float NULL, PRCn float NULL, OpName char(24) NULL)";
    if(!DM->SQLWRITE(S))
    {
      S = "Не создана таблица  - Controls" + DM->ErrorString;
      ShowMessage(S);
      SelfCloseFlag = true;
      return;
    }
    //Перед записью перезапустить таблицу после создания
    if(!DM->RestartDB())
    {
      S = "Не создана таблица Controls - " + DM->ErrorString;
      ShowMessage(S);
      SelfCloseFlag = true;
      return;
    }
  }
  DM->OpName = OldOpName;
  //таблица операторов уже создана
  FeelOperatorsTable();
  FeelGroupsTable();
///////////////////////////////////////////////////////////////////////////////
*/
//  Работа с ком портом
  AnsiString portname;
  DCB   dcb;  //struct
  if(!ComPortRdOpen())
  {
//    Panel8->Visible = true;
    ImageList1->Draw(Image2->Canvas,0,0,3,true);
    ComPortFlag = false;
    FlagGetDate = false;
    ImageList1->Draw(Image8->Canvas,0,0,3,true);
    ShowMessage(" Не верный номер компорта! Bвведите верный номер компорта в установке");
  }
  else
  {
    ImageList1->Draw(Image2->Canvas,0,0,2,true);
    ComPortFlag = true;
  }
//////////////////////////////////////////////////////////////////////////////
  HWND hWndC=capCreateCaptureWindow("",WS_DISABLED,0,0,0,0,0,0); // скрытое окно камеры
  CamerConectFlag = capDriverConnect(hWndC,NUM);           // подключаем к первой камере (загорается фотодиол)
  if(!CamerConectFlag)
  {
    for(int i = 0; i < 9; i++)
    {
      CamerConectFlag = capDriverConnect(hWndC,NUM);           // подключаем к первой камере (загорается фотодиол)
      Sleep(50);
      if(CamerConectFlag) break;
    }
    if(!CamerConectFlag)
    {
      ImageList1->Draw(Image3->Canvas,0,0,3,true);
//      ShowMessage(" Не удалость подключиться к видеокамере.");
//      SelfCloseFlag = true;
//      return;
    }
    else
      ImageList1->Draw(Image3->Canvas,0,0,2,true);
  }
  else
    ImageList1->Draw(Image3->Canvas,0,0,2,true);
  capDriverDisconnect(hWndC);          // отключаемся от камеры (светодиод тухнет)
  DestroyWindow(hWndC);                // убираем окно
/* Vrem prov
  if(!PassShow())
  {
    SelfCloseFlag = true;
    Priznak = 1;
    Close();
    return;
  }
  pProfile->StoreParameter("Common","LastName",DM->OpName);
*/ //Konettc
  TikCount = 0;
  if( ComPortFlag && CamerConectFlag)
  {
    writer = new TThreadWriter(true, COMportRd, "-1");
//    writer->Execute();
    delete writer;
  }
  Timer1->Enabled = true;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
bool TMainForm::ComPortRdOpen(void)
{
  AnsiString   portname;
  DCB          dcb;  //struct
  COMMTIMEOUTS timeouts;
  char         C[128];                                                           //CREATE_NEW|

  COMportRd = CreateFile(Edit1->Text.c_str(),GENERIC_READ|GENERIC_WRITE,0, NULL,OPEN_EXISTING,FILE_FLAG_OVERLAPPED, NULL);
  if(COMportRd == INVALID_HANDLE_VALUE)
  {
    DWORD D = GetLastError();
    return false;
  }
  //считать структуру из порта
  if(!GetCommState(COMportRd, &dcb)) //?если не удалось
  {
    RdCOMClose();
    ShowMessage ("не удалось считать DCB");
    return false;
  }
  dcb.BaudRate = StrToInt(Edit2->Text); //скорость пеедачи 115200 бод
  dcb.fBinary = TRUE; //включаем двоичный режим обмена
  dcb.fOutxCtsFlow = FALSE; //включаем режим слежения за сигналом CTS
  dcb.fOutxDsrFlow = FALSE; //выключаем режим слежения за сигналом DSR
  dcb.fDtrControl = DTR_CONTROL_DISABLE; //отключаем использование линии DTR
  dcb.fDsrSensitivity = FALSE; //отключаем восприимчивость драйвера к состоянию линии DSR
  dcb.fNull = FALSE; //разрешить прием нулевых байтов
  dcb.fRtsControl = RTS_CONTROL_DISABLE; //отключаем использование линии RTS
  dcb.fAbortOnError = FALSE; //отключаем остановку всех операций чтения записи при ошибке
  dcb.ByteSize = 8; //заданы 8 битов в байте
  dcb.Parity = 0; //отключаем проверку четности
  dcb.StopBits = 0; //задаем один стоп бит
  //Загрузить структуру ИСИ в порт
  if(!SetCommState(COMportRd, &dcb)) //если не удалось  - закрыть компорт и выдать сообщение
  {
    RdCOMClose();
    ShowMessage(" Не удалось установить BCB");
    return false;
  }
  //Установить таймауты
  timeouts.ReadIntervalTimeout = 0; //таймаут между двумя символами
  timeouts.ReadTotalTimeoutMultiplier = 0; //общий таймаут операции чтения
  timeouts.ReadTotalTimeoutConstant = 0; //константа для общего таймаута операции чтения
  timeouts.WriteTotalTimeoutMultiplier = 1; //общий таймаут операции записи
  timeouts.WriteTotalTimeoutConstant = 10; //константа для общего таймаута операции записи
  //записать структуру таймаутов в порт
  if(!SetCommTimeouts(COMportRd, &timeouts))
  {
    RdCOMClose();                             //если не удалось
    ShowMessage(" Не удалось записать структуру таймаутов в порт");
    return false;
  }
  //установить размеры буферов приема и ередачи
  SetupComm(COMportRd,2000,2000);
  PurgeComm(COMportRd, PURGE_RXCLEAR); //                                Очистить буфер ввода
//  writer = new TThreadWriter(this);
  reader = new TThreadReader(false, COMportRd);   //    ЗАПУСК ЗАДАЧИ ЧТЕНИЯ
  HWND hWnd;
  LPCTSTR lpszClass;
  LPCTSTR lpszWindow;		// указатель имени окна
  hWnd = GetForegroundWindow();
  reader->Form1Handle = hWnd;
  reader->FreeOnTerminate = true;
  return true;
}
//---------------------------------------------------------------------------
void  __fastcall TMainForm::AnswerEvent(TMessage& Msg)
{
  AnsiString S;
  int i;
  memcpy(BuffR, reader->bufrd, reader->btr);
  if(FlagNePolhoyDlini)
  {
    for(i = 0; i <  reader->btr; i++)
      InputBuffer += (char)reader->bufrd[i];
    ReadedCount += reader->btr;
  }
  else
  {
    WaitCount = reader->bufrd[0] + 1;
    for(i = 1; i <  reader->btr; i++)
      InputBuffer += (char)reader->bufrd[i];
    ReadedCount = reader->btr;
  }
  if(ReadedCount < WaitCount)
  {
    FlagNePolhoyDlini = true;
    return;
  }
/*
  Edit4->Text = InputBuffer;
  Label13->Caption = (AnsiString)ReadedCount-1;
  if(InputBuffer != Edit3->Text)
  {
    ErrCodesCount++;
    Label9->Caption = ErrCodesCount;
    S.sprintf("%5u %s %s",CyklesCount, Edit3->Text.c_str(), InputBuffer.c_str());
    ErrList->Add(S);
  }
*/  
}
//---------------------------------------------------------------------------
void TMainForm::RdCOMClose()
{
  if(reader) reader->Terminate(); //???? ????? ?????? ????????, ????????? ???; ????????
  if(reader)
    CloseHandle(COMportRd); //закрыть порт
  COMportRd=0; //???????? ?????????? ??? ??????????? ?????
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::SendIntoPort(AnsiString S)
{
   memset(bufwr,0,sizeof(bufwr));
   PurgeComm(COMportWr, PURGE_TXCLEAR);
   strcpy(bufwr,S.c_str());
   writer = new TThreadWriter(false, COMportWr, S);
   writer->FreeOnTerminate = true;
}
//---------------------------------------------------------------------------
void TMainForm::FeelOperatorsTable(void)
{
  AnsiString S;
  Operator   O;
  // Таблица групп в ОЗУ
  S  = "Select * from Operators order by OpName;";
  if(!DM->SQLRead(S))
  {
    ShowMessage("Не могу создать таблицу операторов в озу");
    return;
  }
  DM->ADOQuery1->First();
  DM->OpList.clear();
  while(!DM->ADOQuery1->Eof)
  {
    strcpy(O.OpName, Trim(DM->ADOQuery1->FieldByName("OpName")->AsString).c_str());
    strcpy(O.GroupName, Trim(DM->ADOQuery1->FieldByName("GroupName")->AsString).c_str());
    AnsiString S =  Trim(DM->ADOQuery1->FieldByName("Password1")->AsString);
//    for(int i = 1; i <= S.Length(); i++)
//      S[i] = S[i] + i;
    strcpy(O.Password1, S.c_str());
    O.UndeleteF = DM->ADOQuery1->FieldByName("UndeleteF")->AsInteger; //автосброс в базу
    DM->OpList.push_back(O);
    DM->ADOQuery1->Next();
  }
  DM->ADOQuery1->Close();
}
//---------------------------------------------------------------------------
AnsiString TMainForm::CreateDBSQLGet(AnsiString DBName)
{
    //Создается SQL запрос создания станционной БД
  AnsiString S;

  S = "CREATE DATABASE " + DBName ;
  S = S + " ON (name = '" +  DBName + "', filename = '" +
      Dir + "\\DB\\" + DBName + ".MDF" + "', size = 5)";
  S = S + " LOG ON (name = '" +  DBName + "_LOG" + "', filename = '" +
      Dir + "\\DB\\" + DBName + "_LOG.LDF" + "', size = 5)";
  return S;
}
//---------------------------------------------------------------------------
/*
void __fastcall TMainForm::FeelGroupsTable(void)
{
  OpGroup G;
  // Таблица групп в ОЗУ
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
	  G.UndeleteF = DM->Query1->FieldByName("UndeleteF")->AsBoolean; //автосброс в базу
 	  G.PRights      = DM->Query1->FieldByName("PRights")->AsInteger;
	  DM->GrList.push_back(G);
	  DM->Query1->Next();
	}
	DM->Query1->Close();
}
*/
//---------------------------------------------------------------------------
void TMainForm::FeelGroupsTable(void)
{
  AnsiString S;
  OpGroup    G;
  // Таблица групп в ОЗУ
  S = "Select * from Groups order by GrName";
  if(!DM->SQLRead(S))
  {
    ShowMessage("Не могу создать таблицу групп в озу");
    return;
  }
  DM->ADOQuery1->First();
  DM->GrList.clear();
  while(!DM->ADOQuery1->Eof)
  {
    strcpy(G.GrName, DM->ADOQuery1->FieldByName("GrName")->AsString.c_str());
    strcpy(G.GrFullName, DM->ADOQuery1->FieldByName("GrFullName")->AsString.c_str());
    G.UndeleteF = DM->ADOQuery1->FieldByName("UndeleteF")->AsInteger; //автосброс в базу
    G.PRights      = DM->ADOQuery1->FieldByName("PRights")->AsInteger;
    DM->GrList.push_back(G);
    DM->ADOQuery1->Next();
  }
  DM->ADOQuery1->Close();
}
//---------------------------------------------------------------------------
bool TMainForm::PassShow(void)
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
    DM->OpName      = PasswordForm->Name;    //Текущий оператор
    DM->OpRights    = PasswordForm->Rights;  //Права доступа текущего оператора
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
    DM->CurOpName   = PasswordForm->Name;    //Текущий оператор
    DM->OpRights    = PasswordForm->Rights;  //Права доступа текущего оператора
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
void __fastcall TMainForm::OpDispClick(TObject *Sender)
{        //Вызов диспетчера операторов
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
/*   ПОТОМ УДАЛЮ
void __fastcall TMainForm::SaveParametersClick(TObject *Sender)
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
      S = "Не изменена таблица  - Parameters" + DM->ErrorString;
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
bool __fastcall TMainForm::ComparePar(void)
{
/*
  bool Result;

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
  return Result;
*/
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Button1Click(TObject *Sender)
{
  AnsiString S = "Drop table Parameters";
    if(!DM->SQLWRITE(S))
    {
      S = "Не удалена таблица  - Parameters" + DM->ErrorString;
      ShowMessage(S);
      return;
    }
   S = "Drop table Controls";
    if(!DM->SQLWRITE(S))
    {
      S = "Не удалена таблица  - Controls" + DM->ErrorString;
      ShowMessage(S);
      return;
    }
   S = "Drop table OPERATORS";
    if(!DM->SQLWRITE(S))
    {
      S = "Не удалена таблица  - OPERATORS" + DM->ErrorString;
      ShowMessage(S);
      return;
    }
   S = "Drop table Groups";
    if(!DM->SQLWRITE(S))
    {
      S = "Не удалена таблица  - Groups" + DM->ErrorString;
      ShowMessage(S);
      return;
    }

}
//---------------------------------------------------------------------------
void __fastcall TMainForm::StartBtnClick(TObject *Sender)
{
  bool Res;

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
  Calculation = true;
  //
  //Перадача команды в модуль
  //
  switch(NumCodeProv)
  {
    case 0: Res = FotoSave("FotoMinBeg.bmp"); break;
    case 1: Res = FotoSave("FotoMidBeg.bmp"); break;
    case 2: Res = FotoSave("FotoMaxBeg.bmp"); break;
  }
  ReadFlag = true;
  RBDisabling();
  if(Res)
    ImageList1->Draw(Image3->Canvas,0,0,2,true);
  else
  {
    ImageList1->Draw(Image3->Canvas,0,0,3,true);
    return;
  }
  if(ReadWideo2())
    ImageList1->Draw(Image3->Canvas,0,0,2,true);
  else
  {
    ImageList1->Draw(Image3->Canvas,0,0,3,true);
    return;
  }
}
//---------------------------------------------------------------------------
void TMainForm::RBDisabling(void)
{
  QminRb->Enabled = false;
  QtRb->Enabled = false;
  QnomRb->Enabled = false;
  StartBtn->Enabled = false;
}
//---------------------------------------------------------------------------
void TMainForm::RBEnabling(void)
{
  QminRb->Enabled = true;
  QtRb->Enabled = true;
  QnomRb->Enabled = true;
  StartBtn->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::SaveIntoBaseClick(TObject *Sender)
{
  AnsiString S;
///*
  if(EndCalcMin && EndCalcT && EndCalcN != true)
  {
    ShowMessage("Нет завершения испытаний!");
    return;
  }
//*/

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
    S = "Не записана таблица  - Controls" + DM->ErrorString;
    ShowMessage(S);
    return;
  }
  PrintForm3 = new TPrintForm3(this);
  PrintForm3->QRLabel15->Caption = FirmName;
  PrintForm3->QRLabel16->Caption = ContrDT.FormatString("dd.mm.yyyy");
  PrintForm3->QRLabel17->Caption = TypeEdit->Text;
  PrintForm3->QRLabel18->Caption = Edit20->Text + " " + DateTimePicker1->Date.FormatString("dd.mm.yyyy");
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
  PrintForm3->QRLabel9->Caption = ResultEdit->Text;
  PrintForm3->QRImage1->Picture->LoadFromFile("MinBegFile.bmp");
  PrintForm3->QRImage4->Picture->LoadFromFile("MinEndFile.bmp");
  PrintForm3->QRImage2->Picture->LoadFromFile("MidBegFile.bmp");
  PrintForm3->QRImage5->Picture->LoadFromFile("MidEndFile.bmp");
  PrintForm3->QRImage3->Picture->LoadFromFile("MaxBegFile.bmp");
  PrintForm3->QRImage6->Picture->LoadFromFile("MaxEndFile.bmp");
  PrintForm3->QuickRep1->Preview();
  PrintForm3->QuickRep1->Print();
  delete PrintForm3;
}
//---------------------------------------------------------------------------
void TMainForm::WrCOMClose()
{
  if(writer) //???????? if(writer) ???????????, ????? ????????? ??????;   sendMsg
  {
    writer->Terminate();
    writer->Resume();
  }
  if(writer)
    CloseHandle(COMportWr); //закрыть порт
  COMportWr=0; //???????? ?????????? ??? ??????????? ?????
}
//---------------------------------------------------------------------------
bool TMainForm::FotoSave(AnsiString FileName)
{
  TClipboard *pCB;
  AnsiString S;
  TDateTime TD;
  Panel6->Visible = false;
  HWND hWndC=capCreateCaptureWindow("",WS_CHILD,0,0,0,0,this->Handle,0); // скрытое окно камеры
  CamerConectFlag = capDriverConnect(hWndC,NUM);           // подключаем к первой камере (загорается фотодиол)
  if(!CamerConectFlag)
  {
    for(int i = 0; i < 9; i++)
    {
      Sleep(50);
      CamerConectFlag = capDriverConnect(hWndC,NUM);           // подключаем к первой камере (загорается фотодиол)
      if(CamerConectFlag) break;
    }
    if(!CamerConectFlag)
    {
      ShowMessage(" Не удалость подключиться к видеокамере.");
      return false;
    }
  }
  bool b = capGrabFrame(hWndC);    // дожидаемся и берем кадр с камеры
  b = capFileSaveDIB(hWndC, FileName.c_str()); //копируем кадр в файл
  capDriverDisconnect(hWndC);          // отключаемся от камеры (светодиод тухнет)
  DestroyWindow(hWndC);                // убираем окно
  Image1->Picture->LoadFromFile(FileName.c_str());    // или в файл записываем
  TD = Now();
  S = TD.FormatString("dd.mm.yyyy hh:nn:ss");
  Image1->Canvas->TextOut(Image1->Left + 16, Image1->Height + 170 , S);
  Image1->Picture->SaveToFile(FileName);                  // или в файл записываем
  return true;
}
//---------------------------------------------------------------------------
bool TMainForm::ReadWideo2(void)
{
  AnsiString S;
  TDateTime TD;
  char Arr[10] = "G:\A.bmp";

  Panel6->Visible = true;
  Image1->Canvas->Font->Style = TFontStyles()<< fsBold;
  HWND hWndC=capCreateCaptureWindow("",WS_CHILD,0,0,0,0,this->Handle,0); // скрытое окно камеры
//  bool c = capFileSetCaptureFile(hWndC, "G:\A.bmp");
  CamerConectFlag = capDriverConnect(hWndC,0);           // подключаем к первой камере (загорается фотодиол)
  if(!CamerConectFlag)
  {
    for(int i = 0; i < 9; i++)
    {
      Sleep(50);
      CamerConectFlag = capDriverConnect(hWndC,0);           // подключаем к первой камере (загорается фотодиол)
      if(CamerConectFlag) break;
    }
    if(!CamerConectFlag)
    {
      Panel6->Visible = false;
      return false;
    }
  }
  while(ReadFlag)
  {
    bool b = capGrabFrame(hWndC);    // дожидаемся и берем кадр с камеры
    b = capFileSaveDIB(hWndC, "A.bmp"); //копируем кадр в файл
    if (b)
    {                         // если все получилось
      Image1->Picture->LoadFromFile("A.bmp");
      Image1->Refresh();
      TD = Now();
      S = TD.FormatString("dd.mm.yyyy hh:nn:ss");
      Panel6->Caption = S;
      Application->ProcessMessages();
//      int T = Edit21->Text.ToInt();
      Sleep(150);
    }
  }
  capDriverDisconnect(hWndC);          // отключаемся от камеры (светодиод тухнет)
  DestroyWindow(hWndC);                // убираем окно
  Panel6->Visible = false;
  return true;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::ResultPanelClick(TObject *Sender)
{
  int   N;
/*
  if(!FlagCntr)
  {
    ShowMessage("Нет запущенных потоков поверки!");       //TBitBtn
    return;
  }
*/
  Form2 = new TForm2(this);
  switch (NumCodeProv)
  {
    case 0:
    Form2->Image1->Picture->LoadFromFile("FotoMinBeg.bmp");
    Form2->Image2->Picture->LoadFromFile("FotoMinEnd.bmp");
    break;
    case 1:
    Form2->Image1->Picture->LoadFromFile("FotoMidBeg.bmp");
    Form2->Image2->Picture->LoadFromFile("FotoMidEnd.bmp");
    break;
    case 2:
    Form2->Image1->Picture->LoadFromFile("FotoMaxBeg.bmp");
    Form2->Image2->Picture->LoadFromFile("FotoMaxEnd.bmp");
    break;
  }
  if(Form2->ShowModal() == IDOK)
  {
    EtapeCalculate(Form2->BegValue, Form2->EndValue);
  }
}
//---------------------------------------------------------------------------

void TMainForm::EtapeCalculate(float BegValue, float EndValue)
{
  AnsiString S;
  switch (NumCodeProv)    //После получения данных счетчиков вычисляются разности и % отклонения от номмы
  {
    case 0:
      Edit21->Text = S.sprintf("%9.6f",BegValue);
      Edit1->Text = S.sprintf("%9.6f",EndValue);

      EndCalcMin = true;
    break;
    case 1:
      Edit22->Text = S.sprintf("%9.6f",BegValue);
      Edit2->Text = S.sprintf("%9.6f",EndValue);

      EndCalcT = true;
    break;
    case 2:
      Edit23->Text = S.sprintf("%9.6f",BegValue);
      Edit3->Text = S.sprintf("%9.6f",EndValue);

      EndCalcN = true;
    break;
  }

}
//---------------------------------------------------------------------------
void TMainForm::WorkWSReestr(void)
{
  if(Reg->KeyExists("Baza"))  //
  {
    ReadFromReestr();
  }
  else
  {
    WriteIntoReestr();
  }
}
//---------------------------------------------------------------------------
void TMainForm::WriteIntoReestr(void)
{
  DiametrVn D;

  DM->DiametrList.clear();
  try
  {
    D.Diametr = d8->Text.ToInt();
    D.Qn      = ReplPunknaZP(Qn8->Text).ToDouble();
    D.DQn     = ReplPunknaZP(DQn8->Text).ToDouble();
    D.DQt     = ReplPunknaZP(DQt8->Text).ToDouble();
    D.DQmin   = ReplPunknaZP(DQmin8->Text).ToDouble();
    D.Vn      = ReplPunknaZP(Vn8->Text).ToDouble();
    D.Vt      = ReplPunknaZP(Vt8->Text).ToDouble();
    D.Vmin    = ReplPunknaZP(Vmin8->Text).ToDouble();
    DM->DiametrList.push_back(D);
    D.Diametr = d10->Text.ToInt();
    D.Qn      = ReplPunknaZP(Qn10->Text).ToDouble();
    D.DQn     = ReplPunknaZP(DQn10->Text).ToDouble();
    D.DQt     = ReplPunknaZP(DQt10->Text).ToDouble();
    D.DQmin   = ReplPunknaZP(DQmin10->Text).ToDouble();
    D.Vn      = ReplPunknaZP(Vn10->Text).ToDouble();
    D.Vt      = ReplPunknaZP(Vt10->Text).ToDouble();
    D.Vmin    = ReplPunknaZP(Vmin10->Text).ToDouble();
    DM->DiametrList.push_back(D);
    D.Diametr = d15->Text.ToInt();
    D.Qn      = ReplPunknaZP(Qn15->Text).ToDouble();
    D.DQn     = ReplPunknaZP(DQn15->Text).ToDouble();
    D.DQt     = ReplPunknaZP(DQt15->Text).ToDouble();
    D.DQmin   = ReplPunknaZP(DQmin15->Text).ToDouble();
    D.Vn      = ReplPunknaZP(Vn15->Text).ToDouble();
    D.Vt      = ReplPunknaZP(Vt15->Text).ToDouble();
    D.Vmin    = ReplPunknaZP(Vmin15->Text).ToDouble();
    DM->DiametrList.push_back(D);
    D.Diametr = d20->Text.ToInt();
    D.Qn      = ReplPunknaZP(Qn20->Text).ToDouble();
    D.DQn     = ReplPunknaZP(DQn20->Text).ToDouble();
    D.DQt     = ReplPunknaZP(DQt20->Text).ToDouble();
    D.DQmin   = ReplPunknaZP(DQmin20->Text).ToDouble();
    D.Vn      = ReplPunknaZP(Vn20->Text).ToDouble();
    D.Vt      = ReplPunknaZP(Vt20->Text).ToDouble();
    D.Vmin    = ReplPunknaZP(Vmin20->Text).ToDouble();
    DM->DiametrList.push_back(D);
    D.Diametr = d25->Text.ToInt();
    D.Qn      = ReplPunknaZP(Qn25->Text).ToDouble();
    D.DQn     = ReplPunknaZP(DQn25->Text).ToDouble();
    D.DQt     = ReplPunknaZP(DQt25->Text).ToDouble();
    D.DQmin   = ReplPunknaZP(DQmin25->Text).ToDouble();
    D.Vn      = ReplPunknaZP(Vn25->Text).ToDouble();
    D.Vt      = ReplPunknaZP(Vt25->Text).ToDouble();
    D.Vmin    = ReplPunknaZP(Vmin25->Text).ToDouble();
    DM->DiametrList.push_back(D);
    D.Diametr = d32->Text.ToInt();
    D.Qn      = ReplPunknaZP(Qn32->Text).ToDouble();
    D.DQn     = ReplPunknaZP(DQn32->Text).ToDouble();
    D.DQt     = ReplPunknaZP(DQt32->Text).ToDouble();
    D.DQmin   = ReplPunknaZP(DQmin32->Text).ToDouble();
    D.Vn      = ReplPunknaZP(Vn32->Text).ToDouble();
    D.Vt      = ReplPunknaZP(Vt32->Text).ToDouble();
    D.Vmin    = ReplPunknaZP(Vmin32->Text).ToDouble();
    DM->DiametrList.push_back(D);
    D.Diametr = d40->Text.ToInt();
    D.Qn      = ReplPunknaZP(Qn40->Text).ToDouble();
    D.DQn     = ReplPunknaZP(DQn40->Text).ToDouble();
    D.DQt     = ReplPunknaZP(DQt40->Text).ToDouble();
    D.DQmin   = ReplPunknaZP(DQmin40->Text).ToDouble();
    D.Vn      = ReplPunknaZP(Vn40->Text).ToDouble();
    D.Vt      = ReplPunknaZP(Vt40->Text).ToDouble();
    D.Vmin    = ReplPunknaZP(Vmin40->Text).ToDouble();
    DM->DiametrList.push_back(D);
    D.Diametr = d50->Text.ToInt();
    D.Qn      = ReplPunknaZP(Qn50->Text).ToDouble();
    D.DQn     = ReplPunknaZP(DQn50->Text).ToDouble();
    D.DQt     = ReplPunknaZP(DQt50->Text).ToDouble();
    D.DQmin   = ReplPunknaZP(DQmin50->Text).ToDouble();
    D.Vn      = ReplPunknaZP(Vn50->Text).ToDouble();
    D.Vt      = ReplPunknaZP(Vt50->Text).ToDouble();
    D.Vmin    = ReplPunknaZP(Vmin50->Text).ToDouble();
    DM->DiametrList.push_back(D);
  }
  catch(...)
  {
    ShowMessage("В группе <Диаметры и соответствующие Q> введены не числовnые значения");
    return;
  }
  DM->ClassList.clear();
  ClassQ   C;
  try
  {
    strcpy(C.Name, Label77->Caption.c_str());
    C.Qmin = ReplPunknaZP(AQmin->Text).ToDouble();
    C.Qt =   ReplPunknaZP(AQt->Text).ToDouble();
    DM->ClassList.push_back(C);
    strcpy(C.Name, Label78->Caption.c_str());
    C.Qmin = ReplPunknaZP(BQmin->Text).ToDouble();
    C.Qt =   ReplPunknaZP(BQt->Text).ToDouble();
    DM->ClassList.push_back(C);
    strcpy(C.Name, Label79->Caption.c_str());
    C.Qmin = ReplPunknaZP(CQmin->Text).ToDouble();
    C.Qt =   ReplPunknaZP(CQt->Text).ToDouble();
    DM->ClassList.push_back(C);
  }
  catch(...)
  {
    ShowMessage("В группе <Зависимость Qmin и Qt от КЛАССА> введены не числовnые значения");
    return;
  }
  DM->ClassTList.clear();
  ClassT     T;
  try
  {
    strcpy(T.Name, "X");
    T.Tmin  = ReplPunknaZP(TminX->Text).ToDouble();
    T.Tmax  = ReplPunknaZP(TmaxX->Text).ToDouble();
    T.DminL = ReplPunknaZP(DminLX->Text).ToDouble();
    T.DminR = ReplPunknaZP(DminRX->Text).ToDouble();
    T.DtL   = ReplPunknaZP(DtLX->Text).ToDouble();
    T.DtR   = ReplPunknaZP(DtRX->Text).ToDouble();
    T.DnL   = ReplPunknaZP(DnLX->Text).ToDouble();
    T.DnR   = ReplPunknaZP(DnRX->Text).ToDouble();
    DM->ClassTList.push_back(T);
    strcpy(T.Name, "G");
    T.Tmin  = ReplPunknaZP(TminG->Text).ToDouble();
    T.Tmax  = ReplPunknaZP(TmaxG->Text).ToDouble();
    T.DminL = ReplPunknaZP(DminLG->Text).ToDouble();
    T.DminR = ReplPunknaZP(DminRG->Text).ToDouble();
    T.DtL   = ReplPunknaZP(DtLG->Text).ToDouble();
    T.DtR   = ReplPunknaZP(DtRG->Text).ToDouble();
    T.DnL   = ReplPunknaZP(DnLG->Text).ToDouble();
    T.DnR   = ReplPunknaZP(DnRG->Text).ToDouble();
    DM->ClassTList.push_back(T);
  }
  catch(...)
  {
    ShowMessage("В группе <Горячая и холодная вода> введены не числовnые значения");
    return;
  }
  Reg->WriteInteger("Baza","Params",1); //Диаметры и соответствующие QДиаметры и соответствующие Q
  Reg->WriteString("Baza","d8",d8->Text);
  Reg->WriteString("Baza","d10",d10->Text);
  Reg->WriteString("Baza","d15",d15->Text);
  Reg->WriteString("Baza","d20",d20->Text);
  Reg->WriteString("Baza","d25",d25->Text);
  Reg->WriteString("Baza","d32",d32->Text);
  Reg->WriteString("Baza","d40",d40->Text);
  Reg->WriteString("Baza","d50",d50->Text);

  Reg->WriteString("Baza","Qn8",Qn8->Text);
  Reg->WriteString("Baza","Qn10",Qn10->Text);
  Reg->WriteString("Baza","Qn15",Qn15->Text);
  Reg->WriteString("Baza","Qn20",Qn20->Text);
  Reg->WriteString("Baza","Qn25",Qn25->Text);
  Reg->WriteString("Baza","Qn32",Qn32->Text);
  Reg->WriteString("Baza","Qn40",Qn40->Text);
  Reg->WriteString("Baza","Qn50",Qn50->Text);

  Reg->WriteString("Baza","DQn8",DQn8->Text);
  Reg->WriteString("Baza","DQn10",DQn10->Text);
  Reg->WriteString("Baza","DQn15",DQn15->Text);
  Reg->WriteString("Baza","DQn20",DQn20->Text);
  Reg->WriteString("Baza","DQn25",DQn25->Text);
  Reg->WriteString("Baza","DQn32",DQn32->Text);
  Reg->WriteString("Baza","DQn40",DQn40->Text);
  Reg->WriteString("Baza","DQn50",DQn50->Text);

  Reg->WriteString("Baza","DQt8",DQt8->Text);
  Reg->WriteString("Baza","DQt10",DQt10->Text);
  Reg->WriteString("Baza","DQt15",DQt15->Text);
  Reg->WriteString("Baza","DQt20",DQt20->Text);
  Reg->WriteString("Baza","DQt25",DQt25->Text);
  Reg->WriteString("Baza","DQt32",DQt32->Text);
  Reg->WriteString("Baza","DQt40",DQt40->Text);
  Reg->WriteString("Baza","DQt50",DQt50->Text);

  Reg->WriteString("Baza","DQmin8",DQmin8->Text);
  Reg->WriteString("Baza","DQmin10",DQmin10->Text);
  Reg->WriteString("Baza","DQmin15",DQmin15->Text);
  Reg->WriteString("Baza","DQmin20",DQmin20->Text);
  Reg->WriteString("Baza","DQmin25",DQmin25->Text);
  Reg->WriteString("Baza","DQmin32",DQmin32->Text);
  Reg->WriteString("Baza","DQmin40",DQmin40->Text);
  Reg->WriteString("Baza","DQmin50",DQmin50->Text);

  Reg->WriteString("Baza","Vn8",Vn8->Text);
  Reg->WriteString("Baza","Vn10",Vn10->Text);
  Reg->WriteString("Baza","Vn15",Vn15->Text);
  Reg->WriteString("Baza","Vn20",Vn20->Text);
  Reg->WriteString("Baza","Vn25",Vn25->Text);
  Reg->WriteString("Baza","Vn32",Vn32->Text);
  Reg->WriteString("Baza","Vn40",Vn40->Text);
  Reg->WriteString("Baza","Vn50",Vn50->Text);

  Reg->WriteString("Baza","Vt8",Vt8->Text);
  Reg->WriteString("Baza","Vt10",Vt10->Text);
  Reg->WriteString("Baza","Vt15",Vt15->Text);
  Reg->WriteString("Baza","Vt20",Vt20->Text);
  Reg->WriteString("Baza","Vt25",Vt25->Text);
  Reg->WriteString("Baza","Vt32",Vt32->Text);
  Reg->WriteString("Baza","Vt40",Vt40->Text);
  Reg->WriteString("Baza","Vt50",Vt50->Text);

  Reg->WriteString("Baza","Vmin8",Vmin8->Text);
  Reg->WriteString("Baza","Vmin10",Vmin10->Text);
  Reg->WriteString("Baza","Vmin15",Vmin15->Text);
  Reg->WriteString("Baza","Vmin20",Vmin20->Text);
  Reg->WriteString("Baza","Vmin25",Vmin25->Text);
  Reg->WriteString("Baza","Vmin32",Vmin32->Text);
  Reg->WriteString("Baza","Vmin40",Vmin40->Text);
  Reg->WriteString("Baza","Vmin50",Vmin50->Text);

  Reg->WriteString("Baza","AQmin",AQmin->Text); //Зависимость Qmin и Qt от КЛАССА
  Reg->WriteString("Baza","AQt",AQt->Text);
  Reg->WriteString("Baza","BQmin",BQmin->Text);
  Reg->WriteString("Baza","BQt",BQt->Text);
  Reg->WriteString("Baza","CQmin",CQmin->Text);
  Reg->WriteString("Baza","CQt",CQt->Text);

  Reg->WriteString("Baza","TminX",TminX->Text);  //Горячая и холодная вода Пределы температур
  Reg->WriteString("Baza","TmaxX",TmaxX->Text);
  Reg->WriteString("Baza","DminLX",DminLX->Text);   //Процентные допустимые погрешности
  Reg->WriteString("Baza","DminRX",DminRX->Text);
  Reg->WriteString("Baza","DtLX",DtLX->Text);
  Reg->WriteString("Baza","DtRX",DtRX->Text);
  Reg->WriteString("Baza","DnLX",DnLX->Text);
  Reg->WriteString("Baza","DnRX",DnRX->Text);

  Reg->WriteString("Baza","TminG",TminG->Text);   //Пределы температур
  Reg->WriteString("Baza","TmaxG",TmaxG->Text);
  Reg->WriteString("Baza","DminLG",DminLG->Text); //Процентные допустимые погрешности
  Reg->WriteString("Baza","DminRG",DminRG->Text);
  Reg->WriteString("Baza","DtLG",DtLG->Text);
  Reg->WriteString("Baza","DtRG",DtRG->Text);
  Reg->WriteString("Baza","DnLG",DnLG->Text);
  Reg->WriteString("Baza","DnRG",DnRG->Text);
}
//---------------------------------------------------------------------------
void TMainForm::ReadFromReestr(void)
{
  DiametrVn D;

  DM->DiametrList.clear();
 //Диаметры и соответствующие QДиаметры и соответствующие Q
  d8->Text  = Reg->ReadString("Baza","d8", "8");
  d10->Text = Reg->ReadString("Baza","d10","10");
  d15->Text = Reg->ReadString("Baza","d15","15");
  d20->Text = Reg->ReadString("Baza","d20","20");
  d25->Text = Reg->ReadString("Baza","d25","25");
  d32->Text = Reg->ReadString("Baza","d32","32");
  d40->Text = Reg->ReadString("Baza","d40","40");
  d50->Text = Reg->ReadString("Baza","d50","50");

  Qn8->Text  = Reg->ReadString("Baza","Qn8","0.6");
  Qn10->Text = Reg->ReadString("Baza","Qn10","1.0");
  Qn15->Text = Reg->ReadString("Baza","Qn15","1.5");
  Qn20->Text = Reg->ReadString("Baza","Qn20","2.5");
  Qn25->Text = Reg->ReadString("Baza","Qn25","3.5");
  Qn32->Text = Reg->ReadString("Baza","Qn32","6.0");
  Qn40->Text = Reg->ReadString("Baza","Qn40","10.0");
  Qn50->Text = Reg->ReadString("Baza","Qn50","15.0");

  DQn8->Text  = Reg->ReadString("Baza","DQn8","0.08");
  DQn10->Text = Reg->ReadString("Baza","DQn10","0.10");
  DQn15->Text = Reg->ReadString("Baza","DQn15","0.15");
  DQn20->Text = Reg->ReadString("Baza","DQn20","0.25");
  DQn25->Text = Reg->ReadString("Baza","DQn25","0.35");
  DQn32->Text = Reg->ReadString("Baza","DQn32","0.50");
  DQn40->Text = Reg->ReadString("Baza","DQn40","0.80");
  DQn50->Text = Reg->ReadString("Baza","DQn50","1.00");

  DQt8->Text  = Reg->ReadString("Baza","DQt8","0.008");
  DQt10->Text = Reg->ReadString("Baza","DQt10","0.008");
  DQt15->Text = Reg->ReadString("Baza","DQt15","0.012");
  DQt20->Text = Reg->ReadString("Baza","DQt20","0.020");
  DQt25->Text = Reg->ReadString("Baza","DQt25","0.028");
  DQt32->Text = Reg->ReadString("Baza","DQt32","0.040");
  DQt40->Text = Reg->ReadString("Baza","DQt40","0.064");
  DQt50->Text = Reg->ReadString("Baza","DQt50","0.080");

  DQmin8->Text  = Reg->ReadString("Baza","DQmin8","0.6");
  DQmin10->Text = Reg->ReadString("Baza","DQmin10","1.0");
  DQmin15->Text = Reg->ReadString("Baza","DQmin15","1.5");
  DQmin20->Text = Reg->ReadString("Baza","DQmin20","2.5");
  DQmin25->Text = Reg->ReadString("Baza","DQmin25","3.5");
  DQmin32->Text = Reg->ReadString("Baza","DQmin32","6.0");
  DQmin40->Text = Reg->ReadString("Baza","DQmin40","10.0");
  DQmin50->Text = Reg->ReadString("Baza","DQmin50","15.0");

  Vn8->Text  = Reg->ReadString("Baza","Vn8","20");
  Vn10->Text = Reg->ReadString("Baza","Vn10","20");
  Vn15->Text = Reg->ReadString("Baza","Vn15","20");
  Vn20->Text = Reg->ReadString("Baza","Vn20","50");
  Vn25->Text = Reg->ReadString("Baza","Vn25","50");
  Vn32->Text = Reg->ReadString("Baza","Vn32","100");
  Vn40->Text = Reg->ReadString("Baza","Vn40","200");
  Vn50->Text = Reg->ReadString("Baza","Vn50","200");

  Vt8->Text  = Reg->ReadString("Baza","Vt8","5");
  Vt10->Text = Reg->ReadString("Baza","Vt10","5");
  Vt15->Text = Reg->ReadString("Baza","Vt15","5");
  Vt20->Text = Reg->ReadString("Baza","Vt20","20");
  Vt25->Text = Reg->ReadString("Baza","Vt25","20");
  Vt32->Text = Reg->ReadString("Baza","Vt32","50");
  Vt40->Text = Reg->ReadString("Baza","Vt40","500");
  Vt50->Text = Reg->ReadString("Baza","Vt50","500");

  Vmin8->Text  = Reg->ReadString("Baza","Vmin8","2.5");
  Vmin10->Text = Reg->ReadString("Baza","Vmin10","2.5");
  Vmin15->Text = Reg->ReadString("Baza","Vmin15","2.5");
  Vmin20->Text = Reg->ReadString("Baza","Vmin20","10");
  Vmin25->Text = Reg->ReadString("Baza","Vmin25","10");
  Vmin32->Text = Reg->ReadString("Baza","Vmin32","25");
  Vmin40->Text = Reg->ReadString("Baza","Vmin40","50");
  Vmin50->Text = Reg->ReadString("Baza","Vmin50","50");
  try
  {
    D.Diametr = d8->Text.ToInt();
    D.Qn    =  ReplPunknaZP(Qn8->Text).ToDouble();
    D.DQn   =  ReplPunknaZP(DQn8->Text).ToDouble();
    D.DQt   =  ReplPunknaZP(DQt8->Text).ToDouble();
    D.DQmin =  ReplPunknaZP(DQmin8->Text).ToDouble();
    D.Vn    =  ReplPunknaZP(Vn8->Text).ToDouble();
    D.Vt    =  ReplPunknaZP(Vt8->Text).ToDouble();
    D.Vmin  =  ReplPunknaZP(Vmin8->Text).ToDouble();
    DM->DiametrList.push_back(D);
    D.Diametr = d10->Text.ToInt();
    D.Qn    =  ReplPunknaZP(Qn10->Text).ToDouble();
    D.DQn   =  ReplPunknaZP(DQn10->Text).ToDouble();
    D.DQt   =  ReplPunknaZP(DQt10->Text).ToDouble();
    D.DQmin =  ReplPunknaZP(DQmin10->Text).ToDouble();
    D.Vn    =  ReplPunknaZP(Vn10->Text).ToDouble();
    D.Vt    =  ReplPunknaZP(Vt10->Text).ToDouble();
    D.Vmin  =  ReplPunknaZP(Vmin10->Text).ToDouble();
    DM->DiametrList.push_back(D);
    D.Diametr = d15->Text.ToInt();
    D.Qn    =  ReplPunknaZP(Qn15->Text).ToDouble();
    D.DQn   =  ReplPunknaZP(DQn15->Text).ToDouble();
    D.DQt   =  ReplPunknaZP(DQt15->Text).ToDouble();
    D.DQmin =  ReplPunknaZP(DQmin15->Text).ToDouble();
    D.Vn    =  ReplPunknaZP(Vn15->Text).ToDouble();
    D.Vt    =  ReplPunknaZP(Vt15->Text).ToDouble();
    D.Vmin  =  ReplPunknaZP(Vmin15->Text).ToDouble();
    DM->DiametrList.push_back(D);
    D.Diametr = d20->Text.ToInt();
    D.Qn    =  ReplPunknaZP(Qn20->Text).ToDouble();
    D.DQn   =  ReplPunknaZP(DQn20->Text).ToDouble();
    D.DQt   =  ReplPunknaZP(DQt20->Text).ToDouble();
    D.DQmin =  ReplPunknaZP(DQmin20->Text).ToDouble();
    D.Vn    =  ReplPunknaZP(Vn20->Text).ToDouble();
    D.Vt    =  ReplPunknaZP(Vt20->Text).ToDouble();
    D.Vmin  =  ReplPunknaZP(Vmin20->Text).ToDouble();
    DM->DiametrList.push_back(D);
    D.Diametr = d25->Text.ToInt();
    D.Qn    =  ReplPunknaZP(Qn25->Text).ToDouble();
    D.DQn   =  ReplPunknaZP(DQn25->Text).ToDouble();
    D.DQt   =  ReplPunknaZP(DQt25->Text).ToDouble();
    D.DQmin =  ReplPunknaZP(DQmin25->Text).ToDouble();
    D.Vn    =  ReplPunknaZP(Vn25->Text).ToDouble();
    D.Vt    =  ReplPunknaZP(Vt25->Text).ToDouble();
    D.Vmin  =  ReplPunknaZP(Vmin25->Text).ToDouble();
    DM->DiametrList.push_back(D);
    D.Diametr = d32->Text.ToInt();
    D.Qn    =  ReplPunknaZP(Qn32->Text).ToDouble();
    D.DQn   =  ReplPunknaZP(DQn32->Text).ToDouble();
    D.DQt   =  ReplPunknaZP(DQt32->Text).ToDouble();
    D.DQmin =  ReplPunknaZP(DQmin32->Text).ToDouble();
    D.Vn    =  ReplPunknaZP(Vn32->Text).ToDouble();
    D.Vt    =  ReplPunknaZP(Vt32->Text).ToDouble();
    D.Vmin  =  ReplPunknaZP(Vmin32->Text).ToDouble();
    DM->DiametrList.push_back(D);
    D.Diametr = d40->Text.ToInt();
    D.Qn    =  ReplPunknaZP(Qn40->Text).ToDouble();
    D.DQn   =  ReplPunknaZP(DQn40->Text).ToDouble();
    D.DQt   =  ReplPunknaZP(DQt40->Text).ToDouble();
    D.DQmin =  ReplPunknaZP(DQmin40->Text).ToDouble();
    D.Vn    =  ReplPunknaZP(Vn40->Text).ToDouble();
    D.Vt    =  ReplPunknaZP(Vt40->Text).ToDouble();
    D.Vmin  =  ReplPunknaZP(Vmin40->Text).ToDouble();
    DM->DiametrList.push_back(D);
    D.Diametr = d50->Text.ToInt();
    D.Qn    =  ReplPunknaZP(Qn50->Text).ToDouble();
    D.DQn   =  ReplPunknaZP(DQn50->Text).ToDouble();
    D.DQt   =  ReplPunknaZP(DQt50->Text).ToDouble();
    D.DQmin =  ReplPunknaZP(DQmin50->Text).ToDouble();
    D.Vn    =  ReplPunknaZP(Vn50->Text).ToDouble();
    D.Vt    =  ReplPunknaZP(Vt50->Text).ToDouble();
    D.Vmin  =  ReplPunknaZP(Vmin50->Text).ToDouble();
    DM->DiametrList.push_back(D);
  }
  catch(...)
  {
    ShowMessage("В группе <Диаметры и соответствующие Qn, DQn, DQt, DQmin, Vn, Vt, Vmin> введены не числовnые значения");
    return;
  }
  DM->ClassList.clear();
  ClassQ   C;
  AQmin->Text  = Reg->ReadString("Baza","AQmin","0.04"); //Зависимость Qmin и Qt от КЛАССА
  AQt->Text    = Reg->ReadString("Baza","AQt","0.10");
  BQmin->Text  = Reg->ReadString("Baza","BQmin","0.02");
  BQt->Text    = Reg->ReadString("Baza","BQt","0.08");
  CQmin->Text = Reg->ReadString("Baza","CQmin","0.01");
  CQt->Text = Reg->ReadString("Baza","CQt","0.015");
  try
  {
    strcpy(C.Name, Label77->Caption.c_str());
    C.Qmin = ReplPunknaZP(AQmin->Text).ToDouble();
    C.Qt =   ReplPunknaZP(AQt->Text).ToDouble();
    DM->ClassList.push_back(C);
    strcpy(C.Name, Label78->Caption.c_str());
    C.Qmin = ReplPunknaZP(BQmin->Text).ToDouble();
    C.Qt =   ReplPunknaZP(BQt->Text).ToDouble();
    DM->ClassList.push_back(C);
    strcpy(C.Name, Label79->Caption.c_str());
    C.Qmin = ReplPunknaZP(CQmin->Text).ToDouble();
    C.Qt =   ReplPunknaZP(CQt->Text).ToDouble();
    DM->ClassList.push_back(C);
  }
  catch(...)
  {
    ShowMessage("В группе <Зависимость Qmin и Qt от КЛАССА> введены не числовnые значения");
    return;
  }
  DM->ClassTList.clear();
  ClassT     T;
  TminX->Text   = Reg->ReadString("Baza","TminX","5");  //Горячая и холодная вода
  TmaxX->Text   = Reg->ReadString("Baza","TmaxX","30");
  DminLX->Text  = Reg->ReadString("Baza","DminLX","-5");
  DminRX->Text  = Reg->ReadString("Baza","DminRX","5");
  DtLX->Text    = Reg->ReadString("Baza","DtLX","-2");
  DtRX->Text    = Reg->ReadString("Baza","DtRX","2");
  DnLX->Text    = Reg->ReadString("Baza","DnLX","-2");
  DnRX->Text    = Reg->ReadString("Baza","DnRX","2");

  TminG->Text   = Reg->ReadString("Baza","TminG","30");
  TmaxG->Text   = Reg->ReadString("Baza","TmaxG","90");
  DminLG->Text  = Reg->ReadString("Baza","DminLG","-5");
  DminRG->Text  = Reg->ReadString("Baza","DminRG","5");
  DtLG->Text    = Reg->ReadString("Baza","DtLG","-3");
  DtRG->Text    = Reg->ReadString("Baza","DtRG","3");
  DnLG->Text    = Reg->ReadString("Baza","DnLG","-3");
  DnRG->Text    = Reg->ReadString("Baza","DnRG","3");
  try
  {
    strcpy(T.Name, "X");
    T.Tmin  = ReplPunknaZP(TminX->Text).ToDouble();
    T.Tmax  = ReplPunknaZP(TmaxX->Text).ToDouble();
    T.DminL = ReplPunknaZP(DminLX->Text).ToDouble();
    T.DminR = ReplPunknaZP(DminRX->Text).ToDouble();
    T.DtL   = ReplPunknaZP(DtLX->Text).ToDouble();
    T.DtR   = ReplPunknaZP(DtRX->Text).ToDouble();
    T.DnL   = ReplPunknaZP(DnLX->Text).ToDouble();
    T.DnR   = ReplPunknaZP(DnRX->Text).ToDouble();
    DM->ClassTList.push_back(T);
    strcpy(T.Name, "G");
    T.Tmin  = ReplPunknaZP(TminG->Text).ToDouble();
    T.Tmax  = ReplPunknaZP(TmaxG->Text).ToDouble();
    T.DminL = ReplPunknaZP(DminLG->Text).ToDouble();
    T.DminR = ReplPunknaZP(DminRG->Text).ToDouble();
    T.DtL   = ReplPunknaZP(DtLG->Text).ToDouble();
    T.DtR   = ReplPunknaZP(DtRG->Text).ToDouble();
    T.DnL   = ReplPunknaZP(DnLG->Text).ToDouble();
    T.DnR   = ReplPunknaZP(DnRG->Text).ToDouble();
    DM->ClassTList.push_back(T);
  }
  catch(...)
  {
    ShowMessage("В группе <Горячая и холодная вода> введены не числовnые значения");
    return;
  }

}
//-----------------------------------------------------------------------------
void __fastcall TMainForm::SaveParamsClick(TObject *Sender)
{
   WriteIntoReestr();
}
//---------------------------------------------------------------------------
//Процедура определения рабочих параметров пролива по параметрам счетчика
void __fastcall TMainForm::SelParamBtnClick(TObject *Sender)
{
/*
  AnsiString S, SS;
  int        i;

//  if((ComboBox3->Text != "")&&(ComboBox7->Text != "")&&(ComboBox8->Text != "")&&(ComboBox9->Text != ""))
//  {
    //Диаметр
    for(i = 0; i < (int)DiametrList.size(); i++)
    {
      if(DiametrList[i].Diametr == ComboBox3->Text.ToInt())
      {
        Qn = DiametrList[i].Qn * 1000;   //литры/час
        Edit10->Text = SS.sprintf("%8.3f", Qn);
        double T;
        T = Qn/1000;
        Label6->Caption = SS.sprintf("%5.3f",T);
        DQn = DiametrList[i].DQn * 1000;  //+- Литры в час
        DQt = DiametrList[i].DQt * 1000;  //+- Литры в час
        DQmin = DiametrList[i].DQmin * 1000;  //+- Литры в час
        Vn = DiametrList[i].Vn;  //+- Литры
        Edit19->Text =  SS.sprintf("%8.3f", Vn);
        Vt = DiametrList[i].Vt;  //+- Литры
        Edit18->Text =  SS.sprintf("%8.3f", Vt);
        Vmin = DiametrList[i].Vmin;  //+- Литры
        Edit17->Text =  SS.sprintf("%8.3f", Vmin);
        break;
      }
    }
    for(i = 0; i < (int)ClassTList.size(); i++)
    {
      if(Trim((AnsiString)ClassTList[i].Name) == Trim(ComboBox8->Text))
      {
        Tmin = ClassTList[i].Tmin;
        Edit24->Text = SS.sprintf("%5.3f", Tmin);
        Tmax = ClassTList[i].Tmax;
        Edit27->Text = SS.sprintf("%5.3f", Tmax);
        DminL = ClassTList[i].DminL;
        Edit11->Text = SS.sprintf("%5.3f", DminL);
        DminR = ClassTList[i].DminR;
        Edit14->Text = SS.sprintf("%5.3f", DminR);
        DtL = ClassTList[i].DtL;
        Edit12->Text = SS.sprintf("%5.3f", DtL);
        DtR = ClassTList[i].DtR;
        Edit15->Text = SS.sprintf("%5.3f", DtR);
        DnL = ClassTList[i].DnL;
        Edit13->Text = SS.sprintf("%5.3f", DnL);
        DnR = ClassTList[i].DnR;
        Edit16->Text = SS.sprintf("%5.3f", DnR);
        break;
      }
    }
    if(Trim(ComboBox9->Text) == "V")
    {
      if(Trim(ComboBox7->Text) == "B") S = "A";
      if(Trim(ComboBox7->Text) == "C") S = "B";
    }
    else S = ComboBox7->Text;
    for(i = 0; i < (int)ClassList.size(); i++)
    {
      if(Trim((AnsiString)ClassList[i].Name) == S)
      {
      double r;
        Qmin = Qn * ClassList[i].Qmin;    //Литры/час
        Edit8->Text = SS.sprintf("%5.3f",Qmin);
        r =  Qmin/1000;
        Label4->Caption = SS.sprintf("%5.3f",r);
        Qt =  Qn * ClassList[i].Qt;       //Литры/час
        Edit9->Text = SS.sprintf("%5.3f", Qt);
        r =  Qt/1000;
        Label5->Caption = SS.sprintf("%5.3f",r);
        break;
      }
    }
*/
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::Button3Click(TObject *Sender)
{
  ReadFlag = false;
  RBEnabling();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Timer1Timer(TObject *Sender)
{
  if(!ComPortFlag) return; // Нет компорта- нет работв
  TikCount++;
  //Чтение буфера ввода
//  memcpy(Arr, reader->bufrd, 24);
  FlagGetDate = false;
  for(int i = 0; i < 24; i++)
  {
    if(Arr[i] != 0)
    {
      FlagGetDate = true;
      ImageList1->Draw(Image8->Canvas,0,0,2,true);
//      Panel9->Visible = false; ///отутствии сигнала
      TikCount = 0;
      break;
    }
  }
  BYTE B = reader->bufrd[0];
//  Edit22->Text = AnsiString(B);       //Deleting
//  Edit25->Text = reader->Count;       //Deleting
/*
  if(FlagGetDate == false)  //нет данных в данном тике
  {
    if(TikCount > 3)
    {
      Application->ProcessMessages();
      ImageList1->Draw(Image8->Canvas,0,0,3,true);
      FlagGetDate = false;
      TikCount = 0;
      return;
    }
    else return;
  }
*/
  TikCount = 0;
  memcpy(&DateFP, reader->bufrd, sizeof(DateFP));
//  Label500->Caption = (AnsiString)DateFP.CommonImp + " " + (AnsiString)DateFP.ControlImp;
  memset(reader->bufrd, 0, 24);

  if(!Calculation)
  {
//    if(QminRadioButton->Checked) NumCodeProv = 0;   //NumCodeProv уже установлены
//    if(QmidRadioButton->Checked) NumCodeProv = 1;
//    if(QmaxRadioButton->Checked) NumCodeProv = 2;
  }
/*
  if(Calculation) // Получение информации от изметительного    прибора
  {
    //Анализ полученного кода
    //Если есть ошибки, то выход из проверки с выдасей на экран и сбросом проверки.
    //если не завершение, то Показать Q  b T
    //если Завершение то плучение Фото 2 и выход
  }
  else  //Холостой ход и настройка потока
  {
    //Анализ полученного кода
    //Если есть ошибки - выдать сообщение
    //Управление кнопкой мерцания
  }
*/
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::SpeedButton1Click(TObject *Sender)
{
  if(SpeedButton1->Down)
  {
    ReadFlag = true;
    RBDisabling();
    ReadWideo2();
  }
  else
  {
    ReadFlag = false;
    RBEnabling();
    Image1->Picture->CleanupInstance();
  }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::ClearPanelClick(TObject *Sender)
{
    writer = new TThreadWriter(true, COMportRd, "0");
//    writer->Execute();
    delete writer;
}
//---------------------------------------------------------------------------








void __fastcall TMainForm::NastrojkaClick(TObject *Sender)
{
  SetParForm = new TSetParForm(this, DM);
  if(SetParForm->ShowModal() == ID_OK)
  {



  }
  delete SetParForm;
}
//---------------------------------------------------------------------------

