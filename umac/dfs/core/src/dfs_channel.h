/*
 * Copyright (c) 2016-2017 The Linux Foundation. All rights reserved.
 * Copyright (c) 2008 Atheros Communications, Inc.
 *
 * Permission to use, copy, modify, and/or distribute this software for
 * any purpose with or without fee is hereby granted, provided that the
 * above copyright notice and this permission notice appear in all
 * copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 * WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 * AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 * DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 * PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 */

/**
 * DOC: This file has channel related information.
 */

#ifndef _NET80211__IEEE80211_H_
#define _NET80211__IEEE80211_H_

/**
 * enum ieee80211_phymode - Phymodes.
 * @IEEE80211_MODE_AUTO:            autoselect.
 * @IEEE80211_MODE_11A:             5GHz, OFDM
 * @IEEE80211_MODE_11B:             2GHz, CCK
 * @IEEE80211_MODE_11G:             2GHz, OFDM
 * @IEEE80211_MODE_FH:              2GHz, GFSK
 * @IEEE80211_MODE_TURBO_A:         5GHz, OFDM, 2x clock dynamic turbo
 * @IEEE80211_MODE_TURBO_G:         2GHz, OFDM, 2x clock dynamic turbo
 * @IEEE80211_MODE_11NA_HT20:       5Ghz, HT20
 * @IEEE80211_MODE_11NG_HT20:       2Ghz, HT20
 * @IEEE80211_MODE_11NA_HT40PLUS:   5Ghz, HT40 (ext ch +1)
 * @IEEE80211_MODE_11NA_HT40MINUS:  5Ghz, HT40 (ext ch -1)
 * @IEEE80211_MODE_11NG_HT40PLUS:   2Ghz, HT40 (ext ch +1)
 * @IEEE80211_MODE_11NG_HT40MINUS:  2Ghz, HT40 (ext ch -1)
 * @IEEE80211_MODE_11NG_HT40:       2Ghz, Auto HT40.
 * @IEEE80211_MODE_11NA_HT40:       5Ghz, Auto HT40
 * @IEEE80211_MODE_11AC_VHT20:      5Ghz, VHT20
 * @IEEE80211_MODE_11AC_VHT40PLUS:  5Ghz, VHT40 (Ext ch +1)
 * @IEEE80211_MODE_11AC_VHT40MINUS: 5Ghz  VHT40 (Ext ch -1)
 * @IEEE80211_MODE_11AC_VHT40:      5Ghz, VHT40
 * @IEEE80211_MODE_11AC_VHT80:      5Ghz, VHT80
 * @IEEE80211_MODE_11AC_VHT160:     5Ghz, VHT160
 * @IEEE80211_MODE_11AC_VHT80_80:   5Ghz, VHT80_80
 */
enum ieee80211_phymode {
	IEEE80211_MODE_AUTO             = 0,
	IEEE80211_MODE_11A              = 1,
	IEEE80211_MODE_11B              = 2,
	IEEE80211_MODE_11G              = 3,
	IEEE80211_MODE_FH               = 4,
	IEEE80211_MODE_TURBO_A          = 5,
	IEEE80211_MODE_TURBO_G          = 6,
	IEEE80211_MODE_11NA_HT20        = 7,
	IEEE80211_MODE_11NG_HT20        = 8,
	IEEE80211_MODE_11NA_HT40PLUS    = 9,
	IEEE80211_MODE_11NA_HT40MINUS   = 10,
	IEEE80211_MODE_11NG_HT40PLUS    = 11,
	IEEE80211_MODE_11NG_HT40MINUS   = 12,
	IEEE80211_MODE_11NG_HT40        = 13,
	IEEE80211_MODE_11NA_HT40        = 14,
	IEEE80211_MODE_11AC_VHT20       = 15,
	IEEE80211_MODE_11AC_VHT40PLUS   = 16,
	IEEE80211_MODE_11AC_VHT40MINUS  = 17,
	IEEE80211_MODE_11AC_VHT40       = 18,
	IEEE80211_MODE_11AC_VHT80       = 19,
	IEEE80211_MODE_11AC_VHT160      = 20,
	IEEE80211_MODE_11AC_VHT80_80    = 21,
};
#define IEEE80211_MODE_MAX      (IEEE80211_MODE_11AC_VHT80_80 + 1)

/**
 * enum dfs_ieee80211_opmode - Device opmode.
 * @IEEE80211_M_STA:     Infrastructure station
 * @IEEE80211_M_IBSS:    IBSS (adhoc) station
 * @IEEE80211_M_HOSTAP:  Software Access Point
 *
 * opmode value should be same as mlme ieee80211_opmode enum.
 */
