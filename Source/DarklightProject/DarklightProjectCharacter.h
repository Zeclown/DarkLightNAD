//Owner:Pierre-Olivier Chartrand
#pragma once
#include "GameFramework/Character.h"
#include "DarklightProjectCharacter.generated.h"

DECLARE_EVENT(DarklightProjectCharacter, FPlayerDeath);

UCLASS(config=Game)
class ADarklightProjectCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Side view camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* SideViewCameraComponent;

	/** Camera boom positioning the camera beside the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;
protected:

	static FPlayerDeath PlayerDeathEvent;
	static float GlobalHealth;
	static float GlobalMaxHealth;
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="Character Movement: Walking")
	bool bSprinting;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Character Movement: Walking")
	float SprintModifier;
	/* Object Creation Delegate Event */


public:
	ADarklightProjectCharacter();
	virtual void BeginPlay();

	FPlayerDeath& OnDeath() { return PlayerDeathEvent; }

	/** Returns SideViewCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetSideViewCameraComponent() const { return SideViewCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	//The duration each position the player passes stay saved in the trail algorythm in seconds
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trail")
	float TrailLenght;
	//Is the player charged up and ready to produce a collision with another trail
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Trail")
	bool bChargedUp;
	UFUNCTION(BlueprintCallable, Category = "Player State")
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser) override;
	UFUNCTION(BlueprintCallable, Category = "Player State")
	static float GetHealth();
	UFUNCTION(BlueprintCallable,Category="Player State")
	static void SetHealth(float HealthPoints);
	UFUNCTION(BlueprintCallable, Category = "Player State")
	static float GetMaxHealth();
	UFUNCTION(BlueprintCallable, Category = "Player State")
	static void SetMaxHealth(float HealthPoints);

};
