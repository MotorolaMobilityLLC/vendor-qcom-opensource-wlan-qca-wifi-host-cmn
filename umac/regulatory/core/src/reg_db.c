/*
 * Copyright (c) 2017 The Linux Foundation. All rights reserved.
 *
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
 * DOC: reg_db.c
 * This file provides regulatory data base
 */

#include <qdf_types.h>
#include <qdf_trace.h>
#include "reg_db.h"

enum country_code {
	CTRY_AFGHANISTAN = 4,
	CTRY_ALBANIA = 8,
	CTRY_ALGERIA = 12,
	CTRY_AMERICAN_SAMOA = 16,
	CTRY_ANGUILLA = 660,
	CTRY_ARGENTINA = 32,
	CTRY_ARGENTINA2 = 5003,
	CTRY_ARMENIA = 51,
	CTRY_ARUBA = 533,
	CTRY_AUSTRALIA = 36,
	CTRY_AUSTRALIA2 = 5000,
	CTRY_AUSTRIA = 40,
	CTRY_AZERBAIJAN = 31,
	CTRY_BAHAMAS = 44,
	CTRY_BAHRAIN = 48,
	CTRY_BANGLADESH = 50,
	CTRY_BARBADOS = 52,
	CTRY_BELARUS = 112,
	CTRY_BELGIUM = 56,
	CTRY_BELGIUM2 = 4101,
	CTRY_BELIZE = 84,
	CTRY_BERMUDA = 60,
	CTRY_BHUTAN = 64,
	CTRY_BOLIVIA = 68,
	CTRY_BOSNIA_HERZ = 70,
	CTRY_BRAZIL = 76,
	CTRY_BRUNEI_DARUSSALAM = 96,
	CTRY_BULGARIA = 100,
	CTRY_BURKINA_FASO = 854,
	CTRY_CAMBODIA = 116,
	CTRY_CANADA = 124,
	CTRY_CANADA2 = 5001,
	CTRY_CAYMAN_ISLANDS = 136,
	CTRY_CENTRAL_AFRICA_REPUBLIC = 140,
	CTRY_CHAD = 148,
	CTRY_CHILE = 152,
	CTRY_CHINA = 156,
	CTRY_CHRISTMAS_ISLAND = 162,
	CTRY_COLOMBIA = 170,
	CTRY_COSTA_RICA = 188,
	CTRY_COTE_DIVOIRE = 384,
	CTRY_CROATIA = 191,
	CTRY_CYPRUS = 196,
	CTRY_CZECH = 203,
	CTRY_DENMARK = 208,
	CTRY_DOMINICA = 212,
	CTRY_DOMINICAN_REPUBLIC = 214,
	CTRY_ECUADOR = 218,
	CTRY_EGYPT = 818,
	CTRY_EL_SALVADOR = 222,
	CTRY_ESTONIA = 233,
	CTRY_ETHIOPIA = 231,
	CTRY_FINLAND = 246,
	CTRY_FRANCE = 250,
	CTRY_FRENCH_GUIANA = 254,
	CTRY_FRENCH_POLYNESIA = 258,
	CTRY_GEORGIA = 268,
	CTRY_GERMANY = 276,
	CTRY_GHANA = 288,
	CTRY_GREECE = 300,
	CTRY_GREENLAND = 304,
	CTRY_GRENADA = 308,
	CTRY_GUADELOUPE = 312,
	CTRY_GUAM = 316,
	CTRY_GUATEMALA = 320,
	CTRY_GUYANA = 328,
	CTRY_HAITI = 332,
	CTRY_HONDURAS = 340,
	CTRY_HONG_KONG = 344,
	CTRY_HUNGARY = 348,
	CTRY_ICELAND = 352,
	CTRY_INDIA = 356,
	CTRY_INDONESIA = 360,
	CTRY_IRAN = 364,
	CTRY_IRELAND = 372,
	CTRY_ISRAEL = 376,
	CTRY_ITALY = 380,
	CTRY_JAMAICA = 388,
	CTRY_JORDAN = 400,
	CTRY_KAZAKHSTAN = 398,
	CTRY_KENYA = 404,
	CTRY_KOREA_NORTH = 408,
	CTRY_KOREA_ROC = 410,
	CTRY_KUWAIT = 414,
	CTRY_LATVIA = 428,
	CTRY_LEBANON = 422,
	CTRY_LESOTHO = 426,
	CTRY_LIECHTENSTEIN = 438,
	CTRY_LITHUANIA = 440,
	CTRY_LUXEMBOURG = 442,
	CTRY_MACAU = 446,
	CTRY_MACEDONIA = 807,
	CTRY_MALAWI = 454,
	CTRY_MALAYSIA = 458,
	CTRY_MALDIVES = 462,
	CTRY_MALTA = 470,
	CTRY_MARSHALL_ISLANDS = 584,
	CTRY_MARTINIQUE = 474,
	CTRY_MAURITANIA = 478,
	CTRY_MAURITIUS = 480,
	CTRY_MAYOTTE = 175,
	CTRY_MEXICO = 484,
	CTRY_MICRONESIA = 583,
	CTRY_MOLDOVA = 498,
	CTRY_MONACO = 492,
	CTRY_MONGOLIA = 496,
	CTRY_MONTENEGRO = 499,
	CTRY_MOROCCO = 504,
	CTRY_NAMIBIA = 516,
	CTRY_NEPAL = 524,
	CTRY_NETHERLANDS = 528,
	CTRY_NETHERLANDS_ANTILLES = 530,
	CTRY_NEW_ZEALAND = 554,
	CTRY_NIGERIA = 566,
	CTRY_NORTHERN_MARIANA_ISLANDS = 580,
	CTRY_NICARAGUA = 558,
	CTRY_NORWAY = 578,
	CTRY_OMAN = 512,
	CTRY_PAKISTAN = 586,
	CTRY_PALAU = 585,
	CTRY_PANAMA = 591,
	CTRY_PAPUA_NEW_GUINEA = 598,
	CTRY_PARAGUAY = 600,
	CTRY_PERU = 604,
	CTRY_PHILIPPINES = 608,
	CTRY_POLAND = 616,
	CTRY_PORTUGAL = 620,
	CTRY_PUERTO_RICO = 630,
	CTRY_QATAR = 634,
	CTRY_REUNION = 638,
	CTRY_ROMANIA = 642,
	CTRY_RUSSIA = 643,
	CTRY_RWANDA = 646,
	CTRY_SAINT_BARTHELEMY = 652,
	CTRY_SAINT_KITTS_AND_NEVIS = 659,
	CTRY_SAINT_LUCIA = 662,
	CTRY_SAINT_MARTIN = 663,
	CTRY_SAINT_PIERRE_AND_MIQUELON = 666,
	CTRY_SAINT_VINCENT_AND_THE_GRENADIENS = 670,
	CTRY_SAMOA = 882,
	CTRY_SAUDI_ARABIA = 682,
	CTRY_SENEGAL = 686,
	CTRY_SERBIA = 688,
	CTRY_SINGAPORE = 702,
	CTRY_SLOVAKIA = 703,
	CTRY_SLOVENIA = 705,
	CTRY_SOUTH_AFRICA = 710,
	CTRY_SPAIN = 724,
	CTRY_SURINAME = 740,
	CTRY_SRI_LANKA = 144,
	CTRY_SWEDEN = 752,
	CTRY_SWITZERLAND = 756,
	CTRY_SYRIA = 760,
	CTRY_TAIWAN = 158,
	CTRY_TANZANIA = 834,
	CTRY_THAILAND = 764,
	CTRY_TOGO = 768,
	CTRY_TRINIDAD_Y_TOBAGO = 780,
	CTRY_TUNISIA = 788,
	CTRY_TURKEY = 792,
	CTRY_TURKS_AND_CAICOS = 796,
	CTRY_UGANDA = 800,
	CTRY_UKRAINE = 804,
	CTRY_UAE = 784,
	CTRY_UNITED_KINGDOM = 826,
	CTRY_UNITED_STATES = 840,
	CTRY_UNITED_STATES1 = 841,
	CTRY_UNITED_STATES_PS = 842,
	CTRY_UNITED_STATES2 = 843,
	CTRY_URUGUAY = 858,
	CTRY_UZBEKISTAN = 860,
	CTRY_VANUATU = 548,
	CTRY_VENEZUELA = 862,
	CTRY_VIET_NAM = 704,
	CTRY_VIRGIN_ISLANDS = 850,
	CTRY_WALLIS_AND_FUTUNA = 876,
	CTRY_YEMEN = 887,
	CTRY_ZIMBABWE = 716,
	CTRY_JAPAN7 = 4007,
	CTRY_JAPAN8 = 4008,
	CTRY_JAPAN9 = 4009,
	CTRY_JAPAN10 = 4010,
	CTRY_JAPAN11 = 4011,
	CTRY_JAPAN12 = 4012,
	CTRY_JAPAN13 = 4013,
	CTRY_JAPAN14 = 4014,
	CTRY_JAPAN15 = 4015,
	CTRY_JAPAN25 = 4025,
	CTRY_JAPAN26 = 4026,
	CTRY_JAPAN27 = 4027,
	CTRY_JAPAN28 = 4028,
	CTRY_JAPAN29 = 4029,
	CTRY_JAPAN34 = 4034,
	CTRY_JAPAN35 = 4035,
	CTRY_JAPAN36 = 4036,
	CTRY_JAPAN37 = 4037,
	CTRY_JAPAN38 = 4038,
	CTRY_JAPAN39 = 4039,
	CTRY_JAPAN40 = 4040,
	CTRY_JAPAN41 = 4041,
	CTRY_JAPAN42 = 4042,
	CTRY_JAPAN43 = 4043,
	CTRY_JAPAN44 = 4044,
	CTRY_JAPAN45 = 4045,
	CTRY_JAPAN46 = 4046,
	CTRY_JAPAN47 = 4047,
	CTRY_JAPAN48 = 4048,
	CTRY_JAPAN49 = 4049,
	CTRY_JAPAN55 = 4055,
	CTRY_JAPAN56 = 4056,
	CTRY_XA = 4100,
};

