#include "header/gnk_2D.h"
bool creative = false;
// -Class Definition---------------------------------------------------------
// Point Definition
Gnk_Point::Gnk_Point(float x, float y) {
	this->x = x;
	this->y = y;
}

Gnk_Point::Gnk_Point(const Gnk_Point& other) {
	this->x = other.x;
	this->y = other.y;
}

Gnk_Point Gnk_Point::translate(float x, float y) {
	Gnk_Point newPoint(this->x + x, this->y + y);
	return newPoint;
}

// Color Definition
Gnk_Color::Gnk_Color(int r, int g, int b) {
	this->red = (float)r / GNK_NUM_COLORS;
	this->green = (float)g / GNK_NUM_COLORS;
	this->blue = (float)b / GNK_NUM_COLORS;
}

Gnk_Color::Gnk_Color(const Gnk_Color& other) {
	this->red = other.red;
	this->green = other.green;
	this->blue = other.blue;
}

Gnk_Color& Gnk_Color::operator=(const Gnk_Color& other) {
	if (this != &other) {
		this->red = other.red;
		this->green = other.green;
		this->blue = other.blue;
	}
	return *this;
}

Gnk_Color Gnk_Color::operator+(const Gnk_Color& other) {
	int r = (this->red + other.red)* GNK_NUM_COLORS;
	int g = (this->green + other.green)* GNK_NUM_COLORS;
	int b = (this->blue + other.blue)* GNK_NUM_COLORS;
	if(r > GNK_NUM_COLORS) r = GNK_NUM_COLORS;
	if(g > GNK_NUM_COLORS) g = GNK_NUM_COLORS;
	if(b > GNK_NUM_COLORS) b = GNK_NUM_COLORS;
	Gnk_Color newColor(r, g, b);
	return newColor;
}

Gnk_Color Gnk_Color::operator-(const Gnk_Color& other) {
	int r = (this->red - other.red) * GNK_NUM_COLORS;
	int g = (this->green - other.green) * GNK_NUM_COLORS;
	int b = (this->blue - other.blue) * GNK_NUM_COLORS;
	if(r < 0) r = 0;
	if(g < 0) g = 0;
	if(b < 0) b = 0;
	Gnk_Color newColor(r, g, b);
	return newColor;
}

// Font definition
Gnk_Font::Gnk_Font() {
	size = 0;
}

void Gnk_Font::add(char character, Gnk_Glyph glyph) {
	list[character] = glyph;
	if (glyph.size.y > maxHeight) maxHeight = glyph.size.y;
}

void Gnk_Font::remove(char character) {
	if (list.count(character) != 0) {
		list.erase(character);
	}
}

float Gnk_Font::getMaxHeight() {
	return maxHeight;
}

// Font List Definition
Gnk_Font& Gnk_Font_List::operator[](std::string key) {
	return this->list[key];
}

// Image Definition
Gnk_Image::Gnk_Image() {
	nrChannels = 1;
	width = height = 0;
	textureID = 0;
}

GLenum Gnk_Image::get_Format() {
	if (nrChannels == 1) return GL_RED;
	if (nrChannels == 3) return GL_RGB;
	if (nrChannels == 4) return GL_RGBA;
}

// Image List Definition
Gnk_Image& Gnk_Image_List::operator[](std::string key) {
	return this->list[key];
}

// Button Definition
Gnk_Button::Gnk_Button() {
	this->A = Gnk_Point();
	this->B = Gnk_Point();
	this->color = Gnk_Color();
	this->border_radius = 0;
}

void Gnk_Button::setAppear(bool appear) {
	this->appear = appear;
}

void Gnk_Button::setRange(Gnk_Point A, Gnk_Point B) {
	this->A = A;
	this->B = B;
}

void Gnk_Button::setColor(Gnk_Color color) {
	this->color = color;
}

void Gnk_Button::setRadius(float radius) {
	this->border_radius = radius;
}

void Gnk_Button::setHoverProcess(void (*hover)(Gnk_Button*)) {
	this->hover_process = hover;
}

void Gnk_Button::setClickProcess(void (*click)(Gnk_Button*)) {
	this->click_process = click;
}

void Gnk_Button::draw() {
	if (!appear) return;
	gnk_Set_Object_Color(color);
	gnk_Rounded_Rectangle(A, B, border_radius);
}

void Gnk_Button::display() {
	if (!appear) return;
	if (onClick && click_process != nullptr) {
		click_effect();
	}
	else if (onHover && hover_process != nullptr) {
		hover_effect();
	}
	else {
		draw();
	}
}

void Gnk_Button::hover_effect() {
	if (this->hover_process != nullptr) hover_process(this);
}

void Gnk_Button::click_effect() {
	if (this->click_process != nullptr) click_process(this);
	this->onClick = false;
}

