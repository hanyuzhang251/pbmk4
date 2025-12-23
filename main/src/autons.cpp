#include "autons.h"

/**
 * \file autons.cpp
 *
 * Autonomous mode implementation
 */

constexpr float WALL_COORD = 71;

auto c_pose()
{
    return chassis.getPose();
}

auto conditional_heading_reset(const float heading, const float predicted_heading, const float tolerance,
                               const float acceptance)
{
    const float diff = std::abs(heading - predicted_heading);

    if (diff > tolerance)
    {
        std::cout << heading << " OUTSIDE TOLERANCE\n";
        return heading;
    }

    return heading + acceptance * (predicted_heading - heading);
}

namespace auton_skills_namespace
{
    constexpr float MATCHLOAD_ENTER_SPEED_MAX = 57;
    constexpr float MATCHLOAD_ENTER_SPEED_MIN = 20;
    constexpr uint32_t MATCHLOAD_DURATION = 1800;

    constexpr float LONG_GOAL_ENTER_SPEED_MIN = 110;
    constexpr float LONG_GOAL_ENTER_SPEED_MAX = 70;
    constexpr uint32_t LONG_GOAL_DURATION = 3100;
    constexpr uint32_t LONG_GOAL_RAM_DURATION = 500;

    constexpr float LONG_GOAL_CROSS_MIN_SPEED = 80;
    constexpr int LONG_GOAL_DIST_ALIGN = 435;

    constexpr uint32_t WALL_FLUSH_TIME = 600;
    constexpr float WALL_FLUSH_Y = 61.8;
    constexpr float WALL_FLUSH_SPEED = 60;

    void long_goals(const bool first)
    {
#define pn (first?1:-1)
#define aj(a, b) (first?a:b)

#define chr_params chassis.getPose().theta,aj(90,-90),5,0.7f


        // move to matchloader 1
        chassis.moveToPoint(pn * -47.5 + aj(0, 0), pn * 46 + aj(0, 0), 1000, {}, false);
        set_matchloader(true);
        chassis.turnToHeading(aj(-90, 90), 600, {}, false);
        match_load_reset(100, 0, aj(2, 4));
        // enter matchloader 1
        intake_set_state(INTAKE);
        chassis.moveToPoint(pn * -61, pn * 46, aj(400, 440), {.maxSpeed = MATCHLOAD_ENTER_SPEED_MAX,}, false);
        // finish matchloading
        chassis.arcade(MATCHLOAD_ENTER_SPEED_MIN, 0);
        pros::delay(MATCHLOAD_DURATION);

        // cross to other side
        chassis.moveToPoint(c_pose().x + aj(5, -5), c_pose().y, 600, {.forwards = false}, false);
        chassis.turnToHeading(aj(-135, 45), 600, {}, false);
        chassis.moveToPoint(pn * -23, pn * 60, 1000, {
                                .forwards = false, .minSpeed = LONG_GOAL_CROSS_MIN_SPEED, .earlyExitRange = 4
                            }, false);
        set_matchloader(false);
        chassis.moveToPoint(pn * 40, pn * 61, 1500, {.forwards = false}, false);
        // flush with wall
        chassis.turnToHeading(aj(0, 180), 650, {}, false);
        const float side_distance = static_cast<float>(find_dist(right_dist, right_dist_offset, 0, Dir::Right, 100));
        chassis.setPose(pn * (WALL_COORD - side_distance), c_pose().y, c_pose().theta);

        // move to long goal
        drive_until_distance(0, 119, 470, 1, 0, 850);
        chassis.turnToHeading(aj(90, -90), 600, {}, false);
        // move straight backward, actually more consistent here
        chassis.arcade(-LONG_GOAL_ENTER_SPEED_MAX, 0);
        pros::delay(450);
        // scoring
        intake_set_state(SCORE_HIGH);
        chassis.arcade(-LONG_GOAL_ENTER_SPEED_MIN, 0);
        pros::delay(LONG_GOAL_RAM_DURATION);
        chassis.arcade(0, 0);
        pros::delay(LONG_GOAL_DURATION - LONG_GOAL_RAM_DURATION + aj(0, 100));

        // reset pose at long goal
        match_load_reset(100, 0, aj(1, 3));

        // enter matchloader 2
        intake_set_state(INTAKE);
        set_matchloader(true);
        chassis.moveToPoint(pn * 61, pn * 46, 800, {.maxSpeed = MATCHLOAD_ENTER_SPEED_MAX,}, false);
        chassis.arcade(MATCHLOAD_ENTER_SPEED_MIN, 0);
        // finish matchloading while running reset

        chassis.setPose(c_pose().x, c_pose().y, conditional_heading_reset(chr_params));
        match_load_reset(MATCHLOAD_DURATION, 0, aj(1, 3));

        // move to long goal
        chassis.moveToPoint(pn * 26, pn * (47 + aj(0.5f, 0.5f)), 1000,
                            {.forwards = false, .maxSpeed = LONG_GOAL_ENTER_SPEED_MAX,}, false);
        // scoring
        intake_set_state(SCORE_HIGH);
        chassis.arcade(-LONG_GOAL_ENTER_SPEED_MIN, 0);
        pros::delay(LONG_GOAL_RAM_DURATION);
        chassis.arcade(0, 0);
        pros::delay(LONG_GOAL_DURATION - LONG_GOAL_RAM_DURATION + aj(100, 200));

        // reset pose at long goal
        chassis.setPose(c_pose().x, c_pose().y, conditional_heading_reset(chr_params));
        match_load_reset(100, 0, aj(1, 3));

        set_matchloader(false);
    }

