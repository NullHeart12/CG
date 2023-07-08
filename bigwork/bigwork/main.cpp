#include <iostream>
#include <GL/glut.h>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <Windows.h>
#include <random>
#include "Mesh.h"
using namespace std;

Mesh* mesh;//the mesh
Change change;//the change of the mesh
Change copy_;//the copy of the change,to reset the mesh
int LastClickTime = 0;//the time of the last click
GLdouble coordinate[4][4][3];//the coordinate of the mesh
vector<int> error_index;//the index of the error vertexs

void get_off(const string& filename)//get the data from the off file
{
	fstream fin(filename,ios::in);//open the file
	if (!fin.is_open())//if the file is not open, exit
	{
		cout<<"Errors occur when opening the file"<<endl;
		exit(0);
	}
	string type;//the type of the file
	fin >> type;
	//cout << "the type of the file is " << type << endl;
	int ver_num, face_num, invalide_num;//the number of vertexs, faces and invalide data
	fin >> ver_num >> face_num >> invalide_num;
	//cout<<ver_num<<" "<<face_num<<" "<<invalide_num<<endl;
	mesh = new Mesh(ver_num, face_num);
	for (int i = 0; i < ver_num; i++)//get the data of vertexs
	{
		float x, y, z;
		fin>> x >> y >> z;
		Vertex vertex(x, y, z);
		mesh->vertexs.emplace_back(vertex);
	}
	for (int i = 0; i < face_num; i++)//get the data of faces
	{
		int ver_num;
		fin >> ver_num;
		vector<int> index(ver_num);
		fin >> index[0] >> index[1] >> index[2];
		Face face(ver_num, index);
		mesh->faces.emplace_back(face);
	}
	//cout<<mesh.faces.size()<< ' ' << mesh.vertexs.size() << endl;
	fin.close();
	mesh->all_normal_of_faces();
	mesh->all_normal_of_vertexs();
	mesh->copy = mesh->vertexs;
}

void show_data()//for test
{
	//cout<<mesh.ver_num<<" "<<mesh.face_num<<endl;
	//cout<<mesh.vertexs.size()<<" "<<mesh.faces.size()<<endl;
	for (int i = 0; i < mesh->ver_num; i++)
		cout << setw(15) << mesh->vertexs[i].x << setw(15) << mesh->vertexs[i].y << setw(15) << mesh->vertexs[i].z << endl;
	for (int i = 0; i < mesh->face_num; i++)
		cout << mesh->faces[i].ver_num << setw(15) << mesh->faces[i].index[0] << setw(15) << mesh->faces[i].index[1] << setw(15) << mesh->faces[i].index[2] << endl;
}

void KeyBoardEvent(unsigned char key, int x, int y)//keyboard event
{
	switch (key)
	{
	case 'w':
		change.dy += 0.05;
		break;
	case 's':
		change.dy += -0.05;
		break;
	case 'a':
		change.dx += -0.05;
		break;
	case 'd':
		change.dx += 0.05;
		break;
	case 'q':
		change.dz += 0.05;
		break;
	case 'e':
		change.dz -= 0.05;
		break;
	default:
		MessageBox(NULL, L"oh,bro,you pushed the wrong button", L"error", MB_OK);
		//cout << "fuck gay,you push the wrong button" << endl;
		break;
	}
}

void MouseEvent(int button, int state, int x, int y)//mouse event
{
	float cmp = 0.1;
	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
			change.old_x = x;
			change.old_y = y;
			change.mouse_state = down;
			//int currentClickTime = glutGet(GLUT_ELAPSED_TIME);
			//int interVal = currentClickTime - LastClickTime;
			//cout << x << ',' << y << endl;

			//if (x > coordinate[0][0][0] && x<coordinate[0][3][0] && y>coordinate[0][1][1] && y < coordinate[0][0][1] && interVal < 300)
			//{
			//	cout << 1 << endl;
			//	change.angle_y += 0.05;
			//}
			//else if (x > coordinate[0][0][0] && x<coordinate[0][3][0] && y>coordinate[0][1][1] && y < coordinate[0][0][1])
			//{
			//	cout << 2 << endl;
			//	change.dy += 0.05;
			//}

			if (x > 724 && x < 768 && y>4 && y < 42)// && interVal < 300)
				change.angle_y -= 3;
			//else if (x > 724 && x < 768 && y>4 && y < 42 && interVal >= 300)
			//	change.dy += 0.05;
			if (x > 722 && x < 769 && y>827 && y < 866)// && interVal < 300)
				change.angle_y += 3;
			//else if (x > 722 && x < 769 && y>827 && y < 866)
			//	change.dy -= 0.05;
			if (x > 9 && x < 53 && y>412 && y < 457)// && interVal < 300)
				change.angle_x -= 3;
			//else if (x > 9 && x < 53 && y>412 && y < 457)
			//	change.dx += 0.05;
			if (x > 1441 && x < 1485 && y>414 && y < 455)// && interVal < 300)
				change.angle_x += 3;
			//else if (x > 1441 && x < 1485 && y>414 && y < 455)
			//	change.dx -= 0.05;

			//LastClickTime = glutGet(GLUT_ELAPSED_TIME);
		}
		else if (state == GLUT_UP)
			change.mouse_state = up;
	}
	else if (button == GLUT_RIGHT_BUTTON)
	{
		change = copy_;
		mesh->update(copy_);
	}
	else if (button == 3)
	{
		change.scale += 0.05;
		mesh->flag = 1;
	}
	else if (button == 4)
	{
		if (change.scale <= 0)
		{	
			change.scale = 0.05;
		}
		change.scale -= 0.05;
		mesh->flag = 1;
	}
	//if (button == 3 || button == 4)
	//{
	//	for (int i = 0; i < mesh->ver_num; i++)
	//	{
	//		Vertex* ver = &mesh->vertexs[i];
	//		ver->normal[0] += ver->normal[0]*change.scale;
	//		ver->normal[1] += ver->normal[1]*change.scale;
	//		ver->normal[2] += ver->normal[2]*change.scale;
	//	}
	//}
}

void MouseMotionEvent(int x, int y)//mouse motion event
{
	if (change.mouse_state == down)
	{
		change.angle_x += (x - change.old_x)*0.3;
		change.angle_y += (y - change.old_y)*0.3;
		change.old_x = x;
		change.old_y = y;
	}
}

