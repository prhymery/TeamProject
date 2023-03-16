// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

// 채팅 메세지 ENUM클래스
UENUM(BlueprintType)
enum class EnumMessage : uint8
{
	TE_Default UMETA(DisplayName = "Default"),
	TE_Provoke UMETA(DisplayName = "Provoke"),
	TE_Good UMETA(DisplayName = "Good"),
	TE_Bad UMETA(DisplayName = "Bad"),
};

/**
 *
 */
class PROJECTSPLASH_API SendChat : public FRunnable
{
public:
	SendChat();
	SendChat(class FSocket* ServerSocket);
	~SendChat();

	// 아래 3개의 함수는 따로 호출하지 않고 자동적으로 동작할 것이다.
	// 쓰레드를 할당할 함수
	bool Init() override;
	// 쓰레드를 활용해서 할 일을 넣을 함수
	uint32 Run() override;
	// 쓰레드가 언제 종료되어야 하는지 알 때 사용, Run()에서 호출한다.
	void Stop() override;

	FSocket* Socket;

	// 메세지 보낼 때 호출하면 된다
	void SendMessage(EnumMessage SelectMessage);
	
	void SetText(EnumMessage SelectMessage);

private:
	class FRunnableThread* Thread;
	bool bRunThread; // Run함수에서 활용할 변수
	bool bSendMessage;
	uint8 Buffer[1024]; // Send에 쓰이는 버퍼
	char* Text;
};
