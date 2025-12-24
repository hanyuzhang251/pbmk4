#include "main.h"
#include "intake.h"

#include <ranges>

#include "distance-reset.h"

/**
 * \file intake.cpp
 *
 * Intake subsystem implementation
 */

pros::Motor intake_motor(INTAKE_MOTOR_PORT, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);

// Current intake state
static IntakeState current_state = IDLE;

uint32_t last_intake_command_time = 0;

bool matchloader_value = false;
bool pto_value = false;
bool score_mid_value = false;
bool park_value = false;
bool wing_value = false;
bool descore_value = false;
bool clamp_value = false;

JamState::JamState(pros::Motor* target, const uint32_t jam_tolerance, const uint32_t unjam_duration)
    : target(target), jam_tolerance(jam_tolerance), unjam_duration(unjam_duration) {
    jam_start = pros::millis();
}

void JamState::update() {
    if (target->get_target_velocity() == 0 || target->get_actual_velocity() != 0) {
        jam_start = pros::millis();
    }

    if (pros::millis() > unjam_end + jam_tolerance, pros::millis() - jam_start > jam_tolerance) {
        std::cout << "starting unjam\n";

        unjam_end = pros::millis() + unjam_duration;
    }
}

JamState intake_jam_state(nullptr, 50, 120);