void draw()//draw the mesh
{
	for (int i = 0; i < mesh->face_num; i++)
	{	
		Face face = mesh->faces[i];
		glBegin(GL_TRIANGLES); 
		//glNormal3d(face.normal[0], face.normal[1], face.normal[2]);
		//cout << face.normal[0] << ',' << face.normal[1] << ',' << face.normal[2] << endl;
		for (int i = 0; i < face.ver_num; i++)
		{
			Vertex ver = mesh->vertexs[face.index[i]];
			glNormal3d(ver.normal[0], ver.normal[1], ver.normal[2]);
			glVertex3d(ver.x, ver.y, ver.z);
		}
		glEnd();
	}
}

void draw_square()//draw the squares
{
	GLfloat modeView[16];
	GLfloat projection[16];
	GLint viewport[4];
	GLdouble winX, winY, winZ;
	GLdouble posX, posY, posZ;
	glGetFloatv(GL_MODELVIEW_MATRIX, modeView);
	glGetFloatv(GL_PROJECTION_MATRIX, projection);
	glGetIntegerv(GL_VIEWPORT, viewport);

	glBegin(GL_QUADS);
	glColor3d(0, 1, 0);
	glVertex3d(-0.03, 0.91, 0);
	glVertex3d(-0.03, 1, 0);
	glVertex3d(0.03, 1, 0);
	glVertex3d(0.03, 0.91, 0);
	glEnd();
	gluProject(-0.03, 0.91, 0, (GLdouble*)modeView,(GLdouble*)projection, viewport, &winX, &winY, &winZ);
	gluUnProject(winX, winY, winZ, (GLdouble*)modeView, (GLdouble*)projection, viewport,
		&coordinate[0][0][0], &coordinate[0][0][1], &coordinate[0][0][2]);
	gluProject(-0.03, 1, 0, (GLdouble*)modeView,(GLdouble*)projection, viewport, &winX, &winY, &winZ);
	gluUnProject(winX, winY, winZ, (GLdouble*)modeView, (GLdouble*)projection, viewport,
		&coordinate[0][1][0], &coordinate[0][1][1], &coordinate[0][1][2]);
	gluProject(0.03, 1, 0, (GLdouble*)modeView,(GLdouble*)projection, viewport, &winX, &winY, &winZ);
	gluUnProject(winX, winY, winZ, (GLdouble*)modeView, (GLdouble*)projection, viewport,
		&coordinate[0][2][0], &coordinate[0][2][1], &coordinate[0][2][2]);
	gluProject(0.03, 0.91, 0, (GLdouble*)modeView,(GLdouble*)projection, viewport, &winX, &winY, &winZ);
	gluUnProject(winX, winY, winZ, (GLdouble*)modeView, (GLdouble*)projection, viewport,
		&coordinate[0][3][0], &coordinate[0][3][1], &coordinate[0][3][2]);

	glBegin(GL_QUADS);
	glColor3d(1, 0, 0);
	glVertex3d(-0.03, -0.91, 0);
	glVertex3d(-0.03, -1, 0);
	glVertex3d(0.03, -1, 0);
	glVertex3d(0.03, -0.91, 0);
	glEnd();
	gluProject(-0.03, -0.91, 0, (GLdouble*)modeView, (GLdouble*)projection, viewport, &winX, &winY, &winZ);
	gluUnProject(winX, winY, winZ, (GLdouble*)modeView, (GLdouble*)projection, viewport,
		&coordinate[1][0][0], &coordinate[1][0][1], &coordinate[1][0][2]);
	gluProject(-0.03, -1, 0, (GLdouble*)modeView, (GLdouble*)projection, viewport, &winX, &winY, &winZ);
	gluUnProject(winX, winY, winZ, (GLdouble*)modeView, (GLdouble*)projection, viewport,
		&coordinate[1][1][0], &coordinate[1][1][1], &coordinate[1][1][2]);
	gluProject(0.03, -1, 0, (GLdouble*)modeView, (GLdouble*)projection, viewport, &winX, &winY, &winZ);
	gluUnProject(winX, winY, winZ, (GLdouble*)modeView, (GLdouble*)projection, viewport,
		&coordinate[1][2][0], &coordinate[1][2][1], &coordinate[1][2][2]);
	gluProject(0.03, -0.91, 0, (GLdouble*)modeView, (GLdouble*)projection, viewport, &winX, &winY, &winZ);
	gluUnProject(winX, winY, winZ, (GLdouble*)modeView, (GLdouble*)projection, viewport,
		&coordinate[1][3][0], &coordinate[1][3][1], &coordinate[1][3][2]);

	glBegin(GL_QUADS);
	glColor3d(0, 0, 1);
	glVertex3d(0.94, 0.05, 0);
	glVertex3d(0.94, -0.05, 0);
	glVertex3d(1, -0.05, 0);
	glVertex3d(1, 0.05, 0);
	glEnd();
	gluProject(0.94, 0.05, 0, (GLdouble*)modeView, (GLdouble*)projection, viewport, &winX, &winY, &winZ);
	gluUnProject(winX, winY, winZ, (GLdouble*)modeView, (GLdouble*)projection, viewport,
		&coordinate[2][0][0], &coordinate[2][0][1], &coordinate[2][0][2]);
	gluProject(0.94, -0.05, 0, (GLdouble*)modeView, (GLdouble*)projection, viewport, &winX, &winY, &winZ);
	gluUnProject(winX, winY, winZ, (GLdouble*)modeView, (GLdouble*)projection, viewport,
		&coordinate[2][1][0], &coordinate[2][1][1], &coordinate[2][1][2]);
	gluProject(1, -0.05, 0, (GLdouble*)modeView, (GLdouble*)projection, viewport, &winX, &winY, &winZ);
	gluUnProject(winX, winY, winZ, (GLdouble*)modeView, (GLdouble*)projection, viewport,
		&coordinate[2][2][0], &coordinate[2][2][1], &coordinate[2][2][2]);
	gluProject(1, 0.05, 0, (GLdouble*)modeView, (GLdouble*)projection, viewport, &winX, &winY, &winZ);
	gluUnProject(winX, winY, winZ, (GLdouble*)modeView, (GLdouble*)projection, viewport,
		&coordinate[2][3][0], &coordinate[2][3][1], &coordinate[2][3][2]);

	glBegin(GL_QUADS);
	glColor3d(1, 1, 0);
	glVertex3d(-0.94, 0.05, 0);
	glVertex3d(-0.94, -0.05, 0);
	glVertex3d(-1, -0.05, 0);
	glVertex3d(-1, 0.05, 0);
	glEnd();
	gluProject(0.94, 0.05, 0, (GLdouble*)modeView, (GLdouble*)projection, viewport, &winX, &winY, &winZ);
	gluUnProject(winX, winY, winZ, (GLdouble*)modeView, (GLdouble*)projection, viewport,
		&coordinate[3][0][0], &coordinate[3][0][1], &coordinate[3][0][2]);
	gluProject(0.94, -0.05, 0, (GLdouble*)modeView, (GLdouble*)projection, viewport, &winX, &winY, &winZ);
	gluUnProject(winX, winY, winZ, (GLdouble*)modeView, (GLdouble*)projection, viewport,
		&coordinate[3][1][0], &coordinate[3][1][1], &coordinate[3][1][2]);
	gluProject(1, -0.05, 0, (GLdouble*)modeView, (GLdouble*)projection, viewport, &winX, &winY, &winZ);
	gluUnProject(winX, winY, winZ, (GLdouble*)modeView, (GLdouble*)projection, viewport,
		&coordinate[3][2][0], &coordinate[3][2][1], &coordinate[3][2][2]);
	gluProject(1, 0.05, 0, (GLdouble*)modeView, (GLdouble*)projection, viewport, &winX, &winY, &winZ);
	gluUnProject(winX, winY, winZ, (GLdouble*)modeView, (GLdouble*)projection, viewport,
		&coordinate[3][3][0], &coordinate[3][3][1], &coordinate[3][3][2]);
	
	//for (int i = 0; i < 4; i++)
	//{
	//	for (int j = 0; j < 4; j++)
	//	{
	//		for (int k = 0; k < 3; k++)
	//		{
	//			cout << coordinate[i][j][k] << ' ';
	//		}
	//		cout << endl;
	//	}
	//}
}

