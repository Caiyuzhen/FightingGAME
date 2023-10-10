// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MainPlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class GETSTARTED_API UMainPlayerAnimInstance : public UAnimInstance {
	GENERATED_BODY()


	// 👇这个 public 用来放置一些属性
	public:
		UPROPERTY(VisibleAnywhere, blueprintReadOnly, Category = "Animation Movement Properties") // 让这个属性在蓝图内可以看到 
		float Speed; // 判断角色的速度
	
		UPROPERTY(VisibleAnywhere, blueprintReadOnly, Category = "Animation Movement Properties") // 让这个属性在蓝图内可以看到 
		bool bIsInAir; // 判断角色是否跳起来停留在空中

		UPROPERTY(VisibleAnywhere, blueprintReadOnly, Category = "Animation Movement Properties") // 让这个属性在蓝图内可以看到 
		class AMainPlayer* PlayerRef; // 🔥用指针引用 AMainPlayer 类, 用来获得角色的奔跑、跳跃等参数！！
	

	// 👇这个 public 用来放置一些函数
	public:
		virtual void NativeInitializeAnimation() override; // 👈 这个函数用来初始化动画, 在动画初始化时被调用, virtual 表示这个函数可以被重写, 这里我们自己重写这个函数!!

		UFUNCTION(BlueprintCallable, Category = "Animation Movement Function")// 👈 【BlueprintCallable】用来在蓝图内可调用!! 🔥这里是 UFUNCTION !!! 而不是  UPROPERTY !!!
		void UpdateAnimationProperties(); // 这个函数用来更新上面的动画属性
};
