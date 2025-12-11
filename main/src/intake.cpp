#include "main.h"
#include "intake.h"

#include "distance-reset.h"

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

void hold_dist_and_reset(uint32_t sample_time, double heading_mod, int quadrant, int distance) {
	const uint32_t end = pros::millis() + sample_time;

	pros::Task([sample_time, heading_mod, quadrant]() {
		match_load_reset(sample_time, heading_mod, quadrant);
	});

	constexpr int minout = 10;
	constexpr int maxout = 60;

	while (pros::millis() < end) {

		const int32_t measure = front_dist.get_distance();

		// mm to inches and times 5 for scaling
		int power = (measure - distance) / 25.4 * 5;

		if (std::abs(power) < minout) power = lemlib::sgn(power) * minout;
		if (std::abs(power) > maxout) power = lemlib::sgn(power) * maxout;

		chassis.arcade(power, 0);


		pros::delay(PROCESS_DELAY);
	}
}

void drive_until_distance(float heading_hold, const int power, const uint32_t ramp, const int dist, const int tolerance, const bool greater, uint32_t timeout) {
    printf("called\n");
    chassis.cancelAllMotions();

    float heading = std::fmod(heading_hold+360000, 360);
    if (heading > 180 && heading <= 360) {
            heading -=360;
        heading *= -1;
        }

    const uint32_t start_time = pros::millis();
    const uint32_t ramp_up_time_end = start_time + ramp;
    const int ramp_down_dist = 24 * 25.4;

    while (true) {
        float mult = static_cast<float>(pros::millis() - start_time) / static_cast<float>(ramp);

        if (pros::millis() > ramp_up_time_end) {
            mult = 1;
        }

        const float dist_diff = std::abs(front_dist.get_distance() - dist);
        if (dist_diff < ramp_down_dist) {
            mult = dist_diff/static_cast<float>(ramp_down_dist);
        }

        constexpr int minout = 12;
        float drive = power * mult;
        if (front_dist.get_distance() - dist < 0) drive *= -1;
        if (std::abs(drive) < minout) {
            drive = lemlib::sgn(drive) * minout;
        }

        float cheading = std::fmod(chassis.getPose().theta+360000, 360);
        bool mod = false;
        if (cheading > 180 && cheading <= 360) {
            cheading -=360;
        cheading *= -1;
        mod= true;
        }

        float theta_diff = cheading - heading;
    	// highligher may make std::max(6.0f, std::abs(theta_diff)) as incorrect for some type error, but it doesn't build otherise.
        chassis.arcade(drive, (mod ? 1 : -1 )* lemlib::sgn(theta_diff) * std::max(6.0f, std::abs(theta_diff)));

    printf("%f\n", power * mult);

        pros::delay(10);
        // (greater ? front_dist2_sensor.get_distance() > dist : front_dist2_sensor.get_distance() < dist) || dist_diff < static_cast<float>(tolerance) ||
        if (std::abs(dist_diff) < tolerance || pros::millis() > timeout + start_time) {
            chassis.cancelAllMotions();
            chassis.setBrakeMode(MOTOR_BRAKE_BRAKE);
            chassis.arcade(0, 0);
            pros::delay(200);;
            chassis.setBrakeMode(MOTOR_BRAKE_COAST);
            break;
        }
    }
}


IntakeState intake_get_state() {
	return current_state;
}