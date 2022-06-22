// thư viện tải hình ảnh
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"	// Sean Barrett's image loader - http://nothings.org/

#include <iostream>
#include <fstream>
#include <string>
#include <assert.h>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <Vector_Matrix.h>


using namespace std;

typedef struct
{
	float xyzw[4];
	float rgba[4];
	float normal[4];
	float texture[4];
} Vertex;

///    v6----- v5
//   /|      /|
//  v1------v0|
//  | |     | |
//  | |v7---|-|v4
//  |/      |/
//  v2------v3
	// Mảng dữ liệu
Vertex Vertices[] =
{


	// v4-v7-v6 (back - user)
	{ {  0.5f,	-0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 0,-1, 0 },{ 0.0f, 0.0f } },
	{ { -0.5f,	-0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 0,-1, 0 },{ 1.0f, 0.0f } },
	{ { -0.5f,	 0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 0,-1, 0 },{ 1.0f, 1.0f } },
	// v6-v5-v4
	{ { -0.5f,	 0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 0,-1, 0 },{ 1.0f, 1.0f } },
	{ {  0.5f,	 0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 0,-1, 0 },{ 0.0f, 1.0f } },
	{ {  0.5f,	-0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 0,-1, 0 },{ 0.0f, 0.0f } },

	// v2-v3-v0 (front - user)
	{ { -0.5f,	-0.5f,	0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 0, 1, 0 },{ 0.0f, 0.0f } },
	{ {  0.5f,	-0.5f,	0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 0, 1, 0 },{ 1.0f, 0.0f } },
	{ {  0.5f,	 0.5f,	0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 0, 1, 0 },{ 1.0f, 1.0f } },
	// v0-v1-v2
	{ {  0.5f,	 0.5f,	0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 0, 1, 0 },{ 1.0f, 1.0f } },
	{ { -0.5f,	 0.5f,	0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 0, 1, 0 },{ 0.0f, 1.0f } },
	{ { -0.5f,	-0.5f,	0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 0, 1, 0 },{ 0.0f, 0.0f } },

	//v1-v0-v5 (top)
	{ { -0.5f,	0.5f,	 0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 1, 0, 0 },{ 0.0f, 0.0 } },
	{ {  0.5f,	0.5f,	 0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 1, 0, 0 },{ 1.0f, 0.0f } },
	{ {  0.5f,	0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 1, 0, 0 },{ 1.0f, 1.0f } },
	//v5-v6-v1 
	{ {  0.5f,	0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 1, 0, 0 },{ 1.0f, 1.0f } },
	{ { -0.5f,	0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 1, 0, 0 },{ 0.0f, 1.0f } },
	{ { -0.5f,	0.5f,	 0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 1, 0, 0 },{ 0.0f, 0.0f } },

	// v7-v4-v3 (bottom)
	{ { -0.5f,	 -0.5f,-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0,-1, 0, 0 },{ 0.0f, 0.0 } },
	{ {  0.5f,	-0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0,-1, 0, 0 },{ 1.0f, 0.0f } },
	{ {  0.5f,	-0.5f,	 0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0,-1, 0, 0 },{ 1.0f, 1.0f } },
	// v3-v2-v7
	{ {  0.5f,	-0.5f,	 0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0,-1, 0, 0 },{ 1.0f, 1.0f } },
	{ { -0.5f,	-0.5f,	 0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0,-1, 0, 0 },{ 0.0f, 1.0f } },
	{ { -0.5f,	-0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0,-1, 0, 0 },{ 0.0f, 0.0f } },

	// v3-v4-v5 (right)
	{ { 0.5f,	-0.5f,   0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 1, 0, 0, 0 },{ 0.0f, 0.0f } },
	{ { 0.5f,	-0.5f,  -0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 1, 0, 0, 0 },{ 1.0f, 0.0f } },
	{ { 0.5f,	 0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 1, 0, 0, 0 },{ 1.0f, 1.0f } },
	// v5-v0-v3 
	{ { 0.5f,	 0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 1, 0, 0, 0 },{ 1.0f, 1.0f } },
	{ { 0.5f,	 0.5f,	 0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 1, 0, 0, 0 },{ 0.0f, 1.0f } },
	{ { 0.5f,	-0.5f,   0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 1, 0, 0, 0 },{ 0.0f, 0.0f } },

	// v7-v2-v1 (left)
	{ { -0.5f,	-0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ -1, 0, 0, 0 },{ 0.0f, 0.0 } },
	{ { -0.5f,	-0.5f,	 0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ -1, 0, 0, 0 },{ 1.0f, 0.0f } },
	{ { -0.5f,	 0.5f,	 0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ -1, 0, 0, 0 },{ 1.0f, 1.0f } },
	// v1-v6-v7 
	{ { -0.5f,	 0.5f,	 0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ -1, 0, 0, 0 },{ 1.0f, 1.0f } },
	{ { -0.5f,	 0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ -1, 0, 0, 0 },{ 0.0f, 1.0f } },
	{ { -0.5f,	-0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ -1, 0, 0, 0 },{ 0.0f, 0.0f } }

};


