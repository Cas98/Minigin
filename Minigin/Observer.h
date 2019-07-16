#pragma once
class Observer
{
public:
	virtual ~Observer() {}
	virtual void OnNotify(std::string message) = 0;
};

