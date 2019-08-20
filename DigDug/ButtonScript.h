#pragma once
#include <ScriptComponent.h>
#include "InputComponent.h"
#include <functional>
#include "TextureComponent.h"

class ButtonScript final: public dae::ScriptComponent
{
public:
	ButtonScript(glm::vec2 size, std::function<void()> function, std::string path, std::string pathSelected);
	~ButtonScript();

private:
	virtual void Init() override;
	virtual void Update() override;

	dae::InputComponent* m_pInputRef;
	dae::TextureComponent* m_pTextureRef;
	glm::vec2 m_ButtonSize;

	//functionality for button
	std::function<void()> m_Function;

	std::string m_ImagePath;
	std::string m_ImagePathSelected;
	bool m_IsSelected = false;
};

