#include "header/UI.h"
frame_num_value frame_num = LOGIN_FRAME;
QLKhachSan *current_Data;
bool login_failed = false;
void login_frame_draw(Gnk_Frame *frame) {
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
	gnk_Text("Don't have an account? ", Gnk_Point(740.0f, 185.0f), 24.0f);

	gnk_Line(Gnk_Point(821.0f, 455.0f), Gnk_Point(1175.0f, 455.0f));
	gnk_Line(Gnk_Point(821.0f, 365.0f), Gnk_Point(1175.0f, 365.0f));

	gnk_Image(gnk_Image_List["hotel_image"], Gnk_Point(365.0f, 135.0f), Gnk_Point(695.0f, 765.0f));
	gnk_Image(gnk_Image_List["user_icon"], Gnk_Point(740.0f, 450.0f), Gnk_Point(800.0f, 510.0f));
	gnk_Image(gnk_Image_List["password_icon"], Gnk_Point(740.0f, 360.0f), Gnk_Point(800.0f, 420.0f));


	frame->textboxList["username_textbox"]->display();
	frame->textboxList["password_textbox"]->display();
	frame->buttonList["login_button"]->display();
	frame->buttonList["forgotten_password_button"]->display();
	frame->buttonList["sign_up_button"]->display();

	if(login_failed) {
		gnk_Set_Object_Color(Gnk_Color(255, 0, 0));
		gnk_Text("Username or password is incorrect !!", Gnk_Point(740.0f, 310.0f), 24.0f);
	}
}

void login_frame_login_button_click(Gnk_Button *button) {
	Gnk_Button_With_Text *buttonText = (Gnk_Button_With_Text *)button;
	Gnk_Color color = buttonText->color;
	buttonText->color = color - Gnk_Color(40, 40, 40);
	buttonText->draw();
	buttonText->color = color;
	NguoiDung *p = current_Data->dangNhap((login.textboxList["username_textbox"])->text, (login.textboxList["password_textbox"])->text);
	if(p != nullptr) {
		p->work();
		frame_num = DEFAULT_FRAME;
		login_failed = false;
	}
	else {
		login_failed = true;
	}
}

void login_frame_login_button_hover(Gnk_Button *button) {
	Gnk_Button_With_Text *buttonText = (Gnk_Button_With_Text *)button;
	Gnk_Color color = buttonText->color;
	buttonText->color = color - Gnk_Color(20, 20, 20);
	buttonText->draw();
	buttonText->color = color;
}

void login_frame_forgotten_password_button_click(Gnk_Button *button) {
	Gnk_Button_With_Text *buttonText = (Gnk_Button_With_Text *)button;
	Gnk_Color color = buttonText->text_color;
	buttonText->text_color = Gnk_Color(70, 80, 127);
	buttonText->draw();
	buttonText->text_color = color;
	//frame_num = FORGOT_PASSWORD_FRAME;
}

void login_frame_forgotten_password_button_hover(Gnk_Button *button) {
	Gnk_Button_With_Text *buttonText = (Gnk_Button_With_Text *)button;
	Gnk_Color color = buttonText->text_color;
	buttonText->text_color = Gnk_Color(90, 100, 147);
	buttonText->draw();
	buttonText->text_color = color;
}

void login_frame_sign_up_button_click(Gnk_Button *button) {
	Gnk_Button_With_Text *buttonText = (Gnk_Button_With_Text *)button;
	Gnk_Color color = buttonText->text_color;
	buttonText->text_color = Gnk_Color(70, 80, 127);
	buttonText->draw();
	buttonText->text_color = color;
	//frame_num = SIGN_UP_FRAME;
}

void login_frame_sign_up_button_hover(Gnk_Button *button) {
	Gnk_Button_With_Text *buttonText = (Gnk_Button_With_Text *)button;
	Gnk_Color color = buttonText->text_color;
	buttonText->text_color = Gnk_Color(90, 100, 147);
	buttonText->draw();
	buttonText->text_color = color;
}

void login_frame_username_and_password_textbox_select(Gnk_Textbox *textbox) {
	gnk_Set_Object_Color(Gnk_Color(74, 98, 138));
	gnk_Set_Line_Width(3.0f);
	gnk_Line(
		Gnk_Point(
			textbox->A.x + textbox->paddingX,
			textbox->A.y - 5.0f
		),
		Gnk_Point(
			textbox->B.x - textbox->paddingX,
			textbox->A.y - 5.0f
		)
	);
	gnk_Set_Line_Width(1.0f);
	textbox->draw();
}

Gnk_Frame login(login_frame_draw);


