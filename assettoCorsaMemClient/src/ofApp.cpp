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
		physicsOutput << "PHYSICS ====================================" << endl << endl
			<< "packetId" << '\t' << physicsData->packetId << endl
			<< "gas" << '\t' << physicsData->gas << endl
			<< "brake" << '\t' << physicsData->brake << endl
			<< "fuel" << '\t' << physicsData->fuel << endl
			<< "gear" << '\t' << physicsData->gear << endl
			<< "rpms" << '\t' << physicsData->rpms << endl
			<< "steerAngle" << '\t' << physicsData->steerAngle << endl
			<< "speedKmh" << '\t' << physicsData->speedKmh << endl
			<< "velocity" << '\t' << physicsData->velocity << endl
			<< "accG" << '\t' << physicsData->accG << endl
			<< "wheelSlip" << '\t' << physicsData->wheelSlip << endl
			<< "wheelLoad" << '\t' << physicsData->wheelLoad << endl
			<< "wheelsPressure" << '\t' << physicsData->wheelsPressure << endl
			<< "wheelAngularSpeed" << '\t' << physicsData->wheelAngularSpeed << endl
			<< "tyreWear" << '\t' << physicsData->tyreWear << endl
			<< "tyreDirtyLevel" << '\t' << physicsData->tyreDirtyLevel << endl
			<< "tyreCoreTemperature" << '\t' << physicsData->tyreCoreTemperature << endl
			<< "camberRAD" << '\t' << physicsData->camberRAD << endl
			<< "suspensionTravel" << '\t' << physicsData->suspensionTravel << endl
			<< "drs" << '\t' << physicsData->drs << endl
			<< "tc" << '\t' << physicsData->tc << endl
			<< "heading" << '\t' << physicsData->heading << endl
			<< "pitch" << '\t' << physicsData->pitch << endl
			<< "roll" << '\t' << physicsData->roll << endl
			<< "cgHeight" << '\t' << physicsData->cgHeight << endl
			<< "carDamage" << '\t' << physicsData->carDamage << endl
			<< "numberOfTyresOut" << '\t' << physicsData->numberOfTyresOut << endl
			<< "pitLimiterOn" << '\t' << physicsData->pitLimiterOn << endl
			<< "abs" << '\t' << physicsData->abs << endl
			<< "kersCharge" << '\t' << physicsData->kersCharge << endl
			<< "kersInput" << '\t' << physicsData->kersInput << endl
			<< "autoShifterOn" << '\t' << physicsData->autoShifterOn << endl
			<< "rideHeight" << '\t' << physicsData->rideHeight << endl
			<< "turboBoost" << '\t' << physicsData->turboBoost << endl
			<< "ballast" << '\t' << physicsData->ballast << endl
			<< "airDensity" << '\t' << physicsData->airDensity << endl
			<< "airTemp" << '\t' << physicsData->airTemp << endl
			<< "roadTemp" << '\t' << physicsData->roadTemp << endl
			<< "localAngularVel" << '\t' << physicsData->localAngularVel << endl
			<< "finalFF" << '\t' << physicsData->finalFF << endl
			<< "performanceMeter" << '\t' << physicsData->performanceMeter << endl
			<< "engineBrake" << '\t' << physicsData->engineBrake << endl
			<< "ersRecoveryLevel" << '\t' << physicsData->ersRecoveryLevel << endl
			<< "ersPowerLevel" << '\t' << physicsData->ersPowerLevel << endl
			<< "ersHeatCharging" << '\t' << physicsData->ersHeatCharging << endl
			<< "ersIsCharging" << '\t' << physicsData->ersIsCharging << endl
			<< "kersCurrentKJ" << '\t' << physicsData->kersCurrentKJ << endl
			<< "drsAvailable" << '\t' << physicsData->drsAvailable << endl
			<< "drsEnabled" << '\t' << physicsData->drsEnabled << endl;

		graphicsOutput << "GRAPHICS INFO =============================" << endl << endl
			<< "packetID" << '\t' << graphicsData->packetId << endl
			<< "STATUS " << '\t' << graphicsData->status << endl
			<< "session" << '\t' << graphicsData->session << endl
			<< "completed laps" << '\t' << graphicsData->completedLaps << endl
			<< "position" << '\t' << graphicsData->position << endl
			<< "current time s" << '\t' << graphicsData->currentTime << endl
			<< "current time" << '\t' << graphicsData->iCurrentTime << endl
			<< "last time" << '\t' << graphicsData->iLastTime << endl
			<< "best time" << '\t' << graphicsData->iBestTime << endl
			<< "sessionTimeLeft" << '\t' << graphicsData->sessionTimeLeft << endl
			<< "distanceTraveled" << '\t' << graphicsData->distanceTraveled << endl
			<< "isInPit" << '\t' << graphicsData->isInPit << endl
			<< "currentSectorIndex" << '\t' << graphicsData->currentSectorIndex << endl
			<< "lastSectorTime" << '\t' << graphicsData->lastSectorTime << endl
			<< "numberOfLaps" << '\t' << graphicsData->numberOfLaps << endl
			<< "TYRE COMPOUND : " << '\t' << graphicsData->tyreCompound << endl
			<< "replayMult" << '\t' << graphicsData->replayTimeMultiplier << endl
			<< "normalizedCarPosition" << '\t' << graphicsData->normalizedCarPosition << endl
			<< "carCoordinates" << '\t' << graphicsData->carCoordinates << endl;

		fileStaticOutput << "STATIC INFO =============================" << endl << endl
			<< "smVersion" << '\t' << fileStaticData->smVersion << endl
			<< "acVersion" << '\t' << fileStaticData->acVersion << endl
			<< "numberOfSessions" << '\t' << fileStaticData->numberOfSessions << endl
			<< "numCars" << '\t' << fileStaticData->numCars << endl
			<< "carModel" << '\t' << fileStaticData->carModel << endl
			<< "track" << '\t' << fileStaticData->track << endl
			<< "playerName" << '\t' << fileStaticData->playerName << endl
			<< "playerSurname" << '\t' << fileStaticData->playerSurname << endl
			<< "playerNick" << '\t' << fileStaticData->playerNick << endl
			<< "sectorCount" << '\t' << fileStaticData->sectorCount << endl
			<< "maxTorque" << '\t' << fileStaticData->maxTorque << endl
			<< "maxPower" << '\t' << fileStaticData->maxPower << endl
			<< "maxRpm" << '\t' << fileStaticData->maxRpm << endl
			<< "maxFuel" << '\t' << fileStaticData->maxFuel << endl
			<< "suspensionMaxTravel" << '\t' << fileStaticData->suspensionMaxTravel << endl
			<< "tyreRadius" << '\t' << fileStaticData->tyreRadius << endl
			<< "maxTurboBoost" << '\t' << fileStaticData->maxTurboBoost << endl
			<< "deprecated_1" << '\t' << fileStaticData->deprecated_1 << endl
			<< "deprecated_2" << '\t' << fileStaticData->deprecated_2 << endl
			<< "penaltiesEnabled" << '\t' << fileStaticData->penaltiesEnabled << endl
			<< "aidFuelRate" << '\t' << fileStaticData->aidFuelRate << endl
			<< "aidTireRate" << '\t' << fileStaticData->aidTireRate << endl
			<< "aidMechanicalDamage" << '\t' << fileStaticData->aidMechanicalDamage << endl
			<< "aidAllowTyreBlankets" << '\t' << fileStaticData->aidAllowTyreBlankets << endl
			<< "aidStability" << '\t' << fileStaticData->aidStability << endl
			<< "aidAutoClutch" << '\t' << fileStaticData->aidAutoClutch << endl
			<< "aidAutoBlip" << '\t' << fileStaticData->aidAutoBlip << endl
			<< "hasDRS" << '\t' << fileStaticData->hasDRS << endl
			<< "hasERS" << '\t' << fileStaticData->hasERS << endl
			<< "hasKERS" << '\t' << fileStaticData->hasKERS << endl
			<< "kersMaxJ" << '\t' << fileStaticData->kersMaxJ << endl
			<< "engineBrakeSettingsCount" << '\t' << fileStaticData->engineBrakeSettingsCount << endl
			<< "ersPowerControllerCount" << '\t' << fileStaticData->ersPowerControllerCount << endl

			<< "trackSPlineLength" << '\t' << fileStaticData->trackSPlineLength << endl
			<< "trackConfiguration" << '\t' << fileStaticData->trackConfiguration << endl;

		ofDrawBitmapStringHighlight(physicsOutput.str(), 20, 20);
		ofDrawBitmapStringHighlight(graphicsOutput.str(), 390, 20);
		ofDrawBitmapStringHighlight(fileStaticOutput.str(), 750, 20);
		
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
