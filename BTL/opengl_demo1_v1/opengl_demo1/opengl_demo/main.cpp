#include <iostream>
#include <fstream>
#include <string>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <Vector_Matrix.h>


using namespace std;

typedef struct
{
	float XYZW[4];
	float RGBA[4];
} Vertex;

//    v6----- v5
//   /|      /|
//  v1------v0|
//  | |     | |
//  | |v7---|-|v4
//  |/      |/
//  v2------v3
Vertex Vertices[] =
{
	// v0-v1-v2 (front)
	{ { 0.5f,	 0.5f,	0.5f,	1.0f },{ 1.0f,	0.0f,	0.0f,	1.0f } },
	{ { -0.5f,	 0.5f,	0.5f,	1.0f },{ 1.0f,	0.0f,	0.0f,	1.0f } },
	{ { -0.5f,	-0.5f,	0.5f,	1.0f },{ 1.0f,	0.0f,	0.0f,	1.0f } },
	// v2-v3-v0
	{ { -0.5f,	-0.5f,	0.5f,	1.0f },{ 1.0f,	0.0f,	0.0f,	1.0f } },
	{ { 0.5f,	-0.5f,	0.5f,	1.0f },{ 1.0f,	0.0f,	0.0f,	1.0f } },
	{ { 0.5f,	 0.5f,	0.5f,	1.0f },{ 1.0f,	0.0f,	0.0f,	1.0f } },

	// v0-v3-v4 (right)
	{ { 0.5f,	 0.5f,	 0.5f,	1.0f },{ 0.0f,	1.0f,	0.0f,	1.0f } },
	{ { 0.5f,	-0.5f,   0.5f,1.0f },{ 0.0f,	1.0f,	0.0f,	1.0f } },
	{ { 0.5f,	-0.5f,  -0.5f,1.0f },{ 0.0f,	1.0f,	0.0f,	1.0f } },
	// v4-v5-v0
	{ { 0.5f,	-0.5f,	-0.5f,	1.0f },{ 0.0f,	1.0f,	0.0f,	1.0f } },
	{ { 0.5f,	 0.5f,	-0.5f,	1.0f },{ 0.0f,	1.0f,	0.0f,	1.0f } },
	{ { 0.5f,	 0.5f,   0.5f,1.0f },{ 0.0f,	1.0f,	0.0f,	1.0f } },

	// v0-v5-v6 (top)
	{ { 0.5f,	 0.5f,	 0.5f,	1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f } },
	{ { 0.5f,	0.5f,	-0.5f,	1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f } },
	{ { -0.5f,	0.5f,	 -0.5f,1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f } },
	// v6-v1-v0
	{ { -0.5f,	 0.5f,	 -0.5f,1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f } },
	{ { -0.5f,	0.5f,	0.5f,	1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f } },
	{ { 0.5f,	0.5f,	 0.5f,	1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f } },

	// v1-v6-v7 (left)
	{ { -0.5f,	 0.5f,	 0.5f,	1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f } },
	{ { -0.5f,	0.5f,	-0.5f,	1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f } },
	{ { -0.5f,	-0.5f,	 -0.5f,1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f } },
	// v7-v2-v1
	{ { -0.5f,	-0.5f,	 -0.5f,1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f } },
	{ { -0.5f,	-0.5f,	0.5f,	1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f } },
	{ { -0.5f,	0.5f,	 0.5f,	1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f } },

	// v7-v4-v3 (bottom)
	{ { -0.5f,	-0.5f,	-0.5f,	1.0f },{ 0.1f,	0.2f,	0.3f,	1.0f } },
	{ { 0.5f,	-0.5f,	-0.5f,	1.0f },{ 0.1f,	0.2f,	0.3f,	1.0f } },
	{ { 0.5f,	-0.5f,	 0.5f,	1.0f },{ 0.1f,	0.2f,	0.3f,	1.0f } },
	// v3-v2-v7
	{ { 0.5f,	-0.5f,	0.5f,	1.0f },{ 0.1f,	0.2f,	0.3f,	1.0f } },
	{ { -0.5f,	-0.5f,	0.5f,	1.0f },{ 0.1f,	0.2f,	0.3f,	1.0f } },
	{ { -0.5f,	-0.5f,	-0.5f,	1.0f },{ 0.1f,	0.2f,	0.3f,	1.0f } },

	// v4-v7-v6 (back)
	{ { 0.5f,	-0.5f,	-0.5f,	1.0f },{ 0.4f,	0.5f,	0.6f,	1.0f } },
	{ { -0.5f,	-0.5f,	-0.5f,	1.0f },{ 0.4f,	0.5f,	0.6f,	1.0f } },
	{ { -0.5f,	0.5f,	-0.5f,	1.0f },{ 0.4f,	0.5f,	0.6f,	1.0f } },
	// v6-v5-v4
	{ { -0.5f,	 0.5f,	 -0.5f,1.0f },{ 0.4f,	0.5f,	0.6f,	1.0f } },
	{ { 0.5f,	0.5f,	 -0.5f,1.0f },{ 0.4f,	0.5f,	0.6f,	1.0f } },
	{ { 0.5f,	-0.5f,	 -0.5f,1.0f },{ 0.4f,	0.5f,	0.6f,	1.0f } }
};

