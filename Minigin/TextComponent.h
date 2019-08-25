#pragma once
#include "BaseComponent.h"
#include "Font.h"

namespace dae
{
	class TextComponent final : public BaseComponent
	{
	public:
		TextComponent(const std::string& text, const std::string& fontPath, unsigned int size);
		TextComponent(const std::string& fontPath, unsigned int size);
		~TextComponent() override;

		void Update() override;
		void SetText(const std::string& text);
		void SetColor(SDL_Color color);

		TextComponent(const TextComponent &) = delete;
		TextComponent(TextComponent &&) = delete;
		TextComponent & operator= (const TextComponent &) = delete;
		TextComponent & operator= (const TextComponent &&) = delete;

	private:
		bool m_NeedsUpdate;
		std::string m_Text;
		Font* m_pFont;
		SDL_Color m_Color = {255,255,255};
	};
}

