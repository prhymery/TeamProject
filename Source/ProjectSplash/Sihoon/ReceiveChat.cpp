// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "ReceiveChat.h"
#include "Sockets.h"

ReceiveChat::ReceiveChat()
{
}

ReceiveChat::ReceiveChat(FSocket* ServerSocket)
{
	Socket = ServerSocket;
	Thread = FRunnableThread::Create(this, TEXT("ReceiveChatThread"));
}

ReceiveChat::~ReceiveChat()
{
	if (Thread)
	{
		// 실질적으로 쓰레드의 활동을 멈추고 쓰레드를 지우는 곳이다.
		UE_LOG(LogTemp, Warning, TEXT("Delete Receive Thread"));
		Thread->WaitForCompletion();
		Thread->Kill(); // Kill()이 Stop() 호출하네
		delete Thread;
	}
}

bool ReceiveChat::Init()
{
	bRunThread = true;
	return true;
}

uint32 ReceiveChat::Run()
{

	UE_LOG(LogTemp, Warning, TEXT("Run Receive Thread"));

	while (bRunThread)
	{
		uint8 Buffer[1024] = { 0, };
		int32 BytesRecv = 0;
		Socket->Recv(Buffer, sizeof(Buffer), BytesRecv);

		FUTF8ToTCHAR WideBuffer(reinterpret_cast<const ANSICHAR*>(Buffer));

		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("%s"), WideBuffer.Get()));
		}
	}

	return 0;
}

void ReceiveChat::Stop()
{
	UE_LOG(LogTemp, Warning, TEXT("Stop Receive Thread"));

	bRunThread = false;
}