const size_t BufferSize = sizeof(Vertices);
const size_t VertexSize = sizeof(Vertices[0]);
const size_t RgbOffset = sizeof(Vertices[0].XYZW);

int CurrentWidth = 700,
CurrentHeight = 700;

GLuint
VaoId,
VboId,
VertexShaderId,
FragmentShaderId,
ProgramId;

mat4  model_fan, model_lamp;
int model_mat_location,
projection_mat_location;
bool battat = false;
GLfloat height = 0, xoay = 0, gap = 0, dich_nk = 0;

float
r[] = { 0.0f, 0.0f, 0.0f },
s[] = { 1.0f, 1.0f, 1.0f },
t[] = { 0.0f, 0.0f, 0.0f };


bool
translated = false,
rotated = false,
scaled = false;

GLfloat rotateAll = 0;
void block(mat4 mtg, mat4 mt) {
	//vi tri mat nhin
	vec3 eye(0.0, 0.3, 2.0);
	//nhin vao vi tri goc toa do (0,0,0)
	vec3 at(0.0, 0.0, 0.0);
	// huong mat nhin theo chieu duong truc y
	vec3 up(0.0, 1.0, 0.0);

	//goi ham lookat va truyen vao cac tham so eye,at,up
	mat4 m = lookat(eye, at, up);
	mat4 model_base = m * mtg * mt;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);

	//thiet lap chieu phoi canh
	float l = -0.5, r = 0.5, b = -0.5, t = 0.5, znear = 0.5, zfar = 20.0;
	mat4 p = frustum(l, r, b, t, znear, zfar);
	glUniformMatrix4fv(projection_mat_location, 1, GL_FALSE, p.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
// ---------------------------------------------------------------------------	
void block(mat4 mt, bool demo) {
	//vi tri mat nhin
	vec3 eye(0.0, 0.3, 2.0);
	//nhin vao vi tri goc toa do (0,0,0)
	vec3 at(0.0, 0.0, 0.0);
	// huong mat nhin theo chieu duong truc y
	vec3 up(0.0, 1.0, 0.0);

	//goi ham lookat va truyen vao cac tham so eye,at,up
	mat4 m = lookat(eye, at, up);
	mat4 model_base = m * model_lamp * mt;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);

	//thiet lap chieu phoi canh
	float l = -0.5, r = 0.5, b = -0.5, t = 0.5, znear = 0.5, zfar = 20.0;
	mat4 p = frustum(l, r, b, t, znear, zfar);
	glUniformMatrix4fv(projection_mat_location, 1, GL_FALSE, p.m);
	glDrawArrays(GL_TRIANGLES, 0, 10);
}
string ReadShaderSourceFile(string fileName) {
	fstream reader(fileName.c_str());
	string line;
	string code = "";
	while (getline(reader, line)) {
		code += line + "\n";
	}
	reader.close();
	return code;
}
// ---------------------------------------------------------------------------	
void CreatVaoVbo()
{
	glGenVertexArrays(1, &VaoId);
	glBindVertexArray(VaoId);

	glGenBuffers(1, &VboId);
	glBindBuffer(GL_ARRAY_BUFFER, VboId);
	glBufferData(GL_ARRAY_BUFFER, BufferSize, Vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, VertexSize, 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, VertexSize, (GLvoid*)RgbOffset);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
}
// ---------------------------------------------------------------------------	
void CreatShaders()
{
	string vertexSrc = ReadShaderSourceFile("./vs.shader");
	string fragmentSrc = ReadShaderSourceFile("./fs.shader");

	const GLchar* VertexShader = vertexSrc.c_str();
	const GLchar* FragmentShader = fragmentSrc.c_str();

	VertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(VertexShaderId, 1, &VertexShader, NULL);
	glCompileShader(VertexShaderId);

	FragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(FragmentShaderId, 1, &FragmentShader, NULL);
	glCompileShader(FragmentShaderId);

	ProgramId = glCreateProgram();
	glAttachShader(ProgramId, VertexShaderId);
	glAttachShader(ProgramId, FragmentShaderId);
	glLinkProgram(ProgramId);
	glUseProgram(ProgramId);
}
// ---------------------------------------------------------------------------	
void CloseFunc()
{
	glUseProgram(0);

	glDetachShader(ProgramId, VertexShaderId);
	glDetachShader(ProgramId, FragmentShaderId);

	glDeleteShader(FragmentShaderId);
	glDeleteShader(VertexShaderId);

	glDeleteProgram(ProgramId);

	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &VboId);

	glBindVertexArray(0);
	glDeleteVertexArrays(1, &VaoId);
}
// ------------------------------------------

