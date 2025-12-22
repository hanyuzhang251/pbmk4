#ifndef _AUTONS_H_
#define _AUTONS_H_

#include "autons_utils.h"
#include "intake.h"
#include "main.h"
#include "distance-reset.h"
#include "math.h"
#include "config.h"
/**
 * \file autons.h
 *
 * Autonomous mode declarations
 */

namespace auton_skills_namespace
{
    void skills();

    void mid_goal(bool auton = true);
}

void awp_14();

inline void elims_right9() {

    //tune dec 12 5pm
    chassis.setPose(48.5, 16, -90);

    intake_set_state(INTAKE);
    chassis.turnToHeading(-86, 100, {.minSpeed = 70});
    chassis.moveToPoint(22, 23, 1500, {.minSpeed = 70});
    pros::delay(500);
    set_matchloader(true);
    chassis.waitUntilDone();
    set_matchloader(false);
    chassis.moveToPose(9.2, 46, -20, 1200, {.lead = 0.5, .maxSpeed = 90, .minSpeed = 50});
    chassis.turnToHeading(-20, 50, {.minSpeed = 60});
    chassis.waitUntilDone();
    chassis.arcade(60, 20);
    pros::delay(200);
    set_matchloader(true);
    pros::delay(150);
    chassis.turnToHeading(-20, 50, {.minSpeed = 70});
    chassis.moveToPoint(20.5, 30.5, 1500, {.forwards = false, .minSpeed = 15, .earlyExitRange = 5});
    chassis.moveToPoint(30.5, 35.5, 1500, {.forwards = false, .minSpeed = 50, .earlyExitRange = 5});
    chassis.moveToPoint(39, 51, 1300, {.forwards = false, .minSpeed = 80});
    set_matchloader(true);
    chassis.turnToHeading(90, 550, {});
    chassis.waitUntilDone();
    match_load_reset(200, 0, 1);
    chassis.moveToPoint(26, 48.5, 600, {.forwards = false, .maxSpeed = 95, .minSpeed = 80});
    chassis.waitUntilDone();
    intake_set_state(SCORE_HIGH);
    chassis.arcade(-100, 0);
    pros::delay(400);
    chassis.arcade(-60, 0);
    pros::delay(1300);
    set_matchloader(false);
    match_load_reset(100, 0, 1);
    chassis.arcade(50, 0);
    pros::delay(300);
    set_matchloader(true);
    intake_set_state(INTAKE);
    chassis.moveToPoint(65, 47, 1300, {.maxSpeed = 45});
    chassis.waitUntilDone();
    chassis.arcade(45,0);
    pros::delay(200);
    hold_dist_and_reset(270, 0, 1, 190,2);
    chassis.arcade(-60, 0);
    pros::delay(80);
    chassis.moveToPoint(20, 48, 1000, {.forwards = false, .maxSpeed = 70});
    pros::delay(800);
    intake_set_state(SCORE_HIGH);
    chassis.arcade(-70, 0);
    pros::delay(400);
    chassis.arcade(-90, -50);
    pros::delay(300);
    chassis.arcade(-90, 50);
    pros::delay(300);
    chassis.turnToHeading(90, 300, {.minSpeed = 60});
    chassis.waitUntilDone();
    set_matchloader(false);;
    chassis.arcade(-60, 0);
    pros::delay(100);
    chassis.setPose(0, 0, 0);
    chassis.arcade(70, 0);
    pros::delay(200);
    chassis.turnToPoint(-7.8, 10, 200);
    chassis.moveToPoint(-7.8, 10, 900, {.maxSpeed = 100, .minSpeed = 60});
    chassis.turnToHeading(0, 400);
    chassis.waitUntilDone();
    set_wing(false);
    chassis.moveToPose(-9.7, 0, 0, 600, {.forwards = false, .maxSpeed = 120, .minSpeed = 80});
    chassis.moveToPose(-9.7, -5, 0, 300, {.forwards = false, .maxSpeed = 120, .minSpeed = 100});
    chassis.waitUntilDone();
    chassis.arcade(-127, 127);
    pros::delay(100);
    chassis.turnToHeading(0, 300, {.minSpeed = 90});
    chassis.arcade(-20, 20);
    return;
}

