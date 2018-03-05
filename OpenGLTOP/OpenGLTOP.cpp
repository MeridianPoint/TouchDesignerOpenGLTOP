/* Shared Use License: This file is owned by Derivative Inc. (Derivative) and
 * can only be used, and/or modified for use, in conjunction with 
 * Derivative's TouchDesigner software, and only if you are a licensee who has
 * accepted Derivative's TouchDesigner license or assignment agreement (which
 * also govern the use of this file).  You may share a modified version of this
 * file with another authorized licensee of Derivative's TouchDesigner software.
 * Otherwise, no redistribution or sharing of this file, with or without
 * modification, is permitted.
 */

#include "OpenGLTOP.h"

#include <windows.h>

#include <stdio.h>
#include <cstring>
#include <string.h>
#include <gl/gl.h>
#include <assert.h>

//opencv
//#include <opencv2\core.hpp>
#include <opencv2\core\opengl.hpp>
#include <opencv2\core\cuda.hpp>


// These functions are basic C function, which the DLL loader can find
// much easier than finding a C++ Class.
// The DLLEXPORT prefix is needed so the compile exports these functions from the .dll
// you are creating
extern "C"
{

DLLEXPORT
int
GetTOPAPIVersion(void)
{
	// Always return TOP_CPLUSPLUS_API_VERSION in this function.
	return TOP_CPLUSPLUS_API_VERSION;
}

DLLEXPORT
TOP_CPlusPlusBase*
CreateTOPInstance(const OP_NodeInfo* info, TOP_Context *context)
{
	// Return a new instance of your class every time this is called.
	// It will be called once per TOP that is using the .dll
	return new OpenGLTOP(info);
}

DLLEXPORT
void
DestroyTOPInstance(TOP_CPlusPlusBase* instance, TOP_Context *context)
{
	// Delete the instance here, this will be called when
	// Touch is shutting down, when the TOP using that instance is deleted, or
	// if the TOP loads a different DLL
	delete (OpenGLTOP*)instance;
}

};


OpenGLTOP::OpenGLTOP(const OP_NodeInfo* info) : myNodeInfo(info)
{
	myRotation = 0.0;
	myExecuteCount = 0;
}

OpenGLTOP::~OpenGLTOP()
{

}

void
OpenGLTOP::getGeneralInfo(TOP_GeneralInfo* ginfo)
{
	// Uncomment this line if you want the TOP to cook every frame even
	// if none of it's inputs/parameters are changing.
	ginfo->cookEveryFrame = true;
}

bool
OpenGLTOP::getOutputFormat(TOP_OutputFormat* format)
{
	// In this function we could assign variable values to 'format' to specify
	// the pixel format/resolution etc that we want to output to.
	// If we did that, we'd want to return true to tell the TOP to use the settings we've
	// specified.
	// In this example we'll return false and use the TOP's settings
	return false;
}


