object SettingFrm: TSettingFrm
  Left = 0
  Top = 0
  Align = alClient
  BorderStyle = bsNone
  Caption = 'SettingForm'
  ClientHeight = 338
  ClientWidth = 651
  Color = 6374456
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  OnKeyPress = FormKeyPress
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object PanelSubMonitor: TAdvPanel
    Left = 8
    Top = 38
    Width = 625
    Height = 235
    BevelOuter = bvNone
    Color = 5584425
    TabOrder = 0
    UseDockManager = True
    Version = '2.4.2.0'
    AutoSize.Height = False
    AutoSize.Width = False
    BackgroundPosition = bpCenter
    BorderColor = clWhite
    Caption.Color = clHighlight
    Caption.ColorTo = clNone
    Caption.Font.Charset = DEFAULT_CHARSET
    Caption.Font.Color = clWindowText
    Caption.Font.Height = -11
    Caption.Font.Name = 'Tahoma'
    Caption.Font.Style = []
    CollapsColor = clWhite
    DoubleBuffered = True
    StatusBar.Font.Charset = DEFAULT_CHARSET
    StatusBar.Font.Color = clWindowText
    StatusBar.Font.Height = -11
    StatusBar.Font.Name = 'Tahoma'
    StatusBar.Font.Style = []
    Text = ''
    FullHeight = 200
    object PanelLabelMonitor: TPanel
      Left = 0
      Top = 0
      Width = 625
      Height = 31
      ParentCustomHint = False
      Align = alTop
      BevelWidth = 2
      BiDiMode = bdLeftToRight
      Caption = 'PanelLabelRetract'
      Color = 4467489
      Ctl3D = True
      DoubleBuffered = True
      ParentBiDiMode = False
      ParentBackground = False
      ParentCtl3D = False
      ParentDoubleBuffered = False
      TabOrder = 0
      object LabelMonitor: TLabel
        Left = 2
        Top = 2
        Width = 621
        Height = 27
        ParentCustomHint = False
        Align = alClient
        Alignment = taCenter
        BiDiMode = bdLeftToRight
        Caption = 'Monitoring'
        Color = clWhite
        Font.Charset = ANSI_CHARSET
        Font.Color = 5584425
        Font.Height = -13
        Font.Name = 'Segoe UI'
        Font.Style = [fsBold]
        ParentBiDiMode = False
        ParentColor = False
        ParentFont = False
        ParentShowHint = False
        ShowHint = False
        Transparent = False
        Layout = tlCenter
        ExplicitWidth = 70
        ExplicitHeight = 17
      end
    end
    object PanelMode: TPanel
      Left = 16
      Top = 61
      Width = 300
      Height = 30
      Margins.Left = 10
      Margins.Top = 10
      Margins.Right = 10
      Margins.Bottom = 10
      ParentCustomHint = False
      BevelOuter = bvNone
      BiDiMode = bdLeftToRight
      Caption = 'PanelMode'
      Color = 5584425
      Ctl3D = True
      DoubleBuffered = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentBiDiMode = False
      ParentBackground = False
      ParentCtl3D = False
      ParentDoubleBuffered = False
      ParentFont = False
      ParentShowHint = False
      ShowCaption = False
      ShowHint = False
      TabOrder = 1
      object BriskModeEditLbl: TAdvGlassButton
        AlignWithMargins = True
        Left = 5
        Top = 2
        Width = 100
        Height = 25
        Margins.Left = 5
        Margins.Right = 5
        ParentCustomHint = False
        AntiAlias = aaNone
        BackColor = 6374456
        BackGroundSymbolColor = 6374456
        Caption = 'Brisk Mode'
        CornerRadius = 5
        Enabled = False
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWhite
        Font.Height = -13
        Font.Name = 'Segoe UI'
        Font.Style = [fsBold]
        ForeColor = 6374456
        GlowColor = 6374456
        InnerBorderColor = 6374456
        OuterBorderColor = 9135959
        ParentFont = False
        ParentShowHint = False
        ParentBiDiMode = False
        ShineColor = 6374456
        ShortCutHintPos = shpCenter
        ShowHint = False
        TabOrder = 0
        Version = '1.3.0.2'
      end
      object BriskModeEdit: TAdvGlassButton
        Left = 115
        Top = 2
        Width = 170
        Height = 25
        Margins.Left = 5
        Margins.Right = 5
        ParentCustomHint = False
        AntiAlias = aaNone
        BackColor = clWhite
        CornerRadius = 5
        Enabled = False
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWhite
        Font.Height = -13
        Font.Name = 'Segoe UI'
        Font.Style = [fsBold]
        ForeColor = clWhite
        GlowColor = clWhite
        InnerBorderColor = 9135959
        OuterBorderColor = 9135959
        ParentFont = False
        ParentShowHint = False
        ParentBiDiMode = False
        ShineColor = clWhite
        ShortCutHintPos = shpCenter
        ShowHint = False
        TabOrder = 1
        Version = '1.3.0.2'
      end
    end
    object PanelIp: TPanel
      AlignWithMargins = True
      Left = 326
      Top = 58
      Width = 300
      Height = 30
      ParentCustomHint = False
      BevelOuter = bvNone
      BiDiMode = bdLeftToRight
      Caption = 'Panel1'
      Color = 5584425
      Ctl3D = True
      DoubleBuffered = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentBiDiMode = False
      ParentBackground = False
      ParentCtl3D = False
      ParentDoubleBuffered = False
      ParentFont = False
      ParentShowHint = False
      ShowCaption = False
      ShowHint = False
      TabOrder = 2
      object BriskIpLbl: TAdvGlassButton
        AlignWithMargins = True
        Left = 5
        Top = 2
        Width = 100
        Height = 25
        Margins.Left = 5
        Margins.Right = 5
        ParentCustomHint = False
        AntiAlias = aaNone
        BackColor = 6374456
        BackGroundSymbolColor = 6374456
        Caption = 'Brisk Ip'
        CornerRadius = 5
        Enabled = False
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWhite
        Font.Height = -13
        Font.Name = 'Segoe UI'
        Font.Style = [fsBold]
        ForeColor = 6374456
        GlowColor = 6374456
        InnerBorderColor = 6374456
        OuterBorderColor = 6374456
        ParentFont = False
        ParentShowHint = False
        ParentBiDiMode = False
        ShineColor = 6374456
        ShortCutHintPos = shpCenter
        ShowHint = False
        TabOrder = 0
        Version = '1.3.0.2'
      end
      object BriskIp: TAdvGlassButton
        Left = 115
        Top = 3
        Width = 170
        Height = 25
        Margins.Left = 5
        Margins.Right = 5
        ParentCustomHint = False
        AntiAlias = aaNone
        BackColor = clWhite
        CornerRadius = 5
        Enabled = False
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWhite
        Font.Height = -13
        Font.Name = 'Segoe UI'
        Font.Style = [fsBold]
        ForeColor = clWhite
        GlowColor = clWhite
        InnerBorderColor = 9135959
        OuterBorderColor = 9135959
        ParentFont = False
        ParentShowHint = False
        ParentBiDiMode = False
        ShineColor = clWhite
        ShortCutHintPos = shpCenter
        ShowHint = False
        TabOrder = 1
        Version = '1.3.0.2'
      end
    end
    object ConfigButtonPanel: TAdvPanel
      Left = 18
      Top = 101
      Width = 280
      Height = 44
      BevelOuter = bvNone
      Color = 5584425
      TabOrder = 3
      UseDockManager = True
      Version = '2.4.2.0'
      AutoSize.Height = False
      AutoSize.Width = False
      BackgroundPosition = bpCenter
      BorderColor = clWhite
      Caption.Color = clHighlight
      Caption.ColorTo = clNone
      Caption.Font.Charset = DEFAULT_CHARSET
      Caption.Font.Color = clWindowText
      Caption.Font.Height = -11
      Caption.Font.Name = 'Tahoma'
      Caption.Font.Style = []
      CollapsColor = clWhite
      DoubleBuffered = True
      StatusBar.Font.Charset = DEFAULT_CHARSET
      StatusBar.Font.Color = clWindowText
      StatusBar.Font.Height = -11
      StatusBar.Font.Name = 'Tahoma'
      StatusBar.Font.Style = []
      Text = ''
      FullHeight = 200
      object ConfigButton: TAdvGlowButton
        AlignWithMargins = True
        Left = 3
        Top = 3
        Width = 274
        Height = 38
        Align = alClient
        Caption = 'Show Configs'
        Font.Charset = ANSI_CHARSET
        Font.Color = clWhite
        Font.Height = -13
        Font.Name = 'Segoe UI'
        Font.Style = [fsBold]
        NotesFont.Charset = DEFAULT_CHARSET
        NotesFont.Color = clWindowText
        NotesFont.Height = -11
        NotesFont.Name = 'Tahoma'
        NotesFont.Style = []
        ParentFont = False
        WordWrap = False
        TabOrder = 0
        OnClick = ConfigButtonClick
        Appearance.BorderColor = 9135959
        Appearance.BorderColorHot = 9135959
        Appearance.BorderColorCheckedHot = 9135959
        Appearance.BorderColorDown = 9135959
        Appearance.BorderColorChecked = 9135959
        Appearance.BorderColorDisabled = 9135959
        Appearance.BorderColorFocused = 9135959
        Appearance.Color = 9135959
        Appearance.ColorTo = 5584425
        Appearance.ColorChecked = 9135959
        Appearance.ColorCheckedTo = 9135959
        Appearance.ColorDisabled = 9135959
        Appearance.ColorDisabledTo = 9135959
        Appearance.ColorDown = 9135959
        Appearance.ColorDownTo = 9135959
        Appearance.ColorHot = 9135959
        Appearance.ColorHotTo = 9135959
        Appearance.ColorMirror = 5584425
        Appearance.ColorMirrorTo = 5584425
        Appearance.ColorMirrorHot = 9135959
        Appearance.ColorMirrorHotTo = 9135959
        Appearance.ColorMirrorDown = 9135959
        Appearance.ColorMirrorDownTo = 9135959
        Appearance.ColorMirrorChecked = 9135959
        Appearance.ColorMirrorCheckedTo = 9135959
        Appearance.ColorMirrorDisabled = 9135959
        Appearance.ColorMirrorDisabledTo = 9135959
        Appearance.TextColorChecked = clWhite
        Appearance.TextColorDown = clWhite
        Appearance.TextColorHot = clWhite
      end
    end
    object PanelID: TPanel
      Left = 18
      Top = 170
      Width = 300
      Height = 30
      Margins.Left = 10
      Margins.Top = 10
      Margins.Right = 10
      Margins.Bottom = 10
      ParentCustomHint = False
      BevelOuter = bvNone
      BiDiMode = bdLeftToRight
      Caption = 'PanelMode'
      Color = 5584425
      Ctl3D = True
      DoubleBuffered = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentBiDiMode = False
      ParentBackground = False
      ParentCtl3D = False
      ParentDoubleBuffered = False
      ParentFont = False
      ParentShowHint = False
      ShowCaption = False
      ShowHint = False
      TabOrder = 4
      object ClientIDEditLbl: TAdvGlassButton
        AlignWithMargins = True
        Left = 5
        Top = 2
        Width = 100
        Height = 25
        Margins.Left = 5
        Margins.Right = 5
        ParentCustomHint = False
        AntiAlias = aaNone
        BackColor = 6374456
        BackGroundSymbolColor = 6374456
        Caption = 'Client ID'
        CornerRadius = 5
        Enabled = False
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWhite
        Font.Height = -13
        Font.Name = 'Segoe UI'
        Font.Style = [fsBold]
        ForeColor = 6374456
        GlowColor = 6374456
        InnerBorderColor = 6374456
        OuterBorderColor = 9135959
        ParentFont = False
        ParentShowHint = False
        ParentBiDiMode = False
        ShineColor = 6374456
        ShortCutHintPos = shpCenter
        ShowHint = False
        TabOrder = 0
        Version = '1.3.0.2'
      end
      object ClientIDEdit: TAdvGlassButton
        Left = 115
        Top = 2
        Width = 170
        Height = 25
        Margins.Left = 5
        Margins.Right = 5
        ParentCustomHint = False
        AntiAlias = aaNone
        BackColor = clWhite
        CornerRadius = 5
        Enabled = False
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWhite
        Font.Height = -13
        Font.Name = 'Segoe UI'
        Font.Style = [fsBold]
        ForeColor = clWhite
        GlowColor = clWhite
        InnerBorderColor = 9135959
        OuterBorderColor = 9135959
        ParentFont = False
        ParentShowHint = False
        ParentBiDiMode = False
        ShineColor = clWhite
        ShortCutHintPos = shpCenter
        ShowHint = False
        TabOrder = 1
        Version = '1.3.0.2'
      end
    end
    object PanelVersion: TPanel
      Left = 326
      Top = 170
      Width = 300
      Height = 30
      Margins.Left = 10
      Margins.Top = 10
      Margins.Right = 10
      Margins.Bottom = 10
      ParentCustomHint = False
      BevelOuter = bvNone
      BiDiMode = bdLeftToRight
      Caption = 'PanelMode'
      Color = 5584425
      Ctl3D = True
      DoubleBuffered = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentBiDiMode = False
      ParentBackground = False
      ParentCtl3D = False
      ParentDoubleBuffered = False
      ParentFont = False
      ParentShowHint = False
      ShowCaption = False
      ShowHint = False
      TabOrder = 5
      object SoftwareVersionEditLbl: TAdvGlassButton
        AlignWithMargins = True
        Left = 5
        Top = 2
        Width = 100
        Height = 25
        Margins.Left = 5
        Margins.Right = 5
        ParentCustomHint = False
        AntiAlias = aaNone
        BackColor = 6374456
        BackGroundSymbolColor = 6374456
        Caption = 'Version'
        CornerRadius = 5
        Enabled = False
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWhite
        Font.Height = -13
        Font.Name = 'Segoe UI'
        Font.Style = [fsBold]
        ForeColor = 6374456
        GlowColor = 6374456
        InnerBorderColor = 6374456
        OuterBorderColor = 9135959
        ParentFont = False
        ParentShowHint = False
        ParentBiDiMode = False
        ShineColor = 6374456
        ShortCutHintPos = shpCenter
        ShowHint = False
        TabOrder = 0
        Version = '1.3.0.2'
      end
      object SoftwareVersionEdit: TAdvGlassButton
        Left = 115
        Top = 2
        Width = 170
        Height = 25
        Margins.Left = 5
        Margins.Right = 5
        ParentCustomHint = False
        AntiAlias = aaNone
        BackColor = clWhite
        CornerRadius = 5
        Enabled = False
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWhite
        Font.Height = -13
        Font.Name = 'Segoe UI'
        Font.Style = [fsBold]
        ForeColor = clWhite
        GlowColor = clWhite
        InnerBorderColor = 9135959
        OuterBorderColor = 9135959
        ParentFont = False
        ParentShowHint = False
        ParentBiDiMode = False
        ShineColor = clWhite
        ShortCutHintPos = shpCenter
        ShowHint = False
        TabOrder = 1
        Version = '1.3.0.2'
      end
    end
  end
  object Timer1: TTimer
    Enabled = False
    Interval = 15000
    OnTimer = Timer1Timer
    Left = 576
    Top = 288
  end
end
