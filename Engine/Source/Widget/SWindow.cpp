#include "SWindow.h"

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

SSplitter::SSplitter(SWindow* InSideLT, SWindow* InSideRB, float InSplitRatio)
	: SideLT(InSideLT), SideRB(InSideRB), SplitRatio(InSplitRatio)
{
	SetSplitRatio(InSplitRatio);
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
}

void SSplitter::Draw()
{
	SideLT->Draw();
	SideRB->Draw();
}

void SSplitterH::SetSplitRatio(float InSplitRatio)
{
	SSplitter::SetSplitRatio(InSplitRatio);

	float LTWidth = Rect.Size.X * SplitRatio;
	float RBWidth = Rect.Size.X - LTWidth;

	SideLT->SetRect({ Rect.Position, { LTWidth, Rect.Size.Y } });
	SideRB->SetRect({ { Rect.Position.X + LTWidth, Rect.Position.Y }, { RBWidth, Rect.Size.Y } });

}

void SSplitterV::SetSplitRatio(float InSplitRatio)
{
	SSplitter::SetSplitRatio(InSplitRatio);

	float LTHeight = Rect.Size.Y * SplitRatio;
	float RBHeight = Rect.Size.Y - LTHeight;

	SideLT->SetRect({ Rect.Position, { Rect.Size.X, LTHeight } });
	SideRB->SetRect({ { Rect.Position.X, Rect.Position.Y + LTHeight}, { Rect.Size.X, RBHeight } });
}

