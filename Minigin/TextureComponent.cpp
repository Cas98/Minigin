#include "MiniginPCH.h"
#include "TextureComponent.h"
#include <SDL.h>

dae::TextureComponent::TextureComponent()
	:BaseComponent(dae::CompType::Texture)
{
	m_pTexture = new Texture2D();
}

dae::TextureComponent::TextureComponent(const std::string& filePath)
	: BaseComponent(dae::CompType::Texture)
{
	m_pTexture = new Texture2D(filePath);
}

dae::TextureComponent::~TextureComponent()
{
	delete m_pTexture;
}

SDL_Texture* dae::TextureComponent::GetSDLTexture() const
{
	return m_pTexture->GetSDLTexture();
}

void dae::TextureComponent::SetTexture(const std::string& filePath)
{
	m_pTexture->SetTexture(filePath);
}

void dae::TextureComponent::SetTexture(SDL_Texture* pTexture)
{
	m_pTexture->SetTexture(pTexture);
}