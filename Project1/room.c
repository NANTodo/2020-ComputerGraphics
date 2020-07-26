#define STB_IMAGE_IMPLEMENTATION
#define _CRT_SECURE_NO_WARNINGS
#define GL_GLEXT_LEGACY

#include <windows.h>  
#include "stb_image.h"
#include <gl/glut.h>
#include <stdio.h>
#include <gl/GL.h>
#include <math.h>
#include <stdlib.h>


int press_x, press_y;
int release_x, release_y;
float x_angle = 0.0;
float y_angle = 0.0;
float scale_size = 1.0;
float camera_distance = 5.0;
float xTrans = 0.0f, yTrans = 0.0f, zTrans = 0.0f;
int xform_mode = 0;

int width = 256;
int height = 256;
int bitdepth = 4;

static GLuint textureNames;
static GLuint textureNames2;
GLint TexFilter1 = GL_NEAREST;
GLint TexFilter2 = GL_NEAREST;
GLubyte *data1;

#define XFORM_NONE    0 
#define XFORM_ROTATE  1
#define XFORM_SCALE   2
#define XFORM_TRANSLATE	3
#define GL_PI 3.1415f


GLfloat ambient[] = { 0.3, 0.3, 0.3, 1.0 };

GLfloat light_ambient[] = { 0.3, 0.3, 0.3, 1.0 };
GLfloat light_diffuse[] = { 0.6, 0.6, 0.6, 1.0 };
GLfloat light_specular[] = { 0.9, 0.9, 0.9, 1.0 };
GLfloat light_position[] = { 0.0, 0.96, 0, 0.0 };

GLfloat light1_ambient[] = { 0.0, 0.2, 0.2, 1.0 };
GLfloat light1_diffuse[] = { 0.0, 0.4, 0.4, 1.0 };
GLfloat light1_specular[] = { 0.0, 0.6, 0.6, 1.0 };
GLfloat light1_position[] = { 1.5, 0.96, 0.75, 0.0 };

GLfloat light2_ambient[] = { 0.2, 0, 0, 1.0 };
GLfloat light2_diffuse[] = { 0.4, 0, 0, 1.0 };
GLfloat light2_specular[] = { 0.6, 0, 0, 1.0 };
GLfloat light2_position[] = { -1.5, 0.96, 0.75, 0.0 };



GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };

GLfloat ceil_diffuse[] = { 0.98f, 0.952f, 0.894f, 1.0f };
GLfloat ceil_ambient[] = { 0.921f, 0.862f,0.811f, 1.0f };


GLfloat wall_diffuse[] = { 0.98f, 0.97f, 0.894f, 1.0f };
GLfloat wall_ambient[] = { 0.858f, 0.851f, 0.784f, 1.0f };

GLfloat floor_diffuse[] = { 0.921f, 0.666f, 0.372f, 1.0f };
GLfloat floor_ambient[] = { 0.768f, 0.553f, 0.310f, 1.0f };
GLfloat floor_specular[] = { 0.968f, 0.757f, 0.388f, 1.0f };

GLfloat lightt_diffuse[] = { 0.7f, 0.7f, 0.7f, 1.0f };
GLfloat lightt_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
GLfloat lightt_specular[] = { 0.9f, 0.9f, 0.9f, 1.0f };
GLfloat lightt_emission[] = {0.9, 0.9, 0.9, 1.0f};
GLfloat lightt_shiness[] = { 80.0f };

GLfloat wardro_diffuse[] = { 0.901f, 0.635f, 0.447f, 1.0f };
GLfloat wardro_ambient[] = { 0.768f, 0.545f, 0.384f, 1.0f };
GLfloat wardro_specular[] = { 0.968f, 0.686f, 0.486f, 1.0f };

GLfloat wardro2_diffuse[] = { 0.956f, 0.941f, 0.913f, 1.0f };
GLfloat wardro2_ambient[] = { 0.89f, 0.878f, 0.854f, 1.0f };
GLfloat wardro2_specular[] = { 1.0f, 0.988f, 0.961f, 1.0f };

GLfloat mirror_diffuse[] = { 0.7f, 0.7f, 0.7f, 0.0f };
GLfloat mirror_ambient[] = { 0.5f, 0.5f, 0.5f, 0.0f };
GLfloat mirror_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat mirror_shiness[] = { 100.0f };

GLfloat drawer_diffuse[] = { 0.756f, 0.443f, 0.262f, 1.0 };
GLfloat drawer_ambient[] = { 0.651f, 0.384f, 0.227f, 0.0f };
GLfloat drawer_specular[] = { 0.729f, 0.431f, 0.255f, 1.0f };

GLfloat desk_diffuse[] = { 0.968f, 0.898f, 0.824f, 1.0 };
GLfloat desk_ambient[] = { 0.902f, 0.835f, 0.765f, 0.0f };
GLfloat desk_specular[] = { 1.0f, 0.929f, 0.854f, 1.0 };

GLfloat desk2_diffuse[] = { 0.631f, 0.631f, 0.65f, 1.0f };
GLfloat desk2_ambient[] = { 0.545f, 0.545f, 0.561f, 0.0f };
GLfloat desk2_specular[] = { 0.710f, 0.710f, 0.729f, 1.0 };
GLfloat desk2_shinness[] = { 60.0f };

GLfloat deskdrawer_diffuse[] = { 0.902f, 0.678f, 0.494f, 1.0f };
GLfloat deskdrawer_ambient[] = { 0.819f, 0.615f, 0.451f, 1.0 };

GLfloat window_diffuse[] = { 0.509f, 0.788f, 0.949f, 1.0f };
GLfloat window_ambient[] = { 0.541f, 0.831f, 1.0f, 0.0f };
GLfloat window_specular[] = { 0.482f, 0.741f, 0.89f, 1.0 };
GLfloat window_shinness[] = { 100.0f };

GLfloat bed_diffuse[] = { 0.858f, 0.584f, 0.282f, 1.0f };
GLfloat bed_ambient[] = { 0.768f, 0.522f, 0.255f, 1.0f };
GLfloat bed_specular[] = { 0.902f, 0.608f, 0.298f, 1.0f };


GLfloat* calcNormal(GLfloat* a, GLfloat* b, GLfloat* c) {
	// define target plane
	GLfloat u[] = { b[0] - a[0], b[1] - a[1], b[2] - a[2] };
	GLfloat v[] = { c[0] - a[0], c[1] - a[1], c[2] - a[2] };
	// calculate cross product
	static GLfloat cp[3];
	cp[0] = u[1] * v[2] - u[2] * v[1];
	cp[1] = u[2] * v[0] - u[0] * v[2];
	cp[2] = u[0] * v[1] - u[1] * v[0];
	// normalize
	GLfloat length = sqrt(cp[0] * cp[0] + cp[1] * cp[1] + cp[2] * cp[2]);
	for (int i = 0; i < 3; i++) cp[i] /= -length; // <- invert the normal vector
	return cp;
}

void drawfloor() {

	GLfloat floorvertices[][3] = {
		{-1.25, 0, 0.75}, //0
		{-1.25, 0, -0.75}, //1
		{1.25, 0, -0.75}, //2
		{1.25, 0, 0.75},	//3
		{-1.25, -0.03, 0.75}, //4
		{-1.25, -0.03, -0.75}, //5
		{1.25, -0.03, -0.75}, //6
		{1.25, -0.03, 0.75} //7
	};

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, floor_diffuse);
	glMaterialfv(GL_FRONT, GL_AMBIENT, floor_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, floor_specular);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, TexFilter1);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, TexFilter2);
	
	glBegin(GL_QUADS);
	glBindTexture(GL_TEXTURE_2D, textureNames);
	glNormal3fv(calcNormal(floorvertices[0], floorvertices[1], floorvertices[2])); //top
	glTexCoord2f(0, 0); 
	glVertex3fv(floorvertices[0]);
	glTexCoord2f(0, 1); 
	glVertex3fv(floorvertices[1]);
	glTexCoord2f(1, 1); 
	glVertex3fv(floorvertices[2]);
	glTexCoord2f(1, 0); 
	glVertex3fv(floorvertices[3]);
	


	glNormal3fv(calcNormal(floorvertices[1], floorvertices[5], floorvertices[6]));//front
	glVertex3fv(floorvertices[1]);
	glVertex3fv(floorvertices[5]);
	glVertex3fv(floorvertices[6]);
	glVertex3fv(floorvertices[2]);

	glNormal3fv(calcNormal(floorvertices[2], floorvertices[6], floorvertices[7]));//right
	glVertex3fv(floorvertices[2]);
	glVertex3fv(floorvertices[6]);
	glVertex3fv(floorvertices[7]);
	glVertex3fv(floorvertices[3]);

	glNormal3fv(calcNormal(floorvertices[3], floorvertices[7], floorvertices[4]));//back
	glVertex3fv(floorvertices[3]);
	glVertex3fv(floorvertices[7]);
	glVertex3fv(floorvertices[4]);
	glVertex3fv(floorvertices[0]);

	glNormal3fv(calcNormal(floorvertices[0], floorvertices[4], floorvertices[5]));//left
	glVertex3fv(floorvertices[0]);
	glVertex3fv(floorvertices[4]);
	glVertex3fv(floorvertices[5]);
	glVertex3fv(floorvertices[1]);

	glNormal3fv(calcNormal(floorvertices[4], floorvertices[5], floorvertices[6]));//bottom
	glVertex3fv(floorvertices[4]);
	glVertex3fv(floorvertices[5]);
	glVertex3fv(floorvertices[6]);
	glVertex3fv(floorvertices[7]);
	
	glEnd();
}
void drawceiling() {

	GLfloat ceilvertices[][3] = {
	{-1.25, 1.0025, 0.75}, //0
	{-1.25, 1.0025, -0.75}, //1
	{1.25, 1.0025, -0.75}, //2
	{1.25, 1.0025, 0.75},	//3
	{-1.25, 0.9925, 0.75}, //4
	{-1.25, 0.9925, -0.75}, //5
	{1.25, 0.9925, -0.75}, //6
	{1.25, 0.9925, 0.75} //7
	};


	glBegin(GL_QUADS);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, ceil_diffuse);
	glMaterialfv(GL_FRONT, GL_AMBIENT, ceil_ambient);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	glNormal3fv(calcNormal(ceilvertices[0], ceilvertices[1], ceilvertices[2])); //top
	glVertex3fv(ceilvertices[0]);
	glVertex3fv(ceilvertices[1]);
	glVertex3fv(ceilvertices[2]);
	glVertex3fv(ceilvertices[3]);
	glEnd();

	glBegin(GL_QUADS);
	glNormal3fv(calcNormal(ceilvertices[1], ceilvertices[5], ceilvertices[6]));//front
	glVertex3fv(ceilvertices[1]);
	glVertex3fv(ceilvertices[5]);
	glVertex3fv(ceilvertices[6]);
	glVertex3fv(ceilvertices[2]);

	glNormal3fv(calcNormal(ceilvertices[2], ceilvertices[6], ceilvertices[7]));//right
	glVertex3fv(ceilvertices[2]);
	glVertex3fv(ceilvertices[6]);
	glVertex3fv(ceilvertices[7]);
	glVertex3fv(ceilvertices[3]);

	glNormal3fv(calcNormal(ceilvertices[3], ceilvertices[7], ceilvertices[4]));//back
	glVertex3fv(ceilvertices[3]);
	glVertex3fv(ceilvertices[7]);
	glVertex3fv(ceilvertices[4]);
	glVertex3fv(ceilvertices[0]);

	glNormal3fv(calcNormal(ceilvertices[0], ceilvertices[4], ceilvertices[5]));//left
	glVertex3fv(ceilvertices[0]);
	glVertex3fv(ceilvertices[4]);
	glVertex3fv(ceilvertices[5]);
	glVertex3fv(ceilvertices[1]);

	glNormal3fv(calcNormal(ceilvertices[4], ceilvertices[5], ceilvertices[6]));//bottom
	glVertex3fv(ceilvertices[4]);
	glVertex3fv(ceilvertices[5]);
	glVertex3fv(ceilvertices[6]);
	glVertex3fv(ceilvertices[7]);
	glEnd();

}

void drawall() {

	GLfloat wallvertices[][3] = {
		{-1.25f, 1.0f, 0.75},
		{-1.25f, 1.0f, -0.75},
		{1.25f, 1.0f, -0.75},
		{1.25, 1.0f, 0.75},
		{-1.25f, 0.0f, 0.75},
		{-1.25f, 0.0f, -0.75},
		{1.25f, 0.0f, -0.75},
		{1.25, 0.0f, 0.75},
	};
	glBegin(GL_QUADS);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, ceil_diffuse);
	glMaterialfv(GL_FRONT, GL_AMBIENT, ceil_ambient);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	/*
	glNormal3fv(calcNormal(wallvertices[1], wallvertices[5], wallvertices[6])); //d 침대쪽벽
	glVertex3fv(wallvertices[1]);
	glVertex3fv(wallvertices[5]);
	glVertex3fv(wallvertices[6]);
	glVertex3fv(wallvertices[2]);
	*/
	//b
	glNormal3fv(calcNormal(wallvertices[1], wallvertices[5], wallvertices[4]));
	glVertex3fv(wallvertices[1]);
	glVertex3fv(wallvertices[5]);
	glVertex3fv(wallvertices[4]);
	glVertex3fv(wallvertices[0]);
	
	

	glNormal3fv(calcNormal(wallvertices[3], wallvertices[7], wallvertices[4])); //c
	glVertex3fv(wallvertices[3]);
	glVertex3fv(wallvertices[7]);
	glVertex3fv(wallvertices[4]);
	glVertex3fv(wallvertices[0]);

	glNormal3fv(calcNormal(wallvertices[2], wallvertices[6], wallvertices[7])); //a 문벽
	glVertex3fv(wallvertices[2]);
	glVertex3fv(wallvertices[6]);
	glVertex3fv(wallvertices[7]);
	glVertex3fv(wallvertices[3]);

	glEnd();

}

void drawdoor() {

	//door
	GLfloat doorvertices[][3] = {
		{1.245, 0.96, -0.252},
		{1.245, 0.96, -0.708},
		{1.255, 0.96, -0.708},
		{1.255, 0.96, -0.252},
		{1.245, 0, -0.252},
		{1.245, 0, -0.708 },
		{1.255, 0, -0.708},		
		{1.255, 0, -0.252}
	};
	glBegin(GL_QUADS);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, floor_diffuse);
	glMaterialfv(GL_FRONT, GL_AMBIENT, floor_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, floor_specular);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	glNormal3fv(calcNormal(doorvertices[0], doorvertices[1], doorvertices[2])); //top
	glVertex3fv(doorvertices[0]);
	glVertex3fv(doorvertices[1]);
	glVertex3fv(doorvertices[2]);
	glVertex3fv(doorvertices[3]);

	glNormal3fv(calcNormal(doorvertices[1], doorvertices[5], doorvertices[6]));//front
	glVertex3fv(doorvertices[1]);
	glVertex3fv(doorvertices[5]);
	glVertex3fv(doorvertices[6]);
	glVertex3fv(doorvertices[2]);

	glNormal3fv(calcNormal(doorvertices[2], doorvertices[6], doorvertices[7]));//right
	glVertex3fv(doorvertices[2]);
	glVertex3fv(doorvertices[6]);
	glVertex3fv(doorvertices[7]);
	glVertex3fv(doorvertices[3]);


	glNormal3fv(calcNormal(doorvertices[3], doorvertices[7], doorvertices[4]));//back
	glVertex3fv(doorvertices[3]);
	glVertex3fv(doorvertices[7]);
	glVertex3fv(doorvertices[4]);
	glVertex3fv(doorvertices[0]);

	glNormal3fv(calcNormal(doorvertices[0], doorvertices[4], doorvertices[5]));//left
	glVertex3fv(doorvertices[0]);
	glVertex3fv(doorvertices[4]);
	glVertex3fv(doorvertices[5]);
	glVertex3fv(doorvertices[1]);

	glNormal3fv(calcNormal(doorvertices[4], doorvertices[5], doorvertices[6]));//bottom
	glVertex3fv(doorvertices[4]);
	glVertex3fv(doorvertices[5]);
	glVertex3fv(doorvertices[6]);
	glVertex3fv(doorvertices[7]);
	glEnd();

}

