#include "MiniginPCH.h"
#include "TextureComponent.h"
#include <SDL.h>

dae::TextureComponent::TextureComponent()
	:BaseComponent(dae::CompType::Texture)
{
	mTexture = new Texture2D();
}

dae::TextureComponent::TextureComponent(const std::string& filePath)
	: BaseComponent(dae::CompType::Texture)
{
	mTexture = new Texture2D(filePath);
}

dae::TextureComponent::~TextureComponent()
{
	delete mTexture;
}

SDL_Texture* dae::TextureComponent::GetSDLTexture() const
{
	return mTexture->GetSDLTexture();
}

void dae::TextureComponent::SetTexture(const std::string& filePath)
{
	mTexture->SetTexture(filePath);
}

void dae::TextureComponent::SetTexture(SDL_Texture* texture)
{
	mTexture->SetTexture(texture);
}