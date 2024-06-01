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

frame_header_struct_t referee_receive_header;
frame_header_struct_t referee_send_header;

game_result_t game_result;
game_robot_HP_t game_robot_HP;

event_data_t field_event;
supply_projectile_action_t supply_projectile_action;

referee_warning_t referee_warning;

robot_pos_t game_robot_pos;
buff_t buff_musk;
air_support_data_t aerial_robot_energy;
hurt_data_t robot_hurt;
projectile_allowance_t projectile_allowance; 

//change student_interactive_data_t to robot_interaction_data_t
robot_interaction_data_t student_interactive_data; 

interaction_layer_delete_t layer_delete; //Semi new
interaction_figure_t interaction_figure; //Semi new
interaction_figure_2_t figure_2; //semi new
interaction_figure_3_t figure_3; //semi new
interaction_figure_4_t figure_4; //semi new

// New:
dart_info_t dart; 

rfid_status_t rfid_status; 
dart_client_cmd_t dart_client;
ground_robot_position_t ground_robot_position; 
radar_mark_data_t radar_mark;

sentry_info_t sentry_inf; 
sentry_cmd_t sentry_cm; 
radar_info_t radar_inf; 
radar_cmd_t radar_cm; 

ext_client_custom_character_t client_custom_character;

map_command_t map_command; 
map_robot_data_t map_robot_data; 
map_data_t map_data; 

custom_info_t custom_info; 
custom_robot_data_t robot_data; 
remote_control_t remote_control; 
custom_client_data_t client_data; 

// Deleted
//ext_bullet_remaining_t bullet_remaining_t;
//ext_supply_projectile_booking_t supply_projectile_booking_t;

