char md5[] = "85c0d8f829b91cde4675ebd7ca2ce9aa";
/*
 * This file is part of OpenPLC Runtime
 *
 * Copyright (C) 2023 Autonomy, GP Orcullo
 * Based on the work by GP Orcullo on Beremiz for uC
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <stdbool.h>

#include "iec_types_all.h"
#include "POUS.h"

#define SAME_ENDIANNESS      0
#define REVERSE_ENDIANNESS   1

uint8_t endianness;


extern PLC2 RES0__INSTANCE0;

static const struct {
    void *ptr;
    __IEC_types_enum type;
} debug_vars[] = {
    {&(RES0__INSTANCE0.COLORSENSOR_RED), INT_ENUM},
    {&(RES0__INSTANCE0.COLORSENSOR_GREEN), INT_ENUM},
    {&(RES0__INSTANCE0.COLORSENSOR_BLUE), INT_ENUM},
    {&(RES0__INSTANCE0.RANGESENSOR), INT_ENUM},
    {&(RES0__INSTANCE0.PUMP), BOOL_ENUM},
    {&(RES0__INSTANCE0.DOSER_RED), BOOL_ENUM},
    {&(RES0__INSTANCE0.DOSER_BLUE), BOOL_ENUM},
    {&(RES0__INSTANCE0.SETTLETIME), TIME_ENUM},
    {&(RES0__INSTANCE0.DOSETIME), TIME_ENUM},
    {&(RES0__INSTANCE0.TREATMENTCOMPLETE), BOOL_ENUM},
    {&(RES0__INSTANCE0.STAGE), INT_ENUM},
    {&(RES0__INSTANCE0.DESIREDDISTANCEFILL), REAL_ENUM},
    {&(RES0__INSTANCE0.MEASUREDDISTANCE), REAL_ENUM},
    {&(RES0__INSTANCE0.MINRED), INT_ENUM},
    {&(RES0__INSTANCE0.DOSERREDTIMER.EN), BOOL_ENUM},
    {&(RES0__INSTANCE0.DOSERREDTIMER.ENO), BOOL_ENUM},
    {&(RES0__INSTANCE0.DOSERREDTIMER.IN), BOOL_ENUM},
    {&(RES0__INSTANCE0.DOSERREDTIMER.PT), TIME_ENUM},
    {&(RES0__INSTANCE0.DOSERREDTIMER.Q), BOOL_ENUM},
    {&(RES0__INSTANCE0.DOSERREDTIMER.ET), TIME_ENUM},
    {&(RES0__INSTANCE0.DOSERREDTIMER.STATE), SINT_ENUM},
    {&(RES0__INSTANCE0.DOSERREDTIMER.PREV_IN), BOOL_ENUM},
    {&(RES0__INSTANCE0.DOSERREDTIMER.CURRENT_TIME), TIME_ENUM},
    {&(RES0__INSTANCE0.DOSERREDTIMER.START_TIME), TIME_ENUM},
    {&(RES0__INSTANCE0.DOSERBLUETIMER.EN), BOOL_ENUM},
    {&(RES0__INSTANCE0.DOSERBLUETIMER.ENO), BOOL_ENUM},
    {&(RES0__INSTANCE0.DOSERBLUETIMER.IN), BOOL_ENUM},
    {&(RES0__INSTANCE0.DOSERBLUETIMER.PT), TIME_ENUM},
    {&(RES0__INSTANCE0.DOSERBLUETIMER.Q), BOOL_ENUM},
    {&(RES0__INSTANCE0.DOSERBLUETIMER.ET), TIME_ENUM},
    {&(RES0__INSTANCE0.DOSERBLUETIMER.STATE), SINT_ENUM},
    {&(RES0__INSTANCE0.DOSERBLUETIMER.PREV_IN), BOOL_ENUM},
    {&(RES0__INSTANCE0.DOSERBLUETIMER.CURRENT_TIME), TIME_ENUM},
    {&(RES0__INSTANCE0.DOSERBLUETIMER.START_TIME), TIME_ENUM},
    {&(RES0__INSTANCE0.SETTLETIMER.EN), BOOL_ENUM},
    {&(RES0__INSTANCE0.SETTLETIMER.ENO), BOOL_ENUM},
    {&(RES0__INSTANCE0.SETTLETIMER.IN), BOOL_ENUM},
    {&(RES0__INSTANCE0.SETTLETIMER.PT), TIME_ENUM},
    {&(RES0__INSTANCE0.SETTLETIMER.Q), BOOL_ENUM},
    {&(RES0__INSTANCE0.SETTLETIMER.ET), TIME_ENUM},
    {&(RES0__INSTANCE0.SETTLETIMER.STATE), SINT_ENUM},
    {&(RES0__INSTANCE0.SETTLETIMER.PREV_IN), BOOL_ENUM},
    {&(RES0__INSTANCE0.SETTLETIMER.CURRENT_TIME), TIME_ENUM},
    {&(RES0__INSTANCE0.SETTLETIMER.START_TIME), TIME_ENUM},
    {&(RES0__INSTANCE0.DOSETIMERDONE), BOOL_ENUM},
    {&(RES0__INSTANCE0.SETTLEEN), BOOL_ENUM},
};

#define VAR_COUNT               46

uint16_t get_var_count(void)
{
    return VAR_COUNT;
}

size_t get_var_size(size_t idx)
{
    if (idx >= VAR_COUNT)
    {
        return 0;
    }
    switch (debug_vars[idx].type) {
    case REAL_ENUM:
        return sizeof(REAL);
    case BOOL_ENUM:
        return sizeof(BOOL);
    case SINT_ENUM:
        return sizeof(SINT);
    case INT_ENUM:
        return sizeof(INT);
    case TIME_ENUM:
        return sizeof(TIME);
    default:
        return 0;
    }
}

void *get_var_addr(size_t idx)
{
    void *ptr = debug_vars[idx].ptr;

    switch (debug_vars[idx].type) {
    case REAL_ENUM:
        return (void *)&((__IEC_REAL_t *) ptr)->value;
    case BOOL_ENUM:
        return (void *)&((__IEC_BOOL_t *) ptr)->value;
    case SINT_ENUM:
        return (void *)&((__IEC_SINT_t *) ptr)->value;
    case INT_ENUM:
        return (void *)&((__IEC_INT_t *) ptr)->value;
    case TIME_ENUM:
        return (void *)&((__IEC_TIME_t *) ptr)->value;
    default:
        return 0;
    }
}

void force_var(size_t idx, bool forced, void *val)
{
    void *ptr = debug_vars[idx].ptr;

    if (forced) {
        size_t var_size = get_var_size(idx);
        switch (debug_vars[idx].type) {
        case REAL_ENUM: {
            memcpy(&((__IEC_REAL_t *) ptr)->value, val, var_size);
            //((__IEC_REAL_t *) ptr)->value = *((REAL *) val);
            ((__IEC_REAL_t *) ptr)->flags |= __IEC_FORCE_FLAG;
            break;
        }
        case BOOL_ENUM: {
            memcpy(&((__IEC_BOOL_t *) ptr)->value, val, var_size);
            //((__IEC_BOOL_t *) ptr)->value = *((BOOL *) val);
            ((__IEC_BOOL_t *) ptr)->flags |= __IEC_FORCE_FLAG;
            break;
        }
        case SINT_ENUM: {
            memcpy(&((__IEC_SINT_t *) ptr)->value, val, var_size);
            //((__IEC_SINT_t *) ptr)->value = *((SINT *) val);
            ((__IEC_SINT_t *) ptr)->flags |= __IEC_FORCE_FLAG;
            break;
        }
        case INT_ENUM: {
            memcpy(&((__IEC_INT_t *) ptr)->value, val, var_size);
            //((__IEC_INT_t *) ptr)->value = *((INT *) val);
            ((__IEC_INT_t *) ptr)->flags |= __IEC_FORCE_FLAG;
            break;
        }
        case TIME_ENUM: {
            memcpy(&((__IEC_TIME_t *) ptr)->value, val, var_size);
            //((__IEC_TIME_t *) ptr)->value = *((TIME *) val);
            ((__IEC_TIME_t *) ptr)->flags |= __IEC_FORCE_FLAG;
            break;
        }
        default:
            break;
        }
    } else {
        switch (debug_vars[idx].type) {
        case REAL_ENUM:
            ((__IEC_REAL_t *) ptr)->flags &= ~__IEC_FORCE_FLAG;
            break;
        case BOOL_ENUM:
            ((__IEC_BOOL_t *) ptr)->flags &= ~__IEC_FORCE_FLAG;
            break;
        case SINT_ENUM:
            ((__IEC_SINT_t *) ptr)->flags &= ~__IEC_FORCE_FLAG;
            break;
        case INT_ENUM:
            ((__IEC_INT_t *) ptr)->flags &= ~__IEC_FORCE_FLAG;
            break;
        case TIME_ENUM:
            ((__IEC_TIME_t *) ptr)->flags &= ~__IEC_FORCE_FLAG;
            break;
        default:
            break;
        }
    }
}

void swap_bytes(void *ptr, size_t size) 
{
    uint8_t *bytePtr = (uint8_t *)ptr;
    size_t i;
    for (i = 0; i < size / 2; ++i) 
    {
        uint8_t temp = bytePtr[i];
        bytePtr[i] = bytePtr[size - 1 - i];
        bytePtr[size - 1 - i] = temp;
    }
}

void trace_reset(void)
{
    for (size_t i=0; i < VAR_COUNT; i++) 
    {
        force_var(i, false, 0);
    }
}

void set_trace(size_t idx, bool forced, void *val)
{
    if (idx >= 0 && idx < VAR_COUNT) 
    {
        if (endianness == REVERSE_ENDIANNESS)
        {
            // Aaaaarghhhh... Stupid AVR is Big Endian.
            swap_bytes(val, get_var_size(idx));
        }

        force_var(idx, forced, val);
    }
}

void set_endianness(uint8_t value)
{
    if (value == SAME_ENDIANNESS || value == REVERSE_ENDIANNESS)
    {
        endianness = value;
    }
}
