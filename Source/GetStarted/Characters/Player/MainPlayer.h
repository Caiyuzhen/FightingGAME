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


		// 键盘玩家的转向变量
		float BaseTurnRate; // 🔥基础转向率 - 因为键盘每次按下只有 1 或 -1， 所以要乘以一个比较大的值, 不然会旋转得很小
		float BaseLookUpRate; // 🔥基础上下看率 - 因为键盘每次按下只有 1 或 -1， 所以要乘以一个比较大的值, 不然会旋转得很小



	protected:
		virtual void BeginPlay() override;



	// 第二个 public 一般声明一些函数
	public:	
		virtual void Tick(float DeltaTime) override;

		virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

		// 🌟 声明前后左右的轴映射
		void MoveForward(float Value);
		void MoveRight(float Value);

		// 🌟 声明鼠标转向 + 键盘转向的方法
		void Turn(float Value);
		void LookUp(float Value);
		void TurnAtRate(float Rate); // 键盘上下左右旋转事件, 所以 Rate 不是 0 就是 1 就是 -1, 所以要乘以一个比较大的值, 不然会旋转得很小
		void LookUpAtRate(float Rate); // 键盘上下左右旋转事件, 所以 Rate 不是 0 就是 1 就是 -1, 所以要乘以一个比较大的值, 不然会旋转得很小
};