enum dfs_ieee80211_opmode {
	IEEE80211_M_STA         = 1,
	IEEE80211_M_IBSS        = 0,
	IEEE80211_M_HOSTAP      = 6,
};

/* Channel attributes */
/* Turbo channel */
#define IEEE80211_CHAN_TURBO            0x00000010

/* CCK channel */
#define IEEE80211_CHAN_CCK              0x00000020

/* OFDM channel */
#define IEEE80211_CHAN_OFDM             0x00000040

/* 2 GHz spectrum channel. */
#define IEEE80211_CHAN_2GHZ             0x00000080

/* 5 GHz spectrum channel */
#define IEEE80211_CHAN_5GHZ             0x00000100

/* Only passive scan allowed */
#define IEEE80211_CHAN_PASSIVE          0x00000200

/* Dynamic CCK-OFDM channel */
#define IEEE80211_CHAN_DYN              0x00000400

/* GFSK channel (FHSS PHY) */
#define IEEE80211_CHAN_GFSK             0x00000800

/* Radar found on channel */
#define IEEE80211_CHAN_DFS_RADAR        0x00001000

/* 11a static turbo channel only */
#define IEEE80211_CHAN_STURBO           0x00002000

/* Half rate channel */
#define IEEE80211_CHAN_HALF             0x00004000

/* Quarter rate channel */
#define IEEE80211_CHAN_QUARTER          0x00008000

/* HT 20 channel */
#define IEEE80211_CHAN_HT20             0x00010000

/* HT 40 with extension channel above */
#define IEEE80211_CHAN_HT40PLUS         0x00020000

/* HT 40 with extension channel below */
#define IEEE80211_CHAN_HT40MINUS        0x00040000

/* HT 40 Intolerant */
#define IEEE80211_CHAN_HT40INTOL        0x00080000

/* VHT 20 channel */
#define IEEE80211_CHAN_VHT20            0x00100000

/* VHT 40 with extension channel above */
#define IEEE80211_CHAN_VHT40PLUS        0x00200000

/* VHT 40 with extension channel below */
#define IEEE80211_CHAN_VHT40MINUS       0x00400000

/* VHT 80 channel */
#define IEEE80211_CHAN_VHT80            0x00800000

/* HT 40 Intolerant mark bit for ACS use */
#define IEEE80211_CHAN_HT40INTOLMARK    0x01000000

/* channel temporarily blocked due to noise */
#define IEEE80211_CHAN_BLOCKED          0x02000000

/* VHT 160 channel */
#define IEEE80211_CHAN_VHT160           0x04000000

/* VHT 80_80 channel */
#define IEEE80211_CHAN_VHT80_80         0x08000000

/* HE 20 channel */
#define IEEE80211_CHAN_HE20             0x0000000010000000

/* HE 40 with extension channel above */
#define IEEE80211_CHAN_HE40PLUS         0x0000000020000000

/* HE 40 with extension channel below */
#define IEEE80211_CHAN_HE40MINUS        0x0000000040000000

/* HE 40 Intolerant */
#define IEEE80211_CHAN_HE40INTOL        0x0000000080000000

/* HE 40 Intolerant mark bit for ACS use */
#define IEEE80211_CHAN_HE40INTOLMARK    0x0000000100000000

/* HE 80 channel */
#define IEEE80211_CHAN_HE80             0x0000000200000000

/* HE 160 channel */
#define IEEE80211_CHAN_HE160            0x0000000400000000

/* HE 80_80 channel */
#define IEEE80211_CHAN_HE80_80          0x0000000800000000

/* flagext */
#define IEEE80211_CHAN_DFS_RADAR_FOUND    0x01

/* DFS required on channel */
#define IEEE80211_CHAN_DFS              0x0002

/* DFS required on channel for 2nd band of 80+80*/
#define IEEE80211_CHAN_DFS_CFREQ2       0x0004

/* if channel has been checked for DFS */
#define IEEE80211_CHAN_DFS_CLEAR        0x0008

/* excluded in 11D */
#define IEEE80211_CHAN_11D_EXCLUDED     0x0010

/* Channel Switch Announcement received on this channel */
#define IEEE80211_CHAN_CSA_RECEIVED     0x0020

/* ad-hoc is not allowed */
#define IEEE80211_CHAN_DISALLOW_ADHOC   0x0040

/* Station only channel */
#define IEEE80211_CHAN_DISALLOW_HOSTAP  0x0080

/* DFS radar history for slave device(STA mode) */
#define IEEE80211_CHAN_HISTORY_RADAR    0x0100

/* DFS CAC valid for  slave device(STA mode) */
#define IEEE80211_CHAN_CAC_VALID        0x0200