void
OpenGLTOP::execute(const TOP_OutputFormatSpecs* outputFormat ,
							OP_Inputs* inputs,
							TOP_Context* context)
{
	myExecuteCount++;

	// These functions must be called before
	// beginGLCommands()/endGLCommands() block
	//double speed = inputs->getParDouble("Speed");


	//double color1[3];
	//double color2[3];

	//inputs->getParDouble3("Color1", color1[0], color1[1], color1[2]);
	//inputs->getParDouble3("Color2", color2[0], color2[1], color2[2]);


	//myRotation += speed;

	int width = outputFormat->width;
	int height = outputFormat->height;

	//get tracking parameters
	int nlevels = inputs->getParInt("Nlevel");
	int hit_threshold = inputs->getParInt("Hitthreshold");
	int win_stride = inputs->getParInt("Winstride");
	double scale = inputs->getParDouble("Scale");
	int gr_threshold = inputs->getParDouble("Groupthreshold");


	//draw bounding volume
	int DrawBounding = inputs->getParInt("Drawbounding");

	//int x = width / 2;
	//int y = height / 2;

	const OP_TOPInput * frameTOP = inputs->getInputTOP(0);

	//prepare img =============================
	if (frameTOP == nullptr) {
		ErrorMessage += "not enough input TOP";
		return;
	}
	else {
		ErrorMessage.clear();
	}

	GLuint inputTextureIndex = frameTOP->textureIndex;

	int Inputwidth = frameTOP->width;
	int Inputheight = frameTOP->height;

	// bind texture
	glBindTexture(GL_TEXTURE_2D, inputTextureIndex);
	//GetError();

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//GetError();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//GetError();

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WIDTH, Inputwidth);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_HEIGHT, Inputheight);

	glPixelStorei(GL_PACK_ALIGNMENT, 4);

	//::glViewport(0, 0, width, height);

	//::glMatrixMode(GL_PROJECTION);

	//::glLoadIdentity();
	//::glOrtho(0, width, 0, height, -1, 1);

	// Lets just draw a small square in the lower left quadrant of the texture
	//::glColor4f((float)color1[0], (float)color1[1], (float)color1[2], 1);
	//::glMatrixMode(GL_MODELVIEW);
	//::glPushMatrix();
	//::glLoadIdentity();
	//::glTranslatef(width / 2.0f, height / 2.0f, 0.0f);
	//::glRotatef((float)myRotation, 0.0f, 0.0f, 1.0f);
	//::glBegin(GL_QUADS);
	//::glVertex2i(0, 0);
	//::glVertex2i(width / 2, 0);
	//::glVertex2i(width / 2, height / 2);
	//::glVertex2i(0, height / 2);
	//::glEnd();
	//::glPopMatrix();

	// Draw a diamond to test anti-aliasing (it will draw over part of the above square)
	//::glPushMatrix();
	//::glLoadIdentity();
	//::glTranslatef(width / 2.0f, height / 2.0f, 0.0f);
	//::glRotatef((float)-myRotation, 0.0f, 0.0f, 1.0f);
	//::glColor4f((float)color2[0], (float)color2[1], (float)color2[2], 1);
	//::glBegin(GL_QUADS);
	//::glVertex2i(width / 2, 0);
	//::glVertex2i(width, height / 2);
	//::glVertex2i(width / 2, height);
	//::glVertex2i(0, height / 2);
	//::glEnd();
	//::glPopMatrix();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, inputTextureIndex);
	//glLoadIdentity();
	//glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);
	//::glLoadIdentity();
	//::glTranslatef(width / -2.0f, height / -2.0f, 0.0f);
	//::glScalef(1.0f, -1.0f, 1.0f);
	//::glTranslatef(-1.f, -1.f, 0.0f);
	
	//glBegin(GL_QUADS);
	// the reason why texture coordinates are weird - the texture is flipped horizontally
	//glTexCoord2f(0., 1.); glVertex2i(0, 0);
	//glTexCoord2f(1., 1.); glVertex2i(width, 0);
	//glTexCoord2f(1., 0.); glVertex2i(width, height);
	//glTexCoord2f(0., 0.); glVertex2i(0, height);
	//glTexCoord2f(0., 1.); glVertex2i(0, 0);
	//glTexCoord2f(1., 1.); glVertex2i(2, 0);
	//glTexCoord2f(1., 0.); glVertex2i(2, 2);
	//glTexCoord2f(0., 0.); glVertex2i(0, 2);
	//glTexCoord2f(0., 1.); glVertex2i(0, 0);
	//glEnd();
	//::glPopMatrix();

	//set up cuda
	cv::cuda::setDevice(0);

	//opengl to opencv
	cv::ogl::Buffer fboBuffer = cv::ogl::Buffer(Inputwidth, Inputheight, CV_8UC4);
	

	//fboBuffer.setAutoRelease(true);

	glReadBuffer(GL_FRONT);

	glBindTexture(GL_TEXTURE_2D, inputTextureIndex);
	//write to mat
	fboBuffer.bind(cv::ogl::Buffer::Target::PIXEL_PACK_BUFFER);

	//glBindTexture(GL_TEXTURE_2D, 0);
	//glBufferData(GL_PIXEL_PACK_BUFFER_ARB, width * height * 8, NULL, GL_STREAM_READ);
	//glPixelStorei(GL_UNPACK_ROW_LENGTH, Inputwidth);
	//glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	glPixelStorei(GL_PACK_ALIGNMENT, 4);
	glPixelStorei(GL_PACK_ROW_LENGTH, Inputwidth);
	

	glGetTexImage(GL_TEXTURE_2D, 0, GL_BGRA, GL_UNSIGNED_BYTE, 0);

	//glPixelStorei(GL_UNPACK_ROW_LENGTH, Inputwidth);
	//glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	
	//mat = fboBuffer.mapDevice();
	
	//fboBuffer.unmapDevice();

	fboBuffer.unbind(cv::ogl::Buffer::Target::PIXEL_PACK_BUFFER);
	glBindTexture(GL_TEXTURE_2D, 0);

	//prepare gpu mat
	cv::cuda::GpuMat mat = cv::cuda::GpuMat(width, height, CV_8UC4);
	
	fboBuffer.copyTo(mat);


	//Opencv process
	/*unsigned char * dataArray;

	unsigned char imgdata[64] = {
		255, 255, 0, 255,   255, 255, 0, 255,   255, 255, 0, 255,   255, 255, 0, 255,
		255, 255, 0, 255,   255, 255, 0, 255,   255, 255, 0, 255,   255, 255, 0, 255,
		255, 255, 0, 255,   255, 255, 0, 255,   255, 255, 0, 255,   255, 255, 0, 255,
		255, 255, 0, 255,   255, 255, 0, 255,   255, 255, 0, 255,   255, 255, 0, 255,
	};

	dataArray = imgdata;
*/
	//cv::Mat testMat = cv::Mat(cv::Size(4, 4), CV_8UC4, imgdata, 4);

	//convert color
	//cv::cvtColor(mat, mat, CV_RGBA2GRAY);

	cv::cuda::GpuMat flippedMat = cv::cuda::GpuMat(mat.cols, mat.rows, CV_8UC4, 4);

	cv::cuda::flip(mat, flippedMat, -1);

	//release mat
	mat.release();

	GPUHogPersonDetection(nlevels, gr_threshold, hit_threshold, scale, flippedMat);

	cv::Mat img_to_show = cv::Mat(flippedMat);


	

	cv::ogl::Texture2D outputTex = cv::ogl::Texture2D(cv::Size(width, height), cv::ogl::Texture2D::Format::RGBA, true);

	//draw rectangle

	if (DrawBounding) {
		for (size_t i = 0; i < detectedPerson.size(); i++)
		{
			cv::Rect r = detectedPerson[i];
			cv::rectangle(img_to_show, r.tl(), r.br(), cv::Scalar(0, 255, 0) * detectPersonConfidence[i] + cv::Scalar(255, 0, 0) * ( 1- detectPersonConfidence[i]), 3);
		}

		
		outputTex.copyFrom(img_to_show);
	}
	else {
		outputTex.copyFrom(flippedMat);
	}


	//outputTex.setAutoRelease(true);

	

	//release flippedMat
	fboBuffer.release();

	//outputTex.copyFrom(testMat);

	//delete [] dataArray;

		//testMat.release();

	mat.release();

	context->beginGLCommands();

	//cv::ogl::render(outputTex);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	::glViewport(0, 0, width, height);

	glLoadIdentity();
	glEnable(GL_TEXTURE_2D);

	outputTex.bind();

	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 0.1f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, -1.0f, 0.1f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, -1.0f, 0.1f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 1.0f, 0.1f);
	glEnd();

	//fbo
	/*GLuint fboID;
	glGenFramebuffers(1, &fboID);
	glBindFramebuffer(GL_FRAMEBUFFER, fboID);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, inputTextureIndex, 0);*/

	//glClearColor(0.0, 1.0, 0.0, 1.0);
	//glClear(GL_COLOR_BUFFER_BIT);
	////read pixels
	//glPixelStorei(GL_PACK_ALIGNMENT, 1);
	//GLubyte* pixels = (GLubyte*)malloc(width * height * 4 * sizeof(GLubyte));
	//glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

	glDisable(GL_TEXTURE_2D);

	outputTex.release();

	context->endGLCommands();
}