void drawlight() {

	GLfloat lightvertices[][3] = {
		{-0.25, 0.99, 0.25},
		{-0.25, 0.99, -0.25},
		{0.25, 0.99, -0.25},
		{0.25, 0.99, 0.25},
		{-0.25, 0.93, 0.25},
		{-0.25, 0.93, -0.25},
		{0.25, 0.93, -0.25},
		{0.25, 0.93, 0.25}
	};

	glBegin(GL_QUADS);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, lightt_diffuse);
	glMaterialfv(GL_FRONT, GL_AMBIENT, lightt_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, lightt_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, lightt_shiness);
	glMaterialfv(GL_FRONT, GL_EMISSION, lightt_emission);

	glNormal3fv(calcNormal(lightvertices[0], lightvertices[1], lightvertices[2])); //top
	glVertex3fv(lightvertices[0]);
	glVertex3fv(lightvertices[1]);
	glVertex3fv(lightvertices[2]);
	glVertex3fv(lightvertices[3]);

	glNormal3fv(calcNormal(lightvertices[1], lightvertices[5], lightvertices[6]));//front
	glVertex3fv(lightvertices[1]);
	glVertex3fv(lightvertices[5]);
	glVertex3fv(lightvertices[6]);
	glVertex3fv(lightvertices[2]);

	glNormal3fv(calcNormal(lightvertices[2], lightvertices[6], lightvertices[7]));//right
	glVertex3fv(lightvertices[2]);
	glVertex3fv(lightvertices[6]);
	glVertex3fv(lightvertices[7]);
	glVertex3fv(lightvertices[3]);

	glNormal3fv(calcNormal(lightvertices[3], lightvertices[7], lightvertices[4])); //back
	glVertex3fv(lightvertices[3]);
	glVertex3fv(lightvertices[7]);
	glVertex3fv(lightvertices[4]);
	glVertex3fv(lightvertices[0]);

	glNormal3fv(calcNormal(lightvertices[0], lightvertices[4], lightvertices[5]));//left
	glVertex3fv(lightvertices[0]);
	glVertex3fv(lightvertices[4]);
	glVertex3fv(lightvertices[5]);
	glVertex3fv(lightvertices[1]);

	glNormal3fv(calcNormal(lightvertices[4], lightvertices[5], lightvertices[6]));//bottom
	glVertex3fv(lightvertices[4]);
	glVertex3fv(lightvertices[5]);
	glVertex3fv(lightvertices[6]);
	glVertex3fv(lightvertices[7]);
	glEnd();

}

void wardrobe() {
	//벽장전체
	GLfloat wardrobvertices[][3] = {
		{0.95, 1.0, 0.749},
		{0.95, 1.0, -0.08},
		{1.249, 1.0, -0.08},
		{1.249, 1.0, 0.749},
		{0.95, 0.0, 0.749},
		{0.95, 0.0, -0.08},
		{1.249, 0.0, -0.08},
		{1.249, 0.0, 0.749},
	};
	glBegin(GL_QUADS);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, wardro_diffuse);
	glMaterialfv(GL_FRONT, GL_AMBIENT, wardro_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, wardro_specular);
	glNormal3fv(calcNormal(wardrobvertices[0], wardrobvertices[1], wardrobvertices[2])); //top
	glVertex3fv(wardrobvertices[0]);
	glVertex3fv(wardrobvertices[1]);
	glVertex3fv(wardrobvertices[2]);
	glVertex3fv(wardrobvertices[3]);

	glNormal3fv(calcNormal(wardrobvertices[1], wardrobvertices[5], wardrobvertices[6]));//front
	glVertex3fv(wardrobvertices[1]);
	glVertex3fv(wardrobvertices[5]);
	glVertex3fv(wardrobvertices[6]);
	glVertex3fv(wardrobvertices[2]);

	glNormal3fv(calcNormal(wardrobvertices[2], wardrobvertices[6], wardrobvertices[7]));//right
	glVertex3fv(wardrobvertices[2]);
	glVertex3fv(wardrobvertices[6]);
	glVertex3fv(wardrobvertices[7]);
	glVertex3fv(wardrobvertices[3]);

	glNormal3fv(calcNormal(wardrobvertices[3], wardrobvertices[7], wardrobvertices[4]));//back
	glVertex3fv(wardrobvertices[3]);
	glVertex3fv(wardrobvertices[7]);
	glVertex3fv(wardrobvertices[4]);
	glVertex3fv(wardrobvertices[0]);

	glNormal3fv(calcNormal(wardrobvertices[0], wardrobvertices[4], wardrobvertices[5]));//left
	glVertex3fv(wardrobvertices[0]);
	glVertex3fv(wardrobvertices[4]);
	glVertex3fv(wardrobvertices[5]);
	glVertex3fv(wardrobvertices[1]);

	glNormal3fv(calcNormal(wardrobvertices[4], wardrobvertices[5], wardrobvertices[6]));//bottom
	glVertex3fv(wardrobvertices[4]);
	glVertex3fv(wardrobvertices[5]);
	glVertex3fv(wardrobvertices[6]);
	glVertex3fv(wardrobvertices[7]);
	glEnd();

	//center
	GLfloat warcvertices[][3] = {
		{0.9495, 0.9, 0.45},
		{0.9495, 0.9, 0.21},
		{0.9495, 0.2, 0.21},
		{0.9495, 0.2, 0.45}
};

	GLfloat warrvertices[][3] = {
		{0.9495, 0.9, 0.71},
		{0.9495, 0.9, 0.47},
		{0.9495, 0.2, 0.47},
		{0.9495, 0.2, 0.71}
	};

	GLfloat warlvertices[][3] = {
		{0.9495, 0.9, 0.19},
		{0.9495, 0.9, -0.05},
		{0.9495, 0.2, -0.05},
		{0.9495, 0.2, 0.19}
	};
	glBegin(GL_QUADS);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, wardro2_diffuse);
	glMaterialfv(GL_FRONT, GL_AMBIENT, wardro2_ambient);
	glNormal3fv(calcNormal(warcvertices[0], warcvertices[1], warcvertices[2])); //top
	glVertex3fv(warcvertices[0]);
	glVertex3fv(warcvertices[1]);
	glVertex3fv(warcvertices[2]);
	glVertex3fv(warcvertices[3]);
	
	//right
	glNormal3fv(calcNormal(warrvertices[0], warrvertices[1], warrvertices[2])); //top
	glVertex3fv(warrvertices[0]);
	glVertex3fv(warrvertices[1]);
	glVertex3fv(warrvertices[2]);
	glVertex3fv(warrvertices[3]);


	//left
	glNormal3fv(calcNormal(warlvertices[0], warlvertices[1], warlvertices[2])); //top
	glVertex3fv(warlvertices[0]);
	glVertex3fv(warlvertices[1]);
	glVertex3fv(warlvertices[2]);
	glVertex3fv(warlvertices[3]);
	glEnd();


	GLfloat chandlevertices[][3] = {
		{0.94, 0.4375, 0.445},
		{0.94, 0.4375, 0.355},
		{0.96, 0.4375, 0.355},
		{0.96, 0.4375, 0.445 },
		{0.94, 0.4225, 0.445},
		{0.94, 0.4225, 0.355},
		{0.96, 0.4225, 0.355},
		{0.96, 0.4225, 0.445 }
	};

	//center 손잡이
	glBegin(GL_QUADS);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, wardro_diffuse);
	glMaterialfv(GL_FRONT, GL_AMBIENT, wardro_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, wardro_specular);
	glNormal3fv(calcNormal(chandlevertices[0], chandlevertices[1], chandlevertices[2])); //top
	glVertex3fv(chandlevertices[0]);
	glVertex3fv(chandlevertices[1]);
	glVertex3fv(chandlevertices[2]);
	glVertex3fv(chandlevertices[3]);

	glNormal3fv(calcNormal(chandlevertices[1], chandlevertices[5], chandlevertices[6]));//front
	glVertex3fv(chandlevertices[1]);
	glVertex3fv(chandlevertices[5]);
	glVertex3fv(chandlevertices[6]);
	glVertex3fv(chandlevertices[2]);

	glNormal3fv(calcNormal(chandlevertices[2], chandlevertices[6], chandlevertices[7]));//right
	glVertex3fv(chandlevertices[2]);
	glVertex3fv(chandlevertices[6]);
	glVertex3fv(chandlevertices[7]);
	glVertex3fv(chandlevertices[3]);

	glNormal3fv(calcNormal(chandlevertices[3], chandlevertices[7], chandlevertices[4]));//back
	glVertex3fv(chandlevertices[3]);
	glVertex3fv(chandlevertices[7]);
	glVertex3fv(chandlevertices[4]);
	glVertex3fv(chandlevertices[0]);

	glNormal3fv(calcNormal(chandlevertices[0], chandlevertices[4], chandlevertices[5]));//left
	glVertex3fv(chandlevertices[0]);
	glVertex3fv(chandlevertices[4]);
	glVertex3fv(chandlevertices[5]);
	glVertex3fv(chandlevertices[1]);

	glNormal3fv(calcNormal(chandlevertices[4], chandlevertices[5], chandlevertices[6]));//bottom
	glVertex3fv(chandlevertices[4]);
	glVertex3fv(chandlevertices[5]);
	glVertex3fv(chandlevertices[6]);
	glVertex3fv(chandlevertices[7]);
	glEnd();
	
	GLfloat rhandlevertices[][3] = {
		{0.94, 0.4375, 0.565},
		{0.94, 0.4375, 0.475},
		{0.96, 0.4375, 0.475},
		{0.96, 0.4375, 0.565 },
		{0.94, 0.4225, 0.565},
		{0.94, 0.4225, 0.475},
		{0.96, 0.4225, 0.475},
		{0.96, 0.4225, 0.565 }
	};
	glBegin(GL_QUADS);
	//right 손잡이
	glNormal3fv(calcNormal(rhandlevertices[0], rhandlevertices[1], rhandlevertices[2])); //top
	glVertex3fv(rhandlevertices[0]);
	glVertex3fv(rhandlevertices[1]);
	glVertex3fv(rhandlevertices[2]);
	glVertex3fv(rhandlevertices[3]);

	glNormal3fv(calcNormal(rhandlevertices[1], rhandlevertices[5], rhandlevertices[6]));//front
	glVertex3fv(rhandlevertices[1]);
	glVertex3fv(rhandlevertices[5]);
	glVertex3fv(rhandlevertices[6]);
	glVertex3fv(rhandlevertices[2]);

	glNormal3fv(calcNormal(rhandlevertices[2], rhandlevertices[6], rhandlevertices[7]));//right
	glVertex3fv(rhandlevertices[2]);
	glVertex3fv(rhandlevertices[6]);
	glVertex3fv(rhandlevertices[7]);
	glVertex3fv(rhandlevertices[3]);

	glNormal3fv(calcNormal(rhandlevertices[3], rhandlevertices[7], rhandlevertices[4]));//back
	glVertex3fv(rhandlevertices[3]);
	glVertex3fv(rhandlevertices[7]);
	glVertex3fv(rhandlevertices[4]);
	glVertex3fv(rhandlevertices[0]);

	glNormal3fv(calcNormal(rhandlevertices[0], rhandlevertices[4], rhandlevertices[5]));//left
	glVertex3fv(rhandlevertices[0]);
	glVertex3fv(rhandlevertices[4]);
	glVertex3fv(rhandlevertices[5]);
	glVertex3fv(rhandlevertices[1]);

	glNormal3fv(calcNormal(rhandlevertices[4], rhandlevertices[5], rhandlevertices[6]));//bottom
	glVertex3fv(rhandlevertices[4]);
	glVertex3fv(rhandlevertices[5]);
	glVertex3fv(rhandlevertices[6]);
	glVertex3fv(rhandlevertices[7]);
	glEnd();

	
	GLfloat lhandlevertices[][3] = {
		{0.94, 0.4375, 0.185},
		{0.94, 0.4375, 0.095},
		{0.96, 0.4375, 0.095},
		{0.96, 0.4375, 0.185 },
		{0.94, 0.4225, 0.185},
		{0.94, 0.4225, 0.095},
		{0.96, 0.4225, 0.095},
		{0.96, 0.4225, 0.185 }
	};

	//left 손잡이
	glBegin(GL_QUADS);
	glNormal3fv(calcNormal(lhandlevertices[0], lhandlevertices[1], lhandlevertices[2])); //top
	glVertex3fv(lhandlevertices[0]);
	glVertex3fv(lhandlevertices[1]);
	glVertex3fv(lhandlevertices[2]);
	glVertex3fv(lhandlevertices[3]);

	glNormal3fv(calcNormal(lhandlevertices[1], lhandlevertices[5], lhandlevertices[6]));//front
	glVertex3fv(lhandlevertices[1]);
	glVertex3fv(lhandlevertices[5]);
	glVertex3fv(lhandlevertices[6]);
	glVertex3fv(lhandlevertices[2]);

	glNormal3fv(calcNormal(lhandlevertices[2], lhandlevertices[6], lhandlevertices[7]));//right
	glVertex3fv(lhandlevertices[2]);
	glVertex3fv(lhandlevertices[6]);
	glVertex3fv(lhandlevertices[7]);
	glVertex3fv(lhandlevertices[3]);

	glNormal3fv(calcNormal(lhandlevertices[3], lhandlevertices[7], lhandlevertices[4]));//back
	glVertex3fv(lhandlevertices[3]);
	glVertex3fv(lhandlevertices[7]);
	glVertex3fv(lhandlevertices[4]);
	glVertex3fv(lhandlevertices[0]);

	glNormal3fv(calcNormal(lhandlevertices[0], lhandlevertices[4], lhandlevertices[5]));//left
	glVertex3fv(lhandlevertices[0]);
	glVertex3fv(lhandlevertices[4]);
	glVertex3fv(lhandlevertices[5]);
	glVertex3fv(lhandlevertices[1]);

	glNormal3fv(calcNormal(lhandlevertices[4], lhandlevertices[5], lhandlevertices[6]));//bottom
	glVertex3fv(lhandlevertices[4]);
	glVertex3fv(lhandlevertices[5]);
	glVertex3fv(lhandlevertices[6]);
	glVertex3fv(lhandlevertices[7]);
	glEnd();
}

void drawmirror() {
	GLfloat mirrorvertices[][3] = {
		{0.25, 0.8, 0.749},
		{0.25, 0.8, 0.5},
		{0.45, 0.8, 0.5},
		{0.45, 0.8, 0.749},
		{0.25, 0.0, 0.749},
		{0.25, 0.0, 0.5},
		{0.45, 0.0, 0.5},
		{0.45, 0.0, 0.749},
	};
	glBegin(GL_QUADS);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, desk_diffuse);
	glMaterialfv(GL_FRONT, GL_AMBIENT, desk_ambient);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

	glNormal3fv(calcNormal(mirrorvertices[0], mirrorvertices[1], mirrorvertices[2])); //top
	glVertex3fv(mirrorvertices[0]);
	glVertex3fv(mirrorvertices[1]);
	glVertex3fv(mirrorvertices[2]);
	glVertex3fv(mirrorvertices[3]);

	glNormal3fv(calcNormal(mirrorvertices[1], mirrorvertices[5], mirrorvertices[6]));//front
	glVertex3fv(mirrorvertices[1]);
	glVertex3fv(mirrorvertices[5]);
	glVertex3fv(mirrorvertices[6]);
	glVertex3fv(mirrorvertices[2]);

	glNormal3fv(calcNormal(mirrorvertices[2], mirrorvertices[6], mirrorvertices[7]));//right
	glVertex3fv(mirrorvertices[2]);
	glVertex3fv(mirrorvertices[6]);
	glVertex3fv(mirrorvertices[7]);
	glVertex3fv(mirrorvertices[3]);

	glNormal3fv(calcNormal(mirrorvertices[3], mirrorvertices[7], mirrorvertices[4]));//back
	glVertex3fv(mirrorvertices[3]);
	glVertex3fv(mirrorvertices[7]);
	glVertex3fv(mirrorvertices[4]);
	glVertex3fv(mirrorvertices[0]);

	glNormal3fv(calcNormal(mirrorvertices[0], mirrorvertices[4], mirrorvertices[5]));//left
	glVertex3fv(mirrorvertices[0]);
	glVertex3fv(mirrorvertices[4]);
	glVertex3fv(mirrorvertices[5]);
	glVertex3fv(mirrorvertices[1]);

	glNormal3fv(calcNormal(mirrorvertices[4], mirrorvertices[5], mirrorvertices[6]));//bottom
	glVertex3fv(mirrorvertices[4]);
	glVertex3fv(mirrorvertices[5]);
	glVertex3fv(mirrorvertices[6]);
	glVertex3fv(mirrorvertices[7]);
	glEnd();
	
	GLfloat mirglavertices[][3] = {
		{0.26, 0.785, 0.499},
		{0.42, 0.785, 0.499},
		{0.42, 0.035, 0.499},
		{0.26, 0.035, 0.499}
		};
	glBegin(GL_QUADS);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mirror_diffuse);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mirror_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mirror_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mirror_shiness);
	glNormal3fv(calcNormal(mirglavertices[0], mirglavertices[1], mirglavertices[2])); //top
	glVertex3fv(mirglavertices[0]);
	glVertex3fv(mirglavertices[1]);
	glVertex3fv(mirglavertices[2]);
	glVertex3fv(mirglavertices[3]);
	glEnd();
}

