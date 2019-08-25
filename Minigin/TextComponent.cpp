#include "MiniginPCH.h"
#include "TextComponent.h"
#include "Renderer.h"
#include "GameObject.h"
#include "TextureComponent.h"
#include "ResourceManager.h"

dae::TextComponent::TextComponent(const std::string& text, const std::string& fontPath, unsigned int size)
	:BaseComponent(dae::CompType::Text)
{
	m_Text = text;
	m_pFont = new Font(fontPath, size);

	m_NeedsUpdate = true;
}

dae::TextComponent::TextComponent(const std::string& fontPath, unsigned int size)
	:BaseComponent(dae::CompType::Text)
{
	m_pFont = new Font(fontPath, size);
}

dae::TextComponent::~TextComponent()
{
	delete m_pFont;
}

void dae::TextComponent::TextComponent::Update()
{
	if (m_NeedsUpdate)
	{
		//look for parent texture component
		auto textureComp = GetGameObject()->GetComponent<TextureComponent>();

		if (textureComp == nullptr)
		{
			throw std::runtime_error(std::string("Parent obnject doesn't have an texture component"));
		}

		const auto surf = TTF_RenderText_Blended(m_pFont->GetFont(), m_Text.c_str(), m_Color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);

		//set texture
		textureComp->SetTexture(texture);

		m_NeedsUpdate = false;
	}
}

void dae::TextComponent::SetText(const std::string& text)
{
	//set text
	m_Text = text;
	m_NeedsUpdate = true;
}

void dae::TextComponent::SetColor(SDL_Color color)
{
	m_Color = color;
}

