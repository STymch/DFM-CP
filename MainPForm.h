//---------------------------------------------------------------------------

#ifndef MainPFormH
#define MainPFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include "DataModule.h"
#include "OpAudit.h"
#include "Defines.h"
#include "DataModule.h"
#include "Unit2.h"
#include "Tools_proc.h"
#include <Registry.hpp>
#include "Unit3.h"
#include "cxGridCustomTableView.hpp"
#include <DB.hpp>
#include <math.h>
#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include "ReadTread.h"
#include "WriteTread.h"
#include <Mask.hpp>
#include <vfw.h>           // VfW.H - Video for windows include file for WIN32
#include <Graphics.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <Registry.hpp>
#include <Buttons.hpp>
#include <ImgList.hpp>
#include "_GClass.hpp"
#include "AbRMeter.hpp"
#include "AbDBCtrls.hpp"
#include <jpeg.hpp>
#include <Menus.hpp>
#include <deque>
#include <vfw.h>
#include <Windows.h>
#include <Messages.hpp>
#include "DefWinMessage.h"
#include "Unit1.h"
#include <DateUtils.hpp>
#include <SyncObjs.hpp>
#include "ParamsN.h"
#include "mSetParams.h"

#include <windows.h>
#include <tlhelp32.h>
//---------------------------------------------------------------------------
class TMainKPSForm : public TForm
{
__published:	// IDE-managed Components
        TGroupBox *GroupBox1;
        TLabel *Label34;
        TLabel *Label37;
        TLabel *Label38;
        TLabel *Label40;
        TLabel *Label41;
        TGroupBox *GroupBox2;
        TLabel *Label42;
        TLabel *Label43;
        TGroupBox *GroupBox18;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *Label60;
        TLabel *Label68;
        TLabel *Label72;
        TLabel *Label4;
        TLabel *Label5;
        TLabel *Label6;
        TLabel *Label7;
        TLabel *Label8;
        TLabel *Label9;
        TLabel *Label10;
        TLabel *Label33;
        TLabel *Label46;
        TLabel *Label15;
        TLabel *Label16;
        TLabel *Label17;
        TLabel *Label26;
        TLabel *Label27;
        TLabel *Label18;
        TLabel *Label20;
        TLabel *Label28;
        TLabel *Label29;
        TRadioButton *QminRb;
        TRadioButton *QtRb;
        TRadioButton *QnomRb;
        TEdit *Edit21;
        TEdit *Edit22;
        TEdit *Edit23;
        TEdit *Edit1;
        TEdit *Edit2;
        TEdit *Edit3;
        TPanel *StartProlivBtn;
        TPanel *ClearPanel;
        TPanel *Parameters;
        TPanel *Abonent;
        TPanel *Panel1;
        TPanel *OtchetPanel;
        TImage *CamerImage;
        TLabel *Label61;
        TImage *ComPortImage;
        TLabel *Label53;
        TImage *PriborImage;
        TLabel *Label101;
        TImage *Image5;
        TLabel *Bat;
        TImage *Image6;
        TLabel *Temp;
        TLabel *Knopka;
        TImageList *ImageList1;
        TTimer *Timer1;
        TPanel *Nastrojka;
        TLabel *Label19;
        TLabel *Label1;
        TLabel *Label11;
        TLabel *Label21;
        TLabel *Label22;
        TLabel *Label23;
        TLabel *Label30;
        TPanel *OperatorsP;
        TPanel *Panel2;
        TImage *Image1;
        TAbDB270Meter *AbDB270Meter1;
        TPanel *SvjazSetting;
        TLabel *Label44;
        TStatusBar *StatusBar1;
        TLabel *Label31;
        TLabel *Label32;
        TProgressBar *ProgressBar1;
        TLabel *Label36;
        TLabel *Label39;
        TLabel *Label45;
        TLabel *Label47;
        TLabel *Label48;
        TLabel *Label49;
        TLabel *Label50;
        TLabel *Label51;
        TLabel *Label52;
        TGroupBox *GroupBox3;
        TRadioButton *HandStartBtn;
        TRadioButton *AvtomatStartBtn;
        TRadioButton *TickTestBtn;
        TSpeedButton *PhotoSB;
        TImage *Image2;
        TLabel *Label12;
        TImage *Image3;
        TLabel *Label13;
        TPanel *Panel3;
        TLabel *Label14;
        TLabel *Label24;
        TLabel *Label25;
        TLabel *Label54;
        TLabel *Label55;
        TLabel *Label56;
        TLabel *Label57;
        TLabel *Label35;
        TPanel *Panel4;
        TImage *Image7;
        TPopupMenu *PopupMenu1;
        TMenuItem *BegCommStart1;
        TMenuItem *BegCadrStart1;
        TMenuItem *EndCommStop1;
        TMenuItem *EndCadrStop1;
        void __fastcall NastrojkaClick(TObject *Sender);
        void __fastcall ParametersClick(TObject *Sender);
        void __fastcall AbonentClick(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall StartProlivBtnClick(TObject *Sender);
        void __fastcall ResultPanelClick(TObject *Sender);
        void __fastcall ClearPanelClick(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall OtchetPanelClick(TObject *Sender);
        void __fastcall QminRbClick(TObject *Sender);
        void __fastcall QtRbClick(TObject *Sender);
        void __fastcall QnomRbClick(TObject *Sender);
        void __fastcall Image1Click(TObject *Sender);
        void __fastcall SvjazSettingClick(TObject *Sender);
        void __fastcall PhotoSBClick(TObject *Sender);
        void __fastcall HandStartBtnClick(TObject *Sender);
        void __fastcall AvtomatStartBtnClick(TObject *Sender);
        void __fastcall TickTestBtnClick(TObject *Sender);
        void __fastcall Panel4Click(TObject *Sender);
        void __fastcall FormDestroy(TObject *Sender);
        void __fastcall OperatorsPClick(TObject *Sender);
        void __fastcall PopupMenu1Popup(TObject *Sender);
//        void __fastcall SpeedButton2Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TMainKPSForm(TComponent* Owner);
        void __fastcall OpDispClick(TObject *Sender);
//        void __fastcall SaveParamsClick(TObject *Sender);
        void __fastcall AnswerEvent(TMessage& Msg);
private:	// User declarations
protected:  // User declarations
protected:
  BEGIN_MESSAGE_MAP
    MESSAGE_HANDLER(WM_PROGRESS, TMessage, AnswerEvent)        // WM_COPYDATA
  END_MESSAGE_MAP(TForm)
public:		// User declarations
        __fastcall TMainForm(TComponent* Owner);
        bool __fastcall ComparePar(void);
//   void __fastcall FeelOperatorsTable(void);
//   void __fastcall FeelGroupsTable(void);
//   void __fastcall PassShow(void);
//   void __fastcall FeelGroupsTable(void);
  bool             CameraWorking(void);
//  AnsiString       CreateDBSQLGet(AnsiString DBName);
  bool             PassShow(void);
  void             FeelOperatorsTable(void);
  void             FeelGroupsTable(void);
  bool             ComPortOpen(void);
  void             RdCOMClose();
//  void __fastcall  SendIntoPort(AnsiString S);
//  bool             ReadVideo(void); //bool SaveFile, AnsiString FileNameB, AnsiString FileNameE);
  void             EtapeCalculate(float BegValue, float EntValue);
  void             WorkWSReestr(void);
  void             WriteIntoReestr(void);
  void             WriteIntoReestrEdited(void);
  void             ReadFromReestr(void);
  void             ReadFromReestrToChange(void);
  void             RBDisabling(void);
  void             RBEnabling(void);
  void             SetPanelsColors(void);
  void             KommandIntoIS(int Code);
  void             ShowWorkCamer(void);
  void             DelComPortAndReader(void);
  void             DisabledQSelection(void);
  void             EnabledQSelection(void);
  void             ShowCalculation(void);
  void             ShowHideLabels(bool TF);
  void             ConvertPhotoToCode64(AnsiString FName);
  void             GettingPhotoWPlomb(void);
  void             TestVideo(void);
  void             TestVideo1(void);
  void             ShowProliv(void);
  void             ShowProliv4(void);
  void             Start_Stop(void);
  void             Stop_Start(void);
  TStringList     *pListDir;
  TRegIniFile     *Reg;
  AnsiString      DBName;
  AnsiString      OldOpName;    //Текущий оператор
  AnsiString      InputBuffer;  //bufer vvjlf simvolov
  TDateTime       ContrDT;
  HANDLE          ComPort;
//  HANDLE          COMportWr;
  int             handle;         //File handle
  TThreadWriter   *writer;
  TThreadReader   *reader;
  unsigned char   bufwr[256];
  OVERLAPPED      overlapped; //????? ???????????? ??? ???????? ?????? (??. ????? ReadThread)
//  OVERLAPPED      overlappedwr; //????? ???????????? ??? ???????? ?????? (??. ????? WriteThread)
//  bool            ReadCadrsFlag;         //Признак продолжения видео
  bool            CamerConectFlag;  //Признак bключенной камеры
  int             CamerNUM;              //Номер камеры
  bool            FlagProliva;      //Flag того что идет пролив   и до ввода параметров из фото
//       Основные параметры расчета
  bool            EndCalcMin;   //Признак завершения пролива Минимального
  bool            EndCalcT;     //Признак завершения пролива промежуточного
  bool            EndCalcN;     //Признак завершения пролива номинального
  bool            BegCalcMin;   //Признак  пролива Минимального
  bool            BegCalcT;     //Признак  пролива промежуточного
  bool            BegCalcN;     //Признак  пролива номинального
  int             NumCodeProv;  //Номер текущей проверки
  AnsiString      FirmName;    //Начвание фирмы
//  AnsiString      Dir;          //Директория программы
  float          MinRashPrib, MidRashPrib, MaxRashPrib;  //Значения проливов, полученные от Прибора проверки

  float          MinBegSCH, MidBegSCH, MaxBegSCH;  //Начальные значения счетчиков 3-х проливов
  float          MinEndSCH, MidEndSCH, MaxEndSCH;  //Конечные значения счетчиков 3-х проливов

  float          MinDelta,  MidDelta,  MaxDelta;   //Разность значений счетчиков конечного и начального

  float          MinEtalon, MidEtalon, MaxEtalon;  //Эталонные значения пролива

  double          MinPerc,   MidPerc,   MaxPerc;    //Расхождение в процентах
  float          QminCurProliv;                             //min Q proliv
  float          QmaxCurProliv;                             //max Q proliv
  int            ReadedCount;                      //kol-vo prinjanix simvolov
  int            WaitCount;                        //kol-vo ozidaemix simvolov
  bool           FlagGetDate;                      //Флаг получения данных в тике
  bool           ComPortFlag;                      //Флаг работы порта
  bool           CamerWorkingFlag;
  BYTE           BuffOut[20];                      //Буфер Выдачи команды
  BYTE           *pBuffOut;
  int            BuffOutLen;                       //
  BYTE           BuffOut2[20];                     //Буфер последней команды
  BYTE           *pBuffOut2;
  int            BuffOut2Len;                      //
  AnsiString     ComportName;
  int            ProgramState;                    //0-начальное 1 - ожидание 2 - пролив 3- контроль тиков
  BYTE           BufferVVODA[40];
  int            CurCountValue;                   //Текущее состояние счетчика
  int            ForCurCountValue;                //Предыдущее состояние счетчика
  TDateTime      CurTime;                         //Время Текущего состояние счетчика
  TDateTime      ForCurTime;                       //Время Предыдущего состояние счетчика
  TDateTime      DTAnswer;
  TCursor        SaveCursor;
  bool           FlagVvodaSubscr;         //флаг -абонент и прибор введен в обработку
  bool           FlagVvodaParamsProliv;   //Флаг того, что введены параметры пролива
  TCriticalSection *csSendToPort;
  HWND           hWndC;
//  bool           RestartFlag;
  int            TimerTickCount;        //тики таймера
  int            Flag_Q_Control_Off;    //Тестовый флаг для отключения контроля на Скорость пролива
  int            MaxProlivCountValue;    //Счетчик пролива исходный
  bool            FlagTickControl;       //0 - просто пролив, 1 - контроль тиков при проливе и режим 3
  int            BeginTickCountValue;
  TDateTime      StartTime;
  TDateTime      StopTime;
  TDateTime      StopVTime;
  TDateTime      StartVTime;
  double         Q0, Q1, Q2;
  double         QSA;
  int            Vertuschka;
  bool           FlagBegProliva;         //Flag начала и всего пролива
  bool           FlagEndProliva;         //Flag конца пролива
  bool           FlagTestVideo;          //Flag Тестирования видео
  bool           FlagPhotoPlomb;           //Flag фото с пломбой
  AnsiString     FNameB;                 //Photo File Name Behin
  AnsiString     FNameE;                 //Photo File Name End
  int            CountCadr;
//  int            TicNullCount;
  bool           PhotoVideoFlag;
  bool           FlagEndTestWideo;
  bool           AvtomatStartFlag;
  int            MaxUValue;             //Мах. значение напряжения батареи
  int            MinUValue;             //Мин. значение напряжения батареи
  int            HavUValue;             //Авар. значение напряжения батареи
  int            BegTicCount;          // Нач.значения счетчика для контроля ИС
  int            CountRecivedAnswer;   // Число полученных от ИС пакетов
  double         SummOF_Q_Proliva;       //Cумма всех Q пролива
  double         TempratBegProliv;     //Температура начала пролива
  double         TempratEndProliv;     //Температура конца пролива
  bool           FlagRead_T_After_Proliv;
  bool           StartProlivBtnState;
  double         QSredneeProliva;
  int            TimeOfProliv;
  bool           FlagStartAvtomat;
  bool           FlagCiklaAvtomata;    //Для сброса бесконечного цикла
  int            StartStopExt;         //Flag внешнего zapuska kontrolja
  int            QMA;                  //Флаг скользящего Q
  double         dVImp;                //cislo imp zadano
  int            UpdateScreen;         //Число выдачь на шкалу
  int            IntPaketCount;        //Счетчик пакетов
  int            FlagVideo;            //Признак отсутствия видео при автомате
  bool           PriborImageState;     //Состояние прибора зеленый=истина
  int            PhotoPrio;            // 1 - Сначала фото, затем командв, 0 наоборот
  AnsiString     BODA;                 // Признак воды = горячая "Г", или холодная "Х"
  AnsiString     BaseName;                 // Поле в таблицах парадокса
  AnsiString     FullFileName;        //Имя файла с путем
//
};
//---------------------------------------------------------------------------
extern PACKAGE TMainKPSForm *MainKPSForm;
//---------------------------------------------------------------------------
#endif
