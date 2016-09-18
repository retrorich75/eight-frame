#include <main.h>
#include <math.h>
#include <pebble.h>

// Information received from AppMessage
void inbox_received_callback(DictionaryIterator *iterator, void *context) {

  /*This AppMessage callback function has two sections. The first section saves
     settings data sent from the Clay-generated configuration page in the Pebble
     app to persistent storage, reads the values from storage, and then applies
     them to the watch face. Each complication has settings for text color,
     background color, and complication.

     The second section retrieves weather complication information from Dark
     Sky, writes it to storage, and then reads it into buffers for display on
     the watch face.*/

  // Read tuples containing settings data
  Tuple *time_text_tuple = dict_find(iterator, MESSAGE_KEY_TIME_TEXT_COLOR);
  Tuple *time_background_tuple =
      dict_find(iterator, MESSAGE_KEY_TIME_BACKGROUND_COLOR);

  Tuple *text1_tuple = dict_find(iterator, MESSAGE_KEY_TEXT_COLOR_ONE);
  Tuple *background1_tuple =
      dict_find(iterator, MESSAGE_KEY_BACKGROUND_COLOR_ONE);
  Tuple *complication1_tuple =
      dict_find(iterator, MESSAGE_KEY_COMPLICATION_ONE);

  Tuple *text2_tuple = dict_find(iterator, MESSAGE_KEY_TEXT_COLOR_TWO);
  Tuple *background2_tuple =
      dict_find(iterator, MESSAGE_KEY_BACKGROUND_COLOR_TWO);
  Tuple *complication2_tuple =
      dict_find(iterator, MESSAGE_KEY_COMPLICATION_TWO);

  Tuple *text3_tuple = dict_find(iterator, MESSAGE_KEY_TEXT_COLOR_THREE);
  Tuple *background3_tuple =
      dict_find(iterator, MESSAGE_KEY_BACKGROUND_COLOR_THREE);
  Tuple *complication3_tuple =
      dict_find(iterator, MESSAGE_KEY_COMPLICATION_THREE);

  Tuple *text4_tuple = dict_find(iterator, MESSAGE_KEY_TEXT_COLOR_FOUR);
  Tuple *background4_tuple =
      dict_find(iterator, MESSAGE_KEY_BACKGROUND_COLOR_FOUR);
  Tuple *complication4_tuple =
      dict_find(iterator, MESSAGE_KEY_COMPLICATION_FOUR);

  Tuple *text5_tuple = dict_find(iterator, MESSAGE_KEY_TEXT_COLOR_FIVE);
  Tuple *background5_tuple =
      dict_find(iterator, MESSAGE_KEY_BACKGROUND_COLOR_FIVE);
  Tuple *complication5_tuple =
      dict_find(iterator, MESSAGE_KEY_COMPLICATION_FIVE);

  Tuple *text6_tuple = dict_find(iterator, MESSAGE_KEY_TEXT_COLOR_SIX);
  Tuple *background6_tuple =
      dict_find(iterator, MESSAGE_KEY_BACKGROUND_COLOR_SIX);
  Tuple *complication6_tuple =
      dict_find(iterator, MESSAGE_KEY_COMPLICATION_SIX);

  Tuple *text7_tuple = dict_find(iterator, MESSAGE_KEY_TEXT_COLOR_SEVEN);
  Tuple *background7_tuple =
      dict_find(iterator, MESSAGE_KEY_BACKGROUND_COLOR_SEVEN);
  Tuple *complication7_tuple =
      dict_find(iterator, MESSAGE_KEY_COMPLICATION_SEVEN);

  Tuple *text8_tuple = dict_find(iterator, MESSAGE_KEY_TEXT_COLOR_EIGHT);
  Tuple *background8_tuple =
      dict_find(iterator, MESSAGE_KEY_BACKGROUND_COLOR_EIGHT);
  Tuple *complication8_tuple =
      dict_find(iterator, MESSAGE_KEY_COMPLICATION_EIGHT);

  /* Colors are written as an int value, read, converted to a GColor, and then
     applied. Fonts are set here rather than somewhere else because the
     Conditions complication uses a dingbat icon font to display the current
     conditions.*/
  if (time_text_tuple) {
    persist_write_int(key_time_text, time_text_tuple->value->int32);
    time_text_int = persist_read_int(key_time_text);
    time_text = GColorFromHEX(time_text_int);
    text_layer_set_text_color(s_time_layer, time_text);
  }
  if (time_background_tuple) {
    persist_write_int(key_time_background, time_background_tuple->value->int32);
    time_background_int = persist_read_int(key_time_background);
    time_background = GColorFromHEX(time_background_int);
    text_layer_set_background_color(s_time_layer, time_background);
    window_set_background_color(s_main_window,
                                PBL_IF_RECT_ELSE(GColorWhite, time_background));
  }

  if (text1_tuple) {
    persist_write_int(key_text1, text1_tuple->value->int32);
    text1_int = persist_read_int(key_text1);
    text1 = GColorFromHEX(text1_int);
    text_layer_set_text_color(s_complication_layer_one, text1);
  }
  if (background1_tuple) {
    persist_write_int(key_background1, background1_tuple->value->int32);
    background1_int = persist_read_int(key_background1);
    background1 = GColorFromHEX(background1_int);
    text_layer_set_background_color(s_complication_layer_one, background1);
  }
  if (complication1_tuple) {
    persist_write_int(key_complication1,
                      atoi(complication1_tuple->value->cstring));
    complication1_int = persist_read_int(key_complication1);
    switch (complication1_int) {
    case 0:
      text_layer_set_text(s_complication_layer_one, "");
      break;
    case 1:
      text_layer_set_font(s_complication_layer_one, s_complication_font);
      text_layer_set_text(s_complication_layer_one, s_date_buffer);
      break;
    case 2:
      text_layer_set_font(s_complication_layer_one, s_complication_font);
      text_layer_set_text(s_complication_layer_one, s_battery_buffer);
      break;
    case 3:
      text_layer_set_font(s_complication_layer_one, s_complication_font);
      text_layer_set_text(s_complication_layer_one, temperature_buffer);
      break;
    case 4:
      text_layer_set_font(s_complication_layer_one, s_complication_font);
      text_layer_set_text(s_complication_layer_one, max_min_buffer);
      break;
    case 5:
      text_layer_set_font(s_complication_layer_one, s_icon_font);
      text_layer_set_text(s_complication_layer_one, weather_icon_buffer);
      break;
    case 6:
      text_layer_set_font(s_complication_layer_one, s_complication_font);
      text_layer_set_text(s_complication_layer_one, wind_buffer);
      break;
    case 7:
      text_layer_set_font(s_complication_layer_one, s_complication_font);
      text_layer_set_text(s_complication_layer_one, precip_buffer);
      break;
    case 8:
      text_layer_set_font(s_complication_layer_one, s_complication_font);
      text_layer_set_text(s_complication_layer_one, s_step_buffer);
      break;
    case 9:
      text_layer_set_font(s_complication_layer_one, s_complication_font);
      text_layer_set_text(s_complication_layer_one, distance_walked_buffer);
      break;
    case 10:
      text_layer_set_font(s_complication_layer_one, s_complication_font);
      text_layer_set_text(s_complication_layer_one, calories_active_buffer);
    }
  }

  if (text2_tuple) {
    persist_write_int(key_text2, text2_tuple->value->int32);
    text2_int = persist_read_int(key_text2);
    text2 = GColorFromHEX(text2_int);
    text_layer_set_text_color(s_complication_layer_two, text2);
  }
  if (background2_tuple) {
    persist_write_int(key_background2, background2_tuple->value->int32);
    background2_int = persist_read_int(key_background2);
    background2 = GColorFromHEX(background2_int);
    text_layer_set_background_color(s_complication_layer_two, background2);
  }
  if (complication2_tuple) {
    persist_write_int(key_complication2,
                      atoi(complication2_tuple->value->cstring));
    complication2_int = persist_read_int(key_complication2);
    switch (complication2_int) {
    case 0:
      text_layer_set_text(s_complication_layer_two, "");
      break;
    case 1:
      text_layer_set_font(s_complication_layer_two, s_complication_font);
      text_layer_set_text(s_complication_layer_two, s_date_buffer);
      break;
    case 2:
      text_layer_set_font(s_complication_layer_two, s_complication_font);
      text_layer_set_text(s_complication_layer_two, s_battery_buffer);
      break;
    case 3:
      text_layer_set_font(s_complication_layer_two, s_complication_font);
      text_layer_set_text(s_complication_layer_two, temperature_buffer);
      break;
    case 4:
      text_layer_set_font(s_complication_layer_two, s_complication_font);
      text_layer_set_text(s_complication_layer_two, max_min_buffer);
      break;
    case 5:
      text_layer_set_font(s_complication_layer_two, s_icon_font);
      text_layer_set_text(s_complication_layer_two, weather_icon_buffer);
      break;
    case 6:
      text_layer_set_font(s_complication_layer_two, s_complication_font);
      text_layer_set_text(s_complication_layer_two, wind_buffer);
      break;
    case 7:
      text_layer_set_font(s_complication_layer_two, s_complication_font);
      text_layer_set_text(s_complication_layer_two, precip_buffer);
      break;
    case 8:
      text_layer_set_font(s_complication_layer_two, s_complication_font);
      text_layer_set_text(s_complication_layer_two, s_step_buffer);
      break;
    case 9:
      text_layer_set_font(s_complication_layer_two, s_complication_font);
      text_layer_set_text(s_complication_layer_two, distance_walked_buffer);
      break;
    case 10:
      text_layer_set_font(s_complication_layer_two, s_complication_font);
      text_layer_set_text(s_complication_layer_two, calories_active_buffer);
    }
  }

  if (text3_tuple) {
    persist_write_int(key_text3, text3_tuple->value->int32);
    text3_int = persist_read_int(key_text3);
    text3 = GColorFromHEX(text3_int);
    text_layer_set_text_color(s_complication_layer_three, text3);
  }
  if (background3_tuple) {
    persist_write_int(key_background3, background3_tuple->value->int32);
    background3_int = persist_read_int(key_background3);
    background3 = GColorFromHEX(background3_int);
    text_layer_set_background_color(s_complication_layer_three, background3);
  }
  if (complication3_tuple) {
    persist_write_int(key_complication3,
                      atoi(complication3_tuple->value->cstring));
    complication3_int = persist_read_int(key_complication3);
    switch (complication3_int) {
    case 0:
      text_layer_set_text(s_complication_layer_three, "");
      break;
    case 1:
      text_layer_set_font(s_complication_layer_three, s_complication_font);
      text_layer_set_text(s_complication_layer_three, s_date_buffer);
      break;
    case 2:
      text_layer_set_font(s_complication_layer_three, s_complication_font);
      text_layer_set_text(s_complication_layer_three, s_battery_buffer);
      break;
    case 3:
      text_layer_set_font(s_complication_layer_three, s_complication_font);
      text_layer_set_text(s_complication_layer_three, temperature_buffer);
      break;
    case 4:
      text_layer_set_font(s_complication_layer_three, s_complication_font);
      text_layer_set_text(s_complication_layer_three, max_min_buffer);
      break;
    case 5:
      text_layer_set_font(s_complication_layer_three, s_icon_font);
      text_layer_set_text(s_complication_layer_three, weather_icon_buffer);
      break;
    case 6:
      text_layer_set_font(s_complication_layer_three, s_complication_font);
      text_layer_set_text(s_complication_layer_three, wind_buffer);
      break;
    case 7:
      text_layer_set_font(s_complication_layer_three, s_complication_font);
      text_layer_set_text(s_complication_layer_three, precip_buffer);
      break;
    case 8:
      text_layer_set_font(s_complication_layer_three, s_complication_font);
      text_layer_set_text(s_complication_layer_three, s_step_buffer);
      break;
    case 9:
      text_layer_set_font(s_complication_layer_three, s_complication_font);
      text_layer_set_text(s_complication_layer_three, distance_walked_buffer);
      break;
    case 10:
      text_layer_set_font(s_complication_layer_three, s_complication_font);
      text_layer_set_text(s_complication_layer_three, calories_active_buffer);
    }
  }

  if (text4_tuple) {
    persist_write_int(key_text4, text4_tuple->value->int32);
    text4_int = persist_read_int(key_text4);
    text4 = GColorFromHEX(text4_int);
    text_layer_set_text_color(s_complication_layer_four, text4);
  }
  if (background4_tuple) {
    persist_write_int(key_background4, background4_tuple->value->int32);
    background4_int = persist_read_int(key_background4);
    background4 = GColorFromHEX(background4_int);
    text_layer_set_background_color(s_complication_layer_four, background4);
  }
  if (complication4_tuple) {
    persist_write_int(key_complication4,
                      atoi(complication4_tuple->value->cstring));
    complication4_int = persist_read_int(key_complication4);
    switch (complication4_int) {
    case 0:
      text_layer_set_text(s_complication_layer_four, "");
      break;
    case 1:
      text_layer_set_font(s_complication_layer_four, s_complication_font);
      text_layer_set_text(s_complication_layer_four, s_date_buffer);
      break;
    case 2:
      text_layer_set_font(s_complication_layer_four, s_complication_font);
      text_layer_set_text(s_complication_layer_four, s_battery_buffer);
      break;
    case 3:
      text_layer_set_font(s_complication_layer_four, s_complication_font);
      text_layer_set_text(s_complication_layer_four, temperature_buffer);
      break;
    case 4:
      text_layer_set_font(s_complication_layer_four, s_complication_font);
      text_layer_set_text(s_complication_layer_four, max_min_buffer);
      break;
    case 5:
      text_layer_set_font(s_complication_layer_four, s_icon_font);
      text_layer_set_text(s_complication_layer_four, weather_icon_buffer);
      break;
    case 6:
      text_layer_set_font(s_complication_layer_four, s_complication_font);
      text_layer_set_text(s_complication_layer_four, wind_buffer);
      break;
    case 7:
      text_layer_set_font(s_complication_layer_four, s_complication_font);
      text_layer_set_text(s_complication_layer_four, precip_buffer);
      break;
    case 8:
      text_layer_set_font(s_complication_layer_four, s_complication_font);
      text_layer_set_text(s_complication_layer_four, s_step_buffer);
      break;
    case 9:
      text_layer_set_font(s_complication_layer_four, s_complication_font);
      text_layer_set_text(s_complication_layer_four, distance_walked_buffer);
      break;
    case 10:
      text_layer_set_font(s_complication_layer_four, s_complication_font);
      text_layer_set_text(s_complication_layer_four, calories_active_buffer);
    }
  }

  if (text5_tuple) {
    persist_write_int(key_text5, text5_tuple->value->int32);
    text5_int = persist_read_int(key_text5);
    text5 = GColorFromHEX(text5_int);
    text_layer_set_text_color(s_complication_layer_five, text5);
  }
  if (background5_tuple) {
    persist_write_int(key_background5, background5_tuple->value->int32);
    background5_int = persist_read_int(key_background5);
    background5 = GColorFromHEX(background5_int);
    text_layer_set_background_color(s_complication_layer_five, background5);
  }
  if (complication5_tuple) {
    persist_write_int(key_complication5,
                      atoi(complication5_tuple->value->cstring));
    complication5_int = persist_read_int(key_complication5);
    switch (complication5_int) {
    case 0:
      text_layer_set_text(s_complication_layer_five, "");
      break;
    case 1:
      text_layer_set_font(s_complication_layer_five, s_complication_font);
      text_layer_set_text(s_complication_layer_five, s_date_buffer);
      break;
    case 2:
      text_layer_set_font(s_complication_layer_five, s_complication_font);
      text_layer_set_text(s_complication_layer_five, s_battery_buffer);
      break;
    case 3:
      text_layer_set_font(s_complication_layer_five, s_complication_font);
      text_layer_set_text(s_complication_layer_five, temperature_buffer);
      break;
    case 4:
      text_layer_set_font(s_complication_layer_five, s_complication_font);
      text_layer_set_text(s_complication_layer_five, max_min_buffer);
      break;
    case 5:
      text_layer_set_font(s_complication_layer_five, s_icon_font);
      text_layer_set_text(s_complication_layer_five, weather_icon_buffer);
      break;
    case 6:
      text_layer_set_font(s_complication_layer_five, s_complication_font);
      text_layer_set_text(s_complication_layer_five, wind_buffer);
      break;
    case 7:
      text_layer_set_font(s_complication_layer_five, s_complication_font);
      text_layer_set_text(s_complication_layer_five, precip_buffer);
      break;
    case 8:
      text_layer_set_font(s_complication_layer_five, s_complication_font);
      text_layer_set_text(s_complication_layer_five, s_step_buffer);
      break;
    case 9:
      text_layer_set_font(s_complication_layer_five, s_complication_font);
      text_layer_set_text(s_complication_layer_five, distance_walked_buffer);
      break;
    case 10:
      text_layer_set_font(s_complication_layer_five, s_complication_font);
      text_layer_set_text(s_complication_layer_five, calories_active_buffer);
    }
  }

  if (text6_tuple) {
    persist_write_int(key_text6, text6_tuple->value->int32);
    text6_int = persist_read_int(key_text6);
    text6 = GColorFromHEX(text6_int);
    text_layer_set_text_color(s_complication_layer_six, text6);
  }
  if (background6_tuple) {
    persist_write_int(key_background6, background6_tuple->value->int32);
    background6_int = persist_read_int(key_background6);
    background6 = GColorFromHEX(background6_int);
    text_layer_set_background_color(s_complication_layer_six, background6);
  }
  if (complication6_tuple) {
    persist_write_int(key_complication6,
                      atoi(complication6_tuple->value->cstring));
    complication6_int = persist_read_int(key_complication6);
    switch (complication6_int) {
    case 0:
      text_layer_set_text(s_complication_layer_six, "");
      break;
    case 1:
      text_layer_set_font(s_complication_layer_six, s_complication_font);
      text_layer_set_text(s_complication_layer_six, s_date_buffer);
      break;
    case 2:
      text_layer_set_font(s_complication_layer_six, s_complication_font);
      text_layer_set_text(s_complication_layer_six, s_battery_buffer);
      break;
    case 3:
      text_layer_set_font(s_complication_layer_six, s_complication_font);
      text_layer_set_text(s_complication_layer_six, temperature_buffer);
      break;
    case 4:
      text_layer_set_font(s_complication_layer_six, s_complication_font);
      text_layer_set_text(s_complication_layer_six, max_min_buffer);
      break;
    case 5:
      text_layer_set_font(s_complication_layer_six, s_icon_font);
      text_layer_set_text(s_complication_layer_six, weather_icon_buffer);
      break;
    case 6:
      text_layer_set_font(s_complication_layer_six, s_complication_font);
      text_layer_set_text(s_complication_layer_six, wind_buffer);
      break;
    case 7:
      text_layer_set_font(s_complication_layer_six, s_complication_font);
      text_layer_set_text(s_complication_layer_six, precip_buffer);
      break;
    case 8:
      text_layer_set_font(s_complication_layer_six, s_complication_font);
      text_layer_set_text(s_complication_layer_six, s_step_buffer);
      break;
    case 9:
      text_layer_set_font(s_complication_layer_six, s_complication_font);
      text_layer_set_text(s_complication_layer_six, distance_walked_buffer);
      break;
    case 10:
      text_layer_set_font(s_complication_layer_six, s_complication_font);
      text_layer_set_text(s_complication_layer_six, calories_active_buffer);
    }
  }

  if (text7_tuple) {
    persist_write_int(key_text7, text7_tuple->value->int32);
    text7_int = persist_read_int(key_text7);
    text7 = GColorFromHEX(text7_int);
    text_layer_set_text_color(s_complication_layer_seven, text7);
  }
  if (background7_tuple) {
    persist_write_int(key_background7, background7_tuple->value->int32);
    background7_int = persist_read_int(key_background7);
    background7 = GColorFromHEX(background7_int);
    text_layer_set_background_color(s_complication_layer_seven, background7);
  }
  if (complication7_tuple) {
    persist_write_int(key_complication7,
                      atoi(complication7_tuple->value->cstring));
    complication7_int = persist_read_int(key_complication7);
    switch (complication7_int) {
    case 0:
      text_layer_set_text(s_complication_layer_seven, "");
      break;
    case 1:
      text_layer_set_font(s_complication_layer_seven, s_complication_font);
      text_layer_set_text(s_complication_layer_seven, s_date_buffer);
      break;
    case 2:
      text_layer_set_font(s_complication_layer_seven, s_complication_font);
      text_layer_set_text(s_complication_layer_seven, s_battery_buffer);
      break;
    case 3:
      text_layer_set_font(s_complication_layer_seven, s_complication_font);
      text_layer_set_text(s_complication_layer_seven, temperature_buffer);
      break;
    case 4:
      text_layer_set_font(s_complication_layer_seven, s_complication_font);
      text_layer_set_text(s_complication_layer_seven, max_min_buffer);
      break;
    case 5:
      text_layer_set_font(s_complication_layer_seven, s_icon_font);
      text_layer_set_text(s_complication_layer_seven, weather_icon_buffer);
      break;
    case 6:
      text_layer_set_font(s_complication_layer_seven, s_complication_font);
      text_layer_set_text(s_complication_layer_seven, wind_buffer);
      break;
    case 7:
      text_layer_set_font(s_complication_layer_seven, s_complication_font);
      text_layer_set_text(s_complication_layer_seven, precip_buffer);
      break;
    case 8:
      text_layer_set_font(s_complication_layer_seven, s_complication_font);
      text_layer_set_text(s_complication_layer_seven, s_step_buffer);
      break;
    case 9:
      text_layer_set_font(s_complication_layer_seven, s_complication_font);
      text_layer_set_text(s_complication_layer_seven, distance_walked_buffer);
      break;
    case 10:
      text_layer_set_font(s_complication_layer_seven, s_complication_font);
      text_layer_set_text(s_complication_layer_seven, calories_active_buffer);
    }
  }

  if (text8_tuple) {
    persist_write_int(key_text8, text8_tuple->value->int32);
    text8_int = persist_read_int(key_text8);
    text8 = GColorFromHEX(text8_int);
    text_layer_set_text_color(s_complication_layer_eight, text8);
  }
  if (background8_tuple) {
    persist_write_int(key_background8, background8_tuple->value->int32);
    background8_int = persist_read_int(key_background8);
    background8 = GColorFromHEX(background8_int);
    text_layer_set_background_color(s_complication_layer_eight, background8);
  }
  if (complication8_tuple) {
    persist_write_int(key_complication8,
                      atoi(complication8_tuple->value->cstring));
    complication8_int = persist_read_int(key_complication8);
    switch (complication8_int) {
    case 0:
      text_layer_set_text(s_complication_layer_eight, "");
      break;
    case 1:
      text_layer_set_font(s_complication_layer_eight, s_complication_font);
      text_layer_set_text(s_complication_layer_eight, s_date_buffer);
      break;
    case 2:
      text_layer_set_font(s_complication_layer_eight, s_complication_font);
      text_layer_set_text(s_complication_layer_eight, s_battery_buffer);
      break;
    case 3:
      text_layer_set_font(s_complication_layer_eight, s_complication_font);
      text_layer_set_text(s_complication_layer_eight, temperature_buffer);
      break;
    case 4:
      text_layer_set_font(s_complication_layer_eight, s_complication_font);
      text_layer_set_text(s_complication_layer_eight, max_min_buffer);
      break;
    case 5:
      text_layer_set_font(s_complication_layer_eight, s_icon_font);
      text_layer_set_text(s_complication_layer_eight, weather_icon_buffer);
      break;
    case 6:
      text_layer_set_font(s_complication_layer_eight, s_complication_font);
      text_layer_set_text(s_complication_layer_eight, wind_buffer);
      break;
    case 7:
      text_layer_set_font(s_complication_layer_eight, s_complication_font);
      text_layer_set_text(s_complication_layer_eight, precip_buffer);
      break;
    case 8:
      text_layer_set_font(s_complication_layer_eight, s_complication_font);
      text_layer_set_text(s_complication_layer_eight, s_step_buffer);
      break;
    case 9:
      text_layer_set_font(s_complication_layer_eight, s_complication_font);
      text_layer_set_text(s_complication_layer_eight, distance_walked_buffer);
      break;
    case 10:
      text_layer_set_font(s_complication_layer_eight, s_complication_font);
      text_layer_set_text(s_complication_layer_eight, calories_active_buffer);
    }
  }

  // Retrieve, store, and read date formatting sent from Clay, write date to a
  // buffer
  Tuple *date_format_tuple = dict_find(iterator, MESSAGE_KEY_DATE_FORMAT);
  if (date_format_tuple) {
    persist_write_int(key_date_format, atoi(date_format_tuple->value->cstring));
    time_t temp = time(NULL);
    struct tm *tick_time = localtime(&temp);
    date_format_int = persist_read_int(key_date_format);
    switch (date_format_int) {
    case 1:
      strftime(s_date_buffer, sizeof(s_date_buffer),
               PBL_IF_RECT_ELSE("%a %d", "%a%d"), tick_time);
      break;
    case 2:
      strftime(s_date_buffer, sizeof(s_date_buffer),
               PBL_IF_RECT_ELSE("%b %d", "%b%d"), tick_time);
      break;
    case 3:
      strftime(s_date_buffer, sizeof(s_date_buffer),
               PBL_IF_RECT_ELSE("%d %a", "%d%a"), tick_time);
      break;
    case 4:
      strftime(s_date_buffer, sizeof(s_date_buffer),
               PBL_IF_RECT_ELSE("%d %b", "%d%b"), tick_time);
      break;
    case 5:
      strftime(s_date_buffer, sizeof(s_date_buffer), "%a", tick_time);
      break;
    case 6:
      strftime(s_date_buffer, sizeof(s_date_buffer), "%b", tick_time);
      break;
    default:
      strftime(s_date_buffer, sizeof(s_date_buffer),
               PBL_IF_RECT_ELSE("%a %d", "%a%d"), tick_time);
    }
  }

  // Read and store weather data sent from app.js
  Tuple *temp_tuple = dict_find(iterator, MESSAGE_KEY_TEMPERATURE);
  Tuple *max_min_tuple = dict_find(iterator, MESSAGE_KEY_MAX_MIN);
  Tuple *weather_icon_tuple = dict_find(iterator, MESSAGE_KEY_WEATHER_ICON);
  Tuple *wind_gauge_tuple = dict_find(iterator, MESSAGE_KEY_WIND_GAUGE);
  Tuple *precip_gauge_tuple = dict_find(iterator, MESSAGE_KEY_PRECIP_GAUGE);

  if (temp_tuple) {
    persist_write_string(key_temperature, temp_tuple->value->cstring);
    persist_read_string(key_temperature, temperature_buffer,
                        sizeof(temperature_buffer));
  }

  if (max_min_tuple) {
    persist_write_string(key_max_min, max_min_tuple->value->cstring);
    persist_read_string(key_max_min, max_min_buffer, sizeof(max_min_buffer));
  }

  if (weather_icon_tuple) {
    persist_write_string(key_weather_icon, weather_icon_tuple->value->cstring);
    persist_read_string(key_weather_icon, weather_icon_buffer,
                        sizeof(weather_icon_buffer));
  }

  if (wind_gauge_tuple) {
    persist_write_string(key_wind, wind_gauge_tuple->value->cstring);
    persist_read_string(key_wind, wind_buffer, sizeof(wind_buffer));
  }

  if (precip_gauge_tuple) {
    persist_write_string(key_rain, precip_gauge_tuple->value->cstring);
    persist_read_string(key_rain, precip_buffer, sizeof(precip_buffer));
  }
}