void Gnk_Button::process() {
	if(!appear) return;
	double xpos, ypos;
	glfwGetCursorPos(gnk_Window, &xpos, &ypos);
	ypos = gnk_Height - ypos;
	if (glfwGetMouseButton(gnk_Window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
		if (xpos >= A.x && xpos <= B.x && 
		ypos >= A.y + (gnk_Height - gnk_Frame_Position)&& 
		ypos <= B.y + (gnk_Height - gnk_Frame_Position)) {
			onClick = true;
		}
		else {
			onClick = false;
		}
	}
	else if (xpos >= A.x && xpos <= B.x && 
		ypos >= A.y + (gnk_Height - gnk_Frame_Position)&& 
		ypos <= B.y + (gnk_Height - gnk_Frame_Position)) {
		onHover = true;
		onClick = false;
	}
	else {
		onHover = false;
		onClick = false;
	}
}

// Button with Text Definition
Gnk_Button_With_Text::Gnk_Button_With_Text() {
	this->text = "";
	this->text_font = "";
	this->font_size = 0;
	this->text_color = Gnk_Color();
	this->paddingX = 0;
	this->paddingY = 0;
	this->textAlign = GNK_TEXT_LEFT;
}

void Gnk_Button_With_Text::setText(std::string text) {
	this->text = text;
}

void Gnk_Button_With_Text::setTextFont(std::string font) {
	this->text_font = font;
}

void Gnk_Button_With_Text::setFontSize(float size) {
	this->font_size = size;
}

void Gnk_Button_With_Text::setTextColor(Gnk_Color color) {
	this->text_color = color;
}

void Gnk_Button_With_Text::setPaddingX(float x) {
	this->paddingX = x;
}

void Gnk_Button_With_Text::setPaddingY(float y) {
	this->paddingY = y;
}

void Gnk_Button_With_Text::setTextAlign(text_align_value align) {
	this->textAlign = align;
}

void Gnk_Button_With_Text::draw() {
	if (!appear) return;
	Gnk_Button::draw();
	gnk_Set_Character_Font(text_font);
	gnk_Set_Object_Color(text_color);
	float scale = font_size / gnk_Current_Font->size;
	float maxWidth = gnk_Get_Text_Width(text, font_size);
	float maxHeight = gnk_Current_Font->getMaxHeight() * scale;
	if (maxWidth > B.x - A.x - 2 * paddingX) {
		maxWidth = B.x - A.x - 2 * paddingX;
	}
	if (maxHeight > B.y - A.y - 2 * paddingY) {
		maxHeight = B.y - A.y - 2 * paddingY;
	}
	if (textAlign == GNK_TEXT_CENTER) {
		gnk_Text_Limited(text, A.translate(paddingX, paddingY), B.x - A.x - 2 * paddingX, B.y - A.y - 2 * paddingY, font_size, GNK_TEXT_CENTER);
	}
	else if (textAlign == GNK_TEXT_LEFT) {
		gnk_Text_Limited(text, A.translate(paddingX, paddingY), B.x - A.x - 2 * paddingX, B.y - A.y - 2 * paddingY, font_size, GNK_TEXT_LEFT);
	}
	else if (textAlign == GNK_TEXT_RIGHT) {
		gnk_Text_Limited(text, A.translate(paddingX, paddingY), B.x - A.x - 2 * paddingX, B.y - A.y - 2 * paddingY, font_size, GNK_TEXT_RIGHT);
	}
}

void Gnk_Button_With_Text::display() {
	if(!appear) return;
	if (onClick && click_process != nullptr) {
		click_effect();
	}
	else if (onHover && hover_process != nullptr) {
		hover_effect();
	}
	else {
		draw();
	}
}

// Button with Image Definition
Gnk_Button_With_Image::Gnk_Button_With_Image() {
	this->image = new Gnk_Image();
}

void Gnk_Button_With_Image::setImage(Gnk_Image *image) {
	Gnk_Image *tmp = this->image;
	this->image = image;
	delete tmp;
}

void Gnk_Button_With_Image::draw() {
	if (!appear) return;
	Gnk_Button::draw();
	gnk_Image(*image, A, B);
}

void Gnk_Button_With_Image::display() {
	if(!appear) return;
	if(onClick && click_process != nullptr) {
		click_effect();
	}
	else if(onHover && hover_process != nullptr) {
		hover_effect();
	}
	else {
		draw();
	}
}

// Textbox definition
Gnk_Textbox::Gnk_Textbox() {
	this->A = Gnk_Point();
	this->B = Gnk_Point();
	this->color = Gnk_Color();
	this->text = "";
	this->text_font = "";
	this->font_size = 0;
	this->text_color = Gnk_Color();
	this->placeholder = "";
	this->placeholder_font = "";
	this->placeholder_font_size = 0;
	this->placeholder_color = Gnk_Color();
	this->paddingX = 0;
	this->paddingY = 0;
	this->text_align = GNK_TEXT_LEFT;
	this->on_select = false;
}

void Gnk_Textbox::setAppear(bool appear) {
	this->appear = appear;
}

void Gnk_Textbox::setRange(Gnk_Point A, Gnk_Point B) {
	this->A = A;
	this->B = B;
}

void Gnk_Textbox::setColor(Gnk_Color color) {
	this->color = color;
}

void Gnk_Textbox::setBorderRadius(float radius) {
	this->border_radius = radius;
}

void Gnk_Textbox::setText(std::string text) {
	this->text = text;
}

void Gnk_Textbox::setTextFont(std::string font) {
	this->text_font = font;
}

void Gnk_Textbox::setFontSize(float size) {
	this->font_size = size;
}

void Gnk_Textbox::setTextColor(Gnk_Color color) {
	this->text_color = color;
}

void Gnk_Textbox::setPlaceholder(std::string text) {
	this->placeholder = text;
}

void Gnk_Textbox::setPlaceholderFont(std::string font) {
	this->placeholder_font = font;
}

void Gnk_Textbox::setPlaceholderFontSize(float size) {
	this->placeholder_font_size = size;
}

void Gnk_Textbox::setPlaceholderColor(Gnk_Color color) {
	this->placeholder_color = color;
}

void Gnk_Textbox::setPaddingX(float x) {
	this->paddingX = x;
}

void Gnk_Textbox::setPaddingY(float y) {
	this->paddingY = y;
}

void Gnk_Textbox::setTextAlign(text_align_value align) {
	this->text_align = align;
}

void Gnk_Textbox::setSelectProcess(void (*select)(Gnk_Textbox*)) {
	this->select_process = select;
}

float Gnk_Textbox::getWidth() {
	return B.x - A.x;
}

float Gnk_Textbox::getHeight() {
	return B.y - A.y;
}

void Gnk_Textbox::draw() {
	if (!appear) return;
	gnk_Set_Object_Color(color);
	gnk_Rounded_Rectangle(A, B, border_radius);
	std::string output;
	std::string output_font;
	float output_font_size;
	Gnk_Color output_color;
	if (text == "") {
		if (!on_select) output = placeholder;
		else output = "";
		output_font = placeholder_font;
		output_font_size = placeholder_font_size;
		output_color = placeholder_color;
	}
	else {
		output = text;
		output_font = text_font;
		output_font_size = font_size;
		output_color = text_color;
	}

	gnk_Set_Character_Font(output_font);
	float scale = output_font_size / gnk_Current_Font->size;
	gnk_Set_Object_Color(output_color);

	float maxWidth = gnk_Get_Text_Width(output, output_font_size);
	float maxHeight = gnk_Current_Font->getMaxHeight() * scale;

	if (maxWidth > getWidth() - 2 * paddingX) {
		maxWidth = getWidth() - 2 * paddingX;
	}
		
	if (maxHeight > getHeight() - 2 * paddingY)
		maxHeight = getHeight() - 2 * paddingY;

	float cpX = 0, cpY = 0;
	if (text_align == GNK_TEXT_CENTER) {
		gnk_Text_Limited(output, A.translate(paddingX, paddingY), getWidth() - 2 * paddingX, getHeight() - 2 * paddingY, font_size, GNK_TEXT_CENTER);
		cpX = paddingX + (getWidth() - 2 * paddingX - maxWidth) / 2 + maxWidth;
		cpY = paddingY + (getHeight() - 2 * paddingY - maxHeight) / 2 + maxHeight;
	}
	else if (text_align == GNK_TEXT_LEFT) {
		gnk_Text_Limited(output, A.translate(paddingX, paddingY), getWidth() - 2 * paddingX, getHeight() - 2 * paddingY, font_size, GNK_TEXT_LEFT);
		cpX = paddingX + maxWidth;
		cpY = paddingY + (getHeight() - 2 * paddingY - maxHeight) / 2 + maxHeight;
	}
	else if (text_align == GNK_TEXT_RIGHT) {
		gnk_Text_Limited(output, A.translate(paddingX, paddingY), getWidth() - 2 * paddingX, getHeight() - 2 * paddingY, font_size, GNK_TEXT_RIGHT);
		cpX = paddingX + (getWidth() - 2 * paddingX - maxWidth) + maxWidth;
		cpY = paddingY + (getHeight() - 2 * paddingY - maxHeight) / 2 + maxHeight;
	}
	
	if (on_select) {
		if (glfwGetTime() - gnk_Text_Cursor_Last_Time > 0.5f) {
			gnk_Text_Cursor_Appear = !gnk_Text_Cursor_Appear;
			gnk_Text_Cursor_Last_Time = glfwGetTime();
		}
		if (gnk_Text_Cursor_Appear) {
			gnk_Set_Line_Width(2.0f);
			gnk_Set_Object_Color(Gnk_Color(0, 0, 0));
			gnk_Line(Gnk_Point(A.x + cpX, A.y + cpY - maxHeight),
				Gnk_Point(A.x + cpX, A.y + cpY));
			gnk_Set_Line_Width(1.0f);
		}
	}
}

void Gnk_Textbox::display() {
	if (!appear) return;
	if(on_select && select_process != nullptr) {
		select_effect();
	}
	else {
		draw();
	}
}

void Gnk_Textbox::select_effect() {
	if (select_process != NULL) select_process(this);
}

void Gnk_Textbox::process() {
	if(!appear) return;
	double xpos, ypos;
	glfwGetCursorPos(gnk_Window, &xpos, &ypos);
	ypos = gnk_Height - ypos;
	
	if (glfwGetMouseButton(gnk_Window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
		if (xpos >= A.x && xpos <= B.x && 
		ypos >= A.y + (gnk_Height - gnk_Frame_Position)&& 
		ypos <= B.y + (gnk_Height - gnk_Frame_Position)) {
			on_select = true;
		}
		else {
			on_select = false;
		}
	}
}

// Textbox Password Definition
void Gnk_Textbox_Password::draw() {
	if(!appear) return;
	std::string newText = this->text;
	for(int i = 0; i < this->text.size(); ++i) {
		this->text[i] = '*';
	}
	Gnk_Textbox::draw();
	this->text = newText;
}

void Gnk_Textbox_Password::display() {
	if(!appear) return;
	if(on_select && select_process != nullptr) {
		select_effect();
	}
	else {
		draw();
	}
}

// Frame Definition
Gnk_Frame::Gnk_Frame() {
	this->process = nullptr;
}

Gnk_Frame::~Gnk_Frame() {
	for(auto &it:buttonList) {
		if(it.second != nullptr) {
			delete it.second;
			it.second = nullptr;
		}
	}

	for(auto &it:textboxList) {
		if(it.second != nullptr) {
			delete it.second;
			it.second = nullptr;
		}
	}

	if(scrollbar != nullptr) {
		delete scrollbar;
	}
}

Gnk_Frame::Gnk_Frame(void (*process)(Gnk_Frame *)) {
	this->process = process;
}

void Gnk_Frame::addButton(std::string key, Gnk_Button *button) {
	buttonList[key] = button;
}

void Gnk_Frame::addTextbox(std::string key, Gnk_Textbox *textbox) {
	textboxList[key] = textbox;
}

void Gnk_Frame::setScrollbar(Gnk_Scrollbar *scrollbar) {
	this->scrollbar = scrollbar;
}

void Gnk_Frame::display() {
	if (process != nullptr) this->process(this);
}

// Scrollbar Definition------------------------------------------------------
Gnk_Scrollbar::Gnk_Scrollbar() {
	this->maxHeight = 0;
	this->frameHeight = 0;
	this->scrollPosition = 0;
	this->A = Gnk_Point();
	this->B = Gnk_Point();
	this->C = Gnk_Point();
	this->D = Gnk_Point();
	this->color = Gnk_Color();
	this->scrollColor = Gnk_Color();
	this->hoverColor = Gnk_Color();
	this->clickColor = Gnk_Color();
}

void Gnk_Scrollbar::setAppear(bool appear) {
	this->appear = appear;
	if(maxHeight <= frameHeight) appear = false;
}

void Gnk_Scrollbar::setRange(Gnk_Point A, Gnk_Point B) {
	this->A = A;
	this->B = B;
}

void Gnk_Scrollbar::setColor(Gnk_Color color) {
	this->color = color;
}

void Gnk_Scrollbar::setScrollColor(Gnk_Color color) {
	this->scrollColor = color;
}

void Gnk_Scrollbar::setHoverColor(Gnk_Color color) {
	this->hoverColor = color;
}

void Gnk_Scrollbar::setClickColor(Gnk_Color color) {
	this->clickColor = color;
}

void Gnk_Scrollbar::setMaxHeight(int maxHeight) {
	this->maxHeight = maxHeight;
}

void Gnk_Scrollbar::setFrameHeight(int frameHeight) {
	this->frameHeight = frameHeight;
}

void Gnk_Scrollbar::display() {
	if(!appear) return;
	gnk_Set_Object_Color(color);
	gnk_Rectangle(A.translate(0.0f, gnk_Frame_Position - gnk_Height), B.translate(0.0f, gnk_Frame_Position - gnk_Height));
	if(onClick) {
		gnk_Set_Object_Color(clickColor);
	}
	else if(onHover) {
		gnk_Set_Object_Color(hoverColor);
	}
	else {
		gnk_Set_Object_Color(scrollColor);
	}
	float ratio = (float)frameHeight / maxHeight;
	C = Gnk_Point(A.x, -ratio*(scrollPosition - frameHeight) + (ratio + 1)*(gnk_Frame_Position - gnk_Height));
	D = Gnk_Point(B.x, -ratio*(scrollPosition - 2 * frameHeight) + (ratio + 1)*(gnk_Frame_Position - gnk_Height));
	gnk_Rectangle(C, D);
}

void Gnk_Scrollbar::process() {
	if(!appear) return;
	double xpos, ypos;
	glfwGetCursorPos(gnk_Window, &xpos, &ypos);
	ypos = gnk_Height - ypos;
	if (glfwGetMouseButton(gnk_Window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
		if (xpos >= C.x && xpos <= D.x && 
		ypos >= C.y + (gnk_Height - gnk_Frame_Position)&& 
		ypos <= D.y + (gnk_Height - gnk_Frame_Position)) {
			onClick = true;
		}
		else {
			onClick = false;
		}
	}
	else if (xpos >= C.x && xpos <= D.x && 
		ypos >= C.y + (gnk_Height - gnk_Frame_Position)&& 
		ypos <= D.y + (gnk_Height - gnk_Frame_Position)) {
		onHover = true;
		onClick = false;
	}
	else {
		onHover = false;
		onClick = false;
	}
}

// -Variable Declaration-----------------------------------------------------
float gnk_Width = 0, gnk_Height = 0;	// screen width & screen height
unsigned int gnk_TVA, gnk_TVB;			// text vertex array & text vertex buffer

// window
GLFWwindow* gnk_Window = NULL;

// text render
FT_Library gnk_FT;
FT_Face gnk_Face;

Shader gnk_Shader;
Gnk_Frame gnk_Default_Frame;
Gnk_Frame* gnk_Current_Frame = &gnk_Default_Frame;
void (*gnk_Frame_Space)() = NULL;

Gnk_Font gnk_Default_Font;
Gnk_Font* gnk_Current_Font = &gnk_Default_Font;

Gnk_Font_List gnk_Font_List;
Gnk_Image_List gnk_Image_List;

double gnk_Text_Cursor_Last_Time;
bool gnk_Text_Cursor_Appear = false;
double gnk_Backspace_Last_Time = 0.0;
double gnk_Backspace_Speed = 0.06;
double gnk_Event_Timeout = 0.5;
int gnk_Scroll_Speed = 40;
int gnk_Frame_Position = 0;
static void gnk_Cursor_Position_Callback(GLFWwindow* window, double xpos, double ypos) {
	for(auto &it: gnk_Current_Frame->buttonList) {
		if(it.second != nullptr) {
			it.second->process();
		}
		if (gnk_Current_Frame->scrollbar != nullptr) {
			gnk_Current_Frame->scrollbar->process();
		}
	}
}

void gnk_Mouse_Button_Callback(GLFWwindow* window, int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
		creative = true;
	}
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE) {
		creative = false;
	}
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		for (auto& it : gnk_Current_Frame->buttonList) {
			if (it.second != nullptr) {
				it.second->process();
			}
		}
		for (auto& it : gnk_Current_Frame->textboxList) {
			if (it.second != nullptr) {
				it.second->process();
			}
		}
		if (gnk_Current_Frame->scrollbar != nullptr) {
			gnk_Current_Frame->scrollbar->process();
		}
	}
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
        for (auto& it : gnk_Current_Frame->buttonList) {
			if (it.second != nullptr) {
				it.second->onClick = false;
			}
		}
		if (gnk_Current_Frame->scrollbar != nullptr) {
			gnk_Current_Frame->scrollbar->onClick = false;
		}
    }
}

