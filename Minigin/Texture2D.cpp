#include "MiniginPCH.h"
#include "Texture2D.h"
#include <SDL.h>
#include "ResourceManager.h"

dae::Texture2D::Texture2D(SDL_Texture* texture)
{
	m_pTexture = texture;
}

dae::Texture2D::Texture2D(const std::string& filePath)
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(filePath);
}

dae::Texture2D::~Texture2D()
{
	SDL_DestroyTexture(m_pTexture);
}

SDL_Texture* dae::Texture2D::GetSDLTexture() const
{
	return m_pTexture;
}

void dae::Texture2D::SetTexture(SDL_Texture* texture)
{
	SDL_DestroyTexture(m_pTexture);
	m_pTexture = texture;
}

void dae::Texture2D::SetTexture(const std::string& filePath)
{
	SDL_DestroyTexture(m_pTexture);
	m_pTexture = ResourceManager::GetInstance().LoadTexture(filePath);
}