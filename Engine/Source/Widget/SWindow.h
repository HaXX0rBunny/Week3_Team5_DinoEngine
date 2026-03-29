#pragma once
#include "Math/Rect.h"

class ENGINE_API SWindow
{
protected:
	FRect Rect;
public:
	void SetRect(const FRect& InRect);
	virtual bool ISHover(FPoint coord) const;
	virtual SWindow* GetWindow(FPoint coord);
	FRect GetRect() const { return Rect; }
	virtual void OnResize() = 0;
	virtual void Draw() = 0;
};

class ENGINE_API SSplitter : public SWindow
{
	virtual SWindow* GetWindow(FPoint coord) override;

protected:
	float SplitRatio = 0.5; // 0.0f ~ 1.0f
	SWindow* SideLT = nullptr; // Left or Top
	SWindow* SideRB = nullptr; // Right or Bottom
public:
	SSplitter(SWindow* InSideLT, SWindow* InSideRB, float InSplitRatio = 0.5f);
	~SSplitter();
	float GetSplitRatio() { return SplitRatio; }
	virtual void SetSplitRatio(float InSplitRatio);
	virtual void Draw() override;
};

class SSplitterH : public SSplitter
{
public:
	virtual void SetSplitRatio(float InSplitRatio) override;
};

class SSplitterV : public SSplitter
{
public:
	virtual void SetSplitRatio(float InSplitRatio) override;
};

