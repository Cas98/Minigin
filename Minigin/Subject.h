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

protected:
	void Notify();

private:
	std::vector<Observer*> m_pObservers;
};

