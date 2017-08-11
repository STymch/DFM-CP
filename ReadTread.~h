//---------------------------------------------------------------------------

#ifndef ReadTreadH
#define ReadTreadH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include "DefWinMessage.h"
#include <SyncObjs.hpp>
//---------------------------------------------------------------------------
class TThreadReader : public TThread
{            
private:
protected:
        void __fastcall Execute();
public:
        __fastcall TThreadReader(bool CreateSuspended);
        __fastcall TThreadReader(bool CreateSuspended, HANDLE A);

  HANDLE comport;
//  OVERLAPPED over;
  HWND   Form1Handle;
  BYTE bufrd[256];
  DWORD btr;
//  int Count;   //смещение в поле буфера
  int SendetCount;  //счетчик полных записей
  int BCount;  //счетчик внутри одной записи
  BYTE Cbufrd[256];
  TDateTime DT;
  TCriticalSection *csReadFromPort;
  AnsiString PortReadState;
  int ErrCount;
};
extern PACKAGE TThreadReader *reader;
//---------------------------------------------------------------------------
#endif