enum reg_domain {
	NULL1_WORLD = 0x03,

	FCC1_FCCA = 0x10,
	FCC1_WORLD = 0x11,
	FCC2_WORLD = 0x21,
	FCC2_ETSIC = 0x22,
	FCC3_FCCA = 0x3A,
	FCC3_WORLD = 0x3B,
	FCC3_ETSIC = 0x3F,
	FCC4_FCCA = 0x12,
	FCC6_WORLD = 0x23,
	FCC6_FCCA = 0x14,
	FCC8_FCCA = 0x16,
	FCC11_WORLD = 0x19,

	ETSI1_WORLD = 0x37,
	ETSI3_WORLD = 0x36,
	ETSI4_WORLD = 0x30,
	ETSI8_WORLD = 0x3D,
	ETSI9_WORLD = 0x3E,

	APL1_WORLD = 0x52,
	APL1_ETSIC = 0x55,
	APL2_WORLD = 0x45,
	APL2_ETSIC = 0x56,
	APL4_WORLD = 0x42,
	APL6_WORLD = 0x5B,
	APL8_WORLD = 0x5D,
	APL9_WORLD = 0x5E,
	APL10_WORLD = 0x5F,
	APL12_WORLD = 0x51,
	APL13_WORLD = 0x5A,
	APL14_WORLD = 0x57,
	APL15_WORLD = 0x59,

	MKK3_MKKA = 0xF0,
	MKK3_MKKB = 0x80,
	MKK3_MKKC = 0x82,
	MKK3_FCCA = 0xF2,
	MKK4_MKKA = 0xF3,
	MKK4_MKKB = 0x83,
	MKK4_MKKC = 0x85,
	MKK4_FCCA = 0xF5,
	MKK5_MKKA = 0x99,
	MKK5_MKKB = 0x86,
	MKK5_MKKC = 0x88,
	MKK5_FCCA = 0x9A,
	MKK9_MKKA = 0xF6,
	MKK9_MKKC = 0xFE,
	MKK9_FCCA = 0xFC,
	MKK10_MKKA = 0xF7,
	MKK10_MKKC = 0xD2,
	MKK10_FCCA = 0xD0,
	MKK11_MKKA = 0xD4,
	MKK11_FCCA = 0xD5,
	MKK11_MKKC = 0xD7,

	WORLD_60 = 0x60,
	WORLD_61 = 0x61,
	WORLD_62 = 0x62,
	WORLD_63 = 0x63,
	WORLD_65 = 0x65,
	WORLD_64 = 0x64,
	WORLD_66 = 0x66,
	WORLD_69 = 0x69,
	WORLD_67 = 0x67,
	WORLD_68 = 0x68,
	WORLD_6A = 0x6A,
	WORLD_6C = 0x6C,
};