/* CONF: block the use of DFS channels */
#define IEEE80211_FEXT_BLKDFSCHAN          0x00000200

/* Useful combinations of channel characteristics. */
#define IEEE80211_CHAN_FHSS \
	(IEEE80211_CHAN_2GHZ | IEEE80211_CHAN_GFSK)

#define IEEE80211_CHAN_A \
	(IEEE80211_CHAN_5GHZ | IEEE80211_CHAN_OFDM)

#define IEEE80211_CHAN_B \
	(IEEE80211_CHAN_2GHZ | IEEE80211_CHAN_CCK)

#define IEEE80211_CHAN_PUREG \
	(IEEE80211_CHAN_2GHZ | IEEE80211_CHAN_OFDM)

#define IEEE80211_CHAN_G \
	(IEEE80211_CHAN_2GHZ | IEEE80211_CHAN_DYN)

#define IEEE80211_CHAN_108A \
	(IEEE80211_CHAN_5GHZ | IEEE80211_CHAN_OFDM | IEEE80211_CHAN_TURBO)

#define IEEE80211_CHAN_108G \
	(IEEE80211_CHAN_2GHZ | IEEE80211_CHAN_OFDM | IEEE80211_CHAN_TURBO)

#define IEEE80211_CHAN_ST \
	(IEEE80211_CHAN_108A | IEEE80211_CHAN_STURBO)

#define IEEE80211_CHAN_11NG_HT20 \
	(IEEE80211_CHAN_2GHZ | IEEE80211_CHAN_HT20)

#define IEEE80211_CHAN_11NA_HT20 \
	(IEEE80211_CHAN_5GHZ | IEEE80211_CHAN_HT20)

#define IEEE80211_CHAN_11NG_HT40PLUS \
	(IEEE80211_CHAN_2GHZ | IEEE80211_CHAN_HT40PLUS)

#define IEEE80211_CHAN_11NG_HT40MINUS \
	(IEEE80211_CHAN_2GHZ | IEEE80211_CHAN_HT40MINUS)

#define IEEE80211_CHAN_11NA_HT40PLUS \
	(IEEE80211_CHAN_5GHZ | IEEE80211_CHAN_HT40PLUS)

#define IEEE80211_CHAN_11NA_HT40MINUS \
	(IEEE80211_CHAN_5GHZ | IEEE80211_CHAN_HT40MINUS)

#define IEEE80211_CHAN_11AXG_HE20 \
	(IEEE80211_CHAN_2GHZ | IEEE80211_CHAN_HE20)

#define IEEE80211_CHAN_11AXA_HE20 \
	(IEEE80211_CHAN_5GHZ | IEEE80211_CHAN_HE20)

#define IEEE80211_CHAN_11AXG_HE40PLUS \
	(IEEE80211_CHAN_2GHZ | IEEE80211_CHAN_HE40PLUS)

#define IEEE80211_CHAN_11AXG_HE40MINUS \
	(IEEE80211_CHAN_2GHZ | IEEE80211_CHAN_HE40MINUS)

#define IEEE80211_CHAN_11AXG_HE40 \
	(IEEE80211_CHAN_11AXG_HE40PLUS | IEEE80211_CHAN_11AXG_HE40MINUS)

#define IEEE80211_CHAN_11AXA_HE40PLUS \
	(IEEE80211_CHAN_5GHZ | IEEE80211_CHAN_HE40PLUS)

#define IEEE80211_CHAN_11AXA_HE40MINUS \
	(IEEE80211_CHAN_5GHZ | IEEE80211_CHAN_HE40MINUS)

#define IEEE80211_CHAN_11AXA_HE40 \
	(IEEE80211_CHAN_11AXA_HE40PLUS | IEEE80211_CHAN_11AXA_HE40MINUS)

#define IEEE80211_CHAN_11AX_HE40 \
	(IEEE80211_CHAN_HE40PLUS | IEEE80211_CHAN_HE40MINUS)

#define IEEE80211_CHAN_11AXA_HE80 \
	(IEEE80211_CHAN_5GHZ | IEEE80211_CHAN_HE80)

#define IEEE80211_CHAN_11AXA_HE160 \
	(IEEE80211_CHAN_5GHZ | IEEE80211_CHAN_HE160)

#define IEEE80211_CHAN_11AXA_HE80_80 \
	(IEEE80211_CHAN_5GHZ | IEEE80211_CHAN_HE80_80)

