// Cop// Copyright MyPublicId, LLC. 2020

#include "MyPublicId.h"
#include "RequestHandler.h"
#include "Dom/JsonObject.h"
#include "MyPublicIdSettings.h"
#include "UObject/UObjectGlobals.h"

UMyPublicId::UMyPublicId()
{
}

bool UMyPublicId::Authorize(FString tokenName, FString token, FMyPublicId_Authorize SuccessDelegate, FMyPublicId_Error ErrorDelegate)
{
	UMyPublicId* inst = NewObject<UMyPublicId>();
	if (inst->IsSafeForRootSet()) inst->AddToRoot();

	UMyPublicIdSettings* Settings = GetMutableDefault<UMyPublicIdSettings>();
    TMap<FString, FString> map;
    map.Add("token_name", tokenName);
    map.Add("token", token);

    auto HttpRequest = RequestHandler::SendRequest("POST", "/game/authorize", map);
    HttpRequest->OnProcessRequestComplete().BindUObject(inst, &UMyPublicId::OnAuthorize, SuccessDelegate, ErrorDelegate);
    return HttpRequest->ProcessRequest();
}

void UMyPublicId::OnAuthorize(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FMyPublicId_Authorize SuccessDelegate, FMyPublicId_Error ErrorDelegate)
{
	TSharedPtr<class FJsonObject> OutResult;
	if (RequestHandler::DecodeRequest(HttpRequest, HttpResponse, bSucceeded, OutResult))
	{
		SuccessDelegate.ExecuteIfBound(OutResult->GetBoolField("active"), OutResult->GetIntegerField("country"));
	}
	else if (OutResult->HasField("code"))
	{
		ErrorDelegate.ExecuteIfBound(OutResult->GetNumberField("code"), OutResult->GetStringField("message"));
	}
	else
	{
		ErrorDelegate.ExecuteIfBound(1000, "Unknown error occurred!");
	}
}

bool UMyPublicId::Ban(FString tokenName, FString token, FMyPublicId_Ban SuccessDelegate, FMyPublicId_Error ErrorDelegate)
{
	UMyPublicId* inst = NewObject<UMyPublicId>();
	if (inst->IsSafeForRootSet()) inst->AddToRoot();

	UMyPublicIdSettings* Settings = GetMutableDefault<UMyPublicIdSettings>();
	TMap<FString, FString> map;
	map.Add("token_name", tokenName);
	map.Add("token", token);

	auto HttpRequest = RequestHandler::SendRequest("PUT", "/game/ban", map);
	HttpRequest->OnProcessRequestComplete().BindUObject(inst, &UMyPublicId::OnBan, SuccessDelegate, ErrorDelegate);
	return HttpRequest->ProcessRequest();
}

void UMyPublicId::OnBan(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FMyPublicId_Ban SuccessDelegate, FMyPublicId_Error ErrorDelegate)
{
	TSharedPtr<class FJsonObject> OutResult;
	if (RequestHandler::DecodeRequest(HttpRequest, HttpResponse, bSucceeded, OutResult))
	{
		SuccessDelegate.ExecuteIfBound();
	}
	else if (OutResult->HasField("code"))
	{
		ErrorDelegate.ExecuteIfBound(OutResult->GetNumberField("code"), OutResult->GetStringField("message"));
	}
	else
	{
		ErrorDelegate.ExecuteIfBound(1000, "Unknown error occurred!");
	}
}

bool UMyPublicId::UnBan(FString tokenName, FString token, FMyPublicId_UnBan SuccessDelegate, FMyPublicId_Error ErrorDelegate)
{
	UMyPublicId* inst = NewObject<UMyPublicId>();
	if (inst->IsSafeForRootSet()) inst->AddToRoot();

	UMyPublicIdSettings* Settings = GetMutableDefault<UMyPublicIdSettings>();
	TMap<FString, FString> map;
	map.Add("token_name", tokenName);
	map.Add("token", token);

	auto HttpRequest = RequestHandler::SendRequest("DELETE", "/game/ban", map);
	HttpRequest->OnProcessRequestComplete().BindUObject(inst, &UMyPublicId::OnUnBan, SuccessDelegate, ErrorDelegate);
	return HttpRequest->ProcessRequest();
}

void UMyPublicId::OnUnBan(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FMyPublicId_UnBan SuccessDelegate, FMyPublicId_Error ErrorDelegate)
{
	TSharedPtr<class FJsonObject> OutResult;
	if (RequestHandler::DecodeRequest(HttpRequest, HttpResponse, bSucceeded, OutResult))
	{
		SuccessDelegate.ExecuteIfBound();
	}
	else if (OutResult->HasField("code"))
	{
		ErrorDelegate.ExecuteIfBound(OutResult->GetNumberField("code"), OutResult->GetStringField("message"));
	}
	else
	{
		ErrorDelegate.ExecuteIfBound(1000, "Unknown error occurred!");
	}
}