const struct country_code_to_reg_domain g_all_countries[] = {
	{CTRY_AFGHANISTAN, ETSI1_WORLD, "AF", "AF" , 40, 160, 0},
	{CTRY_ALBANIA, ETSI1_WORLD, "AL", "AL", 40, 160, 0},
	{CTRY_ALGERIA, APL13_WORLD, "DZ", "DZ", 40, 160, 0},
	{CTRY_AMERICAN_SAMOA, FCC3_FCCA, "AS", "AS", 40, 160, 0},
	{CTRY_ANGUILLA, ETSI1_WORLD, "AI", "AI", 40, 160, 0},
	{CTRY_ARGENTINA, FCC3_WORLD, "AR1", "AR", 40, 160, 0},
	{CTRY_ARGENTINA2, FCC6_WORLD, "AR", "AR", 40, 160, 0},
	{CTRY_ARMENIA, ETSI4_WORLD, "AM", "AM", 40, 20, 0},
	{CTRY_ARUBA, ETSI1_WORLD, "AW", "AW", 40, 160, 0},
	{CTRY_AUSTRALIA, FCC3_WORLD, "AU1", "AU", 40, 160, 0},
	{CTRY_AUSTRALIA2, FCC6_WORLD, "AU", "AU", 40, 160, 0},
	{CTRY_AUSTRIA, ETSI1_WORLD, "AT", "AT", 40, 160, 0},
	{CTRY_AZERBAIJAN, ETSI4_WORLD, "AZ", "AZ", 40, 160, 0},
	{CTRY_BAHAMAS, FCC3_WORLD, "BS", "BS", 40, 160, 0},
	{CTRY_BAHRAIN, APL6_WORLD, "BH", "BH", 40, 20, 0},
	{CTRY_BANGLADESH, APL1_WORLD, "BD", "BD", 40, 160, 0},
	{CTRY_BARBADOS, FCC2_WORLD, "BB", "BB", 40, 160, 0},
	{CTRY_BELARUS, ETSI1_WORLD, "BY", "BY", 40, 160, 0},
	{CTRY_BELGIUM, ETSI1_WORLD, "BE", "BE", 40, 160, 0},
	{CTRY_BELGIUM2, ETSI4_WORLD, "BEL", "BE", 40, 160, 0},
	{CTRY_BELIZE, FCC3_ETSIC, "BZ", "BZ", 40, 160, 0},
	{CTRY_BERMUDA, FCC3_FCCA, "BM", "BM", 40, 160, 0},
	{CTRY_BHUTAN, ETSI1_WORLD, "BT", "BT", 40, 160, 0},
	{CTRY_BOLIVIA, APL8_WORLD, "BO", "BO", 40, 160, 0},
	{CTRY_BOSNIA_HERZ, ETSI1_WORLD, "BA", "BA", 40, 160, 0},
	{CTRY_BRAZIL, FCC3_ETSIC, "BR", "BR", 40, 160, 0},
	{CTRY_BRUNEI_DARUSSALAM, APL6_WORLD, "BN", "BN", 40, 160, 0},
	{CTRY_BULGARIA, ETSI1_WORLD, "BG", "BG", 40, 160, 0},
	{CTRY_BURKINA_FASO, FCC3_WORLD, "BF", "BF", 40, 160, 0},
	{CTRY_CAMBODIA, ETSI1_WORLD, "KH", "KH", 40, 160, 0},
	{CTRY_CANADA, FCC3_FCCA, "CA1", "CA", 40, 160, 0},
	{CTRY_CANADA2, FCC6_FCCA, "CA", "CA", 40, 160, 0},
	{CTRY_CAYMAN_ISLANDS, FCC3_WORLD, "KY", "KY", 40, 160, 0},
	{CTRY_CENTRAL_AFRICA_REPUBLIC, FCC3_WORLD, "CF", "CF", 40, 40, 0},
	{CTRY_CHAD, ETSI1_WORLD, "TD", "TD", 40, 160, 0},
	{CTRY_CHILE, APL6_WORLD, "CL", "CL", 40, 160, 0},
	{CTRY_CHINA, APL14_WORLD, "CN", "CN", 40, 160, 0},
	{CTRY_CHRISTMAS_ISLAND, FCC3_WORLD, "CX", "CX", 40, 160, 0},
	{CTRY_COLOMBIA, FCC3_WORLD, "CO", "CO", 40, 160, 0},
	{CTRY_COSTA_RICA, FCC3_WORLD, "CR", "CR", 40, 20, 0},
	{CTRY_COTE_DIVOIRE, FCC3_WORLD, "CI", "CI", 40, 160, 0},
	{CTRY_CROATIA, ETSI1_WORLD, "HR", "HR", 40, 160, 0},
	{CTRY_CYPRUS, ETSI1_WORLD, "CY", "CY", 40, 160, 0},
	{CTRY_CZECH, ETSI1_WORLD, "CZ", "CZ", 40, 160, 0},
	{CTRY_DENMARK, ETSI1_WORLD, "DK", "DK" , 40, 160,  0},
	{CTRY_DOMINICA, FCC1_FCCA, "DM", "DM", 40, 160, 0},
	{CTRY_DOMINICAN_REPUBLIC, FCC1_FCCA, "DO", "DO", 40, 160, 0},
	{CTRY_ECUADOR, FCC3_WORLD, "EC", "EC", 40, 20, 0},
	{CTRY_EGYPT, ETSI3_WORLD, "EG", "EG", 20, 20, 0},
	{CTRY_EL_SALVADOR, FCC1_WORLD, "SV", "SV", 40, 20, 0},
	{CTRY_ESTONIA, ETSI1_WORLD, "EE", "EE", 40, 160, 0},
	{CTRY_ETHIOPIA, ETSI1_WORLD, "ET", "ET", 40, 160, 0},
	{CTRY_FINLAND, ETSI1_WORLD, "FI", "FI" , 40, 160, 0},
	{CTRY_FRANCE, ETSI1_WORLD, "FR", "FR", 40, 160, 0},
	{CTRY_FRENCH_GUIANA, ETSI1_WORLD, "GF", "GF", 40, 160, 0},
	{CTRY_FRENCH_POLYNESIA, ETSI1_WORLD, "PF", "PF", 40, 160, 0},
	{CTRY_GEORGIA, ETSI4_WORLD, "GE", "GE", 40, 160, 0},
	{CTRY_GERMANY, ETSI1_WORLD, "DE", "DE", 40, 160, 0},
	{CTRY_GHANA, FCC3_WORLD, "GH", "GH", 40, 160, 0},
	{CTRY_GREECE, ETSI1_WORLD, "GR", "GR", 40, 160, 0},
	{CTRY_GREENLAND, ETSI1_WORLD, "GL", "GL", 40, 160, 0},
	{CTRY_GRENADA, FCC3_FCCA, "GD", "GD", 40, 160, 0},
	{CTRY_GUADELOUPE, ETSI1_WORLD, "GP", "GP", 40, 160, 0},
	{CTRY_GUAM, FCC3_FCCA, "GU", "GU", 40, 160, 0},
	{CTRY_GUATEMALA, ETSI1_WORLD, "GT", "GT", 40, 160, 0},
	{CTRY_GUYANA, APL1_ETSIC, "GY", "GY", 40, 160, 0},
	{CTRY_HAITI, FCC3_FCCA, "HT", "HT", 40, 160, 0},
	{CTRY_HONDURAS, FCC3_WORLD, "HN", "HN", 40, 160, 0},
	{CTRY_HONG_KONG, FCC3_WORLD, "HK", "HK", 40, 160, 0},
	{CTRY_HUNGARY, ETSI1_WORLD, "HU", "HU" , 40, 160, 0},
	{CTRY_ICELAND, ETSI1_WORLD, "IS", "IS" , 40, 160, 0},
	{CTRY_INDIA, APL6_WORLD, "IN", "IN", 40, 160, 0},
	{CTRY_INDONESIA, APL2_ETSIC, "ID", "ID", 40, 20, 0},
	{CTRY_IRAN, APL1_WORLD, "IR", "IR", 40, 160, 0},
	{CTRY_IRELAND, ETSI1_WORLD, "IE", "IE", 40, 160, 0},
	{CTRY_ISRAEL, ETSI3_WORLD, "IL", "IL", 40, 160, 0},
	{CTRY_ITALY, ETSI1_WORLD, "IT", "IT", 40, 160,  0},
	{CTRY_JAMAICA, FCC3_WORLD, "JM", "JM", 40, 160, 0},
	{CTRY_JORDAN, APL4_WORLD, "JO", "JO", 40, 160, 0},
	{CTRY_KAZAKHSTAN, NULL1_WORLD, "KZ", "KZ", 40, 0, 0},
	{CTRY_KENYA, APL12_WORLD, "KE", "KE", 40, 160, 0},
	{CTRY_KOREA_NORTH, APL9_WORLD, "KP", "KP", 40, 20, 0},
	{CTRY_KOREA_ROC, APL9_WORLD, "KR", "KR", 40, 160, 0},
	{CTRY_KUWAIT, ETSI3_WORLD, "KW", "KW", 40, 160, 0},
	{CTRY_LATVIA, ETSI1_WORLD, "LV", "LV", 40, 160, 0},
	{CTRY_LEBANON, FCC3_WORLD, "LB", "LB", 40, 160, 0},
	{CTRY_LESOTHO, ETSI1_WORLD, "LS", "LS", 40, 160, 0},
	{CTRY_LIECHTENSTEIN, ETSI1_WORLD, "LI", "LI", 40, 160, 0},
	{CTRY_LITHUANIA, ETSI1_WORLD, "LT", "LT", 40, 160, 0},
	{CTRY_LUXEMBOURG, ETSI1_WORLD, "LU", "LU", 40, 160, 0},
	{CTRY_MACAU, FCC3_WORLD, "MO", "MO", 40, 160, 0},
	{CTRY_MACEDONIA, ETSI1_WORLD, "MK", "MK", 40, 160, 0},
	{CTRY_MALAWI, ETSI1_WORLD, "MW", "MW", 40, 160, 0},
	{CTRY_MALAYSIA, FCC11_WORLD, "MY", "MY", 40, 160, 0},
	{CTRY_MALDIVES, APL6_WORLD, "MV", "MV", 40, 160, 0},
	{CTRY_MALTA, ETSI1_WORLD, "MT", "MT", 40, 160, 0},
	{CTRY_MARSHALL_ISLANDS, FCC3_FCCA, "MH", "MH", 40, 160, 0},
	{CTRY_MARTINIQUE, ETSI1_WORLD, "MQ", "MQ", 40, 160, 0},
	{CTRY_MAURITANIA, ETSI1_WORLD, "MR", "MR", 40, 160, 0},
	{CTRY_MAURITIUS, FCC3_WORLD, "MU", "MU", 40, 160, 0},
	{CTRY_MAYOTTE, ETSI1_WORLD, "YT", "YT", 40, 160, 0},
	{CTRY_MEXICO, FCC3_ETSIC, "MX", "MX", 40, 160, 0},
	{CTRY_MICRONESIA, FCC3_FCCA, "FM", "FM", 40, 160, 0},
	{CTRY_MOLDOVA, ETSI1_WORLD, "MD", "MD", 40, 160, 0},
	{CTRY_MONACO, ETSI1_WORLD, "MC", "MC", 40, 160, 0},
	{CTRY_MONGOLIA, FCC3_WORLD, "MN", "MN", 40, 160, 0},
	{CTRY_MONTENEGRO, ETSI1_WORLD, "ME", "ME", 40, 160, 0},
	{CTRY_MOROCCO, ETSI3_WORLD, "MA", "MA", 40, 160, 0},
	{CTRY_NAMIBIA, APL9_WORLD, "NA", "NA", 40, 160, 0},
	{CTRY_NEPAL, APL6_WORLD, "NP", "NP", 40, 160, 0},
	{CTRY_NETHERLANDS, ETSI1_WORLD, "NL", "NP", 40, 160, 0},
	{CTRY_NETHERLANDS_ANTILLES, ETSI1_WORLD, "AN", "AN", 40, 160, 0},
	{CTRY_NEW_ZEALAND, FCC3_ETSIC, "NZ", "NZ", 40, 160, 0},
	{CTRY_NIGERIA, APL8_WORLD, "NG", "NG", 40, 160, 0},
	{CTRY_NORTHERN_MARIANA_ISLANDS, FCC3_FCCA, "MP", "MP", 40, 160, 0},
	{CTRY_NICARAGUA, FCC3_FCCA, "NI", "NI", 40, 160, 0},
	{CTRY_NORWAY, ETSI1_WORLD, "NO", "NO", 40, 160, 0},
	{CTRY_OMAN, ETSI1_WORLD, "OM", "OM", 40, 160, 0},
	{CTRY_PAKISTAN, APL1_ETSIC, "PK", "PK", 40, 160, 0},
	{CTRY_PALAU, FCC3_FCCA, "PW", "PW", 40, 160, 0},
	{CTRY_PANAMA, FCC1_FCCA, "PA", "PA", 40, 160, 0},
	{CTRY_PAPUA_NEW_GUINEA, FCC3_WORLD, "PG", "PG", 40, 160, 0},
	{CTRY_PARAGUAY, FCC3_WORLD, "PY", "PY", 40, 160, 0},
	{CTRY_PERU, FCC3_WORLD, "PE", "PE", 40, 160, 0},
	{CTRY_PHILIPPINES, FCC3_WORLD, "PH", "PH", 40, 160, 0},
	{CTRY_POLAND, ETSI1_WORLD, "PL", "PL", 40, 160, 0},
	{CTRY_PORTUGAL, ETSI1_WORLD, "PT", "PT", 40, 160, 0},
	{CTRY_PUERTO_RICO, FCC3_FCCA, "PR", "PR", 40, 160, 0},
	{CTRY_QATAR, APL1_WORLD, "QA", "QA" , 40, 160, 0},
	{CTRY_REUNION, ETSI1_WORLD, "RE", "RE", 40, 160, 0},
	{CTRY_ROMANIA, ETSI1_WORLD, "RO", "RO", 40, 160, 0},
	{CTRY_RUSSIA, ETSI8_WORLD, "RU", "RU", 40, 160, 0},
	{CTRY_RWANDA, FCC3_WORLD, "RW", "RW", 40, 160, 0},
	{CTRY_SAINT_BARTHELEMY, ETSI1_WORLD, "BL", "BL", 40, 160, 0},
	{CTRY_SAINT_KITTS_AND_NEVIS, APL10_WORLD, "KN", "KN", 40, 160, 0},
	{CTRY_SAINT_LUCIA, APL10_WORLD, "LC", "LC", 40, 160, 0},
	{CTRY_SAINT_MARTIN, ETSI1_WORLD, "MF", "MF", 40, 160, 0},
	{CTRY_SAINT_PIERRE_AND_MIQUELON, ETSI1_WORLD, "PM", "PM", 40, 160, 0},
	{CTRY_SAINT_VINCENT_AND_THE_GRENADIENS, ETSI1_WORLD, "VC",
	 "VC" , 40, 160, 0},
	{CTRY_SAMOA, ETSI1_WORLD, "WS", "WS", 40, 40, 0},
	{CTRY_SAUDI_ARABIA, ETSI1_WORLD, "SA", "SA", 40, 160, 0},
	{CTRY_SENEGAL, FCC3_WORLD, "SN", "SN", 40, 160, 0},
	{CTRY_SERBIA, ETSI1_WORLD, "RS", "RS", 40, 160, 0},
	{CTRY_SINGAPORE, FCC3_WORLD, "SG", "SG", 40, 160, 0},
	{CTRY_SLOVAKIA, ETSI1_WORLD, "SK", "SK", 40, 160, 0},
	{CTRY_SLOVENIA, ETSI1_WORLD, "SI", "SI", 40, 160, 0},
	{CTRY_SOUTH_AFRICA, FCC3_WORLD, "ZA", "ZA", 40, 160, 0},
	{CTRY_SPAIN, ETSI1_WORLD, "ES", "ES", 40, 160, 0},
	{CTRY_SURINAME, ETSI1_WORLD, "SR", "SR", 40, 160, 0},
	{CTRY_SRI_LANKA, FCC3_WORLD, "LK", "LK", 40, 20, 0},
	{CTRY_SWEDEN, ETSI1_WORLD, "SE", "SE", 40, 160, 0},
	{CTRY_SWITZERLAND, ETSI1_WORLD, "CH", "CH", 40, 160, 0},
	{CTRY_SYRIA, NULL1_WORLD, "SY", "SY", 40, 0, 0},
	{CTRY_TAIWAN, FCC3_FCCA, "TW", "TW", 40, 160, 0},
	{CTRY_TANZANIA, APL1_WORLD, "TZ", "TZ", 40, 160, 0},
	{CTRY_THAILAND, FCC3_WORLD, "TH", "TH", 40, 160, 0},
	{CTRY_TOGO, ETSI1_WORLD, "TG", "TG", 40, 40, 0},
	{CTRY_TRINIDAD_Y_TOBAGO, FCC3_WORLD, "TT", "TT", 40, 160, 0},
	{CTRY_TUNISIA, ETSI3_WORLD, "TN", "TN", 40, 160, 0},
	{CTRY_TURKEY, ETSI1_WORLD, "TR", "TR", 40, 160, 0},
	{CTRY_TURKS_AND_CAICOS, FCC3_WORLD, "TC", "TC", 40, 160, 0},
	{CTRY_UGANDA, FCC3_WORLD, "UG", "UG", 40, 160, 0},
	{CTRY_UKRAINE, ETSI9_WORLD, "UA", "UA", 40, 160, 0},
	{CTRY_UAE, FCC3_WORLD, "AE", "AE", 40, 160, 0},
	{CTRY_UNITED_KINGDOM, ETSI1_WORLD, "GB", "GB", 40, 160, 0},
	{CTRY_UNITED_STATES, FCC3_FCCA, "US", "US", 40, 160, 0},
	{CTRY_UNITED_STATES1, FCC6_FCCA, "US1", "US", 40, 160, 0},
	{CTRY_UNITED_STATES_PS, FCC4_FCCA, "PS", "PS", 40, 160, 0},
	{CTRY_UNITED_STATES2, FCC8_FCCA, "US2", "US", 40, 160, 0},
	{CTRY_URUGUAY, FCC2_WORLD, "UY", "UY", 40, 160, 0},
	{CTRY_UZBEKISTAN, ETSI3_WORLD, "UZ", "UZ", 40, 160, 0},
	{CTRY_VANUATU, FCC3_WORLD, "VU", "VU", 40, 160, 0},
	{CTRY_VENEZUELA, FCC2_ETSIC, "VE", "VE", 40, 160, 0},
	{CTRY_VIET_NAM, FCC3_WORLD, "VN", "VN", 40, 80, 0},
	{CTRY_VIRGIN_ISLANDS, FCC3_FCCA, "VI", "VI", 40, 160, 0},
	{CTRY_WALLIS_AND_FUTUNA, ETSI1_WORLD, "WF", "WF", 40, 160, 0},
	{CTRY_YEMEN, NULL1_WORLD, "YE", "YE", 40, 0, 0},
	{CTRY_ZIMBABWE, ETSI1_WORLD, "ZW", "ZW", 40, 160, 0},
	{CTRY_JAPAN7, MKK3_MKKB, "J7", "JP" , 40, 160, 0},
	{CTRY_JAPAN8, MKK3_MKKA, "J8", "JP" , 40, 160, 0},
	{CTRY_JAPAN9, MKK3_MKKC, "J9", "JP" , 40, 160, 0},
	{CTRY_JAPAN10, MKK4_MKKB, "J10", "JP" , 40, 160, 0},
	{CTRY_JAPAN11, MKK4_MKKA, "J11", "JP" , 40, 160, 0},
	{CTRY_JAPAN12, MKK4_MKKC, "J12", "JP" , 40, 160, 0},
	{CTRY_JAPAN13, MKK5_MKKB, "J13", "JP" , 40, 160, 0},
	{CTRY_JAPAN14, MKK5_MKKA, "JP", "JP" , 40, 160, 0},
	{CTRY_JAPAN15, MKK5_MKKC, "J15", "JP" , 40, 160, 0},
	{CTRY_JAPAN25, MKK3_MKKA, "J25", "JP" , 40, 160, 0},
	{CTRY_JAPAN26, MKK3_MKKA, "J26", "JP" , 40, 160, 0},
	{CTRY_JAPAN27, MKK3_FCCA, "J27", "JP" , 40, 160, 0},
	{CTRY_JAPAN28, MKK4_MKKA, "J28", "JP" , 40, 160, 0},
	{CTRY_JAPAN29, MKK4_FCCA, "J29", "JP" , 40, 160, 0},
	{CTRY_JAPAN34, MKK9_MKKA, "J34", "JP" , 40, 160, 0},
	{CTRY_JAPAN35, MKK10_MKKA, "J35", "JP" , 40, 160, 0},
	{CTRY_JAPAN36, MKK4_MKKA, "J36", "JP" , 40, 160, 0},
	{CTRY_JAPAN37, MKK9_FCCA, "J37", "JP" , 40, 160, 0},
	{CTRY_JAPAN38, MKK9_MKKA, "J38", "JP" , 40, 160, 0},
	{CTRY_JAPAN39, MKK9_MKKC, "J39", "JP" , 40, 160, 0},
	{CTRY_JAPAN40, MKK9_MKKA, "J40", "JP" , 40, 160, 0},
	{CTRY_JAPAN41, MKK10_FCCA, "J41", "JP" , 40, 160, 0},
	{CTRY_JAPAN42, MKK10_MKKA, "J42", "JP" , 40, 160, 0},
	{CTRY_JAPAN43, MKK10_MKKC, "J43", "JP" , 40, 160, 0},
	{CTRY_JAPAN44, MKK10_MKKA, "J44", "JP" , 40, 160, 0},
	{CTRY_JAPAN45, MKK11_MKKA, "J45", "JP" , 40, 160, 0},
	{CTRY_JAPAN46, MKK11_FCCA, "J46", "JP" , 40, 160, 0},
	{CTRY_JAPAN47, MKK11_MKKA, "J47", "JP" , 40, 160, 0},
	{CTRY_JAPAN48, MKK11_MKKC, "J48", "JP" , 40, 160, 0},
	{CTRY_JAPAN49, MKK11_MKKA, "J49", "JP" , 40, 160, 0},
	{CTRY_JAPAN55, MKK5_MKKA, "J55", "JP" , 40, 160, 0},
	{CTRY_JAPAN56, MKK5_FCCA, "J56", "JP" , 40, 160, 0},
	{CTRY_XA, MKK5_MKKA, "XA", "XA", 40, 160, 0},
};