const size_t BufferSize = sizeof(Vertices);
const size_t VertexSize = sizeof(Vertices[0]);
const size_t RgbOffset = sizeof(Vertices[0].xyzw);
const size_t NormalOffset = sizeof(Vertices[0].xyzw) + sizeof(Vertices[1].rgba);
const size_t TextureOffset = sizeof(Vertices[0].xyzw) + sizeof(Vertices[1].rgba) + sizeof(Vertices[1].normal);


class MatrixStack {
	int    index;
	int    size;
	mat4* matrices;

public:
	MatrixStack(int numMatrices = 32) :index(0), size(numMatrices)
	{
		matrices = new mat4[numMatrices];
	}

	~MatrixStack()
	{
		delete[]matrices;
	}

	mat4& push(const mat4& m) {
		assert(index + 1 < size);
		matrices[index++] = m;
		return matrices[index];
	}

	mat4& pop(void) {
		assert(index - 1 >= 0);
		index--;
		return matrices[index];
	}
};

int
CurrentWidth = 800,
CurrentHeight = 600;

GLuint
VaoId,
VboId,
VertexShaderId,
FragmentShaderId,
ProgramId;

MatrixStack  mvstack;

mat4 model_mat_cpp,
model_lamp,
model_fan,
view_mat_cpp,
projection_mat_cpp;


int
model_mat_location,
view_mat_location,
projection_mat_location;

GLfloat rotateAll = 0;

float
r[] = { 0.0f, 0.0f, 0.0f },
s[] = { 1.0f, 1.0f, 1.0f },
t[] = { 0.0f, 0.0f, 0.0f };

bool
translated = false,
rotated = false,
scaled = false,
xoaycanh = false,
xoaythan = false,
xoayxuoi = false,
battat = false;

GLfloat height = 0, xoay = 0, gap = 0, dich_nk = 0;


GLfloat xoay2 = 0, rota = 0, quaydeuquaydeu = 0, ganxa = 0;

GLfloat gocxoay[4] = { 0, 12.5, 25, 37.5 };

int so = 0;

GLfloat tmp = 0;

float a = 0, dich_ban_x = 0, dich_ban_z = 0;

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
//-----------------------------------------------------------------
void block1(mat4 mtg, mat4 mt) {
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
	glDrawArrays(GL_TRIANGLES, 0, 6);
}
// -----------------------------------------------------------------
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
// --------------------------------------
bool CompileShader(GLuint shaderID) {
	cout << "Compiling shader" << shaderID << "..." << endl;
	glCompileShader(shaderID);
	int result = -1;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
	if (result != GL_TRUE) {
		cout << "Shader " << shaderID << " compile failed" << endl;
		int maxLength = 2048;
		int realLength = 0;
		char log[2048];
		glGetShaderInfoLog(shaderID, maxLength, &realLength, log);
		cout << log << endl;
		return false;
	}
	cout << "Shader " << shaderID << " compile successful" << endl;
	return true;
}

