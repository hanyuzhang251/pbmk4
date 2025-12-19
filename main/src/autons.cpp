#include "autons.h"

/**
 * \file autons.cpp
 *
 * Autonomous mode implementation
 */

constexpr float WALL_COORD = 71;

constexpr float MATCHLOAD_ENTER_SPEED_MAX = 70;
constexpr float MATCHLOAD_ENTER_SPEED_MIN = 15;
constexpr uint32_t MATCHLOAD_DURATION = 2000;

constexpr float LONG_GOAL_ENTER_SPEED_MIN = 110;
constexpr float LONG_GOAL_ENTER_SPEED_MAX = 70;
constexpr uint32_t LONG_GOAL_DURATION = 1000;

constexpr float LONG_GOAL_CROSS_MIN_SPEED = 80;
constexpr int LONG_GOAL_DIST_ALIGN = 435;

constexpr uint32_t WALL_FLUSH_TIME = 600;
constexpr float WALL_FLUSH_Y = 61.8;
constexpr float WALL_FLUSH_SPEED = 60;

void long_goals(const bool first)
{

#define pn (first?1:-1)
#define aj(a, b) (first?a:b)

#define chr_params chassis.getPose().theta,aj(90,-90),2,0.8f

    auto c_pose = []()
    {
        return chassis.getPose();
    };

    auto conditional_heading_reset = [](const float heading, const float predicted_heading, const float tolerance, const float acceptance)
    {
        const float diff = std::abs(heading - predicted_heading);

        if (diff > tolerance) return heading;

        return heading + acceptance * (predicted_heading - heading);
    };

    intake_set_state(INTAKE);

    // move to matchloader 1
    chassis.moveToPoint(pn* -47.5 +aj(0, 0), pn* 46 +aj(0, 0), 1000, {}, false);
    set_matchloader(true);
    chassis.turnToHeading(aj(-90, 90), 600, {}, false);
    match_load_reset(100, 0, aj(2,4));
    // enter matchloader 1
    chassis.moveToPoint(pn* -61, pn* 46, 300, {.maxSpeed = MATCHLOAD_ENTER_SPEED_MAX, }, false);
    // finish matchloading
    chassis.arcade(MATCHLOAD_ENTER_SPEED_MIN, 0);
    pros::delay(MATCHLOAD_DURATION);

    // cross to other side
    chassis.moveToPoint(c_pose().x + aj(5, -5), c_pose().y, 600, {.forwards = false}, false);
    chassis.turnToHeading(aj(-135, 45), 600, {}, false);
    chassis.moveToPoint(pn* -23, pn* 60, 1000, {.forwards = false, .minSpeed = LONG_GOAL_CROSS_MIN_SPEED, .earlyExitRange = 4}, false);
    set_matchloader(false);
    chassis.moveToPoint(pn* 40, pn* 61, 1500, {.forwards = false}, false);
    // flush with wall
    chassis.turnToHeading(aj(0, 180), 800, {}, false);
    const float side_distance = static_cast<float>(find_dist(right_dist, right_dist_offset, 0, Dir::Right, 100));
    chassis.setPose(pn* (WALL_COORD - side_distance), c_pose().y, c_pose().theta);

    // move to long goal
    drive_until_distance(0, 119, 450, 1, 0, 850);
    chassis.turnToHeading(aj(90, -90), 600, {}, false);
    chassis.moveToPoint(pn* 26, pn* (47 +1), 600, {.forwards = false, .maxSpeed = LONG_GOAL_ENTER_SPEED_MAX, }, false);
    // scoring
    intake_set_state(SCORE_HIGH);
    chassis.arcade(-LONG_GOAL_ENTER_SPEED_MIN, 0);
    pros::delay(LONG_GOAL_DURATION);

    // reset pose at long goal
    match_load_reset(MATCHLOAD_DURATION, 0, aj(1, 3));

    // enter matchloader 2
    intake_set_state(INTAKE);
    set_matchloader(true);
    chassis.moveToPoint(pn* 61, pn* 46, 700, {.maxSpeed = MATCHLOAD_ENTER_SPEED_MAX,}, false);
    chassis.arcade(MATCHLOAD_ENTER_SPEED_MIN, 0);
    // finish matchloading while running reset

    chassis.setPose(c_pose().x, c_pose().y, conditional_heading_reset(chr_params));
    match_load_reset(MATCHLOAD_DURATION, 0, aj(1, 3));

    // move to long goal
    chassis.moveToPoint(pn* 26, pn* (47 +1), 1000, {.forwards = false, .maxSpeed = LONG_GOAL_ENTER_SPEED_MAX,}, false);
    // scoring
    intake_set_state(SCORE_HIGH);
    chassis.arcade(-LONG_GOAL_ENTER_SPEED_MIN, 0);
    pros::delay(LONG_GOAL_DURATION);

    // reset pose at long goal
    chassis.setPose(c_pose().x, c_pose().y, conditional_heading_reset(chr_params));
    match_load_reset(MATCHLOAD_DURATION, 0, aj(1, 3));

    set_matchloader(false);
}

