// Copyright MyPublicId, LLC. 2020

#pragma once

#include "CoreMinimal.h"
#include "Http.h"
#include "UObject/Object.h"
#include "MyPublicId.generated.h"

UCLASS(Blueprintable, BlueprintType)
class MYPUBLICID_API UMyPublicId : public UObject
{
	GENERATED_BODY()

public:
	UMyPublicId();

	DECLARE_DYNAMIC_DELEGATE_TwoParams(FMyPublicId_Error, const int32, ErrorCode, const FString, ErrorMessage);

	// Methods

	// Authorize
	DECLARE_DYNAMIC_DELEGATE_TwoParams(FMyPublicId_Authorize, const bool, UserActive, const int32, CountryId);

	UFUNCTION(BlueprintCallable, Category = "MyPublicId")
		static bool Authorize(FString tokenName, FString token, FMyPublicId_Authorize SuccessDelegate, FMyPublicId_Error ErrorDelegate);
	void OnAuthorize(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FMyPublicId_Authorize SuccessDelegate, FMyPublicId_Error ErrorDelegate);

	// Ban
	DECLARE_DYNAMIC_DELEGATE(FMyPublicId_Ban);

	UFUNCTION(BlueprintCallable, Category = "MyPublicId")
		static bool Ban(FString tokenName, FString token, FMyPublicId_Ban SuccessDelegate, FMyPublicId_Error ErrorDelegate);
	void OnBan(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FMyPublicId_Ban SuccessDelegate, FMyPublicId_Error ErrorDelegate);

	// Unban
	DECLARE_DYNAMIC_DELEGATE(FMyPublicId_UnBan);

	UFUNCTION(BlueprintCallable, Category = "MyPublicId")
		static bool UnBan(FString tokenName, FString token, FMyPublicId_UnBan SuccessDelegate, FMyPublicId_Error ErrorDelegate);
	void OnUnBan(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FMyPublicId_UnBan SuccessDelegate, FMyPublicId_Error ErrorDelegate);
};