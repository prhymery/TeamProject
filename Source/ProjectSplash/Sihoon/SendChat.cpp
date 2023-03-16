// Fill out your copyright notice in the Description page of Project Settings.


#include "SendChat.h"
#include "Sockets.h"


SendChat::SendChat()
{
}

SendChat::SendChat(FSocket* ServerSocket)
{
	Socket = ServerSocket;
	Thread = FRunnableThread::Create(this, TEXT("SendChatThread"));
}

SendChat::~SendChat()
{
	if (Thread)
	{
		// 실질적으로 쓰레드의 활동을 멈추고 쓰레드를 지우는 곳이다.
		UE_LOG(LogTemp, Warning, TEXT("Delete Send Thread"));
		Thread->WaitForCompletion();
		Thread->Kill(); // Kill()이 Stop() 호출하네
		delete Thread;
	}
}

bool SendChat::Init()
{
	bRunThread = true;
	bSendMessage = false;

	return true;
}

uint32 SendChat::Run()
{

	UE_LOG(LogTemp, Warning, TEXT("Run Send Thread"));

	while (bRunThread)
	{
		int32 BytesSent = 0;

		if (bSendMessage)
		{
			Socket->Send(Buffer, sizeof(Buffer), BytesSent);
			bSendMessage = false;
		}

	}

	return 0;
}

void SendChat::Stop()
{
	UE_LOG(LogTemp, Warning, TEXT("Stop Send Thread"));

	bRunThread = false;
}

void SendChat::SendMessage(EnumMessage SelectMessage)
{
	SetText(SelectMessage);
	bSendMessage = true;

	// 버퍼 리셋
	for (int i = 0; i < sizeof(Buffer); i++)
	{
		// Buffer[i] = 0;은 왜 안 되는걸까?
		char Temp = 0;
		Buffer[i] = Temp;
	}

	for (int i = 0; i < strlen(Text) + 1; i++)
	{
		Buffer[i] = *(Text + i);
	}
}

void SendChat::SetText(EnumMessage SelectMessage)
{
	switch (SelectMessage)
	{
	case EnumMessage::TE_Default:
		Text = "Hello!";
		break;
	case EnumMessage::TE_Provoke:
		Text = "So easy~";
		break;
	case EnumMessage::TE_Good:
		Text = "Good job!";
		break;
	case EnumMessage::TE_Bad:
		Text = "It's too bad.";
		break;
	default:
		break;
	}
}

