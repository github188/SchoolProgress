####### Compiler, tools and options

DEL_FILE      = rm -f
CC            = gcc
CXX           = g++
LINK          = g++

####### Files
object = astar.o\
	md5.o\
	function_register.o\
	bag.o\
	bag_operator.o\
	pickGoods.o\
	pet.o\
	pet_box.o \
	pet_operator.o\
	pet_communicate.o\
	petSkill_config.o \
	pet_skill.o\
	pet_attack_monster.o\
	pet_attack_hero.o\
	user_role_manage_task.o\
	user_role_accept_task.o\
	user_role_finish_task.o\
	task_goods_info.o\
	dropGoods.o\
	game_fight_assist.o\
	warehouse.o\
	warehouse_operator.o\
	warehouse_communicate.o\
	reward_operator.o\
	reward_communicate.o\
	reward_level_config.o\
	reward_online_config.o\
	reward_online.o\
	guildBussiness.o\
	shengWang_bussiness.o\
	GM.o\
	GM_communicate.o\
	festivalActive.o\
	read_festival.o\
	verify.o\
	midasTouch.o\
	midasTouch_communicate.o\
	mysteriousBussiness_config.o\
	mysteriousBussiness.o\
	mysteriousBussiness_communicate.o\
	function_read_configuration_files_revival.o\
	revival_config.o\
	function_read_configuration_files_reward_level.o\
	reward_recharge_config.o\
	function_read_configuration_files_reward_recharge.o\
	function_read_configuration_files_reward_online.o\
	read_cdkey.o\
	read_everyDaySignReward.o\
	read_rank_reward.o\
	game_move.o\
	command_other_function_all_over.o\
	over_all_varity.o\
	hero.o\
	fingerGuessingGame_communicate.o\
	nbox.o\
	role.o\
	npc.o\
	task.o\
	read_main_config.o\
	read_server_config.o\
	read_scene_config.o\
	parseTowerDefence.o\
	read_files_ointment.o\
	read_pet_range.o\
	equipment.o\
	equip_config.o\
	pet_config.o\
	ectype_reward_info.o\
	ectype_reward_set.o\
	read_ectype_reward_goods.o\
	read_task_goods_info.o\
	read_ectype_reward_info.o\
	ointment.o\
	function_read_configuration_files_exp.o\
	function_read_configuration_files_map.o\
	function_read_configuration_files_monster.o\
	function_read_configuration_files_skill.o\
	function_read_configuration_files_five.o\
	function_read_configuration_files_equip.o\
	function_read_configuration_files_goods.o \
	function_read_configuration_files_midasTouch.o \
	function_read_configuration_files_mysteriousBussiness.o \
	function_read_configuration_files_guildBussiness.o \
	function_read_configuration_files_shengWangBussiness.o \
	function_read_configuration_files_pet.o\
	function_read_configuration_files_jumpId.o\
	function_read_configuration_files_task.o\
	function_read_configuration_files_touch.o\
	function_read_configuration_files_droplist.o\
	function_read_configuration_files_npc.o\
	function_read_configuration_files_petSkill.o \
	read_words.o\
	read_equip_operator.o\
	read_vip.o\
	read_factor_reward.o \
	read_active_double.o \
	goods_config.o \
	task_configuration.o\
	task_touch_configuration.o\
	npc_configuration.o\
	skill_configuration.o\
	hero_configuration.o\
	droplist_configuration.o\
	monster_configuration.o\
	five_configuration.o\
	role_manage_create_hero.o\
	role_manage_delete_hero.o\
	role_manage_select_hero.o\
	role_manage_change_scene.o\
	exit_exception.o\
	exit_normal.o\
	user_manage_login.o\
	login_from_web.o\
	user_role_manage_assist.o\
	time_poll.o\
	libev.o\
	read_ride.o\
	read_ride_skill.o\
	read_specialSkill.o\
	ride.o\
	ride_operator.o\
	ride_config.o\
	TD_Instancing.o\
	monsterBase.o\
	monsterPassivity.o\
	monsterActive.o\
	monsterPatrol.o\
	monsterTowerDefence.o\
	read_hatValRue.o\
	monThkFun.o\
	hatValRue.o\
	mapAction.o\
	bruMonInfor.o\
	advertise.o\
	whisper.o\
	systemMssage.o\
	jumpId_to_changeSence.o\
	ordinaryCampWar.o\
	leaderCampWar.o\
	campWarManagement.o\
	analyzeCampWar.o\
	chiefCampWar.o\
	set_camp.o\
	friend.o\
	friendAnalyze.o\
	rankInfo.o\
	analyzeRankInfo.o\
	rankInfoAsist.o\
	analyzeHangUpInfo.o\
	analyzeShortCutInfo.o\
	analyzeSystemSetInfo.o\
	analyzeOperationSetInfo.o\
	bootAssignment.o\
	top_up.o\
	read_campWar_reward_conf.o\
	camp_war_reward.o \
	handsel_flowers.o\
	read_recharge_reward_conf.o\
	read_consume_reward_conf.o\
	read_goods_use_reward_conf.o\
	goods_use_reward.o\
	system_activity_reward_assist.o\
	recharge_reward.o\
	consume_reward.o\
	downline_operate.o\
	pick.o\
	money.o\
	money_operator.o\
	cpy.o\
	read_cpy.o\
	hero_revival.o\
	sitControl.o\
	read_cpyLimit.o\
	cpyLimit.o\
	hero_need_experience.o\
	instancing_manage.o\
	instancing_communication.o\
	entCpy.o\
	entCpyNextMap.o\
	exitCpy.o\
	cpyAsist.o\
	groupBrush.o\
	read_groupBrush.o\
	read_monster_skill.o\
	skillBase.o\
	rigidity.o\
	recoverBlood.o\
	bossSkiRig.o\
	five_elements.o\
	five_asist.o\
	five_elem_comm.o\
	meridian.o\
	meridian_asist.o\
	meridian_comm.o\
	internal_forces_manage.o\
	internal_forces_comm.o\
	read_internal_forces.o\
	read_global.o\
	user_attr_apply.o\
	kaiRen.o\
	yiZhi.o\
	heCheng.o\
	rongLian.o\
	xiangQian.o\
	zhaiQu.o\
	equip_hero_manage_wear.o\
	equip_hero_manage_takeoff.o\
	hero_equip_operate_require.o\
	hero_equip_operate_clientinfo.o\
	hero_equip_change_help.o\
	action.o\
	unEnemy.o\
	bruType.o\
	guild.o\
	guild_asist.o\
	guild_comm.o\
	read_fight_const_value.o\
	hero_skill.o\
	upgrade_hero_skill.o\
	read_hero_skill.o\
	basis_cal.o\
	fight_val_cal.o\
	proc_lose_life.o\
	hero_skill_deal.o\
	proc_use_skill.o\
	upgrade_hero_skill_comm.o\
	use_skill_comm.o\
	read_hero_conf.o\
	shopBusiness.o\
	onLineStallBusiness.o\
	playerBusiness.o\
	npcBusiness.o\
	suit.o\
	function_read_configuration_files_suit.o\
	guild_war_room.o\
	guild_war_asist.o\
	guild_war_comm.o\
	guild_activity.o\
	read_guild_activity.o\
	read_cycle_limit.o\
	read_cycle_task_reward.o\
	takeGoods.o\
	read_take_goods.o\
	wagon.o\
	read_wagon.o\
	bottle.o\
	read_bottle.o\
	trap.o\
	read_trap.o\
	my_memcached.o\
	attack_wagon.o\
	task_failed_comm.o\
	read_npc.o\
	gotoNPC.o\
	monsterPasstrol.o\
	read_vip_config.o\
	mailSysterm.o\
	mail_systerm_interface.o\
	mail_systerm_communicate.o\
	heroCpyRecord.o\
	map_inform.o\
	map_cpy.o\
	map_src.o\
	read_copyCause.o\
	user_role_manage_status.o\
	read_pitchTerm.o\
	hero_title_use.o\
	read_title.o\
	deal_offline_unhandle_event.o\
	wagonAction.o\
	my_time.o\
	my_timer.o\
	read_dirty_words.o\
	dictionary.o\
	dictionary_asist.o\
	enterScenResponse.o\
	enterCpyByTool.o\
	monsterActiveBoss.o\
	read_monsterActiveBoss.o\
	dailyActive.o\
	read_dailyActive.o\
	takePartActive.o\
	activeAsist.o\
	read_cpyPassOlder.o\
	wagon_rank.o\
	boxAsist.o\
	hero_drugs_manage.o\
	read_guild_feast.o\
	guild_club.o\
	guild_club_assist.o\
	read_rsa_key.o\
	panelResponse.o\
	wulinTarget.o\
	read_wuLinTarget.o\
	cpyManager.o\
	read_happy_map.o\
	read_guild_skill.o\
	move_calbak.o\
	dropEquipAction.o\
	read_buff_debuff.o\
	hero_buff.o\
	hero_collect.o\
	monsterCamp.o\
	monsterTool.o\
	read_tool_brush_monster.o\
	attackBottle.o\
	vipBaleRoomLimit.o\
	read_vip_bale_room.o\
	enterVipBaleRoom.o\
	exitVipBaleRoom.o\
	monsterAttRed.o\
	botThkCalBack.o\
	partyRoomLimit.o\
	read_partyRoom.o\
	monsterEscape.o\
	read_heCheng_configure.o\
	read_guild_reward.o\
	showPartyLunch.o\
	read_cpyNpc_pt.o\
	read_party_base_camp.o\
	partyBaseCampLimit.o\
	enterPartyCamp.o\
	read_outer_active_code.o\
	read_inner_active_code.o\
	acceptActiveCode.o\
	read_merid_conf.o\
	read_five_elem_conf.o\
	monsterByHero.o\
	fire_pao_zhu.o\
	hero_ride.o\
	ride_comm.o\
	statuaryBase.o\
	read_statuaryBase.o\
	statuaryHero.o\
	statuaryAsist.o\
	read_mem_group_config.o\
	my_mem_group.o\
	monsterStatuary.o\
	read_camp_res_war_control.o\
	read_guild_war_control.o\
	read_rob_flag_war_control.o\
	camp_res_war.o\
	rob_flag_war.o\
	rob_flag_war_logic.o\
	rob_flag_war_comm.o\
	camp_leader_and_chief.o\
	towerLayerRecord.o\
	read_blackMargin.o\
	enterTowerLayerCopy.o\
	purchaseFatigue.o\
	swapTowerLayerCopy.o\
	brushTower.o\
	monCallSkill.o\
	chatGroup.o\
	chatGroupManager.o\
	monsterStill.o\
	team.o\
	teamManager.o\
	teamOperator.o\
	teamAsist.o\
	test.o	

