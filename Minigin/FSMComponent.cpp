#include "MiniginPCH.h"
#include "FSMComponent.h"
#include "GameObject.h"

dae::FSMComponent::FSMComponent(State* pStartState)
	:BaseComponent(CompType::FSM), m_pCurrentState(pStartState)
{
}


dae::FSMComponent::~FSMComponent()
{
	delete m_pCurrentState;
}


void dae::FSMComponent::Init()
{
	m_pInputRef = GetGameObject()->GetComponent<dae::InputComponent>();

	if(m_pInputRef == nullptr)
	{
		std::cout << "ERROR: FSM can't find input component\n";
	}
}

void dae::FSMComponent::Update()
{
	//handle input state
	auto pNewState = m_pCurrentState->HandleInput(m_pInputRef);

	if(pNewState)
	{
		//trigger exit function old state
		m_pCurrentState->Exit();

		//delete old state and replace with new state
		delete m_pCurrentState;
		m_pCurrentState = pNewState;

		//trigger enter function new state
		m_pCurrentState->Enter();
	}

	//update state
	m_pCurrentState->Update();
}