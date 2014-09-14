#include "face.h"
#include <pebble.h>

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static GBitmap *s_res_face_bg;
static GFont s_res_gothic_14;
static GFont s_res_bitham_34_medium_numbers;
static BitmapLayer *s_bitmaplayer_bg;
static Layer *s_layer_battery;
static TextLayer *s_textlayer_date;
static TextLayer *s_textlayer_time;
static int battery_level;

void show_time(char *time){
	text_layer_set_text(s_textlayer_time, time);
}

void show_date(char *date){
	text_layer_set_text(s_textlayer_date, date);
}

void battery_layer_update_callback(Layer *me, GContext* ctx){
	graphics_context_set_fill_color(ctx, GColorWhite);
	graphics_fill_rect(ctx, GRect(0, 1, 65-(int)((battery_level/100.0)*65.0), 5), 0, GCornerNone);
}

void update_battery(int level){
	battery_level = level;
	layer_mark_dirty(s_layer_battery);
}

static void initialise_ui(void) {
  s_window = window_create();
  window_set_background_color(s_window, GColorBlack);
  window_set_fullscreen(s_window, 1);
  
  s_res_face_bg = gbitmap_create_with_resource(RESOURCE_ID_face_bg);
  s_res_gothic_14 = fonts_get_system_font(FONT_KEY_GOTHIC_14);
  s_res_bitham_34_medium_numbers = fonts_get_system_font(FONT_KEY_BITHAM_34_MEDIUM_NUMBERS);
  // s_bitmaplayer_bg
  s_bitmaplayer_bg = bitmap_layer_create(GRect(0, 0, 144, 168));
  bitmap_layer_set_bitmap(s_bitmaplayer_bg, s_res_face_bg);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_bitmaplayer_bg);
  
  // s_layer_battery
  s_layer_battery = layer_create(GRect(40, 135, 65, 7));
	layer_set_update_proc(s_layer_battery, battery_layer_update_callback);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_layer_battery);
  
  // s_textlayer_date
  s_textlayer_date = text_layer_create(GRect(4, 149, 140, 14));
  text_layer_set_background_color(s_textlayer_date, GColorClear);
  //text_layer_set_text(s_textlayer_date, "");
  text_layer_set_text_alignment(s_textlayer_date, GTextAlignmentCenter);
  text_layer_set_font(s_textlayer_date, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_date);
  
  // s_textlayer_time
  s_textlayer_time = text_layer_create(GRect(25, 65, 94, 34));
  text_layer_set_background_color(s_textlayer_time, GColorClear);
  text_layer_set_text_color(s_textlayer_time, GColorWhite);
  //text_layer_set_text(s_textlayer_time, "");
  text_layer_set_text_alignment(s_textlayer_time, GTextAlignmentCenter);
  text_layer_set_font(s_textlayer_time, s_res_bitham_34_medium_numbers);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_time);
}

static void destroy_ui(void) {
  window_destroy(s_window);
  bitmap_layer_destroy(s_bitmaplayer_bg);
  layer_destroy(s_layer_battery);
  text_layer_destroy(s_textlayer_date);
  text_layer_destroy(s_textlayer_time);
  gbitmap_destroy(s_res_face_bg);
}
// END AUTO-GENERATED UI CODE

static void handle_window_unload(Window* window) {
  destroy_ui();
}

void show_face(void) {
  initialise_ui();
  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
  window_stack_push(s_window, true);
}

void hide_face(void) {
  window_stack_remove(s_window, true);
}