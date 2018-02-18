== How to update the firmware ==
Description: Change the name of the firmware to "firmware.bin" and save it to your micro SD card. Then insert the card to the 4.3inch e-Paper UART module. Power up the module, the indicator LCD will be off and then will be turned on after about 10 seconds.
After firmware update, please remove the SD card and delete the firmware to prevent repeatedly update during booting up.

Note:
1, only the 4.3inch e-Paper UART module sold after June 2017 supports firmware update.
2, if the SD card cannot be read, try to format the SD card to 2048-byte cluster size & FAT32.
   if the card still cannot be read, connect the pin 3 (DIN) and pin 4 (DOUT) to GND.
3, you have to power up the module while updating.

Changes:
firmware20151222.bin {
    Initial release
}
firmware20170513.bin {
    [+] Fix some bugs
    [+] Supports 90 and 270 rotation. 
        The command to rotate 180 in the older version becomes 90 rotation in the new one.
    [+] Chinese font size settings and English font size settings are no longer different.
}
firmware20170612.bin {
    [+] Improve stability
}
firmware20170718.bin {
    [+] Set orientation 180 (A5 00 0A 0D 02 CC 33 C3 3C A0)
    [+] Set orientation 270 (A5 00 0A 0D 03 CC 33 C3 3C A1)
    [+] Nand full erase (A5 00 09 50 CC 33 C3 3C FC)
}

== 如何更新固件 ==
说明：把需要的固件改名为firmware.bin放入micro SD卡中，然后把micro SD卡插入到4.3inch e-Paper UART 模块中。
上电之后，模块的指示灯处于熄灭状态，等待10秒钟左右，直到指示灯常亮，此时固件写入成功。
固件更新完成之后，请取下SD卡并删除固件，以免每次开机都进行更新。

注意：
1，只有2017年6月之后出货的4.3inch e-Paper 才支持固件更新。
2，如果无法读取SD卡，请试着把micro SD卡格式化为2048字节的FAT32。
   如果依然无法读取，则请把模块的pin 3 (DIN)和pin 4 (DOUT)接地。
3，更新固件的时候，模块必须上电。

== 如何更新韌體 ==
說明：把需要的韌體改名為firmware.bin放入micro SD卡中，然後把micro SD卡插入到4.3inch e-Paper UART 模組中。
上電之後，模組的指示燈處於熄滅狀態，等待10秒鐘左右，直到指示燈常亮，此時韌體寫入成功。
韌體更新完成之後，請取下SD卡並删除韌體，以免每次開機都進行更新。

注意：
1，只有2017年6月之後出貨的4.3inch e-Paper 才支持韌體更新。
2，如果無法讀取SD卡，請試著把micro SD卡格式化為2048位元組的FAT32。
   如果依然無法讀取，則請把模組的pin 3 (DIN)和pin 4 (DOUT)接地。
3，更新韌體的時候，模組必須上電。

版本变更：
firmware20151222.bin {
    初始发布
}
firmware20170513.bin {
    [+] 修复一些bug。
    [+] 支持90度、270度旋转。原本旋转180度的指令变成旋转90度。
    [+] 字体大小设置不再区分中文字体大小设置和英文字体大小设置。
}
firmware20170612.bin {
    [+] 提高稳定性
}
firmware20170718.bin {
    [+] 设置旋转180 (A5 00 0A 0D 02 CC 33 C3 3C A0)
    [+] 设置旋转270 (A5 00 0A 0D 03 CC 33 C3 3C A1)
    [+] Nand 全擦除(A5 00 09 50 CC 33 C3 3C FC)
}