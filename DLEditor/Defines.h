//////////////////////////////////////////////////////////////////////////////////
// Project: Simple RPG Editor
//////////////////////////////////////////////////////////////////////////////////
#ifndef DEFINES_
#define DEFINES_

//// Window related defines 
//#define WINDOW_WIDTH   500
//#define WINDOW_HEIGHT  400
//#define WINDOW_TITLE   "Space Invaders Clone"

// Resource Manager defines
#define RES_LIST_NAME			"GameRes.ini"

// Game defines
#define GAME_WIDTH				800
#define GAME_HEIGHT				640
#define GAME_MAP_WIDTH			512
#define GAME_MAP_HEIGHT			512
#define GAME_TITLE				"Dragonlance 0.01"
#define GAME_GRID				32

#define MONSTER_FOV				128	// 4 grids

// Editor Window defines
#define EDITOR_WIDTH			800
#define EDITOR_HEIGHT			640
#define EDITOR_TITLE			"Tasslehoff's Map Editor"
#define EDITOR_MOUSE_X_START	0
#define EDITOR_MOUSE_Y_START	128
#define EDITOR_MOUSE_X_MAX		512		// Map Boundary X
#define EDITOR_MOUSE_Y_MAX		640		// Map Boundary Y
#define EDITOR_BIAS_X_MIN	   	  0		// Four biases mean that		
#define EDITOR_BIAS_X_MAX       512		// the dimension of the
#define EDITOR_BIAS_Y_MIN		  0		// map is 1024*1024
#define EDITOR_BIAS_Y_MAX       512     // this is crucial
#define EDITOR_MOUSE_W			20
#define EDITOR_MOUSE_H			20

#define EDITOR_CURSOR_WIDTH		32
#define EDITOR_CURSOR_HEIGHT	32

#define EDITOR_GUI_WIDTH		32
#define EDITOR_GUI_HEIGHT		32

#define EDITOR_BUTTON_BLINK		30		// 30 frames of animation when clicked

// Frame rate related defines 
#define FRAMES_PER_SECOND		50
#define FRAME_RATE				1000/FRAMES_PER_SECOND  // frame rate (for the menu states)
#define PHYSICS_FPS				30   // physics iterations per second (for the game state)

// Tile related defines
#define TILE_MENU_X_TOTAL		320	//Tilemap starts from x=0
#define TILE_MENU_Y_TOTAL		32	//Tilemap starts from y=0
#define TILE_WIDTH				32
#define TILE_HEIGHT				32
#define TILE_DISPLAY_WIDTH		32
#define TILE_DISPLAY_HEIGHT		32
#define EDITOR_TILE_MAXIMUM		10
#define EIDTOR_TILE_SCROLL		320		//x of Tile Scroll buttons

// Entity menu related defines
#define ENTITY_MENU_WIDTH		32
#define ENTITY_MENU_HEIGHT		96
#define ENTITY_WIDTH			32
#define ENTITY_HEIGHT			32
#define ENTITY_ANIMATE_RATE		200	//200ms for 1 frame

// GUI related
#define PLAYERSTART_FONT_SIZE	18
#define PLAYERSTART_X			600
#define PLAYERSTART_Y			300