all : bin/wsd bin/lsd

bin/wsd : $(object)
	$(LINK) -g -o bin/wsd $(object) -I /usr/local/include/libxml2/ -L /usr/local/include/lib/ -lssl -lcrypto -lxml2 -levent -lmemcached -luuid	
bin/lsd :
	g++ -g -o bin/lsd logSrv/logSrv.cpp -L /usr/local/include/lib/ -levent
	
wulinTarget.o : src/wulinTarget/wulinTarget.cpp
	$(CXX) -g -c $< -Iinclude

read_wuLinTarget.o : src/wulinTarget/read_wuLinTarget.cpp
	$(CXX) -g -c $< -Iinclude -I /usr/local/include/libxml2/ -L /usr/local/include/lib/ -lxml2	

hero_title_use.o : src/user_role_manage/hero_title_use.cpp
	$(CXX) -g -c $< -Iinclude 
	
read_title.o : src/read_configure/read_title.cpp
	$(CXX) -g -c $< -Iinclude -I /usr/local/include/libxml2/ -L /usr/local/include/lib/ -lxml2
	
read_pitchTerm.o : src/read_configure/read_pitchTerm.cpp
	$(CXX) -g -c $< -Iinclude -I /usr/local/include/libxml2/ -L /usr/local/include/lib/ -lxml2
	
read_copyCause.o : src/read_configure/read_copyCause.cpp
	$(CXX) -g -c $< -Iinclude -I /usr/local/include/libxml2/ -L /usr/local/include/lib/ -lxml2
	
read_vip_config.o : src/read_configure/read_vip_config.cpp
	$(CXX) -g -c $< -Iinclude -I /usr/local/include/libxml2/ -L /usr/local/include/lib/ -lxml2
	
gotoNPC.o :	src/model/gotoNPC.cpp
	$(CXX) -g -c $< -Iinclude

read_npc.o : src/read_configure/read_npc.cpp
	$(CXX) -g -c $< -Iinclude -I /usr/local/include/libxml2/ -L /usr/local/include/lib/ -lxml2	
	
npcBusiness.o : src/business/npcBusiness.cpp
	$(CXX) -g -c $< -Iinclude

playerBusiness.o : src/business/playerBusiness.cpp
	$(CXX) -g -c $< -Iinclude

onLineStallBusiness.o : src/business/onLineStallBusiness.cpp
	$(CXX) -g -c $< -Iinclude
	
shopBusiness.o : src/business/shopBusiness.cpp
	$(CXX) -g -c $< -Iinclude
	
astar.o : src/astar/astar.cpp
	$(CXX) -g -c $< -Iinclude
	
ordinaryCampWar.o : src/campWar/ordinaryCampWar.cpp
	$(CXX) -g -c $< -Iinclude
	
campWarManagement.o : src/campWar/campWarManagement.cpp
	$(CXX) -g -c $< -Iinclude
	
leaderCampWar.o : src/campWar/leaderCampWar.cpp
	$(CXX) -g -c $< -Iinclude
	
analyzeCampWar.o : src/campWar/analyzeCampWar.cpp
	$(CXX) -g -c $< -Iinclude
	
chiefCampWar.o : src/campWar/chiefCampWar.cpp
	$(CXX) -g -c $< -Iinclude
		
set_camp.o : src/campWar/set_camp.cpp 
	$(CXX) -g -c $< -Iinclude
	
friend.o :  src/friends/friend.cpp 
	$(CXX) -g -c $< -Iinclude
	
friendAnalyze.o : src/friends/friendAnalyze.cpp 
	$(CXX) -g -c $< -Iinclude
	
rankInfo.o : src/viewInfo/rankInfo.cpp
	$(CXX) -g -c $< -Iinclude
	
rankInfoAsist.o : src/viewInfo/rankInfoAsist.cpp
	$(CXX) -g -c $< -Iinclude	
	
analyzeRankInfo.o : src/viewInfo/analyzeRankInfo.cpp
	$(CXX) -g -c $< -Iinclude
	
analyzeHangUpInfo.o :  src/tempConfigurationInfo/analyzeHangUpInfo.cpp
	$(CXX) -g -c $< -Iinclude
	
analyzeShortCutInfo.o : src/tempConfigurationInfo/analyzeShortCutInfo.cpp
	$(CXX) -g -c $< -Iinclude

analyzeSystemSetInfo.o : src/tempConfigurationInfo/analyzeSystemSetInfo.cpp
	$(CXX) -g -c $< -Iinclude

analyzeOperationSetInfo.o : src/tempConfigurationInfo/analyzeOperationSetInfo.cpp
	$(CXX) -g -c $< -Iinclude

bootAssignment.o : src/bootAssignment/bootAssignment.cpp
	$(CXX) -g -c $< -Iinclude
	
top_up.o : src/business/top_up.cpp
	$(CXX) -g -c $< -Iinclude
	
read_campWar_reward_conf.o : src/campWar/read_campWar_reward_conf.cpp
	$(CXX) -g -c $< -Iinclude -I /usr/local/include/libxml2/ -L /usr/local/include/lib/ -lxml2	
	
camp_war_reward.o : src/campWar/camp_war_reward.cpp
	$(CXX) -g -c $< -Iinclude

advertise.o : src/chat/advertise.cpp 
	$(CXX) -g -c $< -Iinclude
	
handsel_flowers.o : src/chat/handsel_flowers.cpp
	$(CXX) -g -c $< -Iinclude 
	
read_recharge_reward_conf.o : src/system_activity_reward/read_recharge_reward_conf.cpp
	$(CXX) -g -c $< -Iinclude -I /usr/local/include/libxml2/ -L /usr/local/include/lib/ -lxml2	

read_consume_reward_conf.o : src/system_activity_reward/read_consume_reward_conf.cpp
	$(CXX) -g -c $< -Iinclude -I /usr/local/include/libxml2/ -L /usr/local/include/lib/ -lxml2	

read_goods_use_reward_conf.o : src/system_activity_reward/read_goods_use_reward_conf.cpp
	$(CXX) -g -c $< -Iinclude -I /usr/local/include/libxml2/ -L /usr/local/include/lib/ -lxml2	
	
goods_use_reward.o :  src/system_activity_reward/goods_use_reward.cpp
	$(CXX) -g -c $< -Iinclude
	
whisper.o : src/chat/whisper.cpp 
	$(CXX) -g -c $< -Iinclude
	
systemMssage.o : src/chat/systemMssage.cpp 
	$(CXX) -g -c $< -Iinclude
		
