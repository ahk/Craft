#ifndef _physics_h_
#define _physics_h_
#include "craft.h"

int _hit_test(Map *map, float max_distance, int previous, float x, float y, float z, float vx, float vy, float vz, int *hx, int *hy, int *hz);
int hit_test(int previous, float x, float y, float z, float rx, float ry, int *bx, int *by, int *bz);
int hit_test_face(Player *player, int *x, int *y, int *z, int *face);
int collide(int height, float *x, float *y, float *z);
int player_intersects_block(int height, float x, float y, float z, int hx, int hy, int hz);

#endif