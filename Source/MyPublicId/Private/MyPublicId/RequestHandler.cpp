// Copyright MyPublicId, LLC. 2019

#include "RequestHandler.h"
#include "MyPublicIdSettings.h"
#include "UObject/UObjectGlobals.h"
#include "Serialization/JsonSerializer.h"
#include "Misc/CommandLine.h"

uint16 RequestHandler::concurrentCalls = 0;

int RequestHandler::GetPendingCalls()
{
    return RequestHandler::concurrentCalls;
}

FString RequestHandler::buildQueryString(const TMap<FString, FString>& map)
{
	bool isFirst = true;
	FString queryString = "";
	for (auto elem : map) {
		if (!isFirst)
			queryString += "&";
		else
			isFirst = false;
		queryString += elem.Key + "=" + elem.Value;
	}
	return queryString;
}

TSharedRef<IHttpRequest> RequestHandler::SendRequest(const FString& method, const FString& action, const TMap<FString, FString>& map)
{
    UMyPublicIdSettings* Settings = GetMutableDefault<UMyPublicIdSettings>();
    RequestHandler::concurrentCalls += 1;

    TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
    HttpRequest->SetVerb(method);
    HttpRequest->SetURL(Settings->endpoint + action);
    HttpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/x-www-form-urlencoded; charset=utf-8"));
	FString authorizationToken;
	if (!FParse::Value(FCommandLine::Get(), TEXT("mypublicid"), authorizationToken))
		authorizationToken = Settings->authorizationToken;
    HttpRequest->SetHeader("Authorization", authorizationToken);

    HttpRequest->SetContentAsString(RequestHandler::buildQueryString(map));
    return HttpRequest;
}

bool RequestHandler::DecodeRequest(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TSharedPtr<class FJsonObject>& OutResult)
{
    RequestHandler::concurrentCalls -= 1;

    FString ResponseStr, ErrorStr;
    if (bSucceeded && HttpResponse.IsValid())
    {
        if (EHttpResponseCodes::IsOk(HttpResponse->GetResponseCode()))
        {
            // Create the Json parser
            ResponseStr = HttpResponse->GetContentAsString();
            TSharedPtr<FJsonObject> JsonObject;
            TSharedRef<TJsonReader<> > JsonReader = TJsonReaderFactory<>::Create(ResponseStr);

            if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
            {
                OutResult = JsonObject;
                return true;
            }
        }
        else
        {
            // Create the Json parser
            ResponseStr = HttpResponse->GetContentAsString();
            TSharedPtr<FJsonObject> JsonObject;
            TSharedRef<TJsonReader<> > JsonReader = TJsonReaderFactory<>::Create(ResponseStr);

            if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
            {
                OutResult = JsonObject;
                return false;
            }
        }
    }

	// TODO: Put error details in OutResult

    return false;
}