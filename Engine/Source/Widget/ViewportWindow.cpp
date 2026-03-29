#include "ViewportWindow.h"
#include "Core/FEngine.h"

SViewportWindow::SViewportWindow(FViewportContext* InViewportContext)
	: ViewportContext(InViewportContext)
{
}

SViewportWindow::~SViewportWindow()
{
	if (ViewportContext)
	{
		ViewportContext->Cleanup();
	}
	delete ViewportContext;
}

void SViewportWindow::Tick(float DeltaTime)
{
	if (ViewportContext && GEngine)
	{
		ViewportContext->Tick(GEngine->GetCore(), DeltaTime);
	}
}

void SViewportWindow::Draw()
{
	if (ViewportContext && GEngine)
	{
		ViewportContext->Render(GEngine->GetCore(), GEngine->GetCommandQueue());
	}
}

void SViewportWindow::OnResize()
{
	if (!ViewportContext)
	{
		return;
	}

	ViewportContext->SetRect(GetRect());
}
