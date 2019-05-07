#pragma once
#include "Singleton.h"
#include <SDL_ttf.h>
struct SDL_Texture;

namespace dae
{
	class ResourceManager final : public Singleton<ResourceManager>
	{
		std::string mDataPath;
	public:
		ResourceManager() = default;

		void Init(std::string&& data);

		SDL_Texture* LoadTexture(const std::string& file);
		TTF_Font* LoadFont(const std::string& file, unsigned int size);
	};

}
