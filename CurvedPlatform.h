#pragma once
#include "Platform.h"
#include "CurvedCollider.h"
class CurvedPlatform : public Platform
{
public:
	CurvedPlatform(Point start, Point size, double a, double b, double c);
	virtual void Render(double delta, RenderBatch* batch) override;
	virtual int GetY() override;
	int Polynomial(int x);
private:
	double a, b, c;
};

