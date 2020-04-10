#include "tiledexport.h"

const sf::IntRect TiledTiles::tileToTextureRect[] = {
	{},	//NONE
	{ 9 * 16, 2 * 16, 16, 16 }, //=1, BG_1, gid=67
	{ 10 * 16, 2 * 16, 16, 16 }, //=2, BG_2, gid=68
	{ 11 * 16, 2 * 16, 16, 16 }, //=3, BG_3, gid=69
	{ 21 * 16, 2 * 16, 16, 16 }, //=4, BG_4, gid=79
	{ 22 * 16, 2 * 16, 16, 16 }, //=5, BG_5, gid=80
	{ 23 * 16, 2 * 16, 16, 16 }, //=6, BG_6, gid=81
	{ 24 * 16, 2 * 16, 16, 16 }, //=7, BG_7, gid=82
	{ 14 * 16, 3 * 16, 16, 16 }, //=8, BG_8, gid=101
	{ 15 * 16, 3 * 16, 16, 16 }, //=9, BG_9, gid=102
	{ 16 * 16, 3 * 16, 16, 16 }, //=10, BG_10, gid=103
	{ 18 * 16, 3 * 16, 16, 16 }, //=11, BG_11, gid=105
	{ 21 * 16, 3 * 16, 16, 16 }, //=12, BG_12, gid=108
	{ 22 * 16, 3 * 16, 16, 16 }, //=13, BG_13, gid=109
	{ 23 * 16, 3 * 16, 16, 16 }, //=14, BG_14, gid=110
	{ 24 * 16, 3 * 16, 16, 16 }, //=15, BG_15, gid=111
	{ 8 * 16, 4 * 16, 16, 16 }, //=16, BG_16, gid=124
	{ 9 * 16, 4 * 16, 16, 16 }, //=17, BG_17, gid=125
	{ 11 * 16, 4 * 16, 16, 16 }, //=18, BG_18, gid=127
	{ 12 * 16, 4 * 16, 16, 16 }, //=19, BG_19, gid=128
	{ 21 * 16, 4 * 16, 16, 16 }, //=20, BG_20, gid=137
	{ 22 * 16, 4 * 16, 16, 16 }, //=21, BG_21, gid=138
	{ 23 * 16, 4 * 16, 16, 16 }, //=22, BG_22, gid=139
	{ 26 * 16, 4 * 16, 16, 16 }, //=23, BG_23, gid=142
	{ 27 * 16, 4 * 16, 16, 16 }, //=24, BG_24, gid=143
	{ 8 * 16, 5 * 16, 16, 16 }, //=25, BG_25, gid=153
	{ 9 * 16, 5 * 16, 16, 16 }, //=26, BG_26, gid=154
	{ 10 * 16, 5 * 16, 16, 16 }, //=27, BG_27, gid=155
	{ 11 * 16, 5 * 16, 16, 16 }, //=28, BG_28, gid=156
	{ 12 * 16, 5 * 16, 16, 16 }, //=29, BG_29, gid=157
	{ 20 * 16, 5 * 16, 16, 16 }, //=30, BG_30, gid=165
	{ 21 * 16, 5 * 16, 16, 16 }, //=31, BG_31, gid=166
	{ 6 * 16, 6 * 16, 16, 16 }, //=32, BG_32, gid=180
	{ 8 * 16, 6 * 16, 16, 16 }, //=33, BG_33, gid=182
	{ 9 * 16, 6 * 16, 16, 16 }, //=34, BG_34, gid=183
	{ 10 * 16, 6 * 16, 16, 16 }, //=35, BG_35, gid=184
	{ 11 * 16, 6 * 16, 16, 16 }, //=36, BG_36, gid=185
	{ 17 * 16, 6 * 16, 16, 16 }, //=37, BG_37, gid=191
	{ 18 * 16, 6 * 16, 16, 16 }, //=38, BG_38, gid=192
	{ 20 * 16, 6 * 16, 16, 16 }, //=39, BG_39, gid=194
	{ 21 * 16, 6 * 16, 16, 16 }, //=40, BG_40, gid=195
	{ 22 * 16, 6 * 16, 16, 16 }, //=41, BG_41, gid=196
	{ 6 * 16, 7 * 16, 16, 16 }, //=42, BG_42, gid=209
	{ 16 * 16, 7 * 16, 16, 16 }, //=43, BG_43, gid=219
	{ 17 * 16, 7 * 16, 16, 16 }, //=44, BG_44, gid=220
	{ 20 * 16, 7 * 16, 16, 16 }, //=45, BG_45, gid=223
	{ 21 * 16, 7 * 16, 16, 16 }, //=46, BG_46, gid=224
	{ 22 * 16, 7 * 16, 16, 16 }, //=47, BG_47, gid=225
	{ 28 * 16, 7 * 16, 16, 16 }, //=48, BG_48, gid=231
	{ 17 * 16, 8 * 16, 16, 16 }, //=49, BG_49, gid=249
	{ 18 * 16, 8 * 16, 16, 16 }, //=50, BG_50, gid=250
	{ 1 * 16, 9 * 16, 16, 16 }, //=51, BG_51, gid=262
	{ 11 * 16, 9 * 16, 16, 16 }, //=52, BG_52, gid=272
	{ 12 * 16, 9 * 16, 16, 16 }, //=53, BG_53, gid=273
	{ 13 * 16, 9 * 16, 16, 16 }, //=54, BG_54, gid=274
	{ 17 * 16, 9 * 16, 16, 16 }, //=55, BG_55, gid=278
	{ 18 * 16, 9 * 16, 16, 16 }, //=56, BG_56, gid=279
	{ 19 * 16, 9 * 16, 16, 16 }, //=57, BG_57, gid=280
	{ 20 * 16, 9 * 16, 16, 16 }, //=58, BG_58, gid=281
	{ 12 * 16, 10 * 16, 16, 16 }, //=59, BG_59, gid=302
	{ 14 * 16, 10 * 16, 16, 16 }, //=60, BG_60, gid=304
	{ 16 * 16, 10 * 16, 16, 16 }, //=61, BG_61, gid=306
	{ 16 * 16, 11 * 16, 16, 16 }, //=62, BG_62, gid=335
	{ 18 * 16, 11 * 16, 16, 16 }, //=63, BG_63, gid=337
	{ 19 * 16, 11 * 16, 16, 16 }, //=64, BG_64, gid=338
	{ 21 * 16, 11 * 16, 16, 16 }, //=65, BG_65, gid=340
	{ 22 * 16, 11 * 16, 16, 16 }, //=66, BG_66, gid=341
	{ 23 * 16, 11 * 16, 16, 16 }, //=67, BG_67, gid=342
	{ 24 * 16, 11 * 16, 16, 16 }, //=68, BG_68, gid=343
	{ 25 * 16, 11 * 16, 16, 16 }, //=69, BG_69, gid=344
	{ 4 * 16, 12 * 16, 16, 16 }, //=70, BG_70, gid=352
	{ 5 * 16, 12 * 16, 16, 16 }, //=71, BG_71, gid=353
	{ 10 * 16, 12 * 16, 16, 16 }, //=72, BG_72, gid=358
	{ 11 * 16, 12 * 16, 16, 16 }, //=73, BG_73, gid=359
	{ 12 * 16, 12 * 16, 16, 16 }, //=74, BG_74, gid=360
	{ 13 * 16, 12 * 16, 16, 16 }, //=75, BG_75, gid=361
	{ 15 * 16, 12 * 16, 16, 16 }, //=76, BG_76, gid=363
	{ 18 * 16, 12 * 16, 16, 16 }, //=77, BG_77, gid=366
	{ 19 * 16, 12 * 16, 16, 16 }, //=78, BG_78, gid=367
	{ 4 * 16, 13 * 16, 16, 16 }, //=79, BG_79, gid=381
	{ 5 * 16, 13 * 16, 16, 16 }, //=80, BG_80, gid=382
	{ 10 * 16, 13 * 16, 16, 16 }, //=81, BG_81, gid=387
	{ 11 * 16, 13 * 16, 16, 16 }, //=82, BG_82, gid=388
	{ 12 * 16, 13 * 16, 16, 16 }, //=83, BG_83, gid=389
	{ 13 * 16, 13 * 16, 16, 16 }, //=84, BG_84, gid=390
	{ 14 * 16, 13 * 16, 16, 16 }, //=85, BG_85, gid=391
	{ 15 * 16, 13 * 16, 16, 16 }, //=86, BG_86, gid=392
	{ 18 * 16, 13 * 16, 16, 16 }, //=87, BG_87, gid=395
	{ 19 * 16, 13 * 16, 16, 16 }, //=88, BG_88, gid=396
	{ 10 * 16, 14 * 16, 16, 16 }, //=89, BG_89, gid=416
	{ 11 * 16, 14 * 16, 16, 16 }, //=90, BG_90, gid=417
	{ 12 * 16, 14 * 16, 16, 16 }, //=91, BG_91, gid=418
	{ 13 * 16, 14 * 16, 16, 16 }, //=92, BG_92, gid=419
	{ 18 * 16, 14 * 16, 16, 16 }, //=93, BG_93, gid=424
	{ 19 * 16, 14 * 16, 16, 16 }, //=94, BG_94, gid=425
	{ 18 * 16, 15 * 16, 16, 16 }, //=95, BG_95, gid=453
	{ 19 * 16, 15 * 16, 16, 16 }, //=96, BG_96, gid=454
	{ 24 * 16, 15 * 16, 16, 16 }, //=97, BG_97, gid=459
	{ 25 * 16, 15 * 16, 16, 16 }, //=98, BG_98, gid=460
	{ 28 * 16, 2 * 16, 16, 16 }, //=99, ONE_WAY_1, gid=86
	{ 19 * 16, 3 * 16, 16, 16 }, //=100, ONE_WAY_2, gid=106
	{ 20 * 16, 3 * 16, 16, 16 }, //=101, ONE_WAY_3, gid=107
	{ 28 * 16, 3 * 16, 16, 16 }, //=102, ONE_WAY_4, gid=115
	{ 16 * 16, 4 * 16, 16, 16 }, //=103, ONE_WAY_5, gid=132
	{ 17 * 16, 4 * 16, 16, 16 }, //=104, ONE_WAY_6, gid=133
	{ 18 * 16, 4 * 16, 16, 16 }, //=105, ONE_WAY_7, gid=134
	{ 20 * 16, 4 * 16, 16, 16 }, //=106, ONE_WAY_8, gid=136
	{ 28 * 16, 4 * 16, 16, 16 }, //=107, ONE_WAY_9, gid=144
	{ 25 * 16, 6 * 16, 16, 16 }, //=108, ONE_WAY_10, gid=199
	{ 27 * 16, 11 * 16, 16, 16 }, //=109, ONE_WAY_11, gid=346
	{ 21 * 16, 12 * 16, 16, 16 }, //=110, ONE_WAY_12, gid=369
	{ 22 * 16, 12 * 16, 16, 16 }, //=111, ONE_WAY_13, gid=370
	{ 24 * 16, 12 * 16, 16, 16 }, //=112, ONE_WAY_14, gid=372
	{ 27 * 16, 12 * 16, 16, 16 }, //=113, ONE_WAY_15, gid=375
	{ 28 * 16, 12 * 16, 16, 16 }, //=114, ONE_WAY_16, gid=376
	{ 10 * 16, 1 * 16, 16, 16 }, //=115, RIGHT_SLOPE_1, gid=39
	{ 13 * 16, 1 * 16, 16, 16 }, //=116, RIGHT_SLOPE_2, gid=42
	{ 23 * 16, 7 * 16, 16, 16 }, //=117, RIGHT_SLOPE_3, gid=226
	{ 22 * 16, 8 * 16, 16, 16 }, //=118, RIGHT_SLOPE_4, gid=254
	{ 11 * 16, 1 * 16, 16, 16 }, //=119, LEFT_SLOPE_1, gid=40
	{ 12 * 16, 1 * 16, 16, 16 }, //=120, LEFT_SLOPE_2, gid=41
	{ 27 * 16, 7 * 16, 16, 16 }, //=121, LEFT_SLOPE_3, gid=230
	{ 28 * 16, 8 * 16, 16, 16 }, //=122, LEFT_SLOPE_4, gid=260
	{ 12 * 16, 2 * 16, 16, 16 }, //=123, SOLID_1, gid=70
	{ 13 * 16, 2 * 16, 16, 16 }, //=124, SOLID_2, gid=71
	{ 14 * 16, 2 * 16, 16, 16 }, //=125, SOLID_3, gid=72
	{ 15 * 16, 2 * 16, 16, 16 }, //=126, SOLID_4, gid=73
	{ 16 * 16, 2 * 16, 16, 16 }, //=127, SOLID_5, gid=74
	{ 17 * 16, 2 * 16, 16, 16 }, //=128, SOLID_6, gid=75
	{ 18 * 16, 2 * 16, 16, 16 }, //=129, SOLID_7, gid=76
	{ 19 * 16, 2 * 16, 16, 16 }, //=130, SOLID_8, gid=77
	{ 20 * 16, 2 * 16, 16, 16 }, //=131, SOLID_9, gid=78
	{ 8 * 16, 3 * 16, 16, 16 }, //=132, SOLID_10, gid=95
	{ 9 * 16, 3 * 16, 16, 16 }, //=133, SOLID_11, gid=96
	{ 10 * 16, 3 * 16, 16, 16 }, //=134, SOLID_12, gid=97
	{ 11 * 16, 3 * 16, 16, 16 }, //=135, SOLID_13, gid=98
	{ 12 * 16, 3 * 16, 16, 16 }, //=136, SOLID_14, gid=99
	{ 13 * 16, 3 * 16, 16, 16 }, //=137, SOLID_15, gid=100
	{ 8 * 16, 7 * 16, 16, 16 }, //=138, SOLID_16, gid=211
	{ 9 * 16, 7 * 16, 16, 16 }, //=139, SOLID_17, gid=212
	{ 10 * 16, 7 * 16, 16, 16 }, //=140, SOLID_18, gid=213
	{ 24 * 16, 7 * 16, 16, 16 }, //=141, SOLID_19, gid=227
	{ 25 * 16, 7 * 16, 16, 16 }, //=142, SOLID_20, gid=228
	{ 26 * 16, 7 * 16, 16, 16 }, //=143, SOLID_21, gid=229
	{ 23 * 16, 8 * 16, 16, 16 }, //=144, SOLID_22, gid=255
	{ 27 * 16, 8 * 16, 16, 16 }, //=145, SOLID_23, gid=259
	{ 8 * 16, 9 * 16, 16, 16 }, //=146, SOLID_24, gid=269
	{ 9 * 16, 9 * 16, 16, 16 }, //=147, SOLID_25, gid=270
	{ 22 * 16, 9 * 16, 16, 16 }, //=148, SOLID_26, gid=283
	{ 28 * 16, 9 * 16, 16, 16 }, //=149, SOLID_27, gid=289
	{ 28 * 16, 10 * 16, 16, 16 }, //=150, SOLID_28, gid=318
	{ 24 * 16, 13 * 16, 16, 16 }, //=151, SOLID_29, gid=401
	{ 25 * 16, 13 * 16, 16, 16 }, //=152, SOLID_30, gid=402
	{ 24 * 16, 14 * 16, 16, 16 }, //=153, SOLID_31, gid=430
	{ 25 * 16, 14 * 16, 16, 16 }, //=154, SOLID_32, gid=431
	{ 1 * 16, 0 * 16, 16, 16 }, //=155, BREAKABLE_1, gid=1
	{ 1 * 16, 1 * 16, 16, 16 }, //=156, BREAKABLE_2, gid=30
	{ 24 * 16, 1 * 16, 16, 16 }, //=157, BREAKABLE_3, gid=53
	{},	//SOLID_TRANSPARENT
};

