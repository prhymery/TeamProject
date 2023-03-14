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
	void CreateThread();

	UFUNCTION(BlueprintCallable, meta = (KeyWords = "Sihoon"))
	void DeleteThread();

	class FSocket* Socket;
	class SendChat* SendThread;
	class ReceiveChat* ReceiveThread;

	bool ConnectChatServer();
	bool bTryConnect;

	UPROPERTY(EditAnywhere, Category = "Widgets", BlueprintReadOnly)
	TSubclassOf<UUserWidget> ChattingBox;

	UFUNCTION(BlueprintCallable, meta = (KeyWords = "Sihoon"))
	void SetChattingBox(TSubclassOf<UUserWidget> ChattingWidget);

	UFUNCTION(BlueprintCallable, meta = (KeyWords = "Sihoon"))
	void LoadChatWidget();
};
