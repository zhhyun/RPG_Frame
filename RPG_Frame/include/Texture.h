#ifndef __Texture__
#define __Texture__
#include <SDL.h>
#include <string>

namespace GameFrame {
	class Texture {
	public:
		Texture( const std::string name);
		Texture();
		~Texture();
		SDL_Texture* GetTexture() { return mTexture; };
		void SetTexture(SDL_Texture* tex) { mTexture = tex; };
		int GetWidth() { return TexWidth; };
		int GetHeight() { return TexHeight; };
		void CreateFromSurface(SDL_Renderer* renderer, SDL_Surface* surface);
		void CreateFromTexture(SDL_Texture* tex);
	private:
		const std::string Name;
		SDL_Texture* mTexture;
		int TexWidth;
		int TexHeight;
	};
}
#endif __Texture__