const sf::Vector2f TiledMap::map_size = sf::Vector2f(160, 64);

const unsigned short TiledMap::map[] = {
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,131,131,131,131,131,131,131,131,131,131,131,131,131,131,131,131,131,131,131,131,131,131,131,131,131,131,131,131,131,131,131,131,131,131,131,131,131,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,131,0,0,0,0,0,0,
	0,0,0,0,0,0,155,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,131,0,0,0,0,0,0,
	0,0,0,0,0,0,156,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,131,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,16,17,17,17,0,16,17,17,18,0,16,17,17,18,0,16,17,17,0,25,0,16,17,17,17,0,16,34,34,34,0,0,0,131,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,25,0,0,0,0,25,0,0,25,0,25,0,0,25,0,25,0,0,0,25,0,25,0,0,0,0,25,0,0,0,0,0,0,131,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,25,0,0,0,0,25,0,0,25,0,25,0,0,25,0,25,0,0,0,25,0,26,17,17,0,0,33,34,34,18,0,0,0,131,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,25,0,17,18,0,26,17,27,35,0,26,17,17,28,0,25,0,0,0,25,0,25,0,0,0,0,0,0,0,25,0,0,0,131,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,25,0,0,25,0,25,0,33,18,0,25,0,0,25,0,25,0,0,0,25,0,25,0,0,0,0,0,0,0,25,0,0,0,131,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,131,131,131,131,131,131,131,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,33,17,17,35,0,25,0,0,25,0,25,0,0,25,0,33,17,17,0,25,0,33,17,17,17,0,16,17,17,35,0,0,0,131,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,131,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,25,0,0,0,0,0,0,131,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,131,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,25,0,0,0,0,0,0,131,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,131,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,103,104,104,104,105,0,0,0,0,0,0,0,0,0,0,25,0,0,0,0,0,0,131,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,131,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,47,117,141,141,142,141,142,143,141,142,143,121,48,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,103,104,105,0,0,0,0,0,0,0,0,0,0,0,0,0,0,103,104,105,0,0,0,25,0,0,0,0,0,0,131,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,131,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,118,144,0,0,0,0,0,0,0,0,0,145,122,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,25,0,0,0,0,0,0,131,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,131,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,148,0,0,0,0,0,0,0,0,0,0,0,149,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,25,0,0,0,0,0,0,131,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,131,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,148,0,0,0,0,0,0,0,0,0,0,0,150,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,103,104,105,0,0,0,0,103,104,105,0,0,0,0,0,0,0,0,25,0,0,0,0,0,0,131,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,131,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,148,0,0,103,104,105,0,0,0,0,19,0,150,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,25,0,0,0,0,0,0,131,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,131,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,148,0,0,0,0,0,0,0,0,16,29,18,150,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,25,0,0,0,0,0,0,131,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,131,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,148,0,55,56,0,0,0,0,16,35,36,36,150,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,36,0,0,0,0,0,0,131,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,131,125,125,125,125,126,0,0,0,0,123,124,124,124,124,124,124,124,124,124,124,124,124,124,126,113,113,114,113,113,109,113,124,124,124,124,124,124,124,124,124,124,124,124,124,124,124,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,131,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,131,0,0,0,0,128,129,129,129,129,129,129,129,129,129,129,129,129,129,130,0,0,0,0,0,25,0,128,129,129,129,129,129,129,129,129,129,129,129,129,129,129,130,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,131,0,0,0,0,128,129,129,157,129,129,129,129,129,129,129,129,129,131,130,18,0,0,0,0,25,0,128,129,128,129,129,129,129,129,129,129,129,129,128,129,129,130,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,131,0,0,0,0,128,129,129,129,129,129,157,157,129,129,129,129,129,129,130,33,27,17,17,27,35,0,128,129,129,129,157,129,131,129,129,129,157,129,129,129,129,130,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,131,0,0,0,0,128,129,129,129,129,129,129,129,129,129,129,157,129,129,130,0,33,18,0,25,0,0,128,129,129,157,129,129,129,129,129,129,129,129,129,129,129,130,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,131,0,0,0,0,128,129,129,129,129,129,129,129,129,129,129,129,129,129,130,0,0,25,0,33,17,17,128,129,129,129,129,129,129,129,129,129,129,129,157,129,129,130,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,131,0,0,0,0,128,129,129,129,129,129,129,129,129,129,129,129,131,129,130,0,16,28,0,0,0,0,157,129,129,129,129,129,129,157,129,129,129,129,129,129,129,130,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,131,0,0,0,0,128,129,129,157,129,129,128,129,129,129,129,129,129,129,130,17,35,26,18,0,0,0,157,129,129,129,129,129,129,129,129,129,129,130,129,128,129,130,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,131,0,0,0,0,128,129,129,129,129,129,129,129,129,157,129,129,129,129,130,0,0,25,25,0,0,0,157,129,129,129,129,129,129,129,129,157,129,129,128,129,129,130,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,131,0,0,0,0,128,129,129,129,129,129,131,129,129,129,129,129,129,157,130,0,0,25,33,18,0,0,128,129,129,157,129,129,129,129,129,129,129,129,129,129,129,130,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,131,0,0,0,0,128,129,157,129,129,128,129,129,129,129,129,129,129,129,130,0,0,25,0,33,17,17,128,129,129,129,129,129,130,129,129,129,129,129,129,129,129,130,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,131,0,0,0,0,128,129,129,129,129,129,129,129,129,129,129,129,129,129,130,0,0,25,0,0,0,0,128,129,128,129,129,129,129,129,129,129,129,157,157,129,129,130,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,131,0,0,0,0,128,129,129,129,129,129,129,129,157,129,129,129,157,129,130,0,0,26,34,18,0,0,128,129,129,129,129,129,129,129,129,129,129,129,129,129,129,130,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,131,0,0,0,0,128,129,131,129,129,129,129,129,129,129,129,129,157,129,130,17,18,25,0,33,18,0,128,129,129,129,157,129,129,129,129,129,129,129,129,129,129,130,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,131,0,0,0,0,128,129,129,129,129,157,129,129,129,129,129,129,129,129,130,0,33,35,0,0,25,0,128,129,129,157,129,129,129,129,129,129,157,129,129,129,129,130,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,131,0,0,0,0,128,129,129,129,157,129,129,129,128,131,129,129,129,129,130,0,0,0,0,0,26,17,128,129,129,129,129,128,129,129,129,129,129,129,129,129,129,130,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,131,0,0,0,0,128,129,129,129,129,129,129,129,129,129,129,129,129,131,130,0,0,0,0,0,25,0,128,129,129,129,129,129,129,129,129,128,129,129,129,129,157,130,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,131,0,0,0,0,128,157,128,129,128,129,129,129,129,129,157,129,129,129,130,16,17,17,17,17,35,0,128,129,130,129,129,129,157,129,129,129,129,129,129,129,129,130,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,131,0,0,0,0,128,129,129,129,157,129,129,129,129,129,129,129,129,128,130,28,0,0,0,0,0,0,128,129,129,129,129,129,129,129,129,129,129,157,129,129,129,130,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,131,0,0,0,0,128,129,129,129,129,129,129,129,129,129,129,129,129,129,130,25,0,0,0,0,0,0,128,129,129,129,129,129,129,129,129,129,129,129,129,129,129,130,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,131,0,0,0,0,0,0,
	0,0,0,0,0,131,138,138,139,140,140,138,139,146,146,147,140,138,138,138,138,139,140,140,138,138,146,147,140,138,139,140,138,139,146,147,139,140,140,140,140,152,151,147,138,138,139,140,138,138,139,140,138,139,140,146,147,138,138,139,138,139,146,147,138,138,138,138,139,140,128,129,129,129,131,107,107,107,107,129,129,129,129,129,129,129,129,129,129,129,129,129,129,129,124,124,157,157,157,124,124,129,129,129,129,129,129,129,129,129,129,129,129,129,129,129,129,129,129,129,129,129,129,129,129,129,129,129,129,129,129,129,129,129,129,129,129,129,129,129,129,129,129,129,129,129,129,129,129,129,129,129,129,130,0,0,0,0,0,0,
	0,0,0,0,0,131,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,154,153,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,32,0,0,0,131,0,0,0,0,131,9,10,8,9,10,8,9,10,10,10,10,10,8,8,9,10,0,0,0,8,9,10,11,8,9,10,11,20,20,8,9,10,10,10,10,10,157,0,0,0,0,0,0,0,0,0,37,0,0,0,0,0,0,0,0,0,37,0,0,37,0,0,0,0,0,0,0,0,0,0,0,0,24,131,0,0,0,0,0,0,
	0,0,0,0,0,131,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,154,153,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,32,0,0,0,131,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,21,20,0,0,0,0,0,0,0,157,0,0,0,0,0,0,0,0,0,37,0,0,0,0,0,0,0,0,0,37,0,0,37,0,0,0,0,0,0,0,0,0,0,0,0,0,131,0,0,0,0,0,0,
	0,0,0,0,0,131,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,154,153,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,32,0,0,0,131,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,39,40,0,0,0,102,101,99,0,0,0,0,0,0,0,0,0,20,0,0,0,0,0,0,0,157,0,0,0,0,0,0,0,0,0,37,0,0,0,0,0,0,0,0,0,37,0,0,37,0,0,0,0,0,0,0,0,0,0,0,0,0,131,0,0,0,0,0,0,
	0,0,0,0,0,131,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,154,153,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,32,0,0,0,131,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,45,46,0,0,0,0,85,0,0,0,0,0,0,0,0,0,0,31,0,0,0,0,0,0,0,157,0,0,0,0,0,0,0,38,0,44,65,66,66,67,66,67,66,68,0,44,0,0,44,0,65,66,68,0,52,43,0,0,0,0,0,0,131,0,0,0,0,0,0,
	0,0,0,0,0,131,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,63,64,0,154,153,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,42,0,0,0,131,0,0,0,0,0,0,0,0,0,0,0,0,39,40,0,0,0,0,0,0,0,0,30,0,0,0,0,0,0,0,0,0,0,0,0,0,102,107,107,107,108,124,124,157,157,157,124,124,124,124,124,124,125,125,125,125,125,124,124,124,124,124,125,125,124,124,125,124,124,124,124,126,0,0,0,0,0,0,131,0,0,0,0,0,0,
	0,0,0,0,0,131,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,77,78,0,154,153,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,123,124,124,124,129,124,124,124,124,124,124,124,124,126,0,0,0,45,46,0,39,40,0,0,0,0,0,30,0,102,101,99,0,0,0,0,0,0,0,0,0,0,0,0,0,41,131,31,0,0,0,0,0,0,131,0,0,5,4,0,0,0,0,5,0,4,0,0,0,0,4,5,0,0,5,0,131,0,0,0,0,0,0,131,0,0,0,0,0,0,
	0,0,0,0,0,131,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,123,126,0,0,0,0,0,0,0,0,0,0,0,63,64,87,88,0,154,153,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,110,114,114,111,0,0,0,0,0,0,0,0,0,0,0,0,0,24,131,23,22,86,0,0,0,0,0,0,0,45,46,0,0,0,0,0,85,0,0,30,0,0,0,0,0,0,0,0,0,0,0,0,0,0,41,131,0,0,0,0,0,0,0,131,0,0,5,4,0,0,0,0,5,0,4,0,0,0,0,4,5,0,0,5,0,131,0,0,0,0,0,0,131,0,0,0,0,0,0,
	0,0,0,0,0,131,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,131,131,0,0,0,0,0,0,0,0,0,0,0,77,78,93,94,0,154,153,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,131,0,0,76,0,0,0,0,0,0,0,0,0,0,0,0,0,0,30,0,0,85,0,0,0,0,0,0,0,0,0,0,0,102,107,107,108,131,0,0,0,0,0,0,0,131,0,0,5,4,0,0,0,0,5,0,4,0,0,0,0,4,5,0,0,5,0,131,0,0,0,0,0,0,131,0,0,0,0,0,0,
	0,0,0,0,0,131,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,131,131,124,126,0,0,0,0,0,0,0,0,0,87,88,95,96,0,154,153,0,0,0,0,0,0,0,110,114,114,113,114,114,112,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,7,0,0,131,0,0,85,0,0,0,0,0,0,0,0,0,0,0,102,101,99,30,0,0,30,0,0,0,0,63,64,0,0,0,0,0,0,0,0,41,131,0,0,0,0,0,49,50,131,51,0,13,4,0,0,0,0,5,0,4,0,0,0,0,12,5,0,0,13,0,131,0,0,0,0,0,0,131,0,0,0,0,0,0,
	0,0,0,0,0,131,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,131,131,131,131,0,0,0,0,0,0,0,0,0,93,94,87,88,0,154,153,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,14,15,0,0,131,61,53,59,54,0,0,0,0,0,0,0,0,0,0,0,30,0,85,0,0,30,0,0,63,64,77,78,0,0,0,0,0,0,0,0,41,128,125,157,157,157,123,125,125,130,100,0,0,4,0,0,0,0,5,0,4,0,0,0,0,0,5,0,0,0,0,131,0,0,0,0,0,0,131,0,0,0,0,0,0,
	0,0,0,0,0,131,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,131,131,131,131,124,126,0,0,0,0,0,0,0,93,94,87,88,0,154,153,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,22,0,0,0,131,62,0,0,60,0,0,0,0,0,0,0,0,0,0,0,30,0,30,0,0,85,0,0,77,78,87,88,0,0,0,0,0,0,102,107,108,131,72,0,0,0,0,0,0,131,4,0,0,12,0,0,127,0,13,0,4,0,0,157,0,0,5,0,0,0,0,131,0,0,0,0,0,0,131,0,0,0,0,0,0,
	0,0,0,0,0,131,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,131,131,131,131,131,131,0,0,0,0,0,0,0,87,88,93,94,0,98,97,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,73,74,75,0,0,0,0,0,0,0,0,0,0,85,0,106,101,99,30,0,0,87,88,93,94,63,64,0,0,0,0,0,0,41,131,81,0,0,0,0,0,0,131,4,0,0,0,0,0,5,0,0,0,4,0,0,0,0,0,5,0,0,0,0,131,0,0,0,0,0,0,131,0,0,0,0,0,0,
	0,0,0,0,0,131,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,131,131,131,131,131,131,107,107,107,99,0,0,0,87,88,87,88,0,0,0,0,0,0,0,0,0,3,0,0,0,1,2,3,0,0,0,115,132,135,136,137,133,132,137,119,2,0,0,0,0,0,0,0,0,0,0,0,0,0,82,83,84,0,0,0,0,0,0,0,0,0,0,30,0,30,85,0,30,0,0,93,94,93,94,77,78,0,0,0,0,0,0,41,131,89,0,0,0,0,0,0,131,12,0,0,0,0,0,5,0,0,0,12,0,0,0,0,0,5,0,0,0,100,131,0,0,0,0,0,0,131,0,0,0,0,0,0,
	0,0,0,0,0,131,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,157,157,0,0,157,157,0,0,0,0,0,0,0,93,94,93,94,0,0,0,0,0,0,115,137,137,136,137,133,132,136,137,133,132,135,135,97,0,0,0,0,0,0,0,98,136,137,119,0,3,0,0,0,1,2,0,0,0,2,90,91,92,0,3,0,0,0,1,2,3,0,0,30,0,30,30,0,30,3,0,95,96,95,96,95,96,0,0,0,0,1,2,41,131,89,0,0,0,57,58,69,131,0,0,0,0,0,0,5,0,0,0,0,0,0,0,0,0,13,0,0,0,4,131,0,0,0,0,0,0,131,0,0,0,0,0,0,
	0,0,0,0,0,131,2,0,0,0,0,0,0,0,0,0,0,0,0,0,2,3,0,157,157,1,3,157,157,0,0,0,1,2,0,0,95,96,95,96,0,0,1,1,3,115,97,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,98,136,135,135,136,135,136,136,136,135,135,136,137,133,132,136,137,135,135,135,136,137,136,135,136,135,135,136,137,135,136,136,137,132,133,133,132,133,137,135,136,136,135,135,137,111,128,125,157,157,157,123,125,125,130,0,0,0,0,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,4,131,0,0,0,0,0,0,131,0,0,0,0,0,0,
	0,0,0,0,0,137,136,137,119,3,0,0,0,0,0,0,0,1,115,133,134,137,133,132,136,137,135,135,137,137,135,136,137,132,137,132,137,135,137,136,137,137,137,137,137,97,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,131,0,0,0,0,0,5,4,0,0,0,0,0,0,0,13,0,0,0,0,0,0,0,0,127,0,0,0,0,12,131,0,0,70,71,0,0,131,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,98,133,119,2,115,133,119,3,115,135,97,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,131,0,0,0,0,0,13,4,0,0,0,0,0,0,0,0,0,0,0,127,0,0,0,0,4,0,0,0,0,0,131,125,120,79,80,116,124,131,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,98,135,97,0,98,137,97,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,131,0,0,0,0,0,0,12,0,0,0,0,0,157,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,131,129,131,125,125,131,129,131,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,128,125,125,125,125,125,125,125,125,126,0,0,0,0,0,0,0,0,0,0,0,0,0,0,12,0,0,0,0,0,131,130,129,131,128,129,131,131,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,131,131,131,131,131,131,131,131,0,0,0,0,0,0,
	
};

