#ifndef UI_H
#define UI_H
#include "gnk_2D.h"
#include "QLKhachSan.h"
enum frame_num_value {
	DEFAULT_FRAME,
	GUEST_FRAME,
	LOGIN_FRAME,
	FORGOT_PASSWORD_FRAME,
	SIGN_UP_FRAME
};
enum option_value {
	DEFAULT_OPTION,
	SEARCH_ROOM,
	BOOKING_INFORMATION,
	PROFILE,
	BOOKING,
	BOOKING_PART_2,
	BOOKING_DONE,
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
void guest_frame_logout_button_click(Gnk_Button *);
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
// ---------------------------------------------------------
void login_frame_init();
void sign_up_frame_init();
void guest_frame_init();
void UI_init();
void frame_Space();
#endif