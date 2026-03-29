#pragma once
#include "Math/Rect.h"

class ENGINE_API SWindow
{
protected:
	FRect Rect;
public:
	void SetRect(const FRect& InRect) { Rect = InRect; }
	virtual bool ISHover(FPoint coord) const;
	virtual SWindow* GetWindow(FPoint coord);
	FRect GetRect() const { return Rect; }

	virtual void Draw() = 0;
};

class ENGINE_API SSplitter : public SWindow
{
	virtual SWindow* GetWindow(FPoint coord) override;

protected:
	float SplitRatio; // 0.0f ~ 1.0f
	SWindow* SideLT; // Left or Top
	SWindow* SideRB; // Right or Bottom
	SSplitter() = default;

public:
	SSplitter(SWindow* InSideLT, SWindow* InSideRB, float InSplitRatio = 0.5f);
	float GetSplitRatio() { return SplitRatio; }
	virtual void SetSplitRatio(float InSplitRatio);
	virtual void Draw() override;
};

class SSplitterH : public SSplitter
{
	SSplitterH() = default;

public:
	virtual void SetSplitRatio(float InSplitRatio) override;
};

class SSplitterV : public SSplitter
{
	SSplitterV() = default;

public:
	virtual void SetSplitRatio(float InSplitRatio) override;
};

