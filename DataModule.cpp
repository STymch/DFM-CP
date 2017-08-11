//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "DataModule.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "SDEngine"
#pragma resource "*.dfm"
TDataModule1 *DM;
//---------------------------------------------------------------------------
__fastcall TDataModule1::TDataModule1(TComponent* Owner)
  :TDataModule(Owner)
{
}
//---------------------------------------------------------------------------
/*
bool TDataModule1::InsertOperator(Operator *O)
{
  AnsiString S, S1;
  S1 = Trim((AnsiString)O->GroupName );
  S = "INSERT INTO Operators ";                                                       //(AnsiString)O->GroupName
  S += "(OpName, Password1, GroupName, SurName, Name, FName, UndeleteF) VALUES ";
  S += "('" + (AnsiString)O->OpName + "','" + (AnsiString)O->Password1 + "','" + (AnsiString)O->GroupName + "','" + (AnsiString)O->SurName + "','";
  S += (AnsiString)O->Name + "','"  + (AnsiString)O->FName + "'," + (AnsiString)O->UndeleteF + ");";
  if(!SQLWRITE(S))
  {
    return false;
  }
  return true;
}
//---------------------------------------------------------------------------
bool TDataModule1::UpdateOperator(Operator *O)
{
  AnsiString S, S1;

  S1 = Trim((AnsiString)O->GroupName );                                               // (AnsiString)O->GroupName
  S  = " UPDATE  Operators ";
  S += " SET Password1='" + (AnsiString)O->Password1 + "', GroupName = '" + (AnsiString)O->GroupName  + "', SurName = '";
  S += (AnsiString)O->SurName + "', Name = '" + (AnsiString)O->Name + "', FName = '" + (AnsiString)O->FName + "', UndeleteF = " + (AnsiString)O->UndeleteF;
  S += " WHERE OpName = '" + (AnsiString)O->OpName + "';";
  if(!SQLWRITE(S))
  {
    return false;
  }
  return true;
}
//---------------------------------------------------------------------------
bool TDataModule1::DelOperator(Operator *O)
{
  AnsiString S;
  S = "DELETE FROM Operators WHERE OpName = '" + (AnsiString)O->OpName + "';";
  if(!SQLWRITE(S))
  {
    return false;
  }
  return true;
}
//---------------------------------------------------------------------------
bool TDataModule1::InsertGroup(OpGroup *O)
{
	AnsiString S, S1;
	S = "INSERT INTO Groups ";
	S += "(GrName,PRights,GrFullName,UndeleteF) VALUES ";
	S += "('" + (AnsiString)O->GrName + "'," + (AnsiString)O->PRights + ",'" + (AnsiString)O->GrFullName + "'," + (AnsiString)O->UndeleteF + ");";
  if(!SQLWRITE(S))
  {
    return false;
  }
  return true;
}
//---------------------------------------------------------------------------
bool TDataModule1::UpdateGroup(OpGroup *O)
{
	AnsiString S;
	S  = " UPDATE  Groups ";
	S += " SET PRights=" + (AnsiString)O->PRights + ", GrFullName = '" + (AnsiString)O->GrFullName + "', UndeleteF = " + (AnsiString)O->UndeleteF;
  S += " WHERE GrName = '" + (AnsiString)O->GrName + "';";
  if(!SQLWRITE(S))
  {
    return false;
  }
  return true;
}
//---------------------------------------------------------------------------
bool TDataModule1::DelGroup(OpGroup *O)
{
  AnsiString S;
  S = "DELETE FROM Groups WHERE GrName = '" + (AnsiString)O->GrName + "';";
  if(!SQLWRITE(S))
  {
    return false;
  }
  return true;
}
//---------------------------------------------------------------------------
/////////////////////////////////////////////////////////////////////////////
bool TDataModule1::RestartDB(void)
{
  try
  {
    ADOConnection1->Connected = false;
    ADOConnection1->Connected = true;
  }
  catch(Exception &e)
  {
    ErrorString = e.Message;
    return false;
  }
  return true;
//---------------------------------------------------------------------------
/////////////////////////////////////////////////////////////////////////////
}
bool TDataModule1::ConnectionStringSetting(AnsiString DBName)
{
  AnsiString S, S1;
  int t, l, m;
  try
  {
    ADOConnection1->Connected = false;
    S = ADOConnection1->ConnectionString;
    t = S.AnsiPos("Initial Catalog");
    S1= S.SubString(t+15,S.Length()-t);
    l =S1.AnsiPos("=");
    m =S1.AnsiPos(";");
    S.Delete(t+15+l,m-l -1);
    S.Insert(DBName,t+15+l);
    ADOConnection1->ConnectionString = S;
    ADOConnection1->Connected = true;
  }
  catch(Exception &e)
  {
    ErrorString = e.Message;
    return false;
  }
  return true;
}
//---------------------------------------------------------------------------
bool TDataModule1::SQLWRITE(AnsiString SQLStr)
{
  try
  {
    ADOQuery1->SQL->Clear();
    ADOQuery1->SQL->Add(SQLStr);
    ADOQuery1->ExecSQL();
  }
  catch(Exception &e)
  {
    ErrorString = e.Message;
    return false;
  }
  return true;
}
//---------------------------------------------------------------------------
bool TDataModule1::SQLRead(AnsiString SQLStr)
{
  try
  {
    ADOQuery1->Close();
    ADOQuery1->SQL->Clear();
    ADOQuery1->SQL->Add(SQLStr);
    ADOQuery1->Open();
  }
  catch(Exception &e)
  {
    ErrorString = e.Message;
    return false;
  }
  return true;
}
*/
//---------------------------------------------------------------------------
bool TDataModule1::GroupsRead(AnsiString SQLStr)
{
  try
  {
    Query1->Close();
    Query1->SQL->Clear();
    Query1->SQL->Add(SQLStr);
    Query1->Open();
  }
  catch(Exception &e)
  {
    ErrorString = e.Message;
    return false;
  }
  return true;
}
//---------------------------------------------------------------------------
bool TDataModule1::OperatorsRead(AnsiString SQLStr)
{
  try
  {
    Query2->Close();
    Query2->SQL->Clear();
    Query2->SQL->Add(SQLStr);
    Query2->Open();
  }
  catch(Exception &e)
  {
    ErrorString = e.Message;
    return false;
  }
  return true;
}
//---------------------------------------------------------------------------
bool TDataModule1::ParametersRead(AnsiString SQLStr)
{
  try
  {
    Query3->Close();
    Query3->SQL->Clear();
    Query3->SQL->Add(SQLStr);
    Query3->Open();
  }
  catch(Exception &e)
  {
    ErrorString = e.Message;
    return false;
  }
  return true;
}
//---------------------------------------------------------------------------
bool TDataModule1::IsTableExist(AnsiString TableName)
{
  AnsiString   S, SS;
  TStringList* MyList;
  int          z;

  ErrorString = "";
  MyList = new TStringList;
  SS = TableName;
  try
  {
    ADOConnection1->GetTableNames(MyList, false);
  }
  catch(Exception &e)
  {
    ErrorString = e.Message;
    return false;
  }
  S = "";
  int k = -1;
  for(int i = 0; i < MyList->Count; i++)
  {
    S = MyList->Strings[i];
    z = S.AnsiPos(TableName);
    if(z != 0)
    {
      k = i;
      break;
    }
  }
  delete MyList;
  if(k == -1) return false;
  return true;
}
//---------------------------------------------------------------------------
AnsiString TDataModule1::ReplPunknaZP2(AnsiString SI)
{
  AnsiString S;
  S = "";
  for(int i = 1; i <= SI.Length(); i++)
  {
    if(SI[i] == '.') S += ',';
    else S += SI[i];
  }
  return S;
}
//---------------------------------------------------------------------------
AnsiString TDataModule1::ReplZPnaPunk2(AnsiString SI)           //float всегда с точкой
{
  AnsiString S;
  S = "";
  for(int i = 1; i <= SI.Length(); i++)
  {
    if(SI[i] == ',') S += '.';
    else S += SI[i];
  }
  return S;
}


