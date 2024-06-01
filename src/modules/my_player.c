#include "my_player.h"

#include <stdint.h>
#include <math.h>
#include <zephyr/sys/ring_buffer.h>
#include <zephyr/shell/shell.h>

#include "sd_card.h"
#include "sw_codec_lc3.h"
#include "sw_codec_select.h"
#include "pcm_mix.h"
#include "audio_system.h"
#include "zephyr/kernel.h"

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(my_player, CONFIG_MODULE_MY_PLAYER_LOG_LEVEL);

static int cmd_play_lc3_file(const struct shell *shell, size_t argc, char **argv)
{
    if (IS_ENABLED(CONFIG_MY_PLAYER)) {
         LOG_INF("cmd_play_lc3_file Enabled");
    } else {
        LOG_INF("cmd_play_lc3_file Disabled");
    }

	return 0;
}

static int cmd_play_wav_file(const struct shell *shell, size_t argc, char **argv)
{
    LOG_INF("cmd_play_wav_file");
	return 0;
}


SHELL_STATIC_SUBCMD_SET_CREATE(
	my_player_cmd,
	SHELL_COND_CMD(CONFIG_SHELL, play_lc3, NULL, "Play LC3 file", cmd_play_lc3_file),
	SHELL_COND_CMD(CONFIG_SHELL, play_wav, NULL, "Play WAV file", cmd_play_wav_file),
	SHELL_SUBCMD_SET_END);

SHELL_CMD_REGISTER(my_player, &my_player_cmd, "Play audio files from SD card", NULL);
