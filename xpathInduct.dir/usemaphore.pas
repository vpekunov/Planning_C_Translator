unit uSemaphore;

{$mode objfpc}{$H+}

interface

uses
  Classes, SysUtils, syncobjs, contnrs;

type

  { TSemaphore }

  TSemaphore = class
  private
    FEvent: PRTLEvent;
    FCount: Integer;
  public
    constructor Create(ACount: Integer);
    destructor Destroy;
    procedure Wait;
    function  AttemptWait: Boolean;
    procedure Post;
    property Count: Integer read FCount;
  end;


implementation

{ TSemaphore }

constructor TSemaphore.Create(ACount: Integer);
begin
  FCount:= ACount;
  FEvent:= RTLEventCreate;
end;

destructor TSemaphore.Destroy;
begin
  RTLeventdestroy(FEvent);
  inherited Destroy;
end;

procedure TSemaphore.Wait;
begin
  if InterLockedDecrement(FCount) < 0 then
    RTLeventWaitFor(FEvent);
end;

function TSemaphore.AttemptWait: Boolean;
begin
  Result := InterLockedDecrement(FCount) >= 0;
  If Not Result Then
     Post;
end;

procedure TSemaphore.Post;
begin
  if InterLockedIncrement(FCount) <= 0 then
    RTLeventSetEvent(FEvent);
end;

end.

