#include "header/UI.h"
frame_num_value current_frame = LOGIN_FRAME;
frame_num_value previous_frame = DEFAULT_FRAME;
option_value option = DEFAULT_OPTION;
QLKhachSan *current_Data = nullptr;
bool login_failed = false;
bool blank_info = false;
bool username_existed = false;
bool male_toggle_enable = false;
bool female_toggle_enable = false;

bool search_room_list_enable = false;
bool room_list_init = false;
struct room_type {
	string type;
	string bed_type;
	string number_of_guest;
	string area;
	string price;
	string description;
	string amount;
};

struct history_booking {
	string ID;
	string roomtype;
	string roomID;
	string check_in_date;
	string check_out_date;
	string number_of_guest;
	string price_per_night;
	string total_price;
};

struct booking_info {
	string ID;
	string roomtype;
	string roomID;
	string guestID;
	string check_in_date;
	string check_out_date;
	string number_of_guest;
	string price_per_night;
	string total_price;
};
bool booking_info_list_enable = false;
bool booking_info_list_init = false;
vector<booking_info> booking_info_list;

struct guest_info {
	string ID;
	string name;
	string date_of_birth;
	string phone_number;
	string gender;
};

bool guest_info_list_enable = false;
bool guest_info_list_init = false;
vector<guest_info> guest_info_list;

struct room_info {
	string ID;
	string type;
	string bed_type;
	string number_of_guest;
	string area;
	string price;
};
bool room_info_list_enable = false;
bool room_info_list_init = false;
vector<room_info> room_info_list;

struct type_room_info {
	string type;
	string bed_type;
	string number_of_guest;
	string area;
	string price;
	string description;
	string amount;
};
bool type_room_info_list_enable = false;
bool type_room_info_list_init = false;
vector<type_room_info> type_room_info_list;

vector<history_booking> history_booking_list;
bool history_list_enable = false;
bool history_list_init = false;

string check_in_date_str = "";
string check_out_date_str = "";
string number_of_guest_str = "";
string list_room_available = "";
string list_type_room_available = "";
vector<string> list_room_choice;
vector<string> list_type_room_choice;
string room_choice = "";
int index_selected_room = -1;
int index_hover_room = -1;
int index_booking = -1;
vector<room_type> room_list;
struct guest_profile {
	string ID;
	string name;
	string date_of_birth;
	string phone_number;
	gender_value gender;

	string username;
	string password;
};
guest_profile current_guest_profile;
bool edit_profile = false;
bool staff_booking_guest_ID_not_exist = false;
bool admin_type_room_not_exist = false;
string booking_total_price = "";
string staff_booking_guest_ID = "";
bool staff_create_guest_success = false;
// ---------------------------------------------------------
Gnk_Color C_1A1A1D(26, 26, 29);
Gnk_Color H_000000(0, 0, 0);
Gnk_Color H_222831(34, 40, 49);
Gnk_Color H_404040(64, 64, 64);
Gnk_Color H_46507F(70, 80, 127);
Gnk_Color H_5A6493(90, 100, 147);
Gnk_Color H_7E7E81(126, 126, 129);
Gnk_Color H_C8C8C8(200, 200, 200);
Gnk_Color H_FFECB8(250, 235, 205);
Gnk_Color H_F3F2F2(243, 242, 242);
Gnk_Color H_F7C873(247, 200, 115);
Gnk_Color H_FF0000(255, 0, 0);
Gnk_Color H_FFFFFF(255, 255, 255);

// ---------------------------------------------------------
void button_hover_type_1(Gnk_Button *button) {
	Gnk_Button_With_Text *buttonText = (Gnk_Button_With_Text *)button;
	Gnk_Color color = buttonText->color;
	buttonText->color = color - Gnk_Color(20, 20, 20);
	buttonText->draw();
	buttonText->color = color;
}

void button_hover_type_2(Gnk_Button *button) {
	Gnk_Button_With_Text *buttonText = (Gnk_Button_With_Text *)button;
	Gnk_Color color = buttonText->text_color;
	buttonText->text_color = H_5A6493;
	buttonText->draw();
	buttonText->text_color = color;
}

void button_hover_type_3(Gnk_Button *button) {
	Gnk_Button_With_Text *buttonText = (Gnk_Button_With_Text *)button;
	Gnk_Color color = buttonText->color;
	buttonText->color = color + Gnk_Color(20, 20, 20);
	buttonText->draw();
	buttonText->color = color;
}

