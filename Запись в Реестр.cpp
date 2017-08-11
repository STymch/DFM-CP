  DiametrVn D;
  DM->DiametrList.clear();
  try
  {
    D.Diametr = Form4->d8->Text.ToInt();
    if(DecimalSeparator == '.')
    {
      D.Qn      = ReplZPnaPunk(Form4->Qn8->Text).ToDouble();
      D.DQn     = ReplZPnaPunk(Form4->DQn8->Text).ToDouble();
      D.DQt     = ReplZPnaPunk(Form4->DQt8->Text).ToDouble();
      D.DQmin   = ReplZPnaPunk(Form4->DQmin8->Text).ToDouble();
      D.Vn      = ReplZPnaPunk(Form4->Vn8->Text).ToDouble();
      D.Vt      = ReplZPnaPunk(Form4->Vt8->Text).ToDouble();
      D.Vmin    = ReplZPnaPunk(Form4->Vmin8->Text).ToDouble();
    }
    else
    {
      D.Qn      = ReplPunknaZP(Form4->Qn8->Text).ToDouble();
      D.DQn     = ReplPunknaZP(Form4->DQn8->Text).ToDouble();
      D.DQt     = ReplPunknaZP(Form4->DQt8->Text).ToDouble();
      D.DQmin   = ReplPunknaZP(Form4->DQmin8->Text).ToDouble();
      D.Vn      = ReplPunknaZP(Form4->Vn8->Text).ToDouble();
      D.Vt      = ReplPunknaZP(Form4->Vt8->Text).ToDouble();
      D.Vmin    = ReplPunknaZP(Form4->Vmin8->Text).ToDouble();
    }
    DM->DiametrList.push_back(D);

    D.Diametr = Form4->d10->Text.ToInt();
    if(DecimalSeparator == '.')
    {
      D.Qn      = ReplZPnaPunk(Form4->Qn10->Text).ToDouble();
      D.DQn     = ReplZPnaPunk(Form4->DQn10->Text).ToDouble();
      D.DQt     = ReplZPnaPunk(Form4->DQt10->Text).ToDouble();
      D.DQmin   = ReplZPnaPunk(Form4->DQmin10->Text).ToDouble();
      D.Vn      = ReplZPnaPunk(Form4->Vn10->Text).ToDouble();
      D.Vt      = ReplZPnaPunk(Form4->Vt10->Text).ToDouble();
      D.Vmin    = ReplZPnaPunk(Form4->Vmin10->Text).ToDouble();
    }
    else
    {
      D.Qn      = ReplPunknaZP(Form4->Qn10->Text).ToDouble();
      D.DQn     = ReplPunknaZP(Form4->DQn10->Text).ToDouble();
      D.DQt     = ReplPunknaZP(Form4->DQt10->Text).ToDouble();
      D.DQmin   = ReplPunknaZP(Form4->DQmin10->Text).ToDouble();
      D.Vn      = ReplPunknaZP(Form4->Vn10->Text).ToDouble();
      D.Vt      = ReplPunknaZP(Form4->Vt10->Text).ToDouble();
      D.Vmin    = ReplPunknaZP(Form4->Vmin10->Text).ToDouble();
    }
    DM->DiametrList.push_back(D);

    D.Diametr = Form4->d15->Text.ToInt();
    if(DecimalSeparator == '.')
    {
      D.Qn      = ReplZPnaPunk(Form4->Qn15->Text).ToDouble();
      D.DQn     = ReplZPnaPunk(Form4->DQn15->Text).ToDouble();
      D.DQt     = ReplZPnaPunk(Form4->DQt15->Text).ToDouble();
      D.DQmin   = ReplZPnaPunk(Form4->DQmin15->Text).ToDouble();
      D.Vn      = ReplZPnaPunk(Form4->Vn15->Text).ToDouble();
      D.Vt      = ReplZPnaPunk(Form4->Vt15->Text).ToDouble();
      D.Vmin    = ReplZPnaPunk(Form4->Vmin15->Text).ToDouble();
    }
    else
    {
      D.Qn      = ReplPunknaZP(Form4->Qn15->Text).ToDouble();
      D.DQn     = ReplPunknaZP(Form4->DQn15->Text).ToDouble();
      D.DQt     = ReplPunknaZP(Form4->DQt15->Text).ToDouble();
      D.DQmin   = ReplPunknaZP(Form4->DQmin15->Text).ToDouble();
      D.Vn      = ReplPunknaZP(Form4->Vn15->Text).ToDouble();
      D.Vt      = ReplPunknaZP(Form4->Vt15->Text).ToDouble();
      D.Vmin    = ReplPunknaZP(Form4->Vmin15->Text).ToDouble();
    }
    DM->DiametrList.push_back(D);

    D.Diametr = Form4->d20->Text.ToInt();
    if(DecimalSeparator == '.')
    {
      D.Qn      = ReplZPnaPunk(Form4->Qn20->Text).ToDouble();
      D.DQn     = ReplZPnaPunk(Form4->DQn20->Text).ToDouble();
      D.DQt     = ReplZPnaPunk(Form4->DQt20->Text).ToDouble();
      D.DQmin   = ReplZPnaPunk(Form4->DQmin20->Text).ToDouble();
      D.Vn      = ReplZPnaPunk(Form4->Vn20->Text).ToDouble();
      D.Vt      = ReplZPnaPunk(Form4->Vt20->Text).ToDouble();
      D.Vmin    = ReplZPnaPunk(Form4->Vmin20->Text).ToDouble();
    }
    else
    {
      D.Qn      = ReplPunknaZP(Form4->Qn20->Text).ToDouble();
      D.DQn     = ReplPunknaZP(Form4->DQn20->Text).ToDouble();
      D.DQt     = ReplPunknaZP(Form4->DQt20->Text).ToDouble();
      D.DQmin   = ReplPunknaZP(Form4->DQmin20->Text).ToDouble();
      D.Vn      = ReplPunknaZP(Form4->Vn20->Text).ToDouble();
      D.Vt      = ReplPunknaZP(Form4->Vt20->Text).ToDouble();
      D.Vmin    = ReplPunknaZP(Form4->Vmin20->Text).ToDouble();
    }
    DM->DiametrList.push_back(D);

    D.Diametr = Form4->d25->Text.ToInt();
    if(DecimalSeparator == '.')
    {
      D.Qn      = ReplZPnaPunk(Form4->Qn25->Text).ToDouble();
      D.DQn     = ReplZPnaPunk(Form4->DQn25->Text).ToDouble();
      D.DQt     = ReplZPnaPunk(Form4->DQt25->Text).ToDouble();
      D.DQmin   = ReplZPnaPunk(Form4->DQmin25->Text).ToDouble();
      D.Vn      = ReplZPnaPunk(Form4->Vn25->Text).ToDouble();
      D.Vt      = ReplZPnaPunk(Form4->Vt25->Text).ToDouble();
      D.Vmin    = ReplZPnaPunk(Form4->Vmin25->Text).ToDouble();
    }
    else
    {
      D.Qn      = ReplPunknaZP(Form4->Qn25->Text).ToDouble();
      D.DQn     = ReplPunknaZP(Form4->DQn25->Text).ToDouble();
      D.DQt     = ReplPunknaZP(Form4->DQt25->Text).ToDouble();
      D.DQmin   = ReplPunknaZP(Form4->DQmin25->Text).ToDouble();
      D.Vn      = ReplPunknaZP(Form4->Vn25->Text).ToDouble();
      D.Vt      = ReplPunknaZP(Form4->Vt25->Text).ToDouble();
      D.Vmin    = ReplPunknaZP(Form4->Vmin25->Text).ToDouble();
    }
    DM->DiametrList.push_back(D);

    D.Diametr = Form4->d32->Text.ToInt();
    if(DecimalSeparator == '.')
    {
      D.Qn      = ReplZPnaPunk(Form4->Qn32->Text).ToDouble();
      D.DQn     = ReplZPnaPunk(Form4->DQn32->Text).ToDouble();
      D.DQt     = ReplZPnaPunk(Form4->DQt32->Text).ToDouble();
      D.DQmin   = ReplZPnaPunk(Form4->DQmin32->Text).ToDouble();
      D.Vn      = ReplZPnaPunk(Form4->Vn32->Text).ToDouble();
      D.Vt      = ReplZPnaPunk(Form4->Vt32->Text).ToDouble();
      D.Vmin    = ReplZPnaPunk(Form4->Vmin32->Text).ToDouble();
    }
    else
    {
      D.Qn      = ReplPunknaZP(Form4->Qn32->Text).ToDouble();
      D.DQn     = ReplPunknaZP(Form4->DQn32->Text).ToDouble();
      D.DQt     = ReplPunknaZP(Form4->DQt32->Text).ToDouble();
      D.DQmin   = ReplPunknaZP(Form4->DQmin32->Text).ToDouble();
      D.Vn      = ReplPunknaZP(Form4->Vn32->Text).ToDouble();
      D.Vt      = ReplPunknaZP(Form4->Vt32->Text).ToDouble();
      D.Vmin    = ReplPunknaZP(Form4->Vmin32->Text).ToDouble();
    }
    DM->DiametrList.push_back(D);

    D.Diametr = Form4->d40->Text.ToInt();
    if(DecimalSeparator == '.')
    {
      D.Qn      = ReplZPnaPunk(Form4->Qn40->Text).ToDouble();
      D.DQn     = ReplZPnaPunk(Form4->DQn40->Text).ToDouble();
      D.DQt     = ReplZPnaPunk(Form4->DQt40->Text).ToDouble();
      D.DQmin   = ReplZPnaPunk(Form4->DQmin40->Text).ToDouble();
      D.Vn      = ReplZPnaPunk(Form4->Vn40->Text).ToDouble();
      D.Vt      = ReplZPnaPunk(Form4->Vt40->Text).ToDouble();
      D.Vmin    = ReplZPnaPunk(Form4->Vmin40->Text).ToDouble();
    }
    else
    {
      D.Qn      = ReplPunknaZP(Form4->Qn40->Text).ToDouble();
      D.DQn     = ReplPunknaZP(Form4->DQn40->Text).ToDouble();
      D.DQt     = ReplPunknaZP(Form4->DQt40->Text).ToDouble();
      D.DQmin   = ReplPunknaZP(Form4->DQmin40->Text).ToDouble();
      D.Vn      = ReplPunknaZP(Form4->Vn40->Text).ToDouble();
      D.Vt      = ReplPunknaZP(Form4->Vt40->Text).ToDouble();
      D.Vmin    = ReplPunknaZP(Form4->Vmin40->Text).ToDouble();
    }
    DM->DiametrList.push_back(D);
    D.Diametr = Form4->d50->Text.ToInt();
    if(DecimalSeparator == '.')
    {
      D.Qn      = ReplZPnaPunk(Form4->Qn50->Text).ToDouble();
      D.DQn     = ReplZPnaPunk(Form4->DQn50->Text).ToDouble();
      D.DQt     = ReplZPnaPunk(Form4->DQt50->Text).ToDouble();
      D.DQmin   = ReplZPnaPunk(Form4->DQmin50->Text).ToDouble();
      D.Vn      = ReplZPnaPunk(Form4->Vn50->Text).ToDouble();
      D.Vt      = ReplZPnaPunk(Form4->Vt50->Text).ToDouble();
      D.Vmin    = ReplZPnaPunk(Form4->Vmin50->Text).ToDouble();
    }
    else
    {
      D.Qn      = ReplPunknaZP(Form4->Qn50->Text).ToDouble();
      D.DQn     = ReplPunknaZP(Form4->DQn50->Text).ToDouble();
      D.DQt     = ReplPunknaZP(Form4->DQt50->Text).ToDouble();
      D.DQmin   = ReplPunknaZP(Form4->DQmin50->Text).ToDouble();
      D.Vn      = ReplPunknaZP(Form4->Vn50->Text).ToDouble();
      D.Vt      = ReplPunknaZP(Form4->Vt50->Text).ToDouble();
      D.Vmin    = ReplPunknaZP(Form4->Vmin50->Text).ToDouble();
    }
    DM->DiametrList.push_back(D);
  }
  catch(...)
  {
    ShowMessage("A a?oiia <Aeaiao?u e niioaaonoao?uea Q> aaaaaiu ia ?eneianua cia?aiey");
    delete Form4;
    return;
  }
  DM->ClassList.clear();
  ClassQ   C;
  try
  {
    strcpy(C.Name, Form4->Label77->Caption.c_str());
    if(DecimalSeparator == '.')
    {
      C.Qmin = ReplZPnaPunk(Form4->AQmin->Text).ToDouble();
      C.Qt =   ReplZPnaPunk(Form4->AQt->Text).ToDouble();
    }
    else
    {
      C.Qmin = ReplPunknaZP(Form4->AQmin->Text).ToDouble();
      C.Qt =   ReplPunknaZP(Form4->AQt->Text).ToDouble();
    }
    DM->ClassList.push_back(C);
    strcpy(C.Name, Form4->Label78->Caption.c_str());
    if(DecimalSeparator == '.')
    {
      C.Qmin = ReplZPnaPunk(Form4->BQmin->Text).ToDouble();
      C.Qt =   ReplZPnaPunk(Form4->BQt->Text).ToDouble();
    }
    else
    {
      C.Qmin = ReplPunknaZP(Form4->BQmin->Text).ToDouble();
      C.Qt =   ReplPunknaZP(Form4->BQt->Text).ToDouble();
    }
    DM->ClassList.push_back(C);
    strcpy(C.Name, Form4->Label79->Caption.c_str());
    if(DecimalSeparator == '.')
    {
      C.Qmin = ReplZPnaPunk(Form4->CQmin->Text).ToDouble();
      C.Qt =   ReplZPnaPunk(Form4->CQt->Text).ToDouble();
    }
    else
    {
      C.Qmin = ReplPunknaZP(Form4->CQmin->Text).ToDouble();
      C.Qt =   ReplPunknaZP(Form4->CQt->Text).ToDouble();
    }
    DM->ClassList.push_back(C);
  }
  catch(...)
  {
    ShowMessage("A a?oiia <Caaeneiinou Qmin e Qt io EEANNA> aaaaaiu ia ?eneianua cia?aiey");
    delete Form4;
    return;
  }
  DM->ClassTList.clear();
  ClassT     T;
  try
  {
    strcpy(T.Name, "X");
    if(DecimalSeparator == '.')
    {
      T.Tmin  = ReplZPnaPunk(Form4->TminX->Text).ToDouble();
      T.Tmax  = ReplZPnaPunk(Form4->TmaxX->Text).ToDouble();
      T.DminL = ReplZPnaPunk(Form4->DminLX->Text).ToDouble();
      T.DminR = ReplZPnaPunk(Form4->DminRX->Text).ToDouble();
      T.DtL   = ReplZPnaPunk(Form4->DtLX->Text).ToDouble();
      T.DtR   = ReplZPnaPunk(Form4->DtRX->Text).ToDouble();
      T.DnL   = ReplZPnaPunk(Form4->DnLX->Text).ToDouble();
      T.DnR   = ReplZPnaPunk(Form4->DnRX->Text).ToDouble();
    }
    else
    {
      T.Tmin  = ReplPunknaZP(Form4->TminX->Text).ToDouble();
      T.Tmax  = ReplPunknaZP(Form4->TmaxX->Text).ToDouble();
      T.DminL = ReplPunknaZP(Form4->DminLX->Text).ToDouble();
      T.DminR = ReplPunknaZP(Form4->DminRX->Text).ToDouble();
      T.DtL   = ReplPunknaZP(Form4->DtLX->Text).ToDouble();
      T.DtR   = ReplPunknaZP(Form4->DtRX->Text).ToDouble();
      T.DnL   = ReplPunknaZP(Form4->DnLX->Text).ToDouble();
      T.DnR   = ReplPunknaZP(Form4->DnRX->Text).ToDouble();
    }
    DM->ClassTList.push_back(T);
    strcpy(T.Name, "G");
    if(DecimalSeparator == '.')
    {
      T.Tmin  = ReplPunknaZP(Form4->TminG->Text).ToDouble();
      T.Tmax  = ReplPunknaZP(Form4->TmaxG->Text).ToDouble();
      T.DminL = ReplPunknaZP(Form4->DminLG->Text).ToDouble();
      T.DminR = ReplPunknaZP(Form4->DminRG->Text).ToDouble();
      T.DtL   = ReplPunknaZP(Form4->DtLG->Text).ToDouble();
      T.DtR   = ReplPunknaZP(Form4->DtRG->Text).ToDouble();
      T.DnL   = ReplPunknaZP(Form4->DnLG->Text).ToDouble();
      T.DnR   = ReplPunknaZP(Form4->DnRG->Text).ToDouble();
    }
    else
    {
      T.Tmin  = ReplPunknaZP(Form4->TminG->Text).ToDouble();
      T.Tmax  = ReplPunknaZP(Form4->TmaxG->Text).ToDouble();
      T.DminL = ReplPunknaZP(Form4->DminLG->Text).ToDouble();
      T.DminR = ReplPunknaZP(Form4->DminRG->Text).ToDouble();
      T.DtL   = ReplPunknaZP(Form4->DtLG->Text).ToDouble();
      T.DtR   = ReplPunknaZP(Form4->DtRG->Text).ToDouble();
      T.DnL   = ReplPunknaZP(Form4->DnLG->Text).ToDouble();
      T.DnR   = ReplPunknaZP(Form4->DnRG->Text).ToDouble();
    }
    DM->ClassTList.push_back(T);
  }
  catch(...)
  {
    ShowMessage("A a?oiia <Ai?y?ay e oieiaiay aiaa> aaaaaiu ia ?eneianua cia?aiey");
    delete Form4;
    return;
  }
  Reg->WriteInteger("Baza","Params",1); //Aeaiao?u e niioaaonoao?uea QAeaiao?u e niioaaonoao?uea Q
  Reg->WriteString("Baza","d8",Form4->d8->Text);
  Reg->WriteString("Baza","d10",Form4->d10->Text);
  Reg->WriteString("Baza","d15",Form4->d15->Text);
  Reg->WriteString("Baza","d20",Form4->d20->Text);
  Reg->WriteString("Baza","d25",Form4->d25->Text);
  Reg->WriteString("Baza","d32",Form4->d32->Text);
  Reg->WriteString("Baza","d40",Form4->d40->Text);
  Reg->WriteString("Baza","d50",Form4->d50->Text);

  Reg->WriteString("Baza","Qn8",Form4->Qn8->Text);
  Reg->WriteString("Baza","Qn10",Form4->Qn10->Text);
  Reg->WriteString("Baza","Qn15",Form4->Qn15->Text);
  Reg->WriteString("Baza","Qn20",Form4->Qn20->Text);
  Reg->WriteString("Baza","Qn25",Form4->Qn25->Text);
  Reg->WriteString("Baza","Qn32",Form4->Qn32->Text);
  Reg->WriteString("Baza","Qn40",Form4->Qn40->Text);
  Reg->WriteString("Baza","Qn50",Form4->Qn50->Text);

  Reg->WriteString("Baza","DQn8",Form4->DQn8->Text);
  Reg->WriteString("Baza","DQn10",Form4->DQn10->Text);
  Reg->WriteString("Baza","DQn15",Form4->DQn15->Text);
  Reg->WriteString("Baza","DQn20",Form4->DQn20->Text);
  Reg->WriteString("Baza","DQn25",Form4->DQn25->Text);
  Reg->WriteString("Baza","DQn32",Form4->DQn32->Text);
  Reg->WriteString("Baza","DQn40",Form4->DQn40->Text);
  Reg->WriteString("Baza","DQn50",Form4->DQn50->Text);

  Reg->WriteString("Baza","DQt8",Form4->DQt8->Text);
  Reg->WriteString("Baza","DQt10",Form4->DQt10->Text);
  Reg->WriteString("Baza","DQt15",Form4->DQt15->Text);
  Reg->WriteString("Baza","DQt20",Form4->DQt20->Text);
  Reg->WriteString("Baza","DQt25",Form4->DQt25->Text);
  Reg->WriteString("Baza","DQt32",Form4->DQt32->Text);
  Reg->WriteString("Baza","DQt40",Form4->DQt40->Text);
  Reg->WriteString("Baza","DQt50",Form4->DQt50->Text);

  Reg->WriteString("Baza","DQmin8",Form4->DQmin8->Text);
  Reg->WriteString("Baza","DQmin10",Form4->DQmin10->Text);
  Reg->WriteString("Baza","DQmin15",Form4->DQmin15->Text);
  Reg->WriteString("Baza","DQmin20",Form4->DQmin20->Text);
  Reg->WriteString("Baza","DQmin25",Form4->DQmin25->Text);
  Reg->WriteString("Baza","DQmin32",Form4->DQmin32->Text);
  Reg->WriteString("Baza","DQmin40",Form4->DQmin40->Text);
  Reg->WriteString("Baza","DQmin50",Form4->DQmin50->Text);

  Reg->WriteString("Baza","Vn8",Form4->Vn8->Text);
  Reg->WriteString("Baza","Vn10",Form4->Vn10->Text);
  Reg->WriteString("Baza","Vn15",Form4->Vn15->Text);
  Reg->WriteString("Baza","Vn20",Form4->Vn20->Text);
  Reg->WriteString("Baza","Vn25",Form4->Vn25->Text);
  Reg->WriteString("Baza","Vn32",Form4->Vn32->Text);
  Reg->WriteString("Baza","Vn40",Form4->Vn40->Text);
  Reg->WriteString("Baza","Vn50",Form4->Vn50->Text);

  Reg->WriteString("Baza","Vt8",Form4->Vt8->Text);
  Reg->WriteString("Baza","Vt10",Form4->Vt10->Text);
  Reg->WriteString("Baza","Vt15",Form4->Vt15->Text);
  Reg->WriteString("Baza","Vt20",Form4->Vt20->Text);
  Reg->WriteString("Baza","Vt25",Form4->Vt25->Text);
  Reg->WriteString("Baza","Vt32",Form4->Vt32->Text);
  Reg->WriteString("Baza","Vt40",Form4->Vt40->Text);
  Reg->WriteString("Baza","Vt50",Form4->Vt50->Text);

  Reg->WriteString("Baza","Vmin8",Form4->Vmin8->Text);
  Reg->WriteString("Baza","Vmin10",Form4->Vmin10->Text);
  Reg->WriteString("Baza","Vmin15",Form4->Vmin15->Text);
  Reg->WriteString("Baza","Vmin20",Form4->Vmin20->Text);
  Reg->WriteString("Baza","Vmin25",Form4->Vmin25->Text);
  Reg->WriteString("Baza","Vmin32",Form4->Vmin32->Text);
  Reg->WriteString("Baza","Vmin40",Form4->Vmin40->Text);
  Reg->WriteString("Baza","Vmin50",Form4->Vmin50->Text);

  Reg->WriteString("Baza","AQmin",Form4->AQmin->Text); //Caaeneiinou Qmin e Qt io EEANNA
  Reg->WriteString("Baza","AQt",Form4->AQt->Text);
  Reg->WriteString("Baza","BQmin",Form4->BQmin->Text);
  Reg->WriteString("Baza","BQt",Form4->BQt->Text);
  Reg->WriteString("Baza","CQmin",Form4->CQmin->Text);
  Reg->WriteString("Baza","CQt",Form4->CQt->Text);

  Reg->WriteString("Baza","TminX",Form4->TminX->Text);  //Ai?y?ay e oieiaiay aiaa I?aaaeu oaiia?aoo?
  Reg->WriteString("Baza","TmaxX",Form4->TmaxX->Text);
  Reg->WriteString("Baza","DminLX",Form4->DminLX->Text);   //I?ioaioiua aiionoeiua iia?aoiinoe
  Reg->WriteString("Baza","DminRX",Form4->DminRX->Text);
  Reg->WriteString("Baza","DtLX",Form4->DtLX->Text);
  Reg->WriteString("Baza","DtRX",Form4->DtRX->Text);
  Reg->WriteString("Baza","DnLX",Form4->DnLX->Text);
  Reg->WriteString("Baza","DnRX",Form4->DnRX->Text);

  Reg->WriteString("Baza","TminG",Form4->TminG->Text);   //I?aaaeu oaiia?aoo?
  Reg->WriteString("Baza","TmaxG",Form4->TmaxG->Text);
  Reg->WriteString("Baza","DminLG",Form4->DminLG->Text); //I?ioaioiua aiionoeiua iia?aoiinoe
  Reg->WriteString("Baza","DminRG",Form4->DminRG->Text);
  Reg->WriteString("Baza","DtLG",Form4->DtLG->Text);
  Reg->WriteString("Baza","DtRG",Form4->DtRG->Text);
  Reg->WriteString("Baza","DnLG",Form4->DnLG->Text);
  Reg->WriteString("Baza","DnRG",Form4->DnRG->Text);