enum reg_domains_2g {
	FCCA,
	WORLD,
	MKKA,
	MKKC,
	ETSIC,
	WORLD_2G_1,
	WORLD_2G_2,
	WORLD_2G_3,
};

enum reg_domains_5g {
	NULL1,
	FCC1,
	FCC2,
	FCC3,
	FCC4,
	FCC6,
	FCC8,
	ETSI1,
	ETSI3,
	ETSI4,
	ETSI8,
	ETSI9,
	APL1,
	APL2,
	APL4,
	APL6,
	APL8,
	APL9,
	APL10,
	APL12,
	APL14,
	MKK3,
	MKK4,
	MKK5,
	MKK9,
	MKK10,
	MKK11,
	WORLD_5G_1,
	WORLD_5G_2,
};


const struct reg_domain_pair g_reg_dmn_pairs[] = {
	{NULL1_WORLD, NULL1, WORLD},

	{FCC1_FCCA, FCC1, FCCA},
	{FCC1_WORLD, FCC1, WORLD},
	{FCC2_WORLD, FCC2, WORLD},
	{FCC2_ETSIC, FCC2, ETSIC},
	{FCC3_FCCA, FCC3, FCCA},
	{FCC3_WORLD, FCC3, WORLD},
	{FCC3_ETSIC, FCC3, ETSIC},
	{FCC4_FCCA, FCC4, FCCA},
	{FCC6_WORLD, FCC6, WORLD},
	{FCC6_FCCA, FCC6, FCCA},
	{FCC8_FCCA, FCC8, FCCA},

	{ETSI1_WORLD, ETSI1, WORLD},
	{ETSI3_WORLD, ETSI3, WORLD},
	{ETSI4_WORLD, ETSI4, WORLD},
	{ETSI8_WORLD, ETSI8, WORLD},
	{ETSI9_WORLD, ETSI9, WORLD},

	{APL1_WORLD, APL1, WORLD},
	{APL1_ETSIC, APL1, ETSIC},
	{APL2_WORLD, APL2, WORLD},
	{APL2_ETSIC, APL2, ETSIC},
	{APL4_WORLD, APL4, WORLD},
	{APL6_WORLD, APL6, WORLD},
	{APL8_WORLD, APL8, WORLD},
	{APL9_WORLD, APL9, WORLD},
	{APL10_WORLD, APL10, WORLD},
	{APL12_WORLD, APL12, WORLD},
	{APL14_WORLD, APL14, WORLD},

	{MKK3_MKKA, MKK3, MKKA},
	{MKK3_MKKC, MKK3, MKKC},
	{MKK3_FCCA, MKK3, FCCA},
	{MKK4_MKKA, MKK4, MKKA},
	{MKK4_MKKC, MKK4, MKKC},
	{MKK4_FCCA, MKK4, FCCA},
	{MKK5_MKKA, MKK5, MKKA},
	{MKK5_MKKC, MKK5, MKKC},
	{MKK5_FCCA, MKK5, FCCA},
	{MKK9_MKKA, MKK9, MKKA},
	{MKK9_MKKC, MKK9, MKKC},
	{MKK9_FCCA, MKK9, FCCA},
	{MKK10_MKKA, MKK10, MKKA},
	{MKK10_MKKC, MKK10, MKKC},
	{MKK10_FCCA, MKK10, FCCA},
	{MKK11_MKKA, MKK11, MKKA},
	{MKK11_FCCA, MKK11, FCCA},
	{MKK11_MKKC, MKK11, MKKC},

	{WORLD_60, WORLD_2G_3, WORLD_5G_2},
	{WORLD_61, WORLD_2G_3, WORLD_5G_2},
	{WORLD_62, WORLD_2G_3, WORLD_5G_2},
	{WORLD_63, WORLD_2G_2, WORLD_5G_1},
	{WORLD_65, WORLD_2G_2, WORLD_5G_1},
	{WORLD_64, WORLD_2G_1, WORLD_5G_1},
	{WORLD_66, WORLD_2G_1, WORLD_5G_2},
	{WORLD_69, WORLD_2G_1, WORLD_5G_2},
	{WORLD_67, WORLD_2G_2, WORLD_5G_2},
	{WORLD_68, WORLD_2G_2, WORLD_5G_2},
	{WORLD_6A, WORLD_2G_2, WORLD_5G_2},
	{WORLD_6C, WORLD_2G_2, WORLD_5G_2},
};

