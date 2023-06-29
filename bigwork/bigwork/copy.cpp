//#include <gl/glut.h> 
//#include <Windows.h>
//
//static GLfloat angle = 0.0f;
//void myDisplay(void)
//{
//	glClearColor(0.3, 0.7, 0.5, 0);
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  //清理颜色和深度缓存     
//
//	// 创建透视效果视图      
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	gluPerspective(80.0f, 1.0f, 1.0f, 50.0f);
//
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//	gluLookAt(0.0, 0.0, 20.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
//
//	// 定义太阳光源，它是一种白色的光源   
//	{
//		GLfloat sun_light_position[] = { 0.0f, 0.0f, 0.0f, 1.0f }; //光源的位置在世界坐标系圆心，齐次坐标形式
//		GLfloat sun_light_ambient[] = { 1.0f, 1.0f, 1.0f, 1.0f }; //RGBA模式的环境光，为0
//		GLfloat sun_light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f }; //RGBA模式的漫反射光，全白光
//		GLfloat sun_light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };  //RGBA模式下的镜面光 ，全白光
//		glLightfv(GL_LIGHT0, GL_POSITION, sun_light_position);
//		glLightfv(GL_LIGHT0, GL_AMBIENT, sun_light_ambient);
//		glLightfv(GL_LIGHT0, GL_DIFFUSE, sun_light_diffuse);
//		glLightfv(GL_LIGHT0, GL_SPECULAR, sun_light_specular);
//
//		//开启灯光
//		glEnable(GL_LIGHT0);
//		glEnable(GL_LIGHTING);
//		glEnable(GL_DEPTH_TEST);
//	}
//
//	// 定义太阳的材质并绘制太阳    
//	{
//		GLfloat sun_mat_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };  //定义材质的环境光颜色，为0
//		GLfloat sun_mat_diffuse[] = { 0.0f, 0.0f, 0.0f, 1.0f };  //定义材质的漫反射光颜色，为0
//		GLfloat sun_mat_specular[] = { 0.0f, 0.0f, 0.0f, 1.0f };   //定义材质的镜面反射光颜色，为0
//		GLfloat sun_mat_emission[] = { 0.8f, 0.0f, 0.0f, 1.0f };   //定义材质的辐射广颜色，为偏红色
//		GLfloat sun_mat_shininess = 0.0f;
//		glMaterialfv(GL_FRONT, GL_AMBIENT, sun_mat_ambient);
//		glMaterialfv(GL_FRONT, GL_DIFFUSE, sun_mat_diffuse);
//		glMaterialfv(GL_FRONT, GL_SPECULAR, sun_mat_specular);
//		glMaterialfv(GL_FRONT, GL_EMISSION, sun_mat_emission);
//		glMaterialf(GL_FRONT, GL_SHININESS, sun_mat_shininess);
//		glutSolidSphere(3.0, 40, 32);
//	}
//
//	// 定义地球的材质并绘制地球    
//	{
//		GLfloat earth_mat_ambient[] = { 0.0f, 0.0f, 0.2f, 1.0f };  //定义材质的环境光颜色，骗蓝色
//		GLfloat earth_mat_diffuse[] = { 0.0f, 0.0f, 0.5f, 1.0f };  //定义材质的漫反射光颜色，偏蓝色
//		GLfloat earth_mat_specular[] = { 1.0f, 0.0f, 0.0f, 1.0f };   //定义材质的镜面反射光颜色，红色
//		GLfloat earth_mat_emission[] = { 0.0f, 0.0f, 0.0f, 1.0f };   //定义材质的辐射光颜色，为0
//		GLfloat earth_mat_shininess = 30.0f;
//		glMaterialfv(GL_FRONT, GL_AMBIENT, earth_mat_ambient);
//		glMaterialfv(GL_FRONT, GL_DIFFUSE, earth_mat_diffuse);
//		glMaterialfv(GL_FRONT, GL_SPECULAR, earth_mat_specular);
//		glMaterialfv(GL_FRONT, GL_EMISSION, earth_mat_emission);
//		glMaterialf(GL_FRONT, GL_SHININESS, earth_mat_shininess);
//		glRotatef(angle, 0.0f, -1.0f, 0.0f);
//		glTranslatef(7.0f, 0.0f, 0.0f);
//		glutSolidSphere(3.0, 40, 32);
//	}
//	Sleep(10);
//	glutSwapBuffers();
//}
//
//void myIdle(void)
//{
//	angle += 1.0f;
//	if (angle >= 360.0f)
//		angle = 0.0f;
//	myDisplay();
//}
//
//int main(int argc, char* argv[])
//{
//	glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
//	glutInitWindowPosition(400, 200);
//	glutInitWindowSize(500, 500);
//	glutCreateWindow("OpenGL光照演示");
//	glutDisplayFunc(&myDisplay);
//	glutIdleFunc(&myIdle);
//	glutMainLoop();
//	return 0;
//}