//---------------------------------------------------------------------------
bool TDataModule1::InsertParametersPx(AnsiString S)
{
  try
  {
    Query3->Close();
    Query3->SQL->Clear();
    Query3->SQL->Add(S);
    Query3->Prepare();
    Query3->ExecSQL();
  }
  catch(Exception &exception)
  {
    Application->ShowException(&exception);
    Query3->Active = false;
    return false;
  }
  Query3->Close();
  return true;
}
//---------------------------------------------------------------------------
bool TDataModule1::InsertOperatorPx(Operator *O)
{
  AnsiString S, S1;
  S1 = O->Password1; for(int i = 1; i <= S1.Length(); i++) S1[i] = S1[i] - i;

  S = "INSERT INTO Operators.db (OpName, Password1, GroupName, SurName, Name, Fname, UndeleteF) VALUES ";
  S += "('" + (AnsiString)O->OpName + "','" + S1 + "','" + (AnsiString)O->GroupName + "','" + (AnsiString)O->SurName;
  S +=  "','" + (AnsiString)O->Name + "','" + (AnsiString)O->Name +"'," + O->UndeleteF + ")";
  try
  {
    Query2->Close();
    Query2->SQL->Clear();
    Query2->SQL->Add(S);
    Query2->Prepare();
//    Query2->ParamByName("OpName")->AsString = O->OpName;
//    S1 = O->Password1;
//    for(int i = 1; i <= S1.Length(); i++)
//      S1[i] = S1[i] - i;

//    Query1->ParamByName("Password1")->AsString  = S1;
//    Query1->ParamByName("GroupName")->AsString  = O->GroupName;
//    Query1->ParamByName("UndeleteF")->AsBoolean = O->UndeleteF;
    Query2->ExecSQL();
  }
  catch(Exception &exception)
  {
    Application->ShowException(&exception);
    Query2->Active = false;
    return false;
  }
  Query2->Close();
  return true;
}
//---------------------------------------------------------------------------
bool TDataModule1::UpdateOperatorPx(Operator *O)
{
  AnsiString S, S1;

  S1 = O->Password1; for(int i = 1; i <= S1.Length(); i++) S1[i] = S1[i] - i;
  S  = " UPDATE  Operators.db ";
  S += " SET Password1='" + S1 + "',SurName = '" + (AnsiString)O->SurName + "', Name = '" + (AnsiString)O->Name + "', FName = '" + (AnsiString)O->Name + "', UndeleteF = " + (AnsiString)O->UndeleteF;
  S += " WHERE OpName = '" + (AnsiString)O->OpName + "';";
  try
  {
    Query1->Close();
    Query1->SQL->Clear();
    Query1->SQL->Add(S);
//    Query1->ParamByName("OpName")->AsString    = O->OpName;
//     S1 = O->Password1;
    Query1->Prepare();
//   Query1->ParamByName("Password1")->AsString  = S1;
//    Query1->ParamByName("GroupName")->AsString  = O->GroupName;
//    Query1->ParamByName("UndeleteF")->AsBoolean = O->UndeleteF;
    Query1->ExecSQL();
  }
  catch(Exception &exception)
  {
    Application->ShowException(&exception);
    Query1->Active = false;
    return false;
  }
  Query1->Close();
  return true;
}
//---------------------------------------------------------------------------
bool TDataModule1::DelOperatorPx(Operator *O)
{
  AnsiString S;
  S = "DELETE FROM Operators.DB WHERE OpName = :OpName";
  try
  {
    Query1->Active = false;
    Query1->SQL->Clear();
    Query1->SQL->Add(S);
    Query1->Prepare();
    Query1->ParamByName("OpName")->AsString  = O->OpName;
		Query1->ExecSQL();
  }
  catch(Exception &exception)
  {
    Application->ShowException(&exception);
    Query1->Active = false;
    return false;
  }
  Query1->Active = false;
  return true;
}
//---------------------------------------------------------------------------
bool TDataModule1::InsertGroupPx(OpGroup *O)
{
  AnsiString S, S1;
  S = "INSERT INTO Groups.db ";
  S += "(GrName,PRights,GrFullName,UndeleteF) VALUES ";
  S += "('" + (AnsiString)O->GrName +"'," + O->PRights + ",'" + (AnsiString)O->GrFullName +"'," + O->UndeleteF + ")";
//  S += "(:GrName,:PRights,:GrFullName,:UndeleteF)";
  try
  {
    Query1->Close();
    Query1->SQL->Clear();
    Query1->SQL->Add(S);
//    Query1->ParamByName("GrName")->AsString     = O->GrName;
//    Query1->ParamByName("PRights")->AsInteger   = O->PRights;
//    Query1->ParamByName("GrFullName")->AsString  = O->GrFullName;
//    Query1->ParamByName("UndeleteF")->AsInteger = O->UndeleteF;
    Query1->Prepare();
    Query1->ExecSQL();
  }
  catch(Exception &exception)
  {
    Application->ShowException(&exception);
    Query1->Active = false;
    return false;
  }
  Query1->Close();
  return true;
}
//---------------------------------------------------------------------------
bool TDataModule1::UpdateGroupPx(OpGroup *O)
{
  AnsiString S;
  S  = " UPDATE  Groups.db ";
  S += " SET PRights= " + (AnsiString)O->PRights + ", GrFullName = '" + (AnsiString)O->GrFullName + "', UndeleteF = " + (AnsiString)O->UndeleteF;
  S += " WHERE GrName = '" + (AnsiString)O->GrName + "';";
  try
  {
    Query1->Close();
    Query1->SQL->Clear();
    Query1->SQL->Add(S);
//    Query1->ParamByName("GrName")->AsString     = O->GrName;
//    Query1->ParamByName("PRights")->AsInteger   = O->PRights;
//    Query1->ParamByName("GrFullName")->AsString = O->GrFullName;
//    Query1->ParamByName("UndeleteF")->AsBoolean = O->UndeleteF;
    Query1->ExecSQL();
  }
  catch(Exception &exception)
  {
    Application->ShowException(&exception);
    Query1->Active = false;
    return false;
  }
  Query1->Close();
  return true;
}
//---------------------------------------------------------------------------
bool TDataModule1::DelGroupPx(OpGroup *O)
{
  AnsiString S;
  S = "DELETE FROM Groups.DB WHERE GrName = :GrName";
  try
  {
    Query1->Active = false;
    Query1->SQL->Clear();
    Query1->SQL->Add(S);
    Query1->Prepare();
    Query1->ParamByName("GrName")->AsString  = O->GrName;
    Query1->ExecSQL();
  }
  catch(Exception &exception)
  {
    Application->ShowException(&exception);
    Query1->Active = false;
    return false;
  }
  Query1->Active = false;
  return true;
}
//---------------------------------------------------------------------------
double TDataModule1::Round(double Value, int Precision)
{
  int i, Mod;
  double D;
  long M;
  try
  {
    i = 0; Mod = 1;
    while(i < Precision)
    {
      Mod *= 10;
      i++;
    }
    D = Value * Mod;
    M = floor(D);
    if((D - (double)M) > 0.5)
      M++;
    D = (double)M / Mod;
  }
  catch(...)
  {
    return Value;
  }
  return D;
}
//---------------------------------------------------------------------------
bool TDataModule1::PGroupsBaseExist(void)
{
  DM->Table1->Active = false; // The Table component must not be active
  DM->Table1->TableType = ttParadox;
  DM->Table1->TableName = "Groups.db";
  if (!DM->Table1->Exists) // Don't overwrite an existing table
    return false;
  else
    return true;
 }