int
OpenGLTOP::getNumInfoCHOPChans()
{
	// We return the number of channel we want to output to any Info CHOP
	// connected to the TOP. In this example we are just going to send one channel.
	return 3 + detectedPerson.size() * 4;
}

void
OpenGLTOP::getInfoCHOPChan(int index,
										OP_InfoCHOPChan* chan)
{
	// This function will be called once for each channel we said we'd want to return
	// In this example it'll only be called once.

	if (index == 0)
	{
		chan->name = "executeCount";
		chan->value = (float)myExecuteCount;
	}

	if (index == 1)
	{
		chan->name = "rotation";
		chan->value = (float)myRotation;
	}

	if (index == 2)
	{
		chan->name = "Number of DetectedPerson";
		chan->value = (float)detectedPerson.size();
	}

	for (int i = 0; i < detectedPerson.size(); i++) {
		if (index == 3 + i * 4)
		{
			char * name = string2charPtr("tx" + std::to_string(i));
			//chan->name = ("tx" + std::to_string(i)).c_str();
			chan->name = name;
			chan->value = (float)detectedPerson[i].x;

			delete[] name;
		}
		if (index == 3 + i * 4 + 1)
		{
			char * name = string2charPtr("ty" + std::to_string(i));
			chan->name = name;
			//chan->name = ("ty" + std::to_string(i)).c_str();
			chan->value = (float)detectedPerson[i].y;

			delete[] name;
		}
		if (index == 3 + i * 4 + 2)
		{
			char * name = string2charPtr("width" + std::to_string(i));
			chan->name = name;
			//chan->name = ("width" + std::to_string(i)).c_str();
			chan->value = (float)detectedPerson[i].width;

			delete[] name;
		}
		if (index == 3 + i * 4 + 3)
		{
			char * name = string2charPtr("height" + std::to_string(i));
			chan->name = name;
			//chan->name = ("height" + std::to_string(i)).c_str();
			chan->value = (float)detectedPerson[i].height;

			delete[] name;
		}
	}
}