//#include <iostream>
//#include <GL/glut.h>
//#include <vector>
//#include <fstream>
//#include <algorithm>
//#include <iomanip>
//#include <Windows.h>
//#include "Mesh.h"
//using namespace std;
//
//Mesh* mesh;//the mesh
//Change change;//the change of the mesh
//Change copy_;//the copy of the change,to reset the mesh
//vector<int> error_index;
//
//void get_off(const string& filename)//get the data from the off file
//{
//	fstream fin(filename, ios::in);//open the file
//	if (!fin.is_open())//if the file is not open, exit
//	{
//		cout << "Errors occur when opening the file" << endl;
//		exit(0);
//	}
//	string type;//the type of the file
//	fin >> type;
//	//cout << "the type of the file is " << type << endl;
//	int ver_num, face_num, invalide_num;//the number of vertexs, faces and invalide data
//	fin >> ver_num >> face_num >> invalide_num;
//	//cout<<ver_num<<" "<<face_num<<" "<<invalide_num<<endl;
//	mesh = new Mesh(ver_num, face_num);
//	for (int i = 0; i < ver_num; i++)//get the data of vertexs
//	{
//		float x, y, z;
//		fin >> x >> y >> z;
//		Vertex vertex(x, y, z);
//		mesh->vertexs.emplace_back(vertex);
//	}
//	for (int i = 0; i < face_num; i++)//get the data of faces
//	{
//		int ver_num;
//		fin >> ver_num;
//		vector<int> index(ver_num);
//		fin >> index[0] >> index[1] >> index[2];
//		Face face(ver_num, index);
//		mesh->faces.emplace_back(face);
//	}
//	//cout<<mesh.faces.size()<< ' ' << mesh.vertexs.size() << endl;
//	fin.close();
//}
//
//void show_data()//for test
//{
//	//cout<<mesh.ver_num<<" "<<mesh.face_num<<endl;
//	//cout<<mesh.vertexs.size()<<" "<<mesh.faces.size()<<endl;
//	for (int i = 0; i < mesh->ver_num; i++)
//		cout << setw(15) << mesh->vertexs[i].x << setw(15) << mesh->vertexs[i].y << setw(15) << mesh->vertexs[i].z << endl;
//	for (int i = 0; i < mesh->face_num; i++)
//		cout << mesh->faces[i].ver_num << setw(15) << mesh->faces[i].index[0] << setw(15) << mesh->faces[i].index[1] << setw(15) << mesh->faces[i].index[2] << endl;
//}
//
//void KeyBoardEvent(unsigned char key, int x, int y)//keyboard event
//{
//	switch (key)
//	{
//	case 'w':
//		change.dy += 0.05;
//		break;
//	case 's':
//		change.dy += -0.05;
//		break;
//	case 'a':
//		change.dx += -0.05;
//		break;
//	case 'd':
//		change.dx += 0.05;
//		break;
//	case 'q':
//		change.dz += 0.05;
//		break;
//	case 'e':
//		change.dz -= 0.05;
//		break;
//	default:
//		MessageBox(NULL, L"oh,fuck bro,you pushed the wrong button", L"error", MB_OK);
//		//cout << "fuck gay,you push the wrong button" << endl;
//		break;
//	}
//}
//
//void MouseEvent(int button, int state, int x, int y)//mouse event
//{
//	if (button == GLUT_LEFT_BUTTON)
//	{
//		if (state == GLUT_DOWN)
//		{
//			change.old_x = x;
//			change.old_y = y;
//			change.mouse_state = down;
//		}
//		else if (state == GLUT_UP)
//			change.mouse_state = up;
//	}
//	else if (button == GLUT_RIGHT_BUTTON)
//		change = copy_;
//	else if (button == 3)
//		change.scale += 0.05;
//	else if (button == 4)
//		change.scale -= 0.05;
//}
//
//void MouseMotionEvent(int x, int y)
//{
//	if (change.mouse_state == down)
//	{
//		change.angle_x += (x - change.old_x) * 0.3;
//		change.angle_y += (y - change.old_y) * 0.3;
//		change.old_x = x;
//		change.old_y = y;
//	}
//}
//
//void draw()//draw the mesh
//{
//	for (int i = 0; i < mesh->face_num; i++)
//	{
//		glBegin(GL_TRIANGLES);
//		Face face = mesh->faces[i];
//		//glNormal3d(-face.normal[0], face.normal[1], face.normal[2]);
//		//glEnable(GL_NORMALIZE);
//		for (int i = 0; i < face.ver_num; i++)
//		{
//			Vertex ver = mesh->vertexs[face.index[i]];
//			glNormal3d(ver.normal[0], ver.normal[1], ver.normal[2]);
//			glVertex3d(ver.x, ver.y, ver.z);
//		}
//		glEnd();
//	}
//
//}
//
//void light_init()//init the light
//{
//	GLfloat light_position1[] = { 0,0,5,1 };
//	GLfloat light_ambient1[] = { 1,1,1,1 };
//	GLfloat light_diffuse1[] = { 1,1,1,1 };
//	GLfloat light_specular1[] = { 1,1,1,1 };
//
//	GLfloat light_position2[] = { 0,0,-5,1 };
//	GLfloat light_ambient2[] = { 1,1,1,1 };
//	GLfloat light_diffuse2[] = { 1,1,1,1 };
//	GLfloat light_specular2[] = { 1,1,1,1 };
//
//	GLfloat material_ambient[] = { 0,0,0,1 };
//	GLfloat material_diffuse[] = { 0.6,0.5,0.5,1 };
//	GLfloat material_specular[] = { 0.9,0.9,0.9,1 };
//	GLfloat material_emission[] = { 0,0,0,1 };
//	GLfloat material_shininess[] = { 30.0 };
//
//
//	glLightfv(GL_LIGHT0, GL_POSITION, light_position1);
//	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.01);
//	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient1);
//	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse1);
//	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular1);
//
//
//	glLightfv(GL_LIGHT1, GL_POSITION, light_position2);
//	glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient2);
//	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse2);
//	glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular2);
//
//	glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
//	glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
//	glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
//	glMaterialfv(GL_FRONT, GL_EMISSION, material_emission);
//	glMaterialfv(GL_FRONT, GL_SHININESS, material_shininess);
//
//	glEnable(GL_LIGHTING);
//	glEnable(GL_LIGHT0);
//	glEnable(GL_LIGHT1);
//	glShadeModel(GL_SMOOTH);
//	glEnable(GL_CULL_FACE);
//	glEnable(GL_DEPTH_TEST);
//	glDepthMask(GL_FALSE);
//	glDepthFunc(GL_LESS);
//	//glEnable(GL_BLEND);
//}
//
//void display()//display the mesh
//{
//	//1. 在绘制前，开启多边形偏移
//	glEnable(GL_POLYGON_OFFSET_FILL);
//	//2. 指定偏移量,参数一般填 -1 和 -1
//	glPolygonOffset(-1.0, -1.0);
//
//	glClearColor(1, 1, 1, 1);
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	gluPerspective(60, 1, 0.1, 3);
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//	gluLookAt(0, 0, 1.75, 0, 0, 0, 0, 1, 0);
//	light_init();
//
//	glPushMatrix();
//
//	glTranslated(change.dx, change.dy, change.dz);
//	glScaled(change.scale, change.scale, change.scale);
//	glRotated(change.angle_x, 0, 1, 0);
//	glRotated(change.angle_y, 1, 0, 0);
//	glPolygonMode(GL_FRONT, GL_FILL);
//	glColor3d(0, 0, 0);
//	draw();
//
//	//for (int i = 0; i < mesh->ver_num; i++)
//	//{
//	//	//glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
//	//	//glBegin(GL_POINTS);
//	//	//glVertex3d(mesh->vertexs[i].x, mesh->vertexs[i].y, mesh->vertexs[i].z);
//	//	//glEnd();
//	//	//if (mesh->vertexs[i].normal[0] < 0&& mesh->vertexs[i].normal[1] > 0&& mesh->vertexs[i].normal[2] < 0)
//	//	//if (mesh->vertexs[i].x < 0|| mesh->vertexs[i].y<0|| mesh->vertexs[i].z<0) continue;
//	//	{
//	//		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//	//		glBegin(GL_LINES);
//	//		glVertex3d(mesh->vertexs[i].x, mesh->vertexs[i].y, mesh->vertexs[i].z);
//	//		glVertex3d(mesh->vertexs[i].x + mesh->vertexs[i].normal[0]/50,
//	//			mesh->vertexs[i].y + mesh->vertexs[i].normal[1]/50, mesh->vertexs[i].z + mesh->vertexs[i].normal[2]/50);
//	//		glEnd();
//	//	}
//	//}
//
//	//for (int i = 0; i < mesh->vertexs.size(); i++)
//	//{
//	//	glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
//	//	//if (mesh->vertexs[i].x > 0)
//	//	{
//	//		glBegin(GL_POINTS);
//	//		glVertex3d(mesh->vertexs[i].x, mesh->vertexs[i].y, mesh->vertexs[i].z);
//	//		glEnd();
//	//	}
//	//}
//
//	//for (int i = 0; i < error_index.size(); i++)
//	//{
//	//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//	//	glBegin(GL_LINES);
//	//	Vertex ver = mesh->vertexs[error_index[i]];
//	//	glVertex3d(ver.x, ver.y, ver.z);
//	//	glVertex3d(ver.x + ver.normal[0]/30, ver.y + ver.normal[1]/30, ver.z + ver.normal[2]/30);
//	//	glEnd();
//	//}
//
//
//	glShadeModel(GL_SMOOTH);
//	//glutSolidSphere(0.3, 40, 32);
//
//	glPopMatrix();
//
//	glFlush();
//	glutSwapBuffers();
//	//3. 绘制完成后关闭多边形偏移
//	glDisable(GL_POLYGON_OFFSET_FILL);
//}
//
//void test()
//{
//	for (int i = 0; i < mesh->vertexs.size(); i++)
//	{
//		Vertex ver = mesh->vertexs[i];
//		if (pow(ver.normal[0] + ver.x, 2) + pow(ver.normal[1] + ver.y, 2) + pow(ver.normal[2] + ver.z, 2) < 1)
//		{
//			error_index.emplace_back(i);
//			cout << "shit" << endl;
//		}
//	}
//}
//
//int main(int argc, char** argv)
//{
//	//string filename = "D:\\study\\CG\\hfut\\exp\\Plane.off";
//	get_off(argv[1]);
//	mesh->all_normal_of_faces();
//	mesh->all_normal_of_vertexs();
//	//show_data();
//	//test();
//
//	glutInit(&argc, argv);
//	glutInitWindowSize(800, 450);
//	glutInitWindowPosition(300, 200);
//	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
//
//	glutCreateWindow("Plane");
//
//	glutKeyboardFunc(KeyBoardEvent);//keyboard event
//	glutMouseFunc(MouseEvent);//mouse event
//	glutMotionFunc(MouseMotionEvent);//mouse motion event
//	glutDisplayFunc(display);
//	glutIdleFunc(display);
//
//	glutMainLoop();
//
//	delete mesh;
//	return 0;
//}