void gnk_Character_Callback(GLFWwindow* window, unsigned int codepoint) {
	for (auto& it : gnk_Current_Frame->textboxList) {
		if (it.second->on_select == true) {
			it.second->text += (char)codepoint;
		}
	}
}

void gnk_Scroll_Callback(GLFWwindow* window, double xoffset, double yoffset) {
	if(gnk_Current_Frame->scrollbar == nullptr) return;
	gnk_Frame_Position += yoffset * gnk_Scroll_Speed;

	if(gnk_Frame_Position > gnk_Height) gnk_Frame_Position = gnk_Height;
	if(gnk_Frame_Position < 2 * gnk_Height - gnk_Current_Frame->scrollbar->maxHeight) 
	gnk_Frame_Position = 2 * gnk_Height - gnk_Current_Frame->scrollbar->maxHeight;

	glm::mat4 projection = glm::ortho(0.0f, gnk_Width, 0.0f, gnk_Height);
	projection = glm::translate(projection, glm::vec3(0.0f, gnk_Height - gnk_Frame_Position, 0.0f));
	glUniformMatrix4fv(glGetUniformLocation(gnk_Shader.ID, "projection"),
		1, GL_FALSE, glm::value_ptr(projection));
	
}

void gnk_Key_Callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_BACKSPACE && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		double currentTime = glfwGetTime();
		if (currentTime - gnk_Backspace_Last_Time >= gnk_Backspace_Speed) {
			for (auto& it : gnk_Current_Frame->textboxList) {
				if (it.second->on_select == true) {
					if (!it.second->text.empty()) {
						it.second->text.pop_back();
					}
				}
			}
			gnk_Backspace_Last_Time = currentTime;
		}
	}
}

