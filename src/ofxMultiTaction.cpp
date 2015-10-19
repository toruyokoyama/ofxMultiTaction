//
//  ofxMultiTaction.cpp
//  example
//
//  Created by YOKOYAMA Toru on 2015/10/19.
//
//

#include "ofxMultiTaction.h"

#include "ofxOsc.h"

class ofMultiTaction::Private
{
public:
    ofxOscReceiver receiver;
    
    std::map<int, Finger> fingers;
    std::map<int, Marker> markers;
    
    //std::vector<Finger> fingerList;
    
};

static void dumpOSC(ofxOscMessage m)
{
    string msg_string;
    msg_string = m.getAddress();
    
    for (int i=0; i < m.getNumArgs(); ++i) {
        msg_string += " ";
        
        if (m.getArgType(i) == OFXOSC_TYPE_INT32)
            msg_string += ofToString(m.getArgAsInt32(i));
        else if(m.getArgType(i) == OFXOSC_TYPE_FLOAT)
            msg_string += ofToString( m.getArgAsFloat(i));
        else if(m.getArgType(i) == OFXOSC_TYPE_STRING)
            msg_string += m.getArgAsString(i);
    }
    
    cout << msg_string <<endl;
}

ofMultiTaction::ofMultiTaction(int port)
: d(new Private())
{
    d->receiver.setup(port);
}

ofMultiTaction::~ofMultiTaction()
{
    delete d;
}

static ofMultiTaction::Finger makeFingerFromOSC(const ofxOscMessage &m)
{
    ofMultiTaction::Finger finger;
    finger.id = m.getArgAsInt32(0);
    finger.x = m.getArgAsFloat(1);
    finger.y = m.getArgAsFloat(2);
    return finger;
}

static ofMultiTaction::Marker makeMarkerFromOSC(const ofxOscMessage &m)
{
    ofMultiTaction::Marker marker;
    marker.id = m.getArgAsInt32(0);
    marker.code = m.getArgAsInt32(1);
    marker.x = m.getArgAsFloat(2);
    marker.y = m.getArgAsFloat(3);
    marker.rotation = m.getArgAsFloat(3);
    return marker;
}

void ofMultiTaction::update(bool isDumpOSC)
{
    while (d->receiver.hasWaitingMessages()) {
        ofxOscMessage m;
        d->receiver.getNextMessage(&m);
        
        if (m.getAddress() == "/fingerDown") {
            Finger finger = makeFingerFromOSC(m);
            appendFinger(finger);
        }
        else if(m.getAddress() == "/fingerMove") {
            Finger finger = makeFingerFromOSC(m);
            appendFinger(finger);
        }
        else if(m.getAddress() == "/fingerUp") {
            Finger finger = makeFingerFromOSC(m);
            removeFinger(finger);
        }
        
        else if(m.getAddress() == "/markerDown") {
            Marker marker = makeMarkerFromOSC(m);
            appendMarker(marker);
        }
        else if(m.getAddress() == "/markerMove") {
            Marker marker = makeMarkerFromOSC(m);
            appendMarker(marker);
        }
        else if(m.getAddress() == "/markerUp") {
            Marker marker = makeMarkerFromOSC(m);
            removeMarker(marker);
        }
        
        if (isDumpOSC) {
            dumpOSC(m);
        }
    }
    
}

std::map<int, ofMultiTaction::Finger> ofMultiTaction::getFingers() const
{
    return d->fingers;
}

std::map<int, ofMultiTaction::Marker> ofMultiTaction::getMarkers() const
{
    return d->markers;
}

void ofMultiTaction::appendFinger(const Finger &finger)
{
    // map
    d->fingers[finger.id] = finger;
    
    // vector
    //    bool ok = false;
    //    for (int i = 0; i < d->fingerList.size(); ++i) {
    //        if (d->fingerList[i].id == finger.id) {
    //            d->fingerList[i] = finger;
    //            ok = true;
    //            break;
    //        }
    //    }
    //
    //    if (!ok) {
    //        d->fingerList.push_back(finger);
    //    }
}

void ofMultiTaction::removeFinger(const Finger &finger)
{
    // map
    std::map<int, Finger>::iterator it = d->fingers.find(finger.id);
    if (it != d->fingers.end()) {
        d->fingers.erase(it);
    }
    
    // vector
    //    for (int i = d->fingerList.size() - 1; i >= 0; --i) {
    //        if (d->fingerList[i].id == finger.id) {
    //            d->fingerList.erase(d->fingerList.begin() + i);
    //            break;
    //        }
    //    }
}

void ofMultiTaction::appendMarker(const Marker &marker)
{
    d->markers[marker.id] = marker;
}

void ofMultiTaction::removeMarker(const Marker &marker)
{
    std::map<int, Marker>::iterator it = d->markers.find(marker.id);
    if (it != d->markers.end()) {
        d->markers.erase(it);
    }
}
