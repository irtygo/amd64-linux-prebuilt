// SPDX-License-Identifier: GPL-2.0-only
// This file incorporates work covered by the following copyright notice:
// Copyright (c) 2020 Intel Corporation
// Copyright (c) 2024 Advanced Micro Devices, Inc.

/*
 *  soc_sdw_dmic - Helpers to handle dmic from generic machine driver
 */

#include <sound/soc.h>
#include <sound/soc-acpi.h>
#include <sound/soc-dapm.h>
#include <sound/soc_sdw_utils.h>

static const struct snd_soc_dapm_widget dmic_widgets[] = {
	SND_SOC_DAPM_MIC("SoC DMIC", NULL),
};

static const struct snd_soc_dapm_route dmic_map[] = {
	/* digital mics */
	{"DMic", NULL, "SoC DMIC"},
};

int asoc_sdw_dmic_init(struct snd_soc_pcm_runtime *rtd)
{
	struct snd_soc_card *card = rtd->card;
	int ret;

	ret = snd_soc_dapm_new_controls(&card->dapm, dmic_widgets,
					ARRAY_SIZE(dmic_widgets));
	if (ret) {
		dev_err(card->dev, "DMic widget addition failed: %d\n", ret);
		/* Don't need to add routes if widget addition failed */
		return ret;
	}

	ret = snd_soc_dapm_add_routes(&card->dapm, dmic_map,
				      ARRAY_SIZE(dmic_map));

	if (ret)
		dev_err(card->dev, "DMic map addition failed: %d\n", ret);

	return ret;
}
EXPORT_SYMBOL_NS(asoc_sdw_dmic_init, "SND_SOC_SDW_UTILS");
