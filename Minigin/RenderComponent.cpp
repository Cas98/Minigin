#include "MiniginPCH.h"
#include "RenderComponent.h"
#include "TextureComponent.h"
#include "TransformComponent.h"
#include "GameObject.h"
#include "Renderer.h"
#include <SDL.h>

void dae::RenderComponent::Render()
{
	//get texture to render
	auto texture = GetParentObject()->GetComponent<TextureComponent>()->GetSDLTexture();
	
	if (texture == nullptr)
	{
		return;
	}

	////get pos
	auto position = GetParentObject()->GetComponent<TransformComponent>()->GetPosition();

	//render texture
	Renderer::GetInstance().RenderTexture(texture, position.x, position.y);
}