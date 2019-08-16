#pragma once
#include "Singleton.h"
#include "TransformComponent.h"
#include "RenderComponent.h"

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

	public:
		void Initialize(SDL_Window* window, int startSize, int growSize = 10);
		void Render();
		void Destroy();
		glm::vec2 GetWindowSize() const;

		void RenderTexture(SDL_Texture* texture, float x, float y) const;
		void RenderTexture(SDL_Texture* texture, float x, float y, float width, float height) const;
		void RenderTexture(SDL_Texture* texture, float x, float y, float scaleX, float scaleY, float rotation) const;

		SDL_Renderer* GetSDLRenderer() const { return mRenderer; }

		RenderComponent* GetRenderComponent();
		void SendRenderComponent(RenderComponent* pRenderComponent);

	private:
		std::vector<RenderComponent*> m_pNonActiveRenderComponents;
		std::vector<RenderComponent*> m_pActiveRenderComponents;
		int m_GrowSize;
		void AddRenderComponents(int size);
	};
}

