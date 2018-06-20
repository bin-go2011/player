#include "display.h"
#include <stdexcept>


SDL::SDL() {
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
}

SDL::~SDL() {
	SDL_Quit();
}

Display::Display(const unsigned width, const unsigned height) :
	window_{SDL_CreateWindow(
		"player", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE), SDL_DestroyWindow},
	renderer_{SDL_CreateRenderer(
		window_.get(), -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC), SDL_DestroyRenderer},
	texture_{SDL_CreateTexture(
		renderer_.get(), SDL_PIXELFORMAT_YV12, SDL_TEXTUREACCESS_STREAMING,
		width, height), SDL_DestroyTexture} {

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(renderer_.get(), width, height);

	SDL_SetRenderDrawColor(renderer_.get(), 0, 0, 0, 255);
	SDL_RenderClear(renderer_.get());
	SDL_RenderPresent(renderer_.get());
}

void Display::refresh(
	std::array<uint8_t*, 3> planes, std::array<size_t, 3> pitches) {
	SDL_UpdateYUVTexture(
		texture_.get(), nullptr,
		planes[0], pitches[0],
		planes[1], pitches[1],
		planes[2], pitches[2]);
	SDL_RenderClear(renderer_.get());
	SDL_RenderCopy(renderer_.get(), texture_.get(), nullptr, nullptr);
	SDL_RenderPresent(renderer_.get());
}

void Display::input() {
	if (SDL_PollEvent(&event_)) {
		switch (event_.type) {
		case SDL_KEYUP:
			switch (event_.key.keysym.sym) {
			case SDLK_ESCAPE:
				quit_ = true;
				break;
			case SDLK_SPACE:
				play_ = !play_;
				break;
			default:
				break;
			}
			break;
		case SDL_QUIT:
			quit_ = true;
			break;
		default:
			break;
		}
	}
}

bool Display::get_quit() {
	return quit_;
}

bool Display::get_play() {
	return play_;
}
