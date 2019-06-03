#include "MiniginPCH.h"
#include "Renderer.h"
#include <SDL.h>
#include "SceneManager.h"
#include "Scene.h"
#include "CameraComponent.h"


void dae::Renderer::Init(SDL_Window * window)
{
	mRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (mRenderer == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}
	m_pWindow = window;
}

void dae::Renderer::Render()
{
	CameraComponent* camera = SceneManager::GetInstance().GetActiveScene()->GetActiveCamera();
	if (camera)
	{
		m_pCameraTransform = camera->GetTransform();
	}

	SDL_RenderClear(mRenderer);

	SceneManager::GetInstance().Render();
	
	SDL_RenderPresent(mRenderer);
}

void dae::Renderer::Destroy()
{
	if (mRenderer != nullptr)
	{
		SDL_DestroyRenderer(mRenderer);
		mRenderer = nullptr;
	}
}

void dae::Renderer::RenderTexture(SDL_Texture* texture, const float x, const float y) const
{
	SDL_Rect dst;
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(texture, nullptr, nullptr, &dst.w, &dst.h);
	SDL_RenderCopy(GetSDLRenderer(), texture, nullptr, &dst);
}

void dae::Renderer::RenderTexture(SDL_Texture* texture, const float x, const float y, const float width, const float height) const
{
	SDL_Rect dst;
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = static_cast<int>(width);
	dst.h = static_cast<int>(height);
	SDL_RenderCopy(GetSDLRenderer(), texture, nullptr, &dst);
}

void dae::Renderer::RenderTexture(SDL_Texture* texture, const float x, const float y, const float scaleX, const float scaleY, const float rotation) const
{
	SDL_Rect dst;
	
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(texture, nullptr, nullptr, &dst.w, &dst.h);
	dst.w = int(dst.w * scaleX);
	dst.h = int(dst.h * scaleY);

	if(m_pCameraTransform)
	{
		dst.x -= static_cast<int>(m_pCameraTransform->GetPosition().x);
		dst.y -= static_cast<int>(m_pCameraTransform->GetPosition().y);
		SDL_RenderSetScale(mRenderer, m_pCameraTransform->GetScale().x, m_pCameraTransform->GetScale().y);
	}

	SDL_RenderCopyEx(GetSDLRenderer(), texture, nullptr, &dst, double(rotation) , NULL, SDL_RendererFlip::SDL_FLIP_NONE);
}

glm::vec2 dae::Renderer::GetWindowSize() const
{
	int x, y;
	SDL_GetWindowSize(m_pWindow, &x, &y);
	return(glm::vec2(x, y));
}