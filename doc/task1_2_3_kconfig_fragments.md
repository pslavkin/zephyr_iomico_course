---
title: Task1_2_3
---

## Task 1 + 2 + 3

### Task 1 - Zephyr project creation T2 style and CPP version selection

<img src="./doc/pics/task1.jpg" width="450" align="center" title="task2">

I create a new project called iomico_blinky that lives aside zephyr kernel

```
zephyr_course_iomico
▸ build/
▸ env/
▸ iomico_blinky/
▸ modules/
▸ zephyr/
```
with this west.yml file

```diff
manifest:
  defaults:
    remote: upstream

  remotes:
    - name: upstream
      url-base: https://github.com/zephyrproject-rtos

  self:
    path: iomico_blinky
  #
  # Please add items below based on alphabetical order
  projects:
    - name: zephyr
      remote: upstream
      #revision: main
      revision: v3.6.0
      import:
        # By using name-allowlist we can clone only the modules that are
        # strictly needed by the application.
        name-allowlist:
          - cmsis      # required by the ARM port
          - hal_nordic # required by the custom_plank board (Nordic based)

        #if not using name-allowlist, the following is an example of how to
        #specify the modules to be imported one by one
          #  projects:
          #        - name: cmsis
          #        #if not specified, the default remote is used
          #          remote: upstream
          #          revision: 4b96cbb174678dcd3ca86e11e1f24bc5f8726da0
          #          path: modules/hal/cmsis
          #          groups:
          #            - hal
```

#### CPP version could be selected using menuconfig or just puttin the next
defines in .prf file:

```
CONFIG_CPP=y
CONFIG_STD_CPP17=y
CONFIG_NEWLIB_LIBC=y
CONFIG_NEWLIB_LIBC_NANO=y
```

### Task 2 - Zephyr version update

<img src="./doc/pics/task2.jpg" width="450" align="center" title="task2">

Modifying west.yml file to use v3.6.0/v3.7.0 version of zephyr and updating the
zephyr version with west update command

```diff
  projects:
    - name: zephyr
      remote: upstream
      #revision: main
      #revision: v3.6.0
      revision: v3.7.0
      import:
```

```bash
west update                                                                                      INT ✘
=== updating zephyr (zephyr):
Updating files: 100% (17053/17053), done.
Warning: you are leaving 1770 commits behind, not connected to
any of your branches:

  4488ed1a20a tests: drivers: build_all: display: add config for 16-bit transfer
  a68c1aa4add drivers: mipi_dbi_spi: add 16-bit transfer to C4
  c809c3730df drivers: mipi_dbi_spi: splitting SPI write function
  d0ba5a38c9f drivers: mipi_dbi_spi: splitting SPI read function
 ... and 1766 more.

If you want to keep them by creating a new branch, this may be a good time
to do so with:

 git branch <new-branch-name> 4488ed1a20a

HEAD is now at 36940db938a release: Zephyr v3.7.0
=== updating cmsis (modules/hal/cmsis):
HEAD is now at 4b96cbb doc: Update documentations for CMSIS 5.9.0
=== updating hal_nordic (modules/hal/nordic):
Warning: you are leaving 103 commits behind, not connected to
any of your branches:

  e0e48c4 module: suit: Update blob to v5.0.0
  cff1472 module: Remove Wi-Fi binary blobs
  5fbccc3 Revert "nrfx: drivers: nrfx_uarte: skip flush workaround for BSIM target"
  95ec8e4 codeowners: Delete unused file
 ... and 99 more.

If you want to keep them by creating a new branch, this may be a good time
to do so with:

 git branch <new-branch-name> e0e48c4
```
```bash
HEAD is now at ab5cb2e nrfx: drivers: nrfx_gpiote: move enabling GPIOTE port interrupt
    ~/zephyr_course_iomico  west update                                                                                   ✔  4s 
=== updating zephyr (zephyr):
Updating files: 100% (30581/30581), done.
Previous HEAD position was 36940db938a release: Zephyr v3.7.0
HEAD is now at 468eb56cf24 release: Zephyr v3.6.0
=== updating cmsis (modules/hal/cmsis):
HEAD is now at 4b96cbb doc: Update documentations for CMSIS 5.9.0
=== updating hal_nordic (modules/hal/nordic):
Warning: you are leaving 21 commits behind, not connected to
any of your branches:

  ab5cb2e nrfx: drivers: nrfx_gpiote: move enabling GPIOTE port interrupt
  f311735 nrfx: allow enabling SPIM externally when CTRLSEL is present
  cfe3ef1 mdk: Fix SAADC gain mask
  fc02d66 nrfx: hal: auxpll: add additional APIs
 ... and 17 more.

If you want to keep them by creating a new branch, this may be a good time
to do so with:

 git branch <new-branch-name> ab5cb2e

HEAD is now at dce8519 nrfx: samples: update to version 3.3
    ~/zephyr_course_iomico   
 ```


