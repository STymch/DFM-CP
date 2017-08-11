//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
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
#include <deque>
#include <vfw.h>
#include <Windows.h>
#include <Messages.hpp>
#include "DefWinMessage.h"

//---------------------------------------------------------------------------
using namespace std;
//---------------------------------------------------------------------------
/*
struct DiametrVn
{
public:		// User declarations
   int Diametr;
   double Qn;
   double DQn;
   double DQt;
   double DQmin;
   double Vn;
   double Vt;
   double Vmin;
};
struct ClassQ
{
public:		// User declarations
  char  Name[4];
  double Qmin;
  double Qt;
};
struct ClassT
{
public:		// User declarations
  char  Name[4];
  double Tmin;
  double Tmax;
  double DminL;
  double DminR;
  double DtL;
  double DtR;
  double DnL;
  double DnR;
};
*/
struct Params
{
public:		// User declarations
  int     INDL;
  int     IND;
  char    PortNum[16];
  char    OpNameL[24];
  int     PortSpeed;
  int     TimeOut;
  char    Camer[64];
  float   MinRash;
  float   MidRash;
  float   MaxRash;
  float   MinLDop;
  float   MinRDop;
  float   MidLDop;
  float   MidRDop;
  float   MaxLDop;
  float   MaxRDop;
  float   MinV;
  float   MidV;
  float   MaxV;
  TDateTime DP;
};
struct InfoLaunch
{
  AnsiString          str_Profile;
  LONG                long_AppIP;
  DWORD               dw_User;
};
struct DateFromPribor
{
  BYTE  State;
  float Grads;
  float Volts;
  int   ImpPerSec;
  DWORD CommonImp;
  DWORD ControlImp;
};
class TMainForm : public TForm
{
__published:	// IDE-managed Components        //unsigned  int
        TPageControl *PageControl1;
        TTabSheet *TabSheet1;
        TTabSheet *TabSheet2;
        TTabSheet *TabSheet3;
        TTabSheet *TabSheet4;
        TTabSheet *TabSheet6;
        TPanel *Panel1;
        TImage *Image1;
        TGroupBox *GroupBox1;
        TGroupBox *GroupBox2;
        TTimer *Timer1;
        TLabel *Label11;
        TLabel *Label31;
        TLabel *Label32;
        TLabel *Label34;
        TLabel *Label35;
        TLabel *Label36;
        TLabel *Label37;
        TLabel *Label38;
        TLabel *Label39;
        TLabel *Label40;
        TLabel *Label41;
        TLabel *Label42;
        TLabel *Label43;
        TGroupBox *GroupBox3;
        TLabel *Label1;
        TComboBox *ComboBox1;
        TLabel *Label44;
        TLabel *Label45;
        TComboBox *ComboBox2;
        TEdit *Edit7;
        TPanel *Panel4;
        TPanel *Panel5;
        TPanel *Panel2;
        TPanel *StartBtn;
        TPanel *ClearPanel;
        TGroupBox *GroupBox4;
        TGroupBox *GroupBox5;
        TLabel *Label47;
        TLabel *Label48;
        TLabel *Label49;
        TEdit *Edit8;
        TEdit *Edit9;
        TEdit *Edit10;
        TEdit *Edit11;
        TEdit *Edit12;
        TEdit *Edit13;
        TEdit *Edit14;
        TEdit *Edit15;
        TEdit *Edit16;
        TEdit *Edit17;
        TEdit *Edit18;
        TEdit *Edit19;
        TLabel *Label50;
        TLabel *Label51;
        TLabel *Label52;
        TPanel *ResultPanel;
        TPanel *OpDisp;
        TPanel *Panel10;
        TGroupBox *GroupBox6;
        TLabel *Label57;
        TEdit *TaunEdit;
        TLabel *Label58;
        TEdit *StreetEdit;
        TLabel *Label59;
        TEdit *HausEdit;
        TLabel *Label63;
        TEdit *KorpEdit;
        TLabel *Label64;
        TEdit *BitEdit;
        TGroupBox *GroupBox7;
        TLabel *Label65;
        TEdit *SurNameEdit;
        TLabel *Label66;
        TLabel *Label67;
        TGroupBox *GroupBox8;
        TLabel *Label54;
        TEdit *Edit20;
        TLabel *Label56;
        TDateTimePicker *DateTimePicker1;
        TEdit *NameEdit;
        TEdit *FNameEdit;
        TGroupBox *GroupBox9;
        TEdit *ResultEdit;
        TButton *Button1;
        TPanel *SaveIntoBase;
        TLabel *Label69;
        TEdit *TypeEdit;
        TDBGrid *DBGrid1;
        TEdit *Edit24;
        TLabel *Label55;
        TLabel *Label70;
        TLabel *Label71;
        TEdit *Edit27;
        TLabel *Label73;
        TLabel *Label74;
        TTabSheet *TabSheet5;
        TGroupBox *GroupBox10;
        TLabel *Label75;
        TLabel *Label76;
        TEdit *d8;
        TEdit *Qn8;
        TEdit *d10;
        TEdit *Qn10;
        TEdit *d15;
        TEdit *Qn15;
        TEdit *d20;
        TEdit *Qn20;
        TEdit *d25;
        TEdit *Qn25;
        TEdit *d32;
        TEdit *Qn32;
        TEdit *d40;
        TEdit *Qn40;
        TEdit *d50;
        TEdit *Qn50;
        TGroupBox *GroupBox11;
        TEdit *AQmin;
        TEdit *AQt;
        TEdit *BQmin;
        TEdit *BQt;
        TEdit *CQmin;
        TEdit *CQt;
        TLabel *Label77;
        TLabel *Label78;
        TLabel *Label79;
        TLabel *Label80;
        TLabel *Label81;
        TGroupBox *GroupBox12;
        TLabel *Label82;
        TLabel *Label83;
        TEdit *TminX;
        TEdit *TmaxX;
        TEdit *DminLX;
        TEdit *DminRX;
        TEdit *DtLX;
        TEdit *DtRX;
        TLabel *Label84;
        TLabel *Label85;
        TLabel *Label86;
        TLabel *Label87;
        TLabel *Label88;
        TLabel *Label89;
        TEdit *DnLX;
        TEdit *DnRX;
        TLabel *Label90;
        TLabel *Label91;
        TEdit *TminG;
        TEdit *TmaxG;
        TLabel *Label92;
        TLabel *Label93;
        TEdit *DminLG;
        TEdit *DminRG;
        TLabel *Label94;
        TLabel *Label95;
        TEdit *DtLG;
        TEdit *DtRG;
        TLabel *Label96;
        TLabel *Label97;
        TEdit *DnLG;
        TEdit *DnRG;
        TLabel *Label98;
        TLabel *Label99;
        TLabel *Label100;
        TGroupBox *GroupBox14;
        TLabel *Label104;
        TComboBox *ComboBox6;
        TEdit *Edit65;
        TButton *SaveParams;
        TLabel *Label62;
        TEdit *DQn50;
        TEdit *DQn8;
        TEdit *DQn10;
        TEdit *DQn15;
        TEdit *DQn20;
        TEdit *DQn25;
        TEdit *DQn32;
        TEdit *DQn40;
        TEdit *DQt50;
        TEdit *DQt8;
        TEdit *DQt10;
        TEdit *DQt15;
        TEdit *DQt20;
        TEdit *DQt25;
        TEdit *DQt32;
        TEdit *DQt40;
        TEdit *DQmin50;
        TEdit *DQmin8;
        TEdit *DQmin10;
        TEdit *DQmin15;
        TEdit *DQmin20;
        TEdit *DQmin25;
        TEdit *DQmin32;
        TEdit *DQmin40;
        TLabel *Label108;
        TLabel *Label109;
        TLabel *Label110;
        TEdit *Vn8;
        TEdit *Vn10;
        TEdit *Vn15;
        TEdit *Vn20;
        TEdit *Vn25;
        TEdit *Vn32;
        TEdit *Vn40;
        TEdit *Vn50;
        TEdit *Vt8;
        TEdit *Vt10;
        TEdit *Vt15;
        TEdit *Vt20;
        TEdit *Vt25;
        TEdit *Vt32;
        TEdit *Vt40;
        TEdit *Vt50;
        TEdit *Vmin8;
        TEdit *Vmin10;
        TEdit *Vmin15;
        TEdit *Vmin20;
        TEdit *Vmin25;
        TEdit *Vmin32;
        TEdit *Vmin40;
        TEdit *Vmin50;
        TLabel *Label111;
        TLabel *Label112;
        TLabel *Label113;
        TButton *Button3;
        TPanel *Panel6;
        TSpeedButton *SpeedButton1;
        TPanel *Panel11;
        TImageList *ImageList1;
        TImage *Image2;
        TLabel *Label53;
        TImage *Image3;
        TLabel *Label61;
        TLabel *Label101;
        TImage *Image5;
        TImage *Image6;
        TImage *Image7;
        TImage *Image8;
        TLabel *Bat;
        TLabel *Temp;
        TLabel *MaxQ;
        TLabel *MinQ;
        TImage *Image4;
        TPanel *Panel7;
        TGroupBox *GroupBox13;
        TRadioButton *RadioButton1;
        TRadioButton *RadioButton2;
        TGroupBox *GroupBox15;
        TRadioButton *RadioButton3;
        TRadioButton *RadioButton4;
        TRadioButton *RadioButton5;
        TGroupBox *GroupBox16;
        TRadioButton *RadioButton6;
        TRadioButton *RadioButton7;
        TGroupBox *GroupBox17;
        TRadioButton *RadioButton8;
        TRadioButton *RadioButton9;
        TRadioButton *RadioButton10;
        TRadioButton *RadioButton11;
        TRadioButton *RadioButton12;
        TRadioButton *RadioButton13;
        TRadioButton *RadioButton14;
        TRadioButton *RadioButton15;
        TGroupBox *GroupBox18;
        TRadioButton *QtRb;
        TRadioButton *QnomRb;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *Label60;
        TLabel *Label68;
        TLabel *Label72;
        TLabel *Label4;
        TLabel *Label5;
        TEdit *Edit21;
        TEdit *Edit22;
        TEdit *Edit23;
        TLabel *Label6;
        TLabel *Label7;
        TEdit *Edit1;
        TEdit *Edit2;
        TEdit *Edit3;
        TLabel *Label8;
        TLabel *Label9;
        TLabel *Label10;
        TLabel *Label33;
        TLabel *Label46;
        TLabel *Label12;
        TLabel *Label13;
        TLabel *Label14;
        TLabel *Label24;
        TLabel *Label25;
        TLabel *Label15;
        TLabel *Label16;
        TLabel *Label17;
        TLabel *Label26;
        TLabel *Label27;
        TLabel *Label18;
        TLabel *Label20;
        TLabel *Label28;
        TLabel *Label29;
        TPanel *Nastrojka;
        TPanel *Abonent;
        TPanel *Panel9;
        TRadioButton *QminRb;
        TPanel *Panel3;
        void __fastcall OpDispClick(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall StartBtnClick(TObject *Sender);
        void __fastcall SaveIntoBaseClick(TObject *Sender);
        void __fastcall ResultPanelClick(TObject *Sender);
        void __fastcall SaveParamsClick(TObject *Sender);
        void __fastcall SelParamBtnClick(TObject *Sender);
        void __fastcall Button3Click(TObject *Sender);
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall SpeedButton1Click(TObject *Sender);
        void __fastcall ClearPanelClick(TObject *Sender);
        void __fastcall AnswerEvent(TMessage& Msg);
        void __fastcall NastrojkaClick(TObject *Sender);
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
  AnsiString       CreateDBSQLGet(AnsiString DBName);
  bool             PassShow(void);
  void             FeelOperatorsTable(void);
  void             FeelGroupsTable(void);
  bool             ComPortRdOpen(void);
  void             RdCOMClose();
  void             WrCOMClose();
  void __fastcall  SendIntoPort(AnsiString S);
  bool             FotoSave(AnsiString FileName);
  bool             ReadWideo2(void);
  void             EtapeCalculate(float BegValue, float EntValue);
  void             WorkWSReestr(void);
  void             WriteIntoReestr(void);
  void             ReadFromReestr(void);
  void             RBDisabling(void);
  void             RBEnabling(void);
  TStringList     *pListDir;
  TRegIniFile     *Reg;
  AnsiString      DBName;
  AnsiString      OldOpName;    //������� ��������
  AnsiString      InputBuffer;  //bufer vvjlf simvolov
  int             Priznak;
  TDateTime       ContrDT;
  HANDLE          COMportRd;
  HANDLE          COMportWr;
  int             handle;         //File handle
  TThreadWriter   *writer;
  TThreadReader   *reader;
  unsigned char   bufwr[256];
  OVERLAPPED      overlapped; //????? ???????????? ??? ???????? ?????? (??. ????? ReadThread)
  OVERLAPPED      overlappedwr; //????? ???????????? ??? ???????? ?????? (??. ????? WriteThread)
  bool            ReadFlag;
  bool            CamerConectFlag;
  int             NUM;
  bool            FlagCntr;
//  deque <DiametrVn> DiametrList;
//  deque <ClassQ>  ClassList;
//  deque <ClassT>  ClassTList;
//       �������� ��������� �������
  bool            EndCalcMin;   //������� ���������� ������� ������������
  bool            EndCalcT;     //������� ���������� ������� ��������������
  bool            EndCalcN;     //������� ���������� ������� ������������
  bool            BegCalcMin;   //�������  ������� ������������
  bool            BegCalcT;     //�������  ������� ��������������
  bool            BegCalcN;     //�������  ������� ������������
  bool            Calculation;  //���� ������
  int             NumCodeProv;
  AnsiString      FirmName;    //�������� �����
  float          MinRashPrib, MidRashPrib, MaxRashPrib;        //�������� ��������, ���������� �� ������� ��������

  float          MinBegSCH, MidBegSCH, MaxBegSCH;  //��������� �������� ��������� 3-� ��������
  float          MinEndSCH, MidEndSCH, MaxEndSCH;  //�������� �������� ��������� 3-� ��������

  float          MinDelta,  MidDelta,  MaxDelta;   //�������� �������� ��������� ��������� � ����������

  float          MinEtalon, MidEtalon, MaxEtalon;  //��������� �������� �������

  double          MinPerc,   MidPerc,   MaxPerc;    //����������� � ���������
/*
  float          Vmin,     Vt,       Vn;           //�������� ���������� �������  �����
  float          Qn;                               //�������� ������ ������� ������ � ���
  float          Qt;                               //�������� ������ ������� ������ � ���
  float          Qmin;                             //�������� ������ ������� ������ � ���
  float          DQnom;                               //������ �������� ������ ������� ������ � ���
  float          DQt;                               //������ ���������������� ������ ������� ������ � ���
  float          DQmin;                             //������ ���������������� ������ ������� ������ � ���
*/
  float          Tmin;                             //min T izmerenija
  float          Tmax;                             //max T izmerenija

  float          QminL, QminR;                     //������ � ����� ������� ���������� ���� ����������� �������� ������
  float          QtL,   QtR;                       //������ � ����� ������� ���������� ���� ����������� �������� ������
  float          QnomL,   QnomR;                       //������ � ����� ������� ���������� ���� ����������� �������� ������
  float          DminL, DminR;                     //���������� �������� �� ������� � ������ ������� �������
  float          DtL, DtR;                         //���������� �������� �� ������� � ������ ������� �������
  float          DnL, DnR;                         //���������� �������� �� ������� � ������ ������� �������
  int             TikCount;
  int             ReadedCount;                      //kol-vo prinjanix simvolov
  int             WaitCount;                        //kol-vo ozidaemix simvolov
  BYTE            Arr[24];                          //��������� ����� ����� ������
  bool            FlagGetDate;                        //���� ��������� ������ � ����
  bool            ComPortFlag;                      //���� ������ �����
  bool            FlagNePolhoyDlini;                //flag ne vsex dannix

  DateFromPribor  DateFP;
  char            BuffR[200];
//
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