enum reg_rules_2g {

	CHAN_1_11_1,
	CHAN_1_11_2,
	CHAN_1_13_1,
	CHAN_1_13_2,
	CHAN_12_13_1,
	CHAN_14_1,
	CHAN_14_2,
};

const struct regulatory_rule reg_rules_2g[] = {

	[CHAN_1_11_1] = {2402, 2472, 40, 30, 0},
	[CHAN_1_11_2] = {2402, 2472, 40, 20, 0},
	[CHAN_1_13_1] = {2402, 2482, 40, 20, 0},
	[CHAN_1_13_2] = {2402, 2482, 40, 30, 0},
	[CHAN_12_13_1] = {2457, 2482, 40, 30, REGULATORY_CHAN_NO_IR},
	[CHAN_14_1] = {2474, 2494, 20, 20, REGULATORY_CHAN_NO_OFDM},
	[CHAN_14_2] = {2474, 2494, 20, 20,
		       REGULATORY_CHAN_NO_OFDM | REGULATORY_CHAN_NO_IR},
};


const struct regdomain regdomains_2g[] = {

	[FCCA] = {CTL_FCC, DFS_UNINIT_REG, 0, 1, {CHAN_1_11_1} },
	[WORLD] = {CTL_ETSI, DFS_UNINIT_REG, 0, 1, {CHAN_1_13_1} },
	[MKKA] = {CTL_MKK, DFS_UNINIT_REG, 0, 2, {CHAN_1_13_1, CHAN_14_1} },
	[MKKC] = {CTL_MKK, DFS_UNINIT_REG, 0, 1, {CHAN_1_13_1} },
	[ETSIC] = {CTL_ETSI, DFS_UNINIT_REG, 0, 1, {CHAN_1_13_2} },
	[WORLD_2G_1] = {CTL_FCC, DFS_UNINIT_REG, 0, 1, {CHAN_1_11_2} },
	[WORLD_2G_2] = {CTL_FCC, DFS_UNINIT_REG, 0, 2,
			{CHAN_1_11_2, CHAN_12_13_1} },
	[WORLD_2G_3] = {CTL_FCC, DFS_UNINIT_REG, 0, 3,
			{CHAN_1_11_2, CHAN_12_13_1, CHAN_14_2} },
};


