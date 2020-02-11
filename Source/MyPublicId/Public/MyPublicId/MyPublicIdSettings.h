//

#pragma once

#include "UObject/Object.h"
#include "MyPublicIdSettings.generated.h"


UCLASS(config = Game)
class UMyPublicIdSettings : public UObject
{
	GENERATED_BODY()

public:
    UMyPublicIdSettings();

public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, config, Category = "MyPublicId")
		FString authorizationToken;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, config, Category = "MyPublicId")
		FString endpoint;
};
