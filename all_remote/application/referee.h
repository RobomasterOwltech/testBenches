#ifndef REFEREE_H
#define REFEREE_H

#include "main.h"

#include "protocol.h"

#define LENGTH_CUSTOM_DATA 0
#define MAX_ROBOT_INTERACTION 113
typedef enum
{
    RED_HERO        = 1,
    RED_ENGINEER    = 2,
    RED_STANDARD_1  = 3,
    RED_STANDARD_2  = 4,
    RED_STANDARD_3  = 5,
    RED_AERIAL      = 6,
    RED_SENTRY      = 7,
    BLUE_HERO       = 11,
    BLUE_ENGINEER   = 12,
    BLUE_STANDARD_1 = 13,
    BLUE_STANDARD_2 = 14,
    BLUE_STANDARD_3 = 15,
    BLUE_AERIAL     = 16,
    BLUE_SENTRY     = 17,
} robot_id_t;
typedef enum
{
    PROGRESS_UNSTART        = 0,
    PROGRESS_PREPARE        = 1,
    PROGRESS_SELFCHECK      = 2,
    PROGRESS_5sCOUNTDOWN    = 3,
    PROGRESS_BATTLE         = 4,
    PROGRESS_CALCULATING    = 5,
} game_progress_t;

//0001
typedef _packed struct 
{
    uint8_t game_type : 4;
    uint8_t game_progress : 4;
    uint16_t stage_remain_time;
    uint64_t SyncTimeStamp;
} game_status_t;
//Old name was: ext_game_state_t;

//0002
typedef _packed struct 
{
    uint8_t winner;
} game_result_t;
// old name was:   ext_game_result_t;


typedef _packed struct //0003
{
    uint16_t red_1_robot_HP;
    uint16_t red_2_robot_HP;
    uint16_t red_3_robot_HP;
    uint16_t red_4_robot_HP;
    uint16_t red_5_robot_HP;
    uint16_t red_7_robot_HP;
    uint16_t red_outpost_HP;
    uint16_t red_base_HP;
    uint16_t blue_1_robot_HP;
    uint16_t blue_2_robot_HP;
    uint16_t blue_3_robot_HP;
    uint16_t blue_4_robot_HP;
    uint16_t blue_5_robot_HP;
    uint16_t blue_7_robot_HP;
    uint16_t blue_outpost_HP;
    uint16_t blue_base_HP;
} game_robot_HP_t;
// Old name was: ext_game_robot_HP_t;

//0101
typedef _packed struct
{
    uint32_t event_data;
} event_data_t;
// Old name was: ext_event_data_t;


//0x0102
typedef _packed struct
{
    uint8_t reserved;
    uint8_t supply_robot_id;
    uint8_t supply_projectile_step;
    uint8_t supply_projectile_num;
} supply_projectile_action_t;
// Old name was: ext_supply_projectile_action_t;


// Deleted
// typedef __packed struct //0x0103
// {
//     uint8_t supply_projectile_id;
//     uint8_t supply_robot_id;
//     uint8_t supply_num;
// } ext_supply_projectile_booking_t;

// 0x0104
typedef _packed struct
{
    uint8_t level;
    uint8_t offending_robot_id;
    uint8_t count;
} referee_warning_t;
// old name was: ext_referee_warning_t;

// new 0x0105
typedef _packed struct
{
    uint8_t dart_remaining_time;
    uint16_t dart_info;
} dart_info_t;

//0x0201
typedef _packed struct
{
    uint8_t robot_id;
    uint8_t robot_level;
    uint16_t current_HP;
    uint16_t maximum_HP;
    uint16_t shooter_barrel_cooling_value;
    uint16_t shooter_barrel_heat_limit;
    uint16_t chassis_power_limit;
    uint8_t power_management_gimbal_output : 1;
    uint8_t power_management_chassis_output : 1;
    uint8_t power_management_shooter_output : 1;
} robot_status_t;
// Old name was: ext_game_robot_state_t;

//0x0202
typedef _packed struct
{
    uint16_t chassis_voltage;
    uint16_t chassis_current;
    float chassis_power;
    uint16_t buffer_energy;
    uint16_t shooter_17mm_1_barrel_heat;
    uint16_t shooter_17mm_2_barrel_heat;
    uint16_t shooter_42mm_barrel_heat;
} power_heat_data_t;
// Old name was: ext_power_heat_data_t

//0x0203
typedef _packed struct
{
    float x;
    float y;
    float angle;
} robot_pos_t;
// old name was: ext_game_robot_pos_t;

//0x0204
typedef _packed struct
{
    uint8_t recovery_buff;
    uint8_t cooling_buff;
    uint8_t defence_buff;
    uint8_t vulnerability_buff;
    uint16_t attack_buff;
} buff_t;
//old name was ext_buff_musk_t;

//0x0205
typedef _packed struct
{
    uint8_t airforce_status;
    uint8_t time_remain;
} air_support_data_t;
//old name was: aerial_robot_energy_t;

//0x0206
typedef _packed struct
{
    uint8_t armor_id : 4;
    uint8_t HP_deduction_reason : 4;
} hurt_data_t;
// old name was ext_robot_hurt_t;

//0x0207
typedef _packed struct
{
    uint8_t bullet_type;
    uint8_t shooter_number;
    uint8_t launching_frequency;
    float initial_speed;
} shoot_data_t;
// old name was ext_shoot_data_t;


// Think this was deleted
// typedef __packed struct
// {
//     uint8_t bullet_remaining_num;
// } ext_bullet_remaining_t;

//0x0208
typedef _packed struct
{
    uint16_t projectile_allowance_17mm;
    uint16_t projectile_allowance_42mm;
    uint16_t remaining_gold_coin;
} projectile_allowance_t;

