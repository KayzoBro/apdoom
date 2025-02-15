//
// Copyright(C) 2023 David St-Louis
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
//
// *Interface header with the underlying C++ archipelago library*
//

#ifndef _APDOOM_
#define _APDOOM_


#ifdef __cplusplus
extern "C"
{
#endif


#define APDOOM_VERSION "0.2.1"
#define APDOOM_VERSION_TEXT APDOOM_VERSION " (BETA)"
#define APDOOM_VERSION_FULL_TEXT "APDOOM " APDOOM_VERSION_TEXT


//#define FIRST_EP_ONLY 1

#ifdef FIRST_EP_ONLY
#define AP_EPISODE_COUNT 1
#else
#define AP_EPISODE_COUNT 3
#endif
#define AP_LEVEL_COUNT 9
#define AP_NUM_POWERS 6
#define AP_NUM_AMMO 4
#define AP_NUM_WEAPONS 9
#define AP_CHECK_MAX 64 // Arbitrary number
#define AP_MAX_THING 1024 // Twice more than current max for every level


typedef struct
{
    int doom_type;
    int index;
} ap_thing_info_t;


typedef struct
{
    int keys[3];
    int use_skull[3];
    int check_count;
    int thing_count;
    ap_thing_info_t thing_infos[AP_MAX_THING];

} ap_level_info_t;


typedef struct
{
    int completed;
    int keys[3];
    int check_count;
    int has_map;
    int unlocked;
    int checks[AP_CHECK_MAX];

} ap_level_state_t;


typedef struct
{
    int health;
    int armor_points;
    int armor_type;
    int backpack; // Has backpack or not
    int ready_weapon; // Last weapon held
    int kill_count; // We accumulate globally
    int item_count;
    int secret_count;
    int powers[AP_NUM_POWERS];
    int weapon_owned[AP_NUM_WEAPONS];
    int ammo[AP_NUM_AMMO];
    int max_ammo[AP_NUM_AMMO]; // Could be deduced by checking backpack

} ap_player_state_t;


typedef struct
{
    ap_level_state_t level_states[AP_EPISODE_COUNT][AP_LEVEL_COUNT];
    ap_player_state_t player_state;
    int ep; // Useful when reloading, to load directly where we left
    int map;
    int difficulty;
    int random_monsters;
    int random_items;
    int death_link;
    
} ap_state_t;


typedef struct
{
    const char* ip;
    const char* game;
    const char* player_name;
    const char* passwd;
    void (*message_callback)(const char*);
    void (*give_item_callback)(int doom_type, int ep, int map);
    void (*victory_callback)();
} ap_settings_t;


#ifdef FIRST_EP_ONLY
extern ap_level_info_t ap_level_infos[1][AP_LEVEL_COUNT];
#else
extern ap_level_info_t ap_level_infos[AP_EPISODE_COUNT][AP_LEVEL_COUNT];
#endif
extern ap_state_t ap_state;
extern int ap_is_in_game; // Don't give items when in menu (Or when dead on the ground).


int apdoom_init(ap_settings_t* settings);
void apdoom_shutdown();
void apdoom_save_state();
void apdoom_check_location(int ep, int map, int index);
int apdoom_is_location_progression(int ep, int map, int index);
void apdoom_check_victory();
void apdoom_update();
int ap_is_doomtype_location(int doomtype);
const char* apdoom_get_seed();
void apdoom_send_message(const char* msg);

// Deathlink stuff
void apdoom_on_death();
void apdoom_clear_death();
int apdoom_should_die();

#ifdef __cplusplus
}
#endif


#endif
