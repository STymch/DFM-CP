//---------------------------------------------------------------------------
#ifndef Tools_procH
#define Tools_procH
#include <Graphics.hpp>
#include <Inifiles.hpp>
#include <stdio.h>
#include <time.h>
//#include "BrowseFolderDialog.h"

// - специальна€ манипул€ци€ битами в DWORD
#define LOBITSDW( dw )   (DWORD)( DWORD(dw)     & 0x1FFFFFFFL ) /* Low 29 bit */
#define HIBITSDW( dw )   (int)(( DWORD(dw)>>29 )& 0x00000007L ) /* High 3 bit */
//---------------------------------------------------------------------------

#define MAKEDWORD(HiByteHiWord,LoByteHiWord,HiByteLoWord,LoByteLoWord) \
  (HiByteHiWord<<24 | LoByteHiWord<<16 | HiByteLoWord<<8 | LoByteLoWord)
#define MAKEDW_VERSION(MajorVer,MinorVer,Release,Build) \
  (Build<<24 | Release<<16 | MinorVer<<8 | MajorVer)
#define POINTER_TO_STR(ptr)     ("0x"+IntToHex((__int64)ptr,8))
#define THIS_TO_STR     POINTER_TO_STR(this)
//---------------------------------------------------------------------------
extern PACKAGE AnsiString RunExePath;
extern PACKAGE AnsiString ExeName;
extern PACKAGE AnsiString  AutoStartPluginPathName;
extern PACKAGE DWORD g_dwIP_App;
extern PACKAGE const char *RegKey;
extern PACKAGE const char *ch_Delimiter;

class PACKAGE LParams {                 //PACKAGE
private:
    char        delimiter;
public:
  int      nParams;
  TStringList  *pList;
  AnsiString  Comment;
public:
  __fastcall LParams(void);
    __fastcall LParams(const LParams& copy);
    __fastcall ~LParams(void);
  void __fastcall operator = (const LParams& copy);

    void        __fastcall Clear(void);
    void        __fastcall Add(AnsiString szStr);
    void        __fastcall SetDelimiter(char s);
//‘ункци€ Separate(AnsiString szStr) раздел€ет входную строку на подстроки,
//отдел€емые разделител€ми и помещает их в список pList и возвращает число подстрок.
// омметарий помещает в строку Comment
  int         __fastcall Separate(AnsiString szStr);
// ѕреобразовывает список в одну длинную строку, разделенную разделител€ми и
// в конец добавл€ет комментарий.
  AnsiString  __fastcall MakeString(void);

    int      __fastcall AsInt(int nStr,int iDefault=0);
    DWORD     __fastcall AsHex(int nStr,DWORD dwDefault=0);
    AnsiString  __fastcall AsStr(int nStr,AnsiString sDefault="");
    DWORD     __fastcall AsDef(int nStr,DWORD dwDefault=0);
    TColor      __fastcall AsColor(int nStr,TColor clDefault=clNone);
    double    __fastcall AsFloat(int nStr,double dbDefault=0);
    TDateTime    __fastcall AsDateTime(int nStr,TDateTime tdDefault=0);
           };

//---------------------------------------------------------------------------
class PACKAGE LProfile {        //PACKAGE
private:
  LParams     pParams;
  AnsiString  FileName;
public:
  TIniFile  *pIni;
public:
  __fastcall LProfile(void);
  __fastcall LProfile(AnsiString sProfileName);
    __fastcall ~LProfile(void);
    bool        __fastcall SectionExists(const AnsiString Section);
    bool        __fastcall ValueExists(const AnsiString Section, const AnsiString Ident);
    int         __fastcall ReadInteger(const AnsiString Section, const AnsiString Ident, int Default);
    LParams     __fastcall LoadParameter(AnsiString Section, AnsiString Key, AnsiString Default);
    LParams *   __fastcall GetValue(void);
    int         __fastcall GetCount(void) { return pParams.nParams; };
    AnsiString  __fastcall GetFileName(void) {return FileName;};
    void        __fastcall WriteInteger(const AnsiString Section, const AnsiString Ident, int Value);
    void        __fastcall StoreParameter(AnsiString Section, AnsiString Key, AnsiString Value);
};

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
extern DWORD      __fastcall PACKAGE PhoneStringToDword(char *ptr);
extern char *     __fastcall PACKAGE PhoneDwordToString(DWORD Number);
extern AnsiString __fastcall PACKAGE PhoneDwToAnsiStr(DWORD Number);
extern AnsiString   __fastcall PACKAGE PhoneDw2Str(DWORD Number);
extern DWORD     __fastcall PACKAGE PhoneStr2Dw(AnsiString szPhone);
extern AnsiString   __fastcall PACKAGE ColorToStr(TColor eColor);