void drawers1() {
	GLfloat lbdrawvertices[][3] = {
		{-0.02, 0.4, 0.749},
		{-0.02, 0.4, 0.73},
		{0.22, 0.4, 0.73},
		{0.22, 0.4, 0.749},
		{-0.02, 0.0, 0.749},
		{-0.02, 0.0, 0.73},
		{0.22, 0.0, 0.73},
		{0.22, 0.0, 0.749},
	};
	//왼쪽서랍장 뒷판
	glBegin(GL_QUADS);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, drawer_diffuse);
	glMaterialfv(GL_FRONT, GL_AMBIENT, drawer_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, drawer_specular);
	
	glNormal3fv(calcNormal(lbdrawvertices[0], lbdrawvertices[1], lbdrawvertices[2])); //top
	glVertex3fv(lbdrawvertices[0]);
	glVertex3fv(lbdrawvertices[1]);
	glVertex3fv(lbdrawvertices[2]);
	glVertex3fv(lbdrawvertices[3]);

	glNormal3fv(calcNormal(lbdrawvertices[1], lbdrawvertices[5], lbdrawvertices[6]));//front
	glVertex3fv(lbdrawvertices[1]);
	glVertex3fv(lbdrawvertices[5]);
	glVertex3fv(lbdrawvertices[6]);
	glVertex3fv(lbdrawvertices[2]);

	glNormal3fv(calcNormal(lbdrawvertices[2], lbdrawvertices[6], lbdrawvertices[7]));//right
	glVertex3fv(lbdrawvertices[2]);
	glVertex3fv(lbdrawvertices[6]);
	glVertex3fv(lbdrawvertices[7]);
	glVertex3fv(lbdrawvertices[3]);

	glNormal3fv(calcNormal(lbdrawvertices[3], lbdrawvertices[7], lbdrawvertices[4]));//back
	glVertex3fv(lbdrawvertices[3]);
	glVertex3fv(lbdrawvertices[7]);
	glVertex3fv(lbdrawvertices[4]);
	glVertex3fv(lbdrawvertices[0]);

	glNormal3fv(calcNormal(lbdrawvertices[0], lbdrawvertices[4], lbdrawvertices[5]));//left
	glVertex3fv(lbdrawvertices[0]);
	glVertex3fv(lbdrawvertices[4]);
	glVertex3fv(lbdrawvertices[5]);
	glVertex3fv(lbdrawvertices[1]);

	glNormal3fv(calcNormal(lbdrawvertices[4], lbdrawvertices[5], lbdrawvertices[6]));//bottom
	glVertex3fv(lbdrawvertices[4]);
	glVertex3fv(lbdrawvertices[5]);
	glVertex3fv(lbdrawvertices[6]);
	glVertex3fv(lbdrawvertices[7]);
	glEnd();

	GLfloat ltopdrawvertices[][3] = {
		{-0.02, 0.4, 0.73},
		{-0.02, 0.4, 0.55},
		{0.22, 0.4, 0.55},
		{0.22, 0.4, 0.73},
		{-0.02, 0.39, 0.73},
		{-0.02, 0.39, 0.55},
		{0.22, 0.39, 0.55},
		{0.22, 0.39, 0.73},
	};

	//왼쪽서랍 맨위
	glBegin(GL_QUADS);
	glNormal3fv(calcNormal(ltopdrawvertices[0], ltopdrawvertices[1], ltopdrawvertices[2])); //top
	glVertex3fv(ltopdrawvertices[0]);
	glVertex3fv(ltopdrawvertices[1]);
	glVertex3fv(ltopdrawvertices[2]);
	glVertex3fv(ltopdrawvertices[3]);

	glNormal3fv(calcNormal(ltopdrawvertices[1], ltopdrawvertices[5], ltopdrawvertices[6]));//front
	glVertex3fv(ltopdrawvertices[1]);
	glVertex3fv(ltopdrawvertices[5]);
	glVertex3fv(ltopdrawvertices[6]);
	glVertex3fv(ltopdrawvertices[2]);

	glNormal3fv(calcNormal(ltopdrawvertices[2], ltopdrawvertices[6], ltopdrawvertices[7]));//right
	glVertex3fv(ltopdrawvertices[2]);
	glVertex3fv(ltopdrawvertices[6]);
	glVertex3fv(ltopdrawvertices[7]);
	glVertex3fv(ltopdrawvertices[3]);

	glNormal3fv(calcNormal(ltopdrawvertices[3], ltopdrawvertices[7], ltopdrawvertices[4]));//back
	glVertex3fv(ltopdrawvertices[3]);
	glVertex3fv(ltopdrawvertices[7]);
	glVertex3fv(ltopdrawvertices[4]);
	glVertex3fv(ltopdrawvertices[0]);

	glNormal3fv(calcNormal(ltopdrawvertices[0], ltopdrawvertices[4], ltopdrawvertices[5]));//left
	glVertex3fv(ltopdrawvertices[0]);
	glVertex3fv(ltopdrawvertices[4]);
	glVertex3fv(ltopdrawvertices[5]);
	glVertex3fv(ltopdrawvertices[1]);

	glNormal3fv(calcNormal(ltopdrawvertices[5], ltopdrawvertices[6], ltopdrawvertices[7]));//bottom
	glVertex3fv(ltopdrawvertices[4]);
	glVertex3fv(ltopdrawvertices[5]);
	glVertex3fv(ltopdrawvertices[6]);
	glVertex3fv(ltopdrawvertices[7]);
	glEnd();

	//왼쪽서랍 3층
	GLfloat l3drawvertices[][3] = {
		{-0.01, 0.27, 0.73},
		{-0.01, 0.27, 0.55},
		{0.22, 0.27, 0.55},
		{0.22, 0.27, 0.73},
		{-0.01, 0.26, 0.73},
		{-0.01, 0.26, 0.55},
		{0.22, 0.26, 0.55},
		{0.22, 0.26, 0.73},
	};
	glBegin(GL_QUADS);
	glNormal3fv(calcNormal(l3drawvertices[0], l3drawvertices[1], l3drawvertices[2])); //top
	glVertex3fv(l3drawvertices[0]);
	glVertex3fv(l3drawvertices[1]);
	glVertex3fv(l3drawvertices[2]);
	glVertex3fv(l3drawvertices[3]);

	glNormal3fv(calcNormal(l3drawvertices[1], l3drawvertices[5], l3drawvertices[6]));//front
	glVertex3fv(l3drawvertices[1]);
	glVertex3fv(l3drawvertices[5]);
	glVertex3fv(l3drawvertices[6]);
	glVertex3fv(l3drawvertices[2]);

	glNormal3fv(calcNormal(l3drawvertices[2], l3drawvertices[6], l3drawvertices[7]));//right
	glVertex3fv(l3drawvertices[2]);
	glVertex3fv(l3drawvertices[6]);
	glVertex3fv(l3drawvertices[7]);
	glVertex3fv(l3drawvertices[3]);

	glNormal3fv(calcNormal(l3drawvertices[3], l3drawvertices[7], l3drawvertices[4]));//back
	glVertex3fv(l3drawvertices[3]);
	glVertex3fv(l3drawvertices[7]);
	glVertex3fv(l3drawvertices[4]);
	glVertex3fv(l3drawvertices[0]);

	glNormal3fv(calcNormal(l3drawvertices[0], l3drawvertices[4], l3drawvertices[5]));//left
	glVertex3fv(l3drawvertices[0]);
	glVertex3fv(l3drawvertices[4]);
	glVertex3fv(l3drawvertices[5]);
	glVertex3fv(l3drawvertices[1]);

	glNormal3fv(calcNormal(l3drawvertices[5], l3drawvertices[6], l3drawvertices[7]));//bottom
	glVertex3fv(l3drawvertices[4]);
	glVertex3fv(l3drawvertices[5]);
	glVertex3fv(l3drawvertices[6]);
	glVertex3fv(l3drawvertices[7]);
	glEnd();

	//왼쪽서랍 2층
	GLfloat l2drawvertices[][3] = {
		{-0.01, 0.14, 0.73},
		{-0.01, 0.14, 0.55},
		{0.22, 0.14, 0.55},
		{0.22, 0.14, 0.73},
		{-0.01, 0.13, 0.73},
		{-0.01, 0.13, 0.55},
		{0.22, 0.13, 0.55},
		{0.22, 0.13, 0.73}
	};
	glBegin(GL_QUADS);
	glNormal3fv(calcNormal(l2drawvertices[0], l2drawvertices[1], l2drawvertices[2])); //top
	glVertex3fv(l2drawvertices[0]);
	glVertex3fv(l2drawvertices[1]);
	glVertex3fv(l2drawvertices[2]);
	glVertex3fv(l2drawvertices[3]);

	glNormal3fv(calcNormal(l2drawvertices[1], l2drawvertices[5], l2drawvertices[6]));//front
	glVertex3fv(l2drawvertices[1]);
	glVertex3fv(l2drawvertices[5]);
	glVertex3fv(l2drawvertices[6]);
	glVertex3fv(l2drawvertices[2]);

	glNormal3fv(calcNormal(l2drawvertices[2], l2drawvertices[6], l2drawvertices[7]));//right
	glVertex3fv(l2drawvertices[2]);
	glVertex3fv(l2drawvertices[6]);
	glVertex3fv(l2drawvertices[7]);
	glVertex3fv(l2drawvertices[3]);

	glNormal3fv(calcNormal(l2drawvertices[3], l2drawvertices[7], l2drawvertices[4]));//back
	glVertex3fv(l2drawvertices[3]);
	glVertex3fv(l2drawvertices[7]);
	glVertex3fv(l2drawvertices[4]);
	glVertex3fv(l2drawvertices[0]);

	glNormal3fv(calcNormal(l2drawvertices[0], l2drawvertices[4], l2drawvertices[5]));//left
	glVertex3fv(l2drawvertices[0]);
	glVertex3fv(l2drawvertices[4]);
	glVertex3fv(l2drawvertices[5]);
	glVertex3fv(l2drawvertices[1]);

	glNormal3fv(calcNormal(l2drawvertices[5], l2drawvertices[6], l2drawvertices[7]));//bottom
	glVertex3fv(l2drawvertices[4]);
	glVertex3fv(l2drawvertices[5]);
	glVertex3fv(l2drawvertices[6]);
	glVertex3fv(l2drawvertices[7]);
	glEnd();

	//왼쪽서랍 바닥
	GLfloat lcdrawvertices[][3] = {
		{-0.02, 0.01, 0.73},
		{-0.02, 0.01, 0.55},
		{0.22, 0.01, 0.55},
		{0.22, 0.01, 0.73},
		{-0.02, 0.0, 0.73},
		{-0.02, 0.0, 0.55},
		{0.22, 0.0, 0.55},
		{0.22, 0.0, 0.73}
	};
	glBegin(GL_QUADS);
	glNormal3fv(calcNormal(lcdrawvertices[0], lcdrawvertices[1], lcdrawvertices[2])); //top
	glVertex3fv(lcdrawvertices[0]);
	glVertex3fv(lcdrawvertices[1]);
	glVertex3fv(lcdrawvertices[2]);
	glVertex3fv(lcdrawvertices[3]);

	glNormal3fv(calcNormal(lcdrawvertices[1], lcdrawvertices[5], lcdrawvertices[6]));//front
	glVertex3fv(lcdrawvertices[1]);
	glVertex3fv(lcdrawvertices[5]);
	glVertex3fv(lcdrawvertices[6]);
	glVertex3fv(lcdrawvertices[2]);

	glNormal3fv(calcNormal(lcdrawvertices[2], lcdrawvertices[6], lcdrawvertices[7]));//right
	glVertex3fv(lcdrawvertices[2]);
	glVertex3fv(lcdrawvertices[6]);
	glVertex3fv(lcdrawvertices[7]);
	glVertex3fv(lcdrawvertices[3]);

	glNormal3fv(calcNormal(lcdrawvertices[3], lcdrawvertices[7], lcdrawvertices[4]));//back
	glVertex3fv(lcdrawvertices[3]);
	glVertex3fv(lcdrawvertices[7]);
	glVertex3fv(lcdrawvertices[4]);
	glVertex3fv(lcdrawvertices[0]);

	glNormal3fv(calcNormal(lcdrawvertices[0], lcdrawvertices[4], lcdrawvertices[5]));//left
	glVertex3fv(lcdrawvertices[0]);
	glVertex3fv(lcdrawvertices[4]);
	glVertex3fv(lcdrawvertices[5]);
	glVertex3fv(lcdrawvertices[1]);

	glNormal3fv(calcNormal(lcdrawvertices[5], lcdrawvertices[6], lcdrawvertices[7]));//bottom
	glVertex3fv(lcdrawvertices[4]);
	glVertex3fv(lcdrawvertices[5]);
	glVertex3fv(lcdrawvertices[6]);
	glVertex3fv(lcdrawvertices[7]);
	glEnd();

	//왼쪽서랍 왼쪽벽
	GLfloat lldrawvertices[][3] = {
		{0.22, 0.4, 0.7495},
		{0.22, 0.4, 0.55},
		{0.23, 0.4, 0.55},
		{0.23, 0.4, 0.7495},
		{0.22, 0.0, 0.7495},
		{0.22, 0.0, 0.55},
		{0.23, 0.0, 0.55},
		{0.23, 0.0, 0.7495},
	};
	glBegin(GL_QUADS);
	glNormal3fv(calcNormal(lldrawvertices[0], lldrawvertices[1], lldrawvertices[2])); //top
	glVertex3fv(lldrawvertices[0]);
	glVertex3fv(lldrawvertices[1]);
	glVertex3fv(lldrawvertices[2]);
	glVertex3fv(lldrawvertices[3]);

	glNormal3fv(calcNormal(lldrawvertices[1], lldrawvertices[5], lldrawvertices[6]));//front
	glVertex3fv(lldrawvertices[1]);
	glVertex3fv(lldrawvertices[5]);
	glVertex3fv(lldrawvertices[6]);
	glVertex3fv(lldrawvertices[2]);

	glNormal3fv(calcNormal(lldrawvertices[2], lldrawvertices[6], lldrawvertices[7]));//right
	glVertex3fv(lldrawvertices[2]);
	glVertex3fv(lldrawvertices[6]);
	glVertex3fv(lldrawvertices[7]);
	glVertex3fv(lldrawvertices[3]);

	glNormal3fv(calcNormal(lldrawvertices[3], lldrawvertices[7], lldrawvertices[4]));//back
	glVertex3fv(lldrawvertices[3]);
	glVertex3fv(lldrawvertices[7]);
	glVertex3fv(lldrawvertices[4]);
	glVertex3fv(lldrawvertices[0]);

	glNormal3fv(calcNormal(lldrawvertices[0], lldrawvertices[4], lldrawvertices[5]));//left
	glVertex3fv(lldrawvertices[0]);
	glVertex3fv(lldrawvertices[4]);
	glVertex3fv(lldrawvertices[5]);
	glVertex3fv(lldrawvertices[1]);

	glNormal3fv(calcNormal(lldrawvertices[5], lldrawvertices[6], lldrawvertices[7]));//bottom
	glVertex3fv(lldrawvertices[4]);
	glVertex3fv(lldrawvertices[5]);
	glVertex3fv(lldrawvertices[6]);
	glVertex3fv(lldrawvertices[7]);
	glEnd();

	//왼쪽서랍 오른쪽벽
	GLfloat lrdrawvertices[][3] = {
		{-0.02, 0.4, 0.7495},
		{-0.02, 0.4, 0.55},
		{-0.01, 0.4, 0.7495},
		{-0.01, 0.4, 0.55},
		{-0.02, 0.0, 0.7495},
		{-0.02, 0.0, 0.55},
		{-0.01, 0.0, 0.7495},
		{-0.01, 0.0, 0.55}
	};
	glBegin(GL_QUADS);
	glNormal3fv(calcNormal(lrdrawvertices[0], lrdrawvertices[1], lrdrawvertices[2])); //top
	glVertex3fv(lrdrawvertices[0]);
	glVertex3fv(lrdrawvertices[1]);
	glVertex3fv(lrdrawvertices[2]);
	glVertex3fv(lrdrawvertices[3]);

	glNormal3fv(calcNormal(lrdrawvertices[1], lrdrawvertices[5], lrdrawvertices[6]));//front
	glVertex3fv(lrdrawvertices[1]);
	glVertex3fv(lrdrawvertices[5]);
	glVertex3fv(lrdrawvertices[6]);
	glVertex3fv(lrdrawvertices[2]);

	glNormal3fv(calcNormal(lrdrawvertices[2], lrdrawvertices[6], lrdrawvertices[7]));//right
	glVertex3fv(lrdrawvertices[2]);
	glVertex3fv(lrdrawvertices[6]);
	glVertex3fv(lrdrawvertices[7]);
	glVertex3fv(lrdrawvertices[3]);

	glNormal3fv(calcNormal(lrdrawvertices[3], lrdrawvertices[7], lrdrawvertices[4]));//back
	glVertex3fv(lrdrawvertices[3]);
	glVertex3fv(lrdrawvertices[7]);
	glVertex3fv(lrdrawvertices[4]);
	glVertex3fv(lrdrawvertices[0]);

	glNormal3fv(calcNormal(lrdrawvertices[0], lrdrawvertices[4], lrdrawvertices[5]));//left
	glVertex3fv(lrdrawvertices[0]);
	glVertex3fv(lrdrawvertices[4]);
	glVertex3fv(lrdrawvertices[5]);
	glVertex3fv(lrdrawvertices[1]);

	glNormal3fv(calcNormal(lrdrawvertices[5], lrdrawvertices[6], lrdrawvertices[7]));//bottom
	glVertex3fv(lrdrawvertices[4]);
	glVertex3fv(lrdrawvertices[5]);
	glVertex3fv(lrdrawvertices[6]);
	glVertex3fv(lrdrawvertices[7]);
	glEnd();
}

