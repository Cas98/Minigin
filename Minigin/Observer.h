#pragma once
namespace dae {
	class GameObject;
}

struct Event
{
	
};

class Observer
{
public:
	virtual ~Observer() {}
	virtual void OnNotify(dae::GameObject* gameObject, Event event) = 0;
};