void textbox_select_type1(Gnk_Textbox *textbox) {
	gnk_Set_Object_Color(H_46507F);
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

void textbox_select_type3(Gnk_Textbox *textbox) {
	gnk_Set_Object_Color(H_222831);
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

void textbox_select_type2(Gnk_Textbox *textbox) {
	textbox->draw();
	gnk_Set_Object_Color(H_46507F);
	gnk_Set_Line_Width(3.0f);
	gnk_Rounded_Rectangle(textbox->A, textbox->B, textbox->border_radius, false);
	gnk_Set_Line_Width(1.0f);
}

// ---------------------------------------------------------
void login_frame_draw(Gnk_Frame *frame) {
	gnk_Set_Background_Color(H_F3F2F2);

	gnk_Set_Object_Color(H_FFFFFF);
	gnk_Rectangle(Gnk_Point(695.0f, 135.0f), Gnk_Point(1235.0f, 765.0f));

	gnk_Set_Object_Color(C_1A1A1D);
	gnk_Set_Character_Font("helvetica-bold");
	gnk_Text("HOTEL DEL LUNA", Gnk_Point(740.0f, 640.0f), 40.0f);

	gnk_Set_Object_Color(H_404040);
	gnk_Set_Character_Font("helvetica");
	gnk_Text("Welcome back! ", Gnk_Point(740.0f, 580.0f), 24.0f);
	gnk_Text("Don't have an account? ", Gnk_Point(740.0f, 185.0f), 24.0f);

	gnk_Line(Gnk_Point(821.0f, 455.0f), Gnk_Point(1175.0f, 455.0f));
	gnk_Line(Gnk_Point(821.0f, 365.0f), Gnk_Point(1175.0f, 365.0f));

	gnk_Image(gnk_Image_List["hotel_image"], Gnk_Point(365.0f, 135.0f), Gnk_Point(695.0f, 765.0f));
	gnk_Image(gnk_Image_List["user_icon"], Gnk_Point(740.0f, 450.0f), Gnk_Point(800.0f, 510.0f));
	gnk_Image(gnk_Image_List["password_icon"], Gnk_Point(740.0f, 360.0f), Gnk_Point(800.0f, 420.0f));

	for(auto &textbox : frame->textboxList) {
		textbox.second->display();
	}

	for(auto &button : frame->buttonList) {
		button.second->display();
	}

	if(login_failed) {
		gnk_Set_Object_Color(H_FF0000);
		gnk_Set_Character_Font("helvetica");
		gnk_Text("Username or password is incorrect !!", Gnk_Point(740.0f, 310.0f), 24.0f);
	}
}

void login_frame_login_button_click(Gnk_Button *button) {
	Gnk_Button_With_Text *buttonText = (Gnk_Button_With_Text *)button;
	Gnk_Color color = buttonText->color;
	buttonText->color = color - Gnk_Color(40, 40, 40);
	buttonText->draw();
	buttonText->color = color;
	UI_input_buffer.str("");UI_input_buffer.clear();
	UI_output_buffer.str("");UI_output_buffer.clear();
	UI_input_buffer << (login.textboxList["username_textbox"])->text << endl;
	UI_input_buffer << (login.textboxList["password_textbox"])->text << endl;
	if(current_Data->dangNhap()) {
		if(current_Data->getCurrentRole() == KHACHHANG) {
			current_frame = GUEST_FRAME;
			option = DEFAULT_OPTION;
			current_Data->requestHandling(PRINT_KHACHHANG);
			string gender;
			getline(UI_output_buffer, current_guest_profile.ID);
			getline(UI_output_buffer, current_guest_profile.name);
			getline(UI_output_buffer, current_guest_profile.date_of_birth);
			getline(UI_output_buffer, current_guest_profile.phone_number);
			getline(UI_output_buffer, gender);
			current_guest_profile.gender = Utils::stringToGender(gender);
			current_guest_profile.username = (login.textboxList["username_textbox"])->text;
			current_guest_profile.password = (login.textboxList["password_textbox"])->text;
		}
		else if(current_Data->getCurrentRole() == NHANVIEN) {
			current_frame = STAFF_FRAME;
			option = DEFAULT_OPTION;
		}
		else if(current_Data->getCurrentRole() == QUANLI) {
			current_frame = ADMIN_FRAME;
			option = ADMIN_MAIN;
		}
	}
	else {
		login_failed = true;
	}
}

void login_frame_forgotten_password_button_click(Gnk_Button *button) {
	Gnk_Button_With_Text *buttonText = (Gnk_Button_With_Text *)button;
	Gnk_Color color = buttonText->text_color;
	buttonText->text_color = H_46507F;
	buttonText->draw();
	buttonText->text_color = color;
	//current_frame = FORGOT_PASSWORD_FRAME;
}

void login_frame_sign_up_button_click(Gnk_Button *button) {
	Gnk_Button_With_Text *buttonText = (Gnk_Button_With_Text *)button;
	Gnk_Color color = buttonText->text_color;
	buttonText->text_color = H_46507F;
	buttonText->draw();
	buttonText->text_color = color;
	current_frame = SIGN_UP_FRAME;
}

Gnk_Frame login(login_frame_draw);
// ---------------------------------------------------------
void sign_up_frame_draw(Gnk_Frame *frame) {
	gnk_Set_Background_Color(H_F3F2F2);

	gnk_Set_Object_Color(H_FFFFFF);
	gnk_Rectangle(Gnk_Point(395.0f, -170.0f), Gnk_Point(1235.0f, 765.0f));

	gnk_Set_Object_Color(C_1A1A1D);
	gnk_Set_Character_Font("helvetica-bold");
	gnk_Text("HOTEL DEL LUNA", Gnk_Point(465.0f, 640.0f), 40.0f);

	gnk_Set_Object_Color(H_404040);
	gnk_Set_Character_Font("helvetica");
	gnk_Text("Create new account!", Gnk_Point(465.0f, 580.0f), 24.0f);
	gnk_Text("Date of birth", Gnk_Point(465.0f, 420.0f), 24.0f);
	gnk_Text("Gender", Gnk_Point(465.0f, 300.0f), 24.0f);

	for(auto &textbox : frame->textboxList) {
		textbox.second->display();
	}
	for(auto &button : frame->buttonList) {
		button.second->display();
	}
	frame->scrollbar->setAppear(true);
	frame->scrollbar->display();
}

void sign_up_frame_to_login_button_click(Gnk_Button *button) {
	Gnk_Button_With_Text *buttonText = (Gnk_Button_With_Text *)button;
	Gnk_Color color = buttonText->text_color;
	buttonText->text_color = color - Gnk_Color(40, 40, 40);
	buttonText->draw();
	buttonText->text_color = color;
	current_frame = LOGIN_FRAME;
}

void sign_up_frame_sign_up_button_click(Gnk_Button *button) {
	Gnk_Button_With_Text *buttonText = (Gnk_Button_With_Text *)button;
	Gnk_Color color = buttonText->color;
	buttonText->color = color - Gnk_Color(40, 40, 40);
	buttonText->draw();
	buttonText->color = color;
	string gender = "";
	if(((Gnk_Button_Toggle *)sign_up.buttonList["male_toggle"])->toggle) {
		gender = "Nam";
	}
	if(((Gnk_Button_Toggle *)sign_up.buttonList["female_toggle"])->toggle) {
		gender = "Nu";
	}
	sign_up_return_value res = current_Data->taoTaiKhoan(
		(sign_up.textboxList["first_name_textbox"])->text,
		(sign_up.textboxList["surname_textbox"])->text,
		(sign_up.textboxList["date_textbox"])->text + "/" + 
		(sign_up.textboxList["month_textbox"])->text + "/" + 
		(sign_up.textboxList["year_textbox"])->text,
		gender,
		(sign_up.textboxList["username_textbox"])->text,
		(sign_up.textboxList["password_textbox"])->text
	);
	if(res == SIGN_UP_BLANK_INFO) {
		cout << "Blank info" << endl;
	}
	else if(res == SIGN_UP_USERNAME_EXISTED) {
		cout << "Username existed" << endl;
	}
	else if(res == SIGN_UP_SUCCESS) {
		current_frame = LOGIN_FRAME;
	}
}

void sign_up_frame_toggle_click(Gnk_Button *button) {
	Gnk_Button_Toggle *toggle = (Gnk_Button_Toggle *)button;
	if(male_toggle_enable == false && ((Gnk_Button_Toggle *) \
	gnk_Current_Frame ->buttonList["male_toggle"])->toggle == true) {
		((Gnk_Button_Toggle *)gnk_Current_Frame-> \
		buttonList["female_toggle"])->toggle = false;
		female_toggle_enable = false;
		male_toggle_enable = true;
	}
	else if(female_toggle_enable == false && ((Gnk_Button_Toggle *) \
	gnk_Current_Frame ->buttonList["female_toggle"])->toggle == true) {
		((Gnk_Button_Toggle *)gnk_Current_Frame-> \
		buttonList["male_toggle"])->toggle = false;
		male_toggle_enable = false;
		female_toggle_enable = true;
	}
	toggle->draw();
}

Gnk_Frame sign_up(sign_up_frame_draw);

// ---------------------------------------------------------
void guest_frame_draw(Gnk_Frame *frame) {
	frame->disable_all();
	gnk_Set_Background_Color(H_F3F2F2);

	gnk_Set_Object_Color(H_222831);
	gnk_Rectangle(Gnk_Point(0.0f, 800.0f), Gnk_Point(1600.0f, 900.0f));

	gnk_Set_Object_Color(H_222831);
	gnk_Rectangle(Gnk_Point(0.0f, 0.0f), Gnk_Point(430.0f, 800.0f));

	gnk_Set_Object_Color(H_7E7E81);
	gnk_Set_Line_Width(2.0f);
	gnk_Line(Gnk_Point(20.0f, 800.0f), Gnk_Point(1560.0f, 800.0f));

	gnk_Set_Object_Color(H_FFECB8);
	gnk_Set_Character_Font("helvetica-bold");
	gnk_Text("HOTEL DEL LUNA", Gnk_Point(40.0f, 830.0f), 40.0f);

	gnk_Set_Object_Color(H_FFFFFF);
	gnk_Set_Character_Font("helvetica");
	gnk_Text("Have a great day and enjoy your stay!", Gnk_Point(430.0f, 830.0f), 24.0f);

	frame->buttonList["logout_button"]->setAppear(true);
	frame->buttonList["search_room_button"]->setAppear(true);
	frame->buttonList["booking_infomation_button"]->setAppear(true);
	frame->buttonList["profile_button"]->setAppear(true);

	frame->buttonList["logout_button"]->display();
	frame->buttonList["search_room_button"]->display();
	frame->buttonList["booking_infomation_button"]->display();
	frame->buttonList["profile_button"]->display();

	if(option == SEARCH_ROOM) {
		frame->textboxList["check_in_textbox"]->setAppear(true);
		frame->textboxList["check_out_textbox"]->setAppear(true);
		frame->textboxList["number_of_guest_textbox"]->setAppear(true);
		frame->buttonList["lookup"]->setAppear(true);
		frame->listObjectList["search_room_list"]->setAppear(true);
		// Search box
		gnk_Set_Object_Color(H_F7C873);
		gnk_Rectangle(Gnk_Point(520.0f, 700.0f), Gnk_Point(1510.0f, 760.0f));
		// Vẽ các textbox
		gnk_Set_Object_Color(C_1A1A1D);
		frame->textboxList["check_in_textbox"]->display();
		frame->textboxList["check_out_textbox"]->display();
		frame->textboxList["number_of_guest_textbox"]->display();
		frame->buttonList["lookup"]->display();
		frame->listObjectList["search_room_list"]->draw();
		// Vẽ cái đường viền
		gnk_Set_Object_Color(C_1A1A1D);
		gnk_Set_Line_Width(2.0f);
		gnk_Rectangle(Gnk_Point(520.0f, 700.0f), Gnk_Point(1510.0f, 760.0f), false);
		gnk_Line(Gnk_Point(825.0f, 700.0f), Gnk_Point(825.0f, 760.0f));
		gnk_Line(Gnk_Point(1135.0f, 700.0f), Gnk_Point(1135.0f, 760.0f));
		gnk_Line(Gnk_Point(1445.0f, 700.0f), Gnk_Point(1445.0f, 760.0f));
		gnk_Line(Gnk_Point(430.0f, 680.0f), Gnk_Point(1600.0f, 680.0f));
		gnk_Set_Line_Width(1.0f);
	}
	else if(option == HISTORY_INFORMATION) {
		// Booking information
		frame->listObjectList["history_list"]->setAppear(true);
		frame->listObjectList["history_list"]->draw();
	}
	else if(option == PROFILE) {
		gnk_Set_Object_Color(H_000000);
		gnk_Rectangle(Gnk_Point(530.0f, 250.0f), Gnk_Point(1500.0f, 700.0f), false);
		gnk_Set_Object_Color(H_FFECB8);
		gnk_Rectangle(Gnk_Point(530.0f, 250.0f), Gnk_Point(1500.0f, 700.0f));

		gnk_Set_Object_Color(C_1A1A1D);
		gnk_Set_Character_Font("helvetica-bold");
		gnk_Text_Limited("My Profile", Gnk_Point(530.0f, 710.0f), 970.0f, 60.0f, 40.0f, GNK_TEXT_LEFT);
		
		if(current_guest_profile.gender == NAM) {
			gnk_Image(gnk_Image_List["man_icon"], Gnk_Point(560.0f, 370.0f), Gnk_Point(860.0f, 670.0f));
		}
		if(current_guest_profile.gender == NU) {
			gnk_Image(gnk_Image_List["woman_icon"], Gnk_Point(560.0f, 370.0f), Gnk_Point(860.0f, 670.0f));
		}

		gnk_Set_Object_Color(H_F3F2F2);
		gnk_Rounded_Rectangle(Gnk_Point(560.0f, 280.0f), Gnk_Point(860.0f, 340.0f), 20.0f);
		gnk_Set_Object_Color(H_404040);
		gnk_Text_Limited(current_guest_profile.username, Gnk_Point(560.0f, 294.0f), 300.0f, 40.0f, 24.0f, GNK_TEXT_CENTER);

		gnk_Text("ID:", Gnk_Point(940.0f, 600.0f), 24.0f);
		gnk_Text("Name:", Gnk_Point(940.0f, 550.0f), 24.0f);
		gnk_Text("Date of birth:", Gnk_Point(940.0f, 500.0f), 24.0f);
		gnk_Text("Phone number:", Gnk_Point(940.0f, 450.0f), 24.0f);
		gnk_Text("Gender:", Gnk_Point(940.0f, 400.0f), 24.0f);
		gnk_Text(current_guest_profile.ID, Gnk_Point(1140.0f, 600.0f), 24.0f);
		if(edit_profile) {
			frame->textboxList["profile_name_textbox"]->setAppear(true);
			frame->textboxList["profile_date_of_birth_textbox"]->setAppear(true);
			frame->textboxList["profile_phone_number_textbox"]->setAppear(true);
			frame->textboxList["profile_phone_number_textbox"]->setAppear(true);
			frame->textboxList["profile_gender_textbox"]->setAppear(true);
			frame->buttonList["save_profile_button"]->setAppear(true);

			frame->textboxList["profile_name_textbox"]->text = Utils::chuanHoaTen(frame->textboxList["profile_name_textbox"]->text);
			frame->textboxList["profile_name_textbox"]->display();
			frame->textboxList["profile_date_of_birth_textbox"]->display();
			frame->textboxList["profile_phone_number_textbox"]->display();
			frame->textboxList["profile_gender_textbox"]->display();
			frame->buttonList["save_profile_button"]->display();
		}
		else {
			gnk_Set_Object_Color(H_404040);
			gnk_Text(current_guest_profile.name, Gnk_Point(1140.0f, 550.0f), 24.0f);
			gnk_Text(current_guest_profile.date_of_birth, Gnk_Point(1140.0f, 500.0f), 24.0f);
			gnk_Text(current_guest_profile.phone_number, Gnk_Point(1140.0f, 450.0f), 24.0f);
			gnk_Text(Utils::genderToString(current_guest_profile.gender), Gnk_Point(1140.0f, 400.0f), 24.0f);
			frame->buttonList["change_profile_button"]->setAppear(true);
			frame->buttonList["change_profile_button"]->display();
		}
	}
	else if(option == BOOKING) {
		// Booking
		if(index_booking != -1) {
			gnk_Set_Object_Color(C_1A1A1D);
			gnk_Set_Character_Font("helvetica-bold");
			gnk_Text_Limited("Booking infomation", Gnk_Point(480.0f, 710.0f), 1030.0f, 60.0f, 40.0f, GNK_TEXT_LEFT);

			gnk_Set_Character_Font("helvetica");
			gnk_Set_Object_Color(H_FFFFFF);
			gnk_Rectangle(Gnk_Point(480.0f, 400.0f), Gnk_Point(1530.0f, 700.0f));
			gnk_Set_Object_Color(H_7E7E81);
			gnk_Rectangle(Gnk_Point(480.0f, 400.0f), Gnk_Point(780.0f, 700.0f));
			gnk_Image(gnk_Image_List[room_list[index_booking].type], Gnk_Point(480.0f, 400.0f), Gnk_Point(780.0f, 700.0f));
			gnk_Set_Object_Color(C_1A1A1D);
			gnk_Text("Loai Phong: ", Gnk_Point(820.0f, 650.0f), 24.0f);
			gnk_Text(room_list[index_booking].type, Gnk_Point(980.0f, 650.0f), 24.0f);
			gnk_Text("Loai Giuong: ", Gnk_Point(820.0f, 620.0f), 24.0f);
			gnk_Text(room_list[index_booking].bed_type, Gnk_Point(980.0f, 620.0f), 24.0f);
			gnk_Text("So Nguoi: ", Gnk_Point(820.0f, 590.0f), 24.0f);
			gnk_Text(room_list[index_booking].number_of_guest, Gnk_Point(980.0f, 590.0f), 24.0f);
			gnk_Text("Dien Tich: ", Gnk_Point(820.0f, 560.0f), 24.0f);
			gnk_Text(room_list[index_booking].area, Gnk_Point(980.0f, 560.0f), 24.0f);
			gnk_Text("Gia: ", Gnk_Point(820.0f, 530.0f), 24.0f);
			gnk_Text(room_list[index_booking].price, Gnk_Point(980.0f, 530.0f), 24.0f);
			gnk_Set_Line_Width(2.0f);
			gnk_Line(Gnk_Point(820.0f, 520.0f), Gnk_Point(1510.0f, 520.0f));
			gnk_Text_Multi_Line(room_list[index_booking].description, Gnk_Point(820.0f, 490.0f), 64, 10, 24);
			gnk_Text("So Luong: " + room_list[index_booking].amount, Gnk_Point(1360.0f, 650.0f), 24.0f);

			gnk_Set_Object_Color(H_FFFFFF);
			gnk_Rectangle(Gnk_Point(480.0f, 140.0f), Gnk_Point(1000.0f, 380.0f));

			glScissor(480, 150, 760, 230);
			glEnable(GL_SCISSOR_TEST);

			gnk_Set_Object_Color(C_1A1A1D);
			gnk_Set_Character_Font("helvetica-bold");
			gnk_Text("Danh sach phong trong:", Gnk_Point(510.0f, 330.0f), 24.0f);
			
			gnk_Set_Character_Font("helvetica");
			gnk_Text_Multi_Line(list_room_available, Gnk_Point(510.0f, 290.0f), 38, 10, 24);
			
			glDisable(GL_SCISSOR_TEST);

			gnk_Set_Object_Color(H_FFFFFF);
			gnk_Rectangle(Gnk_Point(1010.0f, 140.0f), Gnk_Point(1530.0f, 380.0f));

			gnk_Set_Object_Color(C_1A1A1D);
			gnk_Set_Character_Font("helvetica-bold");
			gnk_Text("Room choice:", Gnk_Point(1040.0f, 320.0f), 24.0f);
			
			frame->buttonList["back_to_search_room_button"]->setAppear(true);
			frame->buttonList["continue_booking_button"]->setAppear(true);
			frame->textboxList["room_choice_textbox"]->setAppear(true);

			frame->buttonList["back_to_search_room_button"]->display();
			frame->buttonList["continue_booking_button"]->display();
			frame->textboxList["room_choice_textbox"]->display();
		}
	}
	else if(option == BOOKING_PART_2) {
		// Booking part 2
		gnk_Set_Object_Color(C_1A1A1D);
		gnk_Set_Character_Font("helvetica-bold");
		gnk_Text_Limited("Booking infomation", Gnk_Point(480.0f, 710.0f), 1030.0f, 60.0f, 40.0f, GNK_TEXT_LEFT);

		gnk_Set_Character_Font("helvetica");
		gnk_Set_Object_Color(H_FFFFFF);
		gnk_Rectangle(Gnk_Point(480.0f, 400.0f), Gnk_Point(1530.0f, 700.0f));
		gnk_Set_Object_Color(H_7E7E81);
		gnk_Rectangle(Gnk_Point(480.0f, 400.0f), Gnk_Point(780.0f, 700.0f));
		gnk_Image(gnk_Image_List[room_list[index_booking].type], Gnk_Point(480.0f, 400.0f), Gnk_Point(780.0f, 700.0f));
		gnk_Set_Object_Color(C_1A1A1D);
		gnk_Text("Loai Phong: ", Gnk_Point(820.0f, 650.0f), 24.0f);
		gnk_Text(room_list[index_booking].type, Gnk_Point(980.0f, 650.0f), 24.0f);
		gnk_Text("Loai Giuong: ", Gnk_Point(820.0f, 620.0f), 24.0f);
		gnk_Text(room_list[index_booking].bed_type, Gnk_Point(980.0f, 620.0f), 24.0f);
		gnk_Text("So Nguoi: ", Gnk_Point(820.0f, 590.0f), 24.0f);
		gnk_Text(room_list[index_booking].number_of_guest, Gnk_Point(980.0f, 590.0f), 24.0f);
		gnk_Text("Dien Tich: ", Gnk_Point(820.0f, 560.0f), 24.0f);
		gnk_Text(room_list[index_booking].area, Gnk_Point(980.0f, 560.0f), 24.0f);
		gnk_Text("Gia: ", Gnk_Point(820.0f, 530.0f), 24.0f);
		gnk_Text(room_list[index_booking].price, Gnk_Point(980.0f, 530.0f), 24.0f);
		gnk_Set_Line_Width(2.0f);
		gnk_Line(Gnk_Point(820.0f, 520.0f), Gnk_Point(1510.0f, 520.0f));
		gnk_Text_Multi_Line(room_list[index_booking].description, Gnk_Point(820.0f, 490.0f), 64, 10, 24);
		gnk_Text("So Luong: " + room_list[index_booking].amount, Gnk_Point(1360.0f, 650.0f), 24.0f);

		gnk_Set_Object_Color(H_FFFFFF);
		gnk_Rectangle(Gnk_Point(480.0f, 140.0f), Gnk_Point(1530.0f, 380.0f));

		gnk_Set_Object_Color(C_1A1A1D);
		gnk_Set_Character_Font("helvetica-bold");
		gnk_Text("Xac nhan thong tin dat phong:", Gnk_Point(510.0f, 330.0f), 24.0f);

		gnk_Set_Character_Font("helvetica");
		gnk_Text("Ngay nhan phong: ", Gnk_Point(510.0f, 290.0f), 24.0f);
		gnk_Text(check_in_date_str, Gnk_Point(720.0f, 290.0f), 24.0f);
		gnk_Text("Ngay tra phong: ", Gnk_Point(510.0f, 260.0f), 24.0f);
		gnk_Text(check_out_date_str, Gnk_Point(720.0f, 260.0f), 24.0f);
		gnk_Text("So luong khach: ", Gnk_Point(510.0f, 230.0f), 24.0f);
		gnk_Text(number_of_guest_str, Gnk_Point(720.0f, 230.0f), 24.0f);
		gnk_Text("Ma phong: ", Gnk_Point(510.0f, 200.0f), 24.0f);
		gnk_Text(room_choice, Gnk_Point(720.0f, 200.0f), 24.0f);
		gnk_Text("Tong tien:" , Gnk_Point(510.0f, 170.0f), 24.0f);
		gnk_Text(booking_total_price, Gnk_Point(720.0f, 170.0f), 24.0f);

		frame->buttonList["back_to_search_room_button"]->setAppear(true);
		frame->buttonList["confirm_booking_button"]->setAppear(true);
		
		frame->buttonList["back_to_search_room_button"]->display();
		frame->buttonList["confirm_booking_button"]->display();
	}
	else if(option == BOOKING_DONE) {
		gnk_Set_Object_Color(C_1A1A1D);
		gnk_Set_Character_Font("helvetica-bold");
		gnk_Text_Limited("The room has been successfully booked!", Gnk_Point(430.0f, 370.0f), 1170.0f, 60.0f, 48.0f, GNK_TEXT_CENTER);
	}
}

void logout_button_click(Gnk_Button *button) {
	Gnk_Button_With_Text *buttonText = (Gnk_Button_With_Text *)button;
	Gnk_Color color = buttonText->color;
	buttonText->color = color - Gnk_Color(40, 40, 40);
	buttonText->draw();
	buttonText->color = color;
	current_Data->dangXuat();
	current_frame = LOGIN_FRAME;
}

void guest_frame_search_room_button_click(Gnk_Button *button) {
	Gnk_Button_With_Text *buttonText = (Gnk_Button_With_Text *)button;
	Gnk_Color color = buttonText->color;
	buttonText->color = color - Gnk_Color(40, 40, 40);
	buttonText->draw();
	buttonText->color = color;
	gnk_Current_Frame->clear_Textbox();
	search_room_list_enable = false;
	room_list_init = false;
	option = SEARCH_ROOM;
}

void guest_frame_booking_infomation_button_click(Gnk_Button *button) {
	Gnk_Button_With_Text *buttonText = (Gnk_Button_With_Text *)button;
	Gnk_Color color = buttonText->color;
	buttonText->color = color - Gnk_Color(40, 40, 40);
	buttonText->draw();
	buttonText->color = color;
	history_list_enable = true;
	history_list_init = false;
	gnk_Current_Frame->listObjectList["history_list"]->setCurrentPos(gnk_Current_Frame->listObjectList["history_list"]->getGroupHeight());
	option = HISTORY_INFORMATION;
}

void guest_frame_profile_button_click(Gnk_Button *button) {
	Gnk_Button_With_Text *buttonText = (Gnk_Button_With_Text *)button;
	Gnk_Color color = buttonText->color;
	buttonText->color = color - Gnk_Color(40, 40, 40);
	buttonText->draw();
	buttonText->color = color;
	option = PROFILE;
}

void guest_frame_search_room_list_process(Gnk_List_Object *list) {
	if(search_room_list_enable) {
		if(room_list_init == false) {
			room_list.clear();
			UI_input_buffer.str("");UI_input_buffer.clear();
			UI_output_buffer.str("");UI_output_buffer.clear();
			if(Utils::isDate(check_in_date_str) && Utils::isDate(check_out_date_str) && Utils::isNumberOnly(number_of_guest_str)) {
				UI_input_buffer << check_in_date_str << endl;
				UI_input_buffer << check_out_date_str << endl;
				UI_input_buffer << number_of_guest_str << endl;
			}
			else return;
			current_Data->list_Type_Room_Available();
			string line;
			while(getline(UI_output_buffer, line)) {
				room_type room;
				room.type = line;
				getline(UI_output_buffer, line);
				room.bed_type = line;
				getline(UI_output_buffer, line);
				room.number_of_guest = line;
				getline(UI_output_buffer, line);
				room.area = line;
				getline(UI_output_buffer, line);
				room.price = line;
				getline(UI_output_buffer, line);
				room.description = line;
				getline(UI_output_buffer, line); // Bỏ 1 dòng dư
				getline(UI_output_buffer, line);
				room.amount = line;
				room_list.push_back(room);
			}
			room_list_init = true;
		}
		list->setGroupHeight(list->toNextObject()*room_list.size());
		list->numOfObject = room_list.size();
		for(auto &it : list->buttonList) {
			if(it.button != nullptr) {
				Gnk_Point prev_A = it.button->A;
				Gnk_Point prev_B = it.button->B;
				for(int i = 0; i < list->numOfObject; ++i) {
					it.button->A = prev_A.translate(0.0f, - i * list->toNextObject());
					it.button->B = prev_B.translate(0.0f, - i * list->toNextObject());
					if(it.index_on_click == i) {
						index_selected_room = i;
						it.button->onClick = true;
					}
					else {
						it.button->onClick = false;
					}
					if(it.index_on_hover == i) {
						index_hover_room = i;
						it.button->onHover = true;
					}
					else {
						it.button->onHover = false;
					}
					it.button->display();
				}
				it.index_on_click = -1;
				it.button->A = prev_A;
				it.button->B = prev_B;
			}
		}
		for(int i = 0; i < room_list.size(); i++) {
			if(list->currentPos < list->object_start_position.y - i * list->toNextObject()) {
				continue;
			}
			if(list->object_height + list->object_start_position.y - i * list->toNextObject() < list->currentPos - list->getGroupHeight()) {
				break;
			}
			GLint scissorBox[4];
			glGetIntegerv(GL_SCISSOR_BOX, scissorBox);
			gnk_Scissor_2_object(
			Gnk_Point(gnk_Translate_X, gnk_Translate_Y - i * list->toNextObject()),
			Gnk_Point(gnk_Translate_X + list->object_width, gnk_Translate_Y - i * list->toNextObject() + list->object_height),
			list->A, list->B);
			gnk_Set_Object_Color(H_FFFFFF);
			gnk_Rectangle(Gnk_Point(0.0f, 0.0f - i * list->toNextObject()), Gnk_Point(list->object_width, 300.0f - i * list->toNextObject()));
			gnk_Set_Object_Color(H_7E7E81);
			gnk_Rectangle(Gnk_Point(0.0f, 0.0f - i * list->toNextObject()), Gnk_Point(list->object_height, 300.0f - i * list->toNextObject()));
			gnk_Image(gnk_Image_List[room_list[i].type], Gnk_Point(0.0f, 0.0f - i * list->toNextObject()), Gnk_Point(300.0f, 300.0f - i * list->toNextObject()));
			gnk_Set_Object_Color(C_1A1A1D);
			gnk_Text("Loai Phong: ", Gnk_Point(340.0f, 250.0f - i * list->toNextObject()), 24.0f);
			gnk_Text(room_list[i].type, Gnk_Point(500.0f, 250.0f - i * list->toNextObject()), 24.0f);
			gnk_Text("Loai Giuong: ", Gnk_Point(340.0f, 220.0f - i * list->toNextObject()), 24.0f);
			gnk_Text(room_list[i].bed_type, Gnk_Point(500.0f, 220.0f - i * list->toNextObject()), 24.0f);
			gnk_Text("So Nguoi: ", Gnk_Point(340.0f, 190.0f - i * list->toNextObject()), 24.0f);
			gnk_Text(room_list[i].number_of_guest, Gnk_Point(500.0f, 190.0f - i * list->toNextObject()), 24.0f);
			gnk_Text("Dien Tich: ", Gnk_Point(340.0f, 160.0f - i * list->toNextObject()), 24.0f);
			gnk_Text(room_list[i].area, Gnk_Point(500.0f, 160.0f - i * list->toNextObject()), 24.0f);
			gnk_Text("Gia: ", Gnk_Point(340.0f, 130.0f - i * list->toNextObject()), 24.0f);
			gnk_Text(room_list[i].price, Gnk_Point(500.0f, 130.0f - i * list->toNextObject()), 24.0f);
			gnk_Set_Line_Width(2.0f);
			gnk_Line(Gnk_Point(340.0f, 120.0f - i * list->toNextObject()), Gnk_Point(1030.0f, 120.0f - i * list->toNextObject()));
			gnk_Text_Multi_Line(room_list[i].description, Gnk_Point(340.0f, 90.0f - i * list->toNextObject()), 64, 10, 24);
			gnk_Text("So Luong: " + room_list[i].amount, Gnk_Point(880.0f, 250.0f - i * list->toNextObject()), 24.0f);
			if(index_hover_room == i) {
				gnk_Set_Object_Color(H_000000, 0.2f);
				glEnable(GL_BLEND);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				gnk_Rectangle(Gnk_Point(0.0f, 0.0f - i * list->toNextObject()), Gnk_Point(list->object_width, 300.0f - i * list->toNextObject()));
				glDisable(GL_BLEND);
			}
			if(index_selected_room == i) {
				gnk_Set_Object_Color(H_000000, 0.4f);
				glEnable(GL_BLEND);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				gnk_Rectangle(Gnk_Point(0.0f, 0.0f - i * list->toNextObject()), Gnk_Point(list->object_width, 300.0f - i * list->toNextObject()));
				glDisable(GL_BLEND);
			}
			glScissor(scissorBox[0], scissorBox[1], scissorBox[2], scissorBox[3]);
		}
		index_selected_room = -1;
		index_hover_room = -1;
	}
}

void guest_frame_lookup_button_image_click(Gnk_Button *button) {
	gnk_Current_Frame->listObjectList["search_room_list"]->currentPos = gnk_Current_Frame->listObjectList["search_room_list"]->getGroupHeight();
	check_in_date_str = gnk_Current_Frame->textboxList["check_in_textbox"]->text;
	check_out_date_str = gnk_Current_Frame->textboxList["check_out_textbox"]->text;
	number_of_guest_str = gnk_Current_Frame->textboxList["number_of_guest_textbox"]->text;
	if(Utils::isDate(check_in_date_str) && Utils::isDate(check_out_date_str) && Utils::isNumberOnly(number_of_guest_str)
	&& Utils::stringToDate(check_in_date_str) < Utils::stringToDate(check_out_date_str) && Utils::stringToDate(check_in_date_str) > time(0)) {
		cout << "Check in date: " << check_in_date_str << endl;
		cout << "Check out date: " << check_out_date_str << endl;
		cout << "Number of guest: " << number_of_guest_str << endl;
		search_room_list_enable = true;
		room_list_init = false;
	}
	else {
		room_list.clear();
		cout << "Invalid date" << endl;
		search_room_list_enable = false;
	}
	button->draw();
}

void guest_frame_change_frofile_button_click(Gnk_Button *button) {
	Gnk_Button_With_Text *buttonText = (Gnk_Button_With_Text *)button;
	Gnk_Color color = buttonText->color;
	buttonText->color = color + Gnk_Color(40, 40, 40);
	buttonText->draw();
	buttonText->color = color;
	edit_profile = true;
	gnk_Current_Frame->textboxList["profile_name_textbox"]->text = current_guest_profile.name;
	gnk_Current_Frame->textboxList["profile_date_of_birth_textbox"]->text = current_guest_profile.date_of_birth;
	gnk_Current_Frame->textboxList["profile_phone_number_textbox"]->text = current_guest_profile.phone_number;
	gnk_Current_Frame->textboxList["profile_gender_textbox"]->text = Utils::genderToString(current_guest_profile.gender);
}

void guest_frame_save_profile_button_click(Gnk_Button *button) {
	Gnk_Button_With_Text *buttonText = (Gnk_Button_With_Text *)button;
	Gnk_Color color = buttonText->color;
	buttonText->color = color + Gnk_Color(40, 40, 40);
	buttonText->draw();
	buttonText->color = color;
	edit_profile = false;
	current_guest_profile.name = gnk_Current_Frame->textboxList["profile_name_textbox"]->text;
	current_guest_profile.date_of_birth = gnk_Current_Frame->textboxList["profile_date_of_birth_textbox"]->text;
	current_guest_profile.phone_number = gnk_Current_Frame->textboxList["profile_phone_number_textbox"]->text;
	current_guest_profile.gender = Utils::stringToGender(gnk_Current_Frame->textboxList["profile_gender_textbox"]->text);
	
	UI_input_buffer.str("");UI_input_buffer.clear();
	UI_output_buffer.str("");UI_output_buffer.clear();
	UI_input_buffer << 1 << endl;
	UI_input_buffer << current_guest_profile.name << endl;
	UI_input_buffer << 2 << endl;
	UI_input_buffer << current_guest_profile.date_of_birth << endl;
	UI_input_buffer << 3 << endl;
	UI_input_buffer << current_guest_profile.phone_number << endl;
	UI_input_buffer << 4 << endl;
	UI_input_buffer << Utils::genderToString(current_guest_profile.gender) << endl;
	UI_input_buffer << 5 << endl;
	current_Data->requestHandling(CHANGE_PROFILE);
}

void guest_frame_select_type_room_button_click(Gnk_Button *button) {
	Gnk_Button_With_Text *buttonText = (Gnk_Button_With_Text *)button;
	buttonText->draw();
	index_booking = index_selected_room;
	UI_input_buffer.str("");UI_input_buffer.clear();
	UI_output_buffer.str("");UI_output_buffer.clear();
	list_room_available = "";
	UI_input_buffer << check_in_date_str << endl;
	UI_input_buffer << check_out_date_str << endl;
	UI_input_buffer << number_of_guest_str << endl;
	UI_input_buffer << room_list[index_booking].type << endl;
	current_Data->list_Room_Available();
	string room_available;
	bool first = true;
	while(getline(UI_output_buffer, room_available)) {
		list_room_choice.push_back(room_available);
		if(first)list_room_available = room_available;
		else list_room_available += ", " + room_available;
		first = false;
	}
	gnk_Current_Frame->clear_Textbox();
	staff_booking_guest_ID_not_exist = false;
	option = BOOKING;
}

void guest_frame_back_to_search_room_button_click(Gnk_Button *button) {
	Gnk_Button_With_Text *buttonText = (Gnk_Button_With_Text *)button;
	Gnk_Color color = buttonText->color;
	buttonText->color = color + Gnk_Color(40, 40, 40);
	buttonText->draw();
	buttonText->color = color;
	if(option == BOOKING) {
		index_booking = -1;
		option = SEARCH_ROOM;
	}	
	else if(option == BOOKING_PART_2) {
		gnk_Current_Frame->clear_Textbox();
		staff_booking_guest_ID_not_exist = false;
		option = BOOKING;
	}
}

void guest_frame_continue_booking_button_click(Gnk_Button *button) {
	Gnk_Button_With_Text *buttonText = (Gnk_Button_With_Text *)button;
	Gnk_Color color = buttonText->color;
	buttonText->color = color + Gnk_Color(40, 40, 40);
	buttonText->draw();
	buttonText->color = color;
	room_choice = gnk_Current_Frame->textboxList["room_choice_textbox"]->text;
	bool check = false;
	for(auto &it : list_room_choice) {
		if(it == room_choice) {
			check = true;
			break;
		}
	}
	
	if(current_Data->getCurrentRole() == KHACHHANG) {
		if(check) {
			DatPhong dp("0", 
			Utils::stringToDate(check_in_date_str), 
			Utils::stringToDate(check_out_date_str), 
			Utils::stringToInt(number_of_guest_str), 
			Utils::getOnlyNumber(room_list[index_booking].price));
			booking_total_price = Utils::chuanHoaSo(Utils::intToString(dp.tongTien())) + " VND";

			option = BOOKING_PART_2;
		}
		else {
			cout << "Invalid room choice" << endl;
		}
	}
	else if(current_Data->getCurrentRole() == NHANVIEN) {
		if(check) {
			if(current_Data->GuestExist(gnk_Current_Frame->textboxList["guest_ID_textbox"]->text)) {
				DatPhong dp("0",
				Utils::stringToDate(check_in_date_str), 
				Utils::stringToDate(check_out_date_str), 
				Utils::stringToInt(number_of_guest_str), 
				Utils::getOnlyNumber(room_list[index_booking].price));
				booking_total_price = Utils::chuanHoaSo(Utils::intToString(dp.tongTien())) + " VND";
				option = BOOKING_PART_2;
			}
			else {
				staff_booking_guest_ID_not_exist = true;
			}
		}
		else {
			cout << "Invalid room choice" << endl;
		}
	}
}

void guest_frame_confirm_booking_button_click(Gnk_Button *button) {
	Gnk_Button_With_Text *buttonText = (Gnk_Button_With_Text *)button;
	Gnk_Color color = buttonText->color;
	buttonText->color = color + Gnk_Color(40, 40, 40);
	buttonText->draw();
	buttonText->color = color;

	UI_input_buffer.str("");UI_input_buffer.clear();
	UI_output_buffer.str("");UI_output_buffer.clear();
	if(current_Data->getCurrentRole() == KHACHHANG) {
		UI_input_buffer << check_in_date_str << endl;
		UI_input_buffer << check_out_date_str << endl;
		UI_input_buffer << number_of_guest_str << endl;
		UI_input_buffer << room_list[index_booking].type << endl;
		UI_input_buffer << room_choice << endl;
	}
	else if(current_Data->getCurrentRole() == NHANVIEN) {
		UI_input_buffer << check_in_date_str << endl;
		UI_input_buffer << check_out_date_str << endl;
		UI_input_buffer << number_of_guest_str << endl;
		UI_input_buffer << room_list[index_booking].type << endl;
		UI_input_buffer << room_choice << endl;
		UI_input_buffer << "1" << endl;
		UI_input_buffer << gnk_Current_Frame->textboxList["guest_ID_textbox"]->text << endl;
	}
	else return;
	current_Data->requestHandling(USER_BOOK_ROOM);
	option = BOOKING_DONE;
}

void guest_frame_history_list_process(Gnk_List_Object *list) {
	if(history_list_enable) {
		if(history_list_init == false) {
			history_booking_list.clear();
			UI_input_buffer.str("");UI_input_buffer.clear();
			UI_output_buffer.str("");UI_output_buffer.clear();

			current_Data->requestHandling(USER_BOOK_ROOM_HISTORY);
			string line;
			while(getline(UI_output_buffer, line)) {
				history_booking history;
				history.ID = line;
				getline(UI_output_buffer, line);
				history.roomtype = line;
				getline(UI_output_buffer, line);
				history.roomID = line;
				getline(UI_output_buffer, line); // skip ID KhachHang
				getline(UI_output_buffer, line);
				history.check_in_date = line;
				getline(UI_output_buffer, line);
				history.check_out_date = line;
				getline(UI_output_buffer, line);
				history.number_of_guest = line;
				getline(UI_output_buffer, line);
				history.price_per_night = line;
				getline(UI_output_buffer, line);
				history.total_price = line;
				history_booking_list.push_back(history);
			}
			history_list_init = true;
		}

		list->setGroupHeight(list->toNextObject()*history_booking_list.size());
		list->numOfObject = history_booking_list.size();
		for(int i = 0; i < history_booking_list.size(); i++) {
			if(list->currentPos < list->object_start_position.y - i * list->toNextObject()) {
				continue;
			}
			if(list->object_height + list->object_start_position.y - i * list->toNextObject() < list->currentPos - list->getGroupHeight()) {
				break;
			}
			gnk_Set_Object_Color(H_FFFFFF);
			gnk_Rectangle(Gnk_Point(0.0f, 0.0f - i * list->toNextObject()), Gnk_Point(list->object_width, 300.0f - i * list->toNextObject()));
			gnk_Set_Object_Color(H_7E7E81);
			gnk_Rectangle(Gnk_Point(0.0f, 0.0f - i * list->toNextObject()), Gnk_Point(list->object_height, 300.0f - i * list->toNextObject()));
			gnk_Image(gnk_Image_List[history_booking_list[i].roomtype], Gnk_Point(0.0f, 0.0f - i * list->toNextObject()), Gnk_Point(300.0f, 300.0f - i * list->toNextObject()));
			gnk_Set_Object_Color(C_1A1A1D);
			gnk_Text("Ma Dat Phong: ", Gnk_Point(340.0f, 250.0f - i * list->toNextObject()), 24.0f);
			gnk_Text(history_booking_list[i].ID, Gnk_Point(560.0f, 250.0f - i * list->toNextObject()), 24.0f);
			gnk_Text("Loai Phong: ", Gnk_Point(340.0f, 220.0f - i * list->toNextObject()), 24.0f);
			gnk_Text(history_booking_list[i].roomtype, Gnk_Point(560.0f, 220.0f - i * list->toNextObject()), 24.0f);
			gnk_Text("Ma Phong: ", Gnk_Point(340.0f, 190.0f - i * list->toNextObject()), 24.0f);
			gnk_Text(history_booking_list[i].roomID, Gnk_Point(560.0f, 190.0f - i * list->toNextObject()), 24.0f);
			gnk_Text("Ngay Nhan Phong: ", Gnk_Point(340.0f, 160.0f - i * list->toNextObject()), 24.0f);
			gnk_Text(history_booking_list[i].check_in_date, Gnk_Point(560.0f, 160.0f - i * list->toNextObject()), 24.0f);
			gnk_Text("Ngay Tra Phong: ", Gnk_Point(340.0f, 130.0f - i * list->toNextObject()), 24.0f);
			gnk_Text(history_booking_list[i].check_out_date, Gnk_Point(560.0f, 130.0f - i * list->toNextObject()), 24.0f);
			gnk_Text("So Luong Khach: ", Gnk_Point(340.0f, 100.0f - i * list->toNextObject()), 24.0f);
			gnk_Text(history_booking_list[i].number_of_guest, Gnk_Point(560.0f, 100.0f - i * list->toNextObject()), 24.0f);
			gnk_Text("Gia Tien: ", Gnk_Point(340.0f, 70.0f - i * list->toNextObject()), 24.0f);
			gnk_Text(history_booking_list[i].price_per_night, Gnk_Point(560.0f, 70.0f - i * list->toNextObject()), 24.0f);
			gnk_Text("Tong tien: ", Gnk_Point(340.0f, 40.0f - i * list->toNextObject()), 24.0f);
			gnk_Text(history_booking_list[i].total_price, Gnk_Point(560.0f, 40.0f - i * list->toNextObject()), 24.0f);
		}
	}
}

Gnk_Frame guest(guest_frame_draw);
// ---------------------------------------------------------
void staff_frame_draw(Gnk_Frame *frame) {
	frame->disable_all();
	gnk_Set_Background_Color(H_F3F2F2);

	gnk_Set_Object_Color(H_222831);
	gnk_Rectangle(Gnk_Point(0.0f, 800.0f), Gnk_Point(1600.0f, 900.0f));

	gnk_Set_Object_Color(H_222831);
	gnk_Rectangle(Gnk_Point(0.0f, 0.0f), Gnk_Point(430.0f, 800.0f));

	gnk_Set_Object_Color(H_7E7E81);
	gnk_Set_Line_Width(2.0f);
	gnk_Line(Gnk_Point(20.0f, 800.0f), Gnk_Point(1560.0f, 800.0f));

	gnk_Set_Object_Color(H_FFECB8);
	gnk_Set_Character_Font("helvetica-bold");
	gnk_Text("HOTEL DEL LUNA", Gnk_Point(40.0f, 830.0f), 40.0f);

	gnk_Set_Object_Color(H_FFFFFF);
	gnk_Set_Character_Font("helvetica");
	gnk_Text("Welcome, Hotel Del Luna's Staff!", Gnk_Point(430.0f, 830.0f), 24.0f);
	
	frame->buttonList["logout_button"]->setAppear(true);
	frame->buttonList["search_room_button"]->setAppear(true);
	frame->buttonList["booking_infomation_button"]->setAppear(true);
	frame->buttonList["guest_infomation_button"]->setAppear(true);
	frame->buttonList["type_room_infomation_button"]->setAppear(true);
	frame->buttonList["room_information_button"]->setAppear(true);
	frame->buttonList["create_guest_button"]->setAppear(true);

	frame->buttonList["logout_button"]->display();
	frame->buttonList["search_room_button"]->display();
	frame->buttonList["booking_infomation_button"]->display();
	frame->buttonList["guest_infomation_button"]->display();
	frame->buttonList["type_room_infomation_button"]->display();
	frame->buttonList["room_information_button"]->display();
	frame->buttonList["create_guest_button"]->display();

	if(option == SEARCH_ROOM) {
		frame->textboxList["check_in_textbox"]->setAppear(true);
		frame->textboxList["check_out_textbox"]->setAppear(true);
		frame->textboxList["number_of_guest_textbox"]->setAppear(true);
		frame->buttonList["lookup"]->setAppear(true);
		frame->listObjectList["search_room_list"]->setAppear(true);
		// Search box
		gnk_Set_Object_Color(H_F7C873);
		gnk_Rectangle(Gnk_Point(520.0f, 700.0f), Gnk_Point(1510.0f, 760.0f));
		// Vẽ các textbox
		gnk_Set_Object_Color(C_1A1A1D);
		frame->textboxList["check_in_textbox"]->display();
		frame->textboxList["check_out_textbox"]->display();
		frame->textboxList["number_of_guest_textbox"]->display();
		frame->buttonList["lookup"]->display();
		frame->listObjectList["search_room_list"]->draw();
		// Vẽ cái đường viền
		gnk_Set_Object_Color(C_1A1A1D);
		gnk_Set_Line_Width(2.0f);
		gnk_Rectangle(Gnk_Point(520.0f, 700.0f), Gnk_Point(1510.0f, 760.0f), false);
		gnk_Line(Gnk_Point(825.0f, 700.0f), Gnk_Point(825.0f, 760.0f));
		gnk_Line(Gnk_Point(1135.0f, 700.0f), Gnk_Point(1135.0f, 760.0f));
		gnk_Line(Gnk_Point(1445.0f, 700.0f), Gnk_Point(1445.0f, 760.0f));
		gnk_Line(Gnk_Point(430.0f, 680.0f), Gnk_Point(1600.0f, 680.0f));
		gnk_Set_Line_Width(1.0f);
	}
	else if(option == STAFF_BOOKING_INFO) {
		frame->listObjectList["booking_info_list"]->setAppear(true);
		frame->listObjectList["booking_info_list"]->draw();
	}
	else if(option == STAFF_GUEST_INFO) {
		frame->listObjectList["guest_info_list"]->setAppear(true);
		frame->listObjectList["guest_info_list"]->draw();
	}
	else if(option == STAFF_TYPE_ROOM_INFO) {
		frame->listObjectList["type_room_info_list"]->setAppear(true);
		frame->listObjectList["type_room_info_list"]->draw();
	}
	else if(option == STAFF_ROOM_INFO) {
		frame->listObjectList["room_info_list"]->setAppear(true);
		frame->listObjectList["room_info_list"]->draw();
	}
	else if(option == STAFF_CREATE_GUEST) {

		gnk_Set_Object_Color(H_FFFFFF);
		gnk_Rectangle(Gnk_Point(560.0f, 50.0f), Gnk_Point(1400.0f, 765.0f));

		gnk_Set_Object_Color(H_404040);
		gnk_Set_Character_Font("helvetica-bold");
		gnk_Text("Create new guest!", Gnk_Point(630.0f, 680.0f), 24.0f);
		gnk_Set_Character_Font("helvetica");
		gnk_Text("Date of birth", Gnk_Point(630.0f, 520.0f), 24.0f);
		gnk_Text("Gender", Gnk_Point(630.0f, 400.0f), 24.0f);
		gnk_Text("Phone number", Gnk_Point(630.0f, 280.0f), 24.0f);

		frame->textboxList["first_name_textbox"]->setAppear(true);
		frame->textboxList["surname_textbox"]->setAppear(true);
		frame->textboxList["date_textbox"]->setAppear(true);
		frame->textboxList["month_textbox"]->setAppear(true);
		frame->textboxList["year_textbox"]->setAppear(true);
		frame->textboxList["phone_number_textbox"]->setAppear(true);
		frame->buttonList["male_toggle"]->setAppear(true);
		frame->buttonList["female_toggle"]->setAppear(true);
		frame->buttonList["create_guess_button"]->setAppear(true);
		
		frame->textboxList["first_name_textbox"]->display();
		frame->textboxList["surname_textbox"]->display();
		frame->textboxList["date_textbox"]->display();
		frame->textboxList["month_textbox"]->display();
		frame->textboxList["year_textbox"]->display();
		frame->textboxList["phone_number_textbox"]->display();
		frame->buttonList["male_toggle"]->display();
		frame->buttonList["female_toggle"]->display();
		frame->buttonList["create_guess_button"]->display();
	}
	else if(option == BOOKING) {
		// Booking
		if(index_booking != -1) {
			gnk_Set_Object_Color(C_1A1A1D);
			gnk_Set_Character_Font("helvetica-bold");
			gnk_Text_Limited("Booking infomation", Gnk_Point(480.0f, 710.0f), 1030.0f, 60.0f, 40.0f, GNK_TEXT_LEFT);

			gnk_Set_Character_Font("helvetica");
			gnk_Set_Object_Color(H_FFFFFF);
			gnk_Rectangle(Gnk_Point(480.0f, 400.0f), Gnk_Point(1530.0f, 700.0f));
			gnk_Set_Object_Color(H_7E7E81);
			gnk_Rectangle(Gnk_Point(480.0f, 400.0f), Gnk_Point(780.0f, 700.0f));
			gnk_Image(gnk_Image_List[room_list[index_booking].type], Gnk_Point(480.0f, 400.0f), Gnk_Point(780.0f, 700.0f));
			gnk_Set_Object_Color(C_1A1A1D);
			gnk_Text("Loai Phong: ", Gnk_Point(820.0f, 650.0f), 24.0f);
			gnk_Text(room_list[index_booking].type, Gnk_Point(980.0f, 650.0f), 24.0f);
			gnk_Text("Loai Giuong: ", Gnk_Point(820.0f, 620.0f), 24.0f);
			gnk_Text(room_list[index_booking].bed_type, Gnk_Point(980.0f, 620.0f), 24.0f);
			gnk_Text("So Nguoi: ", Gnk_Point(820.0f, 590.0f), 24.0f);
			gnk_Text(room_list[index_booking].number_of_guest, Gnk_Point(980.0f, 590.0f), 24.0f);
			gnk_Text("Dien Tich: ", Gnk_Point(820.0f, 560.0f), 24.0f);
			gnk_Text(room_list[index_booking].area, Gnk_Point(980.0f, 560.0f), 24.0f);
			gnk_Text("Gia: ", Gnk_Point(820.0f, 530.0f), 24.0f);
			gnk_Text(room_list[index_booking].price, Gnk_Point(980.0f, 530.0f), 24.0f);
			gnk_Set_Line_Width(2.0f);
			gnk_Line(Gnk_Point(820.0f, 520.0f), Gnk_Point(1510.0f, 520.0f));
			gnk_Text_Multi_Line(room_list[index_booking].description, Gnk_Point(820.0f, 490.0f), 64, 10, 24);
			gnk_Text("So Luong: " + room_list[index_booking].amount, Gnk_Point(1360.0f, 650.0f), 24.0f);

			gnk_Set_Object_Color(H_FFFFFF);
			gnk_Rectangle(Gnk_Point(480.0f, 140.0f), Gnk_Point(1000.0f, 380.0f));

			glScissor(480, 150, 760, 230);
			glEnable(GL_SCISSOR_TEST);

			gnk_Set_Object_Color(C_1A1A1D);
			gnk_Set_Character_Font("helvetica-bold");
			gnk_Text("Danh sach phong trong:", Gnk_Point(510.0f, 330.0f), 24.0f);
			
			gnk_Set_Character_Font("helvetica");
			gnk_Text_Multi_Line(list_room_available, Gnk_Point(510.0f, 290.0f), 38, 10, 24);
			
			glDisable(GL_SCISSOR_TEST);

			gnk_Set_Object_Color(H_FFFFFF);
			gnk_Rectangle(Gnk_Point(1010.0f, 140.0f), Gnk_Point(1530.0f, 380.0f));

			gnk_Set_Object_Color(C_1A1A1D);
			gnk_Set_Character_Font("helvetica-bold");
			gnk_Text("Room choice:", Gnk_Point(1040.0f, 320.0f), 24.0f);
			gnk_Text("Guest ID:", Gnk_Point(1040.0f, 250.0f), 24.0f);
			
			frame->buttonList["back_to_search_room_button"]->setAppear(true);
			frame->buttonList["continue_booking_button"]->setAppear(true);
			frame->textboxList["room_choice_textbox"]->setAppear(true);
			frame->textboxList["guest_ID_textbox"]->setAppear(true);

			frame->buttonList["back_to_search_room_button"]->display();
			frame->buttonList["continue_booking_button"]->display();
			frame->textboxList["room_choice_textbox"]->display();
			frame->textboxList["guest_ID_textbox"]->display();

			if(staff_booking_guest_ID_not_exist) {
				gnk_Set_Object_Color(H_FF0000);
				gnk_Text("Guest ID not exist", Gnk_Point(1040.0f, 180.0f), 24.0f);
			}
		}
	}
	else if(option == BOOKING_PART_2) {
		// Booking part 2
		gnk_Set_Object_Color(C_1A1A1D);
		gnk_Set_Character_Font("helvetica-bold");
		gnk_Text_Limited("Booking infomation", Gnk_Point(480.0f, 710.0f), 1030.0f, 60.0f, 40.0f, GNK_TEXT_LEFT);

		gnk_Set_Character_Font("helvetica");
		gnk_Set_Object_Color(H_FFFFFF);
		gnk_Rectangle(Gnk_Point(480.0f, 400.0f), Gnk_Point(1530.0f, 700.0f));
		gnk_Set_Object_Color(H_7E7E81);
		gnk_Rectangle(Gnk_Point(480.0f, 400.0f), Gnk_Point(780.0f, 700.0f));
		gnk_Image(gnk_Image_List[room_list[index_booking].type], Gnk_Point(480.0f, 400.0f), Gnk_Point(780.0f, 700.0f));
		gnk_Set_Object_Color(C_1A1A1D);
		gnk_Text("Loai Phong: ", Gnk_Point(820.0f, 650.0f), 24.0f);
		gnk_Text(room_list[index_booking].type, Gnk_Point(980.0f, 650.0f), 24.0f);
		gnk_Text("Loai Giuong: ", Gnk_Point(820.0f, 620.0f), 24.0f);
		gnk_Text(room_list[index_booking].bed_type, Gnk_Point(980.0f, 620.0f), 24.0f);
		gnk_Text("So Nguoi: ", Gnk_Point(820.0f, 590.0f), 24.0f);
		gnk_Text(room_list[index_booking].number_of_guest, Gnk_Point(980.0f, 590.0f), 24.0f);
		gnk_Text("Dien Tich: ", Gnk_Point(820.0f, 560.0f), 24.0f);
		gnk_Text(room_list[index_booking].area, Gnk_Point(980.0f, 560.0f), 24.0f);
		gnk_Text("Gia: ", Gnk_Point(820.0f, 530.0f), 24.0f);
		gnk_Text(room_list[index_booking].price, Gnk_Point(980.0f, 530.0f), 24.0f);
		gnk_Set_Line_Width(2.0f);
		gnk_Line(Gnk_Point(820.0f, 520.0f), Gnk_Point(1510.0f, 520.0f));
		gnk_Text_Multi_Line(room_list[index_booking].description, Gnk_Point(820.0f, 490.0f), 64, 10, 24);
		gnk_Text("So Luong: " + room_list[index_booking].amount, Gnk_Point(1360.0f, 650.0f), 24.0f);

		gnk_Set_Object_Color(H_FFFFFF);
		gnk_Rectangle(Gnk_Point(480.0f, 140.0f), Gnk_Point(1530.0f, 380.0f));

		gnk_Set_Object_Color(C_1A1A1D);
		gnk_Set_Character_Font("helvetica-bold");
		gnk_Text("Xac nhan thong tin dat phong:", Gnk_Point(510.0f, 330.0f), 24.0f);

		gnk_Set_Character_Font("helvetica");
		gnk_Text("Ngay nhan phong: ", Gnk_Point(510.0f, 290.0f), 24.0f);
		gnk_Text(check_in_date_str, Gnk_Point(720.0f, 290.0f), 24.0f);
		gnk_Text("Ngay tra phong: ", Gnk_Point(510.0f, 260.0f), 24.0f);
		gnk_Text(check_out_date_str, Gnk_Point(720.0f, 260.0f), 24.0f);
		gnk_Text("So luong khach: ", Gnk_Point(510.0f, 230.0f), 24.0f);
		gnk_Text(number_of_guest_str, Gnk_Point(720.0f, 230.0f), 24.0f);
		gnk_Text("Ma phong: ", Gnk_Point(510.0f, 200.0f), 24.0f);
		gnk_Text(room_choice, Gnk_Point(720.0f, 200.0f), 24.0f);
		gnk_Text("Tong tien:" , Gnk_Point(510.0f, 170.0f), 24.0f);
		gnk_Text(booking_total_price, Gnk_Point(720.0f, 170.0f), 24.0f);

		frame->buttonList["back_to_search_room_button"]->setAppear(true);
		frame->buttonList["confirm_booking_button"]->setAppear(true);
		
		frame->buttonList["back_to_search_room_button"]->display();
		frame->buttonList["confirm_booking_button"]->display();
	}
	else if(option == BOOKING_DONE) {
		gnk_Set_Object_Color(C_1A1A1D);
		gnk_Set_Character_Font("helvetica-bold");
		gnk_Text_Limited("The room has been successfully booked!", Gnk_Point(430.0f, 370.0f), 1170.0f, 60.0f, 48.0f, GNK_TEXT_CENTER);
	}
	else if(option == STAFF_CREATE_GUEST_DONE) {
		gnk_Set_Object_Color(C_1A1A1D);
		gnk_Set_Character_Font("helvetica-bold");
		gnk_Text_Limited("The guest has been successfully created!", Gnk_Point(430.0f, 370.0f), 1170.0f, 60.0f, 48.0f, GNK_TEXT_CENTER);

	}
}

void staff_frame_booking_infomation_button_click(Gnk_Button *button) {
	Gnk_Button_With_Text *buttonText = (Gnk_Button_With_Text *)button;
	Gnk_Color color = buttonText->color;
	buttonText->color = color - Gnk_Color(40, 40, 40);
	buttonText->draw();
	buttonText->color = color;
	booking_info_list_enable = true;
	booking_info_list_init = false;
	gnk_Current_Frame->listObjectList["booking_info_list"]->setCurrentPos(gnk_Current_Frame->listObjectList["booking_info_list"]->getGroupHeight());
	option = STAFF_BOOKING_INFO;
}

void staff_frame_guest_infomation_button_click(Gnk_Button *button) {
	Gnk_Button_With_Text *buttonText = (Gnk_Button_With_Text *)button;
	Gnk_Color color = buttonText->color;
	buttonText->color = color - Gnk_Color(40, 40, 40);
	buttonText->draw();
	buttonText->color = color;
	guest_info_list_enable = true;
	guest_info_list_init = false;
	gnk_Current_Frame->listObjectList["guest_info_list"]->setCurrentPos(gnk_Current_Frame->listObjectList["guest_info_list"]->getGroupHeight());
	option = STAFF_GUEST_INFO;
}

void staff_frame_type_room_infomation_button_click(Gnk_Button *button) {
	Gnk_Button_With_Text *buttonText = (Gnk_Button_With_Text *)button;
	Gnk_Color color = buttonText->color;
	buttonText->color = color - Gnk_Color(40, 40, 40);
	buttonText->draw();
	buttonText->color = color;
	type_room_info_list_enable = true;
	type_room_info_list_init = false;
	gnk_Current_Frame->listObjectList["type_room_info_list"]->setCurrentPos(gnk_Current_Frame->listObjectList["type_room_info_list"]->getGroupHeight());
	option = STAFF_TYPE_ROOM_INFO;
}

void staff_frame_room_information_button_click(Gnk_Button *button) {
	Gnk_Button_With_Text *buttonText = (Gnk_Button_With_Text *)button;
	Gnk_Color color = buttonText->color;
	buttonText->color = color - Gnk_Color(40, 40, 40);
	buttonText->draw();
	buttonText->color = color;
	room_info_list_enable = true;
	room_info_list_init = false;
	gnk_Current_Frame->listObjectList["room_info_list"]->setCurrentPos(gnk_Current_Frame->listObjectList["room_info_list"]->getGroupHeight());
	option = STAFF_ROOM_INFO;
}

void staff_frame_create_guest_button_click(Gnk_Button *button) {
	Gnk_Button_With_Text *buttonText = (Gnk_Button_With_Text *)button;
	Gnk_Color color = buttonText->color;
	buttonText->color = color - Gnk_Color(40, 40, 40);
	buttonText->draw();
	buttonText->color = color;
	gnk_Current_Frame->clear_Textbox();
	((Gnk_Button_Toggle *)staff.buttonList["male_toggle"])->toggle = false;
	((Gnk_Button_Toggle *)staff.buttonList["female_toggle"])->toggle = false;
	option = STAFF_CREATE_GUEST;
	staff_create_guest_success = true;
}

void staff_frame_booking_info_list_process(Gnk_List_Object *list) {
	if(booking_info_list_enable) {
		if(booking_info_list_init == false) {
			booking_info_list.clear();
			UI_input_buffer.str("");UI_input_buffer.clear();
			UI_output_buffer.str("");UI_output_buffer.clear();

			current_Data->requestHandling(PRINT_DSDP);
			string line;
			while(getline(UI_output_buffer, line)) {
				booking_info info;
				info.ID = line;
				getline(UI_output_buffer, line);
				info.roomtype = line;
				getline(UI_output_buffer, line);
				info.roomID = line;
				getline(UI_output_buffer, line);
				info.guestID = line; 
				getline(UI_output_buffer, line);
				info.check_in_date = line;
				getline(UI_output_buffer, line);
				info.check_out_date = line;
				getline(UI_output_buffer, line);
				info.number_of_guest = line;
				getline(UI_output_buffer, line);
				info.price_per_night = line;
				getline(UI_output_buffer, line);
				info.total_price = line;
				booking_info_list.push_back(info);
			}
			booking_info_list_init = true;
		}

		list->setGroupHeight(list->toNextObject()*booking_info_list.size());
		list->numOfObject = booking_info_list.size();
		for(int i = 0; i < booking_info_list.size(); i++) {
			if(list->currentPos < list->object_start_position.y - i * list->toNextObject()) {
				continue;
			}
			if(list->object_height + list->object_start_position.y - i * list->toNextObject() < list->currentPos - list->getGroupHeight()) {
				break;
			}
			gnk_Set_Object_Color(H_FFFFFF);
			gnk_Rectangle(Gnk_Point(0.0f, 0.0f - i * list->toNextObject()), Gnk_Point(list->object_width, 300.0f - i * list->toNextObject()));
			gnk_Set_Object_Color(H_7E7E81);
			gnk_Rectangle(Gnk_Point(0.0f, 0.0f - i * list->toNextObject()), Gnk_Point(list->object_height, 300.0f - i * list->toNextObject()));
			gnk_Image(gnk_Image_List[booking_info_list[i].roomtype], Gnk_Point(0.0f, 0.0f - i * list->toNextObject()), Gnk_Point(300.0f, 300.0f - i * list->toNextObject()));
			gnk_Set_Object_Color(C_1A1A1D);
			gnk_Text("Ma Dat Phong: ", Gnk_Point(340.0f, 250.0f - i * list->toNextObject()), 24.0f);
			gnk_Text(booking_info_list[i].ID, Gnk_Point(560.0f, 250.0f - i * list->toNextObject()), 24.0f);
			gnk_Text("Loai Phong: ", Gnk_Point(340.0f, 220.0f - i * list->toNextObject()), 24.0f);
			gnk_Text(booking_info_list[i].roomtype, Gnk_Point(560.0f, 220.0f - i * list->toNextObject()), 24.0f);
			gnk_Text("Ma Phong: ", Gnk_Point(340.0f, 190.0f - i * list->toNextObject()), 24.0f);
			gnk_Text(booking_info_list[i].roomID, Gnk_Point(560.0f, 190.0f - i * list->toNextObject()), 24.0f);
			gnk_Text("ID KhachHang: ", Gnk_Point(340.0f, 160.0f - i * list->toNextObject()), 24.0f);
			gnk_Text(booking_info_list[i].guestID, Gnk_Point(560.0f, 160.0f - i * list->toNextObject()), 24.0f);
			gnk_Text("Ngay Nhan Phong: ", Gnk_Point(340.0f, 130.0f - i * list->toNextObject()), 24.0f);
			gnk_Text(booking_info_list[i].check_in_date, Gnk_Point(560.0f, 130.0f - i * list->toNextObject()), 24.0f);
			gnk_Text("Ngay Tra Phong: ", Gnk_Point(340.0f, 100.0f - i * list->toNextObject()), 24.0f);
			gnk_Text(booking_info_list[i].check_out_date, Gnk_Point(560.0f, 100.0f - i * list->toNextObject()), 24.0f);
			gnk_Text("So Luong Khach: ", Gnk_Point(340.0f, 70.0f - i * list->toNextObject()), 24.0f);
			gnk_Text(booking_info_list[i].number_of_guest, Gnk_Point(560.0f, 70.0f - i * list->toNextObject()), 24.0f);
			gnk_Text("Gia Tien: ", Gnk_Point(340.0f, 40.0f - i * list->toNextObject()), 24.0f);
			gnk_Text(booking_info_list[i].price_per_night, Gnk_Point(560.0f, 40.0f - i * list->toNextObject()), 24.0f);
			gnk_Text("Tong tien: ", Gnk_Point(340.0f, 10.0f - i * list->toNextObject()), 24.0f);
			gnk_Text(booking_info_list[i].total_price, Gnk_Point(560.0f, 10.0f - i * list->toNextObject()), 24.0f);
		}
	}
}

void staff_frame_guest_info_list_process(Gnk_List_Object *list) {
	if(guest_info_list_enable) {
		if(guest_info_list_init == false) {
			guest_info_list.clear();
			UI_input_buffer.str("");UI_input_buffer.clear();
			UI_output_buffer.str("");UI_output_buffer.clear();

			current_Data->requestHandling(PRINT_DSKH);
			string line;
			while(getline(UI_output_buffer, line)) {
				guest_info info;
				info.ID = line;
				getline(UI_output_buffer, line);
				info.name = line;
				getline(UI_output_buffer, line);
				info.date_of_birth = line;
				getline(UI_output_buffer, line);
				info.phone_number = line;
				getline(UI_output_buffer, line);
				info.gender = line;
				guest_info_list.push_back(info);
			}
			guest_info_list_init = true;
		}

		list->setGroupHeight(list->toNextObject()*guest_info_list.size());
		list->numOfObject = guest_info_list.size();
		for(int i = 0; i < guest_info_list.size(); i++) {
			if(list->currentPos < list->object_start_position.y - i * list->toNextObject()) {
				continue;
			}
			if(list->object_height + list->object_start_position.y - i * list->toNextObject() < list->currentPos - list->getGroupHeight()) {
				break;
			}
			gnk_Set_Object_Color(H_FFFFFF);
			gnk_Rectangle(Gnk_Point(0.0f, 0.0f - i * list->toNextObject()), Gnk_Point(list->object_width, 300.0f - i * list->toNextObject()));
			gnk_Set_Object_Color(H_7E7E81);
			gnk_Rectangle(Gnk_Point(0.0f, 0.0f - i * list->toNextObject()), Gnk_Point(list->object_height, 300.0f - i * list->toNextObject()));
			if(Utils::stringToGender(guest_info_list[i].gender) == NAM)
			gnk_Image(gnk_Image_List["man_icon"], Gnk_Point(0.0f, 0.0f - i * list->toNextObject()), Gnk_Point(300.0f, 300.0f - i * list->toNextObject()));
			else gnk_Image(gnk_Image_List["woman_icon"], Gnk_Point(0.0f, 0.0f - i * list->toNextObject()), Gnk_Point(300.0f, 300.0f - i * list->toNextObject()));
			gnk_Set_Object_Color(C_1A1A1D);
			gnk_Text("Ma Khach Hang: ", Gnk_Point(340.0f, 250.0f - i * list->toNextObject()), 24.0f);
			gnk_Text(guest_info_list[i].ID, Gnk_Point(560.0f, 250.0f - i * list->toNextObject()), 24.0f);
			gnk_Text("Ten Khach Hang: ", Gnk_Point(340.0f, 220.0f - i * list->toNextObject()), 24.0f);
			gnk_Text(guest_info_list[i].name, Gnk_Point(560.0f, 220.0f - i * list->toNextObject()), 24.0f);
			gnk_Text("Ngay Sinh: ", Gnk_Point(340.0f, 190.0f - i * list->toNextObject()), 24.0f);
			gnk_Text(guest_info_list[i].date_of_birth, Gnk_Point(560.0f, 190.0f - i * list->toNextObject()), 24.0f);
			gnk_Text("So Dien Thoai: ", Gnk_Point(340.0f, 160.0f - i * list->toNextObject()), 24.0f);
			gnk_Text(guest_info_list[i].phone_number, Gnk_Point(560.0f, 160.0f - i * list->toNextObject()), 24.0f);
			gnk_Text("Gioi Tinh: ", Gnk_Point(340.0f, 130.0f - i * list->toNextObject()), 24.0f);
			gnk_Text(guest_info_list[i].gender, Gnk_Point(560.0f, 130.0f - i * list->toNextObject()), 24.0f);
		}
	}
}

void staff_frame_type_room_info_list_process(Gnk_List_Object *list) {
	if(type_room_info_list_enable) {
		if(type_room_info_list_init == false) {
			booking_info_list.clear();
			UI_input_buffer.str("");UI_input_buffer.clear();
			UI_output_buffer.str("");UI_output_buffer.clear();

			current_Data->requestHandling(PRINT_DSLP);
			string line;
			while(getline(UI_output_buffer, line)) {
				type_room_info info;
				info.type = line;
				getline(UI_output_buffer, line);
				info.bed_type = line;
				getline(UI_output_buffer, line);
				info.number_of_guest = line;
				getline(UI_output_buffer, line);
				info.area = line;
				getline(UI_output_buffer, line);
				info.price = line;
				getline(UI_output_buffer, line);
				info.description = line;
				getline(UI_output_buffer, line);
				info.amount = line;
				type_room_info_list.push_back(info);
			}
			type_room_info_list_init = true;
		}

		list->setGroupHeight(list->toNextObject()*type_room_info_list.size());
		list->numOfObject = type_room_info_list.size();
		for(int i = 0; i < type_room_info_list.size(); i++) {
			if(list->currentPos < list->object_start_position.y - i * list->toNextObject()) {
				continue;
			}
			if(list->object_height + list->object_start_position.y - i * list->toNextObject() < list->currentPos - list->getGroupHeight()) {
				break;
			}
			gnk_Set_Object_Color(H_FFFFFF);
			gnk_Rectangle(Gnk_Point(0.0f, 0.0f - i * list->toNextObject()), Gnk_Point(list->object_width, 300.0f - i * list->toNextObject()));
			gnk_Set_Object_Color(H_7E7E81);
			gnk_Rectangle(Gnk_Point(0.0f, 0.0f - i * list->toNextObject()), Gnk_Point(list->object_height, 300.0f - i * list->toNextObject()));
			gnk_Image(gnk_Image_List[type_room_info_list[i].type], Gnk_Point(0.0f, 0.0f - i * list->toNextObject()), Gnk_Point(300.0f, 300.0f - i * list->toNextObject()));
			gnk_Set_Object_Color(C_1A1A1D);
			gnk_Text("Loai Phong: ", Gnk_Point(340.0f, 250.0f - i * list->toNextObject()), 24.0f);
			gnk_Text(type_room_info_list[i].type, Gnk_Point(560.0f, 250.0f - i * list->toNextObject()), 24.0f);
			gnk_Text("Loai Giuong: ", Gnk_Point(340.0f, 220.0f - i * list->toNextObject()), 24.0f);
			gnk_Text(type_room_info_list[i].bed_type, Gnk_Point(560.0f, 220.0f - i * list->toNextObject()), 24.0f);
			gnk_Text("So Nguoi: ", Gnk_Point(340.0f, 190.0f - i * list->toNextObject()), 24.0f);
			gnk_Text(type_room_info_list[i].number_of_guest, Gnk_Point(560.0f, 190.0f - i * list->toNextObject()), 24.0f);
			gnk_Text("Dien Tich: ", Gnk_Point(340.0f, 160.0f - i * list->toNextObject()), 24.0f);
			gnk_Text(type_room_info_list[i].area, Gnk_Point(560.0f, 160.0f - i * list->toNextObject()), 24.0f);
			gnk_Text("Gia: ", Gnk_Point(340.0f, 130.0f - i * list->toNextObject()), 24.0f);
			gnk_Text(type_room_info_list[i].price, Gnk_Point(560.0f, 130.0f - i * list->toNextObject()), 24.0f);
			gnk_Set_Line_Width(2.0f);
			gnk_Line(Gnk_Point(340.0f, 120.0f - i * list->toNextObject()), Gnk_Point(1030.0f, 120.0f - i * list->toNextObject()));
			gnk_Text_Multi_Line(type_room_info_list[i].description, Gnk_Point(340.0f, 90.0f - i * list->toNextObject()), 64, 10, 24);
			gnk_Set_Line_Width(1.0f);
			gnk_Text("So Luong: " + type_room_info_list[i].amount, Gnk_Point(880.0f, 250.0f - i * list->toNextObject()), 24.0f);
		}
	}
}

void staff_frame_room_info_list_process(Gnk_List_Object *list) {
	if(room_info_list_enable) {
		if(room_info_list_init == false) {
			room_info_list.clear();
			UI_input_buffer.str("");UI_input_buffer.clear();
			UI_output_buffer.str("");UI_output_buffer.clear();

			current_Data->requestHandling(PRINT_DSP);
			string line;
			while(getline(UI_output_buffer, line)) {
				room_info info;
				info.ID = line;
				getline(UI_output_buffer, line);
				info.type = line;
				getline(UI_output_buffer, line);
				info.bed_type = line;
				getline(UI_output_buffer, line);
				info.number_of_guest = line;
				getline(UI_output_buffer, line);
				info.area = line;
				getline(UI_output_buffer, line);
				info.price = line;
				room_info_list.push_back(info);
			}
			room_info_list_init = true;
		}

		list->setGroupHeight(list->toNextObject()*room_info_list.size());
		list->numOfObject = room_info_list.size();
		for(int i = 0; i < room_info_list.size(); i++) {
			if(list->currentPos < list->object_start_position.y - i * list->toNextObject()) {
				continue;
			}
			if(list->object_height + list->object_start_position.y - i * list->toNextObject() < list->currentPos - list->getGroupHeight()) {
				break;
			}
			gnk_Set_Object_Color(H_FFFFFF);
			gnk_Rectangle(Gnk_Point(0.0f, 0.0f - i * list->toNextObject()), Gnk_Point(list->object_width, 300.0f - i * list->toNextObject()));
			gnk_Set_Object_Color(H_7E7E81);
			gnk_Rectangle(Gnk_Point(0.0f, 0.0f - i * list->toNextObject()), Gnk_Point(list->object_height, 300.0f - i * list->toNextObject()));
			gnk_Image(gnk_Image_List[room_info_list[i].type], Gnk_Point(0.0f, 0.0f - i * list->toNextObject()), Gnk_Point(300.0f, 300.0f - i * list->toNextObject()));
			gnk_Set_Object_Color(C_1A1A1D);
			gnk_Text("Ma Phong: ", Gnk_Point(340.0f, 250.0f - i * list->toNextObject()), 24.0f);
			gnk_Text(room_info_list[i].ID, Gnk_Point(560.0f, 250.0f - i * list->toNextObject()), 24.0f);
			gnk_Text("Loai Phong: ", Gnk_Point(340.0f, 220.0f - i * list->toNextObject()), 24.0f);
			gnk_Text(room_info_list[i].type, Gnk_Point(560.0f, 220.0f - i * list->toNextObject()), 24.0f);
			gnk_Text("Loai Giuong: ", Gnk_Point(340.0f, 190.0f - i * list->toNextObject()), 24.0f);
			gnk_Text(room_info_list[i].bed_type, Gnk_Point(560.0f, 190.0f - i * list->toNextObject()), 24.0f);
			gnk_Text("So Nguoi: ", Gnk_Point(340.0f, 160.0f - i * list->toNextObject()), 24.0f);
			gnk_Text(room_info_list[i].number_of_guest, Gnk_Point(560.0f, 160.0f - i * list->toNextObject()), 24.0f);
			gnk_Text("Dien Tich: ", Gnk_Point(340.0f, 130.0f - i * list->toNextObject()), 24.0f);
			gnk_Text(room_info_list[i].area, Gnk_Point(560.0f, 130.0f - i * list->toNextObject()), 24.0f);
			gnk_Text("Gia: ", Gnk_Point(340.0f, 100.0f - i * list->toNextObject()), 24.0f);
			gnk_Text(room_info_list[i].price, Gnk_Point(560.0f, 100.0f - i * list->toNextObject()), 24.0f);
		}
	}
}

void staff_frame_create_guest_button_click_2(Gnk_Button *button) {
	Gnk_Button_With_Text *buttonText = (Gnk_Button_With_Text *)button;
	Gnk_Color color = buttonText->color;
	buttonText->color = color - Gnk_Color(40, 40, 40);
	buttonText->draw();
	buttonText->color = color;

	UI_input_buffer.str("");UI_input_buffer.clear();
	UI_output_buffer.str("");UI_output_buffer.clear();

	string name = gnk_Current_Frame->textboxList["first_name_textbox"]->text + " " + gnk_Current_Frame->textboxList["surname_textbox"]->text;
	string date_of_birth = gnk_Current_Frame->textboxList["date_textbox"]->text 
	+ '/' + gnk_Current_Frame->textboxList["month_textbox"]->text
	+ '/' + gnk_Current_Frame->textboxList["year_textbox"]->text;
	string gender = "";
	if(((Gnk_Button_Toggle *)staff.buttonList["male_toggle"])->toggle) {
		gender = "Nam";
	}
	if(((Gnk_Button_Toggle *)staff.buttonList["female_toggle"])->toggle) {
		gender = "Nu";
	}
	string phone_number = gnk_Current_Frame->textboxList["phone_number_textbox"]->text;
	if(Utils::isAlphabetAndSpaceOnly(name) && Utils::isVietNamPhoneNumber(phone_number) && Utils::isDate(date_of_birth)) {
		UI_input_buffer << name << endl;
		UI_input_buffer << date_of_birth << endl;
		UI_input_buffer << phone_number << endl;
		UI_input_buffer << gender << endl;
		current_Data->requestHandling(ADD_KHACHHANG);
		staff_create_guest_success = true;
		option = STAFF_CREATE_GUEST_DONE;
	}
	else staff_create_guest_success = false;
}

Gnk_Frame staff(staff_frame_draw);
// ---------------------------------------------------------
void  admin_frame_draw(Gnk_Frame *frame) {
	frame->disable_all();
	gnk_Set_Background_Color(H_F3F2F2);

	gnk_Set_Object_Color(H_222831);
	gnk_Rectangle(Gnk_Point(0.0f, 800.0f), Gnk_Point(1600.0f, 900.0f));

	gnk_Set_Object_Color(H_222831);
	gnk_Rectangle(Gnk_Point(0.0f, 0.0f), Gnk_Point(430.0f, 800.0f));

	gnk_Set_Object_Color(H_7E7E81);
	gnk_Set_Line_Width(2.0f);
	gnk_Line(Gnk_Point(20.0f, 800.0f), Gnk_Point(1560.0f, 800.0f));

	gnk_Set_Object_Color(H_FFECB8);
	gnk_Set_Character_Font("helvetica-bold");
	gnk_Text("HOTEL DEL LUNA", Gnk_Point(40.0f, 830.0f), 40.0f);

	gnk_Set_Object_Color(H_FFFFFF);
	gnk_Set_Character_Font("helvetica");
	gnk_Text("Welcome, Hotel Del Luna's Admin!", Gnk_Point(430.0f, 830.0f), 24.0f);
	
	frame->buttonList["logout_button"]->setAppear(true);
	frame->buttonList["logout_button"]->display();

	if(option == ADMIN_MAIN) {
		frame->buttonList["type_room_button"]->setAppear(true);
		frame->buttonList["type_room_button"]->display();

		frame->buttonList["room_button"]->setAppear(true);
		frame->buttonList["room_button"]->display();

		frame->buttonList["room_revenue_button"]->setAppear(true);
		frame->buttonList["room_revenue_button"]->display();
	}
	else if(option == ADMIN_TYPE_ROOM_MANAGEMENT) {
		frame->buttonList["type_room_view_and_edit_button"]->setAppear(true);
		frame->buttonList["type_room_view_and_edit_button"]->display();
		frame->buttonList["add_type_room_button"]->setAppear(true);
		frame->buttonList["add_type_room_button"]->display();
		frame->buttonList["remove_type_room_button"]->setAppear(true);
		frame->buttonList["remove_type_room_button"]->display();
		frame->buttonList["back_to_main_button"]->setAppear(true);
		frame->buttonList["back_to_main_button"]->display();
	}
	else if(option == ADMIN_ROOM_MANAGEMENT) {
		frame->buttonList["room_view_and_edit_button"]->setAppear(true);
		frame->buttonList["room_view_and_edit_button"]->display();
		frame->buttonList["add_room_button"]->setAppear(true);
		frame->buttonList["add_room_button"]->display();
		frame->buttonList["remove_room_button"]->setAppear(true);
		frame->buttonList["remove_room_button"]->display();
		frame->buttonList["back_to_main_button"]->setAppear(true);
		frame->buttonList["back_to_main_button"]->display();
	}
	else if(option == ADMIN_REVENUE_MANAGEMENT) {
		frame->buttonList["daily_revenue_button"]->setAppear(true);
		frame->buttonList["daily_revenue_button"]->display();
		frame->buttonList["monthly_revenue_button"]->setAppear(true);
		frame->buttonList["monthly_revenue_button"]->display();
		frame->buttonList["yearly_revenue_button"]->setAppear(true);
		frame->buttonList["yearly_revenue_button"]->display();
		frame->buttonList["back_to_main_button"]->setAppear(true);
		frame->buttonList["back_to_main_button"]->display();
	}
	else if(option == ADMIN_TYPE_ROOM_VIEW_AND_EDIT) {
		frame->buttonList["type_room_view_and_edit_button"]->setAppear(true);
		frame->buttonList["type_room_view_and_edit_button"]->display();
		frame->buttonList["add_type_room_button"]->setAppear(true);
		frame->buttonList["add_type_room_button"]->display();
		frame->buttonList["remove_type_room_button"]->setAppear(true);
		frame->buttonList["remove_type_room_button"]->display();
		frame->buttonList["back_to_main_button"]->setAppear(true);
		frame->buttonList["back_to_main_button"]->display();
		frame->listObjectList["type_room_list"]->setAppear(true);
		frame->listObjectList["type_room_list"]->draw();

	}
	else if(option == ADMIN_ADD_TYPE_ROOM) {
		frame->buttonList["type_room_view_and_edit_button"]->setAppear(true);
		frame->buttonList["type_room_view_and_edit_button"]->display();
		frame->buttonList["add_type_room_button"]->setAppear(true);
		frame->buttonList["add_type_room_button"]->display();
		frame->buttonList["remove_type_room_button"]->setAppear(true);
		frame->buttonList["remove_type_room_button"]->display();
		frame->buttonList["back_to_main_button"]->setAppear(true);
		frame->buttonList["back_to_main_button"]->display();

	}
	else if(option == ADMIN_REMOVE_TYPE_ROOM) {
		frame->buttonList["type_room_view_and_edit_button"]->setAppear(true);
		frame->buttonList["type_room_view_and_edit_button"]->display();
		frame->buttonList["add_type_room_button"]->setAppear(true);
		frame->buttonList["add_type_room_button"]->display();
		frame->buttonList["remove_type_room_button"]->setAppear(true);
		frame->buttonList["remove_type_room_button"]->display();
		frame->buttonList["back_to_main_button"]->setAppear(true);
		frame->buttonList["back_to_main_button"]->display();
	}
	else if(option == ADMIN_ROOM_VIEW_AND_EDIT) {
		frame->buttonList["room_view_and_edit_button"]->setAppear(true);
		frame->buttonList["room_view_and_edit_button"]->display();
		frame->buttonList["add_room_button"]->setAppear(true);
		frame->buttonList["add_room_button"]->display();
		frame->buttonList["remove_room_button"]->setAppear(true);
		frame->buttonList["remove_room_button"]->display();
		frame->buttonList["back_to_main_button"]->setAppear(true);
		frame->buttonList["back_to_main_button"]->display();
		frame->listObjectList["room_list"]->setAppear(true);
		frame->listObjectList["room_list"]->draw();
	}
	else if(option == ADMIN_ADD_ROOM) {
		frame->buttonList["room_view_and_edit_button"]->setAppear(true);
		frame->buttonList["room_view_and_edit_button"]->display();
		frame->buttonList["add_room_button"]->setAppear(true);
		frame->buttonList["add_room_button"]->display();
		frame->buttonList["remove_room_button"]->setAppear(true);
		frame->buttonList["remove_room_button"]->display();
		frame->buttonList["back_to_main_button"]->setAppear(true);
		frame->buttonList["back_to_main_button"]->display();

	}
	else if(option == ADMIN_REMOVE_ROOM) {
		frame->buttonList["room_view_and_edit_button"]->setAppear(true);
		frame->buttonList["room_view_and_edit_button"]->display();
		frame->buttonList["add_room_button"]->setAppear(true);
		frame->buttonList["add_room_button"]->display();
		frame->buttonList["remove_room_button"]->setAppear(true);
		frame->buttonList["remove_room_button"]->display();
		frame->buttonList["back_to_main_button"]->setAppear(true);
		frame->buttonList["back_to_main_button"]->display();
	}
	else if(option == ADMIN_DAILY_REVENUE) {
		frame->buttonList["daily_revenue_button"]->setAppear(true);
		frame->buttonList["daily_revenue_button"]->display();
		frame->buttonList["monthly_revenue_button"]->setAppear(true);
		frame->buttonList["monthly_revenue_button"]->display();
		frame->buttonList["yearly_revenue_button"]->setAppear(true);
		frame->buttonList["yearly_revenue_button"]->display();
		frame->buttonList["back_to_main_button"]->setAppear(true);
		frame->buttonList["back_to_main_button"]->display();
	}
	else if(option == ADMIN_MONTHLY_REVENUE) {
		frame->buttonList["daily_revenue_button"]->setAppear(true);
		frame->buttonList["daily_revenue_button"]->display();
		frame->buttonList["monthly_revenue_button"]->setAppear(true);
		frame->buttonList["monthly_revenue_button"]->display();
		frame->buttonList["yearly_revenue_button"]->setAppear(true);
		frame->buttonList["yearly_revenue_button"]->display();
		frame->buttonList["back_to_main_button"]->setAppear(true);
		frame->buttonList["back_to_main_button"]->display();

	}
	else if(option == ADMIN_YEARLY_REVENUE) {
		frame->buttonList["daily_revenue_button"]->setAppear(true);
		frame->buttonList["daily_revenue_button"]->display();
		frame->buttonList["monthly_revenue_button"]->setAppear(true);
		frame->buttonList["monthly_revenue_button"]->display();
		frame->buttonList["yearly_revenue_button"]->setAppear(true);
		frame->buttonList["yearly_revenue_button"]->display();
		frame->buttonList["back_to_main_button"]->setAppear(true);
		frame->buttonList["back_to_main_button"]->display();
	}
	else if(option == ADMIN_TYPE_ROOM_EDIT) {
		frame->buttonList["type_room_view_and_edit_button"]->setAppear(true);
		frame->buttonList["type_room_view_and_edit_button"]->display();
		frame->buttonList["add_type_room_button"]->setAppear(true);
		frame->buttonList["add_type_room_button"]->display();
		frame->buttonList["remove_type_room_button"]->setAppear(true);
		frame->buttonList["remove_type_room_button"]->display();
		frame->buttonList["back_to_main_button"]->setAppear(true);
		frame->buttonList["back_to_main_button"]->display();
		if(index_booking != -1) {
			gnk_Set_Object_Color(C_1A1A1D);
			gnk_Set_Character_Font("helvetica-bold");
			gnk_Text_Limited("Edit type room", Gnk_Point(480.0f, 710.0f), 1030.0f, 60.0f, 40.0f, GNK_TEXT_LEFT);

			gnk_Set_Object_Color(H_FFFFFF);
			gnk_Rectangle(Gnk_Point(480.0f, 140.0f), Gnk_Point(1530.0f, 700.0f));
			gnk_Set_Object_Color(H_7E7E81);
			gnk_Rectangle(Gnk_Point(480.0f, 140.0f), Gnk_Point(780.0f, 700.0f));
			gnk_Image(gnk_Image_List[type_room_info_list[index_booking].type], Gnk_Point(480.0f, 400.0f), Gnk_Point(780.0f, 700.0f));
			
			gnk_Set_Character_Font("helvetica");
			gnk_Set_Object_Color(C_1A1A1D);

			gnk_Text("Loai Phong: ", Gnk_Point(820.0f, 592.0f), 24.0f);
			gnk_Text(type_room_info_list[index_booking].type, Gnk_Point(1020.0f, 592.0f), 24.0f);
			gnk_Text("Loai Giuong: ", Gnk_Point(820.0f, 532.0f), 24.0f);
			gnk_Text("So Nguoi: ", Gnk_Point(820.0f, 472.0f), 24.0f);
			gnk_Text("Dien Tich: ", Gnk_Point(820.0f, 412.0f), 24.0f);
			gnk_Text("Gia: ", Gnk_Point(820.0f, 352.0f), 24.0f);
			gnk_Text("Mo Ta: ", Gnk_Point(820.0f, 292.0f), 24.0f);
			frame->textboxList["bed_type_textbox"]->setAppear(true);
			frame->textboxList["bed_type_textbox"]->display();
			frame->textboxList["number_of_guest_textbox"]->setAppear(true);
			frame->textboxList["number_of_guest_textbox"]->display();			
			frame->textboxList["area_textbox"]->setAppear(true);
			frame->textboxList["area_textbox"]->display();
			frame->textboxList["price_textbox"]->setAppear(true);
			frame->textboxList["price_textbox"]->display();
			frame->textboxList["description_textbox"]->setAppear(true);
			frame->textboxList["description_textbox"]->display();	

			frame->buttonList["previous_button"]->setAppear(true);
			frame->buttonList["previous_button"]->display();
			
			frame->buttonList["confirm_button"]->setAppear(true);
			frame->buttonList["confirm_button"]->display();
		}		
	}
	else if(option == ADMIN_ROOM_EDIT) {
		frame->buttonList["room_view_and_edit_button"]->setAppear(true);
		frame->buttonList["room_view_and_edit_button"]->display();
		frame->buttonList["add_room_button"]->setAppear(true);
		frame->buttonList["add_room_button"]->display();
		frame->buttonList["remove_room_button"]->setAppear(true);
		frame->buttonList["remove_room_button"]->display();
		frame->buttonList["back_to_main_button"]->setAppear(true);
		frame->buttonList["back_to_main_button"]->display();
		if(index_booking != -1) {
			gnk_Set_Object_Color(C_1A1A1D);
			gnk_Set_Character_Font("helvetica-bold");
			gnk_Text_Limited("Edit type room", Gnk_Point(480.0f, 710.0f), 1030.0f, 60.0f, 40.0f, GNK_TEXT_LEFT);

			gnk_Set_Object_Color(H_FFFFFF);
			gnk_Rectangle(Gnk_Point(480.0f, 140.0f), Gnk_Point(1530.0f, 700.0f));
			gnk_Set_Object_Color(H_7E7E81);
			gnk_Rectangle(Gnk_Point(480.0f, 140.0f), Gnk_Point(780.0f, 700.0f));
			gnk_Image(gnk_Image_List[room_info_list[index_booking].type], Gnk_Point(480.0f, 400.0f), Gnk_Point(780.0f, 700.0f));
			
			gnk_Set_Character_Font("helvetica");
			gnk_Set_Object_Color(C_1A1A1D);

			gnk_Text("Loai Phong: ", Gnk_Point(820.0f, 592.0f), 24.0f);
			gnk_Text("Ma Phong: ", Gnk_Point(820.0f, 532.0f), 24.0f);
			gnk_Text("Danh sach loai phong: ", Gnk_Point(820.0f, 462.0f), 24.0f);
			gnk_Text_Multi_Line(list_type_room_available, Gnk_Point(820.0f, 412.0f), 54, 10, 24);

			frame->textboxList["type_room_textbox"]->setAppear(true);
			frame->textboxList["type_room_textbox"]->display();
			frame->textboxList["room_ID_textbox"]->setAppear(true);
			frame->textboxList["room_ID_textbox"]->display();

			frame->buttonList["previous_button"]->setAppear(true);
			frame->buttonList["previous_button"]->display();
			
			frame->buttonList["confirm_button"]->setAppear(true);
			frame->buttonList["confirm_button"]->display();
			if(admin_type_room_not_exist) {
				gnk_Set_Object_Color(H_FF0000);
				gnk_Set_Character_Font("helvetica-bold");
				gnk_Text("The type room does not exist!", Gnk_Point(820.0f, 180.0f), 24.0f);
			}
		}		
	}
	else if(option == ADMIN_TYPE_ROOM_EDIT_DONE) {		
		frame->buttonList["type_room_view_and_edit_button"]->setAppear(true);
		frame->buttonList["type_room_view_and_edit_button"]->display();
		frame->buttonList["add_type_room_button"]->setAppear(true);
		frame->buttonList["add_type_room_button"]->display();
		frame->buttonList["remove_type_room_button"]->setAppear(true);
		frame->buttonList["remove_type_room_button"]->display();
		frame->buttonList["back_to_main_button"]->setAppear(true);
		frame->buttonList["back_to_main_button"]->display();
		gnk_Set_Object_Color(C_1A1A1D);
		gnk_Set_Character_Font("helvetica-bold");
		gnk_Text_Limited("The type room has been successfully updated!", Gnk_Point(430.0f, 370.0f), 1170.0f, 60.0f, 48.0f, GNK_TEXT_CENTER);
	}
	else if(option == ADMIN_TYPE_ROOM_ADD_DONE) {
		frame->buttonList["type_room_view_and_edit_button"]->setAppear(true);
		frame->buttonList["type_room_view_and_edit_button"]->display();
		frame->buttonList["add_type_room_button"]->setAppear(true);
		frame->buttonList["add_type_room_button"]->display();
		frame->buttonList["remove_type_room_button"]->setAppear(true);
		frame->buttonList["remove_type_room_button"]->display();
		frame->buttonList["back_to_main_button"]->setAppear(true);
		frame->buttonList["back_to_main_button"]->display();
		gnk_Set_Object_Color(C_1A1A1D);
		gnk_Set_Character_Font("helvetica-bold");
		gnk_Text_Limited("The type room has been successfully added!", Gnk_Point(430.0f, 370.0f), 1170.0f, 60.0f, 48.0f, GNK_TEXT_CENTER);
	}
	else if(option == ADMIN_TYPE_ROOM_REMOVE_DONE) {
		frame->buttonList["type_room_view_and_edit_button"]->setAppear(true);
		frame->buttonList["type_room_view_and_edit_button"]->display();
		frame->buttonList["add_type_room_button"]->setAppear(true);
		frame->buttonList["add_type_room_button"]->display();
		frame->buttonList["remove_type_room_button"]->setAppear(true);
		frame->buttonList["remove_type_room_button"]->display();
		frame->buttonList["back_to_main_button"]->setAppear(true);
		frame->buttonList["back_to_main_button"]->display();
		gnk_Set_Object_Color(C_1A1A1D);
		gnk_Set_Character_Font("helvetica-bold");
		gnk_Text_Limited("The type room has been successfully removed!", Gnk_Point(430.0f, 370.0f), 1170.0f, 60.0f, 48.0f, GNK_TEXT_CENTER);
	}
	else if(option == ADMIN_ROOM_EDIT_DONE) {
		frame->buttonList["room_view_and_edit_button"]->setAppear(true);
		frame->buttonList["room_view_and_edit_button"]->display();
		frame->buttonList["add_room_button"]->setAppear(true);
		frame->buttonList["add_room_button"]->display();
		frame->buttonList["remove_room_button"]->setAppear(true);
		frame->buttonList["remove_room_button"]->display();
		frame->buttonList["back_to_main_button"]->setAppear(true);
		frame->buttonList["back_to_main_button"]->display();
		gnk_Set_Object_Color(C_1A1A1D);
		gnk_Set_Character_Font("helvetica-bold");
		gnk_Text_Limited("The room has been successfully updated!", Gnk_Point(430.0f, 370.0f), 1170.0f, 60.0f, 48.0f, GNK_TEXT_CENTER);
	}
	else if(option == ADMIN_ROOM_ADD_DONE) {
		frame->buttonList["room_view_and_edit_button"]->setAppear(true);
		frame->buttonList["room_view_and_edit_button"]->display();
		frame->buttonList["add_room_button"]->setAppear(true);
		frame->buttonList["add_room_button"]->display();
		frame->buttonList["remove_room_button"]->setAppear(true);
		frame->buttonList["remove_room_button"]->display();
		frame->buttonList["back_to_main_button"]->setAppear(true);
		frame->buttonList["back_to_main_button"]->display();
		gnk_Set_Object_Color(C_1A1A1D);
		gnk_Set_Character_Font("helvetica-bold");
		gnk_Text_Limited("The room has been successfully added!", Gnk_Point(430.0f, 370.0f), 1170.0f, 60.0f, 48.0f, GNK_TEXT_CENTER);
	}
	else if(option == ADMIN_ROOM_REMOVE_DONE) {
		frame->buttonList["room_view_and_edit_button"]->setAppear(true);
		frame->buttonList["room_view_and_edit_button"]->display();
		frame->buttonList["add_room_button"]->setAppear(true);
		frame->buttonList["add_room_button"]->display();
		frame->buttonList["remove_room_button"]->setAppear(true);
		frame->buttonList["remove_room_button"]->display();
		frame->buttonList["back_to_main_button"]->setAppear(true);
		frame->buttonList["back_to_main_button"]->display();
		gnk_Set_Object_Color(C_1A1A1D);
		gnk_Set_Character_Font("helvetica-bold");
		gnk_Text_Limited("The room has been successfully removed!", Gnk_Point(430.0f, 370.0f), 1170.0f, 60.0f, 48.0f, GNK_TEXT_CENTER);
	}
 }

void admin_frame_type_room_button_click(Gnk_Button *button) {
	Gnk_Button_With_Text *buttonText = (Gnk_Button_With_Text *)button;
	Gnk_Color color = buttonText->color;
	buttonText->color = color - Gnk_Color(40, 40, 40);
	buttonText->draw();
	buttonText->color = color;
	option = ADMIN_TYPE_ROOM_MANAGEMENT;
}

void admin_frame_room_button_click(Gnk_Button *button) {
	Gnk_Button_With_Text *buttonText = (Gnk_Button_With_Text *)button;
	Gnk_Color color = buttonText->color;
	buttonText->color = color - Gnk_Color(40, 40, 40);
	buttonText->draw();
	buttonText->color = color;
	option = ADMIN_ROOM_MANAGEMENT;
}

void admin_frame_room_revenue_button_click(Gnk_Button *button) {
	Gnk_Button_With_Text *buttonText = (Gnk_Button_With_Text *)button;
	Gnk_Color color = buttonText->color;
	buttonText->color = color - Gnk_Color(40, 40, 40);
	buttonText->draw();
	buttonText->color = color;
	option = ADMIN_REVENUE_MANAGEMENT;
}


void admin_type_room_view_and_edit_button_click(Gnk_Button *button) {
	Gnk_Button_With_Text *buttonText = (Gnk_Button_With_Text *)button;
	Gnk_Color color = buttonText->color;
	buttonText->color = color - Gnk_Color(40, 40, 40);
	buttonText->draw();
	buttonText->color = color;
	option = ADMIN_TYPE_ROOM_VIEW_AND_EDIT;
	type_room_info_list_enable = true;
	type_room_info_list_init = false;
	admin.listObjectList["type_room_list"]->setCurrentPos(admin.listObjectList["type_room_list"]->getGroupHeight());
}

void admin_add_type_room_button_click(Gnk_Button *button) {
	Gnk_Button_With_Text *buttonText = (Gnk_Button_With_Text *)button;
	Gnk_Color color = buttonText->color;
	buttonText->color = color - Gnk_Color(40, 40, 40);
	buttonText->draw();
	buttonText->color = color;
	option = ADMIN_ADD_TYPE_ROOM;
}

void admin_remove_type_room_button_click(Gnk_Button *button) {
	Gnk_Button_With_Text *buttonText = (Gnk_Button_With_Text *)button;
	Gnk_Color color = buttonText->color;
	buttonText->color = color - Gnk_Color(40, 40, 40);
	buttonText->draw();
	buttonText->color = color;
	option = ADMIN_REMOVE_TYPE_ROOM;
}

void admin_room_view_and_edit_button_click(Gnk_Button *button) {
	Gnk_Button_With_Text *buttonText = (Gnk_Button_With_Text *)button;
	Gnk_Color color = buttonText->color;
	buttonText->color = color - Gnk_Color(40, 40, 40);
	buttonText->draw();
	buttonText->color = color;
	option = ADMIN_ROOM_VIEW_AND_EDIT;
	room_info_list_enable = true;
	room_info_list_init = false;
	admin.listObjectList["room_list"]->setCurrentPos(admin.listObjectList["room_list"]->getGroupHeight());
}

void admin_add_room_button_click(Gnk_Button *button) {
	Gnk_Button_With_Text *buttonText = (Gnk_Button_With_Text *)button;
	Gnk_Color color = buttonText->color;
	buttonText->color = color - Gnk_Color(40, 40, 40);
	buttonText->draw();
	buttonText->color = color;
	option = ADMIN_ADD_ROOM;
}

void admin_remove_room_button_click(Gnk_Button *button) {
	Gnk_Button_With_Text *buttonText = (Gnk_Button_With_Text *)button;
	Gnk_Color color = buttonText->color;
	buttonText->color = color - Gnk_Color(40, 40, 40);
	buttonText->draw();
	buttonText->color = color;
	option = ADMIN_REMOVE_ROOM;
}

void admin_daily_revenue_button_click(Gnk_Button *button) {
	Gnk_Button_With_Text *buttonText = (Gnk_Button_With_Text *)button;
	Gnk_Color color = buttonText->color;
	buttonText->color = color - Gnk_Color(40, 40, 40);
	buttonText->draw();
	buttonText->color = color;
	option = ADMIN_DAILY_REVENUE;
}

void admin_monthly_revenue_button_click(Gnk_Button *button) {
	Gnk_Button_With_Text *buttonText = (Gnk_Button_With_Text *)button;
	Gnk_Color color = buttonText->color;
	buttonText->color = color - Gnk_Color(40, 40, 40);
	buttonText->draw();
	buttonText->color = color;
	option = ADMIN_MONTHLY_REVENUE;
}

void admin_yearly_revenue_button_click(Gnk_Button *button) {
	Gnk_Button_With_Text *buttonText = (Gnk_Button_With_Text *)button;
	Gnk_Color color = buttonText->color;
	buttonText->color = color - Gnk_Color(40, 40, 40);
	buttonText->draw();
	buttonText->color = color;
	option = ADMIN_YEARLY_REVENUE;
}

void admin_frame_back_to_main_button_click(Gnk_Button *button) {
	Gnk_Button_With_Text *buttonText = (Gnk_Button_With_Text *)button;
	Gnk_Color color = buttonText->color;
	buttonText->color = color - Gnk_Color(40, 40, 40);
	buttonText->draw();
	buttonText->color = color;
	option = ADMIN_MAIN;
}

void admin_frame_select_type_room_button_click(Gnk_Button *button) {
	Gnk_Button_With_Text *buttonText = (Gnk_Button_With_Text *)button;
	Gnk_Color color = buttonText->color;
	buttonText->color = color - Gnk_Color(40, 40, 40);
	buttonText->draw();
	buttonText->color = color;
	option = ADMIN_TYPE_ROOM_EDIT;
	index_booking = index_selected_room;
	admin.textboxList["bed_type_textbox"]->text = type_room_info_list[index_selected_room].bed_type;
	admin.textboxList["number_of_guest_textbox"]->text = type_room_info_list[index_selected_room].number_of_guest;
	admin.textboxList["area_textbox"]->text = Utils::intToString(Utils::getOnlyNumber(type_room_info_list[index_selected_room].area.substr(0, type_room_info_list[index_selected_room].area.size() - 3)));
	admin.textboxList["price_textbox"]->text = Utils::intToString(Utils::getOnlyNumber(type_room_info_list[index_selected_room].price));
	admin.textboxList["description_textbox"]->text = type_room_info_list[index_selected_room].description;
}

void admin_frame_select_room_button_click(Gnk_Button *button) {
	Gnk_Button_With_Text *buttonText = (Gnk_Button_With_Text *)button;
	Gnk_Color color = buttonText->color;
	buttonText->color = color - Gnk_Color(40, 40, 40);
	buttonText->draw();
	buttonText->color = color;
	option = ADMIN_ROOM_EDIT;
	index_booking = index_selected_room;
	admin.textboxList["room_ID_textbox"]->text = room_info_list[index_selected_room].ID;
	admin.textboxList["type_room_textbox"]->text = room_info_list[index_selected_room].type;
	
	UI_input_buffer.str("");UI_input_buffer.clear();
	UI_output_buffer.str("");UI_output_buffer.clear();

	list_type_room_available = "";
	current_Data->list_all_type_room();
	string type_room;
	bool first = true;
	while(getline(UI_output_buffer, type_room)) {
		list_type_room_choice.push_back(type_room);
		if(first)list_type_room_available = type_room;
		else list_type_room_available += ", " + type_room;
		first = false;
	}
	admin_type_room_not_exist = false;
}


void admin_frame_type_room_list_process(Gnk_List_Object *list) {
	if(type_room_info_list_enable) {
		if(type_room_info_list_init == false) {
			type_room_info_list.clear();
			UI_input_buffer.str("");UI_input_buffer.clear();
			UI_output_buffer.str("");UI_output_buffer.clear();

			current_Data->requestHandling(PRINT_DSLP);
			string line;
			while(getline(UI_output_buffer, line)) {
				type_room_info info;
				info.type = line;
				getline(UI_output_buffer, line);
				info.bed_type = line;
				getline(UI_output_buffer, line);
				info.number_of_guest = line;
				getline(UI_output_buffer, line);
				info.area = line;
				getline(UI_output_buffer, line);
				info.price = line;
				getline(UI_output_buffer, line);
				info.description = line;
				getline(UI_output_buffer, line);
				info.amount = line;
				type_room_info_list.push_back(info);
			}
			type_room_info_list_init = true;
		}
		list->setGroupHeight(list->toNextObject()*type_room_info_list.size());
		list->numOfObject = type_room_info_list.size();
		for(auto &it : list->buttonList) {
			if(it.button != nullptr) {
				Gnk_Point prev_A = it.button->A;
				Gnk_Point prev_B = it.button->B;
				for(int i = 0; i < list->numOfObject; ++i) {
					it.button->A = prev_A.translate(0.0f, - i * list->toNextObject());
					it.button->B = prev_B.translate(0.0f, - i * list->toNextObject());
					if(it.index_on_click == i) {
						index_selected_room = i;
						it.button->onClick = true;
					}
					else {
						it.button->onClick = false;
					}
					if(it.index_on_hover == i) {
						index_hover_room = i;
						it.button->onHover = true;
					}
					else {
						it.button->onHover = false;
					}
					it.button->display();
				}
				it.index_on_click = -1;
				it.button->A = prev_A;
				it.button->B = prev_B;
			}
		}
		for(int i = 0; i < type_room_info_list.size(); i++) {
			if(list->currentPos < list->object_start_position.y - i * list->toNextObject()) {
				continue;
			}
			if(list->object_height + list->object_start_position.y - i * list->toNextObject() < list->currentPos - list->getGroupHeight()) {
				break;
			}
			GLint scissorBox[4];
			glGetIntegerv(GL_SCISSOR_BOX, scissorBox);
			gnk_Scissor_2_object(
			Gnk_Point(gnk_Translate_X, gnk_Translate_Y - i * list->toNextObject()),
			Gnk_Point(gnk_Translate_X + list->object_width, gnk_Translate_Y - i * list->toNextObject() + list->object_height),
			list->A, list->B);
			gnk_Set_Object_Color(H_FFFFFF);
			gnk_Rectangle(Gnk_Point(0.0f, 0.0f - i * list->toNextObject()), Gnk_Point(list->object_width, 300.0f - i * list->toNextObject()));
			gnk_Set_Object_Color(H_7E7E81);
			gnk_Rectangle(Gnk_Point(0.0f, 0.0f - i * list->toNextObject()), Gnk_Point(list->object_height, 300.0f - i * list->toNextObject()));
			gnk_Image(gnk_Image_List[type_room_info_list[i].type], Gnk_Point(0.0f, 0.0f - i * list->toNextObject()), Gnk_Point(300.0f, 300.0f - i * list->toNextObject()));
			gnk_Set_Object_Color(C_1A1A1D);
			gnk_Text("Loai Phong: ", Gnk_Point(340.0f, 250.0f - i * list->toNextObject()), 24.0f);
			gnk_Text(type_room_info_list[i].type, Gnk_Point(560.0f, 250.0f - i * list->toNextObject()), 24.0f);
			gnk_Text("Loai Giuong: ", Gnk_Point(340.0f, 220.0f - i * list->toNextObject()), 24.0f);
			gnk_Text(type_room_info_list[i].bed_type, Gnk_Point(560.0f, 220.0f - i * list->toNextObject()), 24.0f);
			gnk_Text("So Nguoi: ", Gnk_Point(340.0f, 190.0f - i * list->toNextObject()), 24.0f);
			gnk_Text(type_room_info_list[i].number_of_guest, Gnk_Point(560.0f, 190.0f - i * list->toNextObject()), 24.0f);
			gnk_Text("Dien Tich: ", Gnk_Point(340.0f, 160.0f - i * list->toNextObject()), 24.0f);
			gnk_Text(type_room_info_list[i].area, Gnk_Point(560.0f, 160.0f - i * list->toNextObject()), 24.0f);
			gnk_Text("Gia: ", Gnk_Point(340.0f, 130.0f - i * list->toNextObject()), 24.0f);
			gnk_Text(type_room_info_list[i].price, Gnk_Point(560.0f, 130.0f - i * list->toNextObject()), 24.0f);
			gnk_Set_Line_Width(2.0f);
			gnk_Line(Gnk_Point(340.0f, 120.0f - i * list->toNextObject()), Gnk_Point(1030.0f, 120.0f - i * list->toNextObject()));
			gnk_Text_Multi_Line(type_room_info_list[i].description, Gnk_Point(340.0f, 90.0f - i * list->toNextObject()), 64, 10, 24);
			gnk_Set_Line_Width(1.0f);
			gnk_Text("So Luong: " + type_room_info_list[i].amount, Gnk_Point(880.0f, 250.0f - i * list->toNextObject()), 24.0f);
			if(index_hover_room == i) {
				gnk_Set_Object_Color(H_000000, 0.2f);
				glEnable(GL_BLEND);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				gnk_Rectangle(Gnk_Point(0.0f, 0.0f - i * list->toNextObject()), Gnk_Point(list->object_width, 300.0f - i * list->toNextObject()));
				glDisable(GL_BLEND);
			}
			if(index_selected_room == i) {
				gnk_Set_Object_Color(H_000000, 0.4f);
				glEnable(GL_BLEND);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				gnk_Rectangle(Gnk_Point(0.0f, 0.0f - i * list->toNextObject()), Gnk_Point(list->object_width, 300.0f - i * list->toNextObject()));
				glDisable(GL_BLEND);
			}
			glScissor(scissorBox[0], scissorBox[1], scissorBox[2], scissorBox[3]);
		}
		index_selected_room = -1;
		index_hover_room = -1;
	}
}

void admin_frame_room_list_process(Gnk_List_Object *list) {
	if(room_info_list_enable) {
		if(room_info_list_init == false) {
			room_info_list.clear();
			UI_input_buffer.str("");UI_input_buffer.clear();
			UI_output_buffer.str("");UI_output_buffer.clear();

			current_Data->requestHandling(PRINT_DSP);
			string line;
			while(getline(UI_output_buffer, line)) {
				room_info info;
				info.ID = line;
				getline(UI_output_buffer, line);
				info.type = line;
				getline(UI_output_buffer, line);
				info.bed_type = line;
				getline(UI_output_buffer, line);
				info.number_of_guest = line;
				getline(UI_output_buffer, line);
				info.area = line;
				getline(UI_output_buffer, line);
				info.price = line;
				room_info_list.push_back(info);
			}
			room_info_list_init = true;
		}
		list->setGroupHeight(list->toNextObject()*room_info_list.size());
		list->numOfObject = room_info_list.size();
		for(auto &it : list->buttonList) {
			if(it.button != nullptr) {
				Gnk_Point prev_A = it.button->A;
				Gnk_Point prev_B = it.button->B;
				for(int i = 0; i < list->numOfObject; ++i) {
					it.button->A = prev_A.translate(0.0f, - i * list->toNextObject());
					it.button->B = prev_B.translate(0.0f, - i * list->toNextObject());
					if(it.index_on_click == i) {
						index_selected_room = i;
						it.button->onClick = true;
					}
					else {
						it.button->onClick = false;
					}
					if(it.index_on_hover == i) {
						index_hover_room = i;
						it.button->onHover = true;
					}
					else {
						it.button->onHover = false;
					}
					it.button->display();
				}
				it.index_on_click = -1;
				it.button->A = prev_A;
				it.button->B = prev_B;
			}
		}
		for(int i = 0; i < room_info_list.size(); i++) {
			if(list->currentPos < list->object_start_position.y - i * list->toNextObject()) {
				continue;
			}
			if(list->object_height + list->object_start_position.y - i * list->toNextObject() < list->currentPos - list->getGroupHeight()) {
				break;
			}
			GLint scissorBox[4];
			glGetIntegerv(GL_SCISSOR_BOX, scissorBox);
			gnk_Scissor_2_object(
			Gnk_Point(gnk_Translate_X, gnk_Translate_Y - i * list->toNextObject()),
			Gnk_Point(gnk_Translate_X + list->object_width, gnk_Translate_Y - i * list->toNextObject() + list->object_height),
			list->A, list->B);
			gnk_Set_Object_Color(H_FFFFFF);
			gnk_Rectangle(Gnk_Point(0.0f, 0.0f - i * list->toNextObject()), Gnk_Point(list->object_width, 300.0f - i * list->toNextObject()));
			gnk_Set_Object_Color(H_7E7E81);
			gnk_Rectangle(Gnk_Point(0.0f, 0.0f - i * list->toNextObject()), Gnk_Point(list->object_height, 300.0f - i * list->toNextObject()));
			gnk_Image(gnk_Image_List[room_info_list[i].type], Gnk_Point(0.0f, 0.0f - i * list->toNextObject()), Gnk_Point(300.0f, 300.0f - i * list->toNextObject()));
			gnk_Set_Object_Color(C_1A1A1D);
			gnk_Text("Ma Phong: ", Gnk_Point(340.0f, 250.0f - i * list->toNextObject()), 24.0f);
			gnk_Text(room_info_list[i].ID, Gnk_Point(560.0f, 250.0f - i * list->toNextObject()), 24.0f);
			gnk_Text("Loai Phong: ", Gnk_Point(340.0f, 220.0f - i * list->toNextObject()), 24.0f);
			gnk_Text(room_info_list[i].type, Gnk_Point(560.0f, 220.0f - i * list->toNextObject()), 24.0f);
			gnk_Text("Loai Giuong: ", Gnk_Point(340.0f, 190.0f - i * list->toNextObject()), 24.0f);
			gnk_Text(room_info_list[i].bed_type, Gnk_Point(560.0f, 190.0f - i * list->toNextObject()), 24.0f);
			gnk_Text("So Nguoi: ", Gnk_Point(340.0f, 160.0f - i * list->toNextObject()), 24.0f);
			gnk_Text(room_info_list[i].number_of_guest, Gnk_Point(560.0f, 160.0f - i * list->toNextObject()), 24.0f);
			gnk_Text("Dien Tich: ", Gnk_Point(340.0f, 130.0f - i * list->toNextObject()), 24.0f);
			gnk_Text(room_info_list[i].area, Gnk_Point(560.0f, 130.0f - i * list->toNextObject()), 24.0f);
			gnk_Text("Gia: ", Gnk_Point(340.0f, 100.0f - i * list->toNextObject()), 24.0f);
			gnk_Text(room_info_list[i].price, Gnk_Point(560.0f, 100.0f - i * list->toNextObject()), 24.0f);
			if(index_hover_room == i) {
				gnk_Set_Object_Color(H_000000, 0.2f);
				glEnable(GL_BLEND);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				gnk_Rectangle(Gnk_Point(0.0f, 0.0f - i * list->toNextObject()), Gnk_Point(list->object_width, 300.0f - i * list->toNextObject()));
				glDisable(GL_BLEND);
			}
			if(index_selected_room == i) {
				gnk_Set_Object_Color(H_000000, 0.4f);
				glEnable(GL_BLEND);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				gnk_Rectangle(Gnk_Point(0.0f, 0.0f - i * list->toNextObject()), Gnk_Point(list->object_width, 300.0f - i * list->toNextObject()));
				glDisable(GL_BLEND);
			}
			glScissor(scissorBox[0], scissorBox[1], scissorBox[2], scissorBox[3]);
		}
		index_selected_room = -1;
		index_hover_room = -1;
	}
}


void admin_frame_confirm_button_click(Gnk_Button *button) {
	Gnk_Button_With_Text *buttonText = (Gnk_Button_With_Text *)button;
	Gnk_Color color = buttonText->color;
	buttonText->color = color - Gnk_Color(40, 40, 40);
	buttonText->draw();
	buttonText->color = color;
	if(option == ADMIN_TYPE_ROOM_EDIT) {
		type_room_info info;
		info.type = type_room_info_list[index_booking].type;
		info.bed_type = admin.textboxList["bed_type_textbox"]->text;
		info.number_of_guest = admin.textboxList["number_of_guest_textbox"]->text;
		info.area = admin.textboxList["area_textbox"]->text;
		info.price = admin.textboxList["price_textbox"]->text;
		info.description = admin.textboxList["description_textbox"]->text;
		
		UI_input_buffer.str("");UI_input_buffer.clear();
		UI_output_buffer.str("");UI_output_buffer.clear();
		UI_input_buffer << info.type << endl;
		UI_input_buffer << 1 << endl;
		UI_input_buffer << info.bed_type << endl;
		UI_input_buffer << 2 << endl;
		UI_input_buffer << info.number_of_guest << endl;
		UI_input_buffer << 3 << endl;
		int area = Utils::getOnlyNumber(info.area);
		UI_input_buffer << area << endl;
		UI_input_buffer << 4 << endl;
		int price = Utils::getOnlyNumber(info.price);
		UI_input_buffer << price << endl;
		UI_input_buffer << 5 << endl;
		UI_input_buffer << info.description << endl;
		UI_input_buffer << 6 << endl;

		// Ở đây thêm cái check điều kiện nữa
		current_Data->requestHandling(UPDATE_LOAIPHONG);
		option = ADMIN_TYPE_ROOM_EDIT_DONE;
	}
	else if(option == ADMIN_ROOM_EDIT) {
		string ID = room_info_list[index_booking].ID;
		string newID = admin.textboxList["room_ID_textbox"]->text;
		string type_room = admin.textboxList["type_room_textbox"]->text;
		
		bool check = false;
		for(auto &it : list_type_room_choice) {
			if(it == type_room) {
				check = true;
				break;
			}
		}

		if(check == false) {
			admin_type_room_not_exist = true;
			return;
		}

		UI_input_buffer.str("");UI_input_buffer.clear();
		UI_output_buffer.str("");UI_output_buffer.clear();

		UI_input_buffer << ID << endl;
		UI_input_buffer << 1 << endl;
		UI_input_buffer << type_room << endl;
		UI_input_buffer << 2 << endl;
		UI_input_buffer << newID << endl;
		UI_input_buffer << 3 << endl;

		current_Data->requestHandling(UPDATE_PHONG);
		option = ADMIN_ROOM_EDIT_DONE;
	}
}

void admin_frame_previous_button_click(Gnk_Button *button) {
	Gnk_Button_With_Text *buttonText = (Gnk_Button_With_Text *)button;
	Gnk_Color color = buttonText->color;
	buttonText->color = color - Gnk_Color(40, 40, 40);
	buttonText->draw();
	buttonText->color = color;
	if(option == ADMIN_TYPE_ROOM_EDIT) {
		option = ADMIN_TYPE_ROOM_VIEW_AND_EDIT;
	}
	else if(option == ADMIN_ROOM_EDIT) {
		option = ADMIN_ROOM_VIEW_AND_EDIT;
	}
}

Gnk_Frame admin(admin_frame_draw);

// ---------------------------------------------------------
void login_frame_init() {
	Gnk_Textbox *login_frame_username_textbox = new Gnk_Textbox();
	login_frame_username_textbox->setRange(Gnk_Point(806.0f, 460.0f), Gnk_Point(1190.0f, 520.0f));
	login_frame_username_textbox->setColor(H_FFFFFF);
	login_frame_username_textbox->setBorderRadius(0.0f);
	login_frame_username_textbox->setTextFont("helvetica");
	login_frame_username_textbox->setFontSize(24.0f);
	login_frame_username_textbox->setTextColor(C_1A1A1D);
	login_frame_username_textbox->setPlaceholder("username");
	login_frame_username_textbox->setPlaceholderFont("helvetica");
	login_frame_username_textbox->setPlaceholderFontSize(24.0f);
	login_frame_username_textbox->setPlaceholderColor(H_404040);
	login_frame_username_textbox->setPaddingX(15.0f);
	login_frame_username_textbox->setPaddingY(10.0f);
	login_frame_username_textbox->setTextAlign(GNK_TEXT_LEFT);
	login_frame_username_textbox->setSelectProcess(textbox_select_type1);
	login_frame_username_textbox->setMaxLength(35);

	Gnk_Textbox_Password *login_frame_password_textbox = new Gnk_Textbox_Password(*login_frame_username_textbox);
	login_frame_password_textbox->setRange(Gnk_Point(806.0f, 370.0f), Gnk_Point(1190.0f, 430.0f));
	login_frame_password_textbox->setPlaceholder("password");

	Gnk_Button_With_Text *login_frame_login_button = new Gnk_Button_With_Text();
	login_frame_login_button->setRange(Gnk_Point(1030.0f, 230.0f), Gnk_Point(1190.0f, 290.0f));
	login_frame_login_button->setColor(H_5A6493);
	login_frame_login_button->setText("Login");
	login_frame_login_button->setTextFont("helvetica-bold");
	login_frame_login_button->setFontSize(24.0f);
	login_frame_login_button->setTextColor(H_FFFFFF);
	login_frame_login_button->setTextAlign(GNK_TEXT_CENTER);
	login_frame_login_button->setPaddingX(15.0f);
	login_frame_login_button->setPaddingY(10.0f);
	login_frame_login_button->setRadius(30.0f);
	login_frame_login_button->setClickProcess(login_frame_login_button_click);
	login_frame_login_button->setHoverProcess(button_hover_type_1);

	Gnk_Button_With_Text *login_frame_forgotten_password_button = new Gnk_Button_With_Text();
	login_frame_forgotten_password_button->setRange(Gnk_Point(740.0f, 250.0f), Gnk_Point(990.0f, 284.0f));
	login_frame_forgotten_password_button->setColor(H_FFFFFF);
	login_frame_forgotten_password_button->setText("Forgot your password?");
	login_frame_forgotten_password_button->setTextFont("helvetica");
	login_frame_forgotten_password_button->setFontSize(24.0f);
	login_frame_forgotten_password_button->setTextColor(H_404040);
	login_frame_forgotten_password_button->setPaddingX(0.0f);
	login_frame_forgotten_password_button->setPaddingY(0.0f);
	login_frame_forgotten_password_button->setClickProcess(login_frame_forgotten_password_button_click);
	login_frame_forgotten_password_button->setHoverProcess(button_hover_type_2);

	Gnk_Button_With_Text *login_frame_sign_up_button = new Gnk_Button_With_Text(*login_frame_forgotten_password_button);
	login_frame_sign_up_button->setRange(Gnk_Point(995.0f, 180.0f), Gnk_Point(1200.0f, 214.0f));
	login_frame_sign_up_button->setText("Sign up");
	login_frame_sign_up_button->setClickProcess(login_frame_sign_up_button_click);

	login.addTextbox("username_textbox", login_frame_username_textbox);
	login.addTextbox("password_textbox", login_frame_password_textbox);
	login.addButton("login_button", login_frame_login_button);
	login.addButton("forgotten_password_button", login_frame_forgotten_password_button);
	login.addButton("sign_up_button", login_frame_sign_up_button);
}

void sign_up_frame_init() {
	Gnk_Textbox *sign_up_frame_first_name_textbox = new Gnk_Textbox();
	sign_up_frame_first_name_textbox->setRange(Gnk_Point(465.0f, 480.0f), Gnk_Point(785.0f, 540.0f));
	sign_up_frame_first_name_textbox->setColor(H_FFFFFF);
	sign_up_frame_first_name_textbox->setBorderRadius(0.0f);
	sign_up_frame_first_name_textbox->setTextFont("helvetica");
	sign_up_frame_first_name_textbox->setFontSize(24.0f);
	sign_up_frame_first_name_textbox->setTextColor(C_1A1A1D);
	sign_up_frame_first_name_textbox->setPlaceholder("First name");
	sign_up_frame_first_name_textbox->setPlaceholderFont("helvetica");
	sign_up_frame_first_name_textbox->setPlaceholderFontSize(24.0f);
	sign_up_frame_first_name_textbox->setPlaceholderColor(H_404040);
	sign_up_frame_first_name_textbox->setPaddingX(15.0f);
	sign_up_frame_first_name_textbox->setPaddingY(10.0f);
	sign_up_frame_first_name_textbox->setTextAlign(GNK_TEXT_LEFT);
	sign_up_frame_first_name_textbox->setSelectProcess(textbox_select_type2);
	sign_up_frame_first_name_textbox->setBorder(true);
	sign_up_frame_first_name_textbox->setBorderColor(H_404040);
	sign_up_frame_first_name_textbox->setBorderRadius(10.0f);
	sign_up_frame_first_name_textbox->setMaxLength(50);

	Gnk_Textbox *sign_up_frame_surname_textbox = new Gnk_Textbox(*sign_up_frame_first_name_textbox);
	sign_up_frame_surname_textbox->setRange(Gnk_Point(815.0f, 480.0f), Gnk_Point(1135.0f, 540.0f));
	sign_up_frame_surname_textbox->setPlaceholder("Surname");

	Gnk_Textbox *sign_up_frame_date_textbox = new Gnk_Textbox(*sign_up_frame_first_name_textbox);
	sign_up_frame_date_textbox->setRange(Gnk_Point(465.0f, 340.0f), Gnk_Point(665.0f, 400.0f));
	sign_up_frame_date_textbox->setPlaceholder("Date");
	sign_up_frame_date_textbox->setMaxLength(2);

	Gnk_Textbox *sign_up_frame_month_textbox = new Gnk_Textbox(*sign_up_frame_date_textbox);
	sign_up_frame_month_textbox->setRange(Gnk_Point(700.0f, 340.0f), Gnk_Point(900.0f, 400.0f));
	sign_up_frame_month_textbox->setPlaceholder("Month");

	Gnk_Textbox *sign_up_frame_year_textbox = new Gnk_Textbox(*sign_up_frame_date_textbox);
	sign_up_frame_year_textbox->setRange(Gnk_Point(935.0f, 340.0f), Gnk_Point(1135.0f, 400.0f));
	sign_up_frame_year_textbox->setPlaceholder("Year");
	sign_up_frame_year_textbox->setMaxLength(4);

	Gnk_Button_Toggle *sign_up_frame_male_toggle = new Gnk_Button_Toggle();
	sign_up_frame_male_toggle->setRange(Gnk_Point(465.0f, 220.0f), Gnk_Point(785.0f, 280.0f));
	sign_up_frame_male_toggle->setColor(H_FFFFFF);
	sign_up_frame_male_toggle->setText("Male");
	sign_up_frame_male_toggle->setTextFont("helvetica");
	sign_up_frame_male_toggle->setFontSize(24.0f);
	sign_up_frame_male_toggle->setPaddingX(15.0f);
	sign_up_frame_male_toggle->setPaddingY(10.0f);
	sign_up_frame_male_toggle->setTextColor(C_1A1A1D);
	sign_up_frame_male_toggle->setToggleRange(Gnk_Point(745.0f, 240.0f), Gnk_Point(765.0f, 260.0f));
	sign_up_frame_male_toggle->setToggleColor(H_FFFFFF);
	sign_up_frame_male_toggle->setToggleEnableColor(H_F7C873);
	sign_up_frame_male_toggle->setToggleRadius(10.0f);
	sign_up_frame_male_toggle->setBorder(true);
	sign_up_frame_male_toggle->setBorderColor(H_404040);
	sign_up_frame_male_toggle->setRadius(10.0f);
	sign_up_frame_male_toggle->setClickProcess(sign_up_frame_toggle_click);

	Gnk_Button_Toggle *sign_up_frame_female_toggle = new Gnk_Button_Toggle(*sign_up_frame_male_toggle);
	sign_up_frame_female_toggle->setRange(Gnk_Point(815.0f, 220.0f), Gnk_Point(1135.0f, 280.0f));
	sign_up_frame_female_toggle->setText("Female");
	sign_up_frame_female_toggle->setToggleRange(Gnk_Point(1095.0f, 240.0f), Gnk_Point(1115.0f, 260.0f));

	Gnk_Textbox *sign_up_frame_username_textbox = new Gnk_Textbox(*sign_up_frame_first_name_textbox);
	sign_up_frame_username_textbox->setRange(Gnk_Point(465.0f, 140.0f), Gnk_Point(1135.0f, 200.0f));
	sign_up_frame_username_textbox->setPlaceholder("Username");
	sign_up_frame_username_textbox->setMaxLength(35);

	Gnk_Textbox_Password *sign_up_frame_password_textbox = new Gnk_Textbox_Password(*sign_up_frame_username_textbox);
	sign_up_frame_password_textbox->setRange(Gnk_Point(465.0f, 60.0f), Gnk_Point(1135.0f, 120.0f));
	sign_up_frame_password_textbox->setPlaceholder("Password");

	Gnk_Button_With_Text *sign_up_frame_sign_up_button = new Gnk_Button_With_Text();
	sign_up_frame_sign_up_button->setRange(Gnk_Point(700.0f, -40.0f), Gnk_Point(900.0f, 20.0f));
	sign_up_frame_sign_up_button->setColor(H_5A6493);
	sign_up_frame_sign_up_button->setText("Sign up");
	sign_up_frame_sign_up_button->setTextFont("helvetica-bold");
	sign_up_frame_sign_up_button->setFontSize(24.0f);
	sign_up_frame_sign_up_button->setTextColor(H_FFFFFF);
	sign_up_frame_sign_up_button->setPaddingX(0.0f);
	sign_up_frame_sign_up_button->setPaddingY(0.0f);
	sign_up_frame_sign_up_button->setTextAlign(GNK_TEXT_CENTER);
	sign_up_frame_sign_up_button->border_radius = 30.0f;
	sign_up_frame_sign_up_button->setHoverProcess(button_hover_type_1);
	sign_up_frame_sign_up_button->setClickProcess(sign_up_frame_sign_up_button_click);

	Gnk_Button_With_Text *sign_up_frame_to_login_button = new Gnk_Button_With_Text();
	sign_up_frame_to_login_button->setRange(Gnk_Point(465.0f, -100.0f), Gnk_Point(1135.0f, -60.0f));
	sign_up_frame_to_login_button->setColor(H_FFFFFF);
	sign_up_frame_to_login_button->setText("Already have an account? Login");
	sign_up_frame_to_login_button->setTextFont("helvetica");
	sign_up_frame_to_login_button->setFontSize(24.0f);
	sign_up_frame_to_login_button->setTextColor(H_404040);
	sign_up_frame_to_login_button->setPaddingX(0.0f);
	sign_up_frame_to_login_button->setPaddingY(0.0f);
	sign_up_frame_to_login_button->setTextAlign(GNK_TEXT_CENTER);
	sign_up_frame_to_login_button->setHoverProcess(button_hover_type_2);
	sign_up_frame_to_login_button->setClickProcess(sign_up_frame_to_login_button_click);

	Gnk_Scrollbar *sign_up_frame_scrollbar = new Gnk_Scrollbar();
	sign_up_frame_scrollbar->setRange(Gnk_Point(gnk_Width - 20.0f, 0.0f), Gnk_Point(gnk_Width, gnk_Height));
	sign_up_frame_scrollbar->setColor(H_FFFFFF);
	sign_up_frame_scrollbar->setScrollColor(H_C8C8C8);
	sign_up_frame_scrollbar->setMaxHeight(gnk_Height * 1.4);
	sign_up_frame_scrollbar->setCurrentPos(gnk_Height);

	sign_up.addTextbox("first_name_textbox", sign_up_frame_first_name_textbox);
	sign_up.addTextbox("surname_textbox", sign_up_frame_surname_textbox);
	sign_up.addTextbox("date_textbox", sign_up_frame_date_textbox);
	sign_up.addTextbox("month_textbox", sign_up_frame_month_textbox);
	sign_up.addTextbox("year_textbox", sign_up_frame_year_textbox);
	sign_up.addTextbox("username_textbox", sign_up_frame_username_textbox);
	sign_up.addTextbox("password_textbox", sign_up_frame_password_textbox);
	sign_up.addButton("sign_up_button", sign_up_frame_sign_up_button);
	sign_up.addButton("to_login_button", sign_up_frame_to_login_button);
	sign_up.addButton("male_toggle", sign_up_frame_male_toggle);
	sign_up.addButton("female_toggle", sign_up_frame_female_toggle);
	sign_up.setScrollbar(sign_up_frame_scrollbar);
}

void guest_frame_init() {
	Gnk_Button_With_Text *guest_frame_search_room_button = new Gnk_Button_With_Text();
	guest_frame_search_room_button->setRange(Gnk_Point(40.0f, 680.0f), Gnk_Point(400.0f, 760.0f));
	guest_frame_search_room_button->setColor(H_FFECB8);
	guest_frame_search_room_button->setText("Search Room");
	guest_frame_search_room_button->setTextFont("helvetica");
	guest_frame_search_room_button->setFontSize(24.0f);
	guest_frame_search_room_button->setTextColor(C_1A1A1D);
	guest_frame_search_room_button->setHoverProcess(button_hover_type_1);
	guest_frame_search_room_button->setClickProcess(nullptr);
	guest_frame_search_room_button->setTextAlign(GNK_TEXT_LEFT);
	guest_frame_search_room_button->setPaddingX(30.0f);
	guest_frame_search_room_button->setPaddingY(0.0f);
	guest_frame_search_room_button->setRadius(10.0f);
	guest_frame_search_room_button->setHoverProcess(button_hover_type_1);
	guest_frame_search_room_button->setClickProcess(guest_frame_search_room_button_click);

	Gnk_Button_With_Text *guest_frame_booking_infomation_button = new Gnk_Button_With_Text(*guest_frame_search_room_button);
	guest_frame_booking_infomation_button->setRange(Gnk_Point(40.0f, 580.0f), Gnk_Point(400.0f, 660.0f));
	guest_frame_booking_infomation_button->setText("History Infomation");
	guest_frame_booking_infomation_button->setClickProcess(guest_frame_booking_infomation_button_click);

	Gnk_Button_With_Text *guest_frame_profile_button = new Gnk_Button_With_Text(*guest_frame_search_room_button);
	guest_frame_profile_button->setRange(Gnk_Point(40.0f, 480.0f), Gnk_Point(400.0f, 560.0f));
	guest_frame_profile_button->setText("Profile");
	guest_frame_profile_button->setClickProcess(guest_frame_profile_button_click);

	Gnk_Textbox_Keep_Placeholder *guest_frame_check_in_textbox = new Gnk_Textbox_Keep_Placeholder();
	guest_frame_check_in_textbox->setRange(Gnk_Point(520.0f, 700.0f), Gnk_Point(820.0f, 760.0f));
	guest_frame_check_in_textbox->setColor(H_F7C873);
	guest_frame_check_in_textbox->setTextFont("helvetica");
	guest_frame_check_in_textbox->setFontSize(24.0f);
	guest_frame_check_in_textbox->setTextColor(C_1A1A1D);
	guest_frame_check_in_textbox->setPlaceholder("Check in");
	guest_frame_check_in_textbox->setPlaceholderFont("helvetica");
	guest_frame_check_in_textbox->setPlaceholderFontSize(24.0f);
	guest_frame_check_in_textbox->setPlaceholderColor(H_404040);
	guest_frame_check_in_textbox->setPaddingX(15.0f);
	guest_frame_check_in_textbox->setPaddingY(10.0f);
	guest_frame_check_in_textbox->setTextAlign(GNK_TEXT_LEFT);
	guest_frame_check_in_textbox->setMaxLength(10);

	Gnk_Textbox_Keep_Placeholder *guest_frame_check_out_textbox = new Gnk_Textbox_Keep_Placeholder(*guest_frame_check_in_textbox);
	guest_frame_check_out_textbox->setRange(Gnk_Point(830.0f, 700.0f), Gnk_Point(1130.0f, 760.0f));
	guest_frame_check_out_textbox->setPlaceholder("Check out");

	Gnk_Textbox_Keep_Placeholder *guest_frame_number_of_guest_textbox = new Gnk_Textbox_Keep_Placeholder(*guest_frame_check_in_textbox);
	guest_frame_number_of_guest_textbox->setRange(Gnk_Point(1140.0f, 700.0f), Gnk_Point(1440.0f, 760.0f));
	guest_frame_number_of_guest_textbox->setPlaceholder("Number of guest");
	guest_frame_number_of_guest_textbox->setMaxLength(1);

	Gnk_Button *guest_frame_select_type_room_button = new Gnk_Button();
	guest_frame_select_type_room_button->setRange(Gnk_Point(0.0f, 0.0f), Gnk_Point(1050.0f, 300.0f));
	guest_frame_select_type_room_button->setColor(H_FFFFFF);
	guest_frame_select_type_room_button->setHoverProcess(button_hover_type_1);
	guest_frame_select_type_room_button->setClickProcess(guest_frame_select_type_room_button_click);

	Gnk_List_Object *guest_frame_search_room_list = new Gnk_List_Object();
	guest_frame_search_room_list->setRange(Gnk_Point(430.0f, 0.0f), Gnk_Point(1600.0f, 680.0f));
	guest_frame_search_room_list->setCurrentPos(guest_frame_search_room_list->getGroupHeight());
	guest_frame_search_room_list->setObjectWidth(1050);
	guest_frame_search_room_list->setObjectHeight(300);
	guest_frame_search_room_list->setObjectStartPosition(Gnk_Point(50.0f, 340.0f));
	guest_frame_search_room_list->setObjectSpace(50);
	guest_frame_search_room_list->setGroupHeight(680);
	guest_frame_search_room_list->setDrawProcess(guest_frame_search_room_list_process);
	guest_frame_search_room_list->addButton(guest_frame_select_type_room_button);

	Gnk_List_Object *guest_frame_history_list = new Gnk_List_Object(*guest_frame_search_room_list);
	guest_frame_history_list->setRange(Gnk_Point(430.0f, 0.0f), Gnk_Point(1600.0f, 800.0f));
	guest_frame_history_list->setCurrentPos(guest_frame_history_list->getGroupHeight());
	guest_frame_history_list->setObjectStartPosition(Gnk_Point(50.0f, 460.0f));
	guest_frame_history_list->setGroupHeight(800);
	guest_frame_history_list->setDrawProcess(guest_frame_history_list_process);

	Gnk_Button_With_Image *guest_frame_lookup_button_image = new Gnk_Button_With_Image();
	guest_frame_lookup_button_image->setRange(Gnk_Point(1460.0f, 710.0f), Gnk_Point(1500.0f, 750.0f));
	guest_frame_lookup_button_image->setImage(&gnk_Image_List["search_icon"]);
	guest_frame_lookup_button_image->setClickProcess(guest_frame_lookup_button_image_click);
	guest_frame_lookup_button_image->setColor(H_F7C873);

	Gnk_Button_With_Text *guest_frame_change_profile_button = new Gnk_Button_With_Text();
	guest_frame_change_profile_button->setRange(Gnk_Point(1340.0f, 30.0f), Gnk_Point(1560.0f, 100.0f));
	guest_frame_change_profile_button->setColor(C_1A1A1D);
	guest_frame_change_profile_button->setText("Change Profile");
	guest_frame_change_profile_button->setTextFont("helvetica-bold");
	guest_frame_change_profile_button->setFontSize(24.0f);
	guest_frame_change_profile_button->setTextAlign(GNK_TEXT_CENTER);
	guest_frame_change_profile_button->setTextColor(H_FFFFFF);
	guest_frame_change_profile_button->setRadius(20.0f);
	guest_frame_change_profile_button->setBorder(true);
	guest_frame_change_profile_button->setHoverProcess(button_hover_type_3);
	guest_frame_change_profile_button->setClickProcess(guest_frame_change_frofile_button_click);

	Gnk_Button_With_Text *guest_frame_save_profile_button = new Gnk_Button_With_Text(*guest_frame_change_profile_button);
	guest_frame_save_profile_button->setRange(Gnk_Point(1340.0f, 30.0f), Gnk_Point(1560.0f, 100.0f));
	guest_frame_save_profile_button->setText("Save Profile");
	guest_frame_save_profile_button->setClickProcess(guest_frame_save_profile_button_click);

	Gnk_Textbox *guest_frame_profile_name_textbox = new Gnk_Textbox();
	guest_frame_profile_name_textbox->setRange(Gnk_Point(1140.0f, 540.0f), Gnk_Point(1440.0f, 580.0f));
	guest_frame_profile_name_textbox->setColor(H_FFECB8);
	guest_frame_profile_name_textbox->setBorderRadius(0.0f);
	guest_frame_profile_name_textbox->setTextFont("helvetica");
	guest_frame_profile_name_textbox->setFontSize(24.0f);
	guest_frame_profile_name_textbox->setTextColor(C_1A1A1D);
	guest_frame_profile_name_textbox->setPaddingX(0.0f);
	guest_frame_profile_name_textbox->setPaddingY(0.0f);
	guest_frame_profile_name_textbox->setTextAlign(GNK_TEXT_LEFT);
	guest_frame_profile_name_textbox->setSelectProcess(textbox_select_type3);
	guest_frame_profile_name_textbox->setMaxLength(50);

	Gnk_Textbox *guest_frame_profile_date_of_birth_textbox = new Gnk_Textbox(*guest_frame_profile_name_textbox);
	guest_frame_profile_date_of_birth_textbox->setRange(Gnk_Point(1140.0f, 490.0f), Gnk_Point(1440.0f, 530.0f));
	guest_frame_profile_date_of_birth_textbox->setMaxLength(10);

	Gnk_Textbox *guest_frame_profile_phone_number_textbox = new Gnk_Textbox(*guest_frame_profile_name_textbox);
	guest_frame_profile_phone_number_textbox->setRange(Gnk_Point(1140.0f, 440.0f), Gnk_Point(1440.0f, 480.0f));
	guest_frame_profile_phone_number_textbox->setMaxLength(10);

	Gnk_Textbox *guest_frame_profile_gender_textbox = new Gnk_Textbox(*guest_frame_profile_name_textbox);
	guest_frame_profile_gender_textbox->setRange(Gnk_Point(1140.0f, 390.0f), Gnk_Point(1440.0f, 430.0f));
	guest_frame_profile_gender_textbox->setMaxLength(3);

	Gnk_Button_With_Text *guest_frame_back_to_search_room_button = new Gnk_Button_With_Text(*guest_frame_change_profile_button);
	guest_frame_back_to_search_room_button->setRange(Gnk_Point(480.0f, 30.0f), Gnk_Point(700.0f, 100.0f));
	guest_frame_back_to_search_room_button->setText("Previous");
	guest_frame_back_to_search_room_button->setClickProcess(guest_frame_back_to_search_room_button_click);

	Gnk_Button_With_Text *guest_frame_continue_booking_button = new Gnk_Button_With_Text(*guest_frame_change_profile_button);
	guest_frame_continue_booking_button->setRange(Gnk_Point(1320.0f, 30.0f), Gnk_Point(1530.0f, 100.0f));
	guest_frame_continue_booking_button->setText("Continue");
	guest_frame_continue_booking_button->setClickProcess(guest_frame_continue_booking_button_click);

	Gnk_Button_With_Text *guest_frame_confirm_booking_button = new Gnk_Button_With_Text(*guest_frame_continue_booking_button);
	guest_frame_confirm_booking_button->setText("Confirm");
	guest_frame_confirm_booking_button->setClickProcess(guest_frame_confirm_booking_button_click);

	Gnk_Textbox *guest_frame_room_choice_textbox = new Gnk_Textbox();
	guest_frame_room_choice_textbox->setRange(Gnk_Point(1220.0f, 300.0f), Gnk_Point(1500.0f, 360.0f));
	guest_frame_room_choice_textbox->setColor(H_FFFFFF);
	guest_frame_room_choice_textbox->setPlaceholder("Ex: VIP123");
	guest_frame_room_choice_textbox->setSelectProcess(textbox_select_type3);
	guest_frame_room_choice_textbox->setTextFont("helvetica");
	guest_frame_room_choice_textbox->setFontSize(24.0f);
	guest_frame_room_choice_textbox->setTextColor(C_1A1A1D);
	guest_frame_room_choice_textbox->setPlaceholderFont("helvetica");
	guest_frame_room_choice_textbox->setPlaceholderFontSize(24.0f);
	guest_frame_room_choice_textbox->setPlaceholderColor(H_404040);
	guest_frame_room_choice_textbox->setPaddingX(15.0f);
	guest_frame_room_choice_textbox->setPaddingY(10.0f);
	guest_frame_room_choice_textbox->setTextAlign(GNK_TEXT_LEFT);
	guest_frame_room_choice_textbox->setMaxLength(8);

	guest.addButton("search_room_button", guest_frame_search_room_button);
	guest.addButton("booking_infomation_button", guest_frame_booking_infomation_button);
	guest.addButton("profile_button", guest_frame_profile_button);
	guest.addButton("lookup", guest_frame_lookup_button_image);
	guest.addTextbox("check_in_textbox", guest_frame_check_in_textbox);
	guest.addTextbox("check_out_textbox", guest_frame_check_out_textbox);
	guest.addTextbox("number_of_guest_textbox", guest_frame_number_of_guest_textbox);
	guest.addListObject("search_room_list", guest_frame_search_room_list);
	guest.addListObject("history_list", guest_frame_history_list);
	guest.addButton("change_profile_button", guest_frame_change_profile_button);
	guest.addButton("save_profile_button", guest_frame_save_profile_button);
	guest.addTextbox("profile_name_textbox", guest_frame_profile_name_textbox);
	guest.addTextbox("profile_date_of_birth_textbox", guest_frame_profile_date_of_birth_textbox);
	guest.addTextbox("profile_phone_number_textbox", guest_frame_profile_phone_number_textbox);
	guest.addTextbox("profile_gender_textbox", guest_frame_profile_gender_textbox);
	guest.addButton("back_to_search_room_button", guest_frame_back_to_search_room_button);
	guest.addButton("continue_booking_button", guest_frame_continue_booking_button);
	guest.addTextbox("room_choice_textbox", guest_frame_room_choice_textbox);
	guest.addButton("confirm_booking_button", guest_frame_confirm_booking_button);
}

void staff_frame_init() {
	Gnk_Button_With_Text *staff_frame_search_room_button = new Gnk_Button_With_Text();
	staff_frame_search_room_button->setRange(Gnk_Point(40.0f, 680.0f), Gnk_Point(400.0f, 760.0f));
	staff_frame_search_room_button->setColor(H_FFECB8);
	staff_frame_search_room_button->setText("Search Room");
	staff_frame_search_room_button->setTextFont("helvetica");
	staff_frame_search_room_button->setFontSize(24.0f);
	staff_frame_search_room_button->setTextColor(C_1A1A1D);
	staff_frame_search_room_button->setHoverProcess(button_hover_type_1);
	staff_frame_search_room_button->setClickProcess(nullptr);
	staff_frame_search_room_button->setTextAlign(GNK_TEXT_LEFT);
	staff_frame_search_room_button->setPaddingX(30.0f);
	staff_frame_search_room_button->setPaddingY(0.0f);
	staff_frame_search_room_button->setRadius(10.0f);
	staff_frame_search_room_button->setHoverProcess(button_hover_type_1);
	staff_frame_search_room_button->setClickProcess(guest_frame_search_room_button_click);

	Gnk_Button_With_Text *staff_frame_booking_infomation_button = new Gnk_Button_With_Text(*staff_frame_search_room_button);
	staff_frame_booking_infomation_button->setRange(Gnk_Point(40.0f, 580.0f), Gnk_Point(400.0f, 660.0f));
	staff_frame_booking_infomation_button->setText("Booking Infomation");
	staff_frame_booking_infomation_button->setClickProcess(staff_frame_booking_infomation_button_click);

	Gnk_Button_With_Text *staff_frame_guest_infomation_button = new Gnk_Button_With_Text(*staff_frame_search_room_button);
	staff_frame_guest_infomation_button->setRange(Gnk_Point(40.0f, 480.0f), Gnk_Point(400.0f, 560.0f));
	staff_frame_guest_infomation_button->setText("Guest Infomation");
	staff_frame_guest_infomation_button->setClickProcess(staff_frame_guest_infomation_button_click);

	Gnk_Button_With_Text *staff_frame_type_room_infomation_button = new Gnk_Button_With_Text(*staff_frame_search_room_button);
	staff_frame_type_room_infomation_button->setRange(Gnk_Point(40.0f, 380.0f), Gnk_Point(400.0f, 460.0f));
	staff_frame_type_room_infomation_button->setText("Type Room Infomation");
	staff_frame_type_room_infomation_button->setClickProcess(staff_frame_type_room_infomation_button_click);

	Gnk_Button_With_Text *staff_frame_room_information_button = new Gnk_Button_With_Text(*staff_frame_search_room_button);
	staff_frame_room_information_button->setRange(Gnk_Point(40.0f, 280.0f), Gnk_Point(400.0f, 360.0f));
	staff_frame_room_information_button->setText("Room Infomation");
	staff_frame_room_information_button->setClickProcess(staff_frame_room_information_button_click);

	Gnk_Button_With_Text *staff_frame_create_guest_button = new Gnk_Button_With_Text(*staff_frame_search_room_button);
	staff_frame_create_guest_button->setRange(Gnk_Point(40.0f, 180.0f), Gnk_Point(400.0f, 260.0f));
	staff_frame_create_guest_button->setText("Create Guest");
	staff_frame_create_guest_button->setClickProcess(staff_frame_create_guest_button_click);

	Gnk_Textbox_Keep_Placeholder *guest_frame_check_in_textbox = new Gnk_Textbox_Keep_Placeholder();
	guest_frame_check_in_textbox->setRange(Gnk_Point(520.0f, 700.0f), Gnk_Point(820.0f, 760.0f));
	guest_frame_check_in_textbox->setColor(H_F7C873);
	guest_frame_check_in_textbox->setTextFont("helvetica");
	guest_frame_check_in_textbox->setFontSize(24.0f);
	guest_frame_check_in_textbox->setTextColor(C_1A1A1D);
	guest_frame_check_in_textbox->setPlaceholder("Check in");
	guest_frame_check_in_textbox->setPlaceholderFont("helvetica");
	guest_frame_check_in_textbox->setPlaceholderFontSize(24.0f);
	guest_frame_check_in_textbox->setPlaceholderColor(H_404040);
	guest_frame_check_in_textbox->setPaddingX(15.0f);
	guest_frame_check_in_textbox->setPaddingY(10.0f);
	guest_frame_check_in_textbox->setTextAlign(GNK_TEXT_LEFT);
	guest_frame_check_in_textbox->setMaxLength(10);

	Gnk_Textbox_Keep_Placeholder *guest_frame_check_out_textbox = new Gnk_Textbox_Keep_Placeholder(*guest_frame_check_in_textbox);
	guest_frame_check_out_textbox->setRange(Gnk_Point(830.0f, 700.0f), Gnk_Point(1130.0f, 760.0f));
	guest_frame_check_out_textbox->setPlaceholder("Check out");

	Gnk_Textbox_Keep_Placeholder *guest_frame_number_of_guest_textbox = new Gnk_Textbox_Keep_Placeholder(*guest_frame_check_in_textbox);
	guest_frame_number_of_guest_textbox->setRange(Gnk_Point(1140.0f, 700.0f), Gnk_Point(1440.0f, 760.0f));
	guest_frame_number_of_guest_textbox->setPlaceholder("Number of guest");
	guest_frame_number_of_guest_textbox->setMaxLength(1);
	
	Gnk_Button_With_Image *guest_frame_lookup_button_image = new Gnk_Button_With_Image();
	guest_frame_lookup_button_image->setRange(Gnk_Point(1460.0f, 710.0f), Gnk_Point(1500.0f, 750.0f));
	guest_frame_lookup_button_image->setImage(&gnk_Image_List["search_icon"]);
	guest_frame_lookup_button_image->setClickProcess(guest_frame_lookup_button_image_click);
	guest_frame_lookup_button_image->setColor(H_F7C873);

	Gnk_Button *guest_frame_select_type_room_button = new Gnk_Button();
	guest_frame_select_type_room_button->setRange(Gnk_Point(0.0f, 0.0f), Gnk_Point(1050.0f, 300.0f));
	guest_frame_select_type_room_button->setColor(H_FFFFFF);
	guest_frame_select_type_room_button->setHoverProcess(button_hover_type_1);
	guest_frame_select_type_room_button->setClickProcess(guest_frame_select_type_room_button_click);
	
	Gnk_List_Object *guest_frame_search_room_list = new Gnk_List_Object();
	guest_frame_search_room_list->setRange(Gnk_Point(430.0f, 0.0f), Gnk_Point(1600.0f, 680.0f));
	guest_frame_search_room_list->setCurrentPos(guest_frame_search_room_list->getGroupHeight());
	guest_frame_search_room_list->setObjectWidth(1050);
	guest_frame_search_room_list->setObjectHeight(300);
	guest_frame_search_room_list->setObjectStartPosition(Gnk_Point(50.0f, 340.0f));
	guest_frame_search_room_list->setObjectSpace(50);
	guest_frame_search_room_list->setGroupHeight(680);
	guest_frame_search_room_list->setDrawProcess(guest_frame_search_room_list_process);
	guest_frame_search_room_list->addButton(guest_frame_select_type_room_button);

	Gnk_List_Object *staff_frame_booking_info_list = new Gnk_List_Object(*guest_frame_search_room_list);
	staff_frame_booking_info_list->setRange(Gnk_Point(430.0f, 0.0f), Gnk_Point(1600.0f, 800.0f));
	staff_frame_booking_info_list->setCurrentPos(staff_frame_booking_info_list->getGroupHeight());
	staff_frame_booking_info_list->setObjectStartPosition(Gnk_Point(50.0f, 460.0f));
	staff_frame_booking_info_list->setGroupHeight(800);
	staff_frame_booking_info_list->setDrawProcess(staff_frame_booking_info_list_process);

	Gnk_List_Object *staff_frame_guest_info_list = new Gnk_List_Object(*staff_frame_booking_info_list);
	staff_frame_guest_info_list->setDrawProcess(staff_frame_guest_info_list_process);

	Gnk_List_Object *staff_frame_type_room_info_list = new Gnk_List_Object(*staff_frame_guest_info_list);
	staff_frame_type_room_info_list->setDrawProcess(staff_frame_type_room_info_list_process);

	Gnk_List_Object *staff_frame_room_info_list = new Gnk_List_Object(*staff_frame_type_room_info_list);
	staff_frame_room_info_list->setDrawProcess(staff_frame_room_info_list_process);

	Gnk_Button_With_Text *guest_frame_back_to_search_room_button = new Gnk_Button_With_Text();
	guest_frame_back_to_search_room_button->setRange(Gnk_Point(480.0f, 30.0f), Gnk_Point(700.0f, 100.0f));
	guest_frame_back_to_search_room_button->setColor(C_1A1A1D);
	guest_frame_back_to_search_room_button->setText("Previous");
	guest_frame_back_to_search_room_button->setTextFont("helvetica-bold");
	guest_frame_back_to_search_room_button->setFontSize(24.0f);
	guest_frame_back_to_search_room_button->setTextAlign(GNK_TEXT_CENTER);
	guest_frame_back_to_search_room_button->setTextColor(H_FFFFFF);
	guest_frame_back_to_search_room_button->setRadius(20.0f);
	guest_frame_back_to_search_room_button->setBorder(true);
	guest_frame_back_to_search_room_button->setHoverProcess(button_hover_type_3);
	guest_frame_back_to_search_room_button->setClickProcess(guest_frame_back_to_search_room_button_click);

	Gnk_Button_With_Text *guest_frame_continue_booking_button = new Gnk_Button_With_Text(*guest_frame_back_to_search_room_button);
	guest_frame_continue_booking_button->setRange(Gnk_Point(1320.0f, 30.0f), Gnk_Point(1530.0f, 100.0f));
	guest_frame_continue_booking_button->setText("Continue");
	guest_frame_continue_booking_button->setClickProcess(guest_frame_continue_booking_button_click);
	
	Gnk_Button_With_Text *guest_frame_confirm_booking_button = new Gnk_Button_With_Text(*guest_frame_continue_booking_button);
	guest_frame_confirm_booking_button->setText("Confirm");
	guest_frame_confirm_booking_button->setClickProcess(guest_frame_confirm_booking_button_click);

	Gnk_Textbox *guest_frame_room_choice_textbox = new Gnk_Textbox();
	guest_frame_room_choice_textbox->setRange(Gnk_Point(1220.0f, 300.0f), Gnk_Point(1500.0f, 360.0f));
	guest_frame_room_choice_textbox->setColor(H_FFFFFF);
	guest_frame_room_choice_textbox->setPlaceholder("Ex: VIP123");
	guest_frame_room_choice_textbox->setSelectProcess(textbox_select_type3);
	guest_frame_room_choice_textbox->setTextFont("helvetica");
	guest_frame_room_choice_textbox->setFontSize(24.0f);
	guest_frame_room_choice_textbox->setTextColor(C_1A1A1D);
	guest_frame_room_choice_textbox->setPlaceholderFont("helvetica");
	guest_frame_room_choice_textbox->setPlaceholderFontSize(24.0f);
	guest_frame_room_choice_textbox->setPlaceholderColor(H_404040);
	guest_frame_room_choice_textbox->setPaddingX(15.0f);
	guest_frame_room_choice_textbox->setTextAlign(GNK_TEXT_LEFT);
	guest_frame_room_choice_textbox->setMaxLength(8);

	Gnk_Textbox *staff_frame_guest_ID_textbox = new Gnk_Textbox(*guest_frame_room_choice_textbox);
	staff_frame_guest_ID_textbox->setRange(Gnk_Point(1220.0f, 230.0f), Gnk_Point(1500.0f, 290.0f));
	staff_frame_guest_ID_textbox->setPlaceholder("Ex: 100051");
	staff_frame_guest_ID_textbox->setMaxLength(10);

	/*--------------------------SIGN_UP--------------------------*/
	Gnk_Textbox *sign_up_frame_first_name_textbox = new Gnk_Textbox();
	sign_up_frame_first_name_textbox->setRange(Gnk_Point(630.0f, 580.0f), Gnk_Point(950.0f, 640.0f));
	sign_up_frame_first_name_textbox->setColor(H_FFFFFF);
	sign_up_frame_first_name_textbox->setBorderRadius(0.0f);
	sign_up_frame_first_name_textbox->setTextFont("helvetica");
	sign_up_frame_first_name_textbox->setFontSize(24.0f);
	sign_up_frame_first_name_textbox->setTextColor(C_1A1A1D);
	sign_up_frame_first_name_textbox->setPlaceholder("First name");
	sign_up_frame_first_name_textbox->setPlaceholderFont("helvetica");
	sign_up_frame_first_name_textbox->setPlaceholderFontSize(24.0f);
	sign_up_frame_first_name_textbox->setPlaceholderColor(H_404040);
	sign_up_frame_first_name_textbox->setPaddingX(15.0f);
	sign_up_frame_first_name_textbox->setPaddingY(10.0f);
	sign_up_frame_first_name_textbox->setTextAlign(GNK_TEXT_LEFT);
	sign_up_frame_first_name_textbox->setSelectProcess(textbox_select_type2);
	sign_up_frame_first_name_textbox->setBorder(true);
	sign_up_frame_first_name_textbox->setBorderColor(H_404040);
	sign_up_frame_first_name_textbox->setBorderRadius(10.0f);
	sign_up_frame_first_name_textbox->setMaxLength(50);

	Gnk_Textbox *sign_up_frame_surname_textbox = new Gnk_Textbox(*sign_up_frame_first_name_textbox);
	sign_up_frame_surname_textbox->setRange(Gnk_Point(980.0f, 580.0f), Gnk_Point(1300.0f, 640.0f));
	sign_up_frame_surname_textbox->setPlaceholder("Surname");

	Gnk_Textbox *sign_up_frame_date_textbox = new Gnk_Textbox(*sign_up_frame_first_name_textbox);
	sign_up_frame_date_textbox->setRange(Gnk_Point(630.0f, 440.0f), Gnk_Point(830.0f, 500.0f));
	sign_up_frame_date_textbox->setPlaceholder("Date");
	sign_up_frame_date_textbox->setMaxLength(2);

	Gnk_Textbox *sign_up_frame_month_textbox = new Gnk_Textbox(*sign_up_frame_date_textbox);
	sign_up_frame_month_textbox->setRange(Gnk_Point(865.0f, 440.0f), Gnk_Point(1065.0f, 500.0f));
	sign_up_frame_month_textbox->setPlaceholder("Month");

	Gnk_Textbox *sign_up_frame_year_textbox = new Gnk_Textbox(*sign_up_frame_date_textbox);
	sign_up_frame_year_textbox->setRange(Gnk_Point(1100.0f, 440.0f), Gnk_Point(1300.0f, 500.0f));
	sign_up_frame_year_textbox->setPlaceholder("Year");
	sign_up_frame_year_textbox->setMaxLength(4);

	Gnk_Textbox *staff_frame_phone_number_textbox = new Gnk_Textbox(*sign_up_frame_date_textbox);
	staff_frame_phone_number_textbox->setRange(Gnk_Point(630.0f, 200.0f), Gnk_Point(1060.0f, 260.0f));
	staff_frame_phone_number_textbox->setPlaceholder("Phone number");
	staff_frame_phone_number_textbox->setMaxLength(10);

	Gnk_Button_Toggle *sign_up_frame_male_toggle = new Gnk_Button_Toggle();
	sign_up_frame_male_toggle->setRange(Gnk_Point(630.0f, 320.0f), Gnk_Point(950.0f, 380.0f));
	sign_up_frame_male_toggle->setColor(H_FFFFFF);
	sign_up_frame_male_toggle->setText("Male");
	sign_up_frame_male_toggle->setTextFont("helvetica");
	sign_up_frame_male_toggle->setFontSize(24.0f);
	sign_up_frame_male_toggle->setPaddingX(15.0f);
	sign_up_frame_male_toggle->setPaddingY(10.0f);
	sign_up_frame_male_toggle->setTextColor(C_1A1A1D);
	sign_up_frame_male_toggle->setToggleRange(Gnk_Point(910.0f, 340.0f), Gnk_Point(930.0f, 360.0f));
	sign_up_frame_male_toggle->setToggleColor(H_FFFFFF);
	sign_up_frame_male_toggle->setToggleEnableColor(H_F7C873);
	sign_up_frame_male_toggle->setToggleRadius(10.0f);
	sign_up_frame_male_toggle->setBorder(true);
	sign_up_frame_male_toggle->setBorderColor(H_404040);
	sign_up_frame_male_toggle->setRadius(10.0f);
	sign_up_frame_male_toggle->setClickProcess(sign_up_frame_toggle_click);

	Gnk_Button_Toggle *sign_up_frame_female_toggle = new Gnk_Button_Toggle(*sign_up_frame_male_toggle);
	sign_up_frame_female_toggle->setRange(Gnk_Point(980.0f, 320.0f), Gnk_Point(1300.0f, 380.0f));
	sign_up_frame_female_toggle->setText("Female");
	sign_up_frame_female_toggle->setToggleRange(Gnk_Point(1260.0f, 340.0f), Gnk_Point(1280.0f, 360.0f));
	
	Gnk_Button_With_Text *staff_frame_create_guess_button = new Gnk_Button_With_Text();
	staff_frame_create_guess_button->setRange(Gnk_Point(865.0f, 100.0f), Gnk_Point(1065.0f, 160.0f));
	staff_frame_create_guess_button->setColor(H_F7C873);
	staff_frame_create_guess_button->setText("Create guest");
	staff_frame_create_guess_button->setTextFont("helvetica-bold");
	staff_frame_create_guess_button->setFontSize(24.0f);
	staff_frame_create_guess_button->setTextColor(H_FFFFFF);
	staff_frame_create_guess_button->setPaddingX(0.0f);
	staff_frame_create_guess_button->setPaddingY(0.0f);
	staff_frame_create_guess_button->setTextAlign(GNK_TEXT_CENTER);
	staff_frame_create_guess_button->border_radius = 30.0f;
	staff_frame_create_guess_button->setHoverProcess(button_hover_type_1);
	staff_frame_create_guess_button->setClickProcess(staff_frame_create_guest_button_click_2);
	/*--------------------------SIGN_UP--------------------------*/

	staff.addButton("search_room_button", staff_frame_search_room_button);
	staff.addButton("booking_infomation_button", staff_frame_booking_infomation_button);
	staff.addButton("guest_infomation_button", staff_frame_guest_infomation_button);
	staff.addButton("type_room_infomation_button", staff_frame_type_room_infomation_button);
	staff.addButton("room_information_button", staff_frame_room_information_button);
	staff.addButton("create_guest_button", staff_frame_create_guest_button);
	staff.addTextbox("check_in_textbox", guest_frame_check_in_textbox);
	staff.addTextbox("check_out_textbox", guest_frame_check_out_textbox);
	staff.addTextbox("number_of_guest_textbox", guest_frame_number_of_guest_textbox);

	staff.addListObject("search_room_list", guest_frame_search_room_list);
	staff.addListObject("booking_info_list", staff_frame_booking_info_list);
	staff.addListObject("guest_info_list", staff_frame_guest_info_list);
	staff.addListObject("type_room_info_list", staff_frame_type_room_info_list);
	staff.addListObject("room_info_list", staff_frame_room_info_list);

	staff.addButton("lookup", guest_frame_lookup_button_image);
	staff.addButton("back_to_search_room_button", guest_frame_back_to_search_room_button);
	staff.addButton("continue_booking_button", guest_frame_continue_booking_button);
	staff.addButton("confirm_booking_button", guest_frame_confirm_booking_button);
	staff.addTextbox("room_choice_textbox", guest_frame_room_choice_textbox);
	staff.addTextbox("guest_ID_textbox", staff_frame_guest_ID_textbox);

	staff.addTextbox("first_name_textbox", sign_up_frame_first_name_textbox);
	staff.addTextbox("surname_textbox", sign_up_frame_surname_textbox);
	staff.addTextbox("date_textbox", sign_up_frame_date_textbox);
	staff.addTextbox("month_textbox", sign_up_frame_month_textbox);
	staff.addTextbox("year_textbox", sign_up_frame_year_textbox);
	staff.addTextbox("phone_number_textbox", staff_frame_phone_number_textbox);
	staff.addButton("male_toggle", sign_up_frame_male_toggle);
	staff.addButton("female_toggle", sign_up_frame_female_toggle);
	staff.addButton("create_guess_button", staff_frame_create_guess_button);
}

void admin_frame_init() {
	Gnk_Button_With_Text *admin_frame_type_room_button = new Gnk_Button_With_Text();
	admin_frame_type_room_button->setRange(Gnk_Point(40.0f, 680.0f), Gnk_Point(400.0f, 760.0f));
	admin_frame_type_room_button->setColor(H_FFECB8);
	admin_frame_type_room_button->setText("Manage Room Type");
	admin_frame_type_room_button->setTextFont("helvetica");
	admin_frame_type_room_button->setFontSize(24.0f);
	admin_frame_type_room_button->setTextColor(C_1A1A1D);
	admin_frame_type_room_button->setHoverProcess(button_hover_type_1);
	admin_frame_type_room_button->setClickProcess(nullptr);
	admin_frame_type_room_button->setTextAlign(GNK_TEXT_LEFT);
	admin_frame_type_room_button->setPaddingX(30.0f);
	admin_frame_type_room_button->setPaddingY(0.0f);
	admin_frame_type_room_button->setRadius(10.0f);
	admin_frame_type_room_button->setHoverProcess(button_hover_type_1);
	admin_frame_type_room_button->setClickProcess(admin_frame_type_room_button_click);

	Gnk_Button_With_Text *admin_room_button = new Gnk_Button_With_Text(*admin_frame_type_room_button);
	admin_room_button->setRange(Gnk_Point(40.0f, 580.0f), Gnk_Point(400.0f, 660.0f));
	admin_room_button->setText("Manage Room");
	admin_room_button->setClickProcess(admin_frame_room_button_click);

	Gnk_Button_With_Text *admin_room_revenue_button = new Gnk_Button_With_Text(*admin_frame_type_room_button);
	admin_room_revenue_button->setRange(Gnk_Point(40.0f, 480.0f), Gnk_Point(400.0f, 560.0f));
	admin_room_revenue_button->setText("Room Revenue");
	admin_room_revenue_button->setClickProcess(admin_frame_room_revenue_button_click);

	Gnk_Button_With_Text *admin_type_room_view_and_edit_button = new Gnk_Button_With_Text(*admin_frame_type_room_button);
	admin_type_room_view_and_edit_button->setRange(Gnk_Point(40.0f, 680.0f), Gnk_Point(400.0f, 760.0f));
	admin_type_room_view_and_edit_button->setText("View and Edit");
	admin_type_room_view_and_edit_button->setClickProcess(admin_type_room_view_and_edit_button_click);

	Gnk_Button_With_Text *admin_add_type_room_button = new Gnk_Button_With_Text(*admin_frame_type_room_button);
	admin_add_type_room_button->setRange(Gnk_Point(40.0f, 580.0f), Gnk_Point(400.0f, 660.0f));
	admin_add_type_room_button->setText("Add Type Room");
	admin_add_type_room_button->setClickProcess(admin_add_type_room_button_click);

	Gnk_Button_With_Text *admin_remove_type_room_button = new Gnk_Button_With_Text(*admin_frame_type_room_button);
	admin_remove_type_room_button->setRange(Gnk_Point(40.0f, 480.0f), Gnk_Point(400.0f, 560.0f));
	admin_remove_type_room_button->setText("Remove Type Room");
	admin_remove_type_room_button->setClickProcess(admin_remove_type_room_button_click);

	Gnk_Button_With_Text *admin_room_view_and_edit_button = new Gnk_Button_With_Text(*admin_frame_type_room_button);
	admin_room_view_and_edit_button->setRange(Gnk_Point(40.0f, 680.0f), Gnk_Point(400.0f, 760.0f));
	admin_room_view_and_edit_button->setText("View and Edit");
	admin_room_view_and_edit_button->setClickProcess(admin_room_view_and_edit_button_click);

	Gnk_Button_With_Text *admin_add_room_button = new Gnk_Button_With_Text(*admin_frame_type_room_button);
	admin_add_room_button->setRange(Gnk_Point(40.0f, 580.0f), Gnk_Point(400.0f, 660.0f));
	admin_add_room_button->setText("Add Room");
	admin_add_room_button->setClickProcess(admin_add_room_button_click);

	Gnk_Button_With_Text *admin_remove_room_button = new Gnk_Button_With_Text(*admin_frame_type_room_button);
	admin_remove_room_button->setRange(Gnk_Point(40.0f, 480.0f), Gnk_Point(400.0f, 560.0f));
	admin_remove_room_button->setText("Remove Room");
	admin_remove_room_button->setClickProcess(admin_remove_room_button_click);

	Gnk_Button_With_Text *admin_daily_revenue = new Gnk_Button_With_Text(*admin_frame_type_room_button);
	admin_daily_revenue->setRange(Gnk_Point(40.0f, 680.0f), Gnk_Point(400.0f, 760.0f));
	admin_daily_revenue->setText("Daily Revenue");
	admin_daily_revenue->setClickProcess(admin_daily_revenue_button_click);

	Gnk_Button_With_Text *admin_monthly_revenue = new Gnk_Button_With_Text(*admin_frame_type_room_button);
	admin_monthly_revenue->setRange(Gnk_Point(40.0f, 580.0f), Gnk_Point(400.0f, 660.0f));
	admin_monthly_revenue->setText("Monthly Revenue");
	admin_monthly_revenue->setClickProcess(admin_monthly_revenue_button_click);

	Gnk_Button_With_Text *admin_yearly_revenue = new Gnk_Button_With_Text(*admin_frame_type_room_button);
	admin_yearly_revenue->setRange(Gnk_Point(40.0f, 480.0f), Gnk_Point(400.0f, 560.0f));
	admin_yearly_revenue->setText("Yearly Revenue");
	admin_yearly_revenue->setClickProcess(admin_yearly_revenue_button_click);


	Gnk_Button_With_Text *admin_frame_back_to_main_button = new Gnk_Button_With_Text(*admin_frame_type_room_button);
	admin_frame_back_to_main_button->setRange(Gnk_Point(40.0f, 380.0f), Gnk_Point(400.0f, 460.0f));
	admin_frame_back_to_main_button->setText("Back to Main");
	admin_frame_back_to_main_button->setClickProcess(admin_frame_back_to_main_button_click);

	Gnk_Button *admin_frame_select_type_room_button = new Gnk_Button();
	admin_frame_select_type_room_button->setRange(Gnk_Point(0.0f, 0.0f), Gnk_Point(1050.0f, 300.0f));
	admin_frame_select_type_room_button->setColor(H_FFFFFF);
	admin_frame_select_type_room_button->setHoverProcess(button_hover_type_1);
	admin_frame_select_type_room_button->setClickProcess(admin_frame_select_type_room_button_click);
	admin_frame_select_type_room_button->setAppear(true);

	Gnk_List_Object *admin_frame_type_room_list = new Gnk_List_Object();
	admin_frame_type_room_list->setRange(Gnk_Point(430.0f, 0.0f), Gnk_Point(1600.0f, 800.0f));
	admin_frame_type_room_list->setCurrentPos(admin_frame_type_room_list->getGroupHeight());
	admin_frame_type_room_list->setObjectWidth(1050);
	admin_frame_type_room_list->setObjectHeight(300);
	admin_frame_type_room_list->setObjectStartPosition(Gnk_Point(50.0f, 460.0f));
	admin_frame_type_room_list->setObjectSpace(50);
	admin_frame_type_room_list->setGroupHeight(680);
	admin_frame_type_room_list->setDrawProcess(admin_frame_type_room_list_process);
	admin_frame_type_room_list->addButton(admin_frame_select_type_room_button);

	Gnk_Button *admin_frame_select_room_button = new Gnk_Button();
	admin_frame_select_room_button->setRange(Gnk_Point(0.0f, 0.0f), Gnk_Point(1050.0f, 300.0f));
	admin_frame_select_room_button->setColor(H_FFFFFF);
	admin_frame_select_room_button->setHoverProcess(button_hover_type_1);
	admin_frame_select_room_button->setClickProcess(admin_frame_select_room_button_click);

	Gnk_List_Object *admin_frame_room_list = new Gnk_List_Object();
	admin_frame_room_list->setRange(Gnk_Point(430.0f, 0.0f), Gnk_Point(1600.0f, 800.0f));
	admin_frame_room_list->setCurrentPos(admin_frame_room_list->getGroupHeight());
	admin_frame_room_list->setObjectWidth(1050);
	admin_frame_room_list->setObjectHeight(300);
	admin_frame_room_list->setObjectStartPosition(Gnk_Point(50.0f, 460.0f));
	admin_frame_room_list->setObjectSpace(50);
	admin_frame_room_list->setGroupHeight(680);
	admin_frame_room_list->setDrawProcess(admin_frame_room_list_process);
	admin_frame_room_list->addButton(admin_frame_select_room_button);

	Gnk_Button_With_Text *admin_frame_confirm_button = new Gnk_Button_With_Text();
	admin_frame_confirm_button->setRange(Gnk_Point(1320.0f, 30.0f), Gnk_Point(1530.0f, 100.0f));
	admin_frame_confirm_button->setColor(C_1A1A1D);
	admin_frame_confirm_button->setText("Confirm");
	admin_frame_confirm_button->setTextFont("helvetica-bold");
	admin_frame_confirm_button->setFontSize(24.0f);
	admin_frame_confirm_button->setTextAlign(GNK_TEXT_CENTER);
	admin_frame_confirm_button->setTextColor(H_FFFFFF);
	admin_frame_confirm_button->setRadius(20.0f);
	admin_frame_confirm_button->setBorder(true);
	admin_frame_confirm_button->setHoverProcess(button_hover_type_3);
	admin_frame_confirm_button->setClickProcess(admin_frame_confirm_button_click);

	Gnk_Button_With_Text *admin_frame_previous_button = new Gnk_Button_With_Text(*admin_frame_confirm_button);
	admin_frame_previous_button->setRange(Gnk_Point(480.0f, 30.0f), Gnk_Point(700.0f, 100.0f));
	admin_frame_previous_button->setText("Previous");
	admin_frame_previous_button->setClickProcess(admin_frame_previous_button_click);

	Gnk_Textbox *admin_bed_type_textbox = new Gnk_Textbox();
	admin_bed_type_textbox->setRange(Gnk_Point(1020.0f, 520.0f), Gnk_Point(1480.0f, 570.0f));
	admin_bed_type_textbox->setColor(H_FFFFFF);
	admin_bed_type_textbox->setBorderRadius(0.0f);
	admin_bed_type_textbox->setTextFont("helvetica");
	admin_bed_type_textbox->setFontSize(24.0f);
	admin_bed_type_textbox->setTextColor(C_1A1A1D);
	admin_bed_type_textbox->setPaddingX(0.0f);
	admin_bed_type_textbox->setPaddingY(0.0f);
	admin_bed_type_textbox->setTextAlign(GNK_TEXT_LEFT);
	admin_bed_type_textbox->setSelectProcess(textbox_select_type3);
	admin_bed_type_textbox->setMaxLength(12);

	Gnk_Textbox *admin_number_of_guest_textbox = new Gnk_Textbox(*admin_bed_type_textbox);
	admin_number_of_guest_textbox->setRange(Gnk_Point(1020.0f, 460.0f), Gnk_Point(1480.0f, 510.0f));
	admin_number_of_guest_textbox->setMaxLength(1);

	Gnk_Textbox *admin_area_textbox = new Gnk_Textbox(*admin_bed_type_textbox);
	admin_area_textbox->setRange(Gnk_Point(1020.0f, 400.0f), Gnk_Point(1480.0f, 450.0f));
	admin_area_textbox->setMaxLength(3);

	Gnk_Textbox *admin_price_textbox = new Gnk_Textbox(*admin_bed_type_textbox);
	admin_price_textbox->setRange(Gnk_Point(1020.0f, 340.0f), Gnk_Point(1480.0f, 390.0f));
	admin_price_textbox->setMaxLength(20);

	Gnk_Textbox *admin_description_textbox = new Gnk_Textbox(*admin_bed_type_textbox);
	admin_description_textbox->setRange(Gnk_Point(1020.0f, 280.0f), Gnk_Point(1480.0f, 330.0f));
	admin_description_textbox->setMaxLength(200);

	Gnk_Textbox *admin_type_room_textbox = new Gnk_Textbox(*admin_bed_type_textbox);
	admin_type_room_textbox->setRange(Gnk_Point(1020.0f, 580.0f), Gnk_Point(1480.0f, 630.0f));
	admin_type_room_textbox->setMaxLength(8);

	Gnk_Textbox *admin_room_ID_textbox = new Gnk_Textbox(*admin_bed_type_textbox);
	admin_room_ID_textbox->setRange(Gnk_Point(1020.0f, 520.0f), Gnk_Point(1480.0f, 570.0f));
	admin_room_ID_textbox->setMaxLength(MAX_MAPHONG);

	admin.addButton("type_room_button", admin_frame_type_room_button);
	admin.addButton("room_button", admin_room_button);
	admin.addButton("room_revenue_button", admin_room_revenue_button);

	admin.addButton("type_room_view_and_edit_button", admin_type_room_view_and_edit_button);
	admin.addButton("add_type_room_button", admin_add_type_room_button);
	admin.addButton("remove_type_room_button", admin_remove_type_room_button);

	admin.addButton("room_view_and_edit_button", admin_room_view_and_edit_button);
	admin.addButton("add_room_button", admin_add_room_button);
	admin.addButton("remove_room_button", admin_remove_room_button);

	admin.addButton("daily_revenue_button", admin_daily_revenue);
	admin.addButton("monthly_revenue_button", admin_monthly_revenue);
	admin.addButton("yearly_revenue_button", admin_yearly_revenue);

	admin.addButton("back_to_main_button", admin_frame_back_to_main_button);

	admin.addListObject("type_room_list", admin_frame_type_room_list);
	admin.addListObject("room_list", admin_frame_room_list);

	admin.addButton("confirm_button", admin_frame_confirm_button);
	admin.addButton("previous_button", admin_frame_previous_button);

	admin.addTextbox("bed_type_textbox", admin_bed_type_textbox);
	admin.addTextbox("number_of_guest_textbox", admin_number_of_guest_textbox);
	admin.addTextbox("area_textbox", admin_area_textbox);
	admin.addTextbox("price_textbox", admin_price_textbox);
	admin.addTextbox("description_textbox", admin_description_textbox);
	admin.addTextbox("type_room_textbox", admin_type_room_textbox);
	admin.addTextbox("room_ID_textbox", admin_room_ID_textbox);
}

void UI_init() {
	// Initialize
	const float width = 1600.0f, height = 900.0f;
	gnk_Initialize(width, height, "PBL2 - Hotel Management", "shader/text.vs", "shader/text.fs");
	gnk_Set_Frame_Space(frame_Space);

	gnk_Font_List.addFont("arial", "font/arial.ttf", 48);
	gnk_Font_List.addFont("helvetica", "font/Helvetica.ttf", 24);
	gnk_Font_List.addFont("helvetica-bold", "font/Helvetica-Bold.ttf", 48);
	gnk_Font_List.addFont("helvetica-bold-64", "font/Helvetica-Bold.ttf", 64);

	gnk_Image_List.addImage("hotel_image", "image/hoteldelluna.jpg");
	gnk_Image_List.addImage("user_icon", "image/user_icon.png");
	gnk_Image_List.addImage("password_icon", "image/password_icon.png");
	gnk_Image_List.addImage("search_icon", "image/search_icon.png");
	gnk_Image_List.addImage("man_icon", "image/man_icon.png");
	gnk_Image_List.addImage("woman_icon", "image/woman_icon.png");

	UI_input_buffer.str("");UI_input_buffer.clear();
	UI_output_buffer.str("");UI_output_buffer.clear();
	current_Data->list_all_type_room();

	string type_room;
	while(getline(UI_output_buffer, type_room)) {
		try {
			gnk_Image_List.addImage(type_room, "image/LoaiPhong/" + type_room + ".jpg");
		}
		catch(...) {
			cout << "Error: " << type_room << endl;
		}
	}

	login_frame_init();
	sign_up_frame_init();
	guest_frame_init();
	staff_frame_init();
	admin_frame_init();

	Gnk_Button_With_Text *guest_frame_logout_button = new Gnk_Button_With_Text();
	guest_frame_logout_button->setRange(Gnk_Point(1380.0f, 820.0f), Gnk_Point(1540.0f, 880.0f));
	guest_frame_logout_button->setColor(H_FFECB8);
	guest_frame_logout_button->setText("Logout");
	guest_frame_logout_button->setTextFont("helvetica-bold");
	guest_frame_logout_button->setFontSize(24.0f);
	guest_frame_logout_button->setTextColor(H_222831);
	guest_frame_logout_button->setPaddingX(0.0f);
	guest_frame_logout_button->setPaddingY(0.0f);
	guest_frame_logout_button->setTextAlign(GNK_TEXT_CENTER);
	guest_frame_logout_button->setRadius(10.0f);
	guest_frame_logout_button->setHoverProcess(button_hover_type_1);
	guest_frame_logout_button->setClickProcess(logout_button_click);

	Gnk_Button_With_Text *staff_frame_logout_button = new Gnk_Button_With_Text(*guest_frame_logout_button);
	Gnk_Button_With_Text *admin_frame_logout_button = new Gnk_Button_With_Text(*guest_frame_logout_button);

	guest.addButton("logout_button", guest_frame_logout_button);
	staff.addButton("logout_button", staff_frame_logout_button);
	admin.addButton("logout_button", admin_frame_logout_button);
}

void frame_Space() {
	if(previous_frame == current_frame) {
		return;
	}
	if(current_frame == LOGIN_FRAME) {
		login_failed = false;
		login.clear_Textbox();
	}
	else if(current_frame == SIGN_UP_FRAME) {
		for(auto &toggle : sign_up.buttonList) {
			if(toggle.first == "male_toggle") {
				((Gnk_Button_Toggle *)toggle.second)->toggle = false;
			}
			else if(toggle.first == "female_toggle") {
				((Gnk_Button_Toggle *)toggle.second)->toggle = false;
			}
		}
		sign_up.clear_Textbox();
	}
	else if(current_frame == GUEST_FRAME) {
		option = DEFAULT_OPTION;
		guest.clear_Textbox();
	}
	else if(current_frame == STAFF_FRAME) {
		staff.clear_Textbox();
	}
	else if(current_frame == ADMIN_FRAME) {
		admin.clear_Textbox();
	}
	switch (current_frame) {
	case GUEST_FRAME:
		gnk_Set_Current_Frame(guest);
		break;
	case LOGIN_FRAME:
		gnk_Set_Current_Frame(login);
		break;
	case SIGN_UP_FRAME:
		gnk_Set_Current_Frame(sign_up);
		break;
	case STAFF_FRAME:
		gnk_Set_Current_Frame(staff);
		break;
	case ADMIN_FRAME:
		option = ADMIN_MAIN;
		gnk_Set_Current_Frame(admin);
		break;
	default:
		gnk_Set_Current_Frame(gnk_Default_Frame);
	}
	previous_frame = current_frame;
}