//extern TDateTime   __fastcall PACKAGE ConvertTime(long dt, int nHour=0);
extern WORD         __fastcall PACKAGE UpdateCRC(BYTE c, WORD crc);
extern WORD         __fastcall PACKAGE CalculateCRC(BYTE *pData, int data_len);
extern WORD         __fastcall PACKAGE CRC_Forward(BYTE *pData, int data_len);
extern WORD         __fastcall PACKAGE CRC_Backward(BYTE *pData, int data_len);
extern DWORD        __fastcall PACKAGE crc32(DWORD crc, BYTE *buf, WORD len);

extern char *       __fastcall PACKAGE inet_n2a(DWORD ip_addr);

extern DWORD        __fastcall PACKAGE PackPhoneNumber(char *Str);
extern AnsiString   __fastcall PACKAGE UnPackPhoneNumber(DWORD dwPhone);

extern AnsiString   __fastcall PACKAGE OldCmdToString(BYTE bCommand, BYTE bObject, BYTE bRange);
extern AnsiString   __fastcall PACKAGE la_GetVersion(AnsiString ModuleName);
extern AnsiString   __fastcall PACKAGE GetVersion(char *ModuleName);
extern AnsiString   __fastcall PACKAGE GetVersion(AnsiString ModuleName);

//ф-€ из масива формирует из не нулевых элементов список
//ѕример:
//  1) при значени€х Delim1 и Delim2 по умолчанию
//        индекс-0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21
//        масив: 0,0,0,1,0,1,0,0,0,1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 1 -> список:"3,5,9,11-15,19,21"
//  2) при значени€х Delim1 = "&" и Delim2 = "&&"
//        индекс-0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21
//        масив: 0,0,0,1,0,1,0,0,0,1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 1 -> список:"3&5&9&11&&15&19&21"
extern AnsiString   __fastcall PACKAGE buildStr(BYTE *Buf, WORD maxNum,
  AnsiString Delim1=",", AnsiString Delim2="-", DWORD dwMaxCountInt = -1, BYTE **ppCurPos=NULL);
extern void         __fastcall PACKAGE restoreStr(AnsiString szSource, BYTE *Buf, WORD maxNum, BYTE mbFill);
extern char *       __fastcall PACKAGE ByteToBinary(DWORD Value, int Len);
extern AnsiString   __fastcall PACKAGE SlashSep(AnsiString Path, AnsiString S);
extern BOOL         __fastcall PACKAGE OpenTheFile(HWND hWnd, AnsiString &FileName, int &iDelimiter );
extern void         __fastcall CenterWindow(HWND hWnd);
//extern bool         __fastcall PACKAGE ShowQuestion(const AnsiString &S, HWND hParent=NULL);
extern void         __fastcall PACKAGE ShowError(const AnsiString &S, HWND hParent=NULL);
extern void         __fastcall PACKAGE ShowWarning(const AnsiString &S, HWND hParent=NULL);
extern void         __fastcall PACKAGE ShowInformation(const AnsiString &S, HWND hParent=NULL);
//extern bool         __fastcall PACKAGE ShowQuestion(const AnsiString &S,
//                                  bool &bYesAll, bool &bNoAll, bool &bCancel, HWND hParent=NULL);
//extern bool         __fastcall PACKAGE ShowQuestion(const AnsiString &S, bool &bCancel, HWND hParent=NULL);
//extern TDateTime    __fastcall PACKAGE time_tToDateTime(time_t AValue);
//extern time_t       __fastcall PACKAGE DateTimeTotime_t(TDateTime AValue);
extern AnsiString __fastcall PACKAGE DeltaDateTimeToStr(TDateTime ANow, TDateTime AThen);

#define OS_WIN32_95    0
#define OS_WIN32_98    1
#define OS_WIN32_ME    2
#define OS_WIN32_NT351 3
#define OS_WIN32_NT4   4
#define OS_WIN32_2000  5
#define OS_WIN32_XP    6
#define OS_WIN32_NET   7


extern int __fastcall PACKAGE GetOperatingSystem();
extern void PACKAGE ProcessMessages();
extern TDateTime PACKAGE MSecsToDateTime(__int64 nTime);
extern AnsiString PACKAGE TimeMillisecAsStr(__int64 nTime);
extern AnsiString PACKAGE DelPhoneDelim(const AnsiString &Str);
extern bool PACKAGE LongPhoneStr2DwordArray(const AnsiString &szPhone, DWORD *pdwNumBuff , BYTE n );
extern bool PACKAGE AddDigit( BYTE digit , DWORD *pdwNumBuff , BYTE n );

struct SLoginPassData
{
  DWORD RndData1[5];
  DWORD nLogin;
  DWORD nPass;
  DWORD RndData2[5];
  char szLogin[256];
  DWORD RndData3[5];
  char szPass[256];
  DWORD RndData4[5];
};

const int SIZE_LOGIN_PASS_DATA = sizeof(SLoginPassData);
extern bool PACKAGE WriteLogPass(char *szLogin, char *szPass, HKEY RootKey=HKEY_LOCAL_MACHINE);
extern bool PACKAGE ReadLogPass(SLoginPassData *pLPData, HKEY RootKey=HKEY_LOCAL_MACHINE);
//---------------------------------------------------------------------------
#endif