static void inbox_dropped_callback(AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_ERROR, "Message dropped!");
}

static void outbox_failed_callback(DictionaryIterator *iterator,
                                   AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_ERROR, "Outbox send failed!");
}

static void outbox_sent_callback(DictionaryIterator *iterator, void *context) {
  APP_LOG(APP_LOG_LEVEL_INFO, "Outbox send success!");
}

// Write battery level into a buffer
static void battery_callback(BatteryChargeState state) {
  s_battery_level = state.charge_percent;
  if (state.is_charging) {
    snprintf(s_battery_buffer, sizeof(s_battery_buffer), "...");
  } else {
    snprintf(s_battery_buffer, sizeof(s_battery_buffer), "%d%%",
             s_battery_level);
  }
}

// Write time and date into buffers
static void update_time() {
  // Get a tm structure
  time_t temp = time(NULL);
  struct tm *tick_time = localtime(&temp);

  // Write current hours and minutes into a buffer, display on time layer
  strftime(s_time_buffer, sizeof(s_time_buffer),
           clock_is_24h_style() ? "%H:%M" : "%I:%M", tick_time);
  text_layer_set_text(s_time_layer, s_time_buffer);

  // Write date to a buffer, formatting it based on stored settings option. If
  // none, set default
  if (persist_exists(key_date_format)) {
    date_format_int = persist_read_int(key_date_format);
    switch (date_format_int) {
    case 1:
      strftime(s_date_buffer, sizeof(s_date_buffer),
               PBL_IF_RECT_ELSE("%a %d", "%a%d"), tick_time);
      break;
    case 2:
      strftime(s_date_buffer, sizeof(s_date_buffer),
               PBL_IF_RECT_ELSE("%b %d", "%b%d"), tick_time);
      break;
    case 3:
      strftime(s_date_buffer, sizeof(s_date_buffer),
               PBL_IF_RECT_ELSE("%d %a", "%d%a"), tick_time);
      break;
    case 4:
      strftime(s_date_buffer, sizeof(s_date_buffer),
               PBL_IF_RECT_ELSE("%d %b", "%d%b"), tick_time);
      break;
    case 5:
      strftime(s_date_buffer, sizeof(s_date_buffer), "%a", tick_time);
      break;
    case 6:
      strftime(s_date_buffer, sizeof(s_date_buffer), "%b", tick_time);
      break;
    default:
      strftime(s_date_buffer, sizeof(s_date_buffer),
               PBL_IF_RECT_ELSE("%a %d", "%a%d"), tick_time);
    }
  } else {
    persist_write_int(key_date_format, 1);
    strftime(s_date_buffer, sizeof(s_date_buffer),
             PBL_IF_RECT_ELSE("%a %d", "%a%d"), tick_time);
  }
}

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  update_time();

  // Get weather update every 20 minutes
  if (tick_time->tm_min % 20 == 0) {
    // Begin dictionary
    DictionaryIterator *iter;
    app_message_outbox_begin(&iter);

    // Add a key-value pair
    dict_write_uint8(iter, 0, 0);

    // Send the message
    app_message_outbox_send();
  }
}