void drawers2() {

	//오른쪽서랍장 뒷판
	GLfloat rbdrawvertices[][3] = {
		{-0.27, 0.4, 0.749},
		{-0.27, 0.4, 0.73},
		{-0.04, 0.4, 0.73},
		{-0.04, 0.4, 0.749},
		{-0.27, 0.0, 0.749},
		{-0.27, 0.0, 0.73},
		{-0.04, 0.0, 0.73},
		{-0.04, 0.0, 0.749},
	};

	glBegin(GL_QUADS);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, drawer_diffuse);
	glMaterialfv(GL_FRONT, GL_AMBIENT, drawer_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, drawer_specular);
	
	glNormal3fv(calcNormal(rbdrawvertices[0], rbdrawvertices[1], rbdrawvertices[2])); //top
	glVertex3fv(rbdrawvertices[0]);
	glVertex3fv(rbdrawvertices[1]);
	glVertex3fv(rbdrawvertices[2]);
	glVertex3fv(rbdrawvertices[3]);

	glNormal3fv(calcNormal(rbdrawvertices[1], rbdrawvertices[5], rbdrawvertices[6]));//front
	glVertex3fv(rbdrawvertices[1]);
	glVertex3fv(rbdrawvertices[5]);
	glVertex3fv(rbdrawvertices[6]);
	glVertex3fv(rbdrawvertices[2]);

	glNormal3fv(calcNormal(rbdrawvertices[2], rbdrawvertices[6], rbdrawvertices[7]));//right
	glVertex3fv(rbdrawvertices[2]);
	glVertex3fv(rbdrawvertices[6]);
	glVertex3fv(rbdrawvertices[7]);
	glVertex3fv(rbdrawvertices[3]);

	glNormal3fv(calcNormal(rbdrawvertices[3], rbdrawvertices[7], rbdrawvertices[4]));//back
	glVertex3fv(rbdrawvertices[3]);
	glVertex3fv(rbdrawvertices[7]);
	glVertex3fv(rbdrawvertices[4]);
	glVertex3fv(rbdrawvertices[0]);

	glNormal3fv(calcNormal(rbdrawvertices[0], rbdrawvertices[4], rbdrawvertices[5]));//left
	glVertex3fv(rbdrawvertices[0]);
	glVertex3fv(rbdrawvertices[4]);
	glVertex3fv(rbdrawvertices[5]);
	glVertex3fv(rbdrawvertices[1]);

	glNormal3fv(calcNormal(rbdrawvertices[5], rbdrawvertices[6], rbdrawvertices[7]));//bottom
	glVertex3fv(rbdrawvertices[4]);
	glVertex3fv(rbdrawvertices[5]);
	glVertex3fv(rbdrawvertices[6]);
	glVertex3fv(rbdrawvertices[7]);
	glEnd();

	//왼쪽서랍 맨위
	GLfloat rtopdrawvertices[][3] = {
	{-0.27, 0.4, 0.73},
	{-0.27, 0.4, 0.55},
	{-0.04, 0.4, 0.55},
	{-0.04, 0.4, 0.73},
	{-0.27, 0.39, 0.73},
	{-0.27, 0.39, 0.55},
	{-0.04, 0.39, 0.55},
	{-0.04, 0.39, 0.73},
	};

	glBegin(GL_QUADS);
	glNormal3fv(calcNormal(rtopdrawvertices[0], rtopdrawvertices[1], rtopdrawvertices[2])); //top
	glVertex3fv(rtopdrawvertices[0]);
	glVertex3fv(rtopdrawvertices[1]);
	glVertex3fv(rtopdrawvertices[2]);
	glVertex3fv(rtopdrawvertices[3]);

	glNormal3fv(calcNormal(rtopdrawvertices[1], rtopdrawvertices[5], rtopdrawvertices[6]));//front
	glVertex3fv(rtopdrawvertices[1]);
	glVertex3fv(rtopdrawvertices[5]);
	glVertex3fv(rtopdrawvertices[6]);
	glVertex3fv(rtopdrawvertices[2]);

	glNormal3fv(calcNormal(rtopdrawvertices[2], rtopdrawvertices[6], rtopdrawvertices[7]));//right
	glVertex3fv(rtopdrawvertices[2]);
	glVertex3fv(rtopdrawvertices[6]);
	glVertex3fv(rtopdrawvertices[7]);
	glVertex3fv(rtopdrawvertices[3]);

	glNormal3fv(calcNormal(rtopdrawvertices[3], rtopdrawvertices[7], rtopdrawvertices[4]));//back
	glVertex3fv(rtopdrawvertices[3]);
	glVertex3fv(rtopdrawvertices[7]);
	glVertex3fv(rtopdrawvertices[4]);
	glVertex3fv(rtopdrawvertices[0]);

	glNormal3fv(calcNormal(rtopdrawvertices[0], rtopdrawvertices[4], rtopdrawvertices[5]));//left
	glVertex3fv(rtopdrawvertices[0]);
	glVertex3fv(rtopdrawvertices[4]);
	glVertex3fv(rtopdrawvertices[5]);
	glVertex3fv(rtopdrawvertices[1]);

	glNormal3fv(calcNormal(rtopdrawvertices[5], rtopdrawvertices[6], rtopdrawvertices[7]));//bottom
	glVertex3fv(rtopdrawvertices[4]);
	glVertex3fv(rtopdrawvertices[5]);
	glVertex3fv(rtopdrawvertices[6]);
	glVertex3fv(rtopdrawvertices[7]);
	glEnd();


	//오른쪽서랍 3층
	GLfloat r3drawvertices[][3] = {
		{-0.27, 0.27, 0.73},
		{-0.27, 0.27, 0.55},
		{-0.04, 0.27, 0.55},
		{-0.04, 0.27, 0.73},
		{-0.27, 0.26, 0.73},
		{-0.27, 0.26, 0.55},
		{-0.04, 0.26, 0.55},
		{-0.04, 0.26, 0.73},
	};

	glBegin(GL_QUADS);
	glNormal3fv(calcNormal(r3drawvertices[0], r3drawvertices[1], r3drawvertices[2])); //top
	glVertex3fv(r3drawvertices[0]);
	glVertex3fv(r3drawvertices[1]);
	glVertex3fv(r3drawvertices[2]);
	glVertex3fv(r3drawvertices[3]);

	glNormal3fv(calcNormal(r3drawvertices[1], r3drawvertices[5], r3drawvertices[6]));//front
	glVertex3fv(r3drawvertices[1]);
	glVertex3fv(r3drawvertices[5]);
	glVertex3fv(r3drawvertices[6]);
	glVertex3fv(r3drawvertices[2]);

	glNormal3fv(calcNormal(r3drawvertices[2], r3drawvertices[6], r3drawvertices[7]));//right
	glVertex3fv(r3drawvertices[2]);
	glVertex3fv(r3drawvertices[6]);
	glVertex3fv(r3drawvertices[7]);
	glVertex3fv(r3drawvertices[3]);

	glNormal3fv(calcNormal(r3drawvertices[3], r3drawvertices[7], r3drawvertices[4]));//back
	glVertex3fv(r3drawvertices[3]);
	glVertex3fv(r3drawvertices[7]);
	glVertex3fv(r3drawvertices[4]);
	glVertex3fv(r3drawvertices[0]);

	glNormal3fv(calcNormal(r3drawvertices[0], r3drawvertices[4], r3drawvertices[5]));//left
	glVertex3fv(r3drawvertices[0]);
	glVertex3fv(r3drawvertices[4]);
	glVertex3fv(r3drawvertices[5]);
	glVertex3fv(r3drawvertices[1]);

	glNormal3fv(calcNormal(r3drawvertices[5], r3drawvertices[6], r3drawvertices[7]));//bottom
	glVertex3fv(r3drawvertices[4]);
	glVertex3fv(r3drawvertices[5]);
	glVertex3fv(r3drawvertices[6]);
	glVertex3fv(r3drawvertices[7]);
	glEnd();

	//왼쪽서랍 2층
	GLfloat r2drawvertices[][3] = {
		{-0.27, 0.14, 0.73},
		{-0.27, 0.14, 0.55},
		{-0.04, 0.14, 0.55},
		{-0.04, 0.14, 0.73},
		{-0.27, 0.13, 0.73},
		{-0.27, 0.13, 0.55},
		{-0.04, 0.13, 0.55},
		{-0.04, 0.13, 0.73}
	};

	glBegin(GL_QUADS);
	glNormal3fv(calcNormal(r2drawvertices[0], r2drawvertices[1], r2drawvertices[2])); //top
	glVertex3fv(r2drawvertices[0]);
	glVertex3fv(r2drawvertices[1]);
	glVertex3fv(r2drawvertices[2]);
	glVertex3fv(r2drawvertices[3]);

	glNormal3fv(calcNormal(r2drawvertices[1], r2drawvertices[5], r2drawvertices[6]));//front
	glVertex3fv(r2drawvertices[1]);
	glVertex3fv(r2drawvertices[5]);
	glVertex3fv(r2drawvertices[6]);
	glVertex3fv(r2drawvertices[2]);

	glNormal3fv(calcNormal(r2drawvertices[2], r2drawvertices[6], r2drawvertices[7]));//right
	glVertex3fv(r2drawvertices[2]);
	glVertex3fv(r2drawvertices[6]);
	glVertex3fv(r2drawvertices[7]);
	glVertex3fv(r2drawvertices[3]);

	glNormal3fv(calcNormal(r2drawvertices[3], r2drawvertices[7], r2drawvertices[4]));//back
	glVertex3fv(r2drawvertices[3]);
	glVertex3fv(r2drawvertices[7]);
	glVertex3fv(r2drawvertices[4]);
	glVertex3fv(r2drawvertices[0]);

	glNormal3fv(calcNormal(r2drawvertices[0], r2drawvertices[4], r2drawvertices[5]));//left
	glVertex3fv(r2drawvertices[0]);
	glVertex3fv(r2drawvertices[4]);
	glVertex3fv(r2drawvertices[5]);
	glVertex3fv(r2drawvertices[1]);

	glNormal3fv(calcNormal(r2drawvertices[5], r2drawvertices[6], r2drawvertices[7]));//bottom
	glVertex3fv(r2drawvertices[4]);
	glVertex3fv(r2drawvertices[5]);
	glVertex3fv(r2drawvertices[6]);
	glVertex3fv(r2drawvertices[7]);
	glEnd();

	//왼쪽서랍 바닥
	GLfloat rcdrawvertices[][3] = {
		{-0.27, 0.01, 0.73},
		{-0.27, 0.01, 0.55},
		{-0.04, 0.01, 0.55},
		{-0.04, 0.01, 0.73},
		{-0.27, 0.0, 0.73},
		{-0.27, 0.0, 0.55},
		{-0.04, 0.0, 0.55},
		{-0.04, 0.0, 0.73}
	};

	glBegin(GL_QUADS);
	glNormal3fv(calcNormal(rcdrawvertices[0], rcdrawvertices[1], rcdrawvertices[2])); //top
	glVertex3fv(rcdrawvertices[0]);
	glVertex3fv(rcdrawvertices[1]);
	glVertex3fv(rcdrawvertices[2]);
	glVertex3fv(rcdrawvertices[3]);

	glNormal3fv(calcNormal(rcdrawvertices[1], rcdrawvertices[5], rcdrawvertices[6]));//front
	glVertex3fv(rcdrawvertices[1]);
	glVertex3fv(rcdrawvertices[5]);
	glVertex3fv(rcdrawvertices[6]);
	glVertex3fv(rcdrawvertices[2]);

	glNormal3fv(calcNormal(rcdrawvertices[2], rcdrawvertices[6], rcdrawvertices[7]));//right
	glVertex3fv(rcdrawvertices[2]);
	glVertex3fv(rcdrawvertices[6]);
	glVertex3fv(rcdrawvertices[7]);
	glVertex3fv(rcdrawvertices[3]);

	glNormal3fv(calcNormal(rcdrawvertices[3], rcdrawvertices[7], rcdrawvertices[4]));//back
	glVertex3fv(rcdrawvertices[3]);
	glVertex3fv(rcdrawvertices[7]);
	glVertex3fv(rcdrawvertices[4]);
	glVertex3fv(rcdrawvertices[0]);

	glNormal3fv(calcNormal(rcdrawvertices[0], rcdrawvertices[4], rcdrawvertices[5]));//left
	glVertex3fv(rcdrawvertices[0]);
	glVertex3fv(rcdrawvertices[4]);
	glVertex3fv(rcdrawvertices[5]);
	glVertex3fv(rcdrawvertices[1]);

	glNormal3fv(calcNormal(rcdrawvertices[5], rcdrawvertices[6], rcdrawvertices[7]));//bottom
	glVertex3fv(rcdrawvertices[4]);
	glVertex3fv(rcdrawvertices[5]);
	glVertex3fv(rcdrawvertices[6]);
	glVertex3fv(rcdrawvertices[7]);
	glEnd();

	//왼쪽서랍 왼쪽벽
	GLfloat rldrawvertices[][3] = {
		{-0.04, 0.4, 0.7495},
		{-0.04, 0.4, 0.55},
		{-0.03, 0.4, 0.55},
		{-0.03, 0.4, 0.7495},
		{-0.04, 0.0, 0.7495},
		{-0.04, 0.0, 0.55},
		{-0.03, 0.0, 0.55},
		{-0.03, 0.0, 0.7495},
	};

	glBegin(GL_QUADS);
	glNormal3fv(calcNormal(rldrawvertices[0], rldrawvertices[1], rldrawvertices[2])); //top
	glVertex3fv(rldrawvertices[0]);
	glVertex3fv(rldrawvertices[1]);
	glVertex3fv(rldrawvertices[2]);
	glVertex3fv(rldrawvertices[3]);

	glNormal3fv(calcNormal(rldrawvertices[1], rldrawvertices[5], rldrawvertices[6]));//front
	glVertex3fv(rldrawvertices[1]);
	glVertex3fv(rldrawvertices[5]);
	glVertex3fv(rldrawvertices[6]);
	glVertex3fv(rldrawvertices[2]);

	glNormal3fv(calcNormal(rldrawvertices[2], rldrawvertices[6], rldrawvertices[7]));//right
	glVertex3fv(rldrawvertices[2]);
	glVertex3fv(rldrawvertices[6]);
	glVertex3fv(rldrawvertices[7]);
	glVertex3fv(rldrawvertices[3]);

	glNormal3fv(calcNormal(rldrawvertices[3], rldrawvertices[7], rldrawvertices[4]));//back
	glVertex3fv(rldrawvertices[3]);
	glVertex3fv(rldrawvertices[7]);
	glVertex3fv(rldrawvertices[4]);
	glVertex3fv(rldrawvertices[0]);

	glNormal3fv(calcNormal(rldrawvertices[0], rldrawvertices[4], rldrawvertices[5]));//left
	glVertex3fv(rldrawvertices[0]);
	glVertex3fv(rldrawvertices[4]);
	glVertex3fv(rldrawvertices[5]);
	glVertex3fv(rldrawvertices[1]);

	glNormal3fv(calcNormal(rldrawvertices[5], rldrawvertices[6], rldrawvertices[7]));//bottom
	glVertex3fv(rldrawvertices[4]);
	glVertex3fv(rldrawvertices[5]);
	glVertex3fv(rldrawvertices[6]);
	glVertex3fv(rldrawvertices[7]);
	glEnd();

	//오른쪽서랍 오른쪽벽
	GLfloat rrdrawvertices[][3] = {
		{-0.28, 0.4, 0.7495},
		{-0.28, 0.4, 0.55},
		{-0.27, 0.4, 0.55},
		{-0.27, 0.4, 0.7495},
		{-0.28, 0.0, 0.7495},
		{-0.28, 0.0, 0.55},
		{-0.27, 0.0, 0.55},
		{-0.27, 0.0, 0.7495}
	};

	glBegin(GL_QUADS);
	glNormal3fv(calcNormal(rrdrawvertices[0], rrdrawvertices[1], rrdrawvertices[2])); //top
	glVertex3fv(rrdrawvertices[0]);
	glVertex3fv(rrdrawvertices[1]);
	glVertex3fv(rrdrawvertices[2]);
	glVertex3fv(rrdrawvertices[3]);

	glNormal3fv(calcNormal(rrdrawvertices[1], rrdrawvertices[5], rrdrawvertices[6]));//front
	glVertex3fv(rrdrawvertices[1]);
	glVertex3fv(rrdrawvertices[5]);
	glVertex3fv(rrdrawvertices[6]);
	glVertex3fv(rrdrawvertices[2]);

	glNormal3fv(calcNormal(rrdrawvertices[2], rrdrawvertices[6], rrdrawvertices[7]));//right
	glVertex3fv(rrdrawvertices[2]);
	glVertex3fv(rrdrawvertices[6]);
	glVertex3fv(rrdrawvertices[7]);
	glVertex3fv(rrdrawvertices[3]);

	glNormal3fv(calcNormal(rrdrawvertices[3], rrdrawvertices[7], rrdrawvertices[4]));//back
	glVertex3fv(rrdrawvertices[3]);
	glVertex3fv(rrdrawvertices[7]);
	glVertex3fv(rrdrawvertices[4]);
	glVertex3fv(rrdrawvertices[0]);

	glNormal3fv(calcNormal(rrdrawvertices[0], rrdrawvertices[4], rrdrawvertices[5]));//left
	glVertex3fv(rrdrawvertices[0]);
	glVertex3fv(rrdrawvertices[4]);
	glVertex3fv(rrdrawvertices[5]);
	glVertex3fv(rrdrawvertices[1]);

	glNormal3fv(calcNormal(rrdrawvertices[5], rrdrawvertices[6], rrdrawvertices[7]));//bottom
	glVertex3fv(rrdrawvertices[4]);
	glVertex3fv(rrdrawvertices[5]);
	glVertex3fv(rrdrawvertices[6]);
	glVertex3fv(rrdrawvertices[7]);
	glEnd();

}