    void park_cross(const bool first)
    {
#define pn (first?1:-1)
#define aj(a, b) (first?a:b)
        // position to park zone
        intake_set_state(aj(SCORE_HIGH, INTAKE));
        chassis.moveToPose(pn * 63, pn * 16, aj(170, -10), 1500,
                           {.horizontalDrift = 8, .minSpeed = 60, .earlyExitRange = 2}, false);
        chassis.turnToHeading(aj(170, -10), 300, {}, false);

        if (!first) return;

        // enter park zone
        intake_set_state(INTAKE);
        // cross
        chassis.arcade(80, 0);
        const uint32_t cross_time = aj(3000, 1300);
        constexpr uint32_t drop_time = 2300;
        pros::delay(drop_time);
        if (first) set_matchloader(true);
        pros::delay(std::max(cross_time - drop_time, 1UL));

        // correct heading
        chassis.turnToHeading(180, 600, {}, false);
        // back up
        chassis.arcade(-70, 0);
        pros::delay(800);
        chassis.arcade(0, 0);
    }

    void mid_goal(const bool auton)
    {
        if (!auton)
        {
            chassis.setPose(0, 0, 90);
            match_load_reset(100, 0, 1);
        }

        set_matchloader(false);

        park_cross(true);

        // reset pose
        const float side_distance = find_dist(left_dist, left_dist_offset, M_PI, Dir::Left, 100);
        chassis.setPose(WALL_COORD - side_distance, -17.5, chassis.getPose().theta);

        set_matchloader(false);

        // collect one from four stack
        chassis.turnToPoint(20.5 + 5.5, -20.5 - 6.5, 800, {}, false);
        chassis.moveToPoint(20.5 + 5.5, -20.5 - 6.5, 1000, {}, false);

        // move to mid goal
        chassis.turnToHeading(135, 600, {}, false);
        chassis.moveToPoint(14 + 2, -14, 800, {.forwards = false, .maxSpeed = 40, .earlyExitRange = 2}, false);
        chassis.arcade(-20, 0);

        // score
        intake_set_state(SCORE_MID_SKILLS);
        pros::delay(500);
        // move forward slightly
        chassis.arcade(20, 0);
        pros::delay(400);
        chassis.arcade(0, 0);
        pros::delay(1700);
        // ram
        chassis.arcade(-20, 0);
        pros::delay(500);

        intake_set_state(IDLE);
    }

    void skills()
    {
        // for coordinates and heading, they are in the format of `[target] +[adjustment]/[tuning]`
        // target is the point of interest, adjustment is the number added during routing, and tuning is to adjust when tuning.

        chassis.setPose(-47, 14.5, 90);

        set_wing(true);

        // 1. score matchload +1 in mid goal

        // collect 4 stack
        intake_set_state(INTAKE);
        chassis.moveToPoint(-23.5 + 6.5, 23.5 + 6.5, 1000, {}, false);

        // position to mid goal
        chassis.swingToHeading(-45, DriveSide::RIGHT, 600, {}, false);
        chassis.moveToPoint(-14 + 1, 14 + 1, 1000, {.forwards = false}, true);
        // begin scoring early
        pros::delay(500);
        intake_set_state(SCORE_MID);
        chassis.waitUntilDone();
        // finish scoring
        pros::delay(650);

        // reset pose at mid goal
        chassis.setPose(-14, 14, chassis.getPose().theta);

        intake_set_state(SCORE_HIGH);

        // 2. long goal 1

        long_goals(true);

        // 3. mid goal

        mid_goal();

        // reset pose at mid goal
        chassis.setPose(14, -14, chassis.getPose().theta);


        // 4. long goal 2

        long_goals(false);

        // 5. park

        park_cross(false);

        // enter park zone
        intake_set_state(INTAKE);

        // cross
        chassis.arcade(80, 0);
        pros::delay(2000);

        chassis.arcade(-80, 0);
        pros::delay(500);

        chassis.arcade(0, 0);
    }
}