const std::array<sf::Vector2f, 14> TiledEntities::bat = {
			sf::Vector2f(800.0f, 707.0f),
			sf::Vector2f(829.0f, 852.6667f),
			sf::Vector2f(861.0f, 850.6667f),
			sf::Vector2f(1152.0f, 816.0f),
			sf::Vector2f(1000.667f, 820.3333f),
			sf::Vector2f(2192.0f, 800.0f),
			sf::Vector2f(2112.0f, 800.0f),
			sf::Vector2f(2208.25f, 895.75f),
			sf::Vector2f(2096.0f, 896.5f),
			sf::Vector2f(2239.25f, 976.0f),
			sf::Vector2f(2288.0f, 800.0f),
			sf::Vector2f(1342.0f, 146.0f),
			sf::Vector2f(1762.0f, 212.0f),
			sf::Vector2f(1200.0f, 224.0f),
		};
const sf::Vector2f TiledEntities::gun = sf::Vector2f(206.67000000000007f, 960.667f);
const std::array<sf::Vector2f, 4> TiledEntities::powerup = {
			sf::Vector2f(1151.333f, 777.33333f),
			sf::Vector2f(1616.0f, 508.0f),
			sf::Vector2f(2001.333f, 847.3333f),
			sf::Vector2f(1520.3333f, 318.0f),
		};
const sf::Vector2f TiledEntities::walljump = sf::Vector2f(2392.0f, 972.0f);
const sf::Vector2f TiledEntities::spawn = sf::Vector2f(1569.3333f, 858.0f);

