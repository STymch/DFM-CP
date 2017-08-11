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
  DWORD temp, mask, signal; //����������  temp ���� � ��������   ��������
  over.hEvent = CreateEvent(NULL, true, true, NULL); //������� �������; true,true - ��� ����������� ��������
  SetCommMask(comport, EV_RXCHAR); //����� = ���� ������ ����
  while(!Terminated) //���� ����� �� ����� ������� ����������� ����
  {
//    PortReadState = "����� WaitCommEvent";
    WaitCommEvent(comport, &mask, &over); //������� ������� �������� �����
//      PortReadState = "����� signal = WaitForSingleObject";
    signal = WaitForSingleObject(over.hEvent, INFINITE); //������� ����� �� ������ �����
//      PortReadState = "����� signal = WaitForSingleObject";
    if(signal == WAIT_OBJECT_0) //��� ������� ������� ����� ���������
    {
      if(GetOverlappedResult(comport, &over, &temp, true)) //���������, ������� �� ������������������� WaitCommEvent
        if((mask&EV_RXCHAR)!=0) //���� �������� ������ ������� ������ �����
        {
          ClearCommError(comport, &temp, &curstat); //����� ��������� ��������� COMSTAT
          btr = curstat.cbInQue; //�������� ���������� �������� ������
          if(btr > 32)
          {
             btr = 32;
             ErrCount++;
          }
          if(btr) //���� � ������ ����� ���� ������������� �����
          {
            try
            {
              csReadFromPort->Enter();  ///////////////////////////////////////////
              ReadFile(comport, bufrd, btr, &temp, &over); //��������� ����� �� ����� � ����� ���������
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
  CloseHandle(over.hEvent); //������� ������-�������
}
//---------------------------------------------------------------------------