constexpr int MATCHLOAD_DISTANCE = 195;

constexpr uint32_t MATCHLOAD_3_TIME = 550;

uint32_t long_score_time(const int blocks)
{
    return static_cast<uint32_t>(1000.0 * (0.5 + std::pow(blocks, 1.7) / 8.0));
}

#define lr (left?1:-1)
#define aj(a, b) (left?a:b)

void awp_14()
{
    constexpr uint32_t FINAL_STAGE_RESERVE = 4000;

    const uint32_t start = pros::millis();
    const uint32_t end = start + 15000;

    auto c_pose = []()
    {
        return chassis.getPose();
    };

    chassis.setPose(-46.5, -1.8, 0);

    // grab alliance preload & shove
    intake_set_state(INTAKE);
    chassis.moveToPoint(-46.5, 10, 500, {}, false);

    // move to matchloader
    chassis.moveToPoint(-46.5, -47, 1500, {.forwards = false}, false);
    chassis.turnToHeading(-90, 600, {}, false);
    // enter matchloader
    drive_until_distance(-90, 119, MATCHLOAD_DISTANCE, 0, 0, 400);
    chassis.arcade(20, 9);
    // matchload three
    match_load_reset(MATCHLOAD_3_TIME, 0, 3);

    // move to long goal
    chassis.moveToPoint(-20, -47, 1000, {.forwards = false, .earlyExitRange = 12}, false);
    intake_set_state(SCORE_HIGH);
    chassis.arcade(-127, 0);
    pros::delay(300);
    chassis.arcade(0, 0);

    // reset pose at long goal
    chassis.setPose(c_pose().x, c_pose().y, conditional_heading_reset(c_pose().theta, -90, 5, 0.7f));
    match_load_reset(long_score_time(5), 0, 3);

    // swing to center blocks
    chassis.swingToHeading(10, DriveSide::RIGHT, 600, {.earlyExitRange = 3,}, false);

    // collect first stack
    intake_set_state(INTAKE);
    chassis.moveToPoint(-22.5 +1, -22.5 +3, 1000, {.earlyExitRange = 4}, false);

    // collect second stack
    chassis.moveToPoint(-22.5, 22.5, 1000, {}, false);

    // move to mid goal
    chassis.turnToHeading(-45, 600, {.earlyExitRange = 3}, false);
    chassis.moveToPoint(-14, 14, 800, {.forwards = false, .maxSpeed = 40}, false);

    // score
    intake_set_state(SCORE_MID);
    chassis.arcade(-20, 0);
    pros::delay(500);

    // reset pose
    chassis.setPose(-14, 14, c_pose().theta);

    chassis.arcade(20, 0);
    pros::delay(400);
    chassis.arcade(0, 0);
    // score for as long as we can
    pros::delay(std::max(end - FINAL_STAGE_RESERVE - pros::millis(), 100UL));

    // move to matchloader
    chassis.moveToPoint(-47.5, 47, 1000, {}, false);
    chassis.turnToHeading(-90, 600, {.earlyExitRange = 3}, false);

    // enter matchloader
    chassis.moveToPoint(-61, 47, 500, {.minSpeed = 20, .earlyExitRange = 5}, false);
    chassis.arcade(20, 0);
    // matchload three
    match_load_reset(MATCHLOAD_3_TIME, 0, 2);

    // move to long goal
    chassis.moveToPoint(-20, -47, 1000, {.forwards = false, .earlyExitRange = 12}, false);
    intake_set_state(SCORE_HIGH);
    chassis.arcade(-127, 0);
    pros::delay(300);
    chassis.arcade(0, 0);
}

