/*
 * testTrainer.h
 *
 *  Created on: 31/10/2013
 *      Author: Zeyi Wen
 */

#ifndef TESTTRAINER_H_
#define TESTTRAINER_H_

#include <iostream>
#include "svmModel.h"
#include "../svm-shared/svmParam.h"
#include "../svm-shared/gpu_global_utility.h"

using std::string;

void trainSVM(SVMParam &param, string strTrainingFileName, int nNumofFeature, SvmModel &model, bool evaluateTrainingError = false);

void evaluateSVMClassifier(SvmModel &model, string strTrainingFileName, int nNumofFeature);

void evaluate(SvmModel &model, vector<vector<KeyValue> > &v_v_Instance, vector<int> &v_nLabel, vector<float_point> &classificationError);

#endif /* TESTTRAINER_H_ */
