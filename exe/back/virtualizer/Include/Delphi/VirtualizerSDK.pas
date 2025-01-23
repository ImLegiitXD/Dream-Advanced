unit VirtualizerSDK;

{$ALIGN ON}
{$MINENUMSIZE 4}

interface

uses
  Windows;

procedure VirtualizerStart();stdcall;
procedure VirtualizerEnd();stdcall;

procedure VIRTUALIZER_START();stdcall;
procedure VIRTUALIZER_END();stdcall;

procedure VIRTUALIZER_STR_ENCRYPT_START();stdcall;
procedure VIRTUALIZER_STR_ENCRYPT_END();stdcall;
procedure VIRTUALIZER_STR_ENCRYPTW_START();stdcall;
procedure VIRTUALIZER_STR_ENCRYPTW_END();stdcall;

{$I VirtualizerSDK_CustomVMsInterface.pas}


implementation

const

{$IFDEF WIN64}
  Virtualizer = 'VirtualizerSDK64.DLL';
{$ELSE}
  Virtualizer = 'VirtualizerSDK32.DLL';
{$ENDIF}

procedure VirtualizerStart; external Virtualizer name 'VirtualizerStart';
procedure VirtualizerEnd; external Virtualizer name 'VirtualizerEnd';
procedure VIRTUALIZER_START; external Virtualizer name 'VirtualizerStart';
procedure VIRTUALIZER_END; external Virtualizer name 'VirtualizerEnd';
    
procedure VIRTUALIZER_STR_ENCRYPT_START; external Virtualizer name 'VirtualizerStrEncryptStart';
procedure VIRTUALIZER_STR_ENCRYPT_END; external Virtualizer name 'VirtualizerStrEncryptEnd';
procedure VIRTUALIZER_STR_ENCRYPTW_START; external Virtualizer name 'VirtualizerStrEncryptWStart';
procedure VIRTUALIZER_STR_ENCRYPTW_END; external Virtualizer name 'VirtualizerStrEncryptWEnd';

{$I VirtualizerSDK_CustomVMsImplementation.pas}

end.

