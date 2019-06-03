#pragma once
#include "Singleton.h"
#include "TransformComponent.h"

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Texture;

namespace dae
{
	class Texture2D;
	class Renderer final : public Singleton<Renderer>
	{
		SDL_Window* m_pWindow = nullptr;
		SDL_Renderer* mRenderer = nullptr;
		TransformComponent* m_pCameraTransform = nullptr;
	public:
		void Init(SDL_Window* window);
		void Render();
		void Destroy();
		glm::vec2 GetWindowSize() const;

		void RenderTexture(SDL_Texture* texture, float x, float y) const;
		void RenderTexture(SDL_Texture* texture, float x, float y, float width, float height) const;
		void RenderTexture(SDL_Texture* texture, float x, float y, float scaleX, float scaleY, float rotation) const;

		SDL_Renderer* GetSDLRenderer() const { return mRenderer; }
	};
}

