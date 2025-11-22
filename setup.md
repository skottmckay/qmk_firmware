I used WSL for this

Install qmk as per https://docs.qmk.fm/newbs
  except use fork with this command to pick the branch with the Q6 max firmware

`qmk setup -H ~/qmk_firmware -b wireless_playground skottmckay/qmk_firmware`


This _should_ run `git submodule update --init --recursive` but can do so manually to be sure.

MUST use the 'via' not 'default' keymap otherwise https://launcher.keychron.com/ won't work
  - not necessarily clear that 'default' excludes the VIA functionality
  
Build and copy for flashing on Windows using QMK toolkit
  ~/qmk_firmware> qmk compile -kb keychron/q6_max/ansi_encoder -km via && cp keychron_q6_max_ansi_encoder_via.bin /mnt/c/Users/me/somewhere

Installed QMK toolbox via the instructions/links on https://launcher.keychron.com/#/firmware/flash to make sure it was compatible.
Must run it as admin.

See readme.md in keyboards/keychron/q6_max
Use `make` commands to build or 

NOTE:

If after flashing you go to launcher and the current effect is 'none' and it's not recognising changes to effect or values it's not connected properly.
Try one or more of these until the effect is detected
  - close QMK toolbox
  - reconnect keyboard
  - refresh browser page with toolbox
  
Changes:

Updated quantum/rgb_matrix/animations/runners/effect_runner_reactive_splash.h to set the colour to blue after the effect ran.
If you want to change that colour you have to rebuild and reflash.

See https://github.com/skottmckay/qmk_firmware/commit/61839521bf8bd899894d081fa5746d4618eea5de

Updated timeout so LEDs turn off after 15 mins of activity in keyboards/keychron/q6_max/ansi_encoder/config.h
#    define RGB_MATRIX_TIMEOUT (15 * 60 * 1000)