void drawdesk() {
	GLfloat deskvertices1[][3] = {
		{-1.0, 0.3125, 0.7495},
		{-1.0, 0.3125, 0.5},
		{-0.3, 0.3125, 0.5},
		{-0.3, 0.3125, 0.7495},
		{-1.0, 0.2875, 0.7495},
		{-1.0, 0.2875, 0.5},
		{-0.3, 0.2875, 0.5},
		{-0.3, 0.2875, 0.7495},
	};
	//책상본
	glBegin(GL_QUADS);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, desk_diffuse);
	glMaterialfv(GL_FRONT, GL_AMBIENT, desk_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, desk_specular);
	glNormal3fv(calcNormal(deskvertices1[0], deskvertices1[1], deskvertices1[2])); //top
	glVertex3fv(deskvertices1[0]);
	glVertex3fv(deskvertices1[1]);
	glVertex3fv(deskvertices1[2]);
	glVertex3fv(deskvertices1[3]);

	glNormal3fv(calcNormal(deskvertices1[1], deskvertices1[5], deskvertices1[6]));//front
	glVertex3fv(deskvertices1[1]);
	glVertex3fv(deskvertices1[5]);
	glVertex3fv(deskvertices1[6]);
	glVertex3fv(deskvertices1[2]);

	glNormal3fv(calcNormal(deskvertices1[2], deskvertices1[6], deskvertices1[7]));//right
	glVertex3fv(deskvertices1[2]);
	glVertex3fv(deskvertices1[6]);
	glVertex3fv(deskvertices1[7]);
	glVertex3fv(deskvertices1[3]);

	glNormal3fv(calcNormal(deskvertices1[3], deskvertices1[7], deskvertices1[4]));//back
	glVertex3fv(deskvertices1[3]);
	glVertex3fv(deskvertices1[7]);
	glVertex3fv(deskvertices1[4]);
	glVertex3fv(deskvertices1[0]);

	glNormal3fv(calcNormal(deskvertices1[0], deskvertices1[4], deskvertices1[5]));//left
	glVertex3fv(deskvertices1[0]);
	glVertex3fv(deskvertices1[4]);
	glVertex3fv(deskvertices1[5]);
	glVertex3fv(deskvertices1[1]);

	glNormal3fv(calcNormal(deskvertices1[4], deskvertices1[5], deskvertices1[6]));//bottom
	glVertex3fv(deskvertices1[4]);
	glVertex3fv(deskvertices1[5]);
	glVertex3fv(deskvertices1[6]);
	glVertex3fv(deskvertices1[7]);
	glEnd();

	//책상옆구리
	GLfloat deskvertices2[][3] = {
		{-1.2, 0.3125, 0.7495},
		{-1.2, 0.3125, 0.35},
		{-1.0, 0.3125, 0.35},
		{-1.0, 0.3125, 0.7495},
		{-1.2, 0.2875, 0.7495},
		{-1.2, 0.2875, 0.35},
		{-1.0, 0.2875, 0.35},
		{-1.0, 0.2875, 0.7495},
	};
	glBegin(GL_QUADS);
	glNormal3fv(calcNormal(deskvertices2[0], deskvertices2[1], deskvertices2[2])); //top
	glVertex3fv(deskvertices2[0]);
	glVertex3fv(deskvertices2[1]);
	glVertex3fv(deskvertices2[2]);
	glVertex3fv(deskvertices2[3]);

	glNormal3fv(calcNormal(deskvertices2[1], deskvertices2[5], deskvertices2[6]));//front
	glVertex3fv(deskvertices2[1]);
	glVertex3fv(deskvertices2[5]);
	glVertex3fv(deskvertices2[6]);
	glVertex3fv(deskvertices2[2]);

	glNormal3fv(calcNormal(deskvertices2[2], deskvertices2[6], deskvertices2[7]));//right
	glVertex3fv(deskvertices2[2]);
	glVertex3fv(deskvertices2[6]);
	glVertex3fv(deskvertices2[7]);
	glVertex3fv(deskvertices2[3]);

	glNormal3fv(calcNormal(deskvertices2[3], deskvertices2[7], deskvertices2[4]));//back
	glVertex3fv(deskvertices2[3]);
	glVertex3fv(deskvertices2[7]);
	glVertex3fv(deskvertices2[4]);
	glVertex3fv(deskvertices2[0]);

	glNormal3fv(calcNormal(deskvertices2[0], deskvertices2[4], deskvertices2[5]));//left
	glVertex3fv(deskvertices2[0]);
	glVertex3fv(deskvertices2[4]);
	glVertex3fv(deskvertices2[5]);
	glVertex3fv(deskvertices2[1]);

	glNormal3fv(calcNormal(deskvertices2[4], deskvertices2[5], deskvertices2[6]));//bottom
	glVertex3fv(deskvertices2[4]);
	glVertex3fv(deskvertices2[5]);
	glVertex3fv(deskvertices2[6]);
	glVertex3fv(deskvertices2[7]);
	glEnd();

	//왼쪽 앞다리
	GLfloat leg1vertices[][3] = {
		{-0.365, 0.2874, 0.545},
		{-0.365, 0.2874, 0.515},
		{-0.335, 0.2874, 0.515},
		{-0.335, 0.2874, 0.545},
		{-0.365, 0.0, 0.545},
		{-0.365, 0.0, 0.515},
		{-0.335, 0.0, 0.515},
		{-0.335, 0.0, 0.545},
	};
	glBegin(GL_QUADS);

	glMaterialfv(GL_FRONT, GL_DIFFUSE, desk2_diffuse);
	glMaterialfv(GL_FRONT, GL_AMBIENT, desk2_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, desk2_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, desk2_shinness);

	glNormal3fv(calcNormal(leg1vertices[0], leg1vertices[1], leg1vertices[2])); //top
	glVertex3fv(leg1vertices[0]);
	glVertex3fv(leg1vertices[1]);
	glVertex3fv(leg1vertices[2]);
	glVertex3fv(leg1vertices[3]);

	glNormal3fv(calcNormal(leg1vertices[1], leg1vertices[5], leg1vertices[6]));//front
	glVertex3fv(leg1vertices[1]);
	glVertex3fv(leg1vertices[5]);
	glVertex3fv(leg1vertices[6]);
	glVertex3fv(leg1vertices[2]);

	glNormal3fv(calcNormal(leg1vertices[2], leg1vertices[6], leg1vertices[7]));//right
	glVertex3fv(leg1vertices[2]);
	glVertex3fv(leg1vertices[6]);
	glVertex3fv(leg1vertices[7]);
	glVertex3fv(leg1vertices[3]);

	glNormal3fv(calcNormal(leg1vertices[3], leg1vertices[7], leg1vertices[4]));//back
	glVertex3fv(leg1vertices[3]);
	glVertex3fv(leg1vertices[7]);
	glVertex3fv(leg1vertices[4]);
	glVertex3fv(leg1vertices[0]);

	glNormal3fv(calcNormal(leg1vertices[0], leg1vertices[4], leg1vertices[5]));//left
	glVertex3fv(leg1vertices[0]);
	glVertex3fv(leg1vertices[4]);
	glVertex3fv(leg1vertices[5]);
	glVertex3fv(leg1vertices[1]);

	glNormal3fv(calcNormal(leg1vertices[4], leg1vertices[5], leg1vertices[6]));//bottom
	glVertex3fv(leg1vertices[4]);
	glVertex3fv(leg1vertices[5]);
	glVertex3fv(leg1vertices[6]);
	glVertex3fv(leg1vertices[7]);
	glEnd();


	//왼쪽뒷다리
	GLfloat leg2vertices[][3] = { 
		{-0.365, 0.2874, 0.735},
		{-0.365, 0.2874, 0.705},
		{-0.335, 0.2874, 0.705},
		{-0.335, 0.2874, 0.735},
		{-0.365, 0.0, 0.735},
		{-0.365, 0.0, 0.705},
		{-0.335, 0.0, 0.705},
		{-0.335, 0.0, 0.735},
	}; 
	glBegin(GL_QUADS);
	glNormal3fv(calcNormal(leg2vertices[0], leg2vertices[1], leg2vertices[2])); //top
	glVertex3fv(leg2vertices[0]);
	glVertex3fv(leg2vertices[1]);
	glVertex3fv(leg2vertices[2]);
	glVertex3fv(leg2vertices[3]);

	glNormal3fv(calcNormal(leg2vertices[1], leg2vertices[5], leg2vertices[6]));//front
	glVertex3fv(leg2vertices[1]);
	glVertex3fv(leg2vertices[5]);
	glVertex3fv(leg2vertices[6]);
	glVertex3fv(leg2vertices[2]);

	glNormal3fv(calcNormal(leg2vertices[2], leg2vertices[6], leg2vertices[7]));//right
	glVertex3fv(leg2vertices[2]);
	glVertex3fv(leg2vertices[6]);
	glVertex3fv(leg2vertices[7]);
	glVertex3fv(leg2vertices[3]);

	glNormal3fv(calcNormal(leg2vertices[3], leg2vertices[7], leg2vertices[4]));//back
	glVertex3fv(leg2vertices[3]);
	glVertex3fv(leg2vertices[7]);
	glVertex3fv(leg2vertices[4]);
	glVertex3fv(leg2vertices[0]);

	glNormal3fv(calcNormal(leg2vertices[0], leg2vertices[4], leg2vertices[5]));//left
	glVertex3fv(leg2vertices[0]);
	glVertex3fv(leg2vertices[4]);
	glVertex3fv(leg2vertices[5]);
	glVertex3fv(leg2vertices[1]);

	glNormal3fv(calcNormal(leg2vertices[4], leg2vertices[5], leg2vertices[6]));//bottom
	glVertex3fv(leg2vertices[4]);
	glVertex3fv(leg2vertices[5]);
	glVertex3fv(leg2vertices[6]);
	glVertex3fv(leg2vertices[7]);
	glEnd();

	//오른쪽뒷다리
	GLfloat leg3vertices[][3] = {
		{-1.065, 0.2874, 0.735},
		{-1.065, 0.2874, 0.705},
		{-1.035, 0.2874, 0.705},
		{-1.035, 0.2874, 0.735},
		{-1.065, 0.0, 0.735},
		{-1.065, 0.0, 0.705},
		{-1.035, 0.0, 0.705},
		{-1.035, 0.0, 0.735},
	};
	glBegin(GL_QUADS);
	glNormal3fv(calcNormal(leg3vertices[0], leg3vertices[1], leg3vertices[2])); //top
	glVertex3fv(leg3vertices[0]);
	glVertex3fv(leg3vertices[1]);
	glVertex3fv(leg3vertices[2]);
	glVertex3fv(leg3vertices[3]);

	glNormal3fv(calcNormal(leg3vertices[1], leg3vertices[5], leg3vertices[6]));//front
	glVertex3fv(leg3vertices[1]);
	glVertex3fv(leg3vertices[5]);
	glVertex3fv(leg3vertices[6]);
	glVertex3fv(leg3vertices[2]);

	glNormal3fv(calcNormal(leg3vertices[2], leg3vertices[6], leg3vertices[7]));//right
	glVertex3fv(leg3vertices[2]);
	glVertex3fv(leg3vertices[6]);
	glVertex3fv(leg3vertices[7]);
	glVertex3fv(leg3vertices[3]);

	glNormal3fv(calcNormal(leg3vertices[3], leg3vertices[7], leg3vertices[4]));//back
	glVertex3fv(leg3vertices[3]);
	glVertex3fv(leg3vertices[7]);
	glVertex3fv(leg3vertices[4]);
	glVertex3fv(leg3vertices[0]);

	glNormal3fv(calcNormal(leg3vertices[0], leg3vertices[4], leg3vertices[5]));//left
	glVertex3fv(leg3vertices[0]);
	glVertex3fv(leg3vertices[4]);
	glVertex3fv(leg3vertices[5]);
	glVertex3fv(leg3vertices[1]);

	glNormal3fv(calcNormal(leg3vertices[4], leg3vertices[5], leg3vertices[6]));//bottom
	glVertex3fv(leg3vertices[4]);
	glVertex3fv(leg3vertices[5]);
	glVertex3fv(leg3vertices[6]);
	glVertex3fv(leg3vertices[7]);
	glEnd();

	//오른쪽앞다리
	GLfloat leg4vertices[][3] = {
		{-1.065, 0.2874, 0.395},
		{-1.065, 0.2874, 0.365},
		{-1.035, 0.2874, 0.365},
		{-1.035, 0.2874, 0.395},
		{-1.065, 0.0, 0.395},
		{-1.065, 0.0, 0.365},
		{-1.035, 0.0, 0.365},
		{-1.035, 0.0, 0.395},
	};
	glBegin(GL_QUADS);
	glNormal3fv(calcNormal(leg4vertices[0], leg4vertices[1], leg4vertices[2])); //top
	glVertex3fv(leg4vertices[0]);
	glVertex3fv(leg4vertices[1]);
	glVertex3fv(leg4vertices[2]);
	glVertex3fv(leg4vertices[3]);

	glNormal3fv(calcNormal(leg4vertices[1], leg4vertices[5], leg4vertices[6]));//front
	glVertex3fv(leg4vertices[1]);
	glVertex3fv(leg4vertices[5]);
	glVertex3fv(leg4vertices[6]);
	glVertex3fv(leg4vertices[2]);

	glNormal3fv(calcNormal(leg4vertices[2], leg4vertices[6], leg4vertices[7]));//right
	glVertex3fv(leg4vertices[2]);
	glVertex3fv(leg4vertices[6]);
	glVertex3fv(leg4vertices[7]);
	glVertex3fv(leg4vertices[3]);

	glNormal3fv(calcNormal(leg4vertices[3], leg4vertices[7], leg4vertices[4]));//back
	glVertex3fv(leg4vertices[3]);
	glVertex3fv(leg4vertices[7]);
	glVertex3fv(leg4vertices[4]);
	glVertex3fv(leg4vertices[0]);

	glNormal3fv(calcNormal(leg4vertices[0], leg4vertices[4], leg4vertices[5]));//left
	glVertex3fv(leg4vertices[0]);
	glVertex3fv(leg4vertices[4]);
	glVertex3fv(leg4vertices[5]);
	glVertex3fv(leg4vertices[1]);

	glNormal3fv(calcNormal(leg4vertices[4], leg4vertices[5], leg4vertices[6]));//bottom
	glVertex3fv(leg4vertices[4]);
	glVertex3fv(leg4vertices[5]);
	glVertex3fv(leg4vertices[6]);
	glVertex3fv(leg4vertices[7]);
	glEnd();

}

