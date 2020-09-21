#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	cam.setDistance(30.0);
	cam.lookAt(glm::vec3(0, 0, 0));
	ofSetBackgroundColor(ofColor::black);

	////hardcode test box

	//mesh.addVert(-1.5, -1.5, 1.5);
	//mesh.addVert(1.5, -1.5, 1.5);
	//mesh.addVert(-1.5, 1.5, 1.5);
	//mesh.addVert(1.5, 1.5, 1.5);
	//mesh.addVert(-1.5, 1.5, -1.5);
	//mesh.addVert(1.5, 1.5, -1.5);
	//mesh.addVert(-1.5, -1.5, -1.5);
	//mesh.addVert(1.5, -1.5, -1.5);

	//mesh.addTriangle(1, 2, 3);
	//mesh.addTriangle(3, 2, 4);
	//mesh.addTriangle(3, 4, 5);
	//mesh.addTriangle(5, 4, 6);
	//mesh.addTriangle(5, 6, 7);
	//mesh.addTriangle(7, 6, 8);
	//mesh.addTriangle(7, 8, 1);
	//mesh.addTriangle(1, 8, 2);
	//mesh.addTriangle(2, 8, 4);
	//mesh.addTriangle(4, 8, 6);
	//mesh.addTriangle(7, 1, 5);
	//mesh.addTriangle(5, 1, 3);

	readObjFile("monster-light-triangles-nouv.obj");

}


void MyMesh::addVert(double x, double y, double z) {
	verts.push_back(glm::vec3(x, y, z));
}

void MyMesh::addTriangle(int i, int j, int k) {
	triangles.push_back(Triangle(i, j, k));
}


//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	cam.begin();

	drawAxis();

	ofSetColor(ofColor::white);
	ofNoFill();

	for (int n = 0; n < mesh.triangles.size()*3; n+=3) {
		int i = mesh.triangles[0].vertInd[n] - 1;
		int j = mesh.triangles[0].vertInd[n+1] - 1;
		int k = mesh.triangles[0].vertInd[n+2] - 1;
		ofDrawTriangle(mesh.verts[i], mesh.verts[j], mesh.verts[k]);
	}

}

void ofApp::drawAxis() {
//	ofDrawGrid();
//	ofSetColor(0, 255, 0); //red, green, blue components for RGB space

	// draw Grid aixs
	//X
	//
	ofSetColor(ofColor::red);
	ofDrawLine(glm::vec3(0, 0, 0), glm::vec3(5.0, 0, 0));

	//Y
	//
	ofSetColor(ofColor::green);
	ofDrawLine(glm::vec3(0, 0, 0), glm::vec3(0, 5.0, 0));

	//Z
	//
	ofSetColor(ofColor::blue);
	ofDrawLine(glm::vec3(0, 0, 0), glm::vec3(0, 0, 5.0));
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
//
// Drag/Drop Callback in OpenFrameworks.  When  file is dropped in the viewport
// this function gets called. dragInfo contains the file name.
//
void ofApp::dragEvent(ofDragInfo dragInfo){ 
	cout << dragInfo.files[0] << endl;
//	readObjFile(dragInfo.files[0]);
}


void ofApp::readObjFile(string name) {
	ofFile file;
	string line;
	int numOfVerts = 0;
	int numOfFaces = 0;

	//  Open file, return if error
	//
	if (!file.open(name)) {
		cout << "can't open file: " << name << endl;
	}
	// read each line in file and process vertices and faces
	//
	while (getline(file, line)) {
		if (line.size() < 3) continue; //ignore shorter lines

		//vertex case
		//
		if (line.at(0) == 'v' && line.at(1) == ' ') {
			
			
			istringstream iss(line);
			string type;
			double x, y, z;
			iss >> type >> x >> y >> z;
			//
			//add vertex to mes
			//
			mesh.addVert(x, y, z);
			numOfVerts++;
		}
		//face
		//parse face here
		else if (line.at(0) == 'f') {
			
			string type;
			int i, j, k;
			istringstream iss(line);
			iss >> type >> i >> j >> k;
			mesh.addTriangle(i, j, k);
			numOfFaces++;
		}

	}
	cout << "The total numberof vertices: " << numOfVerts << endl;
	cout << "The total numberof faces: " << numOfFaces << endl;
	cout << "The size of the Mesh structure: " << std::filesystem::file_size(file)/1000 << "KB" << endl;
	file.close();
	
	
}