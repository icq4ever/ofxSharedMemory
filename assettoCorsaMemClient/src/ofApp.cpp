#include "ofApp.h"


/*
 Sets up a custom data class/object as a memory mapped file.
 - Can be a server (creates/destroys the data) or client (reads the data).
 - A memory key string "MyCustomData" is used to identify the shared memory (you can name change this to whatever you want).
 - The source code is identical for exampleDataClient and exampleDataServer, except for the variable below 'isServer'
 */


bool isServer = false;
//string memoryKey = "MyCustomData";
//int memorySize = sizeof(CustomData);

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofEnableAlphaBlending();
    ofSetLogLevel(OF_LOG_VERBOSE);        

    // setup an object with different data types
	physicsData = new SPageFilePhysics();
	graphicsData = new SPageFileGraphic();
	fileStaticData = new SPageFileStatic();
    
	physics.setup("Local\\acpmf_physics", sizeof(physics), false);
	graphics.setup("Local\\acpmf_graphics", sizeof(graphics), false);
	fileStatic.setup("Local\\acpmf_static", sizeof(fileStatic), false);
	
	// setup + connect
	//memoryMappedFile.setup(memoryKey, memorySize, isServer);

    isConnected = physics.connect() && graphics.connect() && fileStatic.connect();

	isPhysicsConnected = physics.connect();
	isGraphicsConnected = graphics.connect();
	isFileStaticConnected = fileStatic.connect();
    
    //ofLog() << "Memory was mapped? " << isConnected;
    /*ofLog() << "Memory key: " << memoryKey;
    ofLog() << "Memory size: " << memorySize;*/
}



