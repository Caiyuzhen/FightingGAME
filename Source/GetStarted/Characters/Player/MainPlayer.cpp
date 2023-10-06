//.cpp 文件, 往下添加
#include "MainPlayer.h" 
#include "GameFramework/SpringArmComponent.h" //引入悬臂跟摄像机的头文件【2】
#include "Camera/CameraComponent.h" //引入悬臂跟摄像机的头文件【2】
#include "Components/CapsuleComponent.h" //引入胶囊体的头文件【3】
#include "Components/InputComponent.h" //引入轴事件的头文件【4】


AMainPlayer::AMainPlayer() { // 构造函数, 对组件进行初始化
	PrimaryActorTick.bCanEverTick = true;

	//实例化 SpringArm - 🏗 摄像机悬臂 
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm")); //根据 USpringArmComponent 类创建实例
	SpringArm -> SetupAttachment(GetRootComponent()); //将【悬臂】附着到【根组件】上
	SpringArm -> TargetArmLength = 400.f; // 修改悬臂长度
	SpringArm -> bUsePawnControlRotation = true; // 🌟让悬臂跟随 Pawn 的旋转, 以实现角色的上下看！

	//实例化 SpringArm - 📷 摄像机 
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera")); //根据 UCameraComponent 类创建实例
	FollowCamera -> SetupAttachment(SpringArm, USpringArmComponent::SocketName); ////将【摄像机】附着到【悬臂】上, SocketName 是 USpringArmComponent 的一个常量, 代表悬臂的末端
	FollowCamera -> bUsePawnControlRotation = false; // 🌟让摄像机不跟随 Pawn 的旋转, 避免角色的上下看时, 整个角色都会翻转面向地面 !!

	//获得【胶囊体】, 并设定初始值 - 绑定人物骨骼
	GetCapsuleComponent() -> SetCapsuleSize(35.0f, 100.0f); //设置胶囊体【半径】、【高度】 -> 因为是个指针, 所以要在上面【声明头文件】！！
}

void AMainPlayer::BeginPlay() {
	Super::BeginPlay();
}

void AMainPlayer::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}


// 👇 自动生成的函数, 在这里取来【绑定】输入的轴映射
void AMainPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent); // 检查输入是否有效, 记得引入 PlayerInputComponent 的 .h 头文件！

	// 👇前后移动用 AMainPlayer, 左右旋转用 Controller 的 Yaw, ⚠️ 但是 上下旋转 要让悬臂（SpringArm）进行 Pitch , 否则整个角色都会翻转面向地面 !!
	PlayerInputComponent -> BindAxis("MoveForward", this, &AMainPlayer::MoveForward); //【轴映射的名称 - 前后看 y 轴】、【绑定哪个类的轴映射(其实就是当前 AMainPlayer 这个类)】、【函数的指针(&用来取地址)】
	PlayerInputComponent -> BindAxis("MoveRight", this, &AMainPlayer::MoveRight); //【轴映射的名称 - 左右看 x 轴】、【绑定哪个类的轴映射(其实就是当前 AMainPlayer 这个类)】、【函数的指针(&用来取地址)】

	PlayerInputComponent -> BindAxis("Turn", this, &ACharacter::AddControllerYawInput); //【轴映射的名称 - 上下看 z 轴, Yaw Pitch】、【绑定哪个类的轴映射(其实就是当前 AMainPlayer 这个类)】、【函数的指针(&用来取地址, 🌟可以绑定父类的函数！=> &ACharacter::AddControllerYawInput )】
	PlayerInputComponent -> BindAxis("LookUp", this, &ACharacter::AddControllerPitchInput); //【轴映射的名称 - 上下看 z 轴, Yaw Pitch】、【绑定哪个类的轴映射(其实就是当前 AMainPlayer 这个类)】、【函数的指针(&用来取地址, 🌟可以绑定父类的函数！=> &ACharacter::AddControllerYawInput )】
}


// 🌟几个轴映射功能（前后左右移动）的【具体实现】
void AMainPlayer::MoveForward(float Value) {
	AddMovementInput(GetActorForwardVector(), Value); //注意, Pawn 类不能调用, Characters 类才能调用 !!  两个参数: 【向世界的哪个方向移动】 【移动的值（移动多远）】, GetActorForwardVector 表示向角色正面方向移动
}

void AMainPlayer::MoveRight(float Value) {
	AddMovementInput(GetActorRightVector(), Value);
}