### Task 3 - Kconfig segments

<img src="./doc/pics/task3.jpg" width="450" align="center" title="task2">

#### minimal answer:
```diff
$ diff -u build/zephyr/.config.old build/zephyr/.config | grep -E '^\+[^+]' | sed 's/^\+//' >> iomico_blinky/prj.prj
```
#### Explanation

#### method 1 - basic .conf file

after launch west build --pristine,  build/zephyr/.conf file will be generated
based on board defconfig and prj.conf.
i.e.: next build capture shows the generation of the .config file and the
modification of the banner string to "BANNER1" 

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

The .config file will be generated in build/zephyr directory but it contains **all**
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
 as it shows, the .config file contains all the default values and not only the
 changed values. It will work and it's a valid way to generate a prj.conf file
 but it's not the most efficient way to do it and it's a bit difficult to read
 the changed values in the .config file compared with the default values of the
 board configuration file (i.e. native_sim_defconfig) 

#### method 2 - diff .conf with .conf_old

After second build the .config file will saved as .config_old and the new .config will be generated.
i.e. using menuconfig to set CONFIG_BOOT_BANNER_STRING="BANNER1" to "BANNER2" and run the diff command:

```diff
[ ] Initialize stack areas
[*] Boot banner
(BANNER2) Boot banner string
(0) Boot delay in milliseconds
[ ] Clear screen
[ ] Thread monitoring
```

then I'd generate a diff file containing only the diff of .conf vs .conf.old file with
next command:

```diff
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
prj.conf will be merged with the board defconfig conf file, so it's easy to read
the changed mades for the actual project

To achieve that the next single line script could be used

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
  in this case west will also try to find and merge a file under iomico_blinky/boards/<BOARD>_banner2.conf

#### method 3 - minimal defconfig

menuconfig interface offer the ability to generate a minimal defconfig file
using 'D' option

The output of this method is ***similar*** as #2, but it also include default
prj.conf and other merged fragment files as the next example

Setting the banner string to "BANNER3" and saving the minimal configuration to
prj_banner3.conf file with the next command:

```diff
[ ] Initialize stack areas
[*] Boot banner
(BANNER3) Boot banner string
(0) Boot delay in milliseconds
[ ] Clear screen
[ ] Thread monitoring
```

```diff
../../../iomico_blinky/prj_banner3.conf
(Relative to /home/pslavkin/zephyr_course_iomico/build/zephyr/kconfig/)
Refer to your home directory with ~
---
Success
Minimal configuration saved to '../../../iomico_blinky/prj_banner3.conf'
```

if I inspect the prj_banner3.conf file I'd see the next content:
```diff
$ cat ../../../iomico_blinky/prj_banner3.conf 
CONFIG_SYS_CLOCK_HW_CYCLES_PER_SEC=1000000
CONFIG_GPIO=y
CONFIG_LOG=y
CONFIG_ASSERT=y
CONFIG_CONSOLE=y
+CONFIG_BOOT_BANNER_STRING="BANNER3"
CONFIG_HEAP_MEM_POOL_SIZE=256
```
So the prj_banner3.conf file contains only the changed values compared with the
default board configuration file (native_sim_defconfig) merged with prj.conf
file and other fragment files that could be merged with the prj.conf file as
well

## Conclusion

I found method 3 as the most efficient way to generate a default prj.conf file with only the
changed values, but the method 2 is also a good way to generate a bunch of prj_BANNERX.conf file
with only the changed values compared with default board values and choose
different prj_x.conf files depending on the target/release version

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
