#pragma once
struct SDL_Texture;

namespace dae
{
	class Texture2D
	{
	public:
		SDL_Texture* GetSDLTexture() const;
		explicit Texture2D(){};
		explicit Texture2D(SDL_Texture* texture);
		explicit Texture2D(const std::string& filePath);
		~Texture2D();

		void SetTexture(SDL_Texture* texture);
		void SetTexture(const std::string& filePath);

		Texture2D(const Texture2D &) = delete;
		Texture2D(Texture2D &&) = delete;
		Texture2D & operator= (const Texture2D &) = delete;
		Texture2D & operator= (const Texture2D &&) = delete;
	private:
		SDL_Texture* m_pTexture;
	};
}
