//---------------------------------------------------------------------------
#include <vcl.h>
#include <time.h>
#pragma hdrstop
#include "Tools_proc.h"
#include <DateUtils.hpp>
#include <Registry.hpp>
//#include "LocalTime.h"
//#include "QuestionDlg.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//#include "TraceLog.h"

AnsiString RunExePath;
AnsiString ExeName;
AnsiString  AutoStartPluginPathName = "";
DWORD g_dwIP_App;
const char *RegKey = "Software\\Sigma-t\\Pa";
const char *ch_Delimiter = ";,|\t";

typedef struct _MYDATA
{
  int  i_RetIndex;
  char **sz_cbItems;
} CBDATA, FAR * LPCBDATA;

UINT CALLBACK ComDlg32DlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);


char    ToneDigit[] = "~1234567890*#ABC........................";
AnsiString  aToneDigit  = "~1234567890*#ABC........................";

static WORD CRC16_Table[256] = {
        0x0000, 0x1021, 0x2042, 0x3063, 0x4084, 0x50a5, 0x60c6, 0x70e7,
        0x8108, 0x9129, 0xa14a, 0xb16b, 0xc18c, 0xd1ad, 0xe1ce, 0xf1ef,
        0x1231, 0x0210, 0x3273, 0x2252, 0x52b5, 0x4294, 0x72f7, 0x62d6,
        0x9339, 0x8318, 0xb37b, 0xa35a, 0xd3bd, 0xc39c, 0xf3ff, 0xe3de,
        0x2462, 0x3443, 0x0420, 0x1401, 0x64e6, 0x74c7, 0x44a4, 0x5485,
        0xa56a, 0xb54b, 0x8528, 0x9509, 0xe5ee, 0xf5cf, 0xc5ac, 0xd58d,
        0x3653, 0x2672, 0x1611, 0x0630, 0x76d7, 0x66f6, 0x5695, 0x46b4,
        0xb75b, 0xa77a, 0x9719, 0x8738, 0xf7df, 0xe7fe, 0xd79d, 0xc7bc,
        0x48c4, 0x58e5, 0x6886, 0x78a7, 0x0840, 0x1861, 0x2802, 0x3823,
        0xc9cc, 0xd9ed, 0xe98e, 0xf9af, 0x8948, 0x9969, 0xa90a, 0xb92b,
        0x5af5, 0x4ad4, 0x7ab7, 0x6a96, 0x1a71, 0x0a50, 0x3a33, 0x2a12,
        0xdbfd, 0xcbdc, 0xfbbf, 0xeb9e, 0x9b79, 0x8b58, 0xbb3b, 0xab1a,
        0x6ca6, 0x7c87, 0x4ce4, 0x5cc5, 0x2c22, 0x3c03, 0x0c60, 0x1c41,
        0xedae, 0xfd8f, 0xcdec, 0xddcd, 0xad2a, 0xbd0b, 0x8d68, 0x9d49,
        0x7e97, 0x6eb6, 0x5ed5, 0x4ef4, 0x3e13, 0x2e32, 0x1e51, 0x0e70,
        0xff9f, 0xefbe, 0xdfdd, 0xcffc, 0xbf1b, 0xaf3a, 0x9f59, 0x8f78,
        0x9188, 0x81a9, 0xb1ca, 0xa1eb, 0xd10c, 0xc12d, 0xf14e, 0xe16f,
        0x1080, 0x00a1, 0x30c2, 0x20e3, 0x5004, 0x4025, 0x7046, 0x6067,
        0x83b9, 0x9398, 0xa3fb, 0xb3da, 0xc33d, 0xd31c, 0xe37f, 0xf35e,
        0x02b1, 0x1290, 0x22f3, 0x32d2, 0x4235, 0x5214, 0x6277, 0x7256,
        0xb5ea, 0xa5cb, 0x95a8, 0x8589, 0xf56e, 0xe54f, 0xd52c, 0xc50d,
        0x34e2, 0x24c3, 0x14a0, 0x0481, 0x7466, 0x6447, 0x5424, 0x4405,
        0xa7db, 0xb7fa, 0x8799, 0x97b8, 0xe75f, 0xf77e, 0xc71d, 0xd73c,
        0x26d3, 0x36f2, 0x0691, 0x16b0, 0x6657, 0x7676, 0x4615, 0x5634,
        0xd94c, 0xc96d, 0xf90e, 0xe92f, 0x99c8, 0x89e9, 0xb98a, 0xa9ab,
        0x5844, 0x4865, 0x7806, 0x6827, 0x18c0, 0x08e1, 0x3882, 0x28a3,
        0xcb7d, 0xdb5c, 0xeb3f, 0xfb1e, 0x8bf9, 0x9bd8, 0xabbb, 0xbb9a,
        0x4a75, 0x5a54, 0x6a37, 0x7a16, 0x0af1, 0x1ad0, 0x2ab3, 0x3a92,
        0xfd2e, 0xed0f, 0xdd6c, 0xcd4d, 0xbdaa, 0xad8b, 0x9de8, 0x8dc9,
        0x7c26, 0x6c07, 0x5c64, 0x4c45, 0x3ca2, 0x2c83, 0x1ce0, 0x0cc1,
        0xef1f, 0xff3e, 0xcf5d, 0xdf7c, 0xaf9b, 0xbfba, 0x8fd9, 0x9ff8,
        0x6e17, 0x7e36, 0x4e55, 0x5e74, 0x2e93, 0x3eb2, 0x0ed1, 0x1ef0 };

