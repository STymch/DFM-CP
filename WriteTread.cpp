//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "WriteTread.h"
#pragma package(smart_init)
TThreadWriter *writer;
extern  OVERLAPPED overlappedwr;
//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall TThreadWriter::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------
__fastcall TThreadWriter::TThreadWriter(bool CreateSuspended)
        : TThread(CreateSuspended)
{
 void __fastcall Execute(); //???????? ??????? ??????
}
//---------------------------------------------------------------------------
__fastcall TThreadWriter::TThreadWriter(bool CreateSuspended, HANDLE H, AnsiString S)
        : TThread(CreateSuspended)
{
 COMport = H;
 strcpy(wrbuf,S.c_str());
 Execute(); //???????? ??????? ??????
}
//---------------------------------------------------------------------------
__fastcall TThreadWriter::TThreadWriter(bool CreateSuspended, HANDLE H, BYTE* p, int Count)
        : TThread(CreateSuspended)
{
 COMport = H;
 memset(&wrbuf2,0,5);
 Count1 = Count + 1;
 wrbuf2[0] = Count;
 memcpy(wrbuf2+1,p,Count);
 Execute2(); //???????? ??????? ??????
}
//---------------------------------------------------------------------------
void __fastcall TThreadWriter::Execute()
{
 DWORD temp, signal; //temp - переменная - заглушка
 overlappedwr.hEvent = CreateEvent(NULL, true, true, NULL); //создать событие
 WriteFile(COMport, wrbuf, strlen(wrbuf), &temp, &overlappedwr); //записать байты в порт
 signal = WaitForSingleObject(overlappedwr.hEvent, INFINITE); //приостановить поток, пока не выполнится операция WriteFile
 if((signal == WAIT_OBJECT_0) && (GetOverlappedResult(COMport, &overlappedwr, &temp, true)))
   fl = true; //если операция выполнилась успешно   //установить соответствующий флажок
 else
   fl = false;
// Synchronize(Printing); //вывод состояние
 CloseHandle(overlappedwr.hEvent);
}
//---------------------------------------------------------------------------
void __fastcall TThreadWriter::Execute2()
{
 DWORD temp, signal; //temp - переменная - заглушка
 overlappedwr.hEvent = CreateEvent(NULL, true, true, NULL); //создать событие
 WriteFile(COMport, wrbuf2, Count1, &temp, &overlappedwr); //записать байты в порт
 signal = WaitForSingleObject(overlappedwr.hEvent, INFINITE); //приостановить поток, пока не выполнится операция WriteFile
 if((signal == WAIT_OBJECT_0) && (GetOverlappedResult(COMport, &overlappedwr, &temp, true)))
   fl = true; //если операция выполнилась успешно   //установить соответствующий флажок
 else
   fl = false;
 CloseHandle(overlappedwr.hEvent);
}
//---------------------------------------------------------------------------
 