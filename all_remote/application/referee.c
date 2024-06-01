#include "referee.h"
#include "string.h"
#include "stdio.h"
#include "CRC8_CRC16.h"
#include "protocol.h"

// These were moved to the .h
// static game_status_t game_state;
// static robot_status_t robot_state;
// static shoot_data_t shoot_data;
// static power_heat_data_t power_heat_data;
// frame_header_struct_t referee_send_header;

frame_header_struct_t referee_receive_header;
game_result_t game_result;
game_robot_HP_t game_robot_HP;
referee_warning_t referee_warning;
projectile_allowance_t projectile_allowance; 
remote_control_t remote_control; 

// event_data_t field_event;
// supply_projectile_action_t supply_projectile_action;

// robot_pos_t game_robot_pos;
// buff_t buff_musk;
// air_support_data_t aerial_robot_energy;
// hurt_data_t robot_hurt;

// change student_interactive_data_t to robot_interaction_data_t
// robot_interaction_data_t student_interactive_data; 

// New:

// rfid_status_t rfid_status; 
// dart_client_cmd_t dart_client;
// ground_robot_position_t ground_robot_position; 
// radar_mark_data_t radar_mark;

// sentry_info_t sentry_inf; 
// sentry_cmd_t sentry_cm; 
// radar_info_t radar_inf; 
// radar_cmd_t radar_cm; 
// ext_client_custom_character_t client_custom_character;

// map_command_t map_command; 
// map_robot_data_t map_robot_data; 
// map_data_t map_data; 

// custom_info_t custom_info; 
// custom_robot_data_t robot_data; 
// custom_client_data_t client_data; 

// Deleted
//ext_bullet_remaining_t bullet_remaining_t;
//ext_supply_projectile_booking_t supply_projectile_booking_t;

void init_referee_struct_data(void)
{
    memset(&referee_receive_header, 0, sizeof(frame_header_struct_t));

    memset(&game_state, 0, sizeof(game_status_t));
    memset(&game_result, 0, sizeof(game_result_t));
    memset(&game_robot_HP, 0, sizeof(game_robot_HP_t));

    memset(&referee_warning, 0, sizeof(referee_warning_t));
    memset(&robot_state, 0, sizeof(robot_status_t));
    memset(&power_heat_data, 0, sizeof(power_heat_data_t));
    memset(&shoot_data, 0, sizeof(shoot_data_t));
    memset(&projectile_allowance, 0, sizeof(projectile_allowance_t));
    
    //memset(&field_event, 0, sizeof(event_data_t));
    //memset(&supply_projectile_action, 0, sizeof(supply_projectile_action_t));
    //memset(&game_robot_pos, 0, sizeof(robot_pos_t));
    //memset(&buff_musk, 0, sizeof(buff_t));
    //memset(&aerial_robot_energy, 0, sizeof(air_support_data_t));
    //memset(&robot_hurt, 0, sizeof(hurt_data_t));
    //memset(&student_interactive_data, 0, sizeof(robot_interaction_data_t));

}

void referee_data_solve(uint8_t *frame)
{
    uint16_t cmd_id = 0;

    uint8_t index = 0;

    memcpy(&referee_receive_header, frame, sizeof(frame_header_struct_t));

    index += sizeof(frame_header_struct_t);

    memcpy(&cmd_id, frame + index, sizeof(uint16_t));
    index += sizeof(uint16_t);

    switch (cmd_id)
    {
        // The most important messages:
        case GAME_STATUS_CMD_ID: 
            memcpy(&game_state, frame + index, sizeof(game_status_t));
            break;
        case GAME_RESULT_CMD_ID:
            memcpy(&game_result, frame + index, sizeof(game_result_t));
            break;
        case GAME_ROBOT_HP_CMD_ID:
            memcpy(&game_robot_HP, frame + index, sizeof(game_robot_HP_t));
            break;
        case REFEREE_WARNING_CMD_ID:
            memcpy(&referee_warning, frame + index, sizeof(referee_warning_t));
            break;
        case ROBOT_STATUS_CMD_ID:
            memcpy(&robot_state, frame + index, sizeof(robot_status_t));
            break;
        case POWER_HEAT_DATA_CMD_ID:
            memcpy(&power_heat_data, frame + index, sizeof(power_heat_data_t));
            break;
        case SHOOT_DATA_CMD_ID:
            memcpy(&shoot_data, frame + index, sizeof(shoot_data_t));
            break;
        case PROJECTILE_ALLOWANCE_CMD_ID:
            memcpy(&projectile_allowance, frame + index, sizeof(projectile_allowance_t));
            break;
        case REMOTE_CONTROL_CMD_ID:
            memcpy(&remote_control, frame + index, sizeof(remote_control_t));
            break;        
        default:
        {
            break;
        }
    }
}

void get_chassis_power_and_buffer(fp32 *power, fp32 *buffer)
{
    *power = power_heat_data.chassis_power;
    *buffer = power_heat_data.buffer_energy;

}


uint8_t get_robot_id(void)
{
    return robot_state.robot_id;
}

void get_shoot_heat0_limit_and_heat0(uint16_t *heat0_limit, uint16_t *heat0)
{
    *heat0_limit = robot_state.shooter_barrel_heat_limit;
    *heat0 = power_heat_data.shooter_17mm_1_barrel_heat;
}

void get_shoot_heat1_limit_and_heat1(uint16_t *heat1_limit, uint16_t *heat1)
{
    *heat1_limit = robot_state.shooter_barrel_cooling_value;
    *heat1 = power_heat_data.shooter_17mm_2_barrel_heat;
}

