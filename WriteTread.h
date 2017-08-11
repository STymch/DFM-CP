//---------------------------------------------------------------------------

#ifndef WriteTreadH
#define WriteTreadH
//---------------------------------------------------------------------------
#include <Classes.hpp>
//---------------------------------------------------------------------------
class TThreadWriter : public TThread
{            
private:
protected:
       void __fastcall Execute();
       void __fastcall Execute2();
public:
        __fastcall TThreadWriter(bool CreateSuspended);
        __fastcall TThreadWriter(bool CreateSuspended, HANDLE H, AnsiString S);
        __fastcall TThreadWriter(bool CreateSuspended, HANDLE H, BYTE* p, int Count);

//  OVERLAPPED overlappedwr;
  HANDLE COMport;
  BYTE       wrbuf2[256];
  unsigned char   wrbuf[256];
  bool fl;
  int    Count1;
};
extern PACKAGE TThreadWriter *writer;

//---------------------------------------------------------------------------
#endif
 