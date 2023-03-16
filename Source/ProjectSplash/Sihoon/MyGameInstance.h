// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTSPLASH_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UMyGameInstance();

	virtual void Init() override;

	UFUNCTION(BlueprintCallable, meta = (KeyWords = "Sihoon"))
	void CloseSocket();

	void CreateThread();
	void DeleteThread();

	UPROPERTY(EditAnywhere, Category = "Widgets", BlueprintReadOnly)
	TSubclassOf<UUserWidget> ChattingBox;

	UFUNCTION(BlueprintCallable, meta = (KeyWords = "Sihoon"))
	void SetChattingBox(TSubclassOf<UUserWidget> ChattingWidget);

	UFUNCTION(BlueprintCallable, meta = (KeyWords = "Sihoon"))
	void LoadChatWidget();

	UFUNCTION(BlueprintCallable, meta = (KeyWords = "Sihoon"))
	void SendChatting(EnumMessage SelectMessage);

private:
	class FSocket* Socket;
	class SendChat* SendThread;
	class ReceiveChat* ReceiveThread;

	bool ConnectChatServer();
	bool bTryConnect;
};
