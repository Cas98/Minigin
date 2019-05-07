#pragma once
#include "BaseComponent.h"
#include <SDL_ttf.h>

namespace dae
{
	class TextComponent final : public BaseComponent
	{
	public:
		TextComponent(const std::string& text, const std::string& fontPath, unsigned int size);
		TextComponent(const std::string& fontPath, unsigned int size);
		~TextComponent();

		void Update() override;
		void SetText(const std::string& text);

		TextComponent(const TextComponent &) = delete;
		TextComponent(TextComponent &&) = delete;
		TextComponent & operator= (const TextComponent &) = delete;
		TextComponent & operator= (const TextComponent &&) = delete;

	private:
		bool mNeedsUpdate;
		std::string mText;
		TTF_Font* mFont;
	};
}

