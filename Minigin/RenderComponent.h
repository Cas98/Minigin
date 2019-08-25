#pragma once
#include "BaseComponent.h"

namespace dae
{
	class Renderer;
	class RenderComponent final : public BaseComponent
	{
	public:
		RenderComponent();
		~RenderComponent() override = default;

		void Render();

		RenderComponent(const RenderComponent &) = delete;
		RenderComponent(RenderComponent &&) = delete;
		RenderComponent & operator= (const RenderComponent &) = delete;
		RenderComponent & operator= (const RenderComponent &&) = delete;

		//overide new operator to get RenderComponent from renderer
		void * operator new(size_t size);
		//overide new operator to send RenderComponent back to renderer
		void operator delete(void* p);
	};
}

