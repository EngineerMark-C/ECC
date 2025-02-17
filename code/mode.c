#include "zf_common_headfile.h"
#include "init.h"

uint8_t Fire_Flag  = 0;                                                   //车辆启动标志位

// // 新增控制状态枚举
// typedef enum {
//     PHASE_GPS_NAV,    // GPS导航阶段
//     PHASE_INS_NAV,    // INS导航阶段
//     PHASE_TRANSITION  // 过渡阶段
// } NavigationPhase;

// NavigationPhase current_phase = PHASE_GPS_NAV;
// uint8_t gps_trigger_point = 0;  // 触发INS阶段的GPS点索引