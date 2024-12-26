---
title: Task2
---

## Task2 - Kconfig fragments

#### minimal answer:
```diff
$ diff -u build/zephyr/.config.old build/zephyr/.config | grep -E '^\+[^+]' | sed 's/^\+//' >> iomico_blinky/prj.prj
```
### Explanation of the task

### method 1 - basic .conf file

launch west build build/zephyr/.conf file will be generated based on defaults
.conf defaults fragments as in next build capture

```
$ west build -b native_sim -s iomico_blinky -d build --pristine

[ ] Initialize stack areas
[*] Boot banner
(BANNER1) Boot banner string
(0) Boot delay in milliseconds
[ ] Clear screen
[ ] Thread monitoring

...
Loaded configuration '/home/pslavkin/zephyr_course_iomico/zephyr/boards/native/native_sim/native_sim_defconfig'
Merged configuration '/home/pslavkin/zephyr_course_iomico/iomico_blinky/prj.conf'
Configuration saved to '/home/pslavkin/zephyr_course_iomico/build/zephyr/.config'
...
```

The .config file will be generated in build/zephyr directory but it contains all
the defaults and ***not only the changed values***.
i.e. the banner string CONFIG_BANNER_STRING could be extracted from build/zephyr/.conf using this command:

```diff
$ grep -10 BANNER_STRING  ./build/zephyr/.config

# Misc Kernel related options
#
CONFIG_ERRNO=y
# end of Misc Kernel related options

#
# Kernel Debugging and Metrics
#
CONFIG_SKIP_BSS_CLEAR=y
CONFIG_BOOT_BANNER=y
+ CONFIG_BOOT_BANNER_STRING="BANNER1"
CONFIG_BOOT_DELAY=0
# CONFIG_BOOT_CLEAR_SCREEN is not set
# CONFIG_THREAD_MONITOR is not set
# CONFIG_THREAD_NAME is not set
# CONFIG_THREAD_RUNTIME_STATS is not set
# end of Kernel Debugging and Metrics

# CONFIG_OBJ_CORE is not set
```

### method 2 - diff .conf with .conf_old

After second build the .config file will saved as .config_old and the new .config will be generated.
i.e. using menuconfig to set CONFIG_BOOT_BANNER_STRING="BANNER1" to "BANNER2" and run the diff command:

generate a diff file containing only the diff of .conf vs .conf.old file with
next command:

```diff
[ ] Initialize stack areas
[*] Boot banner
(BANNER2) Boot banner string
(0) Boot delay in milliseconds
[ ] Clear screen
[ ] Thread monitoring

$ diff -u build/zephyr/.config.old build/zephyr/.config

--- build/zephyr/.config.old    2024-12-26 12:15:46.721091671 -0300
+++ build/zephyr/.config        2024-12-26 12:39:27.353144098 -0300
@@ -335,7 +335,7 @@
 #
 CONFIG_SKIP_BSS_CLEAR=y
 CONFIG_BOOT_BANNER=y
-CONFIG_BOOT_BANNER_STRING="BANNER1"
+CONFIG_BOOT_BANNER_STRING="BANNER2"
 CONFIG_BOOT_DELAY=0
 # CONFIG_BOOT_CLEAR_SCREEN is not set
 # CONFIG_THREAD_MONITOR is not set

```

The idea is to use a prj.conf file to store only the changed values
prj.conf will be merged with the board default conf file, so it's easy to read
the changed mades for the actual project

To achieve that the next script could be used

```diff
$ diff -u build/zephyr/.config.old build/zephyr/.config | grep -E '^\+[^+]' | sed 's/^\+//' > iomico_blinky/prj_banner2.prj && cat iomico_blinky/prj_banner2.conf

CONFIG_BOOT_BANNER_STRING="BANNER2"
```
and then set the env variable as
```diff
export CONF_FILE=prj_banner2.conf
west build -b native_sim -s iomico_blinky -d build --pristine
```
note:
  in this case west will try to find and merge a file under iomico_blinky/boards/<BOARD>_banner2.conf

### method 3 - minimal defconfig

menuconfig west option has the ability to generate a minimal defconfig file
using D option
The output of this method is ***similar*** as #2, but it also include default
prj.conf and other merged fragment files as the next example

```diff
[ ] Initialize stack areas
[*] Boot banner
(BANNER3) Boot banner string
(0) Boot delay in milliseconds
[ ] Clear screen
[ ] Thread monitoring

```
Filename to save minimal configuration to

```diff
../../../iomico_blinky/prj_banner3.conf
(Relative to /home/pslavkin/zephyr_course_iomico/build/zephyr/kconfig/)
Refer to your home directory with ~
---
Success
Minimal configuration saved to '../../../iomico_blinky/prj_banner3.conf'

$ cat ../../../iomico_blinky/prj_banner3.conf 
CONFIG_SYS_CLOCK_HW_CYCLES_PER_SEC=1000000
CONFIG_GPIO=y
CONFIG_LOG=y
CONFIG_ASSERT=y
CONFIG_CONSOLE=y
+CONFIG_BOOT_BANNER_STRING="BANNER3"
CONFIG_HEAP_MEM_POOL_SIZE=256
```

## Conclusion

I found method 3 as the most efficient way to generate a default prj.conf file with only the
changed values, but the method 2 is also a good way to generate a bunch of prj_BANNERX.conf file
with only the changed values compared with default board values

#### method 1
 only prj.conf copied with the contents of build/zephyr/.conf file once it's
 generated

#### method 2
 could use a default prj.conf merged with board/<BOARD>.conf with the content
 of diff script generated prj_banner2.conf file

 or just append prj_banner2.conf to the prj.conf file with
 cat prj_banner2.conf >> prj.conf

#### method 3

replace prj.conf with the content of the default banner3.conf file or you'd
use:
```diff
export CONF_FILE=prj_banner3.conf
west build -b native_sim -s iomico_blinky -d build --pristine
```






