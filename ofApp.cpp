#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	
	ofSetFrameRate(60);
	ofBackground(0);
	ofSetWindowTitle("Insta");

	ofSetRectMode(ofRectMode::OF_RECTMODE_CENTER);

	this->rect_size = 10;
	this->fbo.allocate(ofGetWidth(), ofGetHeight());
}

//--------------------------------------------------------------
void ofApp::update() {

	this->colors.clear();

	float x_count = ofGetWidth() / this->rect_size;
	float y_count = ofGetHeight() / this->rect_size;

	for (int y = 0; y < y_count; y++) {

		vector<ofColor> tmp_colors;

		for (int x = 0; x < x_count; x++) {

			if (y == 0) {

				float value = ofMap(ofNoise(x * 0.03, ofGetFrameNum() * 0.005), 0, 1, 0, 255);
				tmp_colors.push_back(ofColor(value));
			}
			else {

				float value = 0;
				int count = 0;

				for (int tmp_x = x - 1; tmp_x <= x + 1; tmp_x++) {

					if (tmp_x >= 0 && tmp_x < x_count) {

						value += this->colors[y - 1][tmp_x].r;
						count++;
					}
				}

				if (y >= 2) {

					value += this->colors[y - 2][x].r;
					count++;
				}

				float average = value / count + ofMap(ofNoise(x * 0.05, y * 0.1 - ofGetFrameNum() * 0.5), 0, 1, -5, 5);

				if (average < 0) {

					average = 0;
				}
				else if (average > 255) {

					average = 255;
				}

				tmp_colors.push_back(ofColor(average));
			}
		}

		this->colors.push_back(tmp_colors);
	}

	this->fbo.begin();

	for (int y = 0; y < this->colors.size(); y++) {

		for (int x = 0; x < this->colors[y].size(); x++) {

			ofSetColor(this->colors[y][x]);
			ofDrawRectangle(ofVec2f(x * this->rect_size + this->rect_size / 2, ofGetHeight() - (y * this->rect_size + this->rect_size / 2)), this->rect_size, this->rect_size);
		}
	}

	this->fbo.end();
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->fbo.draw(ofGetWidth() / 2, ofGetHeight() / 2); // RectMode‚É‚Â‚ç‚ê‚é
}

//========================================================================
int main() {

	ofSetupOpenGL(1280, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}