void light_init()//init the light
{
	GLfloat light_position1[] = {0,5,2,1};
	GLfloat light_ambient1[] = { 0,0,0,1 };
	GLfloat light_diffuse1[] = { 1,1,1,1 };
	GLfloat light_specular1[] = { 1,1,1,1 };
	
	GLfloat light_position2[] = { 0,-5,2,1 };
	GLfloat light_ambient2[] = { 0,0,0,1 };
	GLfloat light_diffuse2[] = { 1,1,1,1 };
	GLfloat light_specular2[] = { 1,1,1,1 };

	GLfloat material_ambient[] = { 0,0,0.2,1 };
	GLfloat material_diffuse[] = { 0.753, 0.753, 0.753,1 };
	GLfloat material_specular[] = { 1,1,1,1 };
	GLfloat material_emission[] = { 0,0,0,1 };
	GLfloat material_shininess[] = { 30.0 };
	
	//random_device rand;
	//mt19937 gen(rand());
	//uniform_real_distribution<float> dis(0, 1);
	//float r = dis(gen) + 0.0f;
	//float g = dis(gen) + 0.0f;
	//float b = dis(gen) + 0.0f;
	//GLfloat material_ambient[] = { 0,0,0,1 };
	//GLfloat material_diffuse[] = { r, g, b,1 };
	//GLfloat material_specular[] = { 1,1,1,1 };
	//GLfloat material_emission[] = { 0,0,0,1 };
	//GLfloat material_shininess[] = { 30.0 };

	glLightfv(GL_LIGHT0, GL_POSITION, light_position1);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.08);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient1);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse1);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular1);

	glLightfv(GL_LIGHT1, GL_POSITION, light_position2);
	glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient2);
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.08);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse2);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular2);

	glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
	glMaterialfv(GL_FRONT, GL_EMISSION, material_emission);
	glMaterialfv(GL_FRONT, GL_SHININESS, material_shininess);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);

	glClearColor(1, 1, 1, 1);
}