#define IEEE80211_CHAN_ALL \
	(IEEE80211_CHAN_2GHZ | IEEE80211_CHAN_5GHZ | \
	IEEE80211_CHAN_GFSK | IEEE80211_CHAN_CCK | \
	IEEE80211_CHAN_OFDM | IEEE80211_CHAN_DYN | \
	IEEE80211_CHAN_HT20 | IEEE80211_CHAN_HT40PLUS | \
	IEEE80211_CHAN_HT40MINUS | IEEE80211_CHAN_VHT20 | \
	IEEE80211_CHAN_VHT40PLUS | IEEE80211_CHAN_VHT40MINUS | \
	IEEE80211_CHAN_VHT80 | IEEE80211_CHAN_VHT160 | \
	IEEE80211_CHAN_VHT80_80 | IEEE80211_CHAN_HALF | \
	IEEE80211_CHAN_QUARTER | IEEE80211_CHAN_HE20 | \
	IEEE80211_CHAN_HE40PLUS | IEEE80211_CHAN_HE40MINUS | \
	IEEE80211_CHAN_HE80 | IEEE80211_CHAN_HE160 | \
	IEEE80211_CHAN_HE80_80)

#define IEEE80211_CHAN_ALLTURBO \
	(IEEE80211_CHAN_ALL | IEEE80211_CHAN_TURBO | IEEE80211_CHAN_STURBO)

#define IEEE80211_IS_CHAN_FHSS(_c) \
	(((_c)->dfs_ch_flags & IEEE80211_CHAN_FHSS) == IEEE80211_CHAN_FHSS)

#define IEEE80211_IS_CHAN_A(_c) \
	(((_c)->dfs_ch_flags & IEEE80211_CHAN_A) == IEEE80211_CHAN_A)

#define IEEE80211_IS_CHAN_B(_c) \
	(((_c)->dfs_ch_flags & IEEE80211_CHAN_B) == IEEE80211_CHAN_B)

#define IEEE80211_IS_CHAN_PUREG(_c) \
	(((_c)->dfs_ch_flags & IEEE80211_CHAN_PUREG) == IEEE80211_CHAN_PUREG)

#define IEEE80211_IS_CHAN_G(_c) \
	(((_c)->dfs_ch_flags & IEEE80211_CHAN_G) == IEEE80211_CHAN_G)

#define IEEE80211_IS_CHAN_ANYG(_c) \
	(IEEE80211_IS_CHAN_PUREG(_c) || IEEE80211_IS_CHAN_G(_c))

#define IEEE80211_IS_CHAN_ST(_c) \
	(((_c)->dfs_ch_flags & IEEE80211_CHAN_ST) == IEEE80211_CHAN_ST)

#define IEEE80211_IS_CHAN_108A(_c) \
	(((_c)->dfs_ch_flags & IEEE80211_CHAN_108A) == IEEE80211_CHAN_108A)

#define IEEE80211_IS_CHAN_108G(_c) \
	(((_c)->dfs_ch_flags & IEEE80211_CHAN_108G) == IEEE80211_CHAN_108G)

#define IEEE80211_IS_CHAN_2GHZ(_c) \
	(((_c)->dfs_ch_flags & IEEE80211_CHAN_2GHZ) != 0)

#define IEEE80211_IS_CHAN_5GHZ(_c) \
	(((_c)->dfs_ch_flags & IEEE80211_CHAN_5GHZ) != 0)

#define IEEE80211_IS_CHAN_OFDM(_c) \
	(((_c)->dfs_ch_flags & IEEE80211_CHAN_OFDM) != 0)

#define IEEE80211_IS_CHAN_CCK(_c) \
	(((_c)->dfs_ch_flags & IEEE80211_CHAN_CCK) != 0)

#define IEEE80211_IS_CHAN_GFSK(_c) \
	(((_c)->dfs_ch_flags & IEEE80211_CHAN_GFSK) != 0)

#define IEEE80211_IS_CHAN_TURBO(_c) \
	(((_c)->dfs_ch_flags & IEEE80211_CHAN_TURBO) != 0)

#define IEEE80211_IS_CHAN_WEATHER_RADAR(_c) \
	((((_c)->dfs_ch_freq >= 5600) && ((_c)->dfs_ch_freq <= 5650)) || \
	(((_c)->dfs_ch_flags & IEEE80211_CHAN_HT40PLUS) && \
	 (5580 == (_c)->dfs_ch_freq)))

#define IEEE80211_IS_CHAN_STURBO(_c) \
	(((_c)->dfs_ch_flags & IEEE80211_CHAN_STURBO) != 0)

#define IEEE80211_IS_CHAN_DTURBO(_c) \
	(((_c)->dfs_ch_flags & \
	(IEEE80211_CHAN_TURBO | IEEE80211_CHAN_STURBO)) == IEEE80211_CHAN_TURBO)

#define IEEE80211_IS_CHAN_HALF(_c) \
	(((_c)->dfs_ch_flags & IEEE80211_CHAN_HALF) != 0)

