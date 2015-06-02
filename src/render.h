#ifndef _render_h_
#define _render_h_
#include "craft.h"

int render_chunks(Attrib *attrib, Player *player);
void render_signs(Attrib *attrib, Player *player);
void render_sign(Attrib *attrib, Player *player);
void render_players(Attrib *attrib, Player *player);
void render_sky(Attrib *attrib, Player *player, GLuint buffer);
void render_wireframe(Attrib *attrib, Player *player);
void render_crosshairs(Attrib *attrib);
void render_item(Attrib *attrib);
void render_text( Attrib *attrib, int justify, float x, float y, float n, char *text);

#endif