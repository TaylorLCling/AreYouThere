#include <opencv2/opencv.hpp> //include opencv  for tools

using namespace std;
using namespace cv; // Declear cv namespace early

String face_cascade_name = "haarcascade_frontalface_default.xml"; 

int main() {

    VideoCapture cam(0);  // Open the default camera
    if(!cam.isOpened()) {  // Check if we succeeded
        return -1; //return error otherwise
    }


    CascadeClassifier faceClassifier; //Need a face classifier
    if(!faceClassifier.load( face_cascade_name ) ) { // Load preloaded faces and error out if it fails 
        cout << "--(!)Error loading face cascade\n";
        return -1;
    };

    int fontUsed = FONT_HERSHEY_SIMPLEX; //FONT_HERSHEY_PLAIN
    int x = 1; //position of text
    int y = 11; //position of text
    int answerOffset = 145; //X offset for detection answer


    Mat frame; //mat is the cv array class we will call frame.
    while(true) {
        cam >> frame;  // Get a new frame from camera
        putText(frame, "Are you There? = ", Point(x,y), fontUsed, .5, 1, 1, 8, false); //Add detection question text to screen

        vector<Rect> faces; //create vector for faces
        faceClassifier.detectMultiScale(frame, faces); // Detect Faces in frame

        for(auto & face : faces) {
            rectangle(frame, face, Scalar(255, 0, 0), 2); //Draw a Rectangle for each face found
        }
        
        if (faces.empty()) {//if Faces is empty then nobody is detection
            putText(frame, "Nope",  Point((x + answerOffset),y), fontUsed, .5, Scalar(0,0,255), 1, 8, false);
            //Display No detected person answer after question
        } 
        else {
            putText(frame, "Yes",  Point((x + answerOffset),y), fontUsed, .5, Scalar(0,255,0), 1, 8, false);
            //Display, Yes, person detected answer.
        }

        imshow("Face Detection", frame); // Present frame
        
        if(waitKey(30) >= 0) break;  // Wait for a keystroke then close when done. 
    }
    return 0;
}