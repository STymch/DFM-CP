//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "OpAudit.h"
#include "MainP.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TAuditForm *AuditForm;
char *GroupTitle[] =  {"��� ������","��������"};
char *OperTitle[]  =  {"��� ���������","������"};
//extern deque <Operator>  OpList;
//extern deque <OpGroup>   GrList;

//---------------------------------------------------------------------------
__fastcall TAuditForm::TAuditForm(TComponent* Owner, TDataModule1 *DM1)
  : TForm(Owner)
{
  GrIndex = OpIndex = -1;
  DM = DM1;
}
//---------------------------------------------------------------------------

void __fastcall TAuditForm::NewGroupsClick(TObject *Sender)
{
  OpGroup G;
  G.PRights = 0;
  if(!(DM->OpRights & rApEdit)) return;
  FormGroup = new TFormGroup(this, DM, true);
  FormGroup->Caption = "������� ������ ����������";
  for(int i = 0; i < CheckListBox1->Count; i++)
  {
    FormGroup->CheckListBox1->Items->Add(CheckListBox1->Items->Strings[i]);
  }
  if(FormGroup->ShowModal() == ID_OK)
  {
    strcpy(G.GrName, Trim(FormGroup->Edit1->Text).c_str());
    strcpy(G.GrFullName, Trim(FormGroup->Memo1->Text).c_str());
    G.UndeleteF = FormGroup->CheckBox1->Checked;
    int j = 1;
    for(int i = 0; i < CheckListBox1->Count; i++)
    {
      if(FormGroup->CheckListBox1->Checked[i])
        G.PRights = G.PRights | j;
      j = j << 1;
    }
    if(!DM->InsertGroupPx(&G))
    {
      Application->MessageBox("�� ���� �������� ����� ������!","�PUS",MB_OK| MB_ICONERROR);
      return;
    }
    DM->GrList.push_back(G);
    DrawGrid1->Refresh();
  }
  delete FormGroup;
}
//---------------------------------------------------------------------------
void __fastcall TAuditForm::EditGroupClick(TObject *Sender)
{
  int     j;
  OpGroup G;

  if(!(DM->OpRights & rApEdit)) return;
  if( GrIndex == -1) return;
  G = DM->GrList[GrIndex];
  FormGroup = new TFormGroup(this, DM, false);
  FormGroup->Caption = "������������� ������ ����������";
  FormGroup->BitBtn1->Caption = "�������������";
  for(int i = 0; i < CheckListBox1->Count; i++)
  {
    FormGroup->CheckListBox1->Items->Add(CheckListBox1->Items->Strings[i]);
  }
  j = 1;
  for(int i = 0; i < CheckListBox1->Count; i++)
  {
    if(G.PRights & j)
      FormGroup->CheckListBox1->Checked[i] = true;
    j = j << 1;
  }
  AnsiString S;
//  for(int z = 0; z < 24; z++) S += G.GrName[z];  //  FormGroup->Edit1->Text = (AnsiString)G.GrName;
  S = G.GrName;   S = S.SubString(1,24);
  FormGroup->Edit1->Text = Trim(S);
  FormGroup->Memo1->Text = G.GrFullName;
  FormGroup->CheckBox1->Checked = G.UndeleteF;
  if(FormGroup->ShowModal() == ID_OK)
  {
    strcpy(G.GrName, Trim(FormGroup->Edit1->Text).c_str());
    strcpy(G.GrFullName, Trim(FormGroup->Memo1->Text).c_str());
    G.UndeleteF = FormGroup->CheckBox1->Checked;
    G.PRights = 0;
    int j = 1;
    for(int i = 0; i < CheckListBox1->Count; i++)
    {
      if(FormGroup->CheckListBox1->Checked[i])
        G.PRights = G.PRights | j;
      j = j << 1;
    }
    if(!DM->UpdateGroupPx(&G))
    {
      Application->MessageBox("�� ���� �������� ���������� ������!","�PUS",MB_OK| MB_ICONERROR);
      return;
    }
    DM->GrList[GrIndex].PRights   = G.PRights;
    DM->GrList[GrIndex].UndeleteF = G.UndeleteF;
    strcpy(DM->GrList[GrIndex].GrFullName, G.GrFullName);
    DrawGrid1->Refresh();
  }
  delete FormGroup;
}
//---------------------------------------------------------------------------

