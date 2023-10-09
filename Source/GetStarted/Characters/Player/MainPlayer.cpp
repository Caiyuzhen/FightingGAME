//.cpp 文件, 往下添加
#include "MainPlayer.h" 
#include "GameFramework/SpringArmComponent.h" //引入悬臂跟摄像机的头文件【2】
#include "Camera/CameraComponent.h" //引入悬臂跟摄像机的头文件【2】
#include "Components/CapsuleComponent.h" //引入胶囊体的头文件【3】
#include "Components/InputComponent.h" //引入轴事件的头文件【4】
#include "GameFramework/PlayerController.h" //引入 Controller 的头文件【5】
#include "GameFramework/CharacterMovementComponent.h" //引入 Character 的头文件【6】


// 构造函数, 对组件进行初始化 ————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
AMainPlayer::AMainPlayer() { 
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

void AMainPlayer::Tick(float DeltaTime) { // DeltaTime 是时间间隔, 用来平衡不同设备的帧率
	Super::Tick(DeltaTime);
}



// 👇 自动生成的函数, 在这里取来【绑定】输入的轴映射 (第一步, 绑定轴映射) ————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
void AMainPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent); // 检查输入是否有效, 记得引入 PlayerInputComponent 的 .h 头文件！

	// 👇 【动作事件】
	PlayerInputComponent -> BindAction("Jump", IE_Pressed, this, &AMainPlayer::Jump); // IE_Pressed 表示绑定按下按键的事件, Jump 方法为内置好的方法
	PlayerInputComponent -> BindAction("Jump", IE_Released, this, &ACharacter::StopJumping); // IE_Released 表示绑定松开按键的事件, StopJumping 方法为内置好的方法


	// 👇【轴事件, 会不断的调用】前后移动用 AMainPlayer, 左右旋转用 Controller 的 Yaw, ⚠️ 但是 上下旋转 要让悬臂（SpringArm）进行 Pitch , 否则整个角色都会翻转面向地面 !!
	PlayerInputComponent -> BindAxis("MoveForward", this, &AMainPlayer::MoveForward); //MoveForward 为下方声明的函数！【轴映射的名称 - 前后看 y 轴】、【绑定哪个类的轴映射(其实就是当前 AMainPlayer 这个类)】、【函数的指针(&用来取地址)】
	PlayerInputComponent -> BindAxis("MoveRight", this, &AMainPlayer::MoveRight); //MoveRight 为下方声明的函数！【轴映射的名称 - 左右看 x 轴】、【绑定哪个类的轴映射(其实就是当前 AMainPlayer 这个类)】、【函数的指针(&用来取地址)】

	// 【自己定义鼠标跟键盘转向事件后, 这么写, 👉表示用 &取地址, 引用 AMainPlayer 类中的 Turn 方法！👈】
	PlayerInputComponent -> BindAxis("Turn", this, &AMainPlayer::Turn); //【轴映射的名称 - 左右看 z 轴, Yaw Pitch】、【绑定哪个类的轴映射(其实就是当前 AMainPlayer 这个类)】、【函数的指针(&用来取地址)】
	PlayerInputComponent -> BindAxis("LookUp", this, &AMainPlayer::LookUp); //【轴映射的名称 - 上下看 z 轴, Yaw Pitch】、【绑定哪个类的轴映射(其实就是当前 AMainPlayer 这个类)】、【函数的指针(&用来取地址)】
	PlayerInputComponent -> BindAxis("TurnAtRate", this, &AMainPlayer::TurnAtRate); 
	PlayerInputComponent -> BindAxis("LookUpAtRate", this, &AMainPlayer::LookUpAtRate); 

	// 【还没自己定义鼠标跟键盘转向事件时, 这么写】
	// PlayerInputComponent -> BindAxis("Turn", this, &ACharacter::AddControllerYawInput); //【轴映射的名称 - 左右看 z 轴, Yaw Pitch】、【绑定哪个类的轴映射(其实就是当前 AMainPlayer 这个类)】、【函数的指针(&用来取地址, 🌟可以绑定父类的函数！=> &ACharacter::AddControllerYawInput )】
	// PlayerInputComponent -> BindAxis("LookUp", this, &ACharacter::AddControllerPitchInput); //【轴映射的名称 - 上下看 z 轴, Yaw Pitch】、【绑定哪个类的轴映射(其实就是当前 AMainPlayer 这个类)】、【函数的指针(&用来取地址, 🌟可以绑定父类的函数！=> &ACharacter::AddControllerYawInput )】

	// 【摄像机能够旋转到角色前方】 , 更改 mainPlayer 的 Pawn, 用来让可以转到角色面前
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetCharacterMovement() -> bOrientRotationToMovement = true; //🌟让角色朝着移动的方向旋转 【UE 内置的方法, 可以在蓝图里边的（奔跑角色移动）看到 】
	GetCharacterMovement() -> RotationRate = FRotator(0.0f, 540.0f, 0.0f); //🌟设置角色的旋转速率 【UE 内置的方法, 可以在蓝图里边的（奔跑角色移动）看到 】 => 不是一个函数, 只是一个变量, 所以要写 =

	// 角色跳跃的参数
	GetCharacterMovement() -> JumpZVelocity = 500.0f; // 跳跃高度
	GetCharacterMovement() -> AirControl = 0.15f; // 在空中的位移灵敏度


	BaseTurnRate = 65.0f; // 🔥因为键盘每次按下只有 1 或 -1， 所以要乘以一个比较大的值, 不然会旋转得很小
	BaseLookUpRate = 65.0f; // 🔥因为键盘每次按下只有 1 或 -1， 所以要乘以一个比较大的值, 不然会旋转得很小
}





