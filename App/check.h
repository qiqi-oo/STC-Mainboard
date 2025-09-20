#ifndef	__CHECK_H
#define	__CHECK_H


/*
#define TEST 10										//公司测试程序	 10
#define GZ_QNZ_FQXX_KM2 	11			//贵州省黔南州福泉兴鑫科目二 					11
#define GZ_QNZ_DSJJ_KM2 	49			//贵州省黔南州独山剑江科目二 					49
#define GZ_QNZ_GDYG_KM2 	59			//贵州省黔南州贵定阳光科目二					59
#define AH_LA_SCTX_KM2 		60			//安徽省六安市舒城同兴科目二					60
#define SD_WF_QZAS_KM2 		63			//山东省潍坊市青州安盛科目二					63
#define SD_WF_SGJD_KM2 		66			//山东省潍坊市寿光金盾驾校科目二 			66
#define GZ_QNZ_HSQL_KM2 	171			//贵州省黔南州惠水黔岭科目二					70//已改为171
#define HB_ZJK_XH_KM2 		71			//河北省张家口市宣化科目二考场 				71
#define GZ_LPS_QL_KM2 		77			//贵州省六盘水黔龙驾校科目二					77
//#define GZ_QNZ_WAJF_KM2 	79			//贵州省黔南州瓮安江沣科目二（旧考场)	79
#define GZ_TR_SNTN_KM2 		81			//贵州省铜仁思南铜南科目二						81
#define GZ_QNZ_LDJX_KM2 	82			//贵州省黔南州罗甸吉兴科目二	        82
#define GZ_QNZ_DYJD_KM2 	84			//贵州省黔南州都匀金都科目二	        84
#define SD_WF_SGDL_KM2 		85			//山东省潍坊市寿光德隆科目二	        85
#define SD_WF_WFQA_KM2 		86			//山东省潍坊市潍坊乾安科目二	        86
#define SD_WF_GMCY_KM2 		87			//山东省潍坊市高密超越驾校科目二	    87
#define SD_WF_WFLY_KM2 		88			//山东省潍坊市陆洋驾校科目二训练	    88
#define GZ_QDN_KR_KM2 		97			//贵州省黔东南州凯榕科目二						97
#define GZ_QDN_TZQT_KM2 	98			//贵州省黔东南州天柱县擎天驾校科目二	98
#define GZ_QDN_ZXD_KM2 		99			//贵州省黔东南中信达科目二						99
#define GZ_QDN_PTDF_KM2 	100			//贵州省黔东南平塘东方科目二	        100
#define GZ_BJ_YH_KM2 			101			//贵州省毕节宇航科目二	              101
#define GZ_QX_QZ_KM2 			102			//贵州省黔西黔职科目二								102
#define NM_CF_JZ_KM2 			106			//内蒙古赤峰市北山交职科目二					106
#define HB_JZK_XH_KM3 		108			//河北省张家口市宣化科目三考场				108
#define HB_SJZ_YH_KM2 		109			//河北省石家庄市育华驾校科目二				109
#define GZ_QNZ_LLJD_KM2 	119			//贵州省黔南州龙里县金都驾校科目二		119
#define GZ_QDN_JPLX_KM2 	120			//贵州省黔东南州锦屏县龙翔驾校科目二	120
#define NM_CF_HS_KM2 			121			//内蒙古赤峰市红山驾校科目二					121
#define NM_CF_ZH_KM2 			122			//内蒙古赤峰市中昊驾校科目二					122
#define NM_CF_JZ_KM3 			123			//内蒙古赤峰市北山交职科目三					123
#define HN_YZ_JJZD_KM2 		125			//湖南省永州市交警支队支队科目二			125
#define HB_SJZ_YSPA_KM2 	127			//河北省石家庄市元氏平安驾校科目二		127
#define GZ_TR_XJB_KM2 		128			//贵州省铜仁市许家坝科目二考场				128
#define GZ_TR_JKNJ_KM2 		129			//贵州省铜仁市江口南江科目二					129
#define GZ_QNZ_LLJD_KM3 	25			//贵州省黔南州龙里金都科目三					130：2016年1月5日改为25
#define GZ_QNZ_HSJD_KM2 	131			//贵州省黔南州惠水金都科目二					131
#define GZ_QNZ_DYHY_KM2 	132			//贵州省黔南州都匀市浩源驾校科目二		132
#define GZ_QDN_TZRH_KM2 	133			//贵州省黔东南州天柱县嵘华驾校科目二	133
#define NM_CF_AQTD_KM2_3 	134			//内蒙古赤峰市阿旗通达驾校科目二、三	134
#define NM_CF_YBSHD_KM3 	135			//内蒙古赤峰市元宝山赫达驾校科目三		135
#define GZ_QNZ_WAJF_KM2 	136			//贵州省黔南州瓮安县江沣驾校科目二		136
#define GZ_QNZ_LD_KM3 		137			//贵州省黔南州罗店科三								137
#define HN_YZ_NFJX_KM2 		138			//湖南省永州市南方驾校科目二训练			138
#define HB_SJZ_XL_KM2 		139			//河北省石家庄新乐科目二训练					139
#define GZ_QNZ_FQJC_KM2_3	140			//贵州省黔南州福泉市锦程驾校科目二 三	140
#define GZ_QDN_ZYJT_KM2_3	141			//贵州省黔东南镇远金通驾校科目二、三 	141
#define GZ_QNZ_QYDQS_KM3	142			//贵州省黔南黔云栋青树金都科目三			142
#define GZ_QDN_TZRH_KM3		143			//贵州省黔东南州天柱县嵘华驾校科目三	143
#define HN_YZ_HX_KM2			149			//湖南省永州市鸿鑫驾校科目二训练			149
#define HN_YZ_WDL_KM2			150			//湖南省永州市维达利驾校科目二训练		150
#define GZ_GY_YG_KM2			151			//贵州省贵阳市阳光驾校科目二					151
#define HN_YZ_XTYG_KM2		152			//湖南省永州市新田阳光驾校科目二 			152
#define GZ_QDN_JPLX_KM3		153			//贵州省黔东南州锦屏县龙翔驾校科目三	153
#define GZ_QDN_BJHZ_KM3		154			//贵州省黔东南州毕节赫章科三					154
#define FJ_FZ_AKD_KM2			155			//福建福州安康达注册科目二						155
#define GZ_QNZ_PTDF_KM3		156			//贵州省黔南州平塘县东方驾校科目三		156
#define GZ_GY_KC_KM2_3		157			//贵州省贵阳市凯城驾校科目二 三				157
#define GZ_GY_JYCX_KM2		158			//贵州省贵阳市金阳诚信驾校科目二			158
#define GZ_QNZ_LPXSD_KM2	159			//贵州省黔南州荔波县兴盛达驾校科目二	159
#define GZ_QDN_KLGL_KM2		160			//贵州省黔东南州凯里市贵龙驾校科目二	160
#define HN_YZ_XTMX_KM2		161			//湖南省永州市新田民兴驾校科二训练		161
#define SD_WF_AQAJ_KM2		162			//山东潍坊安丘安驾科目二							162
#define HB_WJ_ZD_KM2			163			//河北省武警总队科目二								163
#define GZ_GY_ZJDLP_KM2		164			//贵州省贵阳市智杰驾校灯笼坡分校科目二164
#define GZ_QNZ_FQXQ_KM3		165			//贵州省黔南州福泉市鑫泉驾校科目三		165
#define HB_BD_AC_KM2			166			//河北省保定市奥城科目二训练场				166
#define HB_BD_TD_KM2			167			//河北省保定市腾达科目二训练场				167
#define GZ_GY_YMG_KM2			168			//贵州省贵阳市永铭贵驾校科目二				168
#define FJ_SM_LLT_KM2			169			//福建三明市路路通驾校科目二					169
#define GZ_QNZ_SDXX_KM2		170			//贵州省黔南州三都县兴鑫驾校科目二		170
#define GZ_QNZ_HSQL_KM2		171			//贵州省黔南州惠水黔岭科目二（改造）	171
#define GZ_QDN_TZQT_KM3		172			//贵州省黔东南州天柱县擎天驾校科目三	172
#define GZ_QNZ_HSSX_KM3		173			//贵州省黔南州惠水县顺行驾校科目三		173
#define GZ_GY_QF_KM3			174			//贵州省贵阳市黔丰驾校科目三					174
#define GZ_BJ_HZZH_KM2		175			//贵州省毕节市赫章县众汇科目二				175
#define GZ_QNZ_DS_KM2			176			//贵州省黔南州独山科二								176
#define GZ_QDN_TZYY_KM2		177			//贵州省黔东南州天柱县友谊驾校科目二	177
#define GZ_QNZ_QC_KM2			178			//贵州省黔南州启程机动车驾校科目二		178
#define GZ_QNZ_DYHOY_KM2	179			//贵州省黔南州都匀市宏源驾校科目二		179
#define GZ_QNZ_PTXSD_KM2	180			//贵州省黔南州平塘县兴盛达驾校科目二	180
#define SD_JN_SSD_KM2			181			//山东省济南市三顺达科目二训练场			181
#define GZ_QNZ_LLSJJD_KM3	182			//贵州省黔南州龙里县圣锦金都驾校科三	182
#define HN_YZ_LSXY_KM2		183			//湖南省永州市蓝山县湘源驾校科目二训练183
#define GZ_GY_SF_KM2			184			//贵州省贵阳市时发驾校科目二					184
#define SD_JN_MY_KM2_3		185			//山东省济南市明苑科目二、三考场			185
#define GZ_QNZ_FQQY_KM2		186			//贵州省黔南州福泉市骐源驾校科目二		186
#define SD_JN_YS_KM2			187			//山东省济南市影山驾校科目二训练场		187
#define GZ_QNZ_WAYL_KM2		188			//贵州省黔南州瓮安县云岭驾校科目二		188
#define GZ_QNZ_SDSS_KM2		189			//贵州省黔南州三都山水科二						189
#define GZ_QNZ_QYJD_KM2		190			//贵州省黔南州黔云金都科二						190
#define HN_YZ_JYYX_KM2		191			//湖南永州江永永兴科二训练						191
#define GZ_GY_KYXT_KM2		192			//贵州省贵阳市开阳新天科目二					192
#define HB_SJZ_YHZNC_KM2	193			//石家庄育华科目二智能培训车					193
#define GZ_GY_XFXT_KM2		194			//贵州省贵阳市息峰县新天驾校科目二		194
#define GZ_QNZ_CS_KM2			195			//贵州省黔南州长顺驾校科目二考场			195 
#define GZ_QNZ_HSXS_KM3		196			//贵州省黔南州惠水鑫盛科目三					196
#define TJ_XD_KM3					197			//天津市先达驾校科目三考场						197
#define SD_RZ_SJ_ZNC			198			//山东省日照顺吉驾校智能培训车				198
#define GZ_GY_DHY_KM2			199			//贵州省贵阳大关云顺达科目二					199
#define GZ_QNZ_DSXSD_KM2	200			//贵州省黔南州独山兴盛达科目二				200 
#define GZ_QNZ_DSXY_KM2		201			//贵州省黔南州独山县兴宇驾校科目二		201
#define GZ_QNZ_GDWT_KM2		202			//贵州省黔南州贵定万通驾校科目二			202
#define SD_HZ_CC_KM2			203			//山东省菏泽市辰昌驾校科目二训练			203
#define GZ_QNZ_GDDC_KM3		204			//贵州省黔南州贵定县东成驾校科目三		204
#define HN_YZ_NYZN_KM2		205			//湖南省永州宁远忠南驾校科目二				205
#define GZ_QDN_ZYQXJT_KM2	206			//贵州省黔东南镇远清溪金通科目二			206
#define SD_RZ_LXKT_KM2		207			//山东省日照莒县坤涛科目二训练				207
#define SD_JN_YSJX_KM2		208			//山东省济南市影山俊翔科目二训练			208
#define TJ_JHDS_KM3				209			//天津市静海都顺驾校科目三考场				209
#define GZ_LPS_KD_KM3			210			//贵州省六盘水凯达驾校科目三					210
#define SD_TA_DCBFS_KM2		211			//山东省泰安市东成县白佛山驾校科目二训练211
#define GZ_QNZ_LLXX_KM2		212			//贵州省黔南州龙里兴鑫科目二					212
#define SD_JN_LS_KM2			213			//山东省济南市路舜驾校科目二训练			213
#define GZ_LPS_DA_KM2			214			//贵州省六盘水达安驾校科目二考场			214
#define HN_YZ_QY_KM2			215			//湖南省永州市祁阳科目二考场					215
#define SD_JN_SHXF_KM2		216			//山东省济南市商河谢芳驾校科目二训练场216
#define GZ_QNZ_JT_KM2			217			//贵州省黔南州交通驾校科目二训练场		217
#define SD_JN_NY_KM2			218			//山东省济南市南苑驾校科目二训练场		218
#define SD_JN_SHYH_KM2		219			//山东省济南市商河银河驾校科目二训练	219
#define LJ82_HCLL_ZZPP		220			//82军合成6旅智能评判系统						220
#define LJ81_ZLZYL_ZZPP		221			//81军战略支援旅智能评判系统					221
#define SD_JN_SHJD_KM2		222			//山东济南商河金盾科二训练						222
#define SD_JN_LCLF_KM2		223			//山东省济南市历城区柳埠科目二训练场	223
#define GZ_QNZ_LDZY_KM2		224			//贵州省黔南州罗甸致远驾校训练场			224
#define XJ_KS_32329_ZZPP	225			//新疆32329汽车兵训练系统						225
#define SD_JN_HY_MTC			226			//山东省济南市槐荫区交警大队摩托车		226
#define GZ_QNZ_WAYL_KM3		227			//贵州省黔南州瓮安云岭科目三考场			227
#define SD_WH_LLT_ZNC			228			//山东威海路路通智能培训车						228
#define HB_DZWJ_ZZPP			229			//定州武警智能训考系统								229
#define GZ_QNZ_LDKT				230			//黔南罗甸康泰摩托车考试场						230
#define GZ_ZY_ZSJJDD			231			//贵州遵义习水交警大队摩托车考场			231
#define HB_ZJKWQ_XHMTC		232			//张家口市万全县星皓摩托车考试场			232
#define GZ_LPS_SCMTC			233			//贵州六盘水水城区摩托车考场			    233
#define XJ_KRL_ZJCP				234			//新疆库尔勒装甲车裁评系统项目			  234
#define XJ_TLJ						236			//新疆拖拉机项目			  							236
#define XJ_KRL_LS				  237			//新疆库尔勒汽车项目                 237
*/





extern xdata u8 localid[ID_LENTH];




void Check_Serial_Id(void);	 //校验ID信息
void ByteToHexStr(const unsigned char* source, char* dest, int sourceLen);
void Checksum(u8 *pbuffer, u16 lenth);	 //计算校验和
u8 * ByteArrayCompar(const u8 *source,u16 srclen, const u8 *dest,u16 deslen);	
#ifdef  STC15W4K48S4
u8 * ByteArrayCompar_r(const u8 *source,u16 srclen, const u8 *dest,u16 deslen);
#endif


#endif