#define IEEE80211_IS_CHAN_QUARTER(_c) \
	(((_c)->dfs_ch_flags & IEEE80211_CHAN_QUARTER) != 0)

#define IEEE80211_IS_CHAN_PASSIVE(_c) \
	(((_c)->dfs_ch_flags & IEEE80211_CHAN_PASSIVE) != 0)

#define IEEE80211_IS_PRIMARY_OR_SECONDARY_CHAN_DFS(_c) \
	(IEEE80211_IS_CHAN_DFS(_c) || \
	 ((IEEE80211_IS_CHAN_11AC_VHT160(_c) || \
	 IEEE80211_IS_CHAN_11AC_VHT80_80(_c) || \
	 IEEE80211_IS_CHAN_11AXA_HE160(_c) || \
	 IEEE80211_IS_CHAN_11AXA_HE80_80(_c)) \
	&& IEEE80211_IS_CHAN_DFS_CFREQ2(_c)))

#define IEEE80211_IS_CHAN_DFS(_c) \
	(((_c)->dfs_ch_flagext & \
	(IEEE80211_CHAN_DFS|IEEE80211_CHAN_DFS_CLEAR)) == IEEE80211_CHAN_DFS)

#define IEEE80211_IS_CHAN_DFS_CFREQ2(_c) \
	(((_c)->dfs_ch_flagext & \
	(IEEE80211_CHAN_DFS_CFREQ2|IEEE80211_CHAN_DFS_CLEAR)) == \
	IEEE80211_CHAN_DFS_CFREQ2)

#define IEEE80211_IS_CHAN_DFSFLAG(_c) \
	(((_c)->dfs_ch_flagext & IEEE80211_CHAN_DFS) == IEEE80211_CHAN_DFS)

#define IEEE80211_IS_CHAN_DFSFLAG_CFREQ2(_c) \
	(((_c)->dfs_ch_flagext & IEEE80211_CHAN_DFS_CFREQ2) == \
	IEEE80211_CHAN_DFS_CFREQ2)

#define IEEE80211_IS_CHAN_DISALLOW_ADHOC(_c) \
	(((_c)->dfs_ch_flagext & IEEE80211_CHAN_DISALLOW_ADHOC) != 0)

#define IEEE80211_IS_CHAN_11D_EXCLUDED(_c) \
	(((_c)->dfs_ch_flagext & IEEE80211_CHAN_11D_EXCLUDED) != 0)

#define IEEE80211_IS_CHAN_CSA(_c) \
	(((_c)->dfs_ch_flagext & IEEE80211_CHAN_CSA_RECEIVED) != 0)

#define IEEE80211_IS_CHAN_ODD(_c) \
	(((_c)->dfs_ch_freq == 5170) || ((_c)->dfs_ch_freq == 5190) || \
	((_c)->dfs_ch_freq == 5210) || ((_c)->dfs_ch_freq == 5230))

#define IEEE80211_IS_CHAN_DISALLOW_HOSTAP(_c) \
	(((_c)->dfs_ch_flagext & IEEE80211_CHAN_DISALLOW_HOSTAP) != 0)

#define IEEE80211_IS_CHAN_11NG_HT20(_c) \
	(((_c)->dfs_ch_flags & IEEE80211_CHAN_11NG_HT20) == \
	 IEEE80211_CHAN_11NG_HT20)

#define IEEE80211_IS_CHAN_11NA_HT20(_c) \
	(((_c)->dfs_ch_flags & IEEE80211_CHAN_11NA_HT20) == \
	 IEEE80211_CHAN_11NA_HT20)

#define IEEE80211_IS_CHAN_11NG_HT40PLUS(_c) \
	(((_c)->dfs_ch_flags & IEEE80211_CHAN_11NG_HT40PLUS) == \
	IEEE80211_CHAN_11NG_HT40PLUS)

#define IEEE80211_IS_CHAN_11NG_HT40MINUS(_c) \
	(((_c)->dfs_ch_flags & IEEE80211_CHAN_11NG_HT40MINUS) == \
	IEEE80211_CHAN_11NG_HT40MINUS)

#define IEEE80211_IS_CHAN_11NA_HT40PLUS(_c) \
	(((_c)->dfs_ch_flags & IEEE80211_CHAN_11NA_HT40PLUS) == \
	IEEE80211_CHAN_11NA_HT40PLUS)

#define IEEE80211_IS_CHAN_11NA_HT40MINUS(_c) \
	(((_c)->dfs_ch_flags & IEEE80211_CHAN_11NA_HT40MINUS) == \
	IEEE80211_CHAN_11NA_HT40MINUS)

