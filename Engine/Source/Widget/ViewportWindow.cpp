#include "ViewportWindow.h"
#include "Core/FEngine.h"

SViewportWindow::SViewportWindow(FViewportContext* InViewportContext) : ViewportContext(InViewportContext)
{
}

SViewportWindow::~SViewportWindow()
{
	ViewportContext->Cleanup();
	delete ViewportContext;
	ViewportContext = nullptr;
}

void SViewportWindow::Draw()
{
	ViewportContext->Render(GEngine->GetCore(), GEngine->GetCommandQueue());
}
