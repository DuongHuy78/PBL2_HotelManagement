#include "header/UI.h"
frame_num_value frame_num = LOGIN_FRAME;
QLKhachSan *current_Data;
bool login_failed = false;
void login_frame_draw(Gnk_Frame *frame) {
	gnk_Set_Background_Color(Gnk_Color(243, 242, 242));

	gnk_Set_Object_Color(Gnk_Color(255, 255, 255));
	gnk_Rectangle(Gnk_Point(695.0f, 135.0f), Gnk_Point(1235.0f, 765.0f));

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

void button_hover_type_1(Gnk_Button *button) {
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

void button_hover_type_2(Gnk_Button *button) {
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
	frame_num = SIGN_UP_FRAME;
}

void textbox_select_type1(Gnk_Textbox *textbox) {
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

void sign_up_frame_draw(Gnk_Frame *frame) {
	gnk_Set_Background_Color(Gnk_Color(243, 242, 242));

	gnk_Set_Object_Color(Gnk_Color(255, 255, 255));
	gnk_Rectangle(Gnk_Point(395.0f, -170.0f), Gnk_Point(1235.0f, 765.0f));

	gnk_Set_Object_Color(Gnk_Color(30, 30, 30));
	gnk_Set_Character_Font("helvetica-bold");
	gnk_Text("HOTEL DEL LUNA", Gnk_Point(465.0f, 640.0f), 40.0f);

	gnk_Set_Object_Color(Gnk_Color(60, 60, 60));
	gnk_Set_Character_Font("helvetica");
	gnk_Text("Create new account!", Gnk_Point(465.0f, 580.0f), 24.0f);
	gnk_Text("Date of birth", Gnk_Point(465.0f, 420.0f), 24.0f);
	gnk_Text("Gender", Gnk_Point(465.0f, 300.0f), 24.0f);
	//gnk_Text("Already have an account? ", Gnk_Point(740.0f, 185.0f), 24.0f);

	frame->textboxList["first_name_textbox"]->display();
	frame->textboxList["surname_textbox"]->display();
	frame->textboxList["date_textbox"]->display();
	frame->textboxList["month_textbox"]->display();
	frame->textboxList["year_textbox"]->display();
	frame->textboxList["gender_textbox"]->display();
	frame->textboxList["username_textbox"]->display();
	frame->textboxList["password_textbox"]->display();
	frame->buttonList["sign_up_button"]->display();
	frame->buttonList["to_login_button"]->display();
	frame->scrollbar->display();
}

void textbox_select_type2(Gnk_Textbox *textbox) {
	textbox->draw();
	gnk_Set_Object_Color(Gnk_Color(74, 98, 138));
	gnk_Set_Line_Width(3.0f);
	gnk_Rounded_Rectangle(textbox->A, textbox->B, textbox->border_radius, false);
	gnk_Set_Line_Width(1.0f);
}

void sign_up_frame_to_login_button_click(Gnk_Button *button) {
	Gnk_Button_With_Text *buttonText = (Gnk_Button_With_Text *)button;
	Gnk_Color color = buttonText->text_color;
	buttonText->text_color = color - Gnk_Color(40, 40, 40);
	buttonText->draw();
	buttonText->text_color = color;
	frame_num = LOGIN_FRAME;
}

Gnk_Frame sign_up(sign_up_frame_draw);

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
	login_frame_username_textbox->setSelectProcess(textbox_select_type1);

	Gnk_Textbox_Password *login_frame_password_textbox = new Gnk_Textbox_Password(*login_frame_username_textbox);
	login_frame_password_textbox->setRange(Gnk_Point(806.0f, 370.0f), Gnk_Point(1190.0f, 430.0f));
	login_frame_password_textbox->setPlaceholder("password");

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
	login_frame_login_button->setHoverProcess(button_hover_type_1);

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
	login_frame_forgotten_password_button->setHoverProcess(button_hover_type_2);

	Gnk_Button_With_Text *login_frame_sign_up_button = new Gnk_Button_With_Text(*login_frame_forgotten_password_button);
	login_frame_sign_up_button->setRange(Gnk_Point(990.0f, 180.0f), Gnk_Point(1200.0f, 214.0f));
	login_frame_sign_up_button->setText("Sign up");
	login_frame_sign_up_button->setClickProcess(login_frame_sign_up_button_click);

	login.addTextbox("username_textbox", login_frame_username_textbox);
	login.addTextbox("password_textbox", login_frame_password_textbox);
	login.addButton("login_button", login_frame_login_button);
	login.addButton("forgotten_password_button", login_frame_forgotten_password_button);
	login.addButton("sign_up_button", login_frame_sign_up_button);
	}
	// Add sign up frame
	{
		Gnk_Textbox *sign_up_frame_first_name_textbox = new Gnk_Textbox();
		sign_up_frame_first_name_textbox->setRange(Gnk_Point(465.0f, 480.0f), Gnk_Point(785.0f, 540.0f));
		sign_up_frame_first_name_textbox->setColor(Gnk_Color(255, 255, 255));
		sign_up_frame_first_name_textbox->setBorderRadius(0.0f);
		sign_up_frame_first_name_textbox->setTextFont("helvetica");
		sign_up_frame_first_name_textbox->setFontSize(24.0f);
		sign_up_frame_first_name_textbox->setTextColor(Gnk_Color(17, 17, 17));
		sign_up_frame_first_name_textbox->setPlaceholder("First name");
		sign_up_frame_first_name_textbox->setPlaceholderFont("helvetica");
		sign_up_frame_first_name_textbox->setPlaceholderFontSize(24.0f);
		sign_up_frame_first_name_textbox->setPlaceholderColor(Gnk_Color(85, 85, 85));
		sign_up_frame_first_name_textbox->setPaddingX(15.0f);
		sign_up_frame_first_name_textbox->setPaddingY(10.0f);
		sign_up_frame_first_name_textbox->setTextAlign(GNK_TEXT_LEFT);
		sign_up_frame_first_name_textbox->setSelectProcess(textbox_select_type2);
		sign_up_frame_first_name_textbox->setBorder(true);
		sign_up_frame_first_name_textbox->setBorderColor(Gnk_Color(45, 45, 45));
		sign_up_frame_first_name_textbox->setBorderRadius(10.0f);

		Gnk_Textbox *sign_up_frame_surname_textbox = new Gnk_Textbox(*sign_up_frame_first_name_textbox);
		sign_up_frame_surname_textbox->setRange(Gnk_Point(815.0f, 480.0f), Gnk_Point(1135.0f, 540.0f));
		sign_up_frame_surname_textbox->setPlaceholder("Surname");

		Gnk_Textbox *sign_up_frame_date_textbox = new Gnk_Textbox(*sign_up_frame_first_name_textbox);
		sign_up_frame_date_textbox->setRange(Gnk_Point(465.0f, 340.0f), Gnk_Point(665.0f, 400.0f));
		sign_up_frame_date_textbox->setPlaceholder("Date");

		Gnk_Textbox *sign_up_frame_month_textbox = new Gnk_Textbox(*sign_up_frame_first_name_textbox);
		sign_up_frame_month_textbox->setRange(Gnk_Point(700.0f, 340.0f), Gnk_Point(900.0f, 400.0f));
		sign_up_frame_month_textbox->setPlaceholder("Month");

		Gnk_Textbox *sign_up_frame_year_textbox = new Gnk_Textbox(*sign_up_frame_first_name_textbox);
		sign_up_frame_year_textbox->setRange(Gnk_Point(935.0f, 340.0f), Gnk_Point(1135.0f, 400.0f));
		sign_up_frame_year_textbox->setPlaceholder("Year");

		Gnk_Textbox *sign_up_frame_gender_textbox = new Gnk_Textbox(*sign_up_frame_first_name_textbox);
		sign_up_frame_gender_textbox->setRange(Gnk_Point(465.0f, 220.0f), Gnk_Point(1135.0f, 280.0f));
		sign_up_frame_gender_textbox->setPlaceholder("Nam/Nu");

		Gnk_Textbox *sign_up_frame_username_textbox = new Gnk_Textbox(*sign_up_frame_first_name_textbox);
		sign_up_frame_username_textbox->setRange(Gnk_Point(465.0f, 140.0f), Gnk_Point(1135.0f, 200.0f));
		sign_up_frame_username_textbox->setPlaceholder("Username");

		Gnk_Textbox_Password *sign_up_frame_password_textbox = new Gnk_Textbox_Password(*sign_up_frame_first_name_textbox);
		sign_up_frame_password_textbox->setRange(Gnk_Point(465.0f, 60.0f), Gnk_Point(1135.0f, 120.0f));
		sign_up_frame_password_textbox->setPlaceholder("Password");

		Gnk_Button_With_Text *sign_up_frame_sign_up_button = new Gnk_Button_With_Text();
		sign_up_frame_sign_up_button->setRange(Gnk_Point(700.0f, -40.0f), Gnk_Point(900.0f, 20.0f));
		sign_up_frame_sign_up_button->setColor(Gnk_Color(90, 100, 147));
		sign_up_frame_sign_up_button->setText("Sign up");
		sign_up_frame_sign_up_button->setTextFont("helvetica-bold");
		sign_up_frame_sign_up_button->setFontSize(24.0f);
		sign_up_frame_sign_up_button->setTextColor(Gnk_Color(255, 255, 255));
		sign_up_frame_sign_up_button->setPaddingX(0.0f);
		sign_up_frame_sign_up_button->setPaddingY(0.0f);
		sign_up_frame_sign_up_button->setTextAlign(GNK_TEXT_CENTER);
		sign_up_frame_sign_up_button->border_radius = 30.0f;
		sign_up_frame_sign_up_button->setHoverProcess(button_hover_type_1);
		//sign_up_frame_sign_up_button->setClickProcess();

		Gnk_Button_With_Text *sign_up_frame_to_login_button = new Gnk_Button_With_Text();
		sign_up_frame_to_login_button->setRange(Gnk_Point(465.0f, -100.0f), Gnk_Point(1135.0f, -60.0f));
		sign_up_frame_to_login_button->setColor(Gnk_Color(255, 255, 255));
		sign_up_frame_to_login_button->setText("Already have an account? Login");
		sign_up_frame_to_login_button->setTextFont("helvetica");
		sign_up_frame_to_login_button->setFontSize(24.0f);
		sign_up_frame_to_login_button->setTextColor(Gnk_Color(60, 60, 60));
		sign_up_frame_to_login_button->setPaddingX(0.0f);
		sign_up_frame_to_login_button->setPaddingY(0.0f);
		sign_up_frame_to_login_button->setTextAlign(GNK_TEXT_CENTER);
		sign_up_frame_to_login_button->setHoverProcess(button_hover_type_2);
		sign_up_frame_to_login_button->setClickProcess(sign_up_frame_to_login_button_click);

		Gnk_Scrollbar *sign_up_frame_scrollbar = new Gnk_Scrollbar();
		sign_up_frame_scrollbar->setRange(Gnk_Point(gnk_Width - 20.0f, 0.0f), Gnk_Point(gnk_Width, gnk_Height));
		sign_up_frame_scrollbar->setColor(Gnk_Color(255, 255, 255));
		sign_up_frame_scrollbar->setScrollColor(Gnk_Color(200, 200, 200));
		sign_up_frame_scrollbar->setHoverColor(Gnk_Color(180, 180, 180));
		sign_up_frame_scrollbar->setClickColor(Gnk_Color(160, 160, 160));
		sign_up_frame_scrollbar->setMaxHeight(gnk_Height * 1.4);		// Loi scrollbar
		sign_up_frame_scrollbar->setFrameHeight(gnk_Height);
		sign_up_frame_scrollbar->setAppear(true);

		sign_up.addTextbox("first_name_textbox", sign_up_frame_first_name_textbox);
		sign_up.addTextbox("surname_textbox", sign_up_frame_surname_textbox);
		sign_up.addTextbox("date_textbox", sign_up_frame_date_textbox);
		sign_up.addTextbox("month_textbox", sign_up_frame_month_textbox);
		sign_up.addTextbox("year_textbox", sign_up_frame_year_textbox);
		sign_up.addTextbox("gender_textbox", sign_up_frame_gender_textbox);
		sign_up.addTextbox("username_textbox", sign_up_frame_username_textbox);
		sign_up.addTextbox("password_textbox", sign_up_frame_password_textbox);
		sign_up.addButton("sign_up_button", sign_up_frame_sign_up_button);
		sign_up.addButton("to_login_button", sign_up_frame_to_login_button);
		sign_up.setScrollbar(sign_up_frame_scrollbar);
	}
}
void frame_Space() {
	if(frame_num != LOGIN_FRAME) {
		login_failed = false;
	}
	switch (frame_num) {
	case LOGIN_FRAME:
		gnk_Set_Current_Frame(login);
		break;
	case SIGN_UP_FRAME:
		gnk_Set_Current_Frame(sign_up);
		break;
	default:
		gnk_Set_Current_Frame(gnk_Default_Frame);
	}
}
