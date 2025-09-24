#pragma once
#include <iostream>
#include <cmath>

const int DEFAULT_SCREEN_WIDTH = 1200;
const int DEFAULT_SCREEN_HEIGHT = 900;
const int DEFAULT_MAP_WIDTH = 1280 * 2;
const int DEFAULT_MAP_HEIGHT = 1536 * 2;
const int BORDER_POS_X = 640;
const int BORDER_POS_Y = 512;
const std::string DEFAULT_SCREEN_TITLE = "Thiago Carrijo Rufino Rabelo - 211068350";
const std::string DEFAULT_GAME_PATH = "..";

const int FPS = 144;
const int FPS_PERIOD = 1000 / FPS; // 1000ms / fps

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
const std::string ZOMBIE_PATH = DEFAULT_GAME_PATH + "/resources/img/Enemy.png";

// For Zombie
const int ZOMBIE_HP = 100;
const int ZOMBIE_INIT_X = 600;
const int ZOMBIE_INIT_Y = 450;
const int ZOMBIE_FRAME_TIME = 166; // how many frames in a second
const int ZOMBIE_frameCountW = 3;
const int ZOMBIE_frameCountH = 2;
const int ZOMBIE_HIT_TIME = 500;
const int ZOMBIE_DEATH_TIME = 5000;
const int ZOMBIE_DAMAGE = 20;
const float ZOMBIE_SPEED = 0.5;
const int ZOMBIE_SPAWN_RANGE = 100;
const std::string ZOMBIE_DEATH_SOUND = DEFAULT_GAME_PATH + "/resources/audio/Dead.wav";
const std::string ZOMBIE_DAMAGE_SOUND = DEFAULT_GAME_PATH + "/resources/audio/Hit0.wav";

// For Character
const std::string CHARACTER_PATH = DEFAULT_GAME_PATH + "/resources/img/Player.png";
const int CHARACTER_FRAME_TIME = 166; // how many frames in a second
const int CHARACTER_HP = 100;
const int CHARACTER_DEATH_TIME = 5000;
const int CHARACTER_frameCountW = 3;
const int CHARACTER_frameCountH = 4;
const int CHARACTER_INIT_X = 1280;
const int CHARACTER_INIT_Y = 1280;
const float CHARACTER_SPEED = 1;
const int CHARACTER_HIT_TIME = 500;
const std::string CHARACTER_DEATH_SOUND = DEFAULT_GAME_PATH + "/resources/audio/Dead.wav";
const std::string CHARACTER_DAMAGE_SOUND = DEFAULT_GAME_PATH + "/resources/audio/Hit0.wav";

// For Gun
const std::string GUN_PATH = DEFAULT_GAME_PATH + "/resources/img/Gun.png";
const std::string GUN_SHOT_SOUND = DEFAULT_GAME_PATH + "/resources/audio/Range.wav";
const std::string GUN_RELOAD_SOUND = DEFAULT_GAME_PATH + "/resources/audio/PumpAction.mp3";
const int GUN_COOLDOWN = 830;
const int GUN_FRAME_TIME = 166; // how many frames in a second
const int GUN_FRAME_COUNT_W = 3;
const int GUN_FRAME_COUNT_H = 2;
const int BULLET_COUNT_DEFAULT = 6;
const float GUN_CHARACTER_OFFSET = 60;
const float GUN_BULLET_ANGLE = M_PI / 6; // 60º

// For bullet
const float BULLET_SPEED = 0.5;
const int BULLET_DAMAGE = 30;
const float BULLET_MAX_DISTANCE = 1000;
const std::string BULLET_PATH = DEFAULT_GAME_PATH + "/resources/img/Bullet.png";

// For AI
const std::string AI_CHARACTER_PATH = DEFAULT_GAME_PATH + "/resources/img/NPC.png";
const int AI_HP = 100;
const int COOLDOWN_REST = 1000;
const int AI_SPEED = 0.6;
const int AI_DISTANCE = 350;
const int AI_INIT_X = 0;
const int AI_INIT_Y = 0;

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
