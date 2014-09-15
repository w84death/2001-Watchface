/*
*
*
*   P1X, Krzysztof Jankowski
*   2001: Watchface
*
*   abstract: Watch face for Pebble
*   created: 14-09-2014
*   license: do what you want and dont bother me
*
*   webpage: http://p1x.in
*   twitter: @w84death
*
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <pebble.h>
#include <face.h>

static char the_time[] = "00:00";
static char date_text[] = "DAY 000, 00 Xxxxxxxxx 0000";
static bool refresh_date = true;
	
void tick_handler(struct tm *tick_time, TimeUnits units_changed)
{
	strftime(the_time, sizeof("00:00"), "%H:%M", tick_time);
	strftime(date_text, sizeof(date_text), "DAY %j, %d %B %y", tick_time);
	
	if(units_changed & DAY_UNIT){
		refresh_date = true;
	}
	
	if(refresh_date){
		show_date(date_text);	
		refresh_date = false;
	}  
	show_time(the_time);
}

void batteryChanged(BatteryChargeState batt) {	
	update_battery(batt.charge_percent);
}

void handle_init(void) {
	show_face();
	tick_timer_service_subscribe(MINUTE_UNIT, (TickHandler)tick_handler);
	battery_state_service_subscribe(batteryChanged);
}

void handle_deinit(void) {
  hide_face();
	tick_timer_service_unsubscribe();
	battery_state_service_unsubscribe();
}

int main(void) {
  handle_init();
  app_event_loop();
  handle_deinit();
}
