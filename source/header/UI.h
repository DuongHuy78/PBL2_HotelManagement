#ifndef UI_H
#define UI_H
#include "gnk_2D.h"
#include "QLKhachSan.h"
enum frame_num_value {
	DEFAULT_FRAME,
	GUEST_FRAME,
	LOGIN_FRAME,
	FORGOT_PASSWORD_FRAME,
	SIGN_UP_FRAME,
	STAFF_FRAME,
	ADMIN_FRAME,
};

enum option_value {
	DEFAULT_OPTION,
	SEARCH_ROOM,
	HISTORY_INFORMATION,
	PROFILE,
	BOOKING,
	BOOKING_PART_2,
	BOOKING_DONE,
	
	STAFF_BOOKING_INFO,
	STAFF_GUEST_INFO,
	STAFF_TYPE_ROOM_INFO,
	STAFF_ROOM_INFO,
	STAFF_CREATE_GUEST,
	STAFF_CREATE_GUEST_DONE,

	ADMIN_MAIN,
	
	ADMIN_TYPE_ROOM_MANAGEMENT,
	ADMIN_ROOM_MANAGEMENT,
	ADMIN_REVENUE_MANAGEMENT,

	ADMIN_TYPE_ROOM_VIEW_AND_EDIT,
	ADMIN_TYPE_ROOM_EDIT,
	ADMIN_ADD_TYPE_ROOM,
	ADMIN_REMOVE_TYPE_ROOM,

	ADMIN_ROOM_VIEW_AND_EDIT,
	ADMIN_ROOM_EDIT,
	ADMIN_ADD_ROOM,
	ADMIN_REMOVE_ROOM,

	ADMIN_DAILY_REVENUE,
	ADMIN_MONTHLY_REVENUE,
	ADMIN_YEARLY_REVENUE,


	ADMIN_TYPE_ROOM_EDIT_DONE,
	ADMIN_TYPE_ROOM_ADD_DONE,
	ADMIN_TYPE_ROOM_REMOVE_DONE,

	ADMIN_ROOM_EDIT_DONE,
	ADMIN_ROOM_ADD_DONE,
	ADMIN_ROOM_REMOVE_DONE,
};
class QLKhachSan;
extern QLKhachSan *current_Data;
extern frame_num_value current_frame;
extern frame_num_value previous_frame;
extern bool login_failed;
extern bool blank_info;
extern bool username_existed;
extern bool male_toggle_enable;
extern bool female_toggle_enable;
// ---------------------------------------------------------
void button_hover_type_1(Gnk_Button*);
void button_hover_type_2(Gnk_Button*);
void textbox_select_type1(Gnk_Textbox*);
void textbox_select_type2(Gnk_Textbox*);
// ---------------------------------------------------------
void login_frame_draw(Gnk_Frame *);
void login_frame_login_button_click(Gnk_Button*);
void login_frame_forgotten_password_button_click(Gnk_Button*);
void login_frame_sign_up_button_click(Gnk_Button*);
extern Gnk_Frame login;
// ---------------------------------------------------------
void sign_up_frame_draw(Gnk_Frame *);
void sign_up_frame_to_login_button_click(Gnk_Button*);
void sign_up_frame_sign_up_button_click(Gnk_Button*);
void sign_up_frame_toggle_click(Gnk_Button*);
extern Gnk_Frame sign_up;
// ---------------------------------------------------------
void guest_frame_draw(Gnk_Frame *) ;
void logout_button_click(Gnk_Button *);
void guest_frame_search_room_button_click(Gnk_Button *);
void guest_frame_booking_infomation_button_click(Gnk_Button *);
void guest_frame_profile_button_click(Gnk_Button *);
void guest_frame_search_room_list_process(Gnk_List_Object *);
void guest_frame_lookup_button_image_click(Gnk_Button *);
void guest_frame_change_frofile_button_click(Gnk_Button *);
void guest_frame_save_profile_button_click(Gnk_Button *);
void guest_frame_select_type_room_button_click(Gnk_Button *);
void guest_frame_back_to_search_room_button_click(Gnk_Button *);
void guest_frame_continue_booking_button_click(Gnk_Button *);
void guest_frame_confirm_booking_button_click(Gnk_Button *);
void guest_frame_history_list_process(Gnk_List_Object *);
extern Gnk_Frame guest;
// ---------------------------------------------------------
void staff_frame_draw(Gnk_Frame *);
extern Gnk_Frame staff;
void staff_frame_booking_infomation_button_click(Gnk_Button *);
void staff_frame_guest_infomation_button_click(Gnk_Button *);
void staff_frame_type_room_infomation_button_click(Gnk_Button *);
void staff_frame_room_information_button_click(Gnk_Button *);
void staff_frame_create_guest_button_click(Gnk_Button *);

void staff_frame_booking_info_list_process(Gnk_List_Object *);
void staff_frame_guest_info_list_process(Gnk_List_Object *);
void staff_frame_type_room_info_list_process(Gnk_List_Object *);
void staff_frame_room_info_list_process(Gnk_List_Object *);
void staff_frame_create_guest_button_click_2(Gnk_Button *);
// ---------------------------------------------------------
void admin_frame_draw(Gnk_Frame *);
void admin_frame_type_room_button_click(Gnk_Button *);
void admin_frame_room_button_click(Gnk_Button *);
void admin_frame_room_revenue_button_click(Gnk_Button *);

void admin_type_room_view_and_edit_button_click(Gnk_Button *);
void admin_add_type_room_button_click(Gnk_Button *);
void admin_remove_type_room_button_click(Gnk_Button *);

void admin_room_view_and_edit_button_click(Gnk_Button *);
void admin_add_room_button_click(Gnk_Button *);
void admin_remove_room_button_click(Gnk_Button *);

void admin_daily_revenue_button_click(Gnk_Button *);
void admin_monthly_revenue_button_click(Gnk_Button *);
void admin_yearly_revenue_button_click(Gnk_Button *);

void admin_frame_back_to_main_button_click(Gnk_Button *);

void admin_frame_select_type_room_button_click(Gnk_Button *);
void admin_frame_select_room_button_click(Gnk_Button *);

void admin_frame_type_room_list_process(Gnk_List_Object *);
void admin_frame_room_list_process(Gnk_List_Object *);

void admin_frame_confirm_button_click(Gnk_Button *);
void admin_frame_previous_button_click(Gnk_Button *);
void admin_frame_view_revenue_button_click(Gnk_Button *);
extern Gnk_Frame admin;
// ---------------------------------------------------------
void login_frame_init();
void sign_up_frame_init();
void guest_frame_init();
void staff_frame_init();
void admin_frame_init();
void UI_init();
void frame_Space();
#endif