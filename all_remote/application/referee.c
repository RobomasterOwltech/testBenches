#include "referee.h"
#include "string.h"
#include "stdio.h"
#include "CRC8_CRC16.h"
#include "protocol.h"


frame_header_struct_t referee_receive_header;
frame_header_struct_t referee_send_header;

game_status_t game_state;
game_result_t game_result;
game_robot_HP_t game_robot_HP;

event_data_t field_event;
supply_projectile_action_t supply_projectile_action;

referee_warning_t referee_warning;

robot_status_t robot_state;
power_heat_data_t power_heat_data;
robot_pos_t game_robot_pos;
buff_t buff_musk;
air_support_data_t aerial_robot_energy;
hurt_data_t robot_hurt;
shoot_data_t shoot_data;
projectile_allowance_t projectile_allowance; 
student_interactive_data_t student_interactive_data;

// New:

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
    // memset(&bullet_remaining, 0, sizeof(ext_bullet_remaining_t));
    // memset(&supply_projectile_booking, 0, sizeof(ext_supply_projectile_booking_t));


    memset(&student_interactive_data, 0, sizeof(student_interactive_data_t));

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
        case GAME_STATE_CMD_ID:
            memcpy(&game_state, frame + index, sizeof(game_status_t));
            break;
        case GAME_RESULT_CMD_ID:
            memcpy(&game_result, frame + index, sizeof(game_result));
            break;
        case GAME_ROBOT_HP_CMD_ID:
            memcpy(&game_robot_HP, frame + index, sizeof(game_robot_HP_t));
            break;
        case FIELD_EVENTS_CMD_ID:
            memcpy(&field_event, frame + index, sizeof(field_event));
            break;
        case SUPPLY_PROJECTILE_ACTION_CMD_ID:
            memcpy(&supply_projectile_action, frame + index, sizeof(supply_projectile_action_t));
            break;
        case REFEREE_WARNING_CMD_ID:
            memcpy(&referee_warning, frame + index, sizeof(referee_warning_t));
            break;

        case ROBOT_STATE_CMD_ID:
            memcpy(&robot_state, frame + index, sizeof(robot_status_t));
            break;
        case POWER_HEAT_DATA_CMD_ID:
            memcpy(&power_heat_data, frame + index, sizeof(power_heat_data_t));
            break;
        case ROBOT_POS_CMD_ID:
            memcpy(&game_robot_pos, frame + index, sizeof(robot_pos_t));
            break;
        case BUFF_MUSK_CMD_ID:
            memcpy(&buff_musk, frame + index, sizeof(buff_t));
            break;
        case AERIAL_ROBOT_ENERGY_CMD_ID:
            memcpy(&aerial_robot_energy, frame + index, sizeof(air_support_data_t));
            break;
        case ROBOT_HURT_CMD_ID:
            memcpy(&robot_hurt, frame + index, sizeof(hurt_data_t));
            break;
        case SHOOT_DATA_CMD_ID:
            memcpy(&shoot_data, frame + index, sizeof(shoot_data_t));
            break;
        case STUDENT_INTERACTIVE_DATA_CMD_ID:
            memcpy(&student_interactive_data, frame + index, sizeof(student_interactive_data_t));
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
    *buffer = power_heat_data.chassis_power_buffer;

}


uint8_t get_robot_id(void)
{
    return robot_state.robot_id;
}

void get_shoot_heat0_limit_and_heat0(uint16_t *heat0_limit, uint16_t *heat0)
{
    *heat0_limit = robot_state.shooter_heat0_cooling_limit;
    *heat0 = power_heat_data.shooter_heat0;
}

void get_shoot_heat1_limit_and_heat1(uint16_t *heat1_limit, uint16_t *heat1)
{
    *heat1_limit = robot_state.shooter_heat1_cooling_limit;
    *heat1 = power_heat_data.shooter_heat1;
}

