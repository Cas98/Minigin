#pragma once

namespace dae 
{
	class GameObject;
	class Observer
	{
	public:
		virtual ~Observer() {}
		virtual void OnNotify(dae::GameObject* gameObject, const std::string& message) = 0;
	};
}

