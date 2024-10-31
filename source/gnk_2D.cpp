#include "header/gnk_2D.h"
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
	Gnk_Color newColor(r, g, b);
	return newColor;
}

Gnk_Color Gnk_Color::operator-(const Gnk_Color& other) {
	int r = (this->red - other.red) * GNK_NUM_COLORS;
	int g = (this->green - other.green) * GNK_NUM_COLORS;
	int b = (this->blue - other.blue) * GNK_NUM_COLORS;
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
Gnk_Button::Gnk_Button(Gnk_Point A, Gnk_Point B, Gnk_Color color, std::string text, 
	std::string tFont, float fontSize, Gnk_Color tColor, 
	float pX, float pY,	float radius, void (*logic)(), 
	void (*hover)(Gnk_Button &), text_align textAlign) {
	this->A = A;
	this->B = B;
	this->color = color;

	this->text = text;
	this->textFont = tFont;
	this->fontSize = fontSize;
	this->textColor = tColor;
	
	this->paddingX = pX;
	this->paddingY = pY;
	this->radius = radius;
	
	this->logic = logic;
	this->hover_effect = hover;
	this->textAlign = textAlign;
}

void Gnk_Button::process() {
	logic();
}

float Gnk_Button::getWidth() {
	return B.x - A.x;
}

float Gnk_Button::getHeight() {
	return B.y - A.y;
}

void Gnk_Button::hover() {
	if (hover_effect != NULL) hover_effect(*this);
}

// Textbox definition
Gnk_Textbox::Gnk_Textbox(Gnk_Point A, Gnk_Point B, Gnk_Color color, 
	std::string tFont, float fontSize, Gnk_Color tColor, 
	float pX, float pY, std::string placeholder, std::string plFont,
	float plFontSize, Gnk_Color plColor, text_align textAlign,
	void (*hover)(Gnk_Textbox&)) {
	this->A = A;
	this->B = B;
	this->color = color;

	this->textFont = tFont;
	this->fontSize = fontSize;
	this->textColor = tColor;

	this->paddingX = pX;
	this->paddingY = pY;

	this->placeholder = placeholder;
	this->plFont = plFont;
	this->plFontSize = plFontSize;
	this->plColor = plColor;

	this->textAlign = textAlign;
	this->select_effect = hover;
}

float Gnk_Textbox::getWidth() {
	return B.x - A.x;
}

float Gnk_Textbox::getHeight() {
	return B.y - A.y;
}
void Gnk_Textbox::select() {
	if (select_effect != NULL) select_effect(*this);
}

// Textbox Password Definition
Gnk_Textbox_password::Gnk_Textbox_password(Gnk_Point A, Gnk_Point B, Gnk_Color color, 
	std::string tFont, float fontSize, Gnk_Color tColor, 
	float pX, float pY, std::string placeholder, std::string plFont,
	float plFontSize, Gnk_Color plColor, text_align textAlign,
	void (*hover)(Gnk_Textbox&))
	:Gnk_Textbox(A, B, color, tFont, fontSize, tColor, pX, pY, placeholder, plFont, plFontSize, plColor, textAlign, hover) {

}

// Frame Definition
Gnk_Frame::Gnk_Frame() {
	this->Draw = NULL;
}

Gnk_Frame::~Gnk_Frame() {
	while(!buttonList.empty()) {
		Gnk_Button *p = buttonList.back();
		delete p;
		buttonList.pop_back();
	}

	while(!textboxList.empty()) {
		Gnk_Textbox *p = textboxList.back();
		delete p;
		textboxList.pop_back();
	}
}

Gnk_Frame::Gnk_Frame(void (*Draw)()) {
	this->Draw = Draw;
}

void Gnk_Frame::display() {
	if (Draw != NULL) this->Draw();
}

void Gnk_Frame::addButton(Gnk_Button *B) {
	buttonList.push_back(B);
}

void Gnk_Frame::addTextbox(Gnk_Textbox *T) {
	textboxList.push_back(T);
}

void Gnk_Frame::buttonDisplay() {
	for (auto &it:buttonList) {
		it->display();
	}
}

void Gnk_Frame::textboxDisplay() {
	for (auto &it:textboxList) {
		it->display();
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
double gnk_Backspace_Speed = 0.08;

double gnk_Event_Timeout = 0.5;
static void gnk_Cursor_Position_Callback(GLFWwindow* window, double xpos, double ypos) {
	ypos = gnk_Height - ypos;
	for (auto& it : gnk_Current_Frame->buttonList) {
		if (xpos > it->A.x && xpos < it->B.x &&
			ypos > it->A.y && ypos < it->B.y) {
			it->onHover = true;
		}
		else {
			it->onHover = false;
		}
	}
}

void gnk_Mouse_Button_Callback(GLFWwindow* window, int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		ypos = gnk_Height - ypos;
		for (auto &it:gnk_Current_Frame->textboxList) {
			if (xpos > it->A.x && xpos < it->B.x &&
				ypos > it->A.y && ypos < it->B.y) {
				it->active = true;
			}
			else {
				it->active = false;
			}
		}

		for (auto &it: gnk_Current_Frame->buttonList) {
			if (xpos > it->A.x && xpos < it->B.x && 
				ypos > it->A.y && ypos < it->B.y) {
				it->process();
				return;
			}
		}
	}
}

void gnk_Character_Callback(GLFWwindow* window, unsigned int codepoint) {
	for (auto& it : gnk_Current_Frame->textboxList) {
		if (it->active == true) {
			it->text += (char)codepoint;
		}
	}
}

void gnk_Key_Callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_BACKSPACE && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		double currentTime = glfwGetTime();
		if (currentTime - gnk_Backspace_Last_Time >= gnk_Backspace_Speed) {
			for (auto& it : gnk_Current_Frame->textboxList) {
				if (it->active == true) {
					if (!it->text.empty()) {
						it->text.pop_back();
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

void gnk_Set_Frame(Gnk_Frame &frame) {
	gnk_Current_Frame = &frame;
}

void gnk_Window_Loop() {
	while (!glfwWindowShouldClose(gnk_Window)) {
		glClear(GL_COLOR_BUFFER_BIT);
		glfwWaitEventsTimeout(gnk_Event_Timeout);
		gnk_Process_Input();
		if(gnk_Frame_Space != NULL) gnk_Frame_Space();
		gnk_Current_Frame->display();
		gnk_Current_Frame->buttonDisplay();
		gnk_Current_Frame->textboxDisplay();
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

void gnk_Text_Limited(std::string text, Gnk_Point P, float width, float height, float fontSize, text_align textAlign = GNK_TEXT_LEFT) {
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
	glScissor(P.x, P.y, width, height);
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

void Gnk_Button::display() {
	gnk_Set_Object_Color(color);
	gnk_Rounded_Rectangle(A, B, radius);
	gnk_Set_Object_Color(textColor);
	gnk_Set_Character_Font(textFont);
	gnk_Text_Limited(
		text, 
		A.translate(paddingX, paddingY), 
		getWidth() - 2 * paddingX, 
		getHeight() - 2 * paddingY, 
		fontSize, 
		textAlign
	);
	if (onHover) hover();
}

void Gnk_Textbox::display() {
	gnk_Set_Object_Color(color);
	gnk_Rectangle(A, B);
	std::string output;
	std::string outputFont;
	float outputFontSize;
	Gnk_Color outputColor;
	if (text == "") {
		if (!active) output = placeholder;
		else output = "";
		outputFont = plFont;
		outputFontSize = plFontSize;
		outputColor = plColor;
	}
	else {
		output = text;
		outputFont = textFont;
		outputFontSize = fontSize;
		outputColor = textColor;
	}

	gnk_Set_Character_Font(outputFont);
	float scale = outputFontSize / gnk_Current_Font->size;
	gnk_Set_Object_Color(outputColor);

	float maxWidth = gnk_Get_Text_Width(output, outputFontSize);
	float maxHeight = gnk_Current_Font->getMaxHeight() * scale;

	if (maxWidth > getWidth() - 2 * paddingX) {
		maxWidth = getWidth() - 2 * paddingX;
	}
		
	if (maxHeight > getHeight() - 2 * paddingY)
		maxHeight = getHeight() - 2 * paddingY;

	float cpX = 0, cpY = 0;
	if (textAlign == GNK_TEXT_CENTER) {
		gnk_Text_Limited(output, A.translate(paddingX, paddingY), getWidth() - 2 * paddingX, getHeight() - 2 * paddingY, fontSize, GNK_TEXT_CENTER);
		cpX = paddingX + (getWidth() - 2 * paddingX - maxWidth) / 2 + maxWidth;
		cpY = paddingY + (getHeight() - 2 * paddingY - maxHeight) / 2 + maxHeight;
	}
	else if (textAlign == GNK_TEXT_LEFT) {
		gnk_Text_Limited(output, A.translate(paddingX, paddingY), getWidth() - 2 * paddingX, getHeight() - 2 * paddingY, fontSize, GNK_TEXT_LEFT);
		cpX = paddingX + maxWidth;
		cpY = paddingY + (getHeight() - 2 * paddingY - maxHeight) / 2 + maxHeight;
	}
	else if (textAlign == GNK_TEXT_RIGHT) {
		gnk_Text_Limited(output, A.translate(paddingX, paddingY), getWidth() - 2 * paddingX, getHeight() - 2 * paddingY, fontSize, GNK_TEXT_RIGHT);
		cpX = paddingX + (getWidth() - 2 * paddingX - maxWidth) + maxWidth;
		cpY = paddingY + (getHeight() - 2 * paddingY - maxHeight) / 2 + maxHeight;
	}
	
	if (active) {
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
		select();
	}
}

void Gnk_Textbox_password::display() {
	std::string newText = this->text;
	for(int i = 0; i < this->text.size(); ++i) {
		this->text[i] = '*';
	}
	Gnk_Textbox::display();
	this->text = newText;
}
