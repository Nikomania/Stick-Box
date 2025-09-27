#pragma once
#include <iostream>
#include <cmath>

const int DEFAULT_SCREEN_WIDTH = 1200;
const int DEFAULT_SCREEN_HEIGHT = 900;
const int DEFAULT_MAP_WIDTH = 1280 * 2;
const int DEFAULT_MAP_HEIGHT = 1536 * 2;
const std::string DEFAULT_SCREEN_TITLE = "Stick Box";
const std::string DEFAULT_GAME_PATH = "..";

const int FPS = 144;
const int FPS_PERIOD = 1000 / FPS; // 1000ms / fps
const float GRAVITY = 0.5;

// For Camera
const float CAMERA_SPEED_DEFAULT = 0.7;

// For TileSet and TileMap
const std::string TILE_SET_PATH = DEFAULT_GAME_PATH + "/resources/img/Tileset.png";
const std::string TILE_MAP_PATH = DEFAULT_GAME_PATH + "/resources/map/map.txt";
const int TILE_SET_FRAME_WIDTH = 64;
const int TILE_SET_FRAME_HEIGHT = 64;

// For sdl2_mix
const int CHUNKSIZE_MIX = 1024;
const int SIMUL_CHANNELS_MIX = 32;

// For State Render BG
const int BG_DEFAULT_POS = 0;

// Assets paths
const std::string BG_PATH = DEFAULT_GAME_PATH + "/resources/img/Background.png";
const std::string MUSIC_PATH = DEFAULT_GAME_PATH + "/resources/audio/BGM.wav";

// For Character
const std::string CHARACTER_PATH = DEFAULT_GAME_PATH + "/resources/new_resources/img/stick-box-v2.png";
const int CHARACTER_IDLE_FRAME_TIME = 333; // how many frames in a second
const int CHARACTER_WALK_FRAME_TIME = 166; // how many frames in a second
const int CHARACTER_DEATH_FRAME_TIME = 1000; // how many frames in a second
const int CHARACTER_HP = 100;
const int CHARACTER_DEATH_TIME = 5000;
const int CHARACTER_frameCountW = 7;
const int CHARACTER_frameCountH = 1;
const int CHARACTER_INIT_X = 1280;
const int CHARACTER_INIT_Y = 1280;
const float CHARACTER_SPEED = 0.5;
const int CHARACTER_HIT_TIME = 500;
const std::string CHARACTER_DEATH_SOUND = DEFAULT_GAME_PATH + "/resources/audio/Dead.wav";
const std::string CHARACTER_DAMAGE_SOUND = DEFAULT_GAME_PATH + "/resources/audio/Hit0.wav";

// For title image
const std::string TITLE_IMAGE_PATH = DEFAULT_GAME_PATH + "/resources/img/Title.png";
const std::string TITLE_MESSAGE = "Press SPACE to start";
const int BLINK_SHOW_TIME = 500;
const int BLINK_HIDDEN_TIME = 500;

// For text
const std::string DEFAULT_FONT_PATH = DEFAULT_GAME_PATH + "/resources/font/neodgm.ttf";
const int DEFAULT_FONT_SIZE = 30;

// For EndState
const std::string END_IMAGE_WIN_PATH = DEFAULT_GAME_PATH + "/resources/img/Win.png";
const std::string MUSIC_PATH_WIN = DEFAULT_GAME_PATH + "/resources/audio/endStateWin.ogg";
const std::string END_IMAGE_LOSE_PATH = DEFAULT_GAME_PATH + "/resources/img/Lose.png";
const std::string MUSIC_PATH_LOSE = DEFAULT_GAME_PATH + "/resources/audio/endStateLose.ogg";
const std::string END_QUIT_MESSAGE = "Press ESC to quit";
const std::string END_MESSAGE = "Press SPACE to play again";
const int END_BLINK_SHOW_TIME = 500;
const int END_BLINK_HIDDEN_TIME = 500;
