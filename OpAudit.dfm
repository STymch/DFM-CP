object AuditForm: TAuditForm
  Left = 11
  Top = 34
  Width = 696
  Height = 531
  BorderIcons = [biSystemMenu]
  Caption = #1040#1076#1084#1080#1085#1080#1089#1090#1088#1080#1088#1086#1074#1072#1085#1080#1077' '#1075#1088#1091#1087#1087' '#1080' '#1086#1087#1077#1088#1072#1090#1086#1088#1086#1074
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -16
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 20
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 688
    Height = 504
    Align = alClient
    Caption = 'Panel1'
    TabOrder = 0
    object Panel2: TPanel
      Left = 1
      Top = 303
      Width = 686
      Height = 200
      Align = alBottom
      Caption = 'Panel2'
      TabOrder = 0
      object Label3: TLabel
        Left = 248
        Top = 4
        Width = 113
        Height = 13
        Caption = #1054#1087#1077#1088#1072#1090#1086#1088#1099' '#1075#1088#1091#1087#1087#1099
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object DrawGrid2: TDrawGrid
        Left = 1
        Top = 24
        Width = 684
        Height = 129
        ColCount = 2
        DefaultRowHeight = 20
        FixedCols = 0
        Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goColSizing, goRowSelect]
        TabOrder = 0
        OnClick = DrawGrid2Click
        OnDrawCell = DrawGrid2DrawCell
        ColWidths = (
          99
          579)
      end
      object AddOp: TButton
        Left = 32
        Top = 162
        Width = 91
        Height = 30
        Caption = #1057#1086#1079#1076#1072#1090#1100
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 1
        OnClick = AddOpClick
      end
      object EditOp: TButton
        Left = 136
        Top = 160
        Width = 125
        Height = 30
        Caption = #1056#1077#1076#1072#1082#1090#1080#1088#1086#1074#1072#1090#1100
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 2
        OnClick = EditOpClick
      end
      object DelOp: TButton
        Left = 276
        Top = 160
        Width = 87
        Height = 30
        Caption = #1059#1076#1072#1083#1080#1090#1100
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 3
        OnClick = DelOpClick
      end
      object BitBtn1: TBitBtn
        Left = 544
        Top = 160
        Width = 101
        Height = 30
        Caption = #1042#1099#1093#1086#1076
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 4
        Kind = bkOK
      end
    end
    object Panel3: TPanel
      Left = 1
      Top = 1
      Width = 272
      Height = 302
      Align = alLeft
      Caption = 'Panel3'
      TabOrder = 1
      object Label1: TLabel
        Left = 76
        Top = 8
        Width = 89
        Height = 13
        Caption = #1055#1088#1072#1074#1072' '#1076#1086#1089#1090#1091#1087#1072
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object CheckListBox1: TCheckListBox
        Left = 1
        Top = 36
        Width = 270
        Height = 265
        Align = alBottom
        Constraints.MinHeight = 20
        Enabled = False
        ItemHeight = 20
        Style = lbOwnerDrawFixed
        TabOrder = 0
      end
    end
    object Panel4: TPanel
      Left = 273
      Top = 1
      Width = 414
      Height = 302
      Align = alClient
      Caption = 'Panel4'
      TabOrder = 2
      object Label2: TLabel
        Left = 148
        Top = 8
        Width = 117
        Height = 13
        Caption = #1043#1088#1091#1087#1087#1099' '#1086#1087#1077#1088#1072#1090#1086#1088#1086#1074
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object DrawGrid1: TDrawGrid
        Left = 2
        Top = 28
        Width = 408
        Height = 217
        ColCount = 2
        DefaultRowHeight = 20
        FixedCols = 0
        Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goColSizing, goRowSelect]
        TabOrder = 0
        OnClick = DrawGrid1Click
        OnDrawCell = DrawGrid1DrawCell
        ColWidths = (
          96
          326)
      end
      object NewGroups: TButton
        Left = 12
        Top = 255
        Width = 97
        Height = 30
        Caption = #1057#1086#1079#1076#1072#1090#1100
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 1
        OnClick = NewGroupsClick
      end
      object EditGroup: TButton
        Left = 120
        Top = 255
        Width = 129
        Height = 30
        Caption = #1056#1077#1076#1072#1082#1090#1080#1088#1086#1074#1072#1090#1100
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 2
        OnClick = EditGroupClick
      end
      object DelGroup: TButton
        Left = 260
        Top = 255
        Width = 81
        Height = 30
        Caption = #1059#1076#1072#1083#1080#1090#1100
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 3
        OnClick = DelGroupClick
      end
    end
  end
end