static void bluetooth_callback(bool connected) {
  // Hide icon when connected, vibrate on disconnect
  layer_set_hidden(text_layer_get_layer(s_bluetooth_layer), connected);
  if (!connected) {
    // Issue a vibrating alert
    vibes_double_pulse();
  }
}

// Write today's step count into a buffer
static void display_steps() {
  HealthMetric steps = HealthMetricStepCount;
  time_t start = time_start_of_today();
  time_t end = time(NULL);

  // Check the metric has data available for today
  HealthServiceAccessibilityMask steps_mask =
      health_service_metric_accessible(steps, start, end);

  if (steps_mask & HealthServiceAccessibilityMaskAvailable) {
    snprintf(s_step_buffer, sizeof(s_step_buffer), "%d",
             (int)health_service_sum_today(steps));
  } else {
    // No data recorded yet today
    APP_LOG(APP_LOG_LEVEL_ERROR, "Steps data unavailable!");
  }
}

// Write distance walked today into a buffer
static void display_distance_walked() {
  // Get today's value and measurement system
  const HealthMetric meters = HealthMetricWalkedDistanceMeters;
  const HealthValue distance = health_service_sum_today(meters);
  MeasurementSystem system =
      health_service_get_measurement_system_for_display(meters);

  // Create timestamps for midnight (the start time) and now (the end time)
  time_t start = time_start_of_today();
  time_t end = time(NULL);

  // Check step data is availables
  HealthServiceAccessibilityMask distance_mask =
      health_service_metric_accessible(meters, start, end);

  if (distance_mask & HealthServiceAccessibilityMaskAvailable) {
    // Format into a buffer based on user's measurement system
    switch (system) {
    case MeasurementSystemMetric:
      snprintf(distance_walked_buffer, sizeof(distance_walked_buffer),
               PBL_IF_RECT_ELSE("%d.%d km", "%d.%dkm"),
               (int)floor(distance / 1000),
               (int)(floor(distance % 1000) / 100));
      break;
    case MeasurementSystemImperial: {
      // Convert metric data to imperial
      snprintf(distance_walked_buffer, sizeof(distance_walked_buffer),
               PBL_IF_RECT_ELSE("%d.%d mi", "%d.%dmi"),
               (int)(floor(distance / 1609.34)),
               (int)(floor(distance % 1609) / 161));
    } break;
    case MeasurementSystemUnknown:
    default:
      APP_LOG(APP_LOG_LEVEL_INFO,
              "MeasurementSystem unknown or does not apply");
    }
  } else {
    // No data recorded yet today
    APP_LOG(APP_LOG_LEVEL_ERROR, "Distance walked unavailable!");
  }
}