//// Player related defines 
//#define PLAYER_IMG_X       0
//#define PLAYER_IMG_Y       1
//#define PLAYER_WIDTH       26
//#define PLAYER_HEIGHT      24
//#define PLAYER_SPEED       3.0f
//#define PLAYER_FIRING_RATE 250  // minimum time (milliseconds) between each shot
//#define PLAYER_START_X     ((WINDOW_WIDTH/2)-(PLAYER_WIDTH/2))
//#define PLAYER_START_Y     (WINDOW_HEIGHT-PLAYER_HEIGHT-10)
//
//#define MAX_LIVES 3
//#define SCORE_PER_KILL 250
//
//// Where to display lives and score
//#define LIVES_X (WINDOW_WIDTH-60)
//#define LIVES_Y 5
//#define SCORE_X 5
//#define SCORE_Y 5
//
//// Enemy related defines
//#define ENEMIES_PER_ROW  10
//#define ENEMIES_PER_COL  7
//
//#define ENEMY_START_Y    50   
//
//#define ENEMY1_FRAME1_X  78
//#define ENEMY1_FRAME1_Y  4
//#define ENEMY1_FRAME2_X  112
//#define ENEMY1_FRAME2_Y  4
//
//#define ENEMY2_FRAME1_X  1
//#define ENEMY2_FRAME1_Y  38
//#define ENEMY2_FRAME2_X  37
//#define ENEMY2_FRAME2_Y  38
//
//#define ENEMY3_FRAME1_X  77
//#define ENEMY3_FRAME1_Y  33
//#define ENEMY3_FRAME2_X  111
//#define ENEMY3_FRAME2_Y  33
//
//#define ENEMY4_FRAME1_X  1
//#define ENEMY4_FRAME1_Y  67
//#define ENEMY4_FRAME2_X  36
//#define ENEMY4_FRAME2_Y  67
//
//#define ENEMY5_FRAME1_X  76
//#define ENEMY5_FRAME1_Y  65
//#define ENEMY5_FRAME2_X  109
//#define ENEMY5_FRAME2_Y  65
//
//#define ENEMY_WIDTH       30
//#define ENEMY_HEIGHT      20
//#define ENEMY_SPEED_X     10	// distance per physics iteration the enemy can move 
//#define ENEMY_SPEED_Y     ENEMY_HEIGHT // distance the enemy is moved downwards
//#define ENEMY_ANIM_RATE   500   // time (milliseconds) between change in animation frames
//#define ENEMY_FIRING_RATE 250   // minimum time (milliseconds) between each shot
//#define ENEMY_MOVE_RATE   500   // enemies are moved every ENEMY_MOVE_RATE milliseconds
//#define ENEMY_SHOOT_PROB  1.0f  // probability (as a percentage) an enemy will shoot
//
//// UFO related defines 
//#define UFO_IMG1_X     4
//#define UFO_IMG1_Y     165
//#define UFO_IMG2_X     49
//#define UFO_IMG2_Y     165
//#define UFO_WIDTH      30
//#define UFO_HEIGHT     18
//#define UFO_START_Y    25
//#define UFO_SPEED      1.0f
//#define UFO_ANIM_RATE  500  // time (milliseconds) between change in animation frame
//#define UFO_FLYBY_PROB 1.0f // probability (as a percentage) the UFO will fly-by
//#define UFO_KILL_SCORE 1000
//
//// Projectile related defines 
//#define PLAYER_PROJ_IMG_X  45
//#define PLAYER_PROJ_IMG_Y  3
//#define PLAYER_PROJ_WIDTH  8
//#define PLAYER_PROJ_HEIGHT 8
//#define PLAYER_PROJ_SPEED  2.0f
//#define ENEMY_PROJ_IMG_X   46
//#define ENEMY_PROJ_IMG_Y   16
//#define ENEMY_PROJ_WIDTH   7
//#define ENEMY_PROJ_HEIGHT  7
//#define ENEMY_PROJ_SPEED   2.0f
//
//// Block related defines //
//#define BLOCK5_IMG_X  3
//#define BLOCK5_IMG_Y  101
//#define BLOCK4_IMG_X  54
//#define BLOCK4_IMG_Y  94
//#define BLOCK3_IMG_X  105
//#define BLOCK3_IMG_Y  94
//#define BLOCK2_IMG_X  3
//#define BLOCK2_IMG_Y  132
//#define BLOCK1_IMG_X  54
//#define BLOCK1_IMG_Y  132
//
//#define LEFT_BLOCK_X   75
//#define LEFT_BLOCK_Y   300
//#define RIGHT_BLOCK_X  225
//#define RIGHT_BLOCK_Y  300
//#define MIDDLE_BLOCK_X 375
//#define MIDDLE_BLOCK_Y 300
//
//#define BLOCK_WIDTH  45
//#define BLOCK_HEIGHT 24
//
//#define MAX_BLOCK_HEALTH 4
//
//// Location of the image used for displaying the number of lives left 
//#define LIVES_IMG_X      28
//#define LIVES_IMG_Y      7
//#define LIVES_IMG_WIDTH  13
//#define LIVES_IMG_HEIGHT 12
//
//// Text output related defines (for the menu states)
//#define SG_X  220   // Start (G)ame (from main menu)
//#define SG_Y  160   
//#define QGM_X 220   // (Q)uit Game (from main menu)  
//#define QGM_Y 180
//#define QGE_X 220   // (Q)uit Game (from exit menu)  
//#define QGE_Y 160
//#define YW_X  220   // YOU WIN! (from win screen)
//#define YW_Y  160
//#define QGW_X 220   // (Q)uit Game (from win screen)  
//#define QGW_Y 180
//#define GO_X  220   // GAME OVER (from game over screen)
//#define GO_Y  160
//#define QGL_X 220   // (Q)uit Game (from game over screen)  
//#define QGL_Y 180

#endif
// Aaron Cox, 2005