mat4 model_room;
void room() {

	mat4 san = identity_mat4() * translate(vec3(0, -0.5, 0)) * rotate_z(180) * scale(vec3(2.5, 0.01, 1.6));
	block(model_room, san);
	mat4 tran = translate(vec3(0, 1, 0)) * scale(vec3(2.5, 0.01, 1.6));
	block(model_room, tran);
	mat4 lung = translate(vec3(0, 0.25, -0.8)) * rotate_y(180) * scale(vec3(2.5, 1.5, 0.01));
	block(model_room, lung);
	mat4 trai = translate(vec3(1.25, 0.25, 0)) * scale(vec3(0.01, 1.5, 1.6));
	block(model_room, trai);
	mat4 phai = translate(vec3(-1.25, 0.25, 0)) * rotate_y(180) * scale(vec3(0.01, 1.5, 1.6));
	block(model_room, phai);
}

//--------------------------------------------------------------------------
//ve ban
mat4 model_table;
void table() {
	mat4 foot = scale(vec3(0.01, 0.35, 0.3));
	block(model_table, translate(vec3(-0.2, -0.325, -0.4)) * foot);
	block(model_table, translate(vec3(-0.8, -0.325, -0.4)) * rotate_z(180) * foot);
	mat4 matban = scale(vec3(0.6, 0.01, 0.3));
	block(model_table, translate(vec3(-0.5, -0.15, -0.4)) * rotate_z(180) * matban);
}

//---------------------------------------------------------------------------
//ve ngan keo
mat4 model_drawer;
void drawer() {
	mat4 day_ngankeo = scale(vec3(0.3, 0.01, 0.3));
	block(model_drawer, translate(vec3(-0.65, -0.23, -0.4)) * rotate_z(180) * day_ngankeo);
	mat4 canhtrai_ngankeo = scale(vec3(0.001, 0.08, 0.3));
	block(model_drawer, translate(vec3(-0.5, -0.195, -0.4)) * rotate_z(180) * canhtrai_ngankeo);
	mat4 ngankeo = scale(vec3(0.001, 0.08, 0.3));
	block(model_drawer, translate(vec3(-0.65, -0.19, -0.25)) * rotate_y(270) * ngankeo);
	mat4 hand_keo = scale(vec3(0.01, 0.02, 0.07));
	block(model_drawer, translate(vec3(-0.65, -0.19, -0.215)) * rotate_y(90) * hand_keo);
	mat4 canhphai_ngankeo = scale(vec3(0.001, 0.08, 0.3));
	block(model_drawer, translate(vec3(-0.8, -0.195, -0.4)) * rotate_z(180) * canhphai_ngankeo);
}
//-----------------------------------------------------------
GLfloat xoay2 = 0, rota = 0, quaydeuquaydeu = 0;
mat4 head_fan;

