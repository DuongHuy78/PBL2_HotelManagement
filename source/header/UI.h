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
void draw_login();
void login_button_clicked();
void login_button_hover(Gnk_Button &);
void forgot_password_button_clicked();
void sign_up_button_clicked();
void username_and_password_textbox_select(Gnk_Textbox&);
extern Gnk_Frame login;
//---------------------------------------------------------
void draw_forgot_password();
extern Gnk_Frame forgot_password;
//---------------------------------------------------------
void draw_sign_up();
extern Gnk_Frame sign_up;
//---------------------------------------------------------
void UI_init();
void frame_Space();
#endif