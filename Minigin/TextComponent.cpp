#include "MiniginPCH.h"
#include "TextComponent.h"
#include "Renderer.h"
#include "GameObject.h"
#include "TextureComponent.h"
#include "ResourceManager.h"


dae::TextComponent::TextComponent(const std::string& text, const std::string& fontPath, unsigned int size)
{
	mText = text;

	mFont = ResourceManager::GetInstance().LoadFont(fontPath, size);
	if (mFont == nullptr)
	{
		throw std::runtime_error(std::string("Failed to load font: ") + SDL_GetError());
	}

	mNeedsUpdate = true;
}

dae::TextComponent::TextComponent(const std::string& fontPath, unsigned int size)
{
	mFont = ResourceManager::GetInstance().LoadFont(fontPath, size);
	if (mFont == nullptr)
	{
		throw std::runtime_error(std::string("Failed to load font: ") + SDL_GetError());
	}
}

dae::TextComponent::~TextComponent()
{
	TTF_CloseFont(mFont);
}

void dae::TextComponent::TextComponent::Update()
{
	if (mNeedsUpdate)
	{
		//look for parent texture component
		auto textureComp = GetParentObject()->GetComponent<TextureComponent>();

		if (textureComp == nullptr)
		{
			throw std::runtime_error(std::string("Parent obnject doesn't have an texture component"));
		}

		const SDL_Color color = { 255,255,255 }; // only white text is supported now
		const auto surf = TTF_RenderText_Blended(mFont, mText.c_str(), color);
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

		textureComp->SetTexture(texture);

		mNeedsUpdate = false;
	}
}

void dae::TextComponent::SetText(const std::string& text)
{
	//set text
	mText = text;
	mNeedsUpdate = true;
}