bool LoadTexture(const char* file_name, GLuint* texture) {
	int x, y, n;
	int force_channels = 4;
	stbi_set_flip_vertically_on_load(true);

	// lấy vị trí của tệp ảnh đầu vào
	// x: chiều rộng
	// y: chiều cao
	// : số kênh màu
	unsigned char* image_data = stbi_load(file_name, &x, &y, &n, force_channels);
	if (!image_data) {
		fprintf(stderr, "ERROR: could not load %s\n", file_name);
		return false;
	}
	// NPOT check
	if ((x & (x - 1)) != 0 || (y & (y - 1)) != 0) {
		fprintf(stderr, "WARNING: texture %s is not power-of-2 dimensions\n",
			file_name);
	}

	// tham chiếu kết cấu
	// 1: số lượng kết cấu muốn lưu trữ
	// texture: lưu trữ
	glGenTextures(1, texture);
	glActiveTexture(GL_TEXTURE0);

	// ràng buộc kết cấu
	glBindTexture(GL_TEXTURE_2D, *texture);

	// nạp dữ liệu vào texture
	// GL_TEXTURE_2D: mục tiêu kết cấu
	// 0: cấp độ mipmap, cấp độ cơ bản 0
	// GL_RGBA: định dạng lưu kết cấu
	// x, y: chiều rộng, chiều cao
	// 0: một số công cụ kế thừa???
	// GL_RGBA, GL_UNSIGNED_BYTE: định dạng và kiểu dữ liệu của ảnh nguồn
	// image_data: dữ liệu hình ảnh đã nạp trước đó
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
	glGenerateMipmap(GL_TEXTURE_2D);

	// Texture Wrapping
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// Texture Filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Mipmaps
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	GLfloat max_aniso = 0.0f;
	glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &max_aniso);

	// set the maximum!
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, max_aniso);
	return true;
}

// ------------------------------------------
	// thÃ¢n
mat4 model_room;
void room()
{
	mvstack.push(model_room);
	GLuint texture;
	(LoadTexture("xamnhat.jpg", &texture));
	mat4 san = identity_mat4() * translate(vec3(0, -0.5, 0)) * rotate_z(180) * scale(vec3(2.5, 0.01, 1.6));
	block(model_room, san);
	mat4 tran = identity_mat4() * translate(vec3(0, 1, 0)) * scale(vec3(2.5, 0.01, 1.6));
	block(model_room, tran);

	(LoadTexture("gray.png", &texture));
	mat4 lung = translate(vec3(0, 0.25, -0.8)) * rotate_y(180) * scale(vec3(2.5, 1.5, 0.01));
	block(model_room, lung);
	/*mat4 trai = translate(vec3(1.25, 0.25, 0)) * scale(vec3(0.01, 1.5, 1.6));
	block(model_room, trai);
	mat4 phai = translate(vec3(-1.25, 0.25, 0)) * rotate_y(180) * scale(vec3(0.01, 1.5, 1.6));
	block(model_room, phai);*/
	model_room = mvstack.pop();
}

