#pragma once
#include "CoreMinimal.h"
#include "Windows.h"
#include "SWindow.h"
#include <functional>
#include <memory>
#include "Widget/ViewportWindow.h"

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
	SWindow* GetWindowAtPoint(const FPoint& Point) const;
	void Tick(float DeltaTime);
	void DrawWindows() const;

	template <typename T, typename... Args>
	T* CreateSWindow(Args&&... args)
	{
		T* NewWindow = new T(std::forward<Args>(args)...);
		Windows.push_back(NewWindow);
		return NewWindow;
	}
};