#define IEEE80211_IS_CHAN_11N(_c) \
	(((_c)->dfs_ch_flags & (IEEE80211_CHAN_HT20 | \
					  IEEE80211_CHAN_HT40PLUS | \
					  IEEE80211_CHAN_HT40MINUS)) != 0)

#define IEEE80211_IS_CHAN_11N_HT20(_c) \
	(((_c)->dfs_ch_flags & (IEEE80211_CHAN_HT20)) != 0)

#define IEEE80211_IS_CHAN_11N_HT40(_c) \
	(((_c)->dfs_ch_flags & (IEEE80211_CHAN_HT40PLUS | \
					IEEE80211_CHAN_HT40MINUS)) != 0)

#define IEEE80211_IS_CHAN_11NG(_c) \
	(IEEE80211_IS_CHAN_2GHZ((_c)) && IEEE80211_IS_CHAN_11N((_c)))

#define IEEE80211_IS_CHAN_11NA(_c) \
	(IEEE80211_IS_CHAN_5GHZ((_c)) && IEEE80211_IS_CHAN_11N((_c)))

#define IEEE80211_IS_CHAN_11N_HT40PLUS(_c) \
	(((_c)->dfs_ch_flags & IEEE80211_CHAN_HT40PLUS) != 0)

#define IEEE80211_IS_CHAN_11N_HT40MINUS(_c) \
	(((_c)->dfs_ch_flags & IEEE80211_CHAN_HT40MINUS) != 0)

#define IEEE80211_IS_CHAN_HT20_CAPABLE(_c) \
	(((_c)->dfs_ch_flags & IEEE80211_CHAN_HT20) == IEEE80211_CHAN_HT20)

#define IEEE80211_IS_CHAN_HT40PLUS_CAPABLE(_c) \
	(((_c)->dfs_ch_flags & IEEE80211_CHAN_HT40PLUS)  == \
	 IEEE80211_CHAN_HT40PLUS)

#define IEEE80211_IS_CHAN_HT40MINUS_CAPABLE(_c) \
	(((_c)->dfs_ch_flags & IEEE80211_CHAN_HT40MINUS) == \
	 IEEE80211_CHAN_HT40MINUS)

#define IEEE80211_IS_CHAN_HT40_CAPABLE(_c) \
	(IEEE80211_IS_CHAN_HT40PLUS_CAPABLE(_c) || \
	IEEE80211_IS_CHAN_HT40MINUS_CAPABLE(_c))

#define IEEE80211_IS_CHAN_HT_CAPABLE(_c) \
	(IEEE80211_IS_CHAN_HT20_CAPABLE(_c) || \
	IEEE80211_IS_CHAN_HT40_CAPABLE(_c))

#define IEEE80211_IS_CHAN_11N_CTL_CAPABLE(_c) \
	IEEE80211_IS_CHAN_HT20_CAPABLE(_c)

#define IEEE80211_IS_CHAN_11N_CTL_U_CAPABLE(_c) \
	(((_c)->dfs_ch_flags & IEEE80211_CHAN_HT40PLUS) == \
	 IEEE80211_CHAN_HT40PLUS)

#define IEEE80211_IS_CHAN_11N_CTL_L_CAPABLE(_c) \
	(((_c)->dfs_ch_flags & IEEE80211_CHAN_HT40MINUS) == \
	 IEEE80211_CHAN_HT40MINUS)

#define IEEE80211_IS_CHAN_11N_CTL_40_CAPABLE(_c) \
	(IEEE80211_IS_CHAN_11N_CTL_U_CAPABLE((_c)) || \
	IEEE80211_IS_CHAN_11N_CTL_L_CAPABLE((_c)))

#define IEEE80211_IS_CHAN_VHT(_c) \
	(((_c)->dfs_ch_flags & (IEEE80211_CHAN_VHT20 | \
			    IEEE80211_CHAN_VHT40PLUS | \
			    IEEE80211_CHAN_VHT40MINUS | \
			    IEEE80211_CHAN_VHT80 | \
			    IEEE80211_CHAN_VHT160 | \
			    IEEE80211_CHAN_VHT80_80)) != 0)

#define IEEE80211_IS_CHAN_11AC(_c) \
	(IEEE80211_IS_CHAN_5GHZ((_c)) && IEEE80211_IS_CHAN_VHT((_c)))

#define IEEE80211_CHAN_11AC_VHT20 \
	(IEEE80211_CHAN_5GHZ | IEEE80211_CHAN_VHT20)

#define IEEE80211_CHAN_11AC_VHT40 \
	(IEEE80211_CHAN_5GHZ | IEEE80211_CHAN_VHT40PLUS | \
	 IEEE80211_CHAN_VHT40MINUS)

