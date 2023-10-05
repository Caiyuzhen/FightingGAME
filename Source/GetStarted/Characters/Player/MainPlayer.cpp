//.cpp 文件, 往下添加
#include "MainPlayer.h" 
#include "GameFramework/SpringArmComponent.h" //引入悬臂跟摄像机的头文件【2】
#include "Camera/CameraComponent.h" //引入悬臂跟摄像机的头文件【2】


AMainPlayer::AMainPlayer() { // 构造函数, 对组件进行初始化
	PrimaryActorTick.bCanEverTick = true;

	//实例化 SpringArm - 🏗 摄像机悬臂 
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm")); //根据 USpringArmComponent 类创建实例
	//将悬臂附着到【根组件】上
	Spring -> SetupAttachment(GetRootComponent());

	//实例化 SpringArm - 🏗 摄像机悬臂 
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera")); //根据 UCameraComponent 类创建实例
	//将悬臂附着到【根组件】上
	Spring -> SetupAttachment(GetRootComponent());
}

void AMainPlayer::BeginPlay() {
	Super::BeginPlay();
}

void AMainPlayer::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

void AMainPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

