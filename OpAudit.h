//---------------------------------------------------------------------------

#ifndef OpAuditH
#define OpAuditH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <CheckLst.hpp>
#include <Buttons.hpp>
#include "mFormGroup.h"
#include "mFormOper.h"
#include <deque>
using namespace std;
//---------------------------------------------------------------------------
class TAuditForm : public TForm
{
__published:	// IDE-managed Components
  TPanel *Panel1;
  TPanel *Panel2;
  TPanel *Panel3;
  TPanel *Panel4;
  TLabel *Label1;
  TLabel *Label2;
  TLabel *Label3;
  TDrawGrid *DrawGrid1;
  TDrawGrid *DrawGrid2;
  TButton *NewGroups;
  TButton *EditGroup;
  TButton *DelGroup;
  TButton *AddOp;
  TButton *EditOp;
  TButton *DelOp;
  TCheckListBox *CheckListBox1;
  TBitBtn *BitBtn1;
  void __fastcall NewGroupsClick(TObject *Sender);
  void __fastcall EditGroupClick(TObject *Sender);
  void __fastcall DelGroupClick(TObject *Sender);
  void __fastcall AddOpClick(TObject *Sender);
  void __fastcall EditOpClick(TObject *Sender);
  void __fastcall DelOpClick(TObject *Sender);
  void __fastcall DrawGrid1Click(TObject *Sender);
  void __fastcall DrawGrid1DrawCell(TObject *Sender, int ACol, int ARow,
          TRect &Rect, TGridDrawState State);
  void __fastcall DrawGrid2Click(TObject *Sender);
  void __fastcall DrawGrid2DrawCell(TObject *Sender, int ACol, int ARow,
          TRect &Rect, TGridDrawState State);
private:	// User declarations
public:		// User declarations
  __fastcall TAuditForm(TComponent* Owner, TDataModule1 *DM1);
  AnsiString  GName;
  deque <Operator> GrOperators;
  int         GrIndex, OpIndex;
  int         GRight;
  TDataModule1  *DM;
};
//---------------------------------------------------------------------------
extern PACKAGE TAuditForm *AuditForm;
//---------------------------------------------------------------------------
#endif
