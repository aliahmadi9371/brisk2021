object mainForm: TmainForm
  Left = 0
  Top = 0
  BorderStyle = bsToolWindow
  Caption = 'Brisk Viewer'
  ClientHeight = 349
  ClientWidth = 645
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  OnResize = FormResize
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object mainPanel: TPanel
    Left = 0
    Top = 0
    Width = 645
    Height = 324
    Align = alClient
    Color = clGrayText
    ParentBackground = False
    TabOrder = 0
  end
  object AdvOfficeStatusBar1: TAdvOfficeStatusBar
    Left = 0
    Top = 324
    Width = 645
    Height = 25
    AnchorHint = False
    Panels = <
      item
        AppearanceStyle = psLight
        DateFormat = 'M/d/yyyy'
        Progress.BackGround = clNone
        Progress.Indication = piPercentage
        Progress.Min = 0
        Progress.Max = 100
        Progress.Position = 0
        Progress.Level0Color = clLime
        Progress.Level0ColorTo = 14811105
        Progress.Level1Color = clYellow
        Progress.Level1ColorTo = 13303807
        Progress.Level2Color = 5483007
        Progress.Level2ColorTo = 11064319
        Progress.Level3Color = clRed
        Progress.Level3ColorTo = 13290239
        Progress.Level1Perc = 70
        Progress.Level2Perc = 90
        Progress.BorderColor = clBlack
        Progress.ShowBorder = False
        Progress.Stacked = False
        TimeFormat = 'h:mm:ss AMPM'
        Width = 550
      end
      item
        AppearanceStyle = psLight
        DateFormat = 'M/d/yyyy'
        Progress.BackGround = clNone
        Progress.Indication = piPercentage
        Progress.Min = 0
        Progress.Max = 100
        Progress.Position = 0
        Progress.Level0Color = clLime
        Progress.Level0ColorTo = 14811105
        Progress.Level1Color = clYellow
        Progress.Level1ColorTo = 13303807
        Progress.Level2Color = 5483007
        Progress.Level2ColorTo = 11064319
        Progress.Level3Color = clRed
        Progress.Level3ColorTo = 13290239
        Progress.Level1Perc = 70
        Progress.Level2Perc = 90
        Progress.BorderColor = clBlack
        Progress.ShowBorder = False
        Progress.Stacked = False
        TimeFormat = 'h:mm:ss AMPM'
        Width = -1
      end>
    ShowSplitter = True
    SimplePanel = False
    Styler = AdvOfficeStatusBarOfficeStyler1
    Version = '1.6.1.5'
    object Lable_Status: TLabel
      Left = 0
      Top = 0
      Width = 94
      Height = 25
      Align = alLeft
      Caption = '    Waves Loaded .'
      Layout = tlCenter
      ExplicitHeight = 16
    end
    object Label_Status1: TLabel
      Left = 549
      Top = 0
      Width = 96
      Height = 25
      Align = alRight
      Caption = 'BRISK_VIEWER       '
      Layout = tlCenter
      ExplicitHeight = 16
    end
  end
  object dialog_Open: TOpenDialog
    Left = 392
    Top = 16
  end
  object MainMenu1: TMainMenu
    Left = 16
    Top = 24
    object File1: TMenuItem
      Caption = 'File'
      object Open1: TMenuItem
        Caption = 'Open'
        OnClick = Open1Click
      end
      object Exit1: TMenuItem
        Caption = 'Exit'
        OnClick = Exit1Click
      end
    end
  end
  object AdvOfficeStatusBarOfficeStyler1: TAdvOfficeStatusBarOfficeStyler
    Style = psOffice2013LightGray
    BorderColor = 13027014
    PanelAppearanceLight.BorderColor = clNone
    PanelAppearanceLight.BorderColorHot = 15381630
    PanelAppearanceLight.BorderColorDown = 15048022
    PanelAppearanceLight.Color = 16448250
    PanelAppearanceLight.ColorTo = 16448250
    PanelAppearanceLight.ColorHot = 16576740
    PanelAppearanceLight.ColorHotTo = 16576740
    PanelAppearanceLight.ColorDown = 16573128
    PanelAppearanceLight.ColorDownTo = 16573128
    PanelAppearanceLight.ColorMirror = clNone
    PanelAppearanceLight.ColorMirrorTo = clNone
    PanelAppearanceLight.ColorMirrorHot = 16576740
    PanelAppearanceLight.ColorMirrorHotTo = 16576740
    PanelAppearanceLight.ColorMirrorDown = 16573128
    PanelAppearanceLight.ColorMirrorDownTo = 16573128
    PanelAppearanceLight.TextColor = clBlack
    PanelAppearanceLight.TextColorHot = clBlack
    PanelAppearanceLight.TextColorDown = clBlack
    PanelAppearanceLight.TextStyle = []
    PanelAppearanceDark.BorderColor = 13027014
    PanelAppearanceDark.BorderColorHot = 15381630
    PanelAppearanceDark.BorderColorDown = 15048022
    PanelAppearanceDark.Color = 16185078
    PanelAppearanceDark.ColorTo = 16185078
    PanelAppearanceDark.ColorHot = 16576740
    PanelAppearanceDark.ColorHotTo = 16576740
    PanelAppearanceDark.ColorDown = 16573128
    PanelAppearanceDark.ColorDownTo = 16573128
    PanelAppearanceDark.ColorMirror = clNone
    PanelAppearanceDark.ColorMirrorTo = clNone
    PanelAppearanceDark.ColorMirrorHot = 16576740
    PanelAppearanceDark.ColorMirrorHotTo = 16576740
    PanelAppearanceDark.ColorMirrorDown = 16573128
    PanelAppearanceDark.ColorMirrorDownTo = 16573128
    PanelAppearanceDark.TextColor = clBlack
    PanelAppearanceDark.TextColorHot = clBlack
    PanelAppearanceDark.TextColorDown = clBlack
    PanelAppearanceDark.TextStyle = []
    Left = 152
    Top = 48
  end
end
