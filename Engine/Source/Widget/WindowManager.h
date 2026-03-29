#pragma once
#include "CoreMinimal.h"
#include "SWindow.h"

class FWindowManager
{
	TArray<SWindow*> Windows;

	SWindow* GetWindowAtPoint(const FPoint& Point) const;
	bool TryDeleteWindow(SWindow* Window);

	template <typename T>
	T* CreateWindow(const FRect& Rect) 
	{
		T* NewWindow = new T();
		Windows.push_back(NewWindow);
		return NewWindow;
	}
};

