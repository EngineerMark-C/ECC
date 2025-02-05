#include "zf_common_headfile.h"
#include "init.h"

#define FLASH_SECTION_INDEX       (0)                                // 存储数据用的扇区
#define FLASH_PAGE_INDEX          (8)                                // 存储数据用的页码

// 例程测试
void Flash_test(void)
{
if(flash_check(FLASH_SECTION_INDEX, FLASH_PAGE_INDEX))                      // 判断是否有数据
        flash_erase_page(FLASH_SECTION_INDEX, FLASH_PAGE_INDEX);                // 擦除这一页

    printf("\r\n");
    flash_read_page_to_buffer(FLASH_SECTION_INDEX, FLASH_PAGE_INDEX);           // 将数据从 flash 读取到缓冲区
    printf("\r\n FLASH_SECTION_INDEX: %d, FLASH_PAGE_INDEX: %d, origin data is :", FLASH_SECTION_INDEX, FLASH_PAGE_INDEX);
    printf("\r\n float_type : %f", flash_union_buffer[0].float_type);           // 将缓冲区第 0 个位置的数据以 float  格式输出
    printf("\r\n uint32_type: %lu", flash_union_buffer[1].uint32_type);         // 将缓冲区第 1 个位置的数据以 uint32 格式输出
    printf("\r\n int32_type : %d", flash_union_buffer[2].int32_type);           // 将缓冲区第 2 个位置的数据以 int32  格式输出
    printf("\r\n uint16_type: %u", flash_union_buffer[3].uint16_type);          // 将缓冲区第 3 个位置的数据以 uint16 格式输出
    printf("\r\n int16_type : %d", flash_union_buffer[4].int16_type);           // 将缓冲区第 4 个位置的数据以 int16  格式输出
    printf("\r\n uint8_type : %u", flash_union_buffer[5].uint8_type);           // 将缓冲区第 5 个位置的数据以 uint8  格式输出
    printf("\r\n int8_type  : %d", flash_union_buffer[6].int8_type);            // 将缓冲区第 6 个位置的数据以 int8   格式输出
    // 请注意 数据缓冲区的每个位置只能存储一种类型的数据
    // 请注意 数据缓冲区的每个位置只能存储一种类型的数据
    // 请注意 数据缓冲区的每个位置只能存储一种类型的数据

    // 例如 flash_data_union_buffer[0] 写入 int8_type 那么只能以 int8_type 读取
    // 同样 flash_data_union_buffer[0] 写入 float_type 那么只能以 float_type 读取
    printf("\r\n");
    printf("\r\n Data property display :");
    printf("\r\n flash_data_union_buffer[0] write int8 data type:");
    flash_union_buffer[0].int8_type   = -128;                                   // 向缓冲区第 0 个位置写入     int8   数据
    printf("\r\n float_type : %f-data error", flash_union_buffer[0].float_type);// 将缓冲区第 0 个位置的数据以  float  格式输出 数据将不正确
    printf("\r\n int8_type  : %d", flash_union_buffer[0].int8_type);            // 将缓冲区第 0 个位置的数据以  int8   格式输出 得到正确写入数据

    printf("\r\n flash_data_union_buffer[0] write int8 data type:");
    flash_union_buffer[0].int8_type  -= 1;                                      // 向缓冲区第 0 个位置写入     int8   数据
    printf("\r\n float_type : %f-data error", flash_union_buffer[0].float_type);// 将缓冲区第 0 个位置的数据以  float  格式输出 数据将不正确
    printf("\r\n int8_type  : %d", flash_union_buffer[0].int8_type);            // 将缓冲区第 0 个位置的数据以  int8   格式输出 得到正确写入数据

    printf("\r\n flash_data_union_buffer[0] write float data type:");
    flash_union_buffer[0].float_type  = 16.625;                                 // 向缓冲区第 0 个位置写入     float  数据
    printf("\r\n float_type : %f", flash_union_buffer[0].float_type);           // 将缓冲区第 0 个位置的数据以  float  格式输出 得到正确写入数据
    printf("\r\n int8_type  : %d-data error", flash_union_buffer[0].int8_type); // 将缓冲区第 0 个位置的数据以  int8   格式输出 数据将不正确

    // 请注意 数据缓冲区的每个位置只能存储一种类型的数据
    // 请注意 数据缓冲区的每个位置只能存储一种类型的数据
    // 请注意 数据缓冲区的每个位置只能存储一种类型的数据

    flash_buffer_clear();                                                       // 清空缓冲区
    flash_union_buffer[0].float_type  = 3.1415926;                              // 向缓冲区第 0 个位置写入 float  数据
    flash_union_buffer[1].uint32_type = 4294967294;                             // 向缓冲区第 1 个位置写入 uint32 数据
    flash_union_buffer[2].int32_type  = -2147483648;                            // 向缓冲区第 2 个位置写入 int32  数据
    flash_union_buffer[3].uint16_type = 65535;                                  // 向缓冲区第 3 个位置写入 uint16 数据
    flash_union_buffer[4].int16_type  = -32768;                                 // 向缓冲区第 4 个位置写入 int16  数据
    flash_union_buffer[5].uint8_type  = 255;                                    // 向缓冲区第 5 个位置写入 uint8  数据
    flash_union_buffer[6].int8_type   = -128;                                   // 向缓冲区第 6 个位置写入 int8   数据
    flash_write_page_from_buffer(FLASH_SECTION_INDEX, FLASH_PAGE_INDEX);        // 向指定 Flash 扇区的页码写入缓冲区数据

    printf("\r\n");
    flash_buffer_clear();                                                       // 清空缓冲区
    printf("\r\n Flash data buffer default data is :");
    printf("\r\n float_type : %f", flash_union_buffer[0].float_type);           // 将缓冲区第 0 个位置的数据以 float  格式输出
    printf("\r\n uint32_type: %lu",flash_union_buffer[1].uint32_type);          // 将缓冲区第 1 个位置的数据以 uint32 格式输出
    printf("\r\n int32_type : %d", flash_union_buffer[2].int32_type);           // 将缓冲区第 2 个位置的数据以 int32  格式输出
    printf("\r\n uint16_type: %u", flash_union_buffer[3].uint16_type);          // 将缓冲区第 3 个位置的数据以 uint16 格式输出
    printf("\r\n int16_type : %d", flash_union_buffer[4].int16_type);           // 将缓冲区第 4 个位置的数据以 int16  格式输出
    printf("\r\n uint8_type : %u", flash_union_buffer[5].uint8_type);           // 将缓冲区第 5 个位置的数据以 uint8  格式输出
    printf("\r\n int8_type  : %d", flash_union_buffer[6].int8_type);            // 将缓冲区第 6 个位置的数据以 int8   格式输出
    system_delay_ms(200);
    printf("\r\n");
    flash_read_page_to_buffer(FLASH_SECTION_INDEX, FLASH_PAGE_INDEX);           // 将数据从 flash 读取到缓冲区
    printf("\r\n FLASH_SECTION_INDEX: %d, FLASH_PAGE_INDEX: %d, new data is :", FLASH_SECTION_INDEX, FLASH_PAGE_INDEX);
    printf("\r\n float_type : %f", flash_union_buffer[0].float_type);           // 将缓冲区第 0 个位置的数据以 float  格式输出
    printf("\r\n uint32_type: %lu",flash_union_buffer[1].uint32_type);          // 将缓冲区第 1 个位置的数据以 uint32 格式输出
    printf("\r\n int32_type : %d", flash_union_buffer[2].int32_type);           // 将缓冲区第 2 个位置的数据以 int32  格式输出
    printf("\r\n uint16_type: %u", flash_union_buffer[3].uint16_type);          // 将缓冲区第 3 个位置的数据以 uint16 格式输出
    printf("\r\n int16_type : %d", flash_union_buffer[4].int16_type);           // 将缓冲区第 4 个位置的数据以 int16  格式输出
    printf("\r\n uint8_type : %u", flash_union_buffer[5].uint8_type);           // 将缓冲区第 5 个位置的数据以 uint8  格式输出
    printf("\r\n int8_type  : %d", flash_union_buffer[6].int8_type);            // 将缓冲区第 6 个位置的数据以 int8   格式输出
}
