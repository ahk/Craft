#include "cvars.h"
#include <string.h>
#include <stdio.h>

// rendering options
int     CVAR_RENDER_SHOW_LIGHTS = 1;
int     CVAR_RENDER_SHOW_PLANTS = 1;
int     CVAR_RENDER_SHOW_CLOUDS = 1;
int     CVAR_RENDER_SHOW_TREES = 1;
int     CVAR_RENDER_SHOW_ITEM = 1;
int     CVAR_RENDER_SHOW_CROSSHAIRS = 1;
int     CVAR_RENDER_SHOW_WIREFRAME = 1;
int     CVAR_RENDER_SHOW_INFO_TEXT = 1;
int     CVAR_RENDER_SHOW_CHAT_TEXT = 1;
int     CVAR_RENDER_SHOW_PLAYER_NAMES = 1;
float   CVAR_RENDER_TEXT_SIZE = 8.0f;

// world
int     CVAR_WORLD_CREATE_CHUNK_RADIUS = 2;
int     CVAR_WORLD_RENDER_CHUNK_RADIUS = 2;
int     CVAR_WORLD_RENDER_SIGN_RADIUS = 4;
int     CVAR_WORLD_DELETE_CHUNK_RADIUS = 4;
int     CVAR_WORLD_CHUNK_SIZE = 8;
int     CVAR_WORLD_COMMIT_INTERVAL = 5;

/*// app parameters
#define DEBUG 0
#define FULLSCREEN 1
#define WINDOW_WIDTH 480
#define WINDOW_HEIGHT 272
#define VSYNC 0
#define SCROLL_THRESHOLD 0.1
#define MAX_MESSAGES 4
#define DB_PATH "craft.db"
#define USE_CACHE 1
#define DAY_LENGTH 600
#define INVERT_MOUSE 0

// key bindings
#define CRAFT_KEY_FORWARD 'W'
#define CRAFT_KEY_BACKWARD 'S'
#define CRAFT_KEY_LEFT 'A'
#define CRAFT_KEY_RIGHT 'D'
#define CRAFT_KEY_JUMP GLFW_KEY_SPACE
#define CRAFT_KEY_FLY GLFW_KEY_TAB
#define CRAFT_KEY_OBSERVE 'O'
#define CRAFT_KEY_OBSERVE_INSET 'P'
#define CRAFT_KEY_ITEM_NEXT 'E'
#define CRAFT_KEY_ITEM_PREV 'R'
#define CRAFT_KEY_ZOOM GLFW_KEY_LEFT_SHIFT
#define CRAFT_KEY_ORTHO 'F'
#define CRAFT_KEY_CHAT 't'
#define CRAFT_KEY_COMMAND '/'
#define CRAFT_KEY_SIGN '`'
*/


static CVar config_vars[] = {
    // rendering options
    { "render.show_lights",             CVARTYPE_BOOL,      &CVAR_RENDER_SHOW_LIGHTS            },
    { "render.show_plants",             CVARTYPE_BOOL,      &CVAR_RENDER_SHOW_PLANTS            },
    { "render.show_clouds",             CVARTYPE_BOOL,      &CVAR_RENDER_SHOW_CLOUDS            },
    { "render.show_trees",              CVARTYPE_BOOL,      &CVAR_RENDER_SHOW_TREES             },
    { "render.show_item",               CVARTYPE_BOOL,      &CVAR_RENDER_SHOW_ITEM              },
    { "render.show_crosshairs",         CVARTYPE_BOOL,      &CVAR_RENDER_SHOW_CROSSHAIRS        },
    { "render.show_wireframe",          CVARTYPE_BOOL,      &CVAR_RENDER_SHOW_WIREFRAME         },
    { "render.show_info_text",          CVARTYPE_BOOL,      &CVAR_RENDER_SHOW_INFO_TEXT         },
    { "render.show_chat_text",          CVARTYPE_BOOL,      &CVAR_RENDER_SHOW_CHAT_TEXT         },
    { "render.show_player_names",       CVARTYPE_BOOL,      &CVAR_RENDER_SHOW_PLAYER_NAMES      },
    { "render.text_size",               CVARTYPE_FLOAT,     &CVAR_RENDER_TEXT_SIZE              },

    // world options
    { "world.chunk.creation_radius",    CVARTYPE_INT,       &CVAR_WORLD_CREATE_CHUNK_RADIUS     },
    { "world.chunk.render_radius",      CVARTYPE_INT,       &CVAR_WORLD_RENDER_CHUNK_RADIUS     },
    { "world.sign.render_radius",       CVARTYPE_INT,       &CVAR_WORLD_RENDER_SIGN_RADIUS      },
    { "world.chunk.deletion_radius",    CVARTYPE_INT,       &CVAR_WORLD_DELETE_CHUNK_RADIUS     },
    { "world.chunk.size",               CVARTYPE_INT,       &CVAR_WORLD_CHUNK_SIZE              },
    { "world.chunk.commit_interval",    CVARTYPE_INT,       &CVAR_WORLD_COMMIT_INTERVAL         },
};