enum reg_rules_5g {

	CHAN_4910_4990_1,
	CHAN_4940_4990_1,
	CHAN_5030_5090_1,
	CHAN_5170_5250_1,
	CHAN_5170_5250_2,
	CHAN_5170_5250_3,
	CHAN_5170_5250_4,
	CHAN_5170_5330_1,
	CHAN_5250_5330_1,
	CHAN_5250_5330_2,
	CHAN_5250_5330_3,
	CHAN_5250_5330_4,
	CHAN_5490_5730_1,
	CHAN_5490_5730_2,
	CHAN_5490_5730_3,
	CHAN_5490_5710_1,
	CHAN_5490_5710_2,
	CHAN_5490_5590_1,
	CHAN_5490_5570_1,
	CHAN_5490_5670_1,
	CHAN_5490_5630_1,
	CHAN_5650_5730_1,
	CHAN_5735_5835_1,
	CHAN_5735_5835_2,
	CHAN_5735_5835_3,
	CHAN_5735_5835_4,
	CHAN_5735_5835_5,
	CHAN_5735_5815_1,
	CHAN_5735_5775_1,
};

const struct regulatory_rule reg_rules_5g[] = {

	[CHAN_4910_4990_1] = {4910, 4990, 20, 20, 0},
	[CHAN_4940_4990_1] = {4940, 4990, 20, 33, 0},
	[CHAN_5030_5090_1] = {5030, 5090, 20, 20, 0},
	[CHAN_5170_5250_1] = {5170, 5250, 80, 17, 0},
	[CHAN_5170_5250_2] = {5170, 5250, 80, 23, 0},
	[CHAN_5170_5250_3] = {5170, 5250, 80, 20, 0},
	[CHAN_5170_5250_4] = {5170, 5250, 80, 30, 0},
	[CHAN_5170_5330_1] = {5170, 5330, 160, 20, REGULATORY_CHAN_NO_IR},
	[CHAN_5250_5330_1] = {5250, 5330, 80, 23, REGULATORY_CHAN_RADAR},
	[CHAN_5250_5330_2] = {5250, 5330, 80, 20, REGULATORY_CHAN_RADAR},
	[CHAN_5250_5330_3] = {5250, 5330, 80, 17, REGULATORY_CHAN_RADAR},
	[CHAN_5250_5330_4] = {5250, 5330, 80, 30, REGULATORY_CHAN_RADAR},
	[CHAN_5490_5730_1] = {5490, 5730, 160, 23, REGULATORY_CHAN_RADAR},
	[CHAN_5490_5730_2] = {5490, 5730, 160, 30, REGULATORY_CHAN_RADAR},
	[CHAN_5490_5730_3] = {5490, 5730, 160, 20, REGULATORY_CHAN_NO_IR},
	[CHAN_5490_5710_1] = {5490, 5710, 160, 30, REGULATORY_CHAN_RADAR},
	[CHAN_5490_5710_2] = {5490, 5710, 160, 20, REGULATORY_CHAN_RADAR},
	[CHAN_5490_5590_1] = {5490, 5590, 80, 23, REGULATORY_CHAN_RADAR},
	[CHAN_5490_5570_1] = {5490, 5570, 80, 30, REGULATORY_CHAN_RADAR},
	[CHAN_5490_5670_1] = {5490, 5670, 160, 20, REGULATORY_CHAN_RADAR},
	[CHAN_5490_5630_1] = {5490, 5630, 80, 30, REGULATORY_CHAN_RADAR},
	[CHAN_5650_5730_1] = {5650, 5730, 80, 23, REGULATORY_CHAN_RADAR},
	[CHAN_5735_5835_1] = {5735, 5835, 80, 23, 0},
	[CHAN_5735_5835_2] = {5735, 5835, 80, 30, 0},
	[CHAN_5735_5835_3] = {5735, 5835, 80, 20, 0},
	[CHAN_5735_5835_4] = {5735, 5835, 80, 27, 0},
	[CHAN_5735_5835_5] = {5735, 5835, 80, 20, REGULATORY_CHAN_NO_IR},
	[CHAN_5735_5815_1] = {5735, 5815, 80, 30, 0},
	[CHAN_5735_5775_1] = {5735, 5775, 40, 23, 0},
};


