//Owner:Pierre-Olivier Chartrand
#pragma once
#include "GameFramework/Character.h"
#include "DarklightProjectCharacter.generated.h"

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
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override ;
	// End of APawn interface
	/**Tick event called by the blueprint */
	void Tick(float deltaTime);
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayerState")
		float Health;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerState")
		float MaxHealth;


public:
	ADarklightProjectCharacter();
	virtual void BeginPlay();
	/** Returns SideViewCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetSideViewCameraComponent() const { return SideViewCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Called for front to back input*/
	void MoveForward(float Val);
	/** Called for side to side input */
	void MoveRight(float Val);
	//The duration each position the player passes stay saved in the trail algorythm in seconds
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trail")
	float TrailLenght;
	//Is the player charged up and ready to produce a collision with another trail
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Trail")
	bool bChargedUp;

};
