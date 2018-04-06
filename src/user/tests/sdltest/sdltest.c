#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

void filledRect(void *r_in,
                int x, int y, int w, int h,
                int r, int g, int b, int a)
{
    SDL_Renderer* renderer = (SDL_Renderer*)r_in;
    int rc1 = SDL_SetRenderDrawColor(renderer, r, g, b, a);
    if (rc1 != 0) {
      fprintf(stderr, "SDL_SetRenderDrawColor failed: %s\n", SDL_GetError());
      exit(1);
    }
    SDL_Rect rect = { x, y, w, h };
    int rc2 = SDL_RenderFillRect(renderer, &rect);
    if (rc2 != 0) {
      fprintf(stderr, "SDL_RenderFillRect failed: %s\n", SDL_GetError());
      exit(1);
    }
}

void point(SDL_Renderer* renderer, int x, int y){
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderDrawPoint(renderer, x, y);
}

SDL_Renderer *init(int w, int h) {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    fprintf(stderr, "Cannot initialise SDL: %s\n", SDL_GetError());
    exit(1);
  }

  SDL_Window *window = SDL_CreateWindow(
    "hello", 
    SDL_WINDOWPOS_CENTERED, 
    SDL_WINDOWPOS_CENTERED, 
    w, h,
    SDL_WINDOW_SHOWN
  );
  if (window == NULL) {
    fprintf(stderr, "Unable to create window: %s\n", SDL_GetError());
    exit(1);
  }

  SDL_Renderer *renderer = SDL_CreateRenderer(
    window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
  );
  if (renderer == NULL) {
    fprintf(stderr, "Unable to create renderer: %s\n", SDL_GetError());
    exit(1);
  }

  if (SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND) != 0) {
    fprintf(stderr, "SDL_BlendMode failed: %s\n", SDL_GetError());
    exit(1);
  };

  return renderer;
}

int pollEventsForQuit() {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    switch (e.type) {
      case SDL_QUIT:
        return true;
        break;
      case SDL_KEYDOWN:
        if (e.key.keysym.sym == SDLK_q) {
          return true;
        }
        break;
    }
  }
  return 0;
}

static int TestThread(void *ptr){
	bool ok = true;
	SDL_TLSID tlsid = SDL_TLSCreate();
	SDL_TLSSet(tlsid, (void*)42, NULL);
	if((int)SDL_TLSGet(tlsid) != 42) ok = false;
	SDL_mutex *mtx = SDL_CreateMutex();
	SDL_LockMutex(mtx);
	SDL_UnlockMutex(mtx);
	if(SDL_TryLockMutex(mtx) != 0) ok = false;
	SDL_UnlockMutex(mtx);
	SDL_DestroyMutex(mtx);
	if(ok) filledRect(ptr, 10, 10, 30, 30, 0, 255, 0, 255);
	else filledRect(ptr, 10, 10, 30, 30, 255, 0, 0, 255);
	return 0;
}

int main(void) {
  SDL_Renderer *renderer = init(640, 480);
  bool mousedown = false;
  SDL_RenderClear(renderer);
  
  SDL_Thread *thread = SDL_CreateThread(&TestThread, "TestThread", renderer);
  SDL_WaitThread(thread, NULL);
  
  IMG_Init(IMG_INIT_PNG);
  SDL_Surface *img = IMG_Load("testpng.png");
  SDL_Texture *tex = SDL_CreateTextureFromSurface(renderer, img);
  SDL_Rect dst;
  dst.x = 100;
  dst.y = 100;
  dst.w = 300;
  dst.h = 300;
  SDL_RenderCopy(renderer, tex, NULL, &dst);
  
  for (;;) {
	  SDL_Event e;
	  while (SDL_PollEvent(&e)) {
		switch (e.type) {
		  case SDL_KEYDOWN:
			if (e.key.keysym.sym != SDLK_q) break;
		  case SDL_QUIT:
			goto quit;
		  case SDL_MOUSEBUTTONDOWN:
			  mousedown = true;
			  break;
		   case SDL_MOUSEBUTTONUP:
			  mousedown = false;
			  break;
		}
	  }
	
    int rc1 = SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    if (rc1 != 0) {
      fprintf(stderr, "SDL_SetRenderDrawColor failed: %s\n", SDL_GetError());
      exit(1);
    }
    
	if(mousedown){
		int x, y;
		SDL_GetMouseState(&x, &y);
		point(renderer, x, y);
	}
    filledRect(renderer, 640/2 - 50/2, 480/2 - 50/2, 50, 50, 255, 0, 0, 128);
    SDL_RenderPresent(renderer); // Update screen.
  }
quit:
  SDL_DestroyRenderer(renderer);
  SDL_Quit();

  return 0;
}