const struct regdomain regdomains_5g[] = {

	[FCC1] = {CTL_FCC, DFS_FCC_REG, 2, 3, {CHAN_5170_5250_1,
					      CHAN_5250_5330_1,
					      CHAN_5735_5835_1} },

	[FCC2] = {CTL_FCC, DFS_CN_REG, 2, 3, {CHAN_5170_5250_2,
					     CHAN_5250_5330_1,
					     CHAN_5735_5835_1} },

	[FCC3] = {CTL_FCC, DFS_FCC_REG, 2, 4, {CHAN_5170_5250_2,
					      CHAN_5250_5330_1,
					      CHAN_5490_5730_1,
					      CHAN_5735_5835_1} },

	[FCC4] = {CTL_FCC, DFS_FCC_REG, 2, 4, {CHAN_4940_4990_1,
					      CHAN_5170_5250_1,
					      CHAN_5250_5330_1,
					      CHAN_5735_5835_1} },

	[FCC6] = {CTL_FCC, DFS_FCC_REG, 2, 5, {CHAN_5170_5250_2,
					      CHAN_5250_5330_1,
					      CHAN_5490_5590_1,
					      CHAN_5650_5730_1,
					      CHAN_5735_5835_1} },

	[FCC8] = {CTL_FCC, DFS_FCC_REG, 2, 4, {CHAN_5170_5250_4,
					      CHAN_5250_5330_1,
					      CHAN_5490_5730_1,
					      CHAN_5735_5835_1} },

	[ETSI1] = {CTL_ETSI, DFS_ETSI_REG, 5, 3, {CHAN_5170_5250_2,
						 CHAN_5250_5330_1,
						 CHAN_5490_5710_1} },

	[ETSI3] = {CTL_ETSI, DFS_ETSI_REG, 5, 2, {CHAN_5170_5250_3,
						 CHAN_5250_5330_2} },

	[ETSI4] = {CTL_ETSI, DFS_ETSI_REG, 5, 2, {CHAN_5170_5250_1,
						 CHAN_5250_5330_3} },

	[ETSI8] = {CTL_ETSI, DFS_ETSI_REG, 20, 4, {CHAN_5170_5250_3,
						  CHAN_5250_5330_2,
						  CHAN_5490_5730_2,
						  CHAN_5735_5835_2} },

	[ETSI9] = {CTL_ETSI, DFS_ETSI_REG, 20, 4, {CHAN_5170_5250_3,
						  CHAN_5250_5330_2,
						  CHAN_5490_5670_1,
						  CHAN_5735_5835_3} },

	[APL1] = {CTL_ETSI, DFS_UNINIT_REG, 2, 1, {CHAN_5735_5835_2} },

	[APL2] = {CTL_ETSI, DFS_UNINIT_REG, 2, 1, {CHAN_5735_5815_1} },

	[APL4] = {CTL_ETSI, DFS_UNINIT_REG, 2, 2, {CHAN_5170_5250_2,
						  CHAN_5735_5835_1} },

	[APL6] = {CTL_ETSI, DFS_ETSI_REG, 2, 3, {CHAN_5170_5250_3,
						CHAN_5250_5330_2,
						CHAN_5735_5835_3} },

	[APL8] = {CTL_ETSI, DFS_ETSI_REG, 2, 2, {CHAN_5250_5330_4,
						CHAN_5735_5835_2} },

	[APL9] = {CTL_ETSI, DFS_KR_REG, 2, 4, {CHAN_5170_5250_3,
					      CHAN_5250_5330_2,
					      CHAN_5490_5630_1,
					      CHAN_5735_5815_1} },

	[APL10] = {CTL_ETSI, DFS_ETSI_REG, 2, 4, {CHAN_5170_5250_3,
						 CHAN_5250_5330_2,
						 CHAN_5490_5710_1,
						 CHAN_5735_5815_1} },

	[APL12] = {CTL_ETSI, DFS_ETSI_REG, 2, 3, {CHAN_5170_5250_1,
						 CHAN_5490_5570_1,
						 CHAN_5735_5775_1} },

	[APL14] = {CTL_FCC, DFS_CN_REG, 2, 3, {CHAN_5170_5250_2,
					      CHAN_5250_5330_1,
					      CHAN_5735_5835_4} },

	[MKK3] = {CTL_MKK, DFS_UNINIT_REG, 2, 1, {CHAN_5170_5250_3} },

	[MKK4] = {CTL_MKK, DFS_MKK_REG, 2, 2, {CHAN_5170_5250_3,
					      CHAN_5250_5330_2} },

	[MKK5] = {CTL_MKK, DFS_MKK_REG, 2, 3, {CHAN_5170_5250_3,
					      CHAN_5250_5330_2,
					      CHAN_5490_5710_2} },

	[MKK9] = {CTL_MKK, DFS_UNINIT_REG, 2, 3, {CHAN_5170_5250_3,
						 CHAN_4910_4990_1,
						 CHAN_5030_5090_1} },

	[MKK10] = {CTL_MKK, DFS_MKK_REG, 2, 4, {CHAN_5170_5250_3,
					       CHAN_5250_5330_2,
					       CHAN_4910_4990_1,
					       CHAN_5030_5090_1} },

	[MKK11] = {CTL_MKK, DFS_MKK_REG, 2, 5, {CHAN_5170_5250_3,
					       CHAN_5250_5330_2,
					       CHAN_5490_5710_2,
					       CHAN_4910_4990_1,
					       CHAN_5030_5090_1} },

	[WORLD_5G_1] = {CTL_FCC, DFS_UNINIT_REG, 2, 2, {CHAN_5170_5330_1,
						       CHAN_5735_5835_5} },

	[WORLD_5G_2] = {CTL_FCC, DFS_UNINIT_REG, 2, 3, {CHAN_5170_5330_1,
						       CHAN_5490_5730_3,
						       CHAN_5735_5835_5} },
};

QDF_STATUS get_num_countries(int *num_countries)
{
	*num_countries = QDF_ARRAY_SIZE(g_all_countries);

	return QDF_STATUS_SUCCESS;
}

QDF_STATUS get_num_reg_dmn_pairs(int *num_reg_dmn)
{
	*num_reg_dmn = QDF_ARRAY_SIZE(g_reg_dmn_pairs);

	return QDF_STATUS_SUCCESS;
}

QDF_STATUS get_default_country(uint16_t *default_country)
{
	*default_country = CTRY_UNITED_STATES;

	return QDF_STATUS_SUCCESS;
}