bool gnk_GLFW_Init() {
	if (glfwInit() == false) {
		std::cout << "ERROR::Khong The Khoi Tao GLFW" << std::endl;
		return 0;
	}
	return 1;
}

bool gnk_Create_Window(std::string title) {
	gnk_Window = glfwCreateWindow((int)gnk_Width, (int)gnk_Height, title.c_str(), NULL, NULL);
	if (gnk_Window == NULL) {
		std::cout << "ERROR::Khong The Khoi Tao Cua So::" << title << std::endl;
		return 0;
	}
	glfwMakeContextCurrent(gnk_Window);
	return 1;
}

bool gnk_GLEW_Init() {
	if (glewInit() != GLEW_OK) {
		std::cout << "ERROR::Khong The Khoi Tao GLEW" << std::endl;
		return 0;
	}
	return 1;
}

bool gnk_Shader_Init(std::string vertexPath, std::string fragmentPath) {
	gnk_Shader = Shader(vertexPath.c_str(), fragmentPath.c_str());
	gnk_Shader.use();
	glm::mat4 projection = glm::ortho(0.0f, gnk_Width, 0.0f, gnk_Height);
	glUniformMatrix4fv(glGetUniformLocation(gnk_Shader.ID, "projection"),
		1, GL_FALSE, glm::value_ptr(projection));
	return 1;
}

