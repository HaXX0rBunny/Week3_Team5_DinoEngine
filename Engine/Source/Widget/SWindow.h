#pragma once
#include "Math/Rect.h"

enum SplitDirection
{
	Horizontal,
	Vertical,
	//Cross
};

enum SplitOption
{
	LT,
	RB,
};

class SSplitter;
class ENGINE_API SWindow
{
	SSplitter* Parent = nullptr;
protected:
	FRect Rect;
public:
	void SetParent(SSplitter* InParent) { Parent = InParent; }
	void SetRect(const FRect& InRect);
	virtual bool ISHover(FPoint coord) const;
	virtual SWindow* GetWindow(FPoint coord);
	FRect GetRect() const { return Rect; }
	virtual void OnResize() {};
	virtual void Draw() {};
	SSplitter* Split(SWindow* InNewWindow, SplitDirection InDirection, SplitOption InSplitOption);
};

class ENGINE_API SSplitter : public SWindow
{
	virtual SWindow* GetWindow(FPoint coord) override;

protected:
	float SplitRatio = 0.5; // 0.0f ~ 1.0f
	SWindow* SideLT = nullptr; // Left or Top
	SWindow* SideRB = nullptr; // Right or Bottom
public:
	SWindow* GetSideLT() { return SideLT; }
	SWindow* GetSideRB() { return SideRB; }
	void SetSideLT(SWindow* InSideLT);
	void SetSideRB(SWindow* InSideRB);
	SSplitter(SWindow* InSideLT = nullptr, SWindow* InSideRB = nullptr, float InSplitRatio = 0.5f);
	~SSplitter();
	float GetSplitRatio() { return SplitRatio; }
	virtual void SetSplitRatio(float InSplitRatio);
	virtual void Draw() override;

};

class SSplitterH : public SSplitter
{
public:
	SSplitterH(SWindow* InSideLT = nullptr, SWindow* InSideRB = nullptr, float InSplitRatio = 0.5f) 
		: SSplitter(InSideLT, InSideRB, InSplitRatio) {}

	virtual void OnResize() override;
};

class SSplitterV : public SSplitter
{
public:
	SSplitterV(SWindow* InSideLT = nullptr, SWindow* InSideRB = nullptr, float InSplitRatio = 0.5f) 
		: SSplitter(InSideLT, InSideRB, InSplitRatio) {}

	virtual void OnResize() override;
};

