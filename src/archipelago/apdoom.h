#ifndef _APDOOM_
#define _APDOOM_


#ifdef __cplusplus
extern "C"
{
#endif


#define AP_EPISODE_COUNT 3
#define AP_LEVEL_COUNT 9
#define AP_NUM_POWERS 6
#define AP_NUM_AMMO 4
#define AP_NUM_WEAPONS 9


typedef struct
{
    int keys[3];
    int check_count;

} ap_level_info_t;


typedef struct
{
    int completed;
    int keys[3];
    int check_count;
    int has_map;

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
    
} ap_state_t;


typedef struct
{
    const char* ip;
    const char* game;
    const char* player_name;
    const char* passwd;
    void (*message_callback)(const char*);
    void (*give_item_callback)(int doom_type);
} ap_settings_t;


extern ap_level_info_t ap_level_infos[AP_EPISODE_COUNT][AP_LEVEL_COUNT];
extern ap_state_t ap_state;
extern int ap_is_in_game; // Don't give items when in menu (Or when dead on the ground).


int apdoom_init(ap_settings_t* settings);
void apdoom_shutdown();
void apdoom_save_state();
void apdoom_check_location(int ep, int map, int index);
void apdoom_victory();
void apdoom_update();
const char* apdoom_get_seed();

#ifdef __cplusplus
}
#endif


#endif