#include "mesh.h"

// --------------------------------------------------------------------------
// ----------------------- MESH INITIALIZATIONS -----------------------------
// --------------------------------------------------------------------------

Mesh createMesh(Vec4* vertices, int verticesCount, Face* faces, int facesCount) {
	Mesh mesh;

	mesh.vertices = new Vec4[verticesCount];
	mesh.verticesCount = verticesCount;

	mesh.faces = new Face[facesCount];
	mesh.facesCount = facesCount;

	mesh.translation = zeroVector;
	mesh.rotation = zeroVector;
	mesh.scaling = oneVector;

	for (int i = 0; i < verticesCount; i++) {
		mesh.vertices[i] = vertices[i];
	}

	for (int i = 0; i < facesCount; i++) {
		mesh.faces[i].indices[0] = faces[i].indices[0];
		mesh.faces[i].indices[1] = faces[i].indices[1];
		mesh.faces[i].indices[2] = faces[i].indices[2];
	}

	mesh.modelMatrix = identityMatrix();

	return mesh;
}

Mesh createMesh(Vec4* vertices, int verticesCount, Face* faces, int facesCount, Vec3 translation, Vec3 rotation, Vec3 scaling) {
	Mesh mesh;

	mesh.vertices = new Vec4[verticesCount];
	mesh.verticesCount = verticesCount;

	mesh.faces = new Face[facesCount];
	mesh.facesCount = facesCount;

	for (int i = 0; i < verticesCount; i++) {
		mesh.vertices[i] = vertices[i];
	}

	for (int i = 0; i < facesCount; i++) {
		mesh.faces[i].indices[0] = faces[i].indices[0];
		mesh.faces[i].indices[1] = faces[i].indices[1];
		mesh.faces[i].indices[2] = faces[i].indices[2];
	}

	mesh.translation = translation;
	mesh.rotation = rotation;
	mesh.scaling = scaling;

	updateModelMatrix(mesh);

	return mesh;
}

//Load mesh from an .obj file
Mesh createMesh(char* filePath){
    ///LOADING THE FILE

    //Try to open the file
    std::ifstream fin(filePath);
    if(!fin){ Mesh mesh; mesh.failedLoading = true; return mesh; }

    //Find the file size (bytes)
    fin.seekg(0, std::ios::end);
    unsigned int fileSize = fin.tellg();

    //Load the entire file into a buffer for fast processing
    char* fileBuffer = new char[fileSize+1];
    fin.seekg(0);
    fin.read(fileBuffer, fileSize);

    fin.close();

    //Find actual length of text from the file
    //"fileBuffer" has a nul "end of string" indicator.
    fileBuffer[fileSize] = 0;
    while(!fileBuffer[fileSize-1]){ fileSize--; }

    ///PROCESSING THE FILE

    //Counting vertices and faces
    int verticesCount = 0, facesCount = 0;

    for(char* p = fileBuffer; *p; p++){
        skipSpacesAndEmptyLines(p);
        if(*p == 'v' && *(p+1) == ' '){//Vertex
            goToEndOfLine(p);
            verticesCount++;
        }
        else if(*p == 'f' && *(p+1) == ' '){
            //Face (can have more than 3 sides,
            //triangulation will increase "facesCount")
            p++;
            for(int k = 3; k--;){
                readInt(p); skipNonSpaces(p);
            }
            skipSpaces(p);

            facesCount++;

            while(*p && *p != '\n'){
                readInt(p); skipNonSpaces(p);
                skipSpaces(p);

                facesCount++;
            }
        }
        else{//Comments and unknown type of information are skipped.
            goToEndOfLine(p);
        }
    }

    //Loading vertices and faces
    Vec4* vertices = new Vec4[verticesCount];
    Face* faces = new Face[facesCount];

    verticesCount = facesCount = 0;

    for(char* p = fileBuffer; *p; p++){
        skipSpacesAndEmptyLines(p);
        if(*p == 'v' && *(p+1) == ' '){
            //Vertex
            p++;
            vertices[verticesCount].x = readFloat(p);
            vertices[verticesCount].y = readFloat(p);
            vertices[verticesCount].z = readFloat(p);

            skipSpaces(p);
            if(*p && *p != '\n'){
                vertices[verticesCount].w = readFloat(p);
                goToEndOfLine(p);
            }

            verticesCount++;
        }
        else if(*p == 'f' && *(p+1) == ' '){
            //Face: triangulating polygons with more than 3 sides
            p++;
            int indexA = readInt(p) - 1; skipNonSpaces(p);
            int indexB = readInt(p) - 1; skipNonSpaces(p);
            int indexC = readInt(p) - 1; skipNonSpaces(p);
            skipSpaces(p);

            faces[facesCount].indices[0] = indexA;
            faces[facesCount].indices[1] = indexB;
            faces[facesCount].indices[2] = indexC;

            facesCount++;

            while(*p && *p != '\n'){
                indexB = indexC;
                indexC = readInt(p) - 1; skipNonSpaces(p);
                skipSpaces(p);

                faces[facesCount].indices[0] = indexA;
                faces[facesCount].indices[1] = indexB;
                faces[facesCount].indices[2] = indexC;

                facesCount++;
            }
        }
        else{//Comments and unknown type of information are skipped.
            goToEndOfLine(p);
        }
    }
    delete[] fileBuffer;

    //Creating the mesh
    Mesh mesh = createMesh(vertices, verticesCount, faces, facesCount);

    delete[] vertices;
    delete[] faces;

    return mesh;
}

// --------------------------------------------------------------------------
// ----------------------- MESH TRANSFORMATIONS -----------------------------
// --------------------------------------------------------------------------
void setTranslation(Mesh& mesh, Vec3 translation) {
	mesh.translation = translation;
	updateModelMatrix(mesh);
}

void setRotation(Mesh& mesh, Vec3 rotation) {
	mesh.rotation = rotation;
	updateModelMatrix(mesh);
}

void setScaling(Mesh& mesh, Vec3 scaling) {
	mesh.scaling = scaling;
	updateModelMatrix(mesh);
}

void translateBy(Mesh& mesh, Vec3 translation) {
	mesh.translation = mesh.translation + translation;
	updateModelMatrix(mesh);
}

void rotateBy(Mesh& mesh, Vec3 rotation) {
	mesh.rotation = mesh.rotation + rotation;
	updateModelMatrix(mesh);
}

void scaleBy(Mesh& mesh, Vec3 scaling) {
	mesh.scaling = mesh.scaling + scaling;
	updateModelMatrix(mesh);
}

void updateModelMatrix(Mesh& mesh) {
	mesh.modelMatrix = modelMatrix(mesh.translation, mesh.scaling, mesh.rotation);
}
