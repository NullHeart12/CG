#pragma once
#ifndef MESH_H
#define MESH_H

#include <vector>
#include <iostream>
using namespace std;

enum MouseState//the state of mouse
{
	up = 0, down = 1
};

class Change//the class of change
{
public:
	double dx, dy, dz;//the change of the coordinate
	double angle_x, angle_y;//the change of the angle
	double old_x, old_y;//the old coordinate of the mouse
	int mouse_state;//the state of mouse
	double scale;//the change of the scale
	//Change() {}
	Change(double dx = 0, double dy = 0, double dz = 0, double angle_x = 0, double angle_y = 0, double scale = 1)
		:dx(dx), dy(dy), dz(dz), angle_x(angle_x), angle_y(angle_y), scale(scale) {}
	~Change() {}
};

class Vertex//the class of vertex
{
public:
	double x, y, z;//the coordinate of the vertex
	vector<double> normal;//the normal of the vertex
	Vertex() {}
	Vertex(double x, double y, double z) :x(x), y(y), z(z) { normal = { 0,0,0 }; }
	~Vertex() {}
};

class Face//the class of face
{
public:
	int ver_num;//the number of vertexs
	vector<int> index;//the index of vertexs
	vector<double> normal;//the normal of the face
	Face() {}
	Face(int ver_num, vector<int> index) :ver_num(ver_num), index(index) {}
	~Face() { index.clear(); normal.clear(); }
};

class Mesh//the class of mesh
{
public:
	//the data of the class
	int ver_num, face_num;//the number of vertexs and faces
	vector<Vertex> vertexs;//the vector of vertexs
	vector<Face> faces;//the vector of faces

	//the constructor and destructor of the class
	Mesh() {}
	Mesh(int ver_num, int face_num) :ver_num(ver_num), face_num(face_num) {}
	~Mesh() {}

	//the function of the class
	void normal(Face& face);//calculate the normal of the face
	void all_normal_of_faces();//calculate the normal of all faces
	void normal(int index);//calculate the normal of the vertex
	void all_normal_of_vertexs();//calculate the normal of all vertexs
};

#endif // !1