//0x0209 new
typedef _packed struct
{
    uint32_t rfid_status;
} rfid_status_t;

//0x020A new
typedef _packed struct
{
    uint8_t dart_launch_opening_status;
    uint8_t reserved;
    uint16_t target_change_time;
    uint16_t latest_launch_cmd_time;
} dart_client_cmd_t;


typedef __packed struct //0x0301
{
    uint16_t send_ID;
    uint16_t receiver_ID;
    uint16_t data_cmd_id;
    uint16_t data_len;
    uint8_t *data;
} student_interactive_data_t;
// Old name was: ext_student_interactive_data_t;

typedef __packed struct
{
    float data1;
    float data2;
    float data3;
    uint8_t data4;
} custom_data_t;


typedef __packed struct
{
    uint8_t data[64];
} up_stream_data_t;
// Old name was:ext_up_stream_data_t;

typedef __packed struct
{
    uint8_t data[32];
} download_stream_data_t;
// Old name was:ext_download_stream_data_t;

//EMPIEZA NUEVO REFEREE MANUAL - SOFIA
typedef _packed struct //0x020C
{
 uint8_t mark_hero_progress;
 uint8_t mark_engineer_progress;
 uint8_t mark_standard_3_progress;
 uint8_t mark_standard_4_progress;
 uint8_t mark_standard_5_progress;
 uint8_t mark_sentry_progress;
} radar_mark_data_t;

typedef _packed struct //0x020D
{
    uint32_t sentry_info; 
} sentry_info_t;

typedef _packed struct  //0x020E
{
    uint8_t radar_info;
} radar_info_t;

typedef _packed struct //0x0301
{
    uint16_t data_cmd_id;
    uint16_t sender_id;
    uint16_t receiver_id;
    uint8_t user_data[MAX_ROBOT_INTERACTION]; 
} robot_interaction_data_t;

typedef _packed struct //0x0100
{
    uint8_t delete_type;
    uint8_t layer;
} interaction_layer_delete_t;

typedef _packed struct //0x0101
{
    uint8_t figure_name[3];
    uint32_t operate_tpye:3;
    uint32_t figure_tpye:3;
    uint32_t layer:4;
    uint32_t color:4;
    uint32_t details_a:9;
    uint32_t details_b:9;
    uint32_t width:10;
    uint32_t start_x:11;
    uint32_t start_y:11;
    uint32_t details_c:10;
    uint32_t details_d:11;
    uint32_t details_e:11;
} interaction_figure_t;

typedef _packed struct //0x0102
{
    interaction_figure_t interaction_figure[2];
} interaction_figure_2_t;

typedef _packed struct //0x0103
{
    interaction_figure_t interaction_figure[5];
} interaction_figure_3_t;

typedef _packed struct //0x0104
{
    interaction_figure_t interaction_figure[7];
} interaction_figure_4_t;

typedef __packed struct //0x0301
{
uint8_t graphic_name[3];
uint32_t operate_tpye:3;
uint32_t graphic_tpye:3;
uint32_t layer:4;
uint32_t color:4;
uint32_t start_angle:9;
uint32_t end_angle:9;
uint32_t width:10;
uint32_t start_x:11;
uint32_t start_y:11;
uint32_t radius:10;
uint32_t end_x:11;
uint32_t end_y:11;
} graphic_data_struct_t

typedef _packed struct //0x0110
{
    graphic_data_struct_t grapic_data_struct;
    uint8_t data[30];
} ext_client_custom_character_t;

typedef _packed struct //0x0120
{
    uint32_t sentry_cmd;
} sentry_cmd_t;

typedef _packed struct //0x0121
{
    uint8_t radar_cmd;  
} radar_cmd_t;

typedef _packed struct //0x0303
{
    float target_position_x;
    float target_position_y;
    uint8_t cmd_keyboard;
    uint8_t target_robot_id;
    uint8_t cmd_source;
} map_command_t;

typedef _packed struct //0x0305
{
    uint16_t target_robot_id;
    float target_position_x;
    float target_position_y;
} map_robot_data_t;

typedef _packed struct //0x0307
{
    uint8_t intention;
    uint16_t start_position_x;
    uint16_t start_position_y;
    int8_t delta_x[49];
    int8_t delta_y[49];
    uint16_t sender_id;
} map_data_t;

typedef _packed struct //0x0308
{
    uint16_t sender_id;
    uint16_t receiver_id;
    uint8_t user_data[30];
} custom_info_t;

typedef _packed struct //0x0302
{
    uint8_t data[LENGTH_CUSTOM_DATA];
} custom_robot_data_t; 

typedef _packed struct //0x0304
{
    int16_t mouse_x;
    int16_t mouse_y;
    int16_t mouse_z;
    int8_t left_button_down;
    int8_t right_button_down;
    uint16_t keyboard_value;
    uint16_t reserved;
} remote_control_t;

typedef _packed struct //0x0306
{
    uint16_t key_value;
    uint16_t x_position:12;
    uint16_t mouse_left:4;
    uint16_t y_position:12;
    uint16_t mouse_right:4;
    uint16_t reserved;
} custom_client_data_t;


extern void init_referee_struct_data(void);
extern void referee_data_solve(uint8_t *frame);

extern void get_chassis_power_and_buffer(fp32 *power, fp32 *buffer);

extern uint8_t get_robot_id(void);

extern void get_shoot_heat0_limit_and_heat0(uint16_t *heat0_limit, uint16_t *heat0);
extern void get_shoot_heat1_limit_and_heat1(uint16_t *heat1_limit, uint16_t *heat1);
#endif
