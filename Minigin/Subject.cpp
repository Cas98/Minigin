#include "MiniginPCH.h"
#include "Subject.h"
#include <algorithm>


void dae::Subject::AddObserver(dae::Observer* observer)
{
	m_pObservers.push_back(observer);
}

void dae::Subject::RemoveObserver(dae::Observer* observer)
{
	auto found = std::find(m_pObservers.begin(), m_pObservers.end(), observer);

	if (found != m_pObservers.end())
	{
		m_pObservers.erase(found);
	}
}

void dae::Subject::Notify(dae::GameObject* gameObject, const std::string& message)
{
	for (size_t i{ 0 }; i < m_pObservers.size(); i++)
	{
		m_pObservers[i]->OnNotify(gameObject, message);
	}
}