//--------------------------------------------------------------------------
//ve ban
mat4 model_table;
void table() {
	mvstack.push(model_table);
	GLuint texture;
	(LoadTexture("goban.jpg", &texture));
	mat4 foot = scale(vec3(0.01, 0.35, 0.3));
	block(model_table, translate(vec3(-0.2, -0.325, -0.4)) * foot);
	block(model_table, translate(vec3(-0.8, -0.325, -0.4)) * rotate_z(180) * foot);
	mat4 matban = scale(vec3(0.6, 0.01, 0.3));
	block(model_table, translate(vec3(-0.5, -0.15, -0.4)) * rotate_z(180) * matban);
	model_table = mvstack.pop();
}
//---------------------------------------------------------------------------
//ve ngan keo
mat4 model_drawer;
void drawer() {
	mvstack.push(model_drawer);
	GLuint texture;
	(LoadTexture("nausang.jpg", &texture));
	mat4 day_ngankeo = scale(vec3(0.3, 0.01, 0.3));
	block(model_drawer, translate(vec3(-0.65, -0.23, -0.4)) * rotate_z(180) * day_ngankeo);
	mat4 canhtrai_ngankeo = scale(vec3(0.001, 0.08, 0.3));
	block(model_drawer, translate(vec3(-0.5, -0.195, -0.4)) * rotate_z(180) * canhtrai_ngankeo);
	mat4 ngankeo = scale(vec3(0.001, 0.08, 0.3));
	block(model_drawer, translate(vec3(-0.65, -0.19, -0.25)) * rotate_y(270) * ngankeo);
	(LoadTexture("nau.jpg", &texture));
	mat4 hand_keo = scale(vec3(0.01, 0.02, 0.07));
	block(model_drawer, translate(vec3(-0.65, -0.19, -0.215)) * rotate_y(90) * hand_keo);
	(LoadTexture("nausang.jpg", &texture));
	mat4 canhphai_ngankeo = scale(vec3(0.001, 0.08, 0.3));
	block(model_drawer, translate(vec3(-0.8, -0.195, -0.4)) * rotate_z(180) * canhphai_ngankeo);
	model_drawer = mvstack.pop();
}
//-----------------------------------------
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
	mvstack.push(model_fan);
	GLuint texture;
	(LoadTexture("tim1.jpg", &texture));
	model_fan = model_fan * translate(vec3(0.0, 0.25, -0.4)) * scale(vec3(0.5, 0.5, 0.5)) * rotate_y(xoay - 45);
	base_fan();
	body_down_fan();
	(LoadTexture("timloang.jpg", &texture));
	head_fan = identity_mat4() * rotate_y(quaydeuquaydeu) * translate(vec3(0.0, height, 0.0));
	body_up_fan();
	head_fann();
	(LoadTexture("lacaydam.jpg", &texture));
	point_push();
	head_fan = head_fan * translate(vec3(0.0, 0.3, 0.0));
	(LoadTexture("cam.jpg", &texture));
	rotation_point();
	(LoadTexture("red.jpg", &texture));
	propellers();
	model_fan = mvstack.pop();
}
// ---------------------------------------------------------------------------	
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
	mvstack.push(model_lamp);
	GLuint texture;
	(LoadTexture("timnhat.jpg", &texture));
	lamp_base();
	lamp_body_down();
	(LoadTexture("pink.jpg", &texture));
	head_lamp = identity_mat4() * translate(vec3(0.0, 0.2, 0.0)) * rotate_x(gap);
	lamp_body_up();
	lamp_connection();
	lamp_head();
	(LoadTexture("vang.jpg", &texture));
	if (battat)
	{
		head_lamp = head_lamp * translate(vec3(0, 0, -0.125)) * rotate_x(270);
		for (int i = 0; i < 360; i++)
			anhsang(i);
		vetnangcuoitroi();
	}
	model_lamp = mvstack.pop();
}
//--------------------------------------------
//ve ghe 
mat4 model_ghe;
float dich_ghe_x = 0, dich_ghe_y = 0, dich_ghe_z = 0;
void ghe() {
	mvstack.push(model_ghe);
	GLuint texture;
	(LoadTexture("goghe.jpg", &texture));
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
	model_ghe = mvstack.pop();
}
//-----------------------------------------------------------
// ve giuong
mat4 model_giuong;
float giuong_x = 0, giuong_z = 0;
void giuong() {
	mvstack.push(model_giuong);
	GLuint texture;
	(LoadTexture("gogiuong.jpg", &texture));
	mat4 mat_giuong = scale(vec3(0.6, 0.2, 1.0));
	block(model_giuong, translate(vec3(0.95, -0.4, -0.3)) * rotate_z(180) * mat_giuong);
	(LoadTexture("timnhat.jpg", &texture));
	mat4 goi = scale(vec3(0.15, 0.03, 0.1));
	block(model_giuong, translate(vec3(1.0, -0.29, -0.75)) * goi);
	model_giuong = mvstack.pop();
}
//---------------------------------------------
//ve laptop
mat4 model_laptop;
void laptop() {
	mvstack.push(model_laptop);
	GLuint texture;
	(LoadTexture("blue.jpg", &texture));
	mat4 than_lap = scale(vec3(0.18, 0.01, 0.12));
	block(model_laptop, translate(vec3(-0.3, -0.13, -0.35)) * than_lap);
	mat4 man_hinh = scale(vec3(0.18, 0.01, 0.12));
	block(model_laptop, translate(vec3(-0.3, -0.125, -0.41)) * rotate_x(a) * translate(vec3(0.0, -0.005, 0.06)) * man_hinh);
	model_laptop = mvstack.pop();
}
//---------------------------------------------
//ve tu
mat4 model_tu;
//ve than tu
void body_cabinet() {
	mvstack.push(model_tu);
	GLuint texture;
	(LoadTexture("blue.jpg", &texture));
	mat4 canhben = scale(vec3(0.02, 0.65, 0.2));
	block(model_tu, translate(vec3(-1.2, -0.18, -0.4)) * canhben);
	block(model_tu, translate(vec3(-0.9, -0.18, -0.4)) * canhben);
	mat4 day = scale(vec3(0.32, 0.02, 0.2));
	block(model_tu, translate(vec3(-1.05, 0.15, -0.4)) * day);
	block(model_tu, translate(vec3(-1.05, -0.36, -0.4)) * day);
	block(model_tu, translate(vec3(-1.05, -0.5, -0.4)) * day);
	mat4 canhsau = scale(vec3(0.32, 0.66, 0.02));
	block(model_tu, translate(vec3(-1.05, -0.17, -0.5)) * canhsau);
	model_tu = mvstack.pop();
}
//ve cua trai tu
mat4 combo_tu1;
void leftwing_cabinet() {
	GLuint texture;
	(LoadTexture("timloang.jpg", &texture));
	mat4 cuatrai = identity_mat4();
	cuatrai = scale(vec3(0.16, 0.66, 0.01));
	block(model_tu, translate(vec3(-0.97, -0.17, -0.3)) * combo_tu1 * cuatrai);
}
//-----
//ve cua phai tu
mat4 combo_tu2;
void rightwing_cabinet() {
	GLuint texture;
	(LoadTexture("timloang.jpg", &texture));
	mat4 cuaphai = identity_mat4();
	cuaphai = scale(vec3(0.16, 0.66, 0.01));
	block(model_tu, translate(vec3(-1.13, -0.17, -0.3)) * combo_tu2 * cuaphai);
}
GLfloat quaycanhtu[] = { 0,0 };
GLfloat quaycanhtu1[] = { 0,0 };
GLfloat dichtu_z, quaytu_y;
void tu() {
	model_tu = model_tu * translate(vec3(0.0, 0.0, dichtu_z)) * rotate_y(quaytu_y);
	body_cabinet();
	combo_tu1 = identity_mat4() * translate(vec3(0.05, 0.0, 0.0)) * rotate_y(quaycanhtu[0]) * translate(vec3(-0.055, 0.0, 0.0));
	leftwing_cabinet();
	combo_tu2 = identity_mat4() * translate(vec3(-0.0485, 0.0, 0.0)) * rotate_y(quaycanhtu1[0]) * translate(vec3(0.055, 0.0, 0.0));
	rightwing_cabinet();
}
//-----------------------------------------------
//ve den phong
mat4 model_room_light;
bool checkturn = false;
void roomlight() {
	GLuint texture;
	if (checkturn)
		(LoadTexture("vang.jpg", &texture));
	else
		(LoadTexture("nau.jpg", &texture));
	mat4 light = translate(vec3(0.0, 0.8, -0.4)) * scale(vec3(1, 0.05, 0.05));
	block(model_room_light, light);
}

