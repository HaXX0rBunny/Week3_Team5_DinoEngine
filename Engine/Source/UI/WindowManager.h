#pragma once
#include "CoreMinimal.h"
#include "Windows.h"
#include "SWindow.h"
#include <functional>
#include <memory>

class FViewportClient;
class FViewportContext;
class FInputManager;
class FEnhancedInputManager;
class FCore;
class SViewportWindow;

class ENGINE_API FWindowManager
{
	TArray<SWindow*> Windows;
	FInputManager* InputManager = nullptr;
	FEnhancedInputManager* EnhancedInputManager = nullptr;

public:
	~FWindowManager();

	void Initialize(FInputManager* InInputManager, FEnhancedInputManager* InEnhancedInputManager);
	void Shutdown();
	void SetRootRect(const FRect& InRect);
	void CheckParent();
	SWindow* GetWindowAtPoint(const FPoint& Point) const;
	void Tick(float DeltaTime);
	void DrawWindows() const;
	void AddWindow(SWindow* NewWindow);
};
