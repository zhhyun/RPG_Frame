#include "Texture.h"

GameFrame::Texture::Texture(const std::string name) :
	Name(name),
	mTexture(nullptr),
	TexWidth(0),
	TexHeight(0)
{
}

GameFrame::Texture::Texture():
	Name("图案"),
	mTexture(nullptr),
	TexWidth(0),
	TexHeight(0)
{
}

GameFrame::Texture::~Texture()
{
}

void GameFrame::Texture::CreateFromSurface(SDL_Renderer* renderer, SDL_Surface* surface)
{
	if (mTexture != nullptr) {
		return;
	}
	mTexture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_QueryTexture(mTexture, nullptr, nullptr, &TexWidth, &TexHeight);
}

void GameFrame::Texture::CreateFromTexture(SDL_Texture* tex)
{
	if (mTexture != nullptr) {
		return;
	}
	mTexture = tex;
	SDL_QueryTexture(mTexture, nullptr, nullptr, &TexWidth, &TexHeight);
}