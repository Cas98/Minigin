#include "MiniginPCH.h"
#include "RenderComponent.h"
#include "TextureComponent.h"
#include "TransformComponent.h"
#include "GameObject.h"
#include "Renderer.h"

dae::RenderComponent::RenderComponent()
	:BaseComponent(dae::CompType::Render)
{
	
}

void dae::RenderComponent::Render()
{
	//get texture to render
	auto textureComp = GetGameObject()->GetComponent<TextureComponent>();
	if (textureComp == nullptr)
	{
		std::cout << "ERROR: No texture component to render\n";
		return;
	}

	auto texture = textureComp->GetSDLTexture();
	
	if (texture == nullptr)
	{
		std::cout << "ERROR: No texture in texture component\n";
		return;
	}

	////get pos
	auto transform = GetGameObject()->GetTransformComponent();

	//render texture
	Renderer::GetInstance().RenderTexture(texture, transform->GetPosition().x, transform->GetPosition().y, transform->GetScale().x, transform->GetScale().y, transform->GetRotation());
}