#include "MiniginPCH.h"
#include "TextureComponent.h"
#include <SDL.h>
#include "ResourceManager.h"

dae::TextureComponent::TextureComponent(const std::string& filePath)
{
	SetTexture(filePath);
}

dae::TextureComponent::~TextureComponent()
{
	SDL_DestroyTexture(mTexture);
}

SDL_Texture* dae::TextureComponent::GetSDLTexture() const
{
	return mTexture;
}

void dae::TextureComponent::SetTexture(const std::string& filePath)
{
	SDL_DestroyTexture(mTexture);
	mTexture = ResourceManager::GetInstance().LoadTexture(filePath);
}

void dae::TextureComponent::SetTexture(SDL_Texture* texture)
{
	SDL_DestroyTexture(mTexture);
	mTexture = texture;
}