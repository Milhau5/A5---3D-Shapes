#include "MyPrimitiveClass.h"
MyPrimitiveClass::MyPrimitiveClass() { }
MyPrimitiveClass::MyPrimitiveClass(const MyPrimitiveClass& other) { }
MyPrimitiveClass& MyPrimitiveClass::operator=(const MyPrimitiveClass& other) { return *this; }
MyPrimitiveClass::~MyPrimitiveClass(void) { super::Release(); }
void MyPrimitiveClass::CompileObject(vector3 a_vColor, String a_sName)
{
	m_nVertices = static_cast<int> (m_vVertexPosition.size());
	for(int i = 0; i < m_nVertices ; i++)
	{
		AddVertexColor( a_vColor );
		AddVertexUV( vector3(0.0f) );
	}
	m_sName = a_sName;

	CompleteTriangleInfo(true);
	CalculateTangents();
	CompileOpenGL3X();
	
}
//C--D
//|  |
//A--B
//This will make the triang A->B->C and then the triang C->B->D
void MyPrimitiveClass::AddQuad(vector3 a_vBottomLeft, vector3 a_vBottomRight, vector3 a_vTopLeft, vector3 a_vTopRight)
{
	AddVertexPosition( a_vBottomLeft );
	AddVertexPosition( a_vBottomRight );
	AddVertexPosition( a_vTopLeft );

	AddVertexPosition( a_vTopLeft );
	AddVertexPosition( a_vBottomRight );
	AddVertexPosition( a_vTopRight );
}
void MyPrimitiveClass::GenerateCube(float a_mSize, vector3 a_vColor)
{
	//If the size is less than this make it this large
	if(a_mSize < 0.01f)
		a_mSize = 0.01f;

	//Clean up Memory
	Release();
	Init();

	float fValue = 0.5f * a_mSize;
	//3--2
	//|  |
	//0--1
	vector3 point0(-fValue,-fValue, fValue); //0
	vector3 point1( fValue,-fValue, fValue); //1
	vector3 point2( fValue, fValue, fValue); //2
	vector3 point3(-fValue, fValue, fValue); //3

	//7--6
	//|  |
	//4--5
	vector3 point4(-fValue,-fValue,-fValue); //4
	vector3 point5( fValue,-fValue,-fValue); //5
	vector3 point6( fValue, fValue,-fValue); //6
	vector3 point7(-fValue, fValue,-fValue); //7

	//F
	AddQuad( point0, point1, point3, point2);
	
	//B
	AddQuad( point5, point4, point6, point7);

	//L
	AddQuad( point4, point0, point7, point3);

	//R
	AddQuad( point1, point5, point2, point6);

	//U
	AddQuad( point3, point2, point7, point6);

	//D
	AddQuad( point4, point5, point0, point1);

	//Compile the object in this color and assign it this name
	CompileObject(a_vColor, "cube");
}
void MyPrimitiveClass::GenerateCone(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_vColor)
{
	if(a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if(a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	//Clean up Memory
	Release();
	Init();
		
	//Your Code Goes Here instead of the next three lines
	for(int i=0; i < a_nSubdivisions; i++){
		double theta = (2*PI/a_nSubdivisions) * i;
		double nextTheta = (2*PI/a_nSubdivisions) * (i+1);
		//add points around the centers of cirlces
		//connect them to center
       vector3 vecA = vector3(0,0,0); //center, we'll never use this I guess
	   vector3 vecB = vector3(0, a_fHeight/2, 0); //center of top cirlce
	   vector3 vecC = vector3(0, -a_fHeight/2, 0); //center of bottom cirlce
	   vector3 vecD = vector3(a_fRadius*cos(theta), a_fHeight/2, a_fRadius*sin(theta));
	   vector3 vecE = vector3(a_fRadius*cos(theta), -a_fHeight/2, a_fRadius*sin(theta));
	   vector3 vecF = vector3 (a_fRadius*cos(nextTheta), a_fHeight/2, a_fRadius*sin(nextTheta));
	   vector3 vecG = vector3 (a_fRadius*cos(nextTheta), -a_fHeight/2, a_fRadius*sin(nextTheta));
	   
	   //top
	   AddVertexPosition(vecB);
	   //AddVertexPosition(vecD);
	   //AddVertexPosition(vecF);
	   
	   //CENTER
	   //AddVertexPosition(vecA);
	   
	   //bottom
	   AddVertexPosition(vecG);
	   AddVertexPosition(vecE);
	   //AddVertexPosition(vecC);


		//middle
		//AddQuad(vecB, vecE, vecB, vecG);
	}

	//Compile the object in this color and assign it this name
	CompileObject(a_vColor, "cone");
}
void MyPrimitiveClass::GenerateCylinder(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_vColor)
{
	if(a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if(a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	//Clean up Memory
	Release();
	Init();
		
	//Your Code Goes Here instead of the next three lines
	for(int i=0; i < a_nSubdivisions; i++){
		double theta = (2*PI/a_nSubdivisions) * i;
		double nextTheta = (2*PI/a_nSubdivisions) * (i+1);
		//add points around the centers of cirlces
		//connect them to center
       vector3 vecA = vector3(0,0,0); //center, we'll never use this I guess
	   vector3 vecB = vector3(0, a_fHeight/2, 0); //center of top cirlce
	   vector3 vecC = vector3(0, -a_fHeight/2, 0); //center of bottom cirlce
	   vector3 vecD = vector3(a_fRadius*cos(theta), a_fHeight/2, a_fRadius*sin(theta));
	   vector3 vecE = vector3(a_fRadius*cos(theta), -a_fHeight/2, a_fRadius*sin(theta));
	   vector3 vecF = vector3 (a_fRadius*cos(nextTheta), a_fHeight/2, a_fRadius*sin(nextTheta));
	   vector3 vecG = vector3 (a_fRadius*cos(nextTheta), -a_fHeight/2, a_fRadius*sin(nextTheta));
	   
	   //top
	   AddVertexPosition(vecB);
	   AddVertexPosition(vecD);
	   AddVertexPosition(vecF);
	   
	   //CENTER
	   //AddVertexPosition(vecA);
	   
	   //bottom
	   AddVertexPosition(vecG);
	   AddVertexPosition(vecE);
	   AddVertexPosition(vecC);


		//middle
		AddQuad(vecD, vecE, vecF, vecG);
	}
	//gluCylinder(gluNewQuadric(),a_fRadius,a_fRadius,a_fHeight,a_nSubdivisions,8);

	//Compile the object in this color and assign it this name
	CompileObject(a_vColor, "cylinder");
}
void MyPrimitiveClass::GenerateTube(float a_fOuterRadius, float a_fInnerRadius, float a_fHeight, int a_nSubdivisions, vector3 a_vColor)
{
	if(a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if(a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	//Clean up Memory
	Release();
	Init();
		
	//Your Code Goes Here instead of the next three lines
	for(int i=0; i < a_nSubdivisions; i++){
		double theta = (2*PI/a_nSubdivisions) * i;
		double nextTheta = (2*PI/a_nSubdivisions) * (i+1);
		//add points around the centers of cirlces
		//connect them to center
       vector3 vecA = vector3(0,0,0); //center, we'll never use this I guess
	   vector3 vecB = vector3(0, a_fHeight/2, 0); //center of top cirlce
	   vector3 vecC = vector3(0, -a_fHeight/2, 0); //center of bottom cirlce
	   vector3 vecD = vector3(a_fOuterRadius*cos(theta), a_fHeight/2, a_fOuterRadius*sin(theta));
	   vector3 inD = vector3(a_fInnerRadius*cos(theta), a_fHeight/2, a_fInnerRadius*sin(theta)); //inner
	   vector3 vecE = vector3(a_fOuterRadius*cos(theta), -a_fHeight/2, a_fOuterRadius*sin(theta));
	   vector3 inE = vector3(a_fInnerRadius*cos(theta), -a_fHeight/2, a_fInnerRadius*sin(theta)); //inner
	   vector3 vecF = vector3 (a_fOuterRadius*cos(nextTheta), a_fHeight/2, a_fOuterRadius*sin(nextTheta));
	   vector3 inF = vector3 (a_fInnerRadius*cos(nextTheta), a_fHeight/2, a_fInnerRadius*sin(nextTheta)); //inner
	   vector3 vecG = vector3 (a_fOuterRadius*cos(nextTheta), -a_fHeight/2, a_fOuterRadius*sin(nextTheta));
	   vector3 inG = vector3 (a_fInnerRadius*cos(nextTheta), -a_fHeight/2, a_fInnerRadius*sin(nextTheta));
	   //
	   //vector3 insideTopOne = inD - vecD;
	   vector3 inside = inF - vecF;
	   //vector3 insideBottomOne = inG - vecG;
	   //vector3 insideBottomTwo = inE - vecE;
	   
	   

	   //AddVertexPosition(vecB);
	   //AddVertexPosition(vecD);
	   //AddVertexPosition(vecF);
	   //
	   //AddVertexPosition(vecG);
	   //AddVertexPosition(vecE);
	   //AddVertexPosition(vecC);


		//middle
		
		AddQuad(vecD, vecF, vecE, vecG);
		//now connect the two points
		AddQuad(inD, inE, inF, inG);


	   AddVertexPosition(vecF);
	   AddVertexPosition(inD);
	   AddVertexPosition(inF);
	   AddVertexPosition(vecD); //vecD
	   AddVertexPosition(inD); //inF
	   AddVertexPosition(vecF); //vecF
	   //
	   AddVertexPosition(vecE);
	   AddVertexPosition(inG);
	   AddVertexPosition(inE);
	   AddVertexPosition(vecG);
	   AddVertexPosition(inG);
	   AddVertexPosition(vecE);
//--------------------------------------------------
	 
	   

	}

	//Compile the object in this color and assign it this name
	CompileObject(a_vColor, "tube");
}
void MyPrimitiveClass::GenerateSphere(float a_fRadius, int a_nSubdivisions, vector3 a_vColor)
{
	//Sets minimum and maximum of subdivisions
	if(a_nSubdivisions < 1)
	{
		GenerateCube(a_fRadius * 2, a_vColor);
		return;
	}
	if(a_nSubdivisions > 6)
		a_nSubdivisions = 6;

	//Clean up Memory
	Release();
	Init();

	//Your Code Goes Here instead of the next three lines
	// Code inspired by: http://stackoverflow.com/questions/10460337/how-to-generate-calculate-vertices-of-dodecahedron
	//this is the only method that I got to compile
	//it doesn't work
	// Calculate constants that will be used to generate vertices
            float phi = (sqrt(5) - 1) / 2; // The golden ratio
            float R = (a_fRadius / sqrt(3));

            float a = (R * 1);
            float b = R / phi;
            float c = R * phi;

            // Generate each vertex
            //List vertices = new List<Vertex>();
            for (int i = 0; i < a_nSubdivisions; i ++)
            {
                for (int j = -1; j < 2; j +=2 )
                {
                    AddVertexPosition(vector3(0, i * c * R, j * b * R));
                    AddVertexPosition(vector3(i * c * R, j * b * R, 0));
                    AddVertexPosition(vector3(i * b * R, 0, j * c * R));

                    for (int k = -1; k < 2; k +=2)
                        AddVertexPosition(vector3(i * a * R, j * a * R, k * a * R));
                }
            }
            //return vertices;
        

	//Compile the object in this color and assign it this name
	CompileObject(a_vColor, "Sphere");
}
void MyPrimitiveClass::Render(void)
{
	//This will use a render list, this render version is different and its not currently in use 
	//for this homework assigment, use the other render methods
	const float* temp = glm::value_ptr(matrix4(1.0f));
	float* temp2 = new float[16];
	memcpy(temp2, temp, 16 * sizeof(float));
	super::Render(temp2, 1);
	SafeDelete(temp2);
}
void MyPrimitiveClass::Render(matrix4 a_mModelMatrix, vector3 a_vColor)
{
	//Render the object in solid color
	super::RenderSolid(a_mModelMatrix, a_vColor);
}
void MyPrimitiveClass::RenderWire(matrix4 a_mModelMatrix, vector3 a_vColor)
{
	//Render the object in wireframe mode (the wire is going to be in this color)
	super::RenderWire(a_mModelMatrix, a_vColor);
}