// 👇 几个轴映射功能 : 前后左右移动 + 上下左右看的【具体实现】(第二步, 具体实现) , 需要考虑性能跟安全性, 因为轴映射会一直返回值, 要避免 Controller 为空指针或者一直返回 0
// 🌟 角色跳跃功能
void AMainPlayer::Jump() {
	Super::Jump(); //👈继承【父类的跳跃方法】
}

// 🌟 前后奔跑
void AMainPlayer::MoveForward(float Value) {
	// AddMovementInput(GetActorForwardVector(), Value); //👈【简单版】注意, Pawn 类不能调用, Characters 类才能调用 !!  两个参数: 【向世界的哪个方向移动】 【移动的值（移动多远）】, GetActorForwardVector 表示向角色正面方向移动

	// 【👇复杂版 - 摄像机能够旋转到角色前方, 几何学】利用旋转矩阵获取 Controller 的旋转值, 从而【让摄像机能够旋转到角色前方】
	if((Controller != nullptr) && (Value != 0.0f)) { // nullptr 表示空指针
		FRotator Rotation = Controller -> GetControlRotation();
		FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f); // 表示只取 Yaw 轴的值, 也就是左右看的值
		FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X); // 表示只取 X 轴的值, 也就是前后看的值 => 获取指定轴的单位向量; EAxis 表示枚举
		AddMovementInput(Direction, Value);
	}
}


// 🌟 左右奔跑
void AMainPlayer::MoveRight(float Value) {
	// AddMovementInput(GetActorRightVector(), Value); //👈【简单版】注意, Pawn 类不能调用, Characters 类才能调用 !!  两个参数: 【向世界的哪个方向移动】 【移动的值（移动多远）】, GetActorForwardVector 表示向角色正面方向移动
	// 【👇复杂版 - 摄像机能够旋转到角色前方, 几何学】利用旋转矩阵获取 Controller 的旋转值, 从而【让摄像机能够旋转到角色前方】
	if((Controller != nullptr) && (Value != 0.0f)) {
		FRotator Rotation = Controller -> GetControlRotation();
		FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f); // 表示只取 Yaw 轴的值, 也就是左右看的值
		FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y); // 表示只取 X 轴的值, 也就是前后看的值 => 获取指定轴的单位向量; EAxis 表示枚举
		AddMovementInput(Direction, Value);
	}
}