//-----------------------------------------------
//cua so
mat4 model_window;
void body_cuaso() {
	GLuint texture;
	(LoadTexture("sky.jpg", &texture));
	mat4 khung = identity_mat4() * translate(vec3(-0.4, 0.3, -0.78)) * scale(vec3(0.3, 0.5, 0.01));
	block1(model_window, khung);
}
GLfloat quaycuatrai[] = { 0,0 }, quaycuaphai[] = { 0,0 };
mat4 canhcua1;
void cuasotrai() {
	GLuint texture;
	(LoadTexture("nau.jpg", &texture));
	mat4 canhtrai = identity_mat4() * scale(vec3(0.15, 0.5, 0.01)) /** rotate_y(quaycuatrai) */ * rotate_y(90);
	block(model_window, translate(vec3(-0.3, 0.3, -0.78)) * canhcua1 * canhtrai);
}
mat4 canhcua2;
void cuasophai() {
	GLuint texture;
	(LoadTexture("nau.jpg", &texture));
	mat4 canhphai = identity_mat4() * scale(vec3(0.15, 0.5, 0.01)) /** rotate_y(quaycuaphai) */ * rotate_y(90);
	block(model_window, translate(vec3(-0.4905, 0.3, -0.78)) * canhcua2 * canhphai);
}
void cuaso() {
	body_cuaso();
	canhcua1 = identity_mat4() * translate(vec3(0.0375, 0.0, 0.0)) * rotate_y(quaycuatrai[0]) * translate(vec3(-0.055, 0.0, 0.0));
	cuasotrai();
	canhcua2 = identity_mat4() * translate(vec3(-0.0375, 0.0, 0.0)) * rotate_y(quaycuaphai[0]) * translate(vec3(0.055, 0.0, 0.0));
	cuasophai();
}
//------------------------------------
//ve dong ho
mat4 model_clock;
mat4 combo;
double lac = 0;
void body_clockk() {
	mat4 body_clock = identity_mat4() * translate(vec3(0.0, 0.45, -0.75)) * scale(vec3(0.12, 0.21, 0.1/*0.08,0.25,0.1*/));
	block(model_clock, body_clock);
	GLuint texture;
	(LoadTexture("white.jpg", &texture));
	mat4 body_clock_white = identity_mat4() * translate(vec3(0.0, 0.45, -0.73)) * scale(vec3(0.08, 0.16, 0.08));
	block(model_clock, body_clock_white);
	(LoadTexture("nau.jpg", &texture));
	mat4 clockwise_hour = identity_mat4() * translate(vec3(0.011, 0.44, -0.7)) * rotate_z(135) * scale(vec3(0.035, 0.008, 0.04));
	block(model_clock, clockwise_hour);
	mat4 clockwise_minus = identity_mat4() * translate(vec3(0.0, 0.43, -0.7)) * rotate_z(90) * scale(vec3(0.06, 0.008, 0.04));
	block(model_clock, clockwise_minus);
}
void shaker_bar() {
	mat4 instance = identity_mat4() * translate(vec3(0, -0.065, 0)) * scale(vec3(0.01, 0.13, 0.03));
	block(model_clock, combo * instance);
}
void bob() {
	mat4 instance = identity_mat4() * translate(vec3(0.0, 0.225 - 0.365, 0)) * scale(vec3(0.04, 0.04, 0.03));
	block(model_clock, combo * instance);
}
bool isLacXuoi = true;
void clockk() {
	body_clockk();
	combo = identity_mat4() * translate(vec3(0.0, 0.365, -0.75)) * rotate_z(lac);
	shaker_bar();
	bob();
}
//------------------------------------
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