void gnk_Texture_Buffer_Init() {
	glGenVertexArrays(1, &gnk_TVA);
	glGenBuffers(1, &gnk_TVB);
	glBindVertexArray(gnk_TVA);
	glBindBuffer(GL_ARRAY_BUFFER, gnk_TVB);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 5, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void gnk_Initialize(float width, float height, std::string title, std::string vertexPath, std::string fragmentPath) {
	gnk_Width = width;
	gnk_Height = height;
	gnk_GLFW_Init();
	gnk_Create_Window(title);
	gnk_GLEW_Init();
	gnk_Shader_Init(vertexPath, fragmentPath);
	gnk_Texture_Buffer_Init();
	glfwSetMouseButtonCallback(gnk_Window, gnk_Mouse_Button_Callback);
	glfwSetCharCallback(gnk_Window, gnk_Character_Callback);
	glfwSetKeyCallback(gnk_Window, gnk_Key_Callback);
	glfwSetCursorPosCallback(gnk_Window, gnk_Cursor_Position_Callback);
	glfwSetScrollCallback(gnk_Window, gnk_Scroll_Callback);
	gnk_Frame_Position = gnk_Height;
}

void gnk_Set_Object_Color(Gnk_Color color) {
	gnk_Shader.use();
	glUniform3f(glGetUniformLocation(gnk_Shader.ID, "textColor"),
		color.red, color.green, color.blue);
}

void gnk_Set_Background_Color(Gnk_Color color) {
	glClearColor(color.red, color.green, color.blue, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void gnk_Process_Input() {
	if (glfwGetKey(gnk_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(gnk_Window, true);
	}
}

void gnk_Set_Frame_Space(void (*space)()) {
	gnk_Frame_Space = space;
}

void gnk_Set_Current_Frame(Gnk_Frame &frame) {
	gnk_Current_Frame = &frame;
}

void gnk_Window_Loop() {
	while (!glfwWindowShouldClose(gnk_Window)) {
		glClear(GL_COLOR_BUFFER_BIT);
		glfwWaitEventsTimeout(gnk_Event_Timeout);
		gnk_Process_Input();
		if(gnk_Frame_Space != NULL) gnk_Frame_Space();
		gnk_Current_Frame->display();
		if(creative) {
			double xpos, ypos;
			glfwGetCursorPos(gnk_Window, &xpos, &ypos);
			ypos = gnk_Height - ypos;
			gnk_Set_Object_Color(Gnk_Color(0, 0, 0));
			gnk_Set_Line_Width(1.5f);
			gnk_Line(Gnk_Point(xpos - 100, ypos), Gnk_Point(xpos + 100, ypos));
			gnk_Line(Gnk_Point(xpos, ypos - 100), Gnk_Point(xpos, ypos + 100));
			gnk_Set_Line_Width(1.0f);
			std::string message = "x: " + std::to_string(xpos) + " y: " + std::to_string(ypos);
			gnk_Text(message, Gnk_Point(50, 40), 24);
		}
		glfwSwapBuffers(gnk_Window);
		glfwPollEvents();
	}
}

void gnk_Triangle(Gnk_Point A, Gnk_Point B, Gnk_Point C, bool fill) {
	glBegin(fill * GL_POLYGON + !fill * GL_LINE_LOOP);
	glVertex2f(A.x, A.y);
	glVertex2f(B.x, B.y);
	glVertex2f(C.x, C.y);
	glEnd();
}

void gnk_Rectangle(Gnk_Point A, Gnk_Point B, bool fill) {
	glBegin(fill * GL_POLYGON + !fill * GL_LINE_LOOP);
	glVertex2f(A.x, A.y);
	glVertex2f(B.x, A.y);
	glVertex2f(B.x, B.y);
	glVertex2f(A.x, B.y);
	glEnd();
}

void gnk_Circle(Gnk_Point O, float radius, float a1, float a2, bool fill) {
	float theta = 0;
	float delta = 2 * GNK_PI / GNK_NUM_SEGMENTS;
	glBegin(fill * GL_POLYGON + !fill * GL_LINE_STRIP);
	for (int i = 0; i < GNK_NUM_SEGMENTS; ++i) {
		Gnk_Point A(radius * cos(theta), radius * sin(theta));
		theta = theta + delta;
		Gnk_Point B(radius * cos(theta), radius * sin(theta));
		if (theta - delta >= a1 && theta - delta <= a2) {
			glVertex2f(O.x + A.x, O.y + A.y);
			glVertex2f(O.x + B.x, O.y + B.y);
		}
	}
	if (fill) glVertex2f(O.x, O.y);
	glEnd();
}

void gnk_Set_Line_Width(float width) {
	glLineWidth(width);
}

void gnk_Line(Gnk_Point A, Gnk_Point B) {
	glBegin(GL_LINES);
	glVertex2f(A.x, A.y);
	glVertex2f(B.x, B.y);
	glEnd();
}

void gnk_Rounded_Rectangle(Gnk_Point A, Gnk_Point B, float radius, bool fill) {
	if (2 * radius > B.x - A.x) radius = (B.x - A.x) / 2;
	if (2 * radius > B.y - A.y) radius = (B.y - A.y) / 2;
	float theta = 0;
	float delta = 2 * GNK_PI / GNK_NUM_SEGMENTS;
	glBegin(fill * GL_POLYGON + !fill * GL_LINE_STRIP);

	for (int i = 0; 4 * i < GNK_NUM_SEGMENTS; ++i) {
		Gnk_Point C(radius * cos(theta), radius * sin(theta));
		theta = theta + delta;
		Gnk_Point D(radius * cos(theta), radius * sin(theta));
		glVertex2f(B.x - radius + C.x, B.y - radius + C.y);
		glVertex2f(B.x - radius + D.x, B.y - radius + D.y);
	}

	for (int i = 0; 4 * i < GNK_NUM_SEGMENTS; ++i) {
		Gnk_Point C(radius * cos(theta), radius * sin(theta));
		theta = theta + delta;
		Gnk_Point D(radius * cos(theta), radius * sin(theta));
		glVertex2f(A.x + radius + C.x, B.y - radius + C.y);
		glVertex2f(A.x + radius + D.x, B.y - radius + D.y);
	}

	for (int i = 0; 4 * i < GNK_NUM_SEGMENTS; ++i) {
		Gnk_Point C(radius * cos(theta), radius * sin(theta));
		theta = theta + delta;
		Gnk_Point D(radius * cos(theta), radius * sin(theta));
		glVertex2f(A.x + radius + C.x, A.y + radius + C.y);
		glVertex2f(A.x + radius + D.x, A.y + radius + D.y);
	}

	for (int i = 0; 4 * i < GNK_NUM_SEGMENTS; ++i) {
		Gnk_Point C(radius * cos(theta), radius * sin(theta));
		theta = theta + delta;
		Gnk_Point D(radius * cos(theta), radius * sin(theta));
		glVertex2f(B.x - radius + C.x, A.y + radius + C.y);
		glVertex2f(B.x - radius + D.x, A.y + radius + D.y);
	}
	glVertex2f(B.x, B.y - radius);
	glEnd();
}

bool gnk_Load_Font(Gnk_Font &font, std::string fontPath, int fontSize) {
	if (FT_Init_FreeType(&gnk_FT)) {
		std::cout << "ERROR::Khong The Khoi Tao FREETYPE" << std::endl;
		return 0;
	}

	if (FT_New_Face(gnk_FT, fontPath.c_str(), 0, &gnk_Face)) {
		std::cout << "ERROR::FREETYPE: Khong The Tao Face" << std::endl;
		return 0;
	}

	FT_Set_Pixel_Sizes(gnk_Face, 0, fontSize);
	font.size = fontSize;

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Tranh loi segmentation faults

	for (unsigned char c = 0; c < 128; c++) {
		if (FT_Load_Char(gnk_Face, c, FT_LOAD_RENDER)) {
			std::cout << "ERROR::FREETYTPE: Khong the tai Glyph::" <<
				c << std::endl;
			continue;
		}

		unsigned int texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			gnk_Face->glyph->bitmap.width,
			gnk_Face->glyph->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			gnk_Face->glyph->bitmap.buffer
		);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// luu tru character
		Gnk_Glyph glyph = {
			texture,
			glm::ivec2(gnk_Face->glyph->bitmap.width, gnk_Face->glyph->bitmap.rows),
			glm::ivec2(gnk_Face->glyph->bitmap_left, gnk_Face->glyph->bitmap_top),
			gnk_Face->glyph->advance.x
		};
		font.add(c, glyph);
	}

	FT_Done_Face(gnk_Face);
	FT_Done_FreeType(gnk_FT);
	return 1;
}

void Gnk_Font_List::addFont(std::string fontName, std::string fontPath, int fontSize) {
	list[fontName] = Gnk_Font();
	gnk_Load_Font(list[fontName], fontPath, fontSize);
}

void gnk_Set_Character_Font(std::string font) {
	gnk_Current_Font = &gnk_Font_List[font];
}

void gnk_Text(std::string text, Gnk_Point P, float fontSize) {
	P = Gnk_Point((int)P.x, (int)P.y);
	glUniform1i(glGetUniformLocation(gnk_Shader.ID, "mode"), 1);
	float scale = fontSize / gnk_Current_Font->size;
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(gnk_TVA);

	std::string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++) {
		Gnk_Glyph ch = gnk_Current_Font->list[*c];

		float xpos = P.x + ch.bearing.x * scale;
		float ypos = P.y - (ch.size.y - ch.bearing.y) * scale;

		float w = ch.size.x * scale;
		float h = ch.size.y * scale;
		// cap nhat VBO
		float vertices[6][5] = {
			{ xpos,     ypos + h,	0.0f,   0.0f, 0.0f },
			{ xpos,     ypos,		0.0f,   0.0f, 1.0f },
			{ xpos + w, ypos,       0.0f,	1.0f, 1.0f },

			{ xpos,     ypos + h,   0.0f,	0.0f, 0.0f },
			{ xpos + w, ypos,       0.0f,	1.0f, 1.0f },
			{ xpos + w, ypos + h,   0.0f,	1.0f, 0.0f }
		};

		glBindTexture(GL_TEXTURE_2D, ch.textureID);
		glBindBuffer(GL_ARRAY_BUFFER, gnk_TVB);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glDrawArrays(GL_TRIANGLES, 0, 6);
		// chuyen con tro den vi tri tiep theo, con tro = anvance * 1/64
		P.x += (ch.advance >> 6) * scale; // 2^6 = 64
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(2);
	glDisable(GL_BLEND);
	glUniform1i(glGetUniformLocation(gnk_Shader.ID, "mode"), 0);
}

float gnk_Get_Text_Width(std::string text, float fontSize) {
	float scale = fontSize / gnk_Current_Font->size;
	float width = 0;
	for (std::string::const_iterator c = text.begin();
		c != text.end(); c++) {
		Gnk_Glyph ch = gnk_Current_Font->list[*c];
		width += (ch.advance >> 6) * scale;
	}
	return width;
}

void gnk_Text_Limited(std::string text, Gnk_Point P, float width, float height, float fontSize, text_align_value textAlign = GNK_TEXT_LEFT) {
	float scale = fontSize / gnk_Current_Font->size;
	float maxWidth = gnk_Get_Text_Width(text, fontSize);
	float maxHeight = gnk_Current_Font->getMaxHeight() * scale;

	float text_overflow = 0.0f;
	if (maxWidth > width) {
		text_overflow = maxWidth - width;
		maxWidth = width;
	}

	if (maxHeight > height)
		maxHeight = height;

	glEnable(GL_SCISSOR_TEST);
	glScissor(P.x, P.y + (gnk_Height - gnk_Frame_Position), width, height + (gnk_Height - gnk_Frame_Position));
	if (textAlign == GNK_TEXT_CENTER) {
		gnk_Text(text, P.translate(
				(width - maxWidth) / 2 - text_overflow,
				(height - maxHeight) / 2
			), fontSize
		);
	}
	else if (textAlign == GNK_TEXT_LEFT) {
		gnk_Text(text, P.translate(
				-text_overflow,
				(height - maxHeight) / 2
			), fontSize
		);
	}
	else if (textAlign == GNK_TEXT_RIGHT) {
		gnk_Text(text, P.translate(
				(width - maxWidth) - text_overflow,
				(height - maxHeight) / 2
			), fontSize
		);
	}
	glDisable(GL_SCISSOR_TEST);
}

void gnk_Load_Image(Gnk_Image &image, std::string imagePath) {
	glGenTextures(1, &image.textureID);

	stbi_set_flip_vertically_on_load(true);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, image.textureID);
	unsigned char* data = stbi_load(imagePath.c_str(), &image.width, 
		&image.height, &image.nrChannels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image.width, image.height, 0, image.get_Format(), GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "ERROR::TEXTURE::CAN'T LOAD IMAGE" << std::endl;
	}
	stbi_image_free(data);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Gnk_Image_List::addImage(std::string imageName, std::string imagePath) {
	list[imageName] = Gnk_Image();
	gnk_Load_Image(list[imageName], imagePath);
}

void gnk_Image(Gnk_Image &image, Gnk_Point A, Gnk_Point B) {
	float width = B.x - A.x;
	float height = B.y - A.y;
	float image_ratio_x = width / image.width;
	float image_ratio_y = height / image.height;
	image_ratio_x /= image_ratio_y;
	glUniform1i(glGetUniformLocation(gnk_Shader.ID, "mode"), 2);
	glUniform1i(glGetUniformLocation(gnk_Shader.ID, "nrChannels"), image.nrChannels);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(gnk_TVA);
	float vertices[6][5] = {
			{ A.x, A.y,	0.0f,	0.0f,			0.0f },
			{ B.x, B.y,	0.0f,	image_ratio_x,	1.0f },
			{ B.x, A.y, 0.0f,	image_ratio_x,	0.0f },

			{ A.x, A.y,	0.0f,	0.0f,			0.0f },
			{ B.x, B.y,	0.0f,	image_ratio_x,	1.0f },
			{ A.x, B.y, 0.0f,	0.0f,			1.0f },
	};
	glBindTexture(GL_TEXTURE_2D, image.textureID);
	glBindBuffer(GL_ARRAY_BUFFER, gnk_TVB);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(glGetUniformLocation(gnk_Shader.ID, "mode"), 0);
}