jumpId_to_changeSence.o : src/model/jumpId_to_changeSence.cpp 
	$(CXX) -g -c $< -Iinclude
	
system_activity_reward_assist.o : src/system_activity_reward/system_activity_reward_assist.cpp
	$(CXX) -g -c $< -Iinclude
	
recharge_reward.o : src/system_activity_reward/recharge_reward.cpp
	$(CXX) -g -c $< -Iinclude

consume_reward.o : 	src/system_activity_reward/consume_reward.cpp
	$(CXX) -g -c $< -Iinclude

downline_operate.o : src/user_role_manage/downline_operate.cpp
	$(CXX) -g -c $< -Iinclude
	
bag.o : src/bag/bag.cpp 
	$(CXX) -g -c $< -Iinclude	
	
bag_operator.o : src/bag/bag_operator.cpp 
	$(CXX) -g -c $< -Iinclude

pickGoods.o : src/hero_goods/pickGoods.cpp
	$(CXX) -g -c $< -Iinclude
	
pet.o : src/pet/pet.cpp
	$(CXX) -g -c $< -Iinclude
	
pet_box.o : src/pet/pet_box.cpp
	$(CXX) -g -c $< -Iinclude
	
pet_operator.o : src/pet/pet_operator.cpp
	$(CXX) -g -c $< -Iinclude
	
pet_communicate.o : src/pet/pet_communicate.cpp
	$(CXX) -g -c $< -Iinclude
	
petSkill_config.o : src/pet/petSkill_config.cpp
	$(CXX) -g -c $< -Iinclude
	
pet_skill.o : src/pet/pet_skill.cpp
	$(CXX) -g -c $< -Iinclude	
	
pet_attack_monster.o : src/pet/pet_attack_monster.cpp
	$(CXX) -g -c $< -Iinclude		
	
pet_attack_hero.o : src/pet/pet_attack_hero.cpp
	$(CXX) -g -c $< -Iinclude	
	
function_register.o : src/function_register/function_register.cpp
	$(CXX) -g -c $< -Iinclude

user_role_manage_task.o : src/hero_task/user_role_manage_task.cpp
	$(CXX) -g -c $< -Iinclude

user_role_accept_task.o : src/hero_task/user_role_accept_task.cpp
	$(CXX) -g -c $< -Iinclude
	
user_role_finish_task.o : src/hero_task/user_role_finish_task.cpp
	$(CXX) -g -c $< -Iinclude

task_goods_info.o : src/read_configure/task_goods_info.cpp
	$(CXX) -g -c $< -Iinclude
	
warehouse.o : src/warehouse/warehouse.cpp
	$(CXX) -g -c $< -Iinclude
	
warehouse_operator.o : src/warehouse/warehouse_operator.cpp
	$(CXX) -g -c $< -Iinclude	
	
warehouse_communicate.o : src/warehouse/warehouse_communicate.cpp
	$(CXX) -g -c $< -Iinclude
	
reward_operator.o : src/reward/reward_operator.cpp
	$(CXX) -g -c $< -Iinclude
	
reward_communicate.o : src/reward/reward_communicate.cpp
	$(CXX) -g -c $< -Iinclude
	
reward_level_config.o : src/reward/reward_level_config.cpp
	$(CXX) -g -c $< -Iinclude	
	
reward_online_config.o : src/reward/reward_online_config.cpp
	$(CXX) -g -c $< -Iinclude	
	
reward_online.o : src/reward/reward_online.cpp
	$(CXX) -g -c $< -Iinclude	
	
guildBussiness.o : src/business/guildBussiness.cpp
	$(CXX) -g -c $< -Iinclude	
	
shengWang_bussiness.o : src/business/shengWang_bussiness.cpp
	$(CXX) -g -c $< -Iinclude	
	
GM.o : src/GM/GM.cpp
	$(CXX) -g -c $< -Iinclude	
	
GM_communicate.o : src/GM/GM_communicate.cpp
	$(CXX) -g -c $< -Iinclude			
		
festivalActive.o : src/festivalActive/festivalActive.cpp
	$(CXX) -g -c $< -Iinclude			
		
read_festival.o : src/festivalActive/read_festival.cpp
	$(CXX) -g -c $< -Iinclude -I /usr/local/include/libxml2/ -L /usr/local/include/lib/ -lxml2			
		
verify.o : src/verify.cpp
	$(CXX) -g -c $< -Iinclude			
	
midasTouch.o : src/model/midasTouch.cpp
	$(CXX) -g -c $< -Iinclude			
	
midasTouch_communicate.o : src/communication/midasTouch_communicate.cpp
	$(CXX) -g -c $< -Iinclude			
	
mysteriousBussiness_config.o : src/mysteriousBussiness/mysteriousBussiness_config.cpp
	$(CXX) -g -c $< -Iinclude -I /usr/local/include/libxml2/ -L /usr/local/include/lib/ -lxml2	
	
mysteriousBussiness.o : src/mysteriousBussiness/mysteriousBussiness.cpp
	$(CXX) -g -c $< -Iinclude 	
	
mysteriousBussiness_communicate.o : src/mysteriousBussiness/mysteriousBussiness_communicate.cpp
	$(CXX) -g -c $< -Iinclude 	
	
function_read_configuration_files_revival.o : src/read_configure/function_read_configuration_files_revival.cpp
	$(CXX) -g -c $< -Iinclude -I /usr/local/include/libxml2/ -L /usr/local/include/lib/ -lxml2	
	
revival_config.o: src/read_configure/revival_config.cpp
	$(CXX) -g -c $< -Iinclude	
	
function_read_configuration_files_reward_level.o : src/reward/function_read_configuration_files_reward_level.cpp
	$(CXX) -g -c $< -Iinclude -I /usr/local/include/libxml2/ -L /usr/local/include/lib/ -lxml2	
		
reward_recharge_config.o : src/reward/reward_recharge_config.cpp
	$(CXX) -g -c $< -Iinclude	
	
function_read_configuration_files_reward_recharge.o : src/reward/function_read_configuration_files_reward_recharge.cpp
	$(CXX) -g -c $< -Iinclude -I /usr/local/include/libxml2/ -L /usr/local/include/lib/ -lxml2	
	
function_read_configuration_files_reward_online.o : src/reward/function_read_configuration_files_reward_online.cpp
	$(CXX) -g -c $< -Iinclude -I /usr/local/include/libxml2/ -L /usr/local/include/lib/ -lxml2	
	
read_cdkey.o : src/read_configure/read_cdkey.cpp
	$(CXX) -g -c $< -Iinclude -I /usr/local/include/libxml2/ -L /usr/local/include/lib/ -lxml2	
	
read_everyDaySignReward.o : src/reward/read_everyDaySignReward.cpp
	$(CXX) -g -c $< -Iinclude -I /usr/local/include/libxml2/ -L /usr/local/include/lib/ -lxml2	
	
read_rank_reward.o : src/reward/read_rank_reward.cpp
	$(CXX) -g -c $< -Iinclude -I /usr/local/include/libxml2/ -L /usr/local/include/lib/ -lxml2	
	
#game_fight_heroVSone_manage_all.o : src/game_fight/fight_manage/game_fight_heroVSone_manage_all.cpp
#	$(CXX) -g -c $< -Iinclude	

#game_fight_heroVSone_manage_redlose_hero.o : src/game_fight/fight_manage/game_fight_heroVSone_manage_redlose_hero.cpp
#	$(CXX) -g -c $< -Iinclude	

#game_fight_heroVSone_manage_redlose_monster.o : src/game_fight/fight_manage/game_fight_heroVSone_manage_redlose_monster.cpp
#	$(CXX) -g -c $< -Iinclude	

#game_fight_help_manage_think.o : src/game_fight/fight_manage/game_fight_help_manage_think.cpp
#	$(CXX) -g -c $< -Iinclude	
	
#game_fight_help_status_attacker.o : src/game_fight/fight_manage/game_fight_help_status_attacker.cpp
#	$(CXX) -g -c $< -Iinclude	

#game_fight_help_status_hiter.o : src/game_fight/fight_manage/game_fight_help_status_hiter.cpp
#	$(CXX) -g -c $< -Iinclude	

#game_fight_help_redlose_manage.o : src/game_fight/fight_manage/game_fight_help_redlose_manage.cpp
#	$(CXX) -g -c $< -Iinclude	
	
#game_fight_help_find_object.o : src/game_fight/fight_manage/game_fight_help_find_object.cpp
#	$(CXX) -g -c $< -Iinclude

#game_fight_help_property_attackerAndhiter.o : src/game_fight/fight_manage/game_fight_help_property_attackerAndhiter.cpp
#	$(CXX) -g -c $< -Iinclude
	