void intake_init() {
    // Initialize intake motor
    intake_motor.tare_position();
    intake_motor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    intake_motor.move_velocity(0);

    intake_jam_state.target = &intake_motor;

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

int custom_vel = 0;

void set_custom_mid(int vel) {
    custom_vel = vel;
    intake_set_state(CUSTOM_MID);
}

void update_intake() {
    double intake_vel = 0;

    switch (current_state) {
    case INTAKE:
        set_score_mid(false);
        intake_vel = (600);
        set_pto(false);
        break;
    case SCORE_MID:
        set_score_mid(true);
        intake_vel = (600);
        set_pto(true);
        break;
    case SCORE_LOW:
        set_score_mid(false);
        intake_vel = (-200);
        set_pto(true);
        break;
    case SCORE_HIGH:
        set_score_mid(false);
        set_pto(true);
        intake_vel = (600);
        break;
    case IDLE:

        intake_stop();
        break;
    case SCORE_MID_SKILLS_MEDIUM: {
        set_score_mid(true);
        set_pto(true);
        intake_vel = (250);
        break;
    }
    case SCORE_MID_SKILLS_FAST: {
        set_score_mid(true);
        set_pto(true);
        intake_vel = (420);
        break;
    }
    case SCORE_MID_SKILLS: {
        set_score_mid(true);
        set_pto(true);
        intake_vel = (294);
        break;
    }
    case CUSTOM_MID: {
        set_score_mid(true);
        set_pto(true);
        intake_vel = (custom_vel);

    }
    }


    intake_jam_state.update();

    if (pros::millis() - last_intake_command_time < 200) {
        intake_jam_state.jam_start = pros::millis();
        intake_jam_state.unjam_end = 0;
    }

    if (intake_jam_state.unjam_end > pros::millis()) {
        intake_vel *= -127;
    }

    intake_spin(intake_vel);
}

bool wing_macro_clamp = false;

// void score_7_mid() {
// 	chassis.arcade(0, 0);
// 	set_score_mid(false);
// 	intake_spin(400);
// 	set_pto(true);
// 	pros::delay(1750);
// 	intake_spin(200);
// 	pros::delay(500);
// 	intake_spin(0);
// }

uint32_t intake_run_time = 0;

void intake_set_state(IntakeState state) {
    if (state != current_state) last_intake_command_time = pros::millis();

    current_state = state;
}

float power_mult = 1;

void hold_dist_and_reset(uint32_t sample_time, double heading_mod, int quadrant, int distance, int tolerance) {
    const uint32_t start = pros::millis();
    const uint32_t end = start + sample_time;

    intake_set_state(INTAKE);

    bool dsr_started = false;


    int minout = 1;
    constexpr int maxout = 80;

    int32_t prev_diff = 0;
    constexpr int move_tolerance = 12;
    uint32_t time_since_move = 0;
    constexpr uint32_t time_since_move_tolerance = 200;
    constexpr uint32_t DELAY = 20;

    constexpr float PM_INCREMENT = 3;
    power_mult = 1;
    while (pros::millis() < end) {
        const int32_t diff = front_dist.get_distance() - distance;

        if (lemlib::sgn(prev_diff) != lemlib::sgn(diff)) {
            power_mult = 1;
        }
        if (std::abs(diff - prev_diff) < move_tolerance && std::abs(diff) > tolerance * 25.4) {
            time_since_move += DELAY;
        }
        else {
            time_since_move = 0;

            prev_diff = diff;
            if (power_mult > 1) power_mult -= PM_INCREMENT;
            else power_mult = 1;
        }
        if (time_since_move > time_since_move_tolerance) {
            power_mult += PM_INCREMENT;
        }


        // mm to inches and times 5 for scaling
        int power = (std::pow(std::abs(diff) / 25.4, 5) + power_mult) * lemlib::sgn(diff);

        if (std::abs(power) < minout) power = lemlib::sgn(diff) * minout;
        if (std::abs(power) > maxout) power = lemlib::sgn(diff) * maxout;

        if (!dsr_started && std::abs(diff) <= tolerance || pros::millis() + 20 >= end) {
            dsr_started = true;
            pros::Task([end, heading_mod, quadrant]() {
                match_load_reset(end - pros::millis(), heading_mod, quadrant);
            });
        }

        chassis.arcade(power, 0);


        pros::delay(DELAY);
    }
}

void drive_until_distance(float heading_hold, const int power, const int dist, const int tolerance, float ramp_down, uint32_t timeout) {
    printf("called\n");
    chassis.cancelAllMotions();

    constexpr float MIN_OUT = 20;
    constexpr float MAX_OUT = 110;

    const int32_t ramp_down_mm = ramp_down * 25.4;

    const uint32_t end = pros::millis() + timeout;

    while (pros::millis() <= end)
    {
        const int32_t measure = front_dist.get_distance();
        const int32_t diff = measure - dist;
        const float diff_in = diff / 25.4f;

        float mult = std::min((std::abs(diff_in) > ramp_down ? 1 : std::abs(diff_in) / ramp_down) + 0.25f, 1.0f);

        float out = std::pow(std::abs(diff_in), 2);
        if (out < MIN_OUT) out = MIN_OUT;
        if (out > MAX_OUT) out = MAX_OUT;

        out *= lemlib::sgn(diff_in);
        out *= mult;

        chassis.arcade(out, 0);
    }

}

void score_7_mid() {
    chassis.cancelAllMotions();



    chassis.arcade(30, 0);
    set_matchloader(true);
    pros::delay(200);

    set_custom_mid(-600);
    pros::delay(200);

    intake_set_state(IDLE);
    pros::delay(100);

    chassis.arcade(0, 0);
    chassis.setBrakeMode(MOTOR_BRAKE_BRAKE);

    set_custom_mid(300);
    pros::delay(1300);
    intake_set_state(IDLE);
    pros::delay(300);

    chassis.arcade(70, 0);
    pros::delay(350);
    set_descore(true);
    chassis.arcade(-70, 0);
    pros::delay(600);

    chassis.arcade(80, 0);
    pros::delay(300);
    set_descore(false);
    chassis.arcade(-60, 0);
    pros::delay(350);
    chassis.arcade(0, 0);

    intake_set_state(SCORE_MID_SKILLS_FAST);
    pros::delay(300);
    intake_set_state(SCORE_MID_SKILLS);
    pros::delay(2200);

    chassis.setBrakeMode(MOTOR_BRAKE_COAST);

    intake_set_state(IDLE);

    chassis.arcade(20, 0);
    pros::delay(100);
    chassis.arcade(-40, 0);
    pros::delay(200);
    set_score_mid(true);
    pros::delay(500);
    chassis.arcade(30, 0);
    pros::delay(250);

}


IntakeState intake_get_state() {
    return current_state;
}