void drawdeskdrawer() {

	GLfloat ddvertices[][3] = {
		{-0.6, 0.245, 0.685},
		{-0.6, 0.245, 0.515},
		{-0.38, 0.245, 0.515},
		{-0.38, 0.245, 0.685},
		{-0.6, 0.005, 0.685},
		{-0.6, 0.005, 0.515},
		{-0.38, 0.005, 0.515},
		{-0.38, 0.005, 0.685}
	};
	glBegin(GL_QUADS);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, deskdrawer_diffuse);
	glMaterialfv(GL_FRONT, GL_AMBIENT, deskdrawer_ambient);
	
	glNormal3fv(calcNormal(ddvertices[0], ddvertices[1], ddvertices[2])); //top
	glVertex3fv(ddvertices[0]);
	glVertex3fv(ddvertices[1]);
	glVertex3fv(ddvertices[2]);
	glVertex3fv(ddvertices[3]);

	glNormal3fv(calcNormal(ddvertices[1], ddvertices[5], ddvertices[6]));//front
	glVertex3fv(ddvertices[1]);
	glVertex3fv(ddvertices[5]);
	glVertex3fv(ddvertices[6]);
	glVertex3fv(ddvertices[2]);

	glNormal3fv(calcNormal(ddvertices[2], ddvertices[6], ddvertices[7]));//right
	glVertex3fv(ddvertices[2]);
	glVertex3fv(ddvertices[6]);
	glVertex3fv(ddvertices[7]);
	glVertex3fv(ddvertices[3]);

	glNormal3fv(calcNormal(ddvertices[3], ddvertices[7], ddvertices[4]));//back
	glVertex3fv(ddvertices[3]);
	glVertex3fv(ddvertices[7]);
	glVertex3fv(ddvertices[4]);
	glVertex3fv(ddvertices[0]);

	glNormal3fv(calcNormal(ddvertices[0], ddvertices[4], ddvertices[5]));//left
	glVertex3fv(ddvertices[0]);
	glVertex3fv(ddvertices[4]);
	glVertex3fv(ddvertices[5]);
	glVertex3fv(ddvertices[1]);

	glNormal3fv(calcNormal(ddvertices[4], ddvertices[5], ddvertices[6]));//bottom
	glVertex3fv(ddvertices[4]);
	glVertex3fv(ddvertices[5]);
	glVertex3fv(ddvertices[6]);
	glVertex3fv(ddvertices[7]);
	glEnd();

	GLfloat dd1vertices[][3] = {
		{-0.6, 0.16, 0.515},
		{-0.6, 0.16, 0.505},
		{-0.38, 0.16, 0.505},
		{-0.38, 0.16, 0.515},
		{-0.6, 0.22, 0.515},
		{-0.6, 0.22, 0.505},
		{-0.38, 0.22, 0.505},
		{-0.38, 0.22, 0.515}
	};
	glBegin(GL_QUADS);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, desk_diffuse);
	glMaterialfv(GL_FRONT, GL_AMBIENT, desk_ambient);
	glNormal3fv(calcNormal(dd1vertices[0], dd1vertices[1], dd1vertices[2])); //top
	glVertex3fv(dd1vertices[0]);
	glVertex3fv(dd1vertices[1]);
	glVertex3fv(dd1vertices[2]);
	glVertex3fv(dd1vertices[3]);

	glNormal3fv(calcNormal(dd1vertices[1], dd1vertices[5], dd1vertices[6]));//front
	glVertex3fv(dd1vertices[1]);
	glVertex3fv(dd1vertices[5]);
	glVertex3fv(dd1vertices[6]);
	glVertex3fv(dd1vertices[2]);

	glNormal3fv(calcNormal(dd1vertices[2], dd1vertices[6], dd1vertices[7]));//right
	glVertex3fv(dd1vertices[2]);
	glVertex3fv(dd1vertices[6]);
	glVertex3fv(dd1vertices[7]);
	glVertex3fv(dd1vertices[3]);

	glNormal3fv(calcNormal(dd1vertices[3], dd1vertices[7], dd1vertices[4]));//back
	glVertex3fv(dd1vertices[3]);
	glVertex3fv(dd1vertices[7]);
	glVertex3fv(dd1vertices[4]);
	glVertex3fv(dd1vertices[0]);

	glNormal3fv(calcNormal(dd1vertices[0], dd1vertices[4], dd1vertices[5]));//left
	glVertex3fv(dd1vertices[0]);
	glVertex3fv(dd1vertices[4]);
	glVertex3fv(dd1vertices[5]);
	glVertex3fv(dd1vertices[1]);

	glNormal3fv(calcNormal(dd1vertices[4], dd1vertices[5], dd1vertices[6]));//bottom
	glVertex3fv(dd1vertices[4]);
	glVertex3fv(dd1vertices[5]);
	glVertex3fv(dd1vertices[6]);
	glVertex3fv(dd1vertices[7]);
	glEnd();

	GLfloat dd2vertices[][3] = {
		{-0.6, 0.09, 0.515},
		{-0.6, 0.09, 0.505},
		{-0.38, 0.09, 0.505},
		{-0.38, 0.09, 0.515},
		{-0.6, 0.15, 0.515},
		{-0.6, 0.15, 0.505},
		{-0.38, 0.15, 0.505},
		{-0.38, 0.15, 0.515}
	};
	glBegin(GL_QUADS);
	glNormal3fv(calcNormal(dd2vertices[0], dd2vertices[1], dd2vertices[2])); //top
	glVertex3fv(dd2vertices[0]);
	glVertex3fv(dd2vertices[1]);
	glVertex3fv(dd2vertices[2]);
	glVertex3fv(dd2vertices[3]);

	glNormal3fv(calcNormal(dd2vertices[1], dd2vertices[5], dd2vertices[6]));//front
	glVertex3fv(dd2vertices[1]);
	glVertex3fv(dd2vertices[5]);
	glVertex3fv(dd2vertices[6]);
	glVertex3fv(dd2vertices[2]);

	glNormal3fv(calcNormal(dd2vertices[2], dd2vertices[6], dd2vertices[7]));//right
	glVertex3fv(dd2vertices[2]);
	glVertex3fv(dd2vertices[6]);
	glVertex3fv(dd2vertices[7]);
	glVertex3fv(dd2vertices[3]);

	glNormal3fv(calcNormal(dd2vertices[3], dd2vertices[7], dd2vertices[4]));//back
	glVertex3fv(dd2vertices[3]);
	glVertex3fv(dd2vertices[7]);
	glVertex3fv(dd2vertices[4]);
	glVertex3fv(dd2vertices[0]);

	glNormal3fv(calcNormal(dd2vertices[0], dd2vertices[4], dd2vertices[5]));//left
	glVertex3fv(dd2vertices[0]);
	glVertex3fv(dd2vertices[4]);
	glVertex3fv(dd2vertices[5]);
	glVertex3fv(dd2vertices[1]);

	glNormal3fv(calcNormal(dd2vertices[4], dd2vertices[5], dd2vertices[6]));//bottom
	glVertex3fv(dd2vertices[4]);
	glVertex3fv(dd2vertices[5]);
	glVertex3fv(dd2vertices[6]);
	glVertex3fv(dd2vertices[7]);
	glEnd();

	GLfloat dd3vertices[][3] = {
		{-0.6, 0.02, 0.515},
		{-0.6, 0.02, 0.505},
		{-0.38, 0.02, 0.505},
		{-0.38, 0.02, 0.515},
		{-0.6, 0.08, 0.515},
		{-0.6, 0.08, 0.505},
		{-0.38, 0.08, 0.505},
		{-0.38, 0.08, 0.515}
	};
	glBegin(GL_QUADS);
	glNormal3fv(calcNormal(dd3vertices[0], dd3vertices[1], dd3vertices[2])); //top
	glVertex3fv(dd3vertices[0]);
	glVertex3fv(dd3vertices[1]);
	glVertex3fv(dd3vertices[2]);
	glVertex3fv(dd3vertices[3]);

	glNormal3fv(calcNormal(dd3vertices[1], dd3vertices[5], dd3vertices[6]));//front
	glVertex3fv(dd3vertices[1]);
	glVertex3fv(dd3vertices[5]);
	glVertex3fv(dd3vertices[6]);
	glVertex3fv(dd3vertices[2]);

	glNormal3fv(calcNormal(dd3vertices[2], dd3vertices[6], dd3vertices[7]));//right
	glVertex3fv(dd3vertices[2]);
	glVertex3fv(dd3vertices[6]);
	glVertex3fv(dd3vertices[7]);
	glVertex3fv(dd3vertices[3]);

	glNormal3fv(calcNormal(dd3vertices[3], dd3vertices[7], dd3vertices[4]));//back
	glVertex3fv(dd3vertices[3]);
	glVertex3fv(dd3vertices[7]);
	glVertex3fv(dd3vertices[4]);
	glVertex3fv(dd3vertices[0]);

	glNormal3fv(calcNormal(dd3vertices[0], dd3vertices[4], dd3vertices[5]));//left
	glVertex3fv(dd3vertices[0]);
	glVertex3fv(dd3vertices[4]);
	glVertex3fv(dd3vertices[5]);
	glVertex3fv(dd3vertices[1]);

	glNormal3fv(calcNormal(dd3vertices[4], dd3vertices[5], dd3vertices[6]));//bottom
	glVertex3fv(dd3vertices[4]);
	glVertex3fv(dd3vertices[5]);
	glVertex3fv(dd3vertices[6]);
	glVertex3fv(dd3vertices[7]);
	glEnd();
}