// 🌟 鼠标左右看
void AMainPlayer::Turn(float Value) {
	if(Value != 0.0f) {
		AddControllerYawInput(Value); 
	}
}


// 🌟 鼠标上下看
void AMainPlayer::LookUp(float Value) {
	UE_LOG(LogTemp, Warning, TEXT("%f"), Controller -> GetControlRotation().Pitch); // 👀 观察下鼠标上下看的值, 打印在【输出日志】中, 发现范围是 0/360 ~ 45, 0, 0/360 ~270 这个范围最佳
	//👇会有 bug, UE 内部机制, 快速直接推会推到 46 度, 然后就会卡住了⚠️, 所以要用下面的方法
	// if((GetControlRotation().Pitch > 270.0f && GetControlRotation().Pitch <= 360.0f) ||
	//   (GetControlRotation().Pitch >= 0.0f && GetControlRotation().Pitch < 45.0f))
	// {...}
	// 👇判断非法区域, 限制上下看的范围
	if(GetControlRotation().Pitch < 270.0f && GetControlRotation().Pitch > 180.0f && Value > 0.0f){  // && Value > 0.0f 表示如果在非法区域(旋转到最顶部了)还继续要往大旋转, 则进行阻止
		return; 
	}	
	if(GetControlRotation().Pitch > 45.0f && GetControlRotation().Pitch < 180.0f && Value < 0.0f) { // && Value < 0.0f 表示如果在非法区域(旋转到最底部了)还继续要往小旋转, 则进行阻止
		return;
	}
	//其他区域则合法, 可以上下看
	AddControllerPitchInput(Value); //鼠标上下看
}


// 🌟 键盘左右看的实现
void AMainPlayer::TurnAtRate(float KeyboardRate) { // 键盘上下左右旋转事件, 所以 Rate 不是 0 就是 1 就是 -1, 所以要乘以一个比较大的值, 不然会旋转得很小
	float Value = KeyboardRate *  BaseTurnRate * GetWorld() -> GetDeltaSeconds(); // 【BaseTurmRate】为👆上面定义的变量, GetWorld().GetDeltaSeconds() 表示获得时间间隔 deltaTime, 用来平衡不同设备的帧率
	if(Value != 0.0f) {
		AddControllerYawInput(Value); // 键盘左右看
	}
}


// 🌟 键盘上下看的实现
void AMainPlayer::LookUpAtRate(float KeyboardRate) { // 键盘上下左右旋转事件, 所以 Rate 不是 0 就是 1 就是 -1, 所以要乘以一个比较大的值, 不然会旋转得很小
	float Value = KeyboardRate *  BaseLookUpRate * GetWorld() -> GetDeltaSeconds(); // GetWorld().GetDeltaSeconds() 表示获得时间间隔 deltaTime, 用来平衡不同设备的帧率
	// 👇没有限制上下看范围的做法
	// if(Value != 0.0f) {
	// 	AddControllerPitchInput(-Value); // 键盘上下看, -Value 是因为实际测试上要相反, 希望下键可以向下旋转
	// }
	// 👇判断非法区域, 限制上下看的范围
	if(GetControlRotation().Pitch < 270.0f && GetControlRotation().Pitch > 180.0f && Value > 0.0f){  // && Value > 0.0f 表示如果在非法区域(旋转到最顶部了)还继续要往大旋转, 则进行阻止
		return; 
	}	
	if(GetControlRotation().Pitch > 45.0f && GetControlRotation().Pitch < 180.0f && Value < 0.0f) { // && Value < 0.0f 表示如果在非法区域(旋转到最底部了)还继续要往小旋转, 则进行阻止
		return;
	}
	AddControllerPitchInput(-Value); // 键盘上下看, -Value 是因为实际测试上要相反, 希望下键可以向下旋转
}

