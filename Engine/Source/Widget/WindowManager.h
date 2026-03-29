#pragma once
#include "CoreMinimal.h"
#include "SWindow.h"

class FWindowManager
{
	TArray<SWindow*> Windows;

public:
	~FWindowManager();
	SWindow* GetWindowAtPoint(const FPoint& Point) const;
	bool TryDeleteWindow(SWindow* Window);
	void CheckParent();
	void DrawWindows() const;
	void Tick(float deltaTime);

	template <typename T, typename... Args>
	T* CreateSWindow(Args&&... args)
	{
		T* NewWindow = new T(std::forward<Args>(args)...);
		Windows.push_back(NewWindow);
		return NewWindow;
	}
};

