#include <pebble.h>

static Window *s_main_window;
static TextLayer *s_time_layer;
static TextLayer *s_date_layer;

static GDrawCommandImage *s_image;
static Layer *s_pdc_layer;

static const uint32_t FRAME_IDS[] = {
  RESOURCE_ID_FRAME_000, RESOURCE_ID_FRAME_001, RESOURCE_ID_FRAME_002, RESOURCE_ID_FRAME_003, RESOURCE_ID_FRAME_004, RESOURCE_ID_FRAME_005,
  RESOURCE_ID_FRAME_006, RESOURCE_ID_FRAME_007, RESOURCE_ID_FRAME_008, RESOURCE_ID_FRAME_009, RESOURCE_ID_FRAME_010, RESOURCE_ID_FRAME_011,
  RESOURCE_ID_FRAME_012, RESOURCE_ID_FRAME_013, RESOURCE_ID_FRAME_014, RESOURCE_ID_FRAME_015, RESOURCE_ID_FRAME_016, RESOURCE_ID_FRAME_017,
  RESOURCE_ID_FRAME_018, RESOURCE_ID_FRAME_019, RESOURCE_ID_FRAME_020, RESOURCE_ID_FRAME_021, RESOURCE_ID_FRAME_022, RESOURCE_ID_FRAME_023,
  RESOURCE_ID_FRAME_024, RESOURCE_ID_FRAME_025, RESOURCE_ID_FRAME_026, RESOURCE_ID_FRAME_027, RESOURCE_ID_FRAME_028, RESOURCE_ID_FRAME_029,
  RESOURCE_ID_FRAME_030, RESOURCE_ID_FRAME_031, RESOURCE_ID_FRAME_032, RESOURCE_ID_FRAME_033, RESOURCE_ID_FRAME_034, RESOURCE_ID_FRAME_035,
  RESOURCE_ID_FRAME_036, RESOURCE_ID_FRAME_037, RESOURCE_ID_FRAME_038, RESOURCE_ID_FRAME_039, RESOURCE_ID_FRAME_040, RESOURCE_ID_FRAME_041,
  RESOURCE_ID_FRAME_042, RESOURCE_ID_FRAME_043, RESOURCE_ID_FRAME_044, RESOURCE_ID_FRAME_045, RESOURCE_ID_FRAME_046, RESOURCE_ID_FRAME_047,
  RESOURCE_ID_FRAME_048, RESOURCE_ID_FRAME_049, RESOURCE_ID_FRAME_050, RESOURCE_ID_FRAME_051, RESOURCE_ID_FRAME_052, RESOURCE_ID_FRAME_053,
  RESOURCE_ID_FRAME_054, RESOURCE_ID_FRAME_055, RESOURCE_ID_FRAME_056, RESOURCE_ID_FRAME_057, RESOURCE_ID_FRAME_058, RESOURCE_ID_FRAME_059,
  RESOURCE_ID_FRAME_060, RESOURCE_ID_FRAME_061, RESOURCE_ID_FRAME_062, RESOURCE_ID_FRAME_063, RESOURCE_ID_FRAME_064, RESOURCE_ID_FRAME_065,
  RESOURCE_ID_FRAME_066, RESOURCE_ID_FRAME_067, RESOURCE_ID_FRAME_068, RESOURCE_ID_FRAME_069, RESOURCE_ID_FRAME_070, RESOURCE_ID_FRAME_071,
  RESOURCE_ID_FRAME_072, RESOURCE_ID_FRAME_073, RESOURCE_ID_FRAME_074, RESOURCE_ID_FRAME_075, RESOURCE_ID_FRAME_076, RESOURCE_ID_FRAME_077,
  RESOURCE_ID_FRAME_078, RESOURCE_ID_FRAME_079, RESOURCE_ID_FRAME_080, RESOURCE_ID_FRAME_081, RESOURCE_ID_FRAME_082, RESOURCE_ID_FRAME_083,
  RESOURCE_ID_FRAME_084, RESOURCE_ID_FRAME_085, RESOURCE_ID_FRAME_086, RESOURCE_ID_FRAME_087, RESOURCE_ID_FRAME_088, RESOURCE_ID_FRAME_089,
  RESOURCE_ID_FRAME_090, RESOURCE_ID_FRAME_091, RESOURCE_ID_FRAME_092, RESOURCE_ID_FRAME_093, RESOURCE_ID_FRAME_094, RESOURCE_ID_FRAME_095,
  RESOURCE_ID_FRAME_096, RESOURCE_ID_FRAME_097, RESOURCE_ID_FRAME_098, RESOURCE_ID_FRAME_099, RESOURCE_ID_FRAME_100, RESOURCE_ID_FRAME_101,
  RESOURCE_ID_FRAME_102, RESOURCE_ID_FRAME_103, RESOURCE_ID_FRAME_104, RESOURCE_ID_FRAME_105, RESOURCE_ID_FRAME_106, RESOURCE_ID_FRAME_107,
  RESOURCE_ID_FRAME_108, RESOURCE_ID_FRAME_109, RESOURCE_ID_FRAME_110, RESOURCE_ID_FRAME_111, RESOURCE_ID_FRAME_112, RESOURCE_ID_FRAME_113,
  RESOURCE_ID_FRAME_114, RESOURCE_ID_FRAME_115, RESOURCE_ID_FRAME_116, RESOURCE_ID_FRAME_117, RESOURCE_ID_FRAME_118, RESOURCE_ID_FRAME_119,
  RESOURCE_ID_FRAME_120, RESOURCE_ID_FRAME_121, RESOURCE_ID_FRAME_122, RESOURCE_ID_FRAME_123, RESOURCE_ID_FRAME_124, RESOURCE_ID_FRAME_125,
  RESOURCE_ID_FRAME_126, RESOURCE_ID_FRAME_127, RESOURCE_ID_FRAME_128, RESOURCE_ID_FRAME_129, RESOURCE_ID_FRAME_130, RESOURCE_ID_FRAME_131,
  RESOURCE_ID_FRAME_132, RESOURCE_ID_FRAME_133, RESOURCE_ID_FRAME_134, RESOURCE_ID_FRAME_135, RESOURCE_ID_FRAME_136, RESOURCE_ID_FRAME_137,
  RESOURCE_ID_FRAME_138, RESOURCE_ID_FRAME_139, RESOURCE_ID_FRAME_140, RESOURCE_ID_FRAME_141, RESOURCE_ID_FRAME_142, RESOURCE_ID_FRAME_143,
  RESOURCE_ID_FRAME_144, RESOURCE_ID_FRAME_145, RESOURCE_ID_FRAME_146, RESOURCE_ID_FRAME_147, RESOURCE_ID_FRAME_148, RESOURCE_ID_FRAME_149,
  RESOURCE_ID_FRAME_150, RESOURCE_ID_FRAME_151, RESOURCE_ID_FRAME_152, RESOURCE_ID_FRAME_153, RESOURCE_ID_FRAME_154, RESOURCE_ID_FRAME_155,
  RESOURCE_ID_FRAME_156, RESOURCE_ID_FRAME_157, RESOURCE_ID_FRAME_158, RESOURCE_ID_FRAME_159, RESOURCE_ID_FRAME_160, RESOURCE_ID_FRAME_161,
  RESOURCE_ID_FRAME_162, RESOURCE_ID_FRAME_163, RESOURCE_ID_FRAME_164, RESOURCE_ID_FRAME_165, RESOURCE_ID_FRAME_166, RESOURCE_ID_FRAME_167,
  RESOURCE_ID_FRAME_168, RESOURCE_ID_FRAME_169, RESOURCE_ID_FRAME_170, RESOURCE_ID_FRAME_171, RESOURCE_ID_FRAME_172, RESOURCE_ID_FRAME_173,
  RESOURCE_ID_FRAME_174, RESOURCE_ID_FRAME_175, RESOURCE_ID_FRAME_176, RESOURCE_ID_FRAME_177, RESOURCE_ID_FRAME_178, RESOURCE_ID_FRAME_179,
  RESOURCE_ID_FRAME_180, RESOURCE_ID_FRAME_181, RESOURCE_ID_FRAME_182, RESOURCE_ID_FRAME_183, RESOURCE_ID_FRAME_184, RESOURCE_ID_FRAME_185,
  RESOURCE_ID_FRAME_186, RESOURCE_ID_FRAME_187, RESOURCE_ID_FRAME_188, RESOURCE_ID_FRAME_189, RESOURCE_ID_FRAME_190, RESOURCE_ID_FRAME_191,
  RESOURCE_ID_FRAME_192, RESOURCE_ID_FRAME_193, RESOURCE_ID_FRAME_194, RESOURCE_ID_FRAME_195,
};
#define NUM_FRAMES (sizeof(FRAME_IDS)/sizeof(FRAME_IDS[0]))
static int s_frame = 0;
static AppTimer *s_anim_timer;

