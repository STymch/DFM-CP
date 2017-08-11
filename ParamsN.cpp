//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ParamsN.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TParamsForm *ParamsForm;
//---------------------------------------------------------------------------
AnsiString ReplZPnaPunk0(AnsiString SI)           //float всегда с точкой
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
AnsiString ReplPunknaZP0(AnsiString SI)           //float всегда с точкой
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
__fastcall TParamsForm::TParamsForm(TComponent* Owner, TDataModule1  *TDM, int R )
        : TForm(Owner)
{
  if(!(DM->OpRights & R))
  {
    CloseWithOutSaving = true;
    Qn10a->Enabled = false;     //Qn  d10 klassa A
    DQn10Kta->Enabled = false;   //процент Qt k Qn 10 mm klass A
    DQt10Kma->Enabled = false;   //процент Qm k Qn 10 mm klass A

    Qn10b->Enabled = false;     //Qn  d10 klassa B
    DQn10Ktb->Enabled = false;   //процент Qt k Qn 10 mm klass B
    DQt10Kmb->Enabled = false;   //процент Qm k Qn 10 mm klass B

    Qn15a->Enabled = false;     //Qn  d15 klassa A
    DQn15Kta->Enabled = false;   //процент Qt k Qn 15 mm klass A
    DQt15Kma->Enabled = false;  //процент Qm k Qn 15 mm klass A

    Qn15b->Enabled = false;     //Qn  d15 klassa B
    DQn15Ktb->Enabled = false;  //процент Qt k Qn 15 mm klass B
    DQt15Kmb->Enabled = false;  //процент Qm k Qn 15 mm klass B

    Qn20a->Enabled = false;     //Qn  d20 klassa A
    DQn20Kta->Enabled = false;  //процент Qt k Qn 20 mm klass A
    DQt20Kma->Enabled = false;   //процент Qm k Qn 20 mm klass A

    Qn20b->Enabled = false;     //Qn  d20 klassa B
    DQn20Ktb->Enabled = false;   //процент Qt k Qn 20 mm klass B
    DQt20Kmb->Enabled = false;   //процент Qm k Qn 20 mm klass B

    QnE101->Enabled = false;    //Qn  d101 klassa 1
    DQn10Kt1->Enabled = false;   //процент Qt k Qn 10 mm klass 1
    DQt10Km1->Enabled = false;   //процент Qm k Qn 10 mm klass 1

    QnE102->Enabled = false;     //Qn  d20 klassa 2
    DQn10Kt2->Enabled = false;   //процент Qt k Qn 10 mm klass 2
    DQt10Km2->Enabled = false;   //процент Qm k Qn 10 mm klass 2

    QnE151->Enabled = false;     //Qn  d15 klassa 1
    DQn15Kt1->Enabled = false;   //процент Qt k Qn 15 mm klass 1
    DQt15Km1->Enabled = false;   //процент Qm k Qn 15 mm klass 1

    QnE152->Enabled = false;    //Qn  d15 klassa 2
    DQn15Kt2->Enabled = false;   //процент Qt k Qn 15 mm klass 2
    DQt15Km2->Enabled = false;   //процент Qm k Qn 15 mm klass 2

    QnE201->Enabled = false;     //Qn  d20 klassa 1
    DQn20Kt1->Enabled = false;   //процент Qt k Qn 20 mm klass 1
    DQt20Km1->Enabled = false;   //процент Qm k Qn 20 mm klass 1

    QnE202->Enabled = false;    //Qn  d20 klassa 2
    DQn20Kt2->Enabled = false;   //процент Qt k Qn 20 mm klass 2
    DQt20Km2->Enabled = false;   //процент Qm k Qn 20 mm klass 2
  //Погрешности  1
    PISOQmX1->Enabled = false;   //pogreschnost
  //2
    PISOQmG1->Enabled = false;   //pogreschnost
  //3
    PISOQtX1->Enabled = false; //pogreschnost
  //4
    PISOQtG1->Enabled = false;   //pogreschnost
  //5
    PISOQnX1->Enabled = false;   //pogreschnost
  //6
    PISOQnG1->Enabled = false;  //pogreschnost
  //7
   PISOQmX2->Enabled = false;   //pogreschnost
  //8
   PISOQmG2->Enabled = false;   //pogreschnost
  //9
   PISOQtX2->Enabled = false;   //pogreschnost
  //10
   PISOQtG2->Enabled = false;   //pogreschnost
  //11
   PISOQnX2->Enabled = false;   //pogreschnost
  //12
   PISOQnG2->Enabled = false;   //pogreschnost
  //LCNE OIML R 49-1
  //1
   POIMLQmX1->Enabled = false; //pogreschnost
  //2
   POIMLQmG1->Enabled = false;   //pogreschnost
  //3
   POIMLQtX1->Enabled = false;   //pogreschnost
  //4
   POIMLQtG1->Enabled = false;   //pogreschnost
  //5
   POIMLQnX1->Enabled = false;   //pogreschnost
  //6
   POIMLQnG1->Enabled = false;   //pogreschnost
  //7
   POIMLQmX2->Enabled = false;   //pogreschnost
  //8
   POIMLQmG2->Enabled = false;   //pogreschnost
  //9
   POIMLQtX2->Enabled = false;   //pogreschnost
  //10
   POIMLQtG2->Enabled = false;   //pogreschnost
  //11
   POIMLQnX2->Enabled = false;   //pogreschnost
  //12
   POIMLQnG2->Enabled = false;   //pogreschnost
  //ДСТУ 3580
   POLDQmXA->Enabled = false;   //pogreschnost
  //2
   POLDQmGA->Enabled = false;   //pogreschnost
  //3
   POLDQtXA->Enabled = false;   //pogreschnost
  //4
   POLDQtGA->Enabled = false;   //pogreschnost
  //5
   POLDQnXA->Enabled = false;   //pogreschnost
  //6
   POLDQnGA->Enabled = false;   //pogreschnost
  //7
   POLDQmXB->Enabled = false;   //pogreschnost
  //8
   POLDQmGB->Enabled = false;   //pogreschnost
  //9
   POLDQtXB->Enabled = false;   //pogreschnost
  //10
   POLDQtGB->Enabled = false;   //pogreschnost
  //11
   POLDQnXB->Enabled = false;   //pogreschnost
  //12
   POLDQnGB->Enabled = false;   //pogreschnost

   QminLGr->Enabled = false;    //Qmin left grenc
   QminRGr->Enabled = false;    //Qmin recht grenc
   QtLGr->Enabled = false;      //Qt left grenc
   QtRGr->Enabled = false;     //Qt recht grenc
   QnLGr->Enabled = false;      //Qn left grenc
   QnRGr->Enabled = false;      //Qn recht grenc

   TXolL->Enabled = false;      //Tchol  left grenc
   TXolR->Enabled = false;     //Tchol  recht grenc
   TGorL->Enabled = false;      //TGor  left grenc
   TGorR->Enabled = false;      //TGor  recht grenc

   VKonst->Enabled = false;     //V konstant
   TimeConst->Enabled = false;   //T constant
  }
//  SetCopiDate();
}
//---------------------------------------------------------------------------
void  TParamsForm::SetCopiDate(void)
{
  Ad10a = d10a->Text;       //d10 klassa A
  ADk10a = Dk10a->Text;      //klass Simbol
  AQn10a = Qn10a->Text;      //Qn  d10 klassa A
  ADQn10Kta = DQn10Kta->Text;   //процент Qt k Qn 10 mm klass A
  ADQt10Kma = DQt10Kma->Text;   //процент Qm k Qn 10 mm klass A

  Ad10b = d10b->Text;       //d10 klassa B
  ADk10b = Dk10b->Text;      //klass Simbol
  AQn10b = Qn10b->Text;      //Qn  d10 klassa B
  ADQn10Ktb = DQn10Ktb->Text;   //процент Qt k Qn 10 mm klass B
  ADQt10Kmb = DQt10Kmb->Text;   //процент Qm k Qn 10 mm klass B

  Ad15a = d15a->Text;       //d15 klassa A
  ADk15a = Dk15a->Text;      //klass Simbol
  AQn15a = Qn15a->Text;      //Qn  d15 klassa A
  ADQn15Kta = DQn15Kta->Text;   //процент Qt k Qn 15 mm klass A
  ADQt15Kma = DQt15Kma->Text;   //процент Qm k Qn 15 mm klass A

  Ad15b = d15b->Text;       //d15 klassa b
  ADk15b = Dk15b->Text;      //klass Simbol
  AQn15b = Qn15b->Text;      //Qn  d15 klassa B
  ADQn15Ktb = DQn15Ktb->Text;   //процент Qt k Qn 15 mm klass B
  ADQt15Kmb = DQt15Kmb->Text;   //процент Qm k Qn 15 mm klass B

  Ad20a = d20a->Text;       //d20 klassa A
  ADk20a = Dk20a->Text;      //klass Simbol
  AQn20a = Qn20a->Text;      //Qn  d20 klassa A
  ADQn20Kta = DQn20Kta->Text;   //процент Qt k Qn 20 mm klass A
  ADQt20Kma = DQt20Kma->Text;   //процент Qm k Qn 20 mm klass A

  Ad20b = d20b->Text;       //d20 klassa B
  ADk20b = Dk20b->Text;      //klass Simbol
  AQn20b = Qn20b->Text;      //Qn  d20 klassa B
  ADQn20Ktb = DQn20Ktb->Text;   //процент Qt k Qn 20 mm klass B
  ADQt20Kmb = DQt20Kmb->Text;   //процент Qm k Qn 20 mm klass B

  AdE101 = dE101->Text;      //d10 klassa 1
  AEk101 = Ek101->Text;      //klass Simbol
  AQnE101 = QnE101->Text;     //Qn  d10 klassa 1
  ADQn10Kt1 = DQn10Kt1->Text;   //процент Qt k Qn 10 mm klass 1
  ADQt10Km1 = DQt10Km1->Text;   //процент Qm k Qn 10 mm klass 1

  AdE102 = dE102->Text;      //d10 klassa 2
  AEk102 = Ek102->Text;      //klass Simbol
  AQnE102 = QnE102->Text;     //Qn  d10 klassa 2
  ADQn10Kt2 = DQn10Kt2->Text;   //процент Qt k Qn 10 mm klass 2
  ADQt10Km2 = DQt10Km2->Text;   //процент Qm k Qn 10 mm klass 2

  AdE151 = dE151->Text;      //d15 klassa 1
  AEk151 = Ek151->Text;      //klass Simbol
  AQnE151 = QnE151->Text;     //Qn  d15 klassa 1
  ADQn15Kt1 = DQn15Kt1->Text;   //процент Qt k Qn 15 mm klass 1
  ADQt15Km1 = DQt15Km1->Text;   //процент Qm k Qn 15 mm klass 1

  AdE152 = dE152->Text;      //d15 klassa 2
  AEk152 = Ek152->Text;      //klass Simbol
  AQnE152 = QnE152->Text;     //Qn  d15 klassa 2
  ADQn15Kt2 = DQn15Kt2->Text;   //процент Qt k Qn 15 mm klass 2
  ADQt15Km2 = DQt15Km2->Text;   //процент Qm k Qn 15 mm klass 2

  AdE201 = dE201->Text;      //d20 klassa 1
  AEk201 = Ek201->Text;      //klass Simbol
  AQnE201 = QnE201->Text;     //Qn  d20 klassa 1
  ADQn20Kt1 = DQn20Kt1->Text;   //процент Qt k Qn 20 mm klass 1
  ADQt20Km1 = DQt20Km1->Text;   //процент Qm k Qn 20 mm klass 1

  AdE202 = dE202->Text;      //d20 klassa 2
  AEk202 = Ek202->Text;      //klass Simbol
  AQnE202 = QnE202->Text;     //Qn  d20 klassa 2
  ADQn20Kt2 = DQn20Kt2->Text;   //процент Qt k Qn 20 mm klass 2
  ADQt20Km2 = DQt20Km2->Text;   //процент Qm k Qn 20 mm klass 2
  //Погрешности  1
  AKlISOQmX1 = KlISOQmX1->Text;  //klass Simbol EN ISO
  AQISOQmX1 = QISOQmX1->Text;   //tip proliva - Qm
  AVISOQmX1 = VISOQmX1->Text;   //tip vody
  APISOQmX1 = PISOQmX1->Text;   //pogreschnost
  //2
  AKlISOQmG1 = KlISOQmG1->Text;  //klass Simbol EN ISO
  AQISOQmG1 = QISOQmG1->Text;   //tip proliva - Qm
  AVISOQmG1 = VISOQmG1->Text;   //tip vody
  APISOQmG1 = PISOQmG1->Text;   //pogreschnost
  //3
  AKlISOQtX1 = KlISOQtX1->Text;  //klass Simbol EN ISO
  AQISOQtX1 = QISOQtX1->Text;   //tip proliva - Qt
  AVISOQtX1 = VISOQtX1->Text;   //tip vody
  APISOQtX1 = PISOQtX1->Text;   //pogreschnost
  //4
  AKlISOQtG1 = KlISOQtG1->Text;  //klass Simbol EN ISO
  AQISOQtG1 = QISOQtG1->Text;   //tip proliva - Qt
  AVISOQtG1 = VISOQtG1->Text;   //tip vody
  APISOQtG1 = PISOQtG1->Text;   //pogreschnost
  //5
  AKlISOQnX1 = KlISOQnX1->Text;  //klass Simbol EN ISO
  AQISOQnX1 = QISOQnX1->Text;   //tip proliva - Qn
  AVISOQnX1 = VISOQnX1->Text;   //tip vody
  APISOQnX1 = PISOQnX1->Text;   //pogreschnost
  //6
  AKlISOQnG1 = KlISOQnG1->Text;  //klass Simbol EN ISO
  AQISOQnG1 = QISOQnG1->Text;   //tip proliva - Qn
  AVISOQnG1 = VISOQnG1->Text;   //tip vody
  APISOQnG1 = PISOQnG1->Text;   //pogreschnost
  //7
  AKlISOQmX2 = KlISOQmX2->Text; //klass Simbol EN ISO
  AQISOQmX2 = QISOQmX2->Text;   //tip proliva - Qm
  AVISOQmX2 = VISOQmX2->Text;   //tip vody
  APISOQmX2 = PISOQmX2->Text;   //pogreschnost
  //8
  AKlISOQmG2 = KlISOQmG2->Text;  //klass Simbol EN ISO
  AQISOQmG2 = QISOQmG2->Text;   //tip proliva - Qm
  AVISOQmG2 = VISOQmG2->Text;   //tip vody
  APISOQmG2 = PISOQmG2->Text;   //pogreschnost
  //9
  AKlISOQtX2 = KlISOQtX2->Text;   //klass Simbol EN ISO
  AQISOQtX2 = QISOQtX2->Text;   //tip proliva - Qt
  AVISOQtX2 = VISOQtX2->Text;   //tip vody
  APISOQtX2 = PISOQtX2->Text;   //pogreschnost
  //10
  AKlISOQtG2 = KlISOQtG2->Text;  //klass Simbol EN ISO
  AQISOQtG2 = QISOQtG2->Text;   //tip proliva - Qt
  AVISOQtG2 = VISOQtG2->Text;   //tip vody
  APISOQtG2 = PISOQtG2->Text;   //pogreschnost
  //11
  AKlISOQnX2 = KlISOQnX2->Text;  //klass Simbol EN ISO
  AQISOQnX2 = QISOQnX2->Text;   //tip proliva - Qn
  AVISOQnX2 = VISOQnX2->Text;    //tip vody
  APISOQnX2 = PISOQnX2->Text;   //pogreschnost
  //12
  AKlISOQnG2 = KlISOQnG2->Text;  //klass Simbol EN ISO
  AQISOQnG2 = QISOQnG2->Text;   //tip proliva - Qn
  AVISOQnG2 = VISOQnG2->Text;   //tip vody
  APISOQnG2 = PISOQnG2->Text;   //pogreschnost
  //LCNE OIML R 49-1
  //1
  AKlOIMLQmX1 = KlOIMLQmX1->Text; //klass Simbol LCNE OIML R 49-1
  AQOIMLQmX1 = QOIMLQmX1->Text;  //tip proliva - Qm
  AVOIMLQmX1 = VOIMLQmX1->Text;  //tip vody
  APOIMLQmX1 = POIMLQmX1->Text;  //pogreschnost
  //2
  AKlOIMLQmG1 = KlOIMLQmG1->Text;  //klass Simbol OIML R 49-1
  AQOIMLQmG1 = QOIMLQmG1->Text;   //tip proliva - Qm
  AVOIMLQmG1 = VOIMLQmG1->Text;   //tip vody
  APOIMLQmG1 = POIMLQmG1->Text;   //pogreschnost
  //3
  AKlOIMLQtX1 = KlOIMLQtX1->Text;  //klass Simbol OIML R 49-1
  AQOIMLQtX1 = QOIMLQtX1->Text;   //tip proliva - Qt
  AVOIMLQtX1 = VOIMLQtX1->Text;   //tip vody
  APOIMLQtX1 = POIMLQtX1->Text;   //pogreschnost
  //4
  AKlOIMLQtG1 = KlOIMLQtG1->Text;  //klass Simbol OIML R 49-1
  AQOIMLQtG1 = QOIMLQtG1->Text;   //tip proliva - Qt
  AVOIMLQtG1 = VOIMLQtG1->Text;   //tip vody
  APOIMLQtG1 = POIMLQtG1->Text;   //pogreschnost
  //5
  AKlOIMLQnX1 = KlOIMLQnX1->Text;  //klass Simbol OIML R 49-1
  AQOIMLQnX1 = QOIMLQnX1->Text;   //tip proliva - Qn
  AVOIMLQnX1 = VOIMLQnX1->Text;   //tip vody
  APOIMLQnX1 = POIMLQnX1->Text;   //pogreschnost
  //6
  AKlOIMLQnG1 = KlOIMLQnG1->Text;  //klass Simbol OIML R 49-1
  AQOIMLQnG1 = QOIMLQnG1->Text;   //tip proliva - Qn    QOIMLQnG1
  AVOIMLQnG1 = VOIMLQnG1->Text;   //tip vody
  APOIMLQnG1 = POIMLQnG1->Text;   //pogreschnost
  //7
  AKlOIMLQmX2 = KlOIMLQmX2->Text;  //klass Simbol OIML R 49-1
  AQOIMLQmX2 = QOIMLQmX2->Text;   //tip proliva - Qm
  AVOIMLQmX2 = VOIMLQmX2->Text;   //tip vody
  APOIMLQmX2 = POIMLQmX2->Text;   //pogreschnost
  //8
  AKlOIMLQmG2 = KlOIMLQmG2->Text;  //klass Simbol OIML R 49-1
  AQOIMLQmG2 = QOIMLQmG2->Text;   //tip proliva - Qm
  AVOIMLQmG2 = VOIMLQmG2->Text;   //tip vody
  APOIMLQmG2 = POIMLQmG2->Text;   //pogreschnost
  //9
  AKlOIMLQtX2 = KlOIMLQtX2->Text;   //klass Simbol OIML R 49-1
  AQOIMLQtX2 = QOIMLQtX2->Text;   //tip proliva - Qt
  AVOIMLQtX2 = VOIMLQtX2->Text;   //tip vody
  APOIMLQtX2 = POIMLQtX2->Text;   //pogreschnost
  //10
  AKlOIMLQtG2 = KlOIMLQtG2->Text;  //klass Simbol OIML R 49-1
  AQOIMLQtG2 = QOIMLQtG2->Text;   //tip proliva - Qt
  AVOIMLQtG2 = VOIMLQtG2->Text;   //tip vody
  APOIMLQtG2 = POIMLQtG2->Text;   //pogreschnost
  //11
  AKlOIMLQnX2 = KlOIMLQnX2->Text;  //klass Simbol OIML R 49-1  AKlOIMLQnX2
  AQOIMLQnX2 = QOIMLQnX2->Text;   //tip proliva - Qn
  AVOIMLQnX2 = VOIMLQnX2->Text;   //tip vody
  APOIMLQnX2 = POIMLQnX2->Text;   //pogreschnost
  //12
  AKlOIMLQnG2 = KlOIMLQnG2->Text;  //klass Simbol OIML R 49-1
  AQOIMLQnG2 = QOIMLQnG2->Text;   //tip proliva - Qn
  AVOIMLQnG2 = VOIMLQnG2->Text;   //tip vody
  APOIMLQnG2 = POIMLQnG2->Text;   //pogreschnost
  //ДСТУ 3580
  AKlOLDQmXA = KlOLDQmXA->Text;  //klass Simbol ДСТУ 3580
  AQOLDQmXA = QOLDQmXA->Text;   //tip proliva - Qm
  AVOLDQmXA = VOLDQmXA->Text;   //tip vody
  APOLDQmXA = POLDQmXA->Text;   //pogreschnost
  //2
  AKlOLDQmGA = KlOLDQmGA->Text;  //klass Simbol ДСТУ 3580
  AQOLDQmGA = QOLDQmGA->Text;   //tip proliva - Qm
  AVOLDQmGA = VOLDQmGA->Text;   //tip vody
  APOLDQmGA = POLDQmGA->Text;   //pogreschnost
  //3
  AKlOLDQtXA = KlOLDQtXA->Text;  //klass Simbol ДСТУ 3580
  AQOLDQtXA = QOLDQtXA->Text;   //tip proliva - Qt
  AVOLDQtXA = VOLDQtXA->Text;   //tip vody
  APOLDQtXA = POLDQtXA->Text;   //pogreschnost
  //4
  AKlOLDQtGA = KlOLDQtGA->Text;  //klass Simbol ДСТУ 3580
  AQOLDQtGA = QOLDQtGA->Text;   //tip proliva - Qt
  AVOLDQtGA = VOLDQtGA->Text;   //tip vody
  APOLDQtGA = POLDQtGA->Text;   //pogreschnost
  //5
  AKlOLDQnXA = KlOLDQnXA->Text;  //klass Simbol ДСТУ 3580
  AQOLDQnXA = QOLDQnXA->Text;    //tip proliva - Qn
  AVOLDQnXA = VOLDQnXA->Text;   //tip vody
  APOLDQnXA = POLDQnXA->Text;   //pogreschnost
  //6
  AKlOLDQnGA = KlOLDQnGA->Text;  //klass Simbol ДСТУ 3580
  AQOLDQnGA = QOLDQnGA->Text;   //tip proliva - Qn
  AVOLDQnGA = VOLDQnGA->Text;   //tip vody
  APOLDQnGA = POLDQnGA->Text;   //pogreschnost
  //7
  AKlOLDQmXB = KlOLDQmXB->Text;  //klass Simbol ДСТУ 3580
  AQOLDQmXB = QOLDQmXB->Text;   //tip proliva - Qm
  AVOLDQmXB = VOLDQmXB->Text;   //tip vody
  APOLDQmXB = POLDQmXB->Text;   //pogreschnost
  //8
  AKlOLDQmGB = KlOLDQmGB->Text;  //klass Simbol ДСТУ 3580
  AQOLDQmGB = QOLDQmGB->Text;   //tip proliva - Qm
  AVOLDQmGB = VOLDQmGB->Text;   //tip vody
  APOLDQmGB = POLDQmGB->Text;   //pogreschnost
  //9
  AKlOLDQtXB = KlOLDQtXB->Text;   //klass Simbol ДСТУ 3580
  AQOLDQtXB = QOLDQtXB->Text;   //tip proliva - Qt
  AVOLDQtXB = VOLDQtXB->Text;   //tip vody
  APOLDQtXB = POLDQtXB->Text;   //pogreschnost
  //10
  AKlOLDQtGB = KlOLDQtGB->Text;  //klass Simbol ДСТУ 3580
  AQOLDQtGB = QOLDQtGB->Text;   //tip proliva - Qt
  AVOLDQtGB = VOLDQtGB->Text;   //tip vody
  APOLDQtGB = POLDQtGB->Text;   //pogreschnost
  //11
  AKlOLDQnXB = KlOLDQnXB->Text;  //klass Simbol ДСТУ 3580
  AQOLDQnXB = QOLDQnXB->Text;   //tip proliva - Qn
  AVOLDQnXB = VOLDQnXB->Text;   //tip vody
  APOLDQnXB = POLDQnXB->Text;   //pogreschnost
  //12
  AKlOLDQnGB = KlOLDQnGB->Text;  //klass Simbol ДСТУ 3580
  AQOLDQnGB = QOLDQnGB->Text;   //tip proliva - Qn
  AVOLDQnGB = VOLDQnGB->Text;   //tip vody
  APOLDQnGB = POLDQnGB->Text;   //pogreschnost

  AQminLGr = QminLGr->Text;    //Qmin left grenc
  AQminRGr = QminRGr->Text;    //Qmin recht grenc
  AQtLGr = QtLGr->Text;      //Qt left grenc
  AQtRGr = QtRGr->Text;      //Qt recht grenc
  AQnLGr = QnLGr->Text;      //Qn left grenc
  AQnRGr = QnRGr->Text;      //Qn recht grenc

  ATXolL = TXolL->Text;      //Tchol  left grenc
  ATXolR = TXolR->Text;      //Tchol  recht grenc
  ATGorL = TGorL->Text;      //TGor  left grenc
  ATGorR = TGorR->Text;      //TGor  recht grenc

  AVKonst = VKonst->Text;     //V konstant
  ATimeConst = TimeConst->Text;   //T constant

}
//----------------------------------------------------------------------------
void TParamsForm::ControLNaCislo(AnsiString S)
{
  float F;
  try
  {
    if(DecimalSeparator == '.')
      F = (ReplZPnaPunk0(S)).ToDouble();
    else
      F = (ReplPunknaZP0(S)).ToDouble();
  }
  catch(...)
  {
    CloseFlag = false;
    ShowMessage("Были введены нечисловые значения параметров!! ИСПРАВЬТЕ или ОТКАЗ");
  }
}
//----------------------------------------------------------------------------
void __fastcall TParamsForm::BitBtn2Click(TObject *Sender)
{
  CloseFlag = true;
  FlChange = false;
  AnsiString S;
//ET Password1='" + (AnsiString)O->Password1 + "' , GroupName = '" + S1 + "', UndeleteF = " + (AnsiString)O->UndeleteF;
//  S += " WHERE OpName = '" + (AnsiString)O->OpName + "';";
  if(CloseWithOutSaving) return;
  try
  {
    S = "";
    if(AQn10a != Qn10a->Text)
    {
      FlChange = true;
      S += " Qn10a='" + Qn10a->Text + "'";
      ControLNaCislo(Qn10a->Text);
    }
    if(AQn10b != Qn10b->Text)
    {
      FlChange = true;
      if(S != "") S += ',';
      S += " Qn10b='" + Qn10b->Text + "'";
      ControLNaCislo(Qn10b->Text);
    }
    if(AQn15a != Qn15a->Text)
    {
      FlChange = true;
      if(S != "") S += ',';
      S += " Qn15a='" + Qn15a->Text + "'";
      ControLNaCislo(Qn15a->Text);
    }
    if(AQn15b != Qn15b->Text)
    {
      FlChange = true;
      if(S != "") S += ',';
      S += " Qn15b='" + Qn15b->Text + "'";
      ControLNaCislo(Qn15b->Text);
    }
    if(AQn20a != Qn20a->Text)
    {
      FlChange = true;
      if(S != "") S += ',';
      S += " Qn20a='" + Qn20a->Text + "'";
      ControLNaCislo(Qn20a->Text);
    }
    if(AQn20a != Qn20b->Text)
    {
      FlChange = true;
      if(S != "") S += ',';
      S += " Qn20b='" + Qn20b->Text + "'";
      ControLNaCislo(Qn20b->Text);
    }
    if(ADQn10Kta != DQn10Kta->Text)
    {
      FlChange = true;
      if(S != "") S += ',';
      S += " DQn10Kta='" + DQn10Kta->Text + "'";
      ControLNaCislo(DQn10Kta->Text);
    }
    if(ADQn10Ktb != DQn10Ktb->Text)
    {
      FlChange = true;
      if(S != "") S += ',';
      S += " DQn10Ktb='" + DQn10Ktb->Text + "'";
      ControLNaCislo(DQn10Ktb->Text);
    }
    if(ADQn15Kta != DQn15Kta->Text)
    {
      FlChange = true;
      if(S != "") S += ',';
      S += " DQn10Ktb='" + DQn10Ktb->Text + "'";
      ControLNaCislo(DQn15Kta->Text);
    }
    if(ADQn15Ktb != DQn15Ktb->Text)
    {
      FlChange = true;
      if(S != "") S += ',';
      S += " DQn15Ktb='" + DQn15Ktb->Text + "'";
      ControLNaCislo(DQn15Ktb->Text);
    }
    if(ADQn20Kta != DQn20Kta->Text)
    {
      FlChange = true;
      if(S != "") S += ',';
      S += " DQn20Kta='" + DQn20Kta->Text + "'";
      ControLNaCislo(DQn20Kta->Text);
    }
    if(ADQn20Ktb != DQn20Ktb->Text)
    {
      FlChange = true;
      if(S != "") S += ',';
      S += " DQn20Ktb='" + DQn20Ktb->Text + "'";
      ControLNaCislo(DQn20Ktb->Text);
    }
    if(ADQt10Kma != DQt10Kma->Text)
    {
      FlChange = true;
      if(S != "") S += ',';
      S += " DQt10Kma='" + DQt10Kma->Text + "'";
      ControLNaCislo(DQt10Kma->Text);
    }
    if(ADQt10Kmb != DQt10Kmb->Text)
    {
      FlChange = true;
      if(S != "") S += ',';
      S += " DQt10Kmb='" + DQt10Kmb->Text + "'";
      ControLNaCislo(DQt10Kmb->Text);
    }
    if(ADQt15Kma != DQt15Kma->Text)
    {
      FlChange = true;
      if(S != "") S += ',';
      S += " DQt15Kma='" + DQt15Kma->Text + "'";
      ControLNaCislo(DQt15Kma->Text);
    }
    if(ADQt15Kmb != DQt15Kmb->Text)
    {
      FlChange = true;
      if(S != "") S += ',';
      S += " DQt15Kmb='" + DQt15Kmb->Text + "'";
      ControLNaCislo(DQt15Kmb->Text);
    }
    if(ADQt20Kma != DQt20Kma->Text)
    {
      FlChange = true;
      if(S != "") S += ',';
      S += " DQt20Kma='" + DQt20Kma->Text + "'";
      ControLNaCislo(DQt20Kma->Text);
    }
    if(ADQt20Kmb != DQt20Kmb->Text)
    {
      FlChange = true;
      if(S != "") S += ',';
      S += " DQt20Kmb='" + DQt20Kmb->Text + "'";
      ControLNaCislo(DQt20Kmb->Text);
    }
   // ДСТУ EN ISO 4064-1 и ДСТУ OIML R 49-1
    if(AQnE101 != QnE101->Text)
    {
      FlChange = true;
      if(S != "") S += ',';
      S += " QnE101='" + QnE101->Text + "'";
      ControLNaCislo(QnE101->Text);
    }
    if(AQnE102 != QnE102->Text)
    {
      FlChange = true;
      if(S != "") S += ',';
      S += " QnE102='" + QnE102->Text + "'";
      ControLNaCislo(QnE102->Text);
    }
    if(AQnE151 != QnE151->Text)
    {
      FlChange = true;
      if(S != "") S += ',';
      S += " QnE151='" + QnE151->Text + "'";
      ControLNaCislo(QnE151->Text);
   }
    if(AQnE152 != QnE152->Text)
    {
      FlChange = true;
      if(S != "") S += ',';
      S += " QnE152='" + QnE152->Text + "'";
      ControLNaCislo(QnE152->Text);
    }
    if(AQnE201 != QnE201->Text)
    {
      FlChange = true;
      if(S != "") S += ',';
      S += " QnE201='" + QnE201->Text + "'";
      ControLNaCislo(QnE201->Text);
    }
    if(AQnE202 != QnE202->Text)
    {
      FlChange = true;
      if(S != "") S += ',';
      S += " QnE202='" + QnE202->Text + "'";
      ControLNaCislo(QnE202->Text);
    }
    if(ADQn10Kt1 != DQn10Kt1->Text)
    {
      FlChange = true;
      if(S != "") S += ',';
      S += " DQn10Kt1='" + DQn10Kt1->Text + "'";
      ControLNaCislo(DQn10Kt1->Text);
    }
    if(ADQn10Kt2 != DQn10Kt2->Text)
    {
      FlChange = true;
      if(S != "") S += ',';
      S += " DQn10Kt2='" + DQn10Kt2->Text + "'";
      ControLNaCislo(DQn10Kt2->Text);
    }
    if(ADQn15Kt1 != DQn15Kt1->Text)
    {
      FlChange = true;
      if(S != "") S += ',';
      S += " DQn15Kt1='" + DQn15Kt1->Text + "'";
      ControLNaCislo(DQn15Kt1->Text);
    }
    if(ADQn15Kt2 != DQn15Kt2->Text)
    {
      FlChange = true;
      if(S != "") S += ',';
      S += " DQn15Kt2='" + DQn15Kt2->Text + "'";
      ControLNaCislo(DQn15Kt2->Text);
    }
    if(ADQn20Kt1 != DQn20Kt1->Text)
    {
      FlChange = true;
      if(S != "") S += ',';
      S += " DQn20Kt1='" + DQn20Kt1->Text + "'";
      ControLNaCislo(DQn20Kt1->Text);
    }
    if(ADQn20Kt2 != DQn20Kt2->Text)
    {
      FlChange = true;
      if(S != "") S += ',';
      S += " DQn20Kt2='" + DQn20Kt2->Text + "'";
      ControLNaCislo(DQn20Kt2->Text);
    }
    if(ADQt10Km1 != DQt10Km1->Text)      //DQt10Km1
    {
      FlChange = true;
      if(S != "") S += ',';
      S += " DQt10Km1='" + DQt10Km1->Text + "'";
      ControLNaCislo(DQt10Km1->Text);
    }
    if(ADQt10Km2 != DQt10Km2->Text)
    {
      FlChange = true;
      if(S != "") S += ',';
      S += " DQt10Km2='" + DQt10Km2->Text + "'";
      ControLNaCislo(DQt10Km2->Text);
    }
    if(ADQt15Km1 != DQt15Km1->Text)
    {
      FlChange = true;
      if(S != "") S += ',';
      S += " DQt15Km1='" + DQt15Km1->Text + "'";
      ControLNaCislo(DQt15Km1->Text);
    }
    if(ADQt15Km2 != DQt15Km2->Text)
    {
      FlChange = true;
      if(S != "") S += ',';
      S += " DQt15Km2='" + DQt15Km2->Text + "'";
      ControLNaCislo(DQt15Km2->Text);
    }
    if(ADQt20Km1 != DQt20Km1->Text)
    {
      FlChange = true;
      if(S != "") S += ',';
      S += " DQt20Km1='" + DQt20Km1->Text + "'";
      ControLNaCislo(DQt20Km1->Text);
    }
    if(ADQt20Km2 != DQt20Km2->Text)
    {
      FlChange = true;
      if(S != "") S += ',';
      S += " DQt20Km2='" + DQt20Km2->Text + "'";
      ControLNaCislo(DQt20Km2->Text);
    }
    ////Погрешности
    if(APISOQmX1 != PISOQmX1->Text)
    {
      FlChange = true;
      if(S != "") S += ',';
      S += " PISOQmX1='" + PISOQmX1->Text + "'";
      ControLNaCislo(PISOQmX1->Text);
    }
    if(APISOQmG1 != PISOQmG1->Text)
    {
      FlChange = true;
      if(S != "") S += ',';
      S += " PISOQmG1='" + PISOQmG1->Text + "'";
      ControLNaCislo(PISOQmG1->Text);
    }
    if(APISOQtX1 != PISOQtX1->Text)
    {
      FlChange = true;
      if(S != "") S += ',';
      S += " PISOQtX1='" + PISOQtX1->Text + "'";
      ControLNaCislo(PISOQtX1->Text);
    }
    if(APISOQtG1 != PISOQtG1->Text)
    {
      FlChange = true;
      if(S != "") S += ',';
      S += " PISOQtG1='" + PISOQtG1->Text + "'";
      ControLNaCislo(PISOQtG1->Text);
    }
    if(APISOQnX1 != PISOQnX1->Text)
    {
      FlChange = true;
      if(S != "") S += ',';
      S += " PISOQnX1='" + PISOQnX1->Text + "'";
      ControLNaCislo(PISOQnX1->Text);
    }
    if(APISOQnG1 != PISOQnG1->Text)
    {
      FlChange = true;
      if(S != "") S += ',';
      S += " PISOQnG1='" + PISOQnG1->Text + "'";
      ControLNaCislo(PISOQnG1->Text);
    }
    if(APISOQmX2 != PISOQmX2->Text)
    {
      FlChange = true;
      if(S != "") S += ',';
      S += " PISOQmX2='" + PISOQmX2->Text + "'";
      ControLNaCislo(PISOQmX2->Text);
    }
    if(APISOQmG2 != PISOQmG2->Text)
    {
      FlChange = true;
      if(S != "") S += ',';
      S += " PISOQmG2='" + PISOQmG2->Text + "'";
      ControLNaCislo(PISOQmG2->Text);
    }
    if(APISOQtX2 != PISOQtX2->Text)
    {
      FlChange = true;
      if(S != "") S += ',';
      S += " PISOQtX2='" + PISOQtX2->Text + "'";
      ControLNaCislo(PISOQtX2->Text);
    }
    if(APISOQtG2 != PISOQtG2->Text)
    {
      FlChange = true;
      if(S != "") S += ',';
      S += " PISOQtG2='" + PISOQtG2->Text + "'";
      ControLNaCislo(PISOQtG2->Text);
    }
    if(APISOQnX2 != PISOQnX2->Text)
    {
      FlChange = true;
      if(S != "") S += ',';
      S += " PISOQnX2='" + PISOQnX2->Text + "'";
      ControLNaCislo(PISOQnX2->Text);
    }
    if(APISOQnG2 != PISOQnG2->Text)
    {
      FlChange = true;
      if(S != "") S += ',';
      S += " PISOQnG2='" + PISOQnG2->Text + "'";
      ControLNaCislo(PISOQnG2->Text);
    }
   // Погрешности LCNE OIML R 49-1
    if(APOIMLQmX1 != POIMLQmX1->Text)
    {
      FlChange = true;
      if(S != "") S += ',';
      S += " POIMLQmX1='" + POIMLQmX1->Text + "'";
      ControLNaCislo(POIMLQmX1->Text);
    }
    if(APOIMLQmG1 != POIMLQmG1->Text)
    {
      FlChange = true;
      if(S != "") S += ',';
      S += " POIMLQmG1='" + POIMLQmG1->Text + "'";
      ControLNaCislo(POIMLQmG1->Text);
    }
    if(APOIMLQtX1 != POIMLQtX1->Text)
    {
      FlChange = true;
      if(S != "") S += ',';
      S += " POIMLQtX1='" + POIMLQtX1->Text + "'";
      ControLNaCislo(POIMLQtX1->Text);
    }
    if(APOIMLQtG1 != POIMLQtG1->Text)
    {
      FlChange = true;
      if(S != "") S += ',';
      S += " POIMLQtG1='" + POIMLQtG1->Text + "'";
      ControLNaCislo(POIMLQtG1->Text);
    }
    if(APOIMLQnX1 != POIMLQnX1->Text)
    {
      FlChange = true;
      if(S != "") S += ',';
      S += " POIMLQnX1='" + POIMLQnX1->Text + "'";
      ControLNaCislo(POIMLQnX1->Text);
    }
    if(APOIMLQnG1 != POIMLQnG1->Text)
    {
      FlChange = true;
      if(S != "") S += ',';
      S += " POIMLQnG1='" + POIMLQnG1->Text + "'";
      ControLNaCislo(POIMLQnG1->Text);
    }
    if(APOIMLQmX2 != POIMLQmX2->Text)
    {
      FlChange = true;
      if(S != "") S += ',';
      S += " POIMLQmX2='" + POIMLQmX2->Text + "'";
      ControLNaCislo(POIMLQmX2->Text);
    }
    if(APOIMLQmG2 != POIMLQmG2->Text)
    {
      FlChange = true;
      if(S != "") S += ',';
      S += " POIMLQmG2='" + POIMLQmG2->Text + "'";
      ControLNaCislo(POIMLQmG2->Text);
    }
    if(APOIMLQmG2 != POIMLQmG2->Text)
    {
      FlChange = true;
      if(S != "") S += ',';
      S += " POIMLQmG2='" + POIMLQmG2->Text + "'";
      ControLNaCislo(POIMLQmG2->Text);
    }
    if(APOIMLQtG2 != POIMLQtG2->Text)
    {
      FlChange = true;
      if(S != "") S += ',';
      S += " POIMLQtG2='" + POIMLQtG2->Text + "'";
      ControLNaCislo(POIMLQtG2->Text);
    }
    if(APOIMLQnX2 != POIMLQnX2->Text)
    {
      FlChange = true;
      if(S != "") S += ',';
      S += " POIMLQnX2='" + POIMLQnX2->Text + "'";
      ControLNaCislo(POIMLQnX2->Text);
    }
    if(APOIMLQnG2 != POIMLQnG2->Text)
    {
      FlChange = true;
      if(S != "") S += ',';
      S += " POIMLQnG2='" + POIMLQnG2->Text + "'";
      ControLNaCislo(POIMLQnG2->Text);
    }
   //ПОГРЕШНОСТИ СТАРОГО ГОСТА
    if(APOLDQmXA != POLDQmXA->Text)
    {
      FlChange = true;
      if(S != "") S += ',';
      S += " POLDQmXA='" + POLDQmXA->Text + "'";
      ControLNaCislo(POLDQmXA->Text);
    }
    if(APOLDQmGA != POLDQmGA->Text)
    {
      FlChange = true;
      if(S != "") S += ',';
      S += " POLDQmGA='" + POLDQmGA->Text + "'";
      ControLNaCislo(POLDQmGA->Text);
    }
    if(APOLDQtXA != POLDQtXA->Text)
    {
      FlChange = true;
      if(S != "") S += ',';
      S += " POLDQtXA='" + POLDQtXA->Text + "'";
      ControLNaCislo(POLDQtXA->Text);
    }
    if(APOLDQtGA != POLDQtGA->Text)
    {
      FlChange = true;
      if(S != "") S += ',';
      S += " POLDQtGA='" + POLDQtGA->Text + "'";
      ControLNaCislo(POLDQtGA->Text);
    }
    if(APOLDQnXA != POLDQnXA->Text)
    {
      FlChange = true;
      if(S != "") S += ',';
      S += " POLDQnXA='" + POLDQnXA->Text + "'";
      ControLNaCislo(POLDQnXA->Text);
    }
    if(APOLDQnGA != POLDQnGA->Text)
    {
      FlChange = true;
      if(S != "") S += ',';
      S += " POLDQnGA='" + POLDQnGA->Text + "'";
      ControLNaCislo(POLDQnGA->Text);
    }
    if(APOLDQmXB != POLDQmXB->Text)
    {
      FlChange = true;
      if(S != "") S += ',';
      S += " POLDQmXB='" + POLDQmXB->Text + "'";
      ControLNaCislo(POLDQmXB->Text);
    }
    if(APOLDQmGB != POLDQmGB->Text)
    {
      FlChange = true;
      if(S != "") S += ',';
      S += " POLDQmGB='" + POLDQmGB->Text + "'";
      ControLNaCislo(POLDQmGB->Text);
    }
    if(APOLDQtXB != POLDQtXB->Text)
    {
      FlChange = true;
      if(S != "") S += ',';
      S += " POLDQtXB='" + POLDQtXB->Text + "'";
      ControLNaCislo(POLDQtXB->Text);
    }
    if(APOLDQtGB != POLDQtGB->Text)
    {
      FlChange = true;
      if(S != "") S += ',';
      S += " POLDQtGB='" + POLDQtGB->Text + "'";
      ControLNaCislo(POLDQtGB->Text);
    }
    if(APOLDQnXB != POLDQnXB->Text)
    {
      FlChange = true;
      if(S != "") S += ',';
      S += " POLDQnXB='" + POLDQnXB->Text + "'";
      ControLNaCislo(POLDQnXB->Text);
    }
    if(APOLDQnGB != POLDQnGB->Text)
    {
      FlChange = true;
      if(S != "") S += ',';
      S += " POLDQnGB='" + POLDQnGB->Text + "'";
      ControLNaCislo(POLDQnGB->Text);
    }
    //Границы Q
    if(AQminLGr != QminLGr->Text)
    {
      FlChange = true;
      if(S != "") S += ',';
      S += " QminLGr='" + QminLGr->Text + "'";
      ControLNaCislo(QminLGr->Text);
    }
    if(AQminRGr != QminRGr->Text)
    {
      FlChange = true;
      if(S != "") S += ',';
      S += " QminRGr='" + QminRGr->Text + "'";
      ControLNaCislo(QminRGr->Text);
    }
    if(AQtLGr != QtLGr->Text)
    {
      FlChange = true;
      if(S != "") S += ',';
      S += " QtLGr='" + QtLGr->Text + "'";
      ControLNaCislo(QtLGr->Text);
    }
    if(AQtRGr != QtRGr->Text)
    {
      FlChange = true;
      if(S != "") S += ',';
      S += " QtRGr='" + QtRGr->Text + "'";
      ControLNaCislo(QtRGr->Text);
    }
    if(AQnLGr != QnLGr->Text)
    {
      FlChange = true;
      if(S != "") S += ',';
      S += " QnLGr='" + QnLGr->Text + "'";
      ControLNaCislo(QnLGr->Text);
    }
    if(AQnRGr != QnRGr->Text)
    {
      FlChange = true;
      if(S != "") S += ',';
      S += " QnRGr='" + QnRGr->Text + "'";
      ControLNaCislo(QnRGr->Text);
    }
    if(ATXolL != TXolL->Text)
    {
      FlChange = true;
      if(S != "") S += ',';
      S += " TXolL='" + TXolL->Text + "'";
      ControLNaCislo(TXolL->Text);
    }
    if(ATXolR != TXolR->Text)
    {
      FlChange = true;
      if(S != "") S += ',';
      S += " TXolR='" + TXolR->Text + "'";
      ControLNaCislo(TXolR->Text);
    }
    if(ATGorL != TGorL->Text)
    {
      FlChange = true;
      if(S != "") S += ',';
      S += " TGorL='" + TGorL->Text + "'";
      ControLNaCislo(TGorL->Text);
    }
    if(ATGorR != TGorR->Text)
    {
      FlChange = true;
      if(S != "") S += ',';
      S += " TGorR='" + TGorR->Text + "'";
      ControLNaCislo(TGorR->Text);
    }
    if(AVKonst != VKonst->Text)
    {
      FlChange = true;
      if(S != "") S += ',';
      S += " VKonst='" + VKonst->Text + "'";
      ControLNaCislo(VKonst->Text);
    }
    if(ATimeConst != TimeConst->Text)
    {
      FlChange = true;
      if(S != "") S += ',';
      S += " TimeConst='" + TimeConst->Text + "'";
      ControLNaCislo(TimeConst->Text);
    }
    if(FlChange)
    {
      SQLString  = " UPDATE Parameters SET " + S + + ";";
    }
  }
  catch(...)
  {
    ShowMessage("Были введены нечисловые данные при изменении параметров! Исправьте!");
    CloseFlag = false;
  }
}

//---------------------------------------------------------------------------


