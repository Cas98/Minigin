#pragma once
#include "BaseComponent.h"
#include <string>
#include "Texture2D.h"

namespace dae
{
	class TextureComponent  final : public BaseComponent
	{
	public:
		TextureComponent();
		TextureComponent(const std::string& filePath);
		~TextureComponent() override;

		SDL_Texture* GetSDLTexture() const;
		void SetTexture(const std::string& filePath);
		void SetTexture(SDL_Texture* pTexture);

		TextureComponent(const TextureComponent &) = delete;
		TextureComponent(TextureComponent &&) = delete;
		TextureComponent & operator= (const TextureComponent &) = delete;
		TextureComponent & operator= (const TextureComponent &&) = delete;
	private:
		Texture2D* m_pTexture{nullptr};
	};
}

