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
	return true;
}

uint32 SendChat::Run()
{

	UE_LOG(LogTemp, Warning, TEXT("Run Send Thread"));

	while (bRunThread)
	{
		uint8 Buffer[1024] = "Hello World! 1234";
		int32 BytesSent = 0;
		Socket->Send(Buffer, sizeof(Buffer), BytesSent);

		_sleep(1000);
	}

	return 0;
}

void SendChat::Stop()
{
	UE_LOG(LogTemp, Warning, TEXT("Stop Send Thread"));

	bRunThread = false;
}

