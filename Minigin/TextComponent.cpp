#include "MiniginPCH.h"
#include "TextComponent.h"
#include "Renderer.h"
#include "GameObject.h"
#include "TextureComponent.h"
#include "ResourceManager.h"


dae::TextComponent::TextComponent(const std::string& text, const std::string& fontPath, unsigned int size)
	:BaseComponent(dae::CompType::Text)
{
	mText = text;
	mFont = new Font(fontPath, size);

	mNeedsUpdate = true;
}

dae::TextComponent::TextComponent(const std::string& fontPath, unsigned int size)
	:BaseComponent(dae::CompType::Text)
{
	mFont = new Font(fontPath, size);
}

dae::TextComponent::~TextComponent()
{
	delete mFont;
}

void dae::TextComponent::TextComponent::Update()
{
	if (mNeedsUpdate)
	{
		//look for parent texture component
		auto textureComp = GetGameObject()->GetComponent<TextureComponent>();

		if (textureComp == nullptr)
		{
			throw std::runtime_error(std::string("Parent obnject doesn't have an texture component"));
		}

		const SDL_Color color = { 255,255,255 }; // only white text is supported now
		const auto surf = TTF_RenderText_Blended(mFont->GetFont(), mText.c_str(), color);
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