#game_fight_help_sendmsg.o : src/game_fight/fight_manage/game_fight_help_sendmsg.cpp
#	$(CXX) -g -c $< -Iinclude	

#game_fight_heroVSmany_manage_all.o : src/game_fight/fight_manage/game_fight_heroVSmany_manage_all.cpp
#	$(CXX) -g -c $< -Iinclude	

#game_fight_heroVSmany_manage_attack.o : src/game_fight/fight_manage/game_fight_heroVSmany_manage_attack.cpp
#	$(CXX) -g -c $< -Iinclude	

#game_fight_heroVSmany_manage_redlose.o : src/game_fight/fight_manage/game_fight_heroVSmany_manage_redlose.cpp
#	$(CXX) -g -c $< -Iinclude	

#game_fight_heroVSmany_manage_treat.o : src/game_fight/fight_manage/game_fight_heroVSmany_manage_treat.cpp
#	$(CXX) -g -c $< -Iinclude	

#game_fight_heroVShimself_manage_all.o : src/game_fight/fight_manage/game_fight_heroVShimself_manage_all.cpp
#	$(CXX) -g -c $< -Iinclude	

#game_fight_heroVShimself_manage_hero.o : src/game_fight/fight_manage/game_fight_heroVShimself_manage_hero.cpp
#	$(CXX) -g -c $< -Iinclude	

#game_fight_heroVShimself_manage_drop.o : src/game_fight/fight_manage/game_fight_heroVShimself_manage_drop.cpp
#	$(CXX) -g -c $< -Iinclude	

game_fight_assist.o : src/game_fight/game_fight_assist.cpp
	$(CXX) -g -c -Iinclude $<	
	
dropGoods.o : src/hero_goods/dropGoods.cpp
	$(CXX) -g -c $< -Iinclude $<	
	
game_move.o : src/game_move/game_move.cpp
	$(CXX) -g -c $< -Iinclude

command_other_function_all_over.o : src/global/command_other_function_all_over.cpp
	$(CXX) -g -c $< -Iinclude
	
task_configuration.o : src/read_configure/task_configuration.cpp
	$(CXX) -g -c $< -Iinclude	

goods_config.o : src/read_configure/goods_config.cpp
	$(CXX) -g -c $< -Iinclude
	
task_touch_configuration.o : src/read_configure/task_touch_configuration.cpp
	$(CXX) -g -c $< -Iinclude
	
npc_configuration.o : src/read_configure/npc_configuration.cpp	
	$(CXX) -g -c $< -Iinclude	

skill_configuration.o : src/read_configure/skill_configuration.cpp
	$(CXX) -g -c $< -Iinclude
	
over_all_varity.o : src/global/over_all_varity.cpp
	$(CXX) -g -c $< -Iinclude -I /usr/local/include/libxml2/ -L /usr/local/include/lib/ -lxml2 -levent 

hero.o : src/model/hero.cpp 
	$(CXX) -g -c $< -Iinclude
	
fingerGuessingGame_communicate.o : src/communication/fingerGuessingGame_communicate.cpp 
	$(CXX) -g -c $< -Iinclude
	
hero_buff.o : src/model/hero_buff.cpp 
	$(CXX) -g -c $< -Iinclude	
	
hero_collect.o : src/model/hero_collect.cpp 
	$(CXX) -g -c $< -Iinclude	
	
nbox.o : src/model/nbox.cpp
	$(CXX) -g -c $< -Iinclude
	
skill.o : src/model/skill.cpp include/skill.h
	$(CXX) -g -c $< -Iinclude
	
role.o : src/model/role.cpp
	$(CXX) -g -c $< -Iinclude

npc.o : src/model/npc.cpp
	$(CXX) -g -c $< -Iinclude

task.o : src/model/task.cpp
	$(CXX) -g -c $< -Iinclude
	
equipment.o : src/model/equipment.cpp
	$(CXX) -g -c $< -Iinclude
	
pick.o:src/model/pick.cpp
	$(CXX) -g -c $< -Iinclude	
	
money.o:src/model/money.cpp
	$(CXX) -g -c $< -Iinclude	

money_operator.o:src/model/money_operator.cpp
	$(CXX) -g -c $< -Iinclude	

equip_config.o : src/read_configure/equip_config.cpp
	$(CXX) -g -c $< -Iinclude	

pet_config.o : src/read_configure/pet_config.cpp
	$(CXX) -g -c $< -Iinclude	
	
ointment.o : src/hero_drugs/ointment.cpp
	$(CXX) -g -c $< -Iinclude
	
ectype_reward_info.o : src/read_configure/ectype_reward_info.cpp
	$(CXX) -g -c $< -Iinclude

ectype_reward_set.o : src/read_configure/ectype_reward_set.cpp
	$(CXX) -g -c $< -Iinclude
	
read_ectype_reward_goods.o : src/read_configure/read_ectype_reward_goods.cpp
	$(CXX) -g -c $< -Iinclude -I /usr/local/include/libxml2 -lxml2

read_task_goods_info.o : src/read_configure/read_task_goods_info.cpp 
	$(CXX) -g -c $< -Iinclude -I /usr/local/include/libxml2/ -L /usr/local/include/lib/ -lxml2

read_main_config.o : src/read_configure/read_main_config.cpp
	$(CXX) -g -c $< -Iinclude -I /usr/local/include/libxml2/ -L /usr/local/include/lib/ -lxml2	

read_server_config.o : src/read_configure/read_server_config.cpp
	$(CXX) -g -c $< -Iinclude -I /usr/local/include/libxml2/ -L /usr/local/include/lib/ -lxml2	
	
parseTowerDefence.o : src/read_configure/parseTowerDefence.cpp
	$(CXX) -g -c $< -Iinclude -I /usr/local/include/libxml2/ -lxml2	
	
read_files_ointment.o : src/read_configure/read_files_ointment.cpp
	$(CXX) -g -c $< -Iinclude -I /usr/local/include/libxml2/ -L /usr/local/include/lib/ -lxml2

read_pet_range.o : src/read_configure/read_pet_range.cpp
	$(CXX) -g -c $< -Iinclude -I /usr/local/include/libxml2/ -L /usr/local/include/lib/ -lxml2

read_ectype_reward_info.o : src/read_configure/read_ectype_reward_info.cpp
	$(CXX) -g -c $< -Iinclude -I /usr/local/include/libxml2/ -L /usr/local/include/lib/ -lxml2
	
read_scene_config.o : src/read_configure/read_scene_config.cpp
	$(CXX) -g -c $< -Iinclude -I /usr/local/include/libxml2/ -L /usr/local/include/lib/ -lxml2	
	
function_read_configuration_files_droplist.o :	src/read_configure/function_read_configuration_files_droplist.cpp
	$(CXX) -g -c $< -Iinclude -I /usr/local/include/libxml2/ -L /usr/local/include/lib/ -lxml2

function_read_configuration_files_exp.o : src/read_configure/function_read_configuration_files_exp.cpp
	$(CXX) -g -c $< -Iinclude -I /usr/local/include/libxml2/ -L /usr/local/include/lib/ -lxml2
	
function_read_configuration_files_map.o : src/read_configure/function_read_configuration_files_map.cpp
	$(CXX) -g -c $< -Iinclude -I /usr/local/include/libxml2/ -L /usr/local/include/lib/ -lxml2

function_read_configuration_files_monster.o : src/read_configure/function_read_configuration_files_monster.cpp
	$(CXX) -g -c $< -Iinclude -I /usr/local/include/libxml2/ -L /usr/local/include/lib/ -lxml2

function_read_configuration_files_skill.o : src/read_configure/function_read_configuration_files_skill.cpp
	$(CXX) -g -c $< -Iinclude -I /usr/local/include/libxml2/ -L /usr/local/include/lib/ -lxml2
	
function_read_configuration_files_five.o : src/read_configure/function_read_configuration_files_five.cpp
	$(CXX) -g -c $< -Iinclude -I /usr/local/include/libxml2/ -L /usr/local/include/lib/ -lxml2	

function_read_configuration_files_equip.o : src/read_configure/function_read_configuration_files_equip.cpp
	$(CXX) -g -c $< -Iinclude -I /usr/local/include/libxml2/ -L /usr/local/include/lib/ -lxml2	
	
function_read_configuration_files_goods.o : src/read_configure/function_read_configuration_files_goods.cpp
	$(CXX) -g -c $< -Iinclude -I /usr/local/include/libxml2/ -L /usr/local/include/lib/ -lxml2		
	
function_read_configuration_files_midasTouch.o : src/read_configure/function_read_configuration_files_midasTouch.cpp
	$(CXX) -g -c $< -Iinclude -I /usr/local/include/libxml2/ -L /usr/local/include/lib/ -lxml2		
	