*/
}
//---------------------------------------------------------------------------
void TMainKPSForm::ReadFromReestr(void)
{
  Form4 = new TForm4(this, DM);
  ReadFromReestrToChange();
  delete Form4;
}
//---------------------------------------------------------------------------
void TMainKPSForm::ReadFromReestrToChange(void)
{
  DiametrVn D;

  DM->DiametrList.clear();
 //Aeaiao?u e niioaaonoao?uea QAeaiao?u e niioaaonoao?uea Q
  Form4->d8->Text  = Reg->ReadString("Baza","d8", "8");
  Form4->d10->Text = Reg->ReadString("Baza","d10","10");
  Form4->d15->Text = Reg->ReadString("Baza","d15","15");
  Form4->d20->Text = Reg->ReadString("Baza","d20","20");
  Form4->d25->Text = Reg->ReadString("Baza","d25","25");
  Form4->d32->Text = Reg->ReadString("Baza","d32","32");
  Form4->d40->Text = Reg->ReadString("Baza","d40","40");
  Form4->d50->Text = Reg->ReadString("Baza","d50","50");

  Form4->Qn8->Text  = Reg->ReadString("Baza","Qn8","0.6");
  Form4->Qn10->Text = Reg->ReadString("Baza","Qn10","1.0");
  Form4->Qn15->Text = Reg->ReadString("Baza","Qn15","1.5");
  Form4->Qn20->Text = Reg->ReadString("Baza","Qn20","2.5");
  Form4->Qn25->Text = Reg->ReadString("Baza","Qn25","3.5");
  Form4->Qn32->Text = Reg->ReadString("Baza","Qn32","6.0");
  Form4->Qn40->Text = Reg->ReadString("Baza","Qn40","10.0");
  Form4->Qn50->Text = Reg->ReadString("Baza","Qn50","15.0");

  Form4->DQn8->Text  = Reg->ReadString("Baza","DQn8","0.08");
  Form4->DQn10->Text = Reg->ReadString("Baza","DQn10","0.10");
  Form4->DQn15->Text = Reg->ReadString("Baza","DQn15","0.15");
  Form4->DQn20->Text = Reg->ReadString("Baza","DQn20","0.25");
  Form4->DQn25->Text = Reg->ReadString("Baza","DQn25","0.35");
  Form4->DQn32->Text = Reg->ReadString("Baza","DQn32","0.50");
  Form4->DQn40->Text = Reg->ReadString("Baza","DQn40","0.80");
  Form4->DQn50->Text = Reg->ReadString("Baza","DQn50","1.00");

  Form4->DQt8->Text  = Reg->ReadString("Baza","DQt8","0.008");
  Form4->DQt10->Text = Reg->ReadString("Baza","DQt10","0.008");
  Form4->DQt15->Text = Reg->ReadString("Baza","DQt15","0.012");
  Form4->DQt20->Text = Reg->ReadString("Baza","DQt20","0.020");
  Form4->DQt25->Text = Reg->ReadString("Baza","DQt25","0.028");
  Form4->DQt32->Text = Reg->ReadString("Baza","DQt32","0.040");
  Form4->DQt40->Text = Reg->ReadString("Baza","DQt40","0.064");
  Form4->DQt50->Text = Reg->ReadString("Baza","DQt50","0.080");

  Form4->DQmin8->Text  = Reg->ReadString("Baza","DQmin8","0.6");
  Form4->DQmin10->Text = Reg->ReadString("Baza","DQmin10","1.0");
  Form4->DQmin15->Text = Reg->ReadString("Baza","DQmin15","1.5");
  Form4->DQmin20->Text = Reg->ReadString("Baza","DQmin20","2.5");
  Form4->DQmin25->Text = Reg->ReadString("Baza","DQmin25","3.5");
  Form4->DQmin32->Text = Reg->ReadString("Baza","DQmin32","6.0");
  Form4->DQmin40->Text = Reg->ReadString("Baza","DQmin40","10.0");
  Form4->DQmin50->Text = Reg->ReadString("Baza","DQmin50","15.0");

  Form4->Vn8->Text  = Reg->ReadString("Baza","Vn8","20");
  Form4->Vn10->Text = Reg->ReadString("Baza","Vn10","20");
  Form4->Vn15->Text = Reg->ReadString("Baza","Vn15","20");
  Form4->Vn20->Text = Reg->ReadString("Baza","Vn20","50");
  Form4->Vn25->Text = Reg->ReadString("Baza","Vn25","50");
  Form4->Vn32->Text = Reg->ReadString("Baza","Vn32","100");
  Form4->Vn40->Text = Reg->ReadString("Baza","Vn40","200");
  Form4->Vn50->Text = Reg->ReadString("Baza","Vn50","200");

  Form4->Vt8->Text  = Reg->ReadString("Baza","Vt8","5");
  Form4->Vt10->Text = Reg->ReadString("Baza","Vt10","5");
  Form4->Vt15->Text = Reg->ReadString("Baza","Vt15","5");
  Form4->Vt20->Text = Reg->ReadString("Baza","Vt20","20");
  Form4->Vt25->Text = Reg->ReadString("Baza","Vt25","20");
  Form4->Vt32->Text = Reg->ReadString("Baza","Vt32","50");
  Form4->Vt40->Text = Reg->ReadString("Baza","Vt40","500");
  Form4->Vt50->Text = Reg->ReadString("Baza","Vt50","500");

  Form4->Vmin8->Text  = Reg->ReadString("Baza","Vmin8","2.5");
  Form4->Vmin10->Text = Reg->ReadString("Baza","Vmin10","2.5");
  Form4->Vmin15->Text = Reg->ReadString("Baza","Vmin15","2.5");
  Form4->Vmin20->Text = Reg->ReadString("Baza","Vmin20","10");
  Form4->Vmin25->Text = Reg->ReadString("Baza","Vmin25","10");
  Form4->Vmin32->Text = Reg->ReadString("Baza","Vmin32","25");
  Form4->Vmin40->Text = Reg->ReadString("Baza","Vmin40","50");
  Form4->Vmin50->Text = Reg->ReadString("Baza","Vmin50","50");
  try
  {
    D.Diametr = Form4->d8->Text.ToInt();
    if(DecimalSeparator == '.')
    {
      D.Qn    =  ReplZPnaPunk(Form4->Qn8->Text).ToDouble();
      D.DQn   =  ReplZPnaPunk(Form4->DQn8->Text).ToDouble();
      D.DQt   =  ReplZPnaPunk(Form4->DQt8->Text).ToDouble();
      D.DQmin =  ReplZPnaPunk(Form4->DQmin8->Text).ToDouble();
      D.Vn    =  ReplZPnaPunk(Form4->Vn8->Text).ToDouble();
      D.Vt    =  ReplZPnaPunk(Form4->Vt8->Text).ToDouble();
      D.Vmin  =  ReplZPnaPunk(Form4->Vmin8->Text).ToDouble();
    }
    else
    {
      D.Qn    =  ReplPunknaZP(Form4->Qn8->Text).ToDouble();
      D.DQn   =  ReplPunknaZP(Form4->DQn8->Text).ToDouble();
      D.DQt   =  ReplPunknaZP(Form4->DQt8->Text).ToDouble();
      D.DQmin =  ReplPunknaZP(Form4->DQmin8->Text).ToDouble();
      D.Vn    =  ReplPunknaZP(Form4->Vn8->Text).ToDouble();
      D.Vt    =  ReplPunknaZP(Form4->Vt8->Text).ToDouble();
      D.Vmin  =  ReplPunknaZP(Form4->Vmin8->Text).ToDouble();
    }
    DM->DiametrList.push_back(D);
    D.Diametr = Form4->d10->Text.ToInt();
    if(DecimalSeparator == '.')
    {
      D.Qn    =  ReplZPnaPunk(Form4->Qn10->Text).ToDouble();
      D.DQn   =  ReplZPnaPunk(Form4->DQn10->Text).ToDouble();
      D.DQt   =  ReplZPnaPunk(Form4->DQt10->Text).ToDouble();
      D.DQmin =  ReplZPnaPunk(Form4->DQmin10->Text).ToDouble();
      D.Vn    =  ReplZPnaPunk(Form4->Vn10->Text).ToDouble();
      D.Vt    =  ReplZPnaPunk(Form4->Vt10->Text).ToDouble();
      D.Vmin  =  ReplZPnaPunk(Form4->Vmin10->Text).ToDouble();
    }
    else
    {
      D.Qn    =  ReplPunknaZP(Form4->Qn10->Text).ToDouble();
      D.DQn   =  ReplPunknaZP(Form4->DQn10->Text).ToDouble();
      D.DQt   =  ReplPunknaZP(Form4->DQt10->Text).ToDouble();
      D.DQmin =  ReplPunknaZP(Form4->DQmin10->Text).ToDouble();
      D.Vn    =  ReplPunknaZP(Form4->Vn10->Text).ToDouble();
      D.Vt    =  ReplPunknaZP(Form4->Vt10->Text).ToDouble();
      D.Vmin  =  ReplPunknaZP(Form4->Vmin10->Text).ToDouble();
    }
    DM->DiametrList.push_back(D);
    D.Diametr = Form4->d15->Text.ToInt();
    if(DecimalSeparator == '.')
    {
      D.Qn    =  ReplZPnaPunk(Form4->Qn15->Text).ToDouble();
      D.DQn   =  ReplZPnaPunk(Form4->DQn15->Text).ToDouble();
      D.DQt   =  ReplZPnaPunk(Form4->DQt15->Text).ToDouble();
      D.DQmin =  ReplZPnaPunk(Form4->DQmin15->Text).ToDouble();
      D.Vn    =  ReplZPnaPunk(Form4->Vn15->Text).ToDouble();
      D.Vt    =  ReplZPnaPunk(Form4->Vt15->Text).ToDouble();
      D.Vmin  =  ReplZPnaPunk(Form4->Vmin15->Text).ToDouble();
    }
    else
    {
      D.Qn    =  ReplPunknaZP(Form4->Qn15->Text).ToDouble();
      D.DQn   =  ReplPunknaZP(Form4->DQn15->Text).ToDouble();
      D.DQt   =  ReplPunknaZP(Form4->DQt15->Text).ToDouble();
      D.DQmin =  ReplPunknaZP(Form4->DQmin15->Text).ToDouble();
      D.Vn    =  ReplPunknaZP(Form4->Vn15->Text).ToDouble();
      D.Vt    =  ReplPunknaZP(Form4->Vt15->Text).ToDouble();
      D.Vmin  =  ReplPunknaZP(Form4->Vmin15->Text).ToDouble();
    }
    DM->DiametrList.push_back(D);
    D.Diametr = Form4->d20->Text.ToInt();
    if(DecimalSeparator == '.')
    {
      D.Qn    =  ReplZPnaPunk(Form4->Qn20->Text).ToDouble();
      D.DQn   =  ReplZPnaPunk(Form4->DQn20->Text).ToDouble();
      D.DQt   =  ReplZPnaPunk(Form4->DQt20->Text).ToDouble();
      D.DQmin =  ReplZPnaPunk(Form4->DQmin20->Text).ToDouble();
      D.Vn    =  ReplZPnaPunk(Form4->Vn20->Text).ToDouble();
      D.Vt    =  ReplZPnaPunk(Form4->Vt20->Text).ToDouble();
      D.Vmin  =  ReplZPnaPunk(Form4->Vmin20->Text).ToDouble();
    }
    else
    {
      D.Qn    =  ReplPunknaZP(Form4->Qn20->Text).ToDouble();
      D.DQn   =  ReplPunknaZP(Form4->DQn20->Text).ToDouble();
      D.DQt   =  ReplPunknaZP(Form4->DQt20->Text).ToDouble();
      D.DQmin =  ReplPunknaZP(Form4->DQmin20->Text).ToDouble();
      D.Vn    =  ReplPunknaZP(Form4->Vn20->Text).ToDouble();
      D.Vt    =  ReplPunknaZP(Form4->Vt20->Text).ToDouble();
      D.Vmin  =  ReplPunknaZP(Form4->Vmin20->Text).ToDouble();
    }
    DM->DiametrList.push_back(D);
    D.Diametr = Form4->d25->Text.ToInt();
    if(DecimalSeparator == '.')
    {
      D.Qn    =  ReplZPnaPunk(Form4->Qn25->Text).ToDouble();
      D.DQn   =  ReplZPnaPunk(Form4->DQn25->Text).ToDouble();
      D.DQt   =  ReplZPnaPunk(Form4->DQt25->Text).ToDouble();
      D.DQmin =  ReplZPnaPunk(Form4->DQmin25->Text).ToDouble();
      D.Vn    =  ReplZPnaPunk(Form4->Vn25->Text).ToDouble();
      D.Vt    =  ReplZPnaPunk(Form4->Vt25->Text).ToDouble();
      D.Vmin  =  ReplZPnaPunk(Form4->Vmin25->Text).ToDouble();
    }
    else
    {
      D.Qn    =  ReplPunknaZP(Form4->Qn25->Text).ToDouble();
      D.DQn   =  ReplPunknaZP(Form4->DQn25->Text).ToDouble();
      D.DQt   =  ReplPunknaZP(Form4->DQt25->Text).ToDouble();
      D.DQmin =  ReplPunknaZP(Form4->DQmin25->Text).ToDouble();
      D.Vn    =  ReplPunknaZP(Form4->Vn25->Text).ToDouble();
      D.Vt    =  ReplPunknaZP(Form4->Vt25->Text).ToDouble();
      D.Vmin  =  ReplPunknaZP(Form4->Vmin25->Text).ToDouble();
    }
    DM->DiametrList.push_back(D);
    D.Diametr = Form4->d32->Text.ToInt();
    if(DecimalSeparator == '.')
    {
      D.Qn    =  ReplZPnaPunk(Form4->Qn32->Text).ToDouble();
      D.DQn   =  ReplZPnaPunk(Form4->DQn32->Text).ToDouble();
      D.DQt   =  ReplZPnaPunk(Form4->DQt32->Text).ToDouble();
      D.DQmin =  ReplZPnaPunk(Form4->DQmin32->Text).ToDouble();
      D.Vn    =  ReplZPnaPunk(Form4->Vn32->Text).ToDouble();
      D.Vt    =  ReplZPnaPunk(Form4->Vt32->Text).ToDouble();
      D.Vmin  =  ReplZPnaPunk(Form4->Vmin32->Text).ToDouble();
    }
    else
    {
      D.Qn    =  ReplPunknaZP(Form4->Qn32->Text).ToDouble();
      D.DQn   =  ReplPunknaZP(Form4->DQn32->Text).ToDouble();
      D.DQt   =  ReplPunknaZP(Form4->DQt32->Text).ToDouble();
      D.DQmin =  ReplPunknaZP(Form4->DQmin32->Text).ToDouble();
      D.Vn    =  ReplPunknaZP(Form4->Vn32->Text).ToDouble();
      D.Vt    =  ReplPunknaZP(Form4->Vt32->Text).ToDouble();
      D.Vmin  =  ReplPunknaZP(Form4->Vmin32->Text).ToDouble();
    }
    DM->DiametrList.push_back(D);
    D.Diametr = Form4->d40->Text.ToInt();
    if(DecimalSeparator == '.')
    {
      D.Qn    =  ReplZPnaPunk(Form4->Qn40->Text).ToDouble();
      D.DQn   =  ReplZPnaPunk(Form4->DQn40->Text).ToDouble();
      D.DQt   =  ReplZPnaPunk(Form4->DQt40->Text).ToDouble();
      D.DQmin =  ReplZPnaPunk(Form4->DQmin40->Text).ToDouble();
      D.Vn    =  ReplZPnaPunk(Form4->Vn40->Text).ToDouble();
      D.Vt    =  ReplZPnaPunk(Form4->Vt40->Text).ToDouble();
      D.Vmin  =  ReplZPnaPunk(Form4->Vmin40->Text).ToDouble();
    }
    else
    {
      D.Qn    =  ReplPunknaZP(Form4->Qn40->Text).ToDouble();
      D.DQn   =  ReplPunknaZP(Form4->DQn40->Text).ToDouble();
      D.DQt   =  ReplPunknaZP(Form4->DQt40->Text).ToDouble();
      D.DQmin =  ReplPunknaZP(Form4->DQmin40->Text).ToDouble();
      D.Vn    =  ReplPunknaZP(Form4->Vn40->Text).ToDouble();
      D.Vt    =  ReplPunknaZP(Form4->Vt40->Text).ToDouble();
      D.Vmin  =  ReplPunknaZP(Form4->Vmin40->Text).ToDouble();
    }
    DM->DiametrList.push_back(D);
    D.Diametr = Form4->d50->Text.ToInt();
    if(DecimalSeparator == '.')
    {
      D.Qn    =  ReplZPnaPunk(Form4->Qn50->Text).ToDouble();
      D.DQn   =  ReplZPnaPunk(Form4->DQn50->Text).ToDouble();
      D.DQt   =  ReplZPnaPunk(Form4->DQt50->Text).ToDouble();
      D.DQmin =  ReplZPnaPunk(Form4->DQmin50->Text).ToDouble();
      D.Vn    =  ReplZPnaPunk(Form4->Vn50->Text).ToDouble();
      D.Vt    =  ReplZPnaPunk(Form4->Vt50->Text).ToDouble();
      D.Vmin  =  ReplZPnaPunk(Form4->Vmin50->Text).ToDouble();
    }
    else
    {
      D.Qn    =  ReplPunknaZP(Form4->Qn50->Text).ToDouble();
      D.DQn   =  ReplPunknaZP(Form4->DQn50->Text).ToDouble();
      D.DQt   =  ReplPunknaZP(Form4->DQt50->Text).ToDouble();
      D.DQmin =  ReplPunknaZP(Form4->DQmin50->Text).ToDouble();
      D.Vn    =  ReplPunknaZP(Form4->Vn50->Text).ToDouble();
      D.Vt    =  ReplPunknaZP(Form4->Vt50->Text).ToDouble();
      D.Vmin  =  ReplPunknaZP(Form4->Vmin50->Text).ToDouble();
    }
    DM->DiametrList.push_back(D);
  }
  catch(...)
  {
    ShowMessage("A a?oiia <Aeaiao?u e niioaaonoao?uea Qn, DQn, DQt, DQmin, Vn, Vt, Vmin> aaaaaiu ia ?eneianua cia?aiey");
    delete Form4;
    return;
  }
  DM->ClassList.clear();
  ClassQ   C;
  Form4->AQmin->Text  = Reg->ReadString("Baza","AQmin","0.04"); //Caaeneiinou Qmin e Qt io EEANNA
  Form4->AQt->Text    = Reg->ReadString("Baza","AQt","0.10");
  Form4->BQmin->Text  = Reg->ReadString("Baza","BQmin","0.02");
  Form4->BQt->Text    = Reg->ReadString("Baza","BQt","0.08");
  Form4->CQmin->Text  = Reg->ReadString("Baza","CQmin","0.01");
  Form4->CQt->Text    = Reg->ReadString("Baza","CQt","0.015");
  try
  {
    strcpy(C.Name, Form4->Label77->Caption.c_str());
    if(DecimalSeparator == '.')
    {
      C.Qmin = ReplZPnaPunk(Form4->AQmin->Text).ToDouble();
      C.Qt =   ReplZPnaPunk(Form4->AQt->Text).ToDouble();
    }
    else
    {
      C.Qmin = ReplPunknaZP(Form4->AQmin->Text).ToDouble();
      C.Qt =   ReplPunknaZP(Form4->AQt->Text).ToDouble();
    }
    DM->ClassList.push_back(C);
    strcpy(C.Name, Form4->Label78->Caption.c_str());
    if(DecimalSeparator == '.')
    {
      C.Qmin = ReplZPnaPunk(Form4->BQmin->Text).ToDouble();
      C.Qt =   ReplZPnaPunk(Form4->BQt->Text).ToDouble();
    }
    else
    {
      C.Qmin = ReplPunknaZP(Form4->BQmin->Text).ToDouble();
      C.Qt =   ReplPunknaZP(Form4->BQt->Text).ToDouble();
    }
    DM->ClassList.push_back(C);
    strcpy(C.Name, Form4->Label79->Caption.c_str());
    if(DecimalSeparator == '.')
    {
      C.Qmin = ReplZPnaPunk(Form4->CQmin->Text).ToDouble();
      C.Qt =   ReplZPnaPunk(Form4->CQt->Text).ToDouble();
    }
    else
    {
      C.Qmin = ReplPunknaZP(Form4->CQmin->Text).ToDouble();
      C.Qt =   ReplPunknaZP(Form4->CQt->Text).ToDouble();
    }
    DM->ClassList.push_back(C);
  }
  catch(...)
  {
    ShowMessage("A a?oiia <Caaeneiinou Qmin e Qt io EEANNA> aaaaaiu ia ?eneianua cia?aiey");
    delete Form4;
    return;
  }
  DM->ClassTList.clear();
  ClassT     T;
  Form4->TminX->Text   = Reg->ReadString("Baza","TminX","5");  //Ai?y?ay e oieiaiay aiaa
  Form4->TmaxX->Text   = Reg->ReadString("Baza","TmaxX","30");
  Form4->DminLX->Text  = Reg->ReadString("Baza","DminLX","-5");
  Form4->DminRX->Text  = Reg->ReadString("Baza","DminRX","5");
  Form4->DtLX->Text    = Reg->ReadString("Baza","DtLX","-2");
  Form4->DtRX->Text    = Reg->ReadString("Baza","DtRX","2");
  Form4->DnLX->Text    = Reg->ReadString("Baza","DnLX","-2");
  Form4->DnRX->Text    = Reg->ReadString("Baza","DnRX","2");

  Form4->TminG->Text   = Reg->ReadString("Baza","TminG","30");
  Form4->TmaxG->Text   = Reg->ReadString("Baza","TmaxG","90");
  Form4->DminLG->Text  = Reg->ReadString("Baza","DminLG","-5");
  Form4->DminRG->Text  = Reg->ReadString("Baza","DminRG","5");
  Form4->DtLG->Text    = Reg->ReadString("Baza","DtLG","-3");
  Form4->DtRG->Text    = Reg->ReadString("Baza","DtRG","3");
  Form4->DnLG->Text    = Reg->ReadString("Baza","DnLG","-3");
  Form4->DnRG->Text    = Reg->ReadString("Baza","DnRG","3");
  try
  {
    strcpy(T.Name, "X");
    if(DecimalSeparator == '.')
    {
      T.Tmin  = ReplZPnaPunk(Form4->TminX->Text).ToDouble();
      T.Tmax  = ReplZPnaPunk(Form4->TmaxX->Text).ToDouble();
      T.DminL = ReplZPnaPunk(Form4->DminLX->Text).ToDouble();
      T.DminR = ReplZPnaPunk(Form4->DminRX->Text).ToDouble();
      T.DtL   = ReplZPnaPunk(Form4->DtLX->Text).ToDouble();
      T.DtR   = ReplZPnaPunk(Form4->DtRX->Text).ToDouble();
      T.DnL   = ReplZPnaPunk(Form4->DnLX->Text).ToDouble();
      T.DnR   = ReplZPnaPunk(Form4->DnRX->Text).ToDouble();
    }
    else
    {
      T.Tmin  = ReplPunknaZP(Form4->TminX->Text).ToDouble();
      T.Tmax  = ReplPunknaZP(Form4->TmaxX->Text).ToDouble();
      T.DminL = ReplPunknaZP(Form4->DminLX->Text).ToDouble();
      T.DminR = ReplPunknaZP(Form4->DminRX->Text).ToDouble();
      T.DtL   = ReplPunknaZP(Form4->DtLX->Text).ToDouble();
      T.DtR   = ReplPunknaZP(Form4->DtRX->Text).ToDouble();
      T.DnL   = ReplPunknaZP(Form4->DnLX->Text).ToDouble();
      T.DnR   = ReplPunknaZP(Form4->DnRX->Text).ToDouble();
    }
    DM->ClassTList.push_back(T);
    strcpy(T.Name, "G");
    if(DecimalSeparator == '.')
    {
      T.Tmin  = ReplZPnaPunk(Form4->TminG->Text).ToDouble();
      T.Tmax  = ReplZPnaPunk(Form4->TmaxG->Text).ToDouble();
      T.DminL = ReplZPnaPunk(Form4->DminLG->Text).ToDouble();
      T.DminR = ReplZPnaPunk(Form4->DminRG->Text).ToDouble();
      T.DtL   = ReplZPnaPunk(Form4->DtLG->Text).ToDouble();
      T.DtR   = ReplZPnaPunk(Form4->DtRG->Text).ToDouble();
      T.DnL   = ReplZPnaPunk(Form4->DnLG->Text).ToDouble();
      T.DnR   = ReplZPnaPunk(Form4->DnRG->Text).ToDouble();
    }
    else
    {
      T.Tmin  = ReplPunknaZP(Form4->TminG->Text).ToDouble();
      T.Tmax  = ReplPunknaZP(Form4->TmaxG->Text).ToDouble();
      T.DminL = ReplPunknaZP(Form4->DminLG->Text).ToDouble();
      T.DminR = ReplPunknaZP(Form4->DminRG->Text).ToDouble();
      T.DtL   = ReplPunknaZP(Form4->DtLG->Text).ToDouble();
      T.DtR   = ReplPunknaZP(Form4->DtRG->Text).ToDouble();
      T.DnL   = ReplPunknaZP(Form4->DnLG->Text).ToDouble();
      T.DnR   = ReplPunknaZP(Form4->DnRG->Text).ToDouble();
    }
    DM->ClassTList.push_back(T);
  }
  catch(...)
  {
    ShowMessage("A a?oiia <Ai?y?ay e oieiaiay aiaa> aaaaaiu ia ?eneianua cia?aiey");
    delete Form4;
    return;
  }
}
