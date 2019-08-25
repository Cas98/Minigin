#include "MiniginPCH.h"
#include "Font.h"
#include "ResourceManager.h"
#include <SDL.h>

//test
TTF_Font* dae::Font::GetFont() const {
	return m_pFont;
}

dae::Font::Font(const std::string& fullPath, unsigned size) : m_pFont(nullptr), m_Size(size)
{
	m_pFont = ResourceManager::GetInstance().LoadFont(fullPath, size);
	if (m_pFont == nullptr)
	{
		throw std::runtime_error(std::string("Failed to load font: ") + SDL_GetError());
	}
}

dae::Font::~Font()
{
	TTF_CloseFont(m_pFont);
}
