#pragma once
#include <Scene.h>
class TestScene :
	public dae::Scene
{
public:
	TestScene();
	~TestScene();

protected:
	virtual void Initialize() override;
	virtual void Update() override;

};