inline void elims_left9() {
    chassis.setPose(48.5, -16, -90);
    pros::delay(300);
    set_wing(true);
    intake_set_state(INTAKE);
    chassis.turnToHeading(-95, 100, {.minSpeed = 70});
    chassis.moveToPoint(24, -25, 1500, {.minSpeed = 70});
    pros::delay(500);
    set_matchloader(true);
    chassis.waitUntilDone();
    set_matchloader(false);;
    chassis.moveToPose(13, -46, 190, 1200, {.lead = 0.5, .maxSpeed = 90, .minSpeed = 50});
    chassis.turnToHeading(195, 50, {.minSpeed = 60});
    chassis.waitUntilDone();
    chassis.arcade(60, -10);
    pros::delay(250);
    set_matchloader(true);
    pros::delay(350);
    chassis.turnToHeading(190, 100, {.minSpeed = 60});
    chassis.moveToPoint(20.5, -30.5, 1500, {.forwards = false, .minSpeed = 15, .earlyExitRange = 5});
    chassis.moveToPoint(30.5, -35.5, 1500, {.forwards = false, .minSpeed = 50, .earlyExitRange = 5});
    chassis.moveToPoint(40, -55, 1300, {.forwards = false, .minSpeed = 80});
    chassis.turnToHeading(90, 700, {});
    chassis.waitUntilDone();
    set_matchloader(true);
    match_load_reset(200, 0, 4);
    chassis.moveToPoint(26, -48.5, 600, {.forwards = false, .maxSpeed = 95, .minSpeed = 80});
    chassis.waitUntilDone();
    intake_set_state(SCORE_HIGH);
    chassis.arcade(-100, 0);
    pros::delay(400);
    chassis.arcade(-40, 0);
    pros::delay(300);
    match_load_reset(800, 0, 4);
    chassis.arcade(50, 0);
    pros::delay(300);
    set_matchloader(true);
    set_matchloader(true);
    intake_set_state(INTAKE);
    chassis.turnToPoint(65,-45,50, {.minSpeed=60});
    chassis.waitUntilDone();
    chassis.arcade(70, 0);
    pros::delay(300);
    chassis.moveToPoint(75, -45, 500, {.maxSpeed = 65, .minSpeed = 55});
    chassis.waitUntilDone();
    chassis.arcade(45,0);
    pros::delay(200);
    hold_dist_and_reset(400, 0, 4, 190, 2);
    chassis.arcade(-60, 0);
    pros::delay(80);
    chassis.moveToPoint(20, -49, 1000, {.forwards = false, .maxSpeed = 70});
    pros::delay(800);
    intake_set_state(SCORE_HIGH);
    chassis.arcade(-70, 0);
    pros::delay(400);
    chassis.arcade(-90, -50);
    pros::delay(300);
    chassis.arcade(-90, 50);
    pros::delay(300);
    chassis.turnToHeading(90, 300, {.minSpeed = 60});
    chassis.waitUntilDone();
    set_matchloader(false);
    chassis.arcade(-60, 0);
    pros::delay(800);
    chassis.setPose(0, 0, 0);
    chassis.arcade(70, 0);
    pros::delay(200);
    chassis.turnToPoint(-7.8, 10, 200);
    chassis.moveToPoint(-7.8, 10, 900, {.maxSpeed = 100, .minSpeed = 60});
    chassis.turnToHeading(0, 400);
    chassis.waitUntilDone();
    set_wing(false);
    chassis.moveToPose(-9.7, 0, 0, 600, {.forwards = false, .maxSpeed = 120, .minSpeed = 80});
    chassis.moveToPose(-9.7, -6, 0, 500, {.forwards = false, .maxSpeed = 120, .minSpeed = 100});
    chassis.waitUntilDone();
    chassis.arcade(-100, 80);
    pros::delay(100);
    chassis.turnToHeading(0, 300, {.minSpeed = 90});
    chassis.arcade(-20, 20);
    return;
}