//--------------------------------------------------------------------------
static DWORD CRC32_Table[256] = {
  0x00000000L, 0x77073096L, 0xee0e612cL, 0x990951baL, 0x076dc419L,
  0x706af48fL, 0xe963a535L, 0x9e6495a3L, 0x0edb8832L, 0x79dcb8a4L,
  0xe0d5e91eL, 0x97d2d988L, 0x09b64c2bL, 0x7eb17cbdL, 0xe7b82d07L,
  0x90bf1d91L, 0x1db71064L, 0x6ab020f2L, 0xf3b97148L, 0x84be41deL,
  0x1adad47dL, 0x6ddde4ebL, 0xf4d4b551L, 0x83d385c7L, 0x136c9856L,
  0x646ba8c0L, 0xfd62f97aL, 0x8a65c9ecL, 0x14015c4fL, 0x63066cd9L,
  0xfa0f3d63L, 0x8d080df5L, 0x3b6e20c8L, 0x4c69105eL, 0xd56041e4L,
  0xa2677172L, 0x3c03e4d1L, 0x4b04d447L, 0xd20d85fdL, 0xa50ab56bL,
  0x35b5a8faL, 0x42b2986cL, 0xdbbbc9d6L, 0xacbcf940L, 0x32d86ce3L,
  0x45df5c75L, 0xdcd60dcfL, 0xabd13d59L, 0x26d930acL, 0x51de003aL,
  0xc8d75180L, 0xbfd06116L, 0x21b4f4b5L, 0x56b3c423L, 0xcfba9599L,
  0xb8bda50fL, 0x2802b89eL, 0x5f058808L, 0xc60cd9b2L, 0xb10be924L,
  0x2f6f7c87L, 0x58684c11L, 0xc1611dabL, 0xb6662d3dL, 0x76dc4190L,
  0x01db7106L, 0x98d220bcL, 0xefd5102aL, 0x71b18589L, 0x06b6b51fL,
  0x9fbfe4a5L, 0xe8b8d433L, 0x7807c9a2L, 0x0f00f934L, 0x9609a88eL,
  0xe10e9818L, 0x7f6a0dbbL, 0x086d3d2dL, 0x91646c97L, 0xe6635c01L,
  0x6b6b51f4L, 0x1c6c6162L, 0x856530d8L, 0xf262004eL, 0x6c0695edL,
  0x1b01a57bL, 0x8208f4c1L, 0xf50fc457L, 0x65b0d9c6L, 0x12b7e950L,
  0x8bbeb8eaL, 0xfcb9887cL, 0x62dd1ddfL, 0x15da2d49L, 0x8cd37cf3L,
  0xfbd44c65L, 0x4db26158L, 0x3ab551ceL, 0xa3bc0074L, 0xd4bb30e2L,
  0x4adfa541L, 0x3dd895d7L, 0xa4d1c46dL, 0xd3d6f4fbL, 0x4369e96aL,
  0x346ed9fcL, 0xad678846L, 0xda60b8d0L, 0x44042d73L, 0x33031de5L,
  0xaa0a4c5fL, 0xdd0d7cc9L, 0x5005713cL, 0x270241aaL, 0xbe0b1010L,
  0xc90c2086L, 0x5768b525L, 0x206f85b3L, 0xb966d409L, 0xce61e49fL,
  0x5edef90eL, 0x29d9c998L, 0xb0d09822L, 0xc7d7a8b4L, 0x59b33d17L,
  0x2eb40d81L, 0xb7bd5c3bL, 0xc0ba6cadL, 0xedb88320L, 0x9abfb3b6L,
  0x03b6e20cL, 0x74b1d29aL, 0xead54739L, 0x9dd277afL, 0x04db2615L,
  0x73dc1683L, 0xe3630b12L, 0x94643b84L, 0x0d6d6a3eL, 0x7a6a5aa8L,
  0xe40ecf0bL, 0x9309ff9dL, 0x0a00ae27L, 0x7d079eb1L, 0xf00f9344L,
  0x8708a3d2L, 0x1e01f268L, 0x6906c2feL, 0xf762575dL, 0x806567cbL,
  0x196c3671L, 0x6e6b06e7L, 0xfed41b76L, 0x89d32be0L, 0x10da7a5aL,
  0x67dd4accL, 0xf9b9df6fL, 0x8ebeeff9L, 0x17b7be43L, 0x60b08ed5L,
  0xd6d6a3e8L, 0xa1d1937eL, 0x38d8c2c4L, 0x4fdff252L, 0xd1bb67f1L,
  0xa6bc5767L, 0x3fb506ddL, 0x48b2364bL, 0xd80d2bdaL, 0xaf0a1b4cL,
  0x36034af6L, 0x41047a60L, 0xdf60efc3L, 0xa867df55L, 0x316e8eefL,
  0x4669be79L, 0xcb61b38cL, 0xbc66831aL, 0x256fd2a0L, 0x5268e236L,
  0xcc0c7795L, 0xbb0b4703L, 0x220216b9L, 0x5505262fL, 0xc5ba3bbeL,
  0xb2bd0b28L, 0x2bb45a92L, 0x5cb36a04L, 0xc2d7ffa7L, 0xb5d0cf31L,
  0x2cd99e8bL, 0x5bdeae1dL, 0x9b64c2b0L, 0xec63f226L, 0x756aa39cL,
  0x026d930aL, 0x9c0906a9L, 0xeb0e363fL, 0x72076785L, 0x05005713L,
  0x95bf4a82L, 0xe2b87a14L, 0x7bb12baeL, 0x0cb61b38L, 0x92d28e9bL,
  0xe5d5be0dL, 0x7cdcefb7L, 0x0bdbdf21L, 0x86d3d2d4L, 0xf1d4e242L,
  0x68ddb3f8L, 0x1fda836eL, 0x81be16cdL, 0xf6b9265bL, 0x6fb077e1L,
  0x18b74777L, 0x88085ae6L, 0xff0f6a70L, 0x66063bcaL, 0x11010b5cL,
  0x8f659effL, 0xf862ae69L, 0x616bffd3L, 0x166ccf45L, 0xa00ae278L,
  0xd70dd2eeL, 0x4e048354L, 0x3903b3c2L, 0xa7672661L, 0xd06016f7L,
  0x4969474dL, 0x3e6e77dbL, 0xaed16a4aL, 0xd9d65adcL, 0x40df0b66L,
  0x37d83bf0L, 0xa9bcae53L, 0xdebb9ec5L, 0x47b2cf7fL, 0x30b5ffe9L,
  0xbdbdf21cL, 0xcabac28aL, 0x53b39330L, 0x24b4a3a6L, 0xbad03605L,
  0xcdd70693L, 0x54de5729L, 0x23d967bfL, 0xb3667a2eL, 0xc4614ab8L,
  0x5d681b02L, 0x2a6f2b94L, 0xb40bbe37L, 0xc30c8ea1L, 0x5a05df1bL,
  0x2d02ef8dL
};


#define DO1(buf) crc = CRC32_Table[((DWORD)crc ^ (*buf++)) & 0xff] ^ (crc >> 8);
#define DO2(buf)  DO1(buf); DO1(buf);
#define DO4(buf)  DO2(buf); DO2(buf);
#define DO8(buf)  DO4(buf); DO4(buf);


