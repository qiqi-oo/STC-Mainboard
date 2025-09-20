@echo off
 
@REM 可执行文件(hex)文件名
set HEX_NAME=STC.hex
 
@REM 可执行文件(hex)文件路径
set HEX_PATH=.\Objects
 
@REM 定制Hex输出路径
set OUTPUT_PATH=.\Obj
 
@REM 软件版文件路径
Set VERSION_FILE_PATH=.\User\config.h
 
@REM 软版本字符串的格式(主版本号)
set SOFTWARE_MAIN_VERSION="#define FIRMWARE_NUM"

@REM 软版本字符串的格式(次版本号)
set SOFTWARE_MINOR_VERSION="#define FIRMWARE_MINOR_NUM"

@REM 芯片STC12C5A60S2的宏定义(正则表达式判断是否被屏蔽)
set CHIP_TYPE_12C5A=" *#define *STC12C5A60S2"

@REM 芯片STM32RET6的宏定义(正则表达式判断是否被屏蔽)
set CHIP_TYPE_15W4K=" *#define *STC15W4K48S4"
 
@REM 获取系统日期和时间
set YEAR=%DATE:~2,2%
set MONTH=%DATE:~5,2%
set DAY=%DATE:~8,2%
set HOUR=%TIME:~0,2%
set MINUTE=%TIME:~3,2%
set SECOND=%TIME:~6,2%
set CURRENT_DATE=%YEAR%%MONTH%%DAY%_%HOUR%%MINUTE%%SECOND%
 
@REM 获取软件主版本号
for /f "tokens=3 delims= " %%i in ('findstr /C:%SOFTWARE_MAIN_VERSION% %VERSION_FILE_PATH%') do set main_Ver=%%i
::set SW_Ver=%SW_Ver:~0,2%

@REM 获取软件次版本号
for /f "tokens=3 delims= " %%i in ('findstr /C:%SOFTWARE_MINOR_VERSION% %VERSION_FILE_PATH%') do set minor_Ver=%%i
::set SW_Ver=%SW_Ver:~0,2%

set version=%main_Ver%.%minor_Ver%
echo Version:%version%

@REM 获取编译的芯片类型
setlocal enabledelayedexpansion
for /f "tokens=*" %%i in ('findstr /R /C:%CHIP_TYPE_12C5A% %VERSION_FILE_PATH%') do (
	set current_string=%%i
	if "!current_string:~0,1!"=="#" (
		set chip_type=STC12-115200
		echo chip_type:!current_string!
		goto break))


@REM 获取编译的芯片类型
for /f "tokens=*" %%i in ('findstr /R /C:%CHIP_TYPE_15W4K% %VERSION_FILE_PATH%') do (
	set current_string=%%i
	if "!current_string:~0,1!"=="#" (
		set chip_type=STC15-221184
		echo chip_type:!current_string!
		goto break))

:break

if "%chip_type%"=="" (
    echo Error: The bat script does not obtain the correct chip model....
	exit
) 
@REM 定制Hex文件名
::set output_file_name=%chip_type%_V%SW_Ver%_%CURRENT_DATE%
set output_file_name=%chip_type%-V%version%
 
@REM 显示并复制Hex文件
echo "Output hex file:%OUTPUT_PATH%\%output_file_name%.hex"
move %HEX_PATH%\%HEX_NAME% %OUTPUT_PATH%\%output_file_name%.hex

endlocal
 
exit