inline void LEFT张教练7() {
    //tuned dec 12 6pm
    chassis.setPose(48.5, -16, -90);

    intake_set_state(INTAKE);
    chassis.turnToHeading(-95, 100, {.minSpeed = 70});
    chassis.moveToPoint(21, -28, 1500, {.minSpeed = 70});
    pros::delay(500);
    set_matchloader(true);
    chassis.waitUntilDone();
    chassis.arcade(-40, 0);
    pros::delay(200);
    chassis.turnToPoint(36, -40, 600, {.forwards = true, .minSpeed=60});
    chassis.waitUntilDone();
    chassis.moveToPoint(36, -40, 1200, {.forwards = true, .minSpeed = 80});
    chassis.moveToPoint(42, -44, 600, {.forwards = true, .minSpeed = 80});
    chassis.turnToHeading(90,300, {});
    chassis.waitUntilDone();
    set_matchloader(true);
    match_load_reset(200, 0, 4);
    chassis.moveToPoint(78, -46.6,800, {.maxSpeed = 45});
    chassis.waitUntilDone();
    chassis.arcade(45,0);
    pros::delay(200);
    hold_dist_and_reset(350, 0, 4, 190, 2);
    chassis.arcade(-60, 0);
    pros::delay(80);
    chassis.moveToPoint(20, -47, 1200, {.forwards = false, .maxSpeed = 70});
    chassis.waitUntilDone();
    chassis.arcade(-90, 0);
    intake_set_state(SCORE_HIGH);
    chassis.arcade(-70, 0);
    pros::delay(400);
    chassis.arcade(-90, -50);
    pros::delay(300);
    chassis.arcade(-90, 50);
    pros::delay(300);
    chassis.turnToHeading(90, 300, {.minSpeed = 60});
    chassis.waitUntilDone();
    set_matchloader(false);;
    chassis.arcade(-60, 0);
    pros::delay(1100);
    chassis.setPose(0, 0, 0);
    chassis.arcade(70, 0);
    pros::delay(200);
    chassis.turnToPoint(-7.8, 10, 200);
    chassis.moveToPoint(-7.8, 10, 900, {.maxSpeed = 100, .minSpeed = 60});
    chassis.turnToHeading(0, 400);
    chassis.waitUntilDone();
    set_wing(false);
    chassis.moveToPose(-9.7, 0, 0, 600, {.forwards = false, .maxSpeed = 120, .minSpeed = 80});
    chassis.moveToPose(-9.7, -6, 0, 500, {.forwards = false, .maxSpeed = 120, .minSpeed = 100});
    chassis.waitUntilDone();
    chassis.arcade(-100, 80);
    pros::delay(100);
    chassis.turnToHeading(0, 300, {.minSpeed = 90});
    chassis.arcade(-20, 20);
    return;
}

inline void RIGHT张教练7() {
    //tune nov 14 2pm
    chassis.setPose(48.5, 16, -90);

    intake_set_state(INTAKE);
    chassis.turnToHeading(-85, 100, {.minSpeed = 70});
    chassis.moveToPoint(21, 25, 1500, {.minSpeed = 70});
    pros::delay(500);
    set_matchloader(true);
    chassis.waitUntilDone();
    chassis.arcade(-40, 0);
    pros::delay(200);
    chassis.turnToPoint(36, 40, 600, {.forwards = true, .minSpeed=60});
    chassis.waitUntilDone();
    chassis.moveToPoint(36, 40, 1200, {.forwards = true, .minSpeed = 80});
    chassis.moveToPoint(42, 44, 600, {.forwards = true, .minSpeed = 80});
    chassis.turnToHeading(90,300, {});
    chassis.waitUntilDone();
    set_matchloader(true);
    match_load_reset(200, 0, 1);
    chassis.moveToPoint(88, 47, 1000, {.maxSpeed = 45});
    chassis.waitUntilDone();
    chassis.arcade(45,0);
    pros::delay(200);
    hold_dist_and_reset(350, 0, 1, 190, 2);
    chassis.arcade(-60, 0);
    pros::delay(80);
    chassis.moveToPoint(20, 49, 1400, {.forwards = false, .maxSpeed = 70});
    pros::delay(1100);
    intake_set_state(SCORE_LOW);
    pros::delay(150);
    intake_set_state(SCORE_HIGH);
    chassis.arcade(-70, 0);
    pros::delay(400);
    chassis.arcade(-90, -50);
    pros::delay(300);
    chassis.arcade(-90, 50);
    pros::delay(300);
    chassis.turnToHeading(90, 300, {.minSpeed = 60});
    chassis.waitUntilDone();
    set_matchloader(false);;
    chassis.arcade(-60, 0);
    pros::delay(1100);
    chassis.setPose(0, 0, 0);
    chassis.arcade(70, 0);
    pros::delay(200);
    chassis.turnToPoint(-7.8, 10, 200);
    chassis.moveToPoint(-7.8, 10, 900, {.maxSpeed = 100, .minSpeed = 60});
    chassis.turnToHeading(0, 400);
    chassis.waitUntilDone();
    set_wing(false);
    chassis.moveToPose(-9.7, 0, 0, 600, {.forwards = false, .maxSpeed = 120, .minSpeed = 80});
    chassis.moveToPose(-9.7, -6, 0, 500, {.forwards = false, .maxSpeed = 120, .minSpeed = 100});
    chassis.waitUntilDone();
    chassis.arcade(-100, 80);
    pros::delay(100);
    chassis.turnToHeading(0, 300, {.minSpeed = 90});
    chassis.arcade(-20, 20);
    return;
}