//--------------------------------------------------------------------------
DWORD __fastcall PACKAGE crc32(DWORD crc, BYTE *buf, WORD len)
{
    if (buf == NULL) return 0L;
    crc = crc ^ 0xffffffffL;

    while (len >= 8)
    {
        DO8(buf);
    len -= (WORD)8;
    }

    if (len)
    {
        do { DO1(buf); } while (--len);
    }
    return crc ^ 0xffffffffL;
}
//--------------------------------------------------------------------------
WORD __fastcall PACKAGE UpdateCRC(BYTE c, WORD crc)
{
  return  (WORD)((crc << 8) ^ CRC16_Table[ (crc >> 8) ^ c ]);
}
//--------------------------------------------------------------------------
WORD __fastcall PACKAGE CalculateCRC(BYTE *pData, int data_len)
{
  WORD CheckSum   = 0;
  for (int i = 0;i < data_len;i++)
    CheckSum = UpdateCRC(pData[i], CheckSum);
  return CheckSum;
}
//--------------------------------------------------------------------------
WORD __fastcall PACKAGE CRC_Forward(BYTE *pData, int data_len)
{
  WORD CheckSum   = 0;
  for (int i = 0;i < data_len;i++)
    CheckSum = UpdateCRC(pData[i], CheckSum);
  return CheckSum;
}
//--------------------------------------------------------------------------
WORD __fastcall PACKAGE CRC_Backward(BYTE *pData, int data_len)
{
  WORD CheckSum   = 0;
  for (int i = data_len-1;i >= 0;i--)
    CheckSum = UpdateCRC(pData[i], CheckSum);
  return CheckSum;
}
//--------------------------------------------------------------------------
AnsiString __fastcall PACKAGE OldCmdToString(BYTE bCommand, BYTE bObject, BYTE bRange)
{
    AnsiString  strReturn;
    char     szCommand[25];
    char    szObject[25];
    char     szRange[25];

  LoadString((HINSTANCE)HInstance, bCommand     , szCommand, 25);
     LoadString((HINSTANCE)HInstance, bObject + 100, szObject , 25);
    LoadString((HINSTANCE)HInstance, bRange  + 200, szRange  , 25);

    strReturn  = szCommand; strReturn += " ";
    strReturn += szObject;  strReturn += " ";
    strReturn += szRange;

    return strReturn;
}
//..........................................................................
char * __fastcall PACKAGE inet_n2a(DWORD ip_addr)
{
  static char szTempString[20];
    sprintf(szTempString, "%u.%u.%u.%u", ip_addr & 0xFF, (ip_addr >>  8) & 0xFF,
                                  (ip_addr >> 16) & 0xFF, ip_addr >> 24);
    return szTempString;
}
//--------------------------------------------------------------------------
DWORD __fastcall PACKAGE PackPhoneNumber(char *Str)
{
//char    ToneDigit[] = "~1234567890*#ABC........................";

  DWORD  dwPhone;
    DWORD  off_set;
    DWORD  OneDigit;
    int    i, j;

  off_set = 0L;
    dwPhone = 0L;
  for (i = 0;i < (int)strlen(Str);i++)
    {
      for (j = 0;j < 16;j++)
        {
          if (Str[i] == ToneDigit[j])
            {
              OneDigit = ToneDigit[j];
                OneDigit <<= off_set;
                dwPhone |= OneDigit;
                off_set += 4;
            }
        }
    }

    return dwPhone;
}
//--------------------------------------------------------------------------
AnsiString __fastcall PACKAGE UnPackPhoneNumber(DWORD dwPhone)
{
  AnsiString  szPhone;
    DWORD    OneDigit;
  int     i;
//    char    szTmp[200];

    szPhone = "";
  for (i = 0;i < 8;i++)
    {
      OneDigit = dwPhone & 0x0F;
        if (OneDigit == 0) break;

        szPhone += aToneDigit[OneDigit+1];
        dwPhone >>= 4;
    }

    return szPhone;
/*
  AnsiString  szPhone;
  int     i;
    char    szTmp[200];
  int         NullCount;

    szPhone = "";
  NullCount = (dwPhone>>29) & 7;
  for(i = 0; i < NullCount; i++)
    szPhone += '0';
  ltoa(dwPhone & 0x1FFFFFFF, szTmp, 10);
  szPhone += szTmp;
    return szPhone;
*/
}
//--------------------------------------------------------------------------