#define IEEE80211_CHAN_11AC_VHT40PLUS \
	(IEEE80211_CHAN_5GHZ | IEEE80211_CHAN_VHT40PLUS)

#define IEEE80211_CHAN_11AC_VHT40MINUS \
	(IEEE80211_CHAN_5GHZ | IEEE80211_CHAN_VHT40MINUS)

#define IEEE80211_CHAN_11AC_VHT80 \
	(IEEE80211_CHAN_5GHZ | IEEE80211_CHAN_VHT80)

#define IEEE80211_CHAN_11AC_VHT160 \
	(IEEE80211_CHAN_5GHZ | IEEE80211_CHAN_VHT160)

#define IEEE80211_CHAN_11AC_VHT80_80 \
	(IEEE80211_CHAN_5GHZ | IEEE80211_CHAN_VHT80_80)

#define IEEE80211_IS_CHAN_11AC_VHT20(_c) \
	(((_c)->dfs_ch_flags & IEEE80211_CHAN_11AC_VHT20) == \
	 IEEE80211_CHAN_11AC_VHT20)

#define IEEE80211_IS_CHAN_11AC_VHT40(_c) \
	(((_c)->dfs_ch_flags & (IEEE80211_CHAN_VHT40PLUS | \
			    IEEE80211_CHAN_VHT40MINUS)) != 0)

#define IEEE80211_IS_CHAN_11AC_VHT40PLUS(_c) \
	(((_c)->dfs_ch_flags & IEEE80211_CHAN_11AC_VHT40PLUS) == \
	IEEE80211_CHAN_11AC_VHT40PLUS)

#define IEEE80211_IS_CHAN_11AC_VHT40MINUS(_c) \
	(((_c)->dfs_ch_flags & IEEE80211_CHAN_11AC_VHT40MINUS) == \
	IEEE80211_CHAN_11AC_VHT40MINUS)

#define IEEE80211_IS_CHAN_11AC_VHT80(_c) \
	(((_c)->dfs_ch_flags & IEEE80211_CHAN_11AC_VHT80) == \
	 IEEE80211_CHAN_11AC_VHT80)

#define IEEE80211_IS_CHAN_11AC_VHT160(_c) \
	(((_c)->dfs_ch_flags & IEEE80211_CHAN_11AC_VHT160) == \
	 IEEE80211_CHAN_11AC_VHT160)

#define IEEE80211_IS_CHAN_11AC_VHT80_80(_c) \
	(((_c)->dfs_ch_flags & IEEE80211_CHAN_11AC_VHT80_80) == \
	IEEE80211_CHAN_11AC_VHT80_80)

#define IEEE80211_CH_HOPPING_SET_CHAN_BLOCKED(_c)    \
	((_c)->dfs_ch_flags |= IEEE80211_CHAN_BLOCKED)

#define IEEE80211_CH_HOPPING_IS_CHAN_BLOCKED(_c)    \
	(((_c)->dfs_ch_flags & IEEE80211_CHAN_BLOCKED) == \
	 IEEE80211_CHAN_BLOCKED)

#define IEEE80211_CH_HOPPING_CLEAR_CHAN_BLOCKED(_c)    \
	((_c)->dfs_ch_flags &= ~IEEE80211_CHAN_BLOCKED)

#define IEEE80211_IS_CHAN_RADAR(_c)    \
	(((_c)->dfs_ch_flags & IEEE80211_CHAN_DFS_RADAR) == \
	 IEEE80211_CHAN_DFS_RADAR)

#define IEEE80211_CHAN_SET_RADAR(_c)    \
	((_c)->dfs_ch_flags |= IEEE80211_CHAN_DFS_RADAR)

#define IEEE80211_CHAN_CLR_RADAR(_c)    \
	((_c)->dfs_ch_flags &= ~IEEE80211_CHAN_DFS_RADAR)

#define IEEE80211_CHAN_SET_DISALLOW_ADHOC(_c)   \
	((_c)->dfs_ch_flagext |= IEEE80211_CHAN_DISALLOW_ADHOC)

#define IEEE80211_CHAN_SET_DISALLOW_HOSTAP(_c)   \
	((_c)->dfs_ch_flagext |= IEEE80211_CHAN_DISALLOW_HOSTAP)

#define IEEE80211_CHAN_SET_DFS(_c)  \
	((_c)->dfs_ch_flagext |= IEEE80211_CHAN_DFS)

#define IEEE80211_CHAN_SET_DFS_CLEAR(_c)  \
	((_c)->dfs_ch_flagext |= IEEE80211_CHAN_DFS_CLEAR)

#define IEEE80211_CHAN_EXCLUDE_11D(_c)  \
	((_c)->dfs_ch_flagext |= IEEE80211_CHAN_11D_EXCLUDED)