function_read_configuration_files_mysteriousBussiness.o : src/read_configure/function_read_configuration_files_mysteriousBussiness.cpp
	$(CXX) -g -c $< -Iinclude -I /usr/local/include/libxml2/ -L /usr/local/include/lib/ -lxml2			
		
function_read_configuration_files_guildBussiness.o : src/read_configure/function_read_configuration_files_guildBussiness.cpp
	$(CXX) -g -c $< -Iinclude -I /usr/local/include/libxml2/ -L /usr/local/include/lib/ -lxml2			
	
function_read_configuration_files_shengWangBussiness.o : src/read_configure/function_read_configuration_files_shengWangBussiness.cpp
	$(CXX) -g -c $< -Iinclude -I /usr/local/include/libxml2/ -L /usr/local/include/lib/ -lxml2			
	
function_read_configuration_files_pet.o : src/read_configure/function_read_configuration_files_pet.cpp
	$(CXX) -g -c $< -Iinclude -I /usr/local/include/libxml2/ -L /usr/local/include/lib/ -lxml2	
	
function_read_configuration_files_jumpId.o : src/read_configure/function_read_configuration_files_jumpId.cpp
	$(CXX) -g -c $< -Iinclude -I /usr/local/include/libxml2/ -L /usr/local/include/lib/ -lxml2	

function_read_configuration_files_task.o : src/read_configure/function_read_configuration_files_task.cpp 
	$(CXX) -g -c $< -Iinclude -I /usr/local/include/libxml2/ -L /usr/local/include/lib/ -lxml2
	
function_read_configuration_files_touch.o : src/read_configure/function_read_configuration_files_touch.cpp 
	$(CXX) -g -c $< -Iinclude -I /usr/local/include/libxml2/ -L /usr/local/include/lib/ -lxml2
	
function_read_configuration_files_npc.o : src/read_configure/function_read_configuration_files_npc.cpp 
	$(CXX) -g -c $< -Iinclude -I /usr/local/include/libxml2/ -L /usr/local/include/lib/ -lxml2

function_read_configuration_files_petSkill.o : src/read_configure/function_read_configuration_files_petSkill.cpp 
	$(CXX) -g -c $< -Iinclude -I /usr/local/include/libxml2/ -L /usr/local/include/lib/ -lxml2

read_words.o : src/read_configure/read_words.cpp 
	$(CXX) -g -c $< -Iinclude -I /usr/local/include/libxml2/ -L /usr/local/include/lib/ -lxml2
	
read_equip_operator.o : src/read_configure/read_equip_operator.cpp 
	$(CXX) -g -c $< -Iinclude -I /usr/local/include/libxml2/ -L /usr/local/include/lib/ -lxml2
	
read_vip.o : src/read_configure/read_vip.cpp 
	$(CXX) -g -c $< -Iinclude -I /usr/local/include/libxml2/ -L /usr/local/include/lib/ -lxml2
	
read_factor_reward.o : src/read_configure/read_factor_reward.cpp 
	$(CXX) -g -c $< -Iinclude -I /usr/local/include/libxml2/ -L /usr/local/include/lib/ -lxml2
	
read_active_double.o : src/read_configure/read_active_double.cpp 
	$(CXX) -g -c $< -Iinclude -I /usr/local/include/libxml2/ -L /usr/local/include/lib/ -lxml2
	
hero_configuration.o : src/read_configure/hero_configuration.cpp
	$(CXX) -g -c $< -Iinclude
	
droplist_configuration.o : src/read_configure/droplist_configuration.cpp
	$(CXX) -g -c $< -Iinclude

read_heCheng_configure.o : src/read_configure/read_heCheng_configure.cpp
	$(CXX) -g -c $< -Iinclude -I /usr/local/include/libxml2/ -L /usr/local/include/lib/ -lxml2	
	
read_guild_reward.o : src/read_configure/read_guild_reward.cpp
	$(CXX) -g -c $< -Iinclude -I /usr/local/include/libxml2/ -L /usr/local/include/lib/ -lxml2	
	
read_hatValRue.o : src/read_configure/read_hatValRue.cpp
	$(CXX) -g -c $< -Iinclude -I /usr/local/include/libxml2/ -L /usr/local/include/lib/ -lxml2
	
monster_configuration.o : src/read_configure/monster_configuration.cpp
	$(CXX) -g -c $< -Iinclude

five_configuration.o : src/read_configure/five_configuration.cpp
	$(CXX) -g -c $< -Iinclude
	
role_manage_create_hero.o : src/user_role_manage/role_manage_create_hero.cpp
	$(CXX) -g -c $< -Iinclude
	
role_manage_delete_hero.o : src/user_role_manage/role_manage_delete_hero.cpp
	$(CXX) -g -c $< -Iinclude
	
role_manage_select_hero.o : src/user_role_manage/role_manage_select_hero.cpp
	$(CXX) -g -c $< -Iinclude

role_manage_change_scene.o : src/user_role_manage/role_manage_change_scene.cpp
	$(CXX) -g -c $< -Iinclude

hero_revival.o : src/user_role_manage/hero_revival.cpp
	$(CXX) -g -c $< -Iinclude

sitControl.o : src/user_role_manage/sitControl.cpp
	$(CXX) -g -c $< -Iinclude

user_role_manage_assist.o : src/user_role_manage/user_role_manage_assist.cpp
	$(CXX) -g -c $< -Iinclude

exit_exception.o : src/user_role_manage/exit_exception.cpp
	$(CXX) -g -c $< -Iinclude

exit_normal.o : src/user_role_manage/exit_normal.cpp
	$(CXX) -g -c $< -Iinclude

user_manage_login.o : src/user_role_manage/user_manage_login.cpp
	$(CXX) -g -c $< -Iinclude

login_from_web.o : src/user_role_manage/login_from_web.cpp
	$(CXX) -g -c $< -Iinclude
	
time_poll.o : src/game_move/time_poll.cpp
	$(CXX) -g -c $< -Iinclude 

md5.o : src/md5.cpp
	$(CXX) -g -c $< -Iinclude -fpermissive

libev.o : src/libev.cpp
	$(CXX) -g -c $< -Iinclude
	
read_ride.o : src/ride/read_ride.cpp 
	$(CXX) -g -c $< -Iinclude -I /usr/local/include/libxml2/ -L /usr/local/include/lib/ -lxml2

read_ride_skill.o : src/ride/read_ride_skill.cpp 
	$(CXX) -g -c $< -Iinclude -I /usr/local/include/libxml2/ -L /usr/local/include/lib/ -lxml2

read_specialSkill.o : src/ride/read_specialSkill.cpp 
	$(CXX) -g -c $< -Iinclude -I /usr/local/include/libxml2/ -L /usr/local/include/lib/ -lxml2

ride.o:src/ride/ride.cpp
	$(CXX) -g -c $< -Iinclude

ride_operator.o:src/ride/ride_operator.cpp
	$(CXX) -g -c $< -Iinclude

ride_config.o :	src/ride/ride_config.cpp
	$(CXX) -g -c $< -Iinclude -I /usr/local/include/libxml2/ -L /usr/local/include/lib/ -lxml2
	
monsterBase.o:src/monsterInst/monsterBase.cpp
	$(CXX) -g -c $< -Iinclude

monsterPassivity.o:src/monsterInst/monsterPassivity.cpp
	$(CXX) -g -c $< -Iinclude

monsterActive.o:src/monsterInst/monsterActive.cpp
	$(CXX) -g -c $< -Iinclude

monsterPatrol.o:src/monsterInst/monsterPatrol.cpp
	$(CXX) -g -c $< -Iinclude

monsterTowerDefence.o : src/monsterInst/monsterTowerDefence.cpp
	$(CXX) -g -c $< -Iinclude

monThkFun.o : src/monThkFun.cpp
	$(CXX) -g -c $< -Iinclude

hatValRue.o : src/read_configure/hatValRue.cpp
	$(CXX) -g -c $< -Iinclude

mapAction.o : src/mapAction.cpp
	$(CXX) -g -c $< -Iinclude

bruMonInfor.o : src/bruMonBag/bruMonInfor.cpp
	$(CXX) -g -c $< -Iinclude	
	
cpy.o : src/cpyManage/cpy.cpp
	$(CXX) -g -c $< -Iinclude

read_cpy.o : src/read_configure/read_cpy.cpp
	$(CXX) -g -c $< -Iinclude -I /usr/local/include/libxml2/ -L /usr/local/include/lib/ -lxml2
	