void jiggle(int forward_speed, int backward_speed, int delay_time, int repetitions, int pause_time);

inline void NewQualLeft() {
    chassis.setPose(48.5, -16, -90);
    pros::delay(300);
    set_wing(true);
    intake_set_state(INTAKE);
    chassis.turnToHeading(-95, 100, {.minSpeed = 70});
    chassis.moveToPoint(24, -25, 1500, {.minSpeed = 70});
    pros::delay(500);
    set_matchloader(true);
    chassis.waitUntilDone();
    set_matchloader(false);;
    chassis.moveToPose(13, -46, 190, 1200, {.lead = 0.5, .maxSpeed = 90, .minSpeed = 50});
    chassis.turnToHeading(195, 50, {.minSpeed = 60});
    chassis.waitUntilDone();
    chassis.arcade(60, -10);
    pros::delay(250);
    set_matchloader(true);
    pros::delay(350);
    chassis.turnToHeading(190, 100, {.minSpeed = 60});
    chassis.moveToPoint(20.5, -30.5, 1500, {.forwards = false, .minSpeed = 15, .earlyExitRange = 5});
    chassis.moveToPoint(30.5, -35.5, 1500, {.forwards = false, .minSpeed = 50, .earlyExitRange = 5});
    chassis.moveToPoint(40, -55, 1300, {.forwards = false, .minSpeed = 80});
    chassis.turnToHeading(90, 700, {});
    chassis.waitUntilDone();
    set_matchloader(true);
    match_load_reset(200, 0, 4);
    chassis.moveToPoint(26, -48.5, 600, {.forwards = false, .maxSpeed = 95, .minSpeed = 80});
    chassis.waitUntilDone();
    intake_set_state(SCORE_HIGH);
    chassis.arcade(-100, 0);
    pros::delay(400);
    chassis.arcade(-40, 0);
    pros::delay(300);
    match_load_reset(800, 0, 4);
    chassis.arcade(50, 0);
    pros::delay(300);
    set_matchloader(true);
    set_matchloader(true);
    intake_set_state(INTAKE);
    chassis.turnToPoint(65,-45,50, {.minSpeed=60});
    chassis.waitUntilDone();
    chassis.arcade(70, 0);
    pros::delay(300);
    chassis.moveToPoint(70, -45, 500, {.maxSpeed = 60, .minSpeed = 50});
    chassis.waitUntilDone();
    chassis.arcade(45,0);
    pros::delay(200);
    hold_dist_and_reset(340, 0, 4, 190, 2);
    chassis.arcade(-60, 0);
    pros::delay(80);
    chassis.moveToPoint(52, -45, 700, {.forwards = false, .maxSpeed = 70});
    chassis.waitUntilDone();
    set_matchloader(false);
    pros::delay(200);
    chassis.turnToPoint(9, -11, 400, {.forwards = false});
    chassis.waitUntilDone();
    chassis.moveToPose(9, -11, 135, 500, {.forwards = false, .lead = 0.2, .maxSpeed = 100, .minSpeed=70});
    chassis.waitUntilDone();
    chassis.moveToPose(7, -9, 135, 600, {.forwards = false, .lead = 0.05, .maxSpeed = 100, .minSpeed=60});
    chassis.waitUntilDone();
    chassis.arcade(-60, 0);
    pros::delay(100);
    intake_set_state(SCORE_MID);
    chassis.arcade(-60, 0);
    pros::delay(220);
    chassis.turnToHeading(135, 60, {.minSpeed = 90});
    chassis.waitUntilDone();
    chassis.arcade(-15, 0);
    pros::delay(200);
    chassis.setPose(12, -12, chassis.getPose().theta);
    chassis.arcade(13, 0);
    pros::delay(200);
    chassis.arcade(0, 0);
    pros::delay(300);
    set_matchloader(false);;
    chassis.arcade(70, 0);
    pros::delay(200);
    chassis.moveToPose(34, -35, 135, 800, {.forwards = true, .lead = 0.05, .maxSpeed = 100, .minSpeed = 70});
    chassis.turnToHeading(90, 450);
    chassis.waitUntilDone();
    set_wing(false);
    chassis.moveToPose(9, -35, 90, 700, {.forwards = false, .lead = 0.05, .maxSpeed = 90, .minSpeed = 0});
    chassis.waitUntilDone();
    chassis.arcade(100, 0);
    pros::delay(50);
    chassis.arcade(0, 0);
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
    return;
}

