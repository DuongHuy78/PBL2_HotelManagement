#ifndef UI_H
#define UI_H
#include "gnk_2D.h"
#include "QLKhachSan.h"
class QLKhachSan;
extern QLKhachSan *current_Data;
extern int frame_num;
void UI_init();
void draw_login();
void login_button_clicked();
void login_button_hover(Gnk_Button &);
void forgot_password_button_clicked();
void sign_up_button_clicked();
void username_and_password_textbox_select(Gnk_Textbox&);
extern Gnk_Frame login;
void frame_Space();
#endif