#include "pch.h"
#include "ButtonScript.h"
#include "GameObject.h"

ButtonScript::ButtonScript(glm::vec2 size, std::function<void()> function, std::string path, std::string pathSelected)
	:m_ButtonSize(size), m_Function(function), m_ImagePath(path), m_ImagePathSelected(pathSelected)
{
}


ButtonScript::~ButtonScript()
{

}

void ButtonScript::Init()
{
	m_pInputRef = GetGameObject()->GetComponent<dae::InputComponent>();
	m_pTextureRef = GetGameObject()->GetComponent<dae::TextureComponent>();
}

void ButtonScript::Update()
{
	auto mousePos = m_pInputRef->GetMousePos();
	auto buttonPos = GetGameObject()->GetTransformComponent()->GetPosition();
	
	if(mousePos.x >= buttonPos.x && mousePos.x <= buttonPos.x + m_ButtonSize.x
		&& mousePos.y >= buttonPos.y && mousePos.y <= buttonPos.y + m_ButtonSize.y)
	{
		if(!m_IsSelected)
		{
			m_pTextureRef->SetTexture(m_ImagePathSelected);
			m_IsSelected = true;
		}
		
		if (m_pInputRef->KeyboardPressed(0x01))
		{
			m_Function();
		}
	}
	else if(m_IsSelected)
	{
		m_pTextureRef->SetTexture(m_ImagePath);
		m_IsSelected = false;
	}
	
}
