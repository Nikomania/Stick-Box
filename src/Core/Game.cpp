#include <Core/Game.h>
#include <Manager/Resources.h>
#include <Manager/InputManager.h>
#include <State/TitleState.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <time.h>
#include <DataStructure/constants.h>
#include <cmath>

Game* Game::instance = nullptr;

Game::Game(std::string title, int width, int height) :
stateStack(),
storedState(nullptr),
dt(0) {
  SDL_Log("Starting game...\n");
  if (
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0 ||
    IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG ||
    TTF_Init() != 0 ||
    Mix_Init(MIX_INIT_MP3) != MIX_INIT_MP3 ||
    Mix_OpenAudio(
      MIX_DEFAULT_FREQUENCY,
      MIX_DEFAULT_FORMAT,
      MIX_DEFAULT_CHANNELS,
      CHUNKSIZE_MIX
    ) != 0 ||
    Mix_AllocateChannels(SIMUL_CHANNELS_MIX) != SIMUL_CHANNELS_MIX
  ) {
    std::cout << "Error: " << SDL_GetError() << std::endl;
    exit(1);
  }
  SDL_Log("SDL, SDL_image, SDL_ttf and SDL_mixer initialized!\n");

  window = SDL_CreateWindow(
    title.c_str(),
    SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED,
    width,
    height,
    SDL_WINDOW_SHOWN
  );
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  SDL_Log("Window and renderer created!\n");

  instance = this;
  stateStack.emplace(new TitleState());

  frameStart = SDL_GetTicks();

  srand(time(NULL));

  SDL_Log("Game fully initialized!\n");
}

Game::~Game() {
  SDL_Log("Closing game...\n");

  Resources::ClearImages();
  Resources::ClearMusics();
  Resources::ClearSounds();
  Resources::ClearFonts();

  Mix_CloseAudio();
  Mix_Quit();
  TTF_Quit();
  IMG_Quit();
  
  std::cout << "Destroying renderer...\n";
  SDL_DestroyRenderer(renderer);

  std::cout << "Destroying window...\n";
  SDL_DestroyWindow(window);

  std::cout << "Quitting SDL...\n";
  SDL_Quit();

  std::cout << "Deleting stored state...\n";
  if (storedState != nullptr) {
    delete storedState;
  }

  SDL_Log("See ya!\n");
}

SDL_Renderer* Game::GetRenderer() {
  return renderer;
}

Game& Game::GetInstance() {
  if (instance == nullptr) {
    new Game(DEFAULT_SCREEN_TITLE, DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT);
  }
  return *instance;
}

State& Game::GetCurrentState() {
  if (stateStack.empty()) {
    throw std::runtime_error("State stack is empty!");
  }
  return *(stateStack.top());
}

void Game::Push(State* state) {
  storedState = state;
}

void Game::Run() {
  SDL_Log("Running game...\n");

  InputManager& input = InputManager::GetInstance();

  GetCurrentState().Start();

  while (!stateStack.empty() && !GetCurrentState().QuitRequested()) {
    // SDL_Log("Time for frame: %.2f ms\n", dt);
    CalculateDeltaTime();

    if (GetCurrentState().PopRequested()) {
      stateStack.pop();
      std::cout << "Popped state!\n";
      Resources::ClearImages();
      Resources::ClearMusics();
      Resources::ClearSounds();
      Resources::ClearFonts();
      GetCurrentState().Resume(); // what if there isn't a next state?
    }

    if (storedState != nullptr) {
      GetCurrentState().Pause();
      stateStack.emplace(storedState);
      storedState = nullptr;
      GetCurrentState().Start();
    }

    input.Update();
    GetCurrentState().Update(dt);

    // SDL_RenderClear(renderer);
    GetCurrentState().Render();
    SDL_RenderPresent(renderer);

    // calculate how much time to wait to achieve the desired FPS,
    // considering the time already spent in the frame
    uint32_t wait_next_frame = static_cast<uint32_t>(std::lround(FPS_PERIOD - (SDL_GetTicks() - frameStart)));
    if (wait_next_frame < FPS_PERIOD) {
      SDL_Delay(wait_next_frame);
    }
  }

  if (!stateStack.empty()) {
    std::cout << "Deleting state stack...\n";
    ClearStack();
  }
}

void Game::ClearStack() {
  while (!stateStack.empty()) {
    stateStack.pop();
  }
}

void Game::CalculateDeltaTime() {
  dt = std::min(static_cast<float>(SDL_GetTicks() - frameStart), FPS_PERIOD);
  frameStart = SDL_GetTicks();
}

float Game::GetDeltaTime() {
  return dt;
}