//---------------------------------------------------------------------------
bool TDataModule1::POperatorsBaseExist(void)
{
  DM->Table2->Active = false; // The Table component must not be active
  DM->Table2->TableType = ttParadox;
  DM->Table2->TableName = "Operators.db";
  if (!DM->Table2->Exists) // Don't overwrite an existing table
    return false;
  else
    return true;
 }
//---------------------------------------------------------------------------
bool TDataModule1::PParametersBaseExist(void)
{
  DM->Table3->Active = false; // The Table component must not be active
  DM->Table3->TableType = ttParadox;
  DM->Table3->TableName = "Parameters.db";
  if (!DM->Table3->Exists) // Don't overwrite an existing table
    return false;
  else
    return true;
 }
//---------------------------------------------------------------------------
bool TDataModule1::PGroupsBaseCreated(void)
{
  DM->Table1->FieldDefs->Clear();
  TFieldDef *pNewDef = DM->Table1->FieldDefs->AddFieldDef();

  pNewDef->Name = "GrName";
  pNewDef->DataType = ftString;
  pNewDef->Size = 24;
  pNewDef->Required = true;

  pNewDef = DM->Table1->FieldDefs->AddFieldDef();
  pNewDef->Name = "PRights";
  pNewDef->DataType = ftInteger;
  pNewDef->Required = true;

  pNewDef = DM->Table1->FieldDefs->AddFieldDef();
  pNewDef->Name = "GrFullName";
  pNewDef->DataType = ftString;
  pNewDef->Size = 64;
  pNewDef->Required = true;

  pNewDef = DM->Table1->FieldDefs->AddFieldDef();
  pNewDef->Name = "UndeleteF";
  pNewDef->DataType = ftInteger;

  DM->Table1->IndexDefs->Clear();
  try
  {
    DM->Table1->CreateTable();
  }
  catch(...)
  {
    Application->MessageBox("Не создан объект Groups.DB!", "АПУС",	MB_ICONERROR);
    return false;
  }
  return true;
}
//---------------------------------------------------------------------------
bool TDataModule1::POperatorsBaseCreated(void)
{
  DM->Table2->FieldDefs->Clear();
  TFieldDef *pNewDef = DM->Table2->FieldDefs->AddFieldDef();

  // describe the fields in the table

  pNewDef->Name = "OpName";
  pNewDef->DataType = ftString;
  pNewDef->Size = 24;
  pNewDef->Required = true;

  pNewDef = DM->Table2->FieldDefs->AddFieldDef();
  pNewDef->Name = "Password1";
  pNewDef->DataType = ftString;
  pNewDef->Size = 24;
  pNewDef->Required = true;

  pNewDef = DM->Table2->FieldDefs->AddFieldDef();
  pNewDef->Name = "GroupName";
  pNewDef->DataType = ftString;
  pNewDef->Size = 24;
  pNewDef->Required = true;

  pNewDef = DM->Table2->FieldDefs->AddFieldDef();
  pNewDef->Name = "SurName";
  pNewDef->DataType = ftString;
  pNewDef->Size = 24;
  pNewDef->Required = true;

  pNewDef = DM->Table2->FieldDefs->AddFieldDef();
  pNewDef->Name = "Name";
  pNewDef->DataType = ftString;
  pNewDef->Size = 24;
  pNewDef->Required = true;

  pNewDef = DM->Table2->FieldDefs->AddFieldDef();
  pNewDef->Name = "FName";
  pNewDef->DataType = ftString;
  pNewDef->Size = 24;
  pNewDef->Required = true;

  pNewDef = DM->Table2->FieldDefs->AddFieldDef();
  pNewDef->Name = "UndeleteF";
  pNewDef->DataType = ftInteger;

  DM->Table2->IndexDefs->Clear();
  try
  {
    DM->Table2->CreateTable();
  }
  catch(...)
  {
    Application->MessageBox("Не создан объект Groups.DB!", "АПУС",	MB_ICONERROR);
    return false;
  }
  return true;
}
//---------------------------------------------------------------------------
bool TDataModule1::PParametersBaseCreated(void)
{
  DM->Table3->FieldDefs->Clear();

  TFieldDef *pNewDef = DM->Table3->FieldDefs->AddFieldDef(); pNewDef->Name = "Qn10a"; pNewDef->DataType = ftString;    pNewDef->Size = 8;   pNewDef->Required = true;
  pNewDef = DM->Table3->FieldDefs->AddFieldDef(); pNewDef->Name = "DQn10Kta"; pNewDef->DataType = ftString; pNewDef->Size = 8;   pNewDef->Required = true;
  pNewDef = DM->Table3->FieldDefs->AddFieldDef(); pNewDef->Name = "DQt10Kma"; pNewDef->DataType = ftString; pNewDef->Size = 12;  pNewDef->Required = true;
  pNewDef = DM->Table3->FieldDefs->AddFieldDef(); pNewDef->Name = "Qn10b";   pNewDef->DataType = ftString; pNewDef->Size = 12;   pNewDef->Required = true;
  pNewDef = DM->Table3->FieldDefs->AddFieldDef(); pNewDef->Name = "DQn10Ktb";      pNewDef->DataType = ftString;  pNewDef->Size = 12;  pNewDef->Required = true;
  pNewDef = DM->Table3->FieldDefs->AddFieldDef(); pNewDef->Name = "DQt10Kmb";     pNewDef->DataType = ftString;  pNewDef->Size = 12;  pNewDef->Required = true;
//------------------------------------------------------------------------------
  pNewDef = DM->Table3->FieldDefs->AddFieldDef(); pNewDef->Name = "Qn15a"; pNewDef->DataType = ftString; pNewDef->Size = 8;   pNewDef->Required = true;
  pNewDef = DM->Table3->FieldDefs->AddFieldDef(); pNewDef->Name = "DQn15Kta"; pNewDef->DataType = ftString; pNewDef->Size = 8;  pNewDef->Required = true;
  pNewDef = DM->Table3->FieldDefs->AddFieldDef(); pNewDef->Name = "DQt15Kma";   pNewDef->DataType = ftString; pNewDef->Size = 12;    pNewDef->Required = true;
  pNewDef = DM->Table3->FieldDefs->AddFieldDef(); pNewDef->Name = "Qn15b";      pNewDef->DataType = ftString;  pNewDef->Size = 12; pNewDef->Required = true;
  pNewDef = DM->Table3->FieldDefs->AddFieldDef(); pNewDef->Name = "DQn15Ktb";     pNewDef->DataType = ftString;  pNewDef->Size = 12; pNewDef->Required = true;
  pNewDef = DM->Table3->FieldDefs->AddFieldDef(); pNewDef->Name = "DQt15Kmb";     pNewDef->DataType = ftString;  pNewDef->Size = 12;  pNewDef->Required = true;
//------------------------------------------------------------------------------
  pNewDef = DM->Table3->FieldDefs->AddFieldDef(); pNewDef->Name = "Qn20a"; pNewDef->DataType = ftString; pNewDef->Size = 8;   pNewDef->Required = true;
  pNewDef = DM->Table3->FieldDefs->AddFieldDef(); pNewDef->Name = "DQn20Kta"; pNewDef->DataType = ftString; pNewDef->Size = 8;  pNewDef->Required = true;
  pNewDef = DM->Table3->FieldDefs->AddFieldDef(); pNewDef->Name = "DQt20Kma";   pNewDef->DataType = ftString; pNewDef->Size = 12;    pNewDef->Required = true;
  pNewDef = DM->Table3->FieldDefs->AddFieldDef(); pNewDef->Name = "Qn20b";      pNewDef->DataType = ftString;  pNewDef->Size = 12; pNewDef->Required = true;
  pNewDef = DM->Table3->FieldDefs->AddFieldDef(); pNewDef->Name = "DQn20Ktb";     pNewDef->DataType = ftString;  pNewDef->Size = 12; pNewDef->Required = true;
  pNewDef = DM->Table3->FieldDefs->AddFieldDef(); pNewDef->Name = "DQt20Kmb";     pNewDef->DataType = ftString;  pNewDef->Size = 12;  pNewDef->Required = true;
//------------------------------------------------------------------------------
  pNewDef = DM->Table3->FieldDefs->AddFieldDef(); pNewDef->Name = "QnE101"; pNewDef->DataType = ftString; pNewDef->Size = 8;   pNewDef->Required = true;
  pNewDef = DM->Table3->FieldDefs->AddFieldDef(); pNewDef->Name = "DQn10Kt1"; pNewDef->DataType = ftString; pNewDef->Size = 8;  pNewDef->Required = true;
  pNewDef = DM->Table3->FieldDefs->AddFieldDef(); pNewDef->Name = "DQt10Km1";   pNewDef->DataType = ftString; pNewDef->Size = 12;    pNewDef->Required = true;
  pNewDef = DM->Table3->FieldDefs->AddFieldDef(); pNewDef->Name = "QnE102";      pNewDef->DataType = ftString;  pNewDef->Size = 12; pNewDef->Required = true;
  pNewDef = DM->Table3->FieldDefs->AddFieldDef(); pNewDef->Name = "DQn10Kt2";     pNewDef->DataType = ftString;  pNewDef->Size = 12; pNewDef->Required = true;
  pNewDef = DM->Table3->FieldDefs->AddFieldDef(); pNewDef->Name = "DQt10Km2";     pNewDef->DataType = ftString;  pNewDef->Size = 12;  pNewDef->Required = true;
//------------------------------------------------------------------------------
  pNewDef = DM->Table3->FieldDefs->AddFieldDef(); pNewDef->Name = "QnE151"; pNewDef->DataType = ftString; pNewDef->Size = 8;   pNewDef->Required = true;
  pNewDef = DM->Table3->FieldDefs->AddFieldDef(); pNewDef->Name = "DQn15Kt1"; pNewDef->DataType = ftString; pNewDef->Size = 8;  pNewDef->Required = true;
  pNewDef = DM->Table3->FieldDefs->AddFieldDef(); pNewDef->Name = "DQt15Km1";   pNewDef->DataType = ftString; pNewDef->Size = 12;    pNewDef->Required = true;
  pNewDef = DM->Table3->FieldDefs->AddFieldDef(); pNewDef->Name = "QnE152";      pNewDef->DataType = ftString;  pNewDef->Size = 12; pNewDef->Required = true;
  pNewDef = DM->Table3->FieldDefs->AddFieldDef(); pNewDef->Name = "DQn15Kt2";     pNewDef->DataType = ftString;  pNewDef->Size = 12; pNewDef->Required = true;
  pNewDef = DM->Table3->FieldDefs->AddFieldDef(); pNewDef->Name = "DQt15Km2";     pNewDef->DataType = ftString;  pNewDef->Size = 12;  pNewDef->Required = true;
//------------------------------------------------------------------------------
  pNewDef = DM->Table3->FieldDefs->AddFieldDef(); pNewDef->Name = "QnE201"; pNewDef->DataType = ftString; pNewDef->Size = 8;   pNewDef->Required = true;
  pNewDef = DM->Table3->FieldDefs->AddFieldDef(); pNewDef->Name = "DQn20Kt1"; pNewDef->DataType = ftString; pNewDef->Size = 8;  pNewDef->Required = true;
  pNewDef = DM->Table3->FieldDefs->AddFieldDef(); pNewDef->Name = "DQt20Km1";   pNewDef->DataType = ftString; pNewDef->Size = 12;    pNewDef->Required = true;
  pNewDef = DM->Table3->FieldDefs->AddFieldDef(); pNewDef->Name = "QnE202";      pNewDef->DataType = ftString;  pNewDef->Size = 12; pNewDef->Required = true;
  pNewDef = DM->Table3->FieldDefs->AddFieldDef(); pNewDef->Name = "DQn20Kt2";     pNewDef->DataType = ftString;  pNewDef->Size = 12; pNewDef->Required = true;
  pNewDef = DM->Table3->FieldDefs->AddFieldDef(); pNewDef->Name = "DQt20Km2";     pNewDef->DataType = ftString;  pNewDef->Size = 12;  pNewDef->Required = true;
//------------------------------------------------------------------------------
  pNewDef = DM->Table3->FieldDefs->AddFieldDef(); pNewDef->Name = "PISOQmX1"; pNewDef->DataType = ftString; pNewDef->Size = 8;   pNewDef->Required = true;
  pNewDef = DM->Table3->FieldDefs->AddFieldDef(); pNewDef->Name = "PISOQmG1"; pNewDef->DataType = ftString; pNewDef->Size = 8;  pNewDef->Required = true;
  pNewDef = DM->Table3->FieldDefs->AddFieldDef(); pNewDef->Name = "PISOQtX1";   pNewDef->DataType = ftString; pNewDef->Size = 12;    pNewDef->Required = true;
  pNewDef = DM->Table3->FieldDefs->AddFieldDef(); pNewDef->Name = "PISOQtG1";      pNewDef->DataType = ftString;  pNewDef->Size = 12; pNewDef->Required = true;
  pNewDef = DM->Table3->FieldDefs->AddFieldDef(); pNewDef->Name = "PISOQnX1";     pNewDef->DataType = ftString;  pNewDef->Size = 12; pNewDef->Required = true;
  pNewDef = DM->Table3->FieldDefs->AddFieldDef(); pNewDef->Name = "PISOQnG1";     pNewDef->DataType = ftString;  pNewDef->Size = 12;  pNewDef->Required = true;
//------------------------------------------------------------------------------
  pNewDef = DM->Table3->FieldDefs->AddFieldDef(); pNewDef->Name = "PISOQmX2"; pNewDef->DataType = ftString; pNewDef->Size = 8;   pNewDef->Required = true;
  pNewDef = DM->Table3->FieldDefs->AddFieldDef(); pNewDef->Name = "PISOQmG2"; pNewDef->DataType = ftString; pNewDef->Size = 8;  pNewDef->Required = true;
  pNewDef = DM->Table3->FieldDefs->AddFieldDef(); pNewDef->Name = "PISOQtX2";   pNewDef->DataType = ftString; pNewDef->Size = 12;    pNewDef->Required = true;
  pNewDef = DM->Table3->FieldDefs->AddFieldDef(); pNewDef->Name = "PISOQtG2";      pNewDef->DataType = ftString;  pNewDef->Size = 12; pNewDef->Required = true;
  pNewDef = DM->Table3->FieldDefs->AddFieldDef(); pNewDef->Name = "PISOQnX2";     pNewDef->DataType = ftString;  pNewDef->Size = 12; pNewDef->Required = true;
  pNewDef = DM->Table3->FieldDefs->AddFieldDef(); pNewDef->Name = "PISOQnG2";     pNewDef->DataType = ftString;  pNewDef->Size = 12;  pNewDef->Required = true;
//------------------------------------------------------------------------------
  pNewDef = DM->Table3->FieldDefs->AddFieldDef(); pNewDef->Name = "POIMLQmX1"; pNewDef->DataType = ftString; pNewDef->Size = 8;   pNewDef->Required = true;
  pNewDef = DM->Table3->FieldDefs->AddFieldDef(); pNewDef->Name = "POIMLQmG1"; pNewDef->DataType = ftString; pNewDef->Size = 8;  pNewDef->Required = true;
  pNewDef = DM->Table3->FieldDefs->AddFieldDef(); pNewDef->Name = "POIMLQtX1";   pNewDef->DataType = ftString; pNewDef->Size = 12;    pNewDef->Required = true;
  pNewDef = DM->Table3->FieldDefs->AddFieldDef(); pNewDef->Name = "POIMLQtG1";      pNewDef->DataType = ftString;  pNewDef->Size = 12; pNewDef->Required = true;
  pNewDef = DM->Table3->FieldDefs->AddFieldDef(); pNewDef->Name = "POIMLQnX1";     pNewDef->DataType = ftString;  pNewDef->Size = 12; pNewDef->Required = true;
  pNewDef = DM->Table3->FieldDefs->AddFieldDef(); pNewDef->Name = "POIMLQnG1";     pNewDef->DataType = ftString;  pNewDef->Size = 12;  pNewDef->Required = true;
//------------------------------------------------------------------------------
  pNewDef = DM->Table3->FieldDefs->AddFieldDef(); pNewDef->Name = "POIMLQmX2"; pNewDef->DataType = ftString; pNewDef->Size = 8;   pNewDef->Required = true;
  pNewDef = DM->Table3->FieldDefs->AddFieldDef(); pNewDef->Name = "POIMLQmG2"; pNewDef->DataType = ftString; pNewDef->Size = 8;  pNewDef->Required = true;
  pNewDef = DM->Table3->FieldDefs->AddFieldDef(); pNewDef->Name = "POIMLQtX2";   pNewDef->DataType = ftString; pNewDef->Size = 12;    pNewDef->Required = true;
  pNewDef = DM->Table3->FieldDefs->AddFieldDef(); pNewDef->Name = "POIMLQtG2";      pNewDef->DataType = ftString;  pNewDef->Size = 12; pNewDef->Required = true;
  pNewDef = DM->Table3->FieldDefs->AddFieldDef(); pNewDef->Name = "POIMLQnX2";     pNewDef->DataType = ftString;  pNewDef->Size = 12; pNewDef->Required = true;
  pNewDef = DM->Table3->FieldDefs->AddFieldDef(); pNewDef->Name = "POIMLQnG2";     pNewDef->DataType = ftString;  pNewDef->Size = 12;  pNewDef->Required = true;
//------------------------------------------------------------------------------
  pNewDef = DM->Table3->FieldDefs->AddFieldDef(); pNewDef->Name = "POLDQmXA"; pNewDef->DataType = ftString; pNewDef->Size = 8;   pNewDef->Required = true;
  pNewDef = DM->Table3->FieldDefs->AddFieldDef(); pNewDef->Name = "POLDQmGA"; pNewDef->DataType = ftString; pNewDef->Size = 8;  pNewDef->Required = true;
  pNewDef = DM->Table3->FieldDefs->AddFieldDef(); pNewDef->Name = "POLDQtXA";   pNewDef->DataType = ftString; pNewDef->Size = 12;    pNewDef->Required = true;
  pNewDef = DM->Table3->FieldDefs->AddFieldDef(); pNewDef->Name = "POLDQtGA";      pNewDef->DataType = ftString;  pNewDef->Size = 12; pNewDef->Required = true;
  pNewDef = DM->Table3->FieldDefs->AddFieldDef(); pNewDef->Name = "POLDQnXA";     pNewDef->DataType = ftString;  pNewDef->Size = 12; pNewDef->Required = true;
  pNewDef = DM->Table3->FieldDefs->AddFieldDef(); pNewDef->Name = "POLDQnGA";     pNewDef->DataType = ftString;  pNewDef->Size = 12;  pNewDef->Required = true;
//------------------------------------------------------------------------------
  pNewDef = DM->Table3->FieldDefs->AddFieldDef(); pNewDef->Name = "POLDQmXB"; pNewDef->DataType = ftString; pNewDef->Size = 8;   pNewDef->Required = true;
  pNewDef = DM->Table3->FieldDefs->AddFieldDef(); pNewDef->Name = "POLDQmGB"; pNewDef->DataType = ftString; pNewDef->Size = 8;  pNewDef->Required = true;
  pNewDef = DM->Table3->FieldDefs->AddFieldDef(); pNewDef->Name = "POLDQtXB";   pNewDef->DataType = ftString; pNewDef->Size = 12;    pNewDef->Required = true;
  pNewDef = DM->Table3->FieldDefs->AddFieldDef(); pNewDef->Name = "POLDQtGB";      pNewDef->DataType = ftString;  pNewDef->Size = 12; pNewDef->Required = true;
  pNewDef = DM->Table3->FieldDefs->AddFieldDef(); pNewDef->Name = "POLDQnXB";     pNewDef->DataType = ftString;  pNewDef->Size = 12; pNewDef->Required = true;
  pNewDef = DM->Table3->FieldDefs->AddFieldDef(); pNewDef->Name = "POLDQnGB";     pNewDef->DataType = ftString;  pNewDef->Size = 12;  pNewDef->Required = true;
//------------------------------------------------------------------------------
  pNewDef = DM->Table3->FieldDefs->AddFieldDef(); pNewDef->Name = "QminLGr"; pNewDef->DataType = ftString; pNewDef->Size = 8;   pNewDef->Required = true;
  pNewDef = DM->Table3->FieldDefs->AddFieldDef(); pNewDef->Name = "QminRGr"; pNewDef->DataType = ftString; pNewDef->Size = 8;  pNewDef->Required = true;
  pNewDef = DM->Table3->FieldDefs->AddFieldDef(); pNewDef->Name = "QtLGr";   pNewDef->DataType = ftString; pNewDef->Size = 12;    pNewDef->Required = true;
  pNewDef = DM->Table3->FieldDefs->AddFieldDef(); pNewDef->Name = "QtRGr";      pNewDef->DataType = ftString;  pNewDef->Size = 12; pNewDef->Required = true;
  pNewDef = DM->Table3->FieldDefs->AddFieldDef(); pNewDef->Name = "QnLGr";     pNewDef->DataType = ftString;  pNewDef->Size = 12; pNewDef->Required = true;
  pNewDef = DM->Table3->FieldDefs->AddFieldDef(); pNewDef->Name = "QnRGr";     pNewDef->DataType = ftString;  pNewDef->Size = 12;  pNewDef->Required = true;
//------------------------------------------------------------------------------
  pNewDef = DM->Table3->FieldDefs->AddFieldDef(); pNewDef->Name = "TXolL"; pNewDef->DataType = ftString; pNewDef->Size = 8;   pNewDef->Required = true;
  pNewDef = DM->Table3->FieldDefs->AddFieldDef(); pNewDef->Name = "TXolR"; pNewDef->DataType = ftString; pNewDef->Size = 8;  pNewDef->Required = true;
  pNewDef = DM->Table3->FieldDefs->AddFieldDef(); pNewDef->Name = "TGorL";   pNewDef->DataType = ftString; pNewDef->Size = 12;    pNewDef->Required = true;
  pNewDef = DM->Table3->FieldDefs->AddFieldDef(); pNewDef->Name = "TGorR";      pNewDef->DataType = ftString;  pNewDef->Size = 12; pNewDef->Required = true;
  pNewDef = DM->Table3->FieldDefs->AddFieldDef(); pNewDef->Name = "VKonst";     pNewDef->DataType = ftString;  pNewDef->Size = 12; pNewDef->Required = true;
  pNewDef = DM->Table3->FieldDefs->AddFieldDef(); pNewDef->Name = "TimeConst";     pNewDef->DataType = ftString;  pNewDef->Size = 12;  pNewDef->Required = true;
 DM->Table3->IndexDefs->Clear();
  try
  {
    DM->Table3->CreateTable();
  }
  catch(...)
  {
    Application->MessageBox("Не создан объект Groups.DB!", "АПУС",	MB_ICONERROR);
    return false;
  }
  return true;
}
//---------------------------------------------------------------------------
/*
//Cоздание таблицы операторов___________________________________________________
  DM->Table1->Active = false; // The Table component must not be active
  DM->Table1->TableType = ttParadox;
  DM->Table1->TableName = "Groups";
  if (!DM->Table1->Exists) // Don't overwrite an existing table
  {
  // describe the fields in the table
    DM->Table1->FieldDefs->Clear();
    TFieldDef *pNewDef = DM->Table1->FieldDefs->AddFieldDef();
    pNewDef->Name = "GrName";
    pNewDef->DataType = ftString;
    pNewDef->Size = 16;
    pNewDef->Required = true;

    pNewDef = DM->Table1->FieldDefs->AddFieldDef();
    pNewDef->Name = "PRights";
    pNewDef->DataType = ftInteger;
    pNewDef->Required = true;

    pNewDef = DM->Table1->FieldDefs->AddFieldDef();
    pNewDef->Name = "GrFullName";
    pNewDef->DataType = ftString;
    pNewDef->Size = 64;
    pNewDef->Required = true;

    pNewDef = DM->Table1->FieldDefs->AddFieldDef();
    pNewDef->Name = "UndeleteF";
    pNewDef->DataType = ftBoolean;

    DM->Table1->IndexDefs->Clear();
    try
    {
      DM->Table1->CreateTable();
    }
    catch(...)
    {
  		Application->MessageBox("Не создан объект Groups.DB!", "АПУС",	MB_ICONERROR);
      SelfCloseFlag = true;
      return;
    }
    strcpy(G.GrName, "Администраторы");
    G.PRights = 0xFFFFFFFF;
    strcpy(G.GrFullName, "Системные администраторы");
    G.UndeleteF = true;
    DM->InsertGroup(&G);
  }
  DM->Table2->Active = false; // The Table component must not be active
  DM->Table2->TableType = ttParadox;
  DM->Table2->TableName = "Operators";
  if (!DM->Table2->Exists) // Don't overwrite an existing table
  {
  // describe the fields in the table
    DM->Table2->FieldDefs->Clear();
    TFieldDef *pNewDef = DM->Table2->FieldDefs->AddFieldDef();
    pNewDef->Name = "OpName";
    pNewDef->DataType = ftString;
    pNewDef->Size = 16;
    pNewDef->Required = true;

    pNewDef = DM->Table2->FieldDefs->AddFieldDef();
    pNewDef->Name = "Password1";
    pNewDef->DataType = ftString;
    pNewDef->Size = 16;
    pNewDef->Required = true;

    pNewDef = DM->Table2->FieldDefs->AddFieldDef();
    pNewDef->Name = "GroupName";
    pNewDef->DataType = ftString;
    pNewDef->Size = 16;
    pNewDef->Required = true;

    pNewDef = DM->Table2->FieldDefs->AddFieldDef();
    pNewDef->Name = "UndeleteF";
    pNewDef->DataType = ftBoolean;

    DM->Table2->IndexDefs->Clear();
    try
    {
      DM->Table2->CreateTable();
    }
    catch(...)
    {
      Application->MessageBox("Не создан объект Operators.DB!", "АПУС",	MB_ICONERROR);
      SelfCloseFlag = true;
      return;
    }
    strcpy(O.OpName, "Admin");
    strcpy(O.Password1, "pass");
    strcpy(O.GroupName, "Администраторы");
    O.UndeleteF = true;
    DM->InsertOperator(&O);
  }
  //таблица операторов уже создана
  FeelOperatorsTable();
  FeelGroupsTable();
*/
//---------------------------------------------------------------------------
