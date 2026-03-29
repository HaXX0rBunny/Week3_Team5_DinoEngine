#include "WindowManager.h"


FWindowManager::~FWindowManager()
{
	for (SWindow* Window : Windows)
	{
		delete Window;
	}
	Windows.clear();
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

bool FWindowManager::TryDeleteWindow(SWindow* Window)
{
	if (!std::erase(Windows, Window))
		return false;

	delete Window;
	return true;
}

void FWindowManager::DrawWindows() const
{
	for (SWindow* Window : Windows)
	{
		if (!Window)
			continue;

		Window->Draw();
	}
}