#manage_beidong.o : src/hero_skill/manage_beidong.cpp
#	$(CXX) -g -c $< -Iinclude	

#hero_help.o : src/model/hero_help.cpp
#	$(CXX) -g -c $< -Iinclude		

read_cpyLimit.o : src/read_configure/read_cpyLimit.cpp
	$(CXX) -g -c $< -Iinclude -I /usr/local/include/libxml2/ -L /usr/local/include/lib/ -lxml2
	
cpyLimit.o : src/cpyManage/cpyLimit.cpp
	$(CXX) -g -c $< -Iinclude

TD_Instancing.o : src/instancing/TD_Instancing.cpp
	$(CXX) -g -c $< -Iinclude

instancing_manage.o : src/instancing/instancing_manage.cpp
	$(CXX) -g -c $< -Iinclude

instancing_communication.o : src/instancing/instancing_communication.cpp
	$(CXX) -g -c $< -Iinclude
		
hero_need_experience.o : src/hero_GrowUp/hero_need_experience.cpp
	$(CXX) -g -c $< -Iinclude
	
#manage_all_skill_upgrade.o : src/hero_skill/manage_all_skill_upgrade.cpp
#	$(CXX) -g -c $< -Iinclude	
	
#manage_beidong_upgrade.o : src/hero_skill/manage_beidong_upgrade.cpp
#	$(CXX) -g -c $< -Iinclude	
	
#manage_buff_upgrade.o : src/hero_skill/manage_buff_upgrade.cpp
#	$(CXX) -g -c $< -Iinclude	
	
#manage_yiliao_upgrade.o : src/hero_skill/manage_yiliao_upgrade.cpp
#	$(CXX) -g -c $< -Iinclude	
	
#manage_zhudong_upgrade.o : src/hero_skill/manage_zhudong_upgrade.cpp
#	$(CXX) -g -c $< -Iinclude	

#manage_all_skill_update_help.o : src/hero_skill/manage_all_skill_update_help.cpp
#	$(CXX) -g -c $< -Iinclude
	
entCpy.o : src/cpyManage/entCpy.cpp
	$(CXX) -g -c $< -Iinclude
	
entCpyNextMap.o : src/cpyManage/entCpyNextMap.cpp
	$(CXX) -g -c $< -Iinclude
	
exitCpy.o : src/cpyManage/exitCpy.cpp
	$(CXX) -g -c $< -Iinclude

cpyAsist.o : src/cpyManage/cpyAsist.cpp
	$(CXX) -g -c $< -Iinclude	
	
groupBrush.o : 	src/model/groupBrush.cpp
	$(CXX) -g -c $< -Iinclude
	
read_groupBrush.o : src/read_configure/read_groupBrush.cpp
	$(CXX) -g -c $< -Iinclude -I /usr/local/include/libxml2/ -L /usr/local/include/lib/ -lxml2
	
read_monster_skill.o : src/read_configure/read_monster_skill.cpp
	$(CXX) -g -c $< -Iinclude -I /usr/local/include/libxml2/ -L /usr/local/include/lib/ -lxml2
	
skillBase.o : src/monsterSkill/skillBase.cpp
	$(CXX) -g -c $< -Iinclude
	
rigidity.o : src/monsterSkill/rigidity.cpp
	$(CXX) -g -c $< -Iinclude
	
recoverBlood.o : src/monsterSkill/recoverBlood.cpp
	$(CXX) -g -c $< -Iinclude
	
bossSkiRig.o : src/bossSkiRig.cpp
	$(CXX) -g -c $< -Iinclude
	
five_elements.o : src/model/five_elements.cpp
	$(CXX) -g -c $< -Iinclude
	
five_asist.o : src/model/five_asist.cpp
	$(CXX) -g -c $< -Iinclude

five_elem_comm.o : src/communication/five_elem_comm.cpp
	$(CXX) -g -c $< -Iinclude
	
meridian.o : src/model/meridian.cpp
	$(CXX) -g -c $< -Iinclude
	
meridian_asist.o : src/model/meridian_asist.cpp
	$(CXX) -g -c $< -Iinclude

meridian_comm.o : src/communication/meridian_comm.cpp
	$(CXX) -g -c $< -Iinclude
	
internal_forces_manage.o : src/internal_forces/internal_forces_manage.cpp
	$(CXX) -g -c $< -Iinclude
	
internal_forces_comm.o : src/internal_forces/internal_forces_comm.cpp
	$(CXX) -g -c $< -Iinclude
	
read_internal_forces.o : src/read_configure/read_internal_forces.cpp
	$(CXX) -g -c $< -Iinclude -I /usr/local/include/libxml2/ -L /usr/local/include/lib/ -lxml2
	
read_global.o : src/read_configure/read_global.cpp
	$(CXX) -g -c $< -Iinclude -I /usr/local/include/libxml2/ -L /usr/local/include/lib/ -lxml2

user_attr_apply.o : src/communication/user_attr_apply.cpp
	$(CXX) -g -c $< -Iinclude

kaiRen.o : src/hero_equip/kaiRen.cpp
	$(CXX) -g -c $< -Iinclude

yiZhi.o : src/hero_equip/yiZhi.cpp
	$(CXX) -g -c $< -Iinclude

rongLian.o : src/hero_equip/rongLian.cpp
	$(CXX) -g -c $< -Iinclude

heCheng.o : src/hero_equip/heCheng.cpp
	$(CXX) -g -c $< -Iinclude
	
xiangQian.o : src/hero_equip/xiangQian.cpp
	$(CXX) -g -c $< -Iinclude

zhaiQu.o : src/hero_equip/zhaiQu.cpp
	$(CXX) -g -c $< -Iinclude
	
equip_hero_manage_wear.o : src/hero_equip/equip_hero_manage_wear.cpp
	$(CXX) -g -c $< -Iinclude		

equip_hero_manage_takeoff.o : src/hero_equip/equip_hero_manage_takeoff.cpp
	$(CXX) -g -c $< -Iinclude		
		
hero_equip_operate_require.o : src/hero_equip/hero_equip_operate_require.cpp
	$(CXX) -g -c $< -Iinclude	
	
hero_equip_operate_clientinfo.o : src/hero_equip/hero_equip_operate_clientinfo.cpp
	$(CXX) -g -c $< -Iinclude	
	
hero_equip_change_help.o : src/hero_equip/equip_help/hero_equip_change_help.cpp
	$(CXX) -g -c $< -Iinclude	
	
action.o : src/model/action.cpp	
	$(CXX) -g -c $< -Iinclude
	
unEnemy.o : src/monsterSkill/unEnemy.cpp
	$(CXX) -g -c $< -Iinclude
	
bruType.o : src/bruMonBag/bruType.cpp
	$(CXX) -g -c $< -Iinclude

guild.o : src/guild/guild.cpp	
	$(CXX) -g -c $< -Iinclude

guild_asist.o : src/guild/guild_asist.cpp	
	$(CXX) -g -c $< -Iinclude

guild_comm.o : src/guild/guild_comm.cpp	
	$(CXX) -g -c $< -Iinclude
	
guild_war_room.o : src/guild/guild_war_room.cpp	
	$(CXX) -g -c $< -Iinclude
	
guild_war_asist.o : src/guild/guild_war_asist.cpp	
	$(CXX) -g -c $< -Iinclude
	
guild_war_comm.o : src/guild/guild_war_comm.cpp	
	$(CXX) -g -c $< -Iinclude	

rob_flag_war.o : src/guild/rob_flag_war.cpp	
	$(CXX) -g -c $< -Iinclude

rob_flag_war_logic.o : src/guild/rob_flag_war_logic.cpp	
	$(CXX) -g -c $< -Iinclude
	
rob_flag_war_comm.o : src/guild/rob_flag_war_comm.cpp	
	$(CXX) -g -c $< -Iinclude
	
camp_leader_and_chief.o : src/guild/camp_leader_and_chief.cpp	
	$(CXX) -g -c $< -Iinclude	
	
guild_activity.o : src/guild/guild_activity.cpp	
	$(CXX) -g -c $< -Iinclude

read_guild_activity.o : src/guild/read_guild_activity.cpp
	$(CXX) -g -c $< -Iinclude -I /usr/local/include/libxml2/ -L /usr/local/include/lib/ -lxml2

read_guild_feast.o : src/guild/read_guild_feast.cpp
	$(CXX) -g -c $< -Iinclude -I /usr/local/include/libxml2/ -L /usr/local/include/lib/ -lxml2

guild_club.o : src/guild/guild_club.cpp	
	$(CXX) -g -c $< -Iinclude

guild_club_assist.o : src/guild/guild_club_assist.cpp	
	$(CXX) -g -c $< -Iinclude
	