#define IEEE80211_IS_CHAN_HISTORY_RADAR(_c)    \
	(((_c)->dfs_ch_flagext & IEEE80211_CHAN_HISTORY_RADAR) == \
	IEEE80211_CHAN_HISTORY_RADAR)

#define IEEE80211_CHAN_SET_HISTORY_RADAR(_c)    \
	((_c)->dfs_ch_flagext |= IEEE80211_CHAN_HISTORY_RADAR)

#define IEEE80211_CHAN_CLR_HISTORY_RADAR(_c)    \
	((_c)->dfs_ch_flagext &= ~IEEE80211_CHAN_HISTORY_RADAR)

#define IEEE80211_IS_CHAN_CAC_VALID(_c)    \
	(((_c)->dfs_ch_flagext & IEEE80211_CHAN_CAC_VALID) == \
	 IEEE80211_CHAN_CAC_VALID)

#define IEEE80211_CHAN_SET_CAC_VALID(_c)    \
	((_c)->dfs_ch_flagext |= IEEE80211_CHAN_CAC_VALID)

#define IEEE80211_CHAN_CLR_CAC_VALID(_c)    \
	((_c)->dfs_ch_flagext &= ~IEEE80211_CHAN_CAC_VALID)

#define IEEE80211_CHAN_ANY      (-1)    /* token for ``any channel'' */

#define IEEE80211_CHAN_ANYC \
	((struct dfs_ieee80211_channel *) IEEE80211_CHAN_ANY)

#define IEEE80211_IS_CHAN_11AXA_HE20(_c) \
	(((_c)->dfs_ch_flags & IEEE80211_CHAN_11AXA_HE20) == \
	 IEEE80211_CHAN_11AXA_HE20)

#define IEEE80211_IS_CHAN_11AXA_HE40PLUS(_c) \
	(((_c)->dfs_ch_flags & IEEE80211_CHAN_11AXA_HE40PLUS) == \
	 IEEE80211_CHAN_11AXA_HE40PLUS)

#define IEEE80211_IS_CHAN_11AXA_HE40MINUS(_c) \
	(((_c)->dfs_ch_flags & IEEE80211_CHAN_11AXA_HE40MINUS) == \
	 IEEE80211_CHAN_11AXA_HE40MINUS)

#define IEEE80211_IS_CHAN_11AXA_HE80(_c) \
	(((_c)->dfs_ch_flags & IEEE80211_CHAN_11AXA_HE80) == \
	 IEEE80211_CHAN_11AXA_HE80)

#define IEEE80211_IS_CHAN_11AXA_HE160(_c) \
	(((_c)->dfs_ch_flags & IEEE80211_CHAN_11AXA_HE160) == \
	 IEEE80211_CHAN_11AXA_HE160)

#define IEEE80211_IS_CHAN_11AXA_HE80_80(_c) \
	(((_c)->dfs_ch_flags & IEEE80211_CHAN_11AXA_HE80_80) == \
	 IEEE80211_CHAN_11AXA_HE80_80)

#define IEEE80211_IS_CHAN_MODE_20(_c)      \
	(IEEE80211_IS_CHAN_11NA_HT20(_c)  ||  \
	 IEEE80211_IS_CHAN_11AC_VHT20(_c) ||  \
	 IEEE80211_IS_CHAN_11AXA_HE20(_c))

#define IEEE80211_IS_CHAN_MODE_40(_c)          \
	(IEEE80211_IS_CHAN_11AC_VHT40PLUS(_c)  || \
	 IEEE80211_IS_CHAN_11AC_VHT40MINUS(_c) || \
	 IEEE80211_IS_CHAN_11NA_HT40PLUS(_c)   || \
	 IEEE80211_IS_CHAN_11NA_HT40MINUS(_c)  || \
	 IEEE80211_IS_CHAN_11AXA_HE40PLUS(_c)  || \
	 IEEE80211_IS_CHAN_11AXA_HE40MINUS(_c))

#define IEEE80211_IS_CHAN_MODE_80(_c)          \
	(IEEE80211_IS_CHAN_11AC_VHT80(_c)      || \
	 IEEE80211_IS_CHAN_11AXA_HE80(_c))

#define IEEE80211_IS_CHAN_MODE_160(_c)         \
	(IEEE80211_IS_CHAN_11AC_VHT160(_c)     || \
	 IEEE80211_IS_CHAN_11AXA_HE160(_c))

#define IEEE80211_IS_CHAN_MODE_80_80(_c)       \
	(IEEE80211_IS_CHAN_11AC_VHT80_80(_c)   || \
	 IEEE80211_IS_CHAN_11AXA_HE80_80(_c))

#endif /*  _NET80211__IEEE80211_H_ */
