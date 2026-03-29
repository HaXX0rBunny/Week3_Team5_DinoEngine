#pragma once
#include "EngineAPI.h"
#include "SWindow.h"
#include "Core/ViewportContext.h"

class ENGINE_API SViewportWindow : public SWindow
{
	FViewportContext* ViewportContext = nullptr;


public:
	SViewportWindow(FViewportContext* InViewportContext);
	virtual ~SViewportWindow();
	virtual void Draw() override;
};

