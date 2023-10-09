// Fill out your copyright notice in the Description page of Project Settings.
#include "MainPlayerAnimInstance.h"


// 👇 在蓝图中的 ABP_MainPlayer 中来调用这些方法! => 前提是在 .h 文件中设置了 【BlueprintCallable】!!
// 自己创建的函数, 这个函数用来做一些初始化的操作
virtal void UMainPlayerAnimInstance::NativeInitializeAnimation() {
	// return virtal void();
	PlayerRef = TryGetPawnOwner(); // AMainPlayer 内的方法, 可以得到【😧持有这个动画蓝图】的【😄角色】的【🔗引用】
}

// 自己创建的函数, 这个函数用来更新角色的动画属性
void UMainPlayerAnimInstance::UpdateAnimationProperties() {
	// ...
}