void drawbed() {

	GLfloat bedleg1vertices[][3] = {
		{0.425, 0.025, -0.685},
		{0.425, 0.025, -0.735},
		{0.475, 0.025, -0.735},
		{0.475, 0.025, -0.685},
		{0.425, 0.0, -0.685},
		{0.425, 0.0, -0.735},
		{0.475, 0.0, -0.735},
		{0.475, 0.0, -0.685}
	};
	//아래쪽 벽다리
	glBegin(GL_QUADS);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, bed_diffuse);
	glMaterialfv(GL_FRONT, GL_AMBIENT, bed_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, bed_specular);
	glNormal3fv(calcNormal(bedleg1vertices[0], bedleg1vertices[1], bedleg1vertices[2])); //top
	glVertex3fv(bedleg1vertices[0]);
	glVertex3fv(bedleg1vertices[1]);
	glVertex3fv(bedleg1vertices[2]);
	glVertex3fv(bedleg1vertices[3]);

	glNormal3fv(calcNormal(bedleg1vertices[1], bedleg1vertices[5], bedleg1vertices[6]));//front
	glVertex3fv(bedleg1vertices[1]);
	glVertex3fv(bedleg1vertices[5]);
	glVertex3fv(bedleg1vertices[6]);
	glVertex3fv(bedleg1vertices[2]);

	glNormal3fv(calcNormal(bedleg1vertices[2], bedleg1vertices[6], bedleg1vertices[7]));//right
	glVertex3fv(bedleg1vertices[2]);
	glVertex3fv(bedleg1vertices[6]);
	glVertex3fv(bedleg1vertices[7]);
	glVertex3fv(bedleg1vertices[3]);

	glNormal3fv(calcNormal(bedleg1vertices[3], bedleg1vertices[7], bedleg1vertices[4]));//back
	glVertex3fv(bedleg1vertices[3]);
	glVertex3fv(bedleg1vertices[7]);
	glVertex3fv(bedleg1vertices[4]);
	glVertex3fv(bedleg1vertices[0]);

	glNormal3fv(calcNormal(bedleg1vertices[0], bedleg1vertices[4], bedleg1vertices[5]));//left
	glVertex3fv(bedleg1vertices[0]);
	glVertex3fv(bedleg1vertices[4]);
	glVertex3fv(bedleg1vertices[5]);
	glVertex3fv(bedleg1vertices[1]);

	glNormal3fv(calcNormal(bedleg1vertices[4], bedleg1vertices[5], bedleg1vertices[6]));//bottom
	glVertex3fv(bedleg1vertices[4]);
	glVertex3fv(bedleg1vertices[5]);
	glVertex3fv(bedleg1vertices[6]);
	glVertex3fv(bedleg1vertices[7]);
	glEnd();

	//아래쪽 안 다리
	GLfloat bedleg2vertices[][3] = {
		{0.38, 0.025, -0.012},
		{0.38, 0.025, -0.107},
		{0.475, 0.025, -0.107},
		{0.475, 0.025, -0.012},
		{0.38, 0.0, -0.012},
		{0.38, 0.0, -0.107},
		{0.475, 0.0, -0.107},
		{0.475, 0.0, -0.012}
	};
	glBegin(GL_QUADS);
	glNormal3fv(calcNormal(bedleg2vertices[0], bedleg2vertices[1], bedleg2vertices[2])); //top
	glVertex3fv(bedleg2vertices[0]);
	glVertex3fv(bedleg2vertices[1]);
	glVertex3fv(bedleg2vertices[2]);
	glVertex3fv(bedleg2vertices[3]);

	glNormal3fv(calcNormal(bedleg2vertices[1], bedleg2vertices[5], bedleg2vertices[6]));//front
	glVertex3fv(bedleg2vertices[1]);
	glVertex3fv(bedleg2vertices[5]);
	glVertex3fv(bedleg2vertices[6]);
	glVertex3fv(bedleg2vertices[2]);

	glNormal3fv(calcNormal(bedleg2vertices[2], bedleg2vertices[6], bedleg2vertices[7]));//right
	glVertex3fv(bedleg2vertices[2]);
	glVertex3fv(bedleg2vertices[6]);
	glVertex3fv(bedleg2vertices[7]);
	glVertex3fv(bedleg2vertices[3]);

	glNormal3fv(calcNormal(bedleg2vertices[3], bedleg2vertices[7], bedleg2vertices[4]));//back
	glVertex3fv(bedleg2vertices[3]);
	glVertex3fv(bedleg2vertices[7]);
	glVertex3fv(bedleg2vertices[4]);
	glVertex3fv(bedleg2vertices[0]);

	glNormal3fv(calcNormal(bedleg2vertices[0], bedleg2vertices[4], bedleg2vertices[5]));//left
	glVertex3fv(bedleg2vertices[0]);
	glVertex3fv(bedleg2vertices[4]);
	glVertex3fv(bedleg2vertices[5]);
	glVertex3fv(bedleg2vertices[1]);

	glNormal3fv(calcNormal(bedleg2vertices[4], bedleg2vertices[5], bedleg2vertices[6]));//bottom
	glVertex3fv(bedleg2vertices[4]);
	glVertex3fv(bedleg2vertices[5]);
	glVertex3fv(bedleg2vertices[6]);
	glVertex3fv(bedleg2vertices[7]);
	glEnd();



	//침대 벽쪽 머리기둥
	GLfloat whlegvertices[][3] = {
		{-1.075, 0.4, -0.7},
		{-1.075, 0.4, -0.75},
		{-1.025, 0.4, -0.75},
		{-1.025, 0.4, -0.7},
		{-1.075, 0.0, -0.7},
		{-1.075, 0.0, -0.75},
		{-1.025, 0.0, -0.75},
		{-1.025, 0.0, -0.7}
	};
	glBegin(GL_QUADS);
	glNormal3fv(calcNormal(whlegvertices[0], whlegvertices[1], whlegvertices[2])); //top
	glVertex3fv(whlegvertices[0]);
	glVertex3fv(whlegvertices[1]);
	glVertex3fv(whlegvertices[2]);
	glVertex3fv(whlegvertices[3]);

	glNormal3fv(calcNormal(whlegvertices[1], whlegvertices[5], whlegvertices[6]));//front
	glVertex3fv(whlegvertices[1]);
	glVertex3fv(whlegvertices[5]);
	glVertex3fv(whlegvertices[6]);
	glVertex3fv(whlegvertices[2]);

	glNormal3fv(calcNormal(whlegvertices[2], whlegvertices[6], whlegvertices[7]));//right
	glVertex3fv(whlegvertices[2]);
	glVertex3fv(whlegvertices[6]);
	glVertex3fv(whlegvertices[7]);
	glVertex3fv(whlegvertices[3]);

	glNormal3fv(calcNormal(whlegvertices[3], whlegvertices[7], whlegvertices[4]));//back
	glVertex3fv(whlegvertices[3]);
	glVertex3fv(whlegvertices[7]);
	glVertex3fv(whlegvertices[4]);
	glVertex3fv(whlegvertices[0]);

	glNormal3fv(calcNormal(whlegvertices[0], whlegvertices[4], whlegvertices[5]));//left
	glVertex3fv(whlegvertices[0]);
	glVertex3fv(whlegvertices[4]);
	glVertex3fv(whlegvertices[5]);
	glVertex3fv(whlegvertices[1]);

	glNormal3fv(calcNormal(whlegvertices[4], whlegvertices[5], whlegvertices[6]));//bottom
	glVertex3fv(whlegvertices[4]);
	glVertex3fv(whlegvertices[5]);
	glVertex3fv(whlegvertices[6]);
	glVertex3fv(whlegvertices[7]);
	glEnd();

	glPushMatrix();
	glTranslatef(-1.05, 0.43, -0.725);
	glutSolidSphere(0.027f, 30, 17);
	glPopMatrix();

	//침대 책상쪽 머리기둥
	GLfloat dhlegvertices[][3] = {
		{-1.075, 0.4, -0.005},
		{-1.075, 0.4, -0.055},
		{-1.025, 0.4, -0.055},
		{-1.025, 0.4, -0.005},
		{-1.075, 0.0, -0.005},
		{-1.075, 0.0, -0.055},
		{-1.025, 0.0, -0.055},
		{-1.025, 0.0, -0.005}
	};
	glBegin(GL_QUADS);
	glNormal3fv(calcNormal(dhlegvertices[0], dhlegvertices[1], dhlegvertices[2])); //top
	glVertex3fv(dhlegvertices[0]);
	glVertex3fv(dhlegvertices[1]);
	glVertex3fv(dhlegvertices[2]);
	glVertex3fv(dhlegvertices[3]);

	glNormal3fv(calcNormal(dhlegvertices[1], dhlegvertices[5], dhlegvertices[6]));//front
	glVertex3fv(dhlegvertices[1]);
	glVertex3fv(dhlegvertices[5]);
	glVertex3fv(dhlegvertices[6]);
	glVertex3fv(dhlegvertices[2]);

	glNormal3fv(calcNormal(dhlegvertices[2], dhlegvertices[6], dhlegvertices[7]));//right
	glVertex3fv(dhlegvertices[2]);
	glVertex3fv(dhlegvertices[6]);
	glVertex3fv(dhlegvertices[7]);
	glVertex3fv(dhlegvertices[3]);

	glNormal3fv(calcNormal(dhlegvertices[3], dhlegvertices[7], dhlegvertices[4]));//back
	glVertex3fv(dhlegvertices[3]);
	glVertex3fv(dhlegvertices[7]);
	glVertex3fv(dhlegvertices[4]);
	glVertex3fv(dhlegvertices[0]);

	glNormal3fv(calcNormal(dhlegvertices[0], dhlegvertices[4], dhlegvertices[5]));//left
	glVertex3fv(dhlegvertices[0]);
	glVertex3fv(dhlegvertices[4]);
	glVertex3fv(dhlegvertices[5]);
	glVertex3fv(dhlegvertices[1]);

	glNormal3fv(calcNormal(dhlegvertices[4], dhlegvertices[5], dhlegvertices[6]));//bottom
	glVertex3fv(dhlegvertices[4]);
	glVertex3fv(dhlegvertices[5]);
	glVertex3fv(dhlegvertices[6]);
	glVertex3fv(dhlegvertices[7]);
	glEnd();

	glPushMatrix();
	glTranslatef(-1.05, 0.43, -0.03);
	glutSolidSphere(0.03f, 30, 17);
	glPopMatrix();

	//침대머리
	GLfloat bedheadvertices[][3] = {
		{-1.075, 0.375, -0.7},
		{-1.075, 0.375, -0.0545},
		{-1.025, 0.375, -0.0545},
		{-1.025, 0.375, -0.7},
		{-1.075, 0.025, -0.7},
		{-1.075, 0.025, -0.0545},
		{-1.025, 0.025, -0.0545},
		{-1.025, 0.025, -0.7}
		
	};
	glBegin(GL_QUADS);
	glNormal3fv(calcNormal(bedheadvertices[0], bedheadvertices[1], bedheadvertices[2])); //top
	glVertex3fv(bedheadvertices[0]);
	glVertex3fv(bedheadvertices[1]);
	glVertex3fv(bedheadvertices[2]);
	glVertex3fv(bedheadvertices[3]);

	glNormal3fv(calcNormal(bedheadvertices[1], bedheadvertices[5], bedheadvertices[6]));//front
	glVertex3fv(bedheadvertices[1]);
	glVertex3fv(bedheadvertices[5]);
	glVertex3fv(bedheadvertices[6]);
	glVertex3fv(bedheadvertices[2]);

	glNormal3fv(calcNormal(bedheadvertices[2], bedheadvertices[6], bedheadvertices[7]));//right
	glVertex3fv(bedheadvertices[2]);
	glVertex3fv(bedheadvertices[6]);
	glVertex3fv(bedheadvertices[7]);
	glVertex3fv(bedheadvertices[3]);

	glNormal3fv(calcNormal(bedheadvertices[3], bedheadvertices[7], bedheadvertices[4]));//back
	glVertex3fv(bedheadvertices[3]);
	glVertex3fv(bedheadvertices[7]);
	glVertex3fv(bedheadvertices[4]);
	glVertex3fv(bedheadvertices[0]);

	glNormal3fv(calcNormal(bedheadvertices[0], bedheadvertices[4], bedheadvertices[5]));//left
	glVertex3fv(bedheadvertices[0]);
	glVertex3fv(bedheadvertices[4]);
	glVertex3fv(bedheadvertices[5]);
	glVertex3fv(bedheadvertices[1]);

	glNormal3fv(calcNormal(bedheadvertices[4], bedheadvertices[5], bedheadvertices[6]));//bottom
	glVertex3fv(bedheadvertices[4]);
	glVertex3fv(bedheadvertices[5]);
	glVertex3fv(bedheadvertices[6]);
	glVertex3fv(bedheadvertices[7]);
	glEnd();


	//침대바닥부분
	GLfloat bedvertices[][3] = {
		{-1.025, 0.175, -0.0125},
		{-1.025, 0.175, -0.7425},
		{0.475, 0.175, -0.7425},
		{0.475, 0.175, -0.0125},
		{-1.025, 0.025, -0.0125},
		{-1.025, 0.025, -0.7425},
		{0.475, 0.025, -0.7425},
		{0.475, 0.025, -0.0125}
	};
	glBegin(GL_QUADS);
	glNormal3fv(calcNormal(bedvertices[0], bedvertices[1], bedvertices[2])); //top
	glVertex3fv(bedvertices[0]);
	glVertex3fv(bedvertices[1]);
	glVertex3fv(bedvertices[2]);
	glVertex3fv(bedvertices[3]);

	glNormal3fv(calcNormal(bedvertices[1], bedvertices[5], bedvertices[6]));//front
	glVertex3fv(bedvertices[1]);
	glVertex3fv(bedvertices[5]);
	glVertex3fv(bedvertices[6]);
	glVertex3fv(bedvertices[2]);

	glNormal3fv(calcNormal(bedvertices[2], bedvertices[6], bedvertices[7]));//right
	glVertex3fv(bedvertices[2]);
	glVertex3fv(bedvertices[6]);
	glVertex3fv(bedvertices[7]);
	glVertex3fv(bedvertices[3]);

	glNormal3fv(calcNormal(bedvertices[3], bedvertices[7], bedvertices[4]));//back
	glVertex3fv(bedvertices[3]);
	glVertex3fv(bedvertices[7]);
	glVertex3fv(bedvertices[4]);
	glVertex3fv(bedvertices[0]);

	glNormal3fv(calcNormal(bedvertices[0], bedvertices[4], bedvertices[5]));//left
	glVertex3fv(bedvertices[0]);
	glVertex3fv(bedvertices[4]);
	glVertex3fv(bedvertices[5]);
	glVertex3fv(bedvertices[1]);

	glNormal3fv(calcNormal(bedvertices[4], bedvertices[5], bedvertices[6]));//bottom
	glVertex3fv(bedvertices[4]);
	glVertex3fv(bedvertices[5]);
	glVertex3fv(bedvertices[6]);
	glVertex3fv(bedvertices[7]);
	glEnd();

	//매트리스
	GLfloat mattvertices[][3] = {
		{-1.025, 0.275, -0.0125},
		{-1.025, 0.275, -0.7425},
		{0.475, 0.275, -0.7425},
		{0.475, 0.275, -0.0125},
		{-1.025, 0.175, -0.0125},
		{-1.025, 0.175, -0.7425},
		{0.475, 0.175, -0.7425},
		{0.475, 0.175, -0.0125}
	};
	glBegin(GL_QUADS);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, desk_diffuse);
	glMaterialfv(GL_FRONT, GL_AMBIENT, desk_ambient);

	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, textureNames[1]);
	glNormal3fv(calcNormal(mattvertices[0], mattvertices[1], mattvertices[2])); //top
	//glTexCoord2f(0, 0); 
	glVertex3fv(mattvertices[0]);
	//glTexCoord2f(0, 1);
	glVertex3fv(mattvertices[1]);
	//glTexCoord2f(1, 1); 
	glVertex3fv(mattvertices[2]);
	//glTexCoord2f(1, 0); 
	glVertex3fv(mattvertices[3]);

	glNormal3fv(calcNormal(mattvertices[1], mattvertices[5], mattvertices[6]));//front
	glVertex3fv(mattvertices[1]);
	glVertex3fv(mattvertices[5]);
	glVertex3fv(mattvertices[6]);
	glVertex3fv(mattvertices[2]);

	glNormal3fv(calcNormal(mattvertices[2], mattvertices[6], mattvertices[7]));//right
	glVertex3fv(mattvertices[2]);
	glVertex3fv(mattvertices[6]);
	glVertex3fv(mattvertices[7]);
	glVertex3fv(mattvertices[3]);

	glNormal3fv(calcNormal(mattvertices[3], mattvertices[7], mattvertices[4]));//back
	glVertex3fv(mattvertices[3]);
	glVertex3fv(mattvertices[7]);
	glVertex3fv(mattvertices[4]);
	glVertex3fv(mattvertices[0]);

	glNormal3fv(calcNormal(mattvertices[0], mattvertices[4], mattvertices[5]));//left
	glVertex3fv(mattvertices[0]);
	glVertex3fv(mattvertices[4]);
	glVertex3fv(mattvertices[5]);
	glVertex3fv(mattvertices[1]);

	glNormal3fv(calcNormal(mattvertices[4], mattvertices[5], mattvertices[6]));//bottom
	glVertex3fv(mattvertices[4]);
	glVertex3fv(mattvertices[5]);
	glVertex3fv(mattvertices[6]);
	glVertex3fv(mattvertices[7]);
	glEnd();
	glFlush();
	glutSwapBuffers;
}
void drawwindow() {
	//창틀
	GLfloat ufrwinvertices[][3] = {
		{-1.26, 0.925, -0.455},
		{-1.26, 0.925, 0.455},
		{-1.24, 0.925, 0.455},
		{-1.24, 0.925, -0.455},
		{-1.26, 0.875, -0.455},
		{-1.26, 0.875, 0.455},
		{-1.24, 0.875, 0.455},
		{-1.24, 0.875, -0.455}
	};
	glBegin(GL_QUADS);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, desk_diffuse);
	glMaterialfv(GL_FRONT, GL_AMBIENT, desk_ambient);

	glNormal3fv(calcNormal(ufrwinvertices[0], ufrwinvertices[1], ufrwinvertices[2])); //top
	glVertex3fv(ufrwinvertices[0]);
	glVertex3fv(ufrwinvertices[1]);
	glVertex3fv(ufrwinvertices[2]);
	glVertex3fv(ufrwinvertices[3]);

	glNormal3fv(calcNormal(ufrwinvertices[1], ufrwinvertices[5], ufrwinvertices[6]));//front
	glVertex3fv(ufrwinvertices[1]);
	glVertex3fv(ufrwinvertices[5]);
	glVertex3fv(ufrwinvertices[6]);
	glVertex3fv(ufrwinvertices[2]);

	glNormal3fv(calcNormal(ufrwinvertices[2], ufrwinvertices[6], ufrwinvertices[7]));//right
	glVertex3fv(ufrwinvertices[2]);
	glVertex3fv(ufrwinvertices[6]);
	glVertex3fv(ufrwinvertices[7]);
	glVertex3fv(ufrwinvertices[3]);

	glNormal3fv(calcNormal(ufrwinvertices[3], ufrwinvertices[7], ufrwinvertices[4]));//back
	glVertex3fv(ufrwinvertices[3]);
	glVertex3fv(ufrwinvertices[7]);
	glVertex3fv(ufrwinvertices[4]);
	glVertex3fv(ufrwinvertices[0]);

	glNormal3fv(calcNormal(ufrwinvertices[0], ufrwinvertices[4], ufrwinvertices[5]));//left
	glVertex3fv(ufrwinvertices[0]);
	glVertex3fv(ufrwinvertices[4]);
	glVertex3fv(ufrwinvertices[5]);
	glVertex3fv(ufrwinvertices[1]);

	glNormal3fv(calcNormal(ufrwinvertices[4], ufrwinvertices[5], ufrwinvertices[6]));//bottom
	glVertex3fv(ufrwinvertices[4]);
	glVertex3fv(ufrwinvertices[5]);
	glVertex3fv(ufrwinvertices[6]);
	glVertex3fv(ufrwinvertices[7]);
	glEnd();

	GLfloat dfrwinvertices[][3] = {
		
		{-1.26, 0.425, -0.455},
		{-1.26, 0.425, 0.455},
		{-1.24, 0.425, 0.455},
		{-1.24, 0.425, -0.455},
		{-1.26, 0.375, -0.455},
		{-1.26, 0.375, 0.455},
		{-1.24, 0.375, 0.455},
		{-1.24, 0.375, -0.455},
		
	};
	glBegin(GL_QUADS);
	glNormal3fv(calcNormal(dfrwinvertices[0], dfrwinvertices[1], dfrwinvertices[2])); //top
	glVertex3fv(dfrwinvertices[0]);
	glVertex3fv(dfrwinvertices[1]);
	glVertex3fv(dfrwinvertices[2]);
	glVertex3fv(dfrwinvertices[3]);

	glNormal3fv(calcNormal(dfrwinvertices[1], dfrwinvertices[5], dfrwinvertices[6]));//front
	glVertex3fv(dfrwinvertices[1]);
	glVertex3fv(dfrwinvertices[5]);
	glVertex3fv(dfrwinvertices[6]);
	glVertex3fv(dfrwinvertices[2]);

	glNormal3fv(calcNormal(dfrwinvertices[2], dfrwinvertices[6], dfrwinvertices[7]));//right
	glVertex3fv(dfrwinvertices[2]);
	glVertex3fv(dfrwinvertices[6]);
	glVertex3fv(dfrwinvertices[7]);
	glVertex3fv(dfrwinvertices[3]);

	glNormal3fv(calcNormal(dfrwinvertices[3], dfrwinvertices[7], dfrwinvertices[4]));//back
	glVertex3fv(dfrwinvertices[3]);
	glVertex3fv(dfrwinvertices[7]);
	glVertex3fv(dfrwinvertices[4]);
	glVertex3fv(dfrwinvertices[0]);

	glNormal3fv(calcNormal(dfrwinvertices[0], dfrwinvertices[4], dfrwinvertices[5]));//left
	glVertex3fv(dfrwinvertices[0]);
	glVertex3fv(dfrwinvertices[4]);
	glVertex3fv(dfrwinvertices[5]);
	glVertex3fv(dfrwinvertices[1]);

	glNormal3fv(calcNormal(dfrwinvertices[4], dfrwinvertices[5], dfrwinvertices[6]));//bottom
	glVertex3fv(dfrwinvertices[4]);
	glVertex3fv(dfrwinvertices[5]);
	glVertex3fv(dfrwinvertices[6]);
	glVertex3fv(dfrwinvertices[7]);
	glEnd();

	GLfloat rfrwinvertices[][3] = {
		
		{-1.26, 0.875, -0.454},
		{-1.26, 0.875, -0.31},
		{-1.24, 0.875, -0.31},
		{-1.24, 0.875, -0.454},
		{-1.26, 0.425, -0.454},
		{-1.26, 0.425, -0.31},
		{-1.24, 0.425, -0.31},
		{-1.24, 0.425, -0.454},
		
	};
	glBegin(GL_QUADS);
	glNormal3fv(calcNormal(rfrwinvertices[0], rfrwinvertices[1], rfrwinvertices[2])); //top
	glVertex3fv(rfrwinvertices[0]);
	glVertex3fv(rfrwinvertices[1]);
	glVertex3fv(rfrwinvertices[2]);
	glVertex3fv(rfrwinvertices[3]);

	glNormal3fv(calcNormal(rfrwinvertices[1], rfrwinvertices[5], rfrwinvertices[6]));//front
	glVertex3fv(rfrwinvertices[1]);
	glVertex3fv(rfrwinvertices[5]);
	glVertex3fv(rfrwinvertices[6]);
	glVertex3fv(rfrwinvertices[2]);

	glNormal3fv(calcNormal(rfrwinvertices[2], rfrwinvertices[6], rfrwinvertices[7]));//right
	glVertex3fv(rfrwinvertices[2]);
	glVertex3fv(rfrwinvertices[6]);
	glVertex3fv(rfrwinvertices[7]);
	glVertex3fv(rfrwinvertices[3]);

	glNormal3fv(calcNormal(rfrwinvertices[3], rfrwinvertices[7], rfrwinvertices[4]));//back
	glVertex3fv(rfrwinvertices[3]);
	glVertex3fv(rfrwinvertices[7]);
	glVertex3fv(rfrwinvertices[4]);
	glVertex3fv(rfrwinvertices[0]);

	glNormal3fv(calcNormal(rfrwinvertices[0], rfrwinvertices[4], rfrwinvertices[5]));//left
	glVertex3fv(rfrwinvertices[0]);
	glVertex3fv(rfrwinvertices[4]);
	glVertex3fv(rfrwinvertices[5]);
	glVertex3fv(rfrwinvertices[1]);

	glNormal3fv(calcNormal(rfrwinvertices[4], rfrwinvertices[5], rfrwinvertices[6]));//bottom
	glVertex3fv(rfrwinvertices[4]);
	glVertex3fv(rfrwinvertices[5]);
	glVertex3fv(rfrwinvertices[6]);
	glVertex3fv(rfrwinvertices[7]);
	glEnd();


	GLfloat mfrwinvertices[][3] = {
		
		{-1.26, 0.875, -0.072},
		{-1.26, 0.875, 0.072},
		{-1.24, 0.875, 0.072},
		{-1.24, 0.875, -0.072},
		{-1.26, 0.425, -0.072},
		{-1.26, 0.425, 0.072},
		{-1.24, 0.425, 0.072},
		{-1.24, 0.425, -0.072},
	};
	glBegin(GL_QUADS);
	glNormal3fv(calcNormal(mfrwinvertices[0], mfrwinvertices[1], mfrwinvertices[2])); //top
	glVertex3fv(mfrwinvertices[0]);
	glVertex3fv(mfrwinvertices[1]);
	glVertex3fv(mfrwinvertices[2]);
	glVertex3fv(mfrwinvertices[3]);

	glNormal3fv(calcNormal(mfrwinvertices[1], mfrwinvertices[5], mfrwinvertices[6]));//front
	glVertex3fv(mfrwinvertices[1]);
	glVertex3fv(mfrwinvertices[5]);
	glVertex3fv(mfrwinvertices[6]);
	glVertex3fv(mfrwinvertices[2]);

	glNormal3fv(calcNormal(mfrwinvertices[2], mfrwinvertices[6], mfrwinvertices[7]));//right
	glVertex3fv(mfrwinvertices[2]);
	glVertex3fv(mfrwinvertices[6]);
	glVertex3fv(mfrwinvertices[7]);
	glVertex3fv(mfrwinvertices[3]);

	glNormal3fv(calcNormal(mfrwinvertices[3], mfrwinvertices[7], mfrwinvertices[4]));//back
	glVertex3fv(mfrwinvertices[3]);
	glVertex3fv(mfrwinvertices[7]);
	glVertex3fv(mfrwinvertices[4]);
	glVertex3fv(mfrwinvertices[0]);

	glNormal3fv(calcNormal(mfrwinvertices[0], mfrwinvertices[4], mfrwinvertices[5]));//left
	glVertex3fv(mfrwinvertices[0]);
	glVertex3fv(mfrwinvertices[4]);
	glVertex3fv(mfrwinvertices[5]);
	glVertex3fv(mfrwinvertices[1]);

	glNormal3fv(calcNormal(mfrwinvertices[4], mfrwinvertices[5], mfrwinvertices[6]));//bottom
	glVertex3fv(mfrwinvertices[4]);
	glVertex3fv(mfrwinvertices[5]);
	glVertex3fv(mfrwinvertices[6]);
	glVertex3fv(mfrwinvertices[7]);
	glEnd();

	GLfloat lfrwinvertices[][3] = {
			{-1.26, 0.875, 0.31},
			{-1.26, 0.875, 0.454},
			{-1.24, 0.875, 0.454},
			{-1.24, 0.875, 0.31},
			{-1.26, 0.425, 0.31},
			{-1.26, 0.425, 0.454},
			{-1.24, 0.425, 0.454},
			{-1.24, 0.425, 0.31}
	};
	glBegin(GL_QUADS);
	glNormal3fv(calcNormal(lfrwinvertices[0], lfrwinvertices[1], lfrwinvertices[2])); //top
	glVertex3fv(lfrwinvertices[0]);
	glVertex3fv(lfrwinvertices[1]);
	glVertex3fv(lfrwinvertices[2]);
	glVertex3fv(lfrwinvertices[3]);

	glNormal3fv(calcNormal(lfrwinvertices[1], lfrwinvertices[5], lfrwinvertices[6]));//front
	glVertex3fv(lfrwinvertices[1]);
	glVertex3fv(lfrwinvertices[5]);
	glVertex3fv(lfrwinvertices[6]);
	glVertex3fv(lfrwinvertices[2]);

	glNormal3fv(calcNormal(lfrwinvertices[2], lfrwinvertices[6], lfrwinvertices[7]));//right
	glVertex3fv(lfrwinvertices[2]);
	glVertex3fv(lfrwinvertices[6]);
	glVertex3fv(lfrwinvertices[7]);
	glVertex3fv(lfrwinvertices[3]);

	glNormal3fv(calcNormal(lfrwinvertices[3], lfrwinvertices[7], lfrwinvertices[4]));//back
	glVertex3fv(lfrwinvertices[3]);
	glVertex3fv(lfrwinvertices[7]);
	glVertex3fv(lfrwinvertices[4]);
	glVertex3fv(lfrwinvertices[0]);

	glNormal3fv(calcNormal(lfrwinvertices[0], lfrwinvertices[4], lfrwinvertices[5]));//left
	glVertex3fv(lfrwinvertices[0]);
	glVertex3fv(lfrwinvertices[4]);
	glVertex3fv(lfrwinvertices[5]);
	glVertex3fv(lfrwinvertices[1]);

	glNormal3fv(calcNormal(lfrwinvertices[4], lfrwinvertices[5], lfrwinvertices[6]));//bottom
	glVertex3fv(lfrwinvertices[4]);
	glVertex3fv(lfrwinvertices[5]);
	glVertex3fv(lfrwinvertices[6]);
	glVertex3fv(lfrwinvertices[7]);
	glEnd();

	//창문
	GLfloat win1vertices[][3] = {
			{-1.26, 0.875, -0.31},
			{-1.26, 0.875, -0.072},
			{-1.24, 0.875, -0.072},
			{-1.24, 0.875, -0.31},
			{-1.26, 0.425, -0.31},
			{-1.26, 0.425, -0.072},
			{-1.24, 0.425, -0.072},
			{-1.24, 0.425, -0.31}
	};
	glBegin(GL_QUADS);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, window_diffuse);
	glMaterialfv(GL_FRONT, GL_AMBIENT, window_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, window_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, window_shinness);
	glNormal3fv(calcNormal(win1vertices[0], win1vertices[1], win1vertices[2])); //top
	glVertex3fv(win1vertices[0]);
	glVertex3fv(win1vertices[1]);
	glVertex3fv(win1vertices[2]);
	glVertex3fv(win1vertices[3]);

	glNormal3fv(calcNormal(win1vertices[1], win1vertices[5], win1vertices[6]));//front
	glVertex3fv(win1vertices[1]);
	glVertex3fv(win1vertices[5]);
	glVertex3fv(win1vertices[6]);
	glVertex3fv(win1vertices[2]);

	glNormal3fv(calcNormal(win1vertices[2], win1vertices[6], win1vertices[7]));//right
	glVertex3fv(win1vertices[2]);
	glVertex3fv(win1vertices[6]);
	glVertex3fv(win1vertices[7]);
	glVertex3fv(win1vertices[3]);

	glNormal3fv(calcNormal(win1vertices[3], win1vertices[7], win1vertices[4]));//back
	glVertex3fv(win1vertices[3]);
	glVertex3fv(win1vertices[7]);
	glVertex3fv(win1vertices[4]);
	glVertex3fv(win1vertices[0]);

	glNormal3fv(calcNormal(win1vertices[0], win1vertices[4], win1vertices[5]));//left
	glVertex3fv(win1vertices[0]);
	glVertex3fv(win1vertices[4]);
	glVertex3fv(win1vertices[5]);
	glVertex3fv(win1vertices[1]);

	glNormal3fv(calcNormal(win1vertices[4], win1vertices[5], win1vertices[6]));//bottom
	glVertex3fv(win1vertices[4]);
	glVertex3fv(win1vertices[5]);
	glVertex3fv(win1vertices[6]);
	glVertex3fv(win1vertices[7]);
	glEnd();

	GLfloat win2vertices[][3] = {
			{-1.26, 0.875, 0.072},
			{-1.26, 0.875, 0.31},
			{-1.24, 0.875, 0.31},
			{-1.24, 0.875, 0.072},
			{-1.26, 0.425, 0.072},
			{-1.26, 0.425, 0.31},
			{-1.24, 0.425, 0.31},
			{-1.24, 0.425, 0.072}
	};
	glBegin(GL_QUADS);
	glNormal3fv(calcNormal(win2vertices[0], win2vertices[1], win2vertices[2])); //top
	glVertex3fv(win2vertices[0]);
	glVertex3fv(win2vertices[1]);
	glVertex3fv(win2vertices[2]);
	glVertex3fv(win2vertices[3]);

	glNormal3fv(calcNormal(win2vertices[1], win2vertices[5], win2vertices[6]));//front
	glVertex3fv(win2vertices[1]);
	glVertex3fv(win2vertices[5]);
	glVertex3fv(win2vertices[6]);
	glVertex3fv(win2vertices[2]);

	glNormal3fv(calcNormal(win2vertices[2], win2vertices[6], win2vertices[7]));//right
	glVertex3fv(win2vertices[2]);
	glVertex3fv(win2vertices[6]);
	glVertex3fv(win2vertices[7]);
	glVertex3fv(win2vertices[3]);

	glNormal3fv(calcNormal(win2vertices[3], win2vertices[7], win2vertices[4]));//back
	glVertex3fv(win2vertices[3]);
	glVertex3fv(win2vertices[7]);
	glVertex3fv(win2vertices[4]);
	glVertex3fv(win2vertices[0]);

	glNormal3fv(calcNormal(win2vertices[0], win2vertices[4], win2vertices[5]));//left
	glVertex3fv(win2vertices[0]);
	glVertex3fv(win2vertices[4]);
	glVertex3fv(win2vertices[5]);
	glVertex3fv(win2vertices[1]);

	glNormal3fv(calcNormal(win2vertices[4], win2vertices[5], win2vertices[6]));//bottom
	glVertex3fv(win2vertices[4]);
	glVertex3fv(win2vertices[5]);
	glVertex3fv(win2vertices[6]);
	glVertex3fv(win2vertices[7]);
	glEnd();

}