//--------------------------------------------------------------
void ofApp::update() {

	ofSetWindowTitle(ofToString("AC shared memory - connection statud : ") + ofToString(isConnected ? "YES" : "NO") + ", FPS: " + ofToString(ofGetFrameRate()));

	// if not connected, try reconnect every 5 seconds or so
	if (!isPhysicsConnected && ofGetFrameNum() % 300 == 0)		isPhysicsConnected = physics.connect();
	if (!isGraphicsConnected && ofGetFrameNum() % 300 == 0)		isGraphicsConnected = graphics.connect();
	if (!isFileStaticConnected && ofGetFrameNum() % 300 == 0)	isFileStaticConnected = fileStatic.connect();

	// server updates data and saves to memory mapped file
	// client loads memory mapped file into object

	//myCustomData = memoryMappedFile.getData();
	if (isPhysicsConnected && isGraphicsConnected && isFileStaticConnected) {
		physicsData = physics.getData();
		graphicsData = graphics.getData();
		fileStaticData = fileStatic.getData();
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    // server is blue, client is yellow
    (isServer) ? ofBackground(0, 255, 255) : ofBackground(255, 255, 0);
    
    // ofVec3f- pink cube outline
    ofNoFill();
    ofSetColor(255,0,255);
    //ofBox(myCustomData->vec.x + (ofGetWidth()*.5), myCustomData->vec.y + (ofGetHeight()*.5), myCustomData->vec.z, 30);
    
    // mousex + mouseY- white circle
    ofFill();
    ofSetColor(255);
    //ofCircle(myCustomData->mouseX , myCustomData->mouseY, 20);
    
    ofSetColor(255);
    /*stringstream output;
	output << "Shared data..." << endl
    << "Time : " << myCustomData->time << endl
    << "Mouse X : " << myCustomData->mouseX << endl
    << "Mouse Y : " << myCustomData->mouseY << endl
    << "Vec : " << myCustomData->vec << endl
    << "Message : " << myCustomData->message;*/

	stringstream physicsOutput, graphicsOutput, fileStaticOutput;
	if (isPhysicsConnected && isGraphicsConnected && isFileStaticConnected) {
		physicsOutput << "PHYSICS ====================================" << endl
			<< "packetId" << physicsData->packetId << endl
			<< "gas" << physicsData->gas << endl
			<< "brake" << physicsData->brake << endl
			<< "fuel" << physicsData->fuel << endl
			<< "gear" << physicsData->gear << endl
			<< "rpms" << physicsData->rpms << endl
			<< "steerAngle" << physicsData->steerAngle << endl
			<< "speedKmh" << physicsData->speedKmh << endl
			<< "velocity" << physicsData->velocity << endl
			<< "accG" << physicsData->accG << endl
			<< "wheelSlip" << physicsData->wheelSlip << endl
			<< "wheelLoad" << physicsData->wheelLoad << endl
			<< "wheelsPressure" << physicsData->wheelsPressure << endl
			<< "wheelAngularSpeed" << physicsData->wheelAngularSpeed << endl
			<< "tyreWear" << physicsData->tyreWear << endl
			<< "tyreDirtyLevel" << physicsData->tyreDirtyLevel << endl
			<< "tyreCoreTemperature" << physicsData->tyreCoreTemperature << endl
			<< "camberRAD" << physicsData->camberRAD << endl
			<< "suspensionTravel" << physicsData->suspensionTravel << endl
			<< "drs" << physicsData->drs << endl
			<< "tc" << physicsData->tc << endl
			<< "heading" << physicsData->heading << endl
			<< "pitch" << physicsData->pitch << endl
			<< "roll" << physicsData->roll << endl
			<< "cgHeight" << physicsData->cgHeight << endl
			<< "carDamage" << physicsData->carDamage << endl
			<< "numberOfTyresOut" << physicsData->numberOfTyresOut << endl
			<< "pitLimiterOn" << physicsData->pitLimiterOn << endl
			<< "abs" << physicsData->abs << endl
			<< "kersCharge" << physicsData->kersCharge << endl
			<< "kersInput" << physicsData->kersInput << endl
			<< "autoShifterOn" << physicsData->autoShifterOn << endl
			<< "rideHeight" << physicsData->rideHeight << endl
			<< "turboBoost" << physicsData->turboBoost << endl
			<< "ballast" << physicsData->ballast << endl
			<< "airDensity" << physicsData->airDensity << endl
			<< "airTemp" << physicsData->airTemp << endl
			<< "roadTemp" << physicsData->roadTemp << endl
			<< "localAngularVel" << physicsData->localAngularVel << endl
			<< "finalFF" << physicsData->finalFF << endl
			<< "performanceMeter" << physicsData->performanceMeter << endl
			<< "engineBrake" << physicsData->engineBrake << endl
			<< "ersRecoveryLevel" << physicsData->ersRecoveryLevel << endl
			<< "ersPowerLevel" << physicsData->ersPowerLevel << endl
			<< "ersHeatCharging" << physicsData->ersHeatCharging << endl
			<< "ersIsCharging" << physicsData->ersIsCharging << endl
			<< "kersCurrentKJ" << physicsData->kersCurrentKJ << endl
			<< "drsAvailable" << physicsData->drsAvailable << endl
			<< "drsEnabled" << physicsData->drsEnabled << endl;

		graphicsOutput << "GRAPHICS INFO =============================" << endl
			<< "packetID" << graphicsData->packetId << endl
			<< "STATUS " << graphicsData->status << endl
			<< "session" << graphicsData->session << endl
			<< "completed laps" << graphicsData->completedLaps << endl
			<< "position" << graphicsData->position << endl
			<< "current time s" << graphicsData->currentTime << endl
			<< "current time" << graphicsData->iCurrentTime << endl
			<< "last time" << graphicsData->iLastTime << endl
			<< "best time" << graphicsData->iBestTime << endl
			<< "sessionTimeLeft" << graphicsData->sessionTimeLeft << endl
			<< "distanceTraveled" << graphicsData->distanceTraveled << endl
			<< "isInPit" << graphicsData->isInPit << endl
			<< "currentSectorIndex" << graphicsData->currentSectorIndex << endl
			<< "lastSectorTime" << graphicsData->lastSectorTime << endl
			<< "numberOfLaps" << graphicsData->numberOfLaps << endl
			<< "TYRE COMPOUND : " << graphicsData->tyreCompound << endl
			<< "replayMult" << graphicsData->replayTimeMultiplier << endl
			<< "normalizedCarPosition" << graphicsData->normalizedCarPosition << endl
			<< "carCoordinates" << graphicsData->carCoordinates << endl;

		fileStaticOutput << "STATIC INFO =============================" << endl
			<< "smVersion" << fileStaticData->smVersion << endl
			<< "acVersion" << fileStaticData->acVersion << endl
			<< "numberOfSessions" << fileStaticData->numberOfSessions << endl
			<< "numCars" << fileStaticData->numCars << endl
			<< "carModel" << fileStaticData->carModel << endl
			<< "track" << fileStaticData->track << endl
			<< "playerName" << fileStaticData->playerName << endl
			<< "playerSurname" << fileStaticData->playerSurname << endl
			<< "playerNick" << fileStaticData->playerNick << endl
			<< "sectorCount" << fileStaticData->sectorCount << endl
			<< "maxTorque" << fileStaticData->maxTorque << endl
			<< "maxPower" << fileStaticData->maxPower << endl
			<< "maxRpm" << fileStaticData->maxRpm << endl
			<< "maxFuel" << fileStaticData->maxFuel << endl
			<< "suspensionMaxTravel" << fileStaticData->suspensionMaxTravel << endl
			<< "tyreRadius" << fileStaticData->tyreRadius << endl
			<< "maxTurboBoost" << fileStaticData->maxTurboBoost << endl
			<< "deprecated_1" << fileStaticData->deprecated_1 << endl
			<< "deprecated_2" << fileStaticData->deprecated_2 << endl
			<< "penaltiesEnabled" << fileStaticData->penaltiesEnabled << endl
			<< "aidFuelRate" << fileStaticData->aidFuelRate << endl
			<< "aidTireRate" << fileStaticData->aidTireRate << endl
			<< "aidMechanicalDamage" << fileStaticData->aidMechanicalDamage << endl
			<< "aidAllowTyreBlankets" << fileStaticData->aidAllowTyreBlankets << endl
			<< "aidStability" << fileStaticData->aidStability << endl
			<< "aidAutoClutch" << fileStaticData->aidAutoClutch << endl
			<< "aidAutoBlip" << fileStaticData->aidAutoBlip << endl
			<< "hasDRS" << fileStaticData->hasDRS << endl
			<< "hasERS" << fileStaticData->hasERS << endl
			<< "hasKERS" << fileStaticData->hasKERS << endl
			<< "kersMaxJ" << fileStaticData->kersMaxJ << endl
			<< "engineBrakeSettingsCount" << fileStaticData->engineBrakeSettingsCount << endl
			<< "ersPowerControllerCount" << fileStaticData->ersPowerControllerCount << endl

			<< "trackSPlineLength" << fileStaticData->trackSPlineLength << endl
			<< "trackConfiguration" << fileStaticData->trackConfiguration << endl;

		ofDrawBitmapStringHighlight(physicsOutput.str(), 20, 20);
		ofDrawBitmapStringHighlight(graphicsOutput.str(), 180, 20);
		ofDrawBitmapStringHighlight(fileStaticOutput.str(), 340, 20);
		
	} else {
		ofDrawBitmapStringHighlight("ACS is not running", 20, 20);
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){ }
//--------------------------------------------------------------
void ofApp::keyReleased(int key){ }
//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){ }
//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){ }
//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){ }
//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){ }
//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){ }
//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){ }
//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ }