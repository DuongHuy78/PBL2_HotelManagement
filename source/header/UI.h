#ifndef UI_H
#define UI_H
#include "gnk_2D.h"
#include "QLKhachSan.h"
enum frame_num_value {
	DEFAULT_FRAME,
	LOGIN_FRAME,
	FORGOT_PASSWORD_FRAME,
	SIGN_UP_FRAME
};
class QLKhachSan;
extern QLKhachSan *current_Data;
extern frame_num_value frame_num;
//---------------------------------------------------------
void draw_login(Gnk_Frame&);
void login_frame_login_button_click(Gnk_Button&);
void login_frame_login_button_hover(Gnk_Button&);
void login_frame_forgotten_password_button_click(Gnk_Button&);
void login_frame_forgotten_password_button_hover(Gnk_Button&);
void login_frame_sign_up_button_click(Gnk_Button&);
void login_frame_sign_up_button_hover(Gnk_Button&);
void login_frame_username_and_password_textbox_select(Gnk_Textbox&);
extern Gnk_Frame login;
// //---------------------------------------------------------
// void draw_forgot_password();
// extern Gnk_Frame forgot_password;
// //---------------------------------------------------------
// void draw_sign_up();
// extern Gnk_Frame sign_up;
// //---------------------------------------------------------
void UI_init();
void frame_Space();
#endif