// Write calories burned today into a buffer
static void display_active_calories_burned() {
  HealthMetric calories = HealthMetricActiveKCalories;
  time_t start = time_start_of_today();
  time_t end = time(NULL);
  HealthServiceAccessibilityMask calories_mask =
      health_service_metric_accessible(calories, start, end);

  if (calories_mask & HealthServiceAccessibilityMaskAvailable) {
    snprintf(calories_active_buffer, sizeof(calories_active_buffer),
             PBL_IF_RECT_ELSE("%dCal", "%dk"),
             (int)health_service_sum_today(calories));
  } else {
    APP_LOG(APP_LOG_LEVEL_ERROR, "Active calories unavailable!");
  }
}

static void health_handler(HealthEventType event, void *context) {
  // Which type of event occurred?
  switch (event) {
  case HealthEventSignificantUpdate:
    APP_LOG(APP_LOG_LEVEL_INFO,
            "New HealthService HealthEventSignificantUpdate event");
    display_steps();
    display_distance_walked();
    display_active_calories_burned();
    break;

  case HealthEventMovementUpdate:
    APP_LOG(APP_LOG_LEVEL_INFO,
            "New HealthService HealthEventMovementUpdate event");
    display_steps();
    display_distance_walked();
    display_active_calories_burned();
    break;

  case HealthEventMetricAlert:
    break;

  case HealthEventHeartRateUpdate:
    break;

  case HealthEventSleepUpdate:
    APP_LOG(APP_LOG_LEVEL_INFO,
            "New HealthService HealthEventSleepUpdate event");
    break;
  }
}