bool		
OpenGLTOP::getInfoDATSize(OP_InfoDATSize* infoSize)
{
	infoSize->rows = 2;
	infoSize->cols = 2;
	// Setting this to false means we'll be assigning values to the table
	// one row at a time. True means we'll do it one column at a time.
	infoSize->byColumn = false;
	return true;
}

void
OpenGLTOP::getInfoDATEntries(int index,
										int nEntries,
										OP_InfoDATEntries* entries)
{
	// It's safe to use static buffers here because Touch will make it's own
	// copies of the strings immediately after this call returns
	// (so the buffers can be reuse for each column/row)
	static char tempBuffer1[4096];
	static char tempBuffer2[4096];

	if (index == 0)
	{
		// Set the value for the first column
		strcpy_s(tempBuffer1, "executeCount");
		entries->values[0] = tempBuffer1;

		// Set the value for the second column
		sprintf_s(tempBuffer2, "%d", myExecuteCount);
		entries->values[1] = tempBuffer2;
	}

	if (index == 1)
	{
		// Set the value for the first column
		strcpy_s(tempBuffer1, "rotation");
		entries->values[0] = tempBuffer1;

		// Set the value for the second column
		sprintf_s(tempBuffer2, "%g", myRotation);
		entries->values[1] = tempBuffer2;
	}
}

void
OpenGLTOP::setupParameters(OP_ParameterManager* manager)
{
	// color 1
	//{
	//	OP_NumericParameter	np;

	//	np.name = "Color1";
	//	np.label = "Color 1";

	//	for (int i=0; i<3; i++)
	//	{
	//		np.defaultValues[i] = 1.0;
	//		np.minValues[i] = 0.0;
	//		np.maxValues[i] = 1.0;
	//		np.minSliders[i] = 0.0;
	//		np.maxSliders[i] = 1.0;
	//		np.clampMins[i] = true;
	//		np.clampMaxes[i] = true;
	//	}
	//	
	//	ParAppendResult res = manager->appendRGB(np);
	//	assert(res == PARAMETER_APPEND_SUCCESS);
	//}

	// color 2
	//{
	//	OP_NumericParameter	np;

	//	np.name = "Color2";
	//	np.label = "Color 2";

	//	for (int i=0; i<3; i++)
	//	{
	//		np.defaultValues[i] = 0.0;
	//		np.minValues[i] = 0.0;
	//		np.maxValues[i] = 1.0;
	//		np.minSliders[i] = 0.0;
	//		np.maxSliders[i] = 1.0;
	//		np.clampMins[i] = true;
	//		np.clampMaxes[i] = true;
	//	}
	//	
	//	ParAppendResult res = manager->appendRGB(np);
	//	assert(res == PARAMETER_APPEND_SUCCESS);
	//}

	// speed
	{
		OP_NumericParameter	np;

		np.name = "Speed";
		np.label = "Speed";
		np.defaultValues[0] = 1.0;
		np.minSliders[0] = -10.0;
		np.maxSliders[0] =  10.0;
		
		ParAppendResult res = manager->appendFloat(np);
		assert(res == PARAMETER_APPEND_SUCCESS);
	}

	// pulse
	{
		OP_NumericParameter	np;

		np.name = "Reset";
		np.label = "Reset";
		
		ParAppendResult res = manager->appendPulse(np);
		assert(res == PARAMETER_APPEND_SUCCESS);
	}
	/// parameters for person tracking  ---------------------///

	//number of levels
	{
		OP_NumericParameter	np;

		np.name = "Nlevel";
		np.label = "Number of levels";
		np.defaultValues[0] = 5.0;
		np.minSliders[0] = 0.0;
		np.maxSliders[0] = 10.0;

		ParAppendResult res = manager->appendInt(np);
		assert(res == PARAMETER_APPEND_SUCCESS);
	}

	//hit threshold
	{
		OP_NumericParameter	np;

		np.name = "Hitthreshold";
		np.label = "hit threshold";
		np.defaultValues[0] = 6.0;
		np.minSliders[0] = 0.0;
		np.maxSliders[0] = 10.0;

		ParAppendResult res = manager->appendInt(np);
		assert(res == PARAMETER_APPEND_SUCCESS);
	}

	//WinStride
	{
		OP_NumericParameter	np;

		np.name = "Winstride";
		np.label = "Window Stride";

		ParAppendResult res = manager->appendInt(np);
		assert(res == PARAMETER_APPEND_SUCCESS);
	}

	//scale
	{
		OP_NumericParameter	np;

		np.name = "Scale";
		np.label = "Scale";
		np.defaultValues[0] = 1.0;
		np.minSliders[0] = 0.0;
		np.maxSliders[0] = 4.0;

		ParAppendResult res = manager->appendFloat(np);
		assert(res == PARAMETER_APPEND_SUCCESS);
	}

	//group threshold
	{
		OP_NumericParameter	np;

		np.name = "Groupthreshold";
		np.label = "Group Threshold";
		np.defaultValues[0] = 0.0;
		np.minSliders[0] = 0.0;
		np.maxSliders[0] = 10.0;

		ParAppendResult res = manager->appendInt(np);
		assert(res == PARAMETER_APPEND_SUCCESS);
	}

	//draw bounding box or not
	{
		OP_NumericParameter	np;

		np.name = "Drawbounding";
		np.label = "Draw Bounding";

		ParAppendResult res = manager->appendToggle(np);
		assert(res == PARAMETER_APPEND_SUCCESS);
	}

	//show bounding box in info chop or not
	{
		OP_NumericParameter	np;

		np.name = "Outputbounding";
		np.label = "Output Bounding";

		ParAppendResult res = manager->appendToggle(np);
		assert(res == PARAMETER_APPEND_SUCCESS);
	}
}

