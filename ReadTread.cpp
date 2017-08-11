//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ReadTread.h"
#pragma package(smart_init)
//#define WM_PROGRESS               WM_USER+14
TThreadReader *reader;
extern  OVERLAPPED over;
//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall reader::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
#define BUFSIZE 255 //??????? ??????
//unsigned char bufrd[BUFSIZE], bufwr[BUFSIZE]; //???????? ? ?????????? ??????
///---------------------------------------------------------------------------

__fastcall TThreadReader::TThreadReader(bool CreateSuspended)
        : TThread(CreateSuspended)
{
 void __fastcall Execute(); //???????? ??????? ??????
}
//---------------------------------------------------------------------------

__fastcall TThreadReader::TThreadReader(bool CreateSuspended, HANDLE A)
        : TThread(CreateSuspended)
{
  comport = A;
  ErrCount = 0;
  BCount = 0;
  SendetCount = 0; //////
  DT = Now();
  csReadFromPort = new TCriticalSection();
  void __fastcall Execute();
}
//---------------------------------------------------------------------------
void __fastcall TThreadReader::Execute()
{
  COMSTAT curstat;
  DWORD temp, mask, signal; //переменная  temp ется в качестве   заглушки
  over.hEvent = CreateEvent(NULL, true, true, NULL); //создаем событие; true,true - для асинхронных операций
  SetCommMask(comport, EV_RXCHAR); //маска = если принят байт
  while(!Terminated) //пока поток не будет прерван выполняется цикл
  {
//    PortReadState = "перед WaitCommEvent";
    WaitCommEvent(comport, &mask, &over); //ожидать событие принятия байта
//      PortReadState = "перед signal = WaitForSingleObject";
    signal = WaitForSingleObject(over.hEvent, INFINITE); //усыпить поток до приема байта
//      PortReadState = "после signal = WaitForSingleObject";
    if(signal == WAIT_OBJECT_0) //ели событие прихода байта произошло
    {
      if(GetOverlappedResult(comport, &over, &temp, true)) //проверяем, успешно ли выполняетсяоперация WaitCommEvent
        if((mask&EV_RXCHAR)!=0) //если прозошло именно событие приема байта
        {
          ClearCommError(comport, &temp, &curstat); //нужно заполнить структуру COMSTAT
          btr = curstat.cbInQue; //получить количество принятых байтов
          if(btr > 32)
          {
             btr = 32;
             ErrCount++;
          }
          if(btr) //если в буфере порта есть непрочитанные байты
          {
            try
            {
              csReadFromPort->Enter();  ///////////////////////////////////////////
              ReadFile(comport, bufrd, btr, &temp, &over); //прочитать байты из порта в буфер программы
              DT = Now();
              memcpy(Cbufrd + BCount, &bufrd, btr);
              if(Cbufrd[0] != 31)
              {
                BCount = 0;
                ErrCount++;
              }
              else
              {
                BCount += btr;
                if(BCount == 32)
                {
                  BCount = 0;
                  SendMessage(Form1Handle, WM_PROGRESS, 1, 1);
                  SendetCount++;
                }
                if(BCount > 32)
                {
                  SendMessage(Form1Handle, WM_PROGRESS, 1, 1);
                  SendetCount++;
                  memcpy(&Cbufrd, Cbufrd + (BCount - 32), BCount - 32);
                  if(Cbufrd[0] != 31)
                  {
                    BCount = 0;
                  }
                }
              }
              csReadFromPort->Leave();  ///////////////////////////////////////////
            }
            catch(...)
            {
            }
          }
        }
    }
  }
  CloseHandle(over.hEvent); //закрыть объект-событие
}
//---------------------------------------------------------------------------