static void anim_timer_callback(void *data) {
  gdraw_command_image_destroy(s_image);
  s_frame = (s_frame + 1) % NUM_FRAMES;
  s_image = gdraw_command_image_create_with_resource(FRAME_IDS[s_frame]);
  layer_mark_dirty(s_pdc_layer);
  s_anim_timer = app_timer_register(100, anim_timer_callback, NULL);
}

static void pdc_update_proc(Layer *layer, GContext *ctx) {
  gdraw_command_image_draw(ctx, s_image, GPoint(0, 0));
}

static void update_time() {
  time_t temp = time(NULL);
  struct tm *tick_time = localtime(&temp);

  static char s_time_buffer[8];
  strftime(s_time_buffer, sizeof(s_time_buffer), clock_is_24h_style() ?
                                                    "%H:%M" : "%I:%M", tick_time);
  text_layer_set_text(s_time_layer, s_time_buffer);

  static char s_date_buffer[16];
  strftime(s_date_buffer, sizeof(s_date_buffer), "%a %b %d", tick_time);
  text_layer_set_text(s_date_layer, s_date_buffer);
}

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  update_time();
}

static void main_window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  s_time_layer = text_layer_create(
      GRect(0, PBL_IF_ROUND_ELSE(58, 52), bounds.size.w, 50));
  text_layer_set_background_color(s_time_layer, GColorClear);
  text_layer_set_text_color(s_time_layer, GColorWhite);
  text_layer_set_font(s_time_layer, fonts_get_system_font(FONT_KEY_BITHAM_42_BOLD));
  text_layer_set_text_alignment(s_time_layer, GTextAlignmentCenter);

  s_date_layer = text_layer_create(
      GRect(0, PBL_IF_ROUND_ELSE(110, 104), bounds.size.w, 30));
  text_layer_set_background_color(s_date_layer, GColorClear);
  text_layer_set_text_color(s_date_layer, GColorWhite);
  text_layer_set_font(s_date_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
  text_layer_set_text_alignment(s_date_layer, GTextAlignmentCenter);

  layer_add_child(window_layer, text_layer_get_layer(s_time_layer));
  layer_add_child(window_layer, text_layer_get_layer(s_date_layer));

  s_image = gdraw_command_image_create_with_resource(FRAME_IDS[0]);
  s_pdc_layer = layer_create(bounds);
  layer_set_update_proc(s_pdc_layer, pdc_update_proc);
  layer_add_child(window_layer, s_pdc_layer);
  s_anim_timer = app_timer_register(100, anim_timer_callback, NULL);
}

static void main_window_unload(Window *window) {
  text_layer_destroy(s_time_layer);
  text_layer_destroy(s_date_layer);
  layer_destroy(s_pdc_layer);
  gdraw_command_image_destroy(s_image);
  app_timer_cancel(s_anim_timer);
}

static void init() {
  s_main_window = window_create();
  window_set_background_color(s_main_window, GColorVeryLightBlue);

  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload
  });

  window_stack_push(s_main_window, true);
  update_time();
  tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
}

static void deinit() {
  window_destroy(s_main_window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}