// ------------------------------------------
void CreatVaoVbo()
{
	glGenVertexArrays(1, &VaoId);
	glBindVertexArray(VaoId);

	glGenBuffers(1, &VboId);
	glBindBuffer(GL_ARRAY_BUFFER, VboId);
	glBufferData(GL_ARRAY_BUFFER, BufferSize, Vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, VertexSize, 0); // position
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, VertexSize, (GLvoid*)RgbOffset); // color
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, VertexSize, (GLvoid*)NormalOffset); // normal
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, VertexSize, (GLvoid*)TextureOffset); // texture

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
}
// ------------------------------------------
void CreatShaders()
{
	string vertexSrc = ReadShaderSourceFile("./vs.shader");
	string fragmentSrc = ReadShaderSourceFile("./fs.shader");

	const GLchar* VertexShader = vertexSrc.c_str();
	const GLchar* FragmentShader = fragmentSrc.c_str();

	VertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(VertexShaderId, 1, &VertexShader, NULL);
	CompileShader(VertexShaderId);

	FragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(FragmentShaderId, 1, &FragmentShader, NULL);
	CompileShader(FragmentShaderId);

	ProgramId = glCreateProgram();
	glAttachShader(ProgramId, VertexShaderId);
	glAttachShader(ProgramId, FragmentShaderId);
	glLinkProgram(ProgramId);
	glUseProgram(ProgramId);
}
// ------------------------------------------
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