read_cycle_limit.o : src/hero_task/read_cycle_limit.cpp
	$(CXX) -g -c $< -Iinclude -I /usr/local/include/libxml2/ -L /usr/local/include/lib/ -lxml2
	
read_cycle_task_reward.o : src/hero_task/read_cycle_task_reward.cpp
	$(CXX) -g -c $< -Iinclude -I /usr/local/include/libxml2/ -L /usr/local/include/lib/ -lxml2
	
hero_skill.o : src/new_game_fight/skill/hero_skill.cpp
	$(CXX) -g -c $< -Iinclude

upgrade_hero_skill.o : src/new_game_fight/skill/upgrade_hero_skill.cpp
	$(CXX) -g -c $< -Iinclude

read_hero_skill.o : src/new_game_fight/skill/read_hero_skill.cpp
	$(CXX) -g -c $< -Iinclude -I /usr/local/include/libxml2/ -L /usr/local/include/lib/	

read_fight_const_value.o : src/read_configure/read_fight_const_value.cpp
	$(CXX) -g -c $< -Iinclude -I /usr/local/include/libxml2/ -L /usr/local/include/lib/	

read_hero_conf.o : src/read_configure/read_hero_conf.cpp
	$(CXX) -g -c $< -Iinclude -I /usr/local/include/libxml2/ -L /usr/local/include/lib/	

basis_cal.o : src/new_game_fight/fight/basis_cal.cpp
	$(CXX) -g -c $< -Iinclude

fight_val_cal.o : src/new_game_fight/fight/fight_val_cal.cpp
	$(CXX) -g -c $< -Iinclude

proc_lose_life.o : src/new_game_fight/fight/proc_lose_life.cpp
	$(CXX) -g -c $< -Iinclude

hero_skill_deal.o : src/new_game_fight/fight/hero_skill_deal.cpp
	$(CXX) -g -c $< -Iinclude

proc_use_skill.o : src/new_game_fight/fight/proc_use_skill.cpp
	$(CXX) -g -c $< -Iinclude
	
upgrade_hero_skill_comm.o : src/new_game_fight/comm/upgrade_hero_skill_comm.cpp
	$(CXX) -g -c $< -Iinclude

use_skill_comm.o : src/new_game_fight/comm/use_skill_comm.cpp
	$(CXX) -g -c $< -Iinclude
	
suit.o : src/model/suit.cpp
	$(CXX) -g -c $< -Iinclude

function_read_configuration_files_suit.o : src/read_configure/function_read_configuration_files_suit.cpp
	$(CXX) -g -c $< -Iinclude -I /usr/local/include/libxml2/ -L /usr/local/include/lib/ -lxml2
	
takeGoods.o : src/otherGoods/takeGoods.cpp	
	$(CXX) -g -c $< -Iinclude
	
read_take_goods.o : src/read_configure/read_take_goods.cpp
	$(CXX) -g -c $< -Iinclude -I /usr/local/include/libxml2/ -L /usr/local/include/lib/ -lxml2
	
wagon.o : src/otherGoods/wagon.cpp	
	$(CXX) -g -c $< -Iinclude	

read_wagon.o : src/read_configure/read_wagon.cpp
	$(CXX) -g -c $< -Iinclude -I /usr/local/include/libxml2/ -L /usr/local/include/lib/ -lxml2
	
attack_wagon.o : src/hero_task/attack_wagon.cpp
	$(CXX) -g -c $< -Iinclude
	
task_failed_comm.o : src/hero_task/task_failed_comm.cpp
	$(CXX) -g -c $< -Iinclude
	
bottle.o : src/otherGoods/bottle.cpp	
	$(CXX) -g -c $< -Iinclude	

read_bottle.o : src/read_configure/read_bottle.cpp
	$(CXX) -g -c $< -Iinclude -I /usr/local/include/libxml2/ -L /usr/local/include/lib/ -lxml2

trap.o : src/otherGoods/trap.cpp	
	$(CXX) -g -c $< -Iinclude	

read_trap.o : src/read_configure/read_trap.cpp
	$(CXX) -g -c $< -Iinclude -I /usr/local/include/libxml2/ -L /usr/local/include/lib/ -lxml2
	
my_memcached.o : src/memcached/my_memcached.cpp
	$(CXX) -g -c $< -Iinclude -lmemcached
	
monsterPasstrol.o : src/monsterInst/monsterPasstrol.cpp	
	$(CXX) -g -c $< -Iinclude
	
mailSysterm.o : src/mail_systerm/mailSysterm.cpp
	$(CXX) -g -c $< -Iinclude
	
mail_systerm_interface.o : src/mail_systerm/mail_systerm_interface.cpp
	$(CXX) -g -c $< -Iinclude
	
heroCpyRecord.o : src/cpyManage/heroCpyRecord.cpp
	$(CXX) -g -c $< -Iinclude
	
mail_systerm_communicate.o : src/mail_systerm/mail_systerm_communicate.cpp
	$(CXX) -g -c $< -Iinclude

map_inform.o : src/mapInformation/map_inform.cpp
	$(CXX) -g -c $< -Iinclude
	
map_cpy.o : src/mapInformation/map_cpy.cpp
	$(CXX) -g -c $< -Iinclude

map_src.o : src/mapInformation/map_src.cpp
	$(CXX) -g -c $< -Iinclude

user_role_manage_status.o : src/user_role_manage/user_role_manage_status.cpp
	$(CXX) -g -c $< -Iinclude
	
deal_offline_unhandle_event.o : src/mail_systerm/deal_offline_unhandle_event.cpp
	$(CXX) -g -c $< -Iinclude
	
wagonAction.o : src/wagonAction.cpp
	$(CXX) -g -c $< -Iinclude

my_time.o : src/model/my_time.cpp
	$(CXX) -g -c $< -Iinclude

my_timer.o : src/model/my_timer.cpp
	$(CXX) -g -c $< -Iinclude
	
read_dirty_words.o : src/read_configure/read_dirty_words.cpp
	$(CXX) -g -c $< -Iinclude -I /usr/local/include/libxml2/ -L /usr/local/include/lib/ -lxml2
	
read_happy_map.o : src/read_configure/read_happy_map.cpp
	$(CXX) -g -c $< -Iinclude -I /usr/local/include/libxml2/ -L /usr/local/include/lib/ -lxml2

read_guild_skill.o : src/read_configure/read_guild_skill.cpp
	$(CXX) -g -c $< -Iinclude -I /usr/local/include/libxml2/ -L /usr/local/include/lib/ -lxml2

dictionary.o : src/dictionary.cpp
	$(CXX) -g -c $< -Iinclude

dictionary_asist.o : src/dictionary_asist.cpp
	$(CXX) -g -c $< -Iinclude

#acceptSkillMsg.o : src/game_fight/fight_manage/acceptSkillMsg.cpp
#	$(CXX) -g -c $< -Iinclude

enterScenResponse.o : src/enterScenResponse.cpp
	$(CXX) -g -c $< -Iinclude
	
enterCpyByTool.o : src/cpyManage/enterCpyByTool.cpp
	$(CXX) -g -c $< -Iinclude

monsterActiveBoss.o : src/monsterInst/monsterActiveBoss.cpp
	$(CXX) -g -c $< -Iinclude
	
read_monsterActiveBoss.o : src/read_configure/read_monsterActiveBoss.cpp
	$(CXX) -g -c $< -Iinclude -I /usr/local/include/libxml2/ -L /usr/local/include/lib/ -lxml2
	
dailyActive.o : src/model/dailyActive.cpp 
	$(CXX) -g -c $< -Iinclude
	
read_dailyActive.o : src/read_configure/read_dailyActive.cpp
	$(CXX) -g -c $< -Iinclude -I /usr/local/include/libxml2/ -L /usr/local/include/lib/ 
	
takePartActive.o : src/activeCommunicate/takePartActive.cpp
	$(CXX) -g -c $< -Iinclude
	
activeAsist.o : src/activeCommunicate/activeAsist.cpp
	$(CXX) -g -c $< -Iinclude

wagon_rank.o : src/wagon_rank.cpp
	$(CXX) -g -c $< -Iinclude
	
read_cpyPassOlder.o : src/read_configure/read_cpyPassOlder.cpp
	$(CXX) -g -c $< -Iinclude -I /usr/local/include/libxml2/ -L /usr/local/include/lib/ 

boxAsist.o : src/model/boxAsist.cpp
	$(CXX) -g -c $< -Iinclude

hero_drugs_manage.o : src/hero_drugs/hero_drugs_manage.cpp
	$(CXX) -g -c $< -Iinclude
	
