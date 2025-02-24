// LMGTestTask Huskov Illia


#include "Core/Character/LMGCharacter.h"



ALMGCharacter::ALMGCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

}


void ALMGCharacter::TraceForInteraction(FHitResult& HitResult)
{
	if (!GetWorld()) return;
	if (Controller == nullptr) return;
	FVector ViewLocation;
	FRotator ViewRotation;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(GetOwner());
	Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);
	const FVector ShootDirection = ViewRotation.Vector();
	FVector TraceEnd = ViewLocation + ShootDirection * TraceLength;
	GetWorld()->LineTraceSingleByChannel(HitResult, ViewLocation, TraceEnd, ECollisionChannel::ECC_Visibility, CollisionParams);
}

void ALMGCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FHitResult HitResult;
	TraceForInteraction(HitResult);
	if (HitResult.GetActor() && HitResult.GetComponent()->ComponentHasTag("Highlightable"))
	{
		auto CurrentOutlineMeshPtr = Cast<UPrimitiveComponent>(HitResult.GetComponent());
		if (!IsValid(CurrentOutlineMeshPtr)) return;
		//Turn on outline on component setup reference to it
		if (CurrentOutlineMeshPtr != LastOutlineMeshComponent)
		{
			CurrentOutlineMeshPtr->SetRenderCustomDepth(true);
			CurrentOutlineMeshPtr->CustomDepthStencilValue = CustomDepthStencilValue;
			if (LastOutlineMeshComponent != nullptr)
			{
				//Turn off the outline of the last known component
				LastOutlineMeshComponent->SetRenderCustomDepth(false);
			}
			LastOutlineMeshComponent = CurrentOutlineMeshPtr;
			UE_LOG(LogTemp, Display, TEXT("Trace actor is %s  highlight state active"), *HitResult.GetActor()->GetActorNameOrLabel());
		}
		return;
	}
	//Turn off the outline of the last known component
	else if (LastOutlineMeshComponent != nullptr)
	{
		LastOutlineMeshComponent->SetRenderCustomDepth(false);
			
		UE_LOG(LogTemp, Display, TEXT("End trace actor is %s  highlight state hide"), *LastOutlineMeshComponent->GetOwner()->GetActorNameOrLabel());
		LastOutlineMeshComponent = nullptr;
	}
}