//ve phan chan
void base_fan() {
	mat4 instance = identity_mat4();
	instance = translate(vec3(0.0, -1.49, 0.0)) * scale(vec3(0.3, 0.02, 0.3));
	block(model_fan, instance);
}
//ve than duoi quat
void body_down_fan() {
	mat4 instance = identity_mat4();
	instance = translate(vec3(0.0, -1.3, 0.0)) * scale(vec3(0.1, 0.3, 0.1));
	block(model_fan, instance);
}
//ve than tren quat
void body_up_fan() {
	mat4 instance = identity_mat4();
	head_fan = head_fan * translate(vec3(0.0, -1.15, 0.0));
	instance = scale(vec3(0.04, 0.3, 0.04));
	block(model_fan, head_fan * instance);
}
//ve phan dau quat
void head_fann() {
	mat4 instance = identity_mat4();
	head_fan = head_fan * translate(vec3(0.0, 0.175, 0.0));
	instance = scale(vec3(0.1, 0.1, 0.2));
	block(model_fan, head_fan * instance);
}
//ve nut keo quat
void point_push() {
	mat4 instance = identity_mat4();
	head_fan = head_fan * translate(vec3(0.0, 0.08 - rota, 0.0));
	instance = scale(vec3(0.02, 0.05, 0.02));
	block(model_fan, head_fan * instance);
}
//ve diem quay
void rotation_point() {
	mat4 instance = identity_mat4();
	head_fan = head_fan * translate(vec3(0.0, -0.39 + rota, 0.15));
	instance = scale(vec3(0.08, 0.05, 0.05)) * rotate_x(180);
	block(model_fan, head_fan * instance);
}
//ve canh quat
void propeller(GLfloat x, GLfloat y, GLfloat z) {
	mat4 instance = identity_mat4();
	instance = rotate_z(xoay2) * scale(vec3(x, y, z));
	block(model_fan, head_fan * instance);
}
//ve cac canh quat
void propellers() {
	//mat4 hecanh = identity_mat4();
	propeller(0.1, 0.5, 0.01);
	propeller(0.5, 0.1, 0.01);
	//block(hecanh);
}


//ve quat
void fan() {
	
	model_fan = model_fan * translate(vec3(0.0, 0.25, -0.4)) * scale(vec3(0.5, 0.5, 0.5)) * rotate_y(xoay - 45);
	base_fan();
	body_down_fan();
	head_fan = identity_mat4() * rotate_y(quaydeuquaydeu) * translate(vec3(0.0, height, 0.0));
	body_up_fan();
	head_fann();
	point_push();
	head_fan = head_fan * translate(vec3(0.0, 0.3, 0.0));
	rotation_point();
	propellers();
}
// ---------------------------------------------------------------------------	
//ve den hoc
mat4 head_lamp;
//ve phan chan
void lamp_base()
{
	mat4 instance = identity_mat4();
	instance = scale(vec3(0.15, 0.02, 0.15));
	block(model_lamp, instance);
}
//phan than duoi
void lamp_body_down() {
	mat4 instance = identity_mat4();
	instance = translate(vec3(0.0, 0.1, 0.0)) * scale(vec3(0.05, 0.2, 0.05));
	block(model_lamp, instance);
}
//phan than tren
void lamp_body_up() {
	mat4 instance = identity_mat4();
	instance = translate(vec3(0, 0.05, 0)) * scale(vec3(0.02, 0.1, 0.02));
	block(model_lamp, head_lamp * instance);
}
//phan noi
void lamp_connection() {
	mat4 instance = identity_mat4();
	head_lamp = head_lamp * translate(vec3(0.0, 0.11, 0.0));
	instance = scale(vec3(0.025, 0.02, 0.04));
	block(model_lamp, head_lamp * instance);
}
//phan dau den
void lamp_head() {
	mat4 instance = identity_mat4();
	head_lamp = head_lamp * translate(vec3(0.0, 0.0, -0.055));
	instance = scale(vec3(0.07, 0.07, 0.07));
	block(model_lamp, head_lamp * instance);
}