static void main_window_load(Window *window) {
  // Get information about the Window and identify boundaries
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  // Load fonts
  s_time_font = fonts_load_custom_font(
      resource_get_handle(RESOURCE_ID_FONT_UBUNTU_BOLD_44));
  s_complication_font = fonts_load_custom_font(
      resource_get_handle(RESOURCE_ID_FONT_UBUNTU_REGULAR_20));
  s_icon_font =
      fonts_load_custom_font(resource_get_handle(RESOURCE_ID_WEATHER_ICONS_24));

  /* Retrieve settings data, set defaults if none, convert int values to GColor
   * values*/
  if (persist_exists(key_time_text)) {
    time_text_int = persist_read_int(key_time_text);
    time_text = GColorFromHEX(time_text_int);
  } else {
    time_text_int = 0x000000;
    persist_write_int(key_time_text, time_text_int);
    time_text = GColorFromHEX(time_text_int);
  }

  if (persist_exists(key_time_background)) {
    time_background_int = persist_read_int(key_time_background);
    time_background = GColorFromHEX(time_background_int);
  } else {
    time_background_int = 0xFFFFFF;
    persist_write_int(key_time_background, time_background_int);
    time_background = GColorFromHEX(time_background_int);
  }

  if (persist_exists(key_text1)) {
    text1_int = persist_read_int(key_text1);
    text1 = GColorFromHEX(text1_int);
  } else {
    text1_int = 0x000000;
    persist_write_int(key_text1, text1_int);
    text1 = GColorFromHEX(text1_int);
  }

  if (persist_exists(key_background1)) {
    background1_int = persist_read_int(key_background1);
    background1 = GColorFromHEX(background1_int);
  } else {
    background1_int = 0xFFFFFF;
    persist_write_int(key_background1, background1_int);
    background1 = GColorFromHEX(background1_int);
  }

  if (persist_exists(key_complication1)) {
    complication1_int = persist_read_int(key_complication1);
  } else {
    persist_write_int(key_complication1, 0);
    complication1_int = persist_read_int(key_complication1);
  }

  if (persist_exists(key_text2)) {
    text2_int = persist_read_int(key_text2);
    text2 = GColorFromHEX(text2_int);
  } else {
    text2_int = 0x000000;
    persist_write_int(key_text2, text2_int);
    text2 = GColorFromHEX(text2_int);
  }

  if (persist_exists(key_background2)) {
    background2_int = persist_read_int(key_background2);
    background2 = GColorFromHEX(background2_int);
  } else {
    background2_int = 0xFFFFFF;
    persist_write_int(key_background2, background2_int);
    background2 = GColorFromHEX(background2_int);
  }

  if (persist_exists(key_complication2)) {
    complication2_int = persist_read_int(key_complication2);
  } else {
    persist_write_int(key_complication2, 0);
    complication2_int = persist_read_int(key_complication2);
  }

  if (persist_exists(key_text3)) {
    text3_int = persist_read_int(key_text3);
    text3 = GColorFromHEX(text3_int);
  } else {
    text3_int = 0x000000;
    persist_write_int(key_text3, text3_int);
    text3 = GColorFromHEX(text3_int);
  }

  if (persist_exists(key_background3)) {
    background3_int = persist_read_int(key_background3);
    background3 = GColorFromHEX(background3_int);
  } else {
    background3_int = 0xFFFFFF;
    persist_write_int(key_background3, background3_int);
    background3 = GColorFromHEX(background3_int);
  }

  if (persist_exists(key_complication3)) {
    complication3_int = persist_read_int(key_complication3);
  } else {
    persist_write_int(key_complication3, 0);
    complication3_int = persist_read_int(key_complication3);
  }

  if (persist_exists(key_text4)) {
    text4_int = persist_read_int(key_text4);
    text4 = GColorFromHEX(text4_int);
  } else {
    text4_int = 0x000000;
    persist_write_int(key_text4, text4_int);
    text4 = GColorFromHEX(text4_int);
  }

  if (persist_exists(key_background4)) {
    background4_int = persist_read_int(key_background4);
    background4 = GColorFromHEX(background4_int);
  } else {
    background4_int = 0xFFFFFF;
    persist_write_int(key_background4, background4_int);
    background4 = GColorFromHEX(background4_int);
  }

  if (persist_exists(key_complication4)) {
    complication4_int = persist_read_int(key_complication4);
  } else {
    persist_write_int(key_complication4, 0);
    complication4_int = persist_read_int(key_complication4);
  }

  if (persist_exists(key_text5)) {
    text5_int = persist_read_int(key_text5);
    text5 = GColorFromHEX(text5_int);
  } else {
    text5_int = 0x000000;
    persist_write_int(key_text5, text5_int);
    text5 = GColorFromHEX(text5_int);
  }

  if (persist_exists(key_background5)) {
    background5_int = persist_read_int(key_background5);
    background5 = GColorFromHEX(background5_int);
  } else {
    background5_int = 0xFFFFFF;
    persist_write_int(key_background5, background5_int);
    background5 = GColorFromHEX(background5_int);
  }

  if (persist_exists(key_complication5)) {
    complication5_int = persist_read_int(key_complication5);
  } else {
    persist_write_int(key_complication5, 0);
    complication5_int = persist_read_int(key_complication5);
  }

  if (persist_exists(key_text6)) {
    text6_int = persist_read_int(key_text6);
    text6 = GColorFromHEX(text6_int);
  } else {
    text6_int = 0x000000;
    persist_write_int(key_text6, text6_int);
    text6 = GColorFromHEX(text6_int);
  }

  if (persist_exists(key_background6)) {
    background6_int = persist_read_int(key_background6);
    background6 = GColorFromHEX(background6_int);
  } else {
    background6_int = 0xFFFFFF;
    persist_write_int(key_background6, background6_int);
    background6 = GColorFromHEX(background6_int);
  }

  if (persist_exists(key_complication6)) {
    complication6_int = persist_read_int(key_complication6);
  } else {
    persist_write_int(key_complication6, 0);
    complication6_int = persist_read_int(key_complication6);
  }

  if (persist_exists(key_text7)) {
    text7_int = persist_read_int(key_text7);
    text7 = GColorFromHEX(text7_int);
  } else {
    text7_int = 0x000000;
    persist_write_int(key_text7, text7_int);
    text7 = GColorFromHEX(text7_int);
  }

  if (persist_exists(key_background7)) {
    background7_int = persist_read_int(key_background7);
    background7 = GColorFromHEX(background7_int);
  } else {
    background7_int = 0xFFFFFF;
    persist_write_int(key_background7, background7_int);
    background7 = GColorFromHEX(background7_int);
  }

  if (persist_exists(key_complication7)) {
    complication7_int = persist_read_int(key_complication7);
  } else {
    persist_write_int(key_complication7, 0);
    complication7_int = persist_read_int(key_complication7);
  }

  if (persist_exists(key_text8)) {
    text8_int = persist_read_int(key_text8);
    text8 = GColorFromHEX(text8_int);
  } else {
    text8_int = 0x000000;
    persist_write_int(key_text8, text8_int);
    text8 = GColorFromHEX(text8_int);
  }

  if (persist_exists(key_background8)) {
    background8_int = persist_read_int(key_background8);
    background8 = GColorFromHEX(background8_int);
  } else {
    background8_int = 0xFFFFFF;
    persist_write_int(key_background8, background8_int);
    background8 = GColorFromHEX(background8_int);
  }

  if (persist_exists(key_complication8)) {
    complication8_int = persist_read_int(key_complication8);
  } else {
    persist_write_int(key_complication8, 0);
    complication8_int = persist_read_int(key_complication8);
  }

  // Read persistent storage for weather items
  if (persist_exists(key_temperature)) {
    persist_read_string(key_temperature, temperature_buffer,
                        sizeof(temperature_buffer));
  }
  if (persist_exists(key_max_min)) {
    persist_read_string(key_max_min, max_min_buffer, sizeof(max_min_buffer));
  }
  if (persist_exists(key_weather_icon)) {
    persist_read_string(key_weather_icon, weather_icon_buffer,
                        sizeof(weather_icon_buffer));
  }
  if (persist_exists(key_wind)) {
    persist_read_string(key_wind, wind_buffer, sizeof(wind_buffer));
  }
  if (persist_exists(key_rain)) {
    persist_read_string(key_rain, precip_buffer, sizeof(precip_buffer));
  }

  /* Create and set up time layer. On rectangular watches, it is in the upper
     half with one row above it, and on round watches, it is top and center.*/
  s_time_layer = text_layer_create(GRect(
      PBL_IF_RECT_ELSE(((bounds.size.w / 2) * 0), ((bounds.size.w / 3) * 0)),
      PBL_IF_RECT_ELSE(((bounds.size.h / 6) * 1),
                       ((bounds.size.h / 6) * 0) + 8),
      bounds.size.w, (bounds.size.h / 3)));
  text_layer_set_font(s_time_layer, s_time_font);
  text_layer_set_text_color(s_time_layer, time_text);
  text_layer_set_background_color(s_time_layer, time_background);
  window_set_background_color(s_main_window,
                              PBL_IF_RECT_ELSE(GColorWhite, time_background));
  text_layer_set_text_alignment(s_time_layer, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(s_time_layer));

  /* Create text layer to display Bluetooth disconnection alert with an 'x.' The
     alert will appear to the left of the time layer.*/
  s_bluetooth_layer = text_layer_create(GRect(
      PBL_IF_RECT_ELSE(((bounds.size.w) * 0) - 2, (bounds.size.w) / 12) + 7,
      PBL_IF_RECT_ELSE((bounds.size.h) / 4, (bounds.size.h) / 6),
      ((bounds.size.w) / 12), (bounds.size.h) / 6));
  text_layer_set_font(s_bluetooth_layer, s_complication_font);
  text_layer_set_text(s_bluetooth_layer, "x");
  text_layer_set_text_color(s_bluetooth_layer, time_text);
  text_layer_set_background_color(s_bluetooth_layer, GColorClear);
  text_layer_set_text_alignment(s_bluetooth_layer, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(s_bluetooth_layer));

  // Show the correct state of the BT connection from the start
  bluetooth_callback(connection_service_peek_pebble_app_connection());

  /* Create and set complication layer one. On rectangular watches, it is above
     and to the left of the time, and on round watches, it is on the left above
     the midpoint line.*/
  s_complication_layer_one = text_layer_create(GRect(
      PBL_IF_RECT_ELSE(((bounds.size.w / 2) * 0), ((bounds.size.w / 3) * 0)),
      PBL_IF_RECT_ELSE(((bounds.size.h / 6) * 0), ((bounds.size.h / 6) * 2)),
      PBL_IF_RECT_ELSE((bounds.size.w / 2), (bounds.size.w / 3)),
      (bounds.size.h / 6)));
  if (complication1_int == 5) {
    text_layer_set_font(s_complication_layer_one, s_icon_font);
  } else {
    text_layer_set_font(s_complication_layer_one, s_complication_font);
  }
  switch (complication1_int) {
  case 1:
    text_layer_set_text(s_complication_layer_one, s_date_buffer);
    break;
  case 2:
    text_layer_set_text(s_complication_layer_one, s_battery_buffer);
    break;
  case 3:
    text_layer_set_text(s_complication_layer_one, temperature_buffer);
    break;
  case 4:
    text_layer_set_text(s_complication_layer_one, max_min_buffer);
    break;
  case 5:
    text_layer_set_text(s_complication_layer_one, weather_icon_buffer);
    break;
  case 6:
    text_layer_set_text(s_complication_layer_one, wind_buffer);
    break;
  case 7:
    text_layer_set_text(s_complication_layer_one, precip_buffer);
    break;
  case 8:
    text_layer_set_text(s_complication_layer_one, s_step_buffer);
    break;
  case 9:
    text_layer_set_text(s_complication_layer_one, distance_walked_buffer);
    break;
  case 10:
    text_layer_set_text(s_complication_layer_one, calories_active_buffer);
    break;
  default:
    text_layer_set_text(s_complication_layer_one, "");
  }
  text_layer_set_text_color(s_complication_layer_one, text1);
  text_layer_set_background_color(s_complication_layer_one, background1);
  text_layer_set_text_alignment(s_complication_layer_one, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(s_complication_layer_one));

  /* Create and set up complication layer two. On rectangular watches, it is
     above and to the right above the time, and on round watches, it is in the
     middle above the midpoint line.*/
  s_complication_layer_two = text_layer_create(GRect(
      PBL_IF_RECT_ELSE(((bounds.size.w / 2) * 1), ((bounds.size.w / 3) * 1)),
      PBL_IF_RECT_ELSE(((bounds.size.h / 6) * 0), ((bounds.size.h / 6) * 2)),
      PBL_IF_RECT_ELSE((bounds.size.w / 2), (bounds.size.w / 3)),
      (bounds.size.h / 6)));
  if (complication2_int == 5) {
    text_layer_set_font(s_complication_layer_two, s_icon_font);
  } else {
    text_layer_set_font(s_complication_layer_two, s_complication_font);
  }
  switch (complication2_int) {
  case 1:
    text_layer_set_text(s_complication_layer_two, s_date_buffer);
    break;
  case 2:
    text_layer_set_text(s_complication_layer_two, s_battery_buffer);
    break;
  case 3:
    text_layer_set_text(s_complication_layer_two, temperature_buffer);
    break;
  case 4:
    text_layer_set_text(s_complication_layer_two, max_min_buffer);
    break;
  case 5:
    text_layer_set_text(s_complication_layer_two, weather_icon_buffer);
    break;
  case 6:
    text_layer_set_text(s_complication_layer_two, wind_buffer);
    break;
  case 7:
    text_layer_set_text(s_complication_layer_two, precip_buffer);
    break;
  case 8:
    text_layer_set_text(s_complication_layer_two, s_step_buffer);
    break;
  case 9:
    text_layer_set_text(s_complication_layer_two, distance_walked_buffer);
    break;
  case 10:
    text_layer_set_text(s_complication_layer_two, calories_active_buffer);
    break;
  default:
    text_layer_set_text(s_complication_layer_two, "");
  }
  text_layer_set_text_color(s_complication_layer_two, text2);
  text_layer_set_background_color(s_complication_layer_two, background2);
  text_layer_set_text_alignment(s_complication_layer_two, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(s_complication_layer_two));

  /* Create and set up complication layer three. On rectangular watches, it is
     below the time layer to the left, and on round watches, it is on the right
     above the midpoint line.*/
  s_complication_layer_three = text_layer_create(GRect(
      PBL_IF_RECT_ELSE(((bounds.size.w / 2) * 0), ((bounds.size.w / 3) * 2)),
      PBL_IF_RECT_ELSE(((bounds.size.h / 6) * 3), ((bounds.size.h / 6) * 2)),
      PBL_IF_RECT_ELSE((bounds.size.w / 2), (bounds.size.w / 3)),
      (bounds.size.h / 6)));
  if (complication3_int == 5) {
    text_layer_set_font(s_complication_layer_three, s_icon_font);
  } else {
    text_layer_set_font(s_complication_layer_three, s_complication_font);
  }
  switch (complication3_int) {
  case 1:
    text_layer_set_text(s_complication_layer_three, s_date_buffer);
    break;
  case 2:
    text_layer_set_text(s_complication_layer_three, s_battery_buffer);
    break;
  case 3:
    text_layer_set_text(s_complication_layer_three, temperature_buffer);
    break;
  case 4:
    text_layer_set_text(s_complication_layer_three, max_min_buffer);
    break;
  case 5:
    text_layer_set_text(s_complication_layer_three, weather_icon_buffer);
    break;
  case 6:
    text_layer_set_text(s_complication_layer_three, wind_buffer);
    break;
  case 7:
    text_layer_set_text(s_complication_layer_three, precip_buffer);
    break;
  case 8:
    text_layer_set_text(s_complication_layer_three, s_step_buffer);
    break;
  case 9:
    text_layer_set_text(s_complication_layer_three, distance_walked_buffer);
    break;
  case 10:
    text_layer_set_text(s_complication_layer_three, calories_active_buffer);
    break;
  default:
    text_layer_set_text(s_complication_layer_three, "");
  }
  text_layer_set_text_color(s_complication_layer_three, text3);
  text_layer_set_background_color(s_complication_layer_three, background3);
  text_layer_set_text_alignment(s_complication_layer_three,
                                GTextAlignmentCenter);
  layer_add_child(window_layer,
                  text_layer_get_layer(s_complication_layer_three));

  /* Create and set up complication layer four. On rectangular watches, it is on
     the left below the middle of the watch, and on round watches, it is on the
     left below the midpoint line.*/
  s_complication_layer_four = text_layer_create(GRect(
      PBL_IF_RECT_ELSE(((bounds.size.w / 2) * 1), ((bounds.size.w / 3) * 0)),
      PBL_IF_RECT_ELSE(((bounds.size.h / 6) * 3), ((bounds.size.h / 6) * 3)),
      PBL_IF_RECT_ELSE((bounds.size.w / 2), (bounds.size.w / 3)),
      (bounds.size.h / 6)));
  if (complication4_int == 5) {
    text_layer_set_font(s_complication_layer_four, s_icon_font);
  } else {
    text_layer_set_font(s_complication_layer_four, s_complication_font);
  }
  switch (complication4_int) {
  case 1:
    text_layer_set_text(s_complication_layer_four, s_date_buffer);
    break;
  case 2:
    text_layer_set_text(s_complication_layer_four, s_battery_buffer);
    break;
  case 3:
    text_layer_set_text(s_complication_layer_four, temperature_buffer);
    break;
  case 4:
    text_layer_set_text(s_complication_layer_four, max_min_buffer);
    break;
  case 5:
    text_layer_set_text(s_complication_layer_four, weather_icon_buffer);
    break;
  case 6:
    text_layer_set_text(s_complication_layer_four, wind_buffer);
    break;
  case 7:
    text_layer_set_text(s_complication_layer_four, precip_buffer);
    break;
  case 8:
    text_layer_set_text(s_complication_layer_four, s_step_buffer);
    break;
  case 9:
    text_layer_set_text(s_complication_layer_four, distance_walked_buffer);
    break;
  case 10:
    text_layer_set_text(s_complication_layer_four, calories_active_buffer);
    break;
  default:
    text_layer_set_text(s_complication_layer_four, "");
  }
  text_layer_set_text_color(s_complication_layer_four, text4);
  text_layer_set_background_color(s_complication_layer_four, background4);
  text_layer_set_text_alignment(s_complication_layer_four,
                                GTextAlignmentCenter);
  layer_add_child(window_layer,
                  text_layer_get_layer(s_complication_layer_four));

  /* Create and set up complication layer five. On rectangular watches, it is on
     the middle left side in the bottom half, and on round watches, it is in
     the middle below the midpoint line.*/
  s_complication_layer_five = text_layer_create(GRect(
      PBL_IF_RECT_ELSE(((bounds.size.w / 2) * 0), ((bounds.size.w / 3) * 1)),
      PBL_IF_RECT_ELSE(((bounds.size.h / 6) * 4), ((bounds.size.h / 6) * 3)),
      PBL_IF_RECT_ELSE((bounds.size.w / 2), (bounds.size.w / 3)),
      (bounds.size.h / 6)));
  if (complication5_int == 5) {
    text_layer_set_font(s_complication_layer_five, s_icon_font);
  } else {
    text_layer_set_font(s_complication_layer_five, s_complication_font);
  }
  switch (complication5_int) {
  case 1:
    text_layer_set_text(s_complication_layer_five, s_date_buffer);
    break;
  case 2:
    text_layer_set_text(s_complication_layer_five, s_battery_buffer);
    break;
  case 3:
    text_layer_set_text(s_complication_layer_five, temperature_buffer);
    break;
  case 4:
    text_layer_set_text(s_complication_layer_five, max_min_buffer);
    break;
  case 5:
    text_layer_set_text(s_complication_layer_five, weather_icon_buffer);
    break;
  case 6:
    text_layer_set_text(s_complication_layer_five, wind_buffer);
    break;
  case 7:
    text_layer_set_text(s_complication_layer_five, precip_buffer);
    break;
  case 8:
    text_layer_set_text(s_complication_layer_five, s_step_buffer);
    break;
  case 9:
    text_layer_set_text(s_complication_layer_five, distance_walked_buffer);
    break;
  case 10:
    text_layer_set_text(s_complication_layer_five, calories_active_buffer);
    break;
  default:
    text_layer_set_text(s_complication_layer_five, "");
  }
  text_layer_set_text_color(s_complication_layer_five, text5);
  text_layer_set_background_color(s_complication_layer_five, background5);
  text_layer_set_text_alignment(s_complication_layer_five,
                                GTextAlignmentCenter);
  layer_add_child(window_layer,
                  text_layer_get_layer(s_complication_layer_five));

  /* Create and set up complication layer six. On rectangular watches, it is in
     the middle right side, in the bottom half, and on round watches, it is on
     the right below the midpoint line.*/
  s_complication_layer_six = text_layer_create(GRect(
      PBL_IF_RECT_ELSE(((bounds.size.w / 2) * 1), ((bounds.size.w / 3) * 2)),
      PBL_IF_RECT_ELSE(((bounds.size.h / 6) * 4), ((bounds.size.h / 6) * 3)),
      PBL_IF_RECT_ELSE((bounds.size.w / 2), (bounds.size.w / 3)),
      (bounds.size.h / 6)));
  if (complication6_int == 5) {
    text_layer_set_font(s_complication_layer_six, s_icon_font);
  } else {
    text_layer_set_font(s_complication_layer_six, s_complication_font);
  }
  switch (complication6_int) {
  case 1:
    text_layer_set_text(s_complication_layer_six, s_date_buffer);
    break;
  case 2:
    text_layer_set_text(s_complication_layer_six, s_battery_buffer);
    break;
  case 3:
    text_layer_set_text(s_complication_layer_six, temperature_buffer);
    break;
  case 4:
    text_layer_set_text(s_complication_layer_six, max_min_buffer);
    break;
  case 5:
    text_layer_set_text(s_complication_layer_six, weather_icon_buffer);
    break;
  case 6:
    text_layer_set_text(s_complication_layer_six, wind_buffer);
    break;
  case 7:
    text_layer_set_text(s_complication_layer_six, precip_buffer);
    break;
  case 8:
    text_layer_set_text(s_complication_layer_six, s_step_buffer);
    break;
  case 9:
    text_layer_set_text(s_complication_layer_six, distance_walked_buffer);
    break;
  case 10:
    text_layer_set_text(s_complication_layer_six, calories_active_buffer);
    break;
  default:
    text_layer_set_text(s_complication_layer_six, "");
  }
  text_layer_set_text_color(s_complication_layer_six, text6);
  text_layer_set_background_color(s_complication_layer_six, background6);
  text_layer_set_text_alignment(s_complication_layer_six, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(s_complication_layer_six));

  /* Create and set up complication layer seven. On rectangular watches, it is
     in the bottom row, left side, and on round watches, it is centered, second
     row from the bottom.*/
  s_complication_layer_seven = text_layer_create(GRect(
      PBL_IF_RECT_ELSE(((bounds.size.w / 2) * 0), ((bounds.size.w / 4) * 0)),
      PBL_IF_RECT_ELSE(((bounds.size.h / 6) * 5), ((bounds.size.h / 6) * 4)),
      PBL_IF_RECT_ELSE((bounds.size.w / 2), bounds.size.w),
      (bounds.size.h / 6)));
  if (complication7_int == 5) {
    text_layer_set_font(s_complication_layer_seven, s_icon_font);
  } else {
    text_layer_set_font(s_complication_layer_seven, s_complication_font);
  }
  switch (complication7_int) {
  case 1:
    text_layer_set_text(s_complication_layer_seven, s_date_buffer);
    break;
  case 2:
    text_layer_set_text(s_complication_layer_seven, s_battery_buffer);
    break;
  case 3:
    text_layer_set_text(s_complication_layer_seven, temperature_buffer);
    break;
  case 4:
    text_layer_set_text(s_complication_layer_seven, max_min_buffer);
    break;
  case 5:
    text_layer_set_text(s_complication_layer_seven, weather_icon_buffer);
    break;
  case 6:
    text_layer_set_text(s_complication_layer_seven, wind_buffer);
    break;
  case 7:
    text_layer_set_text(s_complication_layer_seven, precip_buffer);
    break;
  case 8:
    text_layer_set_text(s_complication_layer_seven, s_step_buffer);
    break;
  case 9:
    text_layer_set_text(s_complication_layer_seven, distance_walked_buffer);
    break;
  case 10:
    text_layer_set_text(s_complication_layer_seven, calories_active_buffer);
    break;
  default:
    text_layer_set_text(s_complication_layer_seven, "");
  }
  text_layer_set_text_color(s_complication_layer_seven, text7);
  text_layer_set_background_color(s_complication_layer_seven, background7);
  text_layer_set_text_alignment(s_complication_layer_seven,
                                GTextAlignmentCenter);
  layer_add_child(window_layer,
                  text_layer_get_layer(s_complication_layer_seven));

  /* Create and set up complication layer eight. On rectangular watches, it is
     in the bottom row on the right. On round watches, it is centered at the
     bottom.*/
  s_complication_layer_eight = text_layer_create(GRect(
      PBL_IF_RECT_ELSE(((bounds.size.w / 2) * 1), ((bounds.size.w / 4) * 0)),
      PBL_IF_RECT_ELSE(((bounds.size.h / 6) * 5), ((bounds.size.h / 6) * 5)),
      PBL_IF_RECT_ELSE((bounds.size.w / 2), bounds.size.w),
      (bounds.size.h / 6)));
  if (complication8_int == 5) {
    text_layer_set_font(s_complication_layer_eight, s_icon_font);
  } else {
    text_layer_set_font(s_complication_layer_eight, s_complication_font);
  }
  switch (complication8_int) {
  case 1:
    text_layer_set_text(s_complication_layer_eight, s_date_buffer);
    break;
  case 2:
    text_layer_set_text(s_complication_layer_eight, s_battery_buffer);
    break;
  case 3:
    text_layer_set_text(s_complication_layer_eight, temperature_buffer);
    break;
  case 4:
    text_layer_set_text(s_complication_layer_eight, max_min_buffer);
    break;
  case 5:
    text_layer_set_text(s_complication_layer_eight, weather_icon_buffer);
    break;
  case 6:
    text_layer_set_text(s_complication_layer_eight, wind_buffer);
    break;
  case 7:
    text_layer_set_text(s_complication_layer_eight, precip_buffer);
    break;
  case 8:
    text_layer_set_text(s_complication_layer_eight, s_step_buffer);
    break;
  case 9:
    text_layer_set_text(s_complication_layer_eight, distance_walked_buffer);
    break;
  case 10:
    text_layer_set_text(s_complication_layer_eight, calories_active_buffer);
    break;
  default:
    text_layer_set_text(s_complication_layer_eight, "");
  }
  text_layer_set_text_color(s_complication_layer_eight, text8);
  text_layer_set_background_color(s_complication_layer_eight, background8);
  text_layer_set_text_alignment(s_complication_layer_eight,
                                GTextAlignmentCenter);
  layer_add_child(window_layer,
                  text_layer_get_layer(s_complication_layer_eight));
}

