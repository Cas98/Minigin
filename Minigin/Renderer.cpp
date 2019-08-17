#include "MiniginPCH.h"
#include "Renderer.h"
#include <SDL.h>
#include "SceneManager.h"
#include "GameObject.h"
#include <algorithm>
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
	if(m_Sort)
	{
		std::sort(m_pActiveRenderComponents.begin(), m_pActiveRenderComponents.end(),
			[](RenderComponent* obj1, RenderComponent* obj2)
		{
			return obj1->GetGameObject()->GetTransformComponent()->GetPosition().z > obj2->GetGameObject()->GetTransformComponent()->GetPosition().z;
		});
		m_Sort = false;
	}

	SDL_RenderClear(mRenderer);

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

	m_Sort = true;

	return renderComp;
}

void dae::Renderer::SendRenderComponent(RenderComponent* pRenderComponent)
{
	auto it = std::find(m_pActiveRenderComponents.begin(), m_pActiveRenderComponents.end(), pRenderComponent);

	if(it != m_pActiveRenderComponents.end())
	{
		m_pActiveRenderComponents.erase(it);
	}
	m_pNonActiveRenderComponents.push_back(pRenderComponent);
	std::cout << "Returned render component" << std::endl;
}

void dae::Renderer::AddRenderComponents(int size)
{
	for (int i{ 0 }; i < size; ++i)
	{
		m_pNonActiveRenderComponents.push_back(new(true) RenderComponent());
	}
	std::cout << "Added " << size << " render components" << std::endl;
}

void dae::Renderer::SetActiveRenderBuffer(Scene* pOldScene, Scene* pNewScene)
{
	if (pOldScene != nullptr)
	{
		auto itOld = m_ActiveRenderComponentsBuffers.find(pOldScene->GetName());

		//if buffer for current scene does not exists add one
		if (itOld == m_ActiveRenderComponentsBuffers.end())
		{
			AddActiveRenderBuffer(pOldScene);
			itOld = m_ActiveRenderComponentsBuffers.find(pOldScene->GetName());
		}

		//transfer active components t buffer old scene 
		itOld->second = m_pActiveRenderComponents;
	}

	//transfer new scene components to active buffer
	auto it = m_ActiveRenderComponentsBuffers.find(pNewScene->GetName());
	if (it == m_ActiveRenderComponentsBuffers.end())
	{
		AddActiveRenderBuffer(pNewScene);
		it = m_ActiveRenderComponentsBuffers.find(pNewScene->GetName());
	}
	m_pActiveRenderComponents = it->second;
	it->second.clear();
}

void dae::Renderer::RemoveRenderBuffer(dae::Scene* scene)
{
	auto it = m_ActiveRenderComponentsBuffers.find(scene->GetName());
	if (it != m_ActiveRenderComponentsBuffers.end())
	{
		m_ActiveRenderComponentsBuffers.erase(it);
	}
}

void dae::Renderer::AddActiveRenderBuffer(dae::Scene* scene)
{
	std::vector<RenderComponent*> buffer;
	m_ActiveRenderComponentsBuffers.insert(std::pair<std::string, std::vector<RenderComponent*>>(scene->GetName(), buffer));
}