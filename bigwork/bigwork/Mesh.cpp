#include "Mesh.h"
#include <chrono>

void Mesh::normal(Face& face)//calculate the normal of the face
{
	int index1 = face.index[0], index2 = face.index[1], index3 = face.index[2];
	Vertex* ver1 = &vertexs[index1],*ver2 = &vertexs[index2], *ver3 = &vertexs[index3];
	//two lines with direction
	vector<double> line1 = { ver2->x - ver1->x,ver2->y - ver1->y,ver2->z - ver1->z };
	vector<double> line2 = { ver3->x - ver1->x,ver3->y - ver1->y,ver3->z - ver1->z };
	//the normal of the face
	double normal_x = line1[1] * line2[2] - line1[2] * line2[1];
	double normal_y = line1[2] * line2[0] - line1[0] * line2[2];
	double normal_z = line1[0] * line2[1] - line1[1] * line2[0];
	
	for (int i = 0; i < face.index.size(); i++)//add the normal of the face to the vertexs
	{
		Vertex* ver = &vertexs[face.index[i]];
		ver->normal[0] += normal_x;
		ver->normal[1] += normal_y;
		ver->normal[2] += normal_z;
	}
	//normalization of the normal
	face.normal = { normal_x,normal_y,normal_z };
	double um = sqrt(pow(normal_x, 2) + pow(normal_y, 2) + pow(normal_z, 2));//the sum of the square of the normal
	face.normal = { normal_x / um,normal_y / um,normal_z / um };//the normal of the face
}

void Mesh::all_normal_of_faces()//calculate the normal of all faces
{
	auto start = std::chrono::steady_clock::now();
	for (int i = 0; i < faces.size(); i++)
		normal(faces[i]);
	auto end = std::chrono::steady_clock::now();
	chrono::duration<double> diff = end - start;
	//cout << "time of normal of faces: " << diff.count() << " s\n";
	cout << "face:" << faces[0].normal[0] << ' ' << faces[0].normal[1] << ' ' << faces[0].normal[2] << endl;
}

void Mesh::normal(int index)//calculate the normal of the vertex
{
	Vertex* ver = &vertexs[index];//the vertex
	//normalization of the normal
	double quad_sum = sqrt(pow(ver->normal[0], 2) + pow(ver->normal[1], 2) + pow(ver->normal[2], 2));//the sum of the square of the normal
	ver->normal = { ver->normal[0] / quad_sum,ver->normal[1] / quad_sum,ver->normal[2] / quad_sum };//the normal of the vertex
}

void Mesh::all_normal_of_vertexs()//calculate the normal of all vertexs
{
	for (int i = 0; i < vertexs.size(); i++)
		normal(i);
	cout << "vertex:" << vertexs[0].normal[0] << ' ' << vertexs[0].normal[1] << ' ' << vertexs[0].normal[2] << endl;
}

void Mesh::update(const Change& change)
{
	for (int i = 0; i < vertexs.size(); i++)
	{
		vertexs[i].normal[0] = copy[i].normal[0] * change.scale;
		vertexs[i].normal[1] = copy[i].normal[1] * change.scale;
		vertexs[i].normal[2] = copy[i].normal[2] * change.scale;
	}
	flag = 0;
}