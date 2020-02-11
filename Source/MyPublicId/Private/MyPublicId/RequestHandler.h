// Copyright MyPublicId, LLC. 2020

#pragma once

#include "CoreMinimal.h"
#include "Http.h"
#include "HttpManager.h"

class MYPUBLICID_API RequestHandler
{
private:
    static uint16 concurrentCalls;

public:
    static int GetPendingCalls();
    static FString buildQueryString(const TMap<FString, FString>& map);
    static TSharedRef<IHttpRequest> SendRequest(const FString& method, const FString& action, const TMap<FString, FString>& map);
    static bool DecodeRequest(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TSharedPtr<class FJsonObject>& OutResult);
};