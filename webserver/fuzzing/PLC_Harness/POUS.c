void PLC2_init__(PLC2 *data__, BOOL retain) {
  __INIT_LOCATED(INT,__QW0,data__->COLORSENSOR_RED,retain)
  __INIT_LOCATED_VALUE(data__->COLORSENSOR_RED,0)
  __INIT_LOCATED(INT,__QW1,data__->COLORSENSOR_GREEN,retain)
  __INIT_LOCATED_VALUE(data__->COLORSENSOR_GREEN,0)
  __INIT_LOCATED(INT,__QW2,data__->COLORSENSOR_BLUE,retain)
  __INIT_LOCATED_VALUE(data__->COLORSENSOR_BLUE,0)
  __INIT_LOCATED(INT,__QW3,data__->RANGESENSOR,retain)
  __INIT_LOCATED_VALUE(data__->RANGESENSOR,0)
  __INIT_LOCATED(BOOL,__QX0_4,data__->PUMP,retain)
  __INIT_LOCATED_VALUE(data__->PUMP,__BOOL_LITERAL(FALSE))
  __INIT_LOCATED(BOOL,__QX0_6,data__->DOSER_RED,retain)
  __INIT_LOCATED_VALUE(data__->DOSER_RED,__BOOL_LITERAL(FALSE))
  __INIT_LOCATED(BOOL,__QX0_7,data__->DOSER_BLUE,retain)
  __INIT_LOCATED_VALUE(data__->DOSER_BLUE,__BOOL_LITERAL(FALSE))
  __INIT_VAR(data__->SETTLETIME,__time_to_timespec(1, 700, 0, 0, 0, 0),retain)
  __INIT_VAR(data__->DOSETIME,__time_to_timespec(1, 2000, 0, 0, 0, 0),retain)
  __INIT_LOCATED(BOOL,__QX0_0,data__->TREATMENTCOMPLETE,retain)
  __INIT_LOCATED_VALUE(data__->TREATMENTCOMPLETE,__BOOL_LITERAL(FALSE))
  __INIT_LOCATED(INT,__QW4,data__->STAGE,retain)
  __INIT_LOCATED_VALUE(data__->STAGE,0)
  __INIT_VAR(data__->DESIREDDISTANCEFILL,7.0,retain)
  __INIT_LOCATED(REAL,__QD1,data__->MEASUREDDISTANCE,retain)
  __INIT_LOCATED_VALUE(data__->MEASUREDDISTANCE,0)
  __INIT_VAR(data__->MINRED,20,retain)
  TON_init__(&data__->DOSERREDTIMER,retain);
  TON_init__(&data__->DOSERBLUETIMER,retain);
  TON_init__(&data__->SETTLETIMER,retain);
  __INIT_LOCATED(BOOL,__QX1_2,data__->DOSETIMERDONE,retain)
  __INIT_LOCATED_VALUE(data__->DOSETIMERDONE,0)
  __INIT_VAR(data__->SETTLEEN,__BOOL_LITERAL(FALSE),retain)
}

// Code part
void PLC2_body__(PLC2 *data__) {
  // Initialise TEMP variables

  __SET_LOCATED(data__->,MEASUREDDISTANCE,,(INT_TO_REAL(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (INT)__GET_LOCATED(data__->RANGESENSOR,)) / 100.0));
  __SET_VAR(data__->,DESIREDDISTANCEFILL,,7.0);
  __SET_VAR(data__->,MINRED,,20);
  __SET_VAR(data__->,DOSETIME,,__time_to_timespec(1, 3000, 0, 0, 0, 0));
  __SET_VAR(data__->,SETTLETIME,,__time_to_timespec(1, 5000, 0, 0, 0, 0));
  __SET_VAR(data__->DOSERREDTIMER.,IN,,__GET_LOCATED(data__->DOSER_RED,));
  __SET_VAR(data__->DOSERREDTIMER.,PT,,__GET_VAR(data__->DOSETIME,));
  TON_body__(&data__->DOSERREDTIMER);
  __SET_VAR(data__->DOSERBLUETIMER.,IN,,__GET_LOCATED(data__->DOSER_BLUE,));
  __SET_VAR(data__->DOSERBLUETIMER.,PT,,__GET_VAR(data__->DOSETIME,));
  TON_body__(&data__->DOSERBLUETIMER);
  __SET_LOCATED(data__->,DOSETIMERDONE,,__GET_VAR(data__->DOSERREDTIMER.Q,));
  __SET_VAR(data__->SETTLETIMER.,IN,,__GET_VAR(data__->SETTLEEN,));
  __SET_VAR(data__->SETTLETIMER.,PT,,__GET_VAR(data__->SETTLETIME,));
  TON_body__(&data__->SETTLETIMER);
  {
    INT __case_expression = __GET_LOCATED(data__->STAGE,);
    if ((__case_expression == 0)) {
      if ((__GET_LOCATED(data__->MEASUREDDISTANCE,) > __GET_VAR(data__->DESIREDDISTANCEFILL,))) {
        __SET_LOCATED(data__->,PUMP,,__BOOL_LITERAL(TRUE));
      } else {
        __SET_LOCATED(data__->,PUMP,,__BOOL_LITERAL(FALSE));
        __SET_LOCATED(data__->,STAGE,,1);
      };
    }
    else if ((__case_expression == 1)) {
      if ((__GET_LOCATED(data__->COLORSENSOR_RED,) < __GET_VAR(data__->MINRED,))) {
        __SET_LOCATED(data__->,STAGE,,2);
        __SET_LOCATED(data__->,DOSER_RED,,__BOOL_LITERAL(TRUE));
      } else if ((__GET_LOCATED(data__->COLORSENSOR_RED,) > __GET_LOCATED(data__->COLORSENSOR_BLUE,))) {
        __SET_LOCATED(data__->,STAGE,,3);
        __SET_LOCATED(data__->,DOSER_BLUE,,__BOOL_LITERAL(TRUE));
      } else {
        __SET_LOCATED(data__->,STAGE,,5);
      };
    }
    else if ((__case_expression == 2)) {
      if (__GET_VAR(data__->DOSERREDTIMER.Q,)) {
        __SET_LOCATED(data__->,DOSER_RED,,__BOOL_LITERAL(FALSE));
        __SET_LOCATED(data__->,STAGE,,4);
        __SET_VAR(data__->,SETTLEEN,,__BOOL_LITERAL(TRUE));
      };
    }
    else if ((__case_expression == 3)) {
      if (__GET_VAR(data__->DOSERBLUETIMER.Q,)) {
        __SET_LOCATED(data__->,DOSER_BLUE,,__BOOL_LITERAL(FALSE));
        __SET_LOCATED(data__->,STAGE,,4);
        __SET_VAR(data__->,SETTLEEN,,__BOOL_LITERAL(TRUE));
      };
    }
    else if ((__case_expression == 4)) {
      if (__GET_VAR(data__->SETTLETIMER.Q,)) {
        __SET_LOCATED(data__->,STAGE,,1);
        __SET_VAR(data__->,SETTLEEN,,__BOOL_LITERAL(FALSE));
      };
    }
    else if ((__case_expression == 5)) {
      __SET_LOCATED(data__->,TREATMENTCOMPLETE,,__BOOL_LITERAL(TRUE));
    }
  };

  goto __end;

__end:
  return;
} // PLC2_body__() 