void
OpenGLTOP::pulsePressed(const char* name)
{
	if (!strcmp(name, "Reset"))
	{
		myRotation = 0.0;
	}

}

void OpenGLTOP::GPUHogPersonDetection(int nlevels, int gr_threshold, int hit_threshold, double scale, cv::cuda::GpuMat Mat)
{
	//set up detector
	cv::Size win_size = cv::Size(48, 96); //(64, 128) or (48, 96)
							   //Size win_stride(args.win_stride_width, args.win_stride_height);
	cv::Size win_stride = cv::Size(32, 32);
	//cv::Size win_size(args.win_width, args.win_width * 2);
	cv::Size block_size = cv::Size(64, 64);
	cv::Size block_stride = cv::Size(8, 8);
	cv::Size cell_size = cv::Size(4, 4);
	int bins = 9;

	//cv::Ptr<cv::cuda::HOG> gpu_hog = cv::cuda::HOG::create(win_size, block_size, block_stride, cell_size, bins);
	cv::Ptr<cv::cuda::HOG> gpu_hog = cv::cuda::HOG::create(cv::Size(48, 96), cv::Size(16, 16));

	// Create HOG descriptors and detectors here
	cv::Mat detector = gpu_hog->getDefaultPeopleDetector();

	gpu_hog->setSVMDetector(detector);

	//convert to cuda format
	//cv::cuda::GpuMat gpu_img;

	std::vector<cv::Rect> found;

	//hardcoded parameters
	//int nlevels = 5;
	//int gr_threshold = 2;
	//int hit_threshold = 0;
	//double scale = 1.0;

	//cv::Mat img_to_show = img;

	// Perform HOG classification
	//gpu_img.upload(img);
	gpu_hog->setNumLevels(nlevels);
	gpu_hog->setHitThreshold(hit_threshold);
	gpu_hog->setWinStride(cv::Size(32, 32));
	gpu_hog->setScaleFactor(scale);
	gpu_hog->setGroupThreshold(gr_threshold);
	gpu_hog->detectMultiScale(Mat, found, &detectPersonConfidence);

	//return std::vector<cv::Rect>();

	// Draw positive classified windows
	/*for (size_t i = 0; i < found.size(); i++)
	{
		cv::Rect r = found[i];
		rectangle(img_to_show, r.tl(), r.br(), cv::Scalar(0, 255, 0), 3);
	}*/

	//img = img_to_show;

	//release hog descriper
	gpu_hog.release();

	detectedPerson = found;

	if (found.size() != 0) {
		std::cout << found.size();
	}
	//return found;
}

void OpenGLTOP::RemoveNonStatic(cv::cuda::GpuMat Diff)
{
}

char * OpenGLTOP::string2charPtr(std::string str)
{
	char * strarray = new char[str.size() + 1];
	std::strcpy(strarray, str.c_str());
	return strarray;
}