void drawscene() {


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	gluLookAt(0.0f, 0.7f, -3.0f,
		0.0f, 0.7f, 0.0f,
		0.0f, 1.0f, 0.0f);

	glScalef(scale_size, scale_size, scale_size);
	glRotatef(x_angle, 0, 1, 0);
	glRotatef(y_angle, 1, 0, 0);
	glTranslatef(xTrans, 0.0, 0.0);
	glTranslatef(0.0, yTrans, 0.0);
	glTranslatef(0.0, 0.0, zTrans);

	
	drawfloor();
	drawceiling();
	wardrobe();
	drawdoor();
	drawbed();
	drawlight();
	drawall();
	drawmirror();
	drawers1();
	drawers2();
	drawwindow();
	drawdesk();
	drawdeskdrawer();
	
	glutSwapBuffers();
}
void reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	// set projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)w / h, 1.0, 20.0);

	// set matrix mode back to model-view matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void mymouse(int button, int state, int x, int y) {
	if (state == GLUT_DOWN) {
		press_x = x; press_y = y;
		if (button == GLUT_LEFT_BUTTON)
			xform_mode = XFORM_ROTATE;
		else if (button == GLUT_RIGHT_BUTTON)
			xform_mode = XFORM_SCALE;
		else if (button == GLUT_MIDDLE_BUTTON)
			xform_mode = XFORM_TRANSLATE;
	}

	else if (state == GLUT_UP) {
		release_x = x; release_y = y;
		if (button == GLUT_LEFT_BUTTON) {
			xform_mode = XFORM_ROTATE;
			x_angle += (release_x - press_x);
			y_angle += (release_y - press_y);
			if (x_angle > 180) x_angle -= 360;
			else if (x_angle < -180) x_angle += 360;
			if (y_angle > 180) y_angle -= 360;
			else if (y_angle < -180) y_angle += 360;

		}
		else if (button == GLUT_RIGHT_BUTTON) {
			xform_mode = XFORM_SCALE;
			float old_size = scale_size;
			scale_size -= (release_y - press_y) / 60.0;
			if (scale_size < 0) scale_size = old_size;
		}
		else if (button == GLUT_MIDDLE_BUTTON) {
			xform_mode = XFORM_TRANSLATE;
			xTrans -= (release_x - press_x) / 100.0;
			yTrans -= (release_y - press_y) / 100.0;
		}
	}
	drawscene();
}

void mymotion(int x, int y)
{
	static int count = 0;
	if (xform_mode == XFORM_ROTATE) {
		x_angle += (x - press_x) / 10.0;
		if (x_angle > 180) x_angle -= 360;
		else if (x_angle < -180) x_angle += 360;
		press_x = x;

		y_angle += (y - press_y) / 10.0;
		if (y_angle > 180) y_angle -= 360;
		else if (y_angle < -180) y_angle += 360;
		press_y = y;
	}
	else if (xform_mode == XFORM_SCALE) {
		float old_size = scale_size;
		scale_size -= (y - press_y) / 60.0;
		if (scale_size < 0) scale_size = old_size;
		press_y = y;
	}
	else if (xform_mode == XFORM_TRANSLATE) {
		xTrans -= (x - press_x) / 100.0;
		press_x = x;
		yTrans -= (y - press_y) / 100.0;
		press_y = y;
	}

	count++;
	if (count >= 5) { drawscene(); count = 0; }
}
void mykey(unsigned char key, int x, int y)
{
	if (key == '0') {
		glDisable(GL_LIGHT0);
		glDisable(GL_LIGHT1);
		glDisable(GL_LIGHT2);
	}
	if (key == '1') {
		glDisable(GL_LIGHT0);
		glDisable(GL_LIGHT2);
		glEnable(GL_LIGHT1);
	}
	if (key == '2') {
		glDisable(GL_LIGHT1);
		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHT2);
	}
	if (key == '3') {
		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHT1);
		glEnable(GL_LIGHT2);
	}
	if (key == 'n' || 'N') {
		TexFilter1 = GL_NEAREST;
		TexFilter2 = GL_NEAREST;
	}
	if (key == 'l' || 'L') {
		TexFilter1 = GL_LINEAR;
		TexFilter2 = GL_LINEAR; 
	}
	if (key == 'x' || 'X') {
		
	}
	if (key == 'z' || 'Z') {
		glEnable(GL_TEXTURE_2D);
	}
	
	drawscene();
}
void myinit() {
	
	glClearColor(0, 0, 0, 1);

	data1 = stbi_load("floor.bmp", &width, &height, &bitdepth, 0);
	
	glGenTextures(1, &textureNames);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data1);


	glShadeModel(GL_SMOOTH);

	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);
	glEnable(GL_AUTO_NORMAL);

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
	glLightfv(GL_LIGHT1, GL_POSITION, light1_position);

	glLightfv(GL_LIGHT2, GL_AMBIENT, light2_ambient);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, light2_diffuse);
	glLightfv(GL_LIGHT2, GL_SPECULAR, light2_specular);
	glLightfv(GL_LIGHT2, GL_POSITION, light2_position);

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	

}


int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(1000, 600);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("방만들기 15010970");
	myinit();
	glutDisplayFunc(drawscene);
	glutMouseFunc(mymouse);
	glutMotionFunc(mymotion);
	glutKeyboardFunc(mykey);
	glutReshapeFunc(reshape);
	glutMainLoop();
}