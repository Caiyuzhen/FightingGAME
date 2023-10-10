// Fill out your copyright notice in the Description page of Project Settings.
#include "MainPlayerAnimInstance.h"
#include "Characters/Player/MainPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"


// 👇 在蓝图中的 ABP_MainPlayer 中来调用这些方法! => 前提是在 .h 文件中设置了 【BlueprintCallable】!!
// 自己创建的函数, 这个函数用来做一些初始化的操作
void UMainPlayerAnimInstance::NativeInitializeAnimation() {
	// return virtual void();
	PlayerRef = Cast<AMainPlayer>(TryGetPawnOwner()); // 【🔥 AMainPlayer 内的方法】, 可以得到【😧持有这个动画蓝图】的【😄角色】的【🔗引用】,🔥🔥🔥 Cast<AMainPlayer>(...) 表示将 ... 转化为 AMainPlayer 类型！！ ⚠️注意, 如果转化失败会变为 NULL 空指针！！ 会导致程序死循环！！所以下面要判断是否为空！！
}



// 自己创建的函数, 这个函数用来更新角色的动画属性
void UMainPlayerAnimInstance::UpdateAnimationProperties() {
	if(PlayerRef == nullptr) {
		PlayerRef = Cast<AMainPlayer>(TryGetPawnOwner()); //保护措施, 再度获取一遍
	}
	if(PlayerRef) {
		// 👇 获得角色的速度(包含在空中跳跃前进的速度, 用到了几何向量数学) => 然后在蓝图中进行调用！
		const FVector SpeedVectorObj = PlayerRef -> GetVelocity(); // 获取角色的速度向量对象
		const FVector PlanarSpeed = FVector(SpeedVectorObj.X, SpeedVectorObj.Y, 0.0f); // 获取角色的空间速度向量的长度
		Speed = PlanarSpeed.Size(); // 获得角色的向量大小, 也就是角色的速度
		
		// 👇 获得角色是否在空中的状态 => 然后在蓝图中进行调用！
		bIsInAir = PlayerRef -> GetMovementComponent() -> IsFalling();
	}
}
