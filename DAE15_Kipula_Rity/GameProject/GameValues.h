#pragma once

// UI Values
static const float GUI_HEIGHT{ 150.f };
static const float GUI_OFFSET{ 00.f };

// Global Values

static const float INF{ 100000.f };
static const float DEFAULT_ANIMATION_UPDATE{ .115f };
static const float WORLD_ANIMATION_UPDATE{ .35f };
static const float WORLD_MARGIN_TOP{ 10 };

static const float DEFAULT_DEATH_TIME{ 0.15f };
static const float DEFAULT_ENTITY_WIDTH{ 40 }; 
static const float DEFAULT_ENTITY_HEIGHT{ 40 };
static const float DEFAULT_ENTITY_DECELERATION{ 250 };

static const float INVINCIBILITY_TIME{ 1 };

struct PlayerData {
	int lives;
	int health;
	int score;
};
// Scene

static const float SCENE_TRANSITION_TIME{ .5f };
static const float SCENE_INITIAL_DARKNESS{ .2f };
static const float MAX_SCENE_AMOUNT{ 2 };

// Physics stuff ig???

static const float GRAVITY{ 1500 };
static const float FAKE_AIR_PRESSURE{ 1250 };
static const float MINIMUM_IMPULSE_LENGTH{10};

// Player values

static const int KIRBY_MAX_HEALTH{ 6 };
static const int KIRBY_MAX_LIVES{ 5 };

static const float KIRBY_LEAVE_TIME{ (DEFAULT_ANIMATION_UPDATE * 2) };
static const float KIRBY_MOVEMENT_SPEED{ 270 };
static const float KIRBY_ACCELERATION_SPEED{ 550 };
static const float KIRBY_JUMP_POWER{ (1250 * 12) };
static const float KIRBY_JUMP_MAX_TIME{ 0.35f };
static const float KIRBY_FLIP_SIDE_TIME{ .125f };
static const float KIRBY_SQUISH_TIME{ .08f };
static const float KIRBY_KNOCKBACK_ON_HIT{ 450 };
static const float KIRBY_STUN_TIME{ .35f };
static const float KIRBY_SHOOT_GROUND_ANIMATION_UPDATE{ .1f };
static const float KIRBY_SHOOTING_TIME{ KIRBY_SHOOT_GROUND_ANIMATION_UPDATE * 4 };

static const float KIRBY_ABSORB_RANGE{ 150 };
static const float KIRBY_EAT_RANGE{ 15 };
static const float KIRBY_ABSORB_POWER{ 15 }; 

static const float KIRBY_DEFLATE_TIME{ DEFAULT_ANIMATION_UPDATE*2 };
static const float KIRBY_BIG_RUN_UPDATE{ .15f };
static const float KIRBY_ENTITY_BIG_WIDTH{ 60 };
static const float KIRBY_ENTITY_BIG_HEIGHT{ 60 };

static const float KIRBY_FLYING_GRAVITY{ 200 };
static const float KIRBY_FLYING_MOVEMENT_SPEED{ 200 };
static const float KIRBY_IDLE_FLYING_ANIMATION_UPDATE{ .5f };
static const float KIRBY_RISING_FLYING_ANIMATION_UPDATE{ .08f };
static const float KIRBY_FLYING_BOBBING_OFFSET{ 5.f };
static const float KIRBY_FLYING_END_ANIMATION_UPDATE{ DEFAULT_ANIMATION_UPDATE * 4 };

static const float KIRBY_CLIMBING_WIDTH{ DEFAULT_ENTITY_WIDTH };
static const float KIRBY_CLIMBING_HEIGHT{ 60 };
static const float KIRBY_BIG_CLIMBING_HEIGHT{ 80 };


static const float KIRBY_DEATH_PAUSE_TIME{ 1.5f };
static const float KIRBY_DEATH_RESTART_TIME{ 5 };
static const float KIRBY_MAXIMUM_DEATH_FORCE{ 400 };
static const float KIRBY_DEATH_GRAVITY{ 300 };

// Enemies

static const float DEFAULT_ENEMY_ABILITY_COOLDOWN{ 3 };

// Waddle Doo values

static const float WADDLEDOO_MOVEMENT_SPEED{ 85 };
static const float WADDLEDOO_ANIMATION_UPDATE{ 0.325f };
static const float WADDLEDOO_GRAVITY{ GRAVITY / 8 };
static const float WADDLEDOO_JUMP_POWER{ 275 };

// Waddle Dee values

static const float WADDLEDEE_MOVEMENT_SPEED{ 85 };
static const float WADDLEDEE_ANIMATION_UPDATE{ 0.325f };

// Bronto Burt values

static const float BRONTO_AMPLITUDE{ 3200 };
static const float BRONTO_PERIOD{ 1.25f };
static const float BRONTO_MOVEMENT_SPEED{ 150 };
static const float BRONTO_ANIMATION_UPDATE{ 0.325f };

// Projectiles
static const float PROJECTILE_DEFAULT_WIDTH{ 30 };
static const float PROJECTILE_DEFAULT_HEIGHT{ 30 };

// Star

static const float STAR_SPEED{ 800 };
static const float STAR_RANGE{ INF };
static const float STAR_ANIMATION_UPDATE{ .05f };
static const float STAR_WIDTH{ 40 };
static const float STAR_HEIGHT{ 40 };
static const float STAR_DURATION{ 5 };

// Cloud 

static const float CLOUD_SPEED{ 800 };
static const float CLOUD_RANGE{ 150 };
static const float CLOUD_WIDTH{ 40 };
static const float CLOUD_HEIGHT{ 40 };
static const float CLOUD_DURATION{ .5f };

// Beam Power

static const float BEAM_STAR_HITBOX_SIZE{ 35.f };
static const float BEAM_STAR_SIZE{ 15.f };
static const float BEAM_LENGTH{ .75f };
static const float BEAM_TOTAL_ANGLE{ 110.f };
static const float BEAM_START_ANGLE{ 60.f };
static const float BEAM_MAX_RANGE{ 150.f };
static const int BEAM_MAX_SEGMENTS{ 5 };
static const float BEAM_ANIMATION_UPDATE{ DEFAULT_ANIMATION_UPDATE/2 };
