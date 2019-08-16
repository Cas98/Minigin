#pragma once
#include <vector>
#include "Observer.h"


class Subject
{
public:
	Subject() = default;
	~Subject() = default;

	void AddObserver(Observer* observer);
	void RemoveObserver(Observer* observer);

	void Notify(dae::GameObject* gameObject, const std::string& message);

private:
	std::vector<Observer*> m_pObservers;
};

