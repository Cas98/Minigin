#pragma once
#include "BaseComponent.h"

namespace dae
{
	class RenderComponent final : public BaseComponent
	{
	public:
		RenderComponent();
		~RenderComponent() = default;

		void Render() override;

		RenderComponent(const RenderComponent &) = delete;
		RenderComponent(RenderComponent &&) = delete;
		RenderComponent & operator= (const RenderComponent &) = delete;
		RenderComponent & operator= (const RenderComponent &&) = delete;
	};
}