inline void NewQualRight() {
    //tune nov 14 2pm
    chassis.setPose(48.5, 16, -90);

    intake_set_state(INTAKE);
    chassis.turnToHeading(-86, 100, {.minSpeed = 70});
    chassis.moveToPoint(22, 23, 1500, {.minSpeed = 70});
    pros::delay(500);
    set_matchloader(true);
    chassis.waitUntilDone();
    set_matchloader(false);
    chassis.moveToPose(9.2, 46, -20, 1200, {.lead = 0.5, .maxSpeed = 90, .minSpeed = 50});
    chassis.turnToHeading(-20, 50, {.minSpeed = 60});
    chassis.waitUntilDone();
    chassis.arcade(60, 20);
    pros::delay(200);
    set_matchloader(true);
    pros::delay(150);
    chassis.turnToHeading(-20, 50, {.minSpeed = 70});
    chassis.moveToPoint(20.5, 30.5, 1500, {.forwards = false, .minSpeed = 15, .earlyExitRange = 5});
    chassis.moveToPoint(30.5, 35.5, 1500, {.forwards = false, .minSpeed = 50, .earlyExitRange = 5});
    chassis.moveToPoint(39, 48, 1300, {.forwards = false, .minSpeed = 80});
    set_matchloader(true);
    chassis.turnToHeading(90, 550, {});
    chassis.waitUntilDone();
    set_matchloader(true);
    match_load_reset(100, 0, 1);
    chassis.moveToPoint(26, 48.5, 300, {.forwards = false, .maxSpeed = 95, .minSpeed = 80});
    chassis.waitUntilDone();
    intake_set_state(SCORE_HIGH);
    chassis.moveToPoint(26, 48.5, 300, {.forwards = false, .maxSpeed = 95, .minSpeed = 80});
    chassis.waitUntilDone();
    chassis.arcade(-100, 0);
    pros::delay(500);
    chassis.arcade(-50, 0);
    pros::delay(300);
    match_load_reset(400, 0, 1);
    pros::delay(100);
    chassis.arcade(60, 0);
    pros::delay(300);
    set_matchloader(true);
    intake_set_state(INTAKE);
    chassis.moveToPoint(65, 47, 950, {.maxSpeed = 55, .minSpeed = 45});
    chassis.waitUntilDone();
    chassis.arcade(45,0);
    pros::delay(200);
    hold_dist_and_reset(340, 0, 1, 190,2);
    chassis.arcade(-60, 0);
    pros::delay(80);
    chassis.moveToPoint(48, 47, 700, {.forwards = false, .maxSpeed = 70});
    chassis.waitUntilDone();
    set_matchloader(false);
    pros::delay(200);
    chassis.arcade(40,0);
    pros::delay(200);
    chassis.turnToPoint(12.5, 9, 600);
    chassis.waitUntilDone();
    chassis.moveToPose(12.5, 9, -135, 800, {.forwards = true, .lead = 0.2, .maxSpeed = 100});
    chassis.waitUntilDone();
    intake_set_state(SCORE_LOW);
    chassis.moveToPose(12.5, 9, -135, 900, {.forwards = true, .lead = 0.05, .maxSpeed = 50});
    chassis.waitUntilDone();
    chassis.arcade(60, 0);
    pros::delay(200);
    chassis.turnToHeading(-135, 50, {.minSpeed = 90});
    chassis.arcade(45, 0);
    pros::delay(120);
    chassis.setPose(12, 12, chassis.getPose().theta);
    chassis.arcade(-32, 0);
    pros::delay(200);
    chassis.arcade(0, 0);
    pros::delay(450);
    set_matchloader(false);
    chassis.arcade(-70, 0);
    pros::delay(200);
    chassis.arcade(0, 0);
    chassis.moveToPose(30, 34.6, -135, 600, {.forwards = false, .lead = 0.05, .maxSpeed = 90, .minSpeed = 60});
    chassis.turnToHeading(-90, 500);
    chassis.moveToPose(8, 34, -90, 700, {.forwards = true, .lead = 0.05, .maxSpeed = 100, .minSpeed = 0});
    chassis.waitUntilDone();
    chassis.arcade(-100, 0);
    pros::delay(50);
    chassis.arcade(0, -90);
    pros::delay(400);
    chassis.arcade(0, 0);
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
    return;
}

void auto_3p6(bool strong = false);

#endif // _AUTONS_H_