void __fastcall TAuditForm::DelGroupClick(TObject *Sender)
{
  AnsiString S, S1;

  int Index;
  if(!(DM->OpRights & rApEdit)) return;
  GName = DM->GrList[GrIndex].GrName; //��� ������
  if(GName == DM->GroupName)
  {
    Application->MessageBox("������ ������� ����������� ������!","�PUS",MB_OK| MB_ICONERROR);
    return;
  }
  for(int i = 0; i < (int)DM->GrList.size(); i++)
  {
    S = DM->GrList[i].GrName;  S = Trim(S.SubString(1,24));
//    if(strcmp(DM->GrList[i].GrName, GName.c_str()) == 0)
    if((S.c_str(), GName.c_str()) == 0)
    {
      if((S.c_str(), "��������������") == 0)
      {
        Application->MessageBox("������ ������� ������ '��������������'!","�PUS",MB_OK| MB_ICONERROR);
        return;
      }
//      if((DM->GrList[i].UndeleteF)&&(DM->CurOpName != "�������������"))
      if((DM->GrList[i].UndeleteF)&&(DM->OpName != "�������������"))
      {
        Application->MessageBox("����������� ������ ����� ������� ������ �������������!","�PUS",MB_OK| MB_ICONERROR);
        return;
      }
      for(int j = 0; j < (int)DM->OpList.size(); j++)
      {
        S1 = DM->GrList[j].GrName;
        S1 = Trim(S1.SubString(1,24));
//        if(strcmp(DM->OpList[j].GroupName, GName.c_str()) == 0)
//        if((strcmp(S1.c_str, GName.c_str()) == 0)
        if(S1 == GName)
        {
          Application->MessageBox("� ������ ������ ������ ���������, ������� ������� ��!","�PUS",MB_OK| MB_ICONERROR);
          return;
        }
      }
      Index = i;
      break;
    }
  }
  if(!DM->DelGroupPx(&DM->GrList[Index]))
  {
     Application->MessageBox("�� ���� ������� ������!","�PUS",MB_OK| MB_ICONERROR);
     return;
  }
  DM->GrList.erase(DM->GrList.begin() + Index);
  DrawGrid1->Refresh();
  Application->MessageBox("������ ������� �������!","�PUS",MB_OK| MB_ICONERROR);
}
//---------------------------------------------------------------------------

void __fastcall TAuditForm::AddOpClick(TObject *Sender)
{
  Operator O;
  AnsiString S1;

  if(GrIndex == -1) return;
  
  if(!(DM->OpRights & rApEdit)) return;
  FormOperator = new TFormOperator(this, DM, true);
  FormOperator->Caption = "������� ���������";
  S1 = (AnsiString)DM->GrList[GrIndex].GrName;  S1 = Trim(S1.SubString(1,24));
//  FormOperator->Edit3->Text = Trim((AnsiString)DM->GrList[GrIndex].GrName);
  FormOperator->Edit3->Text = S1;
  if(FormOperator->ShowModal() == ID_OK)
  {
    strcpy(O.OpName, Trim(FormOperator->Edit1->Text).c_str());
    strcpy(O.Password1, Trim(FormOperator->Edit2->Text).c_str());
    strcpy(O.SurName, Trim(FormOperator->Edit4->Text).c_str());
    strcpy(O.Name, Trim(FormOperator->Edit5->Text).c_str());
    strcpy(O.FName, Trim(FormOperator->Edit6->Text).c_str());
    O.UndeleteF = FormOperator->CheckBox1->Checked;
//    strcpy(O.GroupName, DM->GrList[GrIndex].GrName);
    strcpy(O.GroupName, S1.c_str());
    if(!DM->InsertOperatorPx(&O))
    {
      Application->MessageBox("�� ���� �������� ������ ���������!","�PUS",MB_OK| MB_ICONERROR);
      return;
    }
    DM->OpList.push_back(O);
    DrawGrid2->Refresh();
  }
  delete FormOperator;
}
//---------------------------------------------------------------------------

