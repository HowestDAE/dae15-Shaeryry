#pragma once

// Global Values

static const float DEFAULT_ANIMATION_UPDATE{ .125 };

static const float DEFAULT_ENTITY_WIDTH{ 40 }; 
static const float DEFAULT_ENTITY_HEIGHT{ 40 };
static const float DEFAULT_ENTITY_DECELERATION{ 250 };

static const float INVINCIBILITY_TIME{ 1 };

// Physics stuff ig???

static const float GRAVITY{ 1500 };
static const float FAKE_AIR_PRESSURE{ 1250 };
static const float MINIMUM_IMPULSE_LENGTH{10};

// Player values

static const float KIRBY_MOVEMENT_SPEED{ 270 };
static const float KIRBY_ACCELERATION_SPEED{ 550 };
static const float KIRBY_JUMP_POWER{ (1250 * 12) };
static const float KIRBY_JUMP_MAX_TIME{ 0.35f };
static const float KIRBY_FLIP_SIDE_TIME{ .125f };
static const float KIRBY_SQUISH_TIME{ .08f };
static const float KIRBY_KNOCKBACK_ON_HIT{ 450 };
static const float KIRBY_STUN_TIME{ .35f };

static const float KIRBY_ABSORB_RANGE{ 150 };
static const float KIRBY_ABSORB_POWER{ 15 };
static const float KIRBY_DEFLATE_TIME{ DEFAULT_ANIMATION_UPDATE*2 };
static const float KIRBY_ENTITY_BIG_WIDTH{ 60 };
static const float KIRBY_ENTITY_BIG_HEIGHT{ 60 };

// Waddle Doo values

static const float WADDLEDOO_MOVEMENT_SPEED{ 85 };
static const float WADDLEDOO_ANIMATION_UPDATE{ 0.325f };