void park_cross(const bool first)
{
#define pn (first?1:-1)
#define aj(a, b) (first?a:b)
    // position to park zone
    intake_set_state(aj(IDLE, INTAKE));
    chassis.moveToPose(pn* 63.5, pn* 20, aj(170, -10), 1500, {.horizontalDrift = 8, .minSpeed = 60, .earlyExitRange = 2}, false);
    chassis.turnToHeading(aj(170, -10), 300, {}, false);
    chassis.arcade(60, 0);
    pros::delay(600);

    // enter park zone
    intake_set_state(INTAKE);
    // sharp to initially enter
    chassis.arcade(90, 0);
    pros::delay(350);
    // slow cross
    chassis.arcade(70, 0);
    const uint32_t cross_time = aj(3100,2000);
    constexpr uint32_t drop_time = 900;
    pros::delay(drop_time);
    if (first) set_matchloader(true);
    pros::delay(cross_time - drop_time);

    if (!first) return;

    // correct heading
    chassis.turnToHeading(180, 600, {}, false);
    // back up
    chassis.arcade(-60, 0);
    pros::delay(800);
    chassis.arcade(0, 0);
}

void skills()
{
    // for coordinates and heading, they are in the format of `[target] +[adjustment] +[tuning]`
    // target is the point of interest, adjustment is the number added during routing, and tuning is to adjust when tuning.

    chassis.setPose(-47, 14.5, 90);

    set_wing(true);

    // 1. score matchload +1 in mid goal

    // collect 4 stack
    intake_set_state(INTAKE);
    chassis.moveToPoint(-23.5 +4 , 23.5 +4, 1000, {}, false);

    // position to mid goal
    chassis.swingToHeading(-45, DriveSide::RIGHT, 600, {}, false);
    chassis.moveToPoint(-14 +0, 14 +0, 1000, {.forwards = false}, true);
    // begin scoring early
    pros::delay(500);
    intake_set_state(SCORE_MID);
    chassis.waitUntilDone();
    // finish scoring
    pros::delay(800);

    // reset pose at mid goal
    chassis.setPose(-14, 14, chassis.getPose().theta);

    // 2. long goal 1

    long_goals(true);

    // 3. mid goal

    park_cross(true);

    // reset pose
    const float side_distance = find_dist(left_dist, left_dist_offset, M_PI, Dir::Left, 100);
    chassis.setPose(WALL_COORD - side_distance, -17.5, chassis.getPose().theta);

    set_matchloader(false);

    // collect one from four stack
    chassis.turnToPoint(25.25, -22, 800, {}, false);
    chassis.moveToPoint(25.25 -3, -22 -1, 1000, {}, false);

    // move to mid goal
    chassis.turnToHeading(135, 600, {}, false);
    chassis.moveToPoint(14, -14, 800, {.forwards = false, .minSpeed = 32, .earlyExitRange = 2}, false);
    chassis.arcade(-32, 0);
    pros::delay(600);

    // score
    intake_set_state(SCORE_MID);
    pros::delay(3500);

    // reset pose at mid goal
    chassis.setPose(14, -14, chassis.getPose().theta);

    // 4. long goal 2

    long_goals(false);

    // 5. park

    park_cross(false);
}