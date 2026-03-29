#include "SWindow.h"

void SWindow::SetRect(const FRect& InRect)
{
	Rect = InRect;
	OnResize();
}

bool SWindow::ISHover(FPoint coord) const
{
	return coord.X >= Rect.Position.X && coord.X <= Rect.Position.X + Rect.Size.X &&
		coord.Y >= Rect.Position.Y && coord.Y <= Rect.Position.Y + Rect.Size.Y;
}

SWindow* SWindow::GetWindow(FPoint coord)
{
	if (ISHover(coord))
	{
		return this;
	}

	return nullptr;
}

SSplitter* SWindow::Split(SWindow* InNewWindow, SplitDirection InDirection, SplitOption InSplitOption)
{
	SSplitter* NewSplitter = nullptr;

	if (InDirection == SplitDirection::Horizontal)
	{
		NewSplitter = new SSplitterH();
	}
	else if (InDirection == SplitDirection::Vertical)
	{
		NewSplitter = new SSplitterV();
	}

	if (!NewSplitter)
		return nullptr;

	if (InSplitOption == SplitOption::LT)
	{
		NewSplitter->SetSideLT(this);
		NewSplitter->SetSideRB(InNewWindow);
	}
	else if (InSplitOption == SplitOption::RB)
	{
		NewSplitter->SetSideLT(InNewWindow);
		NewSplitter->SetSideRB(this);
	}
	NewSplitter->SetParent(Parent);
	return NewSplitter;
}

void SSplitter::SetSideLT(SWindow* InSideLT)
{
	SideLT = InSideLT;
	if (InSideLT)
		InSideLT->SetParent(this);
}

void SSplitter::SetSideRB(SWindow* InSideRB)
{
	SideRB = InSideRB;
	if (InSideRB)
		InSideRB->SetParent(this);
}

SSplitter::SSplitter(SWindow* InSideLT, SWindow* InSideRB, float InSplitRatio)
	: SideLT(InSideLT), SideRB(InSideRB), SplitRatio(InSplitRatio)
{
	SetSplitRatio(InSplitRatio);
	SetSideLT(InSideLT);
	SetSideRB(InSideRB);
}

SSplitter::~SSplitter()
{
	if (SideLT)
	{
		delete SideLT;
		SideLT = nullptr;
	}
	if (SideRB)
	{
		delete SideRB;
		SideRB = nullptr;
	}
}

SWindow* SSplitter::GetWindow(FPoint coord)
{
	if (SideLT && SideLT->ISHover(coord))
	{
		return SideLT->GetWindow(coord);
	}
	else if (SideRB && SideRB->ISHover(coord))
	{
		return SideRB->GetWindow(coord);
	}
	return nullptr;
}

void SSplitter::SetSplitRatio(float InSplitRatio)
{
	if (InSplitRatio < 0.0f)
	{
		SplitRatio = 0.0f;
	}
	else if (InSplitRatio > 1.0f)
	{
		SplitRatio = 1.0f;
	}
	else
	{
		SplitRatio = InSplitRatio;
	}
	OnResize();
}

void SSplitter::Draw()
{
	SideLT->Draw();
	SideRB->Draw();
}

void SSplitterH::OnResize()
{
	float LTWidth = Rect.Size.X * SplitRatio;
	float RBWidth = Rect.Size.X - LTWidth;

	SideLT->SetRect({ Rect.Position, { LTWidth, Rect.Size.Y } });
	SideRB->SetRect({ { Rect.Position.X + LTWidth, Rect.Position.Y }, { RBWidth, Rect.Size.Y } });
}

void SSplitterV::OnResize()
{
	float LTHeight = Rect.Size.Y * SplitRatio;
	float RBHeight = Rect.Size.Y - LTHeight;

	SideLT->SetRect({ Rect.Position, { Rect.Size.X, LTHeight } });
	SideRB->SetRect({ { Rect.Position.X, Rect.Position.Y + LTHeight}, { Rect.Size.X, RBHeight } });
}

