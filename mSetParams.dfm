object SelectParamsForm: TSelectParamsForm
  Left = 22
  Top = 9
  Width = 976
  Height = 621
  Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1080
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -16
  Font.Name = 'MS Sans Serif'
  Font.Style = [fsBold]
  OldCreateOrder = False
  OnCloseQuery = FormCloseQuery
  PixelsPerInch = 96
  TextHeight = 20
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 968
    Height = 594
    Align = alClient
    TabOrder = 0
    object GroupBox3: TGroupBox
      Left = 16
      Top = 8
      Width = 265
      Height = 281
      Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1072' '#1057#1054#1052' '#1087#1086#1088#1090#1072
      TabOrder = 0
      object Label44: TLabel
        Left = 36
        Top = 246
        Width = 81
        Height = 20
        Caption = #1057#1082#1086#1088#1086#1089#1090#1100
      end
      object ComboBox2: TComboBox
        Left = 144
        Top = 244
        Width = 85
        Height = 28
        ItemHeight = 20
        TabOrder = 0
        Text = '38400'
        Items.Strings = (
          '115200'
          '57600'
          '38400'
          '17200')
      end
      object Com3: TRadioButton
        Left = 36
        Top = 82
        Width = 85
        Height = 17
        Caption = 'Com3'
        Checked = True
        TabOrder = 1
        TabStop = True
      end
      object Com4: TRadioButton
        Left = 166
        Top = 82
        Width = 83
        Height = 17
        Caption = 'Com4'
        TabOrder = 2
      end
      object Com5: TRadioButton
        Left = 36
        Top = 124
        Width = 89
        Height = 17
        Caption = 'Com5'
        TabOrder = 3
      end
      object Com6: TRadioButton
        Left = 166
        Top = 124
        Width = 89
        Height = 17
        Caption = 'Com6'
        TabOrder = 4
      end
      object Com7: TRadioButton
        Left = 36
        Top = 164
        Width = 85
        Height = 17
        Caption = 'Com7'
        TabOrder = 5
      end
      object Com8: TRadioButton
        Left = 166
        Top = 164
        Width = 85
        Height = 17
        Caption = 'Com8'
        TabOrder = 6
      end
      object Com9: TRadioButton
        Left = 36
        Top = 207
        Width = 113
        Height = 17
        Caption = 'Com9'
        TabOrder = 7
      end
      object Com10: TRadioButton
        Left = 166
        Top = 207
        Width = 85
        Height = 17
        Caption = 'Com10'
        TabOrder = 8
      end
      object Com1: TRadioButton
        Left = 36
        Top = 40
        Width = 77
        Height = 17
        Caption = 'Com1'
        TabOrder = 9
      end
      object Com2: TRadioButton
        Left = 166
        Top = 40
        Width = 89
        Height = 17
        Caption = 'Com2'
        TabOrder = 10
      end
    end
    object GroupBox17: TGroupBox
      Left = 536
      Top = 8
      Width = 125
      Height = 236
      Caption = 'DN'
      TabOrder = 1
      object RadioButton9: TRadioButton
        Left = 24
        Top = 48
        Width = 80
        Height = 17
        Caption = '10 '#1084#1084
        TabOrder = 0
      end
      object RadioButton10: TRadioButton
        Left = 24
        Top = 116
        Width = 80
        Height = 17
        Caption = '15 '#1084#1084
        Checked = True
        TabOrder = 1
        TabStop = True
      end
      object RadioButton11: TRadioButton
        Left = 24
        Top = 184
        Width = 80
        Height = 17
        Caption = '20 '#1084#1084
        TabOrder = 2
      end
    end
    object GroupBox16: TGroupBox
      Left = 295
      Top = 8
      Width = 226
      Height = 236
      Caption = #1057#1090#1072#1085#1076#1072#1088#1090
      TabOrder = 2
      object ESOBtn: TRadioButton
        Left = 16
        Top = 48
        Width = 193
        Height = 17
        Caption = #1044#1057#1058#1059' EN ISO 4064-1'
        Checked = True
        TabOrder = 0
        TabStop = True
        OnClick = ESOBtnClick
      end
      object OIMLBtn: TRadioButton
        Left = 16
        Top = 116
        Width = 193
        Height = 17
        Caption = #1044#1057#1058#1059' OIML R 49-1'
        TabOrder = 1
        OnClick = OIMLBtnClick
      end
      object DSTUBtn: TRadioButton
        Left = 16
        Top = 184
        Width = 113
        Height = 17
        Caption = #1044#1057#1058#1059' 3580'
        TabOrder = 2
        OnClick = DSTUBtnClick
      end
    end
    object GroupBox15: TGroupBox
      Left = 678
      Top = 8
      Width = 89
      Height = 236
      Caption = #1050#1083#1072#1089#1089
      TabOrder = 3
      object KL1Btn: TRadioButton
        Left = 24
        Top = 32
        Width = 50
        Height = 17
        Caption = '1'
        TabOrder = 0
      end
      object KL2Btn: TRadioButton
        Left = 24
        Top = 88
        Width = 50
        Height = 17
        Caption = '2'
        Checked = True
        TabOrder = 1
        TabStop = True
      end
      object KLABtn: TRadioButton
        Left = 24
        Top = 144
        Width = 50
        Height = 17
        Caption = 'A'
        TabOrder = 2
      end
      object KLBBtn: TRadioButton
        Left = 24
        Top = 204
        Width = 50
        Height = 17
        Caption = 'B'
        TabOrder = 3
      end
    end
    object GroupBox13: TGroupBox
      Left = 790
      Top = 8
      Width = 163
      Height = 129
      Caption = #1042#1086#1076#1072
      TabOrder = 4
      object RadioButton8: TRadioButton
        Left = 16
        Top = 40
        Width = 113
        Height = 17
        Caption = 'X'#1086#1083#1086#1076#1085#1072#1103
        Checked = True
        TabOrder = 0
        TabStop = True
      end
      object RadioButton12: TRadioButton
        Left = 16
        Top = 80
        Width = 113
        Height = 17
        Caption = #1043#1086#1088#1103#1095#1072#1103
        TabOrder = 1
      end
    end
    object GroupBox1: TGroupBox
      Left = 790
      Top = 144
      Width = 163
      Height = 113
      Caption = #1062#1077#1085#1072' '#1085#1072#1080#1084#1077#1085#1100#1096'.'
      TabOrder = 5
      object Label1: TLabel
        Left = 8
        Top = 24
        Width = 118
        Height = 20
        Caption = #1088#1072#1079#1088#1103#1076#1072'('#1076#1084'3)'
      end
      object Edit1: TEdit
        Left = 24
        Top = 56
        Width = 121
        Height = 28
        TabOrder = 0
        Text = '0.05'
      end
    end
    object GroupBox5: TGroupBox
      Left = 16
      Top = 300
      Width = 937
      Height = 217
      Caption = #1055#1072#1088#1072#1084#1077#1090#1088#1099' '#1089#1095#1077#1090#1095#1080#1082#1072
      TabOrder = 6
      object Label47: TLabel
        Left = 88
        Top = 26
        Width = 73
        Height = 20
        Caption = #1056#1072#1089#1093#1086#1076#1099
      end
      object Label48: TLabel
        Left = 204
        Top = 26
        Width = 127
        Height = 20
        Caption = #1054#1090#1085'. '#1087#1086#1075#1088'.. '#1074' %'
      end
      object Label49: TLabel
        Left = 812
        Top = 26
        Width = 110
        Height = 20
        Caption = 'V '#1087#1088#1086#1083#1080#1074#1072', '#1083
      end
      object Label50: TLabel
        Left = 16
        Top = 76
        Width = 42
        Height = 20
        Caption = 'Qmin'
      end
      object Label51: TLabel
        Left = 16
        Top = 132
        Width = 20
        Height = 20
        Caption = 'Qt'
      end
      object Label52: TLabel
        Left = 16
        Top = 180
        Width = 48
        Height = 20
        Caption = 'Qnom'
      end
      object Label70: TLabel
        Left = 704
        Top = 50
        Width = 71
        Height = 20
        Caption = #1043#1086#1088#1103#1095#1072#1103
      end
      object Label71: TLabel
        Left = 608
        Top = 26
        Width = 135
        Height = 20
        Caption = #1044#1080#1072#1087#1086#1079#1086#1085' T '#1074' '#1057' '
      end
      object Label73: TLabel
        Left = 652
        Top = 72
        Width = 66
        Height = 20
        Caption = #1053#1080#1078#1085#1080#1081
      end
      object Label74: TLabel
        Left = 652
        Top = 136
        Width = 71
        Height = 20
        Caption = #1042#1077#1088#1093#1085#1080#1081
      end
      object Label2: TLabel
        Left = 96
        Top = 48
        Width = 55
        Height = 20
        Caption = ' '#1076#1084'3/'#1095
      end
      object Label3: TLabel
        Left = 388
        Top = 26
        Width = 155
        Height = 20
        Caption = #1044#1080#1072#1087#1086#1079#1086#1085' Q '#1076#1084'3/'#1095
      end
      object Label4: TLabel
        Left = 384
        Top = 48
        Width = 77
        Height = 20
        Caption = #1084#1077#1085#1100#1096#1072#1103
      end
      object Label5: TLabel
        Left = 480
        Top = 48
        Width = 76
        Height = 20
        Caption = #1073#1086#1083#1100#1096#1072#1103
      end
      object Label6: TLabel
        Left = 592
        Top = 50
        Width = 86
        Height = 20
        Caption = #1061#1086#1083#1086#1076#1085#1072#1103
      end
      object Edit8: TEdit
        Left = 72
        Top = 76
        Width = 116
        Height = 28
        TabOrder = 0
        Text = '30.000'
      end
      object Edit9: TEdit
        Left = 72
        Top = 130
        Width = 116
        Height = 28
        TabOrder = 1
        Text = '120.000'
      end
      object Edit10: TEdit
        Left = 72
        Top = 178
        Width = 116
        Height = 28
        TabOrder = 2
        Text = '1500.000'
      end
      object Edit11: TEdit
        Left = 240
        Top = 76
        Width = 60
        Height = 28
        TabOrder = 3
        Text = '-5'
      end
      object Edit12: TEdit
        Left = 240
        Top = 130
        Width = 60
        Height = 28
        TabOrder = 4
        Text = '2'
      end
      object Edit13: TEdit
        Left = 240
        Top = 178
        Width = 60
        Height = 28
        TabOrder = 5
        Text = '-2'
      end
      object Edit18: TEdit
        Left = 816
        Top = 130
        Width = 80
        Height = 28
        TabOrder = 6
        Text = '10.00'
      end
      object Edit19: TEdit
        Left = 816
        Top = 174
        Width = 80
        Height = 28
        TabOrder = 7
        Text = '10.00'
      end
      object Edit24: TEdit
        Left = 596
        Top = 98
        Width = 77
        Height = 28
        TabOrder = 8
        Text = '5.00'
      end
      object Edit27: TEdit
        Left = 600
        Top = 162
        Width = 73
        Height = 28
        TabOrder = 9
        Text = '30.00'
      end
      object Edit17: TEdit
        Left = 816
        Top = 78
        Width = 80
        Height = 28
        TabOrder = 10
        Text = '10.00'
      end
      object Edit2: TEdit
        Left = 376
        Top = 76
        Width = 80
        Height = 28
        TabOrder = 11
        Text = '30.00'
      end
      object Edit3: TEdit
        Left = 480
        Top = 76
        Width = 80
        Height = 28
        TabOrder = 12
        Text = '36.00'
      end
      object Edit4: TEdit
        Left = 376
        Top = 130
        Width = 80
        Height = 28
        TabOrder = 13
        Text = '120.00'
      end
      object Edit5: TEdit
        Left = 480
        Top = 130
        Width = 80
        Height = 28
        TabOrder = 14
        Text = '132.00'
      end
      object Edit6: TEdit
        Left = 376
        Top = 178
        Width = 80
        Height = 28
        TabOrder = 15
        Text = '132.00'
      end
      object Edit7: TEdit
        Left = 480
        Top = 178
        Width = 80
        Height = 28
        TabOrder = 16
        Text = '1500.00'
      end
      object Edit14: TEdit
        Left = 704
        Top = 98
        Width = 77
        Height = 28
        TabOrder = 17
        Text = '30.00'
      end
      object Edit15: TEdit
        Left = 704
        Top = 162
        Width = 77
        Height = 28
        TabOrder = 18
        Text = '90.00'
      end
    end
    object BitBtn1: TBitBtn
      Left = 56
      Top = 530
      Width = 170
      Height = 45
      Caption = #1054#1090#1084#1077#1085#1072
      TabOrder = 7
      OnClick = BitBtn1Click
      Kind = bkCancel
    end
    object BitBtn2: TBitBtn
      Left = 736
      Top = 530
      Width = 170
      Height = 45
      Caption = #1059#1089#1090#1072#1085#1086#1074#1080#1090#1100
      TabOrder = 8
      OnClick = BitBtn2Click
      Kind = bkOK
    end
    object Button1: TButton
      Left = 520
      Top = 252
      Width = 161
      Height = 49
      Caption = #1042#1099#1073#1088#1072#1090#1100
      TabOrder = 9
      OnClick = Button1Click
    end
  end
end
