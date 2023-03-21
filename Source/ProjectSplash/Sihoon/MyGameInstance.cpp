// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "Blueprint/UserWidget.h"

// 소켓 통신을 위한 헤더
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "Interfaces/IPv4/IPv4Address.h"

// 멀티쓰레드용으로 만든 것
#include "SendChat.h"
#include "ReceiveChat.h"

UMyGameInstance::UMyGameInstance()
{
	ChattingBox = nullptr;
}

void UMyGameInstance::Init()
{
	Super::Init();

	bTryConnect = false;
	SendThread = nullptr;
	ReceiveThread = nullptr;

	int32 count = 0;
	// 채팅서버 연결
	while (!bTryConnect)
	{
		// 채팅 서버 연결 0번 시도
		if (++count >= 0)
		{
			break;
		}

		UE_LOG(LogTemp, Warning, TEXT("Try Connect Chat Server"));
		bTryConnect = ConnectChatServer();
	}

	// 채팅서버에 연결됐으면 통신용 쓰레드 생성
	if (bTryConnect)
	{
		UE_LOG(LogTemp, Warning, TEXT("Create Thread"));
		CreateThread();
	}
}

bool UMyGameInstance::CloseSocket()
{
	DeleteThread();

	bool CloseResult = false;

	_sleep(1000);

	if (Socket != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Close Socket"));
		CloseResult = Socket->Close();
		Socket = nullptr;
	}

	return CloseResult;
}

void UMyGameInstance::CreateThread()
{
	if (ChattingBox != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Chat Widget Class %s"), *ChattingBox->GetName());
	}

	// SendChatThread
	if (SendThread == nullptr)
	{
		SendThread = new SendChat(Socket);
	}

	// ReceiveChatThread
	if (ReceiveThread == nullptr)
	{
		ReceiveThread = new ReceiveChat(Socket);
	}
	
}

void UMyGameInstance::DeleteThread()
{
	// FRunnable API를 이용한 쓰레드는 run함수가 끝나면 알아서 사라진다
	if (SendThread != nullptr)
	{
		SendThread->Stop();
		SendThread = nullptr;
	}
	if (ReceiveThread != nullptr)
	{
		ReceiveThread->Stop();
		ReceiveThread = nullptr;
	}
}

bool UMyGameInstance::ConnectChatServer()
{
	// 소켓을 생성
	Socket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(TEXT("Stream"), TEXT("Client Socket"));

	// IP를 FString으로 입력받아 저장
	FString Address = TEXT("127.0.0.1");
	FIPv4Address IP;
	FIPv4Address::Parse(Address, IP);

	int32 Port = 8000;

	// 포트와 소켓을 담는 클래스
	TSharedRef<FInternetAddr> Addr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	Addr->SetIp(IP.Value);
	Addr->SetPort(Port);

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Trying to connect.")));
	}

	// 연결 시도. 결과를 받아옴
	bool bIsConnetcted = Socket->Connect(*Addr);

	return bIsConnetcted;
}

void UMyGameInstance::SetChattingBox(TSubclassOf<UUserWidget> ChattingWidget)
{
	ChattingBox = ChattingWidget;
}

void UMyGameInstance::LoadChatWidget()
{
	if (ChattingBox != nullptr)
	{
		UUserWidget* ChatWidget = CreateWidget<UUserWidget>(this, ChattingBox);

		ChatWidget->AddToViewport();
	}
}

void UMyGameInstance::SendChatting(EnumMessage SelectMessage)
{
	if (SendThread != nullptr)
	{
		SendThread->SendMessage(SelectMessage);
	}
}
