#include "lcd_config.h"


pInt8U Lcd_Set_DisBufAdd(Int32U bufferadder)
{
outpw(REG_LCM_VA_BADDR0, (uint32_t)bufferadder);
outpw(REG_LCM_VA_FBCTRL, inpw(REG_LCM_VA_FBCTRL) & ~(1<<30) & ~VPOSTB_DB_EN);
return (pInt8U)(bufferadder);
}