void anhsang(int i)
{
	mat4 instance = identity_mat4();
	instance = rotate_y(i) * rotate_x(45) * scale(vec3(0.1, 0.1, 0.125));
	block(head_lamp * instance, battat);
}
GLfloat ganxa = 0;
void vetnangcuoitroi()
{
	mat4 instance = identity_mat4();
	ganxa = (40 - gap) / 40;
	instance = translate(vec3(0, (gap <= -30) ? 0 : -0.5,
		(gap <= -30) ? (-1.75 + ganxa / 1.35) : (-2.5 + ganxa / 1.45))) *
		scale(vec3(0.15, 0.0025, 0.15 + (2 - ganxa) / ((ganxa <= -30) ? 5 : 2)));
	block(model_lamp, instance);
}

void lamp()
{
	lamp_base();
	lamp_body_down();
	head_lamp = identity_mat4() * translate(vec3(0.0, 0.2, 0.0)) * rotate_x(gap);
	lamp_body_up();
	lamp_connection();
	lamp_head();
	if (battat)
	{
		head_lamp = head_lamp * translate(vec3(0, 0, -0.125)) * rotate_x(270);
		for (int i = 0; i < 360; i++)
			anhsang(i);
		vetnangcuoitroi();
	}
}
bool xoaycanh = false, xoaythan = false, xoayxuoi = false;
GLfloat gocxoay[4] = { 0, 0.25, 0.5, 0.75 };
int so = 0;
GLfloat tmp = 0;


