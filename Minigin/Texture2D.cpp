#include "MiniginPCH.h"
#include "Texture2D.h"
#include <SDL.h>
#include "ResourceManager.h"

dae::Texture2D::Texture2D(SDL_Texture* texture)
{
	mTexture = texture;
}

dae::Texture2D::Texture2D(const std::string& filePath)
{
	mTexture = ResourceManager::GetInstance().LoadTexture(filePath);
}

dae::Texture2D::~Texture2D()
{
	SDL_DestroyTexture(mTexture);
}

SDL_Texture* dae::Texture2D::GetSDLTexture() const
{
	return mTexture;
}

void dae::Texture2D::SetTexture(SDL_Texture* texture)
{
	SDL_DestroyTexture(mTexture); 
	mTexture = texture;
}

void dae::Texture2D::SetTexture(const std::string& filePath)
{
	SDL_DestroyTexture(mTexture);
	mTexture = ResourceManager::GetInstance().LoadTexture(filePath);
}