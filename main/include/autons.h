#ifndef _AUTONS_H_
#define _AUTONS_H_

#include "autons_utils.h"
#include "intake.h"
#include "main.h"
#include "distance-reset.h"

#include "config.h"
/**
 * \file autons.h
 *
 * Autonomous mode declarations
 */

void auton_skills();
void auton_red_left();
void auton_red_right();
void auton_blue_left();
void auton_blue_right();

inline void awp_12(){
//tuned nov 14 2025 2:55am
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_COAST);
    chassis.setPose(-49.5, -18, 180);
    chassis.moveToPoint(-49, -34.5, 1300, {.maxSpeed = 90, .minSpeed = 70, .earlyExitRange = 0}, true);
    chassis.turnToHeading(-90, 450, {.minSpeed = 60}, true);
intake_set_state(IntakeState::INTAKE);
    chassis.waitUntilDone();
    set_matchloader(true);
    chassis.moveToPoint(-65, -45, 900, {.maxSpeed=60, .minSpeed = 45, .earlyExitRange = 35}, false);
    chassis.waitUntilDone();
    chassis.arcade(40, 0);
    pros::delay(150);
    chassis.arcade(-20, 0);
    pros::delay(150);
    chassis.arcade(40, 0);
    pros::delay(150);
    match_load_reset(120,0,3);
    pros::delay(20);
        chassis.arcade(-80,0);
        pros::delay(300);
        chassis.turnToHeading(-90,50,{.minSpeed=80});
    chassis.moveToPose(-18,-47,-90,600, {.forwards=false, .maxSpeed=110, .minSpeed=80,}, true);
    pros::delay(450);
intake_set_state(IntakeState::SCORE_HIGH);
    chassis.moveToPose(-18,-47,-90,300, {.forwards=false, .maxSpeed=120, .minSpeed=70,}, false);
    chassis.waitUntilDone();
    chassis.arcade(-100,0);
    pros::delay(300);
    set_matchloader(false);
    pros::delay(800);
   chassis.setPose(0,0,-90);
    chassis.turnToHeading(0,400,{.minSpeed=80});
    chassis.turnToHeading(-5,250,{.minSpeed=40});
    chassis.waitUntilDone();
intake_set_state(IntakeState::INTAKE);
chassis.setPose(-27,-43,chassis.getPose().theta);
    chassis.moveToPose(-25,-25,0,900, {.forwards = true, .horizontalDrift = 0, .lead = 0.2, .maxSpeed = 110, .minSpeed = 60, .earlyExitRange = 0}, false);
    chassis.moveToPose(-25.1,15,0,600, {.forwards = true, .horizontalDrift = 0, .lead = 0.1, .maxSpeed = 127, .minSpeed = 110, .earlyExitRange = 0}, true);
    pros::delay(200);
    set_matchloader(true);
    pros::delay(150);
    set_matchloader(false);
    chassis.waitUntilDone();
    chassis.moveToPose(-27.5,33,0,700, {.forwards = true, .horizontalDrift = 0, .lead = 0.1, .maxSpeed = 127, .minSpeed = 0, .earlyExitRange = 0}, true);
    pros::delay(100);
    set_matchloader(true);
    chassis.waitUntilDone();
    chassis.arcade(40,0);
    pros::delay(130);
    chassis.setPose(chassis.getPose().x,30,chassis.getPose().theta);
    chassis.arcade(35,0);
    pros::delay(100);
    chassis.turnToHeading(-53,80,{.minSpeed=60});
intake_set_state(IntakeState::IDLE);
    chassis.moveToPose(-20,15,-45,750, {.forwards=false,.lead=0.6, .maxSpeed=90, .minSpeed=50});
    chassis.waitUntilDone();
    chassis.moveToPose(-12,8,-45,400, {.forwards=false,.lead=0.3, .maxSpeed=100, .minSpeed=50});
    chassis.waitUntilDone();
    chassis.arcade(-50,0);
    pros::delay(200);
intake_set_state(IntakeState::SCORE_MID);
    chassis.turnToHeading(-45,60,{.minSpeed=80});
    chassis.waitUntilDone();
    chassis.arcade(-50,0);
    pros::delay(200);
    chassis.arcade(-15,0);
    pros::delay(600);
intake_set_state(IntakeState::INTAKE);
    chassis.setPose(-12,12,chassis.getPose().theta);
    set_matchloader(false);
    chassis.arcade(120,0);
    pros::delay(140);
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_COAST);
    chassis.moveToPoint(-42, 43, 1400, {.maxSpeed=100, .minSpeed = 70, .earlyExitRange = 0}, false);
    chassis.turnToHeading(-88,600,{.minSpeed=40});
    set_matchloader(true);
    chassis.waitUntilDone();
    match_load_reset(120,0,2);
intake_set_state(IntakeState::INTAKE);
    chassis.moveToPoint(-60, 45.4, 1000, {.maxSpeed=50, .minSpeed = 42}, false);
    chassis.waitUntilDone();
    chassis.arcade(45, 0);
    pros::delay(140);
    chassis.arcade(-20, 0);
    pros::delay(150);
    chassis.arcade(40, 0);
    pros::delay(250);
    chassis.arcade(-110,0);
    pros::delay(200);
    chassis.moveToPose(-18,45,-90,300, {.forwards=false, .maxSpeed=120, .minSpeed=90,}, false);
    chassis.waitUntilDone();
intake_set_state(IntakeState::SCORE_HIGH);
    chassis.arcade(-110,0);
    pros::delay(400);
intake_set_state(IntakeState::SCORE_LOW);
         pros::delay(200);
intake_set_state(IntakeState::SCORE_HIGH);
    chassis.arcade(20,0);
    pros::delay(150);
    chassis.arcade(-3,0);
 pros::delay(2000);
}

#endif // _AUTONS_H_
