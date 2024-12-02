#ifndef GNK_2D_H
#define GNK_2D_H
#include <iostream>
#include <unordered_map>
#include <vector>

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
enum text_align_value {
	GNK_TEXT_LEFT,
	GNK_TEXT_CENTER,
	GNK_TEXT_RIGHT,
};

const float GNK_PI = acos(-1.0f);		// PI = 3.14
const float GNK_NUM_SEGMENTS = 1024;	// num segments to draw circle
const int GNK_NUM_COLORS = 255;			
const int GNK_TEXT_MAX_LENGTH = 1024;		// max size of text
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
	GLint get_internalFormat();
};

class Gnk_Image_List {
	std::unordered_map<std::string, Gnk_Image> list;
public:
	void addImage(std::string, std::string);
	Gnk_Image& operator[](std::string);
};

// class Animation {
// public:
// 	float startTime;
// 	float currentTime;
// 	float duration;
// };
// Comming soon...

class Gnk_Button {
protected:
	void (*hover_process)(Gnk_Button*);
	void (*click_process)(Gnk_Button*);
public:
	bool appear = true;
	Gnk_Point A;
	Gnk_Point B;
	Gnk_Color color;
	float border_radius;
	bool onHover = false;
	bool onClick = false;
	bool border = false;
	Gnk_Color border_color;
	Gnk_Button();
	void setAppear(bool);
	void setRange(Gnk_Point, Gnk_Point);
	void setColor(Gnk_Color);
	void setRadius(float);
	void setHoverProcess(void (*)(Gnk_Button*));
	void setClickProcess(void (*)(Gnk_Button*));
	void setBorder(bool);
	void setBorderColor(Gnk_Color);
	virtual void draw();
	virtual void display();
	void hover_effect();
	void click_effect();
	virtual void process();
};

class Gnk_Button_With_Text: public Gnk_Button {
public:
	std::string text;
	std::string text_font;
	float font_size;
	Gnk_Color text_color;
	float paddingX, paddingY;
	text_align_value textAlign;
	Gnk_Button_With_Text();
	void setText(std::string);
	void setTextFont(std::string);
	void setFontSize(float);
	void setTextColor(Gnk_Color);
	void setPaddingX(float);
	void setPaddingY(float);
	void setTextAlign(text_align_value);
	virtual void draw();
	virtual void display();
};

class Gnk_Button_With_Image: public Gnk_Button {
public:
	Gnk_Image *image;
	Gnk_Button_With_Image();
	void setImage(Gnk_Image *);
	virtual void draw();
	virtual void display();
};

class Gnk_Button_Toggle: public Gnk_Button_With_Text {
public:
	Gnk_Point C;
	Gnk_Point D;
	Gnk_Color toggleColor;
	Gnk_Color toggleEnableColor;
	float toggleRadius;
	bool toggle = false;
	Gnk_Button_Toggle();
	Gnk_Button_Toggle(Gnk_Button_With_Text&);
	void setToggleRange(Gnk_Point, Gnk_Point);
	void setToggleColor(Gnk_Color);
	void setToggleEnableColor(Gnk_Color);
	void setToggleRadius(float);
	virtual void draw();
	virtual void display();
	virtual void process();
};

class Gnk_Textbox {
protected:
	void (*select_process)(Gnk_Textbox*);
public:
	bool appear = true;
	Gnk_Point A;
	Gnk_Point B;
	Gnk_Color color;
	float border_radius;
	std::string text;
	std::string text_font;
	float font_size;
	Gnk_Color text_color;
	std::string placeholder;
	std::string placeholder_font;
	float placeholder_font_size;
	Gnk_Color placeholder_color;
	float paddingX, paddingY;
	text_align_value text_align;
	bool on_select = false;
	bool border = false;
	Gnk_Color border_color;
	int maxLength = GNK_TEXT_MAX_LENGTH;
	Gnk_Textbox();
	Gnk_Textbox(Gnk_Textbox&);
	void setAppear(bool);
	void setRange(Gnk_Point, Gnk_Point);
	void setColor(Gnk_Color);
	void setBorderRadius(float);
	void setText(std::string);
	void setTextFont(std::string);
	void setFontSize(float);
	void setTextColor(Gnk_Color);
	void setPlaceholder(std::string);
	void setPlaceholderFont(std::string);
	void setPlaceholderFontSize(float);
	void setPlaceholderColor(Gnk_Color);
	void setPaddingX(float);
	void setPaddingY(float);
	void setTextAlign(text_align_value);
	void setSelectProcess(void (*)(Gnk_Textbox*));
	void setBorder(bool);
	void setBorderColor(Gnk_Color);
	void setMaxLength(int);
	float getWidth();
	float getHeight();
	virtual void draw();
	virtual void display();
	void select_effect();
	void process();
};

class Gnk_Textbox_Password: public Gnk_Textbox {
public:
	Gnk_Textbox_Password();
	Gnk_Textbox_Password(Gnk_Textbox&);
	Gnk_Textbox_Password(Gnk_Textbox_Password&);
	virtual void draw();
	virtual void display();
};

class Gnk_Textbox_Keep_Placeholder: public Gnk_Textbox {
public:
	Gnk_Textbox_Keep_Placeholder();
	Gnk_Textbox_Keep_Placeholder(Gnk_Textbox&);
	Gnk_Textbox_Keep_Placeholder(Gnk_Textbox_Keep_Placeholder&);
	virtual void draw();
	virtual void display();
};

