//.h 文件, 往上添加
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainPlayer.generated.h"

UCLASS()
class GETSTARTED_API AMainPlayer : public ACharacter {
	GENERATED_BODY()


public:
	AMainPlayer();

	// 🏗 摄像机悬臂 - 组件, 所以使用指针 - 【1】
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)//加入反射系统, 组件一般都使用 VisiableAnywhere
	class USpringArmComponent* SpringArm; // 定义类

	// 📷 摄像机 - 组件, 所以使用指针 - 【1】
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)//加入反射系统, 组件一般都使用 VisiableAnywhere
	class UCameraComponent* FollowCamera; // 定义类


protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
