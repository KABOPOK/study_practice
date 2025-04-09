#include "algoritms.h"
void makePlusOperation(char* expression, int& begin, int& end, fraction& firstFrac, fraction& secondFrac,
	std::vector<Value>& globalValues, std::vector<Value>& localValues, int& fIndx, int& sIndx, bool& fLocal, bool& sLocal)
{
	if (fIndx == -1 && sIndx == -1) {
		std::string local(('~') + std::to_string(localValues.size()));
		localValues.push_back(Value(local, firstFrac + secondFrac));
		int l = 0;
		for (int j = begin; j < begin + local.size(); ++j, ++l) {
			expression[j] = local[l];
		}
		for (int j = (int)(local.size() + begin); j <= end; ++j) {
			expression[j] = 0;
		}
	}
	else if (fIndx == -1) {
		std::string local(('~') + to_string(localValues.size()));
		if (sLocal) {
			localValues.push_back(Value(local, localValues[sIndx].getFraction() + firstFrac));
		}
		else {
			localValues.push_back(Value(local, globalValues[sIndx].getFraction() + firstFrac));
		}
		int l = 0;
		for (int j = begin; j < begin + local.size(); ++j, ++l) {
			expression[j] = local[l];
		}
		for (int j = (int)(local.size() + begin); j <= end; ++j) {
			expression[j] = 0;
		}
	}
	else if (sIndx == -1) {
		std::string local(('~') + to_string(localValues.size()));
		if (fLocal) {
			localValues.push_back(Value(local, localValues[fIndx].getFraction() + secondFrac));
		}
		else {
			localValues.push_back(Value(local, globalValues[fIndx].getFraction() + secondFrac));
		}
		int l = 0;
		for (int j = begin; j < begin + local.size(); ++j, ++l) {
			expression[j] = local[l];
		}
		for (int j = (int)(local.size() + begin); j <= end; ++j) {
			expression[j] = 0;
		}
	}
	else if (fLocal && sLocal) {
		std::string local(('~') + to_string(localValues.size()));
		if (localValues[fIndx].getType()) {
			localValues.push_back(Value(local, localValues[fIndx].getMatrix() + localValues[sIndx].getMatrix()));
		}
		else {
			localValues.push_back(Value(local, localValues[fIndx].getFraction() + localValues[sIndx].getFraction()));
		}
		int l = 0;
		for (int j = begin; j < begin + local.size(); ++j, ++l) {
			expression[j] = local[l];
		}
		for (int j = (int)(local.size() + begin); j <= end; ++j) {
			expression[j] = 0;
		}
	}
	else if (fLocal) {
		std::string local(('~') + to_string(localValues.size()));
		if (localValues[fIndx].getType()) {
			localValues.push_back(Value(('~') + to_string(localValues.size()), localValues[fIndx].getMatrix() + globalValues[sIndx].getMatrix()));
		}
		else {
			localValues.push_back(Value(('~') + to_string(localValues.size()), localValues[fIndx].getFraction() + globalValues[sIndx].getFraction()));
		}
		int l = 0;
		for (int j = begin; j < begin + local.size(); ++j, ++l) {
			expression[j] = local[l];
		}
		for (int j = (int)(local.size() + begin); j <= end; ++j) {
			expression[j] = 0;
		}
	}
	else if (sLocal) {
		std::string local(('~') + to_string(localValues.size()));
		if (localValues[sIndx].getType()) {
			localValues.push_back(Value(local, globalValues[fIndx].getMatrix() + localValues[sIndx].getMatrix()));
		}
		else {
			localValues.push_back(Value(local, globalValues[fIndx].getFraction() + localValues[sIndx].getFraction()));
		}
		int l = 0;
		for (int j = begin; j < begin + local.size(); ++j, ++l) {
			expression[j] = local[l];
		}
		for (int j = (int)(local.size() + begin); j <= end; ++j) {
			expression[j] = 0;
		}
	}
	else {
		std::string local(('~') + to_string(localValues.size()));
		if (globalValues[fIndx].getType()) {
			localValues.push_back(Value(local, globalValues[fIndx].getMatrix() + globalValues[sIndx].getMatrix()));
		}
		else {
			localValues.push_back(Value(local, globalValues[fIndx].getFraction() + globalValues[sIndx].getFraction()));
		}
		int l = 0;
		for (int j = begin; j < begin + local.size(); ++j, ++l) {
			expression[j] = local[l];
		}
		for (int j = (int)(local.size() + begin); j <= end; ++j) {
			expression[j] = 0;
		}
	}
}
void makeMultiplicationOperation(char* expression, int& begin, int& end, fraction& firstFrac, fraction& secondFrac,
	std::vector<Value>& globalValues, std::vector<Value>& localValues, int& fIndx, int& sIndx, bool& fLocal, bool& sLocal)
{
	if (fIndx == -1 && sIndx == -1) {
		std::string local(('~') + std::to_string(localValues.size()));
		localValues.push_back(Value(local, firstFrac * secondFrac));
		int l = 0;
		for (int j = begin; j < begin + local.size(); ++j, ++l) {
			expression[j] = local[l];
		}
		for (int j = (int)(local.size() + begin); j <= end; ++j) {
			expression[j] = 0;
		}
	}
	else if (fIndx == -1) {
		std::string local(('~') + to_string(localValues.size()));
		if (sLocal) {
			localValues.push_back(Value(local, localValues[sIndx].getFraction() * firstFrac));
		}
		else {
			localValues.push_back(Value(local, globalValues[sIndx].getFraction() * firstFrac));
		}
		int l = 0;
		for (int j = begin; j < begin + local.size(); ++j, ++l) {
			expression[j] = local[l];
		}
		for (int j = (int)(local.size() + begin); j <= end; ++j) {
			expression[j] = 0;
		}
	}
	else if (sIndx == -1) {
		std::string local(('~') + to_string(localValues.size()));
		if (fLocal) {
			localValues.push_back(Value(local, localValues[fIndx].getFraction() * secondFrac));
		}
		else {
			localValues.push_back(Value(local, globalValues[fIndx].getFraction() * secondFrac));
		}
		int l = 0;
		for (int j = begin; j < begin + local.size(); ++j, ++l) {
			expression[j] = local[l];
		}
		for (int j = (int)(local.size() + begin); j <= end; ++j) {
			expression[j] = 0;
		}
	}
	else if (fLocal && sLocal) {
		std::string local(('~') + to_string(localValues.size()));
		if (localValues[fIndx].getType()) {
			localValues.push_back(Value(local, localValues[fIndx].getMatrix() * localValues[sIndx].getMatrix()));
		}
		else {
			localValues.push_back(Value(local, localValues[fIndx].getFraction() * localValues[sIndx].getFraction()));
		}
		int l = 0;
		for (int j = begin; j < begin + local.size(); ++j, ++l) {
			expression[j] = local[l];
		}
		for (int j = (int)(local.size() + begin); j <= end; ++j) {
			expression[j] = 0;
		}
	}
	else if (fLocal) {
		std::string local(('~') + to_string(localValues.size()));
		if (localValues[fIndx].getType()) {
			localValues.push_back(Value(('~') + to_string(localValues.size()), localValues[fIndx].getMatrix() * globalValues[sIndx].getMatrix()));
		}
		else {
			localValues.push_back(Value(('~') + to_string(localValues.size()), localValues[fIndx].getFraction() * globalValues[sIndx].getFraction()));
		}
		int l = 0;
		for (int j = begin; j < begin + local.size(); ++j, ++l) {
			expression[j] = local[l];
		}
		for (int j = (int)(local.size() + begin); j <= end; ++j) {
			expression[j] = 0;
		}
	}
	else if (sLocal) {
		std::string local(('~') + to_string(localValues.size()));
		if (localValues[sIndx].getType()) {
			localValues.push_back(Value(local, globalValues[fIndx].getMatrix() * localValues[sIndx].getMatrix()));
		}
		else {
			localValues.push_back(Value(local, globalValues[fIndx].getFraction() * localValues[sIndx].getFraction()));
		}
		int l = 0;
		for (int j = begin; j < begin + local.size(); ++j, ++l) {
			expression[j] = local[l];
		}
		for (int j = (int)(local.size() + begin); j <= end; ++j) {
			expression[j] = 0;
		}
	}
	else {
		std::string local(('~') + to_string(localValues.size()));
		if (globalValues[fIndx].getType()) {
			localValues.push_back(Value(local, globalValues[fIndx].getMatrix() * globalValues[sIndx].getMatrix()));
		}
		else {
			localValues.push_back(Value(local, globalValues[fIndx].getFraction() * globalValues[sIndx].getFraction()));
		}
		int l = 0;
		for (int j = begin; j < begin + local.size(); ++j, ++l) {
			expression[j] = local[l];
		}
		for (int j = (int)(local.size() + begin); j <= end; ++j) {
			expression[j] = 0;
		}
	}
}
void makeDivisionOperation(char* expression, int& begin, int& end, fraction& firstFrac, fraction& secondFrac,
	std::vector<Value>& globalValues, std::vector<Value>& localValues, int& fIndx, int& sIndx, bool& fLocal, bool& sLocal)
{
	if (fIndx == -1 && sIndx == -1) {
		std::string local(('~') + std::to_string(localValues.size()));
		localValues.push_back(Value(local, firstFrac / secondFrac));
		int l = 0;
		for (int j = begin; j < begin + local.size(); ++j, ++l) {
			expression[j] = local[l];
		}
		for (int j = (int)(local.size() + begin); j <= end; ++j) {
			expression[j] = 0;
		}
	}
	else if (fIndx == -1) {
		std::string local(('~') + to_string(localValues.size()));
		if (sLocal) {
			localValues.push_back(Value(local, localValues[sIndx].getFraction() / firstFrac));
		}
		else {
			localValues.push_back(Value(local, globalValues[sIndx].getFraction() / firstFrac));
		}
		int l = 0;
		for (int j = begin; j < begin + local.size(); ++j, ++l) {
			expression[j] = local[l];
		}
		for (int j = (int)(local.size() + begin); j <= end; ++j) {
			expression[j] = 0;
		}
	}
	else if (sIndx == -1) {
		std::string local(('~') + to_string(localValues.size()));
		if (fLocal) {
			localValues.push_back(Value(local, localValues[fIndx].getFraction() / secondFrac));
		}
		else {
			localValues.push_back(Value(local, globalValues[fIndx].getFraction() / secondFrac));
		}
		int l = 0;
		for (int j = begin; j < begin + local.size(); ++j, ++l) {
			expression[j] = local[l];
		}
		for (int j = (int)(local.size() + begin); j <= end; ++j) {
			expression[j] = 0;
		}
	}
	else if (fLocal && sLocal) {
		std::string local(('~') + to_string(localValues.size()));
		if (localValues[fIndx].getType()) {
			localValues.push_back(Value(local, localValues[fIndx].getMatrix() / localValues[sIndx].getMatrix()));
		}
		else {
			localValues.push_back(Value(local, localValues[fIndx].getFraction() / localValues[sIndx].getFraction()));
		}
		int l = 0;
		for (int j = begin; j < begin + local.size(); ++j, ++l) {
			expression[j] = local[l];
		}
		for (int j = (int)(local.size() + begin); j <= end; ++j) {
			expression[j] = 0;
		}
	}
	else if (fLocal) {
		std::string local(('~') + to_string(localValues.size()));
		if (localValues[fIndx].getType()) {
			localValues.push_back(Value(('~') + to_string(localValues.size()), localValues[fIndx].getMatrix() / globalValues[sIndx].getMatrix()));
		}
		else {
			localValues.push_back(Value(('~') + to_string(localValues.size()), localValues[fIndx].getFraction() / globalValues[sIndx].getFraction()));
		}
		int l = 0;
		for (int j = begin; j < begin + local.size(); ++j, ++l) {
			expression[j] = local[l];
		}
		for (int j = (int)(local.size() + begin); j <= end; ++j) {
			expression[j] = 0;
		}
	}
	else if (sLocal) {
		std::string local(('~') + to_string(localValues.size()));
		if (localValues[sIndx].getType()) {
			localValues.push_back(Value(local, globalValues[fIndx].getMatrix() / localValues[sIndx].getMatrix()));
		}
		else {
			localValues.push_back(Value(local, globalValues[fIndx].getFraction() / localValues[sIndx].getFraction()));
		}
		int l = 0;
		for (int j = begin; j < begin + local.size(); ++j, ++l) {
			expression[j] = local[l];
		}
		for (int j = (int)(local.size() + begin); j <= end; ++j) {
			expression[j] = 0;
		}
	}
	else {
		std::string local(('~') + to_string(localValues.size()));
		if (globalValues[fIndx].getType()) {
			localValues.push_back(Value(local, globalValues[fIndx].getMatrix() / globalValues[sIndx].getMatrix()));
		}
		else {
			localValues.push_back(Value(local, globalValues[fIndx].getFraction() / globalValues[sIndx].getFraction()));
		}
		int l = 0;
		for (int j = begin; j < begin + local.size(); ++j, ++l) {
			expression[j] = local[l];
		}
		for (int j = (int)(local.size() + begin); j <= end; ++j) {
			expression[j] = 0;
		}
	}
}
void makeSubtractionOperation(char* expression, int& begin, int& end, fraction& firstFrac, fraction& secondFrac,
	std::vector<Value>& globalValues, std::vector<Value>& localValues, int& fIndx, int& sIndx, bool& fLocal, bool& sLocal)
{
	if (fIndx == -1 && sIndx == -1) {
		std::string local(('~') + std::to_string(localValues.size()));
		localValues.push_back(Value(local, firstFrac - secondFrac));
		int l = 0;
		for (int j = begin; j < begin + local.size(); ++j, ++l) {
			expression[j] = local[l];
		}
		for (int j = (int)(local.size() + begin); j <= end; ++j) {
			expression[j] = 0;
		}
	}
	else if (fIndx == -1) {
		std::string local(('~') + to_string(localValues.size()));
		if (sLocal) {
			localValues.push_back(Value(local, localValues[sIndx].getFraction() - firstFrac));
		}
		else {
			localValues.push_back(Value(local, globalValues[sIndx].getFraction() - firstFrac));
		}
		int l = 0;
		for (int j = begin; j < begin + local.size(); ++j, ++l) {
			expression[j] = local[l];
		}
		for (int j = (int)(local.size() + begin); j <= end; ++j) {
			expression[j] = 0;
		}
	}
	else if (sIndx == -1) {
		std::string local(('~') + to_string(localValues.size()));
		if (fLocal) {
			localValues.push_back(Value(local, localValues[fIndx].getFraction() - secondFrac));
		}
		else {
			localValues.push_back(Value(local, globalValues[fIndx].getFraction() - secondFrac));
		}
		int l = 0;
		for (int j = begin; j < begin + local.size(); ++j, ++l) {
			expression[j] = local[l];
		}
		for (int j = (int)(local.size() + begin); j <= end; ++j) {
			expression[j] = 0;
		}
	}
	else if (fLocal && sLocal) {
		std::string local(('~') + to_string(localValues.size()));
		if (localValues[fIndx].getType()) {
			localValues.push_back(Value(local, localValues[fIndx].getMatrix() - localValues[sIndx].getMatrix()));
		}
		else {
			localValues.push_back(Value(local, localValues[fIndx].getFraction() - localValues[sIndx].getFraction()));
		}
		int l = 0;
		for (int j = begin; j < begin + local.size(); ++j, ++l) {
			expression[j] = local[l];
		}
		for (int j = (int)(local.size() + begin); j <= end; ++j) {
			expression[j] = 0;
		}
	}
	else if (fLocal) {
		std::string local(('~') + to_string(localValues.size()));
		if (localValues[fIndx].getType()) {
			localValues.push_back(Value(('~') + to_string(localValues.size()), localValues[fIndx].getMatrix() - globalValues[sIndx].getMatrix()));
		}
		else {
			localValues.push_back(Value(('~') + to_string(localValues.size()), localValues[fIndx].getFraction() - globalValues[sIndx].getFraction()));
		}
		int l = 0;
		for (int j = begin; j < begin + local.size(); ++j, ++l) {
			expression[j] = local[l];
		}
		for (int j = (int)(local.size() + begin); j <= end; ++j) {
			expression[j] = 0;
		}
	}
	else if (sLocal) {
		std::string local(('~') + to_string(localValues.size()));
		if (localValues[sIndx].getType()) {
			localValues.push_back(Value(local, globalValues[fIndx].getMatrix() - localValues[sIndx].getMatrix()));
		}
		else {
			localValues.push_back(Value(local, globalValues[fIndx].getFraction() - localValues[sIndx].getFraction()));
		}
		int l = 0;
		for (int j = begin; j < begin + local.size(); ++j, ++l) {
			expression[j] = local[l];
		}
		for (int j = (int)(local.size() + begin); j <= end; ++j) {
			expression[j] = 0;
		}
	}
	else {
		std::string local(('~') + to_string(localValues.size()));
		if (globalValues[fIndx].getType()) {
			localValues.push_back(Value(local, globalValues[fIndx].getMatrix() - globalValues[sIndx].getMatrix()));
		}
		else {
			localValues.push_back(Value(local, globalValues[fIndx].getFraction() - globalValues[sIndx].getFraction()));
		}
		int l = 0;
		for (int j = begin; j < begin + local.size(); ++j, ++l) {
			expression[j] = local[l];
		}
		for (int j = (int)(local.size() + begin); j <= end; ++j) {
			expression[j] = 0;
		}
	}
}