class Gnk_Scrollbar {
public:
	bool appear = false;
	int maxHeight;
	int currentPos;
	Gnk_Point A;
	Gnk_Point B;
	Gnk_Point C;
	Gnk_Point D;
	Gnk_Color color;
	Gnk_Color scrollColor;
	Gnk_Color hoverColor;
	Gnk_Color clickColor;
	bool onHover = false;
	bool onClick = false;
	Gnk_Scrollbar();
	void setAppear(bool);
	void setRange(Gnk_Point, Gnk_Point);
	void setColor(Gnk_Color);
	void setScrollColor(Gnk_Color);
	void setHoverColor(Gnk_Color);
	void setClickColor(Gnk_Color);
	void setMaxHeight(int);
	void setCurrentPos(int);
	int getHeight();
	void display();
	void process();
};

class Gnk_List_Object {
	void (*draw_process)(Gnk_List_Object *);
public:
	int currentPos;
	bool appear = true;
	Gnk_Point A;
	Gnk_Point B;
	int group_height;

	int object_height;
	int object_width;
	Gnk_Point object_start_position;
	int object_space;

	bool border = false;
	Gnk_Color border_color;

	Gnk_List_Object();
	void setRange(Gnk_Point, Gnk_Point);
	void setCurrentPos(int);
	void setDrawProcess(void (*)(Gnk_List_Object *));
	void setGroupHeight(int);
	void setObjectHeight(int);
	void setObjectWidth(int);
	void setObjectStartPosition(Gnk_Point);
	void setObjectSpace(int);
	void setAppear(bool);
	void setBorder(bool);
	void setBorderColor(Gnk_Color);
	int getGroupHeight();
	int getGroupWidth();
	int toNextObject();
	void process();	
	void draw();
};

class Gnk_Frame {
	void (*process)(Gnk_Frame *);
public:
	std::unordered_map<std::string, Gnk_Button *> buttonList;
	std::unordered_map<std::string, Gnk_Textbox *> textboxList;
	std::unordered_map<std::string, Gnk_List_Object *> listObjectList;
	Gnk_Scrollbar *scrollbar = NULL;
	Gnk_Frame();
	~Gnk_Frame();
	Gnk_Frame(void (*process)(Gnk_Frame *));
	void addButton(std::string, Gnk_Button *);
	void addTextbox(std::string, Gnk_Textbox *);
	void addListObject(std::string, Gnk_List_Object *);
	void setScrollbar(Gnk_Scrollbar*);
	void display();
	void clear_Textbox();
};

// -Variable Declaration-----------------------------------------------------
extern float gnk_Width, gnk_Height;	// screen width & screen height
extern unsigned int gnk_TVA, gnk_TVB;			// text vertex array & text vertex buffer
extern GLFWwindow* gnk_Window;
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
extern int gnk_Scroll_Speed;
extern int gnk_Frame_Position;
extern bool gnk_Mouse_Ignore;
extern glm::mat4 gnk_Projection;
extern float gnk_Translate_X;
extern float gnk_Translate_Y;
// -Function Prototype-------------------------------------------------------
static void gnk_Cursor_Position_Callback(GLFWwindow*, double, double);
void gnk_Mouse_Button_Callback(GLFWwindow*, int, int, int);
void gnk_Key_Callback(GLFWwindow*, int, int, int, int);
void gnk_Character_Callback(GLFWwindow*, unsigned int);
void gnk_Scroll_Callback(GLFWwindow*, double, double);

bool gnk_GLFW_Init();
bool gnk_Create_Window(std::string);
bool gnk_GLEW_Init();
bool gnk_Shader_Init(std::string, std::string);
void gnk_Texture_Buffer_Init();
void gnk_Initialize(float, float, std::string, std::string, std::string);

void gnk_Set_Object_Color(Gnk_Color);
void gnk_Set_Background_Color(Gnk_Color);
void gnk_Set_Line_Width(float);

void gnk_Process_Input();

void gnk_Set_Frame_Space(void (*)());
void gnk_Set_Current_Frame(Gnk_Frame&);

void gnk_Window_Loop();

void gnk_Triangle(Gnk_Point, Gnk_Point, Gnk_Point, bool = true);
void gnk_Rectangle(Gnk_Point, Gnk_Point, bool = true);
void gnk_Circle(Gnk_Point, float, float, float, bool = true);
void gnk_Line(Gnk_Point, Gnk_Point);
void gnk_Rounded_Rectangle(Gnk_Point, Gnk_Point, float, bool = true);

bool gnk_Load_Font(Gnk_Font&, std::string, int);
void gnk_Set_Character_Font(std::string);

float gnk_Get_Text_Width(std::string, float);
void gnk_Text(std::string, Gnk_Point, float);
void gnk_Text_Limited(std::string, Gnk_Point, float, float, float, text_align_value);
int gnk_Text_Multi_Line(const std::string &, Gnk_Point, int, int, int, text_align_value = GNK_TEXT_LEFT);

void gnk_Load_Image(Gnk_Image&, std::string);
void gnk_Image(Gnk_Image&, Gnk_Point, Gnk_Point);
bool gnk_Point_In_Rectangle(Gnk_Point, Gnk_Point, Gnk_Point);
void gnk_Scissor_2_object(Gnk_Point, Gnk_Point, Gnk_Point, Gnk_Point);
#endif