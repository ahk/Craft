#ifndef _game_h_
#define _game_h_
#include "craft.h"

float time_of_day();
float get_daylight();
int get_scale_factor();
void get_sight_vector(float rx, float ry, float *vx, float *vy, float *vz);
void get_motion_vector(int flying, int sz, int sx, float rx, float ry, float *vx, float *vy, float *vz);
void add_message(const char *text);
void login();
void parse_command(const char *buffer, int forward);
void on_light();
void on_left_click();
void on_right_click();
void on_middle_click();
void on_key(GLFWwindow *window, int key, int scancode, int action, int mods);
void on_char(GLFWwindow *window, unsigned int u);
void on_scroll(GLFWwindow *window, double xdelta, double ydelta);
void on_mouse_button(GLFWwindow *window, int button, int action, int mods);
void create_window();
void handle_mouse_input();
void handle_movement(double dt);
void parse_buffer(char *buffer);
void reset_model();

#endif