#pragma once
#include <Scene.h>
class TestScene :
	public dae::Scene
{
public:
	TestScene();
	//~TestScene();

	float sec = 10.0f;

protected:
	virtual void Initialize() override;
	virtual void Update() override;

};