void DisplayFunc(void)
{
	view_mat_location = glGetUniformLocation(ProgramId, "view_mat_shader");
	model_mat_location = glGetUniformLocation(ProgramId, "model_mat_shader");
	projection_mat_location = glGetUniformLocation(ProgramId, "projection_mat_shader");
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	mvstack.push(model_room);
	model_room = rotate_y(rotateAll) * scale(vec3(s[0], s[1], s[2]));
	room();
	model_room = mvstack.pop();

	mvstack.push(model_table);
	model_table = rotate_y(rotateAll) * scale(vec3(s[0], s[1], s[2])) * translate(vec3(dich_ban_x, 0.0, dich_ban_z));
	table();
	model_table = mvstack.pop();

	mvstack.push(model_drawer);
	model_drawer = rotate_y(rotateAll) * scale(vec3(s[0], s[1], s[2])) * translate(vec3(dich_ban_x, 0.0, dich_ban_z)) * translate(vec3(0.0, 0.0, dich_nk));
	drawer();
	model_drawer = mvstack.pop();

	mvstack.push(model_fan);
	model_fan = rotate_y(rotateAll) * scale(vec3(s[0], s[1], s[2]));
	fan();
	model_fan = mvstack.pop();

	mvstack.push(model_lamp);
	model_lamp = translate(vec3(dich_ban_x, 0.0, dich_ban_z)) * rotate_y(rotateAll - 100) * scale(vec3(s[0] / 2, s[1] / 2, s[2] / 2)) * translate(vec3(-0.5, -0.275, 1.5));
	lamp();
	model_lamp = mvstack.pop();

	mvstack.push(model_ghe);
	model_ghe = rotate_y(rotateAll) * scale(vec3(s[0], s[1], s[2])) * translate(vec3(dich_ghe_x, 0.0, dich_ghe_z));
	ghe();
	model_ghe = mvstack.pop();

	mvstack.push(model_giuong);
	model_giuong = rotate_y(rotateAll) * scale(vec3(s[0], s[1], s[2])) * translate(vec3(giuong_x, 0.0, giuong_z));
	giuong();
	model_giuong = mvstack.pop();

	mvstack.push(model_laptop);
	model_laptop = rotate_y(rotateAll) * scale(vec3(s[0], s[1], s[2])) * translate(vec3(dich_ban_x, 0.0, dich_ban_z));
	laptop();
	model_laptop = mvstack.pop();

	mvstack.push(model_tu);
	model_tu = rotate_y(rotateAll) * scale(vec3(s[0], s[1], s[2]));
	tu();
	model_tu = mvstack.pop();

	mvstack.push(model_room_light);
	model_room_light = rotate_y(rotateAll) * scale(vec3(s[0], s[1], s[2]));
	roomlight();
	model_room_light = mvstack.pop();

	mvstack.push(model_window);
	model_window = rotate_y(rotateAll) * scale(vec3(s[0], s[1], s[2]));
	cuaso();
	model_window = mvstack.pop();

	mvstack.push(model_clock);
	model_clock = rotate_y(rotateAll) * scale(vec3(s[0], s[1], s[2]));
	clockk();
	model_clock = mvstack.pop();

	glutSwapBuffers();
}
// ------------------------------------------
void ReshapeFunc(int Width, int Height)
{
	CurrentWidth = Width;
	CurrentHeight = Height;

}
// ------------------------------------------
void IdleFunc(void)
{
	if (xoaycanh)
	{
		(xoay2 > 360) ? xoay2 -= (360 - tmp) : xoay2 += tmp;
		tmp = (tmp < gocxoay[so]) ? tmp + 0.1 : tmp;
	}
	else
	{
		(xoay2 > 360) ? xoay2 -= (360 - tmp) : xoay2 += tmp;
		tmp = (tmp > gocxoay[so]) ? tmp - 0.1 : tmp;
	}
	if (xoaythan)
	{
		if (xoayxuoi)
		{
			quaydeuquaydeu += 2.5;
			if (quaydeuquaydeu >= 75)
				xoayxuoi = false;
		}
		else
		{
			quaydeuquaydeu -= 2.5;
			if (quaydeuquaydeu <= -75)
				xoayxuoi = true;
		}
	}
	if (isLacXuoi)
	{
		lac += 5;
		isLacXuoi = (lac != 30);
	}
	else
	{
		lac -= 5;
		isLacXuoi = (lac == -30);
	}
	glutPostRedisplay();
}
// ------------------------------------------
void KeyboardFunc(unsigned char key, int x, int y)
{
	switch (key) {
	case 27:
		exit(EXIT_SUCCESS); break;
		//quay canh quat
	case '0': case '1': case '2': case '3':
		xoaycanh = (key - '0' > so);
		so = key - '0';
		break;
		//quay dau quat, an tut nang
	case 'j':
		xoaythan = true - xoaythan;
		rota = 0.015f - rota;
		break;
		//zoom to nho
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
		//dichban
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
		//dichngankeo
	case 'n':
		dich_nk += 0.05;
		if (dich_nk >= 0.25)
			dich_nk = 0.25;
		break;
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
		//mo may tinh
	case 'x':
		a -= 5;
		if (a <= -120)
			a = -120;
		break;
		//dong may tinh
	case 'X':
		a += 5;
		if (a >= 0)
			a = 0;
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
		quaycanhtu1[0] += 5;
		if (quaycanhtu[0] + 5 >= 180) quaycanhtu[0] = 180;
		break;
		//Đóng phai tủ
	case 'E':
		quaycanhtu1[0] -= 5;
		if (quaycanhtu[0] - 5 <= 0)quaycanhtu[0] = 0;
		break;
		// bat tat den phong
	case 'h':
		checkturn = true - checkturn;
		break;
		//mo trai cua 
	case 'q':
		quaycuatrai[0] += 5;
		if (quaycuatrai[0] + 5 >= 180) quaycuatrai[0] = 180;
		break;
		//dong trai cua
	case 'Q':
		quaycuatrai[0] -= 5;
		if (quaycuatrai[0] - 5 <= 0)quaycuatrai[0] = 0;
		break;
		//mo phai cua
	case 'w':
		quaycuaphai[0] -= 5;
		if (quaycuaphai[0] - 5 <= -180) quaycuaphai[0] = -180;
		break;
		//dong phai cua
	case 'W':
		quaycuaphai[0] += 5;
		if (quaycuaphai[0] + 5 >= 0) quaycuaphai[0] = 0;
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
// ------------------------------------------
// ------------------------------------------
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