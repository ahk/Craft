#ifndef _chunk_h_
#define _chunk_h_
#include "craft.h"

int chunked(float x);
Chunk *find_chunk(int p, int q);
int _gen_sign_buffer( GLfloat *data, float x, float y, float z, int face, const char *text);
void gen_sign_buffer(Chunk *chunk);
int has_lights(Chunk *chunk);
void dirty_chunk(Chunk *chunk);
int chunk_distance(Chunk *chunk, int p, int q);
int chunk_visible(float planes[6][4], int p, int q, int miny, int maxy);
void compute_chunk(WorkerItem *item);
void generate_chunk(Chunk *chunk, WorkerItem *item);
void gen_chunk_buffer(Chunk *chunk);
void load_chunk(WorkerItem *item);
void request_chunk(int p, int q);
void init_chunk(Chunk *chunk, int p, int q);
void create_chunk(Chunk *chunk, int p, int q);
void delete_chunks();
void delete_all_chunks();
void check_workers();
void force_chunks(Player *player);
void ensure_chunks_worker(Player *player, Worker *worker);
void ensure_chunks(Player *player);
int worker_run(void *arg);
int highest_block(float x, float z);
void occlusion(char neighbors[27], char lights[27], float shades[27], float ao[6][4], float light[6][4]);
void light_fill(char *opaque, char *light, int x, int y, int z, int w, int force);
void map_set_func(int x, int y, int z, int w, void *arg);
void unset_sign(int x, int y, int z);
void unset_sign_face(int x, int y, int z, int face);
void _set_sign(int p, int q, int x, int y, int z, int face, const char *text, int dirty);
void set_sign(int x, int y, int z, int face, const char *text);
void toggle_light(int x, int y, int z);
void set_light(int p, int q, int x, int y, int z, int w);
void _set_block(int p, int q, int x, int y, int z, int w, int dirty);
void set_block(int x, int y, int z, int w);
void record_block(int x, int y, int z, int w);
int get_block(int x, int y, int z);
void builder_block(int x, int y, int z, int w);
void copy();
void paste();
void array(Block *b1, Block *b2, int xc, int yc, int zc);
void cube(Block *b1, Block *b2, int fill);
void sphere(Block *center, int radius, int fill, int fx, int fy, int fz);
void cylinder(Block *b1, Block *b2, int radius, int fill);
void tree(Block *block);

#endif