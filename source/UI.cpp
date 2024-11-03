#include "header/UI.h"
int frame_num = 1;
QLKhachSan *current_Data;
void UI_init() {
	const float width = 1600.0f, height = 900.0f;
	gnk_Initialize(width, height, "PBL2 - Hotel Management", "shader/text.vs", "shader/text.fs");
	gnk_Set_Frame_Space(frame_Space);

	gnk_Font_List.addFont("arial", "font/arial.ttf", 48);
	gnk_Font_List.addFont("helvetica", "font/Helvetica.ttf", 24);
	gnk_Font_List.addFont("helvetica-bold", "font/Helvetica-Bold.ttf", 48);

	gnk_Image_List.addImage("city_image", "image/hoteldelluna.jpg");
	gnk_Image_List.addImage("user_icon", "image/user_icon.jpg");
	gnk_Image_List.addImage("password_icon", "image/password_icon.jpg");

	Gnk_Textbox *usernameTextbox = new Gnk_Textbox(
			Gnk_Point(806.0f, 460.0f), Gnk_Point(1190.0f, 520.0f), 
			Gnk_Color(255, 255, 255), "helvetica",
			24.0f, Gnk_Color(17, 17, 17), 15.0f, 10.0f, "username",
			"helvetica", 24.0f, Gnk_Color(85, 85, 85), GNK_TEXT_LEFT,
			username_and_password_textbox_select
		);

	Gnk_Textbox_password *passwordTextbox = new Gnk_Textbox_password(
			Gnk_Point(806.0f, 370.0f), Gnk_Point(1190.0f, 430.0f),
			Gnk_Color(255, 255, 255), "helvetica",
			24.0f, Gnk_Color(17, 17, 17), 15.0f, 10.0f, "password",
			"helvetica", 24.0f, Gnk_Color(85, 85, 85), GNK_TEXT_LEFT,
			username_and_password_textbox_select
		);

	Gnk_Button *loginButton = new Gnk_Button(
			Gnk_Point(1030.0f, 240.0f), Gnk_Point(1190.0f, 300.0f), 
			Gnk_Color(90, 100, 147), "Login", "helvetica-bold",
			24.0f, Gnk_Color(255, 255, 255), 15.0f, 10.0f, 30.0f, login_button_clicked,
			login_button_hover
		);

	Gnk_Button *forgotPassButton = new Gnk_Button(
			Gnk_Point(740.0f, 250.0f), Gnk_Point(990.0f, 284.0f),
			Gnk_Color(255, 255, 255), "Forgot your password?", "helvetica",
			24.0f, Gnk_Color(60, 60, 60), 0.0f, 0.0f, 0.0f, forgot_password_button_clicked,
			NULL, GNK_TEXT_LEFT
		);

	Gnk_Button *signInButton = new Gnk_Button(
			Gnk_Point(740.0f, 180.0f), Gnk_Point(1200.0f, 214.0f),
			Gnk_Color(255, 255, 255), "Do not have an account? Sign up", "helvetica",
			24.0f, Gnk_Color(60, 60, 60), 0.0f, 0.0f, 0.0f, sign_up_button_clicked
		);
	login.addTextbox(usernameTextbox);
	login.addTextbox(passwordTextbox);
	login.addButton(loginButton);
	login.addButton(forgotPassButton);
	login.addButton(signInButton);
}
void draw_login() {
	gnk_Set_Background_Color(Gnk_Color(243, 242, 242));

	gnk_Set_Object_Color(Gnk_Color(255, 255, 255));
	gnk_Rectangle(Gnk_Point(695.0f, 135.0f), Gnk_Point(1235.0f, 765.0f));

	gnk_Set_Object_Color(Gnk_Color(85, 85, 85));
	gnk_Rectangle(Gnk_Point(365.0f, 135.0f), Gnk_Point(695.0f, 765.0f));

	gnk_Set_Object_Color(Gnk_Color(30, 30, 30));
	gnk_Set_Character_Font("helvetica-bold");
	gnk_Text("HOTEL DEL LUNA", Gnk_Point(740.0f, 640.0f), 40.0f);

	gnk_Set_Object_Color(Gnk_Color(60, 60, 60));
	gnk_Set_Character_Font("helvetica");
	gnk_Text("Welcome back! ", Gnk_Point(740.0f, 580.0f), 24.0f);

	gnk_Line(Gnk_Point(821.0f, 455.0f), Gnk_Point(1175.0f, 455.0f));
	gnk_Line(Gnk_Point(821.0f, 365.0f), Gnk_Point(1175.0f, 365.0f));

	gnk_Image(gnk_Image_List["city_image"], Gnk_Point(365.0f, 135.0f), Gnk_Point(695.0f, 765.0f));
	gnk_Image(gnk_Image_List["user_icon"], Gnk_Point(740.0f, 450.0f), Gnk_Point(800.0f, 510.0f));
	gnk_Image(gnk_Image_List["password_icon"], Gnk_Point(740.0f, 360.0f), Gnk_Point(800.0f, 420.0f));
}

void login_button_clicked() {
	NguoiDung *p = current_Data->dangNhap(gnk_Current_Frame->textboxList[0]->text, 
		gnk_Current_Frame->textboxList[1]->text);
	if(p != NULL) {
		p->work();
		frame_num = 0;
		std::cout << "You are log in successed!!" << std::endl;
	}
	else {
		std::cout << "Username or password is incorrect !!" << std::endl;
	}
}

void login_button_hover(Gnk_Button &button) {
	gnk_Set_Object_Color(button.color - Gnk_Color(20, 20, 20));
	gnk_Rounded_Rectangle(button.A, button.B, button.radius);
	gnk_Set_Object_Color(button.textColor);
	gnk_Set_Character_Font(button.textFont);
	gnk_Text_Limited(
		button.text, 
		button.A.translate(button.paddingX, button.paddingY), 
		button.getWidth() - 2 * button.paddingX, 
		button.getHeight() - 2 * button.paddingY, 
		button.fontSize, 
		GNK_TEXT_CENTER
	);
}

void forgot_password_button_clicked() {
	std::cout << "forgot password button clicked!!" << std::endl;
}

void sign_up_button_clicked() {
	std::cout << "sign up button clicked!!" << std::endl;
}

void username_and_password_textbox_select(Gnk_Textbox& textbox) {
	gnk_Set_Object_Color(Gnk_Color(74, 98, 138));
	gnk_Set_Line_Width(3.0f);
	gnk_Line(
		Gnk_Point(
			textbox.A.x + textbox.paddingX,
			textbox.A.y - 5.0f
		),
		Gnk_Point(
			textbox.B.x - textbox.paddingX,
			textbox.A.y - 5.0f
		)
	);
	gnk_Set_Line_Width(1.0f);
}

Gnk_Frame login(draw_login);

void frame_Space() {
	switch (frame_num) {
	case 1:
		gnk_Set_Frame(login);
		break;
	default:
		gnk_Set_Frame(gnk_Default_Frame);
	}
}