void stack_undergoal(const bool left)
{
    // for coordinates and heading, they are in the format of `[target] +[adjustment]/[tuning]`
    // target is the point of interest, adjustment is the number added during routing, and tuning is to adjust when tuning.

    chassis.setPose(-47, lr* 14.5, 90);

    // collect blocks
    intake_set_state(INTAKE);
    chassis.moveToPoint(-23.5 +1, lr*(23.5+4), 1000, {.minSpeed = 40, .earlyExitRange = 2}, true);
    pros::delay(400);
    set_matchloader(true);
    chassis.waitUntilDone();
    chassis.moveToPoint(-7 +aj(-10.5f, -5), lr*(36.5 +5 +4), 1300, {.minSpeed = 30, .earlyExitRange = 5}, true);
    pros::delay(160);
    set_matchloader(false);
    chassis.waitUntilDone();
    set_matchloader(true);
    chassis.arcade(30, 0);
    pros::delay(200);

    // move to long goal

    // current pose, target point, adjust for exit, tuning value, in that order
    chassis.moveToPoint(c_pose().x -14 -3 , c_pose().y + lr*(+13 +1) +aj(0, 7.5), 1000, {.forwards = false, .minSpeed = 30, .earlyExitRange = 4}, false);

    // align
    chassis.arcade(-127, lr* 127);
    intake_set_state(SCORE_LOW);
    pros::delay(350);
    if (!left)
    {
        intake_set_state(IDLE);
        pros::delay(100);
    }
    intake_set_state(SCORE_HIGH); // start scoring early
    chassis.arcade(-127, lr* -127);
    pros::delay(200);
    chassis.arcade(-127, 0);
    pros::delay(350);
    chassis.arcade(0, 0);

    pros::delay(long_score_time(5) - 900);
    chassis.arcade(-127, 0);
    pros::delay(300);
    chassis.arcade(0, 0);
    chassis.setPose(c_pose().x, c_pose().y, conditional_heading_reset(c_pose().theta, -90, 5, 0.7f));
    match_load_reset(100, 0, aj(2, 3));
}

void wing(const bool strong, const uint32_t end, const uint32_t extra_time = 0)
{
    if (strong)
    {
        chassis.arcade(-90, 0);
        pros::delay(500 + extra_time);
        chassis.arcade(-80, 127);
        pros::delay(end - pros::millis() - 20);
    } else
    {
        chassis.arcade(-85, 0);
        pros::delay(900 + extra_time);
        chassis.arcade(-85, 127);
        pros::delay(end - pros::millis() - 20);
    }
}

void auto_3p6(const bool strong)
{
    const uint32_t end = pros::millis() + 15000;

    stack_undergoal(true);

    // enter matchloader 1
    intake_set_state(INTAKE);
    chassis.moveToPoint( -61,  46, 350, {.minSpeed = auton_skills_namespace::MATCHLOAD_ENTER_SPEED_MIN,}, false);
    chassis.moveToPoint( -61,  46, 450, {.maxSpeed = auton_skills_namespace::MATCHLOAD_ENTER_SPEED_MAX,}, false);
    // finish matchloading
    chassis.arcade(auton_skills_namespace::MATCHLOAD_ENTER_SPEED_MIN, 0);
    match_load_reset(   (MATCHLOAD_3_TIME), 0, 2);

    chassis.moveToPoint(-47, 47, 800, {.forwards = false}, false);
    chassis.turnToHeading(-45, 600, {.minSpeed = 3, .earlyExitRange = 2}, false);
    chassis.moveToPoint(-14 +3, 14 -3 -0.5f, 1500, {.forwards = false, .minSpeed = 30, .earlyExitRange = 2}, true);
    intake_set_state(SCORE_LOW);
    pros::delay(500);
    intake_set_state(IDLE);
    chassis.waitUntilDone();
    intake_set_state(SCORE_MID);
    chassis.arcade(-30, 0);
    pros::delay(500);
    chassis.setPose(-14, 14, c_pose().theta);
    chassis.arcade(20, 0);
    pros::delay(300);
    chassis.arcade(0, 0);
    pros::delay(400);

    chassis.moveToPoint(-40, 41, 1000, {}, false);
    intake_set_state(IDLE);
    chassis.turnToHeading(-90, 600, {.minSpeed = 3, .earlyExitRange = 2}, false);
    wing(strong, end);
    chassis.arcade(0, 0);
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_COAST);
}

void auto_6(const bool left, const bool strong)
{
    const uint32_t end = pros::millis() + 15000;

    if (!left) set_wing(true);

    stack_undergoal(left);
    set_matchloader(false);

    intake_set_state(IDLE);

    chassis.swingToHeading(180, DriveSide::LEFT, 600, {.minSpeed = 3, .earlyExitRange = 2}, false);
    chassis.arcade(30, 0);
    pros::delay(100);
    chassis.turnToHeading(-90, 600, {}, false);
    set_wing(false);
    wing(strong, end, 250);
}