#include "pch.h"
#include "BlockScript.h"

BlockScript::BlockScript()
{
	m_pSubject = new Subject();
}

BlockScript::~BlockScript()
{
	delete m_pSubject;
}

void BlockScript::Init()
{
}

void BlockScript::Update()
{
	
}

void BlockScript::MoveBlock(const dae::Direction& newDirection)
{
	m_Direction = newDirection;
	m_pSubject->Notify("Move");
}

Subject* BlockScript::GetSubject() const
{
	return m_pSubject;
}

dae::Direction BlockScript::GetDirection() const
{
	return m_Direction;
}