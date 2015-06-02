#ifndef _cvars_h_
#define _cvars_h_


// app parameters

//	#define DEBUG 0
//	#define FULLSCREEN 1
//	#define WINDOW_WIDTH 480
//	#define WINDOW_HEIGHT 272
//	#define VSYNC 0
//	#define SCROLL_THRESHOLD 0.1
//	#define MAX_MESSAGES 4
//	#define DB_PATH "craft.db"
//	#define USE_CACHE 1
//	#define DAY_LENGTH 600
//	#define INVERT_MOUSE 0


// rendering options
extern int          CVAR_RENDER_SHOW_LIGHTS;
extern int          CVAR_RENDER_SHOW_PLANTS;
extern int          CVAR_RENDER_SHOW_CLOUDS;
extern int          CVAR_RENDER_SHOW_TREES;
extern int          CVAR_RENDER_SHOW_ITEM;
extern int          CVAR_RENDER_SHOW_CROSSHAIRS;
extern int          CVAR_RENDER_SHOW_WIREFRAME;
extern int          CVAR_RENDER_SHOW_INFO_TEXT;
extern int          CVAR_RENDER_SHOW_CHAT_TEXT;
extern int          CVAR_RENDER_SHOW_PLAYER_NAMES;
extern float        CVAR_RENDER_TEXT_SIZE;

// world
extern int          CVAR_WORLD_CREATE_CHUNK_RADIUS;
extern int          CVAR_WORLD_RENDER_CHUNK_RADIUS;
extern int          CVAR_WORLD_RENDER_SIGN_RADIUS;
extern int          CVAR_WORLD_DELETE_CHUNK_RADIUS;
extern int          CVAR_WORLD_CHUNK_SIZE;
extern int          CVAR_WORLD_COMMIT_INTERVAL;

// key bindings
//	#define CRAFT_KEY_FORWARD 'W'
//	#define CRAFT_KEY_BACKWARD 'S'
//	#define CRAFT_KEY_LEFT 'A'
//	#define CRAFT_KEY_RIGHT 'D'
//	#define CRAFT_KEY_JUMP GLFW_KEY_SPACE
//	#define CRAFT_KEY_FLY GLFW_KEY_TAB
//	#define CRAFT_KEY_OBSERVE 'O'
//	#define CRAFT_KEY_OBSERVE_INSET 'P'
//	#define CRAFT_KEY_ITEM_NEXT 'E'
//	#define CRAFT_KEY_ITEM_PREV 'R'
//	#define CRAFT_KEY_ZOOM GLFW_KEY_LEFT_SHIFT
//	#define CRAFT_KEY_ORTHO 'F'
//	#define CRAFT_KEY_CHAT 't'
//	#define CRAFT_KEY_COMMAND '/'
//	#define CRAFT_KEY_SIGN '`'


typedef enum {
    CVARTYPE_NONE = 0,
    CVARTYPE_INT,
    CVARTYPE_FLOAT,
    CVARTYPE_STRING,
    CVARTYPE_BOOL,
    CVARTYPE_FP_INT,      // function pointer: int fp( int )
    CVARTYPE_FP_FLOAT,    // function pointer: int fp( float )
    CVARTYPE_FP_STRING,   // function pointer: int fp( string )
} CVarType;

typedef int (*cvar_int_callback)(int);
typedef int (*cvar_float_callback)(float);
typedef int (*cvar_string_callback)(const char*);

typedef struct {
    const char* name;
    CVarType type;
    void* vptr;
} CVar;

int cvar_get_idx( const char *varname );
CVarType cvar_get_type( const int index );
void *cvar_get_ptr( const int index );
int cvar_set_value_from_string(const char *varname, const char *value);

#endif