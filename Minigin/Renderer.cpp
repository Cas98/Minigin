#include "MiniginPCH.h"
#include "Renderer.h"
#include <SDL.h>
#include "SceneManager.h"
#include "Scene.h"
#pragma warning(push)
#pragma warning (disable:4291)


void dae::Renderer::Initialize(SDL_Window * window, int startSize, int growSize)
{
	m_GrowSize = growSize;

	mRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (mRenderer == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}
	m_pWindow = window;

	AddRenderComponents(startSize);
}

void dae::Renderer::Render()
{
	SDL_RenderClear(mRenderer);

	//SceneManager::GetInstance().Render();
	for (int i{ 0 }; i < m_pActiveRenderComponents.size(); ++i)
	{
		m_pActiveRenderComponents[i]->Render();
	}
	
	SDL_RenderPresent(mRenderer);
}

void dae::Renderer::Destroy()
{
	if (mRenderer != nullptr)
	{
		SDL_DestroyRenderer(mRenderer);
		mRenderer = nullptr;
	}

	for (int i{0}; i < m_pNonActiveRenderComponents.size(); ++i)
	{
		free(m_pNonActiveRenderComponents[i]);
	}

	for (int i{ 0 }; i < m_pActiveRenderComponents.size(); ++i)
	{
		free(m_pActiveRenderComponents[i]);
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

	SDL_RenderCopyEx(GetSDLRenderer(), texture, nullptr, &dst, double(rotation) , NULL, SDL_RendererFlip::SDL_FLIP_NONE);
}

glm::vec2 dae::Renderer::GetWindowSize() const
{
	int x, y;
	SDL_GetWindowSize(m_pWindow, &x, &y);
	return(glm::vec2(x, y));
}

dae::RenderComponent* dae::Renderer::GetRenderComponent()
{
	if (m_pNonActiveRenderComponents.size() <= 0) AddRenderComponents(m_GrowSize);

	auto renderComp = m_pNonActiveRenderComponents[m_pNonActiveRenderComponents.size() - 1];

	m_pNonActiveRenderComponents.pop_back();
	m_pActiveRenderComponents.push_back(renderComp);

	std::cout << "Got render component" << std::endl;

	return renderComp;
}

void dae::Renderer::SendRenderComponent(RenderComponent* pRenderComponent)
{
	auto it = std::find(m_pActiveRenderComponents.begin(), m_pActiveRenderComponents.end(), pRenderComponent);

	if(it != m_pActiveRenderComponents.end())
	{
		m_pNonActiveRenderComponents.push_back(*it);
		m_pActiveRenderComponents.erase(it);

		std::cout << "Returned render component" << std::endl;
	}
	else
	{
		free(pRenderComponent);
		std::cout << "Returning render component FAILED" << std::endl;
	}
}

void dae::Renderer::AddRenderComponents(int size)
{
	for (int i{ 0 }; i < size; ++i)
	{
		m_pNonActiveRenderComponents.push_back(new(true) RenderComponent());
	}
	std::cout << "Added " << size << " render components" << std::endl;
}