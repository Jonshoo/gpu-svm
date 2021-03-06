/*
 * cvFunction.cpp
 *
 *  Created on: 09/12/2014
 *      Author: Zeyi Wen
 */

#include<iostream>
#include<cassert>
#include <stdio.h>

#include "cvFunction.h"

#include "../svm-shared/HessianIO/seqAccessor.h"
#include "../svm-shared/HessianIO/parAccessor.h"
//#include "hessianIO.h"
#include "../svm-shared/kernelCalculater/kernelCalculater.h"
#include "../svm-shared/svmTrainer.h"
#include "svmPredictor.h"
#include "modelSelector.h"
#include "../svm-shared/smoSolver.h"
#include "../svm-shared/Cache/cache.h"
#include "../svm-shared/fileOps.h"
#include "../DataReader/BaseLibsvmReader.h"
#include "../DataReader/LibsvmReaderSparse.h"

using std::cout;
using std::endl;

//device function for CPairSelector
void gridSearch(Grid &SGrid, string strTrainingFileName){
	lIO_timer = 0;

	vector<vector<float_point> > v_vDocVector;
	vector<int> v_nLabel;

	int nNumofFeature = 0;
	int nNumofInstance = 0;
	long long nNumofValue = 0;
	BaseLibSVMReader::GetDataInfo(strTrainingFileName, nNumofFeature, nNumofInstance, nNumofValue);
	LibSVMDataReader drHelper;
	drHelper.ReadLibSVMAsDense(v_vDocVector, v_nLabel, strTrainingFileName, nNumofFeature);

	CModelSelector modelSelector;

	timeval t1, t2;
	float_point elapsedTime;
	gettimeofday(&t1, NULL);
	modelSelector.GridSearch(SGrid, v_vDocVector, v_nLabel);
	gettimeofday(&t2, NULL);
	elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;
	elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;
	//cout << elapsedTime << " ms.\n";
}

void crossValidation(SVMParam &param, string strTrainingFileName){
	//initialize grid
	Grid SGrid;
	SGrid.vfC.push_back(param.C);
	SGrid.vfGamma.push_back(param.gamma);

	gridSearch(SGrid, strTrainingFileName);
}