void __fastcall TAuditForm::EditOpClick(TObject *Sender)
{
  Operator O;

  OpIndex = DrawGrid2->Row -1;
  if(OpIndex == -1) return;
  FormOperator = new TFormOperator(this, DM, false);
  FormOperator->Caption = "������������� ���������";
  FormOperator->BitBtn1->Caption = "�������������";
  FormOperator->Edit1->Text        = GrOperators[OpIndex].OpName;
  FormOperator->Edit2->Text        = GrOperators[OpIndex].Password1;
  FormOperator->Edit3->Text        = GrOperators[OpIndex].GroupName;
  FormOperator->Edit4->Text        = GrOperators[OpIndex].SurName;
  FormOperator->Edit5->Text        = GrOperators[OpIndex].Name;
  FormOperator->Edit6->Text        = GrOperators[OpIndex].FName;
  FormOperator->CheckBox1->Checked = GrOperators[OpIndex].UndeleteF;
//  if(!(((DM->OpRights & rApEdit)) || ((AnsiString)GrOperators[OpIndex].OpName == DM->CurOpName))) return;
  if(!(((DM->OpRights & rApEdit)) || ((AnsiString)GrOperators[OpIndex].OpName == DM->OpName))) return;

  if(FormOperator->ShowModal() == ID_OK)
  {
    strcpy(O.OpName, Trim(FormOperator->Edit1->Text).c_str());
    strcpy(O.Password1, Trim(FormOperator->Edit2->Text).c_str());
    strcpy(O.GroupName, Trim(FormOperator->Edit3->Text).c_str());
    strcpy(O.SurName, Trim(FormOperator->Edit4->Text).c_str());
    strcpy(O.Name, Trim(FormOperator->Edit5->Text).c_str());
    strcpy(O.FName, Trim(FormOperator->Edit6->Text).c_str());
    O.UndeleteF = FormOperator->CheckBox1->Checked;
    if(!DM->UpdateOperatorPx(&O))
    {
      Application->MessageBox("�� ���� �������� ��������� ���������!","�PUS",MB_OK| MB_ICONERROR);
      return;
    }
    for(int i = 0; i < (int)DM->OpList.size(); i++)
    {
      if(strcmp(DM->OpList[i].OpName,O.OpName) == 0)
      {
        strcpy(DM->OpList[i].Password1, O.Password1);
        strcpy(DM->OpList[i].SurName, O.SurName);
        strcpy(DM->OpList[i].Name, O.Name);
        strcpy(DM->OpList[i].FName, O.FName);
        DM->OpList[i].UndeleteF = O.UndeleteF;
        DrawGrid2->Refresh();
        break;
      }
    }
  }
  delete FormOperator;
}
//---------------------------------------------------------------------------

