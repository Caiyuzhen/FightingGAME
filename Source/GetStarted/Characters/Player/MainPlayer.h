//.h 文件, 往上添加
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainPlayer.generated.h"

UCLASS()
class GETSTARTED_API AMainPlayer : public ACharacter {
	GENERATED_BODY()


	// 第一个 public 一般声明一些组件、生命值、速度等
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


	// 第二个 public 一般声明一些函数
	public:	
		virtual void Tick(float DeltaTime) override;

		virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

		// 🌟 前后左右的轴映射
		void MoveForward(float Value);
		void MoveRight(float Value);
};
