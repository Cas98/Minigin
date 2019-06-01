#include "MiniginPCH.h"
#include "RenderComponent.h"
#include "TextureComponent.h"
#include "TransformComponent.h"
#include "GameObject.h"
#include "Renderer.h"

void dae::RenderComponent::Render()
{
	//get texture to render
	auto textureComp = GetParentObject()->GetComponent<TextureComponent>();
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
	auto transform = GetParentObject()->GetComponent<TransformComponent>();

	//render texture
	Renderer::GetInstance().RenderTexture(texture, transform->GetPosition().x, transform->GetPosition().y, transform->GetScale().x, transform->GetScale().y, transform->GetRotation());
}