// helper macro to get array size
#define NELEMS(x)  (sizeof(x) / sizeof((x)[0]))

static const int num_config_vars = NELEMS(config_vars);


int cvar_get_idx( const char *varname ) {
    for( int i = 0; i < num_config_vars; i++ ) {
        if( strcasecmp( config_vars[i].name, varname ) == 0 ) {
            return i;
        }
    }
    return -1;
}

CVarType cvar_get_type( const int index ) {
    if( ( index < 0) || ( index > num_config_vars ) )
        return CVARTYPE_NONE;
    else return config_vars[index].type;
}

void *cvar_get_ptr( const int index ) {
    if( ( index < 0) || ( index > num_config_vars ) )
        return 0;
    else return config_vars[index].vptr;
}

int cvar_set_value_from_string(const char *varname, const char *value) {
    // get index into configvar array
    int cfg_var_index = cvar_get_idx( varname );

    // get variable type
    CVarType cfg_var_type =  cvar_get_type( cfg_var_index );

    // get variable pointer
    void *cfg_var_ptr = cvar_get_ptr( cfg_var_index );

    if( cfg_var_ptr != 0 ) {
        
        int tempint = 0;
        float tempfloat = 0;
        char tempstr[128];

        switch( cfg_var_type ) {
            // handle integer vars
            case CVARTYPE_INT:
                return (sscanf( value, "%d", (int*)cfg_var_ptr ) == 1);
                break;

            // handle float vars
            case CVARTYPE_FLOAT:
                return (sscanf( value, "%f", (float*)cfg_var_ptr ) == 1);
                break;

            // handle boolean vars
            case CVARTYPE_BOOL:
                if( ( strcasecmp(value, "on" ) == 0) || ( strcasecmp(value, "true" ) == 0) ) {
                    *((int*)cfg_var_ptr) = 1;
                    return 1;
                }else if( ( strcasecmp(value, "off" ) == 0) || ( strcasecmp(value, "false" ) == 0) ) {
                    *((int*)cfg_var_ptr) = 0;
                    return 1;
                }else return 0;
                break;

            // handle string vars
            case CVARTYPE_STRING:
                strncpy( (char*)cfg_var_ptr, value, 127 );
                return 1;
                break;

            // handle integer vars with a callback
            case CVARTYPE_FP_INT:
                if(sscanf( value, "%d", &tempint ) == 1) {
                    return ((cvar_int_callback)cfg_var_ptr)(tempint);
                }
                else return 0;
                break;

            // handle float vars with a callback
            case CVARTYPE_FP_FLOAT:
                if(sscanf( value, "%f", &tempfloat ) == 1) {
                    return ((cvar_float_callback)cfg_var_ptr)(tempfloat);
                }
                else return 0;
                break;

            // handle string vars with a callback
            case CVARTYPE_FP_STRING:
                strncpy( tempstr, value, 127 );
                return ((cvar_string_callback)cfg_var_ptr)(tempstr);
                break;
            case CVARTYPE_NONE:
                return 0;
                break;
        }
    }
    return 0;
}