#include "MiniginPCH.h"
#include "SubjectComponent.h"


dae::SubjectComponent::SubjectComponent()
	:BaseComponent(dae::CompType::Subject)
{
	m_pSubject = new Subject();
}


dae::SubjectComponent::~SubjectComponent()
{
	delete m_pSubject;
}

void dae::SubjectComponent::Update()
{
	
}

void dae::SubjectComponent::AddObserver(Observer* pObserver)
{
	m_pSubject->AddObserver(pObserver);
}

void dae::SubjectComponent::RemoveObserver(Observer* pObserver)
{
	m_pSubject->RemoveObserver(pObserver);
}

void dae::SubjectComponent::Notify(dae::GameObject* gameObject, const std::string& message)
{
	m_pSubject->Notify(gameObject, message);
}