void init_referee_struct_data(void)
{
    memset(&referee_receive_header, 0, sizeof(frame_header_struct_t));
    memset(&referee_send_header, 0, sizeof(frame_header_struct_t));

    memset(&game_state, 0, sizeof(game_status_t));
    memset(&game_result, 0, sizeof(game_result_t));
    memset(&game_robot_HP, 0, sizeof(game_robot_HP_t));


    memset(&field_event, 0, sizeof(event_data_t));
    memset(&supply_projectile_action, 0, sizeof(supply_projectile_action_t));
    memset(&referee_warning, 0, sizeof(referee_warning_t));


    memset(&robot_state, 0, sizeof(robot_status_t));
    memset(&power_heat_data, 0, sizeof(power_heat_data_t));
    memset(&game_robot_pos, 0, sizeof(robot_pos_t));
    memset(&buff_musk, 0, sizeof(buff_t));
    memset(&aerial_robot_energy, 0, sizeof(air_support_data_t));
    memset(&robot_hurt, 0, sizeof(hurt_data_t));
    memset(&shoot_data, 0, sizeof(shoot_data_t));
    memset(&projectile_allowance, 0, sizeof(projectile_allowance_t));
    //deleted
    // memset(&bullet_remaining, 0, sizeof(ext_bullet_remaining_t));
    // memset(&supply_projectile_booking, 0, sizeof(ext_supply_projectile_booking_t));
    memset(&student_interactive_data, 0, sizeof(robot_interaction_data_t));

    //new
    memset(&dart, 0, sizeof(dart_info_t));
    memset(&map_command, 0, sizeof(map_command_t));
    memset(&map_robot_data, 0, sizeof(map_robot_data_t));
    memset(&map_data, 0, sizeof(map_data_t));
    memset(&custom_info, 0, sizeof(custom_info_t));
    memset(&robot_data, 0, sizeof(custom_robot_data_t));
    memset(&remote_control, 0, sizeof(remote_control_t));
    memset(&client_data, 0, sizeof(custom_client_data_t));
    memset(&rfid_status, 0, sizeof(rfid_status_t));
    memset(&dart_client, 0, sizeof(dart_client_cmd_t));
    memset(&ground_robot_position, 0, sizeof(ground_robot_position_t));
    memset(&radar_mark, 0, sizeof(radar_mark_data_t));
    memset(&client_custom_character, 0, sizeof(ext_client_custom_character_t));
    memset(&sentry_inf, 0, sizeof(sentry_info_t));
    memset(&sentry_cm, 0, sizeof(sentry_cmd_t));
    memset(&radar_inf, 0, sizeof(radar_info_t));
    memset(&radar_cm, 0, sizeof(radar_cmd_t));
    //figures
    memset(&layer_delete, 0, sizeof(interaction_layer_delete_t));
    memset(&interaction_figure, 0, sizeof(interaction_figure_t));
    memset(&figure_2, 0, sizeof(interaction_figure_2_t));
    memset(&figure_3, 0, sizeof(interaction_figure_3_t));
    memset(&figure_4, 0, sizeof(interaction_figure_4_t));
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
        case GAME_STATUS_CMD_ID: 
            memcpy(&game_state, frame + index, sizeof(game_status_t));
            break;
        case GAME_RESULT_CMD_ID:
            memcpy(&game_result, frame + index, sizeof(game_result_t));
            break;
        case GAME_ROBOT_HP_CMD_ID:
            memcpy(&game_robot_HP, frame + index, sizeof(game_robot_HP_t));
            break;
        case EVENT_DATA_CMD_ID:
            memcpy(&field_event, frame + index, sizeof(event_data_t));
            break;
        case SUPPLY_PROJECTILE_ACTION_CMD_ID:
            memcpy(&supply_projectile_action, frame + index, sizeof(supply_projectile_action_t));
            break;
        case REFEREE_WARNING_CMD_ID:
            memcpy(&referee_warning, frame + index, sizeof(referee_warning_t));
            break;
        case DART_INFO_CMD_ID:
            memcpy(&dart, frame + index, sizeof(dart_info_t));
            break;
        case ROBOT_STATUS_CMD_ID:
            memcpy(&robot_state, frame + index, sizeof(robot_status_t));
            break;
        case POWER_HEAT_DATA_CMD_ID:
            memcpy(&power_heat_data, frame + index, sizeof(power_heat_data_t));
            break;
        case ROBOT_POS_CMD_ID:
            memcpy(&game_robot_pos, frame + index, sizeof(robot_pos_t));
            break;
        case BUFF_CMD_ID  :
            memcpy(&buff_musk, frame + index, sizeof(buff_t));
            break;
        case AIR_SUPPORT_DATA_CMD_ID:
            memcpy(&aerial_robot_energy, frame + index, sizeof(air_support_data_t));
            break;
        case HURT_DATA_CMD_ID:
            memcpy(&robot_hurt, frame + index, sizeof(hurt_data_t));
            break;
        case SHOOT_DATA_CMD_ID:
            memcpy(&shoot_data, frame + index, sizeof(shoot_data_t));
            break;
        case PROJECTILE_ALLOWANCE_CMD_ID:
            memcpy(&projectile_allowance, frame + index, sizeof(projectile_allowance_t));
            break;
        case RFID_STATUS_CMD_ID:
            memcpy(&rfid_status, frame + index, sizeof(rfid_status_t));
            break;
        case DART_CLIENT_CMD_ID:
            memcpy(&dart_client, frame + index, sizeof(dart_client_cmd_t));
            break;
        case GROUND_ROBOT_POSITION_CMD_ID:
            memcpy(&ground_robot_position, frame + index, sizeof(ground_robot_position_t));
            break;
        case RADAR_MARK_DATA_CMD_ID:
            memcpy(&radar_mark, frame + index, sizeof(radar_mark_data_t));
            break;
        case SENTRY_INFO_CMD_ID:
            memcpy(&sentry_inf, frame + index, sizeof(sentry_info_t));
            break;
        case RADAR_INFO_CMD_ID:
            memcpy(&radar_inf, frame + index, sizeof(radar_info_t));
            break;
        case ROBOT_INTERACTION_DATA_CMD_ID:
            memcpy(&student_interactive_data, frame + index, sizeof(robot_interaction_data_t));
            break;
        case INTERACTION_LAYER_DELETE_CMD_ID:
            memcpy(&layer_delete, frame + index, sizeof(interaction_layer_delete_t));
            break;
        case CLIENT_CUSTOM_CHARACTER_CMD_ID:
            memcpy(&client_custom_character, frame + index, sizeof(ext_client_custom_character_t));
            break;
        case SENTRY_CMD_ID:
            memcpy(&sentry_cm, frame + index, sizeof(sentry_cmd_t));
            break;
        case RADAR_CMD_ID:
            memcpy(&radar_cm, frame + index, sizeof(radar_cmd_t));
            break;
        case MAP_CMD_ID:
            memcpy(&map_command, frame + index, sizeof(map_command_t));
            break;
        case MAP_ROBOT_DATA_CMD_ID:
            memcpy(&map_robot_data, frame + index, sizeof(map_robot_data_t));
            break;
        case MAP_DATA_CMD_ID:
            memcpy(&map_data, frame + index, sizeof(map_data_t));
            break;
        case CUSTOM_INFO_CMD_ID:
            memcpy(&custom_info, frame + index, sizeof(custom_info_t));
            break;
        case CUSTOM_ROBOT_DATA_CMD_ID:
            memcpy(&robot_data, frame + index, sizeof(custom_robot_data_t));
            break;
        case REMOTE_CONTROL_CMD_ID:
            memcpy(&remote_control, frame + index, sizeof(remote_control_t));
            break;
        case CUSTOM_CLIENT_DATA_CMD_ID:
            memcpy(&client_data, frame + index, sizeof(custom_client_data_t));
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

