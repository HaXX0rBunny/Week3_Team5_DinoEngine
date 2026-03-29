#pragma once
#include "EngineAPI.h"
#include "SWindow.h"
#include "Core/ViewportContext.h"
#include <memory>

class ENGINE_API SViewportWindow : public SWindow
{
	FViewportContext* ViewportContext;

public:
	explicit SViewportWindow(FViewportContext* InViewportContext);
	~SViewportWindow() override;

	virtual void Tick(float DeltaTime) override;
	virtual void Draw() override;
	virtual void OnResize() override;
};