void UI_init() {
	// Initialize
	{
	const float width = 1600.0f, height = 900.0f;
	gnk_Initialize(width, height, "PBL2 - Hotel Management", "shader/text.vs", "shader/text.fs");
	gnk_Set_Frame_Space(frame_Space);

	gnk_Font_List.addFont("arial", "font/arial.ttf", 48);
	gnk_Font_List.addFont("helvetica", "font/Helvetica.ttf", 24);
	gnk_Font_List.addFont("helvetica-bold", "font/Helvetica-Bold.ttf", 48);

	gnk_Image_List.addImage("hotel_image", "image/hoteldelluna_resize.jpg");
	gnk_Image_List.addImage("user_icon", "image/user_icon.jpg");
	gnk_Image_List.addImage("password_icon", "image/password_icon.jpg");
	}
	// Add login frame
	{
	Gnk_Textbox *login_frame_username_textbox = new Gnk_Textbox();
	login_frame_username_textbox->setRange(Gnk_Point(806.0f, 460.0f), Gnk_Point(1190.0f, 520.0f));
	login_frame_username_textbox->setColor(Gnk_Color(255, 255, 255));
	login_frame_username_textbox->setBorderRadius(0.0f);
	login_frame_username_textbox->setTextFont("helvetica");
	login_frame_username_textbox->setFontSize(24.0f);
	login_frame_username_textbox->setTextColor(Gnk_Color(17, 17, 17));
	login_frame_username_textbox->setPlaceholder("username");
	login_frame_username_textbox->setPlaceholderFont("helvetica");
	login_frame_username_textbox->setPlaceholderFontSize(24.0f);
	login_frame_username_textbox->setPlaceholderColor(Gnk_Color(85, 85, 85));
	login_frame_username_textbox->setPaddingX(15.0f);
	login_frame_username_textbox->setPaddingY(10.0f);
	login_frame_username_textbox->setTextAlign(GNK_TEXT_LEFT);
	login_frame_username_textbox->setSelectProcess(login_frame_username_and_password_textbox_select);

	Gnk_Textbox_Password *login_frame_password_textbox = new Gnk_Textbox_Password();
	login_frame_password_textbox->setRange(Gnk_Point(806.0f, 370.0f), Gnk_Point(1190.0f, 430.0f));
	login_frame_password_textbox->setColor(Gnk_Color(255, 255, 255));
	login_frame_password_textbox->setBorderRadius(0.0f);
	login_frame_password_textbox->setTextFont("helvetica");
	login_frame_password_textbox->setFontSize(24.0f);
	login_frame_password_textbox->setTextColor(Gnk_Color(17, 17, 17));
	login_frame_password_textbox->setPlaceholder("password");
	login_frame_password_textbox->setPlaceholderFont("helvetica");
	login_frame_password_textbox->setPlaceholderFontSize(24.0f);
	login_frame_password_textbox->setPlaceholderColor(Gnk_Color(85, 85, 85));
	login_frame_password_textbox->setPaddingX(15.0f);
	login_frame_password_textbox->setPaddingY(10.0f);
	login_frame_password_textbox->setTextAlign(GNK_TEXT_LEFT);
	login_frame_password_textbox->setSelectProcess(login_frame_username_and_password_textbox_select);

	Gnk_Button_With_Text *login_frame_login_button = new Gnk_Button_With_Text();
	login_frame_login_button->setRange(Gnk_Point(1030.0f, 230.0f), Gnk_Point(1190.0f, 290.0f));
	login_frame_login_button->setColor(Gnk_Color(90, 100, 147));
	login_frame_login_button->setText("Login");
	login_frame_login_button->setTextFont("helvetica-bold");
	login_frame_login_button->setFontSize(24.0f);
	login_frame_login_button->setTextColor(Gnk_Color(255, 255, 255));
	login_frame_login_button->setTextAlign(GNK_TEXT_CENTER);
	login_frame_login_button->setPaddingX(15.0f);
	login_frame_login_button->setPaddingY(10.0f);
	login_frame_login_button->setRadius(30.0f);
	login_frame_login_button->setClickProcess(login_frame_login_button_click);
	login_frame_login_button->setHoverProcess(login_frame_login_button_hover);

	Gnk_Button_With_Text *login_frame_forgotten_password_button = new Gnk_Button_With_Text();
	login_frame_forgotten_password_button->setRange(Gnk_Point(740.0f, 250.0f), Gnk_Point(990.0f, 284.0f));
	login_frame_forgotten_password_button->setColor(Gnk_Color(255, 255, 255));
	login_frame_forgotten_password_button->setText("Forgot your password?");
	login_frame_forgotten_password_button->setTextFont("helvetica");
	login_frame_forgotten_password_button->setFontSize(24.0f);
	login_frame_forgotten_password_button->setTextColor(Gnk_Color(60, 60, 60));
	login_frame_forgotten_password_button->setPaddingX(0.0f);
	login_frame_forgotten_password_button->setPaddingY(0.0f);
	login_frame_forgotten_password_button->setClickProcess(login_frame_forgotten_password_button_click);
	login_frame_forgotten_password_button->setHoverProcess(login_frame_forgotten_password_button_hover);

	Gnk_Button_With_Text *login_frame_sign_up_button = new Gnk_Button_With_Text();
	login_frame_sign_up_button->setRange(Gnk_Point(990.0f, 180.0f), Gnk_Point(1200.0f, 214.0f));
	login_frame_sign_up_button->setColor(Gnk_Color(255, 255, 255));
	login_frame_sign_up_button->setText("Sign up");
	login_frame_sign_up_button->setTextFont("helvetica");
	login_frame_sign_up_button->setFontSize(24.0f);
	login_frame_sign_up_button->setTextColor(Gnk_Color(60, 60, 60));
	login_frame_sign_up_button->setPaddingX(0.0f);
	login_frame_sign_up_button->setPaddingY(0.0f);
	login_frame_sign_up_button->setClickProcess(login_frame_sign_up_button_click);
	login_frame_sign_up_button->setHoverProcess(login_frame_sign_up_button_hover);

	login.addTextbox("username_textbox", login_frame_username_textbox);
	login.addTextbox("password_textbox", login_frame_password_textbox);
	login.addButton("login_button", login_frame_login_button);
	login.addButton("forgotten_password_button", login_frame_forgotten_password_button);
	login.addButton("sign_up_button", login_frame_sign_up_button);
	}
}
void frame_Space() {
	switch (frame_num) {
	case LOGIN_FRAME:
		gnk_Set_Current_Frame(login);
		break;
	default:
		gnk_Set_Current_Frame(gnk_Default_Frame);
	}
}
