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

#include <power/reboot.h>

#include <nrfx.h>
#include <hal/nrf_power.h>
#if !NRF_POWER_HAS_RESETREAS
#include <hal/nrf_reset.h>
#endif

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(my_player, CONFIG_MODULE_MY_PLAYER_LOG_LEVEL);

static struct k_timer play_timer;

static void play_timer_expiry_function(struct k_timer *timer_id)
{
    LOG_INF("play_timer expiry function");
} 

static void player_timer_stop_function(struct k_timer *timer_id)
{
    LOG_INF("play_timer stop function");
}

static int cmd_broadcast_lc3_file(const struct shell *shell, size_t argc, char **argv)
{
    LOG_INF("cmd_broadcast_lc3_file");
    k_timer_init(&play_timer, play_timer_expiry_function, player_timer_stop_function);
    k_timer_start(&play_timer,  K_SECONDS(2),  K_SECONDS(2));
	return 0;
}

static int cmd_broadcast_wav_file(const struct shell *shell, size_t argc, char **argv)
{
    LOG_INF("cmd_broadcast_wav_file");
    k_timer_stop(&play_timer);
	return 0;
}

static int cmd_bis_src_start(const struct shell *shell, size_t argc, char **argv)
{
    LOG_INF("cmd_bis_src_start");
	return 0;
}

static int cmd_bis_src_stop(const struct shell *shell, size_t argc, char **argv)
{
    LOG_INF("cmd_bis_src_stop");
	return 0;
}

static int cmd_bis_src_set_broadcast_name(const struct shell *shell, size_t argc, char **argv)
{
    LOG_INF("cmd_bis_src_set_broadcast_name");
	return 0;
}

static int cmd_bis_src_set_broadcast_code(const struct shell *shell, size_t argc, char **argv)
{
    LOG_INF("cmd_bis_src_set_broadcast_code");
	return 0;
}

static int cmd_sys_reboot(const struct shell *shell, size_t argc, char **argv)
{
    LOG_INF("cmd_sys_reboot");
    sys_reboot(SYS_REBOOT_COLD);
	return 0;
}

static int cmd_print_reset_reason(const struct shell *shll, size_t argc, char **argv)
{
    uint32_t reas;
	reas = nrf_reset_resetreas_get(NRF_RESET);
	nrf_reset_resetreas_clear(NRF_RESET, reas);
	if (reas & NRF_RESET_RESETREAS_NFC_MASK) {
		printk("Wake up by NFC field detect\n");
	} else if (reas & NRF_RESET_RESETREAS_RESETPIN_MASK) {
		printk("Reset by pin-reset\n");
	} else if (reas & NRF_RESET_RESETREAS_SREQ_MASK) {
		printk("Reset by soft-reset\n");
	} else if (reas) {
		printk("Reset by a different source (0x%08X)\n", reas);
	} else {
		printk("Power-on-reset\n");
	}
    return 0;
}



SHELL_STATIC_SUBCMD_SET_CREATE(
	my_player_cmd,
	SHELL_COND_CMD(CONFIG_SHELL, broadcast_lc3, NULL, "Broadcast LC3 file ", cmd_broadcast_lc3_file),
	SHELL_COND_CMD(CONFIG_SHELL, broadcast_wav, NULL, "Broadcast WAV file", cmd_broadcast_wav_file),
    SHELL_COND_CMD(CONFIG_SHELL, bis_src_start, NULL, "BIS Source Start", cmd_bis_src_start),
    SHELL_COND_CMD(CONFIG_SHELL, bis_src_stop, NULL, "BIS Source Stop", cmd_bis_src_stop),
    SHELL_COND_CMD(CONFIG_SHELL, bis_src_set_broadcast_name, NULL, "BIS Source Set Broadcast Name", cmd_bis_src_set_broadcast_name),
    SHELL_COND_CMD(CONFIG_SHELL, bis_src_set_broadcast_code, NULL, "BIS Source Set Broadcast Code", cmd_bis_src_set_broadcast_code),
    SHELL_COND_CMD(CONFIG_SHELL, sys_reboot, NULL, "Reboot system", cmd_sys_reboot),
    SHELL_COND_CMD(CONFIG_SHELL, print_reboot_reason, NULL, "Print reset reason", cmd_print_reset_reason),
	SHELL_SUBCMD_SET_END);


SHELL_CMD_REGISTER(my_player, &my_player_cmd, "Control Broadcast Source", NULL);