mat4 model_ghe;
float dich_ghe_x = 0, dich_ghe_y = 0, dich_ghe_z = 0;
void ghe() {
	//than ghe
	mat4 than_ghe = scale(vec3(0.2, 0.2, 0.01));
	block(model_ghe, translate(vec3(-0.35, -0.20, -0.0)) * than_ghe);

	//mat ghe
	mat4 day_ghe = scale(vec3(0.2, 0.01, 0.2));
	block(model_ghe, translate(vec3(-0.35, -0.30, -0.1)) * day_ghe);

	//chan ghe (trai ngoai)
	mat4 chan_ghe = scale(vec3(0.02, 0.18, 0.02));
	block(model_ghe, translate(vec3(-0.275, -0.40, -0.02)) * rotate_y(270) * chan_ghe);

	//chan ghe (phai ngoai)
	block(model_ghe, translate(vec3(-0.425, -0.40, -0.02)) * rotate_y(270) * chan_ghe);

	//chan ghe (trai trong)
	block(model_ghe, translate(vec3(-0.275, -0.40, -0.2)) * rotate_y(270) * chan_ghe);

	//chan ghe (trai trong)
	block(model_ghe, translate(vec3(-0.425, -0.40, -0.2)) * rotate_y(270) * chan_ghe);
}
// ve giuong
mat4 model_giuong;
float giuong_x = 0, giuong_z = 0;
void giuong() {
	mat4 mat_giuong = scale(vec3(0.6, 0.2, 1.0));
	block(model_giuong, translate(vec3(0.95, -0.4, -0.3)) * rotate_z(180) * mat_giuong);
	mat4 goi = scale(vec3(0.15, 0.03, 0.1));
	block(model_giuong, translate(vec3(1.0, -0.29, -0.75)) * goi);
}
//ve laptop
mat4 model_laptop;
float a = 0, dich_ban_x = 0, dich_ban_z = 0;
void laptop() {
	mat4 than_lap = scale(vec3(0.18, 0.006, 0.12));
	block(model_laptop, translate(vec3(-0.3, -0.13, -0.35)) * rotate_y(180) * than_lap);
	mat4 man_hinh = scale(vec3(0.18, 0.006, 0.12));
	block(model_laptop, translate(vec3(-0.3, -0.12, -0.42)) * rotate_y(180) * rotate_x(a) * man_hinh * translate(vec3(0.0, -0.0, -0.28)));
}
//ve tu
mat4 model_tu;
//ve than tu
void body_cabinet() {
	mat4 canhben = scale(vec3(0.02, 0.65, 0.2));
	block(model_tu, translate(vec3(-1.2, -0.18, -0.4)) * canhben);
	block(model_tu, translate(vec3(-0.9, -0.18, -0.4)) * canhben);
	mat4 day = scale(vec3(0.32, 0.02, 0.2));
	block(model_tu, translate(vec3(-1.05, 0.15, -0.4)) * day);
	block(model_tu, translate(vec3(-1.05, -0.36, -0.4)) * day);
	block(model_tu, translate(vec3(-1.05, -0.5, -0.4)) * day);
	mat4 canhsau = scale(vec3(0.32, 0.66, 0.02));
	block(model_tu, translate(vec3(-1.05, -0.17, -0.5)) * canhsau);
}
//ve cua trai tu
mat4 combo_tu;
void leftwing_cabinet() {
	mat4 cuatrai = identity_mat4();
	cuatrai = scale(vec3(0.16, 0.66, 0.01));
	block(model_tu, translate(vec3(-0.97, -0.17, -0.3)) *combo_tu * cuatrai);
	/*mat4 taycam_trai = translate(vec3(-1.0, -0.17, -0.3)) * rotate_y(180) * scale(vec3(0.02, 0.04, 0.02));
	block(model_tu,taycam_trai);*/
}
//-----
//ve cua phai tu
mat4 combo_tu2;
void rightwing_cabinet() {
	mat4 cuaphai = identity_mat4();
	cuaphai = scale(vec3(0.16, 0.66, 0.01));
	block(model_tu, translate(vec3(-1.13, -0.17, -0.3)) * combo_tu2 * cuaphai);
	/*mat4 taycam_trai = translate(vec3(-1.0, -0.17, -0.3)) * rotate_y(180) * scale(vec3(0.02, 0.04, 0.02));
	block(model_tu,taycam_trai);*/
}
//-----
GLfloat quaycanhtu[] = { 0,0 };
GLfloat quaycanhtu1[] = { 0,0 };
GLfloat dichtu_z, quaytu_y;
void tu() {
	model_tu =model_tu* translate(vec3(0.0, 0.0, dichtu_z)) * rotate_y(quaytu_y);
	body_cabinet();
	combo_tu = identity_mat4()* translate(vec3(0.0485, 0.0, 0.0)) * rotate_y(quaycanhtu[0]) * translate(vec3(-0.055, 0.0, 0.0));
	leftwing_cabinet();
	combo_tu2 = identity_mat4() * translate(vec3(-0.0485, 0.0, 0.0)) * rotate_y(quaycanhtu1[0]) * translate(vec3(0.055, 0.0, 0.0));
	rightwing_cabinet();
}
//ve den phong
mat4 model_room_light;
GLfloat turn = 0;
void roomlight() {
	mat4 light = translate(vec3(0.0, 0.8, -0.4)) * rotate_x(turn) * scale(vec3(1, 0.05, 0.05));
	block(model_room_light, light);
}
GLfloat year = 0, day = 0;
void DisplayFunc(void)
{

	model_mat_location = glGetUniformLocation(ProgramId, "model_mat_shader");
	projection_mat_location = glGetUniformLocation(ProgramId, "projection_mat_shader");
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	model_lamp = translate(vec3(dich_ban_x, 0.0, dich_ban_z))* rotate_y(rotateAll - 100) * scale(vec3(s[0] / 2, s[1] / 2, s[2] / 2)) * translate(vec3(-0.5, -0.275, 1.5));
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_lamp.m);
	model_room = rotate_y(rotateAll) * scale(vec3(s[0], s[1], s[2]));
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_room.m);
	model_table = rotate_y(rotateAll) * scale(vec3(s[0], s[1], s[2])) * translate(vec3(dich_ban_x, 0.0, dich_ban_z));
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_table.m);
	model_fan = rotate_y(rotateAll) * scale(vec3(s[0], s[1], s[2]));
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_fan.m);
	model_drawer = rotate_y(rotateAll) * scale(vec3(s[0], s[1], s[2])) * translate(vec3(dich_ban_x, 0.0, dich_ban_z)) * translate(vec3(0.0, 0.0, dich_nk));
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_drawer.m);

	//duong
	model_ghe = rotate_y(rotateAll) * scale(vec3(s[0], s[1], s[2])) * translate(vec3(dich_ghe_x, 0.0, dich_ghe_z));
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_ghe.m);
	model_giuong = rotate_y(rotateAll) * scale(vec3(s[0], s[1], s[2])) * translate(vec3(giuong_x, 0.0, giuong_z));
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_giuong.m);
	model_laptop = rotate_y(rotateAll) * scale(vec3(s[0], s[1], s[2])) * translate(vec3(dich_ban_x, 0.0, dich_ban_z));
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_laptop.m);
	model_tu = rotate_y(rotateAll) * scale(vec3(s[0], s[1], s[2]));
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_tu.m);
	model_room_light = rotate_y(rotateAll) * scale(vec3(s[0], s[1], s[2]));
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_room_light.m);

	room();
	table();
	model_drawer = model_drawer;
	drawer();
	fan();
	model_lamp = model_lamp;
	lamp();
	ghe();
	laptop();
	giuong();
	tu();
	roomlight();
	glutSwapBuffers();
}
// ---------------------------------------------------------------------------	
void ReshapeFunc(int Width, int Height)
{
	CurrentWidth = Width;
	CurrentHeight = Height;
}
// ---------------------------------------------------------------------------	
void IdleFunc(void)
{
	if (xoaycanh)
	{
		(xoay2 > 360) ? xoay2 -= (360 - tmp) : xoay2 += tmp;
		tmp = (tmp < gocxoay[so]) ? tmp + 0.0001 : tmp;
	}
	else
	{
		(xoay2 > 360) ? xoay2 -= (360 - tmp) : xoay2 += tmp;
		tmp = (tmp > gocxoay[so]) ? tmp - 0.0001 : tmp;
	}
	if (xoaythan)
	{
		if (xoayxuoi)
		{
			quaydeuquaydeu += 0.05;
			if (quaydeuquaydeu >= 75)
				xoayxuoi = false;
		}
		else
		{
			quaydeuquaydeu -= 0.05;
			if (quaydeuquaydeu <= -75)
				xoayxuoi = true;
		}
	}
	glutPostRedisplay();
}
// ---------------------------------------------------------------------------
void KeyboardFunc(unsigned char key, int x, int y)
{
	switch (key) {
	case 'd':
		day = (day + 10) / 360;
		break;
	case 'D':
		day = (day - 10) / 360;
		break;
	case 'v':
		year = (year + 5) / 360;
		break;
	case 'V':
		year = (year - 5) / 360;
		break;
		//quay canh quat
	case '0': case '1': case '2': case '3':
		xoaycanh = (key - '0' > so);
		so = key - '0';
		break;
		//quay dau quat, an tut nang
	case 'j':
		xoaythan = true - xoaythan;
		rota = 0.015 - rota;
		break;
		//quay ca quat
	case 'y':
		xoay += 5;
		break;
	case 'Y':
		xoay -= 5;
		break;
		// tang chieu cao quat
	case 'u':
		height += 0.05;
		if (height >= 0.15)
			height = 0.15;
		break;
		// giam chieu cao quat
	case 'U':
		height -= 0.05;
		if (height <= -0.1)
			height = -0.1;
		break;
		//keo ngan keo ra
	case 'n':
		dich_nk += 0.05;
		if (dich_nk >= 0.25)
			dich_nk = 0.25;
		break;
		//day ngan keo vao
	case 'N':
		dich_nk -= 0.05;
		if (dich_nk < 0.05)
			dich_nk = 0.00;
		break;
		//mo den ban
	case 'g':
		gap += 5;
		if (gap >= 0) gap = 0;
		break;
		//gap den ban
	case 'G':
		gap -= 5;
		if (gap <= -40) gap = -40;
		break;
		// bat tat den ban
	case ' ':
		battat = true - battat;
		break;
	case 27:
		exit(EXIT_SUCCESS);
		break;
	case '=':
	case '+':
		s[0] *= 1.05f;
		s[1] *= 1.05f;
		s[2] *= 1.05f;
		scaled = true;
		break;

	case '-':
	case '_':
		s[0] /= 1.05f;
		s[1] /= 1.05f;
		s[2] /= 1.05f;
		scaled = true;
		break;
		//mo may tinh
	case 'x':
		a += 5;
		if (a >= 135)
			a = 135;
		break;
	case 'X':
		a -= 5;
		if (a <= 0)
			a = 0;
		break;
		//dich ghe sang trai,phai
	case 'i':
		dich_ghe_x += 0.05;
		if (dich_ghe_x >= 0.85)
			dich_ghe_x = 0.85;
		break;
	case 'I':
		dich_ghe_x -= 0.05;
		if (dich_ghe_x <= -0.45)
			dich_ghe_x = -0.45;
		break;
		//dich ghe vao trong, ra ngoai
	case 'p':
		dich_ghe_z += 0.05;
		if (dich_ghe_z >= 0.25)
			dich_ghe_z = 0.25;
		break;
	case 'P':
		dich_ghe_z -= 0.05;
		if (dich_ghe_z <= -0.25)
			dich_ghe_z = -0.25;
		break;
		//dich ban sang trai,phai
	case 'k':
		dich_ban_x += 0.05;
		if (dich_ban_x >= 0.1)
			dich_ban_x = 0.1;
		break;
	case 'K':
		dich_ban_x -= 0.05;
		if (dich_ban_x <= -0.05)
			dich_ban_x = -0.05;
		break;
		// bat tat den phong
	case 'h':
		turn = 90 - turn;
		break;
		//Mở trái tủ
	case 'm':
		quaycanhtu[0] += 5;
		if (quaycanhtu[0] + 5 >= 180) quaycanhtu[0] = 180;
		break;
		//Đóng trái tủ
	case 'M':
		quaycanhtu[0] -= 5;
		if (quaycanhtu[0] - 5 <= 0)quaycanhtu[0] = 0;
		break;
		//mo phai tu
	case 'e':
		quaycanhtu1[0] -= 5;
		if (quaycanhtu1[0] - 5 <= -180) quaycanhtu1[0] = -180;
		break;
		//Đóng phai tủ
	case 'E':
		quaycanhtu1[0] += 5;
		if (quaycanhtu1[0] + 5 >= 0)quaycanhtu1[0] = 0;
		break;
	}
}
// ------------------------------------------
void MouseFunc(int button, int state, int x, int y)
{

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		rotateAll += 5.0;
		if (rotateAll > 360.0) { rotateAll -= 360.0; }
	}

	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		rotateAll -= 5.0;
		if (rotateAll < 0.0) { rotateAll += 360.0; }
	}

	glutPostRedisplay();
}

// ---------------------------------------------------------------------------
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitContextVersion(4, 0);
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	glutInitWindowSize(CurrentWidth, CurrentHeight);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutCreateWindow("Phong tro");

	glewExperimental = GL_TRUE;
	glewInit();

	CreatVaoVbo();
	CreatShaders();

	glutDisplayFunc(DisplayFunc);
	glutReshapeFunc(ReshapeFunc);
	glutIdleFunc(IdleFunc);
	glutKeyboardFunc(KeyboardFunc);
	glutMouseFunc(MouseFunc);
	glutCloseFunc(CloseFunc);

	glutMainLoop();
	return 0;
}
