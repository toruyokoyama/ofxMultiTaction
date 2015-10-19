//
//  ofxMultiTaction.h
//  example
//
//  Created by YOKOYAMA Toru on 2015/10/19.
//
//

#ifndef ofxMultiTaction_h
#define ofxMultiTaction_h

#include <string>
#include <vector>
#include <map>

class ofMultiTaction
{
public:
    struct Finger
    {
        int id;
        float x;
        float y;
    };
    
    struct Marker
    {
        int id;
        int code;
        float x;
        float y;
        float rotation;
    };
    
public:
    ofMultiTaction(int port);
    ~ofMultiTaction();
    
    void update(bool isDumpOSC = false);
    
    std::map<int, Finger> getFingers() const;
    std::map<int, Marker> getMarkers() const;
    
private:
    void appendFinger(const Finger &finger);
    void removeFinger(const Finger &finger);
    
    void appendMarker(const Marker &marker);
    void removeMarker(const Marker &marker);
    
private:
    class Private;
    Private *d;
    
};

#endif /* ofxMultiTaction_h */
