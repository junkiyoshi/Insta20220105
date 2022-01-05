#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(255);
	ofEnableDepthTest();
	ofSetCircleResolution(60);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->mesh.clear();

	auto span = 6;
	auto seed = glm::vec3(ofRandom(1000), ofRandom(1000), ofRandom(1000));
	for (int x = -500; x <= 500; x += span) {

		for (int y = -300; y <= 300; y += span) {

			vector<glm::vec3> vertices;
			vertices.push_back(this->rotate(seed, glm::vec3(x, y, 0)));
			vertices.push_back(this->rotate(seed, glm::vec3(x + span, y, 0)));
			vertices.push_back(this->rotate(seed, glm::vec3(x + span, y + span, 0)));
			vertices.push_back(this->rotate(seed, glm::vec3(x, y + span, 0)));

			for (auto& vertex : vertices) {

				vertex.z = ofMap(vertex.z, -5, 5, -30, 30);
			}

			this->mesh.addVertices(vertices);

			this->mesh.addIndex(this->mesh.getNumVertices() - 1); this->mesh.addIndex(this->mesh.getNumVertices() - 2); this->mesh.addIndex(this->mesh.getNumVertices() - 3);
			this->mesh.addIndex(this->mesh.getNumVertices() - 1); this->mesh.addIndex(this->mesh.getNumVertices() - 3); this->mesh.addIndex(this->mesh.getNumVertices() - 4);
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(270);

	ofSetLineWidth(1);

	ofSetColor(255);
	this->mesh.draw();

	ofTranslate(0, 0, 0.01);

	ofSetColor(0);
	this->mesh.drawWireframe();

	ofSetLineWidth(3);

	ofTranslate(0, 400, 0);
	ofRotateX(90);

	ofNoFill();
	ofDrawCircle(glm::vec3(), 250);

	ofSetColor(255);
	ofFill();
	ofDrawCircle(glm::vec3(), 249.5);

	this->cam.end();
}


//--------------------------------------------------------------
glm::vec3 ofApp::rotate(glm::vec3 seed, glm::vec3 location) {

	float deg_x = ofMap(ofNoise(seed.x, location.x * 0.003, location.y * 0.003 + ofGetFrameNum() * 0.0085), 0, 1, -180, 180);
	float deg_y = ofMap(ofNoise(seed.y, location.x * 0.003, location.y * 0.003 + ofGetFrameNum() * 0.0085), 0, 1, -180, 180);
	float deg_z = ofMap(ofNoise(seed.z, location.x * 0.003, location.y * 0.003 + ofGetFrameNum() * 0.0085), 0, 1, -180, 180);

	auto rotation_x = glm::rotate(glm::mat4(), deg_x * (float)DEG_TO_RAD, glm::vec3(1, 0, 0));
	auto rotation_y = glm::rotate(glm::mat4(), deg_y * (float)DEG_TO_RAD, glm::vec3(0, 1, 0));
	auto rotation_z = glm::rotate(glm::mat4(), deg_z * (float)DEG_TO_RAD, glm::vec3(0, 0, 1));

	auto tmp = glm::vec3(5 * cos(0 * DEG_TO_RAD), 5 * sin(0 * DEG_TO_RAD), 0);
	tmp = glm::vec4(tmp, 0) * rotation_z * rotation_y * rotation_x;

	return location + tmp;
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}