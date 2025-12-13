#ifndef _INTAKE_H_
#define _INTAKE_H_

/**
 * \file intake.h
 *
 * Intake subsystem declarations
 */

#include "config.h"
#include "api.h"

// Intake states
enum IntakeState {
	INTAKE = 0,
	SCORE_MID = 1,
	SCORE_LOW = 2,
	SCORE_HIGH = 3,
	IDLE = 4
};


struct JamState {
	pros::Motor* target;

	const uint32_t jam_tolerance;
	const uint32_t unjam_duration;

	uint32_t jam_start = 0;
	uint32_t unjam_end = 0;

	JamState(pros::Motor* target, uint32_t jam_tolerance, uint32_t unjam_duration);

	void update();
};

extern JamState intake_jam_state;

void intake_init();
void intake_spin(double velocity);
void intake_stop();
void intake_set_state(IntakeState state);

inline constexpr uint32_t INTAKE_RUN_DELAY = 100;
extern bool wing_macro_clamp;
extern uint32_t intake_run_time;

extern bool matchloader_value;
extern bool pto_value;
extern bool score_mid_value;
extern bool park_value;
extern bool wing_value;
extern bool descore_value;
extern bool clamp_value;

void set_matchloader(bool value);
void set_pto(bool value);
void set_score_mid(bool value);
void set_park(bool value);
void set_wing(bool value);
void set_descore(bool value);
void set_clamp(bool value);

	extern float power_mult;

void hold_dist_and_reset(uint32_t sample_time, double heading_mod, int quadrant, int distance = 300, int tolerance = 1);

void drive_until_distance(float heading_hold, int power, uint32_t ramp, int dist, int tolerance, bool greater, uint32_t timeout);

void score_7_mid();

IntakeState intake_get_state();

void score_7_mid();

#endif // _INTAKE_H_
