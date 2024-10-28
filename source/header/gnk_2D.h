#ifndef GNK_2D_H
#define GNK_2D_H
#include <iostream>
#include <unordered_map>
#include <vector>
#include <iterator>
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H
#include "stb_image.h"
#include "shader.h"

// --Constant variable----------------------------------------------------------
enum text_align {
	GNK_TEXT_LEFT,
	GNK_TEXT_CENTER,
	GNK_TEXT_RIGHT,
};
const float GNK_PI = acos(-1.0f);		// PI = 3.14
const float GNK_NUM_SEGMENTS = 1024;	// num segments to draw circle
const int GNK_NUM_COLORS = 255;			
// --Class Declaration----------------------------------------------------------
class Gnk_Point {
public:
	float x, y;
	Gnk_Point(float = 0, float = 0);
	Gnk_Point(const Gnk_Point&);
	Gnk_Point translate(float, float);
};

class Gnk_Color {
public:
	float red, green, blue;
	Gnk_Color(int = 255, int = 255, int = 255);
	Gnk_Color(const Gnk_Color&);
	Gnk_Color& operator=(const Gnk_Color&);
	Gnk_Color operator+(const Gnk_Color&);
	Gnk_Color operator-(const Gnk_Color&);
};

class Gnk_Glyph {
public:
	unsigned int textureID;
	glm::ivec2   size;
	glm::ivec2   bearing;
	long int advance;
};

class Gnk_Font {
public:
	int size;
	float maxHeight = 0.0f;
	std::unordered_map<char, Gnk_Glyph> list;
	Gnk_Font();
	void add(char, Gnk_Glyph);
	void remove(char);
	float getMaxHeight();
};

class Gnk_Font_List {
	std::unordered_map<std::string, Gnk_Font> list;
public:
	void addFont(std::string, std::string, int);
	Gnk_Font& operator[](std::string);
};

class Gnk_Image {
public:
	unsigned int textureID;
	int width, height, nrChannels;
	Gnk_Image();
	GLenum get_Format();
};

class Gnk_Image_List {
	std::unordered_map<std::string, Gnk_Image> list;
public:
	void addImage(std::string, std::string);
	Gnk_Image& operator[](std::string);
};

class Gnk_Button {
	void (*logic)();
	void (*hover_effect)(Gnk_Button &);
public:
	Gnk_Point A;
	Gnk_Point B;
	Gnk_Color color;

	std::string text;
	std::string textFont;
	float fontSize;
	Gnk_Color textColor;

	float paddingX, paddingY;
	float radius;

	text_align textAlign;
	bool onHover = false;
	
	Gnk_Button(Gnk_Point, Gnk_Point, Gnk_Color, std::string, 
		std::string, float, Gnk_Color, 
		float, float, float, void (*logic)(), 
		void (*hover)(Gnk_Button &) = NULL, text_align = GNK_TEXT_CENTER);
	void display();
	void process();
	float getWidth();
	float getHeight();
	void hover();
};

class Gnk_Textbox {
	void (*select_effect)(Gnk_Textbox&);
public:
	std::string text;
	Gnk_Point A;
	Gnk_Point B;
	Gnk_Color color;

	std::string textFont;
	float fontSize;
	Gnk_Color textColor;

	std::string placeholder;
	std::string plFont;
	float plFontSize;
	Gnk_Color plColor;

	float paddingX, paddingY;
	text_align textAlign;
	bool active = false;
	bool onHover = false;
	Gnk_Textbox(Gnk_Point, Gnk_Point, Gnk_Color, 
		std::string, float, Gnk_Color, 
		float, float, std::string, std::string,
		float, Gnk_Color, text_align,
		void (*hover)(Gnk_Textbox&) = NULL);
	void display();
	float getWidth();
	float getHeight();
	void select();
};

class Gnk_Frame {
	void (*Draw)();
public:
	std::vector<Gnk_Button> buttonList;
	std::vector<Gnk_Textbox> textboxList;
	Gnk_Frame();
	Gnk_Frame(void (*Draw)());
	void display();
	void addButton(Gnk_Button);
	void addTextbox(Gnk_Textbox);
	void buttonDisplay();
	void textboxDisplay();
};

// -Variable Declaration-----------------------------------------------------
extern float gnk_Width, gnk_Height;	// screen width & screen height
extern unsigned int gnk_TVA, gnk_TVB;			// text vertex array & text vertex buffer

// window
extern GLFWwindow* gnk_Window;

// text render
extern FT_Library gnk_FT;
extern FT_Face gnk_Face;

extern Shader gnk_Shader;
extern Gnk_Frame gnk_Default_Frame;
extern Gnk_Frame* gnk_Current_Frame;
extern void (*gnk_Frame_Space)();

extern Gnk_Font gnk_Default_Font;
extern Gnk_Font* gnk_Current_Font;

extern Gnk_Font_List gnk_Font_List;
extern Gnk_Image_List gnk_Image_List;

extern double gnk_Text_Cursor_Last_Time;
extern bool gnk_Text_Cursor_Appear;
extern double gnk_Backspace_Last_Time;
extern double gnk_Backspace_Speed;

extern double gnk_Event_Timeout;

// -Function Prototype-------------------------------------------------------
static void gnk_Cursor_Position_Callback(GLFWwindow*, double, double);
void gnk_Mouse_Button_Callback(GLFWwindow*, int, int, int);
void gnk_Character_Callback(GLFWwindow*, unsigned int);
bool gnk_GLFW_Init();
bool gnk_Create_Window(std::string);
bool gnk_GLEW_Init();
bool gnk_Shader_Init(std::string, std::string);
void gnk_Texture_Buffer_Init();
void gnk_Initialize(float, float, std::string, std::string, std::string);
void gnk_Set_Object_Color(Gnk_Color);
void gnk_Set_Background_Color(Gnk_Color);
void gnk_Process_Input();
void gnk_Set_Frame_Space(void (*)());
void gnk_Set_Frame(Gnk_Frame&);
void gnk_Window_Loop();
void gnk_Triangle(Gnk_Point, Gnk_Point, Gnk_Point, bool = true);
void gnk_Rectangle(Gnk_Point, Gnk_Point, bool = true);
void gnk_Circle(Gnk_Point, float, float, float, bool = true);
void gnk_Set_Line_Width(float);
void gnk_Line(Gnk_Point, Gnk_Point);
void gnk_Rounded_Rectangle(Gnk_Point, Gnk_Point, float, bool = true);
bool gnk_Load_Font(Gnk_Font&, std::string, int);
void gnk_Set_Character_Font(std::string);
void gnk_Text(std::string, Gnk_Point, float);
float gnk_Get_Text_Width(std::string, float);
void gnk_Text_Limited(std::string, Gnk_Point, float, float, float, text_align);
void gnk_Load_Image(Gnk_Image&, std::string);
void gnk_Image(Gnk_Image&, Gnk_Point, Gnk_Point);
#endif