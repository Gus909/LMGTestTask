// LMGTestTask Huskov Illia

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LMGCharacter.generated.h"


UCLASS()
class LMGTESTTASK_API ALMGCharacter : public ACharacter
{
	GENERATED_BODY()

private:

	UPROPERTY(EditDefaultsOnly, meta = (ClampMin = 0.f, ClampMax = 1500.f), Category = "LMG|Trace")
	float TraceLength = 500.f;

	UPROPERTY(EditDefaultsOnly, meta = (ClampMin = 0.f, ClampMax = 100.f), Category = "LMG|Outline")
	float CustomDepthStencilValue = 1.f;

	TObjectPtr<UPrimitiveComponent> LastOutlineMeshComponent;

public:

	ALMGCharacter();

	virtual void Tick(float DeltaTime) override;

private:
	void TraceForInteraction(FHitResult& HitResult);

};
