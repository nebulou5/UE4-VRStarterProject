#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStaticsTypes.h"
#include "VRCharacter.generated.h"

class UCameraComponent;
class USceneComponent;
class UStaticMeshComponent;
class USplineComponent;
class USplineMeshComponent;
class UMotionControllerComponent;
class UMaterialInterface;

UENUM(BlueprintType)
enum class ESide : uint8 {
  Left  UMETA(DisplayName = "Left"),
  Right UMETA(DisplayName = "Right")
};

UCLASS()
class VRPROJ_API AVRCharacter : public ACharacter {
 
  GENERATED_BODY()

  public:
    AVRCharacter();
    virtual void Tick(float DeltaTime) override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

  protected:
    virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    UCameraComponent* CameraComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    USceneComponent* SceneComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    UStaticMeshComponent* TeleportMarker;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    USplineComponent* TeleportSplinePath;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    TArray<USplineMeshComponent*> TeleportArcMeshComponents;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    UStaticMesh* TeleportArcMesh;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    UMaterialInterface* TeleportArcMaterial;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    UMotionControllerComponent* LeftMotionController;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    UMotionControllerComponent* RightMotionController;

  private:
    bool bIsTeleporting = false;
    float TeleportFadeDuration = 2.5;
    float TeleportTraceRadius = 10.f;
    FVector TeleportTo;
    TMap<ESide, EInputEvent> ThumbstickPressState;

    void MoveForward(float Throttle);
    void TurnRight(float Throttle);
    void StrafeRight(float Throttle);
    void SyncCamera();
    void Teleport();
    void TeleportTrace(const ESide* Side);
    void TeleportOrTrace();
    void TeleportFade(float AlphaStart, float AlphaStop);
    void UpdateTeleportSpline(TArray<FPredictProjectilePathPointData> PathData, UMotionControllerComponent* MotionController);
    void HideTeleportSplines();
    void ResetTeleportMarker();
    void ReleaseTeleportButtons();

    template<EInputEvent InputEvent, ESide Side>
    void OnThumbstickPress();
};
