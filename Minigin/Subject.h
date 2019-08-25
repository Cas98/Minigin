#pragma once
#include <vector>
#include "Observer.h"

namespace dae
{
	class Subject
	{
	public:
		Subject() = default;
		~Subject() = default;

		void AddObserver(dae::Observer* observer);
		void RemoveObserver(dae::Observer* observer);

		void Notify(dae::GameObject* gameObject, const std::string& message);

	private:
		std::vector<dae::Observer*> m_pObservers;
	};
}

