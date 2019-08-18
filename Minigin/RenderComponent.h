#pragma once
#include "BaseComponent.h"

namespace dae
{
	class Renderer;
	class RenderComponent final : public BaseComponent
	{
	public:
		RenderComponent();
		~RenderComponent() = default;

		void Render();

		RenderComponent(const RenderComponent &) = delete;
		RenderComponent(RenderComponent &&) = delete;
		RenderComponent & operator= (const RenderComponent &) = delete;
		RenderComponent & operator= (const RenderComponent &&) = delete;

		void * operator new(size_t size);
		void operator delete(void* p);
	};
}

