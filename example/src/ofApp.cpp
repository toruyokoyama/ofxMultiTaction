#include "ofApp.h"
#include "ofxMultiTaction.h"

const int kMultitactionPort =  8888;


//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0, 0, 0);
    multitaction = new ofMultiTaction(kMultitactionPort);
}

//--------------------------------------------------------------
void ofApp::update(){
    multitaction->update(true);

}

//--------------------------------------------------------------
void ofApp::draw(){
    int radius = 50;
    
    ofSetColor(255, 0, 0);
    std::map<int, ofMultiTaction::Finger> fingers = multitaction->getFingers();
    for (std::map<int, ofMultiTaction::Finger>::iterator it = fingers.begin(); it != fingers.end(); ++it) {
        int id = it->first ; //key
        ofMultiTaction::Finger finger= it->second; //value
        
        ofCircle(finger.x, finger.y, radius);
    }
    
    ofSetColor(0, 255, 0);
    std::map<int, ofMultiTaction::Marker> markers = multitaction->getMarkers();
    for (std::map<int, ofMultiTaction::Marker>::iterator it = markers.begin(); it != markers.end(); ++it) {
        int id = it->first ;
        ofMultiTaction::Marker marker = it->second;
        
        ofCircle(marker.x, marker.y, radius);
    }
    

}

//--------------------------------------------------------------
void ofApp::exit()
{
    delete multitaction;
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
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
