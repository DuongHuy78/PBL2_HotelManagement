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
string check_in_date_str = "";
string check_out_date_str = "";
string number_of_guest_str = "";
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
// ---------------------------------------------------------
Gnk_Color light_yellow(255, 236, 200);
Gnk_Color light_yellow2(253, 247, 228);
Gnk_Color black(0, 0, 0);
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
	buttonText->text_color = Gnk_Color(90, 100, 147);
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

void textbox_select_type3(Gnk_Textbox *textbox) {
	gnk_Set_Object_Color(Gnk_Color(34, 40, 49));
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
	gnk_Set_Object_Color(Gnk_Color(74, 98, 138));
	gnk_Set_Line_Width(3.0f);
	gnk_Rounded_Rectangle(textbox->A, textbox->B, textbox->border_radius, false);
	gnk_Set_Line_Width(1.0f);
}

// ---------------------------------------------------------
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

	for(auto &textbox : frame->textboxList) {
		textbox.second->display();
	}
	for(auto &button : frame->buttonList) {
		button.second->display();
	}

	if(login_failed) {
		gnk_Set_Object_Color(Gnk_Color(255, 0, 0));
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
	UI_input_buffer.clear();
	UI_output_buffer.clear();
	UI_input_buffer << (login.textboxList["username_textbox"])->text << endl;
	UI_input_buffer << (login.textboxList["password_textbox"])->text << endl;
	if(current_Data->dangNhap()) {
		if(current_Data->getCurrentRole() == KHACHHANG) {
			current_frame = GUEST_FRAME;
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
	}
	else {
		login_failed = true;
	}
}

void login_frame_forgotten_password_button_click(Gnk_Button *button) {
	Gnk_Button_With_Text *buttonText = (Gnk_Button_With_Text *)button;
	Gnk_Color color = buttonText->text_color;
	buttonText->text_color = Gnk_Color(70, 80, 127);
	buttonText->draw();
	buttonText->text_color = color;
	//current_frame = FORGOT_PASSWORD_FRAME;
}

void login_frame_sign_up_button_click(Gnk_Button *button) {
	Gnk_Button_With_Text *buttonText = (Gnk_Button_With_Text *)button;
	Gnk_Color color = buttonText->text_color;
	buttonText->text_color = Gnk_Color(70, 80, 127);
	buttonText->draw();
	buttonText->text_color = color;
	current_frame = SIGN_UP_FRAME;
}

Gnk_Frame login(login_frame_draw);
// ---------------------------------------------------------
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

	for(auto &textbox : frame->textboxList) {
		textbox.second->display();
	}
	for(auto &button : frame->buttonList) {
		button.second->display();
	}
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
	gnk_Set_Background_Color(Gnk_Color(243, 242, 242));

	gnk_Set_Object_Color(Gnk_Color(34, 40, 49));
	gnk_Rectangle(Gnk_Point(0.0f, 800.0f), Gnk_Point(1600.0f, 900.0f));

	gnk_Set_Object_Color(Gnk_Color(34, 40, 49));
	gnk_Rectangle(Gnk_Point(0.0f, 0.0f), Gnk_Point(430.0f, 800.0f));

	gnk_Set_Object_Color(Gnk_Color(126, 126, 129));
	gnk_Set_Line_Width(2.0f);
	gnk_Line(Gnk_Point(20.0f, 800.0f), Gnk_Point(1560.0f, 800.0f));

	gnk_Set_Object_Color(Gnk_Color(255, 236, 200));
	gnk_Set_Character_Font("helvetica-bold");
	gnk_Text("HOTEL DEL LUNA", Gnk_Point(40.0f, 830.0f), 40.0f);

	gnk_Set_Object_Color(Gnk_Color(255, 255, 255));
	gnk_Set_Character_Font("helvetica");
	gnk_Text("Have a great day and enjoy your stay!", Gnk_Point(430.0f, 830.0f), 24.0f);

	frame->buttonList["logout_button"]->display();
	frame->buttonList["search_room_button"]->display();
	frame->buttonList["booking_infomation_button"]->display();
	frame->buttonList["profile_button"]->display();
	frame->buttonList["booking_button"]->display();
	if(option == SEARCH_ROOM) {
		// Search box
		gnk_Set_Object_Color(light_yellow2);
		gnk_Rounded_Rectangle(Gnk_Point(490.0f, 700.0f), Gnk_Point(1510.0f, 760.0f), 30.0f);
		// Vẽ các textbox
		gnk_Set_Object_Color(Gnk_Color(26, 26, 29));
		frame->textboxList["check_in_textbox"]->display();
		frame->textboxList["check_out_textbox"]->display();
		frame->textboxList["number_of_guest_textbox"]->display();
		frame->buttonList["lookup"]->display();
		// Vẽ list phòng
		frame->listObjectList["search_room_list"]->draw();
		// Vẽ cái đường viền
		gnk_Set_Object_Color(Gnk_Color(17, 17, 17));
		gnk_Set_Line_Width(2.0f);
		gnk_Rounded_Rectangle(Gnk_Point(490.0f, 700.0f), Gnk_Point(1510.0f, 760.0f), 30.0f, false);
		gnk_Line(Gnk_Point(825.0f, 700.0f), Gnk_Point(825.0f, 760.0f));
		gnk_Line(Gnk_Point(1135.0f, 700.0f), Gnk_Point(1135.0f, 760.0f));
		gnk_Line(Gnk_Point(1445.0f, 700.0f), Gnk_Point(1445.0f, 760.0f));
		gnk_Line(Gnk_Point(430.0f, 680.0f), Gnk_Point(1600.0f, 680.0f));
		gnk_Set_Line_Width(1.0f);
	}
	else if(option == BOOKING_INFORMATION) {
		// Booking information
	}
	else if(option == PROFILE) {
		gnk_Set_Object_Color(black);
		gnk_Rectangle(Gnk_Point(530.0f, 250.0f), Gnk_Point(1500.0f, 700.0f), false);
		gnk_Set_Object_Color(light_yellow2);
		gnk_Rectangle(Gnk_Point(530.0f, 250.0f), Gnk_Point(1500.0f, 700.0f));

		gnk_Set_Object_Color(black);
		gnk_Set_Character_Font("helvetica-bold");
		gnk_Text_Limited("My Profile", Gnk_Point(530.0f, 710.0f), 970.0f, 60.0f, 40.0f, GNK_TEXT_LEFT);
		
		if(current_guest_profile.gender == NAM) {
			gnk_Image(gnk_Image_List["man_icon"], Gnk_Point(560.0f, 370.0f), Gnk_Point(860.0f, 670.0f));
		}
		if(current_guest_profile.gender == NU) {
			gnk_Image(gnk_Image_List["woman_icon"], Gnk_Point(560.0f, 370.0f), Gnk_Point(860.0f, 670.0f));
		}

		gnk_Set_Object_Color(Gnk_Color(254, 249, 242));
		gnk_Rounded_Rectangle(Gnk_Point(560.0f, 280.0f), Gnk_Point(860.0f, 340.0f), 20.0f);
		gnk_Set_Object_Color(Gnk_Color(64, 64, 64));
		gnk_Text_Limited(current_guest_profile.username, Gnk_Point(560.0f, 294.0f), 300.0f, 40.0f, 24.0f, GNK_TEXT_CENTER);

		gnk_Text("ID:", Gnk_Point(940.0f, 600.0f), 24.0f);
		gnk_Text("Name:", Gnk_Point(940.0f, 550.0f), 24.0f);
		gnk_Text("Date of birth:", Gnk_Point(940.0f, 500.0f), 24.0f);
		gnk_Text("Phone number:", Gnk_Point(940.0f, 450.0f), 24.0f);
		gnk_Text("Gender:", Gnk_Point(940.0f, 400.0f), 24.0f);
		gnk_Text(current_guest_profile.ID, Gnk_Point(1140.0f, 600.0f), 24.0f);
		if(edit_profile) {
			frame->textboxList["profile_name_textbox"]->text = Utils::chuanHoaTen(frame->textboxList["profile_name_textbox"]->text);
			frame->textboxList["profile_name_textbox"]->display();
			frame->textboxList["profile_date_of_birth_textbox"]->display();
			frame->textboxList["profile_phone_number_textbox"]->display();
			frame->textboxList["profile_gender_textbox"]->display();
			frame->buttonList["save_profile_button"]->display();
		}
		else {
			gnk_Set_Object_Color(Gnk_Color(64, 64, 64));
			gnk_Text(current_guest_profile.name, Gnk_Point(1140.0f, 550.0f), 24.0f);
			gnk_Text(current_guest_profile.date_of_birth, Gnk_Point(1140.0f, 500.0f), 24.0f);
			gnk_Text(current_guest_profile.phone_number, Gnk_Point(1140.0f, 450.0f), 24.0f);
			gnk_Text(Utils::genderToString(current_guest_profile.gender), Gnk_Point(1140.0f, 400.0f), 24.0f);
		}
		frame->buttonList["change_profile_button"]->display();
	}
	else if(option == BOOKING) {
		// Booking
	}
}