read_rsa_key.o : src/user_role_manage/read_rsa_key.cpp
	$(CXX) -g -c $< -Iinclude
	
panelResponse.o : src/panelResponse.cpp	
	$(CXX) -g -c $< -Iinclude

cpyManager.o : src/cpyManage/cpyManager.cpp
	$(CXX) -g -c $< -Iinclude

move_calbak.o : src/move_calbak.cpp
	$(CXX) -g -c $< -Iinclude

dropEquipAction.o : src/dropEquipAction.cpp
	$(CXX) -g -c $< -Iinclude

read_buff_debuff.o : src/read_configure/read_buff_debuff.cpp
	$(CXX) -g -c $< -Iinclude -I /usr/local/include/libxml2/ -L /usr/local/include/lib/ 


monsterCamp.o : src/monsterInst/monsterCamp.cpp
	$(CXX) -g -c $< -Iinclude

read_tool_brush_monster.o : src/read_configure/read_tool_brush_monster.cpp
	$(CXX) -g -c $< -Iinclude -I /usr/local/include/libxml2/ -L /usr/local/include/lib/ 

monsterTool.o : src/monsterInst/monsterTool.cpp
	$(CXX) -g -c $< -Iinclude
	
attackBottle.o : src/attackBottle.cpp
	$(CXX) -g -c $< -Iinclude
	
vipBaleRoomLimit.o : src/cpyManage/vipBaleRoomLimit.cpp
	$(CXX) -g -c $< -Iinclude
	
read_vip_bale_room.o : src/read_configure/read_vip_bale_room.cpp
	$(CXX) -g -c $< -Iinclude -I /usr/local/include/libxml2/ -L /usr/local/include/lib/	
	
enterVipBaleRoom.o : src/cpyManage/enterVipBaleRoom.cpp
	$(CXX) -g -c $< -Iinclude
	
exitVipBaleRoom.o : src/cpyManage/exitVipBaleRoom.cpp
	$(CXX) -g -c $< -Iinclude
	
monsterAttRed.o : src/monsterInst/monsterAttRed.cpp
	$(CXX) -g -c $< -Iinclude
	
botThkCalBack.o : src/botThkCalBack.cpp
	$(CXX) -g -c $< -Iinclude

partyRoomLimit.o : src/cpyManage/partyRoomLimit.cpp
	$(CXX) -g -c $< -Iinclude
	
read_partyRoom.o : src/read_configure/read_partyRoom.cpp
	$(CXX) -g -c $< -Iinclude -I /usr/local/include/libxml2/ -L /usr/local/include/lib/	
	
monsterEscape.o : src/monsterInst/monsterEscape.cpp
	$(CXX) -g -c $< -Iinclude

showPartyLunch.o : src/cpyManage/showPartyLunch.cpp
	$(CXX) -g -c $< -Iinclude
	
read_cpyNpc_pt.o : src/read_configure/read_cpyNpc_pt.cpp
	$(CXX) -g -c $< -Iinclude -I /usr/local/include/libxml2/ -L /usr/local/include/lib/	
	
read_party_base_camp.o : src/read_configure/read_party_base_camp.cpp
	$(CXX) -g -c $< -Iinclude -I /usr/local/include/libxml2/ -L /usr/local/include/lib/	

read_merid_conf.o : src/read_configure/read_merid_conf.cpp
	$(CXX) -g -c $< -Iinclude -I /usr/local/include/libxml2/ -L /usr/local/include/lib/	
	
read_five_elem_conf.o : src/read_configure/read_five_elem_conf.cpp
	$(CXX) -g -c $< -Iinclude -I /usr/local/include/libxml2/ -L /usr/local/include/lib/	

partyBaseCampLimit.o : src/cpyManage/partyBaseCampLimit.cpp
	$(CXX) -g -c $< -Iinclude
	
enterPartyCamp.o : src/cpyManage/enterPartyCamp.cpp
	$(CXX) -g -c $< -Iinclude 	

read_outer_active_code.o : src/read_configure/read_outer_active_code.cpp
	$(CXX) -g -c $< -Iinclude -I /usr/local/include/libxml2/ -L /usr/local/include/lib/	

read_inner_active_code.o : src/read_configure/read_inner_active_code.cpp
	$(CXX) -g -c $< -Iinclude -I /usr/local/include/libxml2/ -L /usr/local/include/lib/	
	
acceptActiveCode.o : src/activeCommunicate/acceptActiveCode.cpp
	$(CXX) -g -c $< -Iinclude 

fire_pao_zhu.o : src/time_limit_events/fire_pao_zhu.cpp
	$(CXX) -g -c $< -Iinclude 

monsterByHero.o : src/monsterInst/monsterByHero.cpp
	$(CXX) -g -c $< -Iinclude

hero_ride.o : src/model/hero_ride.cpp 
	$(CXX) -g -c $< -Iinclude

ride_comm.o : src/ride/ride_comm.cpp 
	$(CXX) -g -c $< -Iinclude
	
statuaryBase.o : src/model/statuaryBase.cpp
	$(CXX) -g -c $< -Iinclude 
	
read_statuaryBase.o : src/read_configure/read_statuaryBase.cpp
	$(CXX) -g -c $< -Iinclude -I /usr/local/include/libxml2/ -L /usr/local/include/lib/

statuaryHero.o : src/model/statuaryHero.cpp
	$(CXX) -g -c $< -Iinclude 
	
statuaryAsist.o : src/statuaryCommunicate/statuaryAsist.cpp
	$(CXX) -g -c $< -Iinclude 

camp_res_war.o : src/campWar/camp_res_war.cpp
	$(CXX) -g -c $< -Iinclude 

read_guild_war_control.o : src/read_configure/read_guild_war_control.cpp	
	$(CXX) -g -c $< -Iinclude -I /usr/local/include/libxml2/ -L /usr/local/include/lib/ -lxml2

read_rob_flag_war_control.o : src/read_configure/read_rob_flag_war_control.cpp	
	$(CXX) -g -c $< -Iinclude -I /usr/local/include/libxml2/ -L /usr/local/include/lib/ -lxml2

read_camp_res_war_control.o : src/read_configure/read_camp_res_war_control.cpp	
	$(CXX) -g -c $< -Iinclude -I /usr/local/include/libxml2/ -L /usr/local/include/lib/ -lxml2

read_mem_group_config.o : src/read_configure/read_mem_group_config.cpp	
	$(CXX) -g -c $< -Iinclude -I /usr/local/include/libxml2/ -L /usr/local/include/lib/ -lxml2

my_mem_group.o : src/memcached/my_mem_group.cpp
	$(CXX) -g -c $< -Iinclude
	
monsterStatuary.o : src/monsterInst/monsterStatuary.cpp
	$(CXX) -g -c $< -Iinclude
	
test.o : src/test.cpp
	$(CXX) -g -c $< -Iinclude

towerLayerRecord.o : src/cpyManage/towerLayerRecord.cpp
	$(CXX) -g -c $< -Iinclude 
	
read_blackMargin.o : src/read_configure/read_blackMargin.cpp
	$(CXX) -g -c $< -Iinclude -I /usr/local/include/libxml2/ -L /usr/local/include/lib/ -lxml2

enterTowerLayerCopy.o : src/cpyManage/enterTowerLayerCopy.cpp
	$(CXX) -g -c $< -Iinclude
	
purchaseFatigue.o : src/communication/purchaseFatigue.cpp
	$(CXX) -g -c $< -Iinclude
	
swapTowerLayerCopy.o : src/cpyManage/swapTowerLayerCopy.cpp
	$(CXX) -g -c $< -Iinclude 

brushTower.o : src/cpyManage/brushTower.cpp
	$(CXX) -g -c $< -Iinclude 
	
monCallSkill.o : src/monsterSkill/monCallSkill.cpp
	$(CXX) -g -c $< -Iinclude 

chatGroup.o : src/model/chatGroup.cpp
	$(CXX) -g -c $< -Iinclude 

chatGroupManager.o : src/model/chatGroupManager.cpp
	$(CXX) -g -c $< -Iinclude 

monsterStill.o : src/monsterInst/monsterStill.cpp
	$(CXX) -g -c $< -Iinclude 
	
team.o : src/teamOperator/team.cpp
	$(CXX) -g -c $< -Iinclude
	
teamManager.o : src/teamOperator/teamManager.cpp
	$(CXX) -g -c $< -Iinclude 
	
teamOperator.o : src/teamOperator/teamOperator.cpp
	$(CXX) -g -c $< -Iinclude 
	
teamAsist.o : src/teamOperator/teamAsist.cpp
	$(CXX) -g -c $< -Iinclude 
clean:
	$(DEL_FILE) $(object) bin/wsd
