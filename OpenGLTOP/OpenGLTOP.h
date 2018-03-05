/* Shared Use License: This file is owned by Derivative Inc. (Derivative) and
 * can only be used, and/or modified for use, in conjunction with 
 * Derivative's TouchDesigner software, and only if you are a licensee who has
 * accepted Derivative's TouchDesigner license or assignment agreement (which
 * also govern the use of this file).  You may share a modified version of this
 * file with another authorized licensee of Derivative's TouchDesigner software.
 * Otherwise, no redistribution or sharing of this file, with or without
 * modification, is permitted.
 */

#include "TOP_CPlusPlusBase.h"

#include <vector>
//#include <opencv2\core.hpp>
#include <opencv2/core/utility.hpp>
#include "opencv2/cudaobjdetect.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2\cudaimgproc.hpp"
#include "opencv2\cudaarithm.hpp"
//#include "gl/glew.h"

#include <iostream>


class OpenGLTOP : public TOP_CPlusPlusBase
{
public:
	OpenGLTOP(const OP_NodeInfo *info);
	virtual ~OpenGLTOP();

	virtual void		getGeneralInfo(TOP_GeneralInfo *) override;
	virtual bool		getOutputFormat(TOP_OutputFormat*) override;


	virtual void		execute(const TOP_OutputFormatSpecs*,
								OP_Inputs*,
								TOP_Context *context) override;


	virtual int			getNumInfoCHOPChans() override;
	virtual void		getInfoCHOPChan(int index,
										OP_InfoCHOPChan *chan) override;

	virtual bool		getInfoDATSize(OP_InfoDATSize *infoSize) override;
	virtual void		getInfoDATEntries(int index,
											int nEntries,
											OP_InfoDATEntries *entries) override;

	virtual void		setupParameters(OP_ParameterManager *manager) override;
	virtual void		pulsePressed(const char *name) override;

private:

	// We don't need to store this pointer, but we do for the example.
	// The OP_NodeInfo class store information about the node that's using
	// this instance of the class (like its name).
	const OP_NodeInfo		*myNodeInfo;

	// In this example this value will be incremented each time the execute()
	// function is called, then passes back to the TOP 
	int						 myExecuteCount;
	double					 myRotation;

	//parameters for person detection
	std::vector<cv::Rect> detectedPerson;

	std::vector<double>	detectPersonConfidence;

	//error message
	std::string ErrorMessage;

	//priavte functions

	//CUDA based GPU HOG person tracking
	void GPUHogPersonDetection(int nlevels, int gr_threshold, int hit_threshold, double scale, cv::cuda::GpuMat Mat);

	//discard moving part
	void RemoveNonStatic(cv::cuda::GpuMat Diff);

	char * string2charPtr(std::string str);
};