//--------------------------------------------------------------------------
//  Вспомогательный класс разбора строк
//--------------------------------------------------------------------------
__fastcall  LParams::LParams(void)
{
  pList = new TStringList();
    nParams     = 0;
    delimiter   = ',';
    Comment     = "";
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
__fastcall  LParams::LParams(const LParams& copy)
{
  pList = new TStringList();

    delimiter   = copy.delimiter;
    Comment     = copy.Comment;

    pList->AddStrings(copy.pList);
    nParams     = pList->Count;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
__fastcall  LParams::~LParams(void)
{
  delete pList;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void __fastcall LParams::operator = (const LParams& copy)
{
    pList->Clear();
    delimiter   = copy.delimiter;
    Comment     = copy.Comment;

    pList->AddStrings(copy.pList);
    nParams     = pList->Count;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void __fastcall LParams::Clear(void)
{
    pList->Clear();
    delimiter   = ',';
    Comment     = "";
    nParams     = 0;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void __fastcall LParams::Add(AnsiString szStr)
{
    pList->Add(szStr);
    nParams     = pList->Count;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void __fastcall LParams::SetDelimiter(char s)
{
  delimiter = s;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//Функция Separate(AnsiString szStr) разделяет входную строку на подстроки,
//отделяемые разделителями и помещает их в список pList и возвращает число подстрок.
//Комметарий помещает в строку Comment, если разделитель не ';'
int __fastcall  LParams::Separate(AnsiString szStr)
{
  int    i, index;

  pList->Clear();
  Comment = "";

  if (szStr.IsEmpty() || szStr.Length() == 0)
  {
    nParams = 0;
    return nParams;
  }

  if(delimiter != ';')
  {
    // Выделить комментарий
    for (i = 1;i <= szStr.Length();i++)
    {
      if (szStr[i] == ';')               //Комментарий после символа ';'
      {
        Comment = szStr.SubString(i+1, szStr.Length()-i).Trim();
        szStr.SetLength(i-1);          //Обрезание комментария
        break;
      }
    }
  }

  index = 1;
  for (i = 1;i <= szStr.Length()+1;i++)
  {
    if (i == szStr.Length()+1 || szStr[i] == delimiter)
    {
      pList->Add(szStr.SubString(index, i-index).Trim() );
      index = i+1;
    }
  }
  nParams = pList->Count;
  return nParams;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Преобразовывает список в одну длинную строку, разделенную разделителями и
// в конец добавляет комментарий.
AnsiString __fastcall LParams::MakeString(void)
{
    AnsiString  szResult = "";

    for (int i = 0;i < pList->Count;i++)
    {
        szResult += pList->Strings[i];
        if (i >= pList->Count-1) break;
    szResult += (AnsiString)(delimiter);
  }

    if (!Comment.IsEmpty() )
    {
        szResult += " ; ";
        szResult += Comment;
    }

    return szResult;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int __fastcall  LParams::AsInt(int nStr,int iDefault)
{
  if (nStr < pList->Count)
  {
    if(pList->Strings[nStr].Trim()=="")
      return iDefault;
    return (int)strtol(pList->Strings[nStr].c_str(), NULL, 10);
  }
  else
     return -1;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
DWORD __fastcall  LParams::AsHex(int nStr,DWORD dwDefault)
{
  if (nStr < pList->Count)
  {
    if(pList->Strings[nStr].Trim()=="")
      return dwDefault;
    return strtoul(pList->Strings[nStr].c_str(), NULL, 16);
  }
  else
    return (DWORD)(-1);
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
AnsiString __fastcall  LParams::AsStr(int nStr,AnsiString sDefault)
{
  if (nStr < pList->Count)
  {
    if(pList->Strings[nStr].Trim()=="")
      return sDefault;
    return pList->Strings[nStr];
  }
  else
    return "";
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
TColor __fastcall  LParams::AsColor(int nStr,TColor clDefault)
{
  AnsiString  colorStr;
  if (nStr < pList->Count)
  {
    colorStr = pList->Strings[nStr];
    colorStr = colorStr.Trim();
    if(colorStr=="")
      return clDefault;

    if (colorStr.AnsiCompareIC("clBlack")   == 0)   return clBlack;
    if (colorStr.AnsiCompareIC("clMaroon")  == 0)   return clMaroon;
    if (colorStr.AnsiCompareIC("clGreen")   == 0)   return clGreen;
    if (colorStr.AnsiCompareIC("clOlive")   == 0)   return clOlive;

    if (colorStr.AnsiCompareIC("clNavy")    == 0)   return clNavy;
    if (colorStr.AnsiCompareIC("clPurple")  == 0)   return clPurple;
    if (colorStr.AnsiCompareIC("clTeal")    == 0)   return clTeal;
    if (colorStr.AnsiCompareIC("clGray")    == 0)   return clGray;

    if (colorStr.AnsiCompareIC("clSilver")  == 0)   return clSilver;
    if (colorStr.AnsiCompareIC("clRed")     == 0)   return clRed;
    if (colorStr.AnsiCompareIC("clLime")    == 0)   return clLime;
    if (colorStr.AnsiCompareIC("clYellow")  == 0)   return clYellow;

    if (colorStr.AnsiCompareIC("clBlue")    == 0)   return clBlue;
    if (colorStr.AnsiCompareIC("clFuchsia") == 0)   return clFuchsia;
    if (colorStr.AnsiCompareIC("clAqua")    == 0)   return clAqua;
    if (colorStr.AnsiCompareIC("clWhite")   == 0)   return clWhite;

     return clDefault;
  }
  else
     return clNone;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
double __fastcall  LParams::AsFloat(int nStr,double dbDefault)
{
  if (nStr < pList->Count)
  {
    if(pList->Strings[nStr].Trim()=="")
      return dbDefault;
    return strtod(pList->Strings[nStr].c_str(), NULL);
  }
  else
    return (double)(-1);
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
TDateTime __fastcall  LParams::AsDateTime(int nStr,TDateTime tdDefault)
{
  if (nStr < pList->Count)
  {
    if(pList->Strings[nStr].Trim()=="")
      return tdDefault;
    TDateTime dtRet(pList->Strings[nStr]);
    return dtRet;
  }
  else
     return tdDefault;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
DWORD __fastcall  LParams::AsDef(int nStr,DWORD dwDefault)
{
  if (nStr < pList->Count)
  {
    if(pList->Strings[nStr]=="")
      return dwDefault;
    return strtoul(pList->Strings[nStr].c_str(), NULL, 0);
  }
  else
      return (DWORD)(-1);
}
//--------------------------------------------------------------------------


//--------------------------------------------------------------------------
//  Вспомогательный класс работы с профайлом
//--------------------------------------------------------------------------

__fastcall LProfile::LProfile(void)
{
    FileName = ChangeFileExt(ParamStr(0), ".ini");
    pIni = new TIniFile(FileName);
}
//---------------------------------------------------------------------------
__fastcall LProfile::LProfile(AnsiString sProfileName)
{
    if(sProfileName=="")
      FileName = ChangeFileExt(ExeName, ".ini");
    else
      FileName = sProfileName;
    pIni = new TIniFile(FileName);
}
//---------------------------------------------------------------------------
__fastcall LProfile::~LProfile(void)
{
    delete pIni;
}
//---------------------------------------------------------------------------
bool __fastcall LProfile::SectionExists(const AnsiString Section)
{
  return pIni->SectionExists(Section);
}
//---------------------------------------------------------------------------
bool __fastcall LProfile::ValueExists(const AnsiString Section, const AnsiString Ident)
{
  return pIni->ValueExists(Section,Ident);
}
//---------------------------------------------------------------------------
int __fastcall LProfile::ReadInteger(const AnsiString Section, const AnsiString Ident, int Default)
{
  return pIni->ReadInteger(Section, Ident, Default);
}
//---------------------------------------------------------------------------
LParams __fastcall LProfile::LoadParameter(AnsiString Section, AnsiString Key, AnsiString Default)
{
  AnsiString  szResult;
  szResult = pIni->ReadString(Section, Key, Default);
  pParams.Separate(szResult);
  return pParams;
}
//---------------------------------------------------------------------------
LParams * __fastcall LProfile::GetValue(void)
{
  return &pParams;
}
//---------------------------------------------------------------------------
void __fastcall LProfile::WriteInteger(const AnsiString Section, const AnsiString Ident, int Value)
{
  pIni->WriteInteger(Section, Ident, Value);
}
//---------------------------------------------------------------------------
void __fastcall LProfile::StoreParameter(AnsiString Section, AnsiString Key, AnsiString Value)
{
  pIni->WriteString(Section, Key, Value);
}
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
//  Вспомогательные функции
//--------------------------------------------------------------------------

DWORD __fastcall PACKAGE PhoneStringToDword(char *ptr)
{
  DWORD   PhoneNumber;
  DWORD   FirstZero = 0;

  while(*ptr == '0') { FirstZero++; ptr++; }
    PhoneNumber = strtoul(ptr, NULL, 10);
    FirstZero   &= 0x07;
    FirstZero  <<= 29;
    PhoneNumber |= FirstZero;

  return PhoneNumber;
}
//--------------------------------------------------------------------------
char * __fastcall PACKAGE PhoneDwordToString(DWORD Number)
{
  if (Number == 0)
    return "\0";
  static char PhoneString[25];
  ZeroMemory(PhoneString, 25);
  DWORD FirstZero = Number >> 29;
  for (DWORD i = 0;i < FirstZero;++i)
    PhoneString[i] = '0';
  if(Number & 0x1FFFFFFF)
  {
    char *pTmp=PhoneString+FirstZero;
    itoa(Number & 0x1FFFFFFF,pTmp,10);
  }
  return PhoneString;
}
//--------------------------------------------------------------------------

AnsiString __fastcall PACKAGE PhoneDwToAnsiStr(DWORD Number)
{
  AnsiString PhoneString = AnsiString::StringOfChar('0',Number >> 29);
  if (Number & 0x1FFFFFFF)
    PhoneString.cat_sprintf("%lu", Number & 0x1FFFFFFF );
  return PhoneString;
}
//--------------------------------------------------------------------------
AnsiString __fastcall PACKAGE PhoneDw2Str(DWORD Number)
{
  if (Number == 0)
    return "";
  AnsiString PhoneString = AnsiString::StringOfChar('0',Number >> 29);
  if(Number & 0x1FFFFFFF)
    PhoneString.cat_sprintf("%lu", Number & 0x1FFFFFFF );
  switch(PhoneString.Length())
  {
    default:PhoneString.Insert("-", PhoneString.Length()-6);
    case 7:
    case 6:
    case 5:PhoneString.Insert("-", PhoneString.Length()-3);
    case 4:
    case 3:PhoneString.Insert("-", PhoneString.Length()-1);
    case 2:
    case 1:;
  }
  PhoneString.Insert(" ", 1);
  return PhoneString;
}
//--------------------------------------------------------------------------
DWORD __fastcall PACKAGE PhoneStr2Dw(AnsiString szPhone)
{
  for (int j = 1;j <= szPhone.Length();j++)
       if (szPhone[j] < '0' || szPhone[j] > '9')
        {
          szPhone.Delete(j, 1);
            j--;
        }


    return PhoneStringToDword(szPhone.c_str() );
}
/*
//--------------------------------------------------------------------------
TDateTime __fastcall PACKAGE ConvertTime(long dt, int nHour)
{
  tm        *rtm;
    int      Year;
  TDateTime   fullTime;    //time_t
  TDateTime   correctTime((unsigned short)abs(nHour), (unsigned short)0,
    (unsigned short)0, (unsigned short)0);


    if (dt == 0) return fullTime;

    try
    {
      rtm = LocalTimeVC(&dt);
        if (rtm == NULL) return fullTime;
    }
    catch(...)   // tzset
    {
        return fullTime;
    }

    if (rtm->tm_year > 90) Year = rtm->tm_year+1900;
    else                   Year = rtm->tm_year+2000;

  TDateTime dTmp((unsigned short)Year, (unsigned short)(rtm->tm_mon+1),
    (unsigned short)rtm->tm_mday);
  TDateTime tTmp((unsigned short)rtm->tm_hour, (unsigned short)rtm->tm_min,
    (unsigned short)rtm->tm_sec, (unsigned short)0);
    fullTime = dTmp + tTmp;

    if (nHour < 0)
        fullTime -= correctTime;
    else
        fullTime += correctTime;


    return fullTime;
}
*/
//--------------------------------------------------------------------------
AnsiString __fastcall ColorToStr(TColor eColor)
{
    switch(eColor)
    {
        case clBlack    : return "clBlack";
        case clMaroon   : return "clMaroon";
        case clGreen    : return "clGreen";
        case clOlive    : return "clOlive";

        case clNavy     : return "clNavy";
        case clPurple   : return "clPurple";
        case clTeal     : return "clTeal";
        case clGray     : return "clGray";

        case clSilver   : return "clSilver";
        case clRed      : return "clRed";
        case clLime     : return "clLime";
        case clYellow   : return "clYellow";

        case clBlue     : return "clBlue";
        case clFuchsia  : return "clFuchsia";
        case clAqua     : return "clAqua";
        case clWhite    : return "clWhite";

        default:    return "clNone";
    }
}
//--------------------------------------------------------------------------
AnsiString __fastcall la_GetVersion(AnsiString ModuleName)
{
    // Прочитать и вывести версию приложения
    struct TVerTranslation
    {
        WORD    Language;
        WORD    CharSet;
    };

    TVerTranslation     *Trans;
    VS_FIXEDFILEINFO    FixInfo;
    DWORD               dwValue, struct_Size;
    void                *pFixInfo;
    char                *Data;
    char                szTxt[200];
    void                *ptr;
    int                 Res;
    UINT                numBytes;
    UINT                Bytes;
    AnsiString          BaseStr;
    AnsiString          InfoStr;
    AnsiString          sVersion;

    pFixInfo = (void *)&FixInfo;
    struct_Size = GetFileVersionInfoSize(ModuleName.c_str(), &dwValue);

    if (struct_Size)
    {
        Data = new char[struct_Size + 10];
        Res = GetFileVersionInfo(ModuleName.c_str(), 0, struct_Size, Data);

        if (!Res)
        {
            delete [] Data;
            return " ";
        }

        // Язык и кодовая таблица
        Res = VerQueryValue(Data, "\\VarFileInfo\\Translation", &ptr, &Bytes);
        if (Res)
        {
            (void *)Trans = new char[Bytes + 10];
            memcpy(Trans, ptr, Bytes);
            sprintf(szTxt, "StringFileInfo\\%04X%04X\\", Trans->Language, Trans->CharSet);
            BaseStr = szTxt;
            delete [] Trans;
        }

        numBytes = sizeof(FixInfo);
        memset(pFixInfo, 0, numBytes);

        VerQueryValue((void *)Data, "\\", &ptr, &numBytes);
        memcpy(pFixInfo, ptr, numBytes);

        InfoStr = BaseStr + "FileVersion";
        Res = VerQueryValue(Data, InfoStr.c_str(), &ptr, &Bytes);
        sVersion = " ";

        if (Res && (Bytes != 0))
          sVersion = (char *)ptr;
        delete [] Data;
    }

    return sVersion;
}
//---------------------------------------------------------------------------

AnsiString __fastcall GetVersion(char *ModuleName)
{
  AnsiString sVersion = "";
  // Прочитать и вывести версию приложения
  DWORD dwValue;
  DWORD dwSize = GetFileVersionInfoSize(ModuleName, &dwValue);
  if (dwSize)
  {
    char *Data = new char[dwSize + 10];
    if(GetFileVersionInfo(ModuleName, 0, dwSize, Data))
    {
      // Язык и кодовая таблица
      struct TVerTranslation
      {
        WORD    Language;
        WORD    CharSet;
      };
      TVerTranslation *Trans;
      char szKey[100];
      UINT uiSize;
      if (VerQueryValue(Data, "\\VarFileInfo\\Translation", (void**)&Trans, &uiSize))
      {
        sprintf(szKey, "StringFileInfo\\%04X%04X\\FileVersion", Trans->Language, Trans->CharSet);
        void *ptr;
        if(VerQueryValue(Data, szKey, &ptr, &uiSize) && dwSize != 0)
          sVersion = (char *)ptr;
      }
    }
    delete [] Data;
  }
  return sVersion;
}
//---------------------------------------------------------------------------

AnsiString __fastcall GetVersion(AnsiString ModuleName)
{
  return GetVersion(ModuleName.c_str());
}
//---------------------------------------------------------------------------

AnsiString __fastcall buildStr(BYTE *Buf, WORD maxNum,
  AnsiString Delim1, AnsiString Delim2, DWORD dwMaxCountInt, BYTE **ppCurPos)
{
  AnsiString  szTxt;
  DWORD dwCountInt = 0;
  BYTE *pEndBuf = Buf+maxNum;
  BYTE *pCurPos = Buf;
  if(ppCurPos)
    pCurPos = *ppCurPos;
  BYTE *si=NULL; 
  do
  {
    switch(*pCurPos)
    {
      default:
        if(si==NULL)
          si=pCurPos;
        break;
      case 0:
        if(si)
        {
          if(szTxt!="")
            szTxt += Delim1;
          szTxt += IntToStr(si-Buf);
          if(pCurPos-1>si)
          {
            szTxt += Delim2;
            szTxt += IntToStr(pCurPos-1-Buf);
          }
          si = NULL;
          ++dwCountInt;
        }
    }
  }while(++pCurPos<pEndBuf && dwCountInt<dwMaxCountInt);
  if(si)
  {
    if(szTxt!="")
      szTxt += Delim1;
    szTxt += IntToStr(si-Buf);
    if(pCurPos-1>si)
    {
      szTxt += Delim2;
      szTxt += IntToStr(pCurPos-1-Buf);
    }
  }
  if(ppCurPos)
    *ppCurPos = pCurPos;
  return szTxt;
}
//---------------------------------------------------------------------------
void __fastcall restoreStr(AnsiString szSource, BYTE *Buf, WORD maxNum, BYTE mbFill)
{
  char    szBuf[2048];
  char    *sptr, *cptr;
  int   si;
  int   ei = -1;
  strcpy(szBuf, szSource.c_str() );
  if (szSource == "")
    return;
  strcat(szBuf, ",");
  sptr = szBuf;
  cptr = strpbrk(sptr, ",-");
  while (cptr)
  {
    if (*cptr == ',')
    {
      *cptr = 0;
      si = atoi(sptr);
      if (si < maxNum)
        Buf[si] = mbFill;
      sptr = cptr+1;
    }
    else
    {
      // читаем начало диапазона
      *cptr = 0;
      si = atoi(sptr);
      sptr = cptr+1;
      // находим конец диапазона
      cptr = strpbrk(sptr, ",");
      if (cptr)
      {
        *cptr = 0;
        ei = atoi(sptr);
      }
      if (si >= maxNum)
        si = maxNum - 1;
      if (ei >= maxNum)
        ei = maxNum - 1;
      for (int i = si;i <= ei;i++)
        Buf[i] = mbFill;
      sptr = cptr+1;
    }
    cptr = strpbrk(sptr, ",-");
  }
  return;
}
//---------------------------------------------------------------------------
char * __fastcall ByteToBinary(DWORD Value, int Len)
{
  static  char   Num1[34];
    int     Maska = 0x01;

    if (Len > 32) Len = 32;
    if (Len) Maska <<= (Len-1);

    for (int u = 0;u < Len;u++)
    {
      (Value & Maska) ? (Num1[u] = '1') : (Num1[u] = '0');
      Maska >>= 1;
    }

    Num1[Len] = 0;

     return Num1;
}
//---------------------------------------------------------------------------
AnsiString __fastcall SlashSep(AnsiString Path, AnsiString S)
{
  if(S.IsEmpty())
    return Path;
  if(Path.IsEmpty())
    return S;
  switch(*Path.AnsiLastChar())
  {
    case 0: return S;
    case '\\': return Path + S;
    default: return Path + "\\" + S;
  }
}
//---------------------------------------------------------------------------
BOOL __fastcall OpenTheFile(HWND hWnd, AnsiString &FileName, int &iDelimiter )
{
  OPENFILENAME    OpenFileName;
  TCHAR           szFile[MAX_PATH] = "\0";
  BYTE            szFilterInits[] = "Текстовые файлы (*.txt)\0*.txt\0Все файлы (*.*)\0*.*\0\0\0";
  char            *sz_ComboItem[] = { " ;", " ,", " |", "Tab" };
  strcpy( szFile, FileName.c_str() );
  CBDATA sCbData;
  //    for (int i = 0;i < 4;i++)
  sCbData.sz_cbItems = sz_ComboItem;
  // Fill in the OPENFILENAME structure to support a template and hook.
  switch(GetOperatingSystem())
  {
    case OS_WIN32_2000: ;
    case OS_WIN32_XP: ;
    case OS_WIN32_NET: ;
      OpenFileName.lStructSize = sizeof(OPENFILENAME);
      break;
    default: ;
      OpenFileName.lStructSize = OPENFILENAME_SIZE_VERSION_400;
  }
  OpenFileName.hwndOwner         = hWnd;
  OpenFileName.hInstance         = HInstance;
  OpenFileName.lpstrFilter       = (LPCTSTR)szFilterInits;
  OpenFileName.lpstrCustomFilter = NULL;
  OpenFileName.nMaxCustFilter    = 0;
  OpenFileName.nFilterIndex      = 0;
  OpenFileName.lpstrFile         = szFile;
  OpenFileName.nMaxFile          = sizeof(szFile);
  OpenFileName.lpstrFileTitle    = NULL;
  OpenFileName.nMaxFileTitle     = 0;
  OpenFileName.lpstrInitialDir   = NULL;
  OpenFileName.lpstrTitle        = "Введите имя файла:";
  OpenFileName.nFileOffset       = 0;
  OpenFileName.nFileExtension    = 0;
  OpenFileName.lpstrDefExt       = "*.txt";
  OpenFileName.lCustData         = (LPARAM)&sCbData;
  OpenFileName.lpfnHook        = ComDlg32DlgProc;
  OpenFileName.lpTemplateName    = MAKEINTRESOURCE(100);
  OpenFileName.Flags             = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_EXPLORER |
    OFN_ENABLEHOOK | OFN_ENABLETEMPLATE;
  // Call the common dialog function.
  if (!GetSaveFileName(&OpenFileName))
    return false;
  FileName          = OpenFileName.lpstrFile;
  iDelimiter        = sCbData.i_RetIndex;
  return true;

}
//---------------------------------------------------------------------------
//
//  FUNCTION: ComDlg32DlgProc( HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
//
//  MESSAGES:
//
//  WM_INITDIALOG - save pointer to the OPENFILENAME structure in User data
//  WM_DESTROY - get the text entered and fill in the MyData structure
//  WM_NOTIFY - pass this message onto the TestNotify function
//  default - check for a sharing violation or the OK button and
//      display a message box.
//
//---------------------------------------------------------------------------
UINT CALLBACK ComDlg32DlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    HWND            hWndCombo;
    LPOPENFILENAME  lpOFN;
    LPCBDATA        psCbData;
    LPOFNOTIFY      lpOFNOTIFY;

  switch (uMsg)
  {
    case WM_INITDIALOG:
      // Save off the long pointer to the OPENFILENAME structure.
      SetWindowLong(hDlg, DWL_USER, lParam);
            CenterWindow(hDlg);

            lpOFN       = (LPOPENFILENAME)GetWindowLong(hDlg, DWL_USER);
            psCbData    = (LPCBDATA)lpOFN->lCustData;
            hWndCombo   = GetDlgItem(hDlg, 1000);
            for (int i = 0;i < 4;i++)
                SendMessage(hWndCombo, CB_ADDSTRING, 0, (LPARAM)psCbData->sz_cbItems[i]);

            SendMessage(hWndCombo, CB_SETCURSEL, 0, 0);
        break;

    case WM_DESTROY:
            lpOFN       = (LPOPENFILENAME)GetWindowLong(hDlg, DWL_USER);
            psCbData    = (LPCBDATA)lpOFN->lCustData;
            hWndCombo   = GetDlgItem(hDlg, 1000);
            psCbData->i_RetIndex = SendMessage(hWndCombo, CB_GETCURSEL, 0, 0);
        break;

    case WM_NOTIFY:
            lpOFNOTIFY = (LPOFNOTIFY)lParam;
            if (lpOFNOTIFY->hdr.code == CDN_INITDONE) CenterWindow((HWND)GetWindowLong(hDlg, GWL_HWNDPARENT));

//      TestNotify(hDlg, (LPOFNOTIFY)lParam);
        break;

    default:
      return FALSE;
  }

  return TRUE;
}
//---------------------------------------------------------------------------

void __fastcall CenterWindow(HWND hWnd)
{
  TRect       Rect;
  TMonitor    *Monitor;
  GetWindowRect(hWnd, &Rect);
  Monitor = Screen->Monitors[0];
  SetWindowPos(hWnd, 0,
    Monitor->Left + ((Monitor->Width - Rect.Right + Rect.Left) / 2),
    Monitor->Top + ((Monitor->Height - Rect.Bottom + Rect.Top) / 3),
    0, 0, SWP_NOACTIVATE | SWP_NOSIZE | SWP_NOZORDER);
}
//----------------------------------------------------------------------------
/*
bool __fastcall ShowQuestion(const AnsiString &S, HWND hParent)
{
  TForm *pMainForm = (Application && Application->MainForm)?Application->MainForm:NULL;
  HWND hWnd=hParent?hParent:(pMainForm?pMainForm->Handle:NULL);
  AnsiString Caption = "";
  if(pMainForm)
    Caption = Application->MainForm->Caption;
  return MessageBox(hWnd, S.c_str(), Caption.c_str(), MB_YESNO | MB_ICONQUESTION) == IDYES;
}
*/
//----------------------------------------------------------------------------
void __fastcall ShowError(const AnsiString &S, HWND hParent)
{
  TForm *pMainForm = (Application && Application->MainForm)?Application->MainForm:NULL;
  HWND hWnd=hParent?hParent:(pMainForm?pMainForm->Handle:NULL);
  AnsiString Caption = "";
  if(pMainForm)
    Caption = Application->MainForm->Caption;
  MessageBox(hWnd, S.c_str(), Caption.c_str(), MB_OK | MB_ICONERROR);
}
//----------------------------------------------------------------------------
void __fastcall ShowWarning(const AnsiString &S, HWND hParent)
{
  TForm *pMainForm = (Application && Application->MainForm)?Application->MainForm:NULL;
  HWND hWnd=hParent?hParent:(pMainForm?pMainForm->Handle:NULL);
  AnsiString Caption = "";
  if(pMainForm)
    Caption = Application->MainForm->Caption;
  MessageBox(hWnd, S.c_str(), Caption.c_str(), MB_OK | MB_ICONWARNING);
}
//----------------------------------------------------------------------------
void __fastcall ShowInformation(const AnsiString &S, HWND hParent)
{
  TForm *pMainForm = (Application && Application->MainForm)?Application->MainForm:NULL;
  HWND hWnd=hParent?hParent:(pMainForm?pMainForm->Handle:NULL);
  AnsiString Caption = "";
  if(pMainForm)
    Caption = Application->MainForm->Caption;
  MessageBox(hWnd, S.c_str(), Caption.c_str(), MB_OK | MB_ICONINFORMATION);
}
//--------------------------------------------------------------------------
/*
bool __fastcall ShowQuestion(const AnsiString &S,
  bool &bYesAll, bool &bNoAll, bool &bCancel, HWND hParent)
{
  if(bYesAll)
    return true;
  if(bNoAll)
    return false;
  TfQuestionDlg *pDlg=new TfQuestionDlg(hParent?hParent:
    ((Application && Application->MainForm)?Application->MainForm->Handle:NULL));
  bool rez=pDlg->ShowQuestion(S, bYesAll, bNoAll, bCancel);
  delete pDlg;
  return rez;
}
//---------------------------------------------------------------------------

bool __fastcall ShowQuestion(const AnsiString &S, bool &bCancel, HWND hParent)
{
  bCancel=false;
  bool rez = true;
  TForm *pMainForm = (Application && Application->MainForm)?Application->MainForm:NULL;
  HWND hWnd=hParent?hParent:(pMainForm?pMainForm->Handle:NULL);
  AnsiString Caption = "";
  if(pMainForm)
    Caption = Application->MainForm->Caption;
  //char *pCaption =strdup((Application && Application->MainForm)?Application->MainForm->Caption.c_str()):NULL;
  switch(MessageBox(hWnd, S.c_str(), Caption.c_str(), MB_ABORTRETRYIGNORE|MB_ICONERROR|MB_DEFBUTTON1))
  {
    case IDRETRY:
      break;
    case IDABORT:
    default:
      bCancel=true;
    case IDIGNORE:
      rez = false;
  }
  //if(pCaption)
    //free(pCaption);
  return rez;
}
*/
//---------------------------------------------------------------------------
/*
TDateTime __fastcall time_tToDateTime(time_t AValue)
{
  return UnixToDateTime(AValue)-TimeZoneBias();
}
//--------------------------------------------------------------------------
time_t __fastcall DateTimeTotime_t(TDateTime AValue)
{
  return DateTimeToUnix(AValue+TimeZoneBias());
} */
//--------------------------------------------------------------------------
AnsiString __fastcall DeltaDateTimeToStr(TDateTime ANow, TDateTime AThen)
{
  AnsiString S;
  __int64 Delta=(__int64)YearSpan(ANow,AThen);
  if(Delta!=0)
  {
    if(ANow>AThen)
      ANow=IncYear(ANow,-Delta);
    else
      AThen=IncYear(AThen,-Delta);
    S=IntToStr(Delta)+" г  ";
  }
  Delta=(__int64)MonthSpan(ANow,AThen);
  if(Delta!=0)
  {
    if(ANow>AThen)
      ANow=IncMonth(ANow,-Delta);
    else
      AThen=IncMonth(AThen,-Delta);
    S+=IntToStr(Delta)+" мес  ";
  }
  Delta=(__int64)DaySpan(ANow,AThen);
  if(Delta!=0)
  {
    if(ANow>AThen)
      ANow=IncDay(ANow,-Delta);
    else
      AThen=IncDay(AThen,-Delta);
    S+=IntToStr(Delta)+" д  ";
  }
  Delta=(__int64)HourSpan(ANow,AThen);
  if(Delta!=0)
  {
    if(ANow>AThen)
      ANow=IncHour(ANow,-Delta);
    else
      AThen=IncHour(AThen,-Delta);
    S+=IntToStr(Delta)+" ч  ";
  }
  Delta=(__int64)MinuteSpan(ANow,AThen);
  if(Delta!=0)
  {
    if(ANow>AThen)
      ANow=IncMinute(ANow,-Delta);
    else
      AThen=IncMinute(AThen,-Delta);
    S+=IntToStr(Delta)+" мин  ";
  }
  Delta=(__int64)SecondSpan(ANow,AThen);
  if(Delta!=0)
  {
    if(ANow>AThen)
      ANow=IncSecond(ANow,-Delta);
    else
      AThen=IncSecond(AThen,-Delta);
    S+=IntToStr(Delta)+" с  ";
  }
  Delta=(__int64)MilliSecondSpan(ANow,AThen);
  if(Delta!=0&&S=="")
    S=IntToStr(Delta)+" мс";
  return S;
}

int __fastcall GetOperatingSystem()
{
  OSVERSIONINFO vi = { sizeof(vi) };
  if(GetVersionEx(&vi))
  {
    switch(vi.dwPlatformId)
    {
      case VER_PLATFORM_WIN32s:
        return -1;
      case VER_PLATFORM_WIN32_WINDOWS:
        if ((vi.dwMinorVersion == 0) && (vi.dwMajorVersion == 4))
          return OS_WIN32_95;
        else if ((vi.dwMinorVersion == 10) && (vi.dwMajorVersion == 4))
          return OS_WIN32_98;
        else if ((vi.dwMinorVersion == 90) && (vi.dwMajorVersion == 4))
          return OS_WIN32_ME;
        else
          return -2;
      case VER_PLATFORM_WIN32_NT:
        if ((vi.dwMinorVersion == 51) && (vi.dwMajorVersion == 3))
          return OS_WIN32_NT351;
        else if ((vi.dwMinorVersion == 0) && (vi.dwMajorVersion == 4))
          return OS_WIN32_NT4;
        else if ((vi.dwMinorVersion == 0) && (vi.dwMajorVersion == 5))
          return OS_WIN32_2000;
        else if ((vi.dwMinorVersion == 1) && (vi.dwMajorVersion == 5))
          return OS_WIN32_XP;
        else
          return -3;
      default:
        return -4;
    }
  }
  return -5;
}

//---------------------------------------------------------------------------

void ProcessMessages()
{
  tagMSG msg;
  while( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE))
  {
    if (!IsDialogMessage(NULL, &msg) &&
        !TranslateAccelerator(NULL, NULL, &msg))
    {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
  }
}
//---------------------------------------------------------------------------

TDateTime MSecsToDateTime(__int64 nTime)
{
  return TimeStampToDateTime(MSecsToTimeStamp(nTime));
}
//---------------------------------------------------------------------------

AnsiString TimeMillisecAsStr(__int64 nTime)
{
  DWORD dwHour, dwMin, dwSec, dwMSec;
  AnsiString str_Time;
  dwMSec = nTime%1000;  nTime /= 1000;
  dwSec  = nTime%60;    nTime /= 60;
  dwMin  = nTime%60;    dwHour = nTime/60;
  str_Time.sprintf("%2d:%02d:%02d.%03d", dwHour, dwMin, dwSec, dwMSec);
  return str_Time;
}
//---------------------------------------------------------------------------

AnsiString DelPhoneDelim(const AnsiString &Str)
{
  AnsiString S = "";
  for(int i = 1; i <= Str.Length(); i++)
    if(isdigit(Str[i])) S += Str[i];
  return S;
}
//---------------------------------------------------------------------------

bool LongPhoneStr2DwordArray(const AnsiString &szPhone, DWORD *pdwNumBuff , BYTE n )
{
  BYTE j=0;
  for(int i = 0; i < n; ++i)
    pdwNumBuff[i]=0;
  for(int i = 1; i <= szPhone.Length(); ++i)
  {
    if(isdigit(szPhone[i]))
    {
      if(!AddDigit(BYTE(szPhone[i])-48,pdwNumBuff , j))
      {
        ++j;
        if(j>=n || !AddDigit(BYTE(szPhone[i])-48,pdwNumBuff , j))
          return 0;
      }
    }
  }
  return 1;
}
//---------------------------------------------------------------------------
////////////////////////////////////////////////////////
//      --- AddDigit ---
// Comment : добавить цифру номера ( 1-10 ) "digit" в
//     приемник "pdwNumBuff" ( "n" - количество приемников )
////////////////////////////////////////////////////////
bool AddDigit( BYTE digit , DWORD *pdwNumBuff , BYTE n )
{
  // - если 10 - это 0
  if( digit == 10 ) digit = 0 ;

  for( int i = 0 ; i < n ; ++i )
  { // - младшие и старшие биты буфера
    DWORD dwl = LOBITSDW( pdwNumBuff[ i ] );
    DWORD dwh = HIBITSDW( pdwNumBuff[ i ] );

    // - это ведущий ноль ?
    if( !( digit || dwl ) )
    { // -  ведущий ноль - наращиваем счетчик нолей
      pdwNumBuff[ i ] += DWORD(1) << 29;
      return 1;
    }
    else // - это не ведущий ноль - добавляем цифру в приемник
      if( dwl < 10000000L )// в приемнике еще нет 8 цифр
    { // dwl*10 + digit
      pdwNumBuff[i]= digit+( dwl << 3  ) + ( dwl << 1  ) + ( dwh << 29 );
      return 1;
    }
  }
  return 0;
}
//---------------------------------------------------------------------------

bool WriteLogPass(char *szLogin, char *szPass, HKEY RootKey)
{
  SLoginPassData LPData;
  byte *pBinData=(byte*)&LPData;
  randomize();
  for(int i=0;i<SIZE_LOGIN_PASS_DATA;++i,++pBinData)
    *pBinData=random(256);
  LPData.nLogin=strlen(szLogin);
  LPData.nPass=strlen(szPass);
  if(LPData.nLogin>255 || LPData.nLogin==0 || LPData.nPass>255 ||  LPData.nPass==0)
    return false;
  memcpy(LPData.szLogin,szLogin,LPData.nLogin);
  memcpy(LPData.szPass,szPass,LPData.nPass);
  pBinData=(byte*)&LPData;
  for(int i=0;i<SIZE_LOGIN_PASS_DATA;++i,++pBinData)
    *pBinData^=127;
  TRegistry *Registry = new TRegistry();
  try
  {
    Registry->RootKey = RootKey;
    Registry->OpenKey(RegKey,true);
    Registry->WriteBinaryData("BinData", &LPData, SIZE_LOGIN_PASS_DATA);
  }
  catch(...)
  {
    delete Registry;
    return false;
  }
  delete Registry;
  return true;
}
//---------------------------------------------------------------------------

bool ReadLogPass(SLoginPassData *pLPData, HKEY RootKey)
{
  byte *pBinData=(byte*)pLPData;
  TRegistry *Registry = new TRegistry();
  try
  {
    Registry->RootKey = RootKey;
    Registry->OpenKey(RegKey,true);
    Registry->ReadBinaryData("BinData", pBinData, SIZE_LOGIN_PASS_DATA);
  }
  catch(...)
  {
    delete Registry;
    return false;
  }
  delete Registry;
  for(int i=0;i<SIZE_LOGIN_PASS_DATA;++i,++pBinData)
    *pBinData^=127;
  pLPData->szLogin[pLPData->nLogin]=0;
  pLPData->szPass[pLPData->nPass]=0;
  return true;
}
//---------------------------------------------------------------------------



///////////////////////////////////////////////////////////