static void main_window_unload(Window *window) {
  // Unload GFonts
  fonts_unload_custom_font(s_time_font);
  fonts_unload_custom_font(s_complication_font);
  fonts_unload_custom_font(s_icon_font);

  // Destroy time and complication layers
  text_layer_destroy(s_time_layer);
  text_layer_destroy(s_bluetooth_layer);
  text_layer_destroy(s_complication_layer_one);
  text_layer_destroy(s_complication_layer_two);
  text_layer_destroy(s_complication_layer_three);
  text_layer_destroy(s_complication_layer_four);
  text_layer_destroy(s_complication_layer_five);
  text_layer_destroy(s_complication_layer_six);
  text_layer_destroy(s_complication_layer_seven);
  text_layer_destroy(s_complication_layer_eight);
}

static void init() {
  // Create main Window element and assign to pointer
  s_main_window = window_create();

  // Set handlers to manage the elements inside the Window
  window_set_window_handlers(
      s_main_window,
      (WindowHandlers){.load = main_window_load, .unload = main_window_unload});

  // Show the Window on the watch, with animated=true
  window_stack_push(s_main_window, true);
  window_set_background_color(s_main_window,
                              PBL_IF_RECT_ELSE(GColorWhite, time_background));

  // Make sure the time is displayed from the start
  update_time();

  // Register with TickTimerService
  tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);

  // Callbacks for AppMessage
  app_message_register_inbox_received(inbox_received_callback);
  app_message_register_inbox_dropped(inbox_dropped_callback);
  app_message_register_outbox_failed(outbox_failed_callback);
  app_message_register_outbox_sent(outbox_sent_callback);

  // Open AppMessage
  const int inbox_size = 1024;
  const int outbox_size = 1024;
  app_message_open(inbox_size, outbox_size);
  //   app_message_inbox_size_maximum(), app_message_outbox_size_maximum()

  // Register for battery level updates
  battery_state_service_subscribe(battery_callback);

  // Ensure battery level is displayed from the start
  battery_callback(battery_state_service_peek());

  // Register for Bluetooth connection updates
  connection_service_subscribe((ConnectionHandlers){
      .pebble_app_connection_handler = bluetooth_callback});

#if defined(PBL_HEALTH)
  // Attempt to subscribe
  if (!health_service_events_subscribe(health_handler, NULL)) {
    APP_LOG(APP_LOG_LEVEL_ERROR, "Health not available!");
  }
#else
  APP_LOG(APP_LOG_LEVEL_ERROR, "Health not available!");
#endif
}

static void deinit() {
  // Destroy Window
  window_destroy(s_main_window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}