void __fastcall TAuditForm::DelOpClick(TObject *Sender)
{
  Operator O;
  int      Index;

  if(!(DM->OpRights & rApEdit)) return;
  if(DM->GrList.size() == 0) return;
  Index = DrawGrid2->Row - 1;
//  O = GrOperators[GrIndex];
  O = GrOperators[Index];
//  if(strcmp(O.OpName, DM->CurOpName.c_str()) == 0)
  if(strcmp(O.OpName, DM->OpName.c_str()) == 0)
  {
    Application->MessageBox("������ ������� ������ ���� - ���������!","�PUS",MB_OK| MB_ICONERROR);
    return;
  }
//  if((O.UndeleteF)&&(DM->CurOpName != "�������������"))
  if((O.UndeleteF)&&(DM->OpName != "�������������"))
  {
    Application->MessageBox("������������ ��������� ����� ������� ������ �������������!","�PUS",MB_OK| MB_ICONERROR);
    return;
  }
  if(!DM->DelOperatorPx(&O))
  {
     Application->MessageBox("�� ���� ������� ���������!","�PUS",MB_OK| MB_ICONERROR);
     return;
  }
  for(int i = 0; i < (int)DM->OpList.size(); i++)
  {
    if(strcmp(DM->OpList[i].OpName, O.OpName) == 0)
    {
       DM->OpList.erase(DM->OpList.begin() + i);
       DrawGrid1Click(NULL);
       Application->MessageBox("�������� ������� ������!","�PUS",MB_OK| MB_ICONWARNING);
       DrawGrid2->Refresh();
        return;
    }
  }
  return;
}
//---------------------------------------------------------------------------
void __fastcall TAuditForm::DrawGrid1Click(TObject *Sender)
{
  AnsiString S1;

  if(DM->GrList.size() == 0) return;
  GrOperators.erase(GrOperators.begin(), GrOperators.end());
  GrIndex = DrawGrid1->Row -1;
  GName = DM->GrList[GrIndex].GrName;
  GName = Trim(GName.SubString(1,24));
  GRight = DM->GrList[GrIndex].PRights;
  for(int i = 0; i < (int)DM->OpList.size(); i++)
  {
    S1 = DM->OpList[i].GroupName;
    S1 =  Trim(S1.SubString(1,24));
    if(S1 == GName)
//    if(Trim((AnsiString)DM->OpList[i].GroupName) == GName)
       GrOperators.push_back(DM->OpList[i]);
  }
  DrawGrid2->Refresh();
  int j = 1;
  for(int i = 0; i < CheckListBox1->Count; i++)
  {
    if(GRight & j)
      CheckListBox1->Checked[i] = true;
    else
      CheckListBox1->Checked[i] = false;
    j = j << 1;
  }
}
//---------------------------------------------------------------------------

void __fastcall TAuditForm::DrawGrid1DrawCell(TObject *Sender, int ACol,
      int ARow, TRect &Rect, TGridDrawState State)
{
	AnsiString S;

	if(DM->GrList.size())
	{
	  DrawGrid1->RowCount = DM->GrList.size() + 1;
	  if(ARow)
	  {
  		switch (ACol)
  		{
  		  case 0:
                    S = "";
                    S = DM->GrList[ARow - 1].GrName;
                    S = S.SubString(1,24);
//    		    S = DM->GrList[ARow - 1].GrName;
  		  break;
  		  case 1:
    		    S = DM->GrList[ARow - 1].GrFullName;
  		  break;
  		}
  		DrawGrid1->Canvas->TextOut(Rect.Left+5,Rect.Top+2,S);
    }
	}
	else
	{
		DrawGrid1->FixedRows = 1;
		DrawGrid1->RowCount = 2;
	}
	if(!ARow)
		DrawGrid1->Canvas->TextOut(Rect.Left+2,Rect.Top+2,GroupTitle[ACol]);
}
//---------------------------------------------------------------------------
void __fastcall TAuditForm::DrawGrid2Click(TObject *Sender)
{
  if(GrOperators.size() == 0) return;
  OpIndex = DrawGrid2->Row -1;
}
//---------------------------------------------------------------------------

void __fastcall TAuditForm::DrawGrid2DrawCell(TObject *Sender, int ACol,
      int ARow, TRect &Rect, TGridDrawState State)
{
	AnsiString S;

	if(GrOperators.size())
	{
	  DrawGrid2->RowCount = GrOperators.size() + 1;
	  if(ARow)
	  {
  		switch (ACol)
  		{
  		  case 0:
    			S = GrOperators[ARow - 1].OpName;
  		  break;
  		  case 1:
    			S = GrOperators[ARow - 1].GroupName;
  		  break;
  		}
  		DrawGrid2->Canvas->TextOut(Rect.Left+5,Rect.Top+2,S);
    }
	}
	else
	{
		DrawGrid2->FixedRows = 1;
		DrawGrid2->RowCount = 2;
	}
	if(!ARow)
		DrawGrid2->Canvas->TextOut(Rect.Left+2,Rect.Top+2,OperTitle[ACol]);
}
//---------------------------------------------------------------------------