void display()//display the mesh
{
	//glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 1, 0.001, 30);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0,0,1.75,0,0,0,0,1,0);

	glPushMatrix();
	
	glScaled(change.scale, change.scale, change.scale);
	if (mesh->flag)
		mesh->update(change);
	glTranslated(change.dx, change.dy, change.dz);
	glRotated(change.angle_x, 0, 1, 0);
	glRotated(change.angle_y, 1, 0, 0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glColor3d(0, 0, 0);
	draw();

	//for (int i = 0; i < mesh->ver_num; i++)
	//{
	//	//glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
	//	//glBegin(GL_POINTS);
	//	//glVertex3d(mesh->vertexs[i].x, mesh->vertexs[i].y, mesh->vertexs[i].z);
	//	//glEnd();
	//	//if (mesh->vertexs[i].normal[0] < 0&& mesh->vertexs[i].normal[1] > 0&& mesh->vertexs[i].normal[2] < 0)
	//	//if (mesh->vertexs[i].x < 0|| mesh->vertexs[i].y<0|| mesh->vertexs[i].z<0) continue;
	//	{
	//		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//		glBegin(GL_LINES);
	//		glVertex3d(mesh->vertexs[i].x, mesh->vertexs[i].y, mesh->vertexs[i].z);
	//		glVertex3d(mesh->vertexs[i].x + mesh->vertexs[i].normal[0]/50,
	//			mesh->vertexs[i].y + mesh->vertexs[i].normal[1]/50, mesh->vertexs[i].z + mesh->vertexs[i].normal[2]/50);
	//		glEnd();
	//	}
	//}
	//for (int i = 0; i < mesh->vertexs.size(); i++)
	//{
	//	glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
	//	//if (mesh->vertexs[i].x > 0)
	//	{
	//		glBegin(GL_POINTS);
	//		glVertex3d(mesh->vertexs[i].x, mesh->vertexs[i].y, mesh->vertexs[i].z);
	//		glEnd();
	//	}
	//}
	//for (int i = 0; i < error_index.size(); i++)
	//{
	//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//	glBegin(GL_LINES);
	//	Vertex ver = mesh->vertexs[error_index[i]];
	//	glVertex3d(ver.x, ver.y, ver.z);
	//	glVertex3d(ver.x + ver.normal[0]/30, ver.y + ver.normal[1]/30, ver.z + ver.normal[2]/30);
	//	glEnd();
	//}
	
	glPopMatrix();

	glDisable(GL_LIGHTING);
	glPopMatrix();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	draw_square();
	glPopMatrix();
	glEnable(GL_LIGHTING);

	glFlush();
	glutSwapBuffers();
}

void test()//test the normal of vertexs
{
	for (int i = 0; i < mesh->vertexs.size(); i++)
	{
		Vertex ver = mesh->vertexs[i];
		if (pow(ver.normal[0] + ver.x, 2) + pow(ver.normal[1] + ver.y, 2) + pow(ver.normal[2] + ver.z, 2) < 1)
		{
			error_index.emplace_back(i);
			cout << "shit" << endl;
		}
	}
}

int main(int argc, char** argv)
{
	//get_off("D:\\study\\CG\\hfut\\exp\\Plane.off");
	get_off(argv[1]);
	//get_off("Plane.off");
	//mesh->update(change);
	//show_data();
	//test();

	glutInit(&argc, argv);
	glutInitWindowSize(800, 450);
	glutInitWindowPosition(300, 200);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

	glutCreateWindow("Plane");

	glutKeyboardFunc(KeyBoardEvent);//keyboard event
	glutMouseFunc(MouseEvent);//mouse event
	glutMotionFunc(MouseMotionEvent);//mouse motion event
	glutDisplayFunc(display);
	glutIdleFunc(display);

	light_init();//initial the light
	glutMainLoop();

	delete mesh;
	return 0;
}



//#include <GL/glut.h>
//
//void init() {
//	GLfloat light_position[] = { 0, 0, 2, 1 }; // ��Դλ��
//	GLfloat light_ambient[] = { 0.2, 0.2, 0.2, 1.0 }; // ������
//	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 }; // �������
//	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 }; // ���淴���
//	GLfloat material_ambient[] = { 0.7, 0.7, 0.7, 1.0 }; // ���廷����
//	GLfloat material_diffuse[] = { 0.8, 0.8, 0.8, 1.0 }; // �����������
//	GLfloat material_specular[] = { 1.0, 1.0, 1.0, 1.0 }; // ���徵�淴���
//	GLfloat material_shininess[] = { 100.0 }; // ���淴���ĸ߹�ָ��
//
//	//glEnable(GL_LIGHTING); // ���ù���
//	//glEnable(GL_LIGHT0); // ���ù�Դ0
//
//	//glLightfv(GL_LIGHT0, GL_POSITION, light_position); // ���ù�Դλ��
//	//glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient); // ���û�����
//	//glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse); // �����������
//	//glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular); // ���þ��淴���
//
//	//glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient); // �������廷����
//	//glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse); // ���������������
//	//glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular); // �������徵�淴���
//	//glMaterialfv(GL_FRONT, GL_SHININESS, material_shininess); // ��������߹�ָ��
//
//	glEnable(GL_DEPTH_TEST); // ������Ȳ���
//}
//
//void display() {
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	glColor3d(0, 0, 0);
//
//	// ��������
//	glBegin(GL_TRIANGLES);
//	glNormal3f(0.0, 0.0, 1.0); // ���ö��㷨������
//	glVertex3f(-1.0, -1.0, 0.0);
//	glVertex3f(1.0, -1.0, 0.0);
//	glVertex3f(0.0, 1.0, 0.0);
//	glEnd();
//
//	glFlush();
//	
//}
//
//int main(int argc, char** argv) {
//	glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_float | GLUT_RGB | GLUT_DEPTH);
//	glutInitWindowSize(400, 400);
//	glutCreateWindow("Local Lighting Example");
//	init();
//	glutDisplayFunc(display);
//	glutMainLoop();
//	return 0;
//}

//
//�����ͼ��ѧʵ��2
// ���ߣ�ɽ����ѧ��������ذ�frankdura
// Standard include files
//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <ctype.h>
//#include <math.h>
//#include <assert.h>
//#include<string>
//#include<vector>
//#include<iostream>
//#include <fstream>
//#include <GL/glut.h>
////#include <glut/glut.h>
//using namespace std;
////ֻʹ��glut�㹻
////֧��ƽ����ת����
////֧�ֵ�������ɫ�ʺͻ���ɫ��
////֧��off/obj/stl
//int if_face = 0, if_line = 0, if_point = 0;
////�ж����ּ�����Ϣ�Ƿ�չʾ
//static GLfloat my_set_material[] = { 1.0, 1.0, 0.1, 0.8 };
//int if_control_move = 0;
////static char* name2 = "/Users/frankdura/Desktop/CG_playground/b.stl";
////string fname = "/Users/frankdura/Desktop/CG_playground/ddd.obj";
//static char* filename = const_cast<char*>("D:\\study\\CG\\hfut\\exp\\Plane.off");//"/Users/frankdura/Desktop/CG_playground/bunny.off";
////չʾĿ¼�嵥��
///*
// obj:ddd.obj   bunny.obj
// off:bunny.off
// stl:b.stl
// */
// //���ù�Դ��λ��
//
//static GLfloat light0_position[] = { 4.0, 4.0, 4.0, 0.0 };
//static GLfloat light1_position[] = { -3.0, -3.0, -3.0, 0.0 };
//
//typedef struct Vertex {
//    //������άͼ�ε�
//    //����face�ṹ����
//    float x, y, z;
//} Vertex;
//typedef struct Face {
//    //����Σ������Σ���Ľṹ��
//    Face(void) : vert_number(0), verts(0) {};
//    int vert_number;        //��¼����ĸ���
//    Vertex** verts;          //����һ��������� �������飨�������꣩
//    float normal[3];         //��¼��ķ��������ֱ���x��y��z��������
//    //ע���ķ�����ͨ���������Ϣ����õ���
//    //����objģ����������Ѿ��õ��˷��ߵ���Ϣ
//    //��ô��ֱ�������þͺã�
//} Face;
//typedef struct myMesh {
//    //�Զ���mesh�Ľṹ��
//    myMesh(void) : vert_number(0), verts(0), face_number(0), faces(0) {};
//    //�Զ��幹����
//    int vert_number;        //�ܵĶ������
//    Vertex* verts;             //��������
//    int face_number;                 //�����Ŀ
//    Face* faces;
//    vector<Vertex>point;
//} myMesh;
////����ָ�����ļ���
//static int GLUTwindow = 0;
//static int GLUTwindow_height = 800;     //���ô��ڵĴ�С
//static int GLUTwindow_width = 800;
//static int GLUTmouse[2] = { 0, 0 };
//static int GLUTbutton[3] = { 0, 0, 0 };
//static int GLUTarrows[4] = { 0, 0, 0, 0 };
//static int GLUTmodifiers = 0;
//static int scaling = 0;
//static int translating = 0;
//static int rotating = 0;
//static float scale = 1.0;
//static float center[3] = { 0.0, 0.0, 0.0 };
//static float rotation[3] = { 0.0, 0.0, 0.0 };
//static float translation[3] = { 0.0, 0.0, -4.0 };
//static myMesh* mesh = NULL;
//void get_normal(Face& face) {
//    //�����淨�ߣ�
//    //������ķ���
//    //ͨ����ʽ���㣺
//    face.normal[0] = face.normal[1] = face.normal[2] = 0;
//    Vertex* v1 = face.verts[face.vert_number - 1];
//    for (int i = 0; i < face.vert_number; i++) {
//        Vertex* v2 = face.verts[i];
//        //�½����еĵ�
//        face.normal[0] += (v1->y - v2->y) * (v1->z + v2->z);
//        face.normal[1] += (v1->z - v2->z) * (v1->x + v2->x);
//        face.normal[2] += (v1->x - v2->x) * (v1->y + v2->y);
//        //������ɲ�˵Ĺ���
//        v1 = v2;
//    }
//    //�����һ������
//    float squared_normal_length = 0.0;
//    squared_normal_length += face.normal[0] * face.normal[0];
//    squared_normal_length += face.normal[1] * face.normal[1];
//    squared_normal_length += face.normal[2] * face.normal[2];
//    float normal_length = sqrt(squared_normal_length);
//    //�õ���һ������
//    if (normal_length > 1.0E-6) {
//        face.normal[0] /= normal_length;
//        face.normal[1] /= normal_length;
//        face.normal[2] /= normal_length;
//    }
//    //Ȼ����ɹ�һ������
//}
//vector<string> split(const string& str, const string& pattern)
//{
//    //�����ַ������и�
//    //const char* convert to char*
//    char* strc = new char[strlen(str.c_str()) + 1];
//    strcpy(strc, str.c_str());
//    vector<string> resultVec;
//    char* tmpStr = strtok(strc, pattern.c_str());
//    while (tmpStr != NULL)
//    {
//        resultVec.push_back(string(tmpStr));
//        tmpStr = strtok(NULL, pattern.c_str());
//    }
//
//    delete[] strc;
//
//    return resultVec;
//}
//myMesh* ReadASCII(const char* cfilename);
//myMesh* ReadBinary(const char* cfilename);
//myMesh* ReadSTLFile(const char* cfilename)
//{
//    //ֻ�����������㹻�ˣ�
//    if (cfilename == NULL)
//        return 0;
//    std::ifstream in(cfilename, std::ifstream::in);
//    if (!in)
//        return 0;
//    std::string headStr;
//    getline(in, headStr, ' ');
//    in.close();
//    if (headStr.empty())
//        return 0;
//    if (headStr[0] == 's')
//        return ReadASCII(cfilename);
//    else
//        return  ReadBinary(cfilename);
//}
//
//myMesh* ReadASCII(const char* cfilename)
//{
//    std::vector<float> coorX;
//    std::vector<float> coorY;
//    std::vector<float> coorZ;
//    int i = 0, j = 0, cnt = 0, pCnt = 4;
//    char a[100];
//    char str[100];
//    float x = 0, y = 0, z = 0;
//
//    std::ifstream in(cfilename, std::ifstream::in);
//
//    if (!in)
//        return 0;
//    do
//    {
//        i = 0;
//        cnt = 0;
//        in.getline(a, 100, '\n');
//        while (a[i] != '\0')
//        {
//            if (!islower((int)a[i]) && !isupper((int)a[i]) && a[i] != ' ')
//                break;
//            cnt++;
//            i++;
//        }
//
//        while (a[cnt] != '\0')
//        {
//            str[j] = a[cnt];
//            cnt++;
//            j++;
//        }
//        str[j] = '\0';
//        j = 0;
//        if (sscanf(str, "%lf%lf%lf", &x, &y, &z) == 3)
//        {
//            coorX.push_back(x);
//            coorY.push_back(y);
//            coorZ.push_back(z);
//        }
//        pCnt++;
//    } while (!in.eof());
//
//
//
//    return 0;
//}
//
//myMesh* ReadBinary(const char* cfilename)
//{
//    std::vector<GLfloat> coorX;
//    std::vector<GLfloat> coorY;
//    std::vector<GLfloat> coorZ;
//    char str[80];
//    std::ifstream in(cfilename, std::ifstream::in | std::ifstream::binary);
//    if (!in)
//        return 0;
//    //����ʹ�ö����ƶ����ļ�
//    myMesh* meshs = new myMesh();        //�������ǵ�mesh��
//    in.read(str, 80);
//    int triangles;                  //triangles ��¼�����������Ŀ
//    in.read((char*)&triangles, sizeof(int));
//    if (triangles == 0)
//        return 0;
//    for (int i = 0; i < triangles; i++)
//    {
//        //��ʼ��������Ƭ  �����������������++
//        float coorXYZ[12];
//        in.read((char*)coorXYZ, 12 * sizeof(float));
//        for (int j = 1; j < 4; j++)
//        {
//            //�������ֽ���Ϣ
//            //�ֱ���ÿ�������
//            coorX.push_back(coorXYZ[j * 3]);
//            coorY.push_back(coorXYZ[j * 3 + 1]);
//            coorZ.push_back(coorXYZ[j * 3 + 2]);
//            //�������Ϣѹ���ݴ�����
//            //����stl�ļ�����ֻ��Ҫ��������һ��������Ļ��ּ��ɣ�
//        }
//        in.read((char*)coorXYZ, 2);
//    }
//    in.close();
//    //��ṹ�����ת��
//    int vert_number = coorX.size();
//    int face_number = triangles;
//    meshs->verts = new Vertex[vert_number + 1];
//    assert(meshs->verts);
//    //��������Ϣ
//    for (int i = 0; i < vert_number; i++)
//    {
//        Vertex& vert = meshs->verts[meshs->vert_number++];
//        vert.x = coorX[i];
//        vert.y = coorY[i];
//        vert.z = coorZ[i];
//    }
//    //���������Ϣ
//    meshs->faces = new Face[face_number];
//    assert(meshs->faces);
//    int index = 0;
//    for (int i = 0; i < face_number; i++)
//    {
//        Face fa;
//        fa.vert_number = 3;                  //����ֱ������Ϊ��3���ɣ� STL����Ƭ�����ģ�
//        fa.verts = new Vertex * [fa.vert_number];
//        for (int j = 0; j < 3; j++) {
//            fa.verts[j] = &meshs->verts[index++];
//        }
//        get_normal(fa);
//        meshs->faces[meshs->face_number++] = fa;
//        //���ȷ����һά����
//    }
//    return meshs;
//}
//
////��ȡobj�ļ�
//myMesh* ReaderOBj(string fname2) {
//    string line;
//    fstream f;
//    f.open(fname2, ios::in);
//    if (!f.is_open()) {
//        cout << "�ļ��򿪳���" << endl;
//    }
//    vector<vector<GLfloat>> vset;
//    vector<vector<GLint>> fset;
//    int v_counter = 1;
//    int f_counter = 1;
//    while (!f.eof()) {
//        getline(f, line);//�õ�obj�ļ���һ�У���Ϊһ���ַ���
//        vector<string>parameters;
//        string tailMark = " ";
//        string ans = "";
//        line = line.append(tailMark);
//        if (line[0] != 'v' && line[0] != 'f') {
//            continue;
//        }
//        for (int i = 0; i < line.length(); i++) {
//            char ch = line[i];
//            if (ch != ' ') {
//                ans += ch;
//            }
//            else {
//                if (ans != "") {
//                    parameters.push_back(ans); //ȡ���ַ����е�Ԫ�أ��Կո��з�
//                    ans = "";
//                }
//            }
//        }
//        cout << endl;
//        if (parameters[0] == "v") {   //����Ƕ���Ļ�
//            vector<GLfloat>Point;
//            v_counter++;
//            //            cout <<atof( parameters[1].c_str()) << "--" << atof( parameters[2].c_str()) <<" --  " << atof( parameters[3].c_str());
//            Point.push_back(atof(parameters[1].c_str()));
//            Point.push_back(atof(parameters[2].c_str()));
//            Point.push_back(atof(parameters[3].c_str()));
//            vset.push_back(Point);
//        }
//        else if (parameters[0] == "f") {   //�������Ļ�����Ŷ��������
//            vector<GLint>vIndexSets;          //��ʱ��ŵ�ļ���
//            for (int i = 1; i < 4; i++) {
//                string x = parameters[i];
//                string ans = "";
//                for (int j = 0; j < x.length(); j++) {   //������/��
//                    char ch = x[j];
//                    if (ch != '/') {
//                        ans += ch;
//                    }
//                    else {
//                        break;
//                    }
//                }
//                vector<string >res = split(ans, "/");
//                int index = atof(res[0].c_str());
//                index--;//��Ϊ����������obj�ļ����Ǵ�1��ʼ�ģ������Ǵ�ŵĶ���vector�Ǵ�0��ʼ�ģ����Ҫ��1
//                vIndexSets.push_back(index);
//            }
//            fset.push_back(vIndexSets);
//        }
//
//    }
//    f.close();
//    myMesh* meshs = new myMesh();        //�������ǵ�mesh��
//    //    cout << fset.size() << endl;
//    //    cout << vset.size() << endl;
//        //��ṹ�����ת��
//    int vert_number = vset.size();
//    int face_number = fset.size();
//    meshs->verts = new Vertex[vert_number + 1];
//    assert(meshs->verts);
//    //����mesh����Ϣ
//    //----------------��������Ϣ --------------
//    for (int i = 0; i < vset.size(); i++)
//    {
//        Vertex& vert = meshs->verts[meshs->vert_number++];
//        vert.x = vset[i][0];
//        vert.y = vset[i][1];
//        vert.z = vset[i][2];
//    }
//    //----------------��������Ϣ --------------
//    meshs->faces = new Face[face_number];
//    assert(meshs->faces);
//    for (int i = 0; i < fset.size(); i++)
//    {
//        Face a;
//        a.vert_number = fset[i].size();
//        a.verts = new Vertex * [fset[i].size()];
//        for (int j = 0; j < fset[i].size(); j++) {
//            a.verts[j] = &meshs->verts[fset[i][j]];
//        }
//        get_normal(a);
//        meshs->faces[meshs->face_number++] = a;
//        //���ȷ����һά����
//    }
//    return meshs;
//}
////��ȡoff�ļ�
//myMesh* ReadOffFile(const char* filename)
//{       /*
//     ����˵���� ���ļ����ж�ȡ,��ȡ����off�ļ�
//     */
//    int i;
//    FILE* fp;                                         //��ʼ�����ļ�
//    if (!(fp = fopen(filename, "r"))) {
//        cout << "�޷����ļ�" << endl;
//        return 0;
//    }
//    myMesh* mesh = new myMesh();        //�������ǵ�mesh��
//    //���ж����ļ��Ĳ���
//    int vert_number = 0;                            //��¼�������
//    int face_number = 0;                                    //��¼��ĸ���
//    int line_number = 0;                                   //��¼�ߵĸ���
//    int line_count = 0;                               //������Ҷ����˼���
//    char buffer[1024];
//    while (fgets(buffer, 1023, fp)) {
//        line_count++;
//        char* bufferp = buffer;
//        while (isspace(*bufferp)) bufferp++;
//        if (*bufferp == '#') continue;
//        if (*bufferp == '\0') continue;
//        if (vert_number == 0) {
//            if (!strstr(bufferp, "OFF")) {
//                if ((sscanf(bufferp, "%d%d%d", &vert_number, &face_number, &line_number) != 3) || (vert_number == 0)) {
//                    cout << "�����﷨����" << endl;
//                    fclose(fp);
//                    return NULL;
//                }
//                //�洢�������Ϣ
//                cout << "aa" << vert_number << "--" << face_number << endl;
//                mesh->verts = new Vertex[vert_number];
//                assert(mesh->verts);
//                //�洢�����Ϣ
//                mesh->faces = new Face[face_number];
//                assert(mesh->faces);
//                //���ͷ�ļ���Ϣ������ô�����ڴ�ռ�
//            }
//        }
//        else if (mesh->vert_number < vert_number) {
//            Vertex& vert = mesh->verts[mesh->vert_number++];
//            if (sscanf(bufferp, "%f%f%f", &(vert.x), &(vert.y), &(vert.z)) != 3) {
//                cout << "�����Ϣ�У����������㣨3����" << endl;
//                fclose(fp);
//                return NULL;
//            }
//        }
//        else if (mesh->face_number < face_number) {
//            Face& face = mesh->faces[mesh->face_number++];          //�½�һ��face����
//            bufferp = strtok(bufferp, " \t");
//            if (bufferp) face.vert_number = atoi(bufferp);
//            else {
//                fclose(fp);
//                return NULL;
//            }
//            face.verts = new Vertex * [face.vert_number];
//            //�����������
//            assert(face.verts);
//            for (i = 0; i < face.vert_number; i++) {
//                bufferp = strtok(NULL, " \t");
//                if (bufferp) face.verts[i] = &(mesh->verts[atoi(bufferp)]);
//                else {
//                    fprintf(stderr, "Syntax error with face on line %d in file %s\n", line_count, filename);
//                    fclose(fp);
//                    return NULL;
//                }
//            }
//            get_normal(face);
//        }
//        else {
//            cout << "��ʽ���ڴ���" << endl;
//            break;
//        }
//    }
//    //�ж�ʵ�ʵ� �� ����Ŀ�Ƿ��Ҫ����Ŀһ����
//    if (face_number != mesh->face_number) {
//        cout << "�����Ŀ��ʵ�ʲ���" << endl;
//    }
//    fclose(fp);
//    return mesh;
//}
//void draw_faces() {
//    for (int i = 0; i < mesh->face_number; i++) {
//        //ע�����ǵĲ�������
//        Face& face = mesh->faces[i];
//        glBegin(GL_POLYGON);              //���ƶ���μ��ɣ�
//        //�ڻ�����Ĺ��������������Ѿ�����õķ�������Ϣ
//        glNormal3fv(face.normal);           //�ڻ������ʱ��ͬʱ���뷨������Ϣ
//        for (int j = 0; j < face.vert_number; j++) {
//            Vertex* vert = face.verts[j];
//            glVertex3f(vert->x, vert->y, vert->z);
//        }
//        glEnd();
//    }
//}
//void draw_points() {
//    //������Ƶ����Ϣ
//    //���ν������Ϣ����б���
//    glColor3f(0.0, 1.0, 0.0);
//    glPointSize(2);
//    glBegin(GL_POINTS);
//    for (int j = 0; j < mesh->vert_number; j++) {
//        glVertex3f(mesh->verts[j].x, mesh->verts[j].y, mesh->verts[j].z);
//    }
//    glEnd();
//    //    for (int i = 0; i < mesh->face_number; i++) {
//    //        Face& face = mesh->faces[i];
//    //        glColor3f(0.0, 1.0, 0.0);
//    //        glPointSize(1);
//    //        glBegin(GL_POINTS);
//    //
//    //                for (int j = 0; j < face.vert_number; j++) {
//    //            Vertex *vert = face.verts[j];
//    //cout << vert->x << " " << vert->y << "  " << vert->z << endl;
//    //            glVertex3f(vert->x, vert->y, vert->z);
//    //        }
//    //        glEnd();
//    //    }
//}
//void draw_lines() {
//    float temp_x, temp_y, temp_z;
//    for (int i = 0; i < mesh->face_number; i++) {
//        Face& face = mesh->faces[i];
//        glColor3f(0, 0, 1);
//        glBegin(GL_LINES);
//        for (int j = 0; j < face.vert_number; j++) {
//            Vertex* vert = face.verts[j];
//            if (j == 0) {
//                temp_x = vert->x;
//                temp_y = vert->y;
//                temp_z = vert->z;
//                continue;
//            }
//            glVertex3f(temp_x, temp_y, temp_z);
//            glVertex3f(vert->x, vert->y, vert->z);
//            temp_x = vert->x;
//            temp_y = vert->y;
//            temp_z = vert->z;
//        }
//        glEnd();
//    }
//}
//
//void GLUTRedraw(void)
//{
//    //���пռ���ػ�
//    glLoadIdentity();
//    glScalef(scale, scale, scale);
//    glTranslatef(translation[0], translation[1], 0.0);
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    gluPerspective(45.0, (GLfloat)GLUTwindow_width / (GLfloat)GLUTwindow_height, 0.1, 100.0);
//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();
//    glTranslatef(translation[0], translation[1], translation[2]);
//    glScalef(scale, scale, scale);
//    //ˢ�·����Ĵ�С
//    glRotatef(rotation[0], 1.0, 0.0, 0.0);
//    glRotatef(rotation[1], 0.0, 1.0, 0.0);          //���Ʋ�ͬ�Ƕ�
//    glRotatef(rotation[2], 0.0, 0.0, 1.0);
//    glTranslatef(-center[0], -center[1], -center[2]);
//    //�ı���ת����
//    glClearColor(1.0, 1.0, 1.0, 1.0);
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    //���ù���
//    //���벻ͬ��Դ��λ��
//    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
//    glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
//    //���������Ϣ
//    //������Ե���������ɫ��ɢ����ɫ����
//    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, my_set_material);
//    // ���濪ʼ���Ʊ���
//    if (if_face == 1)
//        draw_faces();
//    if (if_line == 1)
//        draw_lines();
//    if (if_point == 1)
//        draw_points();
//    glutSwapBuffers();
//}
//void GLUTResize(int w, int h)
//{
//    glViewport(0, 0, w, h);
//    //���û���ק֮���û�ȡ�ĸ߶ȺͿ����Ϣȥ����ȫ�ֱ���
//    GLUTwindow_width = w;
//    GLUTwindow_height = h;
//    glutPostRedisplay();
//}
//void GLUTMotion(int x, int y)
//{
//    //ͨ������¼����������õĻ���ͣ�
//    //�������������¼���ִ����
//    y = GLUTwindow_height - y;
//    if (rotating) {
//        //������ת���ź�
//        rotation[0] += -0.5 * (y - GLUTmouse[1]);
//        rotation[2] += 0.5 * (x - GLUTmouse[0]);
//        //rotation[1] += 0.5 * (x - GLUTmouse[0]);
//        //�������������������ת
//        //���ػ��ʱ��Ϳ�����
//    }
//    else if (scaling) {
//        // ���������ź�
//        //GLUTmouse�洢��֮ǰ��¼�ĵ���Ϣ
//        scale *= exp(2.0 * (float)((x - GLUTmouse[0])) / (float)GLUTwindow_width);
//        //�������ɰ���y������ƿ���:
//        // scale *= exp(2.0 * (float)( (y- GLUTmouse[1])) / (float) GLUTwindow_width);
//    }
//    else if (translating) {
//        // ����ƽ���ź�
//        translation[0] += 2.0 * (float)(x - GLUTmouse[0]) / (float)GLUTwindow_width;
//        translation[1] += 2.0 * (float)(y - GLUTmouse[1]) / (float)GLUTwindow_height;
//    }
//    //��������ק��ת�Ĺ�������Ҫ���ö�������
//    GLUTmouse[0] = x;
//    GLUTmouse[1] = y;
//    //ˢ�¶���
//}
//void GLUTMouse(int button, int state, int x, int y)
//{
//    cout << "���Ƽ������: " << if_control_move << endl;
//    y = GLUTwindow_height - y;
//    int  kind = 0;
//    if (button == GLUT_LEFT_BUTTON && if_control_move) {
//        translating = 1;
//        cout << "float" << endl;
//        kind = 2;
//        rotating = 0;
//        scaling = 0;
//    }
//    else {
//        if (button == GLUT_LEFT_BUTTON && button != GLUT_RIGHT_BUTTON) {
//            kind = 0;
//            rotating = 1;
//            scaling = 0;
//            translating = 0;
//        }
//        else if (button != GLUT_LEFT_BUTTON && button == GLUT_RIGHT_BUTTON) {
//            kind = 1;
//            scaling = 1;
//            rotating = 0;
//            translating = 0;
//        }
//    }
//    if (rotating || scaling || translating) glutIdleFunc(GLUTRedraw);
//    else glutIdleFunc(0);
//    cout << "��ʱ��B ѡ��Ĳ�����" << kind << endl;
//    GLUTbutton[kind] = (state == GLUT_DOWN) ? 1 : 0;
//    GLUTmodifiers = glutGetModifiers();
//    GLUTmouse[0] = x;
//    GLUTmouse[1] = y;
//}
//void GLUTSpecial(int key, int x, int y)
//{
//    y = GLUTwindow_height - y;
//    //��¼�����������λ��
//    GLUTmouse[0] = x;
//    GLUTmouse[1] = y;
//    // Remember modifiers
//    GLUTmodifiers = glutGetModifiers();
//    glutPostRedisplay();
//}
//
//void GLUTKeyboard(unsigned char key, int x, int y)
//{
//    // Process keyboard button event
//    //��������¼�
//    switch (key) {
//    case '1':
//        cout << "��/�رյ����Ϣ" << endl;
//        if_point = 1 - if_point;
//        break;
//    case '2':
//        cout << "��/�ر��ߵ���Ϣ" << endl;
//        if_line = 1 - if_line;
//        break;
//    case '3':
//        cout << "��/�ر������Ϣ" << endl;
//        if_face = 1 - if_face;
//        break;
//        //���ڱ���Ĳ��ʵ���Ϣ
//    case 'z':
//        if_control_move = 1 - if_control_move;
//        break;
//    case 'q':
//        my_set_material[0] += 0.1;
//        break;
//    case 'w':
//        my_set_material[1] += 0.1;
//        break;
//    case 'e':
//        my_set_material[2] += 0.1;
//        break;
//    case 'r':
//        my_set_material[3] += 0.1;
//        break;
//    case 'a':
//        my_set_material[0] -= 0.1;
//        break;
//    case 's':
//        my_set_material[1] -= 0.1;
//        break;
//    case 'd':
//        my_set_material[2] -= 0.1;
//        break;
//    case 'f':
//        my_set_material[3] -= 0.1;
//        break;
//    case '4':
//        for (int i = 0; i < 4; i++) {
//            light0_position[i] += 0.01;
//        }
//        break;
//    case '5':
//        for (int i = 0; i < 4; i++) {
//            light0_position[i] -= 0.01;
//            if (light0_position[i] <= 0)
//                light0_position[i] = 0;
//        }
//        break;
//    case '6':
//        for (int i = 0; i < 4; i++) {
//            cout << light1_position[i] << " ~~ " << endl;
//            light1_position[i] += 0.01;
//
//        }
//        break;
//    case '7':
//        for (int i = 0; i < 4; i++) {
//            light1_position[i] -= 0.01;
//            cout << light1_position[i] << " ~~ " << endl;
//
//            if (light1_position[i] <= 0)
//                light1_position[i] = 0;
//        }
//        break;
//
//    }
//    // Remember mouse position
//    GLUTmouse[0] = x;
//    GLUTmouse[1] = GLUTwindow_height - y;
//    // Remember modifiers
//    GLUTmodifiers = glutGetModifiers();
//}
//
//
//
//void GLUTInit(int* argc, char** argv)
//{
//    // Open window
//    glutInit(argc, argv);
//    glutInitWindowPosition(100, 100);
//    glutInitWindowSize(GLUTwindow_width, GLUTwindow_height);
//    glutInitDisplayMode(GLUT_float | GLUT_RGB | GLUT_DEPTH); // | GLUT_STENCIL
//    GLUTwindow = glutCreateWindow("powerful_reader~");
//    glutReshapeFunc(GLUTResize);
//    //�����ػ���Ϣ
//    glutDisplayFunc(GLUTRedraw);
//    //ע������¼�
//    glutKeyboardFunc(GLUTKeyboard);
//    glutSpecialFunc(GLUTSpecial);
//    glutMouseFunc(GLUTMouse);
//    glutMotionFunc(GLUTMotion);
//    glutIdleFunc(0);
//    // ���ù�����Ϣ
//    static GLfloat lmodel_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
//    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
//    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
//    static GLfloat light0_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
//    //������ɢ��
//    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
//    glEnable(GL_LIGHT0);
//    static GLfloat light1_diffuse[] = { 0.5, 0.5, 0.5, 1.0 };
//    glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
//    glEnable(GL_LIGHT1);
//    glEnable(GL_NORMALIZE);
//    glEnable(GL_LIGHTING);
//    glEnable(GL_DEPTH_TEST);
//}
//void GLUTMainLoop(void)
//{
//    float bbox[2][3] = { { 1.0E30F, 1.0E30F, 1.0E30F }, { -1.0E30F, -1.0E30F, -1.0E30F } };
//    for (int i = 0; i < mesh->vert_number; i++) {
//        Vertex& vert = mesh->verts[i];
//        if (vert.x < bbox[0][0]) bbox[0][0] = vert.x;
//        else if (vert.x > bbox[1][0]) bbox[1][0] = vert.x;
//        if (vert.y < bbox[0][1]) bbox[0][1] = vert.y;
//        else if (vert.y > bbox[1][1]) bbox[1][1] = vert.y;
//        if (vert.z < bbox[0][2]) bbox[0][2] = vert.z;
//        else if (vert.z > bbox[1][2]) bbox[1][2] = vert.z;
//    }
//    // Setup initial viewing scale
//    float dx = bbox[1][0] - bbox[0][0];
//    float dy = bbox[1][1] - bbox[0][1];
//    float dz = bbox[1][2] - bbox[0][2];
//    scale = 2.0 / sqrt(dx * dx + dy * dy + dz * dz);
//    // Setup initial viewing center
//    center[0] = 0.5 * (bbox[1][0] + bbox[0][0]);
//    center[1] = 0.5 * (bbox[1][1] + bbox[0][1]);
//    center[2] = 0.5 * (bbox[1][2] + bbox[0][2]);
//    glutMainLoop();
//    //���㲢�����ӽǱ߿��Լ�����
//}
//int main(int argc, char** argv)
//{
//    GLUTInit(&argc, argv);
//    //mesh = ReaderOBj(fname);       //objreader��
//    //obj��off������
////    mesh = ReadSTLFile(name2);
//    mesh = ReadOffFile(filename);
//    GLUTMainLoop();
//    return 0;
//}
//