void guest_frame_logout_button_click(Gnk_Button *button) {
	Gnk_Button_With_Text *buttonText = (Gnk_Button_With_Text *)button;
	Gnk_Color color = buttonText->color;
	buttonText->color = color - Gnk_Color(40, 40, 40);
	buttonText->draw();
	buttonText->color = color;
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
	option = BOOKING_INFORMATION;
}

void guest_frame_profile_button_click(Gnk_Button *button) {
	Gnk_Button_With_Text *buttonText = (Gnk_Button_With_Text *)button;
	Gnk_Color color = buttonText->color;
	buttonText->color = color - Gnk_Color(40, 40, 40);
	buttonText->draw();
	buttonText->color = color;
	option = PROFILE;
}

void guest_frame_booking_button_click(Gnk_Button *button) {
	Gnk_Button_With_Text *buttonText = (Gnk_Button_With_Text *)button;
	Gnk_Color color = buttonText->color;
	buttonText->color = color - Gnk_Color(40, 40, 40);
	buttonText->draw();
	buttonText->color = color;
	option = BOOKING;
}

void guest_frame_search_room_list_process(Gnk_List_Object *list) {
	if(search_room_list_enable) {
		if(room_list_init == false) {
			room_list.clear();
			UI_input_buffer.clear();
			UI_output_buffer.clear();
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
				getline(UI_output_buffer, line);
				room.amount = line;
				room_list.push_back(room);
			}
			room_list_init = true;
		}
		list->setGroupHeight(list->toNextObject()*room_list.size());
		for(int i = 0; i < room_list.size(); i++) {
			GLint scissorBox[4];
			glGetIntegerv(GL_SCISSOR_BOX, scissorBox);
			gnk_Scissor_2_object(
			Gnk_Point(gnk_Translate_X, gnk_Translate_Y - i * list->toNextObject()),
			Gnk_Point(gnk_Translate_X + list->object_width, gnk_Translate_Y - i * list->toNextObject() + list->object_height),
			list->A, list->B);
			gnk_Set_Object_Color(Gnk_Color(255, 255, 255));
			gnk_Rectangle(Gnk_Point(0.0f, 0.0f - i * list->toNextObject()), Gnk_Point(list->object_width, 300.0f - i * list->toNextObject()));
			gnk_Set_Object_Color(Gnk_Color(120, 120, 120));
			gnk_Rectangle(Gnk_Point(0.0f, 0.0f - i * list->toNextObject()), Gnk_Point(list->object_height, 300.0f - i * list->toNextObject()));
			gnk_Set_Object_Color(Gnk_Color(17, 17, 17));
			gnk_Text("Loai Phong: " + room_list[i].type, Gnk_Point(340.0f, 250.0f - i * list->toNextObject()), 24.0f);
			gnk_Text("Loai Giuong: " + room_list[i].bed_type, Gnk_Point(340.0f, 220.0f - i * list->toNextObject()), 24.0f);
			gnk_Text("So Nguoi: " + room_list[i].number_of_guest, Gnk_Point(340.0f, 190.0f - i * list->toNextObject()), 24.0f);
			gnk_Text("Dien Tich: " + room_list[i].area, Gnk_Point(340.0f, 160.0f - i * list->toNextObject()), 24.0f);
			gnk_Text("Gia: " + room_list[i].price, Gnk_Point(340.0f, 130.0f - i * list->toNextObject()), 24.0f);
			gnk_Set_Line_Width(2.0f);
			gnk_Line(Gnk_Point(340.0f, 120.0f - i * list->toNextObject()), Gnk_Point(1030.0f, 120.0f - i * list->toNextObject()));
			gnk_Text_Multi_Line(room_list[i].description, Gnk_Point(340.0f, 90.0f - i * list->toNextObject()), 64, 10, 24);
			gnk_Text("So Luong: " + room_list[i].amount, Gnk_Point(880.0f, 250.0f - i * list->toNextObject()), 24.0f);
			glScissor(scissorBox[0], scissorBox[1], scissorBox[2], scissorBox[3]);
		}
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
	button->setAppear(false);
	gnk_Current_Frame->buttonList["save_profile_button"]->setAppear(true);
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
	button->setAppear(false);
	gnk_Current_Frame->buttonList["change_profile_button"]->setAppear(true);
	current_guest_profile.name = gnk_Current_Frame->textboxList["profile_name_textbox"]->text;
	current_guest_profile.date_of_birth = gnk_Current_Frame->textboxList["profile_date_of_birth_textbox"]->text;
	current_guest_profile.phone_number = gnk_Current_Frame->textboxList["profile_phone_number_textbox"]->text;
	current_guest_profile.gender = Utils::stringToGender(gnk_Current_Frame->textboxList["profile_gender_textbox"]->text);
	
	UI_input_buffer.clear();
	UI_output_buffer.clear();
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

Gnk_Frame guest(guest_frame_draw);

// ---------------------------------------------------------
void login_frame_init() {
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
	login_frame_username_textbox->setMaxLength(35);

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
	sign_up_frame_male_toggle->setColor(Gnk_Color(255, 255, 255));
	sign_up_frame_male_toggle->setText("Male");
	sign_up_frame_male_toggle->setTextFont("helvetica");
	sign_up_frame_male_toggle->setFontSize(24.0f);
	sign_up_frame_male_toggle->setPaddingX(15.0f);
	sign_up_frame_male_toggle->setPaddingY(10.0f);
	sign_up_frame_male_toggle->setTextColor(Gnk_Color(17, 17, 17));
	sign_up_frame_male_toggle->setToggleRange(Gnk_Point(745.0f, 240.0f), Gnk_Point(765.0f, 260.0f));
	sign_up_frame_male_toggle->setToggleColor(Gnk_Color(255, 255, 255));
	sign_up_frame_male_toggle->setToggleEnableColor(Gnk_Color(250, 177, 47));
	sign_up_frame_male_toggle->setToggleRadius(10.0f);
	sign_up_frame_male_toggle->setBorder(true);
	sign_up_frame_male_toggle->setBorderColor(Gnk_Color(45, 45, 45));
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
	sign_up_frame_sign_up_button->setClickProcess(sign_up_frame_sign_up_button_click);

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
	sign_up_frame_scrollbar->setMaxHeight(gnk_Height * 1.4);
	sign_up_frame_scrollbar->setCurrentPos(gnk_Height);
	sign_up_frame_scrollbar->setAppear(true);

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
	Gnk_Button_With_Text *guest_frame_logout_button = new Gnk_Button_With_Text();
	guest_frame_logout_button->setRange(Gnk_Point(1380.0f, 820.0f), Gnk_Point(1540.0f, 880.0f));
	guest_frame_logout_button->setColor(Gnk_Color(255, 236, 200));
	guest_frame_logout_button->setText("Logout");
	guest_frame_logout_button->setTextFont("helvetica-bold");
	guest_frame_logout_button->setFontSize(24.0f);
	guest_frame_logout_button->setTextColor(Gnk_Color(34, 40, 49));
	guest_frame_logout_button->setPaddingX(0.0f);
	guest_frame_logout_button->setPaddingY(0.0f);
	guest_frame_logout_button->setTextAlign(GNK_TEXT_CENTER);
	guest_frame_logout_button->border_radius = 10.0f;
	guest_frame_logout_button->setHoverProcess(button_hover_type_1);
	guest_frame_logout_button->setClickProcess(guest_frame_logout_button_click);

	Gnk_Button_With_Text *guest_frame_search_room_button = new Gnk_Button_With_Text(*guest_frame_logout_button);
	guest_frame_search_room_button->setRange(Gnk_Point(40.0f, 680.0f), Gnk_Point(400.0f, 760.0f));
	guest_frame_search_room_button->setColor(light_yellow2);
	guest_frame_search_room_button->setText("Search room");
	guest_frame_search_room_button->setTextFont("helvetica");
	guest_frame_search_room_button->setTextColor(Gnk_Color(26, 26, 29));
	guest_frame_search_room_button->setHoverProcess(button_hover_type_1);
	guest_frame_search_room_button->setClickProcess(nullptr);
	guest_frame_search_room_button->setTextAlign(GNK_TEXT_LEFT);
	guest_frame_search_room_button->setPaddingX(30.0f);
	guest_frame_search_room_button->setClickProcess(guest_frame_search_room_button_click);

	Gnk_Button_With_Text *guest_frame_booking_infomation_button = new Gnk_Button_With_Text(*guest_frame_search_room_button);
	guest_frame_booking_infomation_button->setRange(Gnk_Point(40.0f, 580.0f), Gnk_Point(400.0f, 660.0f));
	guest_frame_booking_infomation_button->setText("Booking infomation");
	guest_frame_booking_infomation_button->setClickProcess(guest_frame_booking_infomation_button_click);

	Gnk_Button_With_Text *guest_frame_profile_button = new Gnk_Button_With_Text(*guest_frame_search_room_button);
	guest_frame_profile_button->setRange(Gnk_Point(40.0f, 480.0f), Gnk_Point(400.0f, 560.0f));
	guest_frame_profile_button->setText("Profile");
	guest_frame_profile_button->setClickProcess(guest_frame_profile_button_click);

	Gnk_Button_With_Text *guest_frame_booking_button = new Gnk_Button_With_Text(*guest_frame_search_room_button);
	guest_frame_booking_button->setRange(Gnk_Point(40.0f, 380.0f), Gnk_Point(400.0f, 460.0f));
	guest_frame_booking_button->setText("Booking");
	guest_frame_booking_button->setClickProcess(guest_frame_booking_button_click);

	Gnk_Textbox_Keep_Placeholder *guest_frame_check_in_textbox = new Gnk_Textbox_Keep_Placeholder();
	guest_frame_check_in_textbox->setRange(Gnk_Point(520.0f, 700.0f), Gnk_Point(820.0f, 760.0f));
	guest_frame_check_in_textbox->setColor(light_yellow2);
	guest_frame_check_in_textbox->setTextFont("helvetica");
	guest_frame_check_in_textbox->setFontSize(24.0f);
	guest_frame_check_in_textbox->setTextColor(Gnk_Color(17, 17, 17));
	guest_frame_check_in_textbox->setPlaceholder("Check in");
	guest_frame_check_in_textbox->setPlaceholderFont("helvetica");
	guest_frame_check_in_textbox->setPlaceholderFontSize(24.0f);
	guest_frame_check_in_textbox->setPlaceholderColor(Gnk_Color(85, 85, 85));
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

	Gnk_List_Object *group = new Gnk_List_Object();
	group->setRange(Gnk_Point(430.0f, 0.0f), Gnk_Point(1600.0f, 680.0f));
	group->setCurrentPos(group->getGroupHeight());
	group->setObjectWidth(1050);
	group->setObjectHeight(300);
	group->setObjectStartPosition(Gnk_Point(50.0f, 340.0f));
	group->setObjectSpace(50);
	group->setGroupHeight(680);
	group->setDrawProcess(guest_frame_search_room_list_process);

	Gnk_Button_With_Image *guest_frame_lookup_button_image = new Gnk_Button_With_Image();
	guest_frame_lookup_button_image->setRange(Gnk_Point(1460.0f, 710.0f), Gnk_Point(1500.0f, 750.0f));
	guest_frame_lookup_button_image->setImage(&gnk_Image_List["search_icon"]);
	guest_frame_lookup_button_image->setClickProcess(guest_frame_lookup_button_image_click);
	guest_frame_lookup_button_image->setColor(light_yellow2);

	Gnk_Button_With_Text *guest_frame_change_profile_button = new Gnk_Button_With_Text();
	guest_frame_change_profile_button->setRange(Gnk_Point(1340.0f, 30.0f), Gnk_Point(1560.0f, 100.0f));
	guest_frame_change_profile_button->setColor(Gnk_Color(26, 26, 29));
	guest_frame_change_profile_button->setText("Change profile");
	guest_frame_change_profile_button->setTextFont("helvetica-bold");
	guest_frame_change_profile_button->setFontSize(24.0f);
	guest_frame_change_profile_button->setTextAlign(GNK_TEXT_CENTER);
	guest_frame_change_profile_button->setTextColor(Gnk_Color(255, 255, 255));
	guest_frame_change_profile_button->setRadius(20.0f);
	guest_frame_change_profile_button->setBorder(true);
	guest_frame_change_profile_button->setHoverProcess(button_hover_type_3);
	guest_frame_change_profile_button->setClickProcess(guest_frame_change_frofile_button_click);

	Gnk_Button_With_Text *guest_frame_save_profile_button = new Gnk_Button_With_Text(*guest_frame_change_profile_button);
	guest_frame_save_profile_button->setRange(Gnk_Point(1340.0f, 30.0f), Gnk_Point(1560.0f, 100.0f));
	guest_frame_save_profile_button->setText("Save profile");
	guest_frame_save_profile_button->setClickProcess(guest_frame_save_profile_button_click);

	Gnk_Textbox *guest_frame_profile_name_textbox = new Gnk_Textbox();
	guest_frame_profile_name_textbox->setRange(Gnk_Point(1140.0f, 540.0f), Gnk_Point(1440.0f, 580.0f));
	guest_frame_profile_name_textbox->setColor(light_yellow2);
	guest_frame_profile_name_textbox->setBorderRadius(0.0f);
	guest_frame_profile_name_textbox->setTextFont("helvetica");
	guest_frame_profile_name_textbox->setFontSize(24.0f);
	guest_frame_profile_name_textbox->setTextColor(Gnk_Color(17, 17, 17));
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

	guest.addButton("logout_button", guest_frame_logout_button);
	guest.addButton("search_room_button", guest_frame_search_room_button);
	guest.addButton("booking_infomation_button", guest_frame_booking_infomation_button);
	guest.addButton("profile_button", guest_frame_profile_button);
	guest.addButton("booking_button", guest_frame_booking_button);
	guest.addButton("lookup", guest_frame_lookup_button_image);
	guest.addTextbox("check_in_textbox", guest_frame_check_in_textbox);
	guest.addTextbox("check_out_textbox", guest_frame_check_out_textbox);
	guest.addTextbox("number_of_guest_textbox", guest_frame_number_of_guest_textbox);
	guest.addListObject("search_room_list", group);
	guest.addButton("change_profile_button", guest_frame_change_profile_button);
	guest.addButton("save_profile_button", guest_frame_save_profile_button);
	guest.addTextbox("profile_name_textbox", guest_frame_profile_name_textbox);
	guest.addTextbox("profile_date_of_birth_textbox", guest_frame_profile_date_of_birth_textbox);
	guest.addTextbox("profile_phone_number_textbox", guest_frame_profile_phone_number_textbox);
	guest.addTextbox("profile_gender_textbox", guest_frame_profile_gender_textbox);
}

void UI_init() {
	// Initialize
	const float width = 1600.0f, height = 900.0f;
	gnk_Initialize(width, height, "PBL2 - Hotel Management", "shader/text.vs", "shader/text.fs");
	gnk_Set_Frame_Space(frame_Space);

	gnk_Font_List.addFont("arial", "font/arial.ttf", 48);
	gnk_Font_List.addFont("helvetica", "font/Helvetica.ttf", 24);
	gnk_Font_List.addFont("helvetica-bold", "font/Helvetica-Bold.ttf", 48);

	gnk_Image_List.addImage("hotel_image", "image/hoteldelluna.jpg");
	gnk_Image_List.addImage("user_icon", "image/user_icon.png");
	gnk_Image_List.addImage("password_icon", "image/password_icon.png");
	gnk_Image_List.addImage("search_icon", "image/search_icon.png");
	gnk_Image_List.addImage("man_icon", "image/man_icon.png");
	gnk_Image_List.addImage("woman_icon", "image/woman_icon.png");
	login_frame_init();
	sign_up_frame_init();
	guest_frame_init();
}

void frame_Space() {
	if(previous_frame == current_frame) {
		return;
	}
	if(current_frame == LOGIN_FRAME) {
		login_failed = false;
		for(auto &textbox : login.textboxList) {
			((Gnk_Textbox *)textbox.second)->text = "";
		}
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
		for(auto &textbox : sign_up.textboxList) {
			((Gnk_Textbox *)textbox.second)->text = "";
		}
	}
	else if(current_frame == GUEST_FRAME) {
		option = DEFAULT_OPTION;
		for(auto &textbox : guest.textboxList) {
			((Gnk_Textbox *)textbox.second)->text = "";
		}
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
	default:
		gnk_Set_Current_Frame(gnk_Default_Frame);
	}
	previous_frame = current_frame;
}
