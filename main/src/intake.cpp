#include "main.h"
#include "intake.h"

/**
 * \file intake.cpp
 *
 * Intake subsystem implementation
 */

pros::Motor intake_motor(INTAKE_MOTOR_PORT, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);

// Current intake state
static IntakeState current_state = IDLE;

bool matchloader_value = false;
bool pto_value = false;
bool score_mid_value = false;
bool park_value = false;
bool wing_value = false;
bool descore_value = false;
bool clamp_value = false;

void intake_init() {
	// Initialize intake motor
	intake_motor.tare_position();
	intake_motor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	intake_motor.move_velocity(0);
	current_state = IDLE;
}

void intake_spin(double velocity) {
	intake_motor.move_velocity(velocity);
}

void intake_stop() {
	intake_motor.move_velocity(0);
}

void set_matchloader(const bool value) {
	matchloader_value = value;
	(void)matchloader_piston.set_value(matchloader_value);
}
void set_pto(bool value) {
    pto_value = value;
    (void)pto_piston.set_value(pto_value);
}

void set_score_mid(bool value) {
    score_mid_value = value;
    (void)score_mid_piston.set_value(score_mid_value);
}

void set_park(bool value) {
    park_value = value;
    (void)park_piston.set_value(park_value);
}

void set_wing(bool value) {
    wing_value = value;
    (void)wing_piston.set_value(wing_value);
}

void set_descore(bool value) {
    descore_value = value;
    (void)descore_piston.set_value(descore_value);
}

void set_clamp(bool value) {
	clamp_value = value;
	(void)clamp_piston.set_value(clamp_value);
}

void set_score_mid(bool value);
void set_park(bool value);
void set_wing(bool value);
void set_descore(bool value);

bool wing_macro_clamp = false;

void score_7_mid() {
	chassis.arcade(0, 0);
	set_score_mid(false);
	intake_spin(400);
	set_pto(true);
	pros::delay(1750);
	intake_spin(200);
	pros::delay(500);
	intake_spin(0);
}

uint32_t intake_run_time = 0;

void intake_set_state(IntakeState state) {
	current_state = state;
	
	// Handle state-specific behavior
	switch (state) {
		case INTAKE:
			set_score_mid(false);
			intake_spin(600);
		set_pto(false);
			break;
		case SCORE_MID:
		set_score_mid(true);
			intake_spin(600);
		set_pto(true);
			break;
		case SCORE_LOW:
		set_score_mid(false);
			intake_spin(-200);
		set_pto(true);
			break;
		case SCORE_HIGH:
		set_score_mid(false);
		set_pto(true);
			intake_spin(600);
			break;
		case IDLE:

			intake_stop();
			break;
	}
}

IntakeState intake_get_state() {
	return current_state;
}