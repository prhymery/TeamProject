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

	// 채팅서버 연결
	while (!bTryConnect)
	{
		UE_LOG(LogTemp, Warning, TEXT("Try Connect Chat Server"));
		bTryConnect = ConnectChatServer();
	}

}

void UMyGameInstance::CreateThread()
{
	if (ChattingBox != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Chat Widget Class %s"), *ChattingBox->GetName());
	}

	// SendChat Thread
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

// ReceiveThread는 delete하면 에디터가 멈춘다. 왜?
void UMyGameInstance::DeleteThread()
{
	if (SendThread != nullptr)
	{
		SendThread->Stop();
		delete SendThread;
		SendThread = nullptr;
	}

	if (ReceiveThread != nullptr)
	{
		ReceiveThread->Stop();
		//delete ReceiveThread;
		//ReceiveThread = nullptr;
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

