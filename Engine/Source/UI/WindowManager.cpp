#include "WindowManager.h"
#include "Core/Viewport.h"
#include "Core/ViewportClient.h"
#include "Core/ViewportContext.h"
#include "Input/InputManager.h"
#include <windowsx.h>

FWindowManager::~FWindowManager()
{
	Shutdown();
}

void FWindowManager::Initialize(FInputManager* InInputManager, FEnhancedInputManager* InEnhancedInputManager)
{
	InputManager = InInputManager;
	EnhancedInputManager = InEnhancedInputManager;
}

void FWindowManager::Shutdown()
{
	for (SWindow* Window : Windows)
	{
		delete Window;
	}
	Windows.clear();
	InputManager = nullptr;
	EnhancedInputManager = nullptr;
}

void FWindowManager::SetRootRect(const FRect& InRect)
{
	if (Windows.empty() || !Windows[0])
	{
		return;
	}

	Windows[0]->SetRect(InRect);
}

void FWindowManager::CheckParent()
{
	for(int i = 0; i < Windows.size(); ++i)
	{
		if (!Windows[i])
			continue;

		if(!Windows[i]->GetParent())
			continue;

		Windows[i] = Windows[i]->GetParent();
	}
}

SWindow* FWindowManager::GetWindowAtPoint(const FPoint& Point) const
{
	for (SWindow* Window : Windows)
	{
		if (Window && Window->ISHover(Point))
		{
			return Window->GetWindow(Point);
		}
	}
	return nullptr;
}


void FWindowManager::Tick(float DeltaTime)
{
	for (SWindow* Window : Windows)
	{
		if (Window)
		{
			Window->Tick(DeltaTime);
		}
	}
}

void FWindowManager::DrawWindows() const
{
	for (SWindow* Window : Windows)
	{
		if (Window)
		{
			Window->Draw();
		}
	}
}

void FWindowManager::AddWindow(SWindow* NewWindow)
{
	if (!NewWindow)
	{
		return;
	}

	Windows.push_